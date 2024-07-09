#! /usr/bin/env python
#------------------------------------------------------------------------
# This script is intended to run the test script
#
# ENVIRONMENT VARIABLES:
#  MATLAB           - Location of MATLAB executable
#  abs_top_builddir - Absolute location where the package was built
#  abs_srcdir       - Absolute location containing the script file
#  builddir         - Relative location where the package was built
#------------------------------------------------------------------------

import argparse
import os.path
import platform
import re
import subprocess
import sys

import unit_test

abs_top_builddir = os.environ.get( 'abs_top_builddir' )
abs_top_srcdir = os.environ.get( 'abs_top_srcdir' )
abs_srcdir = os.environ.get( 'abs_srcdir' )
abs_testerdir = os.environ.get( 'abs_testerdir' )
builddir = os.environ.get( 'builddir' )
prog_matlab = os.environ.get( 'MATLAB' )
prog_octave = os.environ.get( 'OCTAVE', 'octave' )
prog_java = os.environ.get( 'JAVA', 'java' )
prog_python = os.environ.get( 'PYTHON', sys.executable )

unit_tester = unit_test.unit_test( )

def find_target_path( lang, target ):
  global abs_top_builddir

  abs_top_builddir_native = os.path.normpath(abs_top_builddir)
  dirs = [ os.path.join( abs_top_builddir_native, lang, 'module', target ),
           os.path.join( abs_top_builddir_native,  lang, target ) ]

  for path in dirs:
    if ( os.path.exists( path ) ):
      return path
  return None

def set_globals( args ):
  global abs_top_builddir
  global abs_top_srcdir
  global abs_srcdir
  global abs_testerdir
  global builddir
  global prog_matlab

  if ( args.abs_top_builddir ):
    abs_top_builddir = args.abs_top_builddir
  if ( args.abs_top_srcdir ):
    abs_top_srcdir = args.abs_top_srcdir
  if ( args.abs_srcdir ):
    abs_srcdir = args.abs_srcdir
  if ( args.abs_testerdir ):
    abs_testerdir = args.abs_testerdir
  if ( args.builddir ):
    builddir = args.builddir

  if ( args.matlab ):
    prog_matlab = args.matlab

# Python program to compare two version number
# Method to compare two versions.
# Return 1 if v2 is smaller,
# -1 if v1 is smaller,,
# 0 if equal
def versionCompare(v1, v2):

    # This will split both the versions by '.'
    arr1 = v1.split(".")
    arr2 = v2.split(".")

    # Initializer for the version arrays
    i = 0

    # We have taken into consideration that both the
    # versions will contains equal number of delimiters
    while(i < len(arr1)):

        # Version 2 is greater than version 1
        if int(arr2[i]) > int(arr1[i]):
            return -1

        # Version 1 is greater than version 2
        if int(arr1[i]) > int(arr2[i]):
            return 1

        # We can't conclude till now
        i += 1

    # Both the versions are equal
    return 0

class Skip( Exception ):
  EXIT_CODE = 77

  def __init__( self, value ):
    self.value = value

  def __str__( self ):
    return str( self.value )

  def retcode( self ):
    return( Skip.EXIT_CODE )

class server( object ):
  def __init__( self ):
    self.proc = None

  @staticmethod
  def create( type, args ):
    if ( type == 'mock_nds1' ):
      return nds1_mock_server( )
    elif ( type == 'replay' ):
      return replay_server( args )
    elif ( type == 'null' ):
      return null_server( )
    return None

  def stop( self ):
    global unit_tester
    if( self.proc ):
      self.proc.wait( )
      unit_tester.msg_debug( 20, 'Server stdout: %s' % self.proc.stdout )
      unit_tester.msg_debug( 20, 'Server stderr: %s' % self.proc.stderr )
      return( self.proc.returncode )
    else:
      raise( Skip( 'Server was never started' ) )

