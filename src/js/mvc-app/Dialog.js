// -----------------------------------------------
// Dialog.js
// 
// JavaScript port of the Dialog UI component
// A modal dialog controller with OK/Cancel buttons
//
// Ported from C++ by Assistant, 2024
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

const { Controller } = require('./Controller');

/**
 * Dialog result constants
 */
const DialogResult = {
    kCancelled: true,
    kAccepted: false
};

/**
 * Dialog flags
 */
const DialogFlags = {
    dialog_Centered: 1 << 0,
    dialog_CreateBackground: 1 << 1,
    dialog_ReservedFlag: 1 << 2,
    dialog_NonModal: 1 << 3,
    dialog_Standard: (1 << 0) | (1 << 1) // dialog_Centered | dialog_CreateBackground
};

/**
 * Dialog UI component that extends Controller
 * A Dialog expects to only have two buttons, ok and cancel, although they can be named however
 * you want. The cancel button is not required, but if it is provided it will have a key 
 * equivalent of <esc>. The <enter> key always acts as an ok button. Both OK and Cancel will call
 * the doClose() method, which will dismiss the dialog.
 */
class Dialog extends Controller {
    constructor(parentController, width, height, flags = DialogFlags.dialog_Standard, 
                okButtonId, cancelButtonId = -1) {
        
        if (!parentController) {
            throw new Error("Parent controller is required");
        }

        // Create with key press events enabled
        super(parentController, null, null, true, true, true, false, true);
        
        this.buttonWithMouseDown = null;
        this.okButtonId = okButtonId;
        this.cancelButtonId = cancelButtonId;
        this.flags = flags;
        this.viewVisibilitySave = null;
        this.parentController = parentController;
        this.dialogRect = new pdg.Rect(0, 0, width, height);
        
        // Calculate dialog position
        this._calculateDialogPosition();
        
        // Create background if requested
        if (flags & DialogFlags.dialog_CreateBackground) {
            this._createBackground();
        }
        
        // Store event handler references for cleanup
        this.keyPressHandler = null;
        
        // Register for key press events - use more JavaScript-idiomatic on*() event method
        this.keyPressHandler = pdg.onKeyPress((eventData) => this.handleEvent('eventType_KeyPress', eventData));
    }

    /**
     * Calculate dialog position based on flags
     * @private
     */
    _calculateDialogPosition() {
        const port = this.port;
        const drawingArea = port.getDrawingArea();
        
        if (this.flags & DialogFlags.dialog_Centered) {
            // Center the dialog on screen
            this.dialogRect.left = drawingArea.left + (drawingArea.width() - this.dialogRect.width()) / 2;
            this.dialogRect.top = drawingArea.top + (drawingArea.height() - this.dialogRect.height()) / 2;
            this.dialogRect.right = this.dialogRect.left + this.dialogRect.width();
            this.dialogRect.bottom = this.dialogRect.top + this.dialogRect.height();
        } else {
            // Standard dialog position (centered horizontally, 2/3 up vertically)
            this.dialogRect.left = drawingArea.left + (drawingArea.width() - this.dialogRect.width()) / 2;
            this.dialogRect.top = drawingArea.top + drawingArea.height() / 3;
            this.dialogRect.right = this.dialogRect.left + this.dialogRect.width();
            this.dialogRect.bottom = this.dialogRect.top + this.dialogRect.height();
        }
    }

    /**
     * Create dialog background view
     * @private
     */
    _createBackground() {
        // In a real implementation, you would create a background view
        // For now, we'll just set up the dialog area
        console.log(`Creating dialog background: ${this.dialogRect.width()}x${this.dialogRect.height()}`);
    }

    /**
     * Handle mouse down event
     * @param {Object} mouseInfo - Mouse information
     * @param {View} view - The view that was clicked
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doMouseDown(mouseInfo, view, id, part) {
        // Check if this is a button click
        if (view && typeof view.setClickState === 'function') {
            // This is likely a button
            view.setClickState(true);
            this.buttonWithMouseDown = view;
            return true;
        }
        
        return false;
    }

    /**
     * Handle mouse up event
     * @param {Object} mouseInfo - Mouse information
     * @param {View} view - The view that was clicked
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doMouseUp(mouseInfo, view, id, part) {
        // Check if this is a button release
        if (this.buttonWithMouseDown) {
            this.buttonWithMouseDown.setClickState(false);
            this.buttonWithMouseDown = null;
            return true;
        }
        
        return false;
    }

    /**
     * Handle left click event
     * @param {Object} mouseInfo - Mouse information
     * @param {View} view - The view that was clicked
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doLeftClick(mouseInfo, view, id, part) {
        // Check if this is the OK button
        if (id === this.okButtonId) {
            this.doClose(DialogResult.kAccepted);
            return true;
        }
        
        // Check if this is the Cancel button
        if (id === this.cancelButtonId) {
            this.doClose(DialogResult.kCancelled);
            return true;
        }
        
        return false;
    }

    /**
     * Handle key press event
     * @param {Object} keyPressInfo - Key press information
     * @param {View} view - The view that has focus
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doKeyPress(keyPressInfo, view, id, part) {
        // Handle Enter key as OK
        if (keyPressInfo.keyCode === 13 || keyPressInfo.key === 'Enter') { // Enter key
            this.doClose(DialogResult.kAccepted);
            return true;
        }
        
        // Handle Escape key as Cancel
        if (keyPressInfo.keyCode === 27 || keyPressInfo.key === 'Escape') { // Escape key
            if (this.cancelButtonId !== -1) {
                this.doClose(DialogResult.kCancelled);
                return true;
            }
        }
        
        return false;
    }

    /**
     * Handle port resize
     * @param {Port} resizedPort - The port that was resized
     */
    portWasResized(resizedPort) {
        // Recalculate dialog position
        this._calculateDialogPosition();
        
        // Call parent implementation
        super.portWasResized(resizedPort);
    }

