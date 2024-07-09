#!/usr/bin/env python

import ctypes

import optparse
import os.path
import platform
import select
import socket
import sys
import threading
import time

def libcononical(LibName):
    parent = './client/build-osx/tests/'
    prefix = 'lib'
    suffix = '.so'
    parent_subdir = '.libs'

    if platform.system( ) == 'Darwin':
        suffix = '.dylib'
    retval = ('%s%s%s') % (prefix,LibName,suffix)

    if parent_subdir:
        parent = os.path.join( parent, 'sasl', parent_subdir )
    retval = os.path.join( parent, retval )
    return retval

ctypes.cdll.LoadLibrary(libcononical('sasl'))
libsasl = ctypes.CDLL(libcononical('sasl'))
libsasl.nds_authenticate.argtypes=[ctypes.c_int, ctypes.c_char_p]
libsasl.nds_authenticate.restype = ctypes.c_int        

def proxy_loop(clientc, serverc, thread_num):
    global remote_addr
    closed = False

    cbuf = ""
    sbuf = ""

    try:

        cnum = clientc.fileno()
        snum = serverc.fileno()
        while not closed:
            rlist = []
            wlist = []
            if len(cbuf) == 0:
                rlist.append(cnum)
            else:
                wlist.append(cnum)
            if len(sbuf) == 0:
                rlist.append(snum)
            else:
                wlist.append(snum)

            rlist, wlist, xlist  = select.select(rlist, wlist, [])

            for fd in rlist:
                if fd == cnum:
                    buf = clientc.recv(4096)
                    print("[%d] Received %d bytes from the client '%s'" % (thread_num, len(buf), buf))
                    sbuf = sbuf + buf
                    if len(buf) == 0:
                        print("[%d] Client closed" % thread_num)
                        closed = True

                    if buf == "authorize\n":
                        print("[%d] Found an authorize command, hijacking the system" % thread_num)
                        #print "setting to blocking"
                        serverc.setblocking(1)
                        clientc.setblocking(1)
                        serverc.send(sbuf)
                        #print "Sent buffer to server"
                        sbuf = ""
                        resp = serverc.recv(4)
                        #print "received a reply of %s" % resp
                        if resp == "0018":
                            if libsasl.nds_authenticate(serverc.fileno(), remote_addr[0]) != 0:
                                print("[%d] SASL Failed" % thread_num)
                                raise RuntimeError("[%d] Auth Failure" % thread_num)
                            print("[%d] SASL succeeded" % thread_num)
                        clientc.send("0000")
                        #print "setting non-blocking"
                        serverc.setblocking(0)
                        clientc.setblocking(0)
                    
                    
                elif fd == snum:
                    buf = serverc.recv(4096)
                    #print "Received %d bytes from the server '%s'" % (len(buf), buf[:10])
                    #print ".",
                    cbuf = cbuf + buf
                    if len(buf) == 0:
                        print("[%d] Server closed" % thread_num)
                        closed = True
                    

            for fd in wlist:
                if fd == cnum and len(cbuf) > 0:
                    count = clientc.send(cbuf)
                    cbuf = cbuf[count:]
                elif fd == snum and len(sbuf) > 0:
                    count = serverc.send(sbuf)
                    sbuf = sbuf[count:]

            if len(xlist) > 0:
                #print "xlist = %s\nc = %d s=%d\n" % (str(xlist), cnum, snum)
                break
    except socket.error:
        raise

def run_proxy(clientc, remote_addr, thread_num):
    print("run_proxy %s %s %s" % (str(clientc), str(remote_addr), str(thread_num)))
    monitor_this_thread(thread_num)
    serverc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        serverc.connect(remote_addr)
        serverc.setblocking(0)
        print("[%d] Connected to %s" % (thread_num, str(remote_addr)))
        proxy_loop(clientc, serverc, thread_num)
    finally:
        serverc.close()
    print("done.")

def monitor_this_thread(id):
    global monitor_lock
    global monitor_list

    print("%s registering thread with id %s" % (time.strftime("%c"),str(id)))
    cur = threading.current_thread()
    with monitor_lock:    
        monitor_list[id] = cur


def monitor_thread_loop():
    global monitor_lock
    global monitor_list

    """Main loop for the monitor thread.  Its job is to join and the proxy threads periodically"""
    while True:
        joined = 0
        with monitor_lock:
            key_list = monitor_list.keys()
            for entry_key in key_list:
                monitor_list[entry_key].join(0.0)
                if not monitor_list[entry_key].is_alive():
                    joined += 1
                    del monitor_list[entry_key]
        if (joined > 0):
            print("%s Joined %d threads" % (time.strftime("%c"), joined))
        time.sleep(10.0)


def make_address(addr):
    host, port = addr.split(':', 1)
    return (host, int(port))


parser = optparse.OptionParser()
parser.add_option('-l', '--listen', help="address:port to listen on.  [%default]", action="store", type="string", dest="listen_addr", default="127.0.0.1:0")
parser.add_option('-r', '--remote', help="address:port to proxy to.  [%default]", action="store", type="string", dest="remote_addr", default="127.0.0.1:31200")
(options, args) = parser.parse_args()

listen_addr = make_address(options.listen_addr)
remote_addr = make_address(options.remote_addr)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(listen_addr)
listen_addr, listen_port = s.getsockname()

monitor_list = {}
monitor_lock = threading.Lock()
monitor_thread = threading.Thread(group=None, target=monitor_thread_loop, args=(), kwargs={})
monitor_thread.daemon = True
monitor_thread.start()

print("Proxing %s:%d to %s:%d" % (listen_addr, listen_port, remote_addr[0], remote_addr[1]))

id = 0
try:
    while True:
        s.listen(1)
        conn, addr = s.accept()
        conn.setblocking(0)
        print("%s Connection %d from %s" % (time.strftime("%c"), id, str(addr)))
        th = threading.Thread(group=None, target=run_proxy, name="client-%d" % id, args=(conn, remote_addr, id), kwargs={})
        th.daemon = True
        th.start()
        id += 1
finally:
    s.close()
