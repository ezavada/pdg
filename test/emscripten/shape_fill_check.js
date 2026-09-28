// Rendered regressions for polygon UVs and even-odd coverage. Check both the
// filled pixels and the empty regions, including self-intersecting contours.
// Run with: test/ui --web --no-build --automated shape-fill
module.exports = function(pdg, port, gl, canvas) {
    const canvasMarkTexture = require('../lib/canvasmark_texture_check')(pdg);
    const canvasMarkShips = require('../lib/canvasmark_ship_check')(pdg);
    const polygonCache = require('../lib/polygon_cache_check')(pdg);
    var texture = new pdg.Image('data/yinyang.png');
    var background = new pdg.Color(0.2, 0.4, 0.6);
    var area = port.getDrawingArea(), center = new pdg.Point(160, 160);
    var width = Math.round(320 * canvas.width / area.width());
    var height = Math.round(320 * canvas.height / area.height());
    function capture() {
        var pixels = new Uint8Array(width * height * 4);
        gl.readPixels(0, canvas.height - height, width, height, gl.RGBA, gl.UNSIGNED_BYTE, pixels);
        return pixels;
    }
    function clear() {
        port.drawRect(area, new pdg.Attributes().fillColor(background).lineStyle(pdg.lineStyle_None));
    }
    function polygon(points) {
        var result = new pdg.Polygon();
        points.forEach(function(p) { result.addPoint(new pdg.Point(160 + p[0], 160 + p[1])); });
        return result;
    }
    var star = [], pentagon = [], spiral = [];
    for (var i = 0; i < 10; i++) {
        var angle = i * Math.PI / 5 - Math.PI / 2, radius = i % 2 ? 30 : 70;
        star.push([Math.cos(angle) * radius, Math.sin(angle) * radius]);
        if (!(i % 2)) pentagon.push(star[i]);
    }
    for (var i = 0; i <= 36; i++) {
        var angle = i * Math.PI / 6, radius = i * 2;
        spiral.push([Math.cos(angle) * radius, Math.sin(angle) * radius]);
    }
    for (var i = 36; i >= 0; i--) {
        var angle = i * Math.PI / 6, radius = Math.max(0, i * 2 - 9);
        spiral.push([Math.cos(angle) * radius, Math.sin(angle) * radius]);
    }
    var shapes = [
        { name: 'rounded rectangle', bounds: new pdg.Rect(90, 110, 230, 210) },
        { name: 'star', polygon: polygon(star) },
        { name: 'complex polygon', polygon: polygon([[-70,50],[-70,-25],[-45,-50],[-23,-25],
            [0,-50],[23,-25],[45,-50],[70,-25],[70,50],[35,33],[0,50],[-35,33]]) },
        { name: 'spiral', polygon: polygon(spiral) },
        { name: 'pentagram', polygon: polygon([pentagon[0],pentagon[2],pentagon[4],pentagon[1],pentagon[3]]) },
        { name: 'hourglass', polygon: polygon([[-70,-50],[70,-50],[28,0],[70,50],[-70,50],[-28,0]]) },
        { name: 'crossed hourglass', polygon: polygon([[-70,-50],[70,50],[-70,50],[70,-50]]) }
    ];
    var transforms = [
        { name: 'identity', apply: function(a) {} },
        { name: 'translation', apply: function(a) { a.translation(new pdg.Offset(25, 13)); } },
        { name: 'rotation', apply: function(a) { a.rotation(0.6, center); } },
        { name: 'scale', apply: function(a) { a.scale(1.4, 0.7, center); } },
        { name: 'skew', apply: function(a) { a.skew(0.35, -0.15, center); } },
        { name: 'reflection', apply: function(a) { a.scale(-1, 1, center); } },
        { name: 'opacity', opacity: 0.5, apply: function(a) { a.fillOpacity(0.5); } }
    ];
    var failures = [], checks = { textureTransforms: 0, fillCoverage: 0, radialColors: 0, demoTextures: 0,
        canvasMarkTextureCorners: canvasMarkTexture.cornerPixels, canvasMarkShips: canvasMarkShips,
        polygonCache: polygonCache.renderComparisons };
    var fits = [pdg.fit_Fill, pdg.fit_Inside, pdg.fit_Overflow, pdg.fit_Clipped, pdg.fit_Tile];
    function foreground(pixels, x, y) {
        var p = (y * width + x) * 4;
        return Math.abs(pixels[p] - 51) + Math.abs(pixels[p+1] - 102) + Math.abs(pixels[p+2] - 153) > 24;
    }
    function draw(shape, attrs) {
        if (shape.polygon) port.drawPolygon(shape.polygon, attrs);
        else port.drawRect(shape.bounds, attrs.roundedCorners(20));
    }
    // These two demo textures live outside data/. Exercise their actual demo
    // paths and pixels: missing images previously produced plain white fills.
    [
        {path: 'perf_tests/canvasmark2013/images/texture5.png', width: 256, height: 256},
        {path: 'perf_tests/bunnymark/wabbit.png', width: 26, height: 37}
    ].forEach(function(asset) {
        var image = new pdg.Image(asset.path);
        if (!image || image.getWidth() !== asset.width || image.getHeight() !== asset.height) {
            failures.push('Missing or invalid demo texture: ' + asset.path);
            return;
        }
        [pdg.fit_Clipped, pdg.fit_Tile].forEach(function(fit) {
            clear();
            port.drawRect(new pdg.Rect(90, 110, 230, 210), new pdg.Attributes()
                .texture(image).fitType(fit).lineStyle(pdg.lineStyle_None));
            var pixels = capture(), texturedPixels = 0;
            for (var y = 0; y < height; ++y) {
                for (var x = 0; x < width; ++x) {
                    var offset = (y * width + x) * 4;
                    if (foreground(pixels, x, y) &&
                        Math.max(pixels[offset], pixels[offset + 1], pixels[offset + 2]) > 32 &&
                        Math.min(pixels[offset], pixels[offset + 1], pixels[offset + 2]) < 220) texturedPixels++;
                }
            }
            checks.demoTextures++;
            if (texturedPixels < 20) failures.push(asset.path + ' / fit ' + fit + ': texture did not render');
        });
    });
    // Use individually drawn images as the oracle for repeat size, color and
    // alpha. Counting non-background pixels alone also accepts a black fill.
    var rabbit = new pdg.Image('perf_tests/bunnymark/wabbit.png');
    var tileBounds = new pdg.Rect(90, 110, 229, 213);
    var tileShapes = [
        {name: 'quad', draw: function(a) { port.drawRect(tileBounds, a); }},
        {name: 'rounded rectangle', draw: function(a) { port.drawRect(tileBounds, a.roundedCorners(18)); }},
        {name: 'ellipse', draw: function(a) { port.drawEllipse(tileBounds.centerPoint(), tileBounds.width()/2, tileBounds.height()/2, a); }}
    ];
    checks.rabbitTiles = 0;
    [pdg.fit_Tile, pdg.fit_TileX, pdg.fit_TileY].forEach(function(fit) {
        [1, 0.5].forEach(function(opacity) {
            clear();
            var tileWidth = fit === pdg.fit_TileY ? tileBounds.width() : rabbit.getWidth();
            var tileHeight = fit === pdg.fit_TileX ? tileBounds.height() : rabbit.getHeight();
            for (var y = tileBounds.top; y < tileBounds.bottom; y += tileHeight) {
                for (var x = tileBounds.left; x < tileBounds.right; x += tileWidth) {
                    var right = Math.min(x + tileWidth, tileBounds.right), bottom = Math.min(y + tileHeight, tileBounds.bottom);
                    port.drawImage(rabbit, new pdg.Rect(x, y, right, bottom), new pdg.Attributes().fitType(pdg.fit_Fill)
                        .fillOpacity(opacity).subsection(new pdg.Rect(0, 0,
                            (right-x)/tileWidth* rabbit.getWidth(), (bottom-y)/tileHeight* rabbit.getHeight())));
                }
            }
            var reference = capture();
            tileShapes.forEach(function(shape) {
                clear();
                shape.draw(new pdg.Attributes().fillColor('white').lineStyle(pdg.lineStyle_None));
                var mask = capture();
                clear();
                shape.draw(new pdg.Attributes().texture(rabbit).fitType(fit).fillOpacity(opacity).lineStyle(pdg.lineStyle_None));
                var actual = capture(), samples = 0, mismatches = 0;
                for (var y = 2; y < height - 2; ++y) {
                    for (var x = 2; x < width - 2; ++x) {
                        if (!foreground(mask,x,y) || !foreground(mask,x-2,y) || !foreground(mask,x+2,y) ||
                            !foreground(mask,x,y-2) || !foreground(mask,x,y+2)) continue;
                        var p = (y * width + x) * 4;
                        samples++;
                        if (Math.max(Math.abs(actual[p]-reference[p]), Math.abs(actual[p+1]-reference[p+1]),
                            Math.abs(actual[p+2]-reference[p+2])) > 12) mismatches++;
                    }
                }
                checks.rabbitTiles++;
                if (samples < 50 || mismatches / samples > 0.02) failures.push('Rabbit / ' + shape.name +
                    ' / fit ' + fit + ' / opacity ' + opacity + ': ' + mismatches + '/' + samples + ' pixels differ');
            });
        });
    });
    shapes.forEach(function(shape) {
        var bounds = shape.bounds || shape.polygon.getBounds();
        fits.forEach(function(fit) {
            transforms.forEach(function(transform) {
                var attrs = new pdg.Attributes().texture(texture).fitType(fit).lineStyle(pdg.lineStyle_None);
                transform.apply(attrs);
                clear();
                port.drawQuad(new pdg.Quad(bounds), attrs);
                var reference = capture();
                clear();
                try {
                    draw(shape, attrs);
                } catch (error) {
                    failures.push(shape.name + ' / ' + transform.name + ' / fit ' + fit + ': ' + error);
                    return;
                }
                var actual = capture(), samples = 0, mismatches = 0;
                // Exclude clear pixels and contour edges for the UV comparison.
                // Separate coverage checks below also catch unwanted infill.
                for (var y = 2; y < height - 2; y += 2) {
                    for (var x = 2; x < width - 2; x += 2) {
                        if (!foreground(actual,x,y) || !foreground(actual,x-2,y) || !foreground(actual,x+2,y) ||
                            !foreground(actual,x,y-2) || !foreground(actual,x,y+2)) continue;
                        var p = (y * width + x) * 4;
                        samples++;
                        if (Math.max(Math.abs(actual[p]-reference[p]), Math.abs(actual[p+1]-reference[p+1]),
                            Math.abs(actual[p+2]-reference[p+2])) > 12) mismatches++;
                    }
                }
                checks.textureTransforms++;
                if (samples < 50 || mismatches / samples > 0.02) {
                    failures.push(shape.name + ' / ' + transform.name + ' / fit ' + fit +
                        ': ' + mismatches + '/' + samples + ' pixels differ');
                }
            });
        });
    });

    // An opaque texture makes the solid contour a valid coverage oracle.
    // Transparent yinyang pixels must leave holes once alpha blending works;
    // their colors/alpha are compared with a textured quad above instead.
    var coverageTexture = new pdg.Image('perf_tests/canvasmark2013/images/texture5.png');
    // Solid is the existing even-odd reference. Fitted textures resize the
    // contour before the Attributes transform, so resize the reference too.
    function fittedShape(shape, fit) {
        if (!shape.polygon || (fit !== pdg.fit_Inside && fit !== pdg.fit_Overflow)) return shape;
        var bounds = shape.polygon.getBounds(), center = bounds.centerPoint();
        var scale = (fit === pdg.fit_Inside ? Math.min : Math.max)(
            bounds.width() / coverageTexture.getWidth(), bounds.height() / coverageTexture.getHeight());
        var sx = coverageTexture.getWidth() * scale / bounds.width(), sy = coverageTexture.getHeight() * scale / bounds.height();
        var result = new pdg.Polygon();
        for (var i = 0; i < shape.polygon.getPointCount(); i++) {
            var p = shape.polygon.getPoint(i);
            result.insertPoint(i, new pdg.Point(center.x + (p.x-center.x)*sx, center.y + (p.y-center.y)*sy));
        }
        return { polygon: result };
    }
    var gradientStart = new pdg.Color(1, 0, 0), gradientEnd = new pdg.Color(0, 1, 0);
    var smallCenter = new pdg.Point(183, 141);
    var modes = [
        { name: 'linear', apply: function(a) { a.fillGradient(new pdg.Point(110,110), gradientStart,
            new pdg.Point(210,210), gradientEnd); } },
        { name: 'radial', center: center, radius: 70,
            apply: function(a) { a.fillRadialGradient(center, gradientStart, 70, gradientEnd); } },
        // Exercise a gradient whose center/radius can fall between the initial
        // tessellation vertices, including when its circle crosses an edge.
        { name: 'small radial', center: smallCenter, radius: 7,
            apply: function(a) { a.fillRadialGradient(smallCenter, gradientStart, 7, gradientEnd); } }
    ];
    fits.forEach(function(fit) {
        modes.push({ name: 'fit ' + fit, fit: fit, apply: function(a) { a.texture(coverageTexture).fitType(fit); } });
    });
    shapes.forEach(function(shape) {
        modes.forEach(function(mode) {
            // Rounded rectangles already have UV coverage above; their fitted
            // curved contour is not exposed as a Polygon in JavaScript.
            if (!shape.polygon && mode.fit !== undefined) return;
            transforms.forEach(function(transform) {
                // Check opaque contour coverage here; opacity/overdraw is
                // checked against the textured quad and rabbit images above.
                if (mode.fit !== undefined && transform.opacity) return;
                var attrs = new pdg.Attributes().fillColor(new pdg.Color(1,1,1)).lineStyle(pdg.lineStyle_None);
                transform.apply(attrs);
                clear();
                draw(fittedShape(shape, mode.fit), attrs);
                var reference = capture();
                if (shape.name === 'pentagram' && transform.name === 'identity' &&
                    foreground(reference, Math.floor(160 * canvas.width / area.width()),
                        height - 1 - Math.floor(160 * canvas.height / area.height()))) {
                    failures.push('Solid pentagram must leave its center empty');
                }
                mode.apply(attrs);
                clear();
                draw(shape, attrs);
                var actual = capture(), samples = 0, mismatches = 0, colorSamples = 0, colorMismatches = 0;
                for (var y = 2; y < height - 2; y += 2) {
                    for (var x = 2; x < width - 2; x += 2) {
                        var inside = foreground(reference,x,y), edge = false;
                        for (var dy = -2; dy <= 2; dy += 2) {
                            for (var dx = -2; dx <= 2; dx += 2) {
                                if (foreground(reference,x+dx,y+dy) !== inside) edge = true;
                            }
                        }
                        if (edge) continue;
                        if (inside) samples++;
                        if (foreground(actual,x,y) !== inside) mismatches++;
                        // Independently evaluate radial color at each pixel center.
                        // This catches a tessellation that fixes holes but loses
                        // the gradient's interior color (all boundary vertices can
                        // have the same distance from its center).
                        if (inside && mode.radius) {
                            var px = (x+0.5) * area.width() / canvas.width;
                            var py = (height-y-0.5) * area.height() / canvas.height;
                            var t = Math.min(1, Math.hypot(px-mode.center.x, py-mode.center.y) / mode.radius);
                            var opacity = transform.opacity || 1;
                            var p = (y*width+x)*4;
                            colorSamples++;
                            if (Math.max(Math.abs(actual[p] - (255*(1-t)*opacity + 51*(1-opacity))),
                                Math.abs(actual[p+1] - (255*t*opacity + 102*(1-opacity))),
                                Math.abs(actual[p+2] - 153*(1-opacity))) > 8) colorMismatches++;
                        }
                    }
                }
                checks.fillCoverage++;
                if (samples < 50 || mismatches / samples > 0.01) {
                    failures.push(shape.name + ' / ' + transform.name + ' / ' + mode.name +
                        ': coverage differs at ' + mismatches + ' pixels (' + samples + ' interior samples)');
                }
                if (colorSamples) {
                    checks.radialColors++;
                    if (colorMismatches / colorSamples > 0.01) failures.push(shape.name + ' / ' + transform.name +
                        ' / ' + mode.name + ': colors differ at ' + colorMismatches + '/' + colorSamples + ' pixels');
                }
            });
        });
    });
    if (failures.length) throw new Error('Shape fill regression: ' + failures.join('; '));
    checks.clipping = require("./drawing_clip_check.js")(pdg, port, gl, canvas);
    return checks;
};
