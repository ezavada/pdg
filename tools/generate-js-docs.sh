#!/bin/bash
# -------------------------------------------
# generate-js-docs.sh
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

if [ -z "$1" ]; then
	PDG_JS_SRC_DIR="$PDG_ROOT/src/js"
	PDG_DOCS_DIR="$PDG_ROOT/docs"
	PDG_TOOLS_DIR="$PDG_ROOT/tools"
else
	PDG_JS_SRC_DIR="$1"
	PDG_DOCS_DIR="$PDG_JS_SRC_DIR/../docs"
	PDG_TOOLS_DIR="$PDG_JS_SRC_DIR/../tools"
fi
if [ -z "$2" ]; then
	PDG_BUILD_DIR="build"
else
	PDG_BUILD_DIR="$2"
fi

# following invocation of pdg runs tools/main.js, which inspects the pdg interface 
# directly. This requires that the pdg project is already successfully built

cd $PDG_TOOLS_DIR
$PDG_ROOT/pdg
cd ..
cp $PDG_TOOLS_DIR/tmp.out $PDG_DOCS_DIR/pdg-js.i
echo "#include \"js_docs_macros.h\"" > $PDG_BUILD_DIR/tmp.h
cat $PDG_DOCS_DIR/pdg-js.i >> $PDG_BUILD_DIR/tmp.h 

# preprocess and then cleanup the interface file to turn it into Javascript code that we can
# parse with a  to generate our documentation
echo "/* This file automatically generated from docs/pdg-js.i */" > $PDG_DOCS_DIR/pdg-js.js
echo "" >> $PDG_DOCS_DIR/pdg-js.js
echo "" >> $PDG_DOCS_DIR/pdg-js.js
gcc -DPDG_GENERATING_DOCS -I$PDG_TOOLS_DIR $PDG_BUILD_DIR/tmp.h -E -o $PDG_BUILD_DIR/tmp-js.js
sed 'y/@/\n/' $PDG_BUILD_DIR/tmp-js.js > $PDG_BUILD_DIR/tmp2-js.js
sed 's/%#.*$//g' $PDG_BUILD_DIR/tmp2-js.js > $PDG_BUILD_DIR/tmp-js.js
sed 's/# .*$//g' $PDG_BUILD_DIR/tmp-js.js > $PDG_BUILD_DIR/tmp2-js.js
sed 's/\*\*\*"/\/** /g' $PDG_BUILD_DIR/tmp2-js.js > $PDG_BUILD_DIR/tmp-js.js
sed 's/"\*\*\*/ *\//g' $PDG_BUILD_DIR/tmp-js.js > $PDG_BUILD_DIR/tmp2-js.js
# sed 's/\[string Binary]/BinaryString/g' $PDG_BUILD_DIR/tmp2-js.js > $PDG_BUILD_DIR/tmp-js.js
# sed 's/\[\]/$/g' $PDG_BUILD_DIR/tmp-js.js > $PDG_BUILD_DIR/tmp2-js.js
# sed 's/\[object //g' $PDG_BUILD_DIR/tmp2-js.js > $PDG_BUILD_DIR/tmp-js.js
# sed 's/\[number //g' $PDG_BUILD_DIR/tmp-js.js > $PDG_BUILD_DIR/tmp2-js.js
# sed 's/\[//g' $PDG_BUILD_DIR/tmp2-js.js > $PDG_BUILD_DIR/tmp-js.js
# sed 's/\]//g' $PDG_BUILD_DIR/tmp-js.js > $PDG_BUILD_DIR/tmp2-js.js
# sed 's/\$/[]/g' $PDG_BUILD_DIR/tmp2-js.js > $PDG_BUILD_DIR/tmp-js.js
# sed 's/|}/|undefined}/g' $PDG_BUILD_DIR/tmp-js.js > $PDG_BUILD_DIR/tmp2-js.js
touch bcpp.cfg
bcpp $PDG_BUILD_DIR/tmp2-js.js >> $PDG_DOCS_DIR/pdg-js.js
rm -f bcpp.cfg $PDG_BUILD_DIR/tmp-js.js $PDG_BUILD_DIR/tmp2-js.js
echo "Done."
