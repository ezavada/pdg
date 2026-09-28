// Shared interactive controls, installed before a visual script starts.
// Each page runs in its own runtime so event handlers, layers and ports cannot
// leak into the next page. No engine API or production clock is changed.
exports.install = function(pdg, options) {
    var clock = Date.now;
    var pausedAt = 0, skipped = 0, timerWasPaused = false;
    // The browser adds JS timers on the singleton; its native timer manager
    // still drives sprite physics. Pause both using their existing APIs.
    var nativeTimers = pdg.TimerManager && pdg.TimerManager.prototype;
    var separateNativeTimers = nativeTimers && typeof nativeTimers.pause === 'function' &&
        typeof nativeTimers.unpause === 'function' && typeof nativeTimers.isPaused === 'function' &&
        nativeTimers.pause !== pdg.tm.pause;
    var nativeWasPaused = false;
    var session = {paused: false, onPause: [], page: options.page || 0, title: options.title,
        instructions: 'Left/Right: page | Space or background click: pause | Esc: close'};
    pdg.visualTestSession = session;
    session.now = function() { return (session.paused ? pausedAt : clock()) - skipped; };
    // Only the JavaScript-facing scheduler clock changes. Native timers and
    // physics retain their real clock and are suspended by TimerManager.pause.
    var engineClock = pdg.tm.getMilliseconds.bind(pdg.tm);
    var engineEpoch = engineClock(), epoch = session.now();
    pdg.tm.getMilliseconds = function() { return (engineEpoch + session.now() - epoch) >>> 0; };
    session.setTimeout = function(callback, delay) { return pdg.tm.onTimeout(callback, delay); };
    session.toggle = function() {
        if (session.paused) {
            skipped += clock() - pausedAt;
            session.paused = false;
            if (!timerWasPaused) pdg.tm.unpause();
            if (separateNativeTimers && !nativeWasPaused) nativeTimers.unpause.call(pdg.tm);
        } else {
            pausedAt = clock();
            timerWasPaused = pdg.tm.isPaused();
            pdg.tm.pause();
            if (separateNativeTimers) {
                nativeWasPaused = nativeTimers.isPaused.call(pdg.tm);
                nativeTimers.pause.call(pdg.tm);
            }
            session.paused = true;
        }
        console.log((session.paused ? 'Paused: ' : 'Playing: ') + session.title);
        if (options.onPause) options.onPause(session.paused);
        session.onPause.forEach(function(callback) { callback(session.paused); });
    };
    session.navigate = options.navigate;
    var originalQuit = pdg.quit;
    pdg.quit = function() { options.navigate('quit'); };
    session.close = function() { originalQuit.call(pdg); };

    // Register before page handlers: Space must not also advance a legacy test
    // or apply the wheel's old Space-to-brake shortcut.
    pdg.onKeyPress(function(event) {
        var key = event.unicode;
        if (key === 32) session.toggle();
        else if (key === pdg.key_LeftArrow) options.navigate('previous');
        else if (key === pdg.key_RightArrow) options.navigate('next');
        else if (key === pdg.key_Escape) options.navigate('quit');
        else return false;
        return true;
    });

    function bar(port) {
        var area = port.getDrawingArea();
        return {left: area.left, right: area.right, top: area.bottom - 30, bottom: area.bottom};
    }
    function toolbarClick(event) {
        var port = event.port || (pdg.gfx && pdg.gfx.getMainPort());
        if (!port || !event.mousePos) return false;
        var area = bar(port), point = event.mousePos;
        if (point.y < area.top || point.y > area.bottom) return false;
        if (point.x < area.left + 65) options.navigate('previous');
        else if (point.x > area.right - 65) options.navigate('next');
        else session.toggle();
        return true;
    }
    var backgroundStart = null;
    pdg.onMouseDown(function(event) { backgroundStart = null; return toolbarClick(event); });
    pdg.onMouseMove(function(event) {
        if (backgroundStart && event.mousePos &&
            Math.abs(event.mousePos.x - backgroundStart.x) + Math.abs(event.mousePos.y - backgroundStart.y) > 5)
            backgroundStart = null;
        return false;
    });
    session.draw = function(port) {
        var area = bar(port);
        port.drawRect(new pdg.Rect(area.left, area.top, area.right, area.bottom), new pdg.Attributes().fillColor('#20252b'));
        var attrs = new pdg.Attributes().fillColor('#ffffff').textSize(12);
        port.drawText('< Prev', new pdg.Point(area.left + 8, area.bottom - 9), attrs);
        port.drawText('Next >', new pdg.Point(area.right - 55, area.bottom - 9), attrs);
        var label = session.title + (session.paused ? '  [Paused]' : '  [Playing]') + '  Space/click: pause';
        // Long page titles must leave both navigation targets readable.
        while (label.length > 8 && port.getTextWidth(label, 12, 0) > area.right - area.left - 145) label = label.slice(0, -5) + '...';
        port.drawText(label, new pdg.Point(area.left + 70, area.bottom - 9), attrs);
    };
    var originalOn = pdg.on;
    var backgroundHandler, backgroundUpHandler;
    function installBackgroundHandler() {
        if (backgroundHandler) backgroundHandler.cancel();
        if (backgroundUpHandler) backgroundUpHandler.cancel();
        backgroundHandler = originalOn.call(pdg, pdg.eventType_MouseDown, function(event) {
            if (event.mousePos) backgroundStart = {x:event.mousePos.x, y:event.mousePos.y};
            return false;
        });
        backgroundUpHandler = originalOn.call(pdg, pdg.eventType_MouseUp, function() {
            if (!backgroundStart) return false;
            backgroundStart = null;
            session.toggle();
            return true;
        });
    }
    pdg.on = function(type, callback) {
        if (type === pdg.eventType_PortDraw) return originalOn.call(pdg, type, function(event) {
            var result = callback(event);
            session.draw(event.port);
            return result;
        });
        var handler = originalOn.apply(pdg, arguments);
        // MVC applications can register controllers after starting pdg.run().
        // Keep the background action behind these and later modal controls.
        if ((type === pdg.eventType_MouseDown || type === pdg.eventType_MouseUp) && backgroundHandler) installBackgroundHandler();
        return handler;
    };
    // A background click must be unhandled on both press and release. MVC
    // checkboxes handle release; rig buttons and drags handle press.
    var ready = false;
    session.ready = function() {
        if (ready) return;
        ready = true;
        installBackgroundHandler();
        originalOn.call(pdg, pdg.eventType_PortDraw, function(event) { session.draw(event.port); return false; });
    };
    var originalRun = pdg.run;
    pdg.run = function() { session.ready(); return originalRun.apply(pdg, arguments); };
    console.log(session.title + '\n' + session.instructions);
    return session;
};
