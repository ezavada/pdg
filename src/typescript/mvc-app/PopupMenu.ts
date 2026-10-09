import type PDG = require('../../../types');
import type { Controller } from "./Controller";
import type { MouseInfo } from './engine';
import { engine } from './engine';

// -----------------------------------------------
// PopupMenu.ts
//
// TypeScript implementation of the PopupMenu UI component
// A popup menu with scrolling and selection functionality
//
// Adapted from the PDG C++ and JavaScript MVC implementations
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

import { View } from "./View";

// Constants
const ITEM_SIZE_OFFSET = 8;
const TEXT_WIDTH_OFFSET = 10;
const IMAGE_HEIGHT_OFFSET = 4;
const VIEW_HEIGHT_OFFSET = 20;
const VIEW_WIDTH_OFFSET = 12;
const VIEW_HSHIFT_OFFSET = 3;
const MAX_ARROW_IMAGES = 2;
const TEXT_LEFT_MARGIN = 2;
const HIGHLIGHT_AREA_MARGIN = 2;
const CLIP_TEXT = '...';
const RES_MENU_IMAGES = 143;
const TEXT_RESOURCE_ID_NONE = -1;
const MAX_MENU_WIDTH = 200;
const ITEM_UP_ARROW = 1;
const ITEM_DOWN_ARROW = 2;
const RES_PULL_ARROW = 4;
const START_INDEX_NONE = -1;
const HOT_ITEM_NONE = -1;

/**
 * PopupMenu item information
 */
class ItemInfo {
    itemString: string;
    resourceID: number;
    itemID: number;
    style: number;

    constructor(itemID: number, text: string, resourceID: number = -1, textStyle: number = engine.textStyle_Plain | engine.textStyle_LeftJustified) {
        this.itemString = text;
        this.resourceID = resourceID;
        this.itemID = itemID;
        this.style = textStyle;
    }

    equals(item2: ItemInfo | string | number): boolean {
        if (item2 instanceof ItemInfo) {
            return this.itemString === item2.itemString &&
                   this.resourceID === item2.resourceID &&
                   this.itemID === item2.itemID;
        } else if (typeof item2 === 'string') {
            return this.itemString === item2;
        } else if (typeof item2 === 'number') {
            return this.itemID === item2;
        }
        return false;
    }
}

/**
 * PopupMenu UI component that extends View
 * Provides popup menu functionality with scrolling and selection
 */
class PopupMenu extends View {
    resMgr: PDG.ResourceManager;
    drawableItemList: {rect:PDG.Rect;item:ItemInfo}[];
    startIndex: number;
    longestText: string;
    itemList: ItemInfo[];
    bkColor: PDG.Color;
    textColor: PDG.Color;
    highlightColor: PDG.Color;
    hotItem: number;
    itemShowable: number;
    needScrolling: boolean;
    showUpArrow: boolean;
    showDownArrow: boolean;
    oldScrollPos: PDG.Point;
    pullArrowImage: PDG.Image | null;
    baseRect: PDG.Rect;

    constructor(controller: Controller, topLeft: PDG.Point | PDG.Rect, bkColor: PDG.Color = new engine.Color(0.8, 0.8, 0.8, 1.0),
                textColor: PDG.Color = new engine.Color(0.0, 0.0, 0.0, 1.0),
                highlightColor: PDG.Color = new engine.Color(0.0, 0.0, 1.0, 1.0),
                textSize: number = 14) {

        let rect;
        if (topLeft instanceof engine.Point) {
            // Calculate default size based on text size
            const defaultWidth = 150;
            const defaultHeight = 200;
            rect = new engine.Rect(topLeft.x, topLeft.y, topLeft.x + defaultWidth, topLeft.y + defaultHeight);
        } else if (topLeft instanceof engine.Rect) {
            rect = topLeft;
        } else {
            throw new Error('PopupMenu constructor requires Point or Rect for topLeft');
        }

        super(controller, rect);

        this.resMgr = controller.getApplication().getResourceManager();
        this.drawableItemList = []; // Array of { rect: PDG.Rect, item: ItemInfo }
        this.startIndex = START_INDEX_NONE;
        this.longestText = '';
        this.itemList = [];
        this.bkColor = bkColor;
        this.textColor = textColor;
        this.highlightColor = highlightColor;
        this.hotItem = HOT_ITEM_NONE;
        this.textSize(textSize);
        this.itemShowable = 0;
        this.needScrolling = false;
        this.showUpArrow = false;
        this.showDownArrow = false;
        this.oldScrollPos = new engine.Point(0, 0);
        this.pullArrowImage = null;
        this.minWidth = 50;
        this.baseRect = new engine.Rect(rect);

        this.loadImages();
        this.calcClickableAreas();
    }

