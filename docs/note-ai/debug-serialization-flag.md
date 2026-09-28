# Debug Serialization Flag

PDG now supports a `--debug-serialization` flag that enables detailed debug output for serialization operations. This is useful for debugging serialization issues and understanding how data is being serialized.

## Usage

Due to Node.js argument parsing in embedded applications, the flag must be used with the double dash (`--`) separator:

```bash
./pdg -- --debug-serialization your-script.js
```

The double dash (`--`) tells Node.js to stop parsing arguments as Node.js options and pass everything after it to the application.

## What it does

When the `--debug-serialization` flag is present, PDG will:

1. Enable debug mode for the `ISerializer::s_DebugMode` static variable
2. Output detailed information about each serialization operation, including:
   - The type of data being serialized (e.g., `4u`, `2u`, `1u` for unsigned integers)
   - The memory address and offset
   - A hex dump of the serialized data
   - An ASCII representation of the data

## Example Output

With the flag enabled, you'll see output like:

```
Debug serialization mode enabled via --debug-serialization flag
SER: 4u   @00007/01024:  0000 | 70 64 67 [00 00 30 39] 00 00 00 00 00 00 00 00 00 00 00 00 00  | pdg..09.............
SER: 2u   @00009/01024:  0000 | 70 64 67 00 00 30 39 [1A 85] 00 00 00 00 00 00 00 00 00 00 00  | pdg..09.............
SER: 1u   @00010/01024:  0000 | 70 64 67 00 00 30 39 1A 85 [FF] 00 00 00 00 00 00 00 00 00 00  | pdg..09.............
```

Where:
- `SER: 4u` indicates a 4-byte unsigned integer is being serialized
- `@00007/01024` shows the memory address and buffer size
- The hex dump shows the actual bytes being written
- The ASCII representation shows printable characters

## Alternative: JavaScript API

You can also enable debug serialization programmatically from JavaScript:

```javascript
pdg.setSerializationDebugMode(true);
```

This is equivalent to using the command line flag but can be controlled from within your application code.

## Implementation Details

The flag is processed in the JavaScript bootstrap code (`pdg_main_v24.js`) and uses the existing `setSerializationDebugMode()` API to enable debug output. This approach leverages the existing serialization debug infrastructure without requiring changes to the C++ code.
