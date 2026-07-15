// Shape Fill & Transform Test Script
// Comprehensive test of shapes with different fill types and transformations
//
// Grid Layout: 8 columns (fill types) x 6 rows (transform types) = 48 shapes per page
//
// Fill Types (Columns):
//   1. Solid Fill
//   2. Linear Gradient
//   3. Radial Gradient
//   4. Texture fit_Fill
//   5. Texture fit_Inside
//   6. Texture fit_Overflow
//   7. Texture fit_Clipped
//   8. Texture fit_Tile
//
// Transform Types (Rows):
//   1. None (baseline)
//   2. Animated Opacity (0% → 100% → 0% over 5s)
//   3. Animated Rotation (0° → 360° → 0° over 5s)
//   4. Animated Scale (50% → 150% → 50% over 5s)
//   5. Animated Skew (horizontal & vertical over 5s)
//   6. Blend Mode Cycling (changes every 1s)
//
// Additional Animations (all shapes):
//   - Color cycling through hue spectrum (10s cycle)
//   - Line mode cycling (2s per mode)
//   - Line opacity cycling (2s cycle)
//
// KNOWN LIMITATIONS:
//   - Scale/Skew: PDG's scale() and skew() transforms don't have center parameters,
//     so they transform around global origin (0,0) instead of the object's center.
//     rotation() works correctly because it accepts a center point parameter.
//   - Blend Modes: The blendMode attribute exists but is not yet implemented in PDG's
//     renderer. Blend mode row will show shapes without blending effects.

console.log("=== SHAPE FILL & TRANSFORM TEST ===");

// =======================================================================================
// CONFIGURATION
// =======================================================================================

var CONFIG = {
    // Window dimensions
    windowWidth: 1200,
    windowHeight: 900,
    
    // Grid layout
    gridStartX: 40,
    gridStartY: 150,  // Closer to headers to fit everything
    cellWidth: 145,
    cellHeight: 118,  // Reduced to fit 6 rows
    shapeSize: 90,    // Slightly smaller shapes
    
    // Animation durations (milliseconds)
    opacityDuration: 5000,
    rotationDuration: 5000,
    scaleDuration: 5000,
    skewDuration: 5000,
    blendModeDuration: 1000,
    colorCycleDuration: 10000,
    lineModeDuration: 2000,
    textureChangeDuration: 2000,
    
    // Test timing
    testDuration: 30000,  // 30 seconds per test
    
    // Column/Row counts
    numColumns: 8,
    numRows: 6
};

// Check for command line parameters
var waitForUser = false;
var shapeToTest = null;

for (var i = 0; i < process.argv.length; i++) {
    if (process.argv[i] === '--wait') {
        waitForUser = true;
    } else if (process.argv[i] === '--shape' && i + 1 < process.argv.length) {
        shapeToTest = process.argv[i + 1];
    }
}

if (waitForUser) {
    console.log("Manual mode: Press SPACE to advance to next test, b to go back, ESC to quit");
} else {
    console.log("Auto mode: Tests will advance automatically (30s each), press any key to advance early, ESC to quit");
}

// =======================================================================================
// SHAPE DEFINITIONS
// =======================================================================================

var SHAPES = [
    { name: "Rectangle", id: "rect" },
    { name: "Quad", id: "quad" },
    { name: "Circle", id: "circle" },
    { name: "Ellipse", id: "ellipse" },
    { name: "Rounded Rectangle", id: "roundrect" },
    { name: "Pentagon", id: "pentagon" },
    { name: "Star", id: "star" },
    { name: "Pentagram", id: "pentagram" },
    { name: "Complex Polygon", id: "complex" },
    { name: "Spiral Polygon", id: "spiral" },
    { name: "Hourglass", id: "hourglass" },
    { name: "Self-Intersecting Hourglass", id: "selfintersect" }
];

// Filter to specific shape if requested
if (shapeToTest) {
    var filtered = SHAPES.filter(function(s) { return s.id === shapeToTest; });
    if (filtered.length > 0) {
        SHAPES = filtered;
        console.log("Testing only shape: " + filtered[0].name);
    } else {
        console.log("Unknown shape: " + shapeToTest);
        console.log("Available shapes: " + SHAPES.map(function(s) { return s.id; }).join(", "));
        process.exit(1);
    }
}

