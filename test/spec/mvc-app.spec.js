// -----------------------------------------------
// mvc-app.spec.js
//
// Jasmine test suite for the JavaScript Application Framework
// Tests basic functionality of the MVC classes
//
// Converted from test.js by Assistant, 2024
// Original Copyright (c) 2004-2012, Dream Rock Studios, LLC
// -----------------------------------------------

require('./SpecHelper');
const framework = require('../../src/js/mvc-app/index');

// Extract classes from the framework object
const Application = framework.Application.Application;
const AppStates = framework.Application.AppStates;
const IObserver = framework.Observer.IObserver;
const Subject = framework.Observer.Subject;
const View = framework.View.View;
const Rect = framework.View.Rect;
const Point = framework.View.Point;
const ClickablePartsIDs = framework.View.ClickablePartsIDs;
const ViewBinding = framework.View.ViewBinding;
const Controller = framework.Controller.Controller;
const ControllerPreferences = framework.Controller.ControllerPreferences;
const Button = framework.Button.Button;
const Dialog = framework.Dialog.Dialog;
const DialogFlags = framework.Dialog.DialogFlags;
const Checkbox = framework.Checkbox.Checkbox;
const EditText = framework.EditText.EditText;
const ListBox = framework.ListBox.ListBox;
const Scrollbar = framework.Scrollbar.Scrollbar;
const ScrollbarOrientation = framework.Scrollbar.ScrollbarOrientation;
const ModalController = framework.ModalController.ModalController;
const TouchController = framework.TouchController.TouchController;
const ScrollingView = framework.ScrollingView.ScrollingView;
const RadioButton = framework.RadioButton.RadioButton;
const PopupMenu = framework.PopupMenu.PopupMenu;
const MessageDialog = framework.MessageDialog.MessageDialog;
const MessageDialogButtonText = framework.MessageDialog.MessageDialogButtonText;
const MessageView = framework.MessageView.MessageView;

const mocks = require('../../src/js/mvc-app/mocks');
const MockPdg = mocks.MockPdg;
const MockGraphicsManager = mocks.MockGraphicsManager;
const MockPort = mocks.MockPort;

class TestApplication extends Application {
    constructor() {
        super();
        
        // Set up mock managers
        this.timerMgr = {
            timers: new Map(),
            startTimer: (id, delay, oneShot = true) => {
                // Mock timer implementation
            },
            cancelTimer: (id) => {
                this.timerMgr.timers.delete(id);
            }
        };
        this.graphicsMgr = new MockGraphicsManager();
        this.logMgr = {
            log: (msg) => {} // Mock logging
        };
        this.configMgr = {
            get: (key) => null // Mock config
        };
    }
    
    initialize(args) {
        this.setState(AppStates.state_Running);
    }
    
    cleanup() {
        // Mock cleanup
    }
}

// Test classes
class TestObserver extends IObserver {
    constructor(name) {
        super();
        this.name = name;
        this.notified = false;
    }
    
    notify(subject) {
        this.notified = true;
    }
}

class TestView extends View {
    constructor(controller, rect) {
        super(controller, rect);
        this.drawCount = 0;
    }
    
    drawSelf() {
        this.drawCount++;
        const port = this.getPort();
        const area = this.getViewArea();
        var attrs = new pdg.Attributes().fillColor(new pdg.Color(0.8, 0.8, 1.0, 1.0));
        port.drawRect(area, attrs);
    }
}

class TestController extends Controller {
    constructor(app, port) {
        super(null, app, port, true, true, true, false, true);
        this.buttonWasClicked = false;
    }
    
    buttonClicked(buttonId, button) {
        this.buttonWasClicked = true;
    }

    destroy() {
        pdg.gfx.closeGraphicsPort(this.port);
        this.port = null;
        super.destroy();
    }
}

class TestScrollingView extends ScrollingView {
    constructor(controller, rect) {
        super(controller, rect);
    }   
    drawSelf() {
        const port = this.getPort();
        const area = this.getViewArea();
        var attrs = new pdg.Attributes().fillColor(new pdg.Color(0.8, 0.8, 1.0, 1.0));
        port.drawRect(area, attrs);
    }
}

