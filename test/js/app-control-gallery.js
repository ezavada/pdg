// Interactive draw/behavior test for the PDG JavaScript application controls.
// Run with: test/demo mvc
// Browser: test/demo --web mvc
// Add --ui-test on desktop, or &automated=1 in the browser, for a finite check.

if (typeof pdg === 'undefined') global.pdg = require('pdg');
// Log the first three native drawText argument sets for every gallery button.
// This gallery is a diagnostic executable, so keep the evidence in its output.
global.PDG_CONTROL_DRAW_DIAGNOSTICS = { maxDrawsPerButton: automatedGalleryDiagnosticCount() };
function automatedGalleryDiagnosticCount() { return process.argv.includes("--ui-test") ? 3 : 0; }
const framework = require('../../src/js/mvc-app');
const { Application } = framework.Application;
const { Controller } = framework.Controller;
const { View } = framework.View;
const { Button } = framework.Button;
const { Checkbox } = framework.Checkbox;
const { RadioButton } = framework.RadioButton;
const { Scrollbar, ScrollbarOrientation } = framework.Scrollbar;
const { Dialog, DialogFlags } = framework.Dialog;
const { ScrollingView, ScrollingViewBindType } = framework.ScrollingView;
const { ListBox } = framework.ListBox;
const {
    ControlAttributes,
    ControlState,
    ControlType
} = framework.ControlAttributes;

const automatedGallery = process.argv.includes('--ui-test');

const ids = {
    defaultButton: 100,
    disabledButton: 101,
    themedButton: 102,
    imageButton: 103,
    defaultDialog: 104,
    themedDialog: 105
};

class GalleryCanvas extends View {
    drawSelf(port) {
        port.drawRect(this.getViewArea(), new pdg.Attributes()
            .fillColor(new pdg.Color(0.94, 0.95, 0.97, 1)));
        port.drawText('PDG JavaScript App Framework Control Gallery', new pdg.Point(40, 48),
            new pdg.Attributes().textSize(25).textStyle(pdg.textStyle_Bold)
                .fillColor(new pdg.Color(0.12, 0.15, 0.22, 1)));
        port.drawText('Hover, press, click, toggle, and open both dialogs.', new pdg.Point(40, 76),
            new pdg.Attributes().textSize(14).fillColor(new pdg.Color(0.28, 0.31, 0.36, 1)));
        port.drawRect(new pdg.Rect(30, 92, 450, 500), new pdg.Attributes()
            .fillColor(new pdg.Color(1, 1, 1, 1)).lineStyle(pdg.lineStyle_Solid).lineColor(new pdg.Color(0.73, 0.75, 0.79, 1))
            .roundedCorners(10));
        port.drawRect(new pdg.Rect(510, 92, 930, 500), new pdg.Attributes()
            .fillColor(new pdg.Color(0.98, 0.97, 1, 1)).lineStyle(pdg.lineStyle_Solid).lineColor(new pdg.Color(0.49, 0.43, 0.71, 1))
            .lineThickness(2).roundedCorners(10));
        port.drawText('Built-in defaults', new pdg.Point(50, 116),
            new pdg.Attributes().textSize(17).textStyle(pdg.textStyle_Bold).fillColor(new pdg.Color(45/255,52/255,66/255,1)));
        port.drawText('Per-control overrides', new pdg.Point(530, 116),
            new pdg.Attributes().textSize(17).textStyle(pdg.textStyle_Bold)
                .fillColor(new pdg.Color(0.29, 0.22, 0.57, 1)));
        port.drawRect(new pdg.Rect(30, 525, 930, 590), new pdg.Attributes()
            .fillColor(new pdg.Color(0.13, 0.15, 0.21, 1)).roundedCorners(8));
        port.drawText(`Behavior: ${this.controller.status}`, new pdg.Point(50, 557),
            new pdg.Attributes().textSize(16).fillColor(new pdg.Color(1, 1, 1, 1)));
        port.drawText('Overrides: state colors, image, draw routine, click routine, and dialog theme.',
            new pdg.Point(50, 580), new pdg.Attributes().textSize(12)
                .fillColor(new pdg.Color(0.75, 0.8, 0.88, 1)));
        port.drawText('Live appearance & transforms', new pdg.Point(50, 622),
            new pdg.Attributes().textSize(16).fillColor(new pdg.Color(0.2,0.24,0.32)));
        port.drawText('Clipped scrolling', new pdg.Point(340, 622),
            new pdg.Attributes().textSize(16).fillColor(new pdg.Color(0.2,0.24,0.32)));
        port.drawText('Resizing composite list', new pdg.Point(640, 622),
            new pdg.Attributes().textSize(16).fillColor(new pdg.Color(0.2,0.24,0.32)));

    }
}

