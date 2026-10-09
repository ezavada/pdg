import type PDG = require('../../types');
import {Application} from '../../src/typescript/mvc-app/Application';
import {Controller} from '../../src/typescript/mvc-app/Controller';
import {View} from '../../src/typescript/mvc-app/View';
import {Button} from '../../src/typescript/mvc-app/Button';
import {ControlAttributes, ControlState} from '../../src/typescript/mvc-app/ControlAttributes';
import {IObserver, Subject, Observable} from '../../src/typescript/mvc-app/Observer';

declare const port: PDG.Port;
declare const area: PDG.Rect;
const controller = new Controller(null, new Application(), port);
class GameView extends View {
    score = 0;
    drawSelf(port: PDG.Port, frameNum: number): void { this.score += 1; }
}
const view: GameView = new GameView(controller, area).moveTo(20, 30, 0.5).repeat(2);
const button = new Button(controller, area, 1);
button.setText('Start');
controller.addView(button, 1);
new ControlAttributes().stateForeground(ControlState.Normal, null);
class Listener extends IObserver { notify(subject: Observable | null): void {} }
new Subject().addObserver(new Listener());
// @ts-expect-error the controller expects a real view
controller.addView({draw: () => {}}, 2);
// @ts-expect-error draw hooks receive a port
view.drawSelf('port', 1);
// @ts-expect-error colors are not arbitrary objects
new ControlAttributes().stateForeground(ControlState.Normal, {});

const found: Button | null = controller.getView(Button, 1);
if (found) found.setText('Continue');
const owner: Controller | null = button.getController(Controller);
