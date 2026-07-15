#!/usr/bin/env node
// -----------------------------------------------
// CanvasMark 2013 - PDG Port
//
// Port of the CanvasMark 2013 HTML5 Canvas benchmark
// to run using PDG's rendering APIs
//
// Original: https://github.com/kevinroast/CanvasMark
// -----------------------------------------------

console.log("=== CANVASMARK 2013 - PDG PORT ===\n");

var pdg = require('pdg');
var fs = require('fs');
var path = require('path');

// Setup browser globals BEFORE loading any scripts
global.window = {
    pageXOffset: 0,
    pageYOffset: 0,
    setTimeout: setTimeout,
    requestAnimationFrame: function(cb) { setTimeout(cb, 16); },
    webkitRequestAnimationFrame: function(cb) { setTimeout(cb, 16); },
    mozRequestAnimationFrame: function(cb) { setTimeout(cb, 16); },
    oRequestAnimationFrame: function(cb) { setTimeout(cb, 16); },
    msRequestAnimationFrame: function(cb) { setTimeout(cb, 16); },
    addEventListener: function(event, handler) {
        // Stub - we'll call handlers manually
        if (event === 'load') {
            global._windowOnLoad = handler;
        }
    }
};

// Image reference system for data URL simulation
global._prerenderImageMap = {};
global._prerenderImageCounter = 0;

global.document = {
    getElementById: function(id) { return null; },
    createElement: function(tag) {
        if (tag === 'canvas') {
            // Fake offscreen canvas for Arena prerendering
            var canvasWidth = 32;
            var canvasHeight = 32;
            
            return {
                get width() { return canvasWidth; },
                set width(w) { canvasWidth = w; },
                get height() { return canvasHeight; },
                set height(h) { canvasHeight = h; },
                toDataURL: function(type) {
                    // Generate unique reference ID
                    var refId = ++global._prerenderImageCounter;
                    // Store null - prerendered sprites won't display
                    global._prerenderImageMap[refId] = null;
                    // Return fake data URL with reference
                    return 'data:image/pdg;ref=' + refId;
                },
                getContext: function(type) {
                    // Return stub context for prerendering
                    return {
                        drawImage: function() {},
                        clearRect: function() {},
                        fillRect: function() {},
                        beginPath: function() {},
                        moveTo: function() {},
                        lineTo: function() {},
                        closePath: function() {},
                        arc: function() {},
                        fill: function() {},
                        stroke: function() {},
                        save: function() {},
                        restore: function() {},
                        translate: function() {},
                        rotate: function() {},
                        scale: function() {},
                        createRadialGradient: function(x0, y0, r0, x1, y1, r1) {
                            return {
                                addColorStop: function(pos, color) {}
                            };
                        },
                        fillStyle: 'black',
                        strokeStyle: 'black',
                        globalAlpha: 1.0
                    };
                }
            };
        }
        return null;
    },
    onkeydown: null,
    onkeyup: null
};

global.navigator = {
    userAgent: 'Mozilla/5.0 (PDG) AppleWebKit/537.36 Chrome/100.0 Safari/537.36',
    platform: 'MacIntel',
    vendor: 'PDG',
    appVersion: '5.0 (PDG)'
};

global.location = {
    search: '',
    href: 'pdg://canvasmark2013'
};

global.requestAnimFrame = function(callback, element) {
    // Don't actually request animation frames - PDG draw events handle this
    // Just make the function exist so code doesn't error
};

global.alert = function(msg) {
    console.log("ALERT:", msg);
};

// Stub jQuery for results display
global.$ = function(selector) {
    return {
        html: function(content) {},
        attr: function(attr, value) {},
        fadeIn: function() {}
    };
};

// Helper function to load scripts directly into global scope (for compat layer)
function loadScriptDirect(filepath) {
    var fullPath = path.join(__dirname, filepath);
    var code = fs.readFileSync(fullPath, 'utf8');
    (1, eval)(code);
}

// Helper function to load and eval browser scripts  
function loadScript(filepath) {
    var fullPath = path.join(__dirname, filepath);
    var code = fs.readFileSync(fullPath, 'utf8');
    // Prepend variable declarations so eval'd code can see browser globals
    var preamble = 'var window=global.window; var document=global.document; var navigator=global.navigator; var Image=global.Image; var requestAnimFrame=global.requestAnimFrame; var alert=global.alert; var location=global.location; var $=global.$; var DEBUG=global.DEBUG;\n';
    // Use indirect eval to execute in global scope
    (1, eval)(preamble + code);
}

// Load PDG Canvas compatibility layer first (sets up remaining globals)
loadScriptDirect('pdg-canvas-compat.js');

