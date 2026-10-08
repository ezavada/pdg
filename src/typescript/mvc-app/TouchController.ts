import type PDG = require('../../../types');
import type { Controller } from "./Controller";
import type { EventHandler,MouseInfo,UIEvent } from './engine';
import { engine } from './engine';
import type { View } from "./View";

// -----------------------------------------------
// TouchController.ts
//
// TypeScript implementation of the TouchController class
// A controller that handles touch gestures and flicking
//
// Adapted from the PDG C++ and JavaScript MVC implementations
// Original Copyright (c) 2010, Dream Rock Studios, LLC
// -----------------------------------------------

import { ModalController } from "./ModalController";

// Flick decay configuration
const FLICK_DECAY_FACTOR = 3.0;
const FLICK_MAX_MOUSE_UNMOVED_MS = 200;
const FLICK_FRAME_RATE = 16;

/**
 * TouchController that extends ModalController
 * Provides touch gesture recognition including tap, flick, swipe, and pinch
 */
class TouchController extends ModalController {
    mouseDown: boolean;
    lastMousePositionRecorded: boolean;
    lastMousePosition: PDG.Point;
    mouseDownInfo: MouseInfo | null;
    flickVelocity: {
        x: number;
        y: number;
    };
    flickView: View | null;
    snapbackView: View | null;
    flickPart: number;
    flickID: number;
    snapbackID: number;
    snapbackPart: number;
    lastMovedMs: number;
    lastSnapbackMs: number;
    lastMouseUpMs: number;
    touchStartPoint: PDG.Point;
    touchStartTime: number;
    touchMovePoints: PDG.Point[];
    multiTouchPoints: PDG.Point[];
    gestureRecognized: boolean;
    eventHandlers: EventHandler[];

    constructor(parentController: Controller, wantKeyUpDown: boolean = true, wantKeyPress: boolean = true,
                wantMouseEnterLeave: boolean = true, wantAll: boolean = false) {

        super(parentController, wantKeyUpDown, wantKeyPress, wantMouseEnterLeave, wantAll);

        // Touch state
        this.mouseDown = false;
        this.lastMousePositionRecorded = false;
        this.lastMousePosition = new engine.Point(0, 0);
        this.mouseDownInfo = null;

        // Flick state
        this.flickVelocity = { x: 0.0, y: 0.0 };
        this.flickView = null;
        this.snapbackView = null;
        this.flickPart = -1;
        this.flickID = -1;
        this.snapbackID = -1;
        this.snapbackPart = -1;
        this.lastMovedMs = 0;
        this.lastSnapbackMs = 0;
        this.lastMouseUpMs = 0;

        // Touch tracking
        this.touchStartPoint = new engine.Point(0, 0);
        this.touchStartTime = 0;
        this.touchMovePoints = [];
        this.multiTouchPoints = [];
        this.gestureRecognized = false;

        // Store event handler references for cleanup
        this.eventHandlers = [];

        // Register for timer events for flick animation - use more JavaScript-idiomatic on*() event method
        this.eventHandlers.push(engine.onTimer((eventData) => this.handleEvent('eventType_Timer', eventData)));
    }

    /**
     * Handle mouse down with touch behavior
     * @param {Object} mouseInfo - Mouse information
     * @param {View} view - The view that was clicked
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doMouseDown(mouseInfo: MouseInfo, view: View, id: number, part: number) {
        this.mouseDown = true;
        this.lastMousePositionRecorded = true;
        this.lastMousePosition = new engine.Point(mouseInfo.mousePos.x, mouseInfo.mousePos.y);
        this.mouseDownInfo = { ...mouseInfo };

        // Record touch start
        this.touchStartPoint = new engine.Point(mouseInfo.mousePos.x, mouseInfo.mousePos.y);
        this.touchStartTime = Date.now();
        this.touchMovePoints = [new engine.Point(mouseInfo.mousePos.x, mouseInfo.mousePos.y)];
        this.gestureRecognized = false;

        // Stop any existing flick
        this.stopFlick();

        // Call parent implementation
        return super.doMouseDown(mouseInfo, view, id, part);
    }

    /**
     * Handle mouse up with touch behavior
     * @param {Object} mouseInfo - Mouse information
     * @param {View} view - The view that was clicked
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doMouseUp(mouseInfo: MouseInfo, view: View, id: number, part: number) {
        this.mouseDown = false;
        this.lastMouseUpMs = Date.now();

        // Determine if this was a tap or the start of a flick
        if (this.touchMovePoints.length > 0) {
            const touchDuration = Date.now() - this.touchStartTime;
            const distance = this.calculateDistance(this.touchStartPoint, mouseInfo.mousePos);

            if (part !== -1 && touchDuration < FLICK_MAX_MOUSE_UNMOVED_MS && distance < 10) {
                // This was a tap
                this.handleTap(mouseInfo, view, id, part);
            } else if (distance > 5) {
                // This might be a flick - calculate velocity
                this.calculateFlickVelocity();
                if (this.isFlickGesture()) {
                    this.startFlick(mouseInfo, view, id, part);
                }
            }
        }

        // Call parent implementation
        const handled = super.doMouseUp(mouseInfo, view, id, part);

        // Reset touch state
        this.touchMovePoints = [];
        this.gestureRecognized = false;

        return handled;
    }

    /**
     * Handle mouse move with touch behavior
     * @param {Object} mouseInfo - Mouse information
     * @param {View} view - The view that was moved over
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     */
    doMouseMove(mouseInfo: MouseInfo, view: View, id: number, part: number) {
        if (this.mouseDown && this.lastMousePositionRecorded) {
            // Calculate movement delta
            const delta = new engine.Point(
                mouseInfo.mousePos.x - this.lastMousePosition.x,
                mouseInfo.mousePos.y - this.lastMousePosition.y
            );

            // Record touch move
            this.touchMovePoints.push(new engine.Point(mouseInfo.mousePos.x, mouseInfo.mousePos.y));
            this.lastMovedMs = Date.now();

            // Handle touch move gesture
            if (delta.x !== 0 || delta.y !== 0) {
                this.handleTouchMove(delta, view, id, part);
            }

            // Update last position
            this.lastMousePosition = new engine.Point(mouseInfo.mousePos.x, mouseInfo.mousePos.y);
        }

        // Call parent implementation
        super.doMouseMove(mouseInfo, view, id, part);
    }

