import { Button } from './Button';
import type PDG = require('../../../types');
import type { Controller } from "./Controller";
import type { MouseInfo } from './engine';
import { engine } from './engine';

// -----------------------------------------------
// MessageDialog.ts
//
// TypeScript implementation of the MessageDialog class
// A simple dialog that shows a text message with buttons
//
// Adapted from the PDG C++ and JavaScript MVC implementations
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

import { Dialog,DialogFlags } from "./Dialog";
import { View } from "./View";

/**
 * MessageDialog view IDs
 */
const MessageDialogViewIDs = {
    VIEW_ID_MESSAGE_VIEW: 1,
    VIEW_ID_BORDER: 2,
    VIEW_FIRST_BUTTON_ID: 100, // Add new buttons below this entry
    VIEW_ID_BUTTON_1: 101,
    VIEW_ID_BUTTON_2: 102,
    VIEW_LAST_BUTTON_ID: 199    // Add new buttons above this entry
};

/**
 * MessageDialog button text types
 */
const MessageDialogButtonText = {
    NONE: 0,
    OK: 1,
    CANCEL: 2,
    YES: 3,
    NO: 4,
    SAVE: 5,
    LOAD: 6
};

/**
 * MessageDialog that extends Dialog
 * Provides a simple dialog for displaying messages with buttons
 */
class MessageDialog extends Dialog {
    resMgr: PDG.ResourceManager;
    buttonClickedId: number;
    messageCode: number;
    resolvePromise: ((value: number | PromiseLike<number>) => void) | null = null;

    constructor(parentController: Controller, message: string, button1: number = MessageDialogButtonText.NONE, button2: number = MessageDialogButtonText.NONE) {
        // Convert button types to strings
        const buttonText1 = MessageDialog.getTextForButton(button1);
        const buttonText2 = MessageDialog.getTextForButton(button2);

        // Call parent constructor with string buttons
        super(parentController, 300, 150, DialogFlags.dialog_Standard,
              MessageDialogViewIDs.VIEW_ID_BUTTON_1,
              button2 !== MessageDialogButtonText.NONE ? MessageDialogViewIDs.VIEW_ID_BUTTON_2 : -1);

        this.resMgr = parentController.getApplication().getResourceManager();
        this.buttonClickedId = -1;
        this.messageCode = 0;

        this.setupDialog(message, buttonText1, buttonText2);
    }

    /**
     * Alternative constructor with custom button text
     * @param {Controller} parentController - Parent controller
     * @param {string} message - Message text
     * @param {string} buttonText1 - First button text
     * @param {string} buttonText2 - Second button text
     */
    static withCustomButtons(parentController: Controller, message: string, buttonText1: string, buttonText2: string): MessageDialog {
        const dialog = new MessageDialog(parentController, message, MessageDialogButtonText.NONE, MessageDialogButtonText.NONE);
        dialog.setupDialog(message, buttonText1, buttonText2);
        return dialog;
    }

    /**
     * Setup dialog with message and buttons
     * @param {string} message - Message text
     * @param {string} buttonText1 - First button text
     * @param {string} buttonText2 - Second button text
     */
    setupDialog(message: string, buttonText1: string, buttonText2: string): void {
        for (const id of [MessageDialogViewIDs.VIEW_ID_MESSAGE_VIEW, MessageDialogViewIDs.VIEW_ID_BUTTON_1,
            MessageDialogViewIDs.VIEW_ID_BUTTON_2, MessageDialogViewIDs.VIEW_ID_BORDER]) this.removeViewById(id);
        const dialogRect = this.getDialogRect();

        // Create message view
        const messageRect = new engine.Rect(
            dialogRect.left + 20,
            dialogRect.top + 20,
            dialogRect.right - 20,
            dialogRect.top + 80
        );

        const messageView = new MessageDialogView(this, messageRect, message);
        this.addView(messageView, MessageDialogViewIDs.VIEW_ID_MESSAGE_VIEW);

        // Create buttons
        const buttonHeight = 30;
        const buttonWidth = 80;
        const buttonSpacing = 20;
        const buttonY = dialogRect.bottom - 50;

        let buttonX = dialogRect.right - 20 - buttonWidth;

        // Add second button if specified
        if (buttonText2 && buttonText2 !== '') {
            const button2Rect = new engine.Rect(buttonX, buttonY, buttonX + buttonWidth, buttonY + buttonHeight);
            const button2 = new Button(this, button2Rect, MessageDialogViewIDs.VIEW_ID_BUTTON_2);
            button2.setText(buttonText2);
            this.addView(button2, MessageDialogViewIDs.VIEW_ID_BUTTON_2);

            buttonX -= buttonWidth + buttonSpacing;
        }

        // Add first button
        if (buttonText1 && buttonText1 !== '') {
            const button1Rect = new engine.Rect(buttonX, buttonY, buttonX + buttonWidth, buttonY + buttonHeight);
            const button1 = new Button(this, button1Rect, MessageDialogViewIDs.VIEW_ID_BUTTON_1);
            button1.setText(buttonText1);
            this.addView(button1, MessageDialogViewIDs.VIEW_ID_BUTTON_1);
        }

        // Add border view
        const borderRect = new engine.Rect(
            dialogRect.left + 2,
            dialogRect.top + 2,
            dialogRect.right - 2,
            dialogRect.bottom - 2
        );
        const borderView = new MessageDialogBorderView(this, borderRect);
        this.addView(borderView, MessageDialogViewIDs.VIEW_ID_BORDER);
    }