class DialogLabel extends View {
    constructor(controller, area, text) {
        super(controller, area);
        this.text = text;
    }

    drawSelf(port) {
        port.drawText(this.text, new pdg.Point(this.viewArea.left + 12, this.viewArea.top + 28),
            new pdg.Attributes().textSize(17).fillColor(new pdg.Color(0, 0, 0, 1)));
    }
}

class PreviewDialog extends Dialog {
    constructor(parent, themed) {
        super(parent, 360, 150, DialogFlags.dialog_Standard, 1);
        new DialogLabel(this, this.getDialogRect(), themed
            ? 'Custom draw routine for dialog background'
            : 'Default PDG dialog background');
        const area = this.getDialogRect();
        const close = new Button(this,
            new pdg.Rect(area.right - 112, area.bottom - 44, area.right - 22, area.bottom - 14), 1);
        close.setText('Close');
        close.setID(1);
    }
}

// The finite check exercises live native attributes through Port drawing,
// while Drawing continues to use snapshots. The interactive gallery stays open.
class GalleryAppearanceProbe extends View {
    constructor(controller) {
        super(controller, new pdg.Rect(465, 150, 495, 180));
        this.fillColor(new pdg.Color(1, 0, 0));
        this.changeFillColor(new pdg.Color(0, 0, 1), 0.8);
        this.changeFillOpacity(0.4, 0.8);
        this.moveBy(0, 40, 0.8, pdg.linearTween);
        this.elapsed = 0;
        this.draws = 0;
        this.sawIntermediateColor = false;
    }
    animate(seconds) {
        this.elapsed += seconds;
        return super.animate(seconds);
    }
    drawSelf(port) {
        port.drawRect(new pdg.Rect(-0.5, -0.5, 0.5, 0.5), this);
        const blue = this.getFillColor().blue;
        if (blue > 0 && blue < 1) this.sawIntermediateColor = true;
        ++this.draws;
    }
}

class ScrollingGallery extends ScrollingView {
    constructor(controller, frame) {
        super(controller,frame);
        this.setAutoAdjust(ScrollingViewBindType.bind_None);
        this.setViewArea(new pdg.Rect(frame.left,frame.top,frame.right,frame.top+360));
        this.time=0;
        this.setRotation(0.035);
    }
    animate(seconds) {
        this.time+=seconds;
        const frame=this.getViewFrame();
        this.setViewArea(new pdg.Rect(frame.left,frame.top-60*(1-Math.cos(this.time)),frame.right,frame.top+360-60*(1-Math.cos(this.time))));
        return super.animate(seconds);
    }
    drawSelf(port) {
        const area=this.getViewArea();
        // Deliberately draw beyond every viewport edge to exercise clipping.
        for (let row=0;row<12;++row) {
            const y=area.top+row*30;
            port.drawRect(new pdg.Rect(area.left-30,y,area.right+30,y+30),new pdg.Attributes()
                .fillColor(row%2 ? new pdg.Color(.78,.9,.97) : new pdg.Color(.94,.98,1)));
            port.drawText('Scrolling row '+(row+1),new pdg.Point(area.left+12,y+21),new pdg.Attributes()
                .textSize(14).fillColor(new pdg.Color(.14,.28,.4)));
        }
    }
}

