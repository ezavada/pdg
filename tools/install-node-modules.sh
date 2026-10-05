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

NODE_GYP_VERS=11.3.0
JASMINE_NODE_VER=1.16.0
NET_REPL_VERS=0.1.2
TOOL_WORKSPACE="$PDG_ROOT/build/$PDG_BUILD_SUBDIR/node-tools"
TOOL_MODULES="$TOOL_WORKSPACE/node_modules"

if [ -n "$PDG_NODE_PYTHON" ]; then
	PYTHON_BIN="$PDG_NODE_PYTHON"
elif [ -n "$PYTHON" ]; then
	PYTHON_BIN="$PYTHON"
elif command -v python3 >/dev/null 2>&1; then
	PYTHON_BIN="$(command -v python3)"
elif command -v python >/dev/null 2>&1; then
	PYTHON_BIN="$(command -v python)"
else
	PYTHON_BIN=""
fi

package_version() {
	local package_json="$1"
	if [ -f "$package_json" ]; then
		"$PDG_NODE" -p "require(process.argv[1]).version" "$package_json" 2>/dev/null | tr -d '\r\n'
	fi
}

if ! command -v "$PDG_NPM" >/dev/null 2>&1; then
	echo "FATAL: npm executable '$PDG_NPM' was not found" >&2
	exit 1
fi
if [ ! -x "$PDG_NODE" ]; then
	echo "FATAL: Node.js executable '$PDG_NODE' was not found" >&2
	exit 1
fi

if [ -n "$PYTHON_BIN" ]; then
	export PYTHON="$PYTHON_BIN"
	export npm_config_python="$PYTHON_BIN"
fi
export npm_config_loglevel=error

if [ "$(package_version "$TOOL_MODULES/node-gyp/package.json")" != "$NODE_GYP_VERS" ] ||
   [ "$(package_version "$TOOL_MODULES/jasmine-node/package.json")" != "$JASMINE_NODE_VER" ] ||
   [ "$(package_version "$TOOL_MODULES/net-repl/package.json")" != "$NET_REPL_VERS" ]; then
	echo -e "${HEAD}Installing Node.js build and test tools -> $TOOL_WORKSPACE...${RESET}"
	rm -rf "$TOOL_WORKSPACE"
	mkdir -p "$TOOL_WORKSPACE"
	cat > "$TOOL_WORKSPACE/package.json" <<'EOF'
{
  "name": "pdg-node-tools",
  "private": true
}
EOF
	(
		cd "$TOOL_WORKSPACE" || exit 1
		"$PDG_NPM" install --no-save --package-lock=false --no-audit --no-fund \
			node-gyp@$NODE_GYP_VERS jasmine-node@$JASMINE_NODE_VER net-repl@$NET_REPL_VERS
	) || exit 1
fi

mkdir -p "$PDG_ROOT/node_modules"
for package in node-gyp jasmine-node net-repl; do
	rm -rf "$PDG_ROOT/node_modules/$package"
	ln -s "$TOOL_MODULES/$package" "$PDG_ROOT/node_modules/$package"
done
ln -sfn "$PDG_ROOT/node_modules/node-gyp/bin/node-gyp.js" "$PDG_ROOT/tools/node-gyp"
ln -sfn "$PDG_ROOT/node_modules/jasmine-node/bin/jasmine-node" "$PDG_ROOT/tools/jasmine-node"
ln -sfn "$PDG_ROOT/node_modules/net-repl/bin/repl.js" "$PDG_ROOT/tools/repl"
echo "Done."
