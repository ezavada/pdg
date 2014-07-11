#!/bin/bash
# -------------------------------------------
# install-node-modules.sh
#
# Sets up a local npm (node package manager) and uses it to install the
# key node modules needed for testing and debugging node
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

NODE_VERS=0.10.28
NODE_GYP_VERS=0.13.0
NODE_INSPECTOR_VERS=0.7.3
NPM_VERS=1.4.10
JASMINE_NODE_VER=1.14.2
NET_REPL_VERS=0.1.2

OK=1
NEED_NPM=0
NEED_NODE_GYP=0
NEED_NODE_INSPECTOR=0
NEED_JASMINE_NODE=0
NEED_NET_REPL=0

if [ ! -d "$PDG_ROOT/node_modules" ]; then
	OK=0
fi
LINK=`type -t $PDG_NPM`
if [ "$LINK" != "file" ]; then
	if [ -e "$PDG_ROOT/node_modules/npm/bin/npm-cli.js" ]; then
		ln -sf $PDG_ROOT/node_modules/npm/bin/npm-cli.js $PDG_ROOT/tools/npm
	else
		echo "$PDG_NPM not found"
		OK=0
		NEED_NPM=1
	fi
fi
LINK=`type -t $PDG_NODE_GYP`
if [ "$LINK" != "file" ]; then
	if [ -e "$PDG_ROOT/node_modules/node-gyp/bin/node-gyp.js" ]; then
		ln -sf $PDG_ROOT/node_modules/node-gyp/bin/node-gyp.js $PDG_ROOT/tools/node-gyp
	else
		echo "$PDG_NODE_GYP not found"
		OK=0
		NEED_NODE_GYP=1
	fi
fi
LINK=`type -t $PDG_NODE_INSPECTOR`
if [ "$LINK" != "file" ]; then
	if [ -e "$PDG_ROOT/node_modules/node-inspector/bin/inspector.js" ]; then
		ln -sf $PDG_ROOT/node_modules/node-inspector/bin/inspector.js $PDG_ROOT/tools/node-inspector
	else
		echo "$PDG_NODE_INSPECTOR not found"
		OK=0
		NEED_NODE_INSPECTOR=1
	fi
fi
LINK=`type -t $PDG_JASMINE_NODE`
if [ "$LINK" != "file" ]; then
	if [ -e "$PDG_ROOT/node_modules/jasmine-node/bin/jasmine-node" ]; then
		ln -sf $PDG_ROOT/node_modules/jasmine-node/bin/jasmine-node $PDG_ROOT/tools/jasmine-node
	else
		echo "$PDG_JASMINE_NODE not found"
		OK=0
		NEED_JASMINE_NODE=1
	fi
fi
LINK=`type -t $PDG_REPL`
if [ "$LINK" != "file" ]; then
	if [ -e "$PDG_ROOT/node_modules/net-repl/bin/repl.js" ]; then
		ln -sf $PDG_ROOT/node_modules/net-repl/bin/repl.js $PDG_ROOT/tools/repl
	else
		echo "$PDG_REPL not found"
		OK=0
		NEED_NET_REPL=1
	fi
fi
if [ "$OK" == "1" ]; then
	echo "$PDG_ROOT/node_modules already installed"
	exit 0
fi
if [ "$NEED_NPM" == "1" ]; then
	echo "Installing Node Package Manager -> $PDG_ROOT/node_modules..."
	mkdir -p $PDG_ROOT/node_modules
	rm -rf $PDG_ROOT/node_modules/npm
	mkdir -p $PDG_ROOT/share/man
	mkdir -p $PDG_ROOT/bin
	mkdir -p $PDG_ROOT/lib/node
	export clean=yes
	$PDG_ROOT/deps/node/deps/npm/scripts/install.sh > /dev/null
	mv $PDG_ROOT/lib/node_modules/npm $PDG_ROOT/node_modules
	rm -rf share/ bin/ lib/
	ln -sf $PDG_ROOT/node_modules/npm/bin/npm-cli.js $PDG_ROOT/tools/npm
fi
if [ "$NEED_NODE_GYP" == "1" ]; then
	echo "Installing node-gyp $NODE_GYP_VERS -> $PDG_ROOT/node_modules..."
	$PDG_NPM install node-gyp@$NODE_GYP_VERS
	ln -sf $PDG_ROOT/node_modules/node-gyp/bin/node-gyp.js $PDG_ROOT/tools/node-gyp
fi
if [ "$NEED_JASMINE_NODE" == "1" ]; then
	echo "Installing jasmine-node $JASMINE_NODE_VER -> $PDG_ROOT/node_modules..."
	$PDG_NPM install jasmine-node@$JASMINE_NODE_VER
	ln -sf $PDG_ROOT/node_modules/jasmine-node/bin/jasmine-node $PDG_ROOT/tools/jasmine-node
fi
if [ "$NEED_NODE_INSPECTOR" == "1" ]; then
	echo "Installing node-inspector $NODE_INSPECTOR_VERS -> $PDG_ROOT/node_modules..."
	$PDG_NPM install node-inspector@$NODE_INSPECTOR_VERS
	ln -sf $PDG_ROOT/node_modules/node-inspector/bin/inspector.js $PDG_ROOT/tools/node-inspector
fi
if [ "$NEED_NET_REPL" == "1" ]; then
	echo "Installing net-repl $NET_REPL_VERS -> $PDG_ROOT/node_modules..."
	$PDG_NPM install net-repl@$NET_REPL_VERS
	ln -sf $PDG_ROOT/node_modules/net-repl/bin/repl.js $PDG_ROOT/tools/repl
fi
echo "Done."
