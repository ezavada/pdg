// Interactive draw/behavior test for the PDG JavaScript application controls.
// Run with: ./pdg test/js/app-control-gallery.js

if (typeof pdg === 'undefined') global.pdg = require('pdg');
// Log the first three native drawText argument sets for every gallery button.
// This gallery is a diagnostic executable, so keep the evidence in its output.
global.PDG_CONTROL_DRAW_DIAGNOSTICS = { maxDrawsPerButton: 3 };
const framework = require('../../src/js/mvc-app');
const { Application } = framework.Application;
const { Controller } = framework.Controller;
const { View } = framework.View;
const { Button } = framework.Button;
const { Checkbox } = framework.Checkbox;
const { RadioButton } = framework.RadioButton;
const { Scrollbar, ScrollbarOrientation } = framework.Scrollbar;
const { Dialog, DialogFlags } = framework.Dialog;
const {
    ControlAttributes,
    ControlState,
    ControlType
} = framework.ControlAttributes;

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
            .fillColor(new pdg.Color(1, 1, 1, 1)).lineColor(new pdg.Color(0.73, 0.75, 0.79, 1))
            .roundedCorners(10));
        port.drawRect(new pdg.Rect(510, 92, 930, 500), new pdg.Attributes()
            .fillColor(new pdg.Color(0.98, 0.97, 1, 1)).lineColor(new pdg.Color(0.49, 0.43, 0.71, 1))
            .lineThickness(2).roundedCorners(10));
        port.drawText('Built-in defaults', new pdg.Point(50, 116),
            new pdg.Attributes().textSize(17).textStyle(pdg.textStyle_Bold));
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

class GalleryController extends Controller {
    setupViews() {
        this.status = 'Click any enabled control';
        this.useThemedDialog = false;
        this.canvas = new GalleryCanvas(this, this.port.getDrawingArea());

        this.addButton(new pdg.Rect(55, 125, 225, 165), ids.defaultButton, 'Default button');
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
        try { exampleImage = this.app.getResourceManager().getImage('yinyang.png'); } catch (_) {}
        const imageButton = new ControlAttributes()
            .stateImage(ControlState.Normal, exampleImage)
            .stateForeground(ControlState.Normal, new pdg.Color(1, 1, 1, 1));
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
        const disabledRadio = this.addRadio(new pdg.Rect(55, 355, 370, 385));
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
                port.drawRect(area, new pdg.Attributes()
                    .fillGradient(area.leftTop(), new pdg.Color(244 / 255, 236 / 255, 1, 1),
                        area.rightBottom(), new pdg.Color(178 / 255, 211 / 255, 1, 1))
                    .lineColor(new pdg.Color(74 / 255, 57 / 255, 145 / 255, 1))
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

    static drawAccentButton(port, area) {
        port.drawRect(area, new pdg.Attributes()
            .fillGradient(area.leftTop(), new pdg.Color(94 / 255, 86 / 255, 220 / 255, 1),
                area.rightBottom(), new pdg.Color(38 / 255, 167 / 255, 190 / 255, 1))
            .lineColor(new pdg.Color(30 / 255, 30 / 255, 80 / 255, 1))
            .lineThickness(2).roundedCorners(10));
    }

    static drawPressedAccentButton(port, area) {
        port.drawRect(area, new pdg.Attributes()
            .fillColor(new pdg.Color(42 / 255, 83 / 255, 135 / 255, 1))
            .lineColor(new pdg.Color(1, 1, 1, 1)).lineThickness(2).roundedCorners(10));
    }
}

class GalleryApplication extends Application {
    setupGraphics() {
        const bounds = pdg.gfx.getScreenBounds();
        const frame = new pdg.Rect(0, 0, 960, 640);
        frame.center(bounds);
        this.mainPort = pdg.gfx.createWindowPort(frame, 'PDG JavaScript Control Gallery', 0);
    }

    preloadResources() {
        this.resourceMgr.openResourceFile('test');
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
