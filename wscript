import Options, Utils
from subprocess import Popen
import os
from os import system
from os.path import exists, abspath

VERSION = '0.0.2'
APPNAME = 'nodegit'
srcdir = '.'
blddir = 'build'

def set_options(opt):
  opt.tool_options('gcc')
  opt.tool_options('compiler_cxx')

def configure(conf):
  import preproc
  preproc.go_absolute = True

  conf.check_tool('gcc')
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')

def build(bld):
  main = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  main.target = 'nodewii'
  main.source = 'src/base.cc src/connect.cc'
  main.cxxflags = ['-L./vendor/cwiid/libcwiid', '-lcwiid']
