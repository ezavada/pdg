var pdg = require('pdg');
var quick = require('../quick');
quick.requireRelease(pdg);
var quickOptions = quick.options(process.argv);
var benchmarkName = quickOptions.quick ? 'QuickPDGMark' : 'PDGMark';
if (quickOptions.quick) quick.uncap();
var quickSampler = new quick.Sampler(quickOptions);
var quickBaseline = quickOptions.quick ? quick.baseline('pdgmark/pdgmark_baseline.json').tests : {};
var quickResults = {};

// -----------------------------------------------
// PDGMark Performance Test
//
// Test PDG's 2D rendering API performance
//
// Tests 5 different aspects of 2D rendering:
// 1. Bitmap Rendering - Sprite/image drawing
// 2. Line Drawing - Lines, arcs, curves
// 3. Alpha Blending - Transparency and blend modes
// 4. Polygon Fills - Complex shapes with fills/gradients
// 5. Text Rendering - Text drawing with various styles
//
// Each test progressively adds complexity until 60 FPS
// -----------------------------------------------

console.log('=== ' + benchmarkName + ' PERFORMANCE TEST ===');

// Configuration
var TARGET_FPS = 60;
var FRAME_TIME_TARGET_MS = 1000 / TARGET_FPS;
var BASE_OBJECTS = 50;  // Base number of objects to add
var STATS_UPDATE_INTERVAL = 500;  // Update stats every 500ms
var MIN_FRAMES_PER_TEST = 60;  // Minimum frames before allowing test completion

// Calculate delay between object additions based on current FPS
function calculateAutoAddDelay(currentFPS) {
    if (currentFPS < 80) {
        return 2000;  // 2 seconds - near threshold, let it stabilize
    } else {
        return 1000;  // 1 second - add quickly
    }
}

// Calculate how many objects to add based on current FPS
function calculateObjectsToAdd(currentFPS) {
    if (currentFPS > 500) {
        return BASE_OBJECTS * 10;  // 500 objects - very fast, ramp up quickly
    } else if (currentFPS > 200) {
        return BASE_OBJECTS * 5;   // 250 objects - fast, add aggressively
    } else if (currentFPS > 100) {
        return BASE_OBJECTS * 3;   // 150 objects - moderate speed
    } else if (currentFPS > 70) {
        return BASE_OBJECTS * 2;   // 100 objects - getting close to threshold
    } else {
        return BASE_OBJECTS;       // 50 objects - near threshold, add carefully
    }
}

// Test weights (complexity multipliers for scoring)
var TEST_WEIGHTS = {
    bitmap: 1.0,      // Baseline
    drawing: 1.2,     // Lines/curves are more complex
    alpha: 1.3,       // Blending overhead
    polygon: 1.5,     // Tessellation + fills
    text: 1.4         // Font rendering overhead
};

// Global state
var port = null;
var testImage = null;
var currentTestIndex = 0;
var currentTestName = "";
var currentTestLabel = "";
var testStartTime = 0;
var lastAutoAddTime = 0;
var lastStatsUpdate = 0;
var testFrameCount = 0;
var testComplete = false;

// Test objects
var testObjects = [];
var benchmarkFinished = false;
var backgroundAttrs = null, overlayAttrs = null;
var overlayPositions = [];
var overlayObjectCount = -1, overlayCapacity = -1;
var overlayObjectLabel = "", overlayCapacityLabel = "";

function cleanupTestObjects() {
    for (var i = 0; i < testObjects.length; i++) {
        if (testObjects[i].dispose) testObjects[i].dispose();
    }
    testObjects = [];
}

function finishBenchmark() {
    if (benchmarkFinished) return;
    benchmarkFinished = true;
    cleanupTestObjects();
    quick.dispose(backgroundAttrs);
    quick.dispose(overlayAttrs);
    quick.dispose(testImage);
    backgroundAttrs = overlayAttrs = testImage = null;
    overlayPositions = [];
}

