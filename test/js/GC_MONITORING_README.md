# GC monitoring

`gc-monitor.js` is an optional Node/V8 profiling helper. The animation showcase
loads it when run directly outside the visual-test session:

```sh
./pdg test/js/main.js
./pdg --expose-gc test/js/main.js
./pdg --trace-gc test/js/main.js
```

Run from the repository root with a graphics-capable embedded Node build.
The normal `test/demo` visual session and automated demo runs do not enable
this helper. It observes GC events, samples memory and frame intervals, and
prints a report when stopped. Its frame-drop correlations are diagnostic
measurements, not pass/fail tests or proof that GC caused a particular stall.

To use the helper in another script, construct `GCMonitor`, call `start()`,
call `onFrame()` once per frame, then `stop()` and `printReport()` on shutdown.
The source documents its configuration and report fields. Node-specific GC
observation is unavailable in browser and iOS JavaScriptCore runtimes.

Automated lifetime and garbage-collection regressions belong to the unit suite:

```sh
./test/unit node_runtime process_lifetime
./test/unit --node node_runtime process_lifetime
```

Their subprocess inputs live in `test/spec/fixtures`. See the
[testing guide](../README.md) for capabilities and artifact locations.
