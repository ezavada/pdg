#!/bin/bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PDG_ROOT="${PDG_ROOT:-$(cd "$SCRIPT_DIR/.." && pwd)}"
export PDG_ROOT

NODE_BIN="$PDG_ROOT/tools/node"
if [ ! -x "$NODE_BIN" ]; then
    NODE_BIN="$(command -v node || true)"
fi

if [ -z "$NODE_BIN" ]; then
    echo "Error: could not find a Node.js executable." >&2
    exit 1
fi

if [ -n "${NODE_PATH:-}" ]; then
    export NODE_PATH="$PDG_ROOT/node_modules:$NODE_PATH"
else
    export NODE_PATH="$PDG_ROOT/node_modules"
fi

exec "$NODE_BIN" "$@"