// Stats tracking
var frameCount = 0;
var totalFrameTime = 0;
var maxFrameTime = 0;
var minFrameTime = 999999;
var frameTimes = [];
var currentFPS = 60;
var currentFrameTimeMs = 0;
var objectsAt60FPS = 0;

// Test results
var allTestResults = [];
var testStartTimestamp = new Date().toISOString();
var globalStartTime = 0;

// Test definitions
var tests = [
    { name: "bitmap", title: "Bitmap Rendering", weight: TEST_WEIGHTS.bitmap, fn: runBitmapTest },
    { name: "drawing", title: "Line Drawing", weight: TEST_WEIGHTS.drawing, fn: runDrawingTest },
    { name: "alpha", title: "Alpha Blending", weight: TEST_WEIGHTS.alpha, fn: runAlphaTest },
    { name: "polygon", title: "Polygon Fills", weight: TEST_WEIGHTS.polygon, fn: runPolygonTest },
    { name: "text", title: "Text Rendering", weight: TEST_WEIGHTS.text, fn: runTextTest }
];

console.log("Will run " + tests.length + " tests:");
for (var i = 0; i < tests.length; i++) {
    console.log("  " + (i+1) + ". " + tests[i].title + " (weight: " + tests[i].weight + "x)");
}
console.log("\nPress ESC to quit at any time\n");

// ============================================
// TEST 1: BITMAP RENDERING
// ============================================

function BitmapObject(image, bounds, imageWidth, imageHeight) {
    this.x = Math.random() * (bounds.width() - imageWidth);
    this.y = Math.random() * (bounds.height() - imageHeight);
    this.rotation = Math.random() * Math.PI * 2;
    this.rotationSpeed = (Math.random() - 0.5) * 0.1;
    this.scale = 0.5 + Math.random() * 0.5;
    this.image = image;
    this.position = new pdg.Point(this.x, this.y);
    var cx = this.x + imageWidth / 2, cy = this.y + imageHeight / 2;
    // Preserve R(center) * S(origin). AnimatedAttributes scales about its pivot,
    // so normalize that pivot and offset its location once at creation.
    var px = cx / this.scale, py = cy / this.scale;
    this.attrs = new pdg.AnimatedAttributes()
        .setCenterOffset(new pdg.Offset(px, py))
        .setLocation(new pdg.Point(cx - px, cy - py))
        .setScale(this.scale, this.scale);
}

BitmapObject.prototype.update = function() {
    this.rotation += this.rotationSpeed;
};

BitmapObject.prototype.draw = function(port) {
    // Reuse draw arguments and make one native state update per frame.
    // Avoiding allocations and repeated getters is key to high performance.
    this.attrs.setRotation(this.rotation);
    port.drawImage(this.image, this.position, this.attrs);
};

BitmapObject.prototype.dispose = function() {
    quick.dispose(this.attrs);
};

function addBitmapObjects(count, bounds) {
    // Every object shares this fixed image; query its dimensions once per batch.
    var imageWidth = testImage.getWidth(), imageHeight = testImage.getHeight();
    for (var i = 0; i < count; i++) {
        testObjects.push(new BitmapObject(testImage, bounds, imageWidth, imageHeight));
    }
}

function runBitmapTest(port) {
    // Update and draw all bitmap objects
    for (var i = 0; i < testObjects.length; i++) {
        testObjects[i].update();
        testObjects[i].draw(port);
    }
}

// ============================================
// TEST 2: CANVAS DRAWING (Lines, Arcs, Curves)
// ============================================

