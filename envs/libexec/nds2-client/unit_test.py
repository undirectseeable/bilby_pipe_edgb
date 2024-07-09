#! /usr/bin/env python

import os
import sys

class unit_test( object ):
    def __init__( self, value = -1 ):
        self.debug_level = int(os.getenv( 'TEST_VERBOSE_LEVEL', value ))
        self.status = 0

    def check( self, condition, msg, exit_status = 1):
        lead = '-- PASS: '
        if ( not condition ):
            lead = '-- FAIL: '
            if ( self.status == 0 ):
                self.status = exit_status
        self.message( '%s%s' % ( lead, msg ) )

    def exit( self ):
        sys.exit( self.status )

    def message( self, text ):
        text = str( text )
        print( '%s' % ( text ) )

    def msg_debug( self, level, msg ):
        if ( self.debug_level >= level ):
            msg = '-- DBUG: %s' % ( msg )
            self.message( msg )

    def msg_info( self, msg ):
        msg = '-- INFO: %s' % ( msg )
        self.message( msg )

    def msg_error( self, msg, exit_status = 1 ):
        msg = '-- ERRO: %s' % ( msg )
        self.message( msg )
        if ( self.status == 0 ):
            self.status = exit_status

    def msg_skip( self, msg, exit_status = 77 ):
        self.message( '-- SKIP: %s' % msg )
        if ( self.status == 0 ):
            self.status = exit_status

if( __name__ == '__main__'):
    exit( 1 )
    
