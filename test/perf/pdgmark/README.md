# PDG PDGMark Performance Test

A comprehensive 2D rendering benchmark for PDG.

## What It Tests

PDGMark measures five different aspects of 2D rendering performance:

1. **Bitmap Rendering** - Sprite/image drawing with transforms (rotation, scaling)
2. **Line Drawing** - Lines, arcs, splines, curves, and primitive shapes
3. **Alpha Blending** - Transparency rendering with various blend modes
4. **Polygon Fills** - Complex polygon shapes with solid fills and gradients
5. **Text Rendering** - Text drawing with various fonts, sizes, and styles

Each test progressively adds complexity until the frame rate drops below 60 FPS, measuring the rendering capabilities across different types of 2D operations.

## How It Works

### Test Methodology

1. **Sequential Execution**: Tests run one at a time, each to completion
2. **Progressive Complexity**: Objects are added in batches every 2 seconds
3. **60 FPS Threshold**: Each test stops when frame rate drops below 60 FPS
4. **Weighted Scoring**: Each test has a complexity weight:
   - Bitmap: 1.0x (baseline)
   - Drawing: 1.2x (more complex primitives)
   - Alpha: 1.3x (blending overhead)
   - Polygon: 1.5x (tessellation + fills)
   - Text: 1.4x (font rendering)
5. **Composite Score**: Sum of (objects_at_60fps × weight) across all tests

### What Each Test Measures

**Bitmap Rendering**
- `port.drawImage()` performance
- Transform overhead (rotation, scaling)
- Texture binding efficiency
- Multiple sprites with varying transforms

**Line Drawing**
- `port.drawLine()` - Line rendering
- `port.drawArc()` - Arc and curve rendering
- `port.drawSpline()` - Spline path rendering
- `port.drawEllipse()` - Circle/ellipse rendering
- Primitive shape rendering efficiency

**Alpha Blending**
- `Attributes().fillOpacity()` - Alpha channel performance
- `Attributes().blendMode()` - Blend mode overhead
- Multiple blend modes: Normal, Additive, Multiply, Screen, Darken, Lighten
- Overlapping transparent objects

**Polygon Fills**
- `port.drawPolygon()` - Complex polygon rendering
- `Attributes().fillGradient()` - Linear gradients
- `Attributes().fillRadialGradient()` - Radial gradients
- Polygons with 3-7 sides
- Tessellation and fill performance

**Text Rendering**
- `port.drawText()` - Text drawing performance
- Multiple font sizes (12-36pt)
- Text styles: Plain, Bold, Italic
- Text with transforms (rotation)
- Font rendering and caching

## Running the Test

**Standard benchmark run**:
```bash
./pdg test/perf/pdgmark/pdgmark.js
```

The test will automatically:
1. Run all 5 tests sequentially
2. Add objects until 60 FPS threshold is reached
3. Print results for each test
4. Save complete results to JSON
5. Quit when all tests are done

**Manual abort**:
- Press **ESC** to quit at any time
- Results for completed tests will be saved

## Results

Results are saved to `test/perf/pdgmark/pdgmark_results.json`:

```json
{
  "testName": "PDG PDGMark",
  "timestamp": "2025-10-17T...",
  "totalDurationSeconds": 45.2,
  "compositeScore": 8450,
  "tests": {
    "bitmap": {
      "testName": "bitmap",
      "testTitle": "Bitmap Rendering",
      "weight": 1.0,
      "objectsAt60FPS": 2500,
      "score": 2500,
      "durationSeconds": 8.5,
      "totalFrames": 255,
      "frameTime": {
        "meanMs": 28.5,
        "minMs": 12.3,
        "maxMs": 42.1,
        "percentile95Ms": 35.2,
        "percentile99Ms": 38.7
      },
      "averageFPS": 35.1
    },
    "drawing": { ... },
    "alpha": { ... },
    "polygon": { ... },
    "text": { ... }
  }
}
```

## Interpreting Results

### Composite Score

The **composite score** is the primary metric - higher is better. It represents the overall 2D rendering performance weighted by complexity.

### Per-Test Scores

Each test contributes to the composite score:
- **Score** = Objects at 60 FPS × Weight
- Higher scores indicate better performance for that rendering type

### Frame Time Statistics

- **Mean Frame Time**: Average rendering time per frame
- **95th/99th Percentile**: Consistency metrics (lower is better)
- **Min/Max**: Range of frame times during test

### Reference Scores

Approximate scores on modern hardware (varies by GPU):

| Engine | Composite Score | Notes |
|--------|----------------|-------|
| PDG 0.10 JavaScript | ~20,000 | OpenGL 1.x immediate mode |
| PDG 0.10 C++ | ~ | OpenGL 1.x immediate mode |
| Expected after Scenario 1 | ~60,000 | 3x improvement target |
| Expected after Scenario 2 | ~160,000 | 8-10x improvement target |

