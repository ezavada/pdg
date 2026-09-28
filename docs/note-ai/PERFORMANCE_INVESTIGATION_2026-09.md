# Performance investigation — 27 September 2026

Measurements below are from the native GUI build on an Apple M5 Max. Historical
October 2025 baselines were measured on an M2 Pro, so they are context rather
than a controlled comparison. Detailed logs and JSON are under
`artifacts/test-results/darwin/perf-investigation/`; the earlier full ramp suite
is under `artifacts/test-results/darwin/perf-ramp-comparison/`.

## Alpha and Polygon

The original C++ ramp reproduced the regression: alpha scored 7,734 versus the
historical 36,660, and Polygon scored 4,125 versus 6,900. The short measurement
method was not the cause.

The general tessellation introduced in `91d654ba0` constructs and destroys a
libtess2 tessellator for every filled contour, including small rectangles.
Controlled diagnostic builds held the objects and random seed fixed:

| Diagnostic | Alpha mean draw time | Polygon mean draw time |
| --- | ---: | ---: |
| Current renderer before fix | 106.57 ms | 37.42 ms |
| Force normal blending | 98.96 ms | 37.68 ms |
| Replace tessellation with an unchecked triangle fan | 19.59 ms | 9.84 ms |
| Revert joined strokes only | 107.58 ms | 36.73 ms |
| Omit CPU clipping only | 107.81 ms | 37.88 ms |
| Production convex fast path | **20.41 ms** | **9.98 ms** |

The unchecked fan was only an isolated diagnostic; it is incorrect for concave
and crossing contours. The production fix checks that every other vertex lies
strictly on the same side of every edge before using a fan for contours of up
to eight vertices. All other contours retain libtess2's even-odd fill. Checking
only consecutive turns is insufficient because a pentagram can pass that test.
Blending, clipping and antialiased strokes remain intact. Correctly honoring
blend modes since `ab2ba35bb` also accounts for some historical alpha difference.
The safe fix reduces alpha draw cost by about 81% and Polygon by 73%. At the
default load Polygon then hits 60 FPS; a 4× load measured 37.08 FPS and a
QuickPDGMark Polygon score of 17,056. Its alpha score was 44,027 at that load.
These are Quick scores, not a new original-ramp baseline.

## C++ BunnyMark synchronization

Both native window contexts had a swap interval of one. At the default 1.5× load
(47,250 bunnies), QuickBunnyMark measured about 60 FPS. At 2.5× (78,750 bunnies),
it measured 37.96 FPS and estimated 49,827. The original ramp scored 54,000.

At a smaller 15,750-bunny load, disabling synchronization in the benchmark
context alone raised throughput to 120 FPS; disabling it in both contexts raised
it to 171.61 FPS. This confirms a presentation cap. No engine synchronization
policy was changed. Use `--load-factor 2.5` to avoid the ceiling on this machine.

The remaining difference also reflects measurement semantics. With both contexts
unsynchronized, the heavy-load draw callback averaged 24.71 ms (about 53,106
bunnies at 60 FPS), while complete frame intervals estimated 51,692. Original
BunnyMark records peak good draw-callback capacity; QuickBunnyMark averages full
frame intervals, including presentation and scheduling.

## CanvasMark calibration and cube texture mapping

Historical CanvasMark scores encode elapsed ramp time, including a 101-frame
scene title, rather than object counts. The native ramp runs near 40 FPS and
stops after ten cumulative intervals longer than 33.33 ms. Inferring loads at
60 updates/sec was inaccurate. Asteroids, bullets and Arena actors also have
changing populations and lifetimes. Plasma cell count grows quadratically with
grid width, while its original score grows with width/time.

`--calibrate` observes the original ramp without changing its workload or stop
rule. It records terminal populations and the last ten frame intervals. The
median interval per item yields a reference throughput. QuickCanvasMark uses
that measured reference, and plasma converts equivalent cell count back to grid
width when calculating its score. Raw samples are kept in `calibration.json`.
Random actor age/type mixes and cumulative glitch timing still limit accuracy;
these remain approximations of original scores, especially across platforms.

The cube adapter previously used a textured Polygon, whose UVs follow its
axis-aligned bounds. Rotating/skewing a face therefore moved texture corners
away from its vertices. It now draws textured quad faces with `drawImage` and
an explicit Quad, preserving the canvas transform, alpha and K3D corner order.
Untextured faces keep their original rendering path.

The fresh original ramp with both rendering fixes scored 28,943 in 280.8 seconds.
Its cube subtest scored 4,839, compared with 2,663 in the earlier calibration run.
The fresh measured profile is the reference for these Quick comparisons:

| Subtest | Original ramp | Quick 1.5× | Difference | Quick 2× | Difference |
| --- | ---: | ---: | ---: | ---: | ---: |
| asteroids-bitmaps | 1,209 | 1,342 | +11.0% | 1,353 | +11.9% |
| asteroids-vectors | 2,262 | 2,477 | +9.5% | 2,520 | +11.4% |
| asteroids-mixed | 2,489 | 2,876 | +15.5% | 2,902 | +16.6% |
| asteroids-effects | 1,615 | 1,632 | +1.1% | 1,622 | +0.4% |
| arena | 16,152 | 16,142 | -0.1% | 16,357 | +1.3% |
| plasma | 377 | 379 | +0.5% | 376 | -0.3% |
| 3d | 4,839 | 5,379 | +11.2% | 5,442 | +12.5% |
| **Total** | **28,943** | **30,227** | **+4.4%** | **30,572** | **+5.6%** |

The total changes only 1.1% between the two Quick loads. Individual subtests
still differ from the original ramp; mixed actors are the largest discrepancy
at the default load. Do not interpret the close composite as exact equivalence.

## Naming and verification

Short runs use `--quick` and report QuickPDGMark, QuickCanvasMark or QuickBunnyMark.
The shared C++/JavaScript helpers and browser query parameter use `quick` too.
Reports retain stable selection IDs and record `mode: "quick"`, `testName` and
language.
Original ramp names and the separate UI framework's `--automated` flag remain.

Geometry tests compare filled area and coverage against libtess2 for convex,
concave, crossing, collinear and reversed contours. Native and WASM pixel tests
check all four texture corners on square, skewed, rotated and reflected faces at
two alpha values (32 checks). The complete browser shape-fill regression passed.
Sampler tests cover excluded warmup, weighted scoring, incomplete/stale reports,
all seven CanvasMark transitions, measured calibration and plasma scoring.

All eight native Quick tests passed in 91.6 seconds. The subsequent browser
performance run is excluded: the user observed forced plugin sign-in tabs
stealing focus. CanvasMark produced an in-page result but the outer runner timed
out. Its raw artifacts are retained with a validity notice; none of those scores
are used in the comparisons above. Native calibration is unaffected.

## Tessellation caching

At the time of the initial investigation there was no tessellation cache:
`Polygon` cached only bounds. Filled draws computed triangles again, and
`drawPolygon` constructed temporary fitted and transformed polygons. The convex fast path reduces this repeated work but does
not eliminate it. A future cache should retain tessellation on the source polygon,
invalidate it for point edits (including `setPoint`, not just add/remove), and
transform cached triangles for affine drawing transforms. Caching only the
renderer temporary would not survive between draws. Both PDGMark implementations
also construct a new Polygon on every draw, so they would need to retain geometry
to benefit from an object cache.

The native texture negative control confirmed that the previous adapter fails the
same corner test; the corrected adapter passes all 32 corner samples.

## Follow-up: uncapped Quick mode

After committing the investigation as `8f984bf24`, Quick mode gained an internal
process override, `PDG_PERF_UNCAPPED=1`. It bypasses the engine redraw timer and
sets swap interval zero in every native desktop context, including windows
created before the benchmark starts. Ordinary `setTargetFPS` semantics are
unchanged. The browser loop uses MessageChannel scheduling; the performance
runner disables Chrome frame limiting, GPU vsync and extensions. Hidden tabs
invalidate a sample. Browser cleanup now waits for process exit rather than
inherited pipe closure, preventing completed tests from hanging during shutdown.

QuickPDGMark Polygon now uses 4× the historical reference load by default:
18,400 C++ objects and 3,800 JavaScript objects. `--load-factor` still scales all
loads proportionally, and the original score references are unchanged.

The native pacing check kept a configured 5 FPS target: ordinary mode drew three
frames in half a second, then Quick mode drew 938 frames in each of two windows
in the next half second. A separate C++ probe verified swap interval zero in both
contexts and measured about 178 FPS at 15,750 bunnies. The light browser check
measured 637 FPS. The default C++ Polygon run measured 37.39 FPS with 18,400
objects and scored 17,198. These checks establish that the former software limits
are removed; driver and compositor policies can still influence presentation.

Follow-up reports are under `artifacts/test-results/darwin/perf-uncapped/`.

## Follow-up: lazy polygon tessellation cache

The uncapped Quick work was committed as `04b1e4eb4` before this change.
`Polygon` now owns cached even-odd triangles and a dirty flag. Its first
`tessellate()` or filled draw computes them; point additions, removals, edits,
spline additions, clearing, and in-place coordinate transforms invalidate them.
Move construction/assignment transfer the cache and invalidate the moved-from
object. The public `tessellate()` result remains a value copy, while rendering
reads the cache by reference.

