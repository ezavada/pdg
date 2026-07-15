# CanvasMark 2013 - PDG Port

This is a port of the [CanvasMark 2013 HTML5 Canvas benchmark](https://github.com/kevinroast/CanvasMark) to run using PDG's native rendering APIs.

## What is CanvasMark 2013?

CanvasMark 2013 is a comprehensive HTML5 Canvas 2D rendering and JavaScript performance benchmark created by Kevin Roast. It tests various aspects of canvas rendering including:

- Vector drawing (paths, shapes, transformations)
- Bitmap sprite rendering and scaling
- Text rendering
- Particle effects
- 3D wireframe rendering (via K3D library)
- 3D textured polygon rendering
- Mathematical visualization (plasma effects)

## Working Tests (7 total)

### Asteroids Tests (Tests 1-4)
1. **Vector Asteroids** - Rotating vector-drawn asteroids with path transformations
2. **Bitmap Asteroids** - Sprite-based asteroids with image scaling and rotation
3. **Mixed Rendering** - Combined vector/bitmap asteroids, bullets, and transformations
4. **Particle Effects** - Explosions, debris, and text rendering

### Arena Test (Test 5)
- **3D Wireframe Combat** - Multiple 3D ships rendered with K3D, full rotation and perspective projection

### Feature Tests (Tests 6-7)
1. **Plasma** - Mathematical visualization using canvas shapes and pixel-level color manipulation
2. **3D Textured Cubes** - Multiple rotating cubes with texture-mapped faces using PDG's native polygon rendering

## Excluded Tests

**Blur Test** - This test requires `getImageData()` and `putImageData()` pixel manipulation APIs that are not currently exposed to JavaScript in PDG's API. The C++ `Image` class has `getPixel()` but no corresponding `setPixel()` or ability to create images from raw pixel arrays in JavaScript.

## Canvas Compatibility Layer

The port includes a comprehensive Canvas 2D API compatibility layer (`pdg-canvas-compat.js`) that translates HTML5 Canvas API calls to PDG's native rendering APIs.

### Key Features

**Browser Environment Simulation:**
- Implements `window`, `document`, `navigator`, `Image`, `requestAnimationFrame`
- jQuery stub for DOM manipulation
- Event system mapping (mouse, keyboard) to PDG events

**Canvas 2D Context API:**
- Drawing primitives: `fillRect`, `strokeRect`, `arc`, `fill`, `stroke`
- Paths: `beginPath`, `moveTo`, `lineTo`, `closePath`
- Transformations: `translate`, `rotate`, `scale`, `save`, `restore`
- Images: `drawImage` with all 3 signature variants (position, scaling, subsection)
- Text: `fillText`, `strokeText`, `measureText`
- Styles: `fillStyle`, `strokeStyle`, `lineWidth`, `globalAlpha`
- Effects: Shadow/glow simulation using concentric alpha circles
- Blending: `globalCompositeOperation` with additive blending support

**Image Handling:**
- Wraps `pdg.Image` with Canvas-compatible `Image()` constructor
- Supports `src` property and `onload` callbacks
- Handles synchronous PDG image loading in async-expecting browser code

**Transformation System:**
- Full transformation matrix tracking (translate, rotate, scale)
- Applies transforms to all drawing primitives via `transformPoint()`
- Proper canvas state save/restore with deep-copying

### K3D Integration

The original CanvasMark uses the K3D 3D rendering library for wireframe and textured 3D rendering. This port:

1. **Uses the real K3D library** - The complete K3D implementation handles all 3D math (rotation matrices, perspective projection, depth sorting)

2. **Monkey-patches textured rendering** - K3D's `SolidRenderer.renderPolygon()` method is intercepted to use PDG's native `drawPolygon()` with texture support instead of the complex Canvas `transform()` + `clip()` + `drawImage()` approach

3. **Preserves wireframe rendering** - Non-textured K3D rendering uses the standard Canvas compatibility layer

This approach gives us correct 3D transformations from K3D combined with efficient native textured polygon rendering from PDG.

## Running the Benchmark

```bash
./pdg test/perf/canvasmark2013/canvasmark.js
```

Press **SPACE** or **click** to start the tests.  
Press **ESC** to quit at any time.

The benchmark will cycle through all 7 tests, displaying performance metrics (FPS, score) for each.

## Technical Notes

**Coordinate System:**
- Canvas uses top-left origin (0,0)
- PDG uses same coordinate system, so no conversion needed
- K3D screen coordinates account for canvas translation offsets

**Performance Considerations:**
- The Canvas emulation layer adds significant overhead
- On an M2 MacBook Pro, running in Chrome the benchmark is ~39600 vs ~17600 running in PDG with Canvas emulation 
- The benchmark scores will not be directly comparable to browser-based Canvas results
- Glow/shadow effects use multiple draw calls (concentric circles) which may be slower than native Canvas shadows

**Performance Measured:**

| Test | Chrome v141 | pdg v0.10 | Note |
|------|-------------|-----------|------|
| Test 1 | 2121 | 1058 | Asteroids - Bitmaps
| Test 2 | 7103 | 1757 | Asteroids - Vectors
| Test 3 | 11297 | 1762 | Asteroids - Bitmaps, shapes, text
| Test 4 | 416 | 1275 | Asteroids - Shapes, shadows, blending
| Test 5 | 744 | 8289 | Arena5 - Vectors, shadows, bitmaps, text
| Test 6 | 3020 | 356 | Plasma - Maths, canvas shapes
| Test 7 | 14987 | 2742 | 3D Rendering - Maths, polygons, image transforms
| **Total** | 39600 | 17200 | 

*Apple M2 Pro with built-in GPU*

**Limitations:**
- No pixel-level manipulation (`getImageData`/`putImageData`)
- Text rendering uses PDG fonts, not Canvas font system
- Some advanced Canvas features not implemented (patterns, complex gradients, advanced composite operations)

## Credits

- **Original CanvasMark 2013**: Kevin Roast ([@kevinroast](https://github.com/kevinroast))
- **K3D Library**: Kevin Roast
- **PDG Port**: 2025

## License

Original CanvasMark code retains its original license. See `license.txt` in the scripts directory.

