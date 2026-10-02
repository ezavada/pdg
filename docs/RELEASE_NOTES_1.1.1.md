# PDG v1.1.1 release notes

PDG 1.1.1 improves Linux GUI support, fixes Windows runtime and build issues,
repairs macOS native test launching, and simplifies the cross-platform test
workflow.

Version: **1.1.1**. These notes compare against the public repository's
**v1.1.0** tag, commit `1b0622ce6f1ba9aad7bd430ec309c430cba2358c`.
They cover development changes through `439214475` and the 1.1.1 version updates.
The animation, physics, snapshots, benchmark optimizations and WebAssembly
Release packaging already shipped in v1.1.0 are described in the
[previous release notes](RELEASE_NOTES_1.1.md).

## Runtime fixes

- **Spriter collision boxes:** identify active boxes by their authored names and
  current entity objects. Bounds, counts, names, named/indexed lookups and point
  collision queries use the same active-box collection across runtime backends.
- **JavaScript fitting constants:** export `fit_FillKeepProportions` as an alias
  of `fit_Overflow` in V8, matching the other interfaces.
- **Windows configuration:** initialize resource-string buffers and retain the
  registry path after creating a configuration key.
- **Windows file paths:** initialize the Node addon's application directory from
  its launch working directory, matching the other platforms.
- **Windows sound:** initialize the DirectShow graph pointer and update the
  Sound object's load status instead of a shadowing local variable. The visual
  sound test also handles platform playback differences more reliably.
- **Windows compatibility:** fix PNG size checks affected by Windows macros,
  correct an AnimatedAttributes transform override's return type, and read the
  uncapped-performance setting through the Windows environment API.
- Initialize the counterpart Sprite before checking an existing serialized
  joint, and replace TileLayer destruction sentinels with null pointers.

## Builds and packaging

- **Linux GUI:** add the missing OpenGL platform implementation, improve graphics
  dependency setup, and fix GLFW Wayland compilation. Headless builds retain
  their separate configuration.
- **Node build caches:** restore architecture-specific output links before using
  cached libraries and verify that the cached executable can initialize
  JavaScript. A matching version string alone no longer marks a broken runtime
  as usable. POSIX builds normalize CRLF embedded JavaScript inputs when needed.
- **WSL:** reject builds from Windows-mounted checkouts with instructions to use
  WSL's Linux filesystem.
- **Windows tooling:** improve Node output junctions, Python discovery, CMake
  process handling, static runtime consistency, and Debug/Release executable
  selection. Batch build entry points delegate to the PowerShell build driver.
- **macOS native launchers:** point `pdg` and `test/pdg` at the actual executable
  inside the app bundle. This fixes `test/unit` reporting "No current PDG build"
  after a successful Debug build.
- Respect requested build parallelism and avoid passing unusable GNU make
  jobserver settings into the npm/node-gyp subprocess. Install Node build tools
  in the architecture-specific workspace.
- Reduce compiler and linker warnings across Linux, Windows and macOS. The
  addon symbol check recognizes zlib functions supplied by Node while retaining
  reports of unexpected symbols.
- Build bcpp and the standalone performance-measurement test as **C++20**.
  bcpp's build copy uses bounded `snprintf` calls. Benchmark JSON includes are
  treated as third-party headers; their existing C++17 exception remains.
- Synchronize release metadata across CMake, the native version header, the Node
  package template, Doxygen, macOS app bundles and iOS. The version-update helper
  also repairs stale version fields and works without a configured checkout.

## Test workflow and upgrade notes

Use the shared unit runner in scripts and CI:

| Previous entry point | Current entry point |
| --- | --- |
| `test/client` | `test/unit` |
| `test/node` | `test/unit --node` |
| Browser `test/client.html` | `test/unit.html`, normally launched by `test/unit --web` |
| `test/ios --client` | `test/ios --unit`, or `test/unit --ios` |

Windows uses the corresponding `.ps1` wrappers. Runtime selection remains
explicit: **plain `test/unit` runs the native PDG build**; `--node` selects the
addon. Native unit runs also include configured CTest suites. Test lanes, release
scripts and debugger configurations use the consolidated entry points.

The Node dependency remains **v24.21.0**. C++ applications still require a C++20
compiler and standard library with `std::format`; iOS still requires **16.3 or
later**. Rebuild native binaries and the Node addon when upgrading. The v1.1.0
API migration guidance continues to apply; this patch does not repeat that API
reorganization or introduce a new snapshot format.

The benchmark helper's bundled JSON library remains isolated in a C++17 source
file. SCON/JSON animation loading, Spriter atlas loading and authored soundline
playback remain unsupported; the warning cleanup does not enable them.

## Validation

Local macOS, Windows, and Linux checks included all **16 native CTest suites**
and **1,437 JavaScript tests through native PDG**, with zero failures, plus **93
targeted Node tests** for Spriter and serialization. Both C++ benchmarks rebuilt
without warnings. bcpp rebuilt without warnings under C++20, preserved formatting
output across six comparisons, and the performance-measurement test passed.

The 1.1.1 native rebuild repeated the full native unit run successfully and
reported version 1.1.1. Release-tag validation, Apple bundle metadata, generated
JavaScript API metadata and the version-update helper were also checked.

These are recorded checks for the changes, not a claim that every platform's
release assets have been built or tested. Follow the [test guide](../test/README.md)
and platform release scripts for final artifact validation.
