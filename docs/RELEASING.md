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

On macOS or a Windows environment with GNU Make:

    make release RELEASE_TAG=v1.0.0

When RELEASE_TAG is omitted, HEAD must be at an exact release tag. The
platform scripts can also be called directly:

    ./tools/release-macos.sh --tag v1.0.0

On Windows, from PowerShell:

    .\tools\release-windows.ps1 -Tag v1.0.0
    .\make.ps1 -Target release -Tag v1.0.0

Use --configure on macOS or -Configure on Windows to regenerate all dependency
build trees first. An unconfigured checkout is configured automatically. The
Windows configuration expects CMake, Python, and Visual Studio Build Tools to
already be installed.

Each script performs version validation, an optimized Release build, native
CTest tests, the headless JavaScript suite, the GUI/client JavaScript suite,
and staged-binary smoke tests. It also builds pdg-debug with DEBUG=1 and full
symbols. macOS includes a dSYM when dsymutil is available; Windows includes
the debug PDB.

Each platform writes two ZIPs and their SHA-256 files to artifacts/release:

- `pdg-vVERSION-PLATFORM-ARCH.zip` contains only the optimized pdg application.
- `pdg-debug-vVERSION-PLATFORM-ARCH.zip` contains the unstripped pdg-debug
  application and its external symbol bundle.

Both packages also contain LICENSE, README.md, VERSION, and the authoritative
notices for bundled dependencies under THIRD_PARTY_LICENSES. Keeping the debug
application and symbols separate lets runtime users download the much smaller
optimized package.

## Publish on GitHub

After running the local release successfully, create and push the matching
tag:

    git tag v1.0.0
    git push origin v1.0.0

The release workflow builds independently on macOS and Windows. It creates a
GitHub Release only after both local release scripts succeed, and exposes the
separate optimized and debug ZIPs with their SHA-256 files.
