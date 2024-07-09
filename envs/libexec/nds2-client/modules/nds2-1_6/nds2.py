from __future__ import print_function

import binascii
import collections
import struct

Channel = collections.namedtuple(
    'Channel',
    'id name channel_type rate data_type units')

channels = {}


def output_count(val, out):
    data = struct.pack("!I", val)
    out.write(data)
    out.flush()
    print(binascii.hexlify(data))


def get_channels(out, indexes):
    global channels

    output_count(len(indexes), out)
    for i in indexes:
        channel = channels[i]
        data = "%s %s %s %s\0" % (channel.name, channel.channel_type, str(channel.rate), channel.data_type)
        data = data.encode('utf-8')
        output_count(len(data), out)
        out.write(data)
        out.flush()
        # print(data)


def writer_id(out, id, online):
    """   
    :param out: output stream 
    :param id: writer id value
    :param online: true/"online" for an online stream, else offline
    :return: The writer id and online/offline flag
    """
    offline_val = 1
    if online == True or online == "online":
        offline_val = 0
    id_bytes = binascii.hexlify(str(id).encode())
    id_bytes = b"0" * (8-len(id_bytes)) + id_bytes
    out.write(id_bytes + struct.pack("!I", offline_val))


def reconfigure_block(out, chans, stride):
    """
    Write out a reconfiguration block
    :param out: output stream
    :param chans: list of channel ids in the block
    :param stride: stride in seconds of the data blocks
    :return: a reconfigure block
    """
    global channels

    def bytes_in_sample(data_type):
        if data_type in ('real_4', 'int_4', 'int_4'):
            return 4
        if data_type in ('real_8', 'complex_8', 'int_8'):
            return 8
        if data_type in ('int_2',):
            return 2
        raise Exception("Unknown channel data type {0}".format(channels[i].data_type))

    def get_data_type(data_type):
        mapping = {'int_2': 1, 'int_4': 2, 'int_8': 3, 'real_4': 4, 'real_8': 5, 'complex_8': 6, 'uint_4': 7}
        return mapping[data_type]

    def get_chan_type(channel_type):
        mapping = {'online': 1, 'raw': 2, 'reduced': 3, 's-trend': 4, 'm-trend': 5, 'test-pt': 6, 'static': 7, 'simdata': 8}
        return mapping[channel_type]

    unit_size = 4*len(chans)
    for id in chans:
        unit_size += len(channels[id].units)

    output = struct.pack("!IIIII", 16+4*6*len(chans)+unit_size, 0xffffffff, 1, 2, 3)
    offset = 0

    if stride == -1:
        stride = 1/16.0

    for id in chans:
        data_type = channels[id].data_type
        channel_type = channels[id].channel_type
        rate = channels[id].rate
        sample_size = bytes_in_sample(data_type)
        samples_in_stride = int(stride * rate)
        bytes_in_stride = sample_size * samples_in_stride
        status = bytes_in_stride
        units = channels[id].units.encode()
        output = output + struct.pack("!IIHHfffI", status, offset, get_chan_type(channel_type), get_data_type(data_type), rate, 0.0, 1.0, len(units)) + units
        offset += status
    out.write(output)


def data_header(out, chans, gps, stride, sequence, cycle_number=0):
    """
    Write a nds2 data block header
    :param out: output stream
    :param chans: list of channel ids
    :param gps: gps start time of the block
    :param stride: stride in seconds
    :param sequence: sequence number
    :return: 
    """
    def bytes_in_sample(data_type):
        if data_type in ('real_4', 'int_4', 'uint_4'):
            return 4
        if data_type in ('real_8', 'complex_8', 'int_8'):
            return 8
        if data_type in ('int_2',):
            return 2
        raise Exception("Unknown channel data type {0}".format(channels[i].data_type))

    if stride >= 0:
        cycle_number = 0
    nano = int(cycle_number * (1000000000/16))

    global channels
    size = 16
    multiplier = stride
    if stride == -1:
        multiplier = 1/16.0
        stride = 1
    for id in chans:
        size += bytes_in_sample(channels[id].data_type) * int(channels[id].rate * multiplier)
    out.write(struct.pack("!IiIII", size, stride, gps, nano, sequence))


def write_data(out, chan_id, count, value):
    global channels
    to_float = lambda x: float(x)
    to_int = lambda x: int(x)
    data_type = channels[chan_id].data_type
    type_map = {
        'real_4': ('!f', to_float),
        'real_8': ('!d', to_float),
        'int_2': ('!h', to_int),
        'int_4': ('!i', to_int),
        'int_8': ('!q', to_int),
        'uint_4': ('!I', to_int),
    }
    format, func = type_map[data_type]
    out.write(struct.pack(format, func(value)) * count)


def revision(inp, out):
    expected = "server-protocol-revision 6;\n"
    received = ""
    for cur in expected:
        ch = inp.read(1).decode('utf-8')
        received = received + ch
        if cur != ch:
            raise Exception("Unexpected command, wanted '%s', mismatch at '%s'" % (expected, received))

    print("read '{0}'".format(received))
    out.write(b'0000' + struct.pack('!I', 6))
    out.flush()


def translate_nds2_1_5_get_data_block(out, source):
    # pass through status, writer id,
    dat = source[0: 4+8+4]
    source = source[4+8+4:]
    out.write(dat)
    out.flush()

    units = b"undef"
    unit_data = struct.pack("!I", len(units)) + units

    std_hdr_size = 4*4
    reconf_info_size = 4*6

    while len(source) != 0:
        # don't actually take anything out of source yet
        blen = struct.unpack("!I", source[0:4])[0]
        stride = struct.unpack("!I", source[4:8])[0]

        if stride == 0xffffffff:
            # reconfigure block
            chan_count = (blen-std_hdr_size)//reconf_info_size
            added_blen = chan_count*(4 + len(units))

            # new block len
            out.write(struct.pack("!I", blen+added_blen))
            source = source[4:]
            # copy over common header (stride/gps/nano/seq)
            out.write(source[0:std_hdr_size])
            source = source[std_hdr_size:]

            for i in range(chan_count):
                # forward through the channel data
                out.write(source[0:reconf_info_size] + unit_data)
                source = source[reconf_info_size:]
        else:
            # data block, no rewritting just push it out
            out.write(source[0:4])
            source = source[4:]
            out.write(source[0:blen])
            source = source[blen:]
        out.flush()

def validate_action(action, args):
    if action == "register_chan" and len(args) >= 5 and len(args) <= 6:
        return
    if action == "get-channels" and len(args) > 0:
        return
    if action == "writer-id" and len(args) == 2:
        return
    if action == "reconfigure-block" and len(args) == 2:
        return
    if action == "data-header" and (len(args) == 4 or len(args) == 5):
        return
    if action == "write-data" and len(args) == 3:
        return
    if action == "revision" and len(args) == 0:
        return
    if action == "translate_nds2_1_5_get_data_block" and len(args) == 1:
        return


def execute_action(action, args, inp, out):
    global channels

    if action == "register_chan":
        targs = args
        if len(args) == 5:
            targs.append('undef')
        chan = Channel(*targs)
        channels[chan.id] = chan
    elif action == "get-channels":
        get_channels(out, args)
    elif action == "writer-id":
        writer_id(out, *args)
    elif action == "reconfigure-block":
        reconfigure_block(out, *args)
    elif action == "data-header":
        data_header(out, *args)
    elif action == "write-data":
        write_data(out, *args)
    elif action == "revision":
        revision(inp, out)
    elif action == "translate_nds2_1_5_get_data_block":
        translate_nds2_1_5_get_data_block(out, *args)