// =======================================================================================
// TEXTURES
// =======================================================================================

var rocksTexture = new pdg.Image("test/data/rocks.png");
var yinYangTexture = new pdg.Image("test/data/test_image.png");
var earthTexture = new pdg.Image("test/earthmap2.png");
var canvasMarkTexture = new pdg.Image("test/perf/canvasmark2013/images/texture5.png");
var bunnyMarkTexture = new pdg.Image("test/perf/bunnymark/wabbit.png");

if (!rocksTexture || !yinYangTexture || !earthTexture) {
    console.log("ERROR: Could not load test textures");
    process.exit(1);
}

// =======================================================================================
// ANIMATION UTILITIES
// =======================================================================================

// Get value oscillating 0 → 1 → 0 over duration
function getOscillatingValue(time, duration) {
    var phase = (time % duration) / duration;
    return phase < 0.5 ? phase * 2 : (1 - phase) * 2;
}

// Get value ramping 0 → 1 over duration (repeating)
function getRampingValue(time, duration) {
    return (time % duration) / duration;
}

// Get sine wave value oscillating -1 → 1 → -1
function getSineValue(time, duration) {
    var phase = (time % duration) / duration;
    return Math.sin(phase * Math.PI * 2);
}

// Get current hue for color cycling (0-360)
function getCurrentHue(time) {
    return (time % CONFIG.colorCycleDuration) / CONFIG.colorCycleDuration * 360;
}

// Convert HSV to RGB
function hsvToRgb(h, s, v) {
    var c = v * s;
    var x = c * (1 - Math.abs(((h / 60) % 2) - 1));
    var m = v - c;
    var r, g, b;
    
    if (h < 60) { r = c; g = x; b = 0; }
    else if (h < 120) { r = x; g = c; b = 0; }
    else if (h < 180) { r = 0; g = c; b = x; }
    else if (h < 240) { r = 0; g = x; b = c; }
    else if (h < 300) { r = x; g = 0; b = c; }
    else { r = c; g = 0; b = x; }
    
    return new pdg.Color(r + m, g + m, b + m, 1.0);
}

// Get current color for cycling
function getCyclingColor(time) {
    var hue = getCurrentHue(time);
    return hsvToRgb(hue, 0.8, 0.9);
}

// Get current line style
function getCyclingLineStyle(time) {
    var lineStyles = [
        pdg.lineStyle_None,
        pdg.lineStyle_Solid,
        pdg.lineStyle_Solid,
        pdg.lineStyle_Solid
    ];
    var lineThickness = [0, 1, 2, 4];
    
    var index = Math.floor((time % CONFIG.lineModeDuration) / (CONFIG.lineModeDuration / 4));
    return {
        style: lineStyles[index],
        thickness: lineThickness[index]
    };
}

// Get current line opacity (oscillating)
function getCyclingLineOpacity(time) {
    return getOscillatingValue(time, CONFIG.lineModeDuration);
}

// Get current blend mode for row 6
function getCyclingBlendMode(time) {
    var blendModes = [
        pdg.blendMode_Normal,
        pdg.blendMode_Additive,
        pdg.blendMode_Multiply,
        pdg.blendMode_Screen,
        pdg.blendMode_Darken,
        pdg.blendMode_Lighten
    ];
    var index = Math.floor((time % (CONFIG.blendModeDuration * blendModes.length)) / CONFIG.blendModeDuration);
    return blendModes[index];
}

function getCyclingTexture(time, textureNumber) {
    var textures = [
        rocksTexture,
        yinYangTexture,
        earthTexture,
        canvasMarkTexture,
        bunnyMarkTexture,
    ];
    var index = Math.floor((time % (CONFIG.textureChangeDuration * textures.length)) / CONFIG.textureChangeDuration) + textureNumber;
    if (index >= textures.length) {
        index = index - textures.length;
    }
    return textures[index];
}

// =======================================================================================
// FILL TYPE FUNCTIONS
// =======================================================================================

