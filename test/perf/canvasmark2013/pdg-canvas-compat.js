// -----------------------------------------------
// PDG Canvas Compatibility Layer
//
// Makes PDG Port look like HTML5 Canvas 2D Context
// Allows CanvasMark code to run with minimal changes
// -----------------------------------------------

var pdg = require('pdg');

let gParseColor3h = 0;
let gParseColor = 0;
let gGetAttributes = 0;
let gDrawGlow = 0;
let gDrawGlowStep = 0;
let gClearRect = 0;
let gFillRect = 0;
let gStrokeRect = 0;
let gBeginPath = 0;
let gClosePath = 0;
let gMoveTo = 0;
let gLineTo = 0;
let gArc = 0;
let gFill = 0;
let gFillCircle = 0;
let gFillPolygon = 0;
let gStroke = 0;
let gStrokeLine = 0;
let gStrokeClosePath = 0;
let gFillText = 0;
let gDrawImage = 0;
let gDrawImageSimple = 0;
let gDrawImageScaled = 0;
let gDrawImageSubsection = 0;
let gTransformPoint = 0;
let gTransformPointRotate = 0;


// Create a CanvasRenderingContext2D-like wrapper around PDG Port
function PDGCanvasContext(port) {
    this.port = port;
    var _this = this;
    this.canvas = {
        width: 640,
        height: 640,
        _clickHandlers: [],
        getContext: function() { return _this; },
        addEventListener: function(event, handler, useCapture) {
            // Store click handlers so we can call them from PDG mouse events
            if (event === 'mousedown' || event === 'click') {
                this._clickHandlers.push(handler);
            }
        },
        onclick: null
    };
    
    // State stack for save/restore
    this.stateStack = [];
    
    // Current state
    this.state = {
        fillStyle: 'black',
        strokeStyle: 'black',
        lineWidth: 1,
        globalAlpha: 1.0,
        shadowBlur: 0,
        shadowColor: 'transparent',
        shadowOffsetX: 0,
        shadowOffsetY: 0,
        globalCompositeOperation: 'source-over',
        font: '10px sans-serif',
        textAlign: 'start',
        textBaseline: 'alphabetic',
        // Transform state
        translateX: 0,
        translateY: 0,
        rotation: 0,
        scaleX: 1,
        scaleY: 1
    };
    
    // Path building
    this.pathPoints = [];
    this.pathStarted = false;
}

