# JavaScript conversion fixes — September 28, 2026

Each fix is validated and committed before starting the next. Baseline source is commit `999cf6701`; the pinned performance baseline remains unchanged. Runtime artifacts are under `artifacts/test-results/darwin/conversion-fixes/`.

The native and Node lanes use verified Release builds. Each native change runs all client and Node JavaScript units, all 16 CTest suites, targeted JavaScriptCore tests in the iOS Simulator, all eight native performance tests and the Node animation benchmark. The focused call benchmark reports the median of seven 200,000-call samples after warm-up. End-to-end scores are single runs and include timing noise.

## 1. Offset and Vector

Required/optional arguments and animation overloads now validate and convert once using the checked Point reader. Throwing coordinate getters, numeric coercions and proxy traps preserve their original exceptions; failed conversion returns before changing native state. The unexposed Serializer size dispatcher was adapted to the same checked interface. Both generated binding trees were regenerated.

- Client: 1,415 tests / 9,759 assertions; Node: 1,267 tests / 8,756 assertions; all 16 CTest suites passed.
- iOS conversion regressions: nine tests / 160 assertions passed.
- All eight native performance tests and the Node animation benchmark passed.
- `setSize(Offset)`: 153.35 → 77.82 ns/call, **49.3% less time**.
- `setMovement(Vector)`: 159.97 → 83.48 ns/call, **47.8% less time**.
- Native JS scores: BunnyMark 25,029; PDGMark 43,728; CanvasMark 73,533. Compared with the preceding run: −4.9%, −1.0%, +0.7%, respectively. Unchanged microbenchmark controls varied by 5–11%, so these full-mark differences are not evidence of a comparable causal gain or regression.

[Artifacts](../../artifacts/test-results/darwin/conversion-fixes/01-offset-vector/) include full unit logs, per-benchmark reports, comparison against the pinned baseline and raw call timing samples.

## 2. Rect and RotatedRect

Rectangle arguments now validate and convert once, including nested corners, rotation and center offsets. Checked reads preserve getter, proxy and numeric-conversion errors. JavaScriptCore no longer clears optional rotation-field exceptions before serialization. Existing backend-specific rectangle forms remain supported; malformed centers are rejected.

- Client: 1,420 tests / 9,808 assertions; Node: 1,272 tests / 8,810 assertions; all 16 CTest suites passed.
- iOS conversion regressions: 13 tests / 210 assertions passed.
- All eight native performance tests and the Node animation benchmark passed.
- `subsection(Rect)`: 601.37 → 180.40 ns/call, **70.0% less time** than the original baseline.
- Native JS scores: BunnyMark 20,077; PDGMark 45,906; CanvasMark 71,406. A targeted BunnyMark recheck scored 25,153, consistent with the preceding fix's 25,029; the first lower run did not reproduce.

[Artifacts](../../artifacts/test-results/darwin/conversion-fixes/02-rect/) include both BunnyMark runs and full validation logs.

## 3. Quad

Quad arguments now validate and convert once. Four-Point arrays are recognized before numeric rectangle arrays, fixing V8's NaN rectangle conversion. Rectangle/rotation forms use the checked readers; throwing getters stop before native calls. The drawing overload consumes the converted Quad directly. Obsolete unchecked rectangle/Quad implementations were removed.

- Client: 1,424 tests / 9,835 assertions; Node: 1,276 tests / 8,836 assertions; all 16 CTest suites passed.
- iOS conversion regressions: 17 tests / 235 assertions passed.
- Regression tests verify exactly one read of the points property, each array element and each coordinate (the audit measured up to four coordinate reads in JSC).
- All eight native performance tests and the Node animation benchmark passed. Native JS scores: BunnyMark 24,617; PDGMark 42,305; CanvasMark 74,216. These marks do not isolate Quad conversion; the getter-count tests establish the reduction in conversion work.

[Artifacts](../../artifacts/test-results/darwin/conversion-fixes/03-quad/) contain the full results.

## 4. Polygon constructor vertices

Both constructor forms now use the checked Point converter and checked array reads. Malformed vertices fail before allocating the native polygon. The obsolete unchecked Point/Offset/Vector conversion functions were removed. JSC constructors receive an exception output, including a safe fallback for native callers; the V8 managed constructor wrapper preserves the original exception instead of replacing it with a generic creation error. These wrapper corrections were required by the new exception-identity regressions.

- Client: 1,428 tests / 9,858 assertions; Node: 1,280 tests / 8,867 assertions; all 16 CTest suites passed.
- iOS conversion regressions: 20 tests / 256 assertions passed.
- Both constructor forms read each coordinate once; thrown vertex/index getters and numeric coercions return the original error without aborting.
- All eight native performance tests and the Node animation benchmark passed. Native JS scores: BunnyMark 24,622; PDGMark 46,067; CanvasMark 74,117. This is primarily a correctness fix; these benchmarks do not isolate polygon construction.

[Artifacts](../../artifacts/test-results/darwin/conversion-fixes/04-polygon/) contain the passing validation results.

## 5. Matrix arguments

`transform`, `setTransform` and `changeTransform` now check array reads before validating or extracting each numeric element. V8 no longer aborts on a throwing getter; JSC preserves the original exception. Numeric V8 values are extracted directly after their type check. All conversion completes before modifying native transform state.

