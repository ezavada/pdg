(function() {
    "use strict";

    var specs = [
        "animated", "animation_event_filtering", "color", "configmanager",
        "drawing", "event_filtering_comprehensive", "eventemitter", "eventmanager",
        "filemanager", "font", "graphicsmanager", "image", "imagestrip", "log",
        "memblock", "mvc-app", "netclient", "netconnection", "netserver", "offset",
        "point", "polygon", "port", "quad", "rect", "resourcemanager", "rotatedrect",
        "serialization", "serialized_data", "serialized_objects", "sound", "soundmanager",
        "spline", "sprite", "sprite_layer_event_filtering", "spritelayer", "spriter",
        "spriter_animblend", "spriter_attach", "spriter_charmap", "spriter_collisions",
        "spriter_events", "spriter_subentity", "tilelayer", "timermanager", "vector"
    ];
    var moduleCache = {};
    var loadErrors = [];
    var statusNode = document.getElementById("pdg-test-status");
    var loadErrorNode = document.getElementById("pdg-load-errors");

    function setStatus(message) {
        statusNode.textContent = message;
    }

    function requestSource(url) {
        var request = new XMLHttpRequest();
        request.open("GET", url, false);
        request.send(null);
        if ((request.status >= 200 && request.status < 300) || request.status === 0) {
            return request.responseText;
        }
        return null;
    }

    function resolveSource(request, parentUrl) {
        var resolved = new URL(request, parentUrl).href;
        var candidates = /\.[^/]+$/.test(new URL(resolved).pathname)
            ? [resolved]
            : [resolved + ".js", resolved.replace(/\/$/, "") + "/index.js"];
        for (var i = 0; i < candidates.length; i++) {
            var source = requestSource(candidates[i]);
            if (source !== null) return { url: candidates[i], source: source };
        }
        throw new Error("Cannot load module " + request + " from " + parentUrl);
    }

    var pathModule = {
        join: function() {
            return Array.prototype.join.call(arguments, "/").replace(/\/+/g, "/");
        },
        resolve: function(value) { return value || "."; },
        dirname: function(value) { return value.replace(/\/[^/]*$/, "") || "."; },
        basename: function(value) { return value.split("/").pop(); }
    };

    function browserRequire(request, parentUrl) {
        if (request === "pdg") return window.pdg;
        if (request === "fs") {
            return {
                readdirSync: function(path) { return window.FS.readdir(path); },
                readFileSync: function(path, options) {
                    var encoding = typeof options === "string" ? options : options && options.encoding;
                    if (encoding) return window.FS.readFile(path, { encoding: encoding });
                    var bytes = window.FS.readFile(path);
                    bytes.toString = function(requestedEncoding) {
                        return new TextDecoder(requestedEncoding || "utf-8").decode(bytes);
                    };
                    return bytes;
                },
                writeFileSync: function(path, data) { return window.FS.writeFile(path, data); },
                unlinkSync: function(path) { return window.FS.unlink(path); },
                existsSync: function(path) {
                    try { window.FS.stat(path); return true; } catch (error) { return false; }
                }
            };
        }
        if (request === "path") return pathModule;
        if (request === "os") return { tmpdir: function() { return "/tmp"; } };
        if (request.charAt(0) !== "." && request.charAt(0) !== "/") {
            return window.require(request);
        }

        var loaded = resolveSource(request, parentUrl);
        if (moduleCache[loaded.url]) return moduleCache[loaded.url].exports;

        var module = { exports: {} };
        moduleCache[loaded.url] = module;
        var localRequire = function(name) { return browserRequire(name, loaded.url); };
        var dirname = loaded.url.replace(/\/[^/]*$/, "");
        try {
            var factory = new Function("require", "module", "exports", "__filename", "__dirname",
                loaded.source + "\n//# sourceURL=" + loaded.url);
            factory(localRequire, module, module.exports, loaded.url, dirname);
        } catch (error) {
            delete moduleCache[loaded.url];
            throw error;
        }
        return module.exports;
    }

    function recordLoadError(name, error) {
        var message = name + ": " + (error && error.stack ? error.stack : error);
        loadErrors.push(message);
        var item = document.createElement("li");
        item.textContent = message;
        loadErrorNode.appendChild(item);
        console.error("[PDG TEST LOAD ERROR] " + message);
    }

    function finish(runner) {
        var results = runner.results();
        var failed = results.failedCount + loadErrors.length;
        var result = {
            status: failed === 0 ? "passed" : "failed",
            specs: results.totalCount,
            jasmineFailures: results.failedCount,
            loadFailures: loadErrors.length,
            loadErrors: loadErrors.map(function(message) { return message.split("\n")[0]; }),
            loadedFiles: specs.length + 1
        };
        window.pdgTestResults = result;
        document.documentElement.setAttribute("data-status", result.status);
        document.getElementById("pdg-result-json").textContent = JSON.stringify(result);
        setStatus(result.status.toUpperCase() + ": " + result.specs + " specs, " + failed + " failures");
        document.title = "PDG CLIENT TESTS: " + result.status.toUpperCase();
        if (window.pdg && typeof window.pdg.quit === "function") window.pdg.quit();
    }

    function loadHelper(base) {
        var helper = resolveSource("spec/SpecHelper.js", base);
        var module = { exports: {} };
        moduleCache[helper.url] = module;
        var helperFactory = new Function("require", "module", "exports", "__filename", "__dirname",
            helper.source + "\n//# sourceURL=" + helper.url);
        helperFactory(function(name) { return browserRequire(name, helper.url); }, module, module.exports,
            helper.url, helper.url.replace(/\/[^/]*$/, ""));
    }

    function runSpecs() {
        var base = window.location.href;
        setStatus("Loading SpecHelper and " + specs.length + " spec files...");
        try {
            loadHelper(base);
        } catch (error) {
            recordLoadError("SpecHelper.js", error);
        }

        specs.forEach(function(name) {
            try {
                browserRequire("./spec/" + name + ".spec.js", base);
            } catch (error) {
                recordLoadError(name + ".spec.js", error);
            }
        });

        var jasmineEnv = jasmine.getEnv();
        var htmlReporter = new jasmine.HtmlReporter(document);
        jasmineEnv.updateInterval = 250;
        jasmineEnv.addReporter(htmlReporter);
        jasmineEnv.addReporter({ reportRunnerResults: finish });
        jasmineEnv.specFilter = function(spec) { return htmlReporter.specFilter(spec); };
        setStatus("Running client specs...");
        jasmineEnv.execute();
    }

    function failInitialization(message) {
        recordLoadError("libpdg.js", new Error(message));
        var result = { status: "failed", specs: 0, jasmineFailures: 0, loadFailures: loadErrors.length };
        window.pdgTestResults = result;
        document.documentElement.setAttribute("data-status", "failed");
        document.getElementById("pdg-result-json").textContent = JSON.stringify(result);
        setStatus("FAIL: " + message);
        document.title = "PDG CLIENT TESTS: FAILED";
    }

    function waitForPdg(deadline) {
        if (window.pdg && window.pdg.pdgReady) {
            runSpecs();
        } else if (Date.now() > deadline) {
            failInitialization("initialization timed out");
        } else {
            setTimeout(function() { waitForPdg(deadline); }, 25);
        }
    }

    function start() {
        if (window.location.protocol === "file:") {
            failInitialization("serve this directory over HTTP; browsers block Wasm from file:// URLs");
            return;
        }
        var script = document.createElement("script");
        script.src = "../libpdg.js";
        script.onerror = function() { failInitialization("libpdg.js failed to load"); };
        document.head.appendChild(script);
        waitForPdg(Date.now() + 30000);
    }

    start();
})();
