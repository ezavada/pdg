#!/bin/bash

set -euo pipefail

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 /mnt/c/path/to/pdg-devel"
    exit 1
fi

REPO_ROOT="$(cd "$1" && pwd)"
source "$REPO_ROOT/tools/submodules.sh"
if ! ensure_repo_submodule "$REPO_ROOT" "deps/node" "deps/node/src/node_version.h" "Node.js source checkout"; then
    exit 1
fi
NODE_SRC="$REPO_ROOT/deps/node"
BUILD_ROOT="${HOME}/.pdg-node-build-cache"
LOG_DIR="${TMPDIR:-/tmp}/pdg-node-build"
CONFIG_LOG="$LOG_DIR/configure.log"
BUILD_LOG="$LOG_DIR/build.log"

if command -v nproc >/dev/null 2>&1; then
    BUILD_JOBS="${PDG_NODE_BUILD_JOBS:-$(nproc)}"
else
    BUILD_JOBS="${PDG_NODE_BUILD_JOBS:-8}"
fi

NODE_CONFIGURE_ARGS=(--enable-static)
if [ "$(uname -s)" = "Linux" ]; then
    NODE_CONFIGURE_ARGS+=(--without-node-snapshot)
fi

mkdir -p "$BUILD_ROOT" "$LOG_DIR"

if command -v rsync >/dev/null 2>&1; then
    rsync -a --delete --exclude out/ "$NODE_SRC/" "$BUILD_ROOT/"
else
    rm -rf "$BUILD_ROOT"
    mkdir -p "$BUILD_ROOT"
    cp -a "$NODE_SRC/." "$BUILD_ROOT/"
    rm -rf "$BUILD_ROOT/out"
fi

cd "$BUILD_ROOT"
./configure "${NODE_CONFIGURE_ARGS[@]}" >"$CONFIG_LOG" 2>&1
make --jobs="$BUILD_JOBS" V="" >"$BUILD_LOG" 2>&1
find "$BUILD_ROOT/out/Release/obj.target" -name '*.a' -exec cp -f {} "$BUILD_ROOT/out/Release/" \;

mkdir -p "$NODE_SRC/out/Release"
cp -a "$BUILD_ROOT/out/Release/." "$NODE_SRC/out/Release/"

echo "Copied Node build artifacts back to $NODE_SRC/out/Release"
ls -lh "$NODE_SRC/out/Release/libnode.a"
echo "Configure log: $CONFIG_LOG"
echo "Build log: $BUILD_LOG"
