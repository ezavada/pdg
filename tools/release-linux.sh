#!/usr/bin/env bash

set -euo pipefail

usage() {
    echo "Usage: $0 [--tag vMAJOR.MINOR.PATCH] [--configure] [--output-dir PATH] [--skip-tests]"
    echo
    echo "Builds, tests, and packages a native Linux PDG release for the host architecture."
}

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PDG_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
RELEASE_TAG=""
OUTPUT_DIR="$PDG_ROOT/artifacts/release"
FORCE_CONFIGURE=0
SKIP_TESTS=0

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

if [[ "$(uname -s)" != "Linux" ]]; then
    echo "This release script must run on Linux." >&2
    exit 1
fi

cd "$PDG_ROOT"

case "$(uname -m)" in
    x86_64|amd64) ARCH="x86_64" ;;
    arm64|aarch64) ARCH="arm64" ;;
    *)
        echo "Unsupported Linux architecture: $(uname -m)" >&2
        exit 1
        ;;
esac

if [[ -z "$RELEASE_TAG" ]]; then
    RELEASE_TAG="$(git -C "$PDG_ROOT" describe --tags --exact-match HEAD 2>/dev/null || true)"
    if [[ -z "$RELEASE_TAG" ]]; then
        echo "HEAD is not tagged. Pass --tag vMAJOR.MINOR.PATCH when validating a prospective release locally." >&2
        exit 1
    fi
fi

for required_tool in cmake make python3; do
    if ! command -v "$required_tool" >/dev/null 2>&1; then
        echo "Required Linux release tool is unavailable: $required_tool" >&2
        exit 1
    fi
done
if [[ $SKIP_TESTS -eq 0 ]] && ! command -v xvfb-run >/dev/null 2>&1; then
    echo "xvfb-run is required for Linux GUI release tests." >&2
    exit 1
fi

cmake -DPDG_SOURCE_DIR="$PDG_ROOT" -DRELEASE_TAG="$RELEASE_TAG" \
    -P "$PDG_ROOT/cmake/ValidateReleaseVersion.cmake"

PDG_VERSION="$(tr -d '[:space:]' < "$PDG_ROOT/VERSION")"
PLATFORM_BUILD_DIR="$PDG_ROOT/build/linux/$ARCH"
NODE_OUT_DIR="$PLATFORM_BUILD_DIR/node/out"
BUILD_DIR="$PLATFORM_BUILD_DIR/pdg"
DEBUG_BUILD_DIR="$PLATFORM_BUILD_DIR/pdg-debug"

if [[ $FORCE_CONFIGURE -eq 1 || ! -f "$BUILD_DIR/CMakeCache.txt" || ! -f "$PDG_ROOT/Makefile" ]]; then
    "$PDG_ROOT/configure"
fi

# Build the architecture-scoped Node/V8 tree before the final CMake pass so
# CMake can discover every static archive emitted by Node's build.
make -C "$PDG_ROOT" node

cmake -S "$PDG_ROOT" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_TESTING=ON \
    -DCAN_BUILD_INTERFACES=OFF \
    -DCAN_BUILD_JSC_INTERFACES=OFF \
    -DPDG_NODE_OUT_DIR="$NODE_OUT_DIR" \
    -DPDG_HEADLESS=OFF

cmake --build "$PLATFORM_BUILD_DIR/glfw" --config Release --parallel
cmake --build "$PLATFORM_BUILD_DIR/chipmunk" --config Release --parallel
cmake --build "$BUILD_DIR" --config Release \
    --target pdg pdg-app-view-utils-tests pdg-app-framework-tests --parallel

PDG_EXE="$BUILD_DIR/src/pdg"
if [[ ! -x "$PDG_EXE" ]]; then
    echo "Expected release executable was not produced: $PDG_EXE" >&2
    exit 1
fi

ln -sfn "$PDG_EXE" "$PDG_ROOT/pdg"
ln -sfn "$PDG_EXE" "$PDG_ROOT/test/pdg"

