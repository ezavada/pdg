# Performance tests

Run from any directory using `./test/perf` (Windows: `test\perf.bat` or
`test\perf.ps1`). The command runs QuickPDGMark, QuickCanvasMark and QuickBunnyMark
against release builds, including the C++ and JavaScript versions.
It incrementally builds a separate CMake Release client and the selected C++ targets
in `build/<platform>/<architecture>/pdg-perf-release`. A GUI build and a desktop session are required for
the rendering marks.

```sh
./test/perf --list
./test/perf                             # all eight benchmarks
./test/perf bunnymark cpp-bunnymark      # select benchmarks
./test/perf --no-build pdgmark
./test/perf --sample-seconds 5 --warmup-seconds 2 --load-factor 2
./test/perf --web                       # three JS marks, visible Chrome + WASM
./test/perf --node animation-pipeline   # Node module; rendering marks need graphics
./tools/node test/lib/perf_build.js test/perf_tests/canvasmark2013/canvasmark.js --quick  # direct QuickCanvasMark
```

Native entry scripts run in CommonJS module scope, with normal `require`,
`module`, `exports`, `__filename`, `__dirname` and `process.argv`. This keeps hot
local variables out of a contextified VM global object.

The default rendering workload is 1.5 times each recorded capacity, except
QuickPDGMark Polygon, which uses 4 times the recorded capacity following the
convex rendering speedup (18,400 C++ polygons; 3,800 JavaScript polygons).
`--load-factor` scales all workloads proportionally; each sample records its
actual load factor. There is one second of warm-up followed by three seconds
of measurement per subtest. The five rendering marks have 19 subtests:
approximately 76 seconds of sampling and
warm-up altogether, plus startup, object creation, build time and fixed-work
benchmarks. Very slow frames can extend a sample; the runner enforces a process
timeout. `--quick` is accepted but is already the top-level default.

Reports and stdout/stderr logs go under `artifacts/test-results/<platform>/perf/`.
`reports/summary.json` links the individual JSON reports and records failures.
Every run closes with a table of current values, pinned baseline values and
percentage changes for each selected benchmark and all its subsections. The
same table is saved as `reports/comparison.txt`; structured comparison rows are
in `reports/summary.json` under `comparison`.
Rendering reports use the Quick names, `mode: "quick"`, and retain stable
`benchmarkId` values such as `cpp-bunnymark` for selecting and comparing tests.
Standard `PDG_TEST_ARTIFACTS_DIR`, `PDG_TEST_REPORT_DIR`, `PDG_TEST_LOG_DIR` and
`PDG_TEST_TEMP_DIR` overrides apply. `PDG_EXECUTABLE`, `PDG_NODE`,
`PDG_PERF_BUILD_DIR` and `PDG_BROWSER` select local tools/builds.
An explicit `PDG_EXECUTABLE` must report a Release build. `--no-build` skips
compilation and requires an existing release runtime; it never falls back to the
development client. Native reports record the actual PDG executable, configuration
and embedded Node version. The Node lane builds the release addon before running;
its Release configuration excludes debug engine code. Browser perf uses
`build/wasm/wasm32/release/libpdg.js`, built with `WASM_BUILD=release` and
`-O3 -flto -g0`, and loads
benchmark images separately before sampling. Browser benchmarks explicitly delete
owned Embind attributes, geometry and images after their last use;
their reports include `wasmHeapBytes`, the allocated WASM heap size at completion.
Unit/UI browser tests retain their debug WASM build. No recorded baselines are
overwritten. Missing output, incomplete samples, timeouts, crashes
and failed builds produce a nonzero exit status; these are measurements, with
no hard-coded performance regression threshold.

## Pinned Quick baseline

[`baselines/quick-baseline.json`](baselines/quick-baseline.json) pins the
September 28, 2026 native measurements from the Apple M5 Max, macOS arm64,
using the Release runtime with embedded Node 24.21.0 and uncapped rendering.
All eight native benchmarks passed in the run started at 16:41:54 UTC, after
the binding conversion fixes, BunnyMark reuse, and C++/JavaScript PDGMark
resource reuse. Their complete original reports are preserved under
`baselines/quick-2026-09-28-m5-max/native/`.

