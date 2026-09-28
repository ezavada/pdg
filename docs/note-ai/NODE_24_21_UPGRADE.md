# Node 24.21 upgrade validation

Validated on 2026-09-27 on macOS arm64, Apple M5 Max, and Ubuntu 24.04 arm64
in local Docker.

## Runtime and build changes

The Node submodule advances from v24.3.0 to [v24.21.0 LTS](https://nodejs.org/en/blog/release/v24.21.0),
commit `955266bfdd854cd280dffd47548673914484e4c0`. The Node checkout has no local patches.
The rebuilt runtime reports V8 `13.6.233.17-node.53`, OpenSSL `3.5.8`, and native module ABI `137`.

- Node now produces a separate `node_base` library. PDG links it and the added
  dependency archives, using upstream's whole-archive flags for builtin registration.
- Embedded shutdown uses the public `node::Stop()` API and
  `CommonEnvironmentSetup` cleanup.
- POSIX and Windows build helpers check a recorded source version and the runtime's
  actual version before reusing cached builds. Failed builds cannot certify the
  cache. POSIX builds produce the runtime and libraries in one pass.
  The Windows tool copy is refreshed on upgrades.
- Python selection accepts Node's supported range, 3.9–3.14, on both platforms.
- The iOS JavaScriptCore native-source bundle was regenerated from the updated
  vendored Node sources. The maintained iOS test wrapper is preserved by `configure`.

Source builds of Node, the native PDG client, the Node plugin, Emscripten, and the
iOS simulator application completed. Linux headless builds of Node, the embedded
PDG executable, the C++ libraries/tests, and the Node addon also completed.
Windows scripts were parsed with PowerShell; the Python version boundary logic
was executed. Windows binaries were not built in this validation.

## Unit tests

| Run | Result |
| --- | --- |
| `./test/unit` | 16/16 CTest suites; 1,388 JavaScript tests passed |
| `./test/unit --node` | 1,251 tests passed |
| `./test/unit --web --no-build --automated` | 1,368 tests passed; no load failures |
| `./test/unit --ios --iphone` | 1,366 tests passed on iPhone 17 Pro / iOS 26.5 simulator |

The new Node integration suite verifies the pinned runtime version, crypto,
compression, VM initialization, a worker isolate, and an HTTP/fetch round trip.
It runs in both the embedded client and headless plugin.

Validation also uncovered and corrected existing test and platform issues:

- FileManager uses the current `perf_tests` benchmark directory.
- NetServer's initial listening-state assertion ran after yielding to the event
  loop. It now captures the state before calling `listen()` and still verifies
  that the listening event subsequently arrives.
- The iOS event binding dereferenced a null layer when an unattached sprite emitted
  a physics-break event. The JavaScriptCore binding source now handles nullable
  ownership fields like the V8 binding; its output was regenerated. The existing
  physics-break spec now explicitly checks the null layer.
- A ResourceManager lifecycle assertion mistook `/data/` in the simulator's bundle
  path for the resource directory. It now verifies that closing the resource file
  restores the original search paths.

The strengthened physics/resource specs passed targeted reruns on native, Node,
and browser targets, and the full simulator suite. Build-cache regression tests,
runner/catalog tests, and the Quick perf runner/comparison checks also passed.

## UI tests

The UI suites available during upgrade validation passed in each target
(see [the testing guide](../../test/README.md) for the current catalog):

- `./test/ui --automated`
- `./test/ui --web --no-build --automated`
- `./test/ui --ios --iphone --no-build --automated`

These are automated smoke runs. Browser shape-fill verification also passed its
pixel checks for texture mapping, clipping, polygon caching, and CanvasMark ship
decoding/rendering. Native and simulator runs completed all timed UI pages.

## Quick performance

All eight native benchmarks, all three browser benchmarks, and the headless Node
animation-pipeline benchmark passed. The complete native run took 90.7 seconds;
the browser run took 55.8 seconds. Loads, warm-up, sample duration, scoring, and
the pinned baseline were unchanged.

Scores from the complete runs compared with `quick-2026-09-27-m5-max`:

| Benchmark | Native JavaScript | Native C++ | Browser |
| --- | ---: | ---: | ---: |
| QuickBunnyMark | 5,642 (−11.8%) | 47,200 (−0.03%) | 4,052 (+0.4%) |
| QuickPDGMark | 13,784 (+4.8%) | 143,865 (+4.3%) | 8,310 (−0.6%) |
| QuickCanvasMark | 31,274 (+2.4%) | — | 26,423 (−0.4%) |

PDGMark alpha/polygon detail:

| Subtest | Native JavaScript | Native C++ | Browser |
| --- | ---: | ---: | ---: |
| Alpha | 3,425 (+4.1%) | 43,838 (+2.8%) | 2,351 (−2.9%) |
| Polygon | 2,131 (−0.3%) | 20,693 (+3.6%) | 1,268 (+0.2%) |

The JavaScript BunnyMark decrease did not reproduce in an immediate old/new
control: the preserved v24.3.0 client scored **6,401**, followed by **6,958** on
v24.21.0, both at 9,600 bunnies with the standard 1-second warm-up and 3-second
sample. These short measurements vary; the first full-run dip is not sufficient
evidence of a Node regression. Control reports are in `perf-bunny-old-control/`
and `perf-bunny-new-control/`. The old control uses the preserved embedded client;
its summary's `runtime` field still identifies the v24.21.0 launcher.

The native animation timings were 2.9–18.5% lower than baseline, collider timings
6.9–10.4% lower, and rig timings ranged from 25.5% lower to 0.2% higher. These are
single-run comparisons, not measurements isolating Node's contribution. The Node
plugin animation benchmark has no pinned baseline of its own.

An earlier attempt aborted in the C++ rendering marks because the display had
gone idle and GLFW reported zero monitors. A minimal GLFW probe reproduced that
condition and then detected all three monitors after a display-wake assertion.
The successful complete native/browser runs used `caffeinate -diu ./test/perf`
(with `--no-build`, and `--web` for the browser). The failed attempt is preserved
under `perf-native-display-asleep/`; it is excluded from the results above.

Every subsection score and microbenchmark timing is retained in
`perf-native/reports/comparison.txt` and `perf-web/reports/comparison.txt`, with
machine-readable data in their `summary.json` files under the artifact root below.

## Ubuntu Docker validation

An isolated copy of the upgrade was built using the existing
`pdg-physics-linux:ubuntu24.04` image, Ubuntu 24.04.4 on native AArch64,
GCC 13.3.0, CMake 3.28.3, and Python 3.12.3. The container is named
`pdg-node24-linux-check`; its source/build cache lives in the
`pdg-node24-linux-build` volume at `/work/source`. The host checkout was mounted
read-only. Platform-independent JavaScript tooling was copied from the host;
the Node executable, embedded runtime, and addon were built for Linux from source.
The resulting executable and addon were verified as ELF AArch64 binaries.

Node was built with three jobs to fit Docker's 8 GB memory allocation:

```sh
./configure --headless
bash tools/build-node.sh "$PWD" "$PWD/build/linux/arm64/node/out" \
  /usr/bin/python3 3 --dest-cpu=arm64 --without-node-snapshot
make node chipmunk pdg-cmake-refresh
cmake --build build/linux/arm64/pdg --parallel 3
make pdg
npm_config_jobs=3 make pdg-node
```

The Linux run exposed and fixed three issues:

- Standalone C++ consumers need an ELF linker rescan group around Node's zlib
  archives. The optimized inflate archive references `inflate_table` in the main
  archive, which otherwise has already been scanned.
- Fresh addon packages lacked `pnglibconf.h`. Both packaging scripts now copy
  libpng's supplied configuration template. The addon also disables ARM NEON
  paths because its portable PNG source list omits the NEON objects.
- The headless `SpriteLayer` constructor left two event flags uninitialized.
  Optimized GCC code could carry their invalid values into other serialized flag
  bits, incorrectly restoring layers as static and rejecting kinematic rigs or
  mounts. The flags are now initialized on every platform. A regression using
  prefilled memory failed before the fix and passes afterward, including on macOS.

| Linux check | Result |
| --- | --- |
| Embedded `./test/unit` | 11/11 CTest suites; 1,251 JavaScript tests, 8,558 assertions, zero failures |
| `./test/unit --node` | 1,251 tests, 8,558 assertions, zero failures |
| Build-cache, runner options, perf runner, perf comparison checks | All passed |
| Native headless perf | Animation pipeline, C++ collider, and C++ rig passed |
| Node headless perf | Animation pipeline passed |

The embedded test run explicitly set
`PDG_EXECUTABLE=/work/source/build/linux/arm64/pdg/src/pdg-debug` and
`PDG_TEST_BUILD_DIR=/work/source/build/linux/arm64/pdg`. This exercises the actual
embedded executable; the default Linux `pdg` launcher uses the Node addon.
The Node integration specs passed in both runtimes. The rebuilt Node reports
v24.21.0, V8 `13.6.233.17-node.53`, OpenSSL `3.5.8`, and ABI `137`.

Linux validation covers ARM64 headless execution. Linux x86-64 and graphical UI
benchmarks were not exercised. Docker microbenchmark timings are not directly
comparable with the pinned native macOS rendering baseline.

## Artifacts

Build logs, complete unit logs, UI reports, and performance reports are stored under
`artifacts/test-results/darwin/node-24.21/`. The previous Node executable, client,
and plugin were preserved under its `before/` directory for diagnosis. The pinned
Quick perf baseline in `test/perf_tests/baselines/` remains unchanged.

Linux build logs, failed-attempt diagnostics, final unit/perf reports, environment
details, and the exact build/test scripts are under
`artifacts/test-results/linux-docker/node-24.21/`. Source transfer used tar with
macOS metadata disabled after Docker shared-folder rsync exhausted file handles;
accidental AppleDouble files from an earlier transfer were removed from the
isolated copy and affected build files regenerated. These transfer failures are
separate from the source issues above. The task container is stopped after
validation; its build volume is retained for incremental checks.
