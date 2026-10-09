require('./SpecHelper');

// Only the separate TypeScript implementation owns these port-specific checks.
if (process.env.PDG_MVC_MODULE) {
    const mvc = require(process.env.PDG_MVC_MODULE);
    const {Application} = mvc.Application;
    const {Controller} = mvc.Controller;
    const {View} = mvc.View;
    const {MessageDialog, MessageDialogViewIDs} = mvc.MessageDialog;
    class App extends Application { _initialize() {} }
    describe('TypeScript MVC implementation', function() {
        let app, controller, port;
        beforeEach(function() {
            app = new App();
            port = pdg.gfx.createOffscreenPort(new pdg.Rect(640,480));
            controller = new Controller(null,app,port);
        });
        afterEach(function() {
            controller.destroy();
            app._unregisterEventHandlers();
            pdg.gfx.closeGraphicsPort(port);
        });
        it('keeps drag and hover accessors callable after construction', function() {
            const view = new View(controller,new pdg.Rect(20,20));
            expect(view.isDraggable()).toBe(false);
            view.setDraggable(true);
            view.setWantsMouseOvers(true);
            expect(view.isDraggable()).toBe(true);
            expect(view.wantsMouseOvers()).toBe(true);
        });
        it('builds message dialog buttons with text and valid bounds', function() {
            const dialog = MessageDialog.createYesNoDialog(controller,'Play again?');
            try {
                const first = dialog.getUntypedView(MessageDialogViewIDs.VIEW_ID_BUTTON_1);
                const second = dialog.getUntypedView(MessageDialogViewIDs.VIEW_ID_BUTTON_2);
                expect(first.getText()).toBe('Yes');
                expect(second.getText()).toBe('No');
                expect(first.getViewArea().width()).toBe(80);
                expect(second.getViewArea().height()).toBe(30);
                let resolved = false;
                dialog.resolvePromise = function() { resolved = true; };
                controller.attemptChildClose = function() { return false; };
                dialog.doClose(false);
                expect(resolved).toBe(false);
                controller.attemptChildClose = function() { return true; };
                dialog.doClose(false);
                expect(resolved).toBe(true);
            } finally { if (dialog.parentController) dialog.destroy(); }
        });
        it('handles native numeric modal events', function() {
            const modal = new mvc.ModalController.ModalController(controller);
            let escapes = 0;
            modal.handleEscapeKey = function() { escapes++; };
            try {
                expect(modal.handleModalEvents(pdg.eventType_KeyPress, {keyCode:27})).toBe(true);
                expect(escapes).toBe(1);
            } finally { modal.destroy(); }
        });
    });
}

if (process.env.PDG_MVC_MODULE) {
    describe('TypeScript MVC native event boundary', function() {
        const mvc = require(process.env.PDG_MVC_MODULE);
        class App extends mvc.Application.Application { _initialize() {} }
        it('registers catch-all events using a native handler and cancels it', function() {
            const app = new App(), port = pdg.gfx.createOffscreenPort(new pdg.Rect(100,100));
            let controller;
            try {
                controller = new mvc.Controller.Controller(null,app,port,false,false,false,true);
                expect(controller.allEventsHandler instanceof pdg.IEventHandler).toBe(true);
                controller._unregisterEventHandlers();
                expect(controller.allEventsHandler).toBe(null);
            } finally {
                if (controller) controller.destroy();
                app._unregisterEventHandlers();
                pdg.gfx.closeGraphicsPort(port);
            }
        });
        it('normalizes native unicode keypress input for control hooks', function() {
            const app = new App(), port = pdg.gfx.createOffscreenPort(new pdg.Rect(100,100));
            const original = pdg.onKeyPress;
            let callback, controller, received;
            pdg.onKeyPress = function(handler) { callback = handler; return original(handler); };
            try {
                controller = new mvc.Controller.Controller(null,app,port,false,true,false,false);
                controller.onKeyPress = function(event) { received = event; return true; };
                expect(callback({unicode:0x1f600})).toBe(true);
                expect(received.key).toBe(String.fromCodePoint(0x1f600));
                expect(received.keyCode).toBe(0x1f600);
            } finally {
                pdg.onKeyPress = original;
                if (controller) controller.destroy();
                app._unregisterEventHandlers();
                pdg.gfx.closeGraphicsPort(port);
            }
        });
    });
}
