// -----------------------------------------------
// RadioButton.js
// 
// JavaScript port of the RadioButton UI component
// A radio button with multiple options
//
// Ported from C++ by Assistant, 2024
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

const { View  } = require('./View');

const MAX_RADIO_IMAGES = 2;

/**
 * RadioButton UI component that extends View
 * Provides radio button functionality with multiple options
 */
class RadioButton extends View {
    constructor(controller, viewArea, resourceTextID, numStrings) {
        super(controller, viewArea);
        
        this.resMgr = controller.getApplication().getResourceManager();
        this.mpRadioImages = new Array(MAX_RADIO_IMAGES).fill(null);
        this.selectedIndex = 0;
        this.strings = [];
        this.maxStrings = numStrings;
        
        this.loadImages();
        this.loadStrings(resourceTextID, numStrings);
        this.calcClickableAreas();
    }

    /**
     * Load radio button images
     */
    loadImages() {
        try {
            // In a real implementation, you would load images from resources
            // For now, we'll create placeholder images
            for (let i = 0; i < MAX_RADIO_IMAGES; i++) {
                this.mpRadioImages[i] = null; // Placeholder
            }
        } catch (error) {
            console.warn('Failed to load radio button images:', error);
        }
    }

    /**
     * Load strings from resources
     * @param {number} resourceID - Resource ID
     * @param {number} numStrings - Number of strings
     */
    loadStrings(resourceID, numStrings) {
        try {
            this.strings = [];
            for (let i = 0; i < numStrings; i++) {
                const text = this.resMgr.getString(resourceID, i);
                this.strings.push(text);
            }
        } catch (error) {
            console.warn(`Failed to load strings from resource ${resourceID}:`, error);
            // Create placeholder strings
            for (let i = 0; i < numStrings; i++) {
                this.strings.push(`Option ${i + 1}`);
            }
        }
    }

    /**
     * Calculate clickable areas
     */
    calcClickableAreas() {
        const viewArea = this.getViewArea();
        const radioSize = 16;
        const textHeight = 16;
        const spacing = 4;
        
        // Calculate total height needed
        const totalHeight = this.strings.length * (radioSize + spacing) - spacing;
        const startY = viewArea.top + (viewArea.height() - totalHeight) / 2;
        
        // Add clickable areas for each radio option
        for (let i = 0; i < this.strings.length; i++) {
            const optionRect = new pdg.Rect(
                viewArea.left,
                startY + i * (radioSize + spacing),
                viewArea.width(),
                radioSize
            );
            
            this.addClickablePart(optionRect, i);
        }
    }

    /**
     * Draw the radio button
     */
    drawSelf(port, frameNum) {
        const viewArea = this.getViewArea();
        
        // Draw background
        var backgroundAttrs = new pdg.Attributes().fillColor(new pdg.Color(1.0, 1.0, 1.0, 1.0));
        port.drawRect(viewArea, backgroundAttrs);
        
        // Draw border
        var borderAttrs = new pdg.Attributes().lineColor(new pdg.Color(0.7, 0.7, 0.7, 1.0)).lineThickness(1);
        port.drawRect(viewArea, borderAttrs);
        
        // Draw radio options
        this.drawRadioOptions();
    }

    /**
     * Draw radio options
     */
    drawRadioOptions() {
        const port = this.getPort();
        const viewArea = this.getViewArea();
        const radioSize = 16;
        const textHeight = 16;
        const spacing = 4;
        
        // Calculate total height needed
        const totalHeight = this.strings.length * (radioSize + spacing) - spacing;
        const startY = viewArea.top + (viewArea.height() - totalHeight) / 2;
        
        for (let i = 0; i < this.strings.length; i++) {
            const optionY = startY + i * (radioSize + spacing);
            const radioRect = new pdg.Rect(
                viewArea.left + 8,
                optionY,
                radioSize,
                radioSize
            );
            
            // Draw radio circle
            this.drawRadioCircle(radioRect, i === this.selectedIndex);
            
            // Draw text
            const textPoint = new pdg.Point(
                viewArea.left + 8 + radioSize + 8,
                optionY + radioSize / 2 + 6
            );
            
            const textColor = i === this.selectedIndex ? 
                new pdg.Color(0.0, 0.0, 0.0, 1.0) : 
                new pdg.Color(0.5, 0.5, 0.5, 1.0);
            
            port.drawText(this.strings[i], textPoint, 12, pdg.textStyle_Plain, textColor);
        }
    }

