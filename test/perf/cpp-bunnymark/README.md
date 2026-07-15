# PDG Bunnymark - C++ Version

This is the native C++ implementation of the Bunnymark benchmark for PDG. It uses only PDG's C++ APIs and provides a direct comparison to the JavaScript version.

## Why C++ Version?

The C++ version is useful for:

1. **Baseline Performance** - Measures PDG's raw rendering performance without JavaScript overhead
2. **Optimization Validation** - Ensures rendering optimizations benefit both C++ and JavaScript
3. **Direct API Testing** - Tests the C++ rendering pipeline directly
4. **Cross-Language Comparison** - Quantifies JavaScript binding overhead

## Building

The C++ version is now fully integrated into PDG's CMake build system!

**Build from project root (recommended):**
```bash
make pdg-tests
```

This will:
- Build `libpdg-lib.a` - A pure C++ static library of the PDG framework (no JavaScript bindings)
- Build the `bunnymark` executable using pdg-lib
- Create a symlink at `test/perf/cpp-bunnymark/bunnymark`

**What gets built:**
- `build/darwin/pdg/src/libpdg-lib.a` (~42MB) - PDG C++ framework library
- `build/darwin/pdg/src/bunnymark.app` - Bunnymark executable bundle
- `test/perf/cpp-bunnymark/bunnymark` - Symlink for easy access

## Running

```bash
# From cpp-bunnymark directory
./bunnymark

# Or from project root
test/perf/cpp-bunnymark/bunnymark
```

The test will automatically add bunnies until FPS drops below 30, then you can press **ESC** to see results.

## Controls

- **SPACE** - Manually add 100 bunnies
- **ESC** - Quit and show results

## Output

Results are saved to `test/perf/cpp-bunnymark/bunnymark_results.json` in the same format as the JavaScript version, allowing direct comparison with the comparison tool.

### Example Results

```json
{
  "testName": "PDG Bunnymark (C++)",
  "timestamp": "2025-10-16T...",
  "frameTime": {
    "meanMs": 10.2,
    "minMs": 8.1,
    "maxMs": 28.5,
    "percentile95Ms": 14.3,
    "percentile99Ms": 17.8
  },
  "performance": {
    "averageFPS": 98.04,
    "droppedFrames": 32,
    "maxBunniesAt60FPS": 1800,
    "maxBunniesAt30FPS": 3200
  },
  "bunnymarkScore": 1800
}
```

## Comparing with JavaScript Version

You can use the JavaScript comparison tool to compare C++ vs JavaScript results:

```bash
# After running both versions
node test/perf/bunnymark/compare_results.js \
    test/perf/bunnymark/bunnymark_results.json \
    test/perf/cpp-bunnymark/bunnymark_results.json
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
   - Uses `Port`, `Image`, `Attributes` classes directly
   - No serialization/deserialization overhead
   - No object wrapping

2. **Memory Management**
   - Manual management of bunnies (std::vector)
   - No garbage collection
   - Image loaded once and reused

3. **Event Handling**
   - Implements `IEventHandler` interface
   - Direct event dispatching
   - No V8 context switches

4. **Timing**
   - Uses `OS::getMilliseconds()` directly
   - No Date.now() conversion

### Performance Characteristics

The C++ version measures:
- **Pure rendering performance** - How fast PDG can render sprites without JavaScript
- **Baseline overhead** - The absolute best performance PDG can achieve
- **Memory efficiency** - No JS object allocation or GC overhead
- **Binding cost** - Difference between C++ and JavaScript reveals binding overhead

## Troubleshooting

**Build errors:**
- Run `make clean && make pdg-tests` from project root
- Check that all dependencies are built (chipmunk, glfw, node)

**"Could not create window port"**
- Make sure PDG was built: `make pdg-tests`
- Check that your system supports OpenGL

**"Could not load bunny image"**
- Run from the project root directory
- The benchmark tries multiple paths automatically
- Falls back to `yinyang.png` if wabbit.png not found

**Symlink broken:**
- Run `make pdg-tests` to recreate the symlink
- Or run directly: `./build/darwin/pdg/src/bunnymark.app/Contents/MacOS/bunnymark`

**Very different scores from JavaScript**
- This is expected - C++ should be faster
- If C++ is slower, check build mode (Release vs Debug)

## Integration with Optimization Plan

This C++ benchmark helps validate the optimization plan:

### Scenario 1 Testing
Before implementing simple optimizations, establish C++ baseline:
- If C++ baseline is 2,000 sprites @ 60 FPS
- And JavaScript baseline is 1,000 sprites @ 60 FPS
- Then JavaScript binding overhead is ~50%

After optimizations:
- C++ should improve similarly (state caching benefits both)
- JavaScript should close the gap (better batching reduces binding calls)

### Scenario 2 Testing
Modern OpenGL optimizations should benefit both equally:
- VBO/instancing improvements are rendering-level
- Both C++ and JavaScript should see 5-10x improvement
- Gap should remain proportional

## Build Architecture

### libpdg-lib.a - Pure C++ Framework

The bunnymark executable links against `libpdg-lib.a`, a static library containing all PDG C++ framework code compiled **without JavaScript bindings**.

**Key aspects:**
- Compiled with `PDG_INTERNAL_LIB=1` (skips JavaScript binding code)
- Includes all PDG core functionality (graphics, sprites, events, etc.)
- Includes Spriter animation support
- Includes Chipmunk physics integration
- Size: ~42MB static library

**Sources included in pdg-lib:**
- All sys/*.cpp files (graphics, sprites, events, etc.)
- Platform-specific code (macOS, Windows, Linux)
- Spriter support files
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
test/perf/cpp-bunnymark/
├── bunnymark.cpp              - Main benchmark implementation (459 lines)
├── bunnymark                  - Symlink to executable (created by make pdg-tests)
├── README.md                  - This file
├── STATUS.md                  - Build status and architecture details
└── .gitignore                 - Ignore results, keep symlink

Build artifacts (not in repo):
├── build/darwin/pdg/src/libpdg-lib.a        - PDG C++ framework library
├── build/darwin/pdg/src/bunnymark.app/      - Bunnymark executable bundle
└── test/perf/cpp-bunnymark/bunnymark_results.json - Test results
```

