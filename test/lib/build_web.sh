#!/usr/bin/env bash
# Build the selected WASM configuration without changing the user's current native configuration.
set -euo pipefail
PDG_TEST_ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
for PDG_TEST_TOOL in emmake make python3; do
    if ! command -v "$PDG_TEST_TOOL" >/dev/null 2>&1; then
        echo "Missing $PDG_TEST_TOOL. Activate Emscripten and install GNU make/Python; on Windows use a Bash build environment." >&2
        exit 2
    fi
done
PDG_WEB_CONFIG="${1:-test}"
case "$PDG_WEB_CONFIG" in test|debug|release) ;; *) echo "Expected test, debug or release" >&2; exit 2 ;; esac
export PDG_ROOT="$PDG_TEST_ROOT"
export WASM_ARCH=wasm32
export EMSDK_PYTHON="${EMSDK_PYTHON:-$(command -v python3)}"
export EM_CACHE="${EM_CACHE:-$PDG_TEST_ROOT/build/wasm/wasm32/emscripten-cache}"
cd "$PDG_TEST_ROOT"
exec emmake make "--jobs=${PDG_BUILD_JOBS:-8}" -f tools/pdg-js.mak WASM_BUILD="$PDG_WEB_CONFIG"