function DrawingObject(bounds) {
    this.type = Math.floor(Math.random() * 4); // 0=line, 1=arc, 2=spline, 3=bezier
    this.x = Math.random() * bounds.width();
    this.y = Math.random() * bounds.height();
    this.color = new pdg.Color(Math.random(), Math.random(), Math.random(), 0.8);
    this.thickness = 1 + Math.random() * 3;
    this.size = 20 + Math.random() * 80;
    this.angle = Math.random() * Math.PI * 2;
    this.angleSpeed = (Math.random() - 0.5) * 0.05;
    this.attrs = new pdg.Attributes().lineColor(this.color).lineThickness(this.thickness);
    this.center = new pdg.Point(this.x, this.y);
    this.point1 = new pdg.Point(this.x, this.y);
    this.point2 = new pdg.Point(this.x, this.y);
    if (this.type === 2) {
        // Keep the native spline and its vertex storage. Only the middle two
        // control points move; repeated allocations/native calls waste frame time.
        this.spline = new pdg.Spline();
        this.spline.addPoint(this.center);
        this.spline.addPoint(this.point1);
        this.spline.addPoint(this.point2);
        this.spline.addPoint(new pdg.Point(this.x, this.y + this.size));
    }
}

DrawingObject.prototype.update = function() {
    this.angle += this.angleSpeed;
};

DrawingObject.prototype.draw = function(port) {
    var attrs = this.attrs;
    
    var cx = this.x;
    var cy = this.y;
    var s = this.size;
    
    switch(this.type) {
        case 0: // Line
            var dx = Math.cos(this.angle) * s;
            var dy = Math.sin(this.angle) * s;
            this.point1.x = cx + dx; this.point1.y = cy + dy;
            this.point2.x = cx - dx; this.point2.y = cy - dy;
            port.drawLine(this.point1, this.point2, attrs);
            break;
        case 1: // Arc
            port.drawArc(this.center, s, s, this.angle, this.angle + Math.PI * 1.5, attrs);
            break;
        case 2: // Spline
            this.point1.x = cx + s * Math.cos(this.angle);
            this.point1.y = cy + s * Math.sin(this.angle);
            this.point2.x = cx + s * Math.cos(this.angle + 1);
            this.point2.y = cy + s * Math.sin(this.angle + 1);
            this.spline.setPoint(1, this.point1);
            this.spline.setPoint(2, this.point2);
            port.drawSpline(this.spline, attrs);
            break;
        case 3: // Circle (using ellipse)
            port.drawEllipse(this.center, s/2, s/2, attrs);
            break;
    }
};

DrawingObject.prototype.dispose = function() {
    quick.dispose(this.attrs);
    quick.dispose(this.spline);
};

function addDrawingObjects(count, bounds) {
    for (var i = 0; i < count; i++) {
        testObjects.push(new DrawingObject(bounds));
    }
}

function runDrawingTest(port) {
    for (var i = 0; i < testObjects.length; i++) {
        testObjects[i].update();
        testObjects[i].draw(port);
    }
}

// ============================================
// TEST 3: ALPHA BLENDING
// ============================================

function AlphaObject(bounds) {
    this.type = Math.floor(Math.random() * 2); // 0=rect, 1=ellipse
    this.x = Math.random() * bounds.width();
    this.y = Math.random() * bounds.height();
    this.width = 40 + Math.random() * 80;
    this.height = 40 + Math.random() * 80;
    this.color = new pdg.Color(Math.random(), Math.random(), Math.random(), 1.0);
    this.opacity = 0.3 + Math.random() * 0.5;
    this.blendMode = Math.floor(Math.random() * 6); // All blend modes
    this.rotation = Math.random() * Math.PI * 2;
    this.rotationSpeed = (Math.random() - 0.5) * 0.02;
    this.center = new pdg.Point(this.x + this.width/2, this.y + this.height/2);
    if (this.type === 0) this.rect = new pdg.Rect(this.x, this.y, this.x + this.width, this.y + this.height);
    // Geometry and styles are fixed. Retain them to avoid allocating wrappers
    // and repeating native style calls for every object on every frame.
    this.attrs = new pdg.AnimatedAttributes()
        .setCenterOffset(new pdg.Offset(this.center.x, this.center.y))
        .fillColor(this.color).fillOpacity(this.opacity).blendMode(this.blendMode);
}