    /**
     * Handle touch gesture
     * @param {Object} mouseInfo - Mouse information
     * @param {View} view - The view that was touched
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doTouch(mouseInfo: MouseInfo, view: View, id: number, part: number): boolean {
        // This is called for general touch events
        // Override in subclasses for specific touch handling
        return false;
    }

    /**
     * Handle tap gesture
     * @param {Object} mouseInfo - Mouse information
     * @param {View} view - The view that was tapped
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doTap(mouseInfo: MouseInfo, view: View, id: number, part: number): boolean {
        // Override in subclasses for tap handling
        return false;
    }

    /**
     * Handle touch move gesture
     * @param {Point} delta - Movement delta
     * @param {boolean} flick - Whether this is a flick gesture
     * @param {View} view - The view being touched
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doTouchMove(delta: PDG.Point, flick: boolean, view: View, id: number, part: number): boolean {
        // Override in subclasses for touch move handling
        return false;
    }

    /**
     * Handle swipe gesture
     * @param {Point} delta - Movement delta
     * @param {View} view - The view being swiped
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doSwipeMove(delta: PDG.Point, view: View, id: number, part: number): boolean {
        // Override in subclasses for swipe handling
        return false;
    }

    /**
     * Handle pinch gesture
     * @param {Point} delta1 - First finger delta
     * @param {Point} delta2 - Second finger delta
     * @param {number} distance - Distance between fingers
     * @param {number} deltaDistance - Change in distance
     * @param {View} view - The view being pinched
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doPinchMove(delta1: PDG.Point, delta2: PDG.Point, distance: number, deltaDistance: number, view: View, id: number, part: number): boolean {
        // Override in subclasses for pinch handling
        return false;
    }

    /**
     * Handle snapback
     * @param {number} msSinceLastSnapback - Milliseconds since last snapback
     * @param {number} msSinceMouseUp - Milliseconds since mouse up
     * @param {View} view - The view snapping back
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doSnapback(msSinceLastSnapback: number, msSinceMouseUp: number, view: View, id: number, part: number): boolean {
        // Override in subclasses for snapback handling
        return false;
    }

    /**
     * Handle tap gesture
     * @param {Object} mouseInfo - Mouse information
     * @param {View} view - The view that was tapped
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     */
    handleTap(mouseInfo: MouseInfo, view: View, id: number, part: number): void {
        if (view && typeof view.doTap === 'function') {
            view.doTap(mouseInfo, id, part);
        } else {
            this.doTap(mouseInfo, view, id, part);
        }
    }

    /**
     * Handle touch move
     * @param {Point} delta - Movement delta
     * @param {View} view - The view being touched
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     */
    handleTouchMove(delta: PDG.Point, view: View, id: number, part: number): void {
        if (view && typeof view.doTouchMove === 'function') {
            view.doTouchMove(delta, false, id, part);
        } else {
            this.doTouchMove(delta, false, view, id, part);
        }
    }

    /**
     * Calculate distance between two points
     * @param {Point} p1 - First point
     * @param {Point} p2 - Second point
     * @returns {number} Distance
     */
    calculateDistance(p1: PDG.Point, p2: PDG.Point): number {
        const dx = p2.x - p1.x;
        const dy = p2.y - p1.y;
        return Math.sqrt(dx * dx + dy * dy);
    }

    /**
     * Calculate flick velocity from touch points
     */
    calculateFlickVelocity(): void {
        if (this.touchMovePoints.length < 2) {
            this.flickVelocity = { x: 0.0, y: 0.0 };
            return;
        }

        const lastPoint = this.touchMovePoints[this.touchMovePoints.length - 1];
        const prevPoint = this.touchMovePoints[this.touchMovePoints.length - 2];

        const dx = lastPoint.x - prevPoint.x;
        const dy = lastPoint.y - prevPoint.y;
        const dt = 1.0 / FLICK_FRAME_RATE; // Assume frame rate timing

        this.flickVelocity = {
            x: dx / dt,
            y: dy / dt
        };
    }

