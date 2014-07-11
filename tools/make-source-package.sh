#!/bin/bash
# -------------------------------------------
# make-source-package.sh
#
# builds a source tarball
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

TARGET_NAME=pdg-`cat $PDG_ROOT/VERSION`
TARGET_SUBDIR=$TARGET_NAME
TARGET=$TARGET_NAME-src.tar
TARGET_DIR=$PDG_ROOT/build/package/$TARGET_DIR

mkdir -p $TARGET_DIR/deps/
cd $PDG_ROOT/build/package
rm -rf $TARGET.gz $TARGET.bz2

echo "Copying all files into the package..."
# put everything into the package
echo " * pdg/* -> $TARGET_DIR/"
rsync -d --delete --force --exclude-from=../../.gitignore ../../* $TARGET_DIR/
echo " * pdg/deps/chipmunk -> $TARGET_DIR/deps/chipmunk"
rsync -r --delete --force ../../deps/chipmunk $TARGET_DIR/deps/
echo " * pdg/deps/glfw -> $TARGET_DIR/deps/glfw"
rsync -r --delete --force ../../deps/glfw $TARGET_DIR/deps/
echo " * pdg/deps/png -> $TARGET_DIR/deps/png"
rsync -r --delete --force ../../deps/png $TARGET_DIR/deps/
echo " * pdg/deps/scml-pp -> $TARGET_DIR/deps/scml-pp"
rsync -r --delete --force ../../deps/png $TARGET_DIR/deps/
echo " * pdg/deps/node -> $TARGET_DIR/deps/node"
rsync -r --delete --force --delete-excluded \
	--exclude=.DS_Store \
	--exclude-from=../../tools/node-rsync-exclude.txt \
	../../deps/node $TARGET_DIR/deps/
echo " * pdg/deps/png -> $TARGET_DIR/deps/png"
rsync -r --delete --force ../../deps/png $TARGET_DIR/deps/
echo " * pdg/docs -> $TARGET_DIR/docs"
rsync -r --delete --force ../../docs $TARGET_DIR/
echo " * pdg/src -> $TARGET_DIR/src"
rsync -r --delete --force ../../src $TARGET_DIR/
echo " * pdg/test -> $TARGET_DIR/test"
rsync -r --delete --force ../../test $TARGET_DIR/
echo " * pdg/tools -> $TARGET_DIR/tools"
rsync -r --delete --force ../../tools $TARGET_DIR/

# pull out the stuff we don't actually want
rm -rf $TARGET_DIR/docs/html

echo "Building tar.gz and tar.bz2 files..."
tar -czf $TARGET.gz $TARGET_DIR/
tar -cyf $TARGET.bz2 $TARGET_DIR/
echo "Done:"
ls -lh $TARGET.*
echo "Shasums:"
shasum $TARGET.*

#rm -rf $TARGET_DIR/
