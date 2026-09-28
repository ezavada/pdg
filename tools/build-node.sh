#!/usr/bin/env bash
# Build the pinned Node runtime and static libraries together. A version stamp
# prevents a submodule upgrade from silently reusing an older cached runtime.
set -euo pipefail
node_repo_root="$1"
node_output="$2"
node_python="$3"
node_jobs="$4"
shift 4
node_source="$node_repo_root/deps/node"
node_release="$node_output/Release"
node_version_header="$node_source/src/node_version.h"
node_stamp="$node_release/.pdg-node-version.h"
node_expected_version="$(awk '/^#define NODE_(MAJOR|MINOR|PATCH)_VERSION / {v = v sep $3; sep = "."} END {print "v" v}' "$node_version_header")"

if [ -f "$node_release/libnode.a" ] && [ -f "$node_release/libnode_base.a" ] && [ -x "$node_release/node" ] &&
    cmp -s "$node_version_header" "$node_stamp" &&
    [ "$("$node_release/node" --version 2>/dev/null || true)" = "$node_expected_version" ]; then
    echo "Node.js build is current: $("$node_release/node" --version)"
    exit 0
fi

# A failed rebuild must not leave a successful cache marker behind.
rm -f "$node_stamp"
cd "$node_source"
"$node_python" ./configure "$@"
make "--jobs=$node_jobs" V=""
find "$node_release/obj.target" -name '*.a' -exec cp -f {} "$node_release/" \;
test -s "$node_release/libnode.a"
test -s "$node_release/libnode_base.a"
test -x "$node_release/node"
if [ "$("$node_release/node" --version)" != "$node_expected_version" ]; then
    echo "Node.js build does not match source version $node_expected_version" >&2
    exit 1
fi
cp "$node_version_header" "$node_stamp"