class null_server( server ):
  def __init__( self ):
    global unit_tester
    global abs_testerdir

    sep = '/'
    super( self.__class__, self ).__init__( )
    if ( not abs_testerdir ):
      raise Skip( 'Unset variable  abs_testerdir' )
    if ( os.sep in abs_testerdir ):
      sep = os.sep
    self.script = sep.join( [ abs_testerdir, 'null_server.py' ] )
    if ( not os.path.exists( self.script ) ):
      raise Skip( 'Server (%s) does not exist' \
                    % self.script )

  def start( self, args ):
    global unit_tester
    global prog_python

    if ( not self.proc ):
      ## unit_tester.msg_info( 'Starting null_server subprocess: %s' % ( str( [ prog_python,
      ##                                                                    self.script ] + args ) ) )
      self.proc = subprocess.Popen( [ prog_python,
                                      self.script ] + args )
      ## unit_tester.msg_info( 'Server started' )



class nds1_mock_server( server ):
  def __init__( self ):
    global unit_tester
    global abs_testerdir

    sep = '/'
    super( self.__class__, self ).__init__( )
    if ( not abs_testerdir ):
      raise Skip( 'Unset variable  abs_testerdir' )
    if ( os.sep in abs_testerdir ):
      sep = os.sep
    self.script = sep.join( [ abs_testerdir, 'mockup_server.py' ] )
    ## unit_tester.msg_info( 'nds1_mock_server script: %s' % ( self.script ) )
    if ( not os.path.exists( self.script ) ):
      raise Skip( 'Server (%s) does not exist' \
                    % self.script )

  def start( self, args ):
    global unit_tester
    global prog_python

    if ( not self.proc ):
      ## unit_tester.msg_info( 'Starting nds1_mock_server subprocess: %s' % ( str( [ prog_python,
      ##                                                                    self.script ] + args ) ) )
      self.proc = subprocess.Popen( [ prog_python,
                                      self.script ] + args )
      ## unit_tester.msg_info( 'Server started' )

class replay_server( server ):
  DEFAULT_BLOB_REMOTE_CACHE = os.environ.get( 'REPLAY_BLOB_REMOTE_CACHE',
                                              'http://www.ligo-wa.caltech.edu/~jonathan.hanks/blobs' )
  DEFAULT_TEST_DIR = None
  DEFAULT_JSON_FILENAME = None
  DEFAULT_PROTOCOL = None

  def __init__( self, args ):
    global abs_testerdir

    super( self.__class__, self ).__init__( )
    self.proc = None
    self.blob_remote_cache = args.replay_blob_remote_cache
    self.test_dir = args.replay_test_dir
    self.json_filename = args.replay_json_filename
    self.protocol = args.replay_protocol
    if ( not self.test_dir ):
      self.test_dir = os.path.join( abs_testerdir )
    if ( self.json_filename ):
      self.json_filename = os.path.join( self.test_dir,
                                         'test-json',
                                         self.json_filename )
      #--------------------------------------------------------------------
      # Perform sanity checks
      #--------------------------------------------------------------------
      if ( not os.path.isdir( self.test_dir ) ):
        raise( Skip( 'Invalid test directory specified: %s' % self.test_dir ) )
      if ( not self.json_filename or not os.path.exists( self.json_filename ) ):
        raise( Skip( "Invalid json filename: %s" % str( self.json_filename ) ) )
      try:
        #------------------------------------------------------------
        # Leave as the last sanity check since it may take the longest
        #------------------------------------------------------------
        # if ( self.blob_remote_cache.startswith( '/' ) ):
        if ( not os.path.isdir( self.blob_remote_cache ) ):
          raise( Skip( "Unable to find cache directory - %s " %
                       ( self.blob_remote_cache ) ) )
          
      except Exception as Error:
        raise( Skip( 'Unable to connect to blob cache - %s' % ( str( Error ) ) ) )
    os.environ[ 'REPLAY_BLOB_REMOTE_CACHE' ] = self.blob_remote_cache
    #--------------------------------------------------------------------
    # Finish setup
    #--------------------------------------------------------------------
    self.script = os.path.join( self.test_dir, 'sock_test.py' )

  def start( self, args ):
    global prog_python

    module_paths = os.path.join(self.test_dir, 'modules', self.protocol)
    if ( not self.proc ):
      cmd = [ prog_python,
              self.script,
              '-i', self.json_filename,
              '-p', module_paths ] + args
      unit_tester.msg_info( 'cmd: %s' % ( cmd ) )
      self.proc = subprocess.Popen( cmd )

