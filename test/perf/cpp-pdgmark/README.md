# PDG PDGMark - C++ Version

This is the native C++ implementation of the PDGMark benchmark for PDG. It uses only PDG's C++ APIs and provides a direct comparison to the JavaScript version.

## What is PDGMark?

PDGMark is a comprehensive 2D rendering performance benchmark that tests 5 different aspects of PDG's rendering capabilities:

1. **Bitmap Rendering** - Sprite/image drawing with rotation and scaling
2. **Line Drawing** - Lines, arcs, splines, and curves
3. **Alpha Blending** - Transparency and blend modes
4. **Polygon Fills** - Complex shapes with fills and gradients
5. **Text Rendering** - Text drawing with various sizes and styles

Each test progressively adds objects until the frame rate drops below 60 FPS, then calculates a weighted score based on complexity.

## Why C++ Version?

The C++ version is useful for:

1. **Baseline Performance** - Measures PDG's raw rendering performance without JavaScript overhead
2. **Optimization Validation** - Ensures rendering optimizations benefit both C++ and JavaScript
3. **Direct API Testing** - Tests the C++ rendering pipeline directly
4. **Cross-Language Comparison** - Quantifies JavaScript binding overhead

## Building

The C++ version is fully integrated into PDG's CMake build system!

**Build from project root (recommended):**
```bash
make pdg-tests
```

This will:
- Build `libpdg-lib.a` - A pure C++ static library of the PDG framework (no JavaScript bindings)
- Build the `bunnymark` and `pdgmark` executables using pdg-lib
- Create symlinks at `test/perf/cpp-bunnymark/bunnymark` and `test/perf/cpp-pdgmark/pdgmark`

**What gets built:**
- `build/darwin/pdg/src/libpdg-lib.a` (~42MB) - PDG C++ framework library
- `build/darwin/pdg/src/pdgmark.app` - PDGMark executable bundle
- `test/perf/cpp-pdgmark/pdgmark` - Symlink for easy access

## Running

```bash
# From cpp-pdgmark directory
./pdgmark

# Or from project root
test/perf/cpp-pdgmark/pdgmark
```

The test will automatically run through all 5 tests, adding objects until 60 FPS is reached for each test. Press **ESC** at any time to see results.

## Controls

- **ESC** - Quit and show results (can be pressed at any time)

## Output

Results are saved to `test/perf/cpp-pdgmark/pdgmark_results.json` in the same format as the JavaScript version, allowing direct comparison.

### Example Results

```json
{
  "testName": "PDG PDGMark (C++)",
  "timestamp": "2025-10-17T...",
  "totalDurationSeconds": 45.2,
  "compositeScore": 2850,
  "tests": {
    "bitmap": {
      "objectsAt60FPS": 500,
      "score": 500,
      "weight": 1.0,
      "averageFPS": 42.5
    },
    "drawing": {
      "objectsAt60FPS": 400,
      "score": 480,
      "weight": 1.2,
      "averageFPS": 38.2
    },
    "alpha": {
      "objectsAt60FPS": 450,
      "score": 585,
      "weight": 1.3,
      "averageFPS": 40.1
    },
    "polygon": {
      "objectsAt60FPS": 350,
      "score": 525,
      "weight": 1.5,
      "averageFPS": 36.8
    },
    "text": {
      "objectsAt60FPS": 550,
      "score": 770,
      "weight": 1.4,
      "averageFPS": 44.2
    }
  }
}
```

## Comparing with JavaScript Version

You can use the JavaScript comparison tool to compare C++ vs JavaScript results:

```bash
# After running both versions
node test/perf/pdgmark/compare_results.js \
    test/perf/pdgmark/pdgmark_results.json \
    test/perf/cpp-pdgmark/pdgmark_results.json
```

### Expected Differences

**C++ should be faster** because:
- No JavaScript VM overhead
- Direct C++ API calls (no binding layer)
- No garbage collection pauses
- Native compiled code

**Typical difference**: 1.2-2x faster (C++ scores 20-100% higher)

However, if the difference is larger, it indicates:
- JavaScript binding overhead could be optimized
- Potential for caching in the binding layer
- GC pressure from object creation

If C++ is **not** faster, investigate:
- Are rendering calls properly batched?
- Is the same rendering path being used?
- Check for debug builds (should use Release)