AlphaObject.prototype.update = function() {
    this.rotation += this.rotationSpeed;
};

AlphaObject.prototype.draw = function(port) {
    this.attrs.setRotation(this.rotation);
    
    if (this.type === 0) {
        port.drawRect(this.rect, this.attrs);
    } else {
        port.drawEllipse(this.center, this.width/2, this.height/2, this.attrs);
    }
};

AlphaObject.prototype.dispose = function() {
    quick.dispose(this.attrs);
};

function addAlphaObjects(count, bounds) {
    for (var i = 0; i < count; i++) {
        testObjects.push(new AlphaObject(bounds));
    }
}

function runAlphaTest(port) {
    for (var i = 0; i < testObjects.length; i++) {
        testObjects[i].update();
        testObjects[i].draw(port);
    }
}

// ============================================
// TEST 4: POLYGON FILLS
// ============================================

function PolygonObject(bounds) {
    this.centerX = Math.random() * bounds.width();
    this.centerY = Math.random() * bounds.height();
    this.sides = 3 + Math.floor(Math.random() * 5); // 3-7 sides
    this.radius = 20 + Math.random() * 50;
    this.rotation = Math.random() * Math.PI * 2;
    this.rotationSpeed = (Math.random() - 0.5) * 0.03;
    this.useGradient = Math.random() > 0.5;
    
    if (this.useGradient) {
        this.color1 = new pdg.Color(Math.random(), Math.random(), Math.random(), 1.0);
        this.color2 = new pdg.Color(Math.random(), Math.random(), Math.random(), 1.0);
    } else {
        this.color = new pdg.Color(Math.random(), Math.random(), Math.random(), 0.8);
    }

    // These shapes only rotate. Reuse the native geometry and its tessellation;
    // avoiding allocations and repeated native calls is key to high performance.
    this.polygon = new pdg.Polygon();
    for (var i = 0; i < this.sides; i++) {
        var angle = (i / this.sides) * Math.PI * 2;
        var x = this.centerX + Math.cos(angle) * this.radius;
        var y = this.centerY + Math.sin(angle) * this.radius;
        this.polygon.addPoint(new pdg.Point(x, y));
    }

    this.attrs = new pdg.AnimatedAttributes()
        .setCenterOffset(new pdg.Offset(this.centerX, this.centerY))
        .lineColor(new pdg.Color(0, 0, 0, 0.5)).lineThickness(1);
    
    if (this.useGradient) {
        var start = new pdg.Point(this.centerX - this.radius, this.centerY);
        var end = new pdg.Point(this.centerX + this.radius, this.centerY);
        // Polygon gradients use screen coordinates, so this stays horizontal
        // while the retained contour rotates through its Attributes transform.
        this.attrs.fillGradient(start, this.color1, end, this.color2);
    } else {
        this.attrs.fillColor(this.color);
    }
}

PolygonObject.prototype.update = function() {
    this.rotation += this.rotationSpeed;
};

PolygonObject.prototype.draw = function(port) {
    // Set an absolute angle in one native call; avoid accumulated transforms
    // and the per-element conversion cost of passing a matrix every frame.
    this.attrs.setRotation(this.rotation);
    port.drawPolygon(this.polygon, this.attrs);
};

PolygonObject.prototype.dispose = function() {
    quick.dispose(this.attrs);
    quick.dispose(this.polygon);
};

function addPolygonObjects(count, bounds) {
    for (var i = 0; i < count; i++) {
        testObjects.push(new PolygonObject(bounds));
    }
}

function runPolygonTest(port) {
    for (var i = 0; i < testObjects.length; i++) {
        testObjects[i].update();
        testObjects[i].draw(port);
    }
}

// ============================================
// TEST 5: TEXT RENDERING
// ============================================