// Apply fill based on column index
function applyFillType(attrs, col, centerX, centerY, shapeWidth, shapeHeight, time) {
    var color = getCyclingColor(time);
    
    switch(col) {
        case 0: // Solid fill
            attrs.fillColor(color);
            break;
            
        case 1: // Linear gradient
            var startPt = new pdg.Point(centerX - shapeWidth/3, centerY - shapeHeight/3);
            var endPt = new pdg.Point(centerX + shapeWidth/3, centerY + shapeHeight/3);
            var color2 = hsvToRgb((getCurrentHue(time) + 120) % 360, 0.8, 0.9);
            attrs.fillGradient(startPt, color, endPt, color2);
            break;
            
        case 2: // Radial gradient
            var center = new pdg.Point(centerX, centerY);
            var radius = Math.max(shapeWidth, shapeHeight) / 2;
            var color2 = hsvToRgb((getCurrentHue(time) + 180) % 360, 0.8, 0.9);
            attrs.fillRadialGradient(center, color, radius, color2);
            break;
            
        case 3: // Texture fit_Fill
            attrs.texture(getCyclingTexture(time, 0)).fitType(pdg.fit_Fill);
            break;
            
        case 4: // Texture fit_Inside
            attrs.texture(getCyclingTexture(time, 1)).fitType(pdg.fit_Inside);
            break;
            
        case 5: // Texture fit_Overflow
            attrs.texture(getCyclingTexture(time, 2)).fitType(pdg.fit_Overflow);
            break;
            
        case 6: // Texture fit_Clipped
            attrs.texture(getCyclingTexture(time, 3)).fitType(pdg.fit_Clipped);
            break;
            
        case 7: // Texture fit_Tile
            attrs.texture(getCyclingTexture(time, 4)).fitType(pdg.fit_Tile);
            break;
    }
    
    return attrs;
}

// =======================================================================================
// TRANSFORM TYPE FUNCTIONS
// =======================================================================================

// Apply transform based on row index
function applyTransformType(attrs, row, centerX, centerY, time) {
    var center = new pdg.Point(centerX, centerY);
    
    switch(row) {
        case 0: // No transform
            break;
            
        case 1: // Animated opacity
            var opacity = getOscillatingValue(time, CONFIG.opacityDuration);
            attrs.fillOpacity(opacity);
            break;
            
        case 2: // Animated rotation
            var rotation = getOscillatingValue(time, CONFIG.rotationDuration) * Math.PI * 2;
            attrs.rotation(rotation, center);
            break;
            
        case 3: // Animated scale
            var scale = 0.5 + getOscillatingValue(time, CONFIG.scaleDuration);
            // Scale around the center point of the shape
            attrs.scale(scale, scale, center);
            break;
            
        case 4: // Animated skew
            // Skew primarily in X direction to show the shear effect clearly
            var skewX = getSineValue(time, CONFIG.skewDuration) * 0.5; // ±0.5 radians
            // Keep Y skew at 0 to show clean horizontal shear
            var skewY = 0;
            // Skew relative to center so the shape stays in place
            attrs.skew(skewX, skewY, center);
            break;
            
        case 5: // Blend mode cycling
            var blendMode = getCyclingBlendMode(time);
            attrs.blendMode(blendMode);
            break;
    }
    
    return attrs;
}

// =======================================================================================
// SHAPE GENERATION FUNCTIONS
// =======================================================================================

// Generate a rectangle shape bounds
function generateRect(centerX, centerY, width, height) {
    height = height - 20;
    var halfW = width / 2;
    var halfH = height / 2;
    return new pdg.Rect(centerX - halfW, centerY - halfH, centerX + halfW, centerY + halfH);
}

// Generate a quad (rectangle as 4 points)
function generateQuad(centerX, centerY, width, height) {
    var halfW = width / 2;
    var halfH = height / 2;
    return new pdg.Quad(
        new pdg.Point(centerX - halfW, centerY - halfH),
        new pdg.Point(centerX + halfW, centerY - halfH +  10),
        new pdg.Point(centerX + halfW, centerY + halfH - 10),
        new pdg.Point(centerX - halfW, centerY + halfH)
    );
}

// Generate a pentagon polygon
function generatePentagon(centerX, centerY, radius) {
    var polygon = new pdg.Polygon();
    for (var i = 0; i < 5; i++) {
        var angle = (i * 2 * Math.PI / 5) - Math.PI / 2;
        var x = centerX + Math.cos(angle) * radius;
        var y = centerY + Math.sin(angle) * radius;
        polygon.addPoint(new pdg.Point(x, y));
    }
    return polygon;
}

