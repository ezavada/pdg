# Running PDG tests and demos

These examples run from the repository root. The launchers also work when invoked
by path from another directory. Each has an extensionless POSIX launcher, a `.sh`
wrapper, and a `.ps1` PowerShell launcher (`.bat` forwards to PowerShell).

| Runner | Purpose | Runtime/build requirement |
| --- | --- | --- |
| `test/unit` | Jasmine behavioral specs and native CTest suites | Current PDG build; `--node`, `--web`, or `--ios` selects script runtime |
| `test/ui` | Visual regression pages; finite smoke checks with `--automated` | Graphics-capable native, browser, or iOS runtime |
| `test/demo` | Interactive demos; finite smoke checks with `--automated` | Graphics-capable native, browser, or iOS runtime |
| `test/rigs` | Real rig assets and controller integration | Matching Node runtime and built PDG addon with Spriter/Chipmunk |
| `test/tools` | Harness, build-cache and performance-tooling checks | Node; a C++20 compiler for `perf-measurement`; no PDG build |
| `test/perf` | Rendering scores and fixed-work benchmarks | Selected native, Node, or browser build; graphics for rendering marks |

Use `--list` to get the current selection names. Source and fixture locations:

- `spec/`: JavaScript behavioral specs; subprocess inputs are in `spec/fixtures/`.
- `cxx/`: C++ regressions registered with CTest by the configured build.
- `ui_tests/` and `js/`: visual pages, demos, and runtime entry points.
- `rig_tests/<rig>/`: automatically discovered rig checks; see its README for additions.
- `lib/`: shared runners/catalogs, tooling checks, rendering helpers and build-support payloads.
- `perf_tests/`: benchmarks, measurement helpers and committed baselines.
- `data/`: shared assets and test fixtures.

```sh
./test/unit                         # JavaScript specs + configured C++ tests
./test/unit color point              # only these JavaScript suites
./test/unit cpp:pdg-physicsbody       # one CTest suite in the current build
./test/unit --node                   # all specs against the current Node plugin
./test/unit --web color point        # build WASM if needed, open browser results
./test/unit --ios color point        # build/install in iOS Simulator, then test

./test/tools                        # tooling checks; no PDG build needed
./test/tools --list
./test/tools test-options node-build # selected tooling suites

./test/rigs                         # all rig integration checks (PDG Node addon)
./test/rigs --list
./test/rigs human                    # all human-rig checks
./test/rigs human/ground human/pose   # selected checks

./test/ui                           # visual regression pages
./test/ui --list                     # suite/page names and page numbers
./test/ui shape                      # alias for shape-fill; no other suites
./test/ui shape-fill --page pentagram
./test/ui shape-fill --page transforms # fixed pivots and combined transforms
./test/ui compositing --page stroke-opacity
./test/ui compositing --page blend-modes
./test/ui drawing image --page 3     # third page in this selected collection
./test/ui --web shape-fill --page 8
./test/ui --web offscreen            # live offscreen image versus frozen snapshot
./test/ui --ios --iphone drawing

./test/demo                         # interactive demos, separately from UI tests
./test/demo --list
./test/demo animation-physics        # human rig
./test/demo wheel-chains
./test/demo --web astra

./test/perf                         # short C++ and JavaScript benchmarks
./test/perf --list
./test/perf bunnymark cpp-bunnymark
./test/perf --web                    # Quick rendering marks in Chrome
```

Rendering benchmarks use QuickPDGMark, QuickCanvasMark and QuickBunnyMark,
saving synthetic scores plus raw frame measurements. Animation-pipeline, collider,
and rig benchmarks use fixed workloads and report throughput or step timings. See [performance tests](perf_tests/README.md)
for timing/load options, scoring assumptions, artifacts and original ramp modes.

PowerShell uses the same arguments, for example:

```powershell
.\test\unit.ps1 --node color point
.\test\ui.ps1 shape-fill --page pentagram
.\test\demo.ps1 animation-physics
.\test\tools.ps1
.\test\rigs.ps1 human
```

