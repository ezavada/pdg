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
const mvcModulePath = process.ios ? '../src/js/mvc-app' : '../../src/js/mvc-app';
const framework = require(mvcModulePath + '/index');

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
const ControlAttributes = framework.ControlAttributes.ControlAttributes;
const ControlState = framework.ControlAttributes.ControlState;
const ControlType = framework.ControlAttributes.ControlType;
const Button = framework.Button.Button;
const Dialog = framework.Dialog.Dialog;
const DialogFlags = framework.Dialog.DialogFlags;
const Checkbox = framework.Checkbox.Checkbox;
const EditText = framework.EditText.EditText;
const ListBox = framework.ListBox.ListBox;
const Scrollbar = framework.Scrollbar.Scrollbar;
const ScrollbarOrientation = framework.Scrollbar.ScrollbarOrientation;
const ScrollbarClickIDs = framework.Scrollbar.ScrollbarClickIDs;
const ModalController = framework.ModalController.ModalController;
const TouchController = framework.TouchController.TouchController;
const ScrollingView = framework.ScrollingView.ScrollingView;
const RadioButton = framework.RadioButton.RadioButton;
const PopupMenu = framework.PopupMenu.PopupMenu;
const MessageDialog = framework.MessageDialog.MessageDialog;
const MessageDialogButtonText = framework.MessageDialog.MessageDialogButtonText;
const MessageView = framework.MessageView.MessageView;

const mocks = require(mvcModulePath + '/mocks');
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

class ThemedController extends TestController {
    constructor(app, port) {
        super(app, port);
        this.requestedControls = [];
        this.themeFactory = null;
    }

    getControlAttributes(type, styleId = -1) {
        this.requestedControls.push({ type, styleId });
        return this.themeFactory ? this.themeFactory(type, styleId) : new ControlAttributes();
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

  describe("ControlAttributes", function() {

    it("should merge partial state overrides without losing foreground values", function() {
      const foreground = new pdg.Color(0.2, 0.3, 0.4, 1);
      const drawing = new pdg.Attributes().fillColor(new pdg.Color(0.8, 0.7, 0.6, 1));
      const base = new ControlAttributes()
        .stateForeground(ControlState.Normal, foreground)
        .stateAttributes(ControlState.Normal, drawing);
      const overrides = new ControlAttributes()
        .stateForeground(ControlState.Hovered, foreground);

      base.merge(overrides);

      expect(base.state(ControlState.Normal).drawing).toBe(drawing);
      expect(base.state(ControlState.Normal).foreground).toBe(foreground);
      expect(base.state(ControlState.Hovered).foreground).toBe(foreground);
    });

    it("should replace mutually exclusive background sources", function() {
      const image = { width: 20, height: 10 };
      const state = new ControlAttributes()
        .stateAttributes(ControlState.Normal, new pdg.Attributes())
        .merge(new ControlAttributes().stateImage(ControlState.Normal, image))
        .state(ControlState.Normal);

      expect(state.hasImage).toBe(true);
      expect(state.image).toBe(image);
      expect(state.hasDrawing).toBe(false);
      expect(state.hasDrawRoutine).toBe(false);
    });

    it("should fall back to Normal drawing for an unspecified state", function() {
      const calls = [];
      const drawing = new pdg.Attributes();
      const attributes = new ControlAttributes()
        .stateAttributes(ControlState.Normal, drawing);
      const port = { drawRect: (area, attrs) => calls.push({ area, attrs }) };
      const area = new pdg.Rect(0, 0, 20, 10);

      attributes.draw(port, area, ControlState.Hovered);

      expect(calls.length).toEqual(1);
      expect(calls[0].attrs).toBe(drawing);
    });

    it("should prefer a click routine to a click sound", function() {
      let routineCalls = 0;
      const sound = { calls: [], play(volume) { this.calls.push(volume); } };
      const attributes = new ControlAttributes()
        .clickSound(sound, 0.35)
        .clickRoutine(() => { routineCalls++; });

      attributes.playClick();

      expect(routineCalls).toEqual(1);
      expect(sound.calls.length).toEqual(0);
      expect(attributes.getClickVolume()).toEqual(0.35);
    });

    it("should reject invalid states", function() {
      expect(() => new ControlAttributes().state(ControlState.Count)).toThrow();
    });

  });

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

    it("should merge top-controller and per-instance attributes", function() {
      const app = new TestApplication();
      const controller = new ThemedController(app, app.graphicsMgr.getMainPort());
      const themedColor = new pdg.Color(0.1, 0.2, 0.3, 1);
      const localColor = new pdg.Color(0.7, 0.6, 0.5, 1);
      controller.themeFactory = (type) => new ControlAttributes()
        .stateForeground(ControlState.Normal, themedColor);

      const button = new Button(controller, new pdg.Rect(0, 0, 100, 30), 7,
        -1, -1, null, 42);
      button.setAttributes(new ControlAttributes()
        .stateForeground(ControlState.Pressed, localColor));

      expect(controller.requestedControls[0]).toEqual({ type: ControlType.Button, styleId: 42 });
      expect(button.getAttributes().state(ControlState.Normal).foreground).toBe(themedColor);
      expect(button.getAttributes().state(ControlState.Pressed).foreground).toBe(localColor);
    });

    it("should run ControlAttributes click behavior", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      let clicks = 0;
      const button = new Button(controller, new pdg.Rect(0, 0, 100, 30), 7);
      button.setAttributes(new ControlAttributes().clickRoutine(() => { clicks++; }));

      button.doLeftClick({}, 7, 7);

      expect(clicks).toEqual(1);
    });