// Generate a star polygon
function generateStar(centerX, centerY, outerRadius, innerRadius) {
    var polygon = new pdg.Polygon();
    for (var i = 0; i < 10; i++) {
        var angle = (i * Math.PI / 5) - Math.PI / 2;
        var radius = (i % 2 === 0) ? outerRadius : innerRadius;
        var x = centerX + Math.cos(angle) * radius;
        var y = centerY + Math.sin(angle) * radius;
        polygon.addPoint(new pdg.Point(x, y));
    }
    return polygon;
}

// Generate a pentagram - 5 points only, connecting every other vertex
function generatePentagram(centerX, centerY, outerRadius) {
    var polygon = new pdg.Polygon();
    // Create 5 points on a circle
    var points = [];
    for (var i = 0; i < 5; i++) {
        var angle = (i * 2 * Math.PI / 5) - Math.PI / 2;
        points.push({
            x: centerX + Math.cos(angle) * outerRadius,
            y: centerY + Math.sin(angle) * outerRadius
        });
    }
    // Connect points in pentagram order: 0→2→4→1→3→0
    polygon.addPoint(new pdg.Point(points[0].x, points[0].y));
    polygon.addPoint(new pdg.Point(points[2].x, points[2].y));
    polygon.addPoint(new pdg.Point(points[4].x, points[4].y));
    polygon.addPoint(new pdg.Point(points[1].x, points[1].y));
    polygon.addPoint(new pdg.Point(points[3].x, points[3].y));
    return polygon;
}

// Generate a complex polygon with both convex and concave areas (crown/castle shape)
function generateComplexPolygon(centerX, centerY, size) {
    // Create a crown/castle battlement shape with indentations
    var w = size * 2 * 0.9;  // width
    var h = size * 2 * 0.8;  // height
    
    return new pdg.Polygon(
        // Bottom left
        new pdg.Point(centerX - w/2, centerY + h/2),
        // Left tower bottom
        new pdg.Point(centerX - w/2, centerY - h/4),
        // Left tower top
        new pdg.Point(centerX - w/3, centerY - h/2),
        // First indent (concave)
        new pdg.Point(centerX - w/6, centerY - h/4),
        // Center tower top
        new pdg.Point(centerX, centerY - h/2),
        // Second indent (concave)
        new pdg.Point(centerX + w/6, centerY - h/4),
        // Right tower top
        new pdg.Point(centerX + w/3, centerY - h/2),
        // Right tower bottom
        new pdg.Point(centerX + w/2, centerY - h/4),
        // Bottom right
        new pdg.Point(centerX + w/2, centerY + h/2),
        // Bottom indent (concave)
        new pdg.Point(centerX + w/4, centerY + h/3),
        // Bottom center
        new pdg.Point(centerX, centerY + h/2),
        // Bottom left indent (concave)
        new pdg.Point(centerX - w/4, centerY + h/3)
    );
}

// Generate spiral polygon with space between arms
function generateSpiralPolygon(centerX, centerY, maxRadius) {
    var polygon = new pdg.Polygon();
    var numTurns = 3;      // Number of full rotations
    var armWidth = 8;      // Width of each spiral arm in pixels
    var spacing = 12;      // Space between spiral arms in pixels
    var radiusPerTurn = (armWidth + spacing);  // How much radius increases per rotation
    
    // Calculate points along the outer edge of the spiral
    var pointsPerTurn = 12;
    var totalPoints = numTurns * pointsPerTurn;
    
    for (var i = 0; i <= totalPoints; i++) {
        var angle = (i / pointsPerTurn) * 2 * Math.PI;
        var turn = i / pointsPerTurn;
        var radius = turn * radiusPerTurn;
        
        if (radius <= maxRadius) {
            var x = centerX + Math.cos(angle) * radius;
            var y = centerY + Math.sin(angle) * radius;
            polygon.addPoint(new pdg.Point(x, y));
        }
    }
    
    // Add points along the inner edge going backwards to create the arm
    for (var i = totalPoints; i >= 0; i--) {
        var angle = (i / pointsPerTurn) * 2 * Math.PI;
        var turn = i / pointsPerTurn;
        var outerRadius = turn * radiusPerTurn;
        var innerRadius = Math.max(0, outerRadius - armWidth);
        
        if (outerRadius <= maxRadius) {
            var x = centerX + Math.cos(angle) * innerRadius;
            var y = centerY + Math.sin(angle) * innerRadius;
            polygon.addPoint(new pdg.Point(x, y));
        }
    }
    
    return polygon;
}

