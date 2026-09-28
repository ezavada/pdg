# JPEG Support Implementation

This document describes the JPEG image loading support that has been added to PDG for Linux and Windows platforms.

## Overview

JPEG support has been implemented using libjpeg-turbo 3.1.1, providing high-performance JPEG decoding with SIMD optimizations. The implementation is platform-specific:

- **macOS**: Uses native Core Graphics APIs (existing implementation)
- **Linux/Unix**: Uses libjpeg-turbo for JPEG decoding
- **Windows**: Uses libjpeg-turbo for JPEG decoding

## Key Features

- **High Performance**: libjpeg-turbo provides SIMD-optimized JPEG decoding
- **Platform Optimized**: Uses the best available method for each platform
- **Automatic Detection**: JPEG files are automatically detected by file extension and magic bytes
- **Error Handling**: Comprehensive error handling for corrupted or unsupported JPEG files
- **Memory Efficient**: Stream-based decoding with minimal memory overhead

## Build Configuration

### Dependencies

- **libjpeg-turbo 3.1.1**: High-performance JPEG library with SIMD optimizations
- **libpng**: Existing dependency for PNG support

### Build System Integration

The build system has been updated to automatically:

1. **Configure libjpeg-turbo**: Platform-specific configuration files are copied during configure
2. **Build libjpeg-turbo**: Library is built as a dependency before PDG
3. **Link against libjpeg-turbo**: PDG is linked with the compiled library

### Configuration Files

Platform-specific `jconfig.h` files are located in `src/sys/libjpeg-turbo/`:

- `jconfig-win32.h`: Windows-specific configuration
- `jconfig-unix.h`: Unix/Linux-specific configuration

These files are automatically copied to `deps/libjpeg-turbo/src/jconfig.h` during the configure process.

## Implementation Details

### Source Files

- `src/sys/image-jpeg.cpp`: Core JPEG decoding implementation using libjpeg-turbo
- `src/sys/win32/image-win32.cpp`: Windows image loading with JPEG support
- `src/sys/unix/image-unix.cpp`: Unix/Linux image loading with JPEG support

### Key Functions

- `pdg::loadJPEGImage()`: Main JPEG loading function using libjpeg-turbo
- `pdg::isJPEGFile()`: File format detection
- Platform-specific image loading functions updated to handle JPEG files

### Error Handling

The implementation includes comprehensive error handling for:
- Corrupted JPEG files
- Unsupported JPEG formats
- Memory allocation failures
- File I/O errors

## Usage

JPEG files are automatically detected and loaded when using PDG's image loading functions:

```cpp
// JPEG files are automatically detected and loaded
pdg::Image* img = pdg::Image::loadFromFile("image.jpg");
```

## Performance Benefits

- **SIMD Optimizations**: libjpeg-turbo uses CPU vector instructions for faster decoding
- **Reduced Memory Usage**: Stream-based decoding with minimal memory overhead
- **Platform Optimization**: Uses the most efficient method available for each platform

## Testing

The resource-manager spec loads JPEG fixtures and checks that they produce Image
objects. Run it with a graphics-capable runtime from the repository root:

```sh
./test/unit resourcemanager
```

On Windows, use `.\test\unit.ps1 resourcemanager`. These checks do not constitute
decoder benchmarks or comprehensive malformed-JPEG coverage.

## Platform Support

### Linux/Unix
- Full JPEG support via libjpeg-turbo
- SIMD optimizations for x86/x64 architectures
- Automatic configuration during build

### Windows
- Full JPEG support via libjpeg-turbo
- Visual Studio project integration
- SIMD optimizations for x86/x64 architectures

### macOS
- Uses existing native Core Graphics implementation
- No additional dependencies required
- Maintains existing performance characteristics

## Build Instructions

### Unix/Linux/macOS
```bash
./configure
make
```

### Windows
```cmd
configure.ps1
make.ps1 -Target pdg
```

The configure scripts will automatically:
1. Set up libjpeg-turbo build environment
2. Copy appropriate platform-specific configuration files
3. Configure CMake projects for all dependencies
4. Generate Makefiles with proper dependencies

## Troubleshooting

### Common Issues

1. **Build Failures**: Ensure libjpeg-turbo is properly configured
2. **Runtime Errors**: Check that JPEG files are valid and not corrupted
3. **Performance Issues**: Verify SIMD optimizations are enabled

### Debug Information

Enable debug output by setting the appropriate debug flags in the PDG configuration.

## Future Enhancements

Potential future improvements:
- Support for additional JPEG features (progressive JPEG, etc.)
- Integration with other image formats
- Additional optimization options
- Extended error reporting

## Dependencies

- **libjpeg-turbo 3.1.1**: High-performance JPEG library
- **libpng**: PNG support (existing)
- **CMake**: Build system (existing)

## License

The JPEG support implementation follows the same license as the PDG project. libjpeg-turbo is licensed under the IJG (Independent JPEG Group) license.
