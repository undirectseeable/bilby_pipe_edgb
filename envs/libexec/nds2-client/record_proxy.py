#!/usr/bin/env python

from __future__ import print_function

import optparse
import os.path
import select
import socket
import sys

import replay

class Recorder(object):
	def __init__(self):
		self.cmd = ""
		self.received = ""
		self.scripts = []

	def __push_back(self):
		if not (self.cmd == "" and self.received == ""):
			self.scripts.append(replay.Script(self.cmd, self.received))
		self.cmd = ""
		self.received = ""

	def set_command(self, cmd):
		if len(cmd) == cmd.count('\n'):
			self.cmd = self.cmd + cmd
			print("Expanding command " + self.cmd)
			return
		self.__push_back()
		self.cmd = cmd
		self.received = ""
	
	def receive_response(self, response):
		self.received = self.received + response

	def script(self):
		self.__push_back()
		return replay.CompoundScript(self.scripts)

class ClientRecorder(Recorder):
	def __init__(self):
		super(ClientRecorder, self).__init__()

	def client_read(self, data):
		self.set_command(data)

	def client_write(self, data):
		self.receive_response(data)

	def server_read(self, data):
		pass

	def server_write(self, data):
		pass

# class ServerRecorder(Recorder):
# 	def __init__(self):
# 		super(ServerRecorder, self).__init__()

# 	def server_read(self, data):
# 		self.set_command(data)

# 	def server_write(self, data):
# 		self.receive_response(data)

# 	def client_read(self, data):
# 		pass

# 	def client_write(self, data):
# 		pass

def proxy_loop(clientc, serverc, recorder):
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

			rlist, wlist, xlist	 = select.select(rlist, wlist, [])

			for fd in rlist:
				if fd == cnum:
					buf = clientc.recv(4096)
					recorder.client_read(buf)
					print("Received %d bytes from the client '%s'" % (len(buf), buf))
					sbuf = sbuf + buf
					if len(buf) == 0:
						print("Client closed")
						closed = True
					
				elif fd == snum:
					buf = serverc.recv(4096)
					recorder.server_read(buf)
					#print "Received %d bytes from the server '%s'" % (len(buf), buf[:10])
					print(".", end=' ')
					cbuf = cbuf + buf
					if len(buf) == 0:
						print("Server closed")
						closed = True
					

			for fd in wlist:
				if fd == cnum and len(cbuf) > 0:
					count = clientc.send(cbuf)
					recorder.client_write(cbuf[:count])
					cbuf = cbuf[count:]
				elif fd == snum and len(sbuf) > 0:
					count = serverc.send(sbuf)
					recorder.server_write(sbuf[:count])
					sbuf = sbuf[count:]

			if len(xlist) > 0:
				print("xlist = %s\nc = %d s=%d\n" % (str(xlist), cnum, snum))
				break
	except socket.error:
		pass

def get_filename(dest_dir, basename, count):
	base = os.path.join(dest_dir, basename)
	while True:
		fname = "%s-%d.json" % (base, count)
		if not os.path.exists(fname):
			return fname
		count = count + 1

def run_proxy(clientc, remote_addr, dest_dir, basename, count):
	recorder = ClientRecorder()
	serverc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	try:
		serverc.connect(remote_addr)
		serverc.setblocking(0)
		print("Connected to %s" % str(remote_addr))
		proxy_loop(clientc, serverc, recorder)
	finally:
		serverc.close()
	script_path = get_filename(dest_dir, basename, count)
	print("Writing script to %s" % script_path)
	with open(script_path, "wt") as f:
		replay.save_scripts({"recorded_script": recorder.script()}, f)
	print("done.")

def make_address(addr):
	host, port = addr.split(':', 1)
	return (host, int(port))

parser = optparse.OptionParser()
parser.add_option('-l', '--listen', help="address:port to listen on.  [%default]", action="store", type="string", dest="listen_addr", default="127.0.0.1:31200")
parser.add_option('-r', '--remote', help="address:port to proxy to.  [%default]", action="store", type="string", dest="remote_addr", default="127.0.0.1:8088")
parser.add_option('-o', '--output', help="base name of the output file.  The actual output will be basename-number.json [%default]", action="store", type="string", dest="basename", default="proxy_script")

(options, args) = parser.parse_args()

listen_addr = make_address(options.listen_addr)
remote_addr = make_address(options.remote_addr)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(listen_addr)
print("Proxing %s:%d to %s:%d" % (listen_addr[0], listen_addr[1], remote_addr[0], remote_addr[1]))
print("Scripts will be recorded to '%s-?.json'" % options.basename)

i = 1
try:
	while True:
		conn = None
		try:
			s.listen(1)
			conn, addr = s.accept()
			conn.setblocking(0)
			print("Connection from %s" % str(addr))
			run_proxy(conn, remote_addr, "./", options.basename, i)
			i = i + 1
		finally:
			if conn != None:
				conn.close()
finally:
	s.close()