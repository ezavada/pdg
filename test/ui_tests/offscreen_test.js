// Compare direct drawing with a live offscreen image and a frozen snapshot.
// Run: test/ui offscreen  (or test/ui --web offscreen)
(function() {
    'use strict';
    var session = pdg.visualTestSession;
    var port = pdg.gfx.createWindowPort(new pdg.Rect(1080, 620), 'PDG Offscreen Ports');
    if (!port) throw Error('Could not create the offscreen test window');
    var surface = pdg.gfx.createOffscreenPort(new pdg.Rect(256, 256));
    if (!surface) throw Error('Could not create an offscreen port');

    function fill(color) {
        return new pdg.Attributes().fillColor(color).lineStyle(pdg.lineStyle_None);
    }
    function text(target, value, x, y, size, color) {
        target.drawText(value, new pdg.Point(x, y), fill(color)
            .textSize(size).textStyle(pdg.textStyle_Centered));
    }
    // The transparent edge decorations are painted only once on the persistent
    // surface. Each animated frame repaints its opaque inner square, so old
    // animation pixels are covered without accumulating translucent trails.
    function scene(target, left, top, scale, angle, includeEdges) {
        function point(x, y) { return new pdg.Point(left + x * scale, top + y * scale); }
        function circle(x, y, radius, color) {
            target.drawEllipse(point(x, y), radius * scale, radius * scale, fill(color));
        }
        function line(x, y, xx, yy, color, thickness) {
            target.drawLine(point(x, y), point(xx, yy), new pdg.Attributes()
                .lineColor(color).lineThickness(thickness * scale));
        }
        if (includeEdges) {
            circle(30, 30, 28, new pdg.Color(0.2, 0.85, 0.95, 0.45));
            circle(226, 226, 28, new pdg.Color(0.95, 0.45, 0.7, 0.45));
        }
        target.drawRect(new pdg.Rect(left + 24 * scale, top + 24 * scale,
            left + 232 * scale, top + 232 * scale), fill('#17243b'));
        target.drawEllipse(point(128, 128), 70 * scale, 70 * scale,
            new pdg.Attributes().lineColor('#486080').lineThickness(2 * scale));
        for (var i = 0; i < 12; i++) {
            var a = i * Math.PI / 6;
            line(128 + Math.cos(a) * 78, 128 + Math.sin(a) * 78,
                128 + Math.cos(a) * 83, 128 + Math.sin(a) * 83, '#6983a4', 2);
        }
        var x = 128 + Math.cos(angle) * 70, y = 128 + Math.sin(angle) * 70;
        circle(128 - Math.cos(angle) * 40, 128 - Math.sin(angle) * 40, 25,
            new pdg.Color(0.9, 0.35, 0.65, 0.65));
        line(128, 128, x, y, '#58e6da', 4);
        circle(x, y, 14, '#58e6da');
        circle(128, 128, 6, '#ffffff');
        text(target, 'TOP', left + 128 * scale, top + 48 * scale, 13 * scale, '#bed0e5');
        text(target, 'RGBA', left + 128 * scale, top + 222 * scale, 13 * scale, '#bed0e5');
    }

    scene(surface, 0, 0, 1, 0, true);
    // Both images are created exactly once. Only the live image follows later draws.
    var live = new pdg.Image(surface, pdg.SharedSurface);
    var snapshot = new pdg.Image(surface, pdg.CopyPixels);
    if (!live || !snapshot) throw Error('Could not create images from the offscreen port');
    var started = pdg.tm.getMilliseconds();

    function checkerboard(left, top, scale) {
        for (var row = 0; row < 8; row++) {
            for (var col = 0; col < 8; col++) {
                port.drawRect(new pdg.Rect(left + col * 32 * scale, top + row * 32 * scale,
                    left + (col + 1) * 32 * scale, top + (row + 1) * 32 * scale),
                    fill((row + col) % 2 ? '#344155' : '#253247'));
            }
        }
    }
    pdg.on(pdg.eventType_PortDraw, function(event) {
        if (event.port !== port) return false;
        var area = port.getDrawingArea();
        var scale = Math.min(area.width() / 1080, (area.height() - 30) / 570);
        var left = (area.width() - 1080 * scale) / 2;
        var top = (area.height() - 30 - 570 * scale) / 2;
        function label(value, x, y, size, color) {
            text(port, value, left + x * scale, top + y * scale, size * scale, color);
        }
        // This background is drawn before switching targets; the labels and
        // images below also exercise restoration of the window's drawing state.
        port.drawRect(area, fill('#111827'));
        var angle = ((pdg.tm.getMilliseconds() - started) >>> 0) * Math.PI / 4000;
        if (!session || !session.paused) scene(surface, 0, 0, 1, angle, false);

        label('Offscreen ports', 540, 55, 28, '#ffffff');
        label('The live image follows the drawing. The snapshot stays at its starting pose.',
            540, 89, 16, '#b9c8dc');
        var centers = [204, 540, 876];
        var titles = ['Reference drawing', 'Live image', 'Frozen snapshot'];
        var captions = ['Drawn directly to the window', 'SharedSurface', 'CopyPixels (default)'];
        centers.forEach(function(center, index) {
            var x = left + (center - 128) * scale, y = top + 176 * scale;
            label(titles[index], center, 144, 20, index === 1 ? '#58e6da' : '#ffffff');
            checkerboard(x, y, scale);
            if (index === 0) scene(port, x, y, scale, angle, true);
            else port.drawImage(index === 1 ? live : snapshot,
                new pdg.Rect(x, y, x + 256 * scale, y + 256 * scale), new pdg.Attributes());
            label(captions[index], center, 464, 14, '#b9c8dc');
        });
        label('Checkerboard visible through the corners = transparent pixels.', 540, 514, 15, '#b9c8dc');
        label('One offscreen port. Two images created once. Ordinary Port drawing updates the live image.',
            540, 540, 14, '#8195b2');
        return true;
    });

    // The visual session supplies page navigation, Space/click pause, and exit.
    // Standalone and automated smoke runs finish after displaying the comparison.
    if (!session) {
        function finish() {
            pdg.gfx.closeGraphicsPort(surface);
            pdg.gfx.closeGraphicsPort(port);
            pdg.quit();
        }
        pdg.onKeyPress(function(event) {
            if (event.unicode !== pdg.key_Escape) return false;
            finish();
            return true;
        });
        if (process.argv.indexOf('--wait') < 0) setTimeout(finish, 6000);
    }
    pdg.run();
})();
