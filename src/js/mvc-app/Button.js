// -----------------------------------------------
// Button.js
// 
// JavaScript port of the Button UI component
// A clickable button with text and images
//
// Ported from C++ by Assistant, 2024
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

const { View } = require('./View');

const MAX_BUTTON_IMAGES = 3;
const RES_DEFAULT_BUTTON_IMAGE_NAMES = ['button_default.png', 'button_pressed.png', 'button_disabled.png'];

// FIXME: this breaks when run under pdg, but is needed for node
// const pdg = require('pdg'); // uncomment this to run under node

/**
 * Button UI component that extends View
 */
class Button extends View {
    constructor(controller, frameOrPoint, buttonID, resourceTextID = -1, 
                substring = -1, imageNames = RES_DEFAULT_BUTTON_IMAGE_NAMES) {
        
        let rect;
        if (frameOrPoint instanceof pdg.Point) {
            // Make button size match image
            rect = new pdg.Rect(frameOrPoint.x, frameOrPoint.y, 0, 0);
        } else {
            // Make button size match rectangle
            rect = frameOrPoint;
        }

        super(controller, rect);
        
        this.resMgr = controller.getApplication().getResourceManager();
        this.buttonImage = new Array(MAX_BUTTON_IMAGES).fill(null);
        this.clickSound = null;
        this.text = '';
        this.buttonID = buttonID;
        this.imageNames = imageNames;
        this.isButtonPressed = false;
        
        // Tooltip support
        this.isToolTipEnabled = false;
        this.toolTipCtrl = null;
        this.nHasChangedAreaHit = 0;
        this.textBaselineCenterPoint = new pdg.Point(0, 0);
        this.buttonTextSize = 12;
        
        this.initializeButton(resourceTextID, substring);
        this.finishInitButton();
    }

    /**
     * Initialize button with text from resources
     * @param {number} resourceTextID - Resource ID for text
     * @param {number} substring - Substring index
     */
    initializeButton(resourceTextID, substring) {
        if (resourceTextID !== -1) {
            this.setTextFromResource(resourceTextID, substring);
        }
    }

    /**
     * Finish button initialization
     */
    finishInitButton() {
        this.loadImages();
        this.setWantsMouseOvers(true); // Enable mouse over events for tooltips
    }

    /**
     * Set button text
     * @param {string} text - Button text
     */
    setText(text) {
        this.text = text || '';
    }

    /**
     * Set text from resource
     * @param {number} resourceID - Resource ID
     * @param {number} substring - Substring index
     */
    setTextFromResource(resourceID, substring) {
        try {
            const text = this.resMgr.getString(resourceID, substring);
            this.setText(text);
        } catch (error) {
            console.warn(`Failed to load text from resource ${resourceID}:`, error);
            this.setText('');
        }
    }

    /**
     * Set click sound
     * @param {Sound} clickSound - Sound to play when clicked
     */
    setClickSound(clickSound) {
        this.mpClickSound = clickSound;
    }

    /**
     * Load button images
     */
    loadImages() {
        for (let i = 0; i < MAX_BUTTON_IMAGES; i++) {
            this.buttonImage[i] = null;
        }
        if (this.imageNames !== null && this.imageNames.length > 2) {
            try {
                for (let i = 0; i < MAX_BUTTON_IMAGES; i++) {
                    this.buttonImage[i] = this.resMgr.getImage(this.imageNames[i]);
                }
            } catch (error) {
                console.warn(`Failed to load button images for ID ${this.imageNames}:`, error);
            }
        }
    }

    /**
     * Draw the button
     */
    drawSelf(port, frameNum) {
        if (this.buttonImage[0]) {
            // Draw using loaded images
            this.drawWithImages(port);
        } else {
            // Draw standard button background
            this.drawStandardButtonBackground(port);
        }
        
        // Draw text if present
        if (this.text) {
            this.drawText(port);
        }
    }

    /**
     * Draw button using loaded images
     */
    drawWithImages(port) {
        const viewArea = this.getViewArea();
        
        let imageIndex = 0; // Default/normal state
        if (this.isButtonPressed) {
            imageIndex = 1; // Pressed state
        } else if (!this.isEnabled()) {
            imageIndex = 2; // Disabled state
        }
        
        const image = this.buttonImage[imageIndex];
        if (image) {
            port.drawImage(image, viewArea.leftTop(), viewArea);
        }
    }

    /**
     * Draw standard button background
     */
    drawStandardButtonBackground(port) {
        const viewArea = this.getViewArea();
        
        // Choose colors based on state
        let bgColor, borderColor, textColor;
        
        if (!this.isEnabled()) {
            bgColor = new pdg.Color(0.7, 0.7, 0.7, 1.0); // Gray
            borderColor = new pdg.Color(0.5, 0.5, 0.5, 1.0);
            textColor = new pdg.Color(0.4, 0.4, 0.4, 1.0);
        } else         if (this.isButtonPressed) {
            bgColor = new pdg.Color(0.6, 0.6, 0.8, 1.0); // Darker blue
            borderColor = new pdg.Color(0.2, 0.2, 0.4, 1.0);
            textColor = new pdg.Color(1.0, 1.0, 1.0, 1.0);
        } else {
            bgColor = new pdg.Color(0.8, 0.8, 0.9, 1.0); // Light blue
            borderColor = new pdg.Color(0.3, 0.3, 0.5, 1.0);
            textColor = new pdg.Color(0.0, 0.0, 0.0, 1.0);
        }
        
        // Draw background
        var backgroundAttrs = new pdg.Attributes().fillColor(bgColor);
        port.drawRect(viewArea, backgroundAttrs);
        
        // Draw border
        var borderAttrs = new pdg.Attributes().lineColor(borderColor).lineThickness(2);
        port.drawRect(viewArea, borderAttrs);
        
        // Store text color for text drawing
        this.textColor = textColor;
    }

