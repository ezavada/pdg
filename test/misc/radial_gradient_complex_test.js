#!/usr/bin/env node
// Test radial gradient rendering with complex polygons

var pdg = require('pdg');

console.log("Complex Polygon Radial Gradient Test");
console.log("====================================");
console.log("This test draws various complex polygons with radial gradients");
console.log("You should see:");
console.log("1. Concave polygons (star, arrow, L-shape)");
console.log("2. Self-crossing polygons (star with crossed lines, figure-8)");
console.log("3. Complex shapes (spiral, curved shape)");

// Create a window port
var screenBounds = pdg.gfx.getScreenBounds(0);
var windowRect = new pdg.Rect(
    screenBounds.left + 100, 
    screenBounds.top + 100, 
    screenBounds.left + 1000, 
    screenBounds.top + 800
);
var port = pdg.gfx.createWindowPort(windowRect, "Complex Polygon Radial Gradient Test");

pdg.on(pdg.eventType_PortDraw, function(evt) {
    if (evt.port !== port) return false;
    
    // Black background
    port.drawRect(new pdg.Rect(0, 0, port.getDrawingArea().width(), port.getDrawingArea().height()), 
                  new pdg.Attributes().fillColor(new pdg.Color('black')));
    
    var titlePoint = new pdg.Point(port.getDrawingArea().width()/2, 30);
    var textAttrs = new pdg.Attributes()
        .textSize(24)
        .textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold)
        .fillColor("yellow");
    port.drawText("Complex Polygon Radial Gradient Test", titlePoint, textAttrs);

    var colors = [
        [new pdg.Color(1, 0, 0, 1), new pdg.Color(0, 0, 1, 1)],    // Red to Blue
        [new pdg.Color(0, 1, 0, 1), new pdg.Color(1, 1, 0, 1)],    // Green to Yellow
        [new pdg.Color(0, 0, 1, 1), new pdg.Color(1, 0, 1, 1)],    // Blue to Magenta
        [new pdg.Color(1, 1, 0, 1), new pdg.Color(0, 1, 1, 1)],    // Yellow to Cyan
        [new pdg.Color(1, 0.5, 0, 1), new pdg.Color(0.5, 0, 1, 1)] // Orange to Purple
    ];

    // Row 1: Concave Polygons
    var startY = 80;
    port.drawText("Concave Polygons", new pdg.Point(50, startY), 
                  new pdg.Attributes().textSize(16).fillColor("white"));
    startY += 25;
    
    // 5-pointed star
    var starCenter = new pdg.Point(120, startY + 60);
    var starRadius = 50;
    var star = new pdg.Polygon();
    for (var i = 0; i < 10; i++) {
        var angle = (i * Math.PI / 5) - Math.PI / 2;
        var r = (i % 2 === 0) ? starRadius : starRadius * 0.4;
        star.addPoint(new pdg.Point(
            starCenter.x + r * Math.cos(angle),
            starCenter.y + r * Math.sin(angle)
        ));
    }
    var gradAttrs = new pdg.Attributes()
        .fillRadialGradient(starCenter, colors[0][0], starRadius * 0.8, colors[0][1]);
    port.drawPolygon(star, gradAttrs);

    // Arrow shape
    var arrowCenter = new pdg.Point(280, startY + 60);
    var arrow = new pdg.Polygon();
    arrow.addPoint(new pdg.Point(arrowCenter.x - 40, arrowCenter.y - 30));
    arrow.addPoint(new pdg.Point(arrowCenter.x + 10, arrowCenter.y - 30));
    arrow.addPoint(new pdg.Point(arrowCenter.x + 10, arrowCenter.y - 50));
    arrow.addPoint(new pdg.Point(arrowCenter.x + 50, arrowCenter.y));
    arrow.addPoint(new pdg.Point(arrowCenter.x + 10, arrowCenter.y + 50));
    arrow.addPoint(new pdg.Point(arrowCenter.x + 10, arrowCenter.y + 30));
    arrow.addPoint(new pdg.Point(arrowCenter.x - 40, arrowCenter.y + 30));
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(arrowCenter, colors[1][0], 70, colors[1][1]);
    port.drawPolygon(arrow, gradAttrs);

    // L-shape
    var lCenter = new pdg.Point(440, startY + 60);
    var lShape = new pdg.Polygon();
    lShape.addPoint(new pdg.Point(lCenter.x - 50, lCenter.y - 50));
    lShape.addPoint(new pdg.Point(lCenter.x - 20, lCenter.y - 50));
    lShape.addPoint(new pdg.Point(lCenter.x - 20, lCenter.y + 20));
    lShape.addPoint(new pdg.Point(lCenter.x + 50, lCenter.y + 20));
    lShape.addPoint(new pdg.Point(lCenter.x + 50, lCenter.y + 50));
    lShape.addPoint(new pdg.Point(lCenter.x - 50, lCenter.y + 50));
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(lCenter, colors[2][0], 70, colors[2][1]);
    port.drawPolygon(lShape, gradAttrs);

    // Crescent (concave moon shape)
    var crescentCenter = new pdg.Point(600, startY + 60);
    var crescent = new pdg.Polygon();
    for (var i = 0; i <= 16; i++) {
        var angle = (i * Math.PI / 8) - Math.PI / 2;
        crescent.addPoint(new pdg.Point(
            crescentCenter.x + 50 * Math.cos(angle),
            crescentCenter.y + 50 * Math.sin(angle)
        ));
    }
    for (var i = 16; i >= 0; i--) {
        var angle = (i * Math.PI / 8) - Math.PI / 2;
        crescent.addPoint(new pdg.Point(
            crescentCenter.x + 35 * Math.cos(angle) + 15,
            crescentCenter.y + 35 * Math.sin(angle)
        ));
    }
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(crescentCenter, colors[3][0], 60, colors[3][1]);
    port.drawPolygon(crescent, gradAttrs);

    // Plus/Cross shape
    var crossCenter = new pdg.Point(760, startY + 60);
    var cross = new pdg.Polygon();
    var w = 20, len = 50;
    cross.addPoint(new pdg.Point(crossCenter.x - w, crossCenter.y - len));
    cross.addPoint(new pdg.Point(crossCenter.x + w, crossCenter.y - len));
    cross.addPoint(new pdg.Point(crossCenter.x + w, crossCenter.y - w));
    cross.addPoint(new pdg.Point(crossCenter.x + len, crossCenter.y - w));
    cross.addPoint(new pdg.Point(crossCenter.x + len, crossCenter.y + w));
    cross.addPoint(new pdg.Point(crossCenter.x + w, crossCenter.y + w));
    cross.addPoint(new pdg.Point(crossCenter.x + w, crossCenter.y + len));
    cross.addPoint(new pdg.Point(crossCenter.x - w, crossCenter.y + len));
    cross.addPoint(new pdg.Point(crossCenter.x - w, crossCenter.y + w));
    cross.addPoint(new pdg.Point(crossCenter.x - len, crossCenter.y + w));
    cross.addPoint(new pdg.Point(crossCenter.x - len, crossCenter.y - w));
    cross.addPoint(new pdg.Point(crossCenter.x - w, crossCenter.y - w));
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(crossCenter, colors[4][0], 60, colors[4][1]);
    port.drawPolygon(cross, gradAttrs);

    // Row 2: Self-crossing Polygons
    startY += 180;
    port.drawText("Self-Crossing Polygons", new pdg.Point(50, startY), 
                  new pdg.Attributes().textSize(16).fillColor("white"));
    startY += 25;

    // Self-crossing star (pentagram)
    var pentagramCenter = new pdg.Point(120, startY + 60);
    var pentagramRadius = 50;
    var pentagram = new pdg.Polygon();
    for (var i = 0; i < 5; i++) {
        var angle = (i * 4 * Math.PI / 5) - Math.PI / 2;
        pentagram.addPoint(new pdg.Point(
            pentagramCenter.x + pentagramRadius * Math.cos(angle),
            pentagramCenter.y + pentagramRadius * Math.sin(angle)
        ));
    }
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(pentagramCenter, colors[1][0], pentagramRadius * 0.8, colors[1][1]);
    port.drawPolygon(pentagram, gradAttrs);

    // Figure-8 / Infinity shape
    var figureCenter = new pdg.Point(280, startY + 60);
    var figure8 = new pdg.Polygon();
    for (var i = 0; i <= 32; i++) {
        var t = i * 2 * Math.PI / 32;
        var x = figureCenter.x + 50 * Math.sin(t);
        var y = figureCenter.y + 40 * Math.sin(t) * Math.cos(t);
        figure8.addPoint(new pdg.Point(x, y));
    }
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(figureCenter, colors[2][0], 60, colors[2][1]);
    port.drawPolygon(figure8, gradAttrs);

    // Bowtie / Hourglass
    var bowtieCenter = new pdg.Point(440, startY + 60);
    var bowtie = new pdg.Polygon();
    bowtie.addPoint(new pdg.Point(bowtieCenter.x - 50, bowtieCenter.y - 50));
    bowtie.addPoint(new pdg.Point(bowtieCenter.x + 50, bowtieCenter.y + 50));
    bowtie.addPoint(new pdg.Point(bowtieCenter.x + 50, bowtieCenter.y - 50));
    bowtie.addPoint(new pdg.Point(bowtieCenter.x - 50, bowtieCenter.y + 50));
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(bowtieCenter, colors[3][0], 60, colors[3][1]);
    port.drawPolygon(bowtie, gradAttrs);

    // Twisted square
    var twistedCenter = new pdg.Point(600, startY + 60);
    var twisted = new pdg.Polygon();
    twisted.addPoint(new pdg.Point(twistedCenter.x - 50, twistedCenter.y - 30));
    twisted.addPoint(new pdg.Point(twistedCenter.x + 30, twistedCenter.y - 50));
    twisted.addPoint(new pdg.Point(twistedCenter.x + 50, twistedCenter.y + 30));
    twisted.addPoint(new pdg.Point(twistedCenter.x - 30, twistedCenter.y + 50));
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(twistedCenter, colors[4][0], 60, colors[4][1]);
    port.drawPolygon(twisted, gradAttrs);

    // Complex self-crossing star (8-pointed)
    var starCenter2 = new pdg.Point(760, startY + 60);
    var star8 = new pdg.Polygon();
    for (var i = 0; i < 8; i++) {
        var angle = (i * 3 * Math.PI / 4) - Math.PI / 2;
        star8.addPoint(new pdg.Point(
            starCenter2.x + 50 * Math.cos(angle),
            starCenter2.y + 50 * Math.sin(angle)
        ));
    }
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(starCenter2, colors[0][0], 50, colors[0][1]);
    port.drawPolygon(star8, gradAttrs);

    // Row 3: Complex Shapes
    startY += 180;
    port.drawText("Complex Shapes", new pdg.Point(50, startY), 
                  new pdg.Attributes().textSize(16).fillColor("white"));
    startY += 25;

    // Spiral approximation
    var spiralCenter = new pdg.Point(120, startY + 60);
    var spiral = new pdg.Polygon();
    for (var i = 0; i <= 50; i++) {
        var angle = i * Math.PI / 5;
        var r = 5 + i * 0.8;
        spiral.addPoint(new pdg.Point(
            spiralCenter.x + r * Math.cos(angle),
            spiralCenter.y + r * Math.sin(angle)
        ));
    }
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(spiralCenter, colors[2][0], 50, colors[2][1]);
    port.drawPolygon(spiral, gradAttrs);

    // Heart shape
    var heartCenter = new pdg.Point(280, startY + 60);
    var heart = new pdg.Polygon();
    for (var i = 0; i <= 64; i++) {
        var t = i * 2 * Math.PI / 64;
        var x = heartCenter.x + 40 * 16 * Math.pow(Math.sin(t), 3) / 16;
        var y = heartCenter.y - 40 * (13 * Math.cos(t) - 5 * Math.cos(2*t) - 2 * Math.cos(3*t) - Math.cos(4*t)) / 16;
        heart.addPoint(new pdg.Point(x, y));
    }
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(heartCenter, colors[0][0], 50, colors[0][1]);
    port.drawPolygon(heart, gradAttrs);

    // Gear/Cog shape
    var gearCenter = new pdg.Point(440, startY + 60);
    var gear = new pdg.Polygon();
    var teeth = 8;
    for (var i = 0; i < teeth * 4; i++) {
        var angle = i * 2 * Math.PI / (teeth * 4);
        var r = (i % 4 < 2) ? 45 : 30;
        gear.addPoint(new pdg.Point(
            gearCenter.x + r * Math.cos(angle),
            gearCenter.y + r * Math.sin(angle)
        ));
    }
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(gearCenter, colors[3][0], 50, colors[3][1]);
    port.drawPolygon(gear, gradAttrs);

    // Flower/Petal shape
    var flowerCenter = new pdg.Point(600, startY + 60);
    var flower = new pdg.Polygon();
    for (var i = 0; i <= 64; i++) {
        var angle = i * 2 * Math.PI / 64;
        var r = 30 + 20 * Math.sin(5 * angle);
        flower.addPoint(new pdg.Point(
            flowerCenter.x + r * Math.cos(angle),
            flowerCenter.y + r * Math.sin(angle)
        ));
    }
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(flowerCenter, colors[4][0], 50, colors[4][1]);
    port.drawPolygon(flower, gradAttrs);

    // Lightning bolt
    var boltCenter = new pdg.Point(760, startY + 60);
    var bolt = new pdg.Polygon();
    bolt.addPoint(new pdg.Point(boltCenter.x - 10, boltCenter.y - 50));
    bolt.addPoint(new pdg.Point(boltCenter.x + 5, boltCenter.y - 10));
    bolt.addPoint(new pdg.Point(boltCenter.x + 30, boltCenter.y - 15));
    bolt.addPoint(new pdg.Point(boltCenter.x, boltCenter.y + 10));
    bolt.addPoint(new pdg.Point(boltCenter.x + 10, boltCenter.y + 50));
    bolt.addPoint(new pdg.Point(boltCenter.x - 5, boltCenter.y + 10));
    bolt.addPoint(new pdg.Point(boltCenter.x - 30, boltCenter.y + 15));
    gradAttrs = new pdg.Attributes()
        .fillRadialGradient(boltCenter, colors[1][0], 60, colors[1][1]);
    port.drawPolygon(bolt, gradAttrs);
    
    // Instructions
    var instructY = port.getDrawingArea().height() - 40;
    var instructAttrs = new pdg.Attributes().textSize(14).fillColor("gray");
    port.drawText("Press ESC or Q to exit", new pdg.Point(50, instructY), instructAttrs);
    
    return true;
});

pdg.on(pdg.eventType_KeyDown, function(evt) {
    if (evt.keyCode == pdg.key_Escape || evt.keyChar == 'q' || evt.keyChar == 'Q') {
        pdg.gfx.closeGraphicsPort(port);
        pdg.tm.quit();
        return true;
    }
    return false;
});

// Keep the app running
pdg.run();

