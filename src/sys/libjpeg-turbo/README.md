# libjpeg-turbo Configuration Files

This directory contains platform-specific `jconfig.h` files for libjpeg-turbo configuration.

## Files

- `jconfig-win32.h` - Windows-specific configuration
- `jconfig-unix.h` - Unix/Linux-specific configuration

## Purpose

These files are automatically copied to `deps/libjpeg-turbo/src/jconfig.h` during the configure process to provide the correct platform-specific configuration for libjpeg-turbo.

## Configuration Details

Both files include:
- JPEG library version definitions
- libjpeg-turbo version information
- Support for arithmetic coding
- Support for in-memory source/destination managers
- SIMD optimization support
- 8-bit sample precision configuration

### Windows-specific (`jconfig-win32.h`)
- Windows-specific type definitions (boolean, INT16, INT32)
- Windows compatibility macros
- Proper header inclusion guards

### Unix/Linux-specific (`jconfig-unix.h`)
- Standard Unix/Linux configuration
- Minimal platform-specific overrides

## Usage

The configure scripts automatically select and copy the appropriate file:
- `configure` (Unix/Linux/macOS): Copies based on platform detection
- `configure.bat` (Windows): Always copies `jconfig-win32.h`

## Modifications

If you need to modify the configuration:
1. Edit the appropriate platform-specific file in this directory
2. Re-run the configure script to apply changes
3. Rebuild the project

**Note**: Do not edit `deps/libjpeg-turbo/src/jconfig.h` directly as it will be overwritten during the next configure run. 