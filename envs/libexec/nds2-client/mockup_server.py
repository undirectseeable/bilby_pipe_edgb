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
from __future__ import unicode_literals
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
import traceback

import unit_test

unit_tester = unit_test.unit_test( )

unit_tester.msg_info( 'Starting the nds1 mockup server' )

Channel = collections.namedtuple(
    'Channel',
    'name rate type tp_num group unit gain slope offset bytepattern')

# Type values
# 1 - 16bit int
# 2 - 32 bit int
# 3 - 64 bit int
# 4 - 32 bit float
# 5 - 64 bit float
# 6 - 32 bit complex
# 7 - 32 bit uint
#
# Fast channels on the NDS1 servers seem to have non-zero group numbers
channels = [
    Channel('X1:A', 16,    1, 0, 0,   'Undef', 1, 1, 0, binascii.unhexlify('B000')),
    Channel('X1:B', 16,    2, 0, 0,   'Undef', 1, 1, 0, binascii.unhexlify('DEADBEEF')),  
    Channel('X1:C', 16,    3, 0, 0,   'Undef', 1, 1, 0, binascii.unhexlify('00000000FEEDFACE')),
    Channel('X1:D', 16,    4, 0, 0,   'Undef', 1, 1, 0, binascii.unhexlify('600DF00D')),
    Channel('X1:E', 16,    5, 0, 0,   'Undef', 1, 1, 0, binascii.unhexlify('BAADF00D33333333')),
    Channel('X1:F', 16,    6, 0, 0,   'Undef', 1, 1, 0, binascii.unhexlify('600DDEEDBAADFACE')),
    Channel('X1:G', 16,    7, 0, 0,   'Undef', 1, 1, 0, binascii.unhexlify('FEEDFACE')),
    Channel('X1:H', 65536, 4, 0, 10,  'Undef', 1, 1, 0, binascii.unhexlify('FFDDF00D')),
    Channel('X1:I', 16384, 7, 0, 100, 'Undef', 1, 1, 0, binascii.unhexlify('FFEEFACE')),
]
channels_dict = dict((channel.name, channel) for channel in channels)
trend_dict = {}

def build_trend_dict():
    """Build up the trend dictionary with information from the base channel_dict.
       currently adds .min .max .mean .rms .n channels"""
    global trend_dict

    for name in channels_dict:
        trend_name = name + '.min'
        cur = channels_dict[name]
        bytepattern = binascii.unhexlify('0%d' % cur.type) * len(cur.bytepattern)
        params=[trend_name, 1, cur.type, cur.tp_num, cur.group, cur.unit, cur.gain, cur.slope, cur.offset, bytepattern]
        trend_dict[trend_name] = Channel(*params)

        trend_name = name + '.max'
        cur = channels_dict[name]
        bytepattern = binascii.unhexlify('1%d' % cur.type) * len(cur.bytepattern)
        params=[trend_name, 1, cur.type, cur.tp_num, cur.group, cur.unit, cur.gain, cur.slope, cur.offset, bytepattern]
        trend_dict[trend_name] = Channel(*params)

        trend_name = name + '.mean'
        cur = channels_dict[name]
        bytepattern = binascii.unhexlify('%dA' % cur.type) * 8
        params=[trend_name, 1, 5, cur.tp_num, cur.group, cur.unit, cur.gain, cur.slope, cur.offset, bytepattern]
        trend_dict[trend_name] = Channel(*params)
        
        trend_name = name + '.rms'
        cur = channels_dict[name]
        bytepattern = binascii.unhexlify('%dB' % cur.type) * 8
        params=[trend_name, 1, 5, cur.tp_num, cur.group, cur.unit, cur.gain, cur.slope, cur.offset, bytepattern]
        trend_dict[trend_name] = Channel(*params)

        trend_name = name + '.n'
        cur = channels_dict[name]
        bytepattern = binascii.unhexlify('%dC' % cur.type) * 4
        params=[trend_name, 1, 2, cur.tp_num, cur.group, cur.unit, cur.gain, cur.slope, cur.offset, bytepattern]
        trend_dict[trend_name] = Channel(*params)

class UnknownChannelError(ValueError):
    pass

