#!/usr/bin/env bash

set -euo pipefail

usage() {
    echo "Usage: $0 [--tag vMAJOR.MINOR.PATCH] [--configure] [--output-dir PATH]"
    echo
    echo "Builds, tests, and packages the macOS PDG release asset locally."
}

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PDG_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
RELEASE_TAG=""
OUTPUT_DIR="$PDG_ROOT/artifacts/release"
FORCE_CONFIGURE=0

while [[ $# -gt 0 ]]; do
    case "$1" in
        --tag)
            RELEASE_TAG="${2:?--tag requires a value}"
            shift 2
            ;;
        --configure)
            FORCE_CONFIGURE=1
            shift
            ;;
        --output-dir)
            OUTPUT_DIR="${2:?--output-dir requires a value}"
            shift 2
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

if [[ "$(uname -s)" != "Darwin" ]]; then
    echo "This release script must run on macOS." >&2
    exit 1
fi

if [[ -z "$RELEASE_TAG" ]]; then
    RELEASE_TAG="$(git -C "$PDG_ROOT" describe --tags --exact-match HEAD 2>/dev/null || true)"
    if [[ -z "$RELEASE_TAG" ]]; then
        echo "HEAD is not tagged. Pass --tag vMAJOR.MINOR.PATCH when validating a prospective release locally." >&2
        exit 1
    fi
fi

cmake -DPDG_SOURCE_DIR="$PDG_ROOT" -DRELEASE_TAG="$RELEASE_TAG" \
    -P "$PDG_ROOT/cmake/ValidateReleaseVersion.cmake"

PDG_VERSION="$(tr -d '[:space:]' < "$PDG_ROOT/VERSION")"
BUILD_DIR="$PDG_ROOT/build/darwin/pdg"
DEBUG_BUILD_DIR="$PDG_ROOT/build/darwin/pdg-debug"

if [[ $FORCE_CONFIGURE -eq 1 || ! -f "$BUILD_DIR/CMakeCache.txt" ]]; then
    "$PDG_ROOT/configure"
fi

# Reapply release/public settings explicitly because later CMake refreshes
# retain the values from this cache.
cmake -S "$PDG_ROOT" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_TESTING=ON \
    -DCAN_BUILD_INTERFACES=OFF \
    -DCAN_BUILD_JSC_INTERFACES=OFF \
    -DPDG_HEADLESS=OFF

cmake --build "$PDG_ROOT/build/darwin/glfw" --config Release --parallel
cmake --build "$PDG_ROOT/build/darwin/chipmunk" --config Release --parallel
cmake --build "$BUILD_DIR" --config Release --target pdg --parallel

PDG_APP="$BUILD_DIR/src/pdg.app"
PDG_EXE="$PDG_APP/Contents/MacOS/pdg"
if [[ ! -x "$PDG_EXE" ]]; then
    echo "Expected release executable was not produced: $PDG_EXE" >&2
    exit 1
fi

ctest --test-dir "$BUILD_DIR" --build-config Release --output-on-failure
PDG_NODE="$PDG_ROOT/tools/node"
if [[ ! -x "$PDG_NODE" ]]; then
    PDG_NODE="$PDG_ROOT/deps/node/out/Release/node"
fi
PDG_NPM_CLI="$PDG_ROOT/deps/node/deps/npm/bin/npm-cli.js"
if [[ ! -x "$PDG_NODE" || ! -f "$PDG_NPM_CLI" ]]; then
    echo "The locally built Node.js and its npm CLI are required to prepare the JavaScript tests." >&2
    exit 1
fi
if [[ ! -f "$PDG_ROOT/node_modules/jasmine-node/package.json" ||
      ! -f "$PDG_ROOT/node_modules/node-gyp/package.json" ]]; then
    (
        cd "$PDG_ROOT"
        "$PDG_NODE" "$PDG_NPM_CLI" install --no-save --package-lock=false \
            jasmine-node@1.16.0 node-gyp@11.3.0
    )
fi
ln -sf "$PDG_NPM_CLI" "$PDG_ROOT/tools/npm"
ln -sf "$PDG_ROOT/node_modules/node-gyp/bin/node-gyp.js" "$PDG_ROOT/tools/node-gyp"
"$PDG_ROOT/tools/make-node-module.sh"
"$PDG_ROOT/test/node"
"$PDG_ROOT/test/client"

# Build a distinct unstripped Debug application with DEBUG logging enabled.
cmake -S "$PDG_ROOT" -B "$DEBUG_BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_TESTING=OFF \
    -DCAN_BUILD_INTERFACES=OFF \
    -DCAN_BUILD_JSC_INTERFACES=OFF \
    -DPDG_HEADLESS=OFF
cmake --build "$DEBUG_BUILD_DIR" --config Debug --target pdg --parallel

PDG_DEBUG_APP="$DEBUG_BUILD_DIR/src/pdg.app"
PDG_DEBUG_EXE="$PDG_DEBUG_APP/Contents/MacOS/pdg"
if [[ ! -x "$PDG_DEBUG_EXE" ]]; then
    echo "Expected debug executable was not produced: $PDG_DEBUG_EXE" >&2
    exit 1
fi