    /**
     * Close the dialog
     * @param {boolean} cancelled - Whether the dialog was cancelled
     */
    doClose(cancelled) {
        // Notify parent controller that we're trying to close
        if (this.parentController.attemptChildClose(this, cancelled)) {
            // Parent allows us to close
            this._dismissDialog();
        }
        // If parent doesn't allow us to close, we stay open
    }

    /**
     * Dismiss the dialog
     * @private
     */
    _dismissDialog() {
        // Remove from parent controller
        if (this.parentController) {
            this.parentController.removeChild(this);
        }
        
        // Unregister event handlers
        if (this.keyPressHandler) {
            this.app.getEventManager().removeHandler(this.keyPressHandler);
            this.keyPressHandler = null;
        }
        
        // Clean up
        this.destroy();
    }

    /**
     * Show dialog after it was hidden
     */
    showDialog() {
        if (this.viewVisibilitySave) {
            // Restore view visibility
            for (let i = 0; i < this.views.length; i++) {
                const view = this.views[i].first;
                view.visible = this.viewVisibilitySave[i];
                if (view.visible) {
                    view.show();
                }
            }
            this.viewVisibilitySave = null;
        }
        
        this.setActive(true);
        this.redrawAll();
    }

    /**
     * Hide dialog from view but don't close it
     */
    hideDialog() {
        if (!this.viewVisibilitySave) {
            // Save current view visibility
            this.viewVisibilitySave = new Array(this.views.length);
            for (let i = 0; i < this.views.length; i++) {
                const view = this.views[i].first;
                this.viewVisibilitySave[i] = view.visible;
                view.hide();
            }
        }
        
        this.setActive(false);
    }

    /**
     * Check if dialog is visible
     * @returns {boolean} true if visible
     */
    isVisible() {
        return this.viewVisibilitySave === null;
    }

    /**
     * Set dialog position and size
     * @param {Rect} dialogRect - New dialog rectangle
     */
    setDialogRect(dialogRect) {
        this.dialogRect = new pdg.Rect(dialogRect);
        this._calculateDialogPosition();
    }

    /**
     * Get dialog position and size
     * @returns {Rect} Dialog rectangle
     */
    getDialogRect() {
        return this.dialogRect;
    }

    /**
     * Get OK button ID
     * @returns {number} OK button ID
     */
    getOkButtonId() {
        return this.okButtonId;
    }

    /**
     * Get Cancel button ID
     * @returns {number} Cancel button ID
     */
    getCancelButtonId() {
        return this.cancelButtonId;
    }

    /**
     * Get dialog flags
     * @returns {number} Dialog flags
     */
    getFlags() {
        return this.flags;
    }

    /**
     * Check if dialog is modal
     * @returns {boolean} true if modal
     */
    isModal() {
        return !(this.flags & DialogFlags.dialog_NonModal);
    }

    /**
     * Check if dialog is centered
     * @returns {boolean} true if centered
     */
    isCentered() {
        return !!(this.flags & DialogFlags.dialog_Centered);
    }

    /**
     * Handle child activation
     * @param {Controller} child - The child controller that was activated
     */
    childActivated(child) {
        // Dialog doesn't typically have children, but handle it if needed
        super.childActivated(child);
    }

    /**
     * Cleanup when dialog is destroyed
     */
    destroy() {
        // Clean up button reference
        this.buttonWithMouseDown = null;
        
        // Clean up visibility save array
        this.viewVisibilitySave = null;
        
        // Unregister event handlers
        if (this.keyPressHandler) {
            pdg.evt.removeHandler(this.keyPressHandler);
            this.keyPressHandler = null;
        }
        
        // Call parent cleanup
        super.destroy();
    }
}

module.exports = {
    Dialog,
    DialogResult,
    DialogFlags
};