def is_net_writer_command(cmd):
    """Returns true if the command is a net-writer command (raw data, minute, and second trends match)"""
    return re.match("start (trend (60 )?)?net-writer", cmd) != None


def channels_for_cmd(cmd):
    try:
        left_brace_index = cmd.index('{')
    except ValueError:
        return channels

    s = cmd[left_brace_index:].lstrip('{').rstrip('}')
    names = [field.strip('"') for field in s.split()]

    try:
        return [channels_dict[name] for name in names]
    except KeyError:
        raise UnknownChannelError

def channels_for_trend_cmd(cmd):
    left_brace_index = cmd.index('{')

    s = cmd[left_brace_index:].lstrip('{').rstrip('}')
    names = [field.strip('"') for field in s.split()]

    try:
        return [trend_dict[name] for name in names]
    except KeyError:
        raise UnknownChannelError


def hex_float(f):
    print("f = {0} type(f) = {1}".format(f, type(f)))
    return binascii.hexlify(struct.pack(b'>f', f))


def net_writer_cmd(cmd, f):
    RAW_DATA = 0
    S_TREND = 1
    M_TREND = 2
    match = re.match(r'start (?P<trend>trend (?P<minute_trend>60 )?)?net-writer(?P<timing> (?P<timestamp>\d+) (?P<duration>\d+))?', cmd)
    if match == None:
        return False
    trend_type = RAW_DATA
    time_step = 1
    mult = 1
    if match.group('trend') != None:
        chans = channels_for_trend_cmd(cmd)
        trend_type = S_TREND
        if match.group('minute_trend') != None:
            trend_type = M_TREND
            time_step = 60
    else:
        chans = channels_for_cmd(cmd)

    if match.group('timing') != None:
        offline = True
        timestamp = int(match.group('timestamp'))
        duration = int(match.group('duration'))
        if trend_type == 'minute':
            if timestamp % 60 != 0 or duration % 60 != 0:
                return False
        if trend_type != RAW_DATA:
            mult = duration//time_step
    else:
        if trend_type != RAW_DATA:
            return False
        timestamp = 1000000000
        duration = float('inf')
        offline = False

    f.write(b'0' * 12)
    f.write(struct.pack(b'>I', offline))
    f.write(struct.pack(b'>Iiiii',
        len(chans) * 12 + 16,
        -1, -1, 3, -1))
    for channel in chans:
        # WTF! randomly in little-endian order?
        f.write(struct.pack(b'<ffI', channel.offset, channel.slope, 0))
    bytes_per_buffer = sum(len(channel.bytepattern) * channel.rate for channel in chans) * mult
    seq_num = 0
    while duration > 0:
        f.write(struct.pack(b'>IIIII',
            16 + bytes_per_buffer,
            time_step*mult, timestamp, 0, seq_num))
        for channel in chans:
            f.write(channel.bytepattern[::-1] * (channel.rate * mult))
        seq_num += 1
        timestamp += time_step*mult
        duration -= time_step*mult
    f.write(struct.pack(b'>IIIII',
        16, 0, 0, 0, 0))
    f.flush()
    return True

