// Browser harness for the Emscripten UI tests.
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
    var testIds = ["port", "font", "drawing", "shape-fill", "image", "animation"];
    var params = new URLSearchParams(window.location.search);
    var testId = params.get("test");
    var automated = params.get("automated") === "1";
    var statusNode = document.getElementById("pdg-ui-status");
    var resultNode = document.getElementById("pdg-ui-result-json");
    var cacheToken = Date.now().toString(36);
    var finished = false;
    var frameCount = 0;
    var runtimeError = null;
    var fontColorsSeen = { white: false, yellow: false };
    var drawingSpheresSeen = false;

    function sampleFontColors() {
        if (testId !== "font" || (fontColorsSeen.white && fontColorsSeen.yellow)) return;
        var gl = window.Module && window.Module.ctx;
        var canvas = document.getElementById("pdg-canvas");
        if (!gl || !canvas || (gl.isContextLost && gl.isContextLost())) return;
        try {
            var pixels = new Uint8Array(canvas.width * canvas.height * 4);
            gl.readPixels(0, 0, canvas.width, canvas.height, gl.RGBA, gl.UNSIGNED_BYTE, pixels);
            for (var index = 0; index < pixels.length; index += 4) {
                var red = pixels[index];
                var green = pixels[index + 1];
                var blue = pixels[index + 2];
                if (red > 200 && green > 200 && blue > 200) fontColorsSeen.white = true;
                if (red > 180 && green > 180 && blue < 100) fontColorsSeen.yellow = true;
                if (fontColorsSeen.white && fontColorsSeen.yellow) return;
            }
        } catch (error) {
            console.warn("Could not sample the font test framebuffer", error);
        }
    }

    function sampleDrawingSpheres() {
        if (testId !== "drawing" || drawingSpheresSeen) return;
        var gl = window.Module && window.Module.ctx;
        var canvas = document.getElementById("pdg-canvas");
        if (!gl || !canvas || (gl.isContextLost && gl.isContextLost())) return;
        try {
            var pixels = new Uint8Array(canvas.width * canvas.height * 4);
            gl.readPixels(0, 0, canvas.width, canvas.height, gl.RGBA, gl.UNSIGNED_BYTE, pixels);
            var scaleX = canvas.width / 1000;
            var scaleY = canvas.height / 800;

            function pixelAt(x, y) {
                var px = Math.max(0, Math.min(canvas.width - 1, Math.round(x * scaleX)));
                var py = Math.max(0, Math.min(canvas.height - 1, Math.round(y * scaleY)));
                var offset = ((canvas.height - 1 - py) * canvas.width + px) * 4;
                return [pixels[offset], pixels[offset + 1], pixels[offset + 2]];
            }

            var background = pixelAt(800, 700);
            function sphereStats(centerX, centerY) {
                var foreground = 0;
                var bright = 0;
                for (var y = centerY - 36; y <= centerY + 36; y += 2) {
                    for (var x = centerX - 36; x <= centerX + 36; x += 2) {
                        var dx = x - centerX;
                        var dy = y - centerY;
                        if (dx * dx + dy * dy > 36 * 36) continue;
                        var color = pixelAt(x, y);
                        var difference = Math.abs(color[0] - background[0]) +
                            Math.abs(color[1] - background[1]) +
                            Math.abs(color[2] - background[2]);
                        if (difference > 24) foreground++;
                        if (difference > 24 && Math.max(color[0], color[1], color[2]) > 55) bright++;
                    }
                }
                return { foreground: foreground, bright: bright };
            }

            var coloredCenters = [100, 220, 340, 460, 580];
            var geometryIsRound = coloredCenters.every(function(centerX) {
                return sphereStats(centerX, 150).foreground > 700;
            });
            var jupiterIsTextured = sphereStats(580, 510).bright > 250;
            var moonIsTextured = sphereStats(580, 630).bright > 250;
            drawingSpheresSeen = geometryIsRound && jupiterIsTextured && moonIsTextured;
        } catch (error) {
            console.warn("Could not sample the drawing test framebuffer", error);
        }
    }

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
        if (status === "passed" && testId === "font" &&
            (!fontColorsSeen.white || !fontColorsSeen.yellow)) {
            status = "failed";
            message = "font framebuffer did not contain both white and yellow text";
        }
        if (status === "passed" && testId === "drawing" && !drawingSpheresSeen) {
            status = "failed";
            message = "sphere framebuffer did not contain round colored and JPEG-textured spheres";
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
        if (params.get("suite") === "1" && window.parent !== window) {
            window.parent.postMessage({
                type: "pdg-ui-test-result",
                result: result,
                runToken: params.get("run") || ""
            }, window.location.origin);
        }
    }

    function runSuite() {
        var suiteNode = document.getElementById("pdg-ui-suite");
        var frame = document.getElementById("pdg-ui-suite-frame");
        var list = document.getElementById("pdg-ui-suite-results");
        var canvas = document.getElementById("pdg-canvas");
        var results = new Array(testIds.length);
        var index = 0;
        var activeTestId = null;
        var activeRunToken = "";
        var sequenceRunning = true;

        canvas.style.display = "none";
        suiteNode.style.display = "block";
        testIds.forEach(function(id) {
            var item = document.createElement("li");
            item.id = "pdg-ui-suite-" + id;
            item.textContent = id + ": pending";
            item.tabIndex = 0;
            item.setAttribute("role", "button");
            item.setAttribute("aria-label", "Run the " + id + " UI test");
            item.title = "Click to run this test again";
            item.addEventListener("click", function() { launchTest(id, true); });
            item.addEventListener("keydown", function(event) {
                if (event.key === "Enter" || event.key === " ") {
                    event.preventDefault();
                    launchTest(id, true);
                }
            });
            list.appendChild(item);
        });

        function completeSuite() {
            var failures = results.filter(function(result) { return result.status !== "passed"; });
            var totalFrames = results.reduce(function(total, result) {
                return total + result.frames;
            }, 0);
            var result = {
                status: failures.length ? "failed" : "passed",
                suite: true,
                tests: results,
                frames: totalFrames
            };
            window.pdgUiTestResult = result;
            document.documentElement.setAttribute("data-status", result.status);
            resultNode.textContent = JSON.stringify(result);
            statusNode.textContent = result.status.toUpperCase() + ": full UI suite — " +
                results.length + " tests, " + totalFrames +
                " frames. Click any result to rerun it.";
            document.title = "PDG UI SUITE: " + result.status.toUpperCase();
        }

        function launchTest(id, isRerun) {
            if (isRerun) sequenceRunning = false;
            activeTestId = id;
            activeRunToken = id + "-" + Date.now() + "-" + Math.random().toString(36).slice(2);
            var item = document.getElementById("pdg-ui-suite-" + id);
            item.className = "running";
            item.textContent = id + ": running";
            statusNode.textContent = isRerun
                ? "Rerunning " + id + (automated ? " (accelerated)" : "")
                : "Full UI suite " + (index + 1) + "/" + testIds.length + ": " + id +
                    (automated ? " (accelerated)" : "");
            frame.src = "ui.html?test=" + encodeURIComponent(id) +
                "&suite=1" + (automated ? "&automated=1" : "") +
                "&run=" + encodeURIComponent(activeRunToken) + "&_pdg_cache=" + Date.now();
        }

        function launchNext() {
            if (index >= testIds.length) {
                completeSuite();
                return;
            }
            launchTest(testIds[index], false);
        }

        window.addEventListener("message", function(event) {
            if (event.origin !== window.location.origin || event.source !== frame.contentWindow ||
                !event.data || event.data.type !== "pdg-ui-test-result") return;
            var result = event.data.result;
            if (!result || result.test !== activeTestId || event.data.runToken !== activeRunToken) return;
            results[testIds.indexOf(result.test)] = result;
            var item = document.getElementById("pdg-ui-suite-" + result.test);
            item.className = result.status;
            item.textContent = result.test + ": " + result.status + " (" + result.frames + " frames)";
            if (sequenceRunning) {
                index++;
                window.setTimeout(launchNext, automated ? 0 : 500);
            } else {
                window.pdgUiTestResult = result;
                resultNode.textContent = JSON.stringify(result);
                statusNode.textContent = result.status.toUpperCase() + ": reran " + result.test +
                    " (" + result.frames + " frames). Click another result to run it.";
                document.documentElement.setAttribute("data-status", result.status);
                document.title = "PDG UI TEST: " + result.status.toUpperCase();
            }
        });

        launchNext();
    }

    if (!testId) {
        runSuite();
        return;
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
            var effectiveDelay = automated && delay >= 1000
                ? Math.max(50, delay * 0.02)
                : delay;
            return nativeSetTimeout.apply(window, [callback, effectiveDelay].concat(args));
        };

        var originalOn = window.pdg.on;
        window.pdg.on = function(eventType, callback) {
            if (eventType === window.pdg.eventType_PortDraw) {
                return originalOn.call(window.pdg, eventType, function(event) {
                    frameCount++;
                    var handled = callback(event);
                    sampleFontColors();
                    sampleDrawingSpheres();
                    return handled;
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
        }, automated ? 30000 : 900000);
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
