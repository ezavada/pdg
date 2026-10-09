# PDG v1.2.0 release notes

PDG 1.2.0 adds independent scenes, animated cameras, reusable animation scripts,
live Bone controls, procedural FABRIK and jiggle, WebSocket and WebTransport
networking, and TypeScript declarations and MVC support. It also improves text
rendering and expands the browser bindings.

Version: **1.2.0**. These notes describe the actual public repository diff from
**v1.1.1**, commit `dc52a6d2370b3235c103f094482d0cd74c007a97`, to merged
**main**, commit `92b25c6be7aba19ecf4fefb283a48e7665abaa4b`.
Features already present in 1.1.1 are covered by the
[1.1](RELEASE_NOTES_1.1.md) and [1.1.1](RELEASE_NOTES_1.1.1.md) release notes.

## Scenes and cameras

- **Scene ownership and timing.** A `Scene` owns layers, an isolated physics
  world, a default camera, logical timers, and subscriptions that disconnect on
  disposal. Pause simulation while continuing to draw, adjust time scale, select
  fixed steps with optional render interpolation, or advance a manual scene
  explicitly. Separate gameplay and HUD scenes can advance independently.
- **Scene collision queries.** Raycasts, circle sweeps, nearest-point queries,
  and point/circle/box/capsule overlaps inspect attached Sprite, Part and Particle
  colliders, including bodyless colliders. Queries work before the first step
  and while paused. Filter by layers, query groups, categories, sensors,
  exclusions, or a predicate; choose closest-hit or bounded multiple-hit results.
- **Animated Camera.** Ports have a built-in camera; layers can share an explicit
  camera with their own viewport and parallax. Follow targets with smoothing,
  look-ahead, deadzones and offsets; constrain visible world bounds, enable pixel
  snapping, and convert between world and view coordinates.
- **Camera effects and transitions.** Animate zoom and opacity, flash the view,
  compose transient effects, and switch shots using cuts, subject-matched cuts
  and fades, crossfades, directional wipes, luminance fades, or whip pans.
  Composited transitions require compatible ports and viewports.
- **Camera-aware drawing and picking.** Layer rendering and input use the
  effective camera. Ports also provide camera conversions and drawing controls
  for screen-space UI.

## Animation and particles

- **Reusable animation scripts.** Record named definitions with
  `Animated.defineScript()` and play independent instances with `playScript()`.
  Batch and series groups, parallel placement, waits, conditional branches,
  `until`, repeats, yoyo, amplitude and speed envelopes, saved marks, and lifecycle
  events compose on the existing animation scheduler. Selected blocks have their
  own stop/restart/pause/resume controls.
- **Collective animation.** `Troupe` applies commands to a collection of Animated
  targets using one script clock, including staggered starts. Members retain
  their normal rendering, physics and update ownership.
- **Live Bone controls.** `Sprite.getBone()` exposes an animated handle to an
  authored bone. Override individual transform channels, add relative motion
  over fresh clip samples, adjust dimensions and attachment offsets, fade
  influence back to the clip, and apply local IK rotation limits. Handles become
  invalid when their owning rig is replaced.
- **Procedural FABRIK and jiggle.** Solve longer IK chains with bounded iteration
  and diagnostics. Add chain springs or spring-filtered two-bone IK targets, with
  influence fades, kicks, enable/reset controls, and numerical state capture.
  Controllers support imported animation poses and independent Part chains;
  standalone pose solvers are available in C++. Jiggle itself does not create
  physics bodies or perform obstacle collision queries.
- **Particle trails.** Particles and emitter templates can carry solid ribbon
  trails with configurable lifetime, width, color, opacity, sampling and point
  limits. Break a trail on teleportation; retired trails can finish fading after
  the particle disappears.
- **Snapshots.** Supported snapshots now preserve animation script playback,
  saved marks and Troupe membership, Bone controls, built-in procedural
  controllers and state, and explicit layer camera/parallax settings. Callback
  evaluators, event handlers and custom easing remain runtime resources and are
  rejected by portable snapshots. Active camera transitions are not portable.

## Networking

- **JavaScript WebSocket and WebTransport.** The existing NetClient,
  NetServer and NetConnection interfaces gain web transports alongside native
  TCP/UDP. Desktop and Node can host web listeners; browsers use browser APIs;
  iOS exposes client networking through its native bridge.
- **Transport selection.** Choose `auto`, `native-only`, `websocket-only`, or
  `webtransport-required`. Automatic web selection can fall back from unavailable,
  unsupported or timed-out WebTransport to WebSocket. Certificate,
  authentication and protocol failures do not trigger that fallback.
- **Messages and delivery.** Send text, JSON, bytes, MemBlocks and supported
  serialized objects. Datagram sends use reliable delivery when the transport
  lacks datagrams or the payload exceeds its datagram limit. Configure TLS,
  certificate hashes, allowed origins, reservations, deadlines, connection
  limits and pending-byte limits.
- **Optional C++ networking.** Enable `PDG_BUILD_NATIVE_NETWORK` to build the
  separate `pdg-net` API: an explicitly polled runtime, clients, servers,
  connections and owned messages interoperating with the JavaScript protocol.
  Desktop listeners and iOS clients are supported; this facade is not a WASM API.
