// Astra: an original anime portrait made entirely with PDG drawing primitives.
// Run from the repository root: ./pdg test/js/anime-character-demo.js
// Live AnimatedAttributes add blinks, a warmer smile, and occasional light breezes.
// Escape closes the window. Add --ui-test for a short animated rendering check.
// No images, fonts, or other external assets are required.
if (typeof pdg === 'undefined') global.pdg = require('pdg');

(function () {
    'use strict';
    var W = 760, H = 860;
    var P = function (x, y) { return new pdg.Point(x, y); };
    var palette = {
        ink: '#24243e', hair: '#414771', darkHair: '#303454',
        hairLight: '#697caa', hairShine: '#a6bada',
        skin: '#ffe1ce', skinShade: '#edb3a9', skinLight: '#fff0df',
        teal: '#47cbbf', gold: '#f2c777', cream: '#fff8eb'
    };
    var drawing = pdg.createDrawing();
    var animationLoops = [];
    var openingPause = 5.0;
    var blink = { delay: 2.4, close: 0.10, hold: 0.07, open: 0.16 };
    var firstBlinkEnd = openingPause + blink.close + blink.hold + blink.open;

    // Retain each moving group once, including its separate colors and strokes.
    // addDrawing() copies its attributes; explicitly opt into the live source.
    function liveGroup(pivot, paint) {
        var parent = drawing;
        drawing = pdg.createDrawing();
        paint();
        var group = drawing;
        drawing = parent;
        var attributes = new pdg.AnimatedAttributes();
        attributes.setCenterOffset(new pdg.Offset(pivot.x, pivot.y));
        drawing.addDrawing(group.getBounds(), group, attributes).setLiveAttributes(attributes);
        return attributes;
    }

    function loop(attributes, schedule) {
        // Schedules return their duration, including any quiet interval.
        animationLoops.push({ attributes: attributes,
            remaining: schedule(), schedule: schedule });
    }

    // All locks feel the same occasional gust, with small differences in lag.
    // Vary the calm interval, strength, and duration instead of rocking steadily.
    // The first breeze starts as her eyes reopen and is a little stronger.
    var initialGust = { pause: firstBlinkEnd, strength: 1.1, duration: 1.0 };
    var gusts = [
        { pause: 3.0, strength: 1.0, duration: 1.2 },
        { pause: 2.4, strength: 0.7, duration: 0.9 },
        { pause: 3.6, strength: 0.95, duration: 1.1 },
        { pause: 2.2, strength: 0.85, duration: 1.0 }
    ];
    function gustLength(gust) {
        // Five rotation stages plus time for the slowest lock to settle.
        return 2.75 * gust.duration + 0.2;
    }
    var smileStart = initialGust.pause + 1.5;
    function breeze(attributes, degrees, lag) {
        var nextGust = 0;
        loop(attributes, function () {
            var gust = nextGust === 0 ? initialGust : gusts[(nextGust - 1) % gusts.length];
            nextGust++;
            var angle = degrees * gust.strength * Math.PI / 180;
            var duration = gust.duration;
            attributes.wait(gust.pause + lag)
                .rotateTo(angle, 0.55 * duration, pdg.easeInOutSine)
                .andThen().rotateTo(angle * 0.65, 0.45 * duration, pdg.easeInOutSine)
                .andThen().rotateTo(angle * 0.85, 0.35 * duration, pdg.easeInOutSine)
                .andThen().rotateTo(-angle * 0.08, 0.9 * duration, pdg.easeInOutSine)
                .andThen().rotateTo(0, 0.5 * duration, pdg.easeInOutSine);
            // A shared duration keeps the gusts synchronized despite each lag.
            return gust.pause + gustLength(gust);
        });
    }

    function animate(seconds) {
        // Step each source once per update, not once per shape or draw replay.
        // Split at loop boundaries so the schedules do not drift with frame rate.
        animationLoops.forEach(function (track) {
            var remaining = seconds;
            while (remaining > 0) {
                var step = Math.min(remaining, track.remaining);
                track.attributes.animate(step);
                remaining -= step;
                track.remaining -= step;
                if (track.remaining < 1e-8) {
                    track.attributes.cancelSchedule();
                    track.remaining = track.schedule();
                }
            }
        });
        // This expression changes once, then holds through later blinks.
        smile.animate(seconds);
        dimples.animate(seconds);
    }

    function ink(fill, stroke, width) {
        var a = new pdg.Attributes().fillOpacity(fill ? 1 : 0);
        if (fill) a.fillColor(fill);
        if (stroke) a.lineColor(stroke).lineStyle(pdg.lineStyle_Solid).lineThickness(width || 2.5);
        else a.lineStyle(pdg.lineStyle_None);
        return a;
    }

    // Each path starts with [x,y]. Further pairs are straight endpoints;
    // six numbers are a cubic Bezier's two control points and endpoint.
    // PDG splines are strokes; Polygon.addSpline supplies curved filled shapes.
    function shape(commands, fill, stroke, width) {
        var polygon = new pdg.Polygon(), last = commands[0];
        polygon.addPoint(P(last[0], last[1]));
        commands.slice(1).forEach(function (c) {
            if (c.length === 2) polygon.addPoint(P(c[0], c[1]));
            else {
                var spline = new pdg.Spline(pdg.spline_CubicBezier);
                spline.addSegment(P(last[0], last[1]), P(c[0], c[1]), P(c[2], c[3]), P(c[4], c[5]));
                polygon.addSpline(spline, 0.035);
            }
            last = c.slice(-2);
        });
        drawing.addPolygon(polygon, ink(fill, stroke, width));
    }

    function curve(commands, color, width) {
        var spline = new pdg.Spline(pdg.spline_CubicBezier), last = commands[0];
        commands.slice(1).forEach(function (c) {
            spline.addSegment(P(last[0], last[1]), P(c[0], c[1]), P(c[2], c[3]), P(c[4], c[5]));
            last = c.slice(-2);
        });
        drawing.addSpline(spline, ink(null, color, width));
    }

    function oval(x, y, rx, ry, fill, stroke, width) {
        drawing.addEllipse(P(x, y), rx, ry, ink(fill, stroke, width));
    }

    function line(x, y, xx, yy, color, width) {
        drawing.addLine(P(x, y), P(xx, yy), ink(null, color, width));
    }

    function star(x, y, radius, fill, stroke, points) {
        var vertices = [], n = points || 4;
        for (var i = 0; i < n * 2; ++i) {
            var a = -Math.PI / 2 + i * Math.PI / n;
            var r = i % 2 ? radius * 0.38 : radius;
            vertices.push([x + Math.cos(a) * r, y + Math.sin(a) * r]);
        }
        shape(vertices, fill, stroke, 1.8);
    }

    // A warm paper backdrop and a quiet celestial frame.
    drawing.addRect(new pdg.Rect(0, 0, W, H), ink('#f6f1e9'));
    drawing.addRect(new pdg.Rect(22, 22, W - 22, H - 22), ink(null, '#d6cbd1', 1));
    oval(380, 383, 287, 287, '#e5e3ef');
    oval(380, 383, 266, 266, null, '#fcf9f1', 2);
    drawing.addArc(P(380, 383), 303, 303, -2.8, -0.45, ink(null, '#babdd4', 1.5));
    drawing.addArc(P(380, 383), 303, 303, 0.22, 2.66, ink(null, '#babdd4', 1.5));
    [[115,238,13], [626,194,17], [650,410,10], [113,531,18], [589,637,12], [175,128,8]]
        .forEach(function (s) { star(s[0], s[1], s[2], palette.gold); });
    [[144,335,4], [601,282,4], [667,342,3], [145,620,3], [206,197,3], [566,137,3]]
        .forEach(function (s) { oval(s[0], s[1], s[2], s[2], '#b8bdd3'); });
    line(89,471,113,471,'#b8bdd3',1); line(101,459,101,483,'#b8bdd3',1);
    oval(380, 746, 204, 13, '#d7d4df');

    // Back hair: broad silhouette, separate locks, and hard cel shadows.
    var backHair = liveGroup(P(380,160), function () {
        shape([[235,230], [240,119,344,99,400,126], [493,111,553,202,540,292],
            [523,409,584,533,582,650], [557,625], [568,674],
            [498,657,450,647,411,598], [362,677,245,704,188,665], [211,647],
            [165,643,173,602,184,566], [222,476,198,334,235,230]], palette.darkHair, palette.ink, 4);
        shape([[249,254], [244,390,263,522,215,631], [287,604,299,498,288,401],
            [313,328,294,274,249,254]], palette.hair);
        shape([[490,269], [523,403,510,564,554,627], [478,593,461,459,465,351]], palette.hair);
        curve([[239,371], [245,464,231,568,207,607]], palette.hairLight, 2);
        curve([[513,386], [502,469,522,565,536,586]], palette.hairLight, 2);
    });
    breeze(backHair, -1.0, 0.16);

    // Shade the whole neck up to its outline; the face covers its upper edge.
    // Paint only the lit lower area back in, leaving no pale rim under the chin.
    shape([[333,446], [334,478,336,499,315,518], [290,534], [361,592], [443,533],
        [414,510,413,480,423,450]], palette.skinShade, palette.ink, 3);
    shape([[334,510], [362,537], [414,505], [424,521], [381,568], [322,522]], palette.skin);
    // Clothing is deliberately layered underneath the face.
    shape([[305,512], [262,529,207,546,193,588], [169,645,166,702,165,736],
        [595,736], [592,677,584,613,561,578], [542,549,475,528,434,513],
        [381,568]], '#f8f4ee', palette.ink, 4);
    shape([[209,572], [194,631,194,684,196,736], [165,736], [168,659,181,600,209,572]], '#c9ccde');
    shape([[543,567], [579,608,589,682,595,736], [539,736], [551,650,538,616,526,597]], '#c9ccde');
    shape([[307,514], [381,569], [435,514], [484,534], [436,619], [383,652], [321,620], [263,536]],
        palette.darkHair, palette.ink, 3);
    shape([[307,514], [368,566], [333,598], [276,536]], '#58628b');
    shape([[435,514], [399,565], [428,600], [470,534]], '#58628b');
    curve([[285,539], [302,558,316,577,333,588]], '#e9e7ed', 3);
    curve([[463,539], [451,560,441,579,428,589]], '#e9e7ed', 3);
    shape([[350,552], [381,572], [409,549], [397,604], [364,604]], palette.cream, palette.ink, 2);
    line(218,632,207,723,'#888da9',2); line(536,631,552,721,'#888da9',2);
    curve([[236,652], [253,664,261,695,262,734]], '#b7bbcf', 2);
    curve([[508,652], [491,672,494,704,489,734]], '#b7bbcf', 2);
    line(379,652,379,736,'#b7bbcf',2);
    oval(393,691,3,3,palette.gold,palette.ink,1);
    oval(393,721,3,3,palette.gold,palette.ink,1);

    // Bow and its star-shaped brooch.
    shape([[376,609], [356,587,326,585,315,595], [307,612,312,638,327,644],
        [350,642,367,628,380,623]], palette.teal, palette.ink, 3);
    shape([[386,609], [409,587,439,585,449,598], [455,618,450,638,436,644],
        [415,638,398,631,384,623]], palette.teal, palette.ink, 3);
    shape([[365,629], [348,678], [375,665], [389,677], [394,627]], '#258e98', palette.ink, 2);
    shape([[392,627], [420,674], [424,656], [445,660], [409,624]], '#34afa9', palette.ink, 2);
    curve([[326,609], [342,607,350,611,369,618]], '#218992', 2);
    curve([[439,609], [422,607,413,613,395,619]], '#218992', 2);
    oval(382,619,15,16,palette.gold,palette.ink,2);
    star(382,618,10,palette.cream,null,5);

    // Ears, face, and a single warm shadow under the fringe.
    oval(259,363,22,35,palette.skin,palette.ink,3);
    oval(503,363,20,34,palette.skinShade,palette.ink,3);
    curve([[255,346], [237,343,249,375,261,377]], '#c88489', 2);
    curve([[504,346], [521,345,509,373,501,375]], '#c88489', 2);
    shape([[266,273], [265,207,320,172,381,179], [449,177,494,222,497,280],
        [499,340,489,391,468,422], [448,451,412,478,382,490],
        [348,481,307,449,284,414], [266,384,260,326,266,273]], palette.skin, palette.ink, 3.5);
    // Extend the shadow beneath the entire fringe, following the face's upper
    // outline. Only its lower boundary is exposed once the hair is drawn.
    shape([[266,273], [265,207,320,172,381,179], [449,177,494,222,497,280],
        [491,320], [429,318,382,289,341,262], [311,308,286,320,267,319]], palette.skinShade);
    shape([[479,330], [478,404,436,450,383,476], [361,471],
        [375,483,379,488,382,490], [430,468,466,435,479,404], [496,365,497,348,497,321]], '#f6c8b7');

    // Soft blush is a small stack of translucent ellipses.
    [300,458].forEach(function (x) {
        for (var i = 4; i > 0; --i) {
            drawing.addEllipse(P(x,405), 14 + i * 3, 5 + i * 1.4,
                ink('#ee8f9b').fillOpacity(0.055));
        }
        for (var j = 0; j < 3; ++j) line(x - 10 + j * 7,402,x - 13 + j * 7,410,'#d68e96',1);
    });

    // Eyes: almond whites, shaped irises, heavy upper lashes, and reflected stars.
    function eye(x, flip) {
        function path(points, fill, stroke, width) {
            shape(points.map(function (c) {
                return c.map(function (v, i) { return i % 2 ? v : x + flip * v; });
            }), fill, stroke, width);
        }
        path([[-42,351], [-22,331,17,331,39,351], [22,378,-17,384,-34,368]], '#fffaf1', palette.ink, 2);
        path([[-17,341], [-7,337,8,337,17,342], [25,357,17,377,1,378],
            [-16,376,-24,357,-17,341]], '#275e76', palette.ink, 1.6);
        path([[-18,355], [-7,362,9,362,20,351], [20,370,10,377,0,377], [-11,377,-16,367,-18,355]], palette.teal);
        path([[-14,365], [-4,371,7,371,16,363], [11,377,-7,379,-14,365]], '#9de6ca');
        oval(x,354,6.5,15,palette.ink);
        path([[-46,345], [-25,327,12,328,34,343], [43,345], [36,353],
            [11,337,-19,337,-38,355]], palette.ink);
        path([[-39,349], [-49,332], [-47,349], [-56,343], [-44,358]], palette.ink);
        oval(x + flip * -9,346,7,8,'#fffef6');
        oval(x + flip * 11,363,3,3,'#fffef6');
        star(x + flip * 3,371,4,'#e8ffe6');
        curve([[x-flip*23,379], [x-flip*10,384,x+flip*8,383,x+flip*17,379]], '#b97884', 1.5);
    }
    curve([[278,324], [298,312,325,311,342,321]], '#725064', 3);
    curve([[416,321], [435,310,461,312,478,323]], '#725064', 3);
    var eyes = liveGroup(P(380,354), function () {
        eye(313,1);
        eye(447,-1);
    });
    var firstBlink = true;
    loop(eyes, function () {
        var delay = firstBlink ? openingPause : blink.delay;
        firstBlink = false;
        // Keep a tiny nonzero height at closure; the lashes meet without a
        // singular transform. Closing is quicker than opening, as in a blink.
        eyes.wait(delay).changeScaleTo(1,0.025,blink.close,pdg.easeInQuad)
            .andThen().changeScaleTo(1,0.025,blink.hold,pdg.linearTween)
            .andThen().changeScaleTo(1,1,blink.open,pdg.easeOutQuad);
        // Extend only the opening cycle; keep the later blink cadence.
        return 4.6 + delay - blink.delay;
    });
    curve([[379,371], [377,386,369,394,378,397]], '#c78d8b', 1.8);
    line(380,398,385,397,'#c78d8b',1.5);
    oval(381,390,3,5,palette.skinLight);
    var smile = liveGroup(P(381,437), function () {
        curve([[359,431], [371,439,389,439,403,428]], '#a65e75', 2.2);
    });
    // Begin smiling 1.5 seconds into the first breeze, while her hair settles.
    smile.setScale(0.9,0.22);
    smile.wait(smileStart).changeScaleTo(1.25,1.45,1.5,pdg.easeInOutSine);
    var dimples = liveGroup(P(381,427), function () {
        curve([[350,423], [347,424,347,427,350,429]], '#b57f83', 1.4);
        curve([[413,419], [416,420,416,423,413,425]], '#b57f83', 1.4);
    });
    // Small cheek creases emerge as the smile grows, just outside its corners.
    dimples.lineOpacity(0).wait(smileStart + 0.3)
        .changeLineOpacity(0.5,1.2,pdg.easeInOutSine);
    curve([[372,446], [378,448,385,448,390,445]], '#fff4e3', 2.5);

    // Side-lock roots sit beneath the fringe, with enough overlap for the breeze.
    var leftLock = liveGroup(P(252,280), function () {
        shape([[244,276], [237,338,246,405,285,458], [270,411,273,364,281,307],
            [294,306], [305,244], [258,256]], palette.hair, palette.ink, 2.5);
        shape([[249,314], [248,357,257,392,266,407], [259,367,266,325,271,313]], palette.hairLight);
    });
    var rightLock = liveGroup(P(495,280), function () {
        shape([[497,277], [526,342,512,415,477,460], [493,415,483,356,482,308]], palette.hair, palette.ink, 2.5);
        shape([[504,319], [514,358,505,396,495,414], [501,373,492,339,492,315]], palette.hairLight);
    });

    // Front hair, individual tapered locks, and cool reflected light.
    shape([[237,323], [212,269,222,174,278,144], [302,116,349,109,381,128],
        [420,109,477,135,505,168], [544,212,531,283,508,337],
        [500,296,469,267,438,241], [449,275,464,300,479,315],
        [414,298,373,263,353,218], [349,261,320,288,283,311],
        [293,285,300,263,300,244], [273,279,258,304,237,323]], palette.hair, palette.ink, 3.5);
    shape([[353,218], [374,248,414,279,455,296], [416,251,401,211,385,166],
        [377,192,366,212,353,218]], '#535d8a');
    shape([[384,145], [426,134,478,159,498,199], [467,177,431,166,411,174],
        [442,187,473,209,488,236], [455,218,426,203,412,199], [395,180,390,160,384,145]], palette.hairLight);
    shape([[245,239], [252,186,290,155,338,148], [298,171,279,194,268,219],
        [291,205,302,202,313,203], [288,222,268,234,245,253]], palette.hairLight);
    shape([[269,198], [284,177,306,165,322,161], [302,176,292,187,287,198]], palette.hairShine);
    shape([[425,161], [448,165,470,178,481,191], [461,180,451,178,442,177]], palette.hairShine);
    curve([[373,142], [341,150,323,196,310,224]], '#303454', 2);
    curve([[390,145], [391,192,424,252,454,278]], '#303454', 2);
    curve([[271,256], [255,284,250,307,245,337]], '#8b9fc5', 2);

    // One curled ahoge above the crown.
    var crownCurl = liveGroup(P(365,130), function () {
        shape([[357,132], [339,100,354,83,380,86], [365,92,356,105,371,128]], palette.hair, palette.ink, 2);
    });
    // Her right is the viewer's left: the breeze pushes the tips screen-right.
    // The curl rises above its pivot, so its rotation has the opposite sign.
    breeze(leftLock, -2.2, 0);
    breeze(rightLock, -1.7, 0.12);
    breeze(crownCurl, 3.5, 0.05);

    // Gold barrette, little star, and dangling earring.
    line(466,246,504,278,palette.ink,8);
    line(466,246,504,278,palette.gold,5);
    star(485,253,20,palette.gold,palette.ink,5);
    star(485,252,9,palette.cream,null,5);
    oval(502,395,4,4,palette.gold,palette.ink,1);
    line(502,399,502,421,palette.gold,2);
    star(502,428,9,palette.gold,palette.ink,4);

    // The artwork is retained once and replayed during PortDraw, with aspect
    // ratio preserved on smaller screens and on high-DPI drawing surfaces.
    var screen = pdg.gfx.getScreenBounds(0);
    var scale = Math.min(1, (screen.width() - 60) / W, (screen.height() - 100) / H);
    scale = Math.max(0.25, scale);
    var windowRect = new pdg.Rect(Math.round(W * scale), Math.round(H * scale));
    windowRect.center(screen);
    var port = pdg.gfx.createWindowPort(windowRect, 'Astra - PDG anime portrait');
    if (!port) throw new Error('Could not create the portrait window');
    pdg.gfx.setTargetFPS(30);
    var frames = 0, automated = process.argv.indexOf('--ui-test') >= 0;
    var lastFrameTime = (pdg.visualTestSession ? pdg.visualTestSession.now() : Date.now());
    pdg.on(pdg.eventType_PortDraw, function (event) {
        if (event.port !== port) return false;
        var now = (pdg.visualTestSession ? pdg.visualTestSession.now() : Date.now());
        // Fixed steps make the smoke check repeatable; interactive playback uses
        // elapsed seconds, capped after a window drag or suspension.
        animate(automated ? 1 / 30 : Math.min(0.1, Math.max(0, (now - lastFrameTime) / 1000)));
        lastFrameTime = now;
        var area = port.getDrawingArea();
        var s = Math.min(area.width() / W, area.height() / H);
        var left = area.left + (area.width() - W * s) / 2;
        var top = area.top + (area.height() - H * s) / 2;
        port.drawRect(area, ink('#f6f1e9'));
        port.drawDrawing(drawing, new pdg.Rect(left, top, left + W*s, top + H*s), new pdg.Attributes());
        function label(text, y, size, color, bold) {
            port.drawText(text, P(left + W*s/2, top + y*s),
                ink(color).textSize(size*s).textStyle(pdg.textStyle_Centered | (bold ? pdg.textStyle_Bold : 0)));
        }
        label('A S T R A', 64, 25, palette.ink, true);
        label('S T A R L I G H T   C O U R I E R', 787, 12, '#77768c');
        label('An original portrait in points, curves & color', 813, 11, '#96909c');
        // Include the first breeze, the smile, and a subsequent breeze.
        if (++frames === 390 && automated) {
            console.log('PASS: rendered animated Astra (blinking, smiling, and four live hair groups, ' + frames + ' frames)');
            pdg.quit();
        }
        return true;
    });
    pdg.on(pdg.eventType_KeyPress, function (event) {
        if (event.unicode !== pdg.key_Escape) return false;
        pdg.quit();
        return true;
    });
    console.log('Astra: ' + drawing.getElementCount() + ' PDG drawing elements. Escape to close.');
    pdg.run();
}());
