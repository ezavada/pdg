#!/usr/bin/env bash
set -euo pipefail
mkdir -p /work/source /results
# Isolate Linux's generated build/dependency files from the macOS checkout.
rsync -a --delete --exclude=.git --exclude=build --exclude=node_modules \
    --exclude=artifacts --exclude=docs --exclude=ios --exclude=test/sprinter-private \
    --exclude=deps/node/out --exclude=deps/node/test --exclude=deps/node/tools \
    --exclude=deps/SpriterPlusPlus/build --exclude=.codex --exclude=.agents \
    /input/ /work/source/
cd /work/source
arch=$(uname -m)
case "$arch" in aarch64) arch=arm64;; x86_64) ;; *) exit 2;; esac
cmake -S deps/chipmunk -B "build/linux/$arch/chipmunk" \
    -DBUILD_DEMOS=OFF -DINSTALL_DEMOS=OFF -DBUILD_SHARED=OFF -DBUILD_STATIC=ON
cmake --build "build/linux/$arch/chipmunk" -j "${PDG_JOBS:-6}"
for solver in chipmunk basic; do
    enabled=ON
    targets=(pdg-physics-owners-tests pdg-physicsbody-tests pdg-animation-pose-tests)
    if [ "$solver" = chipmunk ]; then targets+=(pdg-spriter-playback-tests); else enabled=OFF; fi
    cmake -S . -B "/work/$solver" -G Ninja -DPDG_HEADLESS=ON \
        -DUSE_CHIPMUNK="$enabled" -DUSE_SPRITER="$enabled" -DBUILD_TESTING=ON \
        -DCAN_BUILD_INTERFACES=OFF -DCAN_BUILD_JSC_INTERFACES=OFF
    cmake --build "/work/$solver" --target "${targets[@]}" -j "${PDG_JOBS:-6}"
    ctest --test-dir "/work/$solver" --output-on-failure \
        -R '^pdg-(physics-owners|physicsbody|animation-pose|spriter-playback)$' \
        --output-junit "/results/$solver.xml"
done