    /**
     * Load popup menu images
     */
    loadImages(): void {
        try {
            // In a real implementation, you would load images from resources
            // For now, we'll create placeholder images
            this.pullArrowImage = null; // Placeholder
        } catch (error) {
            console.warn('Failed to load popup menu images:', error);
        }
    }

    /**
     * Calculate clickable areas
     */
    calcClickableAreas(): void {
        const viewArea = this.getViewArea();

        // Clear existing clickable areas
        this.clickableParts = [];

        // Add clickable areas for each drawable item
        for (let i = 0; i < this.drawableItemList.length; i++) {
            const itemPair = this.drawableItemList[i];
            this.addClickablePart(itemPair.rect, itemPair.item.itemID);
        }
    }

    /**
     * Add menu item by resource ID
     * @param {number} itemID - Item ID
     * @param {number} resourceID - Resource ID
     * @param {string} textStyle - Text style
     * @param {number} index - Insert index (-1 for append)
     * @returns {number} Actual insert index
     */
    addMenuItemFromResource(itemID: number, resourceID: number, textStyle: number = engine.textStyle_Plain | engine.textStyle_LeftJustified, index: number = -1): number {
        try {
            const text = this.resMgr.getString(resourceID);
            return this.addMenuItem(itemID, text, textStyle, index);
        } catch (error) {
            console.warn(`Failed to load string from resource ${resourceID}:`, error);
            return -1;
        }
    }

    /**
     * Add menu item by text
     * @param {number} itemID - Item ID
     * @param {string} text - Item text
     * @param {string} textStyle - Text style
     * @param {number} index - Insert index (-1 for append)
     * @returns {number} Actual insert index
     */
    addMenuItem(itemID: number, text: string, textStyle: number = engine.textStyle_Plain | engine.textStyle_LeftJustified, index: number = -1): number {
        const item = new ItemInfo(itemID, text, -1, textStyle);

        if (index === -1 || index >= this.itemList.length) {
            this.itemList.push(item);
            index = this.itemList.length - 1;
        } else {
            this.itemList.splice(index, 0, item);
        }

        this.setLongestText();
        this.sanitiseViewArea();
        this.calcClickableAreas();

        return index;
    }

    /**
     * Delete menu item by item ID
     * @param {number} itemID - Item ID to delete
     * @returns {boolean} true if deleted
     */
    deleteMenuItemByItemID(itemID: number): boolean {
        const index = this.itemList.findIndex(item => item.itemID === itemID);
        if (index !== -1) {
            this.itemList.splice(index, 1);
            this.setLongestText();
            this.sanitiseViewArea();
            this.calcClickableAreas();
            return true;
        }
        return false;
    }

    /**
     * Delete menu item by index
     * @param {number} index - Index to delete
     * @returns {boolean} true if deleted
     */
    deleteMenuItemByIndex(index: number): boolean {
        if (index >= 0 && index < this.itemList.length) {
            this.itemList.splice(index, 1);
            this.setLongestText();
            this.sanitiseViewArea();
            this.calcClickableAreas();
            return true;
        }
        return false;
    }

    /**
     * Delete all menu items
     */
    deleteAllMenuItems(): void {
        this.itemList = [];
        this.drawableItemList = [];
        this.longestText = '';
        this.hotItem = HOT_ITEM_NONE;
        this.calcClickableAreas();
    }

    /**
     * Get item string by item ID
     * @param {number} itemID - Item ID
     * @returns {string} Item string
     */
    getItemStringByItemID(itemID: number): string {
        const item = this.itemList.find(item => item.itemID === itemID);
        return item ? item.itemString : '';
    }

    /**
     * Get item string by index
     * @param {number} index - Item index
     * @returns {string} Item string
     */
    getItemStringByIndex(index: number): string {
        if (index >= 0 && index < this.itemList.length) {
            return this.itemList[index].itemString;
        }
        return '';
    }