describe("MVC Application Framework", function() {

  describe("Observer Pattern", function() {

    it("should add and remove observers", function() {
      console.log('* Testing Observer Pattern...');
      
      const subject = new Subject();
      const observer1 = new TestObserver('Observer1');
      const observer2 = new TestObserver('Observer2');
      
      subject.addObserver(observer1);
      subject.addObserver(observer2);
      
      expect(subject.getObserverCount()).toEqual(2);
      
      subject.notifyObservers();
      
      expect(observer1.notified).toBe(true);
      expect(observer2.notified).toBe(true);
      
      subject.removeObserver(observer1);
      expect(subject.getObserverCount()).toEqual(1);
    });

  });

  describe("Application", function() {

    it("should initialize and manage state", function() {
      console.log('* Testing Application...');
      
      const app = new TestApplication();
      expect(app.getState()).toBeDefined();
      
      app.initialize(['-nosplash']);
      expect(app.getState()).toEqual(AppStates.state_Running);
    });

  });

  describe("View", function() {

    it("should create and manage view properties", function() {
      console.log('* Testing View...');
      
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const rect = new pdg.Rect(10, 10, 100, 50);
      
      const view = new TestView(controller, rect);
      expect(view.getViewArea()).toEqual(rect);
      expect(view.isVisible()).toBe(true);
      expect(view.isEnabled()).toBe(true);
      
      view.hide();
      expect(view.isVisible()).toBe(false);
      view.show();
      expect(view.isVisible()).toBe(true);
    });

    it("should draw itself when requested", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const rect = new pdg.Rect(10, 10, 100, 50);
      
      const view = new TestView(controller, rect);
      expect(view.drawCount).toEqual(0);
      
      view.draw(app.graphicsMgr.getMainPort(), 0);
      expect(view.drawCount).toEqual(1);
    });

  });

  describe("Button", function() {

    it("should create and manage button properties", function() {
      console.log('* Testing Button...');
      
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const rect = new pdg.Rect(50, 50, 120, 30);
      
      const button = new Button(controller, rect, 1, -1, -1, -1);
      button.setText('Test Button');
      
      expect(button.getText()).toEqual('Test Button');
      expect(button.getButtonID()).toEqual(1);
      expect(button.isEnabled()).toBe(true);
      expect(button.isPressed()).toBe(false);
    });

    it("should handle click events", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const rect = new pdg.Rect(50, 50, 120, 30);
      
      const button = new Button(controller, rect, 1, -1, -1, -1);
      
      // Simulate click
      const mouseInfo = { mousePos: new pdg.Point(100, 65), rightButton: false };
      button.doLeftClick(mouseInfo, 1, 1);
      expect(controller.buttonWasClicked).toBe(true);
    });

  });

  describe("Checkbox", function() {

    it("should create and manage checkbox properties", function() {
      console.log('* Testing Checkbox...');
      
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const rect = new pdg.Rect(50, 100, 150, 25);
      
      const checkbox = new Checkbox(controller, rect);
      checkbox.setString('Test Checkbox');
      checkbox.setTextSize(14);
      
      expect(checkbox.getString()).toEqual('Test Checkbox');
      expect(checkbox.isChecked()).toBe(false);
      expect(checkbox.getTextSize()).toEqual(14);
    });

    it("should toggle state", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const rect = new pdg.Rect(50, 100, 150, 25);
      
      const checkbox = new Checkbox(controller, rect);
      expect(checkbox.isChecked()).toBe(false);
      
      checkbox.toggle();
      expect(checkbox.isChecked()).toBe(true);
      
      checkbox.toggle();
      expect(checkbox.isChecked()).toBe(false);
    });

  });

  describe("Dialog", function() {

    it("should create and manage dialog properties", function() {
      console.log('* Testing Dialog...');
      
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      
      const dialog = new Dialog(controller, 300, 200, DialogFlags.dialog_Standard, 1, 2);
      
      expect(dialog.getDialogRect()).toBeDefined();
      expect(dialog.isCentered()).toBeDefined();
      expect(dialog.isModal()).toBeDefined();
      expect(dialog.getOkButtonId()).toEqual(1);
      expect(dialog.getCancelButtonId()).toEqual(2);
    });

  });

  describe("Rect and Point", function() {

    it("should create and manage Rect properties", function() {
      console.log('* Testing Rect and Point...');
      
      // top, left, right, bottom
      const rect = new pdg.Rect(10, 20, 100, 50);
      
      expect(rect.width()).toEqual(90);
      expect(rect.height()).toEqual(30);
      expect(rect.contains(new pdg.Point(50, 30))).toBe(true);
      expect(rect.contains(new pdg.Point(200, 200))).toBe(false);
    });

    it("should handle Rect overlaps and intersections", function() {
      // top, left, right, bottom
      const rect = new pdg.Rect(10, 20, 100, 50);
      const rect2 = new pdg.Rect(50, 30, 80, 60);
      
      expect(rect.overlaps(rect2)).toBe(true);
      expect(rect.intersection(rect2)).toBeDefined();
    });

    it("should create and manage Point properties", function() {
      const point = new pdg.Point(5, 10);
      const offset = new pdg.Point(3, 4);
      const newPoint = point.add(offset);
      
      expect(newPoint.x).toEqual(8);
      expect(newPoint.y).toEqual(14);
    });

  });

  describe("EditText", function() {

    it("should create and manage EditText properties", function() {
      console.log('* Testing EditText...');
      
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const editRect = new pdg.Rect(50, 50, 200, 30);
      const editText = new EditText(controller, editRect);
      
      expect(editText.hasFocus()).toBe(false);
      
      editText.setFocus(true);
      expect(editText.hasFocus()).toBe(true);
      
      editText.setText('Hello World');
      expect(editText.getText()).toEqual('Hello World');
      
      editText.setFocus(false);
      expect(editText.hasFocus()).toBe(false);
    });

  });

  describe("ListBox", function() {

    it("should create and manage ListBox properties", function() {
      console.log('* Testing ListBox...');
      
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const listRect = new pdg.Rect(50, 50, 200, 150);
      const listBox = new ListBox(controller, listRect, 5, 
        new pdg.Color(0.9, 0.9, 0.9, 1.0), new pdg.Color(0.3, 0.3, 1.0, 1.0));
      
      expect(listBox.getItemCount()).toEqual(0);
      expect(listBox.getSelectedIndex()).toEqual(-1);
    });

    it("should add and remove items", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const listRect = new pdg.Rect(50, 50, 200, 150);
      const listBox = new ListBox(controller, listRect, 5, 
        new pdg.Color(0.9, 0.9, 0.9, 1.0), new pdg.Color(0.3, 0.3, 1.0, 1.0));
      
      listBox.addToList('Item 1');
      listBox.addToList('Item 2');
      listBox.addToList('Item 3');
      listBox.addToList('Item 4');
      listBox.addToList('Item 5');
      
      expect(listBox.getItemCount()).toEqual(5);
      
      listBox.setSelectedIndex(2);
      expect(listBox.getSelectedIndex()).toEqual(2);
      expect(listBox.getSelectedText()).toEqual('Item 3');
      
      listBox.removeItem(1);
      expect(listBox.getItemCount()).toEqual(4);
      
      listBox.clear();
      expect(listBox.getItemCount()).toEqual(0);
    });

  });

  describe("Scrollbar", function() {

    it("should create and manage Scrollbar properties", function() {
      console.log('* Testing Scrollbar...');
      
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const scrollRect = new pdg.Rect(50, 50, 20, 200);
      const scrollbar = new Scrollbar(controller, scrollRect, ScrollbarOrientation.VERTICAL, 0, 10, 100);
      
      expect(scrollbar.getOrientation()).toEqual(ScrollbarOrientation.VERTICAL);
      expect(scrollbar.getCurrentPosition()).toEqual(0);
      expect(scrollbar.getScrollRange()).toEqual(90);
    });

    it("should update scrollbar position and range", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const scrollRect = new pdg.Rect(50, 50, 20, 200);
      const scrollbar = new Scrollbar(controller, scrollRect, ScrollbarOrientation.VERTICAL, 0, 10, 100);
      
      scrollbar.setCurrentPosition(50);
      expect(scrollbar.getCurrentPosition()).toEqual(50);
      
      scrollbar.setMaxRange(200);
      expect(scrollbar.getScrollRange()).toEqual(200);
    });

  });

  describe("ModalController", function() {

    it("should create and manage modal state", function() {
      console.log('* Testing ModalController...');
      
      const app = new TestApplication();
      const topLevelController = new TestController(app, app.graphicsMgr.getMainPort());
      const modalController = new ModalController(topLevelController);
      
      expect(modalController.isModal()).toBe(true);
      expect(modalController.isModalActive()).toBe(true);
      
      modalController.activateModal();
      expect(modalController.isModalActive()).toBe(true);
      
      modalController.deactivateModal();
      expect(modalController.isModalActive()).toBe(false);
    });

  });

  describe("TouchController", function() {

    it("should create and manage touch state", function() {
      console.log('* Testing TouchController...');
      
      const app = new TestApplication();
      const topLevelController = new TestController(app, app.graphicsMgr.getMainPort());
      const touchController = new TouchController(topLevelController);
      
      expect(touchController.isModal()).toBe(true);
      expect(touchController.isTouchActive()).toBe(false);
      
      const mouseInfo = { mousePos: new pdg.Point(100, 100), rightButton: false };
      touchController.doMouseDown(mouseInfo, null, 1, 1);
      expect(touchController.isTouchActive()).toBe(true);
      
      touchController.doMouseUp(mouseInfo, null, 1, 1);
      expect(touchController.isTouchActive()).toBe(false);
    });

  });

  describe("ScrollingView", function() {

    it("should create and manage scrolling properties", function() {
      console.log('* Testing ScrollingView...');
      
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const scrollRect = new pdg.Rect(50, 50, 200, 150);
      const scrollingView = new TestScrollingView(controller, scrollRect);
      
      expect(scrollingView.getViewFrame()).toBeDefined();
    });

  });

  describe("RadioButton", function() {

    it("should create and manage radio button properties", function() {
      console.log('* Testing RadioButton...');
      
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const radioRect = new pdg.Rect(50, 50, 150, 100);
      const radioButton = new RadioButton(controller, radioRect, -1, 3);
      
      expect(radioButton.getOptionCount()).toEqual(3);
      expect(radioButton.getSelectedIndex()).toEqual(0);
    });

    it("should manage selection", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const radioRect = new pdg.Rect(50, 50, 150, 100);
      const radioButton = new RadioButton(controller, radioRect, -1, 3);
      
      radioButton.setSelectedIndex(1);
      expect(radioButton.getSelectedIndex()).toEqual(1);
      
      radioButton.addString('New Option');
      expect(radioButton.getOptionCount()).toEqual(4);
    });

  });

  describe("PopupMenu", function() {

    it("should create and manage menu items", function() {
      console.log('* Testing PopupMenu...');
      
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const menuPoint = new pdg.Point(50, 50);
      const popupMenu = new PopupMenu(controller, menuPoint);
      
      expect(popupMenu.getItemCount()).toEqual(0);
      
      popupMenu.addMenuItem(1, 'Menu Item 1');
      popupMenu.addMenuItem(2, 'Menu Item 2');
      popupMenu.addMenuItem(3, 'Menu Item 3');
      
      expect(popupMenu.getItemCount()).toEqual(3);
      
      popupMenu.setHotItem(2);
      expect(popupMenu.getHotItem()).toEqual(2);
    });

  });

  describe("MessageDialog", function() {

    it("should create and manage message dialog", function() {
      console.log('* Testing MessageDialog...');
      
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const message = 'This is a test message';
      const messageDialog = new MessageDialog(controller, message, MessageDialogButtonText.OK, MessageDialogButtonText.CANCEL);
      
      expect(messageDialog.getMessageCode()).toBeDefined();
      
      messageDialog.setMessageCode(123);
      expect(messageDialog.getMessageCode()).toEqual(123);
    });

  });

  describe("MessageView", function() {

    it("should create and manage message view", function() {
      console.log('* Testing MessageView...');
      
      const app = new TestApplication();
      const topLevelController = new TestController(app, app.graphicsMgr.getMainPort());
      const messageRect = new pdg.Rect(50, 50, 200, 100);
      const messageView = new MessageView(topLevelController, messageRect, 'This is a test message');
      
      expect(messageView.getMessage()).toEqual('This is a test message');
      expect(messageView.getTextSize()).toBeDefined();
      
      messageView.setTextSize(16);
      expect(messageView.getTextSize()).toEqual(16);
      
      messageView.setMessage('Updated message');
      expect(messageView.getMessage()).toEqual('Updated message');
    });

  });

});
