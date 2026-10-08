import type PDG = require('../../../types');
import type { Controller } from "./Controller";
import type { KeyInfo,MouseInfo,MVCEventManager,UIEvent } from './engine';
import { engine } from './engine';

// -----------------------------------------------
// EditText.ts
//
// TypeScript implementation of the EditText UI component
// A text input field with caret and selection handling
//
// Adapted from the PDG C++ and JavaScript MVC implementations
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

import { View } from "./View";

const LEFT_MARGIN = 3;
const RIGHT_MARGIN = 3;
const TEXT_HEIGHT_OFFSET = 4;

/**
 * EditText click IDs
 */
const EditTextClickIDs = {
    CLICK_ID_EDITBOXVIEW: 1002
};

/**
 * EditText UI component that extends View and IObserver
 * Provides text input functionality with caret and selection
 */
class EditText extends View {
    resMgr: PDG.ResourceManager;
    mbkColor: PDG.Color;
    textColor: PDG.Color;
    fontSize: number;
    style: number;
    mbShowCaret: boolean;
    mbHasFocus: boolean;
    text: string;
    allowedKeys: string;
    blockedKeys: string;
    caretPos: number;
    highlightStartPoint: PDG.Point;
    highlightEndPoint: PDG.Point;
    highlightStartCharIndex: number;
    highlightEndCharIndex: number;
    maxChars: number;
    eventMgr: MVCEventManager;
    timerMgr: PDG.TimerManager;
    logMgr: PDG.LogManager;

    constructor(controller: Controller, viewArea: PDG.Rect, resourceID: number = -1, fontSize: number = 10,
                bkColor: PDG.Color = new engine.Color(1.0, 1.0, 1.0, 1.0),
                textColor: PDG.Color = new engine.Color(0.0, 0.0, 0.0, 1.0),
                textStyle: number = engine.textStyle_Plain) {

        super(controller, viewArea);

        this.resMgr = controller.getApplication().getResourceManager();
        this.mbkColor = bkColor;
        this.textColor = textColor;
        this.fontSize = fontSize;
        this.style = textStyle;
        this.mbShowCaret = false;
        this.mbHasFocus = false;
        this.text = '';
        this.allowedKeys = '';
        this.blockedKeys = '';
        this.caretPos = 0;
        this.highlightStartPoint = new engine.Point(0, 0);
        this.highlightEndPoint = new engine.Point(0, 0);
        this.highlightStartCharIndex = 0;
        this.highlightEndCharIndex = 0;
        this.maxChars = 256; // Default maximum characters

        // Event managers
        this.eventMgr = controller.getApplication().getEventManager();
        this.timerMgr = controller.getApplication().getTimerManager();
        this.logMgr = controller.getApplication().getLogManager();

        // Note: Event handling is done through the global engine.on* methods
        // No need to register with eventMgr.addHandler

        this.loadString(resourceID);
        this.calcClickableAreas();
    }

    /**
     * Load string from resource
     * @param {number} resourceID - Resource ID
     */
    loadString(resourceID: number): void {
        if (resourceID !== -1) {
            try {
                const text = this.resMgr.getString(resourceID);
                this.setText(text);
            } catch (error) {
                console.warn(`Failed to load string from resource ${resourceID}:`, error);
            }
        }
    }

    /**
     * Calculate clickable areas
     */
    calcClickableAreas(): void {
        const viewArea = this.getViewArea();
        this.removeClickablePart(EditTextClickIDs.CLICK_ID_EDITBOXVIEW);
        this.addClickablePart(new engine.Rect(0, 0, viewArea.width(), viewArea.height()), EditTextClickIDs.CLICK_ID_EDITBOXVIEW);
    }

    /**
     * Draw the EditText
     */
    drawSelf(): void {
        const port = this.getPort();
        const viewArea = this.getViewArea();

        // Draw background
        var backgroundAttrs = new engine.Attributes().fillColor(this.mbkColor);
        port.drawRect(viewArea, this.getDrawingAttributes(backgroundAttrs));

        // Draw border
        this.drawBorder();

        // Draw text
        this.drawText();

        // Draw selection highlight if any
        if (this.hasSelection()) {
            this.drawSelection();
        }

        // Draw caret if focused and visible
        if (this.mbHasFocus && this.mbShowCaret) {
            this.drawCaret();
        }
    }

    /**
     * Draw border around EditText
     */
    drawBorder(): void {
        const port = this.getPort();
        const viewArea = this.getViewArea();

        const borderColor = this.mbHasFocus ?
            new engine.Color(0.0, 0.5, 1.0, 1.0) : // Blue when focused
            new engine.Color(0.7, 0.7, 0.7, 1.0);  // Gray when not focused

        var borderAttrs = new engine.Attributes().lineColor(borderColor).lineThickness(1);
        port.drawRect(viewArea, this.getDrawingAttributes(borderAttrs));
    }