    /**
     * Set string by index
     * @param {number} index - Item index
     * @param {string} text - New text
     * @returns {boolean} true if set
     */
    setStringByIndex(index: number, text: string): boolean {
        if (index >= 0 && index < this.itemList.length) {
            this.itemList[index].itemString = text;
            this.setLongestText();
            this.sanitiseViewArea();
            this.calcClickableAreas();
            return true;
        }
        return false;
    }

    /**
     * Set string by item ID
     * @param {number} itemID - Item ID
     * @param {string} text - New text
     * @returns {boolean} true if set
     */
    setStringByItemID(itemID: number, text: string): boolean {
        const item = this.itemList.find(item => item.itemID === itemID);
        if (item) {
            item.itemString = text;
            this.setLongestText();
            this.sanitiseViewArea();
            this.calcClickableAreas();
            return true;
        }
        return false;
    }

    /**
     * Get index by item ID
     * @param {number} itemID - Item ID
     * @returns {number} Item index or -1 if not found
     */
    getIndex(itemID: number): number {
        return this.itemList.findIndex(item => item.itemID === itemID);
    }

    /**
     * Get index by text
     * @param {string} text - Item text
     * @returns {number} Item index or -1 if not found
     */
    getIndexByText(text: string): number {
        return this.itemList.findIndex(item => item.itemString === text);
    }

    /**
     * Draw the popup menu
     */
    drawSelf(port: PDG.Port, frameNum: number): void {
        const viewArea = this.getViewArea();

        // Draw background
        var backgroundAttrs = new engine.Attributes().fillColor(this.bkColor);
        port.drawRect(viewArea, this.getDrawingAttributes(backgroundAttrs));

        // Draw border
        var borderAttrs = new engine.Attributes().lineColor(new engine.Color(0.5, 0.5, 0.5, 1.0)).lineThickness(1);
        port.drawRect(viewArea, this.getDrawingAttributes(borderAttrs));

        // Draw menu items
        this.drawMenuItems();

        // Draw scroll arrows if needed
        if (this.needScrolling) {
            this.drawScrollArrows();
        }
    }

    /**
     * Draw menu items
     */
    drawMenuItems(): void {
        const port = this.getPort();

        for (let i = 0; i < this.drawableItemList.length; i++) {
            const itemPair = this.drawableItemList[i];
            const rect = itemPair.rect;
            const item = itemPair.item;

            // Draw item background
            if (item.itemID === this.hotItem) {
                var highlightAttrs = new engine.Attributes().fillColor(this.highlightColor);
                port.drawRect(rect, this.getDrawingAttributes(highlightAttrs));
            } else {
                var defaultAttrs = new engine.Attributes().fillColor(new engine.Color(1.0, 1.0, 1.0, 1.0));
                port.drawRect(rect, this.getDrawingAttributes(defaultAttrs));
            }

            // Draw item text
            const textPoint = new engine.Point(
                rect.left + TEXT_LEFT_MARGIN,
                rect.top + rect.height() / 2 + super.getTextSize() / 2
            );

            port.drawText(item.itemString, textPoint, this.getDrawingAttributes(new engine.Attributes().textSize(super.getTextSize()).textStyle(item.style).fillColor(this.textColor), true));

            // Draw item separator
            if (i < this.drawableItemList.length - 1) {
                const separatorY = rect.bottom - 1;
                port.drawLine(new engine.Point(rect.left, separatorY), new engine.Point(rect.right, separatorY), this.getDrawingAttributes(new engine.Attributes().lineColor(new engine.Color(0.8, 0.8, 0.8, 1.0)).lineThickness(1), true));
            }
        }
    }

    /**
     * Draw scroll arrows
     */
    drawScrollArrows(): void {
        const port = this.getPort();
        const viewArea = this.getViewArea();
        const arrowSize = 16;

        // Draw up arrow
        if (this.showUpArrow) {
            const upArrowRect = new engine.Rect(
                viewArea.right - arrowSize,
                viewArea.top,
                arrowSize,
                arrowSize
            );
            this.drawArrow(upArrowRect, true);
        }

        // Draw down arrow
        if (this.showDownArrow) {
            const downArrowRect = new engine.Rect(
                viewArea.right - arrowSize,
                viewArea.bottom - arrowSize,
                arrowSize,
                arrowSize
            );
            this.drawArrow(downArrowRect, false);
        }
    }

