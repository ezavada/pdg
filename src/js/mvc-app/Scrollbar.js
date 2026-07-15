// -----------------------------------------------
// Scrollbar.js
// 
// JavaScript port of the Scrollbar UI component
// A scrollbar with orientation and slider functionality
//
// Ported from C++ by Assistant, 2024
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

const { View } = require('./View');
const { Subject } = require('./Observer');

/**
 * Scrollbar orientation
 */
const ScrollbarOrientation = {
    HORIZONTAL: 0,
    VERTICAL: 1,           // Up is smaller
    VERTICAL_UP_IS_BIGGER: 2
};

/**
 * Scrollbar click IDs
 */
const ScrollbarClickIDs = {
    CLICK_ID_SCROLL_UP: 1,
    CLICK_ID_SCROLL_DOWN: 2,
    CLICK_ID_SLIDER_AREA: 3
};

/**
 * Scrollbar images
 */
const ScrollbarImages = {
    SCROLL_DOWN: 0,
    SCROLL_UP: 1,
    SCROLL_SLIDER: 2,
    SCROLL_DOWN_CLICKED: 3,
    SCROLL_UP_CLICKED: 4,
    MAX_SCROLL_BAR_IMAGES: 5
};

/**
 * Scrollbar UI component that extends View and implements Subject
 * Provides scrolling functionality with orientation support
 */
class Scrollbar extends View {
    constructor(controller, scrollBarRect, orientation, initValue, visibleAmount, rangeSize) {
        super(controller, scrollBarRect);
        
        // Initialize Subject functionality
        this.observers = [];
        
        this.orientation = orientation;
        this.visibleAmount = visibleAmount;
        this.minRange = 0;
        this.maxRange = Math.max(rangeSize - visibleAmount, 0);
        this.currentPosition = Math.min(Math.max(initValue, this.minRange), this.maxRange);
        this.stepSize = 1;
        this.pageSize = visibleAmount;
        
        // Event managers
        this.eventMgr = controller.getApplication().getEventManager();
        this.resMgr = controller.getApplication().getResourceManager();
        this.timerMgr = controller.getApplication().getTimerManager();
        
        // Images
        this.mpScrollBarImages = new Array(ScrollbarImages.MAX_SCROLL_BAR_IMAGES).fill(null);
        
        // Button points
        this.upButtonPoint = new pdg.Point(0, 0);
        this.downButtonPoint = new pdg.Point(0, 0);
        this.sliderArea = new pdg.Rect(0, 0, 0, 0);
        
        // Tracking state
        this.sliderStartTrackPoint = new pdg.Point(0, 0);
        this.oldMousePoint = new pdg.Point(0, 0);
        this.sliderStartTrackHeight = 0;
        this.sliderPoint = new pdg.Point(0, 0);
        
        // Click states
        this.scrollUpClicked = false;
        this.scrollDownClicked = false;
        this.scrollUpFullWindowClicked = false;
        this.scrollDownFullWindowClicked = false;
        this.scrollSliderClicked = false;
        
        // Note: Event handling is done through the global pdg.on* methods
        // No need to register with eventMgr.addHandler
        
        this.calcClickableAreas();
    }

    /**
     * Load scrollbar images
     * @param {number} scrollbarImagesResourceID - Resource ID for images
     */
    loadImages(scrollbarImagesResourceID) {
        try {
            for (let i = 0; i < ScrollbarImages.MAX_SCROLL_BAR_IMAGES; i++) {
                this.mpScrollBarImages[i] = this.resMgr.getImage(scrollbarImagesResourceID, i);
            }
        } catch (error) {
            console.warn(`Failed to load scrollbar images for ID ${scrollbarImagesResourceID}:`, error);
            this.createPlaceholderImages();
        }
    }

    /**
     * Create placeholder images
     */
    createPlaceholderImages() {
        // In a real implementation, you would create actual images
        for (let i = 0; i < ScrollbarImages.MAX_SCROLL_BAR_IMAGES; i++) {
            this.mpScrollBarImages[i] = null;
        }
    }