class executor( object ):
  def __init__( self, script ):
    self.script = script
    self.args = None
    self.jarfiles = None

  @staticmethod
  def create( script, args ):
    global unit_tester
    global prog_octave;

    retval = None
    (root, ext) = os.path.splitext( script )
    unit_tester.msg_debug( 10, 'root: %s ext: %s' % ( root, ext ) )
    if ( not ext or ext == '.exe' ):
      retval = exe( script )
    elif ( ext == '.m' ):
      if ( args.octave ):
        prog_octave = args.octave
        retval = octave( script )
      elif ( args.matlab ):
        retval = matlab( script )
    elif ( ext == '.class' ):
      retval = java( script )
    elif ( ext == '.py' ):
      retval = python( script )
      if ( not retval ):
        raise( Skip( 'Unable to run script with the extension: %s' % ( ext ) ) )
    if ( args.args ):
      retval.args = args.args
    if ( args.jarfiles ):
      retval.jarfiles = args.jarfiles
    try:
      retval.prefix = args.command_prefix
    except:
      retval.prefix = ''
    return retval

  def skip( self ):
    return( 77 )

class exe( executor ):
  def __init__( self, script ):
    super( self.__class__, self ).__init__( script )

  def eval( self ):
    global unit_tester
    global abs_top_builddir

    cmd = "%s " % ( self.prefix )
    cmd += "%s" % ( self.script )
    if ( self.args ):
      cmd += ' ' + ' '.join( self.args )
    cmd = cmd.strip( )

    unit_tester.msg_debug( 10, 'cmd: %s' % ( cmd ) )
    unit_tester.msg_info( 'cmd: %s' % ( cmd ) )
    try:
      output = subprocess.check_output( cmd,
                                        stderr=subprocess.STDOUT,
                                        shell = True )
      unit_tester.msg_debug( 20, output )
    except subprocess.CalledProcessError as Error:
      unit_tester.message( Error.output )
      return Error.returncode
    return 0

