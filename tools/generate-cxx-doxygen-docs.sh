#!/bin/bash
# -------------------------------------------
# generate-cxx-doxygen-docs.sh
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

DOXYGEN="/Applications/Doxygen.app/Contents/Resources/doxygen"

source .pdgrc
if [ -z "$1" ]; then
	PDG_DOCS_DIR="docs/cxx"
else
	PDG_DOCS_DIR="$1"
fi
if [ -z "$2" ]; then
	PDG_BUILD_DIR="build"
	PDG_TOOLS_DIR="tools"
else
	PDG_BUILD_DIR="$2/build"
	PDG_TOOLS_DIR="$2/tools"
fi

rm -rf $PDG_DOCS_DIR/html

cd $PDG_DOCS_DIR; $DOXYGEN DoxyFile

# following can be used to regenerate the header, footer and stylesheets for modification
#cd $PDG_DOCS_DIR; $DOXYGEN -w html pdg_js_header.html pdg_js_footer.html pdg_js_stylesheet.css DoxyFile

rm -f html/*.dot

echo "Done."
