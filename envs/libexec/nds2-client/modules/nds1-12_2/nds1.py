from __future__ import print_function

import binascii
import collections
import struct
import re

simple_st_chan_3 = re.compile("^status channels 3 \{\"(?P<channel>[A-Z:A-Za-z\-_0-9]+)\"\};$")
simple_st_net_writer = re.compile("^start net-writer (?P<start>[0-9]+) (?P<duration>[0-9]+) \{\"(?P<channel>[A-Z:A-Za-z\-_0-9]+)\"\};$")

Channel = collections.namedtuple(
    'Channel',
    'name rate type tp_num group unit gain slope offset')


channels = {}


def _pack_daq_float32(val):
    return binascii.hexlify(struct.pack("!f", val))


def _pack_daq_int32(val):
    return binascii.hexlify(struct.pack("!I", val))


def _pack_daq_int16(val):
    return binascii.hexlify(struct.pack("!H", val))


def sc3_12_1(channel, out):
    print("Status channels 3 for %s\n" % channel.name)

    output = "{0}\n{1}\n{2}\n{3}\n{4}\n{5}\n{6}\n{7}\n{8}\n".format(
        channel.name,
        channel.rate,
        channel.type,
        channel.tp_num,
        channel.group,
        channel.unit,
        channel.gain,
        channel.slope,
        channel.offset,
    )
    out.write(output.encode())
    out.flush()


def sc2_12_1(channel, out):
    print("Status channels 2 for %s\n" % channel.name)
    name_data = "{0}{1}".format(channel.name, " " * (60 - len(channel.name)))
    out.write(name_data.encode())
    unit_data = "{0}{1}".format(channel.unit, " " * (40 - len(channel.unit)))
    out.write(_pack_daq_int32(channel.rate))
    out.write(_pack_daq_int32(channel.tp_num))
    out.write(_pack_daq_int16(channel.group))
    out.write(_pack_daq_int16(channel.type))
    out.write(_pack_daq_float32(channel.gain))
    out.write(_pack_daq_float32(channel.slope))
    out.write(_pack_daq_float32(channel.offset))
    out.write(unit_data.encode())
    out.flush()


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
    id_bytes = "{0:>08}".format(hex(id)[2:])
    out.write(id_bytes.encode() + struct.pack("!I", offline_val))


def reconfigure_block(out, chans):
    """
    Write out a reconfiguration block
    :param out: output stream
    :param chans: list of channel ids in the block
    :param stride: stride in seconds of the data blocks
    :return: a reconfigure block
    """
    global channels

    output = struct.pack("!IIIII", 16+4*3*len(chans), 0xffffffff, 0xffffffff, 3, 0xffffffff)
    offset = 0
    for name in chans:
        offset = 0.0
        slope = channels[name].slope
        status = 0
        output = output + struct.pack("<ffI", offset, slope, status)
    out.write(output)


def data_header(out, chans, gps, stride, sequence):
    """
    Write a nds1 data block header
    :param out: output stream
    :param chans: list of channel names
    :param gps: gps start time of the block
    :param stride: stride in seconds
    :param sequence: sequence number
    :return: 
    """
    def bytes_in_sample(data_type):
        if data_type in (4, 2, 7):
            return 4
        if data_type in (5, 6, 3):
            return 8
        if data_type in (1,):
            return 2
        raise Exception("Unknown channel data type {0}".format(channels[i].data_type))

    global channels
    size = 16
    for name in chans:
        size += bytes_in_sample(channels[name].type) * channels[name].rate * stride
    out.write(struct.pack("!IIIII", size, stride, gps, 0, sequence))


def write_data(out, chan_name, count, value):
    global channels
    to_float = lambda x: float(x)
    to_int = lambda x: int(x)
    data_type = channels[chan_name].type
    type_map = {
        4: ('!f', to_float),
        5: ('!d', to_float),
        1: ('!h', to_int),
        2: ('!i', to_int),
        3: ('!q', to_int),
        7: ('!I', to_int),
    }
    format, func = type_map[data_type]
    out.write(struct.pack(format, func(value)) * count)


def termination_block(out):
    out.write(struct.pack("!IIIII", 16, 0, 0, 0, 0))


def handle_start_net_writer_full(inp, out, count):
    global simple_st_chan_3
    global simple_st_net_writer
    global channels

    i = 0
    while i < count:
        line = inp.readline()
        print("Iteration {0} got input of '{1}'".format(i, line))
        # m = simple_st_chan_3.match(line)
        # if m is not None:
        #     ch = channels[m.group("channel")]
        #     print("Requesting status channels 3 on '{0}'".format(ch))
        #     sc3_12_1(ch, out)
        #     out.flush()
        #     continue
        m = simple_st_net_writer.match(line.decode())
        if m is not None:
            i += 1
            start = int(m.group("start"))
            duration = int(m.group("duration"))
            channel = m.group("channel")
            out.write(b"0000")
            out.flush()
            writer_id(out, i, False)
            reconfigure_block(out, [channel,])
            for j in range(duration):
                data_header(out, [channel,], start + j, 1, j)
                write_data(out, channel, channels[channel].rate, j)
                out.flush()
            termination_block(out)
            out.flush()
            continue
        raise Exception("Unexpected command {0}".format(line))

def validate_action(action, args):
    if action == "register_chan" and len(args) == 9:
        return
    if action == "gen_sc3_12_1" and len(args) == 1:
        return
    if action == "gen_sc2_12_1" and len(args) >= 1:
        return
    if action == "writer-id" and len(args) == 2:
        return
    if action == "reconfigure-block" and len(args) == 1:
        return
    if action == "data-header" and len(args) == 4:
        return
    if action == "write-data" and len(args) == 3:
        return
    if action == "termination-block" and len(args) == 0:
        return
    if action == "handle_start_net_writer_full" and len(args) == 1:
        return


def execute_action(action, args, inp, out):
    global channels

    if action == "register_chan":
        chan = Channel(*args)
        channels[chan.name] = chan
    elif action == "gen_sc3_12_1":
        sc3_12_1(channels[args[0]], out)
    elif action == "gen_sc2_12_1":
        for name in args:
            sc2_12_1(channels[name], out)
    elif action == "writer-id":
        writer_id(out, *args)
    elif action == "reconfigure-block":
        reconfigure_block(out, *args)
    elif action == "data-header":
        data_header(out, *args)
    elif action == "write-data":
        write_data(out, *args)
    elif action == "termination-block":
        termination_block(out)
    elif action == "handle_start_net_writer_full":
        handle_start_net_writer_full(inp, out, *args)
    out.flush()