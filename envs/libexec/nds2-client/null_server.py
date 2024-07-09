#
# Mock-up NDS 1 server
#
# Based on:
#   * https://dcc.ligo.org/T980024
#   * https://dcc.ligo.org/T0900636
#   * and reverse-engineering packet formats with tcpdump
#
# Copyright (C) 2014  Leo Singer <leo.singer@ligo.org>
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

from __future__ import print_function
import binascii
import collections
import copy
import os
import re
import shutil
import socket
import stat
import subprocess
import struct
import sys
import tempfile
import threading

import unit_test

unit_tester = unit_test.unit_test( )

unit_tester.msg_info( 'Starting the null server' )

def exec_client( ):
    global unit_tester

    status = 0
    proc = None
    try:
        unit_tester.msg_info( 'null server: exec_client: %s' % str( sys.argv[1:] ) )
        proc = subprocess.Popen( sys.argv[1:] )
        proc.wait( )
    finally:
        if ( proc ):
            status = proc.returncode
            unit_tester.msg_debug( 0, 'null_server stdout: %s' % str( proc.stdout ) )
            unit_tester.msg_debug( 0, 'null_server stderr: %s' % str( proc.stderr ) )
        else:
            status = 1
    return status

try:
    os.environ['NDS1_MOCKUP_SERVER_BROKEN'] = 't'
    sys.argv[1] = sys.argv[1].replace('/.libs/lt-','/')
    sys.argv[1] = sys.argv[1].replace('/.libs/','/')
    print('INFO: command: %s' % sys.argv[1])
    status = exec_client( )
except Exception as Error:
    unit_tester.msg_error( 'mock_server exception: %s' % str( Error) )
    status = 1
sys.exit(status)
