#!/usr/bin/env bash

set -euo pipefail

usage() {
    echo "Usage: $0 [--tag vMAJOR.MINOR.PATCH] [--configure] [--output-dir PATH] [--skip-tests]"
    echo
    echo "Builds, tests, and packages the PDG Emscripten Release and Debug artifacts."
}

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PDG_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
RELEASE_TAG=""
OUTPUT_DIR="$PDG_ROOT/artifacts/release"
SKIP_TESTS=0

while [[ $# -gt 0 ]]; do
    case "$1" in
        --tag)
            RELEASE_TAG="${2:?--tag requires a value}"
            shift 2
            ;;
        --configure)
            # Accepted so tools/release.sh can forward its common arguments.
            shift
            ;;
        --output-dir)
            OUTPUT_DIR="${2:?--output-dir requires a value}"
            shift 2
            ;;
        --skip-tests)
            SKIP_TESTS=1
            shift
            ;;
        --help|-h)
            usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1" >&2
            usage >&2
            exit 2
            ;;
    esac
done

if [[ -z "$RELEASE_TAG" ]]; then
    RELEASE_TAG="$(git -C "$PDG_ROOT" describe --tags --exact-match HEAD 2>/dev/null || true)"
    if [[ -z "$RELEASE_TAG" ]]; then
        echo "HEAD is not tagged. Pass --tag vMAJOR.MINOR.PATCH when validating a prospective release locally." >&2
        exit 1
    fi
fi

for required_tool in cmake emmake python3; do
    if ! command -v "$required_tool" >/dev/null 2>&1; then
        echo "Required Emscripten release tool is unavailable: $required_tool" >&2
        exit 1
    fi
done

cmake -DPDG_SOURCE_DIR="$PDG_ROOT" -DRELEASE_TAG="$RELEASE_TAG" \
    -P "$PDG_ROOT/cmake/ValidateReleaseVersion.cmake"

PDG_VERSION="$(tr -d '[:space:]' < "$PDG_ROOT/VERSION")"
EMSCRIPTEN_PYTHON="${EMSDK_PYTHON:-$(command -v python3)}"
WASM_ARCH="${PDG_WASM_ARCH:-wasm32}"
WASM_TEST_OUTPUT_DIR="$PDG_ROOT/build/wasm/$WASM_ARCH"
WASM_RELEASE_OUTPUT_DIR="$WASM_TEST_OUTPUT_DIR/release"
WASM_DEBUG_OUTPUT_DIR="$WASM_TEST_OUTPUT_DIR/debug"
EMSCRIPTEN_CACHE="${EM_CACHE:-$WASM_TEST_OUTPUT_DIR/emscripten-cache}"
BUILD_JOBS="${PDG_BUILD_JOBS:-8}"

run_emscripten_make() {
    PDG_ROOT="$PDG_ROOT" WASM_ARCH="$WASM_ARCH" EMSDK_PYTHON="$EMSCRIPTEN_PYTHON" EM_CACHE="$EMSCRIPTEN_CACHE" \
        emmake make "--jobs=$BUILD_JOBS" -f "$PDG_ROOT/tools/pdg-js.mak" "$@"
}

if [[ $SKIP_TESTS -eq 0 ]]; then
    run_emscripten_make WASM_BUILD=test clean
    run_emscripten_make WASM_BUILD=test
    for required_output in libpdg.js libpdg.wasm libpdg.wasm.map; do
        if [[ ! -f "$WASM_TEST_OUTPUT_DIR/$required_output" ]]; then
            echo "Expected Emscripten test output was not produced: $WASM_TEST_OUTPUT_DIR/$required_output" >&2
            exit 1
        fi
    done

    TEST_PORT="$("$EMSCRIPTEN_PYTHON" -c 'import socket; s = socket.socket(); s.bind(("127.0.0.1", 0)); print(s.getsockname()[1]); s.close()')"
    PDG_TEST_PORT="$TEST_PORT" "$PDG_ROOT/test/unit" --web --no-build --automated
    PDG_TEST_PORT="$TEST_PORT" "$PDG_ROOT/test/ui" --web --no-build --automated
    PDG_TEST_PORT="$TEST_PORT" "$PDG_ROOT/test/demo" --web --no-build --automated
fi

run_emscripten_make WASM_BUILD=release clean
run_emscripten_make WASM_BUILD=release
run_emscripten_make WASM_BUILD=debug clean
run_emscripten_make WASM_BUILD=debug