## Implementation Details

### Key Differences from JavaScript Version

1. **Direct API Usage**
   - Uses `Port`, `Image`, `Attributes`, `Polygon`, etc. classes directly
   - No serialization/deserialization overhead
   - No object wrapping

2. **Memory Management**
   - Manual management of test objects (std::vector)
   - No garbage collection
   - Images loaded once and reused

3. **Event Handling**
   - Implements `IEventHandler` interface
   - Direct event dispatching
   - No V8 context switches

4. **Timing**
   - Uses `OS::getMilliseconds()` directly
   - No Date.now() conversion

### Performance Characteristics

The C++ version measures:
- **Pure rendering performance** - How fast PDG can render various primitives without JavaScript
- **Baseline overhead** - The absolute best performance PDG can achieve
- **Memory efficiency** - No JS object allocation or GC overhead
- **Binding cost** - Difference between C++ and JavaScript reveals binding overhead

### Test Implementations

Each test creates objects that:
- Update their state each frame (rotation, position, etc.)
- Render using PDG's drawing API
- Are automatically added until 60 FPS threshold

**Bitmap Test** - Tests image drawing with rotation and scaling  
**Drawing Test** - Tests line, arc, spline, and ellipse rendering  
**Alpha Test** - Tests transparency and blend modes with rectangles and ellipses  
**Polygon Test** - Tests complex polygon rendering with fills and gradients  
**Text Test** - Tests text rendering with various sizes and styles  

## Troubleshooting

**Build errors:**
- Run `make clean && make pdg-tests` from project root
- Check that all dependencies are built (chipmunk, glfw, node)

**"Could not create window port"**
- Make sure PDG was built: `make pdg-tests`
- Check that your system supports OpenGL

**"Could not load test image"**
- Run from the project root directory
- The benchmark tries multiple paths automatically
- Make sure `test/data/test_image.png` exists

**Symlink broken:**
- Run `make pdg-tests` to recreate the symlink
- Or run directly: `./build/darwin/pdg/src/pdgmark.app/Contents/MacOS/pdgmark`

**Very different scores from JavaScript**
- This is expected - C++ should be faster
- If C++ is slower, check build mode (Release vs Debug)

## Integration with Optimization Plan

This C++ benchmark helps validate rendering optimizations:

### Baseline Testing
Before implementing optimizations, establish C++ baselines:
- If C++ composite score is 3,000
- And JavaScript composite score is 1,500
- Then JavaScript binding overhead is ~50%

After optimizations:
- C++ should improve similarly (state caching benefits both)
- JavaScript should close the gap (better batching reduces binding calls)

### Modern OpenGL Testing
OpenGL optimizations should benefit both equally:
- VBO/instancing improvements are rendering-level
- Both C++ and JavaScript should see 5-10x improvement
- Gap should remain proportional

### Test-Specific Analysis
Individual test scores reveal specific bottlenecks:
- Low polygon score → tessellation issues
- Low text score → font rendering issues
- Low alpha score → blending overhead
- Compare C++ vs JS per-test to find binding bottlenecks

## Build Architecture

### libpdg-lib.a - Pure C++ Framework

The pdgmark executable links against `libpdg-lib.a`, a static library containing all PDG C++ framework code compiled **without JavaScript bindings**.

**Key aspects:**
- Compiled with `PDG_INTERNAL_LIB=1` (skips JavaScript binding code)
- Includes all PDG core functionality (graphics, sprites, events, etc.)
- Size: ~42MB static library