    /**
     * Draw arrow
     * @param {Rect} rect - Arrow rectangle
     * @param {boolean} up - Whether it's an up arrow
     */
    drawArrow(rect: PDG.Rect, up: boolean): void {
        const port = this.getPort();

        // Draw arrow background
        var arrowBgAttrs = new engine.Attributes().fillColor(new engine.Color(0.9, 0.9, 0.9, 1.0));
        port.drawRect(rect, this.getDrawingAttributes(arrowBgAttrs));
        var arrowBorderAttrs = new engine.Attributes().lineColor(new engine.Color(0.5, 0.5, 0.5, 1.0)).lineThickness(1);
        port.drawRect(rect, this.getDrawingAttributes(arrowBorderAttrs));

        // Draw arrow shape
        const centerX = rect.left + rect.width() / 2;
        const centerY = rect.top + rect.height() / 2;
        const size = 4;

        const arrowColor = new engine.Color(0.2, 0.2, 0.2, 1.0);

        if (up) {
            // Draw up arrow
            port.drawLine(new engine.Point(centerX, centerY - size), new engine.Point(centerX - size, centerY), this.getDrawingAttributes(new engine.Attributes().lineColor(arrowColor).lineThickness(2), true));
            port.drawLine(new engine.Point(centerX, centerY - size), new engine.Point(centerX + size, centerY), this.getDrawingAttributes(new engine.Attributes().lineColor(arrowColor).lineThickness(2), true));
        } else {
            // Draw down arrow
            port.drawLine(new engine.Point(centerX, centerY + size), new engine.Point(centerX - size, centerY), this.getDrawingAttributes(new engine.Attributes().lineColor(arrowColor).lineThickness(2), true));
            port.drawLine(new engine.Point(centerX, centerY + size), new engine.Point(centerX + size, centerY), this.getDrawingAttributes(new engine.Attributes().lineColor(arrowColor).lineThickness(2), true));
        }
    }

    /**
     * Show the popup menu
     */
    showSelf() {
        this.show();
    }

    /**
     * Handle mouse move
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     */
    doMouseMove(mouseInfo: MouseInfo, id: number, part: number) {
        // Update hot item based on mouse position
        const itemID = this.getPartClicked(mouseInfo.mousePos);

        if (itemID !== this.hotItem) {
            this.hotItem = itemID;
        }
    }

    /**
     * Handle mouse leave
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     */
    doMouseLeave(mouseInfo: MouseInfo, id: number, part: number) {
        this.hotItem = HOT_ITEM_NONE;
    }

    /**
     * Handle mouse enter
     * @param {Object} mouseInfo - Mouse information
     * @param {number} id - View ID
     * @param {number} part - Clicked part
     */
    doMouseEnter(mouseInfo: MouseInfo, id: number, part: number) {
        // Hot item will be set by mouse move
    }

    /**
     * Update menu item bounds after the view moves or resizes.
     * @param previous - Previous view area.
     */
    viewAreaChanged(previous: PDG.Rect): void {
        super.viewAreaChanged(previous);
        if (this.drawableItemList) {
            const area=this.viewArea, sx=previous.width() ? area.width()/previous.width() : 1;
            const sy=previous.height() ? area.height()/previous.height() : 1;
            for (const item of this.drawableItemList) {
                const r=item.rect;
                item.rect=new engine.Rect(area.left+(r.left-previous.left)*sx,area.top+(r.top-previous.top)*sy,
                    area.left+(r.right-previous.left)*sx,area.top+(r.bottom-previous.top)*sy);
            }
        }
    }

    getPartClicked(screenPoint: PDG.Point) {
        screenPoint = this.globalToLocal(screenPoint).add(this.viewArea.leftTop());
        for (let i = 0; i < this.drawableItemList.length; i++) {
            const itemPair = this.drawableItemList[i];
            if (itemPair.rect.contains(screenPoint)) {
                return itemPair.item.itemID;
            }
        }
        return HOT_ITEM_NONE;
    }

    /**
     * Scroll menu by number of items
     * @param {number} nItems - Number of items to scroll (positive = down, negative = up)
     */
    scrollMenu(nItems: number): void {
        if (!this.needScrolling) return;

        const newStartIndex = this.startIndex + nItems;
        const maxStartIndex = Math.max(0, this.itemList.length - this.itemShowable);

        this.startIndex = Math.max(0, Math.min(newStartIndex, maxStartIndex));
        this.sanitiseViewArea();
        this.calcClickableAreas();
    }