## Selection and builds

`--list` lists suites for the selected runtime without building or launching it.
Unit suites are the names in `test/spec`; `js:name` and `name.spec.js` also work.
Native unit runs additionally discover CTest suites in the build containing the
current `pdg` executable. These use `cpp:` names. A build without CTest enabled
only runs JavaScript specs. Set `PDG_TEST_BUILD_DIR` to select the corresponding
CMake build directory if the executable has been copied out of its build tree.

For `unit`, `ui`, `demo`, and `perf`, no runtime flag selects the current native
executable without reconfiguring it. `PDG_EXECUTABLE` can select a different executable. `--node` uses
the local Node plugin with `PDG_NODE`, `tools/node`, or Node on `PATH`, in that
order. A headless plugin cannot run UI tests/demos: the launcher reports this
and suggests a graphics runtime.

`--web` builds the test WASM incrementally through `tools/pdg-js.mak`, preserving
the native build configuration. It requires an activated Emscripten toolchain,
GNU make, Python, and Bash (also on Windows). By default, unit, UI, and demo
runs open the default browser and serve the repository on localhost until
Ctrl+C. Unit results remain visible after the tests finish; reload to rerun them.
`--automated` runs use headless Chrome/Chromium, save a report, and exit with the
test status; `PDG_BROWSER` can select its executable. `PDG_TEST_PORT` selects a
fixed port; otherwise a free port is used.

`--ios` requires macOS/Xcode and an available iOS Simulator. It incrementally
builds and installs `pdg-js-test`. Choose `--iphone`, `--ipad`, or set
`PDG_IOS_DEVICE_ID`. Visual pages open Simulator; their on-screen toolbar works
without a keyboard. `--no-build` skips the web/iOS build when deliberately
testing existing binaries. iOS still installs the existing app bundle.

Browser and iOS supported spec lists live in `lib/unit_spec_catalog.js` and
are shared by execution and `--list`. C++ tests run on the native host, not in
the Node plugin, browser, or iOS JavaScript harness.

`node_runtime` includes nested CommonJS imports and isolated garbage-collection
regressions. With native graphics it also checks benchmark frame pacing on
existing and newly opened windows. These subprocess fixtures live in
`spec/fixtures` and have a 15-second timeout. Native `offscreen` specs run the
CanvasMark ship/texture and polygon-cache pixel regressions; the browser's
automated `shape-fill` check runs the same shared helpers.

`process_lifetime` checks idle exit, live timers, worker teardown and embedded
forced-exit controls in isolated subprocesses. Node-specific specs gate themselves
on Node capabilities; their presence in the shared browser/iOS catalog does not
imply Node APIs are available there. Other specs similarly check graphics,
Spriter, Chipmunk and sound capabilities before exercising them.

## Tooling checks

`test/tools` runs the standalone checks in `test/lib`: runner options and catalogs,
Node build-cache handling, WASM build/package configurations, benchmark sampling
and runner behavior, baseline comparisons, and C++ benchmark measurement.
It uses ordinary Node (`PDG_NODE`, then `tools/node`,
then `node` on `PATH`), without loading PDG or requiring an engine build.

The `node-build` and `wasm-release` suites test POSIX build helpers using fake builds
and are explicitly skipped on native Windows. `wasm-release` requires GNU Make,
CMake and Python 3; it verifies Release/Debug ZIPs and checksums without Emscripten.
`perf-runner` also reports its Windows exclusions for fake-executable subprocess
checks. The `perf-measurement` suite compiles a temporary
C++20 executable using `CXX` (a single executable name/path), or `c++` on POSIX and
`cl.exe` on Windows. For MSVC, run from a developer shell. A missing compiler or
other required tool fails its suite; the remaining suites still run.

Each suite runs in a separate process with a two-minute timeout per command.
The runner reports passes, failures and skips, and returns nonzero if a suite fails
or arguments are invalid. Logs and `reports/summary.json` are saved under
`artifacts/test-results/<platform>/tools/`, respecting the usual `PDG_TEST_*`
artifact-directory overrides. Compiled test executables are removed after use.

