#!/bin/bash
# -------------------------------------------
# make-idl-javascript.sh
#
# Uses the C++ preprocessor and bcpp pretty printer
# to convert pdg_js_classes.h/.cpp into pdg_interfaces.h/.cpp
# files. Having the macro expansion be part of the source
# code makes debugging through the bindings much easier.
#
# Written by Ed Zavada, 2012
# Copyright (c) 2012, Dream Rock Studios, LLC
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to permit
# persons to whom the Software is furnished to do so, subject to the
# following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
# NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
# USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# -------------------------------------------

# load pdgrc
_SD=`pwd`;while [ "`pwd`" != '/' ];do { if [ -e ".pdgrc" ];then { source .pdgrc;break; } fi;cd ..; } done;cd $_SD
if [ -z "$PDG_ROOT" ]; then
	echo "FATAL: couldn't source .pdgrc in `pwd` or it's parent directories. Have you run configure yet?"
	exit 1
fi

PDG_BUILD_DIR="$PDG_ROOT/build"
PDG_TOOLS_DIR="$PDG_ROOT/tools"
if [ -z "$1" ]; then
	PDG_DOCS_DIR="$PDG_ROOT/docs/javascript"
else
	PDG_DOCS_DIR="$1"
fi

cd $PDG_TOOLS_DIR
$PDG_ROOT/pdg make-idl.js
cd ..
if [ -z "`diff $PDG_BUILD_DIR/pdg-js.out $PDG_DOCS_DIR/pdg-js.i`" ]; then
	echo "-- IDL was unchanged --"
else
	mv $PDG_BUILD_DIR/pdg-js.out $PDG_DOCS_DIR/pdg-js.i
	ls -l $PDG_DOCS_DIR/pdg-js.i

	$PDG_TOOLS_DIR/make-pdg-js-header.sh
fi
