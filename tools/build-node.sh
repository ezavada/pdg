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
node_expected_version="$(awk '/^#define NODE_(MAJOR|MINOR|PATCH)_VERSION / {gsub(/\r/, "", $3); v = v sep $3; sep = "."} END {print "v" v}' "$node_version_header")"

# Git for Windows may check the Node submodule out with CRLF endings. Node's
# js2c generator records those bytes as the resource length, while a Linux C++
# compiler normalizes newlines inside the generated raw string literals. The
# resulting executable reads past every embedded script. Normalize only the
# JavaScript inputs when this checkout is being built by a POSIX toolchain.
node_javascript_probe="$node_source/lib/internal/per_context/primordials.js"
if [ -f "$node_javascript_probe" ] && LC_ALL=C grep -q $'\r$' "$node_javascript_probe"; then
    if ! command -v perl >/dev/null 2>&1; then
        echo "Perl is required to normalize Node.js sources checked out with CRLF endings" >&2
        exit 1
    fi
    echo "Normalizing Node.js embedded JavaScript sources to LF"
    find "$node_source/lib" "$node_source/deps" -type f \( -name '*.js' -o -name '*.mjs' \) \
        -exec perl -pi -e 's/\r$//' {} +
fi

# Node always writes thin archives through deps/node/out. Restore the
# architecture-specific link before validating or using a cached build.
node_out_link="$node_source/out"
mkdir -p "$node_output"
if [ -L "$node_out_link" ]; then
    if [ "$(readlink "$node_out_link")" != "$node_output" ]; then
        rm "$node_out_link"
        ln -s "$node_output" "$node_out_link"
    fi
elif [ -e "$node_out_link" ]; then
    echo "Node.js output path is not a symlink: $node_out_link" >&2
    echo "Rerun ./configure to preserve the old output and create the architecture-specific cache link." >&2
    exit 1
else
    ln -s "$node_output" "$node_out_link"
fi

node_artifacts_match=false
if [ -f "$node_release/libnode.a" ] && [ -f "$node_release/libnode_base.a" ] && [ -x "$node_release/node" ] &&
    cmp -s "$node_version_header" "$node_stamp" &&
    [ "$("$node_release/node" --version 2>/dev/null || true)" = "$node_expected_version" ]; then
    node_artifacts_match=true
fi

if [ "$node_artifacts_match" = true ] && "$node_release/node" -e 0 >/dev/null 2>&1; then
    echo "Node.js build is current: $("$node_release/node" --version)"
    exit 0
fi

# --version exits before Node initializes V8 or its embedded JavaScript. Clear a
# matching cache that cannot create a real environment so stale objects cannot
# survive the rebuild.
if [ "$node_artifacts_match" = true ]; then
    echo "Node.js cached runtime cannot initialize JavaScript; rebuilding from scratch"
    rm -rf "$node_output"
    mkdir -p "$node_output"
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
if ! "$node_release/node" -e 0 >/dev/null 2>&1; then
    echo "Node.js build cannot initialize a JavaScript environment" >&2
    exit 1
fi
cp "$node_version_header" "$node_stamp"
