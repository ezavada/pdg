# PDG Bunnymark Quick Start

## What is This?

Bunnymark is a standard performance benchmark that measures how many sprites your engine can render at 60 FPS. It's used across all major game engines (Unity, Godot, Phaser) to compare 2D rendering performance.

## Quick Test (30 seconds)

```bash
# From PDG root directory
./pdg test/perf/bunnymark/bunnymark.js
```

Wait for it to auto-add bunnies until FPS drops, then press **ESC** to see results.

Your **Bunnymark Score** is the key number: sprites rendered @ 60 FPS.

## Measure Optimization Impact

**Before making changes:**
```bash
./pdg test/perf/bunnymark/bunnymark.js
cp test/perf/bunnymark/bunnymark_results.json test/perf/bunnymark/bunnymark_baseline.json
```

**After making changes:**
```bash
make pdg                                  # Rebuild
./pdg test/perf/bunnymark/bunnymark.js             # Re-test
node test/perf/bunnymark/compare_results.js        # Compare
```

## Expected Improvements

Based on the optimization plan in `docs/note-ai/opengl-optimization-analysis.md`:

| Optimization Level | Expected Score | Improvement |
|-------------------|----------------|-------------|
| Baseline (current) | ~6,000 sprites | - |
| Scenario 1 (simple) | ~12,000 sprites | 2-3x |
| Scenario 2 (modern) | ~30,000 sprites | 5-10x |

## What If My Score Is Low?

**This is expected!** PDG currently uses OpenGL 1.x immediate mode rendering, which is very inefficient. Low scores validate the need for the optimizations outlined in the analysis document.

The point of this benchmark is to:
1. Establish a baseline
2. Measure improvements as optimizations are implemented
3. Validate that changes actually improve performance

## Files Created

- `bunnymark_results.json` - Latest test results
- `bunnymark_baseline.json` - Saved baseline (you create this manually)

Results are git-ignored by default (except baseline).

## Troubleshooting

**Can't find image:** Run from PDG root directory (`pdg-devel/`)

**Window doesn't appear:** Check that PDG builds successfully with `make pdg`

**Test finishes immediately:** Check console for errors

## Learn More

- Full documentation: `test/perf/bunnymark/README.md`
- Optimization plan: `docs/note-ai/opengl-optimization-analysis.md`
- Standard benchmarks analysis: See the web research in the optimization doc

