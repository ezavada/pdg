#!/bin/bash
# -------------------------------------------
# gen-script-interface.sh
#
# Uses the C++ preprocessor and bcpp pretty printer
# to convert an script interface file into 
# C++ file that has all the script macros expanded.
# Having the macro expansion be part of the source
# code makes debugging through the bindings much easier.
#
# Written by Ed Zavada, 2012-2013
# Copyright (c) 2013, Dream Rock Studios, LLC
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

command_exists () {
    type "$1" &> /dev/null ;
}

if ! command_exists bcpp ; then
    echo "FATAL: bcpp not found! "
    echo "Please find it in tools/bccp.tar.gz, build and install it if you want to build script interface files"
    echo "If you got this error while just trying to build pdg from source, and weren't modifying the JavaScript \
interface files, use 'make fix-interface-timestamps; make' to proceed."
    exit 1
fi

if [ -z "$1" ]; then
    echo "USAGE: gen-script-interface.sh src_file [target_dir] [build_dir] [out_file_name]"
    exit 1
fi
PDG_SRC="$1"
PDG_REL_SRC=`echo $PDG_SRC | sed 's/\/Users\/[^\/]*\///'`
PDG_SRC_FILENAME=`basename $PDG_SRC`
if [ -z "$2" ]; then
	PDG_TARGET_DIR="src/bindings"
else
	PDG_TARGET_DIR="$2"
fi
PDG_REL_TARGET_DIR=`echo $PDG_TARGET_DIR | sed 's/\/Users\/[^\/]*\///'`
if [ -z "$3" ]; then
	PDG_BUILD_DIR="build"
else
	PDG_BUILD_DIR="$3"
fi
if [ -z "$4" ]; then
	PDG_OUT_FILENAME=$PDG_SRC_FILENAME
else
	PDG_OUT_FILENAME="$4"
fi
PDG_TARGET="$PDG_TARGET_DIR/$PDG_OUT_FILENAME"

echo "// -----------------------------------------------" > $PDG_TARGET
echo "// This file automatically generated from:" >> $PDG_TARGET
echo "//" >> $PDG_TARGET
echo "//    $PDG_REL_SRC" >> $PDG_TARGET
echo "//    $PDG_REL_TARGET_DIR/pdg_script_macros.h" >> $PDG_TARGET
echo "//" >> $PDG_TARGET
cat "$PDG_TARGET_DIR/LICENSE" >> $PDG_TARGET
echo "" >> $PDG_TARGET
echo "" >> $PDG_TARGET
gcc -DPDG_BUILDING_INTERFACE_FILES -I$PDG_TARGET_DIR $PDG_SRC -E -o $PDG_BUILD_DIR/tmp.1.txt
sed 'y/@/\n/' $PDG_BUILD_DIR/tmp.1.txt > $PDG_BUILD_DIR/tmp.2.txt
sed 's/%#/#/g' $PDG_BUILD_DIR/tmp.2.txt > $PDG_BUILD_DIR/tmp.3.txt
sed 's/# .*$//g' $PDG_BUILD_DIR/tmp.3.txt > $PDG_BUILD_DIR/tmp.4.txt
sed 's/__line__/__LINE__/g' $PDG_BUILD_DIR/tmp.4.txt > $PDG_BUILD_DIR/tmp.5.txt
bcpp $PDG_BUILD_DIR/tmp.5.txt 2>/dev/null >> $PDG_TARGET
#rm -f $PDG_BUILD_DIR/tmp.*.txt
