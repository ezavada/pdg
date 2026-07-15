#!/bin/bash
# -------------------------------------------
# rsync-source.sh
#
# rsyncs the source code to a target directory
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
	echo "Usage: $0 <target_dir>"
	exit 1
fi

TARGET_DIR=$1

mkdir -p $TARGET_DIR/deps/

echo "Copying all files into the target directory..."
# put everything into the package
echo " * pdg/* -> $TARGET_DIR/"
rsync -d --delete --force --exclude-from=$PDG_ROOT/.gitignore $PDG_ROOT/* $TARGET_DIR/
echo " * pdg/deps/chipmunk -> $TARGET_DIR/deps/chipmunk"
rsync -r --delete --force $PDG_ROOT/deps/chipmunk $TARGET_DIR/deps/
echo " * pdg/deps/glfw -> $TARGET_DIR/deps/glfw"
rsync -r --delete --force $PDG_ROOT/deps/glfw $TARGET_DIR/deps/
echo " * pdg/deps/png -> $TARGET_DIR/deps/png"
rsync -r --delete --force $PDG_ROOT/deps/png $TARGET_DIR/deps/
echo " * pdg/deps/scml-pp -> $TARGET_DIR/deps/scml-pp"
rsync -r --delete --force $PDG_ROOT/deps/scml-pp $TARGET_DIR/deps/
echo " * pdg/deps/minizip -> $TARGET_DIR/deps/minizip"
rsync -r --delete --force $PDG_ROOT/deps/minizip $TARGET_DIR/deps/
echo " * pdg/deps/libjpeg-turbo -> $TARGET_DIR/deps/libjpeg-turbo"
rsync -r --delete --force $PDG_ROOT/deps/libjpeg-turbo $TARGET_DIR/deps/

echo " * pdg/deps/node -> $TARGET_DIR/deps/node"
rsync -r --delete --force --delete-excluded \
	--exclude=.DS_Store \
	--exclude-from=$PDG_ROOT/tools/node-rsync-exclude.txt \
	$PDG_ROOT/deps/node $TARGET_DIR/deps/

echo " * pdg/docs -> $TARGET_DIR/docs"
rsync -r --delete --force $PDG_ROOT/docs $TARGET_DIR/
echo " * pdg/src -> $TARGET_DIR/src"
rsync -r --delete --force --delete-excluded \
	--exclude=.DS_Store \
	--exclude-from=$PDG_ROOT/tools/src-rsync-exclude.txt \
	$PDG_ROOT/src $TARGET_DIR/
echo " * pdg/test -> $TARGET_DIR/test"
rsync -r --delete --force $PDG_ROOT/test $TARGET_DIR/
echo " * pdg/tools -> $TARGET_DIR/tools"
rsync -r --delete --force $PDG_ROOT/tools $TARGET_DIR/

# pull out the stuff we don't actually want
rm -rf $TARGET_DIR/docs/html

echo "Done."
