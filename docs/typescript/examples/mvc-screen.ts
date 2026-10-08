import type pdg = require('../../../types');
import { Application } from '../../../src/typescript/mvc-app/Application';
import { Controller } from '../../../src/typescript/mvc-app/Controller';
import { Button } from '../../../src/typescript/mvc-app/Button';

/** Call after PDG initializes. Supply a graphical port and button rectangle. */
export function createScreen(port: pdg.Port, buttonArea: pdg.Rect): Controller {
    const application = new Application();
    const controller = new Controller(null, application, port);
    const button = new Button(controller, buttonArea, 1);
    button.setText('Start');
    controller.addView(button, 1);
    button.moveTo(160, 100, 0.4).yoyo().repeat(2);
    return controller; // Call controller.destroy() when the screen closes.
}