class AnimatedGalleryButton extends Button {
    constructor(controller, area, id) {
        super(controller, area, id);
        this.remaining = 0;
        this.forward = false;
        this.fillColor(new pdg.Color(.18,.49,.68)).roundedCorners(4);
        this.setRotation(-.12);
    }
    animate(seconds) {
        this.remaining -= seconds;
        if (this.remaining <= 0) {
            this.forward = !this.forward;
            this.remaining = 2;
            this.rotateTo(this.forward ? .12 : -.12, 2);
            this.moveTo(new pdg.Point(this.forward ? 170 : 160,673), 2);
            this.changeFillColor(this.forward ? new pdg.Color(.46,.27,.72) : new pdg.Color(.18,.49,.68), 2);
            this.changeRoundedCorners(this.forward ? 18 : 4, 2);
        }
        return super.animate(seconds);
    }
}

class GalleryController extends Controller {
    setupViews() {
        this.status = 'Click any enabled control';
        this.useThemedDialog = false;
        this.canvas = new GalleryCanvas(this, this.port.getDrawingArea());

        this.defaultButton = this.addButton(new pdg.Rect(55, 125, 225, 165), ids.defaultButton, 'Default button');
        const disabled = this.addButton(new pdg.Rect(55, 180, 225, 220), ids.disabledButton, 'Disabled');
        disabled.setEnabled(false);

        const themedButton = new ControlAttributes()
            .stateDrawRoutine(ControlState.Normal, GalleryController.drawAccentButton)
            .stateDrawRoutine(ControlState.Hovered, GalleryController.drawAccentButton)
            .stateDrawRoutine(ControlState.Pressed, GalleryController.drawPressedAccentButton)
            .stateForeground(ControlState.Normal, new pdg.Color(1, 1, 1, 1))
            .stateForeground(ControlState.Hovered, new pdg.Color(1, 1, 1, 1))
            .stateForeground(ControlState.Pressed, new pdg.Color(1, 1, 1, 1))
            .clickRoutine(() => { this.status = 'Custom button click routine ran'; });
        this.addButton(new pdg.Rect(535, 125, 705, 165), ids.themedButton, 'Draw routine', themedButton);

        let exampleImage = null;
        try { exampleImage = this.app.getResourceManager().getImage('wood-brass-button.png'); } catch (_) {}
        this.exampleImageLoaded = !!exampleImage;
        const imageButton = new ControlAttributes();
        for (const [state, overlay] of [
            [ControlState.Normal, new pdg.Color(0,0,0,0)],
            [ControlState.Hovered, new pdg.Color(1,.8,.35,.12)],
            [ControlState.Pressed, new pdg.Color(0,0,0,.28)],
            [ControlState.Disabled, new pdg.Color(.65,.65,.65,.65)]]) {
            imageButton.stateImage(state, exampleImage)
                .stateAttributes(state, new pdg.Attributes().fillColor(overlay))
                .stateForeground(state, new pdg.Color(1,.92,.7,1));
        }
        this.addButton(new pdg.Rect(730, 125, 900, 165), ids.imageButton, 'Image state', imageButton);

        this.addCheckbox(new pdg.Rect(55, 245, 360, 277), 'Default checkbox');
        const disabledCheck = this.addCheckbox(new pdg.Rect(55, 277, 360, 309), 'Disabled checkbox');
        disabledCheck.setEnabled(false);
        this.addCheckbox(new pdg.Rect(535, 245, 850, 277), 'Override text colors',
            new ControlAttributes()
                .stateForeground(ControlState.Normal, new pdg.Color(0.18, 0.27, 0.55, 1))
                .stateForeground(ControlState.Selected, new pdg.Color(0.64, 0.19, 0.36, 1))
                .clickRoutine(() => { this.status = 'Custom checkbox toggled'; }));

        this.addRadio(new pdg.Rect(55, 315, 370, 345));
        const disabledRadio = this.disabledRadio = this.addRadio(new pdg.Rect(55, 355, 370, 385));
        disabledRadio.setEnabled(false);
        this.addRadio(new pdg.Rect(535, 315, 850, 345), new ControlAttributes()
            .stateForeground(ControlState.Normal, new pdg.Color(0.14, 0.37, 0.28, 1))
            .stateForeground(ControlState.Selected, new pdg.Color(0.75, 0.29, 0.12, 1))
            .clickRoutine(() => { this.status = 'Custom radio selection changed'; }));

        new Scrollbar(this, new pdg.Rect(55, 402, 370, 424),
            ScrollbarOrientation.HORIZONTAL, 35, 10, 110);
        const themedScrollbar = new Scrollbar(this, new pdg.Rect(535, 402, 850, 424),
            ScrollbarOrientation.HORIZONTAL, 65, 10, 110);
        themedScrollbar.setAttributes(new ControlAttributes()
            .stateAttributes(ControlState.Normal, new pdg.Attributes().fillColor(new pdg.Color(0.88, 0.85, 0.96, 1)))
            .stateAttributes(ControlState.Decrement, new pdg.Attributes().fillColor(new pdg.Color(0.53, 0.47, 0.81, 1)).roundedCorners(4))
            .stateAttributes(ControlState.Increment, new pdg.Attributes().fillColor(new pdg.Color(0.53, 0.47, 0.81, 1)).roundedCorners(4))
            .stateAttributes(ControlState.Thumb, new pdg.Attributes().fillColor(new pdg.Color(0.64, 0.19, 0.36, 1)).roundedCorners(6)));

        this.addButton(new pdg.Rect(55, 447, 255, 487), ids.defaultDialog, 'Open default dialog');
        this.addButton(new pdg.Rect(535, 447, 735, 487), ids.themedDialog, 'Open themed dialog', themedButton);
        this.animatedButton = new AnimatedGalleryButton(this, new pdg.Rect(55,654,265,692), 106);
        this.animatedButton.setID(106);
        this.animatedButton.setText('Animated — click me');
        this.reflectedButton=this.addButton(new pdg.Rect(55,727,265,765),107,'Reflected — click me');
        this.reflectedButton.setFlipX(true);
        this.scrolling=new ScrollingGallery(this,new pdg.Rect(330,642,590,792));
        this.list=new ListBox(this,new pdg.Rect(640,650,895,780),4,new pdg.Color(1,1,1),new pdg.Color(.7,.84,1));
        ['Alpha','Bravo','Charlie','Delta','Echo','Foxtrot','Golf','Hotel'].forEach(text=>this.list.addToList(text,new pdg.Color(.15,.2,.3)));
        this.list.createScrollbar();
        this.list.setRotation(-.035);
        this.list.resizeTo(230,130,1,pdg.linearTween);
        global.pdgMvcGallery=this;
        if (automatedGallery) {
            this.appearanceProbe = new GalleryAppearanceProbe(this);
            this.defaultButton.moveBy(48, 0, 0.8, pdg.linearTween);
        }
    }