    /**
     * Calculate clickable areas
     */
    calcClickableAreas() {
        const viewArea = this.getViewArea();
        const buttonSize = 16; // Standard button size
        
        if (this.orientation === ScrollbarOrientation.HORIZONTAL) {
            // Horizontal scrollbar
            this.upButtonPoint = new pdg.Point(viewArea.left, viewArea.top);
            this.downButtonPoint = new pdg.Point(viewArea.right - buttonSize, viewArea.top);
            this.sliderArea = new pdg.Rect(viewArea.left + buttonSize, viewArea.top, 
                                      viewArea.right - buttonSize * 2, viewArea.bottom);
            
            // Add clickable areas
            this.addClickablePart(new pdg.Rect(viewArea.left, viewArea.top, buttonSize, viewArea.height()),
                                ScrollbarClickIDs.CLICK_ID_SCROLL_UP);
            this.addClickablePart(new pdg.Rect(viewArea.right - buttonSize, viewArea.top, buttonSize, viewArea.height()),
                                ScrollbarClickIDs.CLICK_ID_SCROLL_DOWN);
            this.addClickablePart(this.sliderArea, ScrollbarClickIDs.CLICK_ID_SLIDER_AREA);
        } else {
            // Vertical scrollbar
            this.upButtonPoint = new pdg.Point(viewArea.left, viewArea.top);
            this.downButtonPoint = new pdg.Point(viewArea.left, viewArea.bottom - buttonSize);
            this.sliderArea = new pdg.Rect(viewArea.left, viewArea.top + buttonSize,
                                      viewArea.right, viewArea.bottom - buttonSize * 2);
            
            // Add clickable areas
            this.addClickablePart(new pdg.Rect(viewArea.left, viewArea.top, viewArea.width(), buttonSize),
                                ScrollbarClickIDs.CLICK_ID_SCROLL_UP);
            this.addClickablePart(new pdg.Rect(viewArea.left, viewArea.bottom - buttonSize, viewArea.width(), buttonSize),
                                ScrollbarClickIDs.CLICK_ID_SCROLL_DOWN);
            this.addClickablePart(this.sliderArea, ScrollbarClickIDs.CLICK_ID_SLIDER_AREA);
        }
        
        this.updateSliderPosition();
    }

    /**
     * Update slider position based on current position
     */
    updateSliderPosition() {
        if (this.maxRange <= 0) {
            this.sliderPoint = this.sliderArea.leftTop();
            return;
        }
        
        const range = this.maxRange - this.minRange;
        const position = (this.currentPosition - this.minRange) / range;
        
        if (this.orientation === ScrollbarOrientation.HORIZONTAL) {
            const sliderWidth = Math.max(this.sliderArea.width() * this.visibleAmount / (this.visibleAmount + range), 20);
            const availableWidth = this.sliderArea.width() - sliderWidth;
            const sliderX = this.sliderArea.left + position * availableWidth;
            this.sliderPoint = new pdg.Point(sliderX, this.sliderArea.top);
        } else {
            const sliderHeight = Math.max(this.sliderArea.height() * this.visibleAmount / (this.visibleAmount + range), 20);
            const availableHeight = this.sliderArea.height() - sliderHeight;
            const sliderY = this.sliderArea.top + position * availableHeight;
            this.sliderPoint = new pdg.Point(this.sliderArea.left, sliderY);
        }
    }

