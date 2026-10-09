import type PDG = require('../../../types');
import type { DrawRoutine } from './engine';
import { engine } from './engine';

// -----------------------------------------------
// ControlAttributes.ts
//
// Application-control styling and behavior
// -----------------------------------------------

const ControlState = Object.freeze({
    Normal: 0,
    Hovered: 1,
    Pressed: 2,
    Disabled: 3,
    Selected: 4,
    SelectedDisabled: 5,
    Decrement: 6,
    DecrementPressed: 7,
    Increment: 8,
    IncrementPressed: 9,
    Thumb: 10,
    Count: 11
});

const ControlType = Object.freeze({
    Dialog: 0,
    Button: 1,
    Checkbox: 2,
    RadioButton: 3,
    Scrollbar: 4,
    Other: 5
});

class ControlStateAttributes {
    drawing: PDG.Attributes | null;
    image: PDG.Image | null;
    foreground: PDG.Color | null;
    drawRoutine: DrawRoutine | null;
    hasDrawing: boolean;
    hasImage: boolean;
    hasForeground: boolean;
    hasDrawRoutine: boolean;

    constructor() {
        this.drawing = null;
        this.image = null;
        this.foreground = null;
        this.drawRoutine = null;
        this.hasDrawing = false;
        this.hasImage = false;
        this.hasForeground = false;
        this.hasDrawRoutine = false;
    }

    drawAttributes(value: PDG.Attributes | null): this {
        this.drawing = value;
        this.hasDrawing = true;
        return this;
    }

    backgroundImage(value: PDG.Image | null): this {
        this.image = value;
        this.hasImage = true;
        return this;
    }

    foregroundColor(value: PDG.Color | null): this {
        this.foreground = value;
        this.hasForeground = true;
        return this;
    }

    customDraw(value: DrawRoutine | null): this {
        this.drawRoutine = value;
        this.hasDrawRoutine = true;
        return this;
    }

    merge(overrides: ControlStateAttributes | null): this {
        if (!overrides) return this;

        // Match the C++ precedence rules. These are alternative background
        // sources; drawing attributes may additionally modify an image or be
        // inspected by a custom draw routine.
        if (overrides.hasDrawRoutine) {
            this.drawRoutine = overrides.drawRoutine;
            this.hasDrawRoutine = true;
            this.image = null;
            this.hasImage = false;
            this.drawing = null;
            this.hasDrawing = false;
        } else if (overrides.hasImage) {
            this.backgroundImage(overrides.image);
            this.drawRoutine = null;
            this.hasDrawRoutine = false;
            if (!overrides.hasDrawing) {
                this.drawing = null;
                this.hasDrawing = false;
            }
        } else if (overrides.hasDrawing) {
            this.drawAttributes(overrides.drawing);
            this.image = null;
            this.hasImage = false;
            this.drawRoutine = null;
            this.hasDrawRoutine = false;
        }

        if (overrides.hasDrawing && (overrides.hasImage || overrides.hasDrawRoutine)) {
            this.drawAttributes(overrides.drawing);
        }
        if (overrides.hasForeground) this.foregroundColor(overrides.foreground);
        return this;
    }
}

class ControlAttributes {
    states: ControlStateAttributes[];
    _clickSound: PDG.Sound | null;
    _clickVolume: number;
    _clickRoutine: (() => void) | null;
    _hasClickSound: boolean;
    _hasClickRoutine: boolean;

    constructor() {
        this.states = Array.from(
            { length: ControlState.Count },
            () => new ControlStateAttributes()
        );
        this._clickSound = null;
        this._clickVolume = 1.0;
        this._clickRoutine = null;
        this._hasClickSound = false;
        this._hasClickRoutine = false;
    }

    state(value: number): ControlStateAttributes {
        if (!Number.isInteger(value) || value < 0 || value >= ControlState.Count) {
            throw new RangeError(`Invalid control state: ${value}`);
        }
        return this.states[value];
    }

    stateAttributes(state: number, value: PDG.Attributes | null): this {
        this.state(state).drawAttributes(value);
        return this;
    }

    stateImage(state: number, value: PDG.Image | null): this {
        this.state(state).backgroundImage(value);
        return this;
    }

    stateForeground(state: number, value: PDG.Color | null): this {
        this.state(state).foregroundColor(value);
        return this;
    }

    stateDrawRoutine(state: number, value: DrawRoutine | null): this {
        this.state(state).customDraw(value);
        return this;
    }

    clickSound(value: PDG.Sound | null, volume: number = 1.0): this {
        this._clickSound = value;
        this._clickVolume = volume;
        this._hasClickSound = true;
        return this;
    }

    clickRoutine(value: (() => void) | null): this {
        this._clickRoutine = value;
        this._hasClickRoutine = true;
        return this;
    }

    getClickSound() { return this._clickSound; }
    getClickVolume(): number { return this._clickVolume; }
    hasClickSound(): boolean { return this._hasClickSound; }
    hasClickRoutine(): boolean { return this._hasClickRoutine; }

    merge(overrides: ControlAttributes | null): this {
        if (!overrides) return this;
        for (let i = 0; i < ControlState.Count; ++i) {
            this.states[i].merge(overrides.states[i]);
        }
        if (overrides._hasClickSound) {
            this.clickSound(overrides._clickSound, overrides._clickVolume);
        }
        if (overrides._hasClickRoutine) {
            this.clickRoutine(overrides._clickRoutine);
        }
        return this;
    }

    draw(port: PDG.Port, area: PDG.Rect, state: number, appearance: PDG.Attributes | null = null): void {
        const selected = this.state(state);
        const normal = this.state(ControlState.Normal);
        let visual = this._drawableState(selected) ? selected
            : (selected !== normal && this._drawableState(normal) ? normal : null);
        if (!visual) return;
        if (appearance) {
            const composed = Object.assign(new ControlStateAttributes(), visual);
            composed.drawAttributes((visual.hasDrawing && visual.drawing ? visual.drawing : new engine.Attributes()).withAppearance(appearance));
            visual = composed;
        }

        if (visual.hasDrawRoutine && visual.drawRoutine) {
            visual.drawRoutine(port, area, visual);
        } else if (visual.hasImage && visual.image) {
            port.drawImage(
                visual.image,
                area,
                visual.hasDrawing && visual.drawing ? visual.drawing : new engine.Attributes()
            );
        } else if (visual.hasDrawing && visual.drawing) {
            // A centered stroke must stay inside the control viewport.
            const inset = visual.drawing.getLineStyle() !== engine.lineStyle_None ? visual.drawing.getLineThickness()/2 : 0;
            port.drawRect(new engine.Rect(area).shrink(inset), visual.drawing);
        }
    }

    playClick(): void {
        if (this._hasClickRoutine && this._clickRoutine) {
            this._clickRoutine();
        } else if (this._hasClickSound && this._clickSound) {
            this._clickSound.play(this._clickVolume);
        }
    }

    _drawableState(state: ControlStateAttributes) {
        return (state.hasDrawRoutine && !!state.drawRoutine) ||
            (state.hasImage && !!state.image) || state.hasDrawing;
    }
}

export {
ControlAttributes,ControlState,ControlStateAttributes,ControlType
};
