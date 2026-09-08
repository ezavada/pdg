# Releasing PDG

PDG releases are built and tested by repository scripts. GitHub Actions only
invokes those scripts and publishes the resulting assets.

## Version contract

A release uses a tag of the form vMAJOR.MINOR.PATCH. The tag (without its
leading v), the first line of VERSION, and the version in the root
project(PDG VERSION ...) declaration must match exactly.

Validate a prospective release locally without creating a tag:

    cmake -DRELEASE_TAG=v1.0.0 -P cmake/ValidateReleaseVersion.cmake

## Build release assets locally

On Linux, macOS, or a Windows environment with GNU Make:

    make release RELEASE_TAG=v1.0.0

Generate all C++, JavaScript, manual-page, and bundled third-party
documentation locally:

    make docs

This installs Doxygen and Graphviz with Homebrew on macOS or apt-get on Linux
when either tool is missing. The generated site and versioned documentation
ZIP are written under artifacts/docs. Maintainers can run
`tools/build-docs.sh --refresh-api` after building PDG when the generated
JavaScript API description also needs to be refreshed.

When RELEASE_TAG is omitted, HEAD must be at an exact release tag. The
platform scripts can also be called directly:

    ./tools/release-linux.sh --tag v1.0.0
    ./tools/release-macos.sh --tag v1.0.0
    ./tools/release-emscripten.sh --tag v1.0.0

On Windows, from PowerShell:

    .\tools\release-windows.ps1 -Tag v1.0.0
    .\make.ps1 -Target release -Tag v1.0.0

Use --configure on Linux or macOS, or -Configure on Windows, to regenerate all
dependency build trees first. An unconfigured checkout is configured
automatically. The Windows configuration expects CMake, Python, and Visual
Studio Build Tools to already be installed.

Bundled Node.js requires Python 3.9 through 3.13. The POSIX configure script
selects a compatible versioned or system interpreter automatically, even when
an unsupported newer `python3` appears first in `PATH`. Set
`PDG_NODE_PYTHON=/path/to/python3` to override that selection.

Each native script performs version validation, an optimized Release build,
native CTest tests, the headless JavaScript suite, the GUI/client JavaScript
suite, and staged-binary smoke tests. It also builds pdg-debug with DEBUG=1
and full symbols. macOS includes a dSYM when dsymutil is available; Windows
includes the debug PDB.

The native platform scripts write two architecture-specific ZIPs and their SHA-256 files to
artifacts/release:

- `pdg-vVERSION-PLATFORM-ARCH.zip` contains only the optimized pdg application.
- `pdg-debug-vVERSION-PLATFORM-ARCH.zip` contains the unstripped pdg-debug
  application and its external symbol bundle.

Both packages also contain LICENSE, README.md, VERSION, and the authoritative
notices for bundled dependencies under THIRD_PARTY_LICENSES. Keeping the debug
application and symbols separate lets runtime users download the much smaller
optimized package.

Native build products use a common `build/PLATFORM/ARCHITECTURE` layout:

    build/darwin/arm64
    build/linux/x86_64
    build/linux/arm64
    build/win32/x86_64

Node and V8 outputs are isolated under `build/PLATFORM/ARCHITECTURE/node/out`.
Emscripten follows the same convention at `build/wasm/wasm32`, leaving room
for a future `wasm64` build without another directory migration.

The Emscripten script performs a clean WebAssembly build in `build/wasm/wasm32`, runs
the browser client and UI suites, and writes `pdg-vVERSION-emscripten-wasm32.zip` plus its
SHA-256 file to `artifacts/release`. The package contains `libpdg.js`,
`libpdg.wasm`, `libpdg.wasm.map`, and the applicable licenses. These build
outputs are intentionally ignored by Git and are published only as release
artifacts.

## Publish on GitHub

After running the local release successfully, create and push the matching
tag:

    git tag v1.0.0
    git push origin v1.0.0

The release workflow builds independently on Linux x86_64, Linux arm64, macOS,
Windows, and Emscripten, and also builds platform-neutral documentation. It
creates a GitHub Release only after every job succeeds and exposes the separate optimized,
debug, WebAssembly, and documentation ZIPs with their SHA-256 files.
