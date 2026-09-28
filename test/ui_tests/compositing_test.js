// Stable, side-by-side comparisons for stroke alpha and filled blend modes.
// Run: test/ui compositing --page stroke-opacity (or --page blend-modes).
(function() {
    'use strict';
    var session = pdg.visualTestSession;
    var page = session ? session.page : 0;
    var port = pdg.gfx.createWindowPort(new pdg.Rect(1080, 720), 'PDG Compositing');
    if (!port) throw Error('Could not create the compositing test window');
    var rendered = [false, false];
    var background = '#17243b';
    var scale = 1, left = 0, top = 0;

    function layout(attrs) {
        return attrs.translation(new pdg.Offset(left, top)).scale(scale);
    }
    function fill(color) {
        return layout(new pdg.Attributes().fillColor(color).lineStyle(pdg.lineStyle_None));
    }
    function label(text, x, y, size, color) {
        port.drawText(text, new pdg.Point(x, y), fill(color || '#bed0e5')
            .textSize(size || 15).textStyle(pdg.textStyle_Centered));
    }
    function stroke(shape, x, y, alpha, opacity) {
        var attrs = layout(new pdg.Attributes().lineStyle(pdg.lineStyle_Solid).lineThickness(5)
            .lineColor(new pdg.Color(0.3, 0.9, 1, alpha)).lineOpacity(opacity));
        if (shape === 0) {
            var polygon = new pdg.Polygon();
            for (var i = 0; i < 5; i++) {
                var angle = i * Math.PI * 2 / 5 - Math.PI / 2;
                polygon.addPoint(new pdg.Point(x + 26 * Math.cos(angle), y + 26 * Math.sin(angle)));
            }
            port.drawPolygon(polygon, attrs);
        } else if (shape === 1) port.drawCircle(new pdg.Point(x, y), 26, attrs);
        else port.drawEllipse(new pdg.Point(x, y), 34, 23, attrs);
    }
    function strokePage() {
        label('Stroke alpha × opacity', 540, 65, 28, 'white');
        label('Each pair should match. The last two pairs should be invisible.', 540, 100, 17);
        var cases = [
            {alpha: 1, opacity: 1, title: '1 × 1 = 1'},
            {alpha: 1, opacity: 0.5, title: '1 × 0.5 = 0.5'},
            {alpha: 0.5, opacity: 1, title: '0.5 × 1 = 0.5'},
            {alpha: 0.5, opacity: 0.5, title: '0.5 × 0.5 = 0.25'},
            {alpha: 0, opacity: 1, title: '0 × 1 = 0'},
            {alpha: 1, opacity: 0, title: '1 × 0 = 0'}
        ];
        cases.forEach(function(c, column) {
            var x = 125 + column * 170;
            label(c.title, x, 150, 15, 'white');
            label('test     reference', x, 176, 12);
            for (var row = 0; row < 3; row++) {
                var y = 245 + row * 130;
                // Keep the pair locations visible even when the strokes vanish.
                port.drawRect(new pdg.Rect(x - 79, y - 45, x + 79, y + 45), fill(background));
                stroke(row, x - 39, y, c.alpha, c.opacity);
                stroke(row, x + 39, y, c.alpha * c.opacity, 1);
            }
        });
        label('Pentagons / circles / ellipses. Reference uses the product as color alpha, opacity = 1.',
            540, 625, 15);
    }
    function blendPage() {
        label('Blend modes', 540, 55, 28, 'white');
        label('Overlap color should match the reference swatch. White dots should stay white.', 540, 89, 16);
        var source = [0.7, 0.35, 0.55], destination = [0.25, 0.6, 0.4];
        var modes = [
            {name: 'Normal', mode: pdg.blendMode_Normal, mix: function(s, d) { return s; }},
            {name: 'Additive', mode: pdg.blendMode_Additive, mix: function(s, d) { return Math.min(1, s + d); }},
            {name: 'Multiply', mode: pdg.blendMode_Multiply, mix: function(s, d) { return s * d; }},
            {name: 'Screen', mode: pdg.blendMode_Screen, mix: function(s, d) { return s + d - s * d; }},
            {name: 'Darken', mode: pdg.blendMode_Darken, mix: Math.min},
            {name: 'Lighten', mode: pdg.blendMode_Lighten, mix: Math.max}
        ];
        modes.forEach(function(m, index) {
            var x = 40 + index % 3 * 350, y = 135 + Math.floor(index / 3) * 240;
            label(m.name, x + 155, y, 20, 'white');
            port.drawRect(new pdg.Rect(x, y + 20, x + 310, y + 195), fill(background));
            port.drawRect(new pdg.Rect(x + 15, y + 35, x + 185, y + 140),
                fill(new pdg.Color(destination[0], destination[1], destination[2], 1)));
            port.drawRect(new pdg.Rect(x + 100, y + 70, x + 220, y + 175),
                fill(new pdg.Color(source[0], source[1], source[2], 1)).blendMode(m.mode));
            // Draw a normal, translucent white dot immediately after the blend
            // to expose a blend equation that leaks into subsequent draws.
            port.drawCircle(new pdg.Point(x + 260, y + 45), 7,
                fill(new pdg.Color(1, 1, 1, 0.999)));
            var rgb = source.map(function(s, channel) { return m.mix(s, destination[channel]); });
            port.drawRect(new pdg.Rect(x + 240, y + 85, x + 295, y + 140),
                fill(new pdg.Color(rgb[0], rgb[1], rgb[2], 1)));
            label('reference', x + 267, y + 163, 12);
        });
        label('Opaque source and destination; references are calculated from each blend equation.', 540, 635, 15);
    }
    pdg.on(pdg.eventType_PortDraw, function(event) {
        if (event.port !== port) return false;
        var area = port.getDrawingArea();
        scale = Math.min(area.width() / 1080, (area.height() - 30) / 720);
        left = (area.width() - 1080 * scale) / 2;
        top = (area.height() - 30 - 720 * scale) / 2;
        port.drawRect(area, new pdg.Attributes().fillColor('#0c1422').lineStyle(pdg.lineStyle_None));
        if (page === 0) strokePage(); else blendPage();
        label(session ? session.instructions : 'Automatic comparison pages', 540, 684, 13);
        rendered[page] = true;
        return true;
    });
    if (!session) {
        function advance() {
            if (!rendered[page]) throw Error('Compositing page did not render: ' + page);
            if (++page === 2) {
                pdg.gfx.closeGraphicsPort(port);
                pdg.quit();
            } else setTimeout(advance, 4000);
        }
        setTimeout(advance, 4000);
    }
    pdg.run();
})();
