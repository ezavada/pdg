(function() {
    "use strict";

    var tests = {
        "port": "port_test.js",
        "font": "font_test.js",
        "drawing": "drawing_test.js",
        "shape-fill": "shape_fill_test.js",
        "image": "image_test.js",
        "animation": "animation_test.js"
    };
    var params = new URLSearchParams(window.location.search);
    var testId = params.get("test") || "port";
    var statusNode = document.getElementById("pdg-ui-status");
    var resultNode = document.getElementById("pdg-ui-result-json");
    var cacheToken = Date.now().toString(36);
    var finished = false;
    var frameCount = 0;
    var runtimeError = null;

    function requestSource(url) {
        var request = new XMLHttpRequest();
        request.open("GET", url + (url.indexOf("?") === -1 ? "?" : "&") +
            "_pdg_cache=" + cacheToken, false);
        request.send(null);
        if (request.status >= 200 && request.status < 300) return request.responseText;
        throw new Error("Could not load " + url + " (HTTP " + request.status + ")");
    }

    function finish(status, message) {
        if (finished) return;
        finished = true;
        if (status === "passed" && frameCount === 0) {
            status = "failed";
            message = "test quit without rendering a PortDraw frame";
        }
        var result = {
            status: status,
            test: testId,
            frames: frameCount,
            message: message || ""
        };
        window.pdgUiTestResult = result;
        document.documentElement.setAttribute("data-status", status);
        resultNode.textContent = JSON.stringify(result);
        statusNode.textContent = status.toUpperCase() + ": " + testId +
            " (" + frameCount + " frames)" + (message ? " — " + message : "");
        document.title = "PDG UI TEST: " + status.toUpperCase();
    }

    window.addEventListener("error", function(event) {
        runtimeError = event.error && event.error.stack ? event.error.stack : event.message;
        finish("failed", runtimeError);
    });
    window.addEventListener("unhandledrejection", function(event) {
        runtimeError = event.reason && event.reason.stack ? event.reason.stack : String(event.reason);
        finish("failed", runtimeError);
    });

    function runUiTest() {
        if (!tests[testId]) {
            finish("failed", "unknown UI test: " + testId);
            return;
        }

        var nativeSetTimeout = window.setTimeout;
        window.setTimeout = function(callback, delay) {
            var args = Array.prototype.slice.call(arguments, 2);
            var accelerated = delay >= 1000 ? Math.max(50, delay * 0.02) : delay;
            return nativeSetTimeout.apply(window, [callback, accelerated].concat(args));
        };

        var originalOn = window.pdg.on;
        window.pdg.on = function(eventType, callback) {
            if (eventType === window.pdg.eventType_PortDraw) {
                return originalOn.call(window.pdg, eventType, function(event) {
                    frameCount++;
                    return callback(event);
                });
            }
            return originalOn.apply(window.pdg, arguments);
        };

        var originalQuit = window.pdg.quit;
        window.pdg.quit = function() {
            finish(runtimeError ? "failed" : "passed", runtimeError || "completed");
            return originalQuit.apply(window.pdg, arguments);
        };

        window.process.argv = ["pdg", "ui_tests/" + tests[testId]];
        window.process.exit = function(code) {
            finish(code ? "failed" : "passed", "process.exit(" + code + ")");
            if (code) throw new Error("UI test exited with status " + code);
            window.pdg.quit();
        };

        statusNode.textContent = "Running " + testId + " UI test…";
        var source = requestSource("ui_tests/" + tests[testId]);
        var factory = new Function(source + "\n//# sourceURL=/test/ui_tests/" + tests[testId]);
        factory();

        nativeSetTimeout(function() {
            if (!finished) finish("failed", "UI test timed out");
        }, 30000);
    }

    function waitForPdg(deadline) {
        if (window.pdg && window.pdg.pdgReady) {
            try { runUiTest(); } catch (error) {
                runtimeError = error && error.stack ? error.stack : String(error);
                finish("failed", runtimeError);
            }
        } else if (Date.now() > deadline) {
            finish("failed", "WebAssembly initialization timed out");
        } else {
            setTimeout(function() { waitForPdg(deadline); }, 25);
        }
    }

    var script = document.createElement("script");
    script.src = "../libpdg.js?_pdg_cache=" + cacheToken;
    script.onerror = function() { finish("failed", "libpdg.js failed to load"); };
    document.head.appendChild(script);
    waitForPdg(Date.now() + 30000);
})();
