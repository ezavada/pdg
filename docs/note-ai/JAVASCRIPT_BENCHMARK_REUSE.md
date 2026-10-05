# JavaScript benchmark resource reuse

September 28, 2026, macOS arm64. These changes follow the
[binding conversion fixes](JAVASCRIPT_CONVERSION_FIXES.md). Each BunnyMark fix
is tested, measured and committed separately. The native embedded runtime and
browser WASM runtime are Release builds; benchmark JavaScript is loaded from
the working tree. The pinned baseline files remain unchanged.

## 1. Reuse BunnyMark draw arguments

BunnyMark now creates one scratch Point and one native-backed Attributes object
for all bunny draws. The Point coordinates change before each synchronous draw;
the Attributes remain constant. Completion releases the shared native object,
including in the browser. Comments explain why avoiding per-sprite allocations
matters. Background and HUD work are unchanged.

The regression test executes the actual benchmark with deterministic input. It
checks motion, resized bounce limits, shared argument identity, resource lifetime
and both quick and manual completion paths. It runs through
`./test/tools perf-runner`.

Validation after this fix:

- Client: 1,436 tests / 10,027 assertions; all 16 CTest suites passed.
- Node: 1,288 tests / 9,031 assertions passed.
- Browser: 1,372 tests / 9,355 assertions passed.
- Performance tooling and native/browser BunnyMark runs passed.

Both runs use 9,600 bunnies, one second of warm-up and three seconds of sampling.
These are individual measurements, subject to scheduling and workload variation.

| Runtime | Before mean frame time | Reused arguments | Before score | After score |
| --- | ---: | ---: | ---: | ---: |
| Native JavaScript | 6.065 ms | 5.560 ms | 26,381 | 28,776 |
| Browser | 28.467 ms | 25.370 ms | 5,621 | 6,307 |

Frame time fell 8.3% and 10.9%, respectively. The deterministic tests establish
that per-bunny draw argument allocations were eliminated independently of timing.

[Before artifacts](../../artifacts/test-results/darwin/benchmark-js-reuse/before/)
and [allocation-fix validation](../../artifacts/test-results/darwin/benchmark-js-reuse/01-allocations/)
contain the reports and logs.

## 2. Read BunnyMark dimensions once per frame

The draw handler now reads image dimensions and computes the shared bounce
limits before entering the bunny loop. Each update receives two numeric limits.
This removes repeated image getter calls and rectangle-width/height calculations
while refreshing dimensions every frame for resizing. Comments explain the cost
of repeated JavaScript-to-native calls.

At 9,600 bunnies, image-size getter calls fall from 19,200 to 2 per rendered
frame. The new getter-count assertion failed before this fix and passes after it.
Regression coverage also changes both the image and window dimensions between
frames and checks the resulting bounce positions.

Validation after this fix:

- Client: 1,436 tests / 10,027 assertions; all 16 CTest suites passed.
- Node: 1,288 tests / 9,029 assertions passed.
- Browser: 1,372 tests / 9,360 assertions passed.
- Performance tooling and native/browser BunnyMark runs passed.

| Runtime | After allocation fix | After getter fix | Previous score | Final score |
| --- | ---: | ---: | ---: | ---: |
| Native JavaScript | 5.560 ms | 5.401 ms | 28,776 | 29,626 |
| Browser | 25.370 ms | 25.403 ms | 6,307 | 6,299 |

The incremental native frame-time reduction was 2.9%. The browser measurement
was effectively unchanged (+0.1% frame time); this run does not establish a
browser speedup from getter hoisting alone. Relative to the fresh measurements
before both fixes, native/browser frame times fell 11.0%/10.8% and scores rose
12.3%/12.1%.

The final scores exceed the older pinned native/browser scores (6,394/4,037) by
363.3%/56.0%. Those cumulative comparisons include the earlier runtime, loader
and binding changes, not just these two JavaScript edits.