if [[ $SKIP_TESTS -eq 0 ]]; then
    ctest --test-dir "$BUILD_DIR" --build-config Release --output-on-failure

    PDG_NODE="$NODE_OUT_DIR/Release/node"
    PDG_NPM_CLI="$PDG_ROOT/deps/node/deps/npm/bin/npm-cli.js"
    if [[ ! -x "$PDG_NODE" || ! -f "$PDG_NPM_CLI" ]]; then
        echo "The architecture-specific Node.js build and npm CLI are required for JavaScript tests." >&2
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
    ln -sfn "$PDG_NPM_CLI" "$PDG_ROOT/tools/npm"
    ln -sfn "$PDG_ROOT/node_modules/node-gyp/bin/node-gyp.js" "$PDG_ROOT/tools/node-gyp"
    ln -sfn "$PDG_NODE" "$PDG_ROOT/tools/node"
    "$PDG_ROOT/tools/make-node-module.sh"
    "$PDG_ROOT/test/node"
    xvfb-run -a "$PDG_ROOT/test/client"
fi

cmake -S "$PDG_ROOT" -B "$DEBUG_BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_TESTING=OFF \
    -DCAN_BUILD_INTERFACES=OFF \
    -DCAN_BUILD_JSC_INTERFACES=OFF \
    -DPDG_NODE_OUT_DIR="$NODE_OUT_DIR" \
    -DPDG_HEADLESS=OFF
cmake --build "$DEBUG_BUILD_DIR" --config Debug --target pdg --parallel

PDG_DEBUG_EXE="$DEBUG_BUILD_DIR/src/pdg-debug"
if [[ ! -x "$PDG_DEBUG_EXE" ]]; then
    echo "Expected debug executable was not produced: $PDG_DEBUG_EXE" >&2
    exit 1
fi

ASSET_BASENAME="pdg-v${PDG_VERSION}-linux-${ARCH}"
DEBUG_ASSET_BASENAME="pdg-debug-v${PDG_VERSION}-linux-${ARCH}"
STAGE_DIR="$OUTPUT_DIR/stage/$ASSET_BASENAME"
DEBUG_STAGE_DIR="$OUTPUT_DIR/stage/$DEBUG_ASSET_BASENAME"
ASSET_PATH="$OUTPUT_DIR/$ASSET_BASENAME.zip"
DEBUG_ASSET_PATH="$OUTPUT_DIR/$DEBUG_ASSET_BASENAME.zip"

cmake -E remove_directory "$STAGE_DIR"
cmake -E remove_directory "$DEBUG_STAGE_DIR"
cmake -E make_directory "$STAGE_DIR" "$DEBUG_STAGE_DIR"
cmake -E copy "$PDG_EXE" "$STAGE_DIR/pdg"
cmake -E copy "$PDG_DEBUG_EXE" "$DEBUG_STAGE_DIR/pdg-debug"

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

if [[ $SKIP_TESTS -eq 0 ]]; then
    xvfb-run -a "$STAGE_DIR/pdg" "$PDG_ROOT/test/misc/test_exit.js"
    xvfb-run -a "$DEBUG_STAGE_DIR/pdg-debug" "$PDG_ROOT/test/misc/test_exit.js"
fi

cmake -E make_directory "$OUTPUT_DIR"
cmake -E rm -f \
    "$ASSET_PATH" "$ASSET_PATH.sha256" \
    "$DEBUG_ASSET_PATH" "$DEBUG_ASSET_PATH.sha256"
(
    cd "$OUTPUT_DIR/stage"
    cmake -E tar cf "$ASSET_PATH" --format=zip "$ASSET_BASENAME"
    cmake -E tar cf "$DEBUG_ASSET_PATH" --format=zip "$DEBUG_ASSET_BASENAME"
)
(
    cd "$OUTPUT_DIR"
    cmake -E sha256sum "$(basename "$ASSET_PATH")" > "$(basename "$ASSET_PATH").sha256"
    cmake -E sha256sum "$(basename "$DEBUG_ASSET_PATH")" > "$(basename "$DEBUG_ASSET_PATH").sha256"
)

echo "Created $ASSET_PATH"
echo "Created $ASSET_PATH.sha256"
echo "Created $DEBUG_ASSET_PATH"
echo "Created $DEBUG_ASSET_PATH.sha256"