    /**
     * Draw text content
     */
    drawText(): void {
        const port = this.getPort();
        const viewArea = this.getViewArea();

        // Calculate text position
        const textX = viewArea.left + LEFT_MARGIN;
        const textAttrs = this.getDrawingAttributes(new engine.Attributes().textSize(this.fontSize).textStyle(this.style), true);
        const textY = viewArea.top + viewArea.height() / 2 + textAttrs.getTextSize() / 2;

        // Draw text
        if (this.text) {
            port.drawText(this.text, new engine.Point(textX, textY), this.getDrawingAttributes(new engine.Attributes().textSize(this.fontSize).textStyle(this.style).fillColor(this.textColor), true));
        }
    }

    /**
     * Draw selection highlight
     */
    drawSelection(): void {
        if (!this.hasSelection()) return;

        const port = this.getPort();
        const viewArea = this.getViewArea();

        // Calculate selection rectangle
        const startX = viewArea.left + LEFT_MARGIN + this.getTextWidth(this.text.substring(0, this.highlightStartCharIndex));
        const endX = viewArea.left + LEFT_MARGIN + this.getTextWidth(this.text.substring(0, this.highlightEndCharIndex));
        const selY = viewArea.top + TEXT_HEIGHT_OFFSET;
        const selHeight = viewArea.height() - TEXT_HEIGHT_OFFSET * 2;

        const selectionRect = new engine.Rect(startX, selY, endX, selY + selHeight);
        var selectionAttrs = new engine.Attributes().fillColor(new engine.Color(0.3, 0.5, 1.0, 0.3)); // Light blue highlight
        port.drawRect(selectionRect, this.getDrawingAttributes(selectionAttrs));
    }

    /**
     * Draw caret
     */
    drawCaret(): void {
        const port = this.getPort();
        const viewArea = this.getViewArea();

        // Calculate caret position
        const caretX = viewArea.left + LEFT_MARGIN + this.getTextWidth(this.text.substring(0, this.caretPos));
        const caretY = viewArea.top + TEXT_HEIGHT_OFFSET;
        const caretHeight = viewArea.height() - TEXT_HEIGHT_OFFSET * 2;

        // Draw caret as a vertical line
        port.drawLine(new engine.Point(caretX, caretY), new engine.Point(caretX, caretY + caretHeight), this.getDrawingAttributes(new engine.Attributes().lineColor(this.textColor).lineThickness(1), true));
    }

    /**
     * Get text width for a given string
     * @param {string} text - Text to measure
     * @returns {number} Text width in pixels
     */
    getTextWidth(text: string): number {
        return this._measureText(text, new engine.Attributes().textSize(this.fontSize).textStyle(this.style));
    }

    /**
     * Check if there's a text selection
     * @returns {boolean} true if there's a selection
     */
    hasSelection(): boolean {
        return this.highlightStartCharIndex !== this.highlightEndCharIndex;
    }

    /**
     * Handle mouse down
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doMouseDown(mouseInfo: MouseInfo, id: number, part: number): boolean {
        if (part === EditTextClickIDs.CLICK_ID_EDITBOXVIEW) {
            this.setFocus(true);

            // Calculate caret position based on click
            const localPoint = this.globalToLocal(mouseInfo.mousePos);
            this.caretPos = this.getCaretPositionFromPoint(localPoint);

            // Clear selection
            this.highlightStartCharIndex = this.caretPos;
            this.highlightEndCharIndex = this.caretPos;

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
    doMouseUp(mouseInfo: MouseInfo, id: number, part: number) {
        if (part === EditTextClickIDs.CLICK_ID_EDITBOXVIEW) {
            // Handle selection end
            const localPoint = this.globalToLocal(mouseInfo.mousePos);
            this.highlightEndCharIndex = this.getCaretPositionFromPoint(localPoint);

            return true;
        }
        return false;
    }

    /**
     * Handle mouse move
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     */
    doMouseMove(mouseInfo: MouseInfo, id: number, part: number) {
        if (part === EditTextClickIDs.CLICK_ID_EDITBOXVIEW && this.mbHasFocus) {
            // Update selection during drag
            const localPoint = this.globalToLocal(mouseInfo.mousePos);
            this.highlightEndCharIndex = this.getCaretPositionFromPoint(localPoint);
        }
    }