class matlab( executor ):
  def __init__( self, script ):
    super( self.__class__, self ).__init__( script )

  def eval( self ):
    global unit_tester
    global abs_top_builddir
    global abs_srcdir
    global prog_matlab

    argv = ''

    abs_top_builddir_native = os.path.normpath(abs_top_builddir)
    ndspath = os.path.join( abs_top_builddir_native, 'common', 'module' )
    ndscpath = os.path.join( abs_top_builddir_native, 'src', 'client' )
    if ( not prog_matlab or prog_matlab == 'PROG_MATLAB-NOTFOUND' ):
      return self.skip( )
    jarfile = java.find_nds2( )
    matlabpath = matlab.find_path( )
    usr_script = os.path.join( self.script )
    print( "executing matlab with args = %s" % str(self.args) )
    no_nodisplay = False
    if ( platform.system( ) == "Windows" ):
      no_nodisplay = True
    if ( self.args ):
      if '--no-nodisplay' in self.args:
        no_nodisplay = True
        self.args.remove('--no-nodisplay')
      # argv =  'setenv( \'ARGV\', \'' + ';'.join( self.args ) + '\');'
      argv =  'argv=regexp(\'' + ';'.join( self.args ) + '\',\';\',\'split\');'
    if ( self.jarfiles ):
      jf = '  javaaddpath(\'%s\');' % self.jarfiles
    else:
      jf = ''
    diary_filename = os.path.join( os.getcwd( ), 'results.txt' )
    mscript = ''.join( ['"',
                        'try;',
                        '  pwd;',
                        '  diary( \'%s\');' % ( diary_filename ) ,
                        '  javaaddpath(\'%s\');' % ( os.path.normpath( jarfile ) ),
                        jf,
                        '  addpath(\'%s\');' % matlabpath,
                        '  addpath(\'%s\');' % ndspath,
                        '  addpath(\'%s\');' % ndscpath,
                        argv,
                        '  run(\'%s\');' % (usr_script),
                        '  ret = 0;'
                        'catch ex;',
                        '  ret = 1;',
                        '  disp(ex.getReport());',
                        'end;',
                        'diary off;',
                        'exit(ret);',
                        '"' ] )
    #mscript = ''.join( ['"',
    #                    'exit(0);',
    #                    '"' ] )
    cmd = "%s " % ( self.prefix )
    prog_matlab_native = os.path.normpath(prog_matlab)
    if ( platform.system( ) == "Windows" ):
      cmd += "\"%s\" -automation -wait -r " % ( prog_matlab_native )
    else:
      if no_nodisplay:
        cmd += "\"%s\" -v -nodesktop -nosplash -r " % ( prog_matlab_native )
      else:
        cmd += "\"%s\" -v -nodisplay -r " % ( prog_matlab_native )
    cmd += mscript
    cmd = cmd.strip( )

    try:
      if ( os.path.isfile( diary_filename ) ):
        os.remove( diary_filename )
      output = subprocess.check_output( cmd,
                                        stderr=subprocess.STDOUT,
                                        shell = True )
      if ( os.path.isfile( diary_filename ) ):
        with open( diary_filename ) as results:
          output += results.read( )
      unit_tester.message( output )
    except subprocess.CalledProcessError as Error:
      output = Error.output
      with open( diary_filename ) as results:
        output += results.read( )
      unit_tester.message( output )
      return Error.returncode
    finally:
      # MATLAB leaves the terminal in an unusable state
      # The stty resets the terminal to a usable state
      if ( platform.system( ) != "Windows" ):
        subprocess.call(["stty", "sane"])
    return 0

  @staticmethod
  def find_path( ):
    path = find_target_path( lang = 'matlab',
                             target = '+ndsm' )
    if ( path ):
      return os.path.dirname( path )
    return( path )
      

class octave( executor ):
    def __init__( self, script ):
        super( self.__class__, self ).__init__( script )

    def eval( self ):
        global abs_top_builddir
        global abs_srcdir
        global builddir
        global prog_octave

        if ( not prog_octave ):
            return self.skip( )

        cmd = "%s " % ( self.prefix )
        cmd += "%s --no-init-file --no-site-file --no-window-system --silent" % ( prog_octave )
        # cmd += " --echo-commands"
        # cmd += " --verbose"
        cmd += " --path %s" % ( os.pathsep.join( [os.path.join( builddir, '..', 'module', '.libs' ),
                                                  os.path.join( builddir, '..', 'module' )] ) )
        cmd += " %s" % ( self.script )
        if ( self.args ):
          cmd += ' ' + ' '.join( self.args )
        cmd = cmd.strip( )
        try:
            output = subprocess.check_output( cmd,
                                              stderr=subprocess.STDOUT,
                                              shell = True )
            unit_tester.msg_debug( 0, output )
        except subprocess.CalledProcessError as Error:
            unit_tester.message( Error.output )
            return Error.returncode
        return 0