    /**
     * Sanitise view area
     */
    sanitiseViewArea(): void {
        const viewArea = this.getViewArea();
        const itemHeight = super.getTextSize() + ITEM_SIZE_OFFSET;
        this.itemShowable = Math.floor(viewArea.height() / itemHeight);

        // Check if scrolling is needed
        this.needScrolling = this.itemList.length > this.itemShowable;

        if (this.needScrolling) {
            // Set up scrolling
            if (this.startIndex === START_INDEX_NONE) {
                this.startIndex = 0;
            }

            this.startIndex = Math.max(0, Math.min(this.startIndex, this.itemList.length - this.itemShowable));

            // Determine which arrows to show
            this.showUpArrow = this.startIndex > 0;
            this.showDownArrow = this.startIndex < this.itemList.length - this.itemShowable;
        } else {
            this.startIndex = 0;
            this.showUpArrow = false;
            this.showDownArrow = false;
        }

        // Update drawable item list
        this.drawableItemList = [];
        const startY = viewArea.top + 2;

        for (let i = 0; i < this.itemShowable && this.startIndex + i < this.itemList.length; i++) {
            const item = this.itemList[this.startIndex + i];
            const itemRect = new engine.Rect(
                viewArea.left + 2,
                startY + i * itemHeight,
                viewArea.width() - 4,
                itemHeight
            );

            this.addDrawableItemPart(itemRect, item);
        }
    }

    /**
     * Set text size
     * @param {number} size - Text size
     */
    setTextSize(size: number): void {
        this.textSize(size);
        this.sanitiseViewArea();
        this.calcClickableAreas();
    }

    /**
     * Hide the popup menu
     */
    hide() {
        this.hotItem = HOT_ITEM_NONE;
        super.hide();
    }

    /**
     * Add drawable item part
     * @param {Rect} rect - Item rectangle
     * @param {ItemInfo} item - Item information
     */
    addDrawableItemPart(rect: PDG.Rect, item: ItemInfo): void {
        this.drawableItemList.push({ rect: rect, item: item });
    }

    /**
     * Set longest text
     */
    setLongestText(): void {
        this.longestText = '';
        for (const item of this.itemList) {
            if (item.itemString.length > this.longestText.length) {
                this.longestText = item.itemString;
            }
        }

        // Update minimum width based on longest text
        this.minWidth = Math.min(MAX_MENU_WIDTH, this.longestText.length * super.getTextSize() * 0.6 + TEXT_WIDTH_OFFSET);
    }

    /**
     * Load string from resource
     * @param {string} aString - String to load
     * @param {number} resourceID - Resource ID
     * @param {number} numStrings - Number of strings
     */
    loadString(aString: string, resourceID: number, numStrings: number): void {
        try {
            aString = this.resMgr.getString(resourceID);
        } catch (error) {
            console.warn(`Failed to load string from resource ${resourceID}:`, error);
            aString = `Resource_${resourceID}`;
        }
    }

    /**
     * Get item count
     * @returns {number} Number of items
     */
    getItemCount(): number {
        return this.itemList.length;
    }

    /**
     * Get hot item
     * @returns {number} Hot item ID
     */
    getHotItem(): number {
        return this.hotItem;
    }

    /**
     * Set hot item
     * @param {number} itemID - Item ID to set as hot
     */
    setHotItem(itemID: number): void {
        this.hotItem = itemID;
    }

    /**
     * Cleanup when popup menu is destroyed
     */
    destroy() {
        super.destroy();
        this.itemList = [];
        this.drawableItemList = [];
        this.pullArrowImage = null;
    }
}

export {
CLIP_TEXT,HIGHLIGHT_AREA_MARGIN,HOT_ITEM_NONE,IMAGE_HEIGHT_OFFSET,ITEM_DOWN_ARROW,ITEM_SIZE_OFFSET,ITEM_UP_ARROW,ItemInfo,MAX_ARROW_IMAGES,MAX_MENU_WIDTH,PopupMenu,RES_MENU_IMAGES,RES_PULL_ARROW,
START_INDEX_NONE,TEXT_LEFT_MARGIN,TEXT_RESOURCE_ID_NONE,TEXT_WIDTH_OFFSET,VIEW_HEIGHT_OFFSET,VIEW_HSHIFT_OFFSET,VIEW_WIDTH_OFFSET
};