    /**
     * Handle double click
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @param {number} clickCount - Number of clicks
     * @returns {boolean} true if handled
     */
    doDoubleClick(mouseInfo: MouseInfo, id: number, part: number, clickCount: unknown) {
        if (part === EditTextClickIDs.CLICK_ID_EDITBOXVIEW) {
            this.selectAll();
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
    doKeyPress(keyPressInfo: KeyInfo, view: View, id: number, part: number): boolean {
        if (!this.mbHasFocus) return false;

        const key = keyPressInfo.key;
        const keyCode = keyPressInfo.keyCode;

        // Handle special keys
        if (keyCode === 8) { // Backspace
            this.handleBackspace();
            return true;
        } else if (keyCode === 46) { // Delete
            this.handleDelete();
            return true;
        } else if (keyCode === 37) { // Left arrow
            this.handleLeftArrow();
            return true;
        } else if (keyCode === 39) { // Right arrow
            this.handleRightArrow();
            return true;
        } else if (keyCode === 36) { // Home
            this.caretPos = 0;
            this.clearSelection();
            return true;
        } else if (keyCode === 35) { // End
            this.caretPos = this.text.length;
            this.clearSelection();
            return true;
        } else if (keyCode === 13) { // Enter
            // Handle enter key (could trigger validation or form submission)
            return true;
        }

        // Handle printable characters
        if (key !== undefined && this.isPrintableChar(key)) {
            this.handlePrintableChar(key);
            return true;
        }

        return false;
    }

    /**
     * Handle backspace key
     */
    handleBackspace(): void {
        if (this.hasSelection()) {
            this.deleteSelection();
        } else if (this.caretPos > 0) {
            this.text = this.text.substring(0, this.caretPos - 1) + this.text.substring(this.caretPos);
            this.caretPos--;
        }
    }

    /**
     * Handle delete key
     */
    handleDelete(): void {
        if (this.hasSelection()) {
            this.deleteSelection();
        } else if (this.caretPos < this.text.length) {
            this.text = this.text.substring(0, this.caretPos) + this.text.substring(this.caretPos + 1);
        }
    }

    /**
     * Handle left arrow key
     */
    handleLeftArrow(): void {
        if (this.caretPos > 0) {
            this.caretPos--;
            this.clearSelection();
        }
    }

    /**
     * Handle right arrow key
     */
    handleRightArrow(): void {
        if (this.caretPos < this.text.length) {
            this.caretPos++;
            this.clearSelection();
        }
    }

    /**
     * Handle printable character input
     * @param {string} char - Character to insert
     */
    handlePrintableChar(char: string): void {
        // Check if character is allowed
        if (!this.isCharAllowed(char)) {
            return;
        }

        // Check maximum length
        if (this.text.length >= this.maxChars) {
            return;
        }

        if (this.hasSelection()) {
            this.deleteSelection();
        }

        // Insert character
        this.text = this.text.substring(0, this.caretPos) + char + this.text.substring(this.caretPos);
        this.caretPos++;
    }

    /**
     * Delete selected text
     */
    deleteSelection(): void {
        const start = Math.min(this.highlightStartCharIndex, this.highlightEndCharIndex);
        const end = Math.max(this.highlightStartCharIndex, this.highlightEndCharIndex);

        this.text = this.text.substring(0, start) + this.text.substring(end);
        this.caretPos = start;
        this.clearSelection();
    }

    /**
     * Clear text selection
     */
    clearSelection(): void {
        this.highlightStartCharIndex = this.caretPos;
        this.highlightEndCharIndex = this.caretPos;
    }

    /**
     * Check if character is printable
     * @param {string} char - Character to check
     * @returns {boolean} true if printable
     */
    isPrintableChar(char: string): boolean {
        return !!char && char.length === 1 && char.charCodeAt(0) >= 32 && char.charCodeAt(0) <= 126;
    }

    /**
     * Check if character is allowed based on filters
     * @param {string} char - Character to check
     * @returns {boolean} true if allowed
     */
    isCharAllowed(char: string): boolean {
        if (this.blockedKeys && this.blockedKeys.includes(char)) {
            return false;
        }

        if (this.allowedKeys && !this.allowedKeys.includes(char)) {
            return false;
        }

        return true;
    }

    /**
     * Get caret position from point
     * @param {Point} point - Point in local coordinates
     * @returns {number} Caret position
     */
    getCaretPositionFromPoint(point: PDG.Point): number {
        const textX = LEFT_MARGIN;
        const clickX = point.x - textX;

        // Find the closest character position
        let pos = 0;
        for (let i = 0; i <= this.text.length; i++) {
            const width = this.getTextWidth(this.text.substring(0, i));
            if (clickX < width + this.getTextWidth(this.text[i] || '') / 2) {
                pos = i;
                break;
            }
            pos = i;
        }

        return Math.min(pos, this.text.length);
    }

    /**
     * Check if text can fit in display area
     * @param {Object} keyPressInfo - Key press information
     * @returns {boolean} true if text fits
     */
    canFitInDisplayArea(keyPressInfo: KeyInfo): boolean {
        const viewArea = this.getViewArea();
        const availableWidth = viewArea.width() - LEFT_MARGIN - RIGHT_MARGIN;

        // Check if adding the character would exceed available width
        const testText = this.text.substring(0, this.caretPos) +
                        (keyPressInfo.key || '') +
                        this.text.substring(this.caretPos);

        return this.getTextWidth(testText) <= availableWidth;
    }

    /**
     * Handle events
     * @param {string} eventType - Event type
     * @param {*} eventData - Event data
     * @returns {boolean} true if handled
     */
    handleEvent(eventType: string, eventData: UIEvent): boolean {
        if (eventType === 'eventType_Timer') {
            // Toggle caret visibility
            this.mbShowCaret = !this.mbShowCaret;
            return true;
        }
        return false;
    }

    /**
     * Set text filter
     * @param {string} allowedKeys - Allowed characters (empty string means all allowed)
     * @param {string} blockedKeys - Blocked characters
     */
    setFilter(allowedKeys: string = '', blockedKeys: string = ''): void {
        this.allowedKeys = allowedKeys;
        this.blockedKeys = blockedKeys;
    }

    /**
     * Set maximum buffer size
     * @param {number} maxChars - Maximum number of characters
     */
    setBufMax(maxChars: number): void {
        this.maxChars = maxChars;
    }

    /**
     * Get maximum buffer size
     * @returns {number} Maximum number of characters
     */
    getBufMax(): number {
        return this.maxChars;
    }

    /**
     * Check if EditText has focus
     * @returns {boolean} true if focused
     */
    hasFocus(): boolean {
        return this.mbHasFocus;
    }

    /**
     * Set focus state
     * @param {boolean} focus - Whether to have focus
     */
    setFocus(focus: boolean = true): void {
        if (this.mbHasFocus !== focus) {
            this.mbHasFocus = focus;

            if (focus) {
                // Start caret blinking timer
                this.timerMgr.startTimer(0x504401, 500, false); // oneShot = false (repeating), blink every 500ms
                this.mbShowCaret = true;
            } else {
                // Stop caret blinking timer
                this.timerMgr.cancelTimer(0x504401);
                this.mbShowCaret = false;
                this.clearSelection();
            }
        }
    }

    /**
     * Set text content
     * @param {string} text - Text to set
     */
    setText(text: string): void {
        this.text = (text || '').substring(0, this.maxChars);
        this.caretPos = this.text.length;
        this.clearSelection();
    }

    /**
     * Get text content
     * @param {string} outString - Output string (for compatibility)
     * @returns {string} Current text
     */
    getText(outString: string = ''): string {
        return this.text;
    }

    /**
     * Select all text
     */
    selectAll(): void {
        this.highlightStartCharIndex = 0;
        this.highlightEndCharIndex = this.text.length;
        this.caretPos = this.text.length;
    }

    /**
     * Get selected text
     * @returns {string} Selected text
     */
    getSelectedText(): string {
        if (!this.hasSelection()) return '';

        const start = Math.min(this.highlightStartCharIndex, this.highlightEndCharIndex);
        const end = Math.max(this.highlightStartCharIndex, this.highlightEndCharIndex);

        return this.text.substring(start, end);
    }

    /**
     * Replace selected text
     * @param {string} newText - Text to replace selection with
     */
    replaceSelection(newText: string): void {
        if (this.hasSelection()) {
            this.deleteSelection();
        }

        // Insert new text
        this.text = this.text.substring(0, this.caretPos) + newText + this.text.substring(this.caretPos);
        this.caretPos += newText.length;
    }

    /**
     * Set text color
     * @param {Object} color - Text color
     */
    setTextColor(color: PDG.Color): void {
        this.textColor = color;
    }

    /**
     * Set background color
     * @param {Object} color - Background color
     */
    setBackgroundColor(color: PDG.Color): void {
        this.mbkColor = color;
    }

    /**
     * Set font size
     * @param {number} size - Font size
     */
    setFontSize(size: number): void {
        this.fontSize = size;
    }

    /**
     * Cleanup when EditText is destroyed
     */
    destroy() {
        super.destroy();
        // Stop caret timer
        if (this.mbHasFocus) {
            this.timerMgr.cancelTimer(0x504401);
        }
    }
}

export {
EditText,
EditTextClickIDs,
LEFT_MARGIN,
RIGHT_MARGIN,
TEXT_HEIGHT_OFFSET
};