class java( executor ):
    def __init__( self, script ):
        super( self.__class__, self ).__init__( script )
        self.debug_flags = '-verbose:jni'

    def eval( self ):
        global abs_top_builddir
        global abs_srcdir
        global builddir
        global prog_java

        script =  ( os.path.basename( self.script ) )
        (script, ext) = os.path.splitext( script )
        jarfile = java.find_nds2( )
        jversion = java.get_version( )

        cmd = "%s " % ( self.prefix )
        cmd += "\"%s\" %s -enableassertions" % ( prog_java, self.debug_flags )
        cmd += " -cp .%s%s.jar%s%s" % ( os.pathsep, os.path.join(
            os.path.normpath( builddir ), script),
                                        os.pathsep, os.path.normpath(
            jarfile ) )
        cmd += " %s" % ( script )
        if ( self.args ):
          cmd += ' ' + ' '.join( self.args )
        cmd = cmd.strip( )
        try:
            output = subprocess.check_output( cmd,
                                              stderr=subprocess.STDOUT,
                                              shell = True )
            unit_tester.message( output )
        except subprocess.CalledProcessError as Error:
            unit_tester.message( Error.output )
            return Error.returncode
        return 0

    @staticmethod
    def get_version( ):
      global prog_java

      retval = subprocess.check_output([prog_java, "-version"], stderr=subprocess.STDOUT)
      retval = retval.splitlines()[ 0 ].decode("utf-8")
      retval = re.findall('"([^"]*)"', retval)[ 0 ]
      return retval

    @staticmethod
    def find_nds2( ):
      return( find_target_path( lang = 'java',
                                target = 'nds2.jar' ) )

class python( executor ):
    def __init__( self, script ):
        super( self.__class__, self ).__init__( script )

    def eval( self ):
        global abs_top_builddir
        global abs_srcdir
        global prog_python

        lang = 'python'

        dirs = [ os.path.join( abs_top_builddir, lang, 'module' ),
                 os.path.join( abs_top_builddir, lang, 'module', '.libs' ) ]

        if ( 'PYTHONPATH' in os.environ ):
            dirs.append( os.environ['PYTHONPATH'] )
        os.environ[ 'PYTHONPATH'] = os.pathsep.join(dirs)

        cmd = "%s " % ( self.prefix )
        cmd += "%s %s" % ( prog_python, self.script )
        if ( self.args ):
            cmd += ' ' + ' '.join( self.args )
        cmd = cmd.strip( )
        output = None
        try:
            output = subprocess.check_output( cmd,
                                              stderr=subprocess.STDOUT,
                                              shell = True )
            unit_tester.msg_debug( 20, output )
        except subprocess.CalledProcessError as Error:
            if output is not None:
                unit_test.msg_debug( 20, output )
            unit_tester.msg_debug( 20, Error.output )
            return Error.returncode
        return 0