[Getter-fix validation](../../artifacts/test-results/darwin/benchmark-js-reuse/02-getters/)
contains the full reports and logs.

## PDGMark audit

The original JavaScript PDGMark had similar costs in all five tests. This table
records the audit; the implementation and measured results are tracked below.

| Draw path | Repeated work | Candidate change |
| --- | --- | --- |
| [Bitmap](../../test/perf_tests/pdgmark/pdgmark.js) | Two image-size getters, two Points and one Attributes per object per frame | Cache shared image dimensions and each object's fixed position/center; retain Attributes and replace the transform each frame. |
| [Drawing](../../test/perf_tests/pdgmark/pdgmark.js) | Attributes with unchanged line styling; temporary Points; a new native Spline and four `addPoint` calls per spline draw | Retain styled Attributes and Points; create each Spline once and update its two moving control points with `setPoint`. |
| [Alpha](../../test/perf_tests/pdgmark/pdgmark.js) | Attributes with unchanged color, opacity and blend mode; center Points and rectangles | Retain geometry and styled Attributes; replace only the rotation transform each frame. |
| [Polygon](../../test/perf_tests/pdgmark/pdgmark.js) | Native Polygon, vertex Points, Attributes, outline Color and gradient endpoints recreated each frame | Retain the polygon and styles; rotate through Attributes. The shape never warps, so vertices and tessellation can remain unchanged. |
| [Text](../../test/perf_tests/pdgmark/pdgmark.js) | Two identical position Points and Attributes with unchanged text styling | Retain position and styled Attributes; replace only the rotation transform each frame. |

The [background and HUD](../../test/perf_tests/pdgmark/pdgmark.js) also
allocated Attributes, Colors and Points each frame. This was constant overhead,
so the per-object paths were the first candidates.

Two implementation requirements governed these changes:

- `Attributes.rotation()` and `scale()`
  [compose with the current transform](../../src/sys/attributes.cpp#L469).
  Reusing Attributes without resetting the matrix would accumulate rotations
  and scales. Reset with `setTransform(identity)` before applying the original
  operations, replace the complete transform, or use AnimatedAttributes absolute
  setters. Verify equivalence over many frames.
- Retained native Attributes, Splines and Polygons need explicit browser
  disposal when [switching tests](../../test/perf_tests/pdgmark/pdgmark.js)
  and when finishing or aborting. Clearing `testObjects` alone is insufficient
  for Embind ownership.

## C++ PDGMark comparison

The original [C++ benchmark](../../test/perf_tests/cpp-pdgmark/pdgmark.cpp)
repeated most of the same work, although the costs differed:

| Pattern | Original C++ behavior and significance |
| --- | --- |
| Bitmap dimensions | `BitmapObject::draw` calls both image getters every frame and recomputes the fixed center. The base getters return stored fields; there is no JavaScript/native conversion. Caching can remove work, but the expected benefit is smaller than in JavaScript. |
| Attributes and static styling | All five draw methods construct local Attributes and reapply unchanged styles. Retaining initialized Attributes can avoid that work. Rotation and scale still need a fresh transform each frame. |
| Points, Rects and Colors | These are small local values, without heap allocation or script wrappers in these draw paths. Replacing every temporary with a persistent member is not automatically beneficial. |
| Splines | Each spline draw constructs an empty Spline and calls `addPoint` four times. Its `std::vector<Point>` repeatedly allocates and frees storage. Retaining the Spline and updating its two moving points is a concrete allocation improvement. |
| Polygons | Originally each draw constructed an empty Polygon and added 3–7 vertices. Only the rotation angle changes. Retaining the original polygon and rotating through Attributes avoids both vertex-vector growth and repeated tessellation. |
| Background and HUD | The handler reconstructs styled Attributes each frame and formats the overlay text. The Attributes and formatting buffer are local values; this is constant per-frame work rather than per-object allocation. |

The strongest shared allocation candidates are Spline and Polygon vertex
storage. Both versions also repeat style setup. Any corresponding optimization
should be applied and measured in both benchmarks while preserving the rendered
animation. Polygon retention intentionally removes repeated tessellation from
the workload. C++ members have automatic destruction;
the existing `cleanupTestObjects()` deletes objects between stages, unlike
JavaScript's need for explicit Embind disposal. These are source-inspection
findings; measured results follow.

## PDGMark implementation: retained polygons

Both versions create each regular polygon once and set its absolute angle with
`AnimatedAttributes.setRotation()` each frame. This also avoids passing a
nine-element matrix through the JavaScript bindings on every draw. The renderer
samples gradient colors at transformed
vertices using screen-space endpoints, so the original horizontal gradient is
preserved. A filled polygon's tessellation is built during warm-up and reused.
Per-frame contour transformation and renderer scratch allocations still occur.

The JavaScript benchmark now disposes retained objects between stages and on
normal completion or Escape, and ignores draw events after completion. C++
objects own their geometry and Attributes as members; existing stage cleanup
destroys them, including the quick-mode Escape path.

The deterministic benchmark test checks all 3–7-sided polygons with solid and
gradient fills over 120 frames, comparing transformed coordinates to the old
formula. It checks unchanged gradient endpoints, no vertex edits or draw-argument
allocations, stable object identities, and stage/completion/abort disposal.

Comparisons use fresh Release measurements on the same Apple M5 Max, with WASM
`-O3`, unchanged fixed loads, one second warm-up and three seconds sampling per
stage. Benchmarks run serially after builds and unit tests finish. Timings are
individual runs with random scenes and scheduling variation; the allocation
checks establish resource reuse independently of timing. Pinned baselines are
left unchanged and include additional earlier runtime/binding differences.

| Polygon mean frame time | Before | Retained geometry |
| --- | ---: | ---: |
| Native JavaScript (3,800 objects) | 11.417 ms | 5.612 ms |
| Native C++ (18,400 objects) | 23.227 ms | 21.715 ms |
| Browser (3,800 objects) | 37.612 ms | 36.629 ms |

Native JavaScript improves 50.8%; C++ improves 6.5%. The browser difference is
only 2.6%, too small for a strong speedup claim from one run. An intermediate
implementation that reset a matrix before composing rotation measured 41.259 ms
in the browser; using the absolute-angle API avoids that conversion overhead.

Validation: 1,436 native unit tests, 1,288 Node unit tests, 1,372 browser tests, all 16 CTest
suites, the performance tooling checks and all three affected PDGMark runs passed.
[Fresh baseline](../../artifacts/test-results/darwin/pdgmark-reuse/before/) and
[polygon validation](../../artifacts/test-results/darwin/pdgmark-reuse/01-polygons-animated/)
contain full reports and logs.

## PDGMark implementation: retained drawing resources

Both versions retain styled Attributes for lines, arcs, splines and ellipses.
Each spline is created with four points once; each draw updates just its two
moving control points. Unlike polygons, these splines really do change shape,
so their bounds and curve samples still need to be recomputed. JavaScript also
retains all Point arguments; C++ uses small stack values for moving endpoints
and retains the fixed center. Spline storage is released at stage cleanup.

The deterministic test exercises all four drawing types over 120 frames,
checking the old coordinate formulas, radii, arc angles and styling. It checks
that only the two middle spline points change, no new draw arguments are
allocated, and retained native resources are disposed.

| Drawing mean frame time | After polygon fix | After drawing fix |
| --- | ---: | ---: |
| Native JavaScript | 5.732 ms | 4.176 ms |
| Native C++ | 20.514 ms | 20.575 ms |
| Browser | 24.887 ms | 22.205 ms |

Native JavaScript improves 27.1% and browser improves 10.8%; C++ is effectively
unchanged (+0.3%). All 1,436 client, 1,288 Node and 1,372 browser tests, all 16
CTest suites, tooling checks and the three PDGMark runs passed.
[Drawing validation](../../artifacts/test-results/darwin/pdgmark-reuse/02-drawing/).

## PDGMark implementation: retained bitmap state

Both versions read the shared, fixed image dimensions once per batch when
creating objects. Each object retains its position and Attributes;
drawing replaces the absolute transform. There are no per-frame image getters,
new Attributes, or JavaScript Point arguments.

The transform remains `R(center) * S(origin)`. JavaScript uses AnimatedAttributes
with pivot `center / scale` and location `center - pivot`, setting only the
absolute rotation per draw. C++ retains an ordinary Attributes and fixed center,
resetting and composing its matrix with native methods. This avoids repeated
animated-matrix evaluation during native image drawing. The regression test compares all
four image corners against the original transform over 120 frames at four
different scales/positions, verifies argument identity and disposal, and checks
one width/height read per batch with no further reads during drawing.

Isolated measurements of the selected implementations were 3.427 ms for native
JavaScript and 14.904 ms for browser (`03-bitmap`), versus 5.323/13.686 ms after
the drawing fix. Native JavaScript improves 35.6%; browser is 8.9% slower in this
sample. C++ with ordinary Attributes measured 16.572 ms (`03-bitmap-matrix`)
versus 16.679 ms, effectively unchanged. JavaScript matrix-array submission
measured 24.863 ms in browser, so the final JavaScript code uses scalar angle
updates. These paths intentionally differ to suit their binding costs.

All unit/tooling suites and three performance runs passed on the combined final
source in [bitmap validation](../../artifacts/test-results/darwin/pdgmark-reuse/03-bitmap-final/).
Those final timings were affected by an unrelated 18-job Godot build: unchanged
sections also slowed substantially. They establish successful execution, not
an isolated performance comparison. The earlier measurements and exploratory
variants remain under `pdgmark-reuse/03-bitmap*` for provenance.

## PDGMark implementation: retained alpha shapes

Both versions retain the rectangle/ellipse center and fixed fill color, opacity
and blend mode. Drawing updates the absolute rotation only. JavaScript uses
AnimatedAttributes for scalar updates; C++ retains ordinary Attributes so its
matrix is prepared once before rendering. The deterministic test covers both
shapes and all six blend modes over 120 frames, checking transformed corners,
style, argument identity, allocation counts and disposal.

After this change, alpha mean frame times were 3.635 ms native JavaScript,
22.116 ms C++, and 10.334 ms browser. Earlier isolated bitmap-fix runs measured
4.539/22.238/10.623 ms respectively: approximately 20% better in native
JavaScript, with small C++/browser differences. System load fell during this
validation; do not compare against the overloaded `03-bitmap-final` run.
All 1,436 client, 1,288 Node and 1,372 browser tests, all 16 CTest suites, tooling
and all three PDGMark runs passed.
[Alpha validation](../../artifacts/test-results/darwin/pdgmark-reuse/04-alpha/).

## PDGMark implementation: retained text state

Both versions retain the fixed draw position, size, font style and fill color;
only rotation changes at draw time. JavaScript uses AnimatedAttributes and C++
uses ordinary Attributes as in the alpha test. The benchmark still draws every
text object every frame; this does not cache rendered text or reduce font work.
Regression coverage checks all three font styles over 120 frames, including
the unchanged text origin, rotation of nearby points, resource reuse and cleanup.

All 1,436 client, 1,288 Node and 1,372 browser tests, all 16 CTest suites, tooling
and all three PDGMark runs passed. Text frame times were 27.944 ms native
JavaScript, 28.326 ms C++, and 441.543 ms browser. Unchanged sections also slowed
in this run, so these measurements do not establish a text speedup or isolate
the cost of this change. Draw-argument reuse is verified deterministically.
[Text validation](../../artifacts/test-results/darwin/pdgmark-reuse/05-text/).

## PDGMark implementation: retained background and HUD

Both versions initialize background and HUD Attributes once, cache the stage
title, and reformat object-count/capacity labels only when those counts change.
JavaScript retains all eight HUD Points. C++ keeps its small stack Points and
format buffer. FPS and frame-time labels still refresh and draw every frame;
the background still reads current port bounds so window resizing works.

JavaScript releases the shared Attributes and test image on completion/Escape,
in addition to the current stage's objects. A queued manual stabilization timer
cannot restart the benchmark after Escape. Integration tests drive all five
stages in both modes, checking HUD layout, bounds changes, argument reuse,
labels and complete native-resource cleanup, including late timers/events.

All 1,436 client, 1,288 Node and 1,372 browser tests, all 16 CTest suites, tooling
checks and the three PDGMark runs passed. Composite scores were 75,968 native
JavaScript, 126,990 C++, and 16,850 browser. These individual runs still showed
system-load variation; the alternating original/updated comparison below is the
final performance comparison rather than attributing these changes to the HUD.
[HUD validation](../../artifacts/test-results/darwin/pdgmark-reuse/06-hud/).

## Final alternating comparison

To reduce sensitivity to the changing machine load, reran the original
`f67005dc8` benchmark and the completed `bbaaf9db6` implementation in the order
**original, updated, updated, original**, separately for native JavaScript,
C++ and browser: 12 successful runs. The original C++ benchmark was compiled
separately with the same Release flags and linked to the same engine libraries;
both JavaScript versions used the same native/WASM Release runtimes. No engine
or binding code changed in this series. Browser uses `-O3`.

All loads and sampling settings match: one second warm-up and three seconds
sampling per stage, with the existing 1.5x loads and 4x polygon load. Values below
are arithmetic means of the two runs per version. Random scenes and other
desktop activity still introduce variation; these are measured comparisons,
not statistical guarantees. The artifacts record source/binary hashes and
system load for reproducibility.

| Runtime | Original mean score | Updated mean score | Change |
| --- | ---: | ---: | ---: |
| Native JavaScript | 45,933.5 | 69,229.5 | +50.7% |
| Native C++ | 129,874.5 | 134,664.0 | +3.7% |
| Browser JavaScript | 14,689.0 | 15,816.5 | +7.7% |

Mean frame times (lower is better):

| Stage | Native JS before → after | C++ before → after | Browser before → after |
| --- | ---: | ---: | ---: |
| Bitmap | 5.403 → 4.102 ms | 17.095 → 16.658 ms | 18.759 → 17.426 ms |
| Drawing | 7.251 → 4.612 ms | 21.515 → 21.534 ms | 28.579 → 23.697 ms |
| Alpha | 5.256 → 3.895 ms | 23.113 → 22.805 ms | 11.961 → 11.630 ms |
| Polygon | 12.711 → 6.115 ms | 26.236 → 22.420 ms | 43.330 → 41.367 ms |
| Text | 26.746 → 27.587 ms | 28.997 → 28.440 ms | 412.862 → 414.263 ms |

Polygon frame time falls 51.9% in native JavaScript and 14.5% in C++. Native
JavaScript drawing improves 36.4%; browser drawing improves 17.1%. Text shows
no meaningful improvement: retaining its arguments does not remove glyph
rendering/readback costs. Small differences in other sections should be read
in light of the remaining run-to-run variation. Browser memory remains a
64 MiB allocated WASM heap in all four comparison runs.

[Comparison reports](../../artifacts/test-results/darwin/pdgmark-reuse/paired/),
[summary](../../artifacts/test-results/darwin/pdgmark-reuse/paired-summary.json),
[metadata](../../artifacts/test-results/darwin/pdgmark-reuse/paired-metadata.json),
and the self-contained `compare.js` / `build-before.py` drivers in the same
artifact directory preserve the measurements. The pinned baseline remains
unchanged; unlike these paired comparisons, it also predates the earlier
runtime, binding and WASM compiler improvements.