*Scores measured on Apple M2 Pro with built-in GPU*

## Using for Optimization Testing

### Establish Baseline

Before making optimizations:

```bash
# Run baseline test
./pdg test/perf/pdgmark/pdgmark.js

# Save as baseline
cp test/perf/pdgmark/pdgmark_results.json \
   test/perf/pdgmark/pdgmark_baseline.json
```

### Test Optimizations

After implementing optimizations:

```bash
# Rebuild PDG
make pdg

# Run new test
./pdg test/perf/pdgmark/pdgmark.js

# Compare results
node test/perf/pdgmark/compare_results.js
```

The comparison tool shows:
- Composite score improvement (%)
- Per-test score changes
- Frame time improvements
- Detailed metric comparisons

### Expected Improvements

Based on the optimization plan in `docs/note-ai/opengl-optimization-analysis.md`:

**Scenario 1: Simple Optimizations**
- State caching
- Basic batching
- Texture optimization
- **Target**: 2-3x improvement (15,000-24,000 composite score)

**Scenario 2: Modern OpenGL**
- Command queue system
- Instanced rendering
- Texture arrays
- Shader-based pipeline
- **Target**: 5-10x improvement (40,000-80,000 composite score)

## Comparison with Bunnymark

| Aspect | Bunnymark | PDGMark |
|--------|-----------|------------|
| Focus | Sprite rendering only | 5 different render types |
| Metric | Max sprites @ 60 FPS | Composite score (60 FPS) |
| Use Case | Sprite batching optimization | Overall 2D performance |
| Tests | 1 test (sprites + physics) | 5 tests (comprehensive) |
| Duration | 30-60 seconds | 60-120 seconds |

**Use both benchmarks together:**
- **Bunnymark** for targeted sprite rendering optimization
- **PDGMark** for comprehensive 2D API performance

## Test Configuration

You can modify these constants in `pdgmark.js`:

```javascript
var OBJECTS_PER_BATCH = 250;     // Objects added per batch
var AUTO_ADD_DELAY = 2000;       // Milliseconds between batches
var MIN_FRAMES_PER_TEST = 60;    // Minimum frames before test can complete
```

**Faster testing** (less accurate):
```javascript
var OBJECTS_PER_BATCH = 100;
var AUTO_ADD_DELAY = 1000;
var MIN_FRAMES_PER_TEST = 30;
```

**More thorough testing** (more accurate):
```javascript
var OBJECTS_PER_BATCH = 25;
var AUTO_ADD_DELAY = 3000;
var MIN_FRAMES_PER_TEST = 120;
```

## Troubleshooting

**"Could not load test image"**
Run from the PDG root directory:
```bash
cd /path/to/pdg-devel
./pdg test/perf/pdgmark/pdgmark.js
```

**Test closes immediately**
Check console for error messages. Make sure PDG was built successfully:
```bash
make pdg
```

**Test hangs or runs very slowly**
The test may take 1-2 minutes to complete all 5 tests. This is normal. Press ESC to abort if needed.

## Technical Details

### Physics/Animation

Each test includes simple animations to simulate realistic rendering scenarios:
- Rotation animations for visual interest
- No complex physics (unlike Bunnymark)
- Consistent frame-to-frame rendering load

### Measurement Precision

- Uses `Date.now()` for timing (millisecond precision)
- Tracks frame times for percentile calculation
- 500ms stats update interval to reduce overhead
- Minimum frame count requirement for stable measurements

### Compatibility

- Works with PDG's Port/Renderer API
- Uses Attributes for styling and transforms
- Standard PDG event handlers (PortDraw, KeyPress)
- Node.js compatible for comparison tool

## Integration with Optimization Plan

This benchmark directly supports the optimization work outlined in `docs/note-ai/opengl-optimization-analysis.md`:

### Validates Multiple Optimization Areas

1. **State Caching** - All tests benefit from reduced state changes
2. **Batching** - Bitmap and text tests show batching improvements
3. **Blend Mode Optimization** - Alpha test specifically measures this
4. **Gradient Performance** - Polygon test measures gradient fills
5. **Text Rendering** - Text test shows font rendering improvements

### Complements Other Benchmarks

- **Bunnymark** - Sprite rendering focus
- **PDGMark** - Comprehensive 2D API coverage
- **CanvasMark 2013** - Game oriented test for in-browser performance

## See Also

- `QUICKSTART.md` - Quick 30-second start guide
- `docs/note-ai/opengl-optimization-analysis.md` - Full optimization plan
- `test/perf/bunnymark/README.md` - Bunnymark sprite test