def main( argv ):
  global prog_matlab
  global unit_tester

  unit_tester.msg_info( 'Started nds_tester: %s' % str( argv ) )
  #----------------------------------------------------------------------
  # Setup for the parsing of the command line
  #----------------------------------------------------------------------
  parser = argparse.ArgumentParser( description = 'Execute test script' )

  parser.add_argument( '--command-prefix',
                       help = 'String of command to prefix client execution',
                       action = 'store',
                       dest = 'command_prefix',
                       default = "" )
  parser.add_argument( '--nds1-mock-server',
                       help = 'Request NDS1 mock server',
                       action = 'store_const',
                       const='mock_nds1',
                       dest = 'server_type'  )
  parser.add_argument( '--null-server',
                       help = 'Request null server',
                       action = 'store_const',
                       const='null',
                       dest = 'server_type'  )
  parser.add_argument( '--replay-server',
                       help = 'Request replay server',
                       action = 'store_const',
                       const='replay',
                       dest = 'server_type'  )
  parser.add_argument( '--replay-blob-remote-cache',
                       help = 'Location of remote blob cache',
                       action = 'store',
                       default = replay_server.DEFAULT_BLOB_REMOTE_CACHE )
  parser.add_argument( '--replay-json-filename',
                       help = 'Json filename',
                       action = 'store',
                       default = replay_server.DEFAULT_JSON_FILENAME )
  parser.add_argument( '--replay-protocol',
                       help = 'Protocol version to mimic',
                       action = 'store',
                       default = replay_server.DEFAULT_PROTOCOL )
  parser.add_argument( '--replay-test-dir',
                       help = 'Location of replay test directory',
                       action = 'store',
                       default = replay_server.DEFAULT_TEST_DIR )
  parser.add_argument( '--abs-top-builddir',
                       help = 'Specify absolute path to the top build directory',
                       action = 'store',
                       default = None )
  parser.add_argument( '--abs-top-srcdir',
                       help = 'Specify absolute path to the top source directory',
                       action = 'store',
                       default = None )
  parser.add_argument( '--abs-srcdir',
                       help = 'Specify absolute path to the current source directory',
                       action = 'store',
                       default = None )
  parser.add_argument( '--abs-testerdir',
                       help = 'Specify absolute path to the tester directory',
                       action = 'store',
                       default = None )
  parser.add_argument( '--builddir',
                       help = 'Specify current build directory',
                       action = 'store',
                       default = '.' )
  parser.add_argument( '--matlab',
                       help = 'Specify location of matlab program',
                       action = 'store',
                       default = None )
  parser.add_argument( '--no-nodisplay',
                       help = 'Run matlab tests w/o the -nodisplay option',
                       action = 'store_true',
                       default = None)
  parser.add_argument( '--jarfiles',
                       help = 'Specify additional jar files needed to run command',
                       action = 'store',
                       default = None )
  parser.add_argument( '--octave',
                       help = 'Specify location of octave program',
                       action = 'store',
                       default = None )
  parser.add_argument( 'script',
                       help = 'Script to execute' )
  parser.add_argument( 'args',
                       nargs=argparse.REMAINDER,
                       help = 'Arguments to send to the script' )
  
  args = parser.parse_args( )
  set_globals( args )
  if args.no_nodisplay:
    if args.args is None:
      args = ['--no-nodisplay']
    else:
      args.args.append('--no-nodisplay')
  #------------------------------------------------------------------
  # Establish the type of server that is to be executed
  #------------------------------------------------------------------
  if ( args.server_type ):
    sargs = [ sys.executable, sys.argv[0] ]
    if ( args.matlab ):
      sargs += [ '--matlab=%s' % args.matlab ]
    if ( args.octave ):
      sargs += [ '--octave=%s' % args.octave ]
    if ( args.abs_top_builddir ):
      sargs += [ '--abs-top-builddir=%s' % args.abs_top_builddir ]
    if ( args.abs_top_srcdir ):
      sargs += [ '--abs-top-srcdir=%s' % args.abs_top_srcdir ]
    if ( args.abs_srcdir ):
      sargs += [ '--abs-srcdir=%s' % args.abs_srcdir ]
    if ( args.abs_testerdir ):
      sargs += [ '--abs-testerdir=%s' % args.abs_testerdir ]
    if ( args.builddir ):
      sargs += [ '--builddir=%s' % args.builddir ]
    if ( args.command_prefix ):
      sargs += [ '--command-prefix=%s' % args.command_prefix ]
    if ( args.jarfiles ):
      sargs += [ '--jarfiles=%s' % args.jarfiles ]
    sargs.append( args.script )
    sargs.extend( args.args )
    srvr = server.create( args.server_type, args )
    ## unit_tester.msg_info( 'Server Args: %s' % str( sargs ) )
    srvr.start( sargs )
    retval = srvr.stop( )
    unit_tester.check( retval == 0, 'Mock Server retval: %s' % ( str( retval ) ), retval )
  else:
    e = executor.create( args.script, args )
    retval = e.eval( )
    unit_tester.check( retval == 0, 'Mock Client retval: %s' % ( str( retval ) ), retval )

if( __name__ == '__main__' ):
  try:
    main( sys.argv[1:] )
  except Skip as Error:
    unit_tester.msg_skip( 'Skipping because: %s' % ( str( Error ) ),
                          Error.retcode( ) )
  except Exception as Error:
    unit_tester.msg_error( 'Failed because: %s' % str( Error ) )
  unit_tester.exit( )