PDGCanvasContext.prototype = {

    // ============================================
    // State Management
    // ============================================
    
    save: function() {
        // Deep copy current state (including transforms)
        var stateCopy = {};
        for (var key in this.state) {
            stateCopy[key] = this.state[key];
        }
        this.stateStack.push(stateCopy);
    },
    
    restore: function() {
        if (this.stateStack.length > 0) {
            this.state = this.stateStack.pop();
        }
    },
    
    // ============================================
    // Styles and Colors
    // ============================================
    
    get fillStyle() { return this.state.fillStyle; },
    set fillStyle(value) { this.state.fillStyle = value; },
    
    get strokeStyle() { return this.state.strokeStyle; },
    set strokeStyle(value) { this.state.strokeStyle = value; },
    
    get lineWidth() { return this.state.lineWidth; },
    set lineWidth(value) { this.state.lineWidth = value; },
    
    get globalAlpha() { return this.state.globalAlpha; },
    set globalAlpha(value) { this.state.globalAlpha = value; },
    
    get shadowBlur() { return this.state.shadowBlur; },
    set shadowBlur(value) { this.state.shadowBlur = value; },
    
    get shadowColor() { return this.state.shadowColor; },
    set shadowColor(value) { this.state.shadowColor = value; },
    
    get shadowOffsetX() { return this.state.shadowOffsetX; },
    set shadowOffsetX(value) { this.state.shadowOffsetX = value; },
    
    get shadowOffsetY() { return this.state.shadowOffsetY; },
    set shadowOffsetY(value) { this.state.shadowOffsetY = value; },
    
    get globalCompositeOperation() { return this.state.globalCompositeOperation; },
    set globalCompositeOperation(value) { this.state.globalCompositeOperation = value; },
    
    get font() { return this.state.font; },
    set font(value) { this.state.font = value; },
    
    get textAlign() { return this.state.textAlign; },
    set textAlign(value) { this.state.textAlign = value; },
    
    get textBaseline() { return this.state.textBaseline; },
    set textBaseline(value) { this.state.textBaseline = value; },
    
    // ============================================
    // Helper Functions
    // ============================================
    
    parseColor: function(colorStr) {
        gParseColor++;
        // Parse CSS color string to PDG Color
        if (typeof colorStr === 'string') {
            if (colorStr.indexOf('rgb') === 0) {
                // Parse rgb(r,g,b) or rgba(r,g,b,a)
                var match = colorStr.match(/rgba?\((\d+),\s*(\d+),\s*(\d+)(?:,\s*([\d.]+))?\)/);
                if (match) {
                    return new pdg.Color(
                        parseInt(match[1]) / 255,
                        parseInt(match[2]) / 255,
                        parseInt(match[3]) / 255,
                        match[4] ? parseFloat(match[4]) : 1.0
                    );
                }
            } else if (colorStr[0] === '#') {
                // Parse #RGB or #RRGGBB
                var hex = colorStr.substring(1);
                var r, g, b;
                if (hex.length === 3) {
                    gParseColor3h++;
                    // #RGB -> #RRGGBB
                    r = parseInt(hex[0] + hex[0], 16) / 255;
                    g = parseInt(hex[1] + hex[1], 16) / 255;
                    b = parseInt(hex[2] + hex[2], 16) / 255;
                } else {
                    // #RRGGBB
                    r = parseInt(hex.substring(0, 2), 16) / 255;
                    g = parseInt(hex.substring(2, 4), 16) / 255;
                    b = parseInt(hex.substring(4, 6), 16) / 255;
                }
                return new pdg.Color(r, g, b, 1.0);
            } else {
                // Named colors - basic set
                var colors = {
                    'black': [0, 0, 0],
                    'white': [1, 1, 1],
                    'red': [1, 0, 0],
                    'green': [0, 1, 0],
                    'blue': [0, 0, 1],
                    'yellow': [1, 1, 0],
                    'cyan': [0, 1, 1],
                    'magenta': [1, 0, 1],
                    'grey': [0.5, 0.5, 0.5],
                    'gray': [0.5, 0.5, 0.5],
                    'lightblue': [0.678, 0.847, 0.902],
                    'transparent': [0, 0, 0, 0]
                };
                var rgb = colors[colorStr.toLowerCase()];
                if (rgb) {
                    return new pdg.Color(rgb[0], rgb[1], rgb[2], rgb[3] || 1.0);
                }
            }
        }
        // Default to black
        return new pdg.Color(0, 0, 0, 1.0);
    },
    
    getAttributes: function(forFill) {
        gGetAttributes++;
        var attrs = new pdg.Attributes();
        
        var color = this.parseColor(forFill ? this.state.fillStyle : this.state.strokeStyle);
        var alpha = this.state.globalAlpha;
        
        if (forFill) {
            attrs.fillColor(color);
            attrs.fillOpacity(alpha);
        } else {
            attrs.lineColor(color);
            attrs.lineOpacity(alpha);
            attrs.lineThickness(this.state.lineWidth);
        }
        
        // Map composite operations to blend modes
        if (this.state.globalCompositeOperation === 'lighter') {
            attrs.blendMode(1);  // pdg.blendMode_Additive
        }
        // Add other blend modes as needed
        
        return attrs;
    },
    
    // Simulate glow/shadow effect with concentric circles
    drawGlow: function(x, y, size, color, blur) {
        gDrawGlow++;
        if (blur <= 0) return;
        
        var steps = Math.min(5, Math.ceil(blur / 2));
        for (var i = steps; i > 0; i--) {
            gDrawGlowStep++;
            var radius = size + (blur * i / steps);
            var alpha = 0.15 * this.state.globalAlpha * (1 - i / steps);
            
            var attrs = new pdg.Attributes()
                .fillColor(color)
                .fillOpacity(alpha);
            
            this.port.drawEllipse(new pdg.Point(x, y), radius, radius, attrs);
        }
    },
    
    // ============================================
    // Rectangle Operations
    // ============================================
    
    clearRect: function(x, y, w, h) {
        gClearRect++;
        var rect = new pdg.Rect(x, y, x + w, y + h);
        var attrs = new pdg.Attributes().fillColor(new pdg.Color(0, 0, 0, 1));
        this.port.drawRect(rect, attrs);
    },
    
    fillRect: function(x, y, w, h) {
        gFillRect++;
        // Create polygon with 4 corners to handle transforms properly
        var polygon = new pdg.Polygon();
        polygon.addPoint(this.transformPoint(x, y));
        polygon.addPoint(this.transformPoint(x + w, y));
        polygon.addPoint(this.transformPoint(x + w, y + h));
        polygon.addPoint(this.transformPoint(x, y + h));
        
        var attrs = this.getAttributes(true);
        
        // Apply shadow/glow if needed
        if (this.state.shadowBlur > 0) {
            var shadowColor = this.parseColor(this.state.shadowColor);
            var center = this.transformPoint(x + w/2, y + h/2);
            this.drawGlow(
                center.x + this.state.shadowOffsetX,
                center.y + this.state.shadowOffsetY,
                Math.max(w, h) / 2,
                shadowColor,
                this.state.shadowBlur
            );
        }
        
        this.port.drawPolygon(polygon, attrs);
    },
    
    strokeRect: function(x, y, w, h) {
        gStrokeRect++;
        // Create polygon with 4 corners to handle transforms properly
        var polygon = new pdg.Polygon();
        polygon.addPoint(this.transformPoint(x, y));
        polygon.addPoint(this.transformPoint(x + w, y));
        polygon.addPoint(this.transformPoint(x + w, y + h));
        polygon.addPoint(this.transformPoint(x, y + h));
        
        var attrs = this.getAttributes(false);
        this.port.drawPolygon(polygon, attrs);
    },
    
    // ============================================
    // Path Operations
    // ============================================
    
    beginPath: function() {
        gBeginPath++;
        this.pathPoints = [];
        this._currentPath = []; // For clip() support
        this.pathStarted = true;
        this.pathIsClosed = false;
    },
    
    closePath: function() {
        gClosePath++;
        this.pathIsClosed = true;
    },
    
    moveTo: function(x, y) {
        gMoveTo++;
        if (this.pathPoints.length > 0 && !this.pathIsClosed) {
            // Start a new sub-path
            this.pathPoints.push(null); // Marker for sub-path
        }
        var pt = new pdg.Point(x, y);
        this.pathPoints.push(pt);
        this._currentPath.push(pt); // Track for clip()
    },
    
    lineTo: function(x, y) {    
        gLineTo++;
        var pt = new pdg.Point(x, y);
        this.pathPoints.push(pt);
        this._currentPath.push(pt); // Track for clip()
    },
    
    arc: function(x, y, radius, startAngle, endAngle, anticlockwise) {
        gArc++;
        // For simple filled/stroked circles, just store center and radius
        // Full arc drawing is complex - simplified for CanvasMark usage
        this.arcX = x;
        this.arcY = y;
        this.arcRadius = radius;
        this.arcStartAngle = startAngle;
        this.arcEndAngle = endAngle;
        this.isFullCircle = Math.abs(endAngle - startAngle) >= Math.PI * 2 - 0.01;
    },
    
    fill: function() {
        gFill++;
        if (this.arcX !== undefined && this.isFullCircle) {
            gFillCircle++;
            // Simple circle fill - apply transforms
            var attrs = this.getAttributes(true);
            var center = this.transformPoint(this.arcX, this.arcY);
            var radius = this.arcRadius * Math.max(this.state.scaleX, this.state.scaleY);
            
            // Apply shadow/glow if needed
            if (this.state.shadowBlur > 0) {
                var shadowColor = this.parseColor(this.state.shadowColor);
                this.drawGlow(
                    center.x + this.state.shadowOffsetX,
                    center.y + this.state.shadowOffsetY,
                    radius,
                    shadowColor,
                    this.state.shadowBlur
                );
            }
            
            this.port.drawEllipse(center, radius, radius, attrs);
        } else if (this.pathPoints.length >= 3) {
            gFillPolygon++;
            // Polygon fill - transform all points
            var polygon = new pdg.Polygon();
            for (var i = 0; i < this.pathPoints.length; i++) {
                if (this.pathPoints[i] !== null) {
                    var transformed = this.transformPoint(this.pathPoints[i].x, this.pathPoints[i].y);
                    polygon.addPoint(transformed);
                }
            }
            
            var attrs = this.getAttributes(true);
            this.port.drawPolygon(polygon, attrs);
        }
        
        this.arcX = undefined;
    },
    
    stroke: function() {
        gStroke++;
        if (this.arcX !== undefined) {
            // Arc/circle stroke - not commonly used in CanvasMark, skip for now
            this.arcX = undefined;
            return;
        }
        
        if (this.pathPoints.length >= 2) {
            var attrs = this.getAttributes(false);
            
            // Transform all points and draw lines between them
            for (var i = 1; i < this.pathPoints.length; i++) {
                if (this.pathPoints[i] !== null && this.pathPoints[i-1] !== null) {
                    gStrokeLine++;
                    var p1 = this.transformPoint(this.pathPoints[i-1].x, this.pathPoints[i-1].y);
                    var p2 = this.transformPoint(this.pathPoints[i].x, this.pathPoints[i].y);
                    this.port.drawLine(p1, p2, attrs);
                }
            }
            
            // Close path if needed
            if (this.pathIsClosed && this.pathPoints.length > 0) {
                var firstPoint = this.pathPoints[0];
                var lastPoint = this.pathPoints[this.pathPoints.length - 1];
                if (firstPoint && lastPoint) {
                    gStrokeClosePath++;
                    var p1 = this.transformPoint(lastPoint.x, lastPoint.y);
                    var p2 = this.transformPoint(firstPoint.x, firstPoint.y);
                    this.port.drawLine(p1, p2, attrs);
                }
            }
        }
    },
    
    // ============================================
    // Text Operations
    // ============================================
    
    fillText: function(text, x, y) {
        gFillText++;
        // Parse font to get size
        var fontSize = 10;
        var fontMatch = this.state.font.match(/(\d+)(?:px|pt)/);
        if (fontMatch) {
            fontSize = parseInt(fontMatch[1]);
        }
        
        // Create completely fresh attributes for text
        var color = this.parseColor(this.state.fillStyle);
        var attrs = new pdg.Attributes()
            .fillColor(color)
            .fillOpacity(this.state.globalAlpha)
            .textSize(fontSize);
        
        this.port.drawText(text, new pdg.Point(x, y), attrs);
    },
    
    strokeText: function(text, x, y) {
        // PDG doesn't have outlined text - just draw filled
        this.fillText(text, x, y);
    },
    
    measureText: function(text) {
        // Return fake measurement - CanvasMark doesn't heavily rely on this
        return { width: text.length * 7 };
    },
    
    // ============================================
    // Image Operations
    // ============================================
    
    drawImage: function(image, sx, sy, sw, sh, dx, dy, dw, dh) {
        gDrawImage++;
        // Unwrap Image object if needed
        var pdgImage = image;
        if (image && typeof image._getPDGImage === 'function') {
            pdgImage = image._getPDGImage();
        }
        
        if (!pdgImage) return; // Image not loaded yet
        
        // K3D texture mapping is now handled by monkey-patched renderPolygon
        // This code path is for normal (non-K3D) drawImage calls
        
        // Handle different argument counts for normal drawImage
        if (arguments.length === 3) {
            // drawImage(image, dx, dy)
            gDrawImageSimple++;
            var attrs = new pdg.Attributes()
                .fillOpacity(this.state.globalAlpha);
            this.port.drawImage(pdgImage, new pdg.Point(sx, sy), attrs);
        } else if (arguments.length === 5) {
            // drawImage(image, dx, dy, dw, dh)
            gDrawImageScaled++;
            // Draw whole image scaled to dw x dh at position dx, dy
            var attrs = new pdg.Attributes()
                .fillOpacity(this.state.globalAlpha);
            var destRect = new pdg.Rect(sx, sy, sx + sw, sy + sh);
            this.port.drawImage(pdgImage, destRect, attrs);
        } else if (arguments.length === 9) {
            // drawImage(image, sx, sy, sw, sh, dx, dy, dw, dh)
            gDrawImageSubsection++;
            // Use Image.getSubsection() to extract the source rect
            var attrs = new pdg.Attributes()
                .fillOpacity(this.state.globalAlpha);
            var srcRect = new pdg.Rect(sx, sy, sx + sw, sy + sh);
            var subImage = pdgImage.getSubsection(srcRect);
            var destRect = new pdg.Rect(dx, dy, dx + dw, dy + dh);
            this.port.drawImage(subImage, destRect, attrs);
        }
    },
    
    // ============================================
    // Transform Operations
    // ============================================
    
    translate: function(x, y) {
        this.state.translateX += x;
        this.state.translateY += y;
    },
    
    rotate: function(angle) {
        this.state.rotation += angle;
    },
    
    scale: function(x, y) {
        this.state.scaleX *= x;
        this.state.scaleY *= (y !== undefined ? y : x);
    },
    
    // Apply current transforms to a point
    transformPoint: function(x, y) {
        gTransformPoint++;
        // Apply scale
        var tx = x * this.state.scaleX;
        var ty = y * this.state.scaleY;
        
        // Apply rotation
        if (this.state.rotation !== 0) {
            gTransformPointRotate++;
            var cos = Math.cos(this.state.rotation);
            var sin = Math.sin(this.state.rotation);
            var rx = tx * cos - ty * sin;
            var ry = tx * sin + ty * cos;
            tx = rx;
            ty = ry;
        }
        
        // Apply translation
        tx += this.state.translateX;
        ty += this.state.translateY;
        
        return new pdg.Point(tx, ty);
    },
    
    transform: function(a, b, c, d, e, f) {
        // K3D uses transform() for texture mapping, but we handle that via monkey-patch
        // No-op for now
    },
    
    clip: function() {
        // K3D uses clip() for texture mapping, but we handle that via monkey-patch
        // No-op for now
    }
};

