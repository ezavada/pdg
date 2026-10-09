Pixel Dust Game Engine (PDG)
============================

PDG is an open source, professional quality 2D game engine. It provides 
system independent abstractions of common elements needed by game developers. 
It can be used directly from C++ or used from scripting languages like 
Javascript.

This is the documentation for the Javascript API.

Features
--------
- integrated with Node.js v24.21.0 LTS
- high performance Javascript via Google's V8 engine
- event driven
- cross platform
- 2D OpenGL hardware accelerated graphics
- resource and file management
- user input handling
- timers
- networking
- efficient serialization and deserialization
- sound
- animation including jQuery-like easing functions
- sprites
- bone based animation via [Brash Monkey's Spriter](https://brashmonkey.com/spriter-pro/)
- tile based maps
- physics support using [Chipmunk Physics](https://chipmunk-physics.net/)
- works with node inspector for Javascript debugging
- interactive Javascript console mode

Build requirements
------------------

PDG requires a C++20 compiler and standard library, including `std::format`.
The iOS application requires **iOS 16.3 or later**; both Debug and Release
configurations use that deployment target. Use an Xcode toolchain with C++20
library support when building the iOS project.

The `deps/node` submodule pins Node.js **v24.21.0**. After updating the checkout,
run `git submodule update --init deps/node`, `./configure`, and `make pdg pdg-node`
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
upgrade guidance since v1.1.1. The [v1.1.1 release notes](docs/RELEASE_NOTES_1.1.1.md) cover fixes since
v1.1.0. The [v1.1.0 release notes](docs/RELEASE_NOTES_1.1.md) cover features,
changes from v1.0, and API migration guidance.

For unit tests, rig regressions, tooling checks, visual pages, and interactive
demos, see the [testing guide](test/README.md): `test/unit`, `test/rigs`,
`test/tools`, `test/ui`, and `test/demo`
(with `.sh` and `.ps1` launchers).

The [TypeScript guide](docs/typescript/README.md) covers generated engine declarations,
the separate TypeScript MVC implementation, build commands, and deferred IDL contracts.

Documentation (HTML and Man pages) are included in the docs directory, and can also be found online (along with comment areas) at:

http://ezavada.com/pdg/javascript/html/

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

PDG is focused on making a broad array of capabilities available to developers 
regardless of the OS platform they are targeting. Currently it works on Mac OS X, 
Windows, and iOS. The Non-GUI build (and Node.js plugin) also work on Linux.

The PDG API is designed to make simple things easy to do, without adding undue 
complexity to more complicated problems.

History
-------

PDG was originally developed in 2003 by Ed Zavada of Pixel Dust Games for use in Catan Online. It was later updated by Dream Rock Studios for use in their game
Parthenon. Those updates included OpenGL hardware acceleration, a sprite engine, and iOS support. In 2012 it was further updated with Chipmunk physics, Javascript
bindings, and then made open source under the MIT license.

Usage assumptions
-----------------

PDG is supplied in several different forms:
- a C++20 SDK
- a Javascript SDK (that will eventually include a binary runtime for Mac OS X and Windows)
- an npm package for Node.js for server side programming

No languages other than Javascript and C++ are currently supported, though Ruby bindings have been created in the past. The Javascript bindings could serve as a guide for anyone wishing to add support for other languages.

Roles and Responsibilities
--------------------------

PDG is integrated with Node.js, so all of the excellent networking, file i/o, encyption, process management and debugging facilities of Node.js are available to you. For multiplayer games you can write your server with Node.js, and use PDG as an add-on module if needed. On the client side, you can run as a double clickable application with PDG providing most of the functionality, and Node.js modules available for networking and so forth.

In most cases PDG does not duplicate functionality already in Node.js. There are, however a few notable exceptions:

- **Timers**: PDG provides its own TimerManager, which greatly improves on the functionality available through standard Javascript/Node.js.  
- **Events**: PDG has its own event system, and does not relay events through Node.js's EventEmitter. That would be easy to add at an application level if desired.
- **Logging**: PDG has a LogManager that writes time-stamped log entries with runtime configurable logging levels.

What's missing?
---------------

There are a few things we'd like to add to PDG, but haven't had time to build yet. Some
are pretty simple, others rather larger. In no particular order, they are:

- Binary distributions and release builds of the runtime
- Pure Javascript HTML5 implementation so you can run your game in a browser
- Port.drawRadialGradient()
- Applying Chipmunk Physics to SCML based sprites
- A map editor for tile layers
- Particle System (similar to sprites but optimized for particle effects)
- Example Code
- More comprehensive Unit Tests
- FluidLayer for simulating floating objects
- OuterSpaceLayer for simulating gravitational attraction between objects
- Android port
- Support for graphics on Linux
- Support for rotation of TileLayers
- DiagonalTileLayer for Ultima Online style isometric maps
- HexGridTileLayer for board games

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

For an existing checkout, initialize dependencies with
`git submodule update --init --recursive`. Build the Node addon with `make pdg-node`
(Windows: `.\make pdg-node`) before running `test/unit --node` or
`test/rigs`. See the [testing guide](test/README.md) for browser, iOS, headless,
performance, and tooling checks.