    /**
     * Get text for button type
     * @param {number} buttonType - Button type
     * @returns {string} Button text
     */
    static getTextForButton(buttonType: number): string {
        switch (buttonType) {
            case MessageDialogButtonText.OK:
                return 'OK';
            case MessageDialogButtonText.CANCEL:
                return 'Cancel';
            case MessageDialogButtonText.YES:
                return 'Yes';
            case MessageDialogButtonText.NO:
                return 'No';
            case MessageDialogButtonText.SAVE:
                return 'Save';
            case MessageDialogButtonText.LOAD:
                return 'Load';
            default:
                return '';
        }
    }

    /**
     * Handle left click
     * @param {Object} mouseInfo - Mouse information
     * @param {View} view - The view that was clicked
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     * @returns {boolean} true if handled
     */
    doLeftClick(mouseInfo: MouseInfo, view: View, id: number, part: number) {
        // Handle button clicks
        if (id === MessageDialogViewIDs.VIEW_ID_BUTTON_1) {
            this.buttonClickedId = MessageDialogViewIDs.VIEW_ID_BUTTON_1;
            this.doClose();
            return true;
        } else if (id === MessageDialogViewIDs.VIEW_ID_BUTTON_2) {
            this.buttonClickedId = MessageDialogViewIDs.VIEW_ID_BUTTON_2;
            this.doClose();
            return true;
        }

        return super.doLeftClick(mouseInfo, view, id, part);
    }

    /**
     * Get button clicked ID
     * @returns {number} Button clicked ID
     */
    getButtonClickedId(): number {
        return this.buttonClickedId;
    }

    /**
     * Get message code
     * @returns {number} Message code
     */
    getMessageCode(): number {
        return this.messageCode;
    }

    /**
     * Set message code
     * @param {number} msgCode - Message code
     */
    setMessageCode(msgCode: number): void {
        this.messageCode = msgCode;
    }

    /**
     * Show dialog and wait for result
     * @returns {Promise<number>} Button clicked ID
     */
    showModal(): Promise<number> {
        return new Promise((resolve) => {
            this.resolvePromise = resolve;
            super.showModal();
        });
    }

    /**
     * Handle dialog close
     */
    doClose(cancelled: boolean = this.buttonClickedId !== MessageDialogViewIDs.VIEW_ID_BUTTON_1): void {
        super.doClose(cancelled);
        if (!this.parentController && this.resolvePromise) {
            this.resolvePromise(this.buttonClickedId);
            this.resolvePromise = null;
        }
    }

    /**
     * Create OK dialog
     * @param {Controller} parentController - Parent controller
     * @param {string} message - Message text
     * @returns {MessageDialog} OK dialog
     */
    static createOKDialog(parentController: Controller, message: string): MessageDialog {
        return new MessageDialog(parentController, message, MessageDialogButtonText.OK);
    }

    /**
     * Create Yes/No dialog
     * @param {Controller} parentController - Parent controller
     * @param {string} message - Message text
     * @returns {MessageDialog} Yes/No dialog
     */
    static createYesNoDialog(parentController: Controller, message: string): MessageDialog {
        return new MessageDialog(parentController, message, MessageDialogButtonText.YES, MessageDialogButtonText.NO);
    }

    /**
     * Create OK/Cancel dialog
     * @param {Controller} parentController - Parent controller
     * @param {string} message - Message text
     * @returns {MessageDialog} OK/Cancel dialog
     */
    static createOKCancelDialog(parentController: Controller, message: string): MessageDialog {
        return new MessageDialog(parentController, message, MessageDialogButtonText.OK, MessageDialogButtonText.CANCEL);
    }

