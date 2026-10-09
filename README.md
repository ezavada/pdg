Pixel Dust Game Engine (PDG)
============================

PDG is an open source 2D game engine. It provides graphics, animation, physics,
input, resources and networking across platforms for games written in C++ or
JavaScript. TypeScript applications compile to
JavaScript using the generated engine declarations and optional TypeScript MVC
framework.

Version **1.2.0** supports native desktop applications, headless servers, iOS,
and Emscripten/WebAssembly browser applications. See the
[v1.2.0 release notes](docs/RELEASE_NOTES_1.2.md) for new features and breaking
API and snapshot changes, and [GitHub releases](https://github.com/ezavada/pdg/releases)
for runtime bundles.

Features
--------

- **C++ and JavaScript runtimes:** C++20 APIs, V8 scripting integrated with
  Node.js v24.21.0, a headless Node addon, Node inspector debugging and an
  interactive JavaScript console. Browser and iOS scripting use their own
  runtime integrations.
- **Cross-platform rendering:** hardware-accelerated 2D OpenGL graphics on
  macOS, Windows and Linux, plus iOS and WebAssembly browser builds. Drawing
  artwork supports editable text, paths, linear/radial gradients, animated
  attributes, clipping and offscreen surfaces.
- **Scenes and timing:** independent scenes with owned layers, physics worlds,
  timers and subscriptions; pause, time scaling, fixed-step simulation,
  optional render interpolation and manual advancement.
- **Animated cameras:** shared views, viewports, parallax, target following,
  smoothing, deadzones, look-ahead, pixel snapping and world/view conversions.
  Camera effects include zoom, flashes, fades, cuts, subject matching, wipes,
  luminance transitions and whip pans.
- **Sprites and tile maps:** composable Sprite-owned Parts, attachments, artwork
  and colliders, plus repeating tile maps rendered through the camera transform.
- **Skeletal animation:** [Spriter](https://brashmonkey.com/spriter-pro/) SCML
  playback, editable poses, blending, live Bone controls and IK. Procedural
  FABRIK solves longer chains; jiggle adds chain springs or filtered IK targets.
- **Animation composition:** easing, reusable named scripts, parallel and
  sequential groups, conditions, repeats, yoyo, marks, events and playback
  controls. Troupes coordinate multiple targets with optional staggered starts.
- **Physics and queries:** [Chipmunk](https://chipmunk-physics.net/) bodies,
  constraints, articulated Parts and physical animation rigs, including
  kinematic, dynamic and driven control. Scene raycasts, sweeps, nearest-point
  and overlap queries also work on bodyless colliders and paused scenes.
- **Particles:** template-based emitters, bursts, continuous emission, lifetimes,
  optional physics and configurable ribbon trails.
- **Networking:** native TCP/UDP, WebSocket and WebTransport through the
  JavaScript interfaces, with transport selection, reliable/datagram delivery,
  TLS for secure web transports and configurable limits. An optional C++
  networking library interoperates with the same protocol; iOS provides clients.
- **Resources and snapshots:** file/resource management, owned binary byte
  arrays, serialization and supported Sprite/Layer snapshots with shared
  artwork, animation resources, Parts and physics state.
- **Application services:** input, events, timers, logging and sound on supported
  targets, plus MVC views, controllers, controls, dialogs and themes in C++,
  JavaScript and a separate TypeScript implementation.
- **Development tools:** generated TypeScript declarations, TypeDoc and Doxygen
  references, examples, interactive demos, native/Node/browser tests, rig checks
  and performance benchmarks.

Capabilities vary by build: headless builds omit graphics, the Node addon is
headless, and the Linux desktop build currently omits sound. Spriter animation
and Chipmunk physics can be disabled separately; physical animation rigs require
both. See the [testing guide](test/README.md) and
[TypeScript guide](docs/typescript/README.md) for runtime-specific workflows.

Build requirements
------------------

PDG requires a C++20 compiler and standard library, including `std::format`.
The iOS application requires **iOS 16.3 or later**; both Debug and Release
configurations use that deployment target. Use an Xcode toolchain with C++20
library support when building the iOS project.

The `deps/node` submodule pins Node.js **v24.21.0**. After updating the checkout,
run `git submodule update --init --recursive`, `./configure`, and `make pdg pdg-node`
(Windows: `configure.ps1` followed by `make pdg` and
`make pdg-node`). Node builds record their source version so a version
change triggers a rebuild of the cached runtime and libraries. Node builds
accept Python 3.9 through 3.14.

`make pdg-node` builds and installs the local addon. For a release version update,
run `tools/version-update.sh MAJOR.MINOR.PATCH` (requires Python 3), then regenerate
documentation and rebuild the release artifacts.

Documentation
-------------

Read the [v1.2.0 release notes](docs/RELEASE_NOTES_1.2.md) for new features and
upgrade guidance since v1.1.1. The
[v1.1.1 release notes](docs/RELEASE_NOTES_1.1.1.md) cover fixes since v1.1.0. The [v1.1.0 release notes](docs/RELEASE_NOTES_1.1.md) cover features,
changes from v1.0, and API migration guidance.

For unit tests, rig regressions, tooling checks, visual pages, and interactive
demos, see the [testing guide](test/README.md): `test/unit`, `test/rigs`,
`test/tools`, `test/ui`, and `test/demo`
(with `.sh` and `.ps1` launchers).

The [TypeScript guide](docs/typescript/README.md) covers generated engine declarations,
the separate TypeScript MVC implementation, build commands, and deferred IDL contracts.

Documentation (HTML and Man pages) are included in the docs directory, or as a [separate download](https://github.com/ezavada/pdg/releases/download/v1.2.0/pdg-docs-v1.2.0.zip).

To regenerate the documentation locally, run `make docs` after `./configure` (or run
`./tools/build-docs.sh` directly). This runs TypeDoc for the TypeScript reference and Doxygen for the C++ HTML, JavaScript
HTML, and JavaScript manual pages, then packages the results into a ZIP archive.
Missing Doxygen and Graphviz tools are installed automatically on supported systems.

The regenerated pages replace `docs/cxx/html/`, `docs/javascript/html/`, and
`docs/javascript/man/`, and `docs/typescript/html/`, so existing local bookmarks show the current API. These
are generated directories; keep documentation edits in the source headers and
`.dox` files. The complete site is also available at
`artifacts/docs/site/pdg-docs-v<VERSION>/index.html`, where `<VERSION>` is the value
in the root `VERSION` file. The archive and SHA-256 checksum are in
`artifacts/docs/`, and Doxygen progress and warning logs are in
`artifacts/docs/work/`. Use `./tools/build-docs.sh --no-local-copy` when only the
artifact site and archive are needed.

JavaScript documentation uses the declarations in `docs/javascript/pdg-js.h`.
After API changes, build the current runtime with `make pdg`, then run
`./tools/build-docs.sh --refresh-api` to refresh those declarations from the runtime
before regenerating and packaging the documentation.

To audit class coverage on both Topics pages after generation, run
`node tools/check-missing-docs.js --topics artifacts/docs/site/pdg-docs-v<VERSION>`.
The check verifies topic membership and links for every indexed class and structure,
checks the JavaScript class index against the generated API inventory, and verifies
that every public event type appears in Events.

Design Goals
------------

PDG provides engine and runtime capabilities across macOS, Windows, Linux,
iOS and WebAssembly browsers, with graphical and headless builds. Platform
services and runtime APIs may vary slightly depend on the selected build.

The PDG API is designed to make simple things easy to do, without adding undue 
complexity to more complicated problems.

History
-------

PDG was originally developed in 2003 by Ed Zavada of Pixel Dust Games for use in Catan Online. It was later updated by Dream Rock Studios for use in their game
Parthenon. Those updates included OpenGL hardware acceleration, a sprite engine, and iOS support. In 2012 it was further updated with Chipmunk physics, Javascript
bindings, and then made open source under the MIT license.

Usage assumptions
-----------------

PDG can be used as:

- a C++20 SDK for native applications;
- a JavaScript runtime for desktop applications, with runtime bundles available
  through [GitHub releases](https://github.com/ezavada/pdg/releases);
- a Node.js addon for headless/server-side programming;
- an Emscripten/WebAssembly runtime for browser applications;
- an iOS application integration with JavaScriptCore scripting;
- a TypeScript development workflow using generated declarations and compiled
  JavaScript, including the separate TypeScript MVC framework.

TypeScript declarations are opt-in and describe the native GUI inventory;
applications must select APIs available in their actual runtime. See the
[TypeScript guide](docs/typescript/README.md) for setup and limitations. Other
language bindings can use the C++ API and existing bindings as a starting point.

Roles and Responsibilities
--------------------------

The desktop JavaScript runtime integrates Node.js facilities for file I/O,
encryption, process management and debugging. Multiplayer servers can use the
headless Node addon; clients can use native applications, iOS or the browser
runtime. PDG's networking interfaces provide compatible messages across supported
transports. Browser and iOS applications use the services supplied by those
platforms rather than the full Node.js environment.

In most cases PDG does not duplicate functionality already in Node.js. There are, however a few notable exceptions:

- **Timers**: PDG provides its own TimerManager, which greatly improves on the functionality available through standard Javascript/Node.js.  
- **Events**: PDG has its own event system, and does not relay events through Node.js's EventEmitter. That would be easy to add at an application level if desired.
- **Logging**: PDG has a LogManager that writes time-stamped log entries with runtime configurable logging levels.

What's missing?
---------------

PDG still has gaps in authoring tools and specialized runtime support:

- An integrated tile-map editor.
- Dedicated isometric and hex-grid tile layers.
- Fluid simulation and gravitational-attraction layers.
- An Android port.
- Spriter SCON/JSON loading, atlas loading and authored soundline playback.
- Sound support on Linux.
- Input management to simplify mapping keyboard/mouse/control inputs to actions.
- Improvements beyond just basic sound play and controls.

Some existing features also have limits. Portable snapshots reject runtime
callbacks and active camera transitions, and do not save every animation/physics
configuration. The TypeScript declaration inventory does not yet provide
separate browser/iOS capability profiles or automatic npm root types. Consult the
[v1.2.0 migration notes](docs/RELEASE_NOTES_1.2.md#compatibility-and-migration) and
[TypeScript guide](docs/typescript/README.md) before relying on those contracts.

Examples, demos and automated tests are included in the repository. Start with
[test/README.md](test/README.md) and the
[TypeScript examples](docs/typescript/examples).

Game Kits
---------

PDG doesn't provide any implementation of higher level functionality commonly used in 
games, such as AI, pathfinding, dialog trees, tooltips, character classes, dynamic map 
generation, segmented loading of large maps, etc.. You should be able to build those 
things as needed for your game.

We do plan to build Game Kits for a variety of game genres on top of PDG, so check to
see if they are available and have what you need.


Building From Source
--------------------

Note that PDG builds Node.js from source, which takes some time. However, it
should only do this for the first build -- even `make clean` won't remove the
cached Node build.

**Windows**:

Install Git, CMake 3.16 or later, Python in the supported range above, and a
Visual Studio C++ toolchain with C++20 standard-library support. In a developer
PowerShell session:

```powershell
git clone --recurse-submodules git@github.com:ezavada/pdg.git pdg
cd pdg
.\configure.ps1
.\make pdg
.\test\unit.ps1
.\test\ui.ps1
.\test\demo.ps1
```

**macOS**:

Install Git, CMake 3.16 or later, Python in the supported range above, and Xcode
with its command-line tools and C++20 standard-library support. In Terminal:

```sh
git clone --recurse-submodules git@github.com:ezavada/pdg.git pdg
cd pdg
./configure
make pdg
./test/unit
./test/ui
./test/demo
```

**Linux**:

Install Git, CMake, Python and a C++20 toolchain with the standard-library support
listed above. Graphical builds also need OpenGL/GLU, FreeType, Fontconfig, JPEG
and GLFW's X11/Wayland development dependencies; `./configure` checks the build
setup.

```sh
git clone --recurse-submodules git@github.com:ezavada/pdg.git pdg
cd pdg
./configure
make pdg
./test/unit
./test/ui
./test/demo
```

Run graphical tests in a desktop session, or use Xvfb for automated Linux checks.
For Emscripten browser builds and iOS, follow the platform commands in the
[testing guide](test/README.md).

For an existing checkout, initialize dependencies with
`git submodule update --init --recursive`. Build the Node addon with `make pdg-node`
(Windows: `.\make pdg-node`) before running `test/unit --node` or
`test/rigs`. See the [testing guide](test/README.md) for browser, iOS, headless,
performance, and tooling checks.
