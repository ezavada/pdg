#!/bin/sh
# Xcode build phase: SDK/architecture/configuration-specific static backend.
set -eu
PDG_TASK_ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
PDG_WT_CMAKE=${PDG_WT_CMAKE:-$(command -v cmake || true)}
if [ -z "$PDG_WT_CMAKE" ]; then
    for PDG_WT_CANDIDATE in /opt/homebrew/bin/cmake /usr/local/bin/cmake; do
        if [ -x "$PDG_WT_CANDIDATE" ]; then PDG_WT_CMAKE=$PDG_WT_CANDIDATE; break; fi
    done
fi
if [ -z "$PDG_WT_CMAKE" ]; then echo 'error: Native WebTransport requires CMake 3.18 or newer'; exit 1; fi
for PDG_WT_ARCH in $ARCHS; do
    PDG_WT_BUILD="$PDG_TASK_ROOT/build/webtransport/ios-$PLATFORM_NAME-$PDG_WT_ARCH-$CONFIGURATION"
    set -- -S "$PDG_TASK_ROOT/src/sys/webtransport" -B "$PDG_WT_BUILD" \
        -DCMAKE_SYSTEM_NAME=iOS "-DCMAKE_OSX_SYSROOT=$SDKROOT" \
        "-DCMAKE_OSX_ARCHITECTURES=$PDG_WT_ARCH" "-DCMAKE_OSX_DEPLOYMENT_TARGET=$IPHONEOS_DEPLOYMENT_TARGET" \
        "-DCMAKE_BUILD_TYPE=$CONFIGURATION" -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY
    # Optional pre-fetched source cache for offline builds; never share SDK object files.
    if [ -n "${PDG_WEBTRANSPORT_SOURCES:-}" ]; then
        for PDG_WT_DEP in picoquic picotls mbedtls cjson; do
            PDG_WT_UPPER=$(printf '%s' "$PDG_WT_DEP" | tr '[:lower:]' '[:upper:]')
            set -- "$@" "-DFETCHCONTENT_SOURCE_DIR_$PDG_WT_UPPER=$PDG_WEBTRANSPORT_SOURCES/$PDG_WT_DEP"
        done
    fi
    "$PDG_WT_CMAKE" "$@"
    "$PDG_WT_CMAKE" --build "$PDG_WT_BUILD" --target pdg_webtransport_bundle --parallel 8
done
mkdir -p "$BUILT_PRODUCTS_DIR/webtransport"
# Paths are passed individually so project locations containing spaces remain valid.
set --
for PDG_WT_ARCH in $ARCHS; do
    set -- "$@" "$PDG_TASK_ROOT/build/webtransport/ios-$PLATFORM_NAME-$PDG_WT_ARCH-$CONFIGURATION/libpdg_webtransport_all.a"
done
/usr/bin/lipo -create "$@" -output "$BUILT_PRODUCTS_DIR/webtransport/libpdg_webtransport_all.a"
/usr/bin/ditto "$PDG_TASK_ROOT/src/sys/webtransport/THIRD_PARTY_NOTICES.txt" "$BUILT_PRODUCTS_DIR/webtransport/THIRD_PARTY_NOTICES.txt"