    it("should create and manage button properties", function() {
      console.log('* Testing Button...');
      
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const rect = new pdg.Rect(50, 50, 120, 90);
      
      const button = new Button(controller, rect, 1, -1, -1, -1);
      button.setText('Test Button');
      
      expect(button.getText()).toEqual('Test Button');
      expect(button.getButtonID()).toEqual(1);
      expect(button.buttonTextSize).toEqual(19);
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

    it("should always draw text at a finite baseline", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      controller.port.getCurrentFont = () => ({
        getFontAscent: () => 0,
        getFontDescent: () => 0
      });
      const button = new Button(controller, new pdg.Rect(50, 50, 120, 90), 1);
      button.setText('Visible');
      let textPoint = null;
      let textAttributes = null;
      controller.port.drawText = (text, point, attributes) => {
        textPoint = point;
        textAttributes = attributes;
      };

      button.drawText(controller.port);

      expect(textPoint).not.toBe(null);
      expect(Number.isFinite(textPoint.x)).toBe(true);
      expect(Number.isFinite(textPoint.y)).toBe(true);
      expect(textPoint.y).toBeGreaterThan(button.getViewArea().top);
      expect(textPoint.y).toBeLessThan(button.getViewArea().bottom);
      expect(textAttributes.getTextStyle()).toEqual(17);
    });

    it("should keep the local text baseline stable across draw frames", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      controller.port.getCurrentFont = () => ({
        getFontAscent: () => 14,
        getFontDescent: () => 4
      });
      const button = new Button(controller, new pdg.Rect(50, 50, 120, 90), 1);
      button.setText('Stable');
      const textPoints = [];
      controller.port.drawText = (text, point) => {
        textPoints.push({ x: point.x, y: point.y });
      };

      button.drawText(controller.port);
      button.drawText(controller.port);
      button.drawText(controller.port);

      expect(textPoints).toEqual([
        { x: 85, y: 76 },
        { x: 85, y: 76 },
        { x: 85, y: 76 }
      ]);
      expect(button.textBaselineCenterPoint.x).toEqual(35);
      expect(button.textBaselineCenterPoint.y).toEqual(26);
    });