function TextObject(bounds) {
    this.x = Math.random() * bounds.width();
    this.y = Math.random() * bounds.height();
    this.text = "PDGMark " + Math.floor(Math.random() * 1000);
    this.size = 12 + Math.floor(Math.random() * 24);
    this.color = new pdg.Color(Math.random(), Math.random(), Math.random(), 0.9);
    this.rotation = (Math.random() - 0.5) * 0.5;
    this.rotationSpeed = (Math.random() - 0.5) * 0.01;
    this.style = [pdg.textStyle_Plain, pdg.textStyle_Bold, pdg.textStyle_Italic][Math.floor(Math.random() * 3)];
    // Text and styling are fixed. Avoid recreating native Attributes and Point
    // wrappers or repeating native style setters inside the drawing loop.
    this.position = new pdg.Point(this.x, this.y);
    this.attrs = new pdg.AnimatedAttributes()
        .setCenterOffset(new pdg.Offset(this.x, this.y))
        .textSize(this.size).textStyle(this.style).fillColor(this.color);
}

TextObject.prototype.update = function() {
    this.rotation += this.rotationSpeed;
};

TextObject.prototype.draw = function(port) {
    this.attrs.setRotation(this.rotation);
    port.drawText(this.text, this.position, this.attrs);
};

TextObject.prototype.dispose = function() {
    quick.dispose(this.attrs);
};

function addTextObjects(count, bounds) {
    for (var i = 0; i < count; i++) {
        testObjects.push(new TextObject(bounds));
    }
}

function runTextTest(port) {
    for (var i = 0; i < testObjects.length; i++) {
        testObjects[i].update();
        testObjects[i].draw(port);
    }
}

// ============================================
// STATISTICS & SCORING
// ============================================

function calculatePercentile(sortedArray, percentile) {
    if (sortedArray.length === 0) return 0;
    var index = Math.ceil((percentile / 100) * sortedArray.length) - 1;
    index = Math.max(0, Math.min(index, sortedArray.length - 1));
    return sortedArray[index];
}

function updateStats(frameTimeMs) {
    frameCount++;
    testFrameCount++;
    totalFrameTime += frameTimeMs;
    maxFrameTime = Math.max(maxFrameTime, frameTimeMs);
    minFrameTime = Math.min(minFrameTime, frameTimeMs);
    frameTimes.push(frameTimeMs);
    
    // Track max objects at 60 FPS
    if (frameTimeMs <= FRAME_TIME_TARGET_MS && testObjects.length > objectsAt60FPS) {
        objectsAt60FPS = testObjects.length;
    }
}

function resetTestStats() {
    frameCount = 0;
    testFrameCount = 0;
    totalFrameTime = 0;
    maxFrameTime = 0;
    minFrameTime = 999999;
    frameTimes = [];
    currentFPS = 60;
    currentFrameTimeMs = 0;
    objectsAt60FPS = 0;
    testStartTime = Date.now();
    lastAutoAddTime = testStartTime;
    lastStatsUpdate = testStartTime;
    testComplete = false;
}

function saveTestResults() {
    var testDuration = (Date.now() - testStartTime) / 1000;
    var meanFrameTime = totalFrameTime / frameCount;
    
    frameTimes.sort(function(a, b) { return a - b; });
    var p95 = calculatePercentile(frameTimes, 95);
    var p99 = calculatePercentile(frameTimes, 99);
    
    var test = tests[currentTestIndex];
    var score = Math.round(objectsAt60FPS * test.weight);
    
    var result = {
        testName: test.name,
        testTitle: test.title,
        weight: test.weight,
        objectsAt60FPS: objectsAt60FPS,
        score: score,
        durationSeconds: parseFloat(testDuration.toFixed(2)),
        totalFrames: frameCount,
        frameTime: {
            meanMs: parseFloat(meanFrameTime.toFixed(2)),
            minMs: parseFloat(minFrameTime.toFixed(2)),
            maxMs: parseFloat(maxFrameTime.toFixed(2)),
            percentile95Ms: parseFloat(p95.toFixed(2)),
            percentile99Ms: parseFloat(p99.toFixed(2))
        },
        averageFPS: parseFloat((1000 / meanFrameTime).toFixed(2))
    };
    
    allTestResults.push(result);
    
    console.log("\n" + "=".repeat(60));
    console.log("TEST " + (currentTestIndex + 1) + " COMPLETE: " + test.title);
    console.log("=".repeat(60));
    console.log("Objects at 60 FPS: " + objectsAt60FPS);
    console.log("Weight: " + test.weight + "x");
    console.log("Test Score: " + score);
    console.log("Duration: " + testDuration.toFixed(2) + "s");
    console.log("Avg FPS: " + result.averageFPS);
    console.log("Frame Time: " + meanFrameTime.toFixed(2) + "ms (95th: " + p95.toFixed(2) + "ms)");
    console.log("=".repeat(60) + "\n");
}

