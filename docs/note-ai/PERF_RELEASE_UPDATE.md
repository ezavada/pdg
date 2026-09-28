# Release performance update — September 27, 2026

All eight native benchmarks, three browser benchmarks and the Node addon animation benchmark passed on the Apple M5 Max (macOS arm64). The pinned baseline is `quick-2026-09-27-m5-max`; its files were preserved.

## Changes

- Native JavaScript benchmarks build and verify an isolated CMake Release client. The Node lane builds a Release addon; debug defines now belong only to its Debug configuration. Interactive launchers use the same build selection. Explicit Debug runtimes are rejected.
- Browser benchmarks build the production `WASM_BUILD=release` runtime and fetch their images before sampling. Native reports record the executable, build configuration and Node version; browser reports record the release artifact and allocated WASM heap size.
- Embedded entry scripts compile as CommonJS modules, keeping top-level variables out of contextified VM globals. Module identity, relative imports, argument handling, globals and asynchronous use have regression coverage.
- The V8 `drawImage` Point overload validates and converts coordinates once, using internalized property keys. Arrays, inherited coordinates, getter counts, numeric conversion order and exception propagation are covered. Rect and Quad overloads retain their existing dispatch.
- CanvasMark loads its compatibility layer as a module so image paths have a valid `__dirname`.
- Browser benchmarks delete owned temporary attributes, polygons, splines and image subsections after drawing. The release CanvasMark run exposed a pre-existing ownership leak: an inspected `std::bad_alloc` occurred at a 2,147,483,648-byte WASM heap. All three final browser runs completed with a 67,108,864-byte (64 MiB) heap.
- Sampling accepts equal timestamps while retaining frame counts and elapsed time, and still rejects invalid or backwards clocks. CanvasMark stops processing frames after a benchmark exception.

## Measurement conditions

Final runs used the pinned fixed workloads, one-second warm-up and three-second samples, with uncapped rendering. Builds finished before measurement; benchmark processes ran sequentially. The graphics workloads still allocate drawing objects and issue the same drawing calls; browser temporaries are now released after use.

These are single-run comparisons, not regression thresholds. Release compilation, CommonJS loading, binding conversion and browser object cleanup contribute to the combined change. The pinned reports lack runtime build metadata; the runner Node version also changed from v24.3.0 to v24.21.0. Current embedded and addon runtimes report Node 24.21.0.

Scores are higher-is-better, and are synthetic extrapolations from fixed loads. Timing metrics are lower-is-better. Percent change is `100 × (current / baseline − 1)`.

## Native rendering

| Benchmark / subtest | Pinned score | Release score | Change |
| --- | ---: | ---: | ---: |
| QuickBunnyMark (JavaScript) | 6,394 | 26,594 | +315.9% |
| QuickPDGMark (JavaScript) | 13,156 | 39,168 | +197.7% |
| ↳ bitmap | 4,346 | 15,906 | +266.0% |
| ↳ drawing | 3,007 | 8,991 | +199.0% |
| ↳ alpha | 3,290 | 8,610 | +161.7% |
| ↳ polygon | 2,137 | 5,252 | +145.8% |
| ↳ text | 376 | 409 | +8.8% |
| QuickCanvasMark (JavaScript) | 30,544 | 65,009 | +112.8% |
| ↳ asteroids-bitmaps | 1,336 | 2,496 | +86.8% |
| ↳ asteroids-vectors | 2,516 | 6,247 | +148.3% |
| ↳ asteroids-mixed | 2,963 | 7,021 | +137.0% |
| ↳ asteroids-effects | 1,662 | 3,580 | +115.4% |
| ↳ arena | 15,992 | 31,222 | +95.2% |
| ↳ plasma | 380 | 605 | +59.2% |
| ↳ 3d | 5,695 | 13,838 | +143.0% |
| QuickBunnyMark (C++) | 47,214 | 47,230 | 0.0% |
| QuickPDGMark (C++) | 137,986 | 134,652 | -2.4% |
| ↳ bitmap | 47,672 | 47,658 | 0.0% |
| ↳ drawing | 27,271 | 26,523 | -2.7% |
| ↳ alpha | 42,658 | 41,415 | -2.9% |
| ↳ polygon | 19,974 | 18,656 | -6.6% |
| ↳ text | 411 | 400 | -2.7% |

