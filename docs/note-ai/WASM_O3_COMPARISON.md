# Browser Release build: -Oz versus -O3

September 28, 2026, Apple M5 Max, macOS arm64, Chrome 154, Emscripten 6.0.8-git.
The experiment uses source commit `5d37d0337`, including the BunnyMark argument
reuse and getter-hoisting changes. This tests compiler optimization independently
of renderer or benchmark changes.

## Results

All 18 benchmark executions passed. Median scores over three runs favored O3:

| Benchmark | Oz scores | O3 scores | Oz median | O3 median | Score gain |
| --- | --- | --- | ---: | ---: | ---: |
| BunnyMark | 6,210 / 6,247 / 6,269 | 6,970 / 6,915 / 6,921 | 6,247 | 6,921 | +10.8% |
| PDGMark | 15,321 / 14,927 / 15,179 | 17,294 / 17,277 / 17,382 | 15,179 | 17,294 | +13.9% |
| CanvasMark | 41,022 / 41,321 / 41,648 | 47,574 / 47,839 / 47,653 | 41,321 | 47,653 | +15.3% |

BunnyMark at 9,600 bunnies improved from 25.614 to 23.117 ms per frame, a
9.7% time reduction. This is useful but still well above the preceding native
JavaScript measurement of 5.401 ms; compiler optimization does not remove the
legacy GL emulation and per-image submission overhead.

Median mean-frame times by subtest:

| Subtest | Oz (ms) | O3 (ms) | Time reduction |
| --- | ---: | ---: | ---: |
| PDGMark bitmap | 16.334 | 14.209 | 13.0% |
| PDGMark drawing | 26.155 | 25.387 | 2.9% |
| PDGMark alpha | 13.491 | 10.836 | 19.7% |
| PDGMark polygon | 40.866 | 38.011 | 7.0% |
| PDGMark text | 289.945 | 292.491 | −0.9% |
| CanvasMark bitmap asteroids | 35.533 | 28.115 | 20.9% |
| CanvasMark vector asteroids | 38.540 | 36.401 | 5.5% |
| CanvasMark mixed asteroids | 25.217 | 19.364 | 23.2% |
| CanvasMark effects | 42.508 | 36.533 | 14.1% |
| CanvasMark arena | 34.497 | 31.641 | 8.3% |
| CanvasMark plasma | 50.905 | 43.952 | 13.7% |
| CanvasMark 3D | 23.753 | 19.423 | 18.2% |

The overall score ranges do not overlap in these runs. Small section changes,
especially text and drawing, should not be treated as established improvements
or regressions from three samples. All runs ended with a 64 MiB WASM heap.

The results support using O3 for browser builds where runtime performance is
the priority, at the cost of about 209 KB more gzipped WASM. The separate Release
argument-validation failures below need their own binding fix regardless of
which optimization level is used.

## Method

Both configurations were rebuilt from source into separate directories, with
fresh object files. The only changed flag was `-Oz` versus `-O3`; both retain
`-flto -g0`, `NDEBUG`, exception support and `LEGACY_GL_EMULATION=1`.

```sh
export PDG_ROOT="$PWD"
export EM_CACHE="$PWD/build/wasm/wasm32/emscripten-cache"
export EMSDK_PYTHON="$(command -v python3)"
for opt in Oz O3; do
    emmake make -j8 -f tools/pdg-js.mak CC=emcc CXX=em++ WASM_BUILD=release \
        "WASM_OUT_DIR=$PWD/build/wasm/wasm32/compare-$opt" \
        "BUILD_FLAGS=-$opt -flto -g0"
done
```

The existing browser harness serves each isolated build at the usual runtime
URL without replacing the default artifacts. Each build runs BunnyMark,
PDGMark and CanvasMark three times in visible Chrome with uncapped rendering.
Build order alternates: Oz/O3, O3/Oz, Oz/O3. Each subtest uses the usual fixed
load, one second of warm-up and three seconds of measurement. No builds or
other test lanes run concurrently with performance measurements.

Separate links of the same optimized objects embed the unit-test fixtures for
the full browser suite. Thus the units exercise Release code, including its
argument-validation behavior, rather than the normal debug browser runtime.

## Correctness

Both configurations ran all 1,372 browser tests with no load failures. Both
produced the same three failed assertions across two specs: `addEllipse` and
the legacy-named `addOval` spec expect null numeric radii to throw. Counts were
9,358 assertions for Oz and 9,353 for O3; asynchronous assertions vary by run.

The installed Emscripten `src/lib/libembind.js` wraps its float converter's
JavaScript type check in `#if ASSERTIONS`. These Release builds omit it, and
`null` reaches JavaScript-to-WASM numeric coercion instead. This is an existing
Release binding-validation difference, reproduced in Oz; it is not a new O3
failure. The earlier passing browser suites used the debug runtime. The
experiment does not change these bindings or suppress the failing tests.

## Artifact size

| File | Oz | O3 | Change |
| --- | ---: | ---: | ---: |
| WASM | 2,304,235 bytes | 3,171,465 bytes | +37.6% |
| WASM, gzip level 9 | 789,531 bytes | 998,907 bytes | +26.5% |
| JavaScript | 304,671 bytes | 303,797 bytes | −0.3% |
| JavaScript, gzip level 9 | 70,686 bytes | 70,811 bytes | +0.2% |

Gzip numbers are file compression measurements, not measured transfer sizes
from the local test server. Startup and download time are excluded from the
timed benchmark samples.

[Experiment artifacts](../../artifacts/test-results/darwin/wasm-o3/) contain
build commands/logs, runtime hashes, the comparison driver, unit reports and
individual benchmark results. Pinned baseline files and default build flags
are not changed by this experiment.

Following this experiment, the approved build update adopts `-O3 -flto -g0`
for the standard WASM Release configuration, including performance tests and
release packaging. Packaging also builds a separate standalone Debug runtime;
see [Releasing PDG](../RELEASING.md) for the two-archive layout.

Adoption validation:

- Built actual Release and Debug ZIPs with SHA-256 files. Local packaging used
  `--skip-tests`, followed by the independent validation below; the full UI/demo
  release lanes were not rerun for this packaging change.
- Extracted both ZIPs and rendered three frames with each in Chrome. Release
  and Debug assertion behavior was verified, and neither contained test fixtures.
  The Debug map includes all 902 referenced source texts.
- All six tooling suites passed, including new packaging checks for both ZIPs,
  checksums, ordinary test invocation, `--skip-tests`, and missing/failed outputs.
- The full browser Debug suite passed: 1,372 tests, 9,363 assertions, all 70 spec
  files loaded. The shared catalog was updated to include seven existing binding
  specs; those specs gate themselves to V8/JSC where applicable.
- All three standard Release browser benchmarks passed: BunnyMark 7,163,
  PDGMark 17,683, CanvasMark 47,848. The controlled comparison above remains the
  evidence for the compiler speedup.
- CMake's stale `1.0.0` project version was aligned with the existing `VERSION`
  value `1.1.0`, resolving the release validator's version mismatch.

[Adoption artifacts](../../artifacts/test-results/darwin/wasm-packaging/) include
the packages, smoke reports, tooling/unit logs and benchmark results.
