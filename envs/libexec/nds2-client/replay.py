import binascii
import gzip
import hashlib

import json
import os
import os.path
import select
import re
import time


def isfloat(val):
    try:
        float(val)
    except ValueError:
        return False
    return True


class CloseButNoAbort(Exception):
    pass


class StorageBlob(object):
    blob_dir = "./blobs"
    hex_re = re.compile('^[a-fA-F0-9]+$')
    crc_re = re.compile('^.*_c[0-9]+$')

    def __init__(self, data=None, hash=None):
        if (data == None and hash == None) or (data != None and hash != None):
            raise Exception("StorageBlobs require either data or a hash")
        self.__data = ""
        self.__sum = ""
        h = hashlib.sha1()
        is_crc = False
        if data != None:
            self.__data = data
            h.update(self.__data)
            self.__sum = h.hexdigest()
        elif hash != None:
            # sanity check on the hash structure
            if self.crc_re.match(hash) != None:
                is_crc = True
            elif len(hash) != (h.digest_size * 2) or self.hex_re.match(hash) == None:
                raise Exception("Invalid hash passed")

            fname = os.path.join(self.blob_dir, hash)
            gzfname = fname + ".gz"

            # read the data
            # try raw data first
            if os.path.exists(fname):
                with open(fname, "rb") as f:
                    self.__data = f.read()
            elif os.path.exists(gzfname):
                # python2.6 cannot use GzipFile with the 'with' statement
                gz = gzip.GzipFile(gzfname, "rb")
                self.__data = gz.read()
                gz.close()
            else:
                if 'REPLAY_BLOB_REMOTE_CACHE' in os.environ:
                    conn = None
                    url = os.environ['REPLAY_BLOB_REMOTE_CACHE'] + "/" + hash + ".gz"
                    print("Searching for blob at %s" % url)
                    if os.path.exists(url):
                        # python2.6 cannot use GzipFile with the 'with' statement
                        gz = gzip.GzipFile(url, "rb")
                        self.__data = gz.read()
                        gz.close()
                    else:
                        raise Exception("Unable to find blob in cache")
                else:
                    raise Exception("Data blob %s was not found please update %s or set REPLAY_BLOB_REMOTE_CACHE" % (
                    hash, self.blob_dir))

            if not is_crc:
                h.update(self.__data)
                self.__sum = hash
                if h.hexdigest() != self.__sum:
                    raise Exception("Checksum incorrect for data")

    def save(self):
        if not os.path.exists(self.blob_dir):
            os.mkdir(self.blob_dir)
        fname = os.path.join(self.blob_dir, self.__sum + ".gz")
        print('saving blob to %s' % fname)
        if os.path.exists(fname):
            print('blob exists, skipping')
            return
        tmpname = fname + ".tmp"
        print('tmp name = %s' % tmpname)
        f = None
        try:
            f = gzip.GzipFile(tmpname, "wb")
            f.write(self.__data)
            os.rename(tmpname, fname)
            print('Replaced %s' % fname)
        finally:
            try:
                if f != None:
                    f.close()
            except:
                pass
            try:
                os.unlink(tmpname)
            except:
                pass

    def data(self):
        return self.__data

    def sum(self):
        return self.__sum


class Script(object):
    """A script object waits for a command (a given byte sequence, plain text) and response with a response (a given byte sequence, may be binary)"""
    min_blob = 4 * 1024

    def __read_remaining__(self, f):
        try:
            return f.read_remaining()
        except(AttributeError):
            pass
        data = ''
        while True:
            rlist = [f]
            avail = select.select(rlist, [], [], 0.0)
            ravail = avail[0]
            if len(ravail) == 0:
                return data
            ch = f.read(1)
            data = data + ch

    def __init__(self, cmd, response):
        self.cmd = cmd
        self.response = response

    def match(self, inp):
        received = ""
        for cur in self.cmd:
            ch = inp.read(1).decode('utf-8')
            # print("recieved => '{0}' + '{1}'".format(received, ch))
            received = received + ch
            if cur != ch:
                received = received + self.__read_remaining__(inp).decode('utf-8')
                # print("cur => '{0}' ch => '{1}'".format(cur, ch))
                # print("self.cmd => '{0}' {1} received => '{2}' {3}".format(self.cmd, type(self.cmd), received, type(received)))
                raise Exception("Unexpected command, wanted '%s', mismatch at '%s'" % (self.cmd, received))

    def __call__(self, inp, out):

        def wash(data):
            try:
                return data.decode('utf-8')
            except:
                pass
            return binascii.hexlify(data).decode('utf-8')


        self.match(inp)
        print("Received: '%s'" % self.cmd)
        # if cur == 'authorize':
        #	raise CloseButNoAbort()
        print("Sending({0}): '{1}'".format(len(self.response), wash(self.response[:15])))
        # print("{0} {1} {2}".format(type(inp), type(out), type(self.response)))
        # print("{0}".format(dir(out)))
        out.write(self.response)
        out.flush()

    def __must_be_binary(self, data):
        if len(data) > self.min_blob:
            return True
        for ch in data:
            o = ord(ch)
            if o == 0 or o > 127:
                return True
        return False

    def serialize(self):
        chunk = 162

        result = {"type": "script", "command": self.cmd}
        if not self.__must_be_binary(self.response):
            if len(self.response) <= chunk:
                result["response"] = self.response
            else:
                data = self.response
                responses = []
                while len(data) > 0:
                    responses.append(data[:chunk])
                    data = data[chunk:]
                result["responses"] = responses
        else:
            if len(self.response) <= chunk / 2:
                result["response_hex"] = binascii.hexlify(self.response)
            else:
                # large pieces of data or binary data
                blob = StorageBlob(data=self.response)
                blob.save()
                result["response_blob"] = blob.sum()
        return result


