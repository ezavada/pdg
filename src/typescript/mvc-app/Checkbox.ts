import type PDG = require('../../../types');
import type { Controller } from "./Controller";
import type { MouseInfo } from './engine';
import { engine } from './engine';

// -----------------------------------------------
// Checkbox.ts
//
// TypeScript implementation of the Checkbox UI component
// A checkbox with text label
//
// Adapted from the PDG C++ and JavaScript MVC implementations
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

import { ControlAttributes,ControlState,ControlType } from "./ControlAttributes";
import { View } from "./View";
const pdgDefs = engine;

const CHECKBOX_TEXT_SIZE = 16;
const SPACE_BETWEEN_BOX_AND_TEXT = 5;
const SPACE_UP_FROM_BOTTOM = 5;

function getCheckboxTextStyle() {
    return Number.isFinite(engine.textStyle_Bold)
        ? engine.textStyle_Bold : pdgDefs.textStyle_Bold;
}

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
    resMgr: PDG.ResourceManager;
    mpCheckboxImages: (PDG.Image | null)[];
    attributes: ControlAttributes;
    checked: boolean;
    string: string;

    constructor(controller: Controller, viewArea: PDG.Rect) {
        if (!controller) {
            throw new Error("Controller is required");
        }

        super(controller, viewArea);

        this.resMgr = controller.getApplication().getResourceManager();
        this.mpCheckboxImages = new Array(CBImages.NUM_CHECKBOX_IMAGES).fill(null);
        this.attributes = new ControlAttributes();
        this.checked = false;
        this.string = '';
        this.textSize(CHECKBOX_TEXT_SIZE);

        this.attributes
            .stateForeground(ControlState.Normal, new engine.Color(0, 0, 0, 1))
            .stateForeground(ControlState.Selected, new engine.Color(0, 0, 0, 1))
            .stateForeground(ControlState.Disabled, new engine.Color(0.7, 0.7, 0.7, 1))
            .stateForeground(ControlState.SelectedDisabled, new engine.Color(0.7, 0.7, 0.7, 1));
        this.attributes.merge(controller.getTopController()
            .getControlAttributes(ControlType.Checkbox));
        this.calcClickableAreas();
    }

    /**
     * Load checkbox images
     */
    loadImages(): void {
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
    createPlaceholderImages(): void {
        // In a real implementation, you would create actual images
        // For now, we'll handle drawing in drawSelf()
        for (let i = 0; i < CBImages.NUM_CHECKBOX_IMAGES; i++) {
            this.mpCheckboxImages[i] = null;
        }
    }

    /**
     * Draw the checkbox
     */
    drawSelf(): void {
        const port = this.getPort();
        const viewArea = this.getViewArea();
        const state = this.checked
            ? (this.isEnabled() ? ControlState.Selected : ControlState.SelectedDisabled)
            : (this.isEnabled() ? ControlState.Normal : ControlState.Disabled);
        const visual = this.attributes.state(state);
        const normal = this.attributes.state(ControlState.Normal);
        const image = visual.hasImage ? visual.image : (normal.hasImage ? normal.image : null);
        const imageWidth = image ? (image.getWidth()) : 0;
        const imageHeight = image ? (image.getHeight()) : 0;
        const metrics = this.getTextMetrics(port);
        const baseline = Math.round(
            (viewArea.height() - metrics.ascent - metrics.descent) * 0.5 + metrics.ascent);
        const checkboxSize = image ? imageWidth : Math.max(1, Math.round(metrics.ascent + 2), Math.round(metrics.capHeight + 4));
        const checkboxHeight = image ? imageHeight : checkboxSize;
        const checkboxTop = image
            ? viewArea.top + (viewArea.height() - checkboxHeight) / 2
            : viewArea.top + baseline - (metrics.capHeight + checkboxHeight) / 2;
        const checkboxRect = new engine.Rect(
            viewArea.left,
            checkboxTop,
            viewArea.left + checkboxSize,
            checkboxTop + checkboxHeight
        );

        this.attributes.draw(port, checkboxRect, state, this);
        if (!image && !visual.hasDrawing && !visual.hasDrawRoutine &&
            !normal.hasDrawing && !normal.hasDrawRoutine) {
            const markColor = visual.hasForeground && visual.foreground ? visual.foreground : (normal.foreground || new engine.Color(0, 0, 0, 1));
            port.drawRect(new engine.Rect(checkboxRect).shrink(0.5), this.getDrawingAttributes(new engine.Attributes()
                .fillColor(new engine.Color(1, 1, 1, 1)).lineStyle(engine.lineStyle_Solid).lineColor(markColor).lineThickness(1)));
            if (this.checked) this.drawCheckmark(checkboxRect, markColor);
        }

        // Draw text if present
        if (this.string) {
            const textColor = visual.hasForeground && visual.foreground ? visual.foreground : (normal.foreground || new engine.Color(0, 0, 0, 1));
            this.drawText(checkboxSize, baseline, textColor);
        }
    }

    getTextMetrics(port: PDG.Port = this.getPort()) {
        const attrs = this.getDrawingAttributes(new engine.Attributes().textSize(super.getTextSize()).textStyle(getCheckboxTextStyle()), true);
        const style = attrs.getTextStyle();
        try {
            const font = (typeof attrs.getFont === 'function' && attrs.getFont()) || port.getCurrentFont(style);
            const ascent = font.getFontAscent(super.getTextSize(), style);
            const descent = font.getFontDescent(super.getTextSize(), style);
            const capHeight = font.getFontCapHeight(super.getTextSize(), style);
            if (Number.isFinite(ascent) && ascent > 0 &&
                Number.isFinite(descent) && descent >= 0) {
                return { ascent, descent, capHeight };
            }
        } catch (_) {}
        return { ascent: super.getTextSize() * 0.8, descent: super.getTextSize() * 0.2, capHeight: super.getTextSize() * 0.7 };
    }

    /**
     * Draw checkbox using loaded images
     */
    drawWithImages(): void {
        const port = this.getPort();
        const viewArea = this.getViewArea();

        const imageIndex = this.checked ? CBImages.CLOSED : CBImages.OPEN;
        const image = this.mpCheckboxImages[imageIndex];

        if (image) {
            // Calculate checkbox size (assume square)
            const checkboxSize = Math.min(viewArea.height(), 20); // Standard checkbox size
            const checkboxRect = new engine.Rect(viewArea.left, viewArea.top, checkboxSize, checkboxSize);

            port.drawImage(image, checkboxRect, this.getDrawingAttributes(new engine.Attributes()));
        }
    }

    /**
     * Draw standard checkbox without images
     */
    drawStandardCheckbox(): void {
        const port = this.getPort();
        const viewArea = this.getViewArea();

        // Calculate checkbox size (assume square)
        const checkboxSize = Math.min(viewArea.height(), 20); // Standard checkbox size
        const checkboxRect = new engine.Rect(viewArea.left, viewArea.top, checkboxSize, checkboxSize);

        // Choose colors based on state
        let borderColor, fillColor, checkColor;

        if (!this.isEnabled()) {
            borderColor = new engine.Color(0.5, 0.5, 0.5, 1.0); // Gray
            fillColor = new engine.Color(0.8, 0.8, 0.8, 1.0);
            checkColor = new engine.Color(0.6, 0.6, 0.6, 1.0);
        } else {
            borderColor = new engine.Color(0.2, 0.2, 0.2, 1.0); // Dark gray
            fillColor = new engine.Color(1.0, 1.0, 1.0, 1.0); // White
            checkColor = new engine.Color(0.0, 0.0, 0.0, 1.0); // Black
        }

        // Draw checkbox background
        var backgroundAttrs = new engine.Attributes().fillColor(fillColor);
        port.drawRect(checkboxRect, this.getDrawingAttributes(backgroundAttrs));

        // Draw checkbox border
        var borderAttrs = new engine.Attributes().lineColor(borderColor).lineThickness(1);
        port.drawRect(checkboxRect, this.getDrawingAttributes(borderAttrs));

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
    drawCheckmark(checkboxRect: PDG.Rect, color: PDG.Color): void {
        const port = this.getPort();
        // A filled glyph remains bold even on GL implementations limited to 1px lines.
        const check = new engine.Polygon();
        for (const [x,y] of [[.08,.46],[.26,.29],[.42,.51],[.77,.08],[.94,.25],[.43,.92]]) {
            check.insertPoint(check.getPointCount(), new engine.Point(
                checkboxRect.left+x*checkboxRect.width(), checkboxRect.top+y*checkboxRect.height()));
        }
        port.drawPolygon(check, this.getDrawingAttributes(new engine.Attributes().fillColor(color), true));
    }

    /**
     * Draw checkbox text
     */
    drawText(checkboxSize: number, baseline: number, textColor: PDG.Color | null = null): void {
        if (!this.string) return;

        const port = this.getPort();
        const viewArea = this.getViewArea();

        // Calculate text position (to the right of checkbox)
        const textX = viewArea.left + checkboxSize + SPACE_BETWEEN_BOX_AND_TEXT;
        const textY = viewArea.top + baseline;

        textColor = textColor || (this.isEnabled() ?
            new engine.Color(0.0, 0.0, 0.0, 1.0) : // Black
            new engine.Color(0.5, 0.5, 0.5, 1.0));  // Gray

        // Draw text
        port.drawText(this.string, new engine.Point(textX, textY), this.getDrawingAttributes(new engine.Attributes()
            .textSize(super.getTextSize()).textStyle(getCheckboxTextStyle()).fillColor(textColor), true));
    }

    /**
     * Calculate clickable areas
     */
    calcClickableAreas(): void {
        const viewArea = this.getViewArea();
        this.removeClickablePart(CheckboxClickIDs.CLICK_ID_CHECKBOX);
        this.addClickablePart(new engine.Rect(0, 0, viewArea.width(), viewArea.height()),
            CheckboxClickIDs.CLICK_ID_CHECKBOX);
    }

    /**
     * Check if checkbox is checked
     * @returns {boolean} true if checked
     */
    isChecked(): boolean {
        return this.checked;
    }

    /**
     * Set checked state
     * @param {boolean} checked - Whether checkbox is checked
     */
    setChecked(checked: boolean): void {
        if (this.checked !== checked) {
            this.checked = checked;
        }
    }

    /**
     * Toggle checked state
     */
    toggle(): void {
        this.setChecked(!this.checked);
    }

    /**
     * Set checkbox text
     * @param {string} str - Text to display
     */
    setString(str: string): void {
        this.string = str || '';
        if (!this.string) return;

        const port = this.getPort();
        const style = getCheckboxTextStyle();
        const metrics = this.getTextMetrics(port);
        const normal = this.attributes.state(ControlState.Normal);
        const image = normal.hasImage ? normal.image : null;
        const imageWidth = image
            ? (image.getWidth()) : 0;
        const imageHeight = image
            ? (image.getHeight()) : 0;
        const boxWidth = image ? imageWidth : Math.max(1, Math.round(metrics.ascent + 2), Math.round(metrics.capHeight + 4));
        const boxHeight = image ? imageHeight : boxWidth;
        const textWidth = this._measureText(this.string, new engine.Attributes().textSize(super.getTextSize()).textStyle(style));
        const newClickArea = new engine.Rect(this.getViewArea());
        newClickArea.bottom = newClickArea.top + Math.max(
            boxHeight, Math.ceil(metrics.ascent + metrics.descent) + SPACE_UP_FROM_BOTTOM);
        newClickArea.right = newClickArea.left + boxWidth
            + SPACE_BETWEEN_BOX_AND_TEXT + textWidth;
        this.setViewArea(newClickArea);
        this.calcClickableAreas();
    }

    /**
     * Get checkbox text
     * @returns {string} Current text
     */
    getString(): string {
        return this.string;
    }

    /**
     * Set text size
     * @param {number} pointSize - Text size in points
     */
    setTextSize(pointSize: number): void {
        this.textSize(pointSize);
    }

    /**
     * Get text size
     * @returns {number} Current text size
     */
    getTextSize(): number {
        return super.getTextSize();
    }

    /**
     * Handle click
     * @param {number} part - Clicked part
     */
    doClick(part: number): void {
        if (!this.isEnabled()) return;
        if (part === CheckboxClickIDs.CLICK_ID_CHECKBOX) {
            this.toggle();

            this.attributes.playClick();
        }
    }

    /**
     * Handle left click
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doLeftClick(mouseInfo: MouseInfo, id: number, part: number) {
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
    setClickSound(clickSound: PDG.Sound): void {
        this.attributes.clickSound(clickSound);
    }

    /**
     * Get click sound
     * @returns {Sound} Current click sound
     */
    getClickSound(): PDG.Sound | null {
        return this.attributes.getClickSound();
    }

    setAttributes(attributes: ControlAttributes): void {
        this.attributes.merge(attributes);
        this.calcClickableAreas();
    }

    getAttributes(): ControlAttributes {
        return this.attributes;
    }

    /**
     * Set enabled state and redraw
     * @param {boolean} enabled - Whether checkbox is enabled
     */
    setEnabled(enabled: boolean) {
        super.setEnabled(enabled);
    }

    /**
     * Cleanup when checkbox is destroyed
     */
    destroy() {
        super.destroy();
        // Clean up images
        for (let i = 0; i < CBImages.NUM_CHECKBOX_IMAGES; i++) {
            if (this.mpCheckboxImages[i]) {
                // In C++, this would call image->release()
                this.mpCheckboxImages[i] = null;
            }
        }

        // Clean up sound
        this.attributes = new ControlAttributes();
    }
}

export {
CBImages,Checkbox,
CheckboxClickIDs
};