    it("should receive hover, press, and click events through its controller", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const button = new Button(controller, new pdg.Rect(10, 10, 110, 40), 7);
      const inside = {
        mousePos: new pdg.Point(50, 25),
        rightButton: false,
        lastClickElapsed: 1000
      };

      controller.onMouseMove(inside);
      expect(button.isHovered).toBe(true);

      controller.onMouseDown(inside);
      expect(button.isPressed()).toBe(true);

      controller.onMouseUp(inside);
      expect(button.isPressed()).toBe(false);
      expect(controller.buttonWasClicked).toBe(true);

      controller.onMouseMove(Object.assign({}, inside, {
        mousePos: new pdg.Point(200, 200)
      }));
      expect(button.isHovered).toBe(false);
    });

  });

  describe("Pointer capture", function() {
    function fixture() {
      const app = new TestApplication(), controller = new TestController(app, app.graphicsMgr.getMainPort());
      const a = new Button(controller, new pdg.Rect(10,10,110,40),7);
      const b = new Button(controller, new pdg.Rect(150,10,250,40),8);
      const info = (x,y=25) => ({mousePos:new pdg.Point(x,y),rightButton:false,lastClickElapsed:1000});
      return {controller,a,b,info};
    }
    it("clears pressed appearance on exit and releases only the original view", function() {
      const {controller,a,b,info}=fixture(); let releases=0, otherReleases=0, releasePart;
      const up=a.doMouseUp.bind(a);
      a.doMouseUp=(mi,id,part)=>{++releases;releasePart=part;return up(mi,id,part);};
      b.doMouseUp=()=>{++otherReleases;return false;};
      // No preceding mouse-move event: the press itself establishes capture.
      controller.onMouseDown(info(50)); expect(a.isPressed()).toBe(true);
      controller.onMouseMove(info(200)); expect(a.isPressed()).toBe(false);
      controller.onMouseUp(info(200));
      expect(releases).toBe(1);expect(otherReleases).toBe(0);expect(releasePart).toBe(-1);
      expect(controller.buttonWasClicked).toBe(false);
      controller.onMouseUp(info(50)); // a stray release cannot finish the old press
      expect(releases).toBe(1);expect(controller.buttonWasClicked).toBe(false);
    });
    it("rearms on reentry and ignores releases of another mouse button", function() {
      const {controller,a,info}=fixture();
      controller.onMouseDown(info(50));controller.onMouseMove(info(300));
      expect(a.isPressed()).toBe(false);
      controller.onMouseMove(info(50));expect(a.isPressed()).toBe(true);
      controller.onMouseUp(Object.assign(info(50),{rightButton:true}));
      expect(a.isPressed()).toBe(true);expect(controller.buttonWasClicked).toBe(false);
      controller.onMouseUp(info(50));expect(a.isPressed()).toBe(false);
      expect(controller.buttonWasClicked).toBe(true);
    });
    it("cancels hidden, disabled, removed, or deactivated presses", function() {
      for (const cancel of [(c,a)=>a.setEnabled(false),(c,a)=>a.hide(),
          (c,a)=>c.removeView(a),(c,a)=>c.setActive(false)]) {
        const {controller,a,info}=fixture();
        controller.onMouseDown(info(50));cancel(controller,a);controller.onMouseUp(info(50));
        expect(a.isPressed()).toBe(false);expect(controller.buttonWasClicked).toBe(false);
      }
    });
    it("does not click a view removed by its release callback", function() {
      const {controller,a,info}=fixture(), up=a.doMouseUp.bind(a);
      a.doMouseUp=(mi,id,part)=>{up(mi,id,part);controller.removeView(a);return false;};
      controller.onMouseDown(info(50));controller.onMouseUp(info(50));
      expect(controller.buttonWasClicked).toBe(false);
    });
    it("captures generic views without IDs and continues drag motion outside", function() {
      const {controller,info}=fixture();
      const view=new TestView(controller,new pdg.Rect(10,80,110,120));
      view.setID(-1); let ups=0, moves=0, clicks=0;
      view.doMouseMove=()=>++moves;view.doMouseUp=()=>{++ups;return false;};
      view.doLeftClick=()=>{++clicks;return true;};
      controller.onMouseDown(info(50,100));controller.onMouseMove(info(300,100));controller.onMouseUp(info(300,100));
      expect(moves).toBe(1);expect(ups).toBe(1);expect(clicks).toBe(0);
    });
    it("requires release over the same radio option or checkbox", function() {
      const {controller,info}=fixture();
      const radio=new RadioButton(controller,new pdg.Rect(10,80,310,120),-1,3);
      controller.onMouseDown(info(150,100));controller.onMouseUp(info(250,100));
      expect(radio.getSelectedIndex()).toBe(0);
      controller.onMouseUp(info(150,100));expect(radio.getSelectedIndex()).toBe(0);
      controller.onMouseDown(info(150,100));controller.onMouseUp(info(150,100));
      expect(radio.getSelectedIndex()).toBe(1);
      const checkbox=new Checkbox(controller,new pdg.Rect(10,150,150,180));
      controller.onMouseDown(info(20,160));controller.onMouseUp(info(350,160));
      expect(checkbox.isChecked()).toBe(false);
    });
    it("stops scrollbar repeat when released outside", function() {
      const {controller,info}=fixture();
      const bar=new Scrollbar(controller,new pdg.Rect(350,10,370,210),ScrollbarOrientation.VERTICAL,20,10,100);
      controller.onMouseDown(info(360,200));
      expect(bar.scrollDownClicked).toBe(true);
      controller.onMouseMove(info(450,250));controller.onMouseUp(info(450,250));
      expect(bar.scrollDownClicked).toBe(false);
      bar.destroy();
    });
  });

  describe("Checkbox", function() {

    it("should use the C++ default text size, style, and font-metric layout", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      controller.port.getCurrentFont = () => ({
        getFontAscent: () => 12,
        getFontCapHeight: () => 9,
        getFontDescent: () => 3
      });
      let textCall = null;
      controller.port.drawText = (text, point, attributes) => {
        textCall = { text, point, attributes };
      };
      const checkbox = new Checkbox(controller, new pdg.Rect(50, 100, 350, 132));

      expect(checkbox.getTextSize()).toEqual(16);
      checkbox.setString('Default checkbox');
      checkbox.drawSelf();

      expect(checkbox.getViewArea().bottom).toEqual(120);
      expect(textCall.point.x).toEqual(69);
      expect(textCall.point.y).toEqual(115);
      expect(textCall.attributes.getTextSize()).toEqual(16);
      expect(textCall.attributes.getTextStyle()).toEqual(1);
    });

    it("should draw a bold checkmark spanning most of the larger box", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const checkbox = new Checkbox(controller, new pdg.Rect(50,100,150,125));
      let mark = null;
      controller.port.drawPolygon = (polygon) => { mark = polygon; };
      checkbox.drawCheckmark(new pdg.Rect(50,105,64,119), new pdg.Color(0,0,0,1));
      expect(mark.getPointCount()).toBe(6);
      expect(mark.getBounds().width()).toBeGreaterThan(11);
      expect(mark.getBounds().height()).toBeGreaterThan(11);
    });

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

  describe("Control input and cap-height alignment", function() {
    it("keeps disabled radio selection unchanged for pointer, key, and direct clicks", function() {
      const app = new TestApplication(), controller = new TestController(app,app.graphicsMgr.getMainPort());
      const radio = new RadioButton(controller,new pdg.Rect(10,10,310,50),-1,3);
      let clicks=0;
      radio.setAttributes(new ControlAttributes().clickRoutine(()=>++clicks));
      radio.setEnabled(false);
      const info={mousePos:new pdg.Point(150,30),lastClickElapsed:1000};
      controller.onMouseDown(info);controller.onMouseUp(info);
      radio.doClick(1);radio.doKeyPress({keyCode:40});
      expect(radio.getSelectedIndex()).toBe(0);expect(clicks).toBe(0);
    });
    it("aligns the radio circle to the label capitals and greys its disabled dot", function() {
      const app = new TestApplication(), controller = new TestController(app,app.graphicsMgr.getMainPort());
      controller.port.getCurrentFont=()=>({getFontCapHeight:()=>10});
      let circle, text, dot;
      controller.port.drawEllipse=(center,x,y)=>{if (!circle) circle={center,x,y};};
      controller.port.drawCircle=(center,radius,attrs)=>{dot=attrs.getFillColor();};
      controller.port.drawText=(value,point)=>{if (!text) text=point;};
      const radio = new RadioButton(controller,new pdg.Rect(10,10,310,50),-1,3);
      radio.setEnabled(false);radio.drawSelf();
      expect(circle.x).toBe(circle.y);expect(circle.x*2+1).toBe(14);
      expect(text.y-circle.center.y).toBe(5);
      expect(dot.red).toBeGreaterThan(.5);expect(dot.red).toEqual(dot.green);
    });
    it("scrolls vertically in both directions, clamps, notifies, and respects disabled state", function() {
      const app=new TestApplication(), controller=new TestController(app,app.graphicsMgr.getMainPort());
      const bar=new Scrollbar(controller,new pdg.Rect(10,10,26,210),ScrollbarOrientation.VERTICAL,20,10,100);
      let notices=0;bar.addObserver({notify:()=>++notices});
      expect(bar.doScrollWheel({vertDelta:3,horizDelta:0})).toBe(true);
      expect(bar.getCurrentPosition()).toBe(23);
      bar.doScrollWheel({vertDelta:-100,horizDelta:0});expect(bar.getCurrentPosition()).toBe(0);
      expect(bar.doScrollWheel({vertDelta:-1,horizDelta:0})).toBe(false);
      bar.setEnabled(false);expect(bar.doScrollWheel({vertDelta:10,horizDelta:0})).toBe(false);
      expect(bar.getCurrentPosition()).toBe(0);expect(notices).toBe(2);
      bar.destroy();
    });
  });

  describe("Dialog", function() {

    it("should create a themeable background view", function() {
      const app = new TestApplication();
      const controller = new ThemedController(app, app.graphicsMgr.getMainPort());
      const drawRoutine = () => {};
      controller.themeFactory = (type) => type === ControlType.Dialog
        ? new ControlAttributes().stateDrawRoutine(ControlState.Normal, drawRoutine)
        : new ControlAttributes();

      const dialog = new Dialog(controller, 300, 200, DialogFlags.dialog_Standard, 1, 2);

      expect(dialog.backgroundView).not.toBe(null);
      expect(dialog.backgroundView.attributes.state(ControlState.Normal).drawRoutine).toBe(drawRoutine);
      expect(dialog.getDialogRect().width()).toEqual(300);
      expect(dialog.getDialogRect().height()).toEqual(200);
      expect(dialog.getDialogRect().left).toEqual(250);
      expect(dialog.getDialogRect().top).toEqual(200);
      expect(dialog.backgroundView.getViewArea().left).toEqual(249);
      expect(dialog.backgroundView.getViewArea().top).toEqual(199);
      expect(dialog.backgroundView.getViewArea().width()).toEqual(302);
      expect(dialog.backgroundView.getViewArea().height()).toEqual(202);
      expect(dialog.backgroundView.getPartClicked(new pdg.Point(260, 210))).toEqual(1);
    });

    it("should keep all four default dialog borders inside its viewport", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const dialog = new Dialog(controller, 300, 200, DialogFlags.dialog_Standard, 1, 2);
      const draws = [];
      const port = { drawRect: (area, attributes) => draws.push({ area, attributes }) };

      dialog.backgroundView.drawSelf(port);

      expect(draws.length).toEqual(2);
      expect(draws[0].area).toEqual(dialog.backgroundView.getViewArea());
      expect(draws[1].area).toEqual(new pdg.Rect(dialog.backgroundView.getViewArea()).shrink(.5));
    });

    it("should reactivate its parent after closing", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const dialog = new Dialog(controller, 300, 200, DialogFlags.dialog_Standard, 1, 2);
      const mouseDownHandler = dialog.mouseDownHandler;
      const originalCancel = mouseDownHandler.cancel.bind(mouseDownHandler);
      let mouseDownCancelled = false;
      mouseDownHandler.cancel = () => {
        mouseDownCancelled = true;
        originalCancel();
      };

      expect(controller.isActive()).toBe(false);
      expect(controller.children).toContain(dialog);
      expect(dialog.onMouseDown({
        mousePos: new pdg.Point(10, 10),
        rightButton: false,
        lastClickElapsed: 1000
      })).toBe(true);
      expect(dialog.doLeftClick({}, null, -1, -1)).toBe(true);
      expect(controller.children).toContain(dialog);
      expect(controller.isActive()).toBe(false);

      dialog.doClose(false);

      expect(mouseDownCancelled).toBe(true);
      expect(controller.isActive()).toBe(true);
      expect(controller.children).not.toContain(dialog);
      expect(() => dialog.doClose(false)).not.toThrow();
    });

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

    it("should use numeric timer IDs for mouse press repeat handling", function() {
      const app = new TestApplication();
      const started = [];
      const cancelled = [];
      app.timerMgr.startTimer = (id, delay, oneShot) => {
        if (typeof id !== 'number') throw new TypeError('timer id must be numeric');
        started.push({ id, delay, oneShot });
      };
      app.timerMgr.cancelTimer = (id) => {
        if (typeof id !== 'number') throw new TypeError('timer id must be numeric');
        cancelled.push(id);
      };
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const scrollbar = new Scrollbar(controller, new pdg.Rect(0, 0, 200, 20),
        ScrollbarOrientation.HORIZONTAL, 35, 10, 110);

      scrollbar.doMouseDown({ mousePos: new pdg.Point(195, 10) }, 0,
        ScrollbarClickIDs.CLICK_ID_SCROLL_UP);
      expect(started.length).toEqual(1);
      expect(started[0].id).toEqual(scrollbar.scrollUpTimerID);
      expect(started[0].oneShot).toBe(false);

      // Releasing outside the original part must still stop the active timer.
      scrollbar.doMouseUp({ mousePos: new pdg.Point(250, 10) }, 0, -1);
      expect(cancelled).toEqual([scrollbar.scrollUpTimerID]);
    });

    it("should pass orientation as style and use themed image dimensions", function() {
      const app = new TestApplication();
      const controller = new ThemedController(app, app.graphicsMgr.getMainPort());
      const decrement = { width: 13, height: 9 };
      const increment = { width: 17, height: 9 };
      controller.themeFactory = () => new ControlAttributes()
        .stateImage(ControlState.Decrement, decrement)
        .stateImage(ControlState.Increment, increment);

      const scrollbar = new Scrollbar(controller, new pdg.Rect(0, 0, 200, 20),
        ScrollbarOrientation.HORIZONTAL, 0, 10, 100);

      expect(controller.requestedControls[0]).toEqual({
        type: ControlType.Scrollbar,
        styleId: ScrollbarOrientation.HORIZONTAL
      });
      expect(scrollbar.decrementExtent()).toEqual(13);
      expect(scrollbar.incrementExtent()).toEqual(17);
      scrollbar.scrollUp();
      expect(scrollbar.getCurrentPosition()).toEqual(1);
      scrollbar.scrollDown();
      expect(scrollbar.getCurrentPosition()).toEqual(0);
    });

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

    it("should recognize and drag the thumb in global coordinates", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const scrollbar = new Scrollbar(controller, new pdg.Rect(55, 402, 370, 424),
        ScrollbarOrientation.HORIZONTAL, 35, 10, 110);
      const thumb = scrollbar.getSliderRect();
      const pressPoint = new pdg.Point(thumb.left + thumb.width() / 2,
        thumb.top + thumb.height() / 2);
      const press = {
        mousePos: pressPoint,
        rightButton: false,
        lastClickElapsed: 1000
      };

      controller.onMouseDown(press);
      expect(scrollbar.scrollSliderClicked).toBe(true);

      const moved = Object.assign({}, press, {
        mousePos: new pdg.Point(pressPoint.x + 50, pressPoint.y)
      });
      controller.onMouseMove(moved);
      controller.onMouseMove(moved);
      expect(scrollbar.getCurrentPosition()).toBeGreaterThan(35);

      controller.onMouseUp(moved);
      expect(scrollbar.scrollSliderClicked).toBe(false);
    });

    it("should page a horizontal scrollbar toward the clicked track area", function() {
      const app = new TestApplication();
      const controller = new TestController(app, app.graphicsMgr.getMainPort());
      const scrollbar = new Scrollbar(controller, new pdg.Rect(55, 402, 370, 424),
        ScrollbarOrientation.HORIZONTAL, 35, 10, 110);
      let thumb = scrollbar.getSliderRect();

      scrollbar.scrollSliderAreaPressed(new pdg.Point(thumb.left - 5, thumb.top + 5));
      expect(scrollbar.getCurrentPosition()).toEqual(25);
      scrollbar.scrollSliderAreaReleased();

      scrollbar.setCurrentPosition(35);
      thumb = scrollbar.getSliderRect();
      scrollbar.scrollSliderAreaPressed(new pdg.Point(thumb.right + 5, thumb.top + 5));
      expect(scrollbar.getCurrentPosition()).toEqual(45);
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