## Quick Start

### First Time Setup
```bash
# Build PDG and the C++ bunnymark
make pdg-tests

# Run C++ version
./test/perf/cpp-bunnymark/bunnymark
# Press ESC when done to save results
cp test/perf/cpp-bunnymark/bunnymark_results.json \
   test/perf/cpp-bunnymark/bunnymark_baseline.json

# Run JavaScript version  
./pdg test/perf/bunnymark/bunnymark.js
# Press ESC when done
cp test/perf/bunnymark/bunnymark_results.json \
   test/perf/bunnymark/bunnymark_baseline.json
```

### Compare C++ vs JavaScript
```bash
node test/perf/bunnymark/compare_results.js \
    test/perf/bunnymark/bunnymark_results.json \
    test/perf/cpp-bunnymark/bunnymark_results.json
```

This shows how much overhead the JavaScript bindings add.

### After Making Optimizations
```bash
# Rebuild and test
make clean && make pdg-tests
./test/perf/cpp-bunnymark/bunnymark

# Compare against baseline
node test/perf/bunnymark/compare_results.js \
    test/perf/cpp-bunnymark/bunnymark_baseline.json \
    test/perf/cpp-bunnymark/bunnymark_results.json
```

### CMake Changes (src/CMakeLists.txt)

**New libpdg-lib target:**
```cmake
ADD_LIBRARY(pdg-lib STATIC
    ${PDG_SOURCES}          # Core PDG C++ files
    ${PLATFORM_FILES}       # Platform code (macOS/Windows/Linux)
    ${SPRITER_FILES}        # Spriter animation support
)
TARGET_COMPILE_DEFINITIONS(pdg-lib PRIVATE PDG_INTERNAL_LIB=1 ...)
TARGET_LINK_LIBRARIES(pdg-lib PUBLIC libtess2 minizip zlib glfw chipmunk)
```

**New bunnymark target:**
```cmake
ADD_EXECUTABLE(bunnymark
    ../test/perf/cpp-bunnymark/bunnymark.cpp
    sys/unix/main-unix.cpp
)
TARGET_LINK_LIBRARIES(bunnymark pdg-lib + frameworks)
```

**Why separate library?**

The PDG sources need different compile flags for C++ vs JavaScript:
- `pdg-lib`: Compiled **without** `PDG_COMPILING_FOR_JAVASCRIPT`
- `pdg.app`: Compiled **with** `PDG_COMPILING_FOR_JAVASCRIPT=1`

This means the sources must be compiled twice, which is why pdg-lib is a separate target rather than being shared with pdg.app.

### Makefile Changes

**New pdg-tests target:**
```makefile
pdg-tests: glfw chipmunk node js-interfaces
	cd $(PDG_ROOT)/build/darwin/pdg; make bunnymark
	ln -sf .../bunnymark.app/.../bunnymark .../cpp-bunnymark/bunnymark
```

**Added to help:**
```
pdg-tests         - C++ performance test suite (Bunnymark)
```

**Added to clean:**
```makefile
clean:
	...
	-rm -f $(PDG_ROOT)/test/perf/cpp-bunnymark/bunnymark
```

## Related Files

- **JavaScript version:** `test/perf/bunnymark/bunnymark.js`
- **Comparison tool:** `test/perf/bunnymark/compare_results.js`
- **Build summary:** `test/perf/BUILD_SUMMARY.md`
- **Optimization plan:** `docs/note-ai/opengl-optimization-analysis.md`
- **CMake config:** `src/CMakeLists.txt` (pdg-lib and bunnymark targets)
- **Main Makefile:** `Makefile` (pdg-tests target)

