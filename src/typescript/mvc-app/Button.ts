import { host } from './host';
import type PDG = require('../../../types');
import type { Controller } from "./Controller";
import type { MouseInfo } from './engine';
import { engine } from './engine';

// -----------------------------------------------
// Button.ts
//
// TypeScript implementation of the Button UI component
// A clickable button with text and images
//
// Adapted from the PDG C++ and JavaScript MVC implementations
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

import { ControlAttributes,ControlState,ControlType } from "./ControlAttributes";
import { View } from "./View";
const pdgDefs = engine;

const MAX_BUTTON_IMAGES = 3;
const RES_DEFAULT_BUTTON_IMAGE_NAMES = ['button_default.png', 'button_pressed.png', 'button_disabled.png'];

// Keep this expression parallel with buttonTextStyle in Button.cpp, but resolve
// it at use time. PDG publishes its constants during runtime initialization.
function getButtonTextStyle() {
    const bold = Number.isFinite(engine.textStyle_Bold)
        ? engine.textStyle_Bold : pdgDefs.textStyle_Bold;
    const centered = Number.isFinite(engine.textStyle_Centered)
        ? engine.textStyle_Centered : pdgDefs.textStyle_Centered;
    return bold + centered;
}

function rectValues(rect: PDG.Rect | null) {
    return rect ? {
        left: rect.left,
        top: rect.top,
        right: rect.right,
        bottom: rect.bottom
    } : null;
}

function colorValues(color: PDG.Color | null) {
    return color ? {
        red: color.red,
        green: color.green,
        blue: color.blue,
        alpha: color.alpha
    } : null;
}

/**
 * Button UI component that extends View
 */
class Button extends View {
    resMgr: PDG.ResourceManager;
    buttonImage: (PDG.Image | null)[];
    attributes: ControlAttributes;
    text: string;
    buttonID: number;
    imageNames: string[] | null;
    styleId: number;
    isButtonPressed: boolean;
    isHovered: boolean;
    isToolTipEnabled: boolean;
    toolTipCtrl: Controller | null;
    nHasChangedAreaHit: number;
    textBaselineCenterPoint: PDG.Point;
    buttonTextSize: number;
    textDrawDiagnosticCount: number;
    lastTextMetrics: {style:number;size:number;ascent:number | null;descent:number | null;baseline:number;valid:boolean;error?:string} | null;
    hasValidTextMetrics = false;
    textColor = new engine.Color(0, 0, 0, 1);
    mouseIsDown = false;

    constructor(controller: Controller, frameOrPoint: PDG.Rect | PDG.Point, buttonID: number, resourceTextID: number = -1,
                substring: number = -1, imageNames: string[] | number | null = null, styleId: number = -1) {

        let rect;
        if (frameOrPoint instanceof engine.Point) {
            // Make button size match image
            rect = new engine.Rect(frameOrPoint.x, frameOrPoint.y, 0, 0);
        } else {
            // Make button size match rectangle
            rect = frameOrPoint;
        }

        super(controller, rect);

        if (typeof imageNames === 'number') {
            styleId = imageNames;
            imageNames = null;
        }

        this.resMgr = controller.getApplication().getResourceManager();
        this.buttonImage = new Array(MAX_BUTTON_IMAGES).fill(null);
        this.attributes = new ControlAttributes();
        this.text = '';
        this.buttonID = buttonID;
        this.imageNames = imageNames;
        this.styleId = styleId;
        this.isButtonPressed = false;
        this.isHovered = false;

        // Tooltip support
        this.isToolTipEnabled = false;
        this.toolTipCtrl = null;
        this.nHasChangedAreaHit = 0;
        this.textBaselineCenterPoint = new engine.Point(0, 0);
        this.buttonTextSize = 14;
        this.textDrawDiagnosticCount = 0;
        this.lastTextMetrics = null;

        this.initializeButton(resourceTextID, substring);
        this.finishInitButton();
    }

    /**
     * Initialize button with text from resources
     * @param {number} resourceTextID - Resource ID for text
     * @param {number} substring - Substring index
     */
    initializeButton(resourceTextID: number, substring: number): void {
        if (resourceTextID !== -1) {
            this.setTextFromResource(resourceTextID, substring);
        }
    }