// Generate hourglass polygon
function generateHourglass(centerX, centerY, width, height) {
    var halfW = width / 2;
    var halfH = height / 2;
    var waist = width * 0.2;
    
    return new pdg.Polygon(
        new pdg.Point(centerX - halfW, centerY - halfH),
        new pdg.Point(centerX + halfW, centerY - halfH),
        new pdg.Point(centerX + waist, centerY),
        new pdg.Point(centerX + halfW, centerY + halfH),
        new pdg.Point(centerX - halfW, centerY + halfH),
        new pdg.Point(centerX - waist, centerY)
    );
}

// Generate self-intersecting hourglass
function generateSelfIntersectingHourglass(centerX, centerY, width, height) {
    var halfW = width / 2;
    var halfH = height / 2;
    
    return new pdg.Polygon(
        new pdg.Point(centerX - halfW, centerY - halfH),
        new pdg.Point(centerX + halfW, centerY - halfH),
        new pdg.Point(centerX - halfW, centerY + halfH),
        new pdg.Point(centerX + halfW, centerY + halfH)
    );
}

// =======================================================================================
// DRAWING FUNCTIONS
// =======================================================================================

// Draw a single shape at grid position
function drawShapeAtCell(port, row, col, shapeId, time) {
    var cellCenterX = CONFIG.gridStartX + col * CONFIG.cellWidth + CONFIG.cellWidth / 2;
    var cellCenterY = CONFIG.gridStartY + row * CONFIG.cellHeight + CONFIG.cellHeight / 2;
    
    var shapeWidth = CONFIG.shapeSize;
    var shapeHeight = CONFIG.shapeSize;
    
    // Draw 6 background color bars for each row (black, gray, white, red, green, blue)
    var barWidth = 15;
    var barColors = [
        new pdg.Color(0, 0, 0, 1),      // black
        new pdg.Color(0.5, 0.5, 0.5, 1), // gray
        new pdg.Color(1, 1, 1, 1),      // white
        new pdg.Color(1, 0, 0, 1),      // red
        new pdg.Color(0, 1, 0, 1),      // green
        new pdg.Color(0, 0, 1, 1)       // blue
    ];
    
    var cellLeft = CONFIG.gridStartX + col * CONFIG.cellWidth;
    var cellTop = CONFIG.gridStartY + row * CONFIG.cellHeight;
    var cellHeight = CONFIG.cellHeight;
    
    for (var i = 0; i < 6; i++) {
        var barLeft = cellLeft + i * barWidth + 25;
        var barRect = new pdg.Rect(barLeft, cellTop, barLeft + barWidth, cellTop + cellHeight);
        var barAttrs = new pdg.Attributes().fillColor(barColors[i]);
        port.drawRect(barRect, barAttrs);
    }
    
    // For blend mode row, draw a background shape to show blending
    if (false) { //row === 5) {
        var bgRect = generateRect(cellCenterX, cellCenterY, shapeWidth * 0.8, shapeHeight * 0.8);
        var bgAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.3, 0.3, 0.3, 1.0));
        port.drawRect(bgRect, bgAttrs);
    }
    
    // Create attributes
    var attrs = new pdg.Attributes();
    
    // Apply fill type based on column
    applyFillType(attrs, col, cellCenterX, cellCenterY, shapeWidth, shapeHeight, time);
    
    // Apply transform type based on row
    applyTransformType(attrs, row, cellCenterX, cellCenterY, time);
    
    // Apply cycling line style and opacity
    var lineInfo = getCyclingLineStyle(time);
    if (lineInfo.style !== pdg.lineStyle_None) {
        attrs.lineColor(new pdg.Color(1, 1, 1, 1))
            .lineStyle(lineInfo.style)
            .lineThickness(lineInfo.thickness)
            .lineOpacity(getCyclingLineOpacity(time));
    }
    
    // Draw the shape based on type
    switch(shapeId) {
        case "rect":
            var rect = generateRect(cellCenterX, cellCenterY, shapeWidth, shapeHeight);
            port.drawRect(rect, attrs);
            break;
            
        case "quad":
            var quad = generateQuad(cellCenterX, cellCenterY, shapeWidth, shapeHeight);
            port.drawQuad(quad, attrs);
            break;
            
        case "circle":
            port.drawCircle(new pdg.Point(cellCenterX, cellCenterY), shapeWidth / 2, attrs);
            break;
            
        case "ellipse":
            port.drawEllipse(new pdg.Point(cellCenterX, cellCenterY), 
                           shapeWidth / 2, shapeHeight / 2.5, attrs);
            break;
            
        case "roundrect":
            var rect = generateRect(cellCenterX, cellCenterY, shapeWidth, shapeHeight);
            attrs.roundedCorners(15);
            port.drawRect(rect, attrs);
            break;
            
        case "pentagon":
            var pentagon = generatePentagon(cellCenterX, cellCenterY, shapeWidth / 2);
            port.drawPolygon(pentagon, attrs);
            break;
            
        case "star":
            var star = generateStar(cellCenterX, cellCenterY, shapeWidth / 2, shapeWidth / 4);
            port.drawPolygon(star, attrs);
            break;
            
        case "pentagram":
            var pentagram = generatePentagram(cellCenterX, cellCenterY, shapeWidth / 2);
            port.drawPolygon(pentagram, attrs);
            break;
            
        case "complex":
            var complex = generateComplexPolygon(cellCenterX, cellCenterY, shapeWidth / 2);
            port.drawPolygon(complex, attrs);
            break;
            
        case "spiral":
            var spiral = generateSpiralPolygon(cellCenterX, cellCenterY, shapeWidth / 2);
            port.drawPolygon(spiral, attrs);
            break;
            
        case "hourglass":
            var hourglass = generateHourglass(cellCenterX, cellCenterY, shapeWidth * 0.8, shapeHeight);
            port.drawPolygon(hourglass, attrs);
            break;
            
        case "selfintersect":
            var selfIntersect = generateSelfIntersectingHourglass(cellCenterX, cellCenterY, shapeWidth * 0.8, shapeHeight);
            port.drawPolygon(selfIntersect, attrs);
            break;
    }
}

