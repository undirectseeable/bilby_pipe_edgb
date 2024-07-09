import nds2
import os

host = 'localhost'
if os.environ.has_key('NDS_TEST_HOST'):
    host = os.environ['NDS_TEST_HOST']
port = 31200
if os.environ.has_key('NDS_TEST_PORT'):
    port = int(os.environ['NDS_TEST_PORT'])

c = nds2.connection(host, port, nds2.connection.PROTOCOL_TWO)

start = 1108835634
end = start + 4

lst = c.find_channels('H1:SUS-BS*')
print('Found ' + str( len( lst ) ) + ' channels matching the pattern')

c.close()
