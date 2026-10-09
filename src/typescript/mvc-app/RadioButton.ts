import type PDG = require('../../../types');
import type { Controller } from "./Controller";
import type { KeyInfo,MouseInfo } from './engine';
import { engine } from './engine';

// -----------------------------------------------
// RadioButton.ts
//
// TypeScript implementation of the RadioButton UI component
// A radio button with multiple options
//
// Adapted from the PDG C++ and JavaScript MVC implementations
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

import { ControlAttributes,ControlState,ControlType } from "./ControlAttributes";
import { View } from "./View";

const MAX_RADIO_IMAGES = 2;

/**
 * RadioButton UI component that extends View
 * Provides radio button functionality with multiple options
 */
class RadioButton extends View {
    resMgr: PDG.ResourceManager;
    mpRadioImages: (PDG.Image | null)[];
    selectedIndex: number;
    strings: string[];
    maxStrings: number;
    attributes: ControlAttributes;

    constructor(controller: Controller, viewArea: PDG.Rect, resourceTextID: number, numStrings: number) {
        super(controller, viewArea);

        this.resMgr = controller.getApplication().getResourceManager();
        this.mpRadioImages = new Array(MAX_RADIO_IMAGES).fill(null);
        this.selectedIndex = 0;
        this.strings = [];
        this.maxStrings = numStrings;
        this.attributes = new ControlAttributes();
        this.textSize(14);

        this.attributes
            .stateForeground(ControlState.Normal, new engine.Color(0, 0, 0, 1))
            .stateForeground(ControlState.Selected, new engine.Color(0, 0, 0, 1))
            .stateForeground(ControlState.Disabled, new engine.Color(0.7, 0.7, 0.7, 1))
            .stateForeground(ControlState.SelectedDisabled, new engine.Color(0.7, 0.7, 0.7, 1));
        this.attributes.merge(controller.getTopController()
            .getControlAttributes(ControlType.RadioButton));
        this.loadStrings(resourceTextID, numStrings);
        this.calcClickableAreas();
    }

