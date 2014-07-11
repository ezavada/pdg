#!/bin/bash
# -------------------------------------------
# version-update.sh
#
# update version number
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

OLD_VERS=`cat $PDG_ROOT/VERSION`
OLD_VERS_REGEX=`cat $PDG_ROOT/VERSION | sed 's/\./\\\./g'`
NEW_VERS=$1
if [ -z "$1" ]; then
	echo "Usage: version-update.sh major.minor.bugfix"
	exit 0
fi
echo "Changing $OLD_VERS to $NEW_VERS... (regex: $OLD_VERS_REGEX)"

# tools/node-pdg/package.json
sed s/$OLD_VERS_REGEX/$NEW_VERS/g $PDG_ROOT/tools/node-pdg/package.json > $PDG_ROOT/build/tmp
mv -f $PDG_ROOT/build/tmp $PDG_ROOT/tools/node-pdg/package.json
grep --with-filename --line-number $NEW_VERS $PDG_ROOT/tools/node-pdg/package.json

# src/inc/pdg/version.h
sed s/$OLD_VERS_REGEX/$NEW_VERS/g $PDG_ROOT/src/inc/pdg/version.h > $PDG_ROOT/build/tmp
mv -f $PDG_ROOT/build/tmp $PDG_ROOT/src/inc/pdg/version.h
grep --with-filename --line-number $NEW_VERS $PDG_ROOT/src/inc/pdg/version.h

# docs/cxx/Doxyfile
sed s/$OLD_VERS_REGEX/$NEW_VERS/g $PDG_ROOT/docs/cxx/Doxyfile > $PDG_ROOT/build/tmp
mv -f $PDG_ROOT/build/tmp $PDG_ROOT/docs/cxx/Doxyfile
grep --with-filename --line-number $NEW_VERS $PDG_ROOT/docs/cxx/Doxyfile

# docs/javascript/Doxyfile
sed s/$OLD_VERS_REGEX/$NEW_VERS/g $PDG_ROOT/docs/javascript/Doxyfile > $PDG_ROOT/build/tmp
mv -f $PDG_ROOT/build/tmp $PDG_ROOT/docs/javascript/Doxyfile
grep --with-filename --line-number $NEW_VERS $PDG_ROOT/docs/javascript/Doxyfile

# docs/javascript/Doxyfile-man
sed s/$OLD_VERS_REGEX/$NEW_VERS/g $PDG_ROOT/docs/javascript/Doxyfile-man > $PDG_ROOT/build/tmp
mv -f $PDG_ROOT/build/tmp $PDG_ROOT/docs/javascript/Doxyfile-man
grep --with-filename --line-number $NEW_VERS $PDG_ROOT/docs/javascript/Doxyfile-man

# VERSION
sed s/$OLD_VERS_REGEX/$NEW_VERS/g $PDG_ROOT/VERSION > $PDG_ROOT/build/tmp
mv -f $PDG_ROOT/build/tmp $PDG_ROOT/VERSION
grep --with-filename --line-number $NEW_VERS $PDG_ROOT/VERSION

rm -rf $PDG_ROOT/build/tmp
