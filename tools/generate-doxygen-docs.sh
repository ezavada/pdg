#!/bin/bash
# -------------------------------------------
# generate-doxygen-docs.sh
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

DOXYGEN=`which doxygen`
if [ -z "$DOXYGEN" ]; then
	DOXYGEN="/Applications/Doxygen.app/Contents/Resources/doxygen"
fi
$PDG_ROOT/tools/check-tool.sh bcpp "cd $PDG_ROOT/tools; open bcpp.tar.zip; ./configure; make; sudo make install"
$PDG_ROOT/tools/check-tool.sh doxygen "http://www.doxygen.org"

PDG_DOCS_DIR?="$PDG_ROOT/docs/javascript"
PDG_BUILD_DIR?="$PDG_ROOT/build"
PDG_TOOLS_DIR?="$PDG_ROOT/tools"
if [ -z "$1" ]; then
	BUILD_DOCS="yes"
else 
	BUILD_DOCS="no"
fi
if [ "--help" = "$1" ]; then
	echo "Usage: generate-doxygen-docs.sh
end
		

echo "#include \"js_docs_macros_doxygen.h\"" > $PDG_BUILD_DIR/tmp.h
cat $PDG_DOCS_DIR/pdg-js.i >> $PDG_BUILD_DIR/tmp.h 

# preprocess and then cleanup the interface file to turn it into C++ code that we can
# parse with Doxygen to generate our documentation
echo "/* This file automatically generated from docs/javascript/pdg-js.i */" > $PDG_DOCS_DIR/pdg-js.h
echo "" >> $PDG_DOCS_DIR/pdg-js.h
echo "" >> $PDG_DOCS_DIR/pdg-js.h
gcc -DPDG_GENERATING_DOCS -I$PDG_TOOLS_DIR $PDG_BUILD_DIR/tmp.h -E -o $PDG_BUILD_DIR/tmp-js.h
sed 'y/@/\n/' $PDG_BUILD_DIR/tmp-js.h > $PDG_BUILD_DIR/tmp2-js.h
sed 's/%#.*$//g' $PDG_BUILD_DIR/tmp2-js.h > $PDG_BUILD_DIR/tmp-js.h
sed 's/# .*$//g' $PDG_BUILD_DIR/tmp-js.h > $PDG_BUILD_DIR/tmp2-js.h
sed 's/\*\*\*"/\/** /g' $PDG_BUILD_DIR/tmp2-js.h > $PDG_BUILD_DIR/tmp-js.h
sed 's/"\*\*\*/ *\//g' $PDG_BUILD_DIR/tmp-js.h > $PDG_BUILD_DIR/tmp2-js.h
sed 's/\[string Binary]/BinaryString/g' $PDG_BUILD_DIR/tmp2-js.h > $PDG_BUILD_DIR/tmp-js.h
sed 's/\[\]/$/g' $PDG_BUILD_DIR/tmp-js.h > $PDG_BUILD_DIR/tmp2-js.h
sed 's/\[object //g' $PDG_BUILD_DIR/tmp2-js.h > $PDG_BUILD_DIR/tmp-js.h
sed 's/\[number //g' $PDG_BUILD_DIR/tmp-js.h > $PDG_BUILD_DIR/tmp2-js.h
sed 's/\[//g' $PDG_BUILD_DIR/tmp2-js.h > $PDG_BUILD_DIR/tmp-js.h
sed 's/\]//g' $PDG_BUILD_DIR/tmp-js.h > $PDG_BUILD_DIR/tmp2-js.h
sed 's/\$/[]/g' $PDG_BUILD_DIR/tmp2-js.h > $PDG_BUILD_DIR/tmp-js.h
sed 's/|}/|undefined}/g' $PDG_BUILD_DIR/tmp-js.h > $PDG_BUILD_DIR/tmp2-js.h
touch bcpp.cfg
bcpp $PDG_BUILD_DIR/tmp2-js.h >> $PDG_DOCS_DIR/pdg-js.h
rm -f bcpp.cfg $PDG_BUILD_DIR/tmp-js.h $PDG_BUILD_DIR/tmp2-js.h


rm -rf $PDG_DOCS_DIR/html

cd $PDG_DOCS_DIR; $DOXYGEN DoxyFile | grep -v "..."

# following can be used to regenerate the header, footer and stylesheets for modification
#cd $PDG_DOCS_DIR; $DOXYGEN -w html pdg_js_header.html pdg_js_footer.html pdg_js_stylesheet.css DoxyFile

rm -f html/*.dot

echo "Done."
