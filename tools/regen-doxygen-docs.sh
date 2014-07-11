#!/bin/bash
# -------------------------------------------
# regen-doxygen-docs.sh
#
# Regnerate the HTML from the Doxygen. Doesn't do any of the
# rebuilding of interface headers that generate-doxygen-docs.sh does. 
#
# Written by Ed Zavada, 2014
# Copyright (c) 2014, Dream Rock Studios, LLC
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

DOXYGEN=`which doxygen`
if [ -z "$DOXYGEN" ]; then
	DOXYGEN="/Applications/Doxygen.app/Contents/Resources/doxygen"
fi

$PDG_ROOT/tools/check-tool.sh doxygen "http://www.doxygen.org"

PDG_DOCS_DIR="$PDG_ROOT/docs/javascript"

if [ ! -z "$1" ]; then
	if [ "--help" = "$1" ]; then
		echo "Usage: regen-doxygen-docs.sh [sudo_user]"
		echo " - sudo_user is the user who has priviledges to run doxygen and modify files"
		exit 0
	fi
	DOXYGEN="sudo -u $1 $DOXYGEN"
fi


cd $PDG_DOCS_DIR

echo "Excuting: $DOXYGEN DoxyFile | grep"
$DOXYGEN DoxyFile | grep -v "..."

echo "Excuting: $DOXYGEN DoxyFile-man | grep"
$DOXYGEN DoxyFile-man | grep -v "..."

echo "Done."

