#!/bin/bash
# -------------------------------------------
# make-node-module.sh
#
# builds a Node.js module for uploading with npm
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

# !!! use npm pack instead !!!

TARGET_NAME=node-pdg-`cat VERSION`
TARGET_DIR=$PDG_ROOT/build/package/$TARGET_NAME
TARGET=$TARGET_NAME-src.tar

rm -rf build/package/$TARGET.gz 
rm -rf build/package/$TARGET.bz2 
$PDG_ROOT/tools/copy-node-module-source.sh $TARGET_DIR

cd $PDG_ROOT/build/package/
echo "Building tar.gz and tar.bz2 files..."
tar -czf $TARGET.gz $TARGET_NAME/
tar -cyf $TARGET.bz2 $TARGET_NAME/
echo "Done:"
ls -lh $TARGET.*
echo "Shasums:"
shasum $TARGET.*