`drawPolygon` now tessellates the source polygon and transforms the resulting
triangles for solid, linear-gradient, radial-gradient, and textured fills.
Texture fitting also uses the source cache. Attribute transforms do not
invalidate it. The renderer no longer constructs fitted and transformed Polygon
copies for each draw. Even-odd fill coverage, clipping and local texture UVs are
preserved.

The same native Quick workloads and sampling settings produced:

| Benchmark | Previous uncapped Quick | With cache/renderer changes | Change |
|---|---:|---:|---:|
| QuickBunnyMark JavaScript | 7,033 | 6,394 | -9.1% |
| QuickBunnyMark C++ | 47,208 | 47,214 | +0.0% |
| QuickPDGMark JavaScript | 13,316 | 13,156 | -1.2% |
| QuickPDGMark C++ | 133,527 | 137,986 | +3.3% |
| QuickCanvasMark | 30,766 | 30,544 | -0.7% |

| QuickPDGMark subtest | Previous score | New score | Change | Previous FPS | New FPS |
|---|---:|---:|---:|---:|---:|
| C++ Polygon (18,400 objects) | 17,198 | 19,974 | +16.1% | 37.39 | 43.42 |
| C++ Alpha (42,300 objects) | 41,478 | 42,658 | +2.8% | 45.26 | 46.54 |
| JavaScript Polygon (3,800 objects) | 1,899 | 2,137 | +12.5% | 19.99 | 22.50 |
| JavaScript Alpha (3,000 objects) | 3,391 | 3,290 | -3.0% | 52.18 | 50.62 |

All eight native Quick tests passed. The benchmark implementations still create
fresh Polygon objects each frame, preserving comparability: these polygon gains
reflect the renderer integration, not repeated hits on retained polygon caches.
Alpha uses rectangles and ellipses, so its workload does not gain retained
polygon caching. Single short samples have timing/random-workload variation;
the small alpha changes and unrelated JavaScript BunnyMark change should not be
attributed to the cache without controlled repetitions.

Validation passed for native/WASM builds, headless polygon compilation, C++
cache/invalidation/geometry tests, and 55 edited/reused-versus-fresh pixel
comparisons in each of native and browser rendering. Existing browser texture,
gradient, clipping and CanvasMark corner checks also passed. Reports and the
complete native/browser comparison are under
`artifacts/test-results/darwin/perf-tessellation-cache/`.

All three browser Quick tests also passed: QuickBunnyMark 4,074 → 4,037 (-0.9%),
QuickPDGMark 8,049 → 8,362 (+3.9%), and QuickCanvasMark 24,925 → 26,516 (+6.4%).
Browser Polygon rose 991 → 1,265 (+27.6%; 10.43 → 13.31 FPS), while Alpha was
2,395 → 2,420 (+1.0%). These used the same isolated-tab runner and unchanged
loads as the preceding uncapped browser run.

## Follow-up: striped ships in browser CanvasMark

The tessellation work was committed as `096c00f6b` before this fix. The player
and enemy ship sprite sheets are palette PNGs with `tRNS` transparency. The
portable decoder requested palette-to-RGB and transparency-to-alpha expansion,
but allocated rows and chose GL_RGB/GL_RGBA from the original PNG color type.
For these images libpng wrote four-byte RGBA pixels into three-byte RGB rows,
corrupting rows and overrunning the pixel buffer. This caused colored stripes
and missing transparency; it was not caused by polygon tessellation.

Browser/WASM uses `src/sys/image-png.cpp`. The native macOS client instead uses
AppKit's `NSBitmapImageRep` in `src/sys/macosx/platform-image-macosx.mm`, so those
runs did not exercise the defective decoder. Windows and Linux builds using the
portable decoder were also affected by these PNG formats. The asteroid sheets
already contain RGBA pixels and did not trigger this palette-expansion bug.

The decoder now updates libpng's transformed image information before selecting
channel format, row pitch and buffer size. Error paths free partial allocations
and leave the output empty. The earlier browser-specific `retainData()`
workaround has been removed: the buffer corruption originated during decoding,
not from a separate texture-upload allocator.

A standalone CTest target exercises the portable decoder on macOS as well as
other platforms. Its palette/transparency case failed before the fix and passes
afterward, along with RGB, RGBA, low-bit grayscale, grayscale-alpha, 16-bit,
interlaced and truncated-input cases. An AddressSanitizer run passed too.
Independent RGBA reference samples from the first, middle and final frames of
both ship sheets check 72 decoded and 72 rendered pixels in native and browser
rendering. The old WASM build fails this check; the rebuilt browser passes it,
along with the existing shape-fill, polygon cache and cube texture regressions.

Artifacts, including the corrected browser ship frames, are under
`artifacts/test-results/darwin/canvasmark-ship/`.

Browser QuickCanvasMark completed all seven subtests without the retention
workaround, scoring 26,542 versus the preceding 26,516 (+0.1%).
