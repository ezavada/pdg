// -----------------------------------------------
// Checkbox.js
// 
// JavaScript port of the Checkbox UI component
// A checkbox with text label
//
// Ported from C++ by Assistant, 2024
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

const { View } = require('./View');

/**
 * Checkbox click IDs
 */
const CheckboxClickIDs = {
    CLICK_ID_CHECKBOX: 1
};

/**
 * Checkbox images enumeration
 */
const CBImages = {
    OPEN: 0,    // Unchecked state
    CLOSED: 1,  // Checked state
    NUM_CHECKBOX_IMAGES: 2
};

/**
 * Checkbox UI component that extends View
 */
class Checkbox extends View {
    constructor(controller, viewArea) {
        if (!controller) {
            throw new Error("Controller is required");
        }

        super(controller, viewArea);
        
        this.resMgr = controller.getApplication().getResourceManager();
        this.mpCheckboxImages = new Array(CBImages.NUM_CHECKBOX_IMAGES).fill(null);
        this.mpClickSound = null;
        this.checked = false;
        this.string = '';
        this.textSize = 12;
        
        this.loadImages();
        this.calcClickableAreas();
    }

    /**
     * Load checkbox images
     */
    loadImages() {
        try {
            // Try to load images from resources
            // In a real implementation, you would load actual checkbox images
            for (let i = 0; i < CBImages.NUM_CHECKBOX_IMAGES; i++) {
                // this.mpCheckboxImages[i] = this.resMgr.getImage(CHECKBOX_IMAGE_ID, i);
                this.mpCheckboxImages[i] = null; // Placeholder
            }
        } catch (error) {
            console.warn('Failed to load checkbox images:', error);
            // Create placeholder images
            this.createPlaceholderImages();
        }
    }

    /**
     * Create placeholder checkbox images
     */
    createPlaceholderImages() {
        // In a real implementation, you would create actual images
        // For now, we'll handle drawing in drawSelf()
        for (let i = 0; i < CBImages.NUM_CHECKBOX_IMAGES; i++) {
            this.mpCheckboxImages[i] = null;
        }
    }

    /**
     * Draw the checkbox
     */
    drawSelf() {
        const port = this.getPort();
        const viewArea = this.getViewArea();
        
        if (this.mpCheckboxImages[0] && this.mpCheckboxImages[1]) {
            // Draw using loaded images
            this.drawWithImages();
        } else {
            // Draw standard checkbox
            this.drawStandardCheckbox();
        }
        
        // Draw text if present
        if (this.string) {
            this.drawText();
        }
    }

    /**
     * Draw checkbox using loaded images
     */
    drawWithImages() {
        const port = this.getPort();
        const viewArea = this.getViewArea();
        
        const imageIndex = this.checked ? CBImages.CLOSED : CBImages.OPEN;
        const image = this.mpCheckboxImages[imageIndex];
        
        if (image) {
            // Calculate checkbox size (assume square)
            const checkboxSize = Math.min(viewArea.height(), 20); // Standard checkbox size
            const checkboxRect = new pdg.Rect(viewArea.left, viewArea.top, checkboxSize, checkboxSize);
            
            port.drawImage(image, checkboxRect.leftTop(), checkboxRect);
        }
    }

    /**
     * Draw standard checkbox without images
     */
    drawStandardCheckbox() {
        const port = this.getPort();
        const viewArea = this.getViewArea();
        
        // Calculate checkbox size (assume square)
        const checkboxSize = Math.min(viewArea.height(), 20); // Standard checkbox size
        const checkboxRect = new pdg.Rect(viewArea.left, viewArea.top, checkboxSize, checkboxSize);
        
        // Choose colors based on state
        let borderColor, fillColor, checkColor;
        
        if (!this.isEnabled()) {
            borderColor = new pdg.Color(0.5, 0.5, 0.5, 1.0); // Gray
            fillColor = new pdg.Color(0.8, 0.8, 0.8, 1.0);
            checkColor = new pdg.Color(0.6, 0.6, 0.6, 1.0);
        } else {
            borderColor = new pdg.Color(0.2, 0.2, 0.2, 1.0); // Dark gray
            fillColor = new pdg.Color(1.0, 1.0, 1.0, 1.0); // White
            checkColor = new pdg.Color(0.0, 0.0, 0.0, 1.0); // Black
        }
        
        // Draw checkbox background
        var backgroundAttrs = new pdg.Attributes().fillColor(fillColor);
        port.drawRect(checkboxRect, backgroundAttrs);
        
        // Draw checkbox border
        var borderAttrs = new pdg.Attributes().lineColor(borderColor).lineThickness(1);
        port.drawRect(checkboxRect, borderAttrs);
        
        // Draw checkmark if checked
        if (this.checked) {
            this.drawCheckmark(checkboxRect, checkColor);
        }
    }