    /**
     * Load radio button images
     */
    loadImages(): void {
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
    loadStrings(resourceID: number, numStrings: number): void {
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
    calcClickableAreas(): void {
        const viewArea = this.getViewArea();
        const optionWidth = viewArea.width() / Math.max(1, this.strings.length);
        for (let i = 0; i < this.strings.length; i++) {
            this.removeClickablePart(i);
            const optionRect = new engine.Rect(
                i * optionWidth,
                0,
                (i + 1) * optionWidth,
                viewArea.height()
            );

            this.addClickablePart(optionRect, i);
        }
    }

    /**
     * Draw the radio button
     */
    drawSelf(port: PDG.Port, frameNum: number): void {
        this.drawRadioOptions(port);
    }

    /**
     * Draw radio options
     */
    drawRadioOptions(port: PDG.Port = this.getPort()): void {
        const viewArea = this.getViewArea();
        const optionWidth = viewArea.width() / Math.max(1, this.strings.length);
        const textAttrs = this.getDrawingAttributes(new engine.Attributes().textSize(super.getTextSize()).textStyle(engine.textStyle_Plain), true);
        const font = (typeof textAttrs.getFont === 'function' && textAttrs.getFont()) || port.getCurrentFont(textAttrs.getTextStyle());
        const capHeight = font.getFontCapHeight(textAttrs.getTextSize(), textAttrs.getTextStyle());
        const diameter = Math.max(1, Math.round(textAttrs.getTextSize()));
        const baseline = Math.round(viewArea.top + (viewArea.height()+capHeight)/2);

        for (let i = 0; i < this.strings.length; i++) {
            const selected = i === this.selectedIndex;
            const state = selected
                ? (this.isEnabled() ? ControlState.Selected : ControlState.SelectedDisabled)
                : (this.isEnabled() ? ControlState.Normal : ControlState.Disabled);
            const visual = this.attributes.state(state);
            const normal = this.attributes.state(ControlState.Normal);
            const image = visual.hasImage ? visual.image : (normal.hasImage ? normal.image : null);
            const imageWidth = image ? (image.getWidth()) : diameter;
            const imageHeight = image ? (image.getHeight()) : diameter;
            const optionX = viewArea.left + i * optionWidth;
            const radioRect = new engine.Rect(
                optionX,
                (image ? viewArea.top + (viewArea.height() - imageHeight) / 2 : baseline-(capHeight+diameter)/2),
                optionX + imageWidth,
                (image ? viewArea.top + (viewArea.height() - imageHeight) / 2 : baseline-(capHeight+diameter)/2) + imageHeight
            );
            this.attributes.draw(port, radioRect, state, this);
            if (!image && !visual.hasDrawing && !visual.hasDrawRoutine &&
                !normal.hasDrawing && !normal.hasDrawRoutine) {
                this.drawRadioCircle(radioRect, selected,
                    visual.hasForeground && visual.foreground ? visual.foreground : (normal.foreground || new engine.Color(0, 0, 0, 1)));
            }

            // Draw text
            const textPoint = new engine.Point(
                optionX + imageWidth + 5,
                baseline
            );
            const textColor = visual.hasForeground && visual.foreground ? visual.foreground : (normal.foreground || new engine.Color(0, 0, 0, 1));

            port.drawText(this.strings[i], textPoint, this.getDrawingAttributes(new engine.Attributes()
                .textSize(super.getTextSize()).textStyle(engine.textStyle_Plain).fillColor(textColor), true));
        }
    }

    /**
     * Draw radio circle
     * @param {engine.Rect} rect - Circle rectangle
     * @param {boolean} selected - Whether this option is selected
     */
    drawRadioCircle(rect: PDG.Rect, selected: boolean, color: PDG.Color = new engine.Color(0, 0, 0, 1)): void {
        const port = this.getPort();

        // Draw outer circle
        port.drawEllipse(rect.centerPoint(), (rect.width()-1) / 2, (rect.height()-1) / 2, this.getDrawingAttributes(new engine.Attributes().fillColor(new engine.Color(1, 1, 1, 1)).lineStyle(engine.lineStyle_Solid).lineColor(color), true));

        if (selected) {
            // Draw inner filled circle
            const radius = rect.width()*0.25;
            port.drawCircle(rect.centerPoint(), radius,
                this.getDrawingAttributes(new engine.Attributes().fillColor(color), true));
        }
    }

    /**
     * Handle click
     * @param {number} part - Clicked part
     */
    doClick(part: number): void {
        if (!this.isEnabled()) return;
        if (part >= 0 && part < this.strings.length) {
            this.setSelectedIndex(part);
            this.attributes.playClick();
        }
    }

    /**
     * Handle mouse down
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doMouseDown(mouseInfo: MouseInfo, id: number, part: number): boolean {
        if (!this.isEnabled()) return false;
        if (part >= 0 && part < this.strings.length) {
            return true; // Selection waits for a completed click
        }
        return false;
    }

    /**
     * Handle a completed click
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doLeftClick(mouseInfo: MouseInfo, id: number, part: number) {
        if (!this.isEnabled()) return false;
        if (part >= 0 && part < this.strings.length) {
            this.doClick(part);
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
        if (!this.isEnabled()) return false;
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
    moveSelection(delta: number): void {
        let newIndex = this.selectedIndex + delta;
        newIndex = Math.max(0, Math.min(newIndex, this.strings.length - 1));
        this.setSelectedIndex(newIndex);
    }

    /**
     * Get selected index
     * @returns {number} Selected index
     */
    getSelectedIndex(): number {
        return this.selectedIndex;
    }

    /**
     * Set selected index
     * @param {number} selected - Index to select
     */
    setSelectedIndex(selected: number): void {
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
    getSelectedText(): string {
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
    getString(index: number): string {
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
    setString(index: number, text: string): void {
        if (index >= 0 && index < this.strings.length) {
            this.strings[index] = text;
        }
    }

    /**
     * Add string option
     * @param {string} text - Text to add
     */
    addString(text: string): void {
        this.strings.push(text);
        this.maxStrings = this.strings.length;
        this.calcClickableAreas();
    }

    /**
     * Remove string at index
     * @param {number} index - Index to remove
     */
    removeString(index: number): void {
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
    clearStrings(): void {
        this.strings = [];
        this.maxStrings = 0;
        this.selectedIndex = 0;
        this.calcClickableAreas();
    }

    /**
     * Get number of options
     * @returns {number} Number of options
     */
    getOptionCount(): number {
        return this.strings.length;
    }

    /**
     * Check if option is selected
     * @param {number} index - Option index
     * @returns {boolean} true if selected
     */
    isOptionSelected(index: number): boolean {
        return index === this.selectedIndex;
    }

    /**
     * Select next option
     */
    selectNext(): void {
        this.moveSelection(1);
    }

    /**
     * Select previous option
     */
    selectPrevious(): void {
        this.moveSelection(-1);
    }

    /**
     * Select first option
     */
    selectFirst(): void {
        this.setSelectedIndex(0);
    }

    /**
     * Select last option
     */
    selectLast(): void {
        this.setSelectedIndex(this.strings.length - 1);
    }

    /**
     * Get all strings
     * @returns {string[]} Array of all strings
     */
    getAllStrings(): string[] {
        return [...this.strings];
    }

    /**
     * Set all strings
     * @param {string[]} strings - Array of strings
     */
    setAllStrings(strings: string[]): void {
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
    findString(text: string): number {
        return this.strings.indexOf(text);
    }

    /**
     * Set text size
     * @param {number} size - Text size
     */
    setTextSize(size: number): void {
        // This would be used in a more advanced implementation
        // For now, we'll just store it
        this.textSize(size);
    }

    /**
     * Get text size
     * @returns {number} Text size
     */
    getTextSize(): number {
        return super.getTextSize() || 12;
    }

    setClickSound(clickSound: PDG.Sound | null): void {
        this.attributes.clickSound(clickSound);
    }

    setAttributes(attributes: ControlAttributes): void {
        this.attributes.merge(attributes);
        this.calcClickableAreas();
    }

    getAttributes(): ControlAttributes {
        return this.attributes;
    }

    /**
     * Cleanup when radio button is destroyed
     */
    destroy() {
        super.destroy();
        // Clean up images
        for (let i = 0; i < MAX_RADIO_IMAGES; i++) {
            this.mpRadioImages[i] = null;
        }

        // Clear strings
        this.strings = [];
        this.attributes = new ControlAttributes();
    }
}

export {
MAX_RADIO_IMAGES,RadioButton
};