    /**
     * Draw button text
     */
    drawText() {
        if (!this.text) return;
        
        const port = this.getPort();
        const viewArea = this.getViewArea();
        
        // Calculate text position (centered)
        const textColor = this.textColor || new pdg.Color(0.0, 0.0, 0.0, 1.0);
        const centerX = viewArea.left + viewArea.width() / 2;
        const centerY = viewArea.top + viewArea.height() / 2;
        
        // Adjust for button pressed state
        const offsetX = this.isButtonPressed ? 1 : 0;
        const offsetY = this.isButtonPressed ? 1 : 0;
        
        const textPoint = new pdg.Point(centerX + offsetX, centerY + offsetY);
        
        // Draw text centered
        port.drawText(this.text, textPoint, this.buttonTextSize, pdg.textStyle_Centered, textColor);
        
        // Store baseline center point for tooltips
        this.textBaselineCenterPoint = textPoint;
    }

    /**
     * Set click state
     * @param {boolean} clicked - Whether button is clicked/pressed
     */
    setClickState(clicked) {
        this.isButtonPressed = clicked;
    }

    /**
     * Handle mouse down
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doMouseDown(mouseInfo, id, part) {
        if (this.isEnabled()) {
            this.setClickState(true);
            return true;
        }
        return false;
    }

    /**
     * Handle mouse up
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doMouseUp(mouseInfo, id, part) {
        if (this.isButtonPressed) {
            this.setClickState(false);
            
            // Play click sound if available
            if (this.clickSound) {
                this.clickSound.play();
            }
            
            return true;
        }
        return false;
    }

    /**
     * Handle left click
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doLeftClick(mouseInfo, id, part) {
        if (this.isEnabled()) {
            // Notify controller that button was clicked
            const controller = this.controller;
            if (controller && typeof controller.buttonClicked === 'function') {
                controller.buttonClicked(this.buttonID, this);
            }
            return true;
        }
        return false;
    }

    // ============================ Tooltip Support ============================

    /**
     * Show tooltip
     * @param {number} nArea - Area number
     * @param {Point} pts - Point position
     * @param {Rect} rToolRect - Tooltip rectangle
     */
    showToolTip(nArea, pts, rToolRect) {
        if (this.isToolTipEnabled && this.toolTipCtrl) {
            // Implementation would show tooltip
            console.log(`Showing tooltip for button ${this.buttonID}`);
        }
    }

    /**
     * Check if mouse is in tool area
     * @param {Point} pts - Point position
     * @param {Rect} rToolRect - Tooltip rectangle
     * @returns {boolean} true if mouse is in tool area
     */
    isMouseInToolArea(pts, rToolRect) {
        return rToolRect.contains(pts);
    }

    /**
     * Set tooltip text
     * @param {string} text - Tooltip text
     */
    setToolTipText(text) {
        this.isToolTipEnabled = true;
        // In a real implementation, you would create or update the tooltip control
        console.log(`Setting tooltip text for button ${this.buttonID}: ${text}`);
    }

    /**
     * Handle mouse move (for tooltips)
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     */
    doMouseMove(mouseInfo, id, part) {
        if (this.isToolTipEnabled) {
            // Check if we should show tooltip
            const viewArea = this.getViewArea();
            if (this.isMouseInToolArea(mouseInfo.mousePos, viewArea)) {
                this.showToolTip(part, mouseInfo.mousePos, viewArea);
            }
        }
    }

    /**
     * Handle mouse leave
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     */
    doMouseLeave(mouseInfo, id, part) {
        // Hide tooltip when mouse leaves
        if (this.isToolTipEnabled) {
            console.log(`Hiding tooltip for button ${this.buttonID}`);
        }
    }

    /**
     * Get button ID
     * @returns {number} Button ID
     */
    getButtonID() {
        return this.buttonID;
    }

    /**
     * Get button text
     * @returns {string} Button text
     */
    getText() {
        return this.text;
    }

    /**
     * Check if button is pressed
     * @returns {boolean} true if pressed
     */
    isPressed() {
        return this.isButtonPressed;
    }

    /**
     * Set button text size
     * @param {number} size - Text size
     */
    setTextSize(size) {
        this.buttonTextSize = size;
    }

    /**
     * Cleanup when button is destroyed
     */
    destroy() {
        // Clean up images
        for (let i = 0; i < MAX_BUTTON_IMAGES; i++) {
            if (this.buttonImage[i]) {
                this.resMgr.releaseImage(this.buttonImage[i]);
                this.buttonImage[i] = null;
            }
        }
        
        // Clean up sound
        this.clickSound = null;
        
        // Clean up tooltip
        this.toolTipCtrl = null;
    }
}

module.exports = {
    Button,
    MAX_BUTTON_IMAGES,
    RES_DEFAULT_BUTTON_IMAGE_NAMES
};
