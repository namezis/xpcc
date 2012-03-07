#!/usr/bin/env python
# 
# Copyright (c) 2009, Roboterclub Aachen e.V.
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the Roboterclub Aachen e.V. nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# $Id: hosted.py 653 2011-11-29 15:51:20Z dergraaf $

import os
import platform

from SCons.Script import *

# -----------------------------------------------------------------------------
def generate(env, **kw):
	if platform.system() == 'Windows':
		env.Append(ENV = {'PATH' : os.environ['PATH']})
		env.Tool('default')
		
		env.Append(CXXFLAGS = "/EHsc")
	else:
		env.Append(ENV = {'PATH' : os.environ['PATH']})
		env.Tool('gcc')
		env.Tool('g++')
		env.Tool('gnulink')
		env.Tool('ar')
		env.Tool('as')
	
		env['NM'] = "nm"
		env['SIZE'] = "du -s -h"
		
		# build messages
		if ARGUMENTS.get('verbose') != '1':
			env['CCCOMSTR'] = "Compiling C: $TARGET"
			env['CXXCOMSTR'] = "Compiling C++: $TARGET"
			env['ASCOMSTR'] = "Assembling: $TARGET"
			env['ASPPCOMSTR'] = "Assembling: $TARGET"
			env['LINKCOMSTR'] = "Linking: $TARGET"
			env['RANLIBCOMSTR'] = "Indexing: $TARGET"
			env['ARCOMSTR'] = "Create Library: $TARGET"
			
			env['SIZECOMSTR'] = "Size after:"
			env['SYMBOLSCOMSTR'] = "Show symbols for '$SOURCE':"
		
		# flags for C and C++
		env['CCFLAGS'] = [
			"-funsigned-char",
			"-funsigned-bitfields",
			"-Wall",
			"-Wextra",
			"-Wundef",
			"-ggdb",
			"-DBASENAME=${SOURCE.file}",
		]
		
		# C++ flags
		env['CXXFLAGS'] = [
			"-std=gnu++98",
	#		"-Weffc++",
			"-Woverloaded-virtual",
		]

def exists(env):
	return env.Detect('g++')