for required_output in libpdg.js libpdg.wasm; do
    if [[ ! -f "$WASM_RELEASE_OUTPUT_DIR/$required_output" ]]; then
        echo "Expected Emscripten release output was not produced: $WASM_RELEASE_OUTPUT_DIR/$required_output" >&2
        exit 1
    fi
done

for required_output in libpdg.js libpdg.wasm libpdg.wasm.map; do
    if [[ ! -f "$WASM_DEBUG_OUTPUT_DIR/$required_output" ]]; then
        echo "Expected Emscripten debug output was not produced: $WASM_DEBUG_OUTPUT_DIR/$required_output" >&2
        exit 1
    fi
done

mkdir -p "$OUTPUT_DIR"
OUTPUT_DIR="$(cd "$OUTPUT_DIR" && pwd)"

package_runtime() {
    local RUNTIME_DIR="$1"
    local ASSET_BASENAME="$2"
    local STAGE_DIR="$OUTPUT_DIR/stage/$ASSET_BASENAME"
    local ASSET_PATH="$OUTPUT_DIR/$ASSET_BASENAME.zip"

    cmake -E remove_directory "$STAGE_DIR"
    cmake -E make_directory "$STAGE_DIR"
    local output
    for output in libpdg.js libpdg.wasm libpdg.data libpdg.wasm.map; do
        if [[ -f "$RUNTIME_DIR/$output" ]]; then
            cmake -E copy "$RUNTIME_DIR/$output" "$STAGE_DIR/$output"
        fi
    done
    cmake -E copy "$PDG_ROOT/LICENSE" "$STAGE_DIR/LICENSE"
    cmake -E copy "$PDG_ROOT/README.md" "$STAGE_DIR/README.md"
    cmake -E copy "$PDG_ROOT/VERSION" "$STAGE_DIR/VERSION"

    local NOTICES_DIR="$STAGE_DIR/THIRD_PARTY_LICENSES"
    cmake -E make_directory "$NOTICES_DIR"
    cmake -E copy "$PDG_ROOT/deps/chipmunk/LICENSE.txt" "$NOTICES_DIR/chipmunk.txt"
    cmake -E copy "$PDG_ROOT/deps/glm/copying.txt" "$NOTICES_DIR/glm.txt"
    cmake -E copy "$PDG_ROOT/deps/libjpeg-turbo/LICENSE.md" "$NOTICES_DIR/libjpeg-turbo.txt"
    cmake -E copy "$PDG_ROOT/deps/libjpeg-turbo/README.ijg" "$NOTICES_DIR/libjpeg-turbo-IJG.txt"
    cmake -E copy "$PDG_ROOT/deps/libtess2/LICENSE.txt" "$NOTICES_DIR/libtess2.txt"
    cmake -E copy "$PDG_ROOT/deps/minizip/LICENSE" "$NOTICES_DIR/minizip.txt"
    cmake -E copy "$PDG_ROOT/deps/node/LICENSE" "$NOTICES_DIR/node.txt"
    cmake -E copy "$PDG_ROOT/deps/png/LICENSE" "$NOTICES_DIR/libpng.txt"
    cmake -E copy "$PDG_ROOT/deps/SpriterPlusPlus/LICENSE" "$NOTICES_DIR/SpriterPlusPlus.txt"
    cmake -E copy "$PDG_ROOT/deps/SpriterPlusPlus/tinyxml2/license.txt" "$NOTICES_DIR/tinyxml2.txt"

    cmake -E make_directory "$OUTPUT_DIR"
    cmake -E rm -f "$ASSET_PATH" "$ASSET_PATH.sha256"
    (
        cd "$OUTPUT_DIR/stage"
        cmake -E tar cf "$ASSET_PATH" --format=zip "$ASSET_BASENAME"
    )
    (
        cd "$OUTPUT_DIR"
        cmake -E sha256sum "$(basename "$ASSET_PATH")" > "$(basename "$ASSET_PATH").sha256"
    )

    echo "Created $ASSET_PATH"
    echo "Created $ASSET_PATH.sha256"
}

package_runtime "$WASM_RELEASE_OUTPUT_DIR" "pdg-v${PDG_VERSION}-emscripten-${WASM_ARCH}"
package_runtime "$WASM_DEBUG_OUTPUT_DIR" "pdg-debug-v${PDG_VERSION}-emscripten-${WASM_ARCH}"