## Browser rendering

| Benchmark / subtest | Pinned score | Release score | Change |
| --- | ---: | ---: | ---: |
| QuickBunnyMark (JavaScript) | 4,037 | 5,953 | +47.5% |
| QuickPDGMark (JavaScript) | 8,362 | 15,484 | +85.2% |
| ↳ bitmap | 3,249 | 5,250 | +61.6% |
| ↳ drawing | 1,391 | 2,901 | +108.6% |
| ↳ alpha | 2,420 | 4,938 | +104.0% |
| ↳ polygon | 1,265 | 2,358 | +86.4% |
| ↳ text | 37 | 37 | 0.0% |
| QuickCanvasMark (JavaScript) | 26,542 | 41,922 | +57.9% |
| ↳ asteroids-bitmaps | 1,144 | 1,912 | +67.1% |
| ↳ asteroids-vectors | 2,102 | 3,004 | +42.9% |
| ↳ asteroids-mixed | 2,657 | 4,912 | +84.9% |
| ↳ asteroids-effects | 1,297 | 1,965 | +51.5% |
| ↳ arena | 14,181 | 19,952 | +40.7% |
| ↳ plasma | 319 | 425 | +33.2% |
| ↳ 3d | 4,842 | 9,752 | +101.4% |

## Native fixed-work timings

| Benchmark / operation | Unit | Pinned | Release | Change |
| --- | --- | ---: | ---: | ---: |
| animation-pipeline / owned final pose snapshot | us/op | 17.564 | 13.193 | -24.9% |
| animation-pipeline / silent authored sample (fresh evaluator) | us/op | 90.030 | 19.894 | -77.9% |
| animation-pipeline / atomic seek and publication | us/op | 111.163 | 14.194 | -87.2% |
| animation-pipeline / seek and publication with script modifier | us/op | 138.693 | 29.004 | -79.1% |
| animation-pipeline / seek and publication with modifier and IK | us/op | 157.742 | 31.664 | -79.9% |
| animation-pipeline / independent transition selection/interruption | us/op | 116.191 | 15.306 | -86.8% |
| cpp-collider / basic / contacts | ms/step | 0.886 | 0.843 | -4.9% |
| cpp-collider / basic / approach | ms/step | 0.668 | 0.654 | -2.1% |
| cpp-collider / chipmunk / contacts | ms/step | 1.039 | 1.018 | -2.0% |
| cpp-collider / chipmunk / approach | ms/step | 0.911 | 0.882 | -3.2% |
| cpp-rig / 1 rig | ms/step | 0.261 | 0.196 | -24.6% |
| cpp-rig / 10 rigs | ms/step | 1.986 | 1.992 | +0.3% |
| cpp-rig / 50 rigs | ms/step | 10.512 | 10.290 | -2.1% |
| cpp-rig / 100 rigs | ms/step | 21.814 | 21.957 | +0.7% |

## Release Node addon

Only the animation pipeline applies to this headless addon. There is no pinned Node-addon baseline.

| Operation | Release µs/op |
| --- | ---: |
| owned final pose snapshot | 10.652 |
| silent authored sample (fresh evaluator) | 18.385 |
| atomic seek and publication | 13.307 |
| seek and publication with script modifier | 27.957 |
| seek and publication with modifier and IK | 29.686 |
| independent transition selection/interruption | 14.295 |

## Validation and artifacts

- Complete release client unit run: 1,405 JavaScript tests, 9,556 assertions, zero failures; all 16 CTest suites passed.
- Complete release Node addon run: 1,258 tests, 8,568 assertions, zero failures.
- Final targeted native drawing run: 81 tests, 442 assertions, zero failures.
- Browser drawing and offscreen tests: 77 specs, 405 assertions, zero failures.
- Performance runner, comparison and measurement tooling: all three suites passed.

Artifacts are under `artifacts/test-results/darwin/perf-release-update/`. Each target contains individual JSON results, logs, `reports/summary.json` and `reports/comparison.txt`. Earlier diagnostic attempts are separate from the final passing comparisons.

