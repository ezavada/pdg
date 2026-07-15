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

VERSION="$(tr -d '\r\n' < "$PDG_ROOT/VERSION")"
TARGET="$PDG_ROOT/build/node-pdg/pdg-$VERSION.tgz"
INSTALL_DIR="$PDG_ROOT/build/node-pdg-install"
CACHE_DIR="$PDG_ROOT/build/npm-cache"

if [ -n "$PYTHON" ]; then
	PYTHON_BIN="$PYTHON"
elif command -v python3 >/dev/null 2>&1; then
	PYTHON_BIN="$(command -v python3)"
elif command -v python >/dev/null 2>&1; then
	PYTHON_BIN="$(command -v python)"
else
	PYTHON_BIN=""
fi

initialize_install_workspace() {
	rm -rf "$INSTALL_DIR"
	mkdir -p "$INSTALL_DIR"
	cat > "$INSTALL_DIR/package.json" <<'EOF'
{
  "name": "pdg-node-install",
  "private": true
}
EOF
}

$PDG_ROOT/tools/copy-node-module-source.sh $PDG_ROOT/build/node-pdg

# npm puts out too many warnings that have nothing to do with us
LOGLEVEL=`$PDG_NPM config get loglevel`
$PDG_NPM config set loglevel error
export npm_config_nodedir="$PDG_ROOT/deps/node"
export npm_config_build_from_source=true
rm -rf "$CACHE_DIR"
mkdir -p "$CACHE_DIR"
export npm_config_cache="$CACHE_DIR"
if [ -n "$PYTHON_BIN" ]; then
	export PYTHON="$PYTHON_BIN"
	export npm_config_python="$PYTHON_BIN"
fi

echo -e "${HEAD}Packing the module${RESET}"
cd $PDG_ROOT/build/node-pdg
$PDG_NPM pack
cd $PDG_ROOT
rm -rf "$PDG_ROOT/node_modules/pdg"
echo "Done packing the module"

echo -e "${HEAD}Installing the pdg Node.js module (native build via node-gyp)${RESET}"
initialize_install_workspace
cd "$INSTALL_DIR"
$PDG_NPM --foreground-scripts install --no-save --package-lock=false "$TARGET" || exit 1
$PDG_NPM list pdg
cd "$PDG_ROOT"
mkdir -p "$PDG_ROOT/node_modules"
cp -a "$INSTALL_DIR/node_modules/pdg" "$PDG_ROOT/node_modules/" || exit 1
echo "Done installing the module"

# restore log level
$PDG_NPM config set loglevel $LOGLEVEL

echo -e "${HEAD}Testing the module${RESET}"
cd $PDG_ROOT/tools/node-pdg
make check-dylib
cd $PDG_ROOT/node_modules/pdg
$PDG_NPM test || exit 1
echo "Done testing the module"

echo ""
echo -e "${GOOD}Done with PDG Node.js Module${RESET}"
ls -lh $TARGET
echo "Shasums:"
shasum $TARGET
