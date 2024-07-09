import nds2
import os
import sys

host = os.getenv('NDS_TEST_HOST', 'localhost')
port = int(os.getenv('NDS_TEST_PORT', 31200))

c = nds2.connection(host, port, nds2.connection.PROTOCOL_ONE)

try:

    lst = c.find_channels('*')

except RuntimeError as e:
    print("Caught Runtime error, should be from a timeout, but we currently cannot get a good error message")
    sys.exit(0)
print("Did not test timeouts!!!!")
sys.exit(1)