    /**
     * Draw the scrollbar
     */
    drawSelf(port, frameNum) {
        const viewArea = this.getViewArea();
        
        // Draw background
        var backgroundAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.9, 0.9, 0.9, 1.0));
        port.drawRect(viewArea, backgroundAttrs);
        
        // Draw border
        var borderAttrs = new pdg.Attributes().lineColor(new pdg.Color(0.7, 0.7, 0.7, 1.0)).lineThickness(1);
        port.drawRect(viewArea, borderAttrs);
        
        // Draw buttons and slider
        this.drawScrollBar();
    }

    /**
     * Draw scrollbar components
     */
    drawScrollBar() {
        const port = this.getPort();
        const buttonSize = 16;
        
        // Draw up button
        const upButtonRect = this.getUpButtonRect();
        this.drawButton(upButtonRect, this.scrollUpClicked ? ScrollbarImages.SCROLL_UP_CLICKED : ScrollbarImages.SCROLL_UP);
        
        // Draw down button
        const downButtonRect = this.getDownButtonRect();
        this.drawButton(downButtonRect, this.scrollDownClicked ? ScrollbarImages.SCROLL_DOWN_CLICKED : ScrollbarImages.SCROLL_DOWN);
        
        // Draw slider area background
        var sliderBgAttrs = new pdg.Attributes().fillColor(new pdg.Color(0.8, 0.8, 0.8, 1.0));
        port.drawRect(this.sliderArea, sliderBgAttrs);
        var sliderBorderAttrs = new pdg.Attributes().lineColor(new pdg.Color(0.6, 0.6, 0.6, 1.0)).lineThickness(1);
        port.drawRect(this.sliderArea, sliderBorderAttrs);
        
        // Draw slider
        if (this.maxRange > 0) {
            const sliderRect = this.getSliderRect();
            this.drawSlider(sliderRect);
        }
    }

    /**
     * Draw a button
     * @param {pdg.Rect} rect - Button rectangle
     * @param {number} imageIndex - Image index
     */
    drawButton(rect, imageIndex) {
        const port = this.getPort();
        
        if (this.mpScrollBarImages[imageIndex]) {
            // Draw using loaded image
            port.drawImage(this.mpScrollBarImages[imageIndex], rect.leftTop(), rect);
        } else {
            // Draw standard button
            const bgColor = this.isButtonPressed(imageIndex) ? 
                new pdg.Color(0.6, 0.6, 0.6, 1.0) : 
                new pdg.Color(0.9, 0.9, 0.9, 1.0);
            
            var buttonBgAttrs = new pdg.Attributes().fillColor(bgColor);
            port.drawRect(rect, buttonBgAttrs);
            var buttonBorderAttrs = new pdg.Attributes().lineColor(new pdg.Color(0.5, 0.5, 0.5, 1.0)).lineThickness(1);
            port.drawRect(rect, buttonBorderAttrs);
            
            // Draw arrow
            this.drawArrow(rect, imageIndex);
        }
    }

    /**
     * Draw arrow in button
     * @param {pdg.Rect} rect - Button rectangle
     * @param {number} imageIndex - Image index
     */
    drawArrow(rect, imageIndex) {
        const port = this.getPort();
        const centerX = rect.left + rect.width() / 2;
        const centerY = rect.top + rect.height() / 2;
        const size = 4;
        
        const arrowColor = new pdg.Color(0.2, 0.2, 0.2, 1.0);
        
        if (imageIndex === ScrollbarImages.SCROLL_UP || imageIndex === ScrollbarImages.SCROLL_UP_CLICKED) {
            // Draw up arrow
            port.drawLine(new pdg.Point(centerX, centerY - size), new pdg.Point(centerX - size, centerY), arrowColor, 2);
            port.drawLine(new pdg.Point(centerX, centerY - size), new pdg.Point(centerX + size, centerY), arrowColor, 2);
        } else if (imageIndex === ScrollbarImages.SCROLL_DOWN || imageIndex === ScrollbarImages.SCROLL_DOWN_CLICKED) {
            // Draw down arrow
            port.drawLine(new pdg.Point(centerX, centerY + size), new pdg.Point(centerX - size, centerY), arrowColor, 2);
            port.drawLine(new pdg.Point(centerX, centerY + size), new pdg.Point(centerX + size, centerY), arrowColor, 2);
        }
    }

    /**
     * Draw slider
     * @param {pdg.Rect} rect - Slider rectangle
     */
    drawSlider(rect) {
        const port = this.getPort();
        
        if (this.mpScrollBarImages[ScrollbarImages.SCROLL_SLIDER]) {
            // Draw using loaded image
            port.drawImage(this.mpScrollBarImages[ScrollbarImages.SCROLL_SLIDER], rect.leftTop(), rect);
        } else {
            // Draw standard slider
            const bgColor = this.scrollSliderClicked ? 
                new pdg.Color(0.5, 0.5, 0.5, 1.0) : 
                new pdg.Color(0.7, 0.7, 0.7, 1.0);
            
            var sliderBgAttrs = new pdg.Attributes().fillColor(bgColor);
            port.drawRect(rect, sliderBgAttrs);
            var sliderBorderAttrs = new pdg.Attributes().lineColor(new pdg.Color(0.3, 0.3, 0.3, 1.0)).lineThickness(1);
            port.drawRect(rect, sliderBorderAttrs);
        }
    }

    /**
     * Check if button is pressed
     * @param {number} imageIndex - Image index
     * @returns {boolean} true if pressed
     */
    isButtonPressed(imageIndex) {
        return imageIndex === ScrollbarImages.SCROLL_UP_CLICKED || 
               imageIndex === ScrollbarImages.SCROLL_DOWN_CLICKED;
    }

    /**
     * Get up button rectangle
     * @returns {pdg.Rect} Up button rectangle
     */
    getUpButtonRect() {
        const buttonSize = 16;
        if (this.orientation === ScrollbarOrientation.HORIZONTAL) {
            return new pdg.Rect(this.upButtonPoint.x, this.upButtonPoint.y, buttonSize, this.getViewArea().height());
        } else {
            return new pdg.Rect(this.upButtonPoint.x, this.upButtonPoint.y, this.getViewArea().width(), buttonSize);
        }
    }

    /**
     * Get down button rectangle
     * @returns {pdg.Rect} Down button rectangle
     */
    getDownButtonRect() {
        const buttonSize = 16;
        if (this.orientation === ScrollbarOrientation.HORIZONTAL) {
            return new pdg.Rect(this.downButtonPoint.x, this.downButtonPoint.y, buttonSize, this.getViewArea().height());
        } else {
            return new pdg.Rect(this.downButtonPoint.x, this.downButtonPoint.y, this.getViewArea().width(), buttonSize);
        }
    }

    /**
     * Get slider rectangle
     * @returns {pdg.Rect} Slider rectangle
     */
    getSliderRect() {
        const range = this.maxRange - this.minRange;
        if (range <= 0) return new pdg.Rect(0, 0, 0, 0);
        
        if (this.orientation === ScrollbarOrientation.HORIZONTAL) {
            const sliderWidth = Math.max(this.sliderArea.width() * this.visibleAmount / (this.visibleAmount + range), 20);
            return new pdg.Rect(this.sliderPoint.x, this.sliderPoint.y, sliderWidth, this.sliderArea.height());
        } else {
            const sliderHeight = Math.max(this.sliderArea.height() * this.visibleAmount / (this.visibleAmount + range), 20);
            return new pdg.Rect(this.sliderPoint.x, this.sliderPoint.y, this.sliderArea.width(), sliderHeight);
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
        switch (part) {
            case ScrollbarClickIDs.CLICK_ID_SCROLL_UP:
                this.scrollUpPressed();
                return true;
                
            case ScrollbarClickIDs.CLICK_ID_SCROLL_DOWN:
                this.scrollDownPressed();
                return true;
                
            case ScrollbarClickIDs.CLICK_ID_SLIDER_AREA:
                this.scrollSliderAreaPressed(mouseInfo.mousePos);
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
    doMouseUp(mouseInfo, id, part) {
        switch (part) {
            case ScrollbarClickIDs.CLICK_ID_SCROLL_UP:
                this.scrollUpReleased();
                return true;
                
            case ScrollbarClickIDs.CLICK_ID_SCROLL_DOWN:
                this.scrollDownReleased();
                return true;
                
            case ScrollbarClickIDs.CLICK_ID_SLIDER_AREA:
                this.scrollSliderAreaReleased();
                return true;
        }
        return false;
    }

    /**
     * Scroll up
     */
    scrollUp() {
        this.setCurrentPosition(this.currentPosition - this.stepSize);
    }

    /**
     * Scroll up pressed
     */
    scrollUpPressed() {
        this.scrollUpClicked = true;
        this.scrollUp();
        
        // Start repeat timer
        this.timerMgr.startTimer('SCROLL_UP_TIMER', 100, false); // oneShot = false (repeating)
    }

    /**
     * Scroll up released
     */
    scrollUpReleased() {
        this.scrollUpClicked = false;
        this.timerMgr.cancelTimer('SCROLL_UP_TIMER');
    }

    /**
     * Scroll down
     */
    scrollDown() {
        this.setCurrentPosition(this.currentPosition + this.stepSize);
    }

    /**
     * Scroll down pressed
     */
    scrollDownPressed() {
        this.scrollDownClicked = true;
        this.scrollDown();
        
        // Start repeat timer
        this.timerMgr.startTimer('SCROLL_DOWN_TIMER', 100, false); // oneShot = false (repeating)
    }

    /**
     * Scroll down released
     */
    scrollDownReleased() {
        this.scrollDownClicked = false;
        this.timerMgr.cancelTimer('SCROLL_DOWN_TIMER');
    }

    /**
     * Scroll slider area pressed
     * @param {pdg.Point} clickPoint - Click point
     */
    scrollSliderAreaPressed(clickPoint) {
        const localPoint = this.globalToLocal(clickPoint);
        
        if (this.getSliderRect().contains(localPoint)) {
            // Clicked on slider - start tracking
            this.scrollSliderClicked = true;
            this.sliderStartTrackPoint = localPoint;
            this.oldMousePoint = localPoint;
            this.sliderStartTrackHeight = this.currentPosition;
        } else {
            // Clicked in slider area - page up/down
            if (this.orientation === ScrollbarOrientation.HORIZONTAL) {
                if (localPoint.x < this.sliderPoint.x) {
                    this.scrollUpFullWindow();
                } else {
                    this.scrollDownFullWindow();
                }
            } else {
                if (localPoint.y < this.sliderPoint.y) {
                    this.scrollUpFullWindow();
                } else {
                    this.scrollDownFullWindow();
                }
            }
        }
    }

    /**
     * Scroll slider area released
     */
    scrollSliderAreaReleased() {
        this.scrollSliderClicked = false;
    }

    /**
     * Scroll up full window (page up)
     */
    scrollUpFullWindow() {
        this.setCurrentPosition(this.currentPosition - this.pageSize);
    }

    /**
     * Scroll down full window (page down)
     */
    scrollDownFullWindow() {
        this.setCurrentPosition(this.currentPosition + this.pageSize);
    }

    /**
     * Track scroll slider
     */
    trackScrollSlider() {
        if (!this.scrollSliderClicked) return;
        
        // This would be called during mouse move to update slider position
        // Implementation would calculate new position based on mouse movement
    }

    /**
     * Handle events
     * @param {string} eventType - Event type
     * @param {*} eventData - Event data
     * @returns {boolean} true if handled
     */
    handleEvent(eventType, eventData) {
        if (eventType === 'eventType_Timer') {
            if (eventData.id === 'SCROLL_UP_TIMER') {
                this.scrollUp();
                return true;
            } else if (eventData.id === 'SCROLL_DOWN_TIMER') {
                this.scrollDown();
                return true;
            }
        }
        return false;
    }

    /**
     * Get current position
     * @returns {number} Current position
     */
    getCurrentPosition() {
        return this.currentPosition;
    }

    /**
     * Get scroll range
     * @returns {number} Scroll range
     */
    getScrollRange() {
        return this.maxRange - this.minRange;
    }

    /**
     * Set maximum range
     * @param {number} range - Maximum range
     */
    setMaxRange(range) {
        this.maxRange = range;
        this.updateSliderPosition();
    }

    /**
     * Set current position
     * @param {number} position - New position
     */
    setCurrentPosition(position) {
        const oldPosition = this.currentPosition;
        this.currentPosition = Math.min(Math.max(position, this.minRange), this.maxRange);
        
        if (this.currentPosition !== oldPosition) {
            this.updateSliderPosition();
            this.notifyObservers(); // Notify observers of change
        }
    }

    /**
     * Set minimum range
     * @param {number} range - Minimum range
     */
    setMinRange(range) {
        this.minRange = range;
        this.updateSliderPosition();
    }

    /**
     * Set visible amount
     * @param {number} amount - Visible amount
     */
    setVisibleAmount(amount) {
        this.visibleAmount = amount;
        this.updateSliderPosition();
    }

    /**
     * Set step size
     * @param {number} size - Step size
     */
    setStepSize(size) {
        this.stepSize = size;
    }

    /**
     * Set page size
     * @param {number} size - Page size
     */
    setPageSize(size) {
        this.pageSize = size;
    }

    /**
     * Get orientation
     * @returns {number} Orientation
     */
    getOrientation() {
        return this.orientation;
    }

    /**
     * Add observer (Subject method)
     * @param {IObserver} observer - Observer to add
     */
    addObserver(observer) {
        if (!this.observers.includes(observer)) {
            this.observers.push(observer);
        }
    }

    /**
     * Remove observer (Subject method)
     * @param {IObserver} observer - Observer to remove
     */
    removeObserver(observer) {
        const index = this.observers.indexOf(observer);
        if (index > -1) {
            this.observers.splice(index, 1);
        }
    }

    /**
     * Notify observers (Subject method)
     */
    notifyObservers() {
        // Most recently added is notified first (reverse iteration)
        for (let i = this.observers.length - 1; i >= 0; i--) {
            this.observers[i].notify(this);
        }
    }

    /**
     * Cleanup when scrollbar is destroyed
     */
    destroy() {
        // Cancel timers
        this.timerMgr.cancelTimer('SCROLL_UP_TIMER');
        this.timerMgr.cancelTimer('SCROLL_DOWN_TIMER');
        
        // Unregister event handlers
        this.eventMgr.removeHandler(this, PDGEventTypes.eventType_Timer);
        
        // Clean up images
        for (let i = 0; i < ScrollbarImages.MAX_SCROLL_BAR_IMAGES; i++) {
            this.mpScrollBarImages[i] = null;
        }
        
        // Clear observers
        this.observers = [];
    }
}

module.exports = {
    Scrollbar,
    ScrollbarOrientation,
    ScrollbarClickIDs,
    ScrollbarImages
};