    /**
     * Check if gesture is a flick
     * @returns {boolean} true if flick
     */
    isFlickGesture(): boolean {
        const velocity = Math.sqrt(this.flickVelocity.x * this.flickVelocity.x +
                                  this.flickVelocity.y * this.flickVelocity.y);
        return velocity > 100; // Minimum velocity threshold
    }

    /**
     * Start flick animation
     * @param {Object} mouseInfo - Mouse information
     * @param {View} view - The view flicking
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     */
    startFlick(mouseInfo: MouseInfo, view: View, id: number, part: number): void {
        this.flickView = view;
        this.flickPart = part;
        this.flickID = id;

        // Start flick timer
        this.app.getTimerManager().startTimer(0x504402, FLICK_FRAME_RATE, true); // oneShot = true

        console.log('TouchController: Started flick animation');
    }

    /**
     * Stop flick animation
     */
    stopFlick(): void {
        this.app.getTimerManager().cancelTimer(0x504402);
        this.flickView = null;
        this.flickPart = -1;
        this.flickID = -1;
        this.flickVelocity = { x: 0.0, y: 0.0 };
    }

    /**
     * Update flick animation
     */
    updateFlick(): void {
        if (!this.flickView || this.flickVelocity.x === 0 && this.flickVelocity.y === 0) {
            this.stopFlick();
            return;
        }

        // Apply flick to view
        const delta = new engine.Point(this.flickVelocity.x * FLICK_FRAME_RATE / 1000.0,
                               this.flickVelocity.y * FLICK_FRAME_RATE / 1000.0);

        if (this.flickView.doTouchMove) {
            this.flickView.doTouchMove(delta, true, this.flickID, this.flickPart);
        } else {
            this.doTouchMove(delta, true, this.flickView, this.flickID, this.flickPart);
        }

        // Apply decay to velocity
        this.flickVelocity.x *= (1.0 - FLICK_DECAY_FACTOR * FLICK_FRAME_RATE / 1000.0);
        this.flickVelocity.y *= (1.0 - FLICK_DECAY_FACTOR * FLICK_FRAME_RATE / 1000.0);

        // Stop if velocity is too low
        const velocity = Math.sqrt(this.flickVelocity.x * this.flickVelocity.x +
                                  this.flickVelocity.y * this.flickVelocity.y);
        if (velocity < 1.0) {
            this.stopFlick();
        }
    }

    /**
     * Handle events
     * @param {string} eventType - Event type
     * @param {*} eventData - Event data
     * @returns {boolean} true if handled
     */
    handleEvent(eventType: string | number, eventData: UIEvent) {
        if ((eventType === 'eventType_Timer' || eventType === engine.eventType_Timer) && 'id' in eventData) {
            if (eventData.id === 0x504402) {
                this.updateFlick();
                return true;
            }
        }

        return super.handleEvent(eventType, eventData);
    }

    /**
     * Remove view with touch cleanup
     * @param {View} view - View to remove
     */
    removeView(view: View) {
        // If this view is being flicked, stop the flick
        if (this.flickView === view) {
            this.stopFlick();
        }

        // Call parent implementation
        super.removeView(view);
    }

    /**
     * Get flick velocity
     * @returns {Object} Flick velocity {x, y}
     */
    getFlickVelocity() {
        return { ...this.flickVelocity };
    }

    /**
     * Set flick velocity
     * @param {number} x - X velocity
     * @param {number} y - Y velocity
     */
    setFlickVelocity(x: number, y: number): void {
        this.flickVelocity = { x, y };
    }

    /**
     * Get touch start point
     * @returns {Point} Touch start point
     */
    getTouchStartPoint(): PDG.Point {
        return new engine.Point(this.touchStartPoint.x, this.touchStartPoint.y);
    }

    /**
     * Get touch move points
     * @returns {Point[]} Array of touch move points
     */
    getTouchMovePoints(): PDG.Point[] {
        return this.touchMovePoints.map(p => new engine.Point(p.x, p.y));
    }

    /**
     * Check if touch is active
     * @returns {boolean} true if touch is active
     */
    isTouchActive(): boolean {
        return this.mouseDown;
    }

    /**
     * Get touch duration
     * @returns {number} Touch duration in milliseconds
     */
    getTouchDuration(): number {
        return Date.now() - this.touchStartTime;
    }

    /**
     * Cleanup when touch controller is destroyed
     */
    destroy() {
        // Stop flick animation
        this.stopFlick();

        // Unregister timer events
        for (const handler of this.eventHandlers) {
            if (typeof handler.cancel === 'function') handler.cancel();
            else this.app.getEventManager().removeHandler(handler, engine.eventType_Timer);
        }
        this.eventHandlers = [];

        // Call parent cleanup
        super.destroy();
    }
}

export {
FLICK_DECAY_FACTOR,FLICK_FRAME_RATE,FLICK_MAX_MOUSE_UNMOVED_MS,TouchController
};