// GameHandler.init_pdg will be added in canvasmark.js after GameHandler is loaded

// ============================================
// Browser Globals for Node.js Environment
// ============================================

// Note: Main globals (window, document, navigator) are set in canvasmark.js
// We just augment them here as needed

// Image constructor that wraps pdg.Image
global.Image = function() {
    var pdgImage = null;
    var src = null;
    var onload = null;
    var url = null;  // For preloader
    
    Object.defineProperty(this, 'src', {
        get: function() { return src; },
        set: function(value) {
            src = value;
            
            // Handle data URLs (from Arena prerenderer)
            if (value && value.indexOf('data:image/pdg;ref=') === 0) {
                // Extract reference ID from our custom data URL
                var refId = parseInt(value.substring('data:image/pdg;ref='.length));
                // Look up the prerendered PDG image
                pdgImage = global._prerenderImageMap[refId] || null;
                if (onload) {
                    setTimeout(function() { onload(); }, 0);
                }
                return;
            } else if (value && value.indexOf('data:') === 0) {
                // Other data URLs we can't handle
                pdgImage = null;
                if (onload) {
                    setTimeout(function() { onload(); }, 0);
                }
                return;
            }
            
            try {
                // Load image relative to canvasmark directory
                var path = require('path');
                var imagePath = path.join(__dirname, value.replace('./', ''));
                pdgImage = new pdg.Image(imagePath);
                // Call onload immediately (PDG loads synchronously)
                if (onload) {
                    setTimeout(function() { onload(); }, 0);
                }
            } catch (e) {
                console.warn('Failed to load image:', value, e.message);
            }
        }
    });
    
    Object.defineProperty(this, 'onload', {
        get: function() { return onload; },
        set: function(value) { 
            onload = value;
            // If src was already set, call onload now
            if (src && pdgImage && onload) {
                setTimeout(function() { onload(); }, 0);
            }
        }
    });
    
    Object.defineProperty(this, 'url', {
        get: function() { return url; },
        set: function(value) { url = value; }
    });
    
    Object.defineProperty(this, 'width', {
        get: function() { return pdgImage ? pdgImage.width : 0; }
    });
    
    Object.defineProperty(this, 'height', {
        get: function() { return pdgImage ? pdgImage.height : 0; }
    });
    
    // Return the PDG Image for actual drawing
    this._getPDGImage = function() { return pdgImage; };
};