    /**
     * Draw radio circle
     * @param {pdg.Rect} rect - Circle rectangle
     * @param {boolean} selected - Whether this option is selected
     */
    drawRadioCircle(rect, selected) {
        const port = this.getPort();
        
        // Draw outer circle
        var outerAttrs = new pdg.Attributes().lineColor(new pdg.Color(0.3, 0.3, 0.3, 1.0)).lineThickness(1);
        port.drawRect(rect, outerAttrs);
        
        if (selected) {
            // Draw inner filled circle
            const innerRect = new pdg.Rect(
                rect.left + 3,
                rect.top + 3,
                rect.width() - 6,
                rect.height() - 6
            );
            var innerAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.0, 0.0, 0.0, 1.0));
            port.drawRect(innerRect, innerAttrs);
        }
    }

    /**
     * Handle click
     * @param {number} part - Clicked part
     */
    doClick(part) {
        if (part >= 0 && part < this.strings.length) {
            this.setSelectedIndex(part);
        }
    }

    /**
     * Handle mouse down
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doMouseDown(mouseInfo, id, part) {
        if (part >= 0 && part < this.strings.length) {
            return true; // We'll handle the selection on mouse up
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
        if (part >= 0 && part < this.strings.length) {
            this.setSelectedIndex(part);
            return true;
        }
        return false;
    }

    /**
     * Handle key press
     * @param {Object} keyPressInfo - Key press information
     * @param {View} view - The view that has focus
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doKeyPress(keyPressInfo, view, id, part) {
        const keyCode = keyPressInfo.keyCode;
        
        switch (keyCode) {
            case 38: // Up arrow
                this.moveSelection(-1);
                return true;
                
            case 40: // Down arrow
                this.moveSelection(1);
                return true;
                
            case 32: // Space
                // Toggle current selection (though radio buttons don't really toggle)
                return true;
        }
        
        return false;
    }

    /**
     * Move selection by delta
     * @param {number} delta - Delta to move by
     */
    moveSelection(delta) {
        let newIndex = this.selectedIndex + delta;
        newIndex = Math.max(0, Math.min(newIndex, this.strings.length - 1));
        this.setSelectedIndex(newIndex);
    }

    /**
     * Get selected index
     * @returns {number} Selected index
     */
    getSelectedIndex() {
        return this.selectedIndex;
    }

    /**
     * Set selected index
     * @param {number} selected - Index to select
     */
    setSelectedIndex(selected) {
        if (selected >= 0 && selected < this.strings.length) {
            this.selectedIndex = selected;
            
            // Notify controller of selection change
            if (this.controller && typeof this.controller.radioButtonChanged === 'function') {
                this.controller.radioButtonChanged(this.selectedIndex, this);
            }
        }
    }

    /**
     * Get selected text
     * @returns {string} Selected text
     */
    getSelectedText() {
        if (this.selectedIndex >= 0 && this.selectedIndex < this.strings.length) {
            return this.strings[this.selectedIndex];
        }
        return '';
    }

    /**
     * Get string at index
     * @param {number} index - String index
     * @returns {string} String at index
     */
    getString(index) {
        if (index >= 0 && index < this.strings.length) {
            return this.strings[index];
        }
        return '';
    }

    /**
     * Set string at index
     * @param {number} index - String index
     * @param {string} text - New text
     */
    setString(index, text) {
        if (index >= 0 && index < this.strings.length) {
            this.strings[index] = text;
        }
    }

    /**
     * Add string option
     * @param {string} text - Text to add
     */
    addString(text) {
        this.strings.push(text);
        this.maxStrings = this.strings.length;
        this.calcClickableAreas();
    }

    /**
     * Remove string at index
     * @param {number} index - Index to remove
     */
    removeString(index) {
        if (index >= 0 && index < this.strings.length) {
            this.strings.splice(index, 1);
            this.maxStrings = this.strings.length;
            
            // Adjust selection if necessary
            if (this.selectedIndex >= index) {
                this.selectedIndex = Math.max(0, this.selectedIndex - 1);
            }
            
            this.calcClickableAreas();
        }
    }

    /**
     * Clear all strings
     */
    clearStrings() {
        this.strings = [];
        this.maxStrings = 0;
        this.selectedIndex = 0;
        this.calcClickableAreas();
    }

    /**
     * Get number of options
     * @returns {number} Number of options
     */
    getOptionCount() {
        return this.strings.length;
    }

    /**
     * Check if option is selected
     * @param {number} index - Option index
     * @returns {boolean} true if selected
     */
    isOptionSelected(index) {
        return index === this.selectedIndex;
    }

    /**
     * Select next option
     */
    selectNext() {
        this.moveSelection(1);
    }

    /**
     * Select previous option
     */
    selectPrevious() {
        this.moveSelection(-1);
    }

    /**
     * Select first option
     */
    selectFirst() {
        this.setSelectedIndex(0);
    }

    /**
     * Select last option
     */
    selectLast() {
        this.setSelectedIndex(this.strings.length - 1);
    }

    /**
     * Get all strings
     * @returns {string[]} Array of all strings
     */
    getAllStrings() {
        return [...this.strings];
    }

    /**
     * Set all strings
     * @param {string[]} strings - Array of strings
     */
    setAllStrings(strings) {
        this.strings = [...strings];
        this.maxStrings = this.strings.length;
        
        // Ensure selection is valid
        if (this.selectedIndex >= this.strings.length) {
            this.selectedIndex = Math.max(0, this.strings.length - 1);
        }
        
        this.calcClickableAreas();
    }

    /**
     * Find string index
     * @param {string} text - Text to find
     * @returns {number} Index of string or -1 if not found
     */
    findString(text) {
        return this.strings.indexOf(text);
    }

    /**
     * Set text size
     * @param {number} size - Text size
     */
    setTextSize(size) {
        // This would be used in a more advanced implementation
        // For now, we'll just store it
        this.textSize = size;
    }

    /**
     * Get text size
     * @returns {number} Text size
     */
    getTextSize() {
        return this.textSize || 12;
    }

    /**
     * Cleanup when radio button is destroyed
     */
    destroy() {
        // Clean up images
        for (let i = 0; i < MAX_RADIO_IMAGES; i++) {
            this.mpRadioImages[i] = null;
        }
        
        // Clear strings
        this.strings = [];
    }
}

module.exports = {
    RadioButton,
    MAX_RADIO_IMAGES
};