// Make browser globals accessible as variables (not just global.*)
var window = global.window;
var document = global.document;
var navigator = global.navigator;
var Image = global.Image;

// Stub out BrowserDetect to avoid errors
global.BrowserDetect = {
    browser: 'PDG',
    version: '0.10',
    OS: process.platform,
    init: function() {}
};

// Stub DEBUG object
global.DEBUG = {};

console.log("Loading CanvasMark scripts...");

// Load dependencies
loadScript('scripts/mathlib-min.js');
// Load real K3D library (does 3D transforms and canvas rendering)
loadScript('scripts/k3d-min.js');

// Monkey-patch K3D.SolidRenderer to use PDG's native textured polygon rendering
(function() {
    var originalRenderPolygon = K3D.SolidRenderer.prototype.renderPolygon;
    var debugOnce = false;
    
    K3D.SolidRenderer.prototype.renderPolygon = function(ctx, obj, face, fillColor) {
        var screenCoords = obj.screencoords;
        var vertices = face.vertices;
        
        // Check if this face has a texture
        if (face.texture !== null && face.texture !== undefined) {
            var texture = obj.textures[face.texture];
            
            // Get the PDG image from the wrapper
            var pdgImage = texture;
            if (texture && typeof texture._getPDGImage === 'function') {
                pdgImage = texture._getPDGImage();
            }
            
            if (pdgImage && ctx.port) {
                //if (!debugOnce) {
                //    console.log("K3D textured face - vertices:", vertices.length);
                //    console.log("First vertex screen coords:", screenCoords[vertices[0]]);
                //    console.log("Canvas state - translate:", ctx.state ? (ctx.state.translateX + "," + ctx.state.translateY) : "none");
                //    debugOnce = true;
                //}
                
                // Create PDG polygon from screen coordinates
                // Apply canvas translation if active (K3D's original rendering uses canvas transform)
                var polygon = new pdg.Polygon();
                var offsetX = ctx.state ? ctx.state.translateX : 0;
                var offsetY = ctx.state ? ctx.state.translateY : 0;
                
                for (var i = 0; i < vertices.length; i++) {
                    var pt = screenCoords[vertices[i]];
                    polygon.addPoint(new pdg.Point(pt.x + offsetX, pt.y + offsetY));
                }
                
                // Use PDG's native textured polygon rendering
                var attrs = new pdg.Attributes()
                    .fillOpacity(ctx.state ? ctx.state.globalAlpha : 1.0)
                    .texture(pdgImage);
                
                ctx.port.drawPolygon(polygon, attrs);
                return;
            }
        }
        
        // Fall back to original rendering for non-textured polygons
        originalRenderPolygon.call(this, ctx, obj, face, fillColor);
    };
})();

// Load game library
loadScript('scripts/gamelib_benchmark.js');

// Load feature tests
loadScript('scripts/feature_main_benchmark.js');

// Load Asteroids game (main first to create namespace)
loadScript('scripts/asteroids_main_benchmark.js');
loadScript('scripts/asteroids_player.js');
loadScript('scripts/asteroids_enemies.js');
loadScript('scripts/asteroids_weapons.js');
loadScript('scripts/asteroids_effects.js');

// Load Arena game (main first to create namespace)
loadScript('scripts/arena_main_benchmark.js');
loadScript('scripts/arena_3d.js');
loadScript('scripts/arena_player.js');
loadScript('scripts/arena_enemies.js');
loadScript('scripts/arena_weapons.js');
loadScript('scripts/arena_effects.js');

// Load main benchmark
loadScript('scripts/benchmark_main.js');

console.log("All scripts loaded successfully\n");

// ============================================
// PDG Initialization
// ============================================

// Add PDG initialization to GameHandler (now that it exists)
GameHandler.init_pdg = function(port) {
    this.port = port;
    var ctx = new PDGCanvasContext(port);
    this.canvas = ctx.canvas;  // Set to the fake canvas element, not the context
    this.context = ctx;  // Keep reference to context too
    this.width = 640;
    this.height = 640;
    this.frameStart = Date.now();
    this.offsetX = 0;
    this.offsetY = 0;
};

// Override the original init to do nothing (we use init_pdg instead)
GameHandler.init = function() {
    // Already initialized via init_pdg
};

var port = null;
var testStartTime = Date.now();

var game = null;