- **Native WebTransport backend.** The build integrates pinned QUIC/HTTP/3 and
  TLS dependencies, with desktop, Node and iOS build paths and accompanying
  third-party notices. Browser builds use browser WebTransport instead.

## TypeScript and browser support

- Generate engine declarations from the checked-in JavaScript IDL, including
  overloads, callback payloads, shared option records and fluent return types.
  Coverage metadata records the declaration inventory and construction rules.
- Add a separate TypeScript MVC implementation, including views, controllers,
  observers, controls, dialogs, scrolling and touch support. It compiles to
  CommonJS modules for an initialized graphical PDG runtime; the headless Node
  addon cannot run the graphical MVC framework.
- Add strict contract checks, examples, a relocatable build distribution and
  TypeDoc reference. `make docs` now packages the TypeScript site alongside the
  C++ and JavaScript references. See the [TypeScript guide](typescript/README.md)
  for setup and runtime constraints. Declarations are opt-in; this change does
  not publish a separate npm package or enable direct `.ts` execution.
- Expand Emscripten bindings and adapters for the new APIs, typed byte arrays,
  fluent calls and exposed Chipmunk operations. Source-driven generation checks
  validate the binding inventory and manual adapters.

## Rendering, fixes and builds

- **Editable Drawing text.** Add UTF-8 text elements to Drawing artwork and edit
  them through ElementRef. Text participates in transforms, opacity, hit testing
  and supported artwork snapshots; fonts are referenced by name rather than
  embedded.
- **Text caching and batching.** Replace linear text-cache lookup with hashed
  lookup, shared texture atlases and batched text drawing, with separate handling
  for changing labels. Browser text measurement and rasterization reuse Canvas2D
  resources. Improve native font fallback and release replaced font metrics.
- **Graphics lifetime and display scaling.** Detach retained cached fonts when
  a graphics port is destroyed. Keep logical window/drawing/input coordinates
  separate from framebuffer pixels when resizing or moving between displays.
- Correct the human animation demo's simulation clock and overlay drawing calls,
  and position the serialization demo with independent cameras.
- Fix Linux JPEG dependency handling and ensure release builds produce all
  configured CTest executables before running CTest. Repair Windows release
  checksum generation and include WebSocket license notices in desktop packages.
- Remove embedded-JavaScript empty-character warnings in the web build and align
  its scoped vendored Spriter warning suppression with native builds.
- Expand unit, native C++, tooling and browser coverage for scenes, queries,
  cameras, animation scripts, Bone controls, procedural animation, binary data,
  network interoperability and TypeScript. Add camera, Bone, FABRIK and jiggle
  visual/demo checks. See the [test guide](../test/README.md) for running them.

## Compatibility and migration

**This release contains breaking C++ and JavaScript API changes.** Rebuild native
binaries and the Node addon, and review layer transforms, binary data and saved
snapshots before upgrading.

| Previous usage | 1.2.0 migration |
| --- | --- |
| SpriteLayer/TileLayer inherited Animated transforms, movement and animation helpers | Layers no longer inherit Animated. Animate the Camera for view motion; animate Sprites/Parts for object motion. Use `setWorldBounds()` for layer bounds. |
| Layer `setOrigin()`, zoom, auto-center/fixed-axis controls, and `moveWith()` | Configure a Camera, its viewport and attachment anchor; share it with `setCamera()` and select per-layer `setCameraParallax()`. Camera `zoom()` takes a multiplier. |
| Layer `action_ZoomComplete` | Camera emits `eventType_ZoomComplete`, with CameraZoomInfo. |
| `setGravity(gravity, keepItDownward)` / `setKeepGravityDownward()` | Use `setGravity(gravity)`. Gravity belongs to simulation; rotating a camera does not rotate the physics world. |
| Binary JavaScript strings and `MemBlock.toBuffer()` | Use `Uint8Array` (Node Buffer subclasses are accepted). MemBlock byte getters return owned copies; create a Buffer view explicitly when needed. |
| 1.1.1 SpriteLayer snapshots | The layer stream advances from version 5 to 6 and rejects older records. Regenerate saved layer snapshots with 1.2.0; review other changed serialized records as well. |
| C++ overrides returning `void` for Renderer/Port drawing and Image appearance setters | Update overrides to the new reference-returning signatures. These methods, Polygon edits and additional geometry setters support chaining. |

`ser_LayerDraw` now selects explicit camera/parallax state; `ser_Sizes` includes
layer world bounds. `ser_Update` alone leaves the camera attachment unchanged.
Animation durations continue to use seconds; scene timer delays retain
milliseconds.

Binary APIs including `serialize_mem()`, `sizeof_mem()`, `setDataPtr()`,
`loadMapData()` and `binaryDump()` no longer accept strings as byte containers.
`ResourceManager.getResource()` returns owned bytes or `false`.
`Deserializer.setDataPtr(Uint8Array)` snapshots the visible bytes; passing a
MemBlock retains its borrowing contract. See the TypeScript guide's binary-data
section for conversion examples.

The Node dependency remains **v24.21.0** and the existing C++20 and iOS 16.3
requirements remain. Runtime capabilities still depend on the selected build.
The TypeScript inventory describes native GUI contracts and does not promise
that every API exists in browser, iOS or headless builds.
