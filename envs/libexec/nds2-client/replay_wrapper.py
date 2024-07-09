#! /usr/bin/env python

import getopt
import os
import pexpect
import re
import subprocess
import sys

class server( object ):
    def __init__(self, Program, Client ):
        self.program = Program
        host = 'localhost'
        if os.environ.has_key('NDS_TEST_HOST'):
            host = os.environ['NDS_TEST_HOST']
        port = 31200
        if os.environ.has_key('NDS_TEST_PORT'):
            port = int(os.environ['NDS_TEST_PORT'])
        session = 'proxy_script-1.json'
        if os.environ.has_key('NDS_TEST_SESSION'):
            session = os.environ['NDS_TEST_SESSION']
        cmd = ('%s -l %s -i %s %s') % (
            scripting_prefix( self.program ),
            ( '%s:%d' ) % ( host, port ),
            session,
            Client
            )
        print('Server command: ' + cmd)
        # (command_output, exitstatus) = pexpect.run( cmd, withexitstatus=1 )
        p = subprocess.Popen( cmd.split( ), stdout=subprocess.PIPE, stderr=subprocess.PIPE )
        command_stdout, command_stderr = p.communicate( )
        print('Server output: ' + command_stdout)
        print('Server exit:   ' + str( p.returncode ))

class client( object ):
    def __init__(self, Program):
        self.program = Program
        print('Client command: ' + Program)

    def __str__(self):
        return( scripting_prefix( self.program ) )

def scripting_prefix( Program ):
    print("Looking at python script: " + Program)
    if re.search( '.py$', Program ):
        return ( ( '%s %s') % ( 'python', Program) )
    return Program

def main(argv):
    clnt = client( argv[0] )
    server_cmd = 'sock_test.py'
    if ( argv[1] ):
        server_cmd = argv[1]
    srvr = server( server_cmd, clnt )

if __name__ == "__main__":
    main( sys.argv[1:] )