- [Native comparison](../../artifacts/test-results/darwin/perf-release-update/native/reports/comparison.txt)
- [Browser comparison](../../artifacts/test-results/darwin/perf-release-update/web/reports/comparison.txt)
- [Node comparison](../../artifacts/test-results/darwin/perf-release-update/node/reports/comparison.txt)

Reproduce the measurements after building with the shared release runner:

```sh
./test/perf
./test/perf --web
./test/perf --node animation-pipeline
```

`--no-build` reuses verified native/addon Release runtimes or the existing production WASM artifact. The pinned baseline is never updated by these commands.

## Shared Point conversion follow-up

`VALUE_IS_POINT(value, point)` now validates and fills the destination in one pass in both V8 and JavaScriptCore. It returns true for a converted Point, false for an invalid argument, or an empty `std::optional<bool>` when JavaScript throws. Callers stop immediately on an exception, before changing native state or attempting another overload.

Required and optional Point arguments, animation setters, collider vertices, and image/drawing/text overloads all reuse the converted coordinates. The shared `drawImage` implementation has no backend conditional. V8 uses internalized property keys and retains numeric coercion; JavaScriptCore retains its existing numeric-coordinate and indexed-object acceptance. Both generated binding trees were regenerated from their sources.

A controlled Release comparison isolates this follow-up from the earlier release-build and loader changes. The before binary already contained the optimized `drawImage` path. Each operation received 100,000 warm-up calls, followed by nine samples of 500,000 calls with a reused Point. The table reports median nanoseconds per call; builds and other tests completed before measurement.

| Call | Before ns/call | Shared conversion ns/call | Time change |
| --- | ---: | ---: | ---: |
| `setLocation(point)` | 157.56 | 73.45 | -53.4% |
| `moveTo(point)` | 165.30 | 76.23 | -53.9% |
| `rotation(0, point)` | 166.21 | 86.34 | -48.1% |
| `contains(point)` | 158.28 | 76.13 | -51.9% |

These are improvements to Point-heavy binding calls, not a claim that entire games become twice as fast. BunnyMark already used the optimized Point conversion before this follow-up.

Validation after the shared conversion change:

- Release client: 1,412 tests, 9,688 assertions, zero failures; all 16 CTest suites passed.
- Release Node addon: 1,264 tests, 8,692 assertions, zero failures.
- iOS Simulator / JavaScriptCore: all seven new Point regression tests passed (114 assertions).
- The regression suite covers getter counts, exception identity, coercion order, inherited coordinates, invalid shapes, optional defaults, reentrant calls, collider vertices, and drawing overloads. It also verifies that failed conversion leaves existing native state intact.

Follow-up artifacts, including the controlled benchmark script, before/after samples, and unit logs, are under `artifacts/test-results/darwin/point-bindings/`.

All eight native performance tests and the headless Node animation benchmark passed again after the macro change. The browser uses Embind rather than these macros, so its earlier three passing Release results remain the applicable comparison.

| Benchmark | Pinned score | Earlier Release score | Shared Point score | vs earlier Release | vs pinned |
| --- | ---: | ---: | ---: | ---: | ---: |
| JS BunnyMark | 6,394 | 26,594 | 26,332 | -1.0% | +311.8% |
| JS PDGMark | 13,156 | 39,168 | 44,159 | +12.7% | +235.7% |
| JS CanvasMark | 30,544 | 65,009 | 72,987 | +12.3% | +139.0% |
| C++ BunnyMark | 47,214 | 47,230 | 47,152 | -0.2% | -0.1% |
| C++ PDGMark | 137,986 | 134,652 | 136,124 | +1.1% | -1.3% |

The end-to-end scores are single runs and include timing noise; the repeated call measurements above isolate the shared Point change more directly. The pinned files were not modified.

- [Follow-up native comparison](../../artifacts/test-results/darwin/point-bindings/native/reports/comparison.txt)
- [Follow-up Node comparison](../../artifacts/test-results/darwin/point-bindings/node/reports/comparison.txt)
