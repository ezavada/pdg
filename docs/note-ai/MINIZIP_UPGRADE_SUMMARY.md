# Resource archive integration

PDG uses the bundled minizip-ng compatibility API for ZIP-backed resource files.
[Resource loading](../../src/sys/resource.cpp) includes `compat/unzip.h`;
[src/CMakeLists.txt](../../src/CMakeLists.txt) builds the minizip sources and
platform-specific stream/crypto support into the native library.

The dependency's available features do not imply that every archive option is
exposed by PDG ResourceManager. Keep archive behavior and error handling aligned
with the current resource API and fixtures.

Run `./test/unit resourcemanager` for resource-file lifecycle, search-path and
asset-loading checks. Use a graphics-capable runtime for image fixtures; the
spec gates unsupported capabilities. Add `--node`, `--web --automated`, or `--ios`
to validate another runtime. See the [test guide](../../test/README.md).
