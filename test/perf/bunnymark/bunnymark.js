// -----------------------------------------------
// PDG Bunnymark Performance Test
//
// Classic sprite rendering benchmark that measures
// how many sprites can be rendered while maintaining
// 60 FPS (16.67ms per frame)
//
// Based on the standard Bunnymark test used across
// game engines (Unity, Godot, Phaser, etc.)
//
// -----------------------------------------------

console.log("=== PDG BUNNYMARK PERFORMANCE TEST ===");
console.log("Measuring sprite rendering throughput...\n");

// Configuration
var AUTO_ADD_BUNNIES = true;  // Auto-add until FPS drops
var BUNNIES_PER_BATCH = 100;  // How many to add at once
var TARGET_FPS = 60;
var MIN_FPS = 30;
var FRAME_TIME_TARGET_MS = 1000 / TARGET_FPS;  // 16.67ms
var FRAME_TIME_MIN_MS = 1000 / MIN_FPS;  // 33.33ms
var STATS_UPDATE_INTERVAL = 500;  // Update stats every 500ms
var AUTO_ADD_DELAY = 2000;  // Wait 2 seconds between auto-adds

// Check for command line options
for (var i = 0; i < process.argv.length; i++) {
    if (process.argv[i] === '--manual') {
        AUTO_ADD_BUNNIES = false;
        console.log("Manual mode: Press SPACE to add bunnies");
    } else if (process.argv[i] === '--batch' && i + 1 < process.argv.length) {
        BUNNIES_PER_BATCH = parseInt(process.argv[i + 1]);
        console.log("Batch size set to:", BUNNIES_PER_BATCH);
    }
}

if (AUTO_ADD_BUNNIES) {
    console.log("Auto mode: Will add " + BUNNIES_PER_BATCH + " bunnies every " + (AUTO_ADD_DELAY/1000) + " seconds until FPS drops below " + TARGET_FPS);
} else {
    console.log("Manual mode: Press SPACE to add " + BUNNIES_PER_BATCH + " bunnies");
}
console.log("Press ESC to quit and show final results\n");

// Bunny state
var bunnies = [];
var bunnyImage = null;
var port = null;

// Physics constants
var GRAVITY = 0.5;
var BOUNCE_DAMPING = 0.95;

// Stats tracking
var frameCount = 0;
var totalFrameTime = 0;
var maxFrameTime = 0;
var minFrameTime = 999999;
var droppedFrames = 0;
var lastStatsUpdate = 0;
var currentFPS = 60;
var currentFrameTimeMs = 0;
var frameTimes = [];  // For calculating percentiles
var maxBunniesAt60FPS = 0;
var maxBunniesAt30FPS = 0;
var testStartTime = 0;
var lastAutoAddTime = 0;

// Performance metrics
var metrics = {
    totalFrames: 0,
    meanFrameTime: 0,
    minFrameTime: 999999,
    maxFrameTime: 0,
    percentile95: 0,
    percentile99: 0,
    droppedFrames: 0,
    maxBunniesAt60FPS: 0,
    maxBunniesAt30FPS: 0,
    testDurationSeconds: 0
};

// Bunny constructor
function Bunny(image, bounds) {
    this.x = Math.random() * bounds.width();
    this.y = Math.random() * bounds.height();
    this.speedX = (Math.random() - 0.5) * 10;
    this.speedY = (Math.random() - 0.5) * 10 - 5; // Bias upward
    this.image = image;
}

Bunny.prototype.update = function(bounds) {
    // Apply gravity
    this.speedY += GRAVITY;
    
    // Update position
    this.x += this.speedX;
    this.y += this.speedY;
    
    // Bounce off walls
    var imgWidth = this.image.getWidth();
    var imgHeight = this.image.getHeight();
    
    if (this.x <= 0) {
        this.x = 0;
        this.speedX = Math.abs(this.speedX) * BOUNCE_DAMPING;
    } else if (this.x + imgWidth >= bounds.width()) {
        this.x = bounds.width() - imgWidth;
        this.speedX = -Math.abs(this.speedX) * BOUNCE_DAMPING;
    }
    
    if (this.y <= 0) {
        this.y = 0;
        this.speedY = Math.abs(this.speedY) * BOUNCE_DAMPING;
    } else if (this.y + imgHeight >= bounds.height()) {
        this.y = bounds.height() - imgHeight;
        this.speedY = -Math.abs(this.speedY) * BOUNCE_DAMPING;
    }
};

Bunny.prototype.draw = function(port) {
    var pos = new pdg.Point(this.x, this.y);
    port.drawImage(this.image, pos, new pdg.Attributes());
};

// Add bunnies
function addBunnies(count) {
    var bounds = port.getDrawingArea();
    for (var i = 0; i < count; i++) {
        bunnies.push(new Bunny(bunnyImage, bounds));
    }
    console.log("Added " + count + " bunnies. Total: " + bunnies.length);
}

// Calculate percentile
function calculatePercentile(sortedArray, percentile) {
    if (sortedArray.length === 0) return 0;
    var index = Math.ceil((percentile / 100) * sortedArray.length) - 1;
    index = Math.max(0, Math.min(index, sortedArray.length - 1));
    return sortedArray[index];
}