function setup() {
    console.log("Setting up PDG graphics...");
    console.log("pdg.gfx exists:", pdg.gfx ? "yes" : "no");
    
    // Create window (640x640 like original)
    try {
        var windowRect = new pdg.Rect(0, 0, 640, 640);
        console.log("Rect created:", windowRect);
        console.log("Creating window port...");
        port = pdg.gfx.createWindowPort(windowRect, "CanvasMark 2013 - PDG Port");
        console.log("createWindowPort returned:", port ? "success" : "null");
    } catch (e) {
        console.log("ERROR creating window:", e.message, e.stack);
    }
    
    if (!port) {
        console.log("ERROR: Could not create window port");
        process.exit(1);
    }
    
    console.log("Window created: 640x640");
    
    // Initialize GameHandler with PDG port
    console.log("Initializing GameHandler...");
    GameHandler.init_pdg(port);
    console.log("GameHandler initialized");
    
    // Trigger the window.onload handler to load splash and initialize
    console.log("Triggering onload handler...");
    if (global._windowOnLoad) {
        try {
            global._windowOnLoad();
            console.log("onload handler completed");
            console.log("GameHandler.game:", GameHandler.game ? "created" : "null");
        } catch (e) {
            console.error("Error in onload handler:", e.message);
            console.error(e.stack);
        }
    } else {
        console.log("No onload handler registered!");
    }
    
    console.log("\nBenchmark initialized. Starting rendering...");
    console.log("Press SPACE or click window to start tests.");
    console.log("Press ESC to quit at any time.\n");
}

// ============================================
// Event Handlers
// ============================================

var drawCount = 0;

function onDraw(evt) {
    if (evt.port !== port) return false;
    
    drawCount++;
    
    // Drive the game's frame method from PDG's draw event
    if (GameHandler.game && !GameHandler.paused) {
        try {
            if (drawCount === 1) {
                console.log("First frame - sceneIndex:", GameHandler.game.sceneIndex);
                if (GameHandler.game.scenes && GameHandler.game.scenes[GameHandler.game.sceneIndex]) {
                    var scene = GameHandler.game.scenes[GameHandler.game.sceneIndex];
                    console.log("Current scene:", scene.interval ? scene.interval.label : "unknown");
                }
            }
            GameHandler.game.frame();
        } catch (e) {
            console.error("Error in game.frame():", e.message);
            console.error(e.stack);
            pdg.quit();
        }
    }
    
    return true;
}

function onKeyPress(evt) {
    if (evt.unicode == pdg.key_Escape) {
        console.log("\nBenchmark stopped by user.");
        printFinalResults();
        pdg.gfx.closeGraphicsPort(port);
        pdg.quit();
        return true;
    }
    
    // Pass keys to the game (including SPACE to start from InfoScene)
    if (GameHandler.game && GameHandler.game.sceneIndex !== -1) {
        var scene = GameHandler.game.scenes[GameHandler.game.sceneIndex];
        if (scene && scene.onKeyDownHandler) {
            scene.onKeyDownHandler(evt.unicode);
        }
    }
    
    return false;
}

function onMouseDown(evt) {
    // Pass mouse clicks to the canvas click handlers
    if (GameHandler.canvas && GameHandler.canvas._clickHandlers) {
        var clickHandlers = GameHandler.canvas._clickHandlers;
        for (var i = 0; i < clickHandlers.length; i++) {
            try {
                if (clickHandlers[i]({ button: 0 })) break;
            } catch (e) {
                console.warn("Click handler error:", e.message);
            }
        }
    }
    return true;
}

function printFinalResults() {
    var totalDuration = (Date.now() - testStartTime) / 1000;
    var score = GameHandler.benchmarkScoreCount;
    
    console.log("\n" + "=".repeat(70));
    console.log("CANVASMARK 2013 - PDG PORT - FINAL RESULTS");
    console.log("=".repeat(70));
    console.log("\nComposite Score: " + score);
    console.log("Total Duration: " + totalDuration.toFixed(2) + " seconds");
    console.log("=".repeat(70) + "\n");
    
    // Save results to JSON
    var results = {
        testName: "CanvasMark 2013 (PDG Port)",
        timestamp: new Date().toISOString(),
        totalDurationSeconds: parseFloat(totalDuration.toFixed(2)),
        compositeScore: score,
        scores: GameHandler.benchmarkScores
    };
    
    var resultsFile = path.join(__dirname, 'canvasmark_results.json');
    try {
        fs.writeFileSync(resultsFile, JSON.stringify(results, null, 2));
        console.log("Results saved to: " + resultsFile + "\n");
    } catch (e) {
        console.log("Warning: Could not save results to file:", e.message);
    }
}

// Setup and run
setup();

pdg.on(pdg.eventType_PortDraw, onDraw);
pdg.on(pdg.eventType_KeyPress, onKeyPress);
pdg.on(pdg.eventType_MouseDown, onMouseDown);

pdg.run();