function printFinalResults() {
    var totalDuration = (Date.now() - globalStartTime) / 1000;
    var compositeScore = 0;
    
    console.log("\n" + "=".repeat(70));
    console.log("CANVASMARK TEST COMPLETE - ALL TESTS FINISHED");
    console.log("=".repeat(70));
    console.log("\nINDIVIDUAL TEST RESULTS:\n");
    
    for (var i = 0; i < allTestResults.length; i++) {
        var result = allTestResults[i];
        compositeScore += result.score;
        console.log((i+1) + ". " + result.testTitle);
        console.log("   Objects @ 60 FPS: " + result.objectsAt60FPS);
        console.log("   Weight: " + result.weight + "x");
        console.log("   Score: " + result.score);
        console.log("   Avg FPS: " + result.averageFPS);
        console.log("   Frame Time: " + result.frameTime.meanMs + "ms");
        console.log("");
    }
    
    console.log("=".repeat(70));
    console.log("COMPOSITE SCORE: " + compositeScore);
    console.log("Total Duration: " + totalDuration.toFixed(2) + " seconds");
    console.log("=".repeat(70) + "\n");
    
    // Save results to JSON
    var results = {
        testName: "PDG PDGMark",
        timestamp: testStartTimestamp,
        totalDurationSeconds: parseFloat(totalDuration.toFixed(2)),
        compositeScore: compositeScore,
        tests: {}
    };
    
    for (var i = 0; i < allTestResults.length; i++) {
        var result = allTestResults[i];
        results.tests[result.testName] = result;
    }
    
    var fs = require('fs');
    var resultsFile = 'test/perf_tests/pdgmark/pdgmark_results.json';
    try {
        fs.writeFileSync(resultsFile, JSON.stringify(results, null, 2));
        console.log("Results saved to: " + resultsFile);
        console.log("\nTo compare with baseline:");
        console.log("  node test/perf_tests/pdgmark/compare_results.js\n");
    } catch (e) {
        console.log("Warning: Could not save results to file:", e.message);
    }

    if (typeof global.pdgPerfReport === 'function') {
        global.pdgPerfReport(results);
    }

    return results;
}

// ============================================
// SETUP & MAIN LOOP
// ============================================

function setup() {
    console.log("Setting up graphics...");
    
    // Create window
    var windowRect = new pdg.Rect(1000, 800);
    port = pdg.gfx.createWindowPort(windowRect, benchmarkName);
    
    if (!port) {
        console.log("ERROR: Could not create window port");
        process.exit(1);
    }
    
    console.log("Window created: " + port.getDrawingArea().width() + "x" + port.getDrawingArea().height());
    
    // Load test image for bitmap test
    var imagePaths = [
        "test/data/test_image.png",
        "data/test_image.png",
        "../data/test_image.png",
        "../../data/test_image.png",
        "test_image.png"
    ];
    
    for (var i = 0; i < imagePaths.length; i++) {
        try {
            testImage = new pdg.Image(imagePaths[i]);
            console.log("Loaded test image from: " + imagePaths[i]);
            break;
        } catch (e) {
            // Try next path
        }
    }
    
    if (!testImage) {
        console.log("ERROR: Could not load test image from any path");
        process.exit(1);
    }
    
    // Reuse fixed background/HUD drawing arguments. Avoiding allocations and
    // repeated style calls matters even outside the per-object loops.
    backgroundAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.05, 0.05, 0.08, 1.0));
    overlayAttrs = new pdg.Attributes().textSize(16).textStyle(pdg.textStyle_Plain)
        .fillColor(new pdg.Color(0.3, 1.0, 0.3, 1.0));
    overlayPositions = [20, 50, 70, 90, 110, 130, 160, 180].map(function(y) { return new pdg.Point(10, y); });
    globalStartTime = Date.now();
    startNextTest();
}