    /**
     * Draw checkmark inside checkbox
     * @param {Rect} checkboxRect - Checkbox rectangle
     * @param {Object} color - Checkmark color
     */
    drawCheckmark(checkboxRect, color) {
        const port = this.getPort();
        
        // Draw a simple checkmark using lines
        const margin = 3;
        const left = checkboxRect.left + margin;
        const right = checkboxRect.right - margin;
        const top = checkboxRect.top + margin;
        const bottom = checkboxRect.bottom - margin;
        const centerX = checkboxRect.left + checkboxRect.width() / 2;
        const centerY = checkboxRect.top + checkboxRect.height() / 2;
        
        // Draw checkmark as two lines forming a check
        // First line: from bottom-left to center
        port.drawLine(
            { x: left, y: centerY + 2 },
            { x: centerX - 1, y: bottom - 1 },
            color, 2
        );
        
        // Second line: from center to top-right
        port.drawLine(
            { x: centerX - 1, y: bottom - 1 },
            { x: right, y: top },
            color, 2
        );
    }

    /**
     * Draw checkbox text
     */
    drawText() {
        if (!this.string) return;
        
        const port = this.getPort();
        const viewArea = this.getViewArea();
        
        // Calculate text position (to the right of checkbox)
        const checkboxSize = Math.min(viewArea.height(), 20);
        const textX = viewArea.left + checkboxSize + 5; // 5 pixels spacing
        const textY = viewArea.top + viewArea.height() / 2;
        
        const textColor = this.isEnabled() ? 
            new pdg.Color(0.0, 0.0, 0.0, 1.0) : // Black
            new pdg.Color(0.5, 0.5, 0.5, 1.0);  // Gray
        
        // Draw text
        port.drawText(this.string, new Point(textX, textY), this.textSize, 
                     pdg.textStyle_Plain, textColor);
    }

    /**
     * Calculate clickable areas
     */
    calcClickableAreas() {
        const viewArea = this.getViewArea();
        
        // Make the entire view area clickable
        this.addClickablePart(viewArea, CheckboxClickIDs.CLICK_ID_CHECKBOX);
    }

    /**
     * Check if checkbox is checked
     * @returns {boolean} true if checked
     */
    isChecked() {
        return this.checked;
    }

    /**
     * Set checked state
     * @param {boolean} checked - Whether checkbox is checked
     */
    setChecked(checked) {
        if (this.checked !== checked) {
            this.checked = checked;
        }
    }

    /**
     * Toggle checked state
     */
    toggle() {
        this.setChecked(!this.checked);
    }

    /**
     * Set checkbox text
     * @param {string} str - Text to display
     */
    setString(str) {
        this.string = str || '';
    }

    /**
     * Get checkbox text
     * @returns {string} Current text
     */
    getString() {
        return this.string;
    }

    /**
     * Set text size
     * @param {number} pointSize - Text size in points
     */
    setTextSize(pointSize) {
        this.textSize = pointSize;
    }

    /**
     * Get text size
     * @returns {number} Current text size
     */
    getTextSize() {
        return this.textSize;
    }

    /**
     * Handle click
     * @param {number} part - Clicked part
     */
    doClick(part) {
        if (part === CheckboxClickIDs.CLICK_ID_CHECKBOX) {
            this.toggle();
            
            // Play click sound if available
            if (this.mpClickSound) {
                this.mpClickSound.play();
            }
        }
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
            this.doClick(part);
            return true;
        }
        return false;
    }

    /**
     * Set click sound
     * @param {Sound} clickSound - Sound to play when clicked
     */
    setClickSound(clickSound) {
        this.mpClickSound = clickSound;
    }

    /**
     * Get click sound
     * @returns {Sound} Current click sound
     */
    getClickSound() {
        return this.mpClickSound;
    }

    /**
     * Set enabled state and redraw
     * @param {boolean} enabled - Whether checkbox is enabled
     */
    setEnabled(enabled) {
        super.setEnabled(enabled);
    }

    /**
     * Cleanup when checkbox is destroyed
     */
    destroy() {
        // Clean up images
        for (let i = 0; i < CBImages.NUM_CHECKBOX_IMAGES; i++) {
            if (this.mpCheckboxImages[i]) {
                // In C++, this would call image->release()
                this.mpCheckboxImages[i] = null;
            }
        }
        
        // Clean up sound
        this.mpClickSound = null;
    }
}

module.exports = {
    Checkbox,
    CheckboxClickIDs,
    CBImages
};
