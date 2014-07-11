#!/bin/bash
# -------------------------------------------
# copy-node-module-source.sh
#
# copies all the source for the pdg Node.js module into a target location
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

if [ -z "$1" ]; then
    echo "USAGE: copy-node-module-source.sh target_dir"
    exit 1
fi

TARGET_DIR=$1
mkdir -p $TARGET_DIR/deps/chipmunk/include
mkdir -p $TARGET_DIR/deps/glfw/include
mkdir -p $TARGET_DIR/deps/glfw/src
mkdir -p $TARGET_DIR/src
mkdir -p $TARGET_DIR/man

RSYNC="rsync -t"

echo "Collecting all the files for the module..."
# put everything into the package
echo " * src/bindings/common ==> $TARGET_DIR/src/bindings/common"
$RSYNC -r --delete --force src/bindings/common $TARGET_DIR/src/bindings/
echo " * src/bindings/javascript/v8 ==> $TARGET_DIR/src/bindings/javascript/v8"
$RSYNC -r --delete --force src/bindings/javascript/v8 $TARGET_DIR/src/bindings/javascript/
echo " * src/bindings/javascript/memblock.h ==> $TARGET_DIR/src/bindings/javascript/memblock.h"
$RSYNC src/bindings/javascript/memblock.h $TARGET_DIR/src/bindings/javascript/memblock.h
echo " * src/bindings/node ==> $TARGET_DIR/src/bindings/node"
$RSYNC -r --delete --force src/bindings/node $TARGET_DIR/src/bindings/
echo " * src/bindings/javascript/pdg.js ==> $TARGET_DIR/lib/pdg.js"
$RSYNC src/bindings/javascript/pdg.js $TARGET_DIR/lib/
echo " * src/js ==> $TARGET_DIR/src/js"
$RSYNC -r --delete --force src/js/* $TARGET_DIR/lib/
echo " * src/inc ==> $TARGET_DIR/src/inc"
$RSYNC -r --delete --force --exclude=inc/pdg/app src/inc $TARGET_DIR/src/
echo " * src/sys ==> $TARGET_DIR/src/sys"
$RSYNC -r --delete --force --exclude=*/gles/*** --exclude=*/ios/*** --exclude=*/ipad/*** src/sys $TARGET_DIR/src/
$RSYNC src/sys/macosx/platform-image-macosx.mm $TARGET_DIR/src/sys/macosx/platform-image-macosx-objc.cxx
echo " * tools/node-pdg/* ==> $TARGET_DIR/"
$RSYNC -d --delete --force tools/node-pdg/* $TARGET_DIR/
mv -f $TARGET_DIR/npm_ignore $TARGET_DIR/.npmignore
echo " * deps/chipmunk/include/chipmunk ==> $TARGET_DIR/deps/chipmunk/include"
$RSYNC -r --delete --force deps/chipmunk/include/chipmunk/* $TARGET_DIR/deps/chipmunk/include/
echo " * deps/chipmunk/src ==> $TARGET_DIR/deps/chipmunk/src"
$RSYNC -r --delete --force deps/chipmunk/src $TARGET_DIR/deps/chipmunk/
echo " * deps/chipmunk/LICENSE.txt ==> $TARGET_DIR/deps/chipmunk/LICENSE.txt"
$RSYNC deps/chipmunk/LICENSE.txt $TARGET_DIR/deps/chipmunk/
echo " * deps/glfw/include ==> $TARGET_DIR/deps/glfw/include"
$RSYNC -r --delete --force deps/glfw/include/* $TARGET_DIR/deps/glfw/include/
echo " * deps/glfw/src ==> $TARGET_DIR/deps/glfw/src"
$RSYNC -r --delete --force deps/glfw/src/* $TARGET_DIR/deps/glfw/src/
echo " * deps/glfw/COPYING.txt ==> $TARGET_DIR/deps/glfw/COPYING.txt"
$RSYNC deps/glfw/COPYING.txt $TARGET_DIR/deps/glfw/
echo " * deps/scml-pp ==> $TARGET_DIR/deps/scml-pp"
$RSYNC -r --delete --force deps/scml-pp $TARGET_DIR/deps/
echo " * deps/node/deps/zlib ==> $TARGET_DIR/deps/zlib"
$RSYNC -r --delete --force deps/node/deps/zlib $TARGET_DIR/deps/
echo " * deps/png ==> $TARGET_DIR/deps/png"
$RSYNC -r --delete --force deps/png $TARGET_DIR/deps/
echo " * docs/javascript/man/* ==> $TARGET_DIR/"
$RSYNC -r --delete --force docs/javascript/man/* $TARGET_DIR/man/
echo " * VERSION ==> $TARGET_DIR/"
$RSYNC VERSION $TARGET_DIR/