function startNextTest() {
    // A manual-mode stabilization timer may still fire after Escape.
    if (benchmarkFinished) return;
    cleanupTestObjects();
    if (currentTestIndex >= tests.length) {
        finishBenchmark();
        if (quickOptions.quick) quick.write(quickOptions, 'pdgmark', quickResults);
        else { printFinalResults(); pdg.gfx.closeGraphicsPort(port); }
        pdg.quit();
        return;
    }
    
    resetTestStats();
    
    var test = tests[currentTestIndex];
    currentTestName = test.name;
    currentTestLabel = "Test " + (currentTestIndex + 1) + "/" + tests.length + ": " + test.title;
    
    console.log("Starting Test " + (currentTestIndex + 1) + "/" + tests.length + ": " + test.title);
    console.log(quickOptions.quick ? "Fixed load (quick)" : "Adaptively adding objects (50-500 per batch) until FPS drops below 60...");
    
    // Add initial batch
    var bounds = port.getDrawingArea();
    var count = BASE_OBJECTS;
    if (currentTestName === "text") {
        count = 10;  // Start very small for text
    }
    
    if (quickOptions.quick) {
        count = quick.load(quickOptions, quickBaseline[currentTestName].objectsAt60FPS, currentTestName);
        quickSampler.reset();
    }
    switch(currentTestName) {
        case "bitmap":
            addBitmapObjects(count, bounds);
            break;
        case "drawing":
            addDrawingObjects(count, bounds);
            break;
        case "alpha":
            addAlphaObjects(count, bounds);
            break;
        case "polygon":
            addPolygonObjects(count, bounds);
            break;
        case "text":
            addTextObjects(count, bounds);
            break;
    }
}

// Draw handler
var lastFrameTime = Date.now();

