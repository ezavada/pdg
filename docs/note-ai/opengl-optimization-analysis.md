# Renderer optimization status

Reviewed 2026-09-27. Use the [performance test guide](../../test/perf_tests/README.md)
for current workloads, pinned baselines, score interpretation and result files.
The [September investigation](PERFORMANCE_INVESTIGATION_2026-09.md) records
measurements and fixes, including uncapped Quick sampling, lazy polygon
tessellation, CanvasMark texture mapping and PNG ship decoding.

## Current implementation

Desktop rendering still includes immediate-mode OpenGL drawing. Images use
per-port cache keys and cached texture bindings; port/context lifecycle controls
cache invalidation. Text uses its own per-port cache. Repeated-texture shape
fills use UV-repeat rendering paths. Polygon tessellation is cached on each
Polygon and invalidated by point edits, while Attributes transforms reuse it.

Sources:

- [Image rendering](../../src/sys/image-opengl.cpp)
- [Port rendering](../../src/sys/port-renderer.cpp)
- [Image cache](../../src/sys/imagecache-opengl-v2.cpp)
- [Text cache](../../src/sys/textcache-opengl.cpp)
- [OpenGL state cache](../../src/sys/opengl-state-cache.cpp)

The benchmark runner measures native JavaScript/C++, browser JavaScript and
selected Node workloads. Its Quick rendering scores are fixed-load estimates;
they are not interchangeable with original ramp scores. Keep runtime, workload,
sampling settings and hardware comparable when assessing a change.

```sh
./test/perf --list
./test/perf bunnymark cpp-bunnymark pdgmark cpp-pdgmark canvasmark
./test/perf --web
./test/tools perf-runner perf-comparison perf-measurement
```

Correctness checks complement performance measurements:

```sh
./test/unit offscreen
./test/ui --web --no-build --automated shape-fill compositing
```

The offscreen and shape-fill checks cover polygon-cache reuse and CanvasMark
texture/ship rendering. Compositing covers blend modes and stroke opacity.
Inspect visual output as well as timing when changing rendering paths.

## Future work

Sprite batching, a glyph atlas, retained tile buffers and a broader render
queue/shader/instancing design remain possible projects. They need measured
bottlenecks, explicit platform requirements and separate acceptance criteria.
Performance multipliers and delivery dates should come from prototypes rather
than architectural estimates.

Broad GL state-setup reductions require platform-specific experiments; previous
macOS measurements did not justify enabling that approach. Preserve a comparable
baseline and validate clipping, transforms, opacity, blend modes, texture state,
context changes and resource teardown before accepting an optimization. Current
product priorities are in the [feature worklist](PDG_FEATURE_WORKLIST.md).