ARCH="$(uname -m)"
ASSET_BASENAME="pdg-v${PDG_VERSION}-macos-${ARCH}"
DEBUG_ASSET_BASENAME="pdg-debug-v${PDG_VERSION}-macos-${ARCH}"
STAGE_DIR="$OUTPUT_DIR/stage/$ASSET_BASENAME"
DEBUG_STAGE_DIR="$OUTPUT_DIR/stage/$DEBUG_ASSET_BASENAME"
ASSET_PATH="$OUTPUT_DIR/$ASSET_BASENAME.zip"
DEBUG_ASSET_PATH="$OUTPUT_DIR/$DEBUG_ASSET_BASENAME.zip"

cmake -E remove_directory "$STAGE_DIR"
cmake -E remove_directory "$DEBUG_STAGE_DIR"
cmake -E make_directory "$STAGE_DIR"
cmake -E make_directory "$DEBUG_STAGE_DIR"
ditto "$PDG_APP" "$STAGE_DIR/pdg.app"
ditto "$PDG_DEBUG_APP" "$DEBUG_STAGE_DIR/pdg-debug.app"
cmake -E rename \
    "$DEBUG_STAGE_DIR/pdg-debug.app/Contents/MacOS/pdg" \
    "$DEBUG_STAGE_DIR/pdg-debug.app/Contents/MacOS/pdg-debug"
/usr/libexec/PlistBuddy -c "Set :CFBundleExecutable pdg-debug" \
    "$DEBUG_STAGE_DIR/pdg-debug.app/Contents/Info.plist"
for package_dir in "$STAGE_DIR" "$DEBUG_STAGE_DIR"; do
    cmake -E copy "$PDG_ROOT/LICENSE" "$package_dir/LICENSE"
    cmake -E copy "$PDG_ROOT/README.md" "$package_dir/README.md"
    cmake -E copy "$PDG_ROOT/VERSION" "$package_dir/VERSION"
    notices_dir="$package_dir/THIRD_PARTY_LICENSES"
    cmake -E make_directory "$notices_dir"
    cmake -E copy "$PDG_ROOT/deps/chipmunk/LICENSE.txt" "$notices_dir/chipmunk.txt"
    cmake -E copy "$PDG_ROOT/deps/glfw/LICENSE.md" "$notices_dir/glfw.txt"
    cmake -E copy "$PDG_ROOT/deps/glm/copying.txt" "$notices_dir/glm.txt"
    cmake -E copy "$PDG_ROOT/deps/libjpeg-turbo/LICENSE.md" "$notices_dir/libjpeg-turbo.txt"
    cmake -E copy "$PDG_ROOT/deps/libjpeg-turbo/README.ijg" "$notices_dir/libjpeg-turbo-IJG.txt"
    cmake -E copy "$PDG_ROOT/deps/libtess2/LICENSE.txt" "$notices_dir/libtess2.txt"
    cmake -E copy "$PDG_ROOT/deps/minizip/LICENSE" "$notices_dir/minizip.txt"
    cmake -E copy "$PDG_ROOT/deps/node/LICENSE" "$notices_dir/node.txt"
    cmake -E copy "$PDG_ROOT/deps/png/LICENSE" "$notices_dir/libpng.txt"
    cmake -E copy "$PDG_ROOT/deps/SpriterPlusPlus/LICENSE" "$notices_dir/SpriterPlusPlus.txt"
    cmake -E copy "$PDG_ROOT/deps/SpriterPlusPlus/tinyxml2/license.txt" "$notices_dir/tinyxml2.txt"
done

if command -v dsymutil >/dev/null 2>&1; then
    dsymutil "$DEBUG_STAGE_DIR/pdg-debug.app/Contents/MacOS/pdg-debug" \
        -o "$DEBUG_STAGE_DIR/pdg-debug.app.dSYM"
fi

# Smoke-test both staged applications rather than their build-tree copies.
"$STAGE_DIR/pdg.app/Contents/MacOS/pdg" "$PDG_ROOT/test/misc/test_exit.js"
"$DEBUG_STAGE_DIR/pdg-debug.app/Contents/MacOS/pdg-debug" "$PDG_ROOT/test/misc/test_exit.js"

cmake -E make_directory "$OUTPUT_DIR"
cmake -E rm -f \
    "$ASSET_PATH" "$ASSET_PATH.sha256" \
    "$DEBUG_ASSET_PATH" "$DEBUG_ASSET_PATH.sha256"
ditto -c -k --sequesterRsrc "$STAGE_DIR" "$ASSET_PATH"
ditto -c -k --sequesterRsrc "$DEBUG_STAGE_DIR" "$DEBUG_ASSET_PATH"
(
    cd "$OUTPUT_DIR"
    shasum -a 256 "$(basename "$ASSET_PATH")" > "$(basename "$ASSET_PATH").sha256"
    shasum -a 256 "$(basename "$DEBUG_ASSET_PATH")" > "$(basename "$DEBUG_ASSET_PATH").sha256"
)

echo "Created $ASSET_PATH"
echo "Created $ASSET_PATH.sha256"
echo "Created $DEBUG_ASSET_PATH"
echo "Created $DEBUG_ASSET_PATH.sha256"