function onDraw(evt) {
    if (benchmarkFinished || evt.port !== port) return false;
    if (quickOptions.quick && quickSampler.tick()) {
        var reference = quickBaseline[currentTestName];
        quickResults[currentTestName] = quickSampler.result(testObjects.length,
            reference.objectsAt60FPS, reference.objectsAt60FPS * tests[currentTestIndex].weight);
        currentTestIndex++;
        startNextTest();
        return true;
    }

    
    if (quickOptions.quick && quickSampler.frames.length) {
        currentFrameTimeMs = quickSampler.elapsed / quickSampler.frames.length;
        currentFPS = 1000 / currentFrameTimeMs;
    }
    var frameStartTime = Date.now();
    var deltaTime = frameStartTime - lastFrameTime;
    lastFrameTime = frameStartTime;
    
    // Clear background
    var bounds = port.getDrawingArea();
    port.drawRect(bounds, backgroundAttrs);
    
    // Run current test
    if (currentTestIndex < tests.length) {
        tests[currentTestIndex].fn(port);
    }
    
    // Draw stats overlay
    var textAttrs = overlayAttrs;
    if (overlayObjectCount !== testObjects.length) {
        overlayObjectCount = testObjects.length;
        overlayObjectLabel = "Objects: " + overlayObjectCount;
    }
    if (overlayCapacity !== objectsAt60FPS) {
        overlayCapacity = objectsAt60FPS;
        overlayCapacityLabel = "Objects @ 60 FPS: " + overlayCapacity;
    }

    port.drawText(benchmarkName, overlayPositions[0], textAttrs);
    
    if (currentTestIndex < tests.length) {
        port.drawText(currentTestLabel, overlayPositions[1], textAttrs);
    }
    
    port.drawText(overlayObjectLabel, overlayPositions[2], textAttrs);
    port.drawText("FPS: " + currentFPS.toFixed(1), overlayPositions[3], textAttrs);
    port.drawText("Frame Time: " + currentFrameTimeMs.toFixed(2) + " ms", overlayPositions[4], textAttrs);
    port.drawText(overlayCapacityLabel, overlayPositions[5], textAttrs);
    
    if (!testComplete) {
        port.drawText(quickOptions.quick ? "Fixed load (quick)" : "Adding objects...", overlayPositions[6], textAttrs);
    } else {
        port.drawText("Test stabilizing...", overlayPositions[6], textAttrs);
    }

    port.drawText("Press ESC to quit", overlayPositions[7], textAttrs);
    
    if (quickOptions.quick) return true;

    // Calculate frame time
    var frameEndTime = Date.now();
    var frameTimeMs = frameEndTime - frameStartTime;
    
    // Update stats
    updateStats(frameTimeMs);
    currentFrameTimeMs = frameTimeMs;
    
    // Update current FPS periodically
    if (frameEndTime - lastStatsUpdate > STATS_UPDATE_INTERVAL) {
        if (frameTimeMs > 0) {
            currentFPS = 1000 / frameTimeMs;
        }
        lastStatsUpdate = frameEndTime;
    }
    
    // Auto-add objects if test not complete and enough time has passed
    var currentDelay = calculateAutoAddDelay(currentFPS);
    if (!testComplete && (frameEndTime - lastAutoAddTime) > currentDelay) {
        // Only add more if we're still at target FPS
        if (currentFPS >= TARGET_FPS) {
            var bounds = port.getDrawingArea();
            
            // Adaptively scale object count based on current FPS
            var count = calculateObjectsToAdd(currentFPS);
            
            // Text test uses fewer objects (they're more expensive)
            if (currentTestName === "text") {
                count = Math.max(10, Math.floor(count / 5));
            }
            
            switch(currentTestName) {
                case "bitmap":
                    addBitmapObjects(count, bounds);
                    break;
                case "drawing":
                    addDrawingObjects(count, bounds);
                    break;
                case "alpha":
                    addAlphaObjects(count, bounds);
                    break;
                case "polygon":
                    addPolygonObjects(count, bounds);
                    break;
                case "text":
                    addTextObjects(count, bounds);
                    break;
            }
            lastAutoAddTime = frameEndTime;
        } else if (testFrameCount >= MIN_FRAMES_PER_TEST) {
            // Test complete - save results and move to next test
            testComplete = true;
            console.log("Test threshold reached. Completing test...");
            
            // Wait a bit for stabilization, then proceed
            setTimeout(function() {
                saveTestResults();
                currentTestIndex++;
                startNextTest();
            }, 2000);
        }
    }
    
    return true;
}

// Key handler
function onKeyPress(evt) {
    if (benchmarkFinished) return false;
    if (evt.unicode == pdg.key_Escape) {
        finishBenchmark();
        if (quickOptions.quick) { process.exit(1); return true; }
        console.log("\nTest stopped by user.");
        if (allTestResults.length > 0) {
            printFinalResults();
        }
        pdg.gfx.closeGraphicsPort(port);
        pdg.quit();
        return true;
    }
    return false;
}

// Setup and run
setup();

pdg.on(pdg.eventType_PortDraw, onDraw);
pdg.on(pdg.eventType_KeyPress, onKeyPress);

console.log("\n" + benchmarkName + " started. Watch the window for live stats.");
console.log("Starting with Test 1: " + tests[0].title + "...\n");

pdg.run();