- Client: 1,431 tests / 9,931 assertions; Node: 1,283 tests / 8,928 assertions; all 16 CTest suites passed.
- iOS conversion regressions: 23 tests / 321 assertions passed.
- Regression tests cover all three methods, single reads, exception identity, early termination and unchanged state after invalid input.
- All eight native performance tests and the Node animation benchmark passed. Native JS scores: BunnyMark 24,447; PDGMark 46,131; CanvasMark 74,599. No isolated matrix speedup is claimed for this correctness fix.

[Artifacts](../../artifacts/test-results/darwin/conversion-fixes/05-matrix/) contain the full results.

## 6. Color

Color arguments now validate and convert once. Native bindings and `Color::makeColor` share a length-aware internal CSS parser with binary search over the existing name table. Short hex duplicates each nibble correctly; invalid digits, lengths and embedded NULs are rejected by the bindings. The public C++ factory keeps its default-color fallback for invalid input. JSC's byte-color conversion initializes all channels, preserves omitted alpha and validates the documented channel range. The Node addon now compiles the shared color implementation.

- Client: 1,436 tests / 10,023 assertions; Node: 1,288 tests / 9,029 assertions; all 16 CTest suites passed, including new native parser regressions.
- iOS conversion regressions: 28 tests / 421 assertions passed.
- `fillColor(Color)`: 621.98 → 191.21 ns/call, **69.3% less time** than the original baseline.
- `fillColor('yellowgreen')`: 527.15 → 56.17 ns/call, **89.3% less time** than the original baseline.
- All eight native performance tests and the Node animation benchmark passed. Native JS scores: BunnyMark 23,589; PDGMark 56,793; CanvasMark 88,908. PDGMark and CanvasMark improved 23.1% and 19.2% over the preceding run.
- Rebuilt browser runtime: all 1,370 units / 9,346 assertions passed. All three Release browser benchmarks passed: BunnyMark 6,093; PDGMark 15,801; CanvasMark 42,151.
- Full browser validation exposed a FileManager test assumption about an untracked `misc` directory. The assertion now requires only the tracked directories packaged in all runtimes. All client/Node/browser units were rerun successfully. A transient macOS zero-screen result was resolved by keeping the display awake for GUI validation.

[Artifacts](../../artifacts/test-results/darwin/conversion-fixes/06-color/) include all native, Node, iOS and browser results.

## 7. Browser drawing destinations

The Emscripten drawing adapters reuse destination values during overload dispatch and conversion. Rect edges are converted in explicit order, with required fields checked before drawing; Quad conversion consumes the cached points array through Embind's existing four-Point array converter.

- Before the fix, the new tests measured two reads each of `right`/`bottom` in `drawImage`, `drawDrawing` and `drawText`, and two reads of Quad's `points` property. After the fix, each is read exactly once.
- All 1,372 browser units / 9,374 assertions passed, including pixel output, getter exceptions and malformed destination tests.
- All three Release browser benchmarks passed: BunnyMark 5,809; PDGMark 15,705; CanvasMark 41,956. Compared with the preceding run: −4.7%, −0.6%, −0.5%. These results do not establish an end-to-end speedup; regression tests directly establish the eliminated duplicate reads.
- Final full client validation: 1,436 tests / 10,027 assertions; Node: 1,288 tests / 9,029 assertions; all 16 CTest suites passed.
- Final eight native performance tests and the Node animation benchmark all passed. Native JS scores: BunnyMark 27,036; PDGMark 59,141; CanvasMark 94,256. Native code is unchanged by this browser-only fix; the variation from the preceding run illustrates whole-mark timing noise.

[Artifacts](../../artifacts/test-results/darwin/conversion-fixes/07-browser/) include the failing getter-count baseline, passing regression tests and final benchmark reports.

## Final comparisons

The focused native call benchmark compares against source commit `999cf6701`, before these seven conversion fixes:

| Call | Before (ns) | Final (ns) | Time reduction |
| --- | ---: | ---: | ---: |
| `setSize(Offset)` | 153.35 | 76.15 | 50.3% |
| `setMovement(Vector)` | 159.97 | 82.93 | 48.2% |
| `subsection(Rect)` | 601.37 | 178.52 | 70.3% |
| `fillColor(Color)` | 621.98 | 191.48 | 69.2% |
| `fillColor('yellowgreen')` | 527.15 | 54.37 | 89.7% |

Whole-mark comparisons against the older pinned `quick-2026-09-27-m5-max` baseline also include the earlier Release-build, loader and Point changes, plus runtime-version differences. They are cumulative comparisons rather than isolated effects of these seven fixes. Pinned files were not changed.

| Runtime / benchmark | Pinned | Final | Score change |
| --- | ---: | ---: | ---: |
| Native JS / BunnyMark | 6,394 | 27,036 | +322.8% |
| Native JS / PDGMark | 13,156 | 59,141 | +349.5% |
| Native JS / CanvasMark | 30,544 | 94,256 | +208.6% |
| Browser / BunnyMark | 4,037 | 5,809 | +43.9% |
| Browser / PDGMark | 8,362 | 15,705 | +87.8% |
| Browser / CanvasMark | 26,542 | 41,956 | +58.1% |