Browser references remain from September 27 under
`baselines/quick-2026-09-27-m5-max/web/`: BunnyMark/PDGMark come from the
tessellation-cache run, and CanvasMark uses the later PNG ship decoding fix.
The manifest records provenance per benchmark and native runtime build metadata.

| Quick benchmark | Native JavaScript | Native C++ | Browser |
| --- | ---: | ---: | ---: |
| QuickBunnyMark | 29,405 | 47,219 | 4,037 |
| QuickPDGMark | 77,870 | 143,839 | 8,362 |
| QuickCanvasMark | 85,173 | — | 26,542 |

The baseline also includes every subsection and the native animation pipeline,
collider and rig timings. Rendering scores are higher-is-better. Fixed-work
comparisons show microseconds per animation operation or milliseconds per
collider/rig step, where lower is better. Percentage change is
`100 × (current / baseline - 1)` for both kinds of measurement.

Native and browser runs use their respective references; there is currently
no Node-plugin baseline. Missing references display `--`, as do current values
for failed or unstarted benchmarks. Partial selections show only the selected
benchmarks. Differences in CPU, platform, architecture, runner runtime or
workload/sampling/scoring settings are noted alongside the comparison.

These are single-run measurements, not averaged regression thresholds. The
runner never updates the baseline. To intentionally establish a new one,
preserve the reviewed reports in a new dated directory and update the manifest
with their provenance. The historical ramp references and CanvasMark
calibration below still define workloads and score scaling; this Quick baseline
only provides a stable comparison point.

The [release runtime comparison](../../docs/note-ai/PERF_RELEASE_UPDATE.md)
records the rerun after the release-build, script-loading and binding fixes.
The [JavaScript resource reuse review](../../docs/note-ai/JAVASCRIPT_BENCHMARK_REUSE.md)
records the BunnyMark allocation/getter improvements and related PDGMark findings.
The [browser compiler comparison](../../docs/note-ai/WASM_O3_COMPARISON.md)
measures separate Release `-Oz` and `-O3` builds, including size and unit-test results.

## Quick scores

Each sample measures elapsed time between frame starts, including presentation
and scheduling. Warm-up and initial object construction are excluded. Average
FPS is completed frame intervals divided by their total elapsed time. Reports
include load, reference values, frame count, elapsed time, mean/p95/p99 frame
times and the synthetic score. For QuickPDGMark and QuickBunnyMark:

```
estimated capacity = fixed load × measured FPS / target FPS
synthetic score = round(reference score × fixed load / reference load × measured FPS / target FPS)
```

QuickBunnyMark uses the recorded bunny count and a 60 FPS target. QuickPDGMark
uses each subtest's recorded object count, a 60 FPS target, and the original weights
(1, 1.2, 1.3, 1.5, 1.4). Composite scores sum the rounded subtest scores.
The C++ and JavaScript marks use their respective committed baseline files.

QuickCanvasMark uses measured original-ramp populations and frame costs from
`canvasmark2013/calibration.json`. The original score depends on elapsed time,
including scene titles, and stops after ten cumulative frames below **30 FPS**;
its last workload does not necessarily run at exactly 30 FPS. Assuming 60 updates
per second to infer populations from historical scores overestimated several loads.
The calibration records actual loads and normalizes the last ten frame intervals
by their loads before taking the median. QuickCanvasMark extrapolates equivalent
load at that measured reference FPS, then scales the reference score. Plasma
measures cell throughput but converts back to grid width (starting at eight cells
per side), since its original ramp score grows with width rather than cell count.

```
equivalent load = fixed load × measured FPS / reference FPS
QuickCanvasMark subscore = round(reference score × equivalent load / reference load)
plasma subscore = round(reference score × max(0, sqrt(equivalent load) - 8) / (sqrt(reference load) - 8))
```

