// Browser harness for the JavaScript PDG performance benchmarks.
(function() {
    "use strict";

    var benchmarks = {
        bunnymark: {
            name: "Bunnymark",
            source: "perf/bunnymark/bunnymark.js",
            virtualPath: "/test/perf/bunnymark/bunnymark.js",
            canvasWidth: 800,
            canvasHeight: 600
        },
        pdgmark: {
            name: "PDGMark",
            source: "perf/pdgmark/pdgmark.js",
            virtualPath: "/test/perf/pdgmark/pdgmark.js",
            canvasWidth: 1000,
            canvasHeight: 800
        },
        canvasmark: {
            name: "CanvasMark 2013",
            source: "perf/canvasmark2013/canvasmark.js",
            virtualPath: "/test/perf/canvasmark2013/canvasmark.js",
            canvasWidth: 640,
            canvasHeight: 640
        }
    };

    var params = new URLSearchParams(window.location.search);
    var benchmarkId = params.get("test");
    var benchmark = benchmarks[benchmarkId];
    var statusNode = document.getElementById("pdg-perf-status");
    var resultNode = document.getElementById("pdg-perf-result");
    var downloadNode = document.getElementById("pdg-perf-download");
    var canvas = document.getElementById("pdg-canvas");
    var cacheToken = Date.now().toString(36);
    var nativeRequire = window.require;
    var resultUrl = null;
    var finished = false;

    if (!benchmarkId) {
        canvas.style.display = "none";
        return;
    }
    if (!benchmark) {
        fail("Unknown performance benchmark: " + benchmarkId);
        return;
    }

    canvas.width = benchmark.canvasWidth;
    canvas.height = benchmark.canvasHeight;
    canvas.focus();

    function setStatus(message) {
        statusNode.textContent = message;
    }

    function requestSource(url) {
        var request = new XMLHttpRequest();
        request.open("GET", url + (url.indexOf("?") === -1 ? "?" : "&") +
            "_pdg_cache=" + cacheToken, false);
        request.send(null);
        if ((request.status >= 200 && request.status < 300) || request.status === 0) {
            return request.responseText;
        }
        throw new Error("Could not load " + url + " (HTTP " + request.status + ")");
    }

    function normalizePath(value) {
        var absolute = value.charAt(0) === "/";
        var parts = value.replace(/\\/g, "/").split("/");
        var normalized = [];
        parts.forEach(function(part) {
            if (!part || part === ".") return;
            if (part === "..") normalized.pop();
            else normalized.push(part);
        });
        return (absolute ? "/" : "") + normalized.join("/");
    }

    var pathModule = {
        join: function() {
            return normalizePath(Array.prototype.join.call(arguments, "/"));
        },
        resolve: function(value) { return normalizePath(value || "."); },
        dirname: function(value) {
            var normalized = normalizePath(value);
            return normalized.replace(/\/[^/]*$/, "") || "/";
        },
        basename: function(value) { return normalizePath(value).split("/").pop(); }
    };

    var fsModule = {
        readFileSync: function(filePath, options) {
            var normalized = normalizePath(filePath);
            var encoding = typeof options === "string" ? options : options && options.encoding;
            try {
                return window.FS.readFile(normalized, encoding ? { encoding: encoding } : undefined);
            } catch (fsError) {
                var source = requestSource(normalized);
                if (encoding) return source;
                return new TextEncoder().encode(source);
            }
        },
        writeFileSync: function(filePath, data) {
            window.pdgPerfVirtualFiles = window.pdgPerfVirtualFiles || {};
            window.pdgPerfVirtualFiles[normalizePath(filePath)] = String(data);
        },
        existsSync: function(filePath) {
            try { window.FS.stat(normalizePath(filePath)); return true; } catch (error) { return false; }
        }
    };

    function browserRequire(request) {
        if (request === "pdg") return window.pdg;
        if (request === "fs") return fsModule;
        if (request === "path") return pathModule;
        if (nativeRequire) return nativeRequire(request);
        throw new Error("Unsupported browser module: " + request);
    }

    function fail(message) {
        if (finished) return;
        finished = true;
        document.documentElement.setAttribute("data-status", "failed");
        setStatus("FAILED: " + benchmarkId + " — " + message);
        resultNode.textContent = message;
        document.title = "PDG PERF: FAILED";
        console.error(message);
    }

    window.pdgPerfReport = function(results) {
        var result = {
            status: "completed",
            benchmark: benchmarkId,
            engine: "emscripten",
            userAgent: navigator.userAgent,
            results: results
        };
        var json = JSON.stringify(result, null, 2);
        window.pdgPerfTestResult = result;
        document.documentElement.setAttribute("data-status", "completed");
        resultNode.textContent = json;
        setStatus("COMPLETED: " + benchmark.name + ". Download the JSON result or choose another benchmark.");
        document.title = "PDG PERF: " + benchmark.name + " COMPLETE";
        if (resultUrl) URL.revokeObjectURL(resultUrl);
        resultUrl = URL.createObjectURL(new Blob([json + "\n"], { type: "application/json" }));
        downloadNode.href = resultUrl;
        downloadNode.download = benchmarkId + "-emscripten-results.json";
        downloadNode.style.display = "block";
    };

    function runBenchmark() {
        var args = ["pdg", benchmark.virtualPath];
        var duration = parseFloat(params.get("duration"));
        if (benchmarkId === "bunnymark" && isFinite(duration) && duration > 0) {
            args.push("--duration", String(duration));
        }
        if (params.get("auto") === "1") args.push("--auto");

        window.process.argv = args;
        window.process.exit = function(code) {
            if (code) fail("benchmark called process.exit(" + code + ")");
            else window.pdg.quit();
        };
        window.__filename = benchmark.virtualPath;
        window.__dirname = pathModule.dirname(benchmark.virtualPath);
        window.require = browserRequire;

        var source = requestSource(benchmark.source);
        // Node accepts a hashbang before parsing; Function() does not.
        source = source.replace(/^#![^\r\n]*(?:\r?\n|$)/, "");
        var module = { exports: {} };
        var factory = new Function("require", "module", "exports", "__filename", "__dirname",
            source + "\n//# sourceURL=/test/" + benchmark.source);
        setStatus("RUNNING: " + benchmark.name +
            (benchmarkId === "bunnymark" && duration > 0 ? " for " + duration + " seconds" : "") +
            ". Press ESC in the canvas to finish early.");
        document.documentElement.setAttribute("data-status", "running");
        factory(browserRequire, module, module.exports, benchmark.virtualPath,
            pathModule.dirname(benchmark.virtualPath));
    }

    function waitForPdg(deadline) {
        if (window.pdg && window.pdg.pdgReady) {
            try { runBenchmark(); } catch (error) {
                fail(error && error.stack ? error.stack : String(error));
            }
        } else if (Date.now() > deadline) {
            fail("WebAssembly initialization timed out");
        } else {
            window.setTimeout(function() { waitForPdg(deadline); }, 25);
        }
    }

    window.addEventListener("error", function(event) {
        fail(event.error && event.error.stack ? event.error.stack : event.message);
    });
    window.addEventListener("unhandledrejection", function(event) {
        fail(event.reason && event.reason.stack ? event.reason.stack : String(event.reason));
    });

    setStatus("Loading WebAssembly for " + benchmark.name + "...");
    var script = document.createElement("script");
    script.src = "../build/wasm/libpdg.js?_pdg_cache=" + cacheToken;
    script.onerror = function() { fail("libpdg.js failed to load"); };
    document.head.appendChild(script);
    waitForPdg(Date.now() + 30000);
})();
