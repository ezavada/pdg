# PDG Agent Guide

This file applies to the whole repository. More specific `agents.md` files in subdirectories should take precedence for their own trees.

## Project Overview

Pixel Dust Game Engine (PDG) is an open source, professional-quality 2D game engine. Its goal is to provide system-independent game-development building blocks across platforms, with first-class use from both C++ and JavaScript. The project intentionally focuses on engine/runtime concerns such as graphics, input, timers, resources, networking, sound, sprites, tile maps, and physics rather than high-level game-specific systems like AI or content design.

The repo reflects that split:

- `src` contains the engine, bindings, application framework, JavaScript runtime helpers, and platform backends.
- `docs` contains the project overview, API documentation sources, generated docs, and engineering notes.
- `ios` contains the Xcode project, iOS packaging metadata, and an iOS test entry point.
- `test` contains C++, Node/headless, GUI/client, UI, and performance tests plus test assets.
- `tools` contains generation, packaging, profiling, and developer helper scripts.

## Build And Runtime Expectations

- Windows development uses `configure.ps1` and `make.ps1`.
- POSIX development uses `./configure` and `make`.
- Modern CMake is also present at the repo root and under `src`.
- PDG supports GUI builds and headless builds. Headless builds intentionally exclude GUI paths and may also exclude sound on some platforms.
- Node integration is a core part of the project. Public behavior often spans native code, generated bindings, and JavaScript wrappers.

## Editing Guidance

- Keep the public API aligned across C++ headers, native implementations, bindings, JavaScript wrappers, docs, and tests.
- Treat cross-platform behavior as part of the feature, not an afterthought. Changes in `src/sys` often need a pass across `win32`, `macosx`, `unix`, `ios`, or `glfw`.
- Prefer changing source-of-truth inputs over generated outputs.
- Do not hand-edit generated documentation under `docs/cxx/html`, `docs/javascript/html`, or `docs/javascript/man` edit the source .dox files instead.
- Do not hand-edit generated bindings under `src/bindings/generated`, edit the sources of those files as indication in the header comments instead.
- Treat vendored or third-party material conservatively. That includes generated docs, bundled tools, and packaged dependencies.

## Source Of Truth Notes

- C++ API overview and project description live in `README.md` and `docs/cxx/dox/index.dox`.
- JavaScript documentation is derived from IDL/doc-generation flows in `tools/make-idl.js`, `tools/generate-js-docs.sh`, and related binding sources.
- Generated binding output is produced by `tools/gen-script-interface.sh` and `tools/gen-script-interface.ps1`.
- Doxygen regeneration is driven by scripts in `tools`.
- `docs/note-ai` is useful context, but it is analysis and planning material. Verify assumptions there against current source before acting on them.

## Verification

- Pick the smallest relevant verification path for the area you change.
- For engine or API work, prefer targeted specs in `test/spec`, `test/misc`, or `test/cxx`.
- For client/UI work, use the GUI-side test wrappers under `test`.
- For headless or server-side behavior, use the Node-based spec path.
- If you change docs generation or binding generation, verify the generating script still matches the committed layout and filenames.
