# PDG with TypeScript

PDG TypeScript support has two parts: engine declarations generated from the
checked-in JavaScript IDL, and a separate MVC implementation written in
TypeScript. The MVC source lives alongside the C++ and JavaScript frameworks;
compiling it does not replace either one.

The declarations describe the checked-in native GUI inventory. This
inventory is not a promise of availability in every runtime: in particular,
the Node addon is headless and cannot run the graphical MVC framework.

## Build and check

From the repository root, using Node and npm:

```sh
npm ci --prefix tools/typescript --ignore-scripts
npm run build --prefix tools/typescript
npm test --prefix tools/typescript
npm run docs --prefix tools/typescript
```

The build writes:

- `types/index.d.ts`: generated engine declarations; no native build is needed.
- `types/coverage.json`: coverage, intentional construction restrictions, runtime profile and input hash.
- `build/typescript/mvc-app`: compiled MVC JavaScript, declarations, source maps.
- `build/typescript/package`: relocatable declarations and compiled MVC modules, with declared type dependencies.
- `docs/typescript/html`: TypeDoc reference and guides (from the docs command).

The distribution is private build output, not a separately published npm package.
Its root is type-only. Import the engine through the actual PDG runtime, not by
executing the declaration package. Its `mvc-app` subdirectory contains executable
CommonJS modules. It requires an initialized graphical PDG runtime providing
`globalThis.pdg` before any MVC module is loaded.

## Engine imports

Compile TypeScript to JavaScript, then use the same PDG launcher as JavaScript.
For a project in this checkout, map the existing runtime module to its opt-in
inventory declarations:

```json
{
  "compilerOptions": {
    "target": "ES2022",
    "module": "CommonJS",
    "strict": true,
    "paths": { "pdg": ["./types/index.d.ts"] },
    "outDir": "./build/my-game"
  }
}
```

```ts
import pdg = require('pdg');
const position = new pdg.Point(32, 48);
```

Adjust the paths relative to your project's tsconfig. With the built distribution,
point `pdg` at its `index.d.ts`. A compiler path mapping changes type resolution;
it does not install a runtime or rewrite imports. Do not import `pdg/types` at
runtime. Automatic npm root types are deferred until runtime availability is
represented in the IDL.

For native PDG, launch the emitted `.js` using `pdg`. For the Node addon, use only
APIs that its headless build supplies. Browser applications must bundle the emitted
modules into their existing PDG web loading flow after initialization. Browser
and iOS profiles and packaged-runtime validation are deferred; neither is implied
by compiling against this inventory. Direct `.ts` execution is not part of this
workflow.

## MVC

Use the separate classes, for example:

```ts
import { Application } from './mvc-app/Application';
import { Controller } from './mvc-app/Controller';
import { Button } from './mvc-app/Button';
```

Here `./mvc-app` denotes the compiled MVC directory beside your application. You
can also compile the source modules with your project, preserving the MVC
compiler configuration (including `useDefineForClassFields: false`). The barrel retains module
namespaces (`framework.View.View`, `framework.Controller.Controller`) and exports
shared constants. Individual module imports are generally simpler for subclasses.

Controllers own view registration and event handlers. Construct an `Application`,
a root `Controller` with a graphical port, and views attached to that controller.
Call `controller.addView(view, id)` to register a view. Override `drawSelf(port,
frameNum)` for custom drawing. Views extend the engine's `AnimatedAttributes`;
fluent animation calls preserve the concrete TypeScript subclass for call chaining.
Root controllers advance animations during `PortDraw`; durations use seconds.
Destroy controllers and clean up the application when finished to release handlers.

The implementation includes observers, theme attributes, buttons, checkboxes,
radio buttons, edit fields, lists, scrollbars, scrolling views, popup menus,
dialogs, message views, modal controllers, and touch controllers. Its control-hook input records
are MVC-facing subsets. The native boundary uses the generated engine types;
engine callbacks and their payloads are described in the IDL.

The [MVC example](examples/mvc-screen.ts) and [animation example](examples/animation.ts)
are checked by `npm test`. To run the existing native behavioral tests against the
compiled implementation on POSIX:

```sh
PDG_MVC_MODULE="$PWD/build/typescript/mvc-app" ./test/unit mvc-app mvc_animation mvc_typescript
```

On Windows, set `$env:PDG_MVC_MODULE` to the absolute compiled directory and run
`./test/unit.ps1 mvc-app mvc_animation mvc_typescript`. Omit the environment variable to test the
existing JavaScript implementation.

The native/Node inventory references Node Buffer and Socket declarations. A
consumer using a path mapping must install `@types/node` (the tooling pins
`24.19.1`); the generated distribution declares this dependency in its manifest.
Do not select these declarations for browser/iOS just to satisfy the compiler.

## Documentation

TypeDoc provides the TypeScript signatures, IDL descriptions, shared schema
comments, and the MVC source reference. Doxygen continues to provide the C++ and
JavaScript references. The combined documentation build (`tools/build-docs.sh`)
publishes all three sites alongside each other.

The TypeScript reference currently uses prose present in the IDL and TypeScript
source. Full Doxygen XML prose conversion remains a follow-up; use the JavaScript
reference for extended behavioral notes that are not yet carried in IDL. No
second handwritten engine method reference is maintained here.

## Binary data

Binary script interfaces use `Uint8Array` (the generated `ByteArray` alias),
including Node `Buffer` subclasses. JavaScript strings remain text; they are
not accepted by `serialize_mem()`, `sizeof_mem()`, `setDataPtr()`,
`loadMapData()`, or `binaryDump()` as byte containers.

```ts
const writer = new pdg.Serializer();
writer.serialize_mem(new Uint8Array([0, 128, 255]));
const packet = writer.getDataPtr().getData();
const reader = new pdg.Deserializer();
reader.setDataPtr(packet);
const payload: Uint8Array = reader.deserialize_mem().getData();
```

`MemBlock.getData()` and `getBytes()` return independent copies.
`ResourceManager.getResource()` returns an owned Uint8Array or `false`.
`Deserializer.setDataPtr(array)` takes an owned snapshot of the array's visible
bytes; later source changes do not affect the reader. Passing a MemBlock instead
retains the borrowing behavior: keep its owner alive and storage unchanged.
Array offsets and lengths are honored. Detached/shared arrays are unsupported;
use an ordinary attached Uint8Array for these operations.

Existing binary-string callers must supply bytes explicitly. Decode resource
bytes as UTF-8 only when consuming a text resource, rather than using a string
to transport binary data. `MemBlock.toBuffer()` has been removed. When a Node API
requires a Buffer, share the owned snapshot to avoid an additional payload copy:

```ts
const bytes = block.getData();
const buffer = Buffer.from(bytes.buffer, bytes.byteOffset, bytes.byteLength);
```

The shorter `Buffer.from(block.getData())` copies the full payload **twice**:
once into the Uint8Array and again into the Buffer. It uses additional memory
and copy time. The shared-view form copies only once; mutations are shared
between `bytes` and `buffer`, while the original MemBlock remains unchanged.
