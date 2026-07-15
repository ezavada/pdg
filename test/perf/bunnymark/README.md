# PDG Performance Tests

This directory contains performance benchmarks for the PDG rendering engine.

## Bunnymark

The classic sprite rendering benchmark used across game engines to measure 2D rendering throughput.

### What It Tests

- Sprite rendering performance
- Texture binding overhead
- Draw call efficiency
- Frame time consistency

### How It Works

The test spawns increasingly large numbers of textured sprites (bunnies) that bounce around the screen with simple physics. It measures:

- **Frame time** (ms per frame)
- **FPS** (frames per second)
- **Maximum sprites at 60 FPS** - The primary Bunnymark score
- **Maximum sprites at 30 FPS** - Secondary metric
- **Frame time percentiles** (95th, 99th) - Measures consistency
- **Dropped frames** - Frames that took > 16.67ms

### Running the Test

**Auto mode** (recommended for benchmarking):
```bash
./pdg test/perf/bunnymark/bunnymark.js
```

This will automatically add bunnies every 2 seconds until FPS drops below 30, then you can press ESC to see results.

**Manual mode** (for interactive testing):
```bash
./pdg test/perf/bunnymark/bunnymark.js --manual
```

Press SPACE to add bunnies, ESC to quit and see results.

**Custom batch size**:
```bash
./pdg test/perf/bunnymark/bunnymark.js --batch 50
```

Adds 50 bunnies at a time instead of the default 100.

### Results

Results are printed to console and saved to `test/perf/bunnymark/bunnymark_results.json`:

```json
{
  "testName": "PDG Bunnymark",
  "timestamp": "2025-10-16T...",
  "frameTime": {
    "meanMs": 12.45,
    "minMs": 8.2,
    "maxMs": 35.6,
    "percentile95Ms": 15.8,
    "percentile99Ms": 18.2
  },
  "performance": {
    "averageFPS": 80.32,
    "droppedFrames": 45,
    "maxBunniesAt60FPS": 1200,
    "maxBunniesAt30FPS": 2500
  },
  "bunnymarkScore": 1200
}
```

### Interpreting Results

**Bunnymark Score**: The maximum number of sprites rendered while maintaining 60 FPS.

**Reference scores** (approximate, varies by hardware):

| Engine | Sprites @ 60 FPS | API |
|--------|-----------------|-----|
| Godot 4.x C# | ~16,000 | OpenGL ES 3.0 | (as reported by AI)
| Unity C# | ~10,000 | running on Mono | (as reported by AI)
| Unity C# | ~30,000 | ECS + IL2CPP | (as reported by AI)
| PDG 0.10 JavaScript | ~6,000 | OpenGL 1.x immediate mode
| PDG 0.10 C++ | ~23,000 | OpenGL 1.x immediate mode

*Apple M2 Pro w/built-in GPU for all tests*

### Using for Optimization Testing

**Establish baseline**:
```bash
# Run before optimizations
./pdg test/perf/bunnymark/bunnymark.js
cp test/perf/bunnymark/bunnymark_results.json test/perf/bunnymark/bunnymark_baseline.json
```

**Test optimizations**:
```bash
# After implementing optimizations
./pdg test/perf/bunnymark/bunnymark.js

# Compare results
node test/perf/bunnymark/compare_results.js
```

The comparison tool will show detailed metrics and calculate improvement percentages.

**Expected improvements**:
- **Scenario 1** (simple optimizations): 2-3x improvement
- **Scenario 2** (modern OpenGL): 5-10x improvement

### The Bunny Image

The test uses the classic **wabbit.png** sprite (26x37 pixels) from the original Bunnymark test by Iain Lobb. This is the same bunny used in Bunnymark implementations across Godot, OpenFL, HaxeFlixel, and other engines, making results directly comparable.

The image is included in `test/perf/bunnymark/wabbit.png` and was sourced from the [OpenFL Bunnymark samples](https://github.com/openfl/openfl-samples/tree/master/demos/BunnyMark).

### Troubleshooting

**"Could not load bunny image"**: Run from the PDG root directory:
```bash
cd /path/to/pdg-devel
./pdg test/perf/bunnymark/bunnymark.js
```

**Test closes immediately**: Check console for error messages. Make sure PDG was built successfully.

**Very low scores**: This is expected for the current implementation. Use this as the baseline to measure improvements against.

## Future Tests

Additional benchmarks to be implemented:

- **tilemark** - TileMap rendering performance
- **textmark** - Text rendering performance
- **mixedmark** - Combined sprite/tile/text scene
- **statemark** - State change overhead measurement
- **batchmark** - Batching efficiency test

See `docs/note-ai/opengl-optimization-analysis.md` for the full performance testing plan.

