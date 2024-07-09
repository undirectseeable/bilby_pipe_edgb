import nds2
import os

#nds_query -1 -n localhost -p 31200 -s 1108842312 -e 1108842316 X2:SUS-ETMX_L1_OLDAMP_P_INMON X2:SUS-ETMX_L1_OSEMINF_UR_INMON

host = 'localhost'
if os.environ.has_key('NDS_TEST_HOST'):
    host = os.environ['NDS_TEST_HOST']
port = 31200
if os.environ.has_key('NDS_TEST_PORT'):
    port = int(os.environ['NDS_TEST_PORT'])

c = nds2.connection(host, port, nds2.connection.PROTOCOL_ONE)
channels = ["X2:SUS-ETMX_L1_OLDAMP_P_INMON", "X2:SUS-ETMX_L1_OSEMINF_UR_INMON"]

dat = c.fetch(1108842312, 1108842316, channels)
c.close()
print(dat)
print(dat[0].channel)
print(dat[1].channel)