    onPortDraw(event) {
        super.onPortDraw(event);
        const probe = this.appearanceProbe;
        if (!probe || this.testFinished || probe.elapsed < 1.2 || probe.draws < 12) return false;
        this.testFinished = true;
        const near = (a, b) => Math.abs(a - b) < 0.001;
        const passed = probe instanceof GalleryAppearanceProbe && probe instanceof pdg.AnimatedAttributes &&
            !('physics' in probe) && this.exampleImageLoaded && probe.sawIntermediateColor &&
            near(probe.getFillColor().blue, 1) && near(probe.getFillOpacity(), 0.4) &&
            near(probe.getViewArea().top, 190) && near(this.defaultButton.getViewArea().left, 103) &&
            this.defaultButton.getPartClicked(this.defaultButton.getViewArea().centerPoint())===this.defaultButton.buttonID &&
            this.animatedButton.getPartClicked(this.animatedButton.localToGlobal(new pdg.Point(40,18)))===106 &&
            this.reflectedButton.getPartClicked(this.reflectedButton.localToGlobal(new pdg.Point(40,18)))===107 &&
            this.list.scrollbar.getParentView()===this.list && near(this.list.getWidth(),230);
        global.pdgControlGalleryTest = { passed, draws: probe.draws,
            intermediateColor: probe.sawIntermediateColor,
            fillOpacity: probe.getFillOpacity(), buttonLeft: this.defaultButton.getViewArea().left };
        console.log('CONTROL GALLERY ' + (passed ? 'PASS: ' : 'FAIL: ') + JSON.stringify(global.pdgControlGalleryTest));
        setTimeout(() => { this.app.cleanup(); process.exit(passed ? 0 : 1); }, 0);
        return false;
    }