// Draw the complete grid for current shape
function drawShapeGrid(port, shapeInfo, time) {
    // Clear background
    var portRect = port.getDrawingArea();
    var bgAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.1, 0.1, 0.15, 1.0));
    port.drawRect(portRect, bgAttrs);
    
    // Draw main title (baseline position - text extends above this)
    var mainTitleY = 55;  // Moved down 20px
    var mainTitleAttrs = new pdg.Attributes()
        .textSize(22)
        .textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold)
        .fillColor("white");
    port.drawText("Shape Fill & Transform Test", 
                  new pdg.Point(CONFIG.windowWidth / 2, mainTitleY), mainTitleAttrs);
    
    // Draw shape name and test number (baseline position)
    var testNumber = (currentTestIndex + 1) + "/" + SHAPES.length;
    var shapeTitleY = 95;  // Moved down 20px
    var shapeTitleAttrs = new pdg.Attributes()
        .textSize(28)
        .textStyle(pdg.textStyle_Centered + pdg.textStyle_Bold)
        .fillColor(new pdg.Color(1.0, 0.8, 0.2, 1.0));
    port.drawText(shapeInfo.name + " (" + testNumber + ")", 
                  new pdg.Point(CONFIG.windowWidth / 2, shapeTitleY), shapeTitleAttrs);
    
    // Draw column headers (moved down 10px)
    var headerY = CONFIG.gridStartY - 10;
    var headerAttrs = new pdg.Attributes()
        .textSize(10)
        .textStyle(pdg.textStyle_Centered)
        .fillColor(new pdg.Color(0.8, 0.8, 0.8, 1.0));
    
    var columnHeaders = ["Solid", "Linear", "Radial", "fit_Fill", "fit_Inside", "fit_Overflow", "fit_Clipped", "fit_Tile"];
    for (var col = 0; col < CONFIG.numColumns; col++) {
        var x = CONFIG.gridStartX + col * CONFIG.cellWidth + CONFIG.cellWidth / 2;
        port.drawText(columnHeaders[col], new pdg.Point(x, headerY), headerAttrs);
    }
    
    // Draw row headers
    var rowLabelX = CONFIG.gridStartX - 35;
    var rowHeaderAttrs = new pdg.Attributes()
        .textSize(10)
        .textStyle(pdg.textStyle_Plain)
        .fillColor(new pdg.Color(0.8, 0.8, 0.8, 1.0));
    
    var rowHeaders = ["None", "Opacity", "Rotation", "Scale", "Skew", "Blend"];
    for (var row = 0; row < CONFIG.numRows; row++) {
        var y = CONFIG.gridStartY + row * CONFIG.cellHeight + CONFIG.cellHeight / 2;
        port.drawText(rowHeaders[row], new pdg.Point(rowLabelX, y), rowHeaderAttrs);
    }
    
    // Draw all shapes in grid
    for (var row = 0; row < CONFIG.numRows; row++) {
        for (var col = 0; col < CONFIG.numColumns; col++) {
            drawShapeAtCell(port, row, col, shapeInfo.id, time);
        }
    }
    
    // Draw footer with current animation info
    var footerY = CONFIG.windowHeight - 30;
    var footerAttrs = new pdg.Attributes()
        .textSize(11)
        .textStyle(pdg.textStyle_Centered)
        .fillColor(new pdg.Color(0.6, 0.6, 0.6, 1.0));
    
    var currentHue = Math.floor(getCurrentHue(time));
    var currentBlend = Math.floor((time % (CONFIG.blendModeDuration * 6)) / CONFIG.blendModeDuration);
    var blendNames = ["Normal", "Additive", "Multiply", "Screen", "Darken", "Lighten"];
    
    var infoText = "Color Hue: " + currentHue + "° | Blend Mode: " + blendNames[currentBlend] + 
                   " | " + (waitForUser ? "Press SPACE to continue" : "Press any key to advance, ESC to quit");
    port.drawText(infoText, new pdg.Point(CONFIG.windowWidth / 2, footerY), footerAttrs);
}

