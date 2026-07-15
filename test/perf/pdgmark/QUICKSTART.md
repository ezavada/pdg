# PDGMark Quick Start

Get a comprehensive 2D rendering performance score in under 2 minutes.

## Run the Test

```bash
./pdg test/perf/pdgmark/pdgmark.js
```

Wait for all 5 tests to complete (1-2 minutes). Press ESC when done.

## What You'll See

The test runs 5 sequential tests:
1. **Bitmap Rendering** - Sprites with transforms
2. **Line Drawing** - Lines, arcs, curves
3. **Alpha Blending** - Transparency and blend modes
4. **Polygon Fills** - Complex shapes with gradients
5. **Text Rendering** - Text with various styles

Each test adds objects until FPS drops below 60, then moves to the next test.

## Expected Output

```
=== PDG PDGMARK TEST ===

TEST 1 COMPLETE: Bitmap Rendering
Objects at 60 FPS: 2500
Score: 2500

TEST 2 COMPLETE: Line Drawing
Objects at 60 FPS: 1200
Score: 1440
...

COMPOSITE SCORE: 8450
```

## Save as Baseline

```bash
cp test/perf/pdgmark/pdgmark_results.json \
   test/perf/pdgmark/pdgmark_baseline.json
```

## After Making Optimizations

```bash
make pdg
./pdg test/perf/pdgmark/pdgmark.js
node test/perf/pdgmark/compare_results.js
```

## Interpreting the Composite Score

| Score Range | Performance Level |
|-------------|-------------------|
| 5,000-8,000 | Baseline (OpenGL 1.x immediate mode) |
| 15,000-24,000 | Good (3x improvement, Scenario 1 target) |
| 40,000-80,000 | Excellent (8-10x improvement, Scenario 2 target) |

## What to Optimize

If individual test scores are low:
- **Bitmap** → Improve sprite batching, texture binding
- **Drawing** → Optimize primitive rendering, state caching
- **Alpha** → Reduce blend mode overhead
- **Polygon** → Improve tessellation, gradient fills
- **Text** → Optimize font rendering, text batching

## Full Documentation

See `README.md` for complete details, troubleshooting, and technical information.

## Comparison with Bunnymark

- **Bunnymark** → Focused on sprite rendering (single test)
- **PDGMark** → Comprehensive 2D API coverage (5 tests)

Use both for complete performance analysis!

