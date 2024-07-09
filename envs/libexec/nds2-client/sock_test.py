#!/usr/bin/env python

#
# Copyright (C) 2015 LIGO Lab
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

import json
import optparse
import os
import select
import shutil
import socket
# import stat
import subprocess
import sys
import threading
import tempfile
import time
import traceback

import replay

server_status_lock = threading.Lock()
server_has_error = False

scripts = {}

class socket_file_adaptor(object):
    def __init__(self, s):
        self.s = s
        self.buf = b''
        # print("socket_file_adaptor {0} {1} {2} {3}".format(self, type(s), s, s.fileno()), )

    def read(self, count):
        if count == 0:
            # print('null read')
            return b''
        while len(self.buf) < count:
            # print("Reading more data from self.s {0} {1} {2}".format(self, type(self.s), self.s))
            self.buf += self.s.recv(1024)
        data = self.buf[:count]
        self.buf = self.buf[count:]
        assert(len(data) == count)
        # print("Returning '{0}'".format(data.decode('utf-8')))
        return data

    def readline(self):
        index = self.buf.find(b'\n')
        while index < 0:
            self.buf += self.s.recv(1024)
            index = self.buf.find(b'\n')
        data = self.read(index+1)
        # print("Readline returning '{0}'".format(data))
        return data

    def read_remaining(self):
        data = self.buf
        self.buf = b''
        while True:
            rlist = [self.s]
            avail = select.select(rlist, [], [], 0.0)
            ravail = avail[0]
            if len(ravail) == 0:
                return data
            data = data + self.s.recv(1024)

    def flush(self):
        pass

    def write(self, data):
        if len(data) == 0:
            # print('null write')
            return
        # print("Sending => '{0}'".format(data.decode('utf-8')))
        self.s.sendall(data)

    def close(self):
        assert(False)
        pass

class multi_acceptor(object):
    def __init__(self, server):
        self.__server = server

    def __call__(self):
        conn, addr = self.__server.accept()
        print("Multi server received new connection on {0}".format(addr))
        return socket_file_adaptor(conn)


def run_script(conn, test_name, server=None):
    global scripts
    global server_status_lock
    global server_has_error

    try:
        # f = conn.makefile(mode='rwb')
        f = socket_file_adaptor(conn)
        if hasattr(scripts[test_name], 'call_with_server'):
            scripts[test_name].call_with_server(f, f, multi_acceptor(server))
        else:
            scripts[test_name](f, f)
    except replay.CloseButNoAbort:
        print("Closing connection, test not complete however")
        server_status_lock.acquire()
        server_has_error = True
        server_status_lock.release()
    except:
        server_status_lock.acquire()
        server_has_error = True
        server_status_lock.release()
        print(traceback.format_exc())
    finally:
        conn.close()


def make_addr(addr):
    host, port = addr.split(':', 1)
    return (host, int(port))


def run_test_as_a_thread(test_name):
    global scripts

    result = hasattr(scripts[test_name], 'call_with_server')
    return not result

def listen(s):
    try:
        while True:
            s.listen(2)
            conn, addr = s.accept()
            print("Connection from %s running %s" % (str(addr), options.test_name))
            # try:
            #	run_script(conn, options.test_name)
            # finally:
            #	conn.close()
            if run_test_as_a_thread(options.test_name):
                serve_thread = threading.Thread(target=run_script, args=(conn, options.test_name))
                serve_thread.daemon = True
                serve_thread.start()
            else:
                print("Starting a multi accept script")
                run_script(conn, options.test_name, server=s)
    finally:
        s.shutdown()
        s.close()


parser = optparse.OptionParser()
parser.disable_interspersed_args()
parser.add_option('-l', '--listen', help="address:port to listen on.  [%default]", action="store", type="string",
                  dest="listen_addr", default="127.0.0.1:0")
parser.add_option('-i', '--input', help="script file to load [%default]", action="store", type="string",
                  dest="script_file", default="script.json")
parser.add_option('-t', '--name', help="The name of the test to run [%default]", action="store", type="string",
                  dest="test_name", default="recorded_script")
parser.add_option('-p', '--path', help="Comma separated additions to the PYTHONPATH to use when loading command modules", action="store", type="string", default="")

(options, args) = parser.parse_args()
listen_addr = make_addr(options.listen_addr)

if options.path != "":
    for part in options.path.split(','):
        if part == "":
            continue
        sys.path.insert(1, part)


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(listen_addr)
host, port = s.getsockname()
print('Test server listening on %s:%d' % (host, port))
with open(options.script_file, "rt") as f:
    scripts = replay.load_scripts(f)

listen_as_daemon = False
if not args == []:
    listen_as_daemon = True

listen_thread = threading.Thread(target=listen, args=(s,))
listen_thread.daemon = listen_as_daemon
listen_thread.start()

if not args == []:
    os.environ['NDS_TEST_HOST'] = str(host)
    os.environ['NDS_TEST_PORT'] = str(port)
    db_dir = tempfile.mkdtemp()
    status = 0
    output = ''
    try:
        os.environ['NDS2_CHANNEL_DB_DIR'] = db_dir
        print('Testing with read-writable database...')
        output = subprocess.check_output(args, stderr=subprocess.STDOUT)
    # if status == 0:
    #    for filename in os.listdir(db_dir):
    #        os.chmod(os.path.join(db_dir, filename), stat.S_IREAD)
    #    print( 'Testing with read-only database...' )
    #    status = subprocess.call(args)
    except subprocess.CalledProcessError as e:
        output = e.output
        status = e.returncode
    finally:
        shutil.rmtree(db_dir)
    # give the server thread a chance to finish
    # maybe we should work out a condition variable or something
    # but I want to make sure we don't error on side out and leave
    # the other hanging in an infinite wait.
    time.sleep(0.1)
    server_status_lock.acquire()
    if server_has_error:
        status = 1
    server_status_lock.release()
    print('-- DEBUG: %s' % output)
    sys.exit(status)
# else:
#	listen(s)