// Update statistics
function updateStats(frameTimeMs) {
    frameCount++;
    totalFrameTime += frameTimeMs;
    maxFrameTime = Math.max(maxFrameTime, frameTimeMs);
    minFrameTime = Math.min(minFrameTime, frameTimeMs);
    
    // Track frame time for percentile calculation
    frameTimes.push(frameTimeMs);
    
    // Count dropped frames (> 16.67ms = below 60 FPS)
    if (frameTimeMs > FRAME_TIME_TARGET_MS) {
        droppedFrames++;
    }
    
    // Track max bunnies at different FPS thresholds
    if (frameTimeMs <= FRAME_TIME_TARGET_MS && bunnies.length > maxBunniesAt60FPS) {
        maxBunniesAt60FPS = bunnies.length;
    }
    if (frameTimeMs <= FRAME_TIME_MIN_MS && bunnies.length > maxBunniesAt30FPS) {
        maxBunniesAt30FPS = bunnies.length;
    }
}

// Print final results
function printFinalResults() {
    console.log("\n" + "=".repeat(60));
    console.log("BUNNYMARK TEST RESULTS");
    console.log("=".repeat(60));
    
    // Calculate final metrics
    var testDuration = (Date.now() - testStartTime) / 1000;
    var meanFrameTime = totalFrameTime / frameCount;
    
    // Sort frame times for percentiles
    frameTimes.sort(function(a, b) { return a - b; });
    var p95 = calculatePercentile(frameTimes, 95);
    var p99 = calculatePercentile(frameTimes, 99);
    
    console.log("\nTest Duration: " + testDuration.toFixed(2) + " seconds");
    console.log("Total Frames: " + frameCount);
    console.log("\nFRAME TIME STATISTICS:");
    console.log("  Mean:        " + meanFrameTime.toFixed(2) + " ms");
    console.log("  Min:         " + minFrameTime.toFixed(2) + " ms");
    console.log("  Max:         " + maxFrameTime.toFixed(2) + " ms");
    console.log("  95th %ile:   " + p95.toFixed(2) + " ms");
    console.log("  99th %ile:   " + p99.toFixed(2) + " ms");
    console.log("\nPERFORMANCE METRICS:");
    console.log("  Average FPS:           " + (1000 / meanFrameTime).toFixed(2));
    console.log("  Dropped Frames:        " + droppedFrames + " (" + ((droppedFrames / frameCount) * 100).toFixed(1) + "%)");
    console.log("  Max Bunnies @ 60 FPS:  " + maxBunniesAt60FPS);
    console.log("  Max Bunnies @ 30 FPS:  " + maxBunniesAt30FPS);
    console.log("  Final Bunny Count:     " + bunnies.length);
    
    console.log("\nKEY METRIC (Bunnymark Score): " + maxBunniesAt60FPS + " sprites @ 60 FPS");
    console.log("=".repeat(60) + "\n");
    
    // Export results to JSON
    var results = {
        testName: "PDG Bunnymark",
        timestamp: new Date().toISOString(),
        testDurationSeconds: testDuration,
        totalFrames: frameCount,
        frameTime: {
            meanMs: parseFloat(meanFrameTime.toFixed(2)),
            minMs: parseFloat(minFrameTime.toFixed(2)),
            maxMs: parseFloat(maxFrameTime.toFixed(2)),
            percentile95Ms: parseFloat(p95.toFixed(2)),
            percentile99Ms: parseFloat(p99.toFixed(2))
        },
        performance: {
            averageFPS: parseFloat((1000 / meanFrameTime).toFixed(2)),
            droppedFrames: droppedFrames,
            droppedFramePercent: parseFloat(((droppedFrames / frameCount) * 100).toFixed(1)),
            maxBunniesAt60FPS: maxBunniesAt60FPS,
            maxBunniesAt30FPS: maxBunniesAt30FPS,
            finalBunnyCount: bunnies.length
        },
        bunnymarkScore: maxBunniesAt60FPS
    };
    
    // Save results
    var fs = require('fs');
    var resultsFile = 'test/perf/bunnymark/bunnymark_results.json';
    try {
        fs.writeFileSync(resultsFile, JSON.stringify(results, null, 2));
        console.log("Results saved to: " + resultsFile);
    } catch (e) {
        console.log("Warning: Could not save results to file:", e.message);
    }
}