`test/lib/test_exit.js` is the PDG payload used to smoke-test staged release
executables. `test/lib/test_pdg.js` prints runtime/binding details for the VS Code
launch configurations. Both require PDG and are invoked by their respective
callers, separately from `test/tools`.

## Rig checks

`test/rigs` runs the real-asset rig regressions in `rig_tests`, including all nine
human-rig checks. It requires the PDG Node addon with Chipmunk
physics and runs each check in an isolated process. Shell, PowerShell, and batch
wrappers are available. See [rig checks](rig_tests/README.md) for selection,
artifacts, and how to add another rig.

## Visual pages

There are 38 UI pages (ports, fonts, drawing primitives, shape fills, transform pivots, compositing, images, offscreen ports,
animation, Spriter/sound) and seven demos (Astra, particles, the human rig,
wheel/chains, Grey Guy/Wonky Skeleton, MVC control gallery, and layer serialization).
`control-gallery` is an alias for `mvc`, not an additional demo.

- Left/Right, or the **Prev/Next** toolbar buttons: change page, wrapping at the ends.
- Space, a background click, or the center of the toolbar: pause/resume.
- Escape: end the session. In a browser, also stop the local server with Ctrl+C.

Pause freezes simulation, scheduled timers, and animation clocks; rendering
and navigation stay active. Demo buttons and drags receive input before the
background-click action. The wheel demo uses **K** for braking in these sessions
because Space now pauses the whole demo. Its Brake button still works.

`--page` accepts a one-based number within the selected collection, a unique
page name, or `suite/page`. Selecting a suite limits navigation to that suite;
multiple suite names combine their pages in catalog order. Each new page starts
with fresh runtime state, including when navigating back. Pages remain visible
until you navigate; `--automated` runs a finite smoke sequence and exits.

## Automated validation and artifacts

```sh
./test/unit --web --no-build --automated color point
./test/ui --web --no-build --automated shape-fill drawing
./test/demo --web --no-build --automated astra particles
./test/ui --automated font           # native smoke check
./test/tools
./test/rigs
node test/emscripten/check_visual_controls.js
```

The browser control check exercises actual keyboard/mouse navigation, paused
framebuffers, clock continuity, particle/rig physics, and demo/MVC input handling.
It uses the existing WASM build. Smoke checks retain their existing assertions and exit on completion;
they cannot be combined with `--page`.

Artifacts live under `artifacts/test-results/<runtime>/<kind>/`. Automated browser
runs save rendered reports; native visual smoke runs save stdout/stderr and a JSON
summary. CI/release browser lanes use `--automated` entry points so they never wait for
page navigation. `tools` and `rigs` always run under Node and use the host platform
name in their artifact paths. Neither is run by `configure` or by `test/unit`.

## Platform lanes and Docker

`test/lanes` groups platform validation from `test/lanes.json`; it is a separate
orchestrator, with a `.bat` entry point on Windows:

```sh
./test/lanes list
./test/lanes run macos-unit-node
./test/lanes run emscripten-browser
```

Without a lane ID, `run` selects the automated lanes supported on the host.
Required builds must already exist; the runner reports missing/stale builds and
their build commands. Manual lanes print a checklist; record the actual outcome
with `test/lanes record <lane-id> <passed|failed|blocked|manual> "note"`.
Lane definitions select specific checks, so they are not a substitute for every
top-level suite. Logs and `latest.json` live under
`artifacts/test-results/<platform>/lanes/<lane-id>/`, with the combined index at
`artifacts/test-results/lanes/latest-results.json`.

For isolated native Linux physics coverage, run `bash test/docker/physics`.
It builds with and without Spriter/Chipmunk using a read-only checkout and a
separate build volume. See [Docker validation](docker/README.md) for scope and
artifacts; it does not run the entire JavaScript or desktop suite.
