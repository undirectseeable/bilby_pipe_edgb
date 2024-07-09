#! /usr/bin/env python

import getopt
import os
import pexpect
import re
import sys

class server( object ):
    def __init__(self, Program):
        self.program = Program
        host = 'localhost'
        if os.environ.has_key('NDS_TEST_HOST'):
            host = os.environ['NDS_TEST_HOST']
        port = 31200
        if os.environ.has_key('NDS_TEST_PORT'):
            port = int(os.environ['NDS_TEST_PORT'])
        cmd = ('%s -r %s') % (
            scripting_prefix( self.program ),
            ( '%s:%d' ) % ( host, port )
            )
        print('Server command: ' + cmd)
        self.child = pexpect.spawn( cmd )

class client( object ):
    def __init__(self, Program):
        self.program = Program
        print('Client command: ' + Program)

    def launch(self):
        self.child = pexpect.spawn( scripting_prefix( self.program ) )

def scripting_prefix( Program ):
    print("Looking at python script: " + Program)
    if re.search( '.py$', Program ):
        return ( ( '%s %s') % ( 'python', Program) )
    return Program

def main(argv):
    clnt = client( argv[0] )
    if ( argv[1] ):
        srvr = server( argv[1] )
    clnt.launch( )

if __name__ == "__main__":
    main( sys.argv[1:] )
