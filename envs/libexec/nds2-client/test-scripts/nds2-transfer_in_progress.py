import nds2
import os
import sys

host = 'localhost'
if os.environ.has_key('NDS_TEST_HOST'):
    host = os.environ['NDS_TEST_HOST']
port = 31200
if os.environ.has_key('NDS_TEST_PORT'):
    port = int(os.environ['NDS_TEST_PORT'])

c = nds2.connection(host, port, nds2.connection.PROTOCOL_TWO)
buffers = []
channels = ["H0:PEM-CS_WIND_ROOF_WEATHER_MPH.mean,m-trend", "H0:PEM-EX_WIND_ROOF_WEATHER_MPH.mean,m-trend", "H0:PEM-EY_WIND_ROOF_WEATHER_MPH.mean,m-trend", "H1:ALS-X_REFL_CTRL_OUT_DQ.rms,m-trend", "H1:ALS-Y_REFL_CTRL_OUT_DQ.rms,m-trend"]
try:
    # currently this will fail
    # we expect to be able to start another fetch (in this case repeating this one)
    buffers = c.fetch(1109370240, 1109370240+864060, channels)
    raise Exception("Should not reach here, please reconfigure the test")
except RuntimeError as e:
    assert e.message == 'Requested data were not found.'
    try:
        buffers = c.fetch(1109370240, 1109370240+864060, channels)
    except RuntimeError as e2:
        # if this matches we cannot start another fetch w/o a new connection
        assert e2.message != 'Another transfer is already in progress. Complete the transfer or retry on a new connection object.'
        # we expect failure, but in this way
        assert e2.message == 'Requested data were not found.'