    /**
     * Finish button initialization
     */
    finishInitButton(): void {
        this.attributes
            .stateAttributes(ControlState.Normal, new engine.Attributes()
                .fillColor(new engine.Color(1, 207 / 255, 82 / 255, 1))
                .lineStyle(engine.lineStyle_Solid).lineColor(new engine.Color(0.3, 0.32, 0.35, 1)).roundedCorners(7))
            .stateAttributes(ControlState.Hovered, new engine.Attributes()
                .fillColor(new engine.Color(1, 220 / 255, 120 / 255, 1))
                .lineStyle(engine.lineStyle_Solid).lineColor(new engine.Color(0.3, 0.32, 0.35, 1)).roundedCorners(7))
            .stateAttributes(ControlState.Pressed, new engine.Attributes()
                .fillColor(new engine.Color(1, 239 / 255, 173 / 255, 1))
                .lineStyle(engine.lineStyle_Solid).lineColor(new engine.Color(0.3, 0.32, 0.35, 1)).roundedCorners(7))
            .stateAttributes(ControlState.Disabled, new engine.Attributes()
                .fillColor(new engine.Color(0.8, 0.8, 0.8, 1.0))
                .lineStyle(engine.lineStyle_Solid).lineColor(new engine.Color(0.6, 0.6, 0.6, 1.0)).roundedCorners(7))
            .stateForeground(ControlState.Normal, new engine.Color(1, 1, 1, 1))
            .stateForeground(ControlState.Pressed, new engine.Color(1, 1, 1, 1))
            .stateForeground(ControlState.Disabled, new engine.Color(0.7, 0.7, 0.7, 1));
        this.attributes.merge(this.controller.getTopController()
            .getControlAttributes(ControlType.Button, this.styleId));
        if (this.imageNames) {
            this.loadImages();
            this.attributes
                .stateImage(ControlState.Normal, this.buttonImage[0])
                .stateImage(ControlState.Pressed, this.buttonImage[1])
                .stateImage(ControlState.Disabled, this.buttonImage[2]);
        }
        this.setWantsMouseOvers(true); // Enable mouse over events for tooltips
        this.updateLayout();
    }

    viewAreaChanged(previous: PDG.Rect): void {
        super.viewAreaChanged(previous);
        if (this.textBaselineCenterPoint) this.updateLayout();
    }

    updateLayout(): void {
        this.removeClickablePart(this.buttonID);
        this.addClickablePart(new engine.Rect(0, 0,
            this.getViewArea().width(), this.getViewArea().height()), this.buttonID);

        const height = this.getViewArea().height();
        this.buttonTextSize = Math.trunc(height / 2 - 1);
        this.textBaselineCenterPoint.x = this.getViewArea().width() / 2;
        this.hasValidTextMetrics = this._updateTextBaseline(this.getPort());
    }

    _updateTextBaseline(port: PDG.Port): boolean {
        const attrs=this.getDrawingAttributes(new engine.Attributes().textSize(this.buttonTextSize).textStyle(getButtonTextStyle()),true);
        const style = attrs.getTextStyle(), size=attrs.getTextSize();
        const height = this.getViewArea().height();
        const fallback = Math.round(
            (height - size) * 0.5 + size * 0.8) + 1;
        this.textBaselineCenterPoint.y = fallback;
        this.lastTextMetrics = {
            style,
            size: size,
            ascent: null,
            descent: null,
            baseline: fallback,
            valid: false
        };
        if (!port || typeof port.getCurrentFont !== 'function') return false;

        try {
            const font = (typeof attrs.getFont === "function" && attrs.getFont()) || port.getCurrentFont(style);
            const ascent = font && font.getFontAscent(size, style);
            const descent = font && font.getFontDescent(size, style);
            this.lastTextMetrics.ascent = ascent;
            this.lastTextMetrics.descent = descent;
            if (!Number.isFinite(ascent) || ascent <= 0 ||
                !Number.isFinite(descent) || descent < 0) return false;

            // This is the same baseline calculation used by Button.cpp.
            const measured = Math.round(
                (height - ascent - descent) * 0.5 + ascent) + 1;
            if (measured < size || measured > height) return false;
            this.textBaselineCenterPoint.y = measured;
            this.lastTextMetrics.baseline = measured;
            this.lastTextMetrics.valid = true;
            return true;
        } catch (error) {
            this.lastTextMetrics.error = error instanceof Error ? error.message : String(error);
            return false;
        }
    }

    /**
     * Set button text
     * @param {string} text - Button text
     */
    setText(text: string): void {
        this.text = text || '';
    }