// add stats to the global window object
// Dump the stats to the console
global.window.dumpStats = function() {
    console.log("gParseColor:", gParseColor);
    console.log("gParseColor3h:", gParseColor3h);
    console.log("gGetAttributes:", gGetAttributes);
    console.log("gDrawGlow:", gDrawGlow);
    console.log("gDrawGlowStep:", gDrawGlowStep);
    console.log("gClearRect:", gClearRect);
    console.log("gFillRect:", gFillRect);
    console.log("gStrokeRect:", gStrokeRect);
    console.log("gBeginPath:", gBeginPath);
    console.log("gClosePath:", gClosePath);
    console.log("gMoveTo:", gMoveTo);
    console.log("gLineTo:", gLineTo);
    console.log("gArc:", gArc);
    console.log("gFill:", gFill);
    console.log("gFillCircle:", gFillCircle);
    console.log("gFillPolygon:", gFillPolygon);
    console.log("gStroke:", gStroke);
    console.log("gStrokeLine:", gStrokeLine);
    console.log("gStrokeClosePath:", gStrokeClosePath);
    console.log("gFillText:", gFillText);
    console.log("gDrawImage:", gDrawImage);
    console.log("gDrawImageSimple:", gDrawImageSimple);
    console.log("gDrawImageScaled:", gDrawImageScaled);
    console.log("gDrawImageSubsection:", gDrawImageSubsection);
    console.log("gTransformPoint:", gTransformPoint);
    console.log("gTransformPointRotate:", gTransformPointRotate);
};

global.window.resetStats = function() {
    gParseColor = 0;
    gParseColor3h = 0;
    gGetAttributes = 0;
    gDrawGlow = 0;
    gDrawGlowStep = 0;
    gClearRect = 0;
    gFillRect = 0;
    gStrokeRect = 0;
    gBeginPath = 0;
    gClosePath = 0;
    gMoveTo = 0;
    gLineTo = 0;
    gArc = 0;
    gFill = 0;
    gFillCircle = 0;
    gFillPolygon = 0;
    gStroke = 0;
    gStrokeLine = 0;
    gStrokeClosePath = 0;
    gFillText = 0;
    gDrawImage = 0;
    gDrawImageSimple = 0;
    gDrawImageScaled = 0;
    gDrawImageSubsection = 0;
    gTransformPoint = 0;
    gTransformPointRotate = 0;
};

// Make PDGCanvasContext available globally
if (typeof module !== 'undefined' && module.exports) {
    module.exports = PDGCanvasContext;
}
global.PDGCanvasContext = PDGCanvasContext;