def serve(conn):
    f = conn.makefile('rwb')
    try:
        for cmd in f:
            cmd = cmd.strip().decode('utf-8').rstrip(';')
            print("MOCK SERVE CMD: '{0}'".format(cmd), file=sys.stderr)
            try:
                if cmd == '':
                    continue
                elif cmd == 'version':
                    f.write(b'0000000c')
                elif cmd == 'revision':
                    f.write(b'00000000')
                elif cmd[:17] == 'status channels 2':
                    # FIXME: HACK for broken servers that return
                    # errant tabs at the end of channel names when
                    # individual channels are requested.
                    hack_val = u''
                    if os.getenv('NDS1_MOCKUP_SERVER_BROKEN', False) \
                       and '{' in cmd:
                        print("Inserting hack \\t in the status channels 2 output");
                        hack_val = u'\t'
                    # FIXME: END HACK
                    chans = channels_for_cmd(cmd)
                    s = '0000{0:08X}'.format(len(chans))
                    f.write(s.encode('utf-8'))
                    print(s)
                    for channel in chans:
                        s = u'{name:60s}{tab_hack}{rate:08X}{tp_num:08X}{group:04X}{type:04X}{hex_gain:s}{hex_slope:s}{hex_offset:s}{unit:40s}'.format(
                            name=channel.name,
                            rate=channel.rate,
                            tp_num=channel.tp_num,
                            group=channel.group,
                            type=channel.type,
                            unit=channel.unit,
                            hex_gain=hex_float(channel.gain).decode('utf-8'),
                            hex_slope=hex_float(channel.slope).decode('utf-8'),
                            hex_offset=hex_float(channel.offset).decode('utf-8'),
                            tab_hack=hack_val,
                        ).encode('utf-8')
                        f.write(s)
                        f.flush()
                        print(s)
                        print("Done with status channels 2")
                elif cmd[:17] == 'status channels 3':
                    chans = channels_for_cmd(cmd)
                    f.write(b'0000{0:d}\n'.format(len(chans)))
                    for channel in chans:
                        # Skip last fields, which is hex data pattern
                        for field in channel[:-3]:
                            f.write(str(field) + '\n')
                elif is_net_writer_command(cmd):
                    if not net_writer_cmd(cmd, f):
                        break
                elif cmd == 'quit':
                    break
                else:
                    # NDS1 servers drop the connection upon receiving
                    # an unknown command
                    raise ValueError("unknown command: %s" % cmd)
            except UnknownChannelError:
                f.write(b'0004')
            f.flush()
    except IOError:
        pass # ignore, just try close socket
    finally:
        # try to close socket, don't really care if any of this fails
        try:
            f.close()
        except:
            pass
        try:
            conn.shutdown(socket.SHUT_RDWR)
        except:
            pass
        try:
            conn.close()
        except:
            pass

unit_tester.msg_info( 'Starting the nds1 mockup server' )
# build the trend dict
build_trend_dict()

# Create socket bound to a random ephemeral port
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
sock.bind(('127.0.0.1', 0))
_, port = sock.getsockname()

def listen():
    while True:
        sock.listen(2)
        conn, _ = sock.accept()
        serve_thread = threading.Thread(target=serve, args=(conn,))
        serve_thread.daemon = True
        serve_thread.start()


def exec_client( ):
    global unit_tester

    status = 0
    proc = None
    try:
        proc = subprocess.Popen( sys.argv[1:] )
        proc.wait( )
    finally:
        if ( proc ):
            status = proc.returncode
            unit_tester.msg_debug( 0, 'mockup_server stdout: {0}'.format( proc.stdout ) )
            unit_tester.msg_debug( 0, 'mockup_server stderr: {0}'.format( proc.stderr ) )
        else:
            status = 1
    return status

listen_thread = threading.Thread(target=listen)
listen_thread.daemon = True
listen_thread.start()

os.environ['NDS_TEST_PORT'] = str(port)
db_dir = tempfile.mkdtemp()
try:
    if len(sys.argv) == 1:
        import time
        print("Running in standalone mode on port {0}.  Press enter to exit".format(port))
        sys.stdin.read()
        sys.exit()

    os.environ['NDS1_MOCKUP_SERVER_BROKEN'] = 't'
    os.environ['NDS2_CHANNEL_DB_DIR'] = db_dir
    sys.argv[1] = sys.argv[1].replace('/.libs/lt-','/')
    sys.argv[1] = sys.argv[1].replace('/.libs/','/')
    print('INFO: command: %s' % sys.argv[1])
    print('Testing with read-writable database...', file=sys.stderr)
    unit_tester.msg_info( 'mockup serverver invoking subprocess: {0}'.format( sys.argv[1:] ) )
    status = exec_client( )
    #if status == 0:
    #    for filename in os.listdir(db_dir):
    #        os.chmod(os.path.join(db_dir, filename), stat.S_IREAD)
    #    print('Testing with read-only database...', file=sys.stderr)
    #    status = exec_client( )
except Exception as Error:
    unit_tester.msg_error( 'mock_server exception: {0}'.format( traceback.format_exc()) )
    status = 1
finally:
    shutil.rmtree(db_dir)
sys.exit(status)