    /**
     * Set text from resource
     * @param {number} resourceID - Resource ID
     * @param {number} substring - Substring index
     */
    setTextFromResource(resourceID: number, substring: number): void {
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
    setClickSound(clickSound: PDG.Sound): void {
        this.attributes.clickSound(clickSound);
    }

    setAttributes(attributes: ControlAttributes): void {
        this.attributes.merge(attributes);
    }

    getAttributes(): ControlAttributes {
        return this.attributes;
    }

    /**
     * Load button images
     */
    loadImages(): void {
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
    drawSelf(port: PDG.Port, frameNum: number): void {
        const state = !this.isEnabled() ? ControlState.Disabled
            : (this.isButtonPressed ? ControlState.Pressed
                : (this.isHovered ? ControlState.Hovered : ControlState.Normal));
        this.attributes.draw(port, this.getViewArea(), state, this);

        // Draw text if present
        if (this.text) {
            this.drawText(port, state);
        }
    }

    /**
     * Draw button using loaded images
     */
    drawWithImages(port: PDG.Port): void {
        const viewArea = this.getViewArea();

        let imageIndex = 0; // Default/normal state
        if (this.isButtonPressed) {
            imageIndex = 1; // Pressed state
        } else if (!this.isEnabled()) {
            imageIndex = 2; // Disabled state
        }

        const image = this.buttonImage[imageIndex];
        if (image) {
            port.drawImage(image, viewArea, this.getDrawingAttributes(new engine.Attributes()));
        }
    }

    /**
     * Draw standard button background
     */
    drawStandardButtonBackground(port: PDG.Port): void {
        const viewArea = this.getViewArea();

        // Choose colors based on state
        let bgColor, borderColor, textColor;

        if (!this.isEnabled()) {
            bgColor = new engine.Color(0.7, 0.7, 0.7, 1.0); // Gray
            borderColor = new engine.Color(0.5, 0.5, 0.5, 1.0);
            textColor = new engine.Color(0.4, 0.4, 0.4, 1.0);
        } else         if (this.isButtonPressed) {
            bgColor = new engine.Color(0.6, 0.6, 0.8, 1.0); // Darker blue
            borderColor = new engine.Color(0.2, 0.2, 0.4, 1.0);
            textColor = new engine.Color(1.0, 1.0, 1.0, 1.0);
        } else {
            bgColor = new engine.Color(0.8, 0.8, 0.9, 1.0); // Light blue
            borderColor = new engine.Color(0.3, 0.3, 0.5, 1.0);
            textColor = new engine.Color(0.0, 0.0, 0.0, 1.0);
        }

        // Draw background
        var backgroundAttrs = new engine.Attributes().fillColor(bgColor);
        port.drawRect(viewArea, this.getDrawingAttributes(backgroundAttrs));

        // Draw border
        var borderAttrs = new engine.Attributes().lineColor(borderColor).lineThickness(2);
        port.drawRect(viewArea, this.getDrawingAttributes(borderAttrs));

        // Store text color for text drawing
        this.textColor = textColor;
    }

    /**
     * Draw button text
     */
    drawText(port: PDG.Port, state: number = ControlState.Normal): void {
        if (!this.text) return;
        this.hasValidTextMetrics = this._updateTextBaseline(port);

        const viewArea = this.getViewArea();

        // Calculate text position (centered)
        const visual = this.attributes.state(state);
        const normal = this.attributes.state(ControlState.Normal);
        const textColor = visual.hasForeground && visual.foreground ? visual.foreground
            : (normal.hasForeground && normal.foreground ? normal.foreground : new engine.Color(0, 0, 0, 1));
        const baseline = this.localToGlobal(this.textBaselineCenterPoint);
        const textPoint = new engine.Point(baseline.x, baseline.y);
        const textStyle = getButtonTextStyle();
        const textAttributes = new engine.Attributes()
            .textSize(this.buttonTextSize).textStyle(textStyle).fillColor(textColor);

        const diagnosticOptions = host.PDG_CONTROL_DRAW_DIAGNOSTICS;
        const diagnosticLimit = typeof diagnosticOptions === "object" && diagnosticOptions.maxDrawsPerButton || 0;
        if (this.textDrawDiagnosticCount < diagnosticLimit) {
            this.textDrawDiagnosticCount++;
            let clipRect = null;
            try { clipRect = port.getClipRect(); } catch (_) {}
            console.log('[Button.drawText] ' + JSON.stringify({
                draw: this.textDrawDiagnosticCount,
                buttonID: this.buttonID,
                text: this.text,
                localBaseline: {
                    x: this.textBaselineCenterPoint.x,
                    y: this.textBaselineCenterPoint.y
                },
                drawPoint: { x: textPoint.x, y: textPoint.y },
                viewArea: rectValues(viewArea),
                clipRect: rectValues(clipRect),
                requested: {
                    textSize: this.buttonTextSize,
                    textStyle,
                    fillColor: colorValues(textColor)
                },
                attributes: {
                    textSize: textAttributes.getTextSize(),
                    textStyle: textAttributes.getTextStyle(),
                    fillColor: colorValues(textAttributes.getFillColor())
                },
                fontMetrics: this.lastTextMetrics
            }));
        }

        // Draw text centered
        try {
            port.drawText(this.text, textPoint, this.getDrawingAttributes(textAttributes, true));
        } catch (error) {
            console.error('[Button.drawText] drawText rejected the logged arguments:', error);
            throw error;
        }
    }

    /**
     * Set click state
     * @param {boolean} clicked - Whether button is clicked/pressed
     */
    setClickState(clicked: boolean): void {
        this.isButtonPressed = clicked;
    }

    /**
     * Handle mouse down
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doMouseDown(mouseInfo: MouseInfo, id: number, part: number): boolean {
        if (part === this.buttonID && this.isEnabled()) {
            this.mouseIsDown = true;
            this.setClickState(true);
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
        this.mouseIsDown = false;
        if (this.isButtonPressed) {
            this.setClickState(false);
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
    doLeftClick(mouseInfo: MouseInfo, id: number, part: number) {
        if (part === this.buttonID && this.isEnabled()) {
            this.attributes.playClick();
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
    showToolTip(nArea: number, pts: PDG.Point, rToolRect: PDG.Rect): void {
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
    isMouseInToolArea(pts: PDG.Point, rToolRect: PDG.Rect): boolean {
        return rToolRect.contains(pts);
    }

    /**
     * Set tooltip text
     * @param {string} text - Tooltip text
     */
    setToolTipText(text: string): void {
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
    doMouseMove(mouseInfo: MouseInfo, id: number, part: number) {
        this.isHovered = part === this.buttonID;
        if (this.mouseIsDown) this.setClickState(this.isHovered && this.isEnabled());
        if (this.isToolTipEnabled) {
            // Check if we should show tooltip
            const viewArea = this.getViewArea();
            if (this.isMouseInToolArea(mouseInfo.mousePos, viewArea)) {
                this.showToolTip(part, mouseInfo.mousePos, viewArea);
            }
        }
    }

    doMouseEnter(mouseInfo: MouseInfo, id: number, part: number): void {
        this.isHovered = true;
        if (this.mouseIsDown && this.isEnabled()) this.setClickState(true);
    }

    /**
     * Handle mouse leave
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     */
    doMouseLeave(mouseInfo: MouseInfo, id: number, part: number) {
        this.isHovered = false;
        this.setClickState(false);
        // Hide tooltip when mouse leaves
        if (this.isToolTipEnabled) {
            console.log(`Hiding tooltip for button ${this.buttonID}`);
        }
    }

    /**
     * Get button ID
     * @returns {number} Button ID
     */
    getButtonID(): number {
        return this.buttonID;
    }

    /**
     * Get button text
     * @returns {string} Button text
     */
    getText(): string {
        return this.text;
    }

    /**
     * Check if button is pressed
     * @returns {boolean} true if pressed
     */
    isPressed(): boolean {
        return this.isButtonPressed;
    }

    /**
     * Set button text size
     * @param {number} size - Text size
     */
    setTextSize(size: number): void {
        this.buttonTextSize = size;
    }

    /**
     * Cleanup when button is destroyed
     */
    destroy() {
        super.destroy();
        // Clean up images
        for (let i = 0; i < MAX_BUTTON_IMAGES; i++) {
            if (this.buttonImage[i]) {
                this.buttonImage[i] = null;
                this.buttonImage[i] = null;
            }
        }

        // Clean up sound
        this.attributes = new ControlAttributes();

        // Clean up tooltip
        this.toolTipCtrl = null;
    }
}

export {
Button,
MAX_BUTTON_IMAGES,
RES_DEFAULT_BUTTON_IMAGE_NAMES
};