**Sources included in pdg-lib:**
- All sys/*.cpp files (graphics, sprites, events, etc.)
- Platform-specific code (macOS, Windows, Linux)
- Does NOT include: Node.js, V8, JavaScript bindings

### Dual Compilation Model

PDG sources are compiled **twice** with different flags:

1. **For pdg-lib** (C++ only):
   ```
   PDG_INTERNAL_LIB=1           # Skip script bindings
   PDG_PROJECT=PDG_PROJECT_C_ONLY_APP
   ```

2. **For pdg.app** (JavaScript runtime):
   ```
   PDG_COMPILING_FOR_JAVASCRIPT=1  # Enable script bindings
   PDG_PROJECT=PDG_PROJECT_NODE_APP
   ```

This allows the same PDG sources to be used for both pure C++ applications and JavaScript-enabled applications.

## File Structure

```
test/perf/cpp-pdgmark/
├── pdgmark.cpp               - Main benchmark implementation (~950 lines)
├── pdgmark                   - Symlink to executable (created by make pdg-tests)
└── README.md                 - This file

Build artifacts (not in repo):
├── build/darwin/pdg/src/libpdg-lib.a        - PDG C++ framework library
├── build/darwin/pdg/src/pdgmark.app/        - PDGMark executable bundle
└── test/perf/cpp-pdgmark/pdgmark_results.json - Test results
```

## Quick Start

### First Time Setup
```bash
# Build PDG and the C++ pdgmark
make pdg-tests

# Run C++ version
./test/perf/cpp-pdgmark/pdgmark
# Press ESC when all tests complete to save results
cp test/perf/cpp-pdgmark/pdgmark_results.json \
   test/perf/cpp-pdgmark/pdgmark_baseline.json

# Run JavaScript version  
./pdg test/perf/pdgmark/pdgmark.js
# Press ESC when all tests complete
cp test/perf/pdgmark/pdgmark_results.json \
   test/perf/pdgmark/pdgmark_baseline.json
```

### Compare C++ vs JavaScript
```bash
node test/perf/pdgmark/compare_results.js \
    test/perf/pdgmark/pdgmark_results.json \
    test/perf/cpp-pdgmark/pdgmark_results.json
```

This shows how much overhead the JavaScript bindings add across all 5 rendering tests.

### After Making Optimizations
```bash
# Rebuild and test
make clean && make pdg-tests
./test/perf/cpp-pdgmark/pdgmark

# Compare against baseline
node test/perf/pdgmark/compare_results.js \
    test/perf/cpp-pdgmark/pdgmark_baseline.json \
    test/perf/cpp-pdgmark/pdgmark_results.json
```

## CMake Configuration

The pdgmark target is defined in `src/CMakeLists.txt`:

```cmake
ADD_EXECUTABLE(pdgmark
    ../test/perf/cpp-pdgmark/pdgmark.cpp
    sys/unix/main-unix.cpp
)
TARGET_COMPILE_DEFINITIONS(pdgmark PRIVATE PDG_INTERNAL_LIB=1 ...)
TARGET_LINK_LIBRARIES(pdgmark pdg-lib + frameworks)
```

## Makefile Integration

The `pdg-tests` target in the main Makefile:
```makefile
pdg-tests: glfw chipmunk node js-interfaces
	cd $(PDG_ROOT)/build/darwin/pdg; make bunnymark pdgmark
	ln -sf .../pdgmark.app/.../pdgmark .../cpp-pdgmark/pdgmark
```

## Related Files

- **JavaScript version:** `test/perf/pdgmark/pdgmark.js`
- **Comparison tool:** `test/perf/pdgmark/compare_results.js`
- **C++ Bunnymark:** `test/perf/cpp-bunnymark/bunnymark.cpp`
- **CMake config:** `src/CMakeLists.txt` (pdg-lib and pdgmark targets)
- **Main Makefile:** `Makefile` (pdg-tests target)

## Performance Tips

1. **Run in Release Mode** - Debug builds are much slower
2. **Close Other Apps** - For consistent benchmark results
3. **Multiple Runs** - Run 3-5 times and average the scores
4. **Same Hardware** - Compare results on the same machine
5. **Stable System** - Disable background processes for best results

## Interpreting Results

### Composite Score
The overall score combines all 5 tests with their weights:
- Higher is better
- Typical C++ scores: 2000-4000
- Typical JS scores: 1000-2500

### Individual Test Scores
Each test score = `objectsAt60FPS × weight`
- Bitmap (1.0x): Baseline rendering
- Drawing (1.2x): More complex than bitmaps
- Alpha (1.3x): Blending overhead
- Polygon (1.5x): Tessellation complexity
- Text (1.4x): Font rendering complexity

### Frame Time Statistics
- Mean: Average time per frame
- 95th percentile: Worst-case excluding outliers
- 99th percentile: Near worst-case performance
- Max: Absolute worst frame

### Objects at 60 FPS
The maximum number of objects rendered while maintaining ≥60 FPS:
- This is the key metric for each test
- Higher numbers indicate better performance
- Used to calculate the weighted score

