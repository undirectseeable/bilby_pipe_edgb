import nds2
import os
import sys

host = 'localhost'
if os.environ.has_key('NDS_TEST_HOST'):
    host = os.environ['NDS_TEST_HOST']
port = 31200
if os.environ.has_key('NDS_TEST_PORT'):
    port = int(os.environ['NDS_TEST_PORT'])

c = nds2.connection(host, port, nds2.connection.PROTOCOL_ONE)

try:

    dat = c.fetch(1108835634, 1108835634+4, ["X1:E"])

except RuntimeError as e:
    print("Caught Runtime error, should be a lack of data")
    sys.exit(0)
sys.exit(1)