    /**
     * Create Save/Cancel dialog
     * @param {Controller} parentController - Parent controller
     * @param {string} message - Message text
     * @returns {MessageDialog} Save/Cancel dialog
     */
    static createSaveCancelDialog(parentController: Controller, message: string): MessageDialog {
        return new MessageDialog(parentController, message, MessageDialogButtonText.SAVE, MessageDialogButtonText.CANCEL);
    }

    /**
     * Show OK dialog
     * @param {Controller} parentController - Parent controller
     * @param {string} message - Message text
     * @returns {Promise<number>} Button clicked ID
     */
    static showOKDialog(parentController: Controller, message: string): Promise<number> {
        const dialog = MessageDialog.createOKDialog(parentController, message);
        return dialog.showModal();
    }

    /**
     * Show Yes/No dialog
     * @param {Controller} parentController - Parent controller
     * @param {string} message - Message text
     * @returns {Promise<number>} Button clicked ID
     */
    static showYesNoDialog(parentController: Controller, message: string): Promise<number> {
        const dialog = MessageDialog.createYesNoDialog(parentController, message);
        return dialog.showModal();
    }

    /**
     * Show OK/Cancel dialog
     * @param {Controller} parentController - Parent controller
     * @param {string} message - Message text
     * @returns {Promise<number>} Button clicked ID
     */
    static showOKCancelDialog(parentController: Controller, message: string): Promise<number> {
        const dialog = MessageDialog.createOKCancelDialog(parentController, message);
        return dialog.showModal();
    }

    /**
     * Show Save/Cancel dialog
     * @param {Controller} parentController - Parent controller
     * @param {string} message - Message text
     * @returns {Promise<number>} Button clicked ID
     */
    static showSaveCancelDialog(parentController: Controller, message: string): Promise<number> {
        const dialog = MessageDialog.createSaveCancelDialog(parentController, message);
        return dialog.showModal();
    }
}

/**
 * MessageView for displaying text in MessageDialog
 */
class MessageDialogView extends View {
    message: string;
    textColor: PDG.Color;

    constructor(controller: Controller, rect: PDG.Rect, message: string) {
        super(controller, rect);
        this.message = message;
        this.textSize(12);
        this.textColor = new engine.Color(0.0, 0.0, 0.0, 1.0);
    }

    /**
     * Draw the message
     */
    drawSelf(port: PDG.Port, frameNum: number): void {
        const viewArea = this.getViewArea();

        // Draw background
        var backgroundAttrs = new engine.Attributes().fillColor(new engine.Color(1.0, 1.0, 1.0, 1.0));
        port.drawRect(viewArea, this.getDrawingAttributes(backgroundAttrs));

        // Draw message text
        const textPoint = new engine.Point(
            viewArea.left + 10,
            viewArea.top + viewArea.height() / 2 + super.getTextSize() / 2
        );
        var textAttrs = new engine.Attributes().textSize(super.getTextSize()).textStyle(engine.textStyle_Centered).fillColor(this.textColor);
        port.drawText(this.message, textPoint, this.getDrawingAttributes(textAttrs, true));
    }

    /**
     * Set message text
     * @param {string} message - New message text
     */
    setMessage(message: string): void {
        this.message = message;
    }

    /**
     * Set text size
     * @param {number} size - Text size
     */
    setTextSize(size: number): void {
        this.textSize(size);
    }

    /**
     * Set text color
     * @param {Object} color - Text color
     */
    setTextColor(color: PDG.Color): void {
        this.textColor = color;
    }
}

/**
 * MessageDialogBorderView for drawing border around MessageDialog
 */
class MessageDialogBorderView extends View {
    borderColor: PDG.Color;
    borderWidth: number;

    constructor(controller: Controller, rect: PDG.Rect) {
        super(controller, rect);
        this.borderColor = new engine.Color(0.3, 0.3, 0.3, 1.0);
        this.borderWidth = 2;
    }

    /**
     * Draw the border
     */
    drawSelf(port: PDG.Port, frameNum: number): void {
        const viewArea = this.getViewArea();

        // Draw border
        var borderAttrs = new engine.Attributes().lineColor(this.borderColor).lineThickness(this.borderWidth);
        port.drawRect(viewArea, this.getDrawingAttributes(borderAttrs));
    }

    /**
     * Set border color
     * @param {Object} color - Border color
     */
    setBorderColor(color: PDG.Color): void {
        this.borderColor = color;
    }

    /**
     * Set border width
     * @param {number} width - Border width
     */
    setBorderWidth(width: number): void {
        this.borderWidth = width;
    }
}

export {
MessageDialog,MessageDialogBorderView,MessageDialogButtonText,MessageDialogView,MessageDialogViewIDs
};