    addButton(area, id, text, attributes = null) {
        const button = new Button(this, area, id);
        button.setText(text);
        button.setID(id);
        if (attributes) button.setAttributes(attributes);
        return button;
    }

    addCheckbox(area, text, attributes = null) {
        const checkbox = new Checkbox(this, area);
        checkbox.setString(text);
        if (attributes) checkbox.setAttributes(attributes);
        return checkbox;
    }

    addRadio(area, attributes = null) {
        const radio = new RadioButton(this, area, -1, 3);
        radio.setString(0, 'One');
        radio.setString(1, 'Two');
        radio.setString(2, 'Three');
        if (attributes) radio.setAttributes(attributes);
        return radio;
    }

    getControlAttributes(type) {
        const attributes = new ControlAttributes();
        if (this.useThemedDialog && type === ControlType.Dialog) {
            attributes.stateDrawRoutine(ControlState.Normal, (port, area) => {
                port.drawRect(new pdg.Rect(area).shrink(2.5), new pdg.Attributes()
                    .fillGradient(area.leftTop(), new pdg.Color(244 / 255, 236 / 255, 1, 1),
                        area.rightBottom(), new pdg.Color(178 / 255, 211 / 255, 1, 1))
                    .lineStyle(pdg.lineStyle_Solid).lineColor(new pdg.Color(74 / 255, 57 / 255, 145 / 255, 1))
                    .lineThickness(5).roundedCorners(12));
            });
        }
        return attributes;
    }

    buttonClicked(id) {
        if (id === ids.defaultDialog || id === ids.themedDialog) {
            this.useThemedDialog = id === ids.themedDialog;
            new PreviewDialog(this, this.useThemedDialog);
            this.useThemedDialog = false;
        } else if (id !== ids.themedButton) {
            this.status = `Button ${id} clicked`;
        }
    }

    static drawAccentButton(port, area, state) {
        port.drawRect(area, new pdg.Attributes()
            .fillGradient(area.leftTop(), new pdg.Color(94 / 255, 86 / 255, 220 / 255, 1),
                area.rightBottom(), new pdg.Color(38 / 255, 167 / 255, 190 / 255, 1))
            .lineStyle(pdg.lineStyle_Solid).lineColor(new pdg.Color(30 / 255, 30 / 255, 80 / 255, 1))
            .lineThickness(2).roundedCorners(10).withAppearance(state.drawing || new pdg.Attributes()));
    }

    static drawPressedAccentButton(port, area, state) {
        port.drawRect(area, new pdg.Attributes()
            .fillColor(new pdg.Color(42 / 255, 83 / 255, 135 / 255, 1))
            .lineStyle(pdg.lineStyle_Solid).lineColor(new pdg.Color(1, 1, 1, 1)).lineThickness(2).roundedCorners(10).withAppearance(state.drawing || new pdg.Attributes()));
    }
}

class GalleryApplication extends Application {
    setupGraphics() {
        const bounds = pdg.gfx.getScreenBounds();
        const frame = new pdg.Rect(0, 0, 960, 840);
        frame.center(bounds);
        this.mainPort = pdg.gfx.createWindowPort(frame, 'PDG MVC Gallery', 0);
    }

    preloadResources() {
        this.resourceMgr.openResourceFile('test/data');
    }

    setupControllers() {
        this.mainController = new GalleryController(null, this, this.mainPort);
    }

    cleanup() {
        if (this.mainController) this.mainController.destroy();
        if (this.mainPort) pdg.gfx.closeGraphicsPort(this.mainPort);
    }
}

new GalleryApplication();