// =======================================================================================
// MAIN TEST RUNNER
// =======================================================================================

var port = null;
var currentTestIndex = 0;
var testStartTime = 0;
var testTimeout = null;

function createPort() {
    var windowRect = new pdg.Rect(0, 0, CONFIG.windowWidth, CONFIG.windowHeight);
    var screenBounds = pdg.gfx.getScreenBounds(0);
    windowRect.center(screenBounds);
    
    port = pdg.gfx.createWindowPort(windowRect, "Shape Fill & Transform Test");
    
    if (!port) {
        console.log("ERROR: Could not create window port");
        process.exit(1);
    }
    
    console.log("Window port created");
}

function setupDrawHandler() {
    return pdg.on(pdg.eventType_PortDraw, function(evt) {
        if (evt.port !== port) return false;
        
        var currentTime = Date.now();
        var elapsedTime = currentTime - testStartTime;
        
        var shapeInfo = SHAPES[currentTestIndex];
        drawShapeGrid(port, shapeInfo, elapsedTime);
        
        return true;
    });
}

function setupKeyHandler() {
    return pdg.on(pdg.eventType_KeyPress, function(evt) {
        if (evt.unicode == pdg.key_Escape) {
            console.log("ESC pressed - quitting...");
            if (testTimeout) {
                clearTimeout(testTimeout);
            }
            pdg.gfx.closeGraphicsPort(port);
            pdg.quit();
        } else if (waitForUser) {
            if (evt.unicode == 32) { // Space key
                advanceToNextTest();
            }
        } else {
            // Any key advances in auto mode
            advanceToNextTest();
        }
        return true;
    });
}

function advanceToNextTest() {
    if (testTimeout) {
        clearTimeout(testTimeout);
        testTimeout = null;
    }
    
    currentTestIndex++;
    
    if (currentTestIndex >= SHAPES.length) {
        console.log("All tests completed!");
        pdg.gfx.closeGraphicsPort(port);
        pdg.quit();
        return;
    }
    
    startCurrentTest();
}

function startCurrentTest() {
    testStartTime = Date.now();
    console.log("Starting test " + (currentTestIndex + 1) + "/" + SHAPES.length + ": " + SHAPES[currentTestIndex].name);
    
    if (!waitForUser) {
        testTimeout = setTimeout(function() {
            advanceToNextTest();
        }, CONFIG.testDuration);
    }
}

// Start the test sequence
console.log("Starting shape fill & transform tests...");
console.log("Testing " + SHAPES.length + " shape(s)");

createPort();
setupDrawHandler();
setupKeyHandler();
startCurrentTest();

pdg.run();