class CompoundScript(object):
    """A CompoundScript is a container object which executes a series of script like objects"""

    def __init__(self, scripts):
        self.scripts = scripts

    def __call__(self, inp, out):
        for cur in self.scripts:
            cur(inp, out)
        print("Compound script done")

    def serialize(self):
        scripts = []
        for script in self.scripts:
            scripts.append(script.serialize())
        return {"type": "compound", "scripts": scripts}

class CompoundMultiConnectScript(object):
    """A CompoundScript is a container object which executes a series of script like objects"""

    def __init__(self, scripts):
        self.scripts = scripts

    def call_with_server(self, inp, out, new_conn):
        first = True
        for cur in self.scripts:
            if not first:
                f = new_conn()
                inp = f
                out = f
            first = False
            cur(inp, out)
        print("Compound multi connect script done")

    def serialize(self):
        scripts = []
        for script in self.scripts:
            scripts.append(script.serialize())
        return {"type": "compound_multi", "scripts": scripts}


class NamedScript(object):
    """A Named script is a container that holds a single script object referenced by name from a external script container"""

    def __init__(self, name, container):
        self.name = name
        self.container = container

    def __call__(self, inp, out):
        return self.container[self.name](inp, out)

    def serialize(self):
        return {"type": "named", "name": self.name}


class NopScript(object):
    """Does nothing"""
    def __call__(self, inp, out):
        return

    def serialize(self):
        return{"type": "nop"}

class ExternalScript(object):
    """An ExternalScript object loads scripts from the specified external script into the local list of scripts.
    Locally defined scripts have precidence over external scripts"""

    def __init__(self, fname, global_scripts):
        self.fname = fname
        with open(fname, 'rt') as f:
            ext_scripts = load_scripts(f)
            for entry in ext_scripts:
                if entry in global_scripts:
                    continue
                global_scripts[entry] = ext_scripts[entry]

    def __call__(self, inp, out):
        pass

    def serialize(self):
        return {"type": "external", "file": self.fname}


class CommandScript(object):
    """A CommandScript takes no input and executes a programable command"""

    modules = {}

    @staticmethod
    def load_module(name):
        try:
            m = __import__(name)
            CommandScript.modules[name] = m
            print("Loaded " + name + " module")
        except ImportError:
            return

    @staticmethod
    def validate_action(action, args):
        if action == "sleep":
            if len(args) == 1 and isfloat(args[0]):
                return
        elif action == "import" and len(args) == 1:
            CommandScript.load_module(args[0])
            return
        else:
            for ext in CommandScript.modules:
                if action.startswith(ext + '.'):
                    CommandScript.modules[ext].validate_action(action[len(ext) + 1:], args)
                    return
        raise Exception("Unsupported command action and args {0} {1}".format(action, args))

    def __init__(self, action, args):
        CommandScript.validate_action(action, args)
        self.action = action
        self.args = args

    def __call__(self, inp, out):
        if self.action == "sleep":
            time.sleep(float(self.args[0]))
            return
        elif self.action == "import":
            # no-op, this happens in the validate stage
            return
        else:
            for ext in CommandScript.modules:
                if self.action.startswith(ext + '.'):
                    CommandScript.modules[ext].execute_action(self.action[len(ext) + 1:], self.args, inp, out)
                    return
        raise Exception("Unknown command action '" + self.action + "'")

    def serialize(self):
        return {"type": "command", "action": self.action, "args": self.args}


def save_scripts(scripts, f):
    data = {}
    for name in scripts:
        data[name] = scripts[name].serialize()

    json.dump(data, f, indent=4, ensure_ascii=True)


def __unserialize_script(data, container):
    def extract_response(data, required=True):
        if "response" in data:
            return data["response"].encode('utf-8')
        elif "responses" in data:
            response = ""
            for val in data["responses"]:
                response = response + val.encode('utf-8')
            return response
        elif "response_hex" in data:
            return binascii.unhexlify(data["response_hex"])
        elif "response_blob" in data:
            blob = StorageBlob(hash=data["response_blob"])
            return blob.data()
        if required:
            raise Exception("Invalid script serialization, missing required response field")
        return None

    if data["type"] == "script":
        return Script(data["command"], extract_response(data))
    elif data["type"] == "compound" or data["type"] == "compound_multi":
        scripts = []
        for script in data["scripts"]:
            scripts.append(__unserialize_script(script, container))
        if data["type"] == "compound":
            return CompoundScript(scripts)
        return CompoundMultiConnectScript(scripts)
    elif data["type"] == "named":
        return NamedScript(data["name"], container)
    elif data["type"] == "external":
        return ExternalScript(data["file"], container)
    elif data["type"] == "command":
        response = extract_response(data, required=False)
        args = data["args"]
        if response is not None:
            args.append(response)
        return CommandScript(data["action"], args)
    elif data["type"] == "nop" or data["type"] == "comment":
        return NopScript()
    else:
        raise Exception("Unknown script type %s" % data["type"])


def load_scripts(f):
    scripts = {}
    data = json.load(f)
    print(' dict(data) - %s ' % dict(data))
    for name in data:
        scripts[name] = __unserialize_script(data[name], scripts)
    return scripts