// Setup graphics
function setup() {
    console.log("Setting up graphics...");
    
    // Create window
    var windowRect = new pdg.Rect(800, 600);
    port = pdg.gfx.createWindowPort(windowRect, "PDG Bunnymark Test");
    
    if (!port) {
        console.log("ERROR: Could not create window port");
        process.exit(1);
    }
    
    console.log("Window created: " + port.getDrawingArea().width() + "x" + port.getDrawingArea().height());
    
    // Load bunny image - try multiple paths
    // Using the classic Bunnymark wabbit.png sprite (26x37)
    var imagePaths = [
        "test/perf/bunnymark/wabbit.png",
        "perf/bunnymark/wabbit.png",
        "bunnymark/wabbit.png",
        "wabbit.png"
    ];
    
    for (var i = 0; i < imagePaths.length; i++) {
        try {
            bunnyImage = new pdg.Image(imagePaths[i]);
            console.log("Loaded bunny image from: " + imagePaths[i]);
            console.log("Image size: " + bunnyImage.getWidth() + "x" + bunnyImage.getHeight());
            break;
        } catch (e) {
            // Try next path
        }
    }
    
    if (!bunnyImage) {
        console.log("ERROR: Could not load bunny image from any path");
        process.exit(1);
    }
    
    // Start with initial batch of bunnies
    addBunnies(BUNNIES_PER_BATCH);
    
    testStartTime = Date.now();
    lastAutoAddTime = testStartTime;
    lastStatsUpdate = testStartTime;
}

// Draw handler
var lastFrameTime = Date.now();

function onDraw(evt) {
    if (evt.port !== port) return false;
    
    var frameStartTime = Date.now();
    var deltaTime = frameStartTime - lastFrameTime;
    lastFrameTime = frameStartTime;
    
    // Clear background
    var bounds = port.getDrawingArea();
    var bgAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.1, 0.1, 0.15, 1.0));
    port.drawRect(bounds, bgAttrs);
    
    // Update and draw all bunnies
    for (var i = 0; i < bunnies.length; i++) {
        bunnies[i].update(bounds);
        bunnies[i].draw(port);
    }
    
    // Draw stats overlay
    var textAttrs = new pdg.Attributes()
        .textSize(16)
        .textStyle(pdg.textStyle_Plain)
        .fillColor("white");
    
    var y = 20;
    var lineHeight = 20;
    
    port.drawText("PDG BUNNYMARK TEST", new pdg.Point(10, y), textAttrs);
    y += lineHeight * 1.5;
    
    port.drawText("Bunnies: " + bunnies.length, new pdg.Point(10, y), textAttrs);
    y += lineHeight;
    
    port.drawText("FPS: " + currentFPS.toFixed(1), new pdg.Point(10, y), textAttrs);
    y += lineHeight;
    
    port.drawText("Frame Time: " + currentFrameTimeMs.toFixed(2) + " ms", new pdg.Point(10, y), textAttrs);
    y += lineHeight;
    
    port.drawText("Max @ 60 FPS: " + maxBunniesAt60FPS, new pdg.Point(10, y), textAttrs);
    y += lineHeight;
    
    port.drawText("Max @ 30 FPS: " + maxBunniesAt30FPS, new pdg.Point(10, y), textAttrs);
    y += lineHeight * 1.5;
    
    if (AUTO_ADD_BUNNIES) {
        port.drawText("Auto-adding bunnies...", new pdg.Point(10, y), textAttrs);
    } else {
        port.drawText("Press SPACE to add bunnies", new pdg.Point(10, y), textAttrs);
    }
    y += lineHeight;
    
    port.drawText("Press ESC to quit", new pdg.Point(10, y), textAttrs);
    
    // Calculate frame time
    var frameEndTime = Date.now();
    var frameTimeMs = frameEndTime - frameStartTime;
    
    // Update stats
    updateStats(frameTimeMs);
    currentFrameTimeMs = frameTimeMs;
    
    // Update current FPS periodically
    if (frameEndTime - lastStatsUpdate > STATS_UPDATE_INTERVAL) {
        var recentFrames = frameCount - (frameCount - 30);  // Rough approximation
        if (frameTimeMs > 0) {
            currentFPS = 1000 / frameTimeMs;
        }
        lastStatsUpdate = frameEndTime;
    }
    
    // Auto-add bunnies if enabled and enough time has passed
    if (AUTO_ADD_BUNNIES && (frameEndTime - lastAutoAddTime) > AUTO_ADD_DELAY) {
        // Only add more if we're still above minimum FPS
        if (currentFrameTimeMs < FRAME_TIME_MIN_MS) {
            addBunnies(BUNNIES_PER_BATCH);
            lastAutoAddTime = frameEndTime;
        } else {
            console.log("Stopped auto-adding: FPS dropped below " + MIN_FPS);
            console.log("Run test for a bit longer, then press ESC to see final results");
            AUTO_ADD_BUNNIES = false;  // Stop auto-adding
        }
    }
    
    return true;
}

// Key handler
function onKeyPress(evt) {
    if (evt.unicode == pdg.key_Escape) {
        console.log("\nTest stopped by user.");
        printFinalResults();
        pdg.gfx.closeGraphicsPort(port);
        pdg.quit();
        return true;
    } else if (evt.unicode == 32) {  // Space key
        addBunnies(BUNNIES_PER_BATCH);
        lastAutoAddTime = Date.now();  // Reset auto-add timer
        return true;
    }
    return false;
}

// Setup and run
setup();

pdg.on(pdg.eventType_PortDraw, onDraw);
pdg.on(pdg.eventType_KeyPress, onKeyPress);

console.log("\nTest started. Watch the window for live stats.");
console.log("Starting with " + bunnies.length + " bunnies...\n");

pdg.run();