Asteroids, ships, bullets, plasma cells and cubes are seeded directly; primary
populations stay fixed. Ships still update and may produce transient bullets and
effects. Actor age, type mix, scheduling and random ramp termination limit the
approximation. The native calibration is also used for browser runs; it is a
reference scale, not a claim that the two platforms have identical ramp behavior.

To collect a new reference without changing the original ramp:

```sh
./tools/node test/lib/perf_build.js test/perf_tests/canvasmark2013/canvasmark.js --calibrate --output /tmp/canvas-ramp.json
```

This exits after all seven tests and includes a `calibration` object with the
terminal samples. Review it before replacing `calibration.json`; add the result's
timestamp and a source description identifying hardware/build. Calibration is
separate from `--quick`, and the runner never overwrites it automatically.

Quick mode enables the internal `PDG_PERF_UNCAPPED=1` process override. It
bypasses the engine's frame timer and disables swap synchronization in every
native desktop window, including the initial window. It does not change the
public `setTargetFPS()` behavior for ordinary applications. Reports identify
`framePacing: "uncapped"`, `requestedEngineFPS: null` and `requestedSwapInterval: 0`.
The 60 FPS and 30 FPS values used in scoring are reference rates, not run limits.
`atOrAboveTarget` is informational; running faster than the reference is expected.

Browser Quick runs use a message queue instead of nested timers. The top-level
runner launches visible Chrome with frame limiting and GPU vsync disabled, and
extensions disabled to prevent sign-in tabs interfering with measurements. A
hidden test tab causes the run to fail. Opening `test/perf.html` manually still
inherits that browser's compositor/driver policies. The OS/driver can override
presentation requests, so these settings cannot guarantee unrestricted physical
display refresh or portable equivalence across platforms.

These estimates assume cost scales linearly with workload. Fixed overhead,
batching and GPU saturation limit accuracy. The original native JS/C++ ramp
tests mostly measured draw-callback duration, so a Quick score is not a drop-in
replacement for those historical measurements. Compare like modes, settings,
builds and hardware. Browser runs do not force a software renderer; the
browser/driver selects the renderer.

The engine caches tessellation on each `Polygon` after its first filled draw.
Point edits invalidate the cache; `Attributes` transforms reuse it. PDGMark now
retains its polygons and rotates them through Attributes in both C++ and
JavaScript. The September 28 native baseline includes this reuse; the September
27 browser baseline rebuilt polygons every frame. Improvements against that
older workload include avoiding construction and repeated tessellation, with
the same visible animation and fixed object counts. Alpha uses rectangles
and ellipses, which also do not retain a polygon cache between frames.

Animation pipeline, collider and articulated rig benchmarks already use fixed
work. The runner records their original throughput/CSV results without
inventing mark scores. Collider uses 200 measured steps for a short run.
Sampling flags apply to rendering marks only.

## Original interactive benchmarks

Launch the scripts/executables directly to retain the original ramp-up modes:

```sh
./tools/node test/lib/perf_build.js test/perf_tests/bunnymark/bunnymark.js
./tools/node test/lib/perf_build.js test/perf_tests/pdgmark/pdgmark.js
./tools/node test/lib/perf_build.js test/perf_tests/canvasmark2013/canvasmark.js --auto
build/darwin/arm64/pdg/src/bunnymark.app/Contents/MacOS/bunnymark
```

Each rendering entry also accepts `--quick`, `--sample-seconds`,
`--warmup-seconds`, `--load-factor` and `--output <json-path>` when run directly
from the repository root. The top-level runner handles working directories and
artifact paths automatically. Existing per-benchmark wrappers and comparison
tools are preserved under `test/perf_tests`.

Run the performance tooling checks with
`./test/tools perf-runner perf-comparison perf-measurement`, or use `./test/tools`
for all tooling checks. These validate sampling and reporting without running PDG
benchmarks; the native measurement check needs a C++17 compiler.
See the [September 2026 investigation](../../docs/note-ai/PERFORMANCE_INVESTIGATION_2026-09.md)
for renderer, synchronization and calibration findings.
