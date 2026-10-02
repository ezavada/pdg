# Animated, PhysicsBody, Part, and Sprite API change list

Started: 2026-09-20. Updated with PDG-owned playback, rotation direction, and attachment discussion: 2026-09-20.
Physics extraction and acceptance updated: 2026-09-21.
Checklist reconciliation: 2026-09-26. Implemented contracts are checked below; owned animation playback remains open. MVC theme composition, transformed rendering/input, composite layout and scrolling clips are implemented. Port clipping, drawing overflow and live Drawing associations are implemented. Platform/manual acceptance is tracked separately from feature implementation.
Related: [animation proposal](PDG_ANIMATION_API_EXTENSION_PROPOSAL.md),
[implementation checklist](PDG_ANIMATION_API_EXTENSION_CHECKLIST.md),
[timing audit](ANIMATION_TIMING_API_AUDIT.md), and
[physics audit](ANIMATION_PHYSICS_UNIT_AUDIT.md).

This records the next API revision discussed after the stage-6 implementation.
Implementation status is tracked explicitly below. Animated timing now uses
floating-point seconds, including public stepping, helpers/easing callbacks and
inherited uses. The current summary and reconciled checkpoints are the implementation inventory.
Dated validation narratives preserve historical results; their then-open blockers
are not additional TODOs. Design alternatives below are not new API commitments.

## Current remaining work — 2026-09-25

The human rig demo is accepted at its current checkpoint. Joint placement,
contour fixes and the current elbow/knee behavior are complete for that scope;
further demo enhancements are deferred in the linked rig plan. Current work
focuses on engine completion and the broader API backlog below.

- [x] Consolidate Sprite's artwork/mask collision entry points with the shared
  Collider API, retain artwork adapters, and add concave polygon/mask geometry.
  Sprite joint/group and collision-mode shortcuts are removed; see the completed
  artwork migration below.
- [x] Finish checkpoint 4: Part-chain joint limits and scheduled IK targets that
  drive dynamic PhysicsBodies through force/torque-limited drives. See the completed
  Part IK and physical control section below.
- [x] Implement [automatic animation physics rigs and control modes](ANIMATION_PHYSICS_RIG_PLAN.md):
  explicit setup from the skeleton, length-weighted mass, zero-length filtering,
  whole-rig/bone/subtree Kinematic/Dynamic/Driven control, animation-plus-IK drives,
  editable shared components and existing Sprite flip semantics. The linked plan
  records the implemented API, completed decisions and remaining acceptance.
  Use root-name/descendant-count selection with explicit override, root-directed
  impulses, child-joint/artwork length inference and configurable 0.5-second
  recovery with a Sprite completion event; collisions report blocking.
  A designated root with calculated length zero receives a 1 mm physical segment
  and participates in mass distribution; other zero-length bones remain excluded.
  Capsule radius is 10% of length; default pivot joints allow free unauthored
  rotation, with unlimited strength, breaking/self-collision off and no drive.
  Drive handoff requires explicit release; the last successful manual
  `setDriveTarget()` wins without release between updates. All user choices in
  the [decision status](ANIMATION_PHYSICS_RIG_PLAN.md#decision-status) are agreed.
  Unchecked implementation work does not reopen the agreed design.
  Shared capsule Collider geometry, queries, solver integration and snapshots are
  now implemented. Dynamic skeleton-derived generation, root selection/impulse
  routing, 1 mm conversion and geometry diagnostics are implemented in C++/JS.
  Kinematic/Dynamic/Driven selections, parent-relative drives, explicit handoff,
  recovery and completion events are implemented. Explicit/generated Sprite rigs now share editable components, same-Sprite
  attachment/detachment and active-rig snapshots. Mixed Fixed/Follow frame movement
  and rotation targets are implemented, with a separate wheel-and-chains demo.
  Live reflection, aggregate force/torque routing and rotational queries are now
  implemented, with torque/braking/flip controls in the separate wheel demo and
  dedicated rig performance measurements. Wider platform/fixture acceptance is
  tracked in the rig plan. Cross-Sprite Part ownership
  transfer is implemented with explicit destination rig attachment.
- [x] Implement the rig's [assembly mass contract](ANIMATION_PHYSICS_RIG_PLAN.md#assembly-mass-and-per-body-inertia)
  through `sprite.physics.getMass()/setMass()`: report component totals, scale
  current mass/inertia proportions together, reflect individual Part edits, and
  preserve total mass on return to a single body. Attaching/detaching components
  adds/removes their mass without redistribution. No separate rig mass API.
  Explicit/generated setup/teardown, component/total mass edits, proportional
  inertia scaling, same-Sprite attachment/detachment and active-rig restoration
  are implemented. Cross-Sprite ownership transfers preserve component values; destination rig attachment is explicit.
- [x] Add [body rotation-speed thresholds and Break events](ANIMATION_PHYSICS_RIG_PLAN.md#body-rotation-speed-thresholds-and-break-events),
  usable on any physics body without requiring a joint. Sprite Break events identify
  body/Part/reason/speed and optional references; Chipmunk braking is unchanged.
  Thresholds, weak reference links and excursion latches survive scene snapshots.
- [x] Finish checkpoint 5: active explicit/generated physical-rig snapshots.
  Shared collider/constraint graphs, edited components, bone mappings, membership,
  root selection, mixed modes, desired poses, drive ownership and recovery state
  restore in complete and external-resource modes. Layer loads stage the graph
  before adoption; recovery and pending disable resume without duplicate completion.
  Existing callback/resource restrictions still apply. See the rig plan for
  continuation and malformed-record coverage.
- [x] MVC follow-up (checkpoint 2): explicit AnimatedAttributes appearance overrides
  compose with control state themes; rotation/reflection, exact viewport clipping,
  inverse hit testing and composite layout work in C++ and JavaScript. The MVC
  gallery supplies the interactive demo. See the MVC acceptance record below.
- [x] Complete [Port clipping and drawing overflow](#port-clipping-and-drawing-overflow):
  a single, non-nested Port clip rectangle and consistent `clipOverflow` support
  for all drawing operations.
- [ ] Separate animation-runtime follow-up (checkpoint 6): import into PDG-owned
  clip/track data, implement per-instance evaluation and verify playback/rendering/
  event/IK parity before retiring the Spriter runtime dependency.
- [x] Live AnimatedAttributes associations via ElementRef.setLiveAttributes();
  existing add/set methods still copy values.
- [x] Part.setupFrameCollider() and Part.setupAnimationCollider(boxName): owned
  Drawing bounds, single-image alpha masks/strip frames, explicitly bound imported
  image frames, named authored boxes, stable source IDs and snapshots. Both language
  references describe source selection, transforms and build prerequisites.
- [x] Particle effects: lightweight Particle and ParticleEmitter APIs in C++ and
  JavaScript, whole-body artwork/animation/physics, captured templates, bursts
  and continuous emission, owned trail emitters, lifetime and layer budgets.
  API references: docs/cxx/dox/particle-methods.dox and
  docs/javascript/dox/particle-methods.dox. Regression coverage:
  test/cxx/particle-tests.inc, test/spec/particle.spec.js, and the native/browser
  particle UI demo at test/ui_tests/particle_test.js. Particles and emitters are
  transient; layer snapshots omit them.

The previously deferred items above were added to the planned todo list at the
user's request on 2026-09-23. Earlier deferral notes below record historical scope.

Remaining acceptance (separate from implemented features):

- [ ] Windows runtime and Linux GUI/JavaScript validation. Linux native ARM64
  Docker suites pass; see [physics validation](PHYSICS_RIG_VALIDATION.md).
- [ ] Manual real-character culling/contact/blocking acceptance; the existing
  Grey Guy/Wonky reflection, accessory and recovery cycles pass automated checks.
- [ ] Deferred human-demo polish, improved pushes, stand-up recovery and blocked
  Kinematic handoff; keep these in the [rig plan](ANIMATION_PHYSICS_RIG_PLAN.md#deferred-demo-enhancements).

The [animation extension checklist](PDG_ANIMATION_API_EXTENSION_CHECKLIST.md)
retains longer-term work: sidecar/topology support, diagnostic overlays,
callback-requested rig replacement, queue-disabled trigger validation, complete
contact-controller transition coverage, motion matching and offline conversion.
These are not prerequisites for the completed rig implementation. The
[Spriter integration inventory](ENHANCED_SPRITER_API_PROPOSAL.md) tracks separate
sound, SCON/atlas, preloading and general nested-entity ideas.

Bindings, API references and platform regression coverage must accompany each
remaining implementation. The collider benchmark, comparison tables and recorded
viewer are complete and included in both language references' Physics topics.

## Port clipping and drawing overflow

Requested 2026-09-25. Use a single axis-aligned clip rectangle in Port coordinates.
Nested clipping, clip stacks and a hierarchy of local clipping regions are outside
this follow-up's scope.

- [x] Complete and verify `Port.getClipRect()` / `setClipRect()` behavior across
  all drawing paths. Define disabling/resetting the clip separately from a fully
  clipped result, including empty rectangles and rectangles outside the Port.
- [x] Support `Attributes.clipOverflow` consistently for all drawing: primitives,
  paths, text, images/image strips, spheres and Drawing replay. Define the overflow
  bounds for each operation, including transformed artwork and texture fit modes;
  remove the current image-only/incomplete behavior. Explicit Port clipping must
  still apply when an operation allows its own overflow.
- [x] C++ and JavaScript ScrollingView contain content within their viewport and
  restore the caller's Port clip, including failed draw callbacks. Rotated/reflected
  views use a reusable offscreen surface for exact clipping. Regression checks
  cover scrolling, resizing and partially offscreen viewports.
- [x] Keep native and script contracts/documentation aligned; add native/API and
  browser framebuffer checks for clipping, overflow and live replay.
- [x] Complete MVC gallery rendering/input acceptance and native/browser/iOS
  scrolling-view framebuffer checks; see the MVC record below.

Validation (2026-09-25): native client 1,342 tests / 9,032 assertions;
headless Node 1,230 / 8,441; focused browser API/MVC suites 247 / 1,602;
795 browser framebuffer checks (125 clipping/live-replay checks plus the existing
670 shape-fill checks); C++ AnimatedAttributes and View suites pass. Native,
Node and WebAssembly builds pass without compiler warnings. Both language
references regenerate with the existing 65-warning Doxygen baseline.

## MVC completion and acceptance — 2026-09-26

- Attributes.withAppearance() copies explicitly assigned or scheduled appearance
  channels onto a base style, including explicitly assigned defaults. It preserves
  the base transform and does not mutate either input. Text-only composition keeps
  theme foregrounds separate from animated background colors.
- C++ and JavaScript Views share transformed drawing and inverse input coordinates.
  Visual children inherit parent transforms, viewport clipping and visibility; each
  registered view still animates once. Layout remains in Port coordinates. ListBox
  scrollbars follow resizing and receive input through the same transform.
- Scrolling views intersect the caller's single Port clip and restore it afterward.
  Transformed views redraw into a reusable offscreen surface and composite a live
  image, preserving exact viewport edges. Port.clear() and setDrawingOrigin()
  support those surfaces. Oversized solid quad fills are clipped before submission
  to avoid incorrect ES1 clipping seen in the iOS regression.
- `test/demo mvc`, `test/demo --web mvc`, `test/demo --ios mvc` and `test/mvc` open
  the gallery. `control-gallery` remains a CLI/legacy-browser alias. The gallery
  includes themed/default controls, animated/reflected buttons, rotated scrolling,
  a resized list and dialogs. The native C++ gallery demonstrates the same cases.
- Targeted native, browser and iOS specs: **98 tests / 865 assertions** each;
  headless Node: **79 tests / 661 assertions**. Three native CTest suites cover
  View animation/layout, the app framework and text helpers. Browser pointer checks
  exercise rotated/reflected buttons, a child scrollbar, row selection and dialogs;
  framebuffer checks verify exact clipping, reflection, surface refresh and exception
  restoration. Physical-device and Windows/Linux GUI acceptance remain part of the
  broader platform gates above.
- Usage and ownership: [JavaScript MVC](../../src/js/mvc-app/README.md) and
  [C++ MVC](../../src/inc/pdg/app/README.md). Engine method references are generated
  from both languages' Attributes/offscreen-port documentation.

## Body angular-speed breaks — 2026-09-23

- [x] Add fluent `setBreakAngularSpeed(radiansPerSecond, referenceBody?)`,
  `getBreakAngularSpeed()` and `getBreakAngularSpeedReference()` on PhysicsBody.
  Zero disables; references are optional, weak and same-layer (or both unlayered).
- [x] Emit `eventType_SpriteBreak` with `physicsBreak_AngularSpeed` and
  `action_BodyBreak`, source body/Part, measured speed, threshold and reference.
  Part events route to their Sprite. Detached native bodies can use `setBreakHandler()`.
- [x] Sample solved velocities after positive-duration world steps in both solvers;
  notify once per excursion, rearm at/below the limit, preserve the latch on
  identical setter calls, and reject invalid edits without changing state.
- [x] Preserve existing motor/braking/joint-force behavior. Body notifications do
  not clamp speed, disconnect joints or split artwork, even when unhandled.
- [x] Serialize thresholds, references and notification state. References outside
  the saved graph and native callbacks reject explicitly. Compact body format 2
  reads format 1; graph format 4 reads format 3. Active rig snapshots remain separate.
- [x] Add native and shared JavaScript regressions for both directions, boundaries,
  reference lifetime, owner routing/removal, retained identities and snapshot continuation.
- [x] Validate native owners (29,963 assertions), basic/Spriter headless owners
  (6,230), feature-disabled owners (6,019), and PhysicsBody contracts (91 per build).
  Desktop PhysicsBody passes 13 tests / 350 assertions; the full browser suite
  passes 1,279 tests / 7,900 assertions. The two affected JSC binding translation
  units pass iOS simulator syntax checks (not an iOS runtime test). Regenerated
  C++/JavaScript references retain the 65 existing warnings and pass Topics checks.
  Snapshot tests include saves inside a Break handler and omitted source-body fields.

## Live source/target Layer demo — 2026-09-23

- [x] Add `test/js/layer-serialization-demo.js`, running the same live scene on
  desktop and in `test/ui.html?test=layer-serialization`. Source-only scripts,
  scheduled movement/rotation, basic physics collisions and a two-joint Part IK
  arm feed an initially empty target through one complete snapshot and updates.
- [x] Add sampled Part transforms/rates/schedules to incremental animation records.
  Preserve Part/artwork identity, rebase receiving schedule pointers, and reject
  changed Part IDs/counts. Topology/artwork edits and Part physics/controller
  changes still require another initial snapshot.
- [x] Display actual delivered bytes/sec over one second, updates/sec, requested
  rate, initial/latest/cumulative byte counts, packet age and pose error at receipt.
  Add 5/20/50 Hz controls, disconnect/reconnect, source pause and fresh snapshots.
- [x] Verify native and browser live checks: 89 updates across the five-second run
  (including a deliberately disconnected interval), 3,071-byte initial snapshot,
  1,542-byte final update, 30,840 bytes/sec at 20 updates/sec, zero pose error.
  Visually inspect the browser rendering. These are local serialized-buffer
  handoffs, excluding socket/protocol overhead; update size varies with state.
- [x] Pass native owners (29,901 assertions), headless owners (6,198), desktop
  SpriteLayer (8 tests / 175 assertions), full browser unit suite (1,276 tests /
  7,855 assertions), and the finite browser/native demo checks. Regenerated docs
  retain the existing 65 warnings and complete class/event Topics coverage.

- [x] Add clickable Micro / Pose + Parts / Standard presets and all seven field
  toggles. Target animation and collision processing can be toggled independently
  and remain selected across incoming packets and new snapshots. Keep packet
  cadence independent of source pause. Show current world-position differences
  without treating expected divergence as corruption; clip each scene to its panel.
- [x] Extend the native/browser live checks through all 128 field combinations,
  selective Part updates, Micro bandwidth reduction (143 versus 1,542 bytes at
  the sampled state), target schedule/body stepping, stopping after receipt and
  independent contact response. Both live checks pass; inspect the browser controls.

Run instructions and scope: [Layer serialization demo](../../test/js/LAYER_SERIALIZATION_DEMO.md).

## Checkpoint 5 graph and authored animation snapshots — 2026-09-22

- [x] Save explicit circle/convex/concave/mask shapes, stable shape IDs, frame source
  mode/threshold, additive shapes, filters, material overrides and participation flags.
- [x] Restore compound-body associations after all Sprite and Part bodies exist.
- [x] Save all ten PhysicsConstraint families once, restoring shared endpoints,
  anchors, parameters, break/force limits, collision policy and ratchet phase.
- [x] Restore live Part rotary-limit links and active physical IK controllers,
  captured offsets, sampled body drives and exclusive ownership without recapturing drift.
- [x] Validate graph input on the staged Layer before replacing live membership;
  reject external runtime endpoints and callback filters/handlers explicitly.
- [x] Cover both solvers, both resource modes, tagged/untagged streams, restored
  ball/box contact response, shared constraint identities and controller continuation.
- [x] Preserve imported SCML documents and shared image/model resources in complete
  saves; external mode verifies the resolved source document fingerprint and uses
  the existing image-reference policy. Complete saves restore after source deletion.
- [x] Restore entity/clip selection, fractional playback, pause/events, character
  maps, reference pose, overrides, ordinary blends and interrupted transitions.
- [x] Restore authored bone/artwork/socket Part bindings before body publication,
  preserving shared rig identity and live animation collider sources.
- [x] Restore built-in rig IK and retained Drawing registrations with stable IDs,
  disabled/error state, ordering and allocator cursors. Arbitrary callbacks reject.
- [x] Make resource import independent of display support: headless Spriter saves
  retain images too, so complete snapshots remain portable to GUI builds.
- [x] Preserve graceful normal imports of malformed XML while rejecting invalid
  saved documents and incomplete image tables. Keep factory ownership safe on errors.
- [x] Verify native owner regressions (5,628 assertions), Spriter/basic headless
  owners (3,925), feature-disabled owners (3,836), native/headless playback, and
  all 1,276 browser tests (7,855 assertions). All five selected desktop CTests and
  both Spriter headless CTests pass. Four JavaScriptCore binding translation units
  pass syntax checks. Current builds introduce no compiler warnings.
- [x] Complete the desktop unit suite. The earlier null-GLFW-monitor abort
  is superseded by the recorded full desktop pass: 1,335 tests / 8,990 assertions.
  See [final validation](PHYSICS_RIG_VALIDATION.md#node-unit-validation-fixes).

- [x] Regenerate C++/JavaScript HTML and JavaScript manuals with no new Doxygen
  warnings (65 existing), and verify complete class/event Topics coverage.
- [x] Save/restore active explicit and generated physical rigs, edited shared
  components, mapped Parts, desired pose, membership, root/control ownership,
  drives and recovery in both resource modes. Layer loads validate on a staged
  graph before adoption. See [rig snapshot acceptance](ANIMATION_PHYSICS_RIG_PLAN.md#snapshots-and-acceptance).

Initial Sprite format is 9; Layer format is 5; the shared physics graph format is 4 (reading format 3 remains supported).
Old initial physics records are not accepted. Scene snapshots preserve configured physical state, not solver contact
caches or queued contact events. Loading may produce new Begin contacts. Invalid
or disconnected IK limit configurations must be repaired or cleared before saving.

## Compact snapshot fields and visual coordinates — 2026-09-23

- [x] Replace individual byte booleans with `serialize_bool` throughout the new
  Drawing/Image, Part, graph, imported-resource and authored-controller records.
  Keep enums and masks with multiple flags as discriminators.
- [x] Suppress default Drawing attributes, optional textures, transparency colors,
  opacity, subsection geometry, fractional frame cursors and absent collision masks.
- [x] Use compact coordinates for Drawing geometry and pixel-space appearance
  (thickness, font size, radii, offsets, subsections and transform translation), plus
  Image subsection geometry. Colors use the existing eight-bit serializer.
- [x] Keep exact nondefault physics doubles and geometry/control floats. Omit defaults
  for bodies, loads, drives, collider filters/materials, constraints, IK, owner motion,
  mounts, timelines and authored playback. Write shape/constraint parameters by type.
  Preserve completed blend/transition state and dormant nondefault attribute settings.
- [x] Preserve the next force ID even after loads expire or are removed; absent defaults
  clear the corresponding prior state when loading into an existing body.
- [x] Reuse `serialize_obj`/`sizeof_obj` for shared assets, images and Drawing storage.
  Keep optional-object presence separate from object identity. Size and write fields
  in identical order, including the second Part-body pass after all Part records.
- [x] Bump changed record versions: Sprite 9, Layer 5, shared physics graph 3,
  Image/Drawing 4, imported asset 3, Animated 2, Animated tracks 4, Sprite tracks 7,
  root body marker 3 and body payload 1. Older initial records are rejected.
- [x] Verify all eight starting bool offsets, tagged/untagged streams, default reset,
  exact physics state/resumed loads, visual rounding boundaries, shared resources,
  malformed graph records and active drives/IK. Native: 29,221 assertions; headless:
  5,518 assertions. Malformed-record fixtures now mutate fields in real serialized
  records rather than splice independently packed tails.
- [x] Verify desktop JavaScript serialization, Layer and animation suites: 59 tests /
  1,118 assertions. Full browser suite: 1,276 tests / 7,855 assertions. Four native
  CTests (owners, basic body and debug/release NoPhysics) pass. Desktop, headless and
  WebAssembly builds introduce no compiler warnings.
- [x] Regenerate C++/JavaScript HTML and manuals, with the same 65 Doxygen warnings
  as before this pass; class/event Topics coverage remains complete.

Current untagged sizes measured by `compactSnapshotRecords()` (no outer object
wrapper for PhysicsBody/Animated; Drawing includes its object wrapper):

| Record | Bytes |
| --- | ---: |
| Default PhysicsBody | 5 |
| Default Animated | 10 |
| Drawing line from (0,0) to (10,20), default Attributes | 15 |
| Additional reference to that Drawing | 4 |
| Ten-Sprite `ser_Update` fixture with move/rotate tracks | 1,076 |

## Compact snapshot colors — 2026-09-23

- [x] Use `serialize_color`, `deserialize_color`, and `sizeof_color` for the seven
  Drawing attribute colors and the Image transparency color. Image/Drawing record
  versions were advanced for compact colors; channels use PDG's eight-bit encoding and opaque alpha is omitted.
- [x] Keep physics/IK quantities exact. The subsequent visual-coordinate pass below
  applies the approved compact encoding only to screen appearance data.
- [x] Verify native/headless snapshots and JavaScript callers, including color
  alpha flags at all eight packed-bit offsets and nested/shared image resources.
  Native: 27,342 assertions; headless: 4,743. JavaScript serialization and animation:
  51 tests / 943 assertions. Regenerated docs retain the 65 existing warnings.

## Embedded XML compression — 2026-09-23

- [x] Compress complete-snapshot SCML with zlib/DEFLATE level 6; store raw bytes
  when compression is not smaller. External references continue to omit XML.
- [x] Version imported asset records (format 2), recording encoding, original
  length and the length-delimited payload. Retain the original XML fingerprint.
- [x] Cache compressed bytes per shared asset across sizing/writes and invalidate
  the cache whenever its source document changes. Preserve shared object identity.
- [x] Bound compressed and expanded records to 64 MiB, verify exact output length,
  require a complete stream with no trailing data and reject invalid checksums.
- [x] Cover raw/compressed round trips, cache replacement, tagged/untagged sizing,
  shared assets, external references, malformed sizes/codecs, truncated/corrupt
  streams and extra/concatenated data. Native: 5,750 assertions; headless: 4,047.
- [x] Verify desktop pose/serialization (51 tests / 943 assertions) and the full
  browser suite (1,276 tests / 7,855 assertions). Native/headless/Wasm builds add
  no compiler warnings. Regenerate both references with no new Doxygen warnings
  (65 existing) and complete class/event Topics coverage.

## Part IK and physical control — completed 2026-09-22

- [x] Share a retained rotary-limit constraint with `Part::setIKLimits(constraint)`;
  use live `PhysicsConstraint::getMinAngle/getMaxAngle/setAngleLimits` in both solvers.
- [x] Validate parent/child endpoints, reverse endpoint order, and supported frames;
  reject reflected/nonuniform parent frames and source-bound root frames explicitly.
- [x] Suspend IK safely after break/disconnect, body removal, or invalid range/frame;
  preserve unwrapped relative drive angles for shared limits.
- [x] Check physical IK pivot/pin anchors against captured Part joint offsets.
- [x] Save linked limit references with the checkpoint 5 constraint/controller graph.

- [x] Add per-joint setIKLimits()/clearIKLimits(), presence and angle queries.
  Solve bounded root/middle rotations, including equivalent wrapped angles,
  preferred bend selection, constrained endpoints and positive partial influence.
- [x] Add setIKDriveTarget() and isIKDriven() for independent contiguous Part
  chains. Root/middle have dynamic bodies; the tip may have a dynamic body or none.
  Capture joint offsets once, retain them across target updates, and apply desired
  positions/orientations through bounded body drives before the shared solve.
  Imported physical-rig Parts continue using their existing rig controllers.
- [x] Keep physical transforms authoritative and reached status based on the actual
  endpoint. Keep joints, physical angular limits and colliders explicitly configured.
- [x] Enforce exclusive drive ownership, transactional target replacement, safe
  retained-body lifetimes and immediate peer-drive shutdown on body removal.
  Clearing an IK target preserves velocities, constraints and independent loads.
- [x] Round-trip ordinary Part IK limits with existing direct controllers in both
  resource modes. Physical controllers now use the checkpoint 5 graph records.
- [x] Expose matching native/V8/JSC/browser APIs and update both language references.
- [x] Verify native owner regressions (4,509 assertions), basic-only headless
  regressions (3,524), desktop JavaScript (1,300 tests), browser JavaScript
  (1,274 tests), and generated JSC syntax. Regenerate both documentation sites
  with no new Doxygen warnings and complete topic coverage. Native tests compare
  constrained IK with a dense angle grid, run driven chains with pivot constraints
  in both solvers, and cover convergence, limits, impulses, ownership and removal.

## Component setup naming — 2026-09-22

- [x] Use setupPhysicsBody() and setupCollider() on both Sprite and Part;
  use setupFrameCollider() and setupAnimationCollider() on Sprite.
- [x] Apply setupPhysicsBody mass and inertia on every call, defaulting each
  omitted value to 1. Access existing bodies with .physics without reconfiguration.
- [x] Keep existing body identity, solver, motion, forces and constraints;
  validate both setup values before changing an existing body.
- [x] Migrate bindings, tests, demos, performance tests and documentation sources.
- [x] Verify native, browser and headless behavior and regenerate API documentation.
  Native physics owners: 4,316 assertions; headless: 3,389; playback: 1,475.
  Desktop JavaScript: 1,296 tests; browser: 1,270. JSC syntax checks pass.
  Both 2,000-body Sprite/Part benchmark smoke runs pass with both solvers.
- [x] Fix the browser snapshot stack overflow found during verification: configure
  a 1 MiB WebAssembly stack (overridable with WASM_STACK_SIZE) and enable overflow
  checks in test builds. Nested Drawing snapshot restoration passes.

## Artwork collider migration — completed 2026-09-22

- [x] Rename source selectors to `setupFrameCollider()` and `setupAnimationCollider()`;
  create only when absent, preserving existing collider configuration and identity.
- [x] Keep source geometry and explicit additions together: `addCircle`, `addBox`,
  `addPolygon` and `addImageMask` retain the source; `set*` and `clearShapes` stop it.
  Reject removal of source-controlled IDs; allow explicit additions to be removed.
- [x] Preserve source IDs by authored box name, including inactive/reappearing boxes;
  expose source kind, shape kind, source names and per-shape circle radius queries.
- [x] Accept simple convex/concave polygons in either winding and native/JavaScript
  Polygon objects. Validate before replacement, decompose through PDG triangulation,
  and aggregate solver pieces under one public shape/contact identity.
- [x] Add shared image-mask geometry preserving holes and separate opaque islands;
  follow frame images, pivots, masks and transforms with cached source geometry.
- [x] Expose contact callbacks and collision predicates in all script bindings;
  null clears callbacks. Keep mouse hit testing independent of collider selection.
- [x] Remove Sprite collision mode/radius/helper entry points and duplicate pair
  detection; migrate native/script tests and visual demos. Retain imported physical
  rig contact events and bridge their existing native shapes to shared colliders.
- [x] Update source references, generated bindings, JavaScript declarations and
  C++/JavaScript Topics. Source-selection and additive geometry contracts have
  examples in both language references.
- [x] Verify desktop/client, native physics/playback, browser and headless suites;
  syntax-check generated JavaScriptCore bindings. Run all existing 2,000-body
  benchmark scenarios for Part owners with both solvers as a short smoke test.
  These short runs do not replace the published timing/settling measurements.
- [x] Fix an intermittent full-client GC crash exposed by this validation:
  retained images and subimages detach from destroyed Ports and invalidate their
  cache keys. A deterministic native regression covers port closure, reattachment
  and later image destruction, including custom Port implementations.

Collider/constraint snapshot graphs remain checkpoint 5 work. Imported physical
rig capsules continue using their existing Sprite collision event payload; ordinary
shared collider contacts use ColliderContact.

## Shared colliders and body constraints — approved 2026-09-22

Sprite and Part expose the same optional, read-only `.collider` reference, backed
by one shared NoCollider object until creation. Collider is independent of Sprite,
rigs, artwork and Animated; lightweight Particles also use it without those
dependencies. Collider mutators chain on Collider; only its reference
property needs an owner template. Physical joints belong to PhysicsBody and
return retained PDG PhysicsConstraint handles, independent of Chipmunk pointers.

- [x] Add Collider, stable shape IDs, circle/box/convex shapes, local transforms,
  category/mask/group filtering, sensors and overlap queries.
- [x] Add shared NoCollider, explicit factories/removal on Sprite and Part, safe
  retained handles, and explicit owner-body versus compound-body association.
- [x] Integrate collider shapes and contact response into basic/Chipmunk worlds;
  define bodyless surfaces and publish generic collider/shape contact identities.
- [x] Add PhysicsConstraint handles and body-to-body joint, spring, limit and
  motor operations, with basic approximations and Chipmunk implementations.
- [x] Define constraint lifetime, collision suppression, break limits, endpoint
  removal/transfer and safe callback mutation.
- [x] Migrate Sprite collision/joint APIs, internal uses, demos, perf and tests;
  preserve artwork-specific mask/import adapters without requiring Sprite owners.
  PhysicsBody owns constraints and Collider owns geometry, groups, filtering and
  contact callbacks. Sprite.setupFrameCollider()/setupAnimationCollider() select
  artwork sources on the same read-only association; setFrameCollisionMask()
  configures per-frame mask overrides.
- [x] Expose the same native, V8, JSC and browser APIs, factories and identities.
- [x] Update source references and Topics; regenerate bindings and documentation.
- [x] Validate ordinary/unbound Parts, compound shapes, mixed Sprite/Part contacts,
  sensor events, retained handles, constraints, basic/Chipmunk and disabled builds.
- [x] Integrate shared collider/constraint graph records with checkpoint 5
  snapshots, including live IK links and active drives. Retain explicit rejection
  for unsupported external endpoints and arbitrary callback state. See the
  [graph snapshot tests](../../test/cxx/physics-graph-snapshot-tests.inc).

- [x] Add and run an optimized native benchmark with 2,000 bodies and colliders,
  both solvers, Sprite/Part owners, warmup, step percentiles, JSON output and
  scene-validity checks. Replace static circle comparisons with approaching pairs
  (row offsets and 10-to-1-second column contact times) and initially touching pairs
  (row force angles and column strengths, releasing forces when contact ends).
  Record three circle trials in
  [the current performance report](../../test/perf_tests/cpp-collider/CONTACT_REUSE_RESULTS.md).
- [x] Reuse Chipmunk contact manifolds for shared Collider events instead of
  running duplicate detection. Keep basic/mixed/static-static/zero-time fallback;
  cover sensors, shape/body removal, body-mode changes, sleeping and teleporting.
- [x] Preserve native contact caches across float owner publication; avoid echoing
  rounded Sprite transforms into the solver, and reindex explicitly moved static
  Parts. Distant Sprite/Part stacks remain supported and can sleep.
- [x] Add 2,000-body box-stack, pivot-chain and settling-pile benchmarks for both
  solvers and Sprite/Part owners. Report independent penetration/anchor error,
  residual motion, settling, escaped bodies and sleeping counts outside step timing.
- [x] Compare default tree indexing against spatial hashes (1/2/4-unit cells,
  20,000 entries), and test sleeping separately. Retain engine defaults: tree,
  10 solver iterations, sleeping disabled. Record repeated throughput trials,
  single-run quality comparisons and raw measurements in
  [the current solver comparison](../../test/perf_tests/cpp-collider/CONTACT_REUSE_RESULTS.md).
- [x] Add an offline side-by-side viewer of native simulation recordings, with
  synchronized playback, scrubbing, stepping, speed and scene/owner/sleep controls.
  Preserve all 26 recordings losslessly in the compact documentation snapshot.
- [x] Publish the latest timing/accuracy tables and collider viewer in the C++ and
  JavaScript Physics topics; verify both generated references and packaged docs.
  Tables use the benchmark report as their source and the viewer identifies its
  recorded playback explicitly.

Validation: native owner regressions; no-GUI/no-Spriter/no-Chipmunk owner/body
contracts and benchmark; full desktop unit suite; V8, browser and iOS/JSC
collider bindings. The benchmark also exposed redundant sibling refreshes during
independent Part publication; leaf updates now avoid whole-host refreshes while
parented physics and attachments retain their propagation.

Contact-reuse follow-up validation: 4,154 native owner assertions; 1,302 desktop
native unit tests/7,710 assertions; 25 browser specs/410 assertions; both disabled-physics
native suites and all five benchmark scenes. Final native/headless/browser builds
have no compiler warnings. Doxygen retains its 65 existing warnings with none new;
C++ and JavaScript Topics/Events coverage passes. The 2,000-body measurements keep
all expected contacts; Chipmunk stacks/piles settle and all 2,000 bodies sleep when
explicitly enabled. Chains remain in motion at the end of the 21.2-second runs.


## Active follow-up checkpoints — 2026-09-21

Reconciled 2026-09-26: checkpoints 1–5 below are implemented and
verified for their stated scope. The [rig plan](ANIMATION_PHYSICS_RIG_PLAN.md) owns remaining platform and
manual acceptance. Owned playback (6) remains implementation work. Live Drawing
associations and the MVC theme/transform follow-up are complete.

Snapshots support complete embedded assets and external references; both restore
the same supported runtime graph, using named Parts and shared PhysicsBody components.

- [x] 1. Animated transform and tween contract.
  - [x] Independent floating-point scale; integrate Sprite/Part/Layer/Attributes transforms.
  - [x] Eased growth/stretch rates with deterministic integration and interruption.
  - [x] Tween pause/resume/cancel/status, including Attributes appearance channels.
  - [x] Native, V8/JSC and browser exposure; update snapshots and API docs.
  - [x] Native/script/browser regression coverage; verify and commit checkpoint.
- [x] 2. MVC theme composition, transformed rendering/input and composite layout.
  - [x] Explicit appearance overrides compose with selected control themes.
  - [x] Rotation/reflection share one rendering/input transform; visual children
    follow owner layout and retain their own appearance.
  - [x] Scrolling viewports preserve exact clips and restore caller state.
  - [x] Gallery replacement and native/browser/iOS/Node regression coverage;
    see the MVC completion record above.
- [x] 3. Part artwork, authored binding mapping, sockets and rigid attachments.
  - [x] Define content/source ownership, transform composition and lifetime.
  - [x] Implement content/attachment APIs with binding and retained-reference coverage.
  - [x] Extend rigid mounting to kinematic bodies, with target sweeps before the
    shared solve and rejection of competing body/root commands. Dynamic holding
    still requires constraints/drives. Browser exposure is checkpoint 5.
- [x] 4. Part physics, constraints, explicit Part-chain IK and final publication.
  - [x] Connect Part bodies to Chipmunk and basic world support.
    Unbound Part bodies join either world without a root body. Shared Collider
    shapes, owner-independent contact payloads and PhysicsBody constraints now
    work with Sprite/Part combinations in both solvers.
  - [x] Define control authority and physical/articulated relationships.
    - [x] Dynamic Parts preserve solved world positions under moving, reflected,
      or physical parents. Publish parents before children after authored poses.
    - [x] Evaluate animation/mount targets before the shared solve; execute helpers
      and clips once and publish physical transforms before collision/bounds checks.
    - [x] Cancel programmed spatial motion on dynamic ownership, including delayed
      rates, without canceling size or appearance animation.
    - [x] Force/torque-limited PhysicsBody drives in basic and Chipmunk solvers,
      including rotation routes, target/error queries and active-drive snapshots.
    - [x] Mapped rig bodies publish bone output through named Parts and `.physics`.
    - [x] General Part articulated constraints through PhysicsBody, shared with Sprites.
    - [x] Scheduled IK-to-body drive integration through Part.setIKDriveTarget().
  - [x] Add Part-chain IK and retire/adapt body-index operations explicitly.
    Direct `Part.solveIK(middle, tip, target, space, bendDirection, influence)`
    solves explicit joint-offset chains without bones, including reflected affine
    ancestors; dynamic bodies reject direct IK. Root scale must be uniform in
    magnitude. Scheduled controllers now run after all Part helpers and before
    physical publication. Per-joint limits and exclusive physical-drive controllers
    now complete the explicit Part-chain implementation.
    - [x] Persistent `Part.setIKTarget()`, clear/participation/reached/error queries,
      parent-first controller ordering, overlap rejection and safe missing-joint handling.
      Kinematic bodies receive solved targets; direct controllers reject dynamic bodies.
    - [x] Remove Sprite body-index state/impulse methods; named mapped Parts expose
      their actual constrained bodies through `.physics`, including forces/drives.
    - [x] Remove Sprite elasticity/static shortcuts; use PhysicsBody restitution/mode.
      PhysicsBody is the only serialized owner of restitution.
- [x] 5. Platform parity and acceptance for the listed graph contracts.
  - [x] Browser Part/PhysicsBody exposure and contract tests.
  - [x] Browser callback-based IAnimationHelper construction and custom easing parity.
  - [x] Animated transform/tween records and active Layer tween update snapshots.
  - [x] Full Layer graph reconstruction and Part content/attachment/controller snapshots.
    - [x] Per-writer save policy and Image/ImageStrip records: embedded pixels or
      external file/resource references, with embedded fallback for runtime edits.
    - [x] Frame-based Sprite records include shared images/masks, complete strip
      layout and fractional playback position; expose frame APIs in the browser.
    - [x] Reconstruct frame-based SpriteLayer collections, preserving order,
      shared images, transforms, tweens and active root-body drives. Stage and
      validate input before replacing live membership.
    - [x] Independent Part records preserve IDs/names, forward parent links,
      local transforms/tweens, bodies, active loads/drives and Image/Drawing content.
      Drawing records preserve editable sharing, nested content and image identity.
    - [x] Layer mount tables restore nested rigid attachments, child grip frames,
      draw order, held error state and kinematic command restrictions after all
      Sprite/Part identities exist. Standalone Sprite saves reject mounted groups.
    - [x] Independent Part IK controller records preserve configuration and last
      reached/error state in both resource modes. Resolve IDs after all parents and
      bodies, validate before replacing live Parts, and preserve fractional targets.
    - [x] Collider and constraint graph tables preserve source/explicit geometry,
      materials/filters, compound associations, shared physical joints and live IK links.
    - [x] Physical Part IK records preserve captured geometry, active drives and
      exclusive ownership in both resource modes; resumed contact/IK regressions pass.
    - [x] Extend snapshots to authored bindings and imported SCML/image dependencies,
      playback/blends/transitions, built-in rig IK and retained Drawing registrations.
    - [x] Restore active explicit/generated physical rigs and their mapped Part
      solver ownership, edited component graph, membership, modes, drives and recovery.
    - [x] Restore identities first, then parent/mount/controller/constraint links;
      preserve shared assets and active state in either resource mode.
    - [x] Round-trip both modes, including runtime Drawing/Image content; reject
      missing resources and unsupported callback state explicitly.
  - [x] Retain off-layer Part attachment groups and coordinate hierarchy layer transfer.
    Host removal/addition carries nested mounted children; independent child moves
    require explicit detachment. Draw-order changes preserve bodies and mounts.
  - [x] Imported Spriter models/artwork have shared ownership independent of the
    source Layer. Transferred/retained sprites keep playback, Part bone bindings
    and callbacks; model resources release with their final owner.
  - [x] JSC/iOS runtime coverage for Part, PhysicsBody, programmed transforms,
    tween controls, AnimatedAttributes, pose/drawing callbacks and playback.
  - [x] Native feature-disabled/headless build and focused contract suites.
  - [x] Retained Sprite/Part/body handles survive mount detach and layer cleanup;
    V8 forced-GC coverage checks wrapper collection and native ownership.
  - [x] Debug NoPhysics warnings are throttled once per operation; release calls
    and queries are silent. Separate debug/release binaries verify output after
    10,000 repeated calls and confirm no state or queued loads escape the singleton.
  - [x] Complete graph snapshots for the implemented controllers/constraints;
    active-rig coverage passes native, headless Node, desktop and browser tests.
    Additional rig-specific platform, visual and performance acceptance remains
    in the [rig plan](ANIMATION_PHYSICS_RIG_PLAN.md).

Physics API consolidation follow-up (2026-09-21): removed Sprite's indexed
rig-body state/impulse methods, set/getElasticity, makeStatic, and the duplicate
AnimationPhysicsBodyState type. Rig setup creates/reuses Parts named after their
bones; PhysicsBody operations address the actual constrained bodies. Disable keeps
Part IDs and detaches retained bodies before freeing solver storage. Mapped Part
transform/rebinding/removal errors become catchable exceptions on all script
platforms. Immediate Animated property setters now translate owner-policy errors
in V8/JSC as well. Sprite initial records use format 4 and no longer duplicate
PhysicsBody restitution; old formats are intentionally unsupported.

Verification: native rig/ownership/programming/body suites 4/4; no-Chipmunk
headless rig/ownership suites 2/2; V8 animation/physics/Part/serialization/Sprite
78 tests with 1,213 assertions; browser 85 specs with 1,270 assertions; iOS
animation 22 tests with 546 assertions. Both native perf targets build without
warnings. Both documentation Topics audits pass; Doxygen remains at 65 warnings.
The source audit found no indexed-body or removed shortcut calls in demos/perf.

- [x] Checkpoint 5 helper lifetime follow-up: finished helpers retain valid script
  wrappers and can be registered again. Owned native registrations use references;
  a stable registration snapshot makes callback removals, clears and additions safe.
  Duplicate registration is idempotent, shared helpers survive individual owners,
  and inactive callback/wrapper cycles are collectible. Browser deletion-specific
  tests remain browser-only; callback lifetime regressions run on all three runtimes.
- [x] Animated chaining audit: all public transform/tween/helper mutators return
  the original receiver in JavaScript and `Animated&` in C++. Timed movement,
  resizing, scaling, rotation, pivot changes and helper management now chain;
  `wait()` returns a reference (including AnimatedAttributes). Native callers use
  `wait(seconds).method(...)`. Binding metadata and generated references agree.

Helper/chaining verification: five native suites passed; the focused Animated
contract passed 163 assertions under AddressSanitizer/UndefinedBehaviorSanitizer.
V8 passed 114 tests / 1,198 assertions plus forced-GC lifetime coverage; browser
passed 66 specs / 1,028 assertions; iOS callback/chaining passed 6 tests / 68
assertions. Both Topics/event audits pass; Doxygen remains at 65 existing warnings.

Scheduled Part IK follow-up: `setIKTarget()` retains one target per chain root.
All Part local animation/helpers run first, then direct controllers in hierarchy
order, then body publication. Controllers cannot share a writable joint. Broken
or removed joints produce a queryable held error and recover after valid
reparenting; clearing/removing the root retires its controller. These controllers
support ordinary and kinematic Parts. Shared articulated constraints are now
implemented; IK limits and IK-to-dynamic-drive control were completed in the later Part IK checkpoint.

Initial Sprite format 5 adds controller records to independent Part graphs.
Both save modes restore references after Part identities, parent links and bodies
exist, preserving controller settings and last solve status. Invalid references,
spaces, bend signs and influence reject without replacing existing Parts.
Imported rigs and general physical constraints gained their graph records in the later checkpoint 5 work.

Validation: native physics/ownership suites and headless operation without Spriter
or Chipmunk; V8 75 tests / 1,262 assertions; browser 77 specs / 1,274 assertions;
iOS Part suite 11 tests / 153 assertions. Both documentation Topics/event audits
pass, with 65 pre-existing Doxygen warnings. The broader native client run passed
the former helper-crash point, then aborted on a separate GLFW null-monitor
assertion in `port.spec.js` while creating a window; that run did not establish full-directory acceptance. The later complete desktop pass is recorded in PHYSICS_RIG_VALIDATION.md.

Tween controls operate only on scheduled transitions and their delays. Pausing a
rate tween holds the current rate while that programmed movement, spin or growth
continues. Cancel discards targets and the pending wait, retaining sampled values
and the pause state. Clip playback, helpers and physics are independently controlled.

Checkpoint 1 verification: GUI native 4/4 tests; headless/no-Spriter/no-Chipmunk
3/3 tests; V8 programming 5 tests plus shared controls 2 tests (61 assertions
combined), AnimatedAttributes 11 tests/87 assertions; browser shared controls,
AnimatedAttributes and Drawing 66 specs/276 assertions. Regenerated V8/JSC and
Doxygen HTML/man output; four affected JSC translation units pass syntax checks.
Doxygen reports the same 77 pre-existing warnings. Sprite snapshots include new
tracks, clock state and pending wait; active Layer tween updates were subsequently implemented in checkpoint 5.
That checkpoint covered `ser_Update`; frame-based Layer initial-data reconstruction
is implemented in the follow-up below. The broader original checkboxes below remain partial.

Follow-up verification: native 5/5 suites; feature-disabled/headless 3/3;
V8 Part, PhysicsBody, pose and Layer-control specs; browser 64 specs/940 assertions
including retained handles after owner destruction, helper removal, easing and
Layer tween updates. Three affected JSC translation units pass syntax checks;
iOS runtime validation was pending at that checkpoint and is covered below. Both C++ performance targets (`bunnymark`
and `pdgmark`) and their core library compile without warnings. Removed redundant
public `setEntityScale`; demos/tests use `Animated.setScale`. Image record
serialization was unsupported at that checkpoint; it is now implemented as recorded
in the resource snapshot follow-up below. Regenerated C++/JavaScript HTML and man pages; 65 existing Doxygen
warnings remain after correcting inherited deserializer parameter documentation.

Attachment lifecycle follow-up: native owner/Spriter suites pass, the headless
owner suite passes without Spriter or Chipmunk, V8 Part passes 7 tests/98 assertions,
and browser Part/PhysicsBody/controls/pose pass 38 specs/765 assertions. Native,
headless and Wasm compilation introduces no warnings. Regenerated both references
and manual pages; Doxygen remains at 65 existing warnings.

Physical publication and platform follow-up: dynamic/static Parts retain world
poses under moving ancestors; kinematic Parts follow the current authored frame.
Parent-before-child publication handles creation order, reflection and independent
artwork scale. Dynamic ownership cancels delayed spatial programming without
consuming the pending wait or appearance/size animation. Rigid kinematic mounts
sweep to their target before the shared Chipmunk solve and reject competing body
motion; removal during a post-step callback restores configured free velocity.

Native acceptance passes 5/5 focused suites, and headless/no-Spriter/no-Chipmunk
passes 5/5. V8 Part passes 9 tests/112 assertions, pose 21/517, playback 7/54, plus
the forced-GC mount/layer lifetime regression. iOS simulator (arm64 JavaScriptCore)
passes eight suites: async runner 2/6, Part 9/112, PhysicsBody 7/110, programming
5/34, tween controls 3/35, AnimatedAttributes 11/87, pose/drawing 21/518 and
playback 7/54. The iOS runner previously failed to wait for `done` callbacks;
it now shares the browser adapter and proves asynchronous fixture ordering.
Browser acceptance passes 53 specs/858 assertions using the same callback adapter.
C++ performance targets and Wasm rebuild without warnings; regenerated references
retain the existing 65 Doxygen warnings and all class/event Topics checks pass.
This run also fixes JSC custom easing registration, numeric clip-ID validation,
and the project-config include needed to compile physical rigs on iOS. iOS still
emits existing platform conversion/OpenGL warnings; no warning-free claim is made.

Physical drive follow-up: `PhysicsBody.setDriveTarget()` drives dynamic Sprite
and Part bodies using bounded force/torque; it never teleports to the target.
Frequency/damping control response, explicit integer rotation directions resolve
an angular route, and `getDriveState()` reports target, last actuation and remaining
error. Clearing a drive preserves momentum; changing to a non-dynamic mode or
stopping all forces removes it. Active drives round-trip in current physics
records (format 2; no older-physics reader).

Verification: native basic/owner suites 2/2, headless suites 2/2, V8 and iOS
PhysicsBody 8 tests/134 assertions each, browser 41 specs/803 assertions. Tests
cover bounded actuation, full-turn directions, contact blocking, Part publication,
NoPhysics and snapshot continuation. Native and Wasm builds have no warnings;
regenerated API references retain 65 existing Doxygen warnings and Topics checks
pass. Scheduled IK-to-drive coupling and articulated constraints were completed in the subsequent Part IK/shared-constraint work.

Resource snapshot foundation: `Serializer.setResourceMode()` accepts integer
`serialization_Complete` (default) or `serialization_ExternalReferences`. Image
records now preserve pixels or named sources, strip layout, opacity, edge clamping,
frame/subsection views and shared source images. Runtime-created/modified images
retain and embed pixels; named references fail explicitly when missing or when
loaded dimensions differ. Sprite/Layer and Drawing graph integration is covered
by the completed checkpoint 5 snapshot work.

This also repairs untagged object-length decoding, truncated memory/string checks,
object-reference bounds and shared-resource size accounting. Validation covers
native/headless image snapshots after source-file removal, repeated/nested shared
resources, modified-image fallback and pre-write byte counts. V8 and browser
serialization suites pass 70 tests/683 assertions; iOS resource/serialization passes
24/277. Generated references retain 65 existing warnings and Topics coverage passes.

Frame snapshot follow-up: initial Sprite records carry their flags, image and
collision-mask object records, all 256 frames and fractional playback position.
Off-layer `deserialize_obj()` constructs a Sprite in all three script runtimes.
Replaced frame resources are released. Default `startFrameAnimation()` now selects
all frames; explicit counts no longer include an extra frame. Browser frame methods
are exposed, and V8 converts native Sprite/Layer serialization bases safely.

Unsupported initial Parts/attachments, imported rigs, constraints and callback
state now fail explicitly before raw Sprite writes rather than silently losing
state. Incremental root-body updates remain supported. Tagged record-size tests
now include their selected tags both before and after writing.

Verification: native 6/6 focused suites; headless owner suite; V8 serialization
71 tests/695 assertions and PhysicsBody 8/134; browser combined 79/829; iOS
serialization 25/289. Regenerated references retain 65 existing warnings, and all
class/event Topics checks pass. Full Layer/Part graph reconstruction remains open.

Layer snapshot follow-up: initial records now restore into empty or populated
layers, read their identities/counts correctly, retain shared frame resources and
rebase active tween pointers to the destination. Validation is staged off-world;
truncated records preserve existing membership and transforms. Validated bodies
join the basic/Chipmunk solver after publication. The destination retains its
Port, application handlers and chosen update flags. Shared-world gravity/damping
is still application configuration.

`ser_Full` now includes Layer draw transforms. Initial records preserve Sprite
reflection, pending Layer fade completion delays and cached gravity settings;
constructors initialize inactive fade timers. Runtime identity counters advance
past restored IDs. Current initial Layer/Sprite formats reject unsupported older
records, and unsupported Part/rig/controller/constraint graphs still fail explicitly.

Validation: native owner suite covers both resource modes, tags on/off, basic and
Chipmunk solvers, repeated replacement, retained old sprites, truncated input,
shared resources and tween continuation. Headless/no-Spriter/no-Chipmunk owner
suite passes. V8 and iOS serialization each pass 26 tests/301 assertions; browser
serialization, tween controls and PhysicsBody pass 83 specs/876 assertions.
Regenerated references retain 65 existing warnings and Topics checks pass.

Independent Part/Drawing snapshot follow-up: Sprite initial records preserve
stable Part IDs/names (including retired-ID counters), creation order, forward
parent links, reflected transforms, paused tracks, body state and active loads/drives.
Parents resolve before physical publication. Drawing records preserve every current
primitive, attributes, nested drawings, shared editable storage and image resources.
Both save modes embed Drawing geometry; named images follow the writer policy.
Unsupported mounts, authored rigs, constraints, callbacks and Font resources still
fail explicitly. GUI-disabled builds restore Parts without artwork.

The Part reader stages its replacement and rejects duplicate identities, missing
parents and cycles. Layer loading keeps the live graph unchanged on failure.
The native string reader now excludes its NUL terminator from std::string length,
which prevents false Part-name mismatches. Full controller/mount/rig graph work
remains open.

Verification: native 6/6 focused suites plus duplicate/missing/cyclic Part-link
regressions; feature-disabled headless owner suite passes. V8 and iOS serialization
pass 27 tests/337 assertions each. Browser serialization, controls, PhysicsBody
and Part suites pass 93 specs/1024 assertions. Native/headless/Wasm builds introduce
no warnings. Regenerated references retain 65 existing Doxygen warnings; all
class/event Topics checks pass.

Mounted graph follow-up: Layer initial records include rigid mount relationships,
restored after all Sprite and Part records. Nested mounts preserve child-first draw
order, mounting Part identity, sampled child grip frames, held error state and
kinematic body restrictions. Restored groups retain remove/add/cleanup behavior.
Missing endpoints, duplicate ownership, cycles and truncated mount records reject
without replacing the live Layer. Standalone Sprite saves require the owning
Layer when mount relationships are present.

Verification: native 6/6 focused suites, headless owner suite, V8 and iOS
serialization 28 tests/361 assertions each, browser combined 94 specs/1048 assertions.

Imported asset lifetime follow-up: Layer caches and their Sprites share model
ownership. Spriter factories and image wrappers no longer retain source-Layer
pointers; rendering uses the active Sprite's Layer. Transferred/off-layer retained
sprites keep playback, pose bindings, modifiers and artwork after cache destruction.
The final Sprite/cache owner releases the model; immutable rig descriptions can
remain alive independently. Image factories balance their acquired resource refs.

Native acceptance includes post-transfer artwork rendering, fresh pose sampling,
Part bone identity, callback retention and final model release. Headless Spriter
without Chipmunk now runs both owner/playback suites; it exposed and fixed a
Chipmunk-only test call and uninitialized basic-solver Sprite restitution. Drawing
callback acceptance waits for rendered frames rather than a fixed 100 ms delay.

Validation: native 6/6 focused suites; headless Spriter/basic-physics 2/2 suites;
feature-disabled owner suite passes. V8 and iOS pose suites each pass 22 tests/526
assertions. Browser pose, playback, Parts, physics and serialization pass 74
specs/1190 assertions. Native/headless/Wasm builds introduce no warnings;
regenerated references retain 65 existing Doxygen warnings and Topics coverage.
Imported-rig snapshot records and checkpoint 4 controllers/constraints were
completed in the later graph/rig acceptance recorded above.

### Snapshot resource policy (approved)

The caller chooses the policy for each save; it is not a global Image setting.
Complete mode embeds the assets needed by the saved graph: imported animation
source and dependent artwork, runtime-created Image data, and Drawing content
including its resources. External-reference mode may replace reusable assets with
stable resource identifiers resolved on load. Runtime-only content without a
resolvable identifier must be embedded or produce an explicit save error; it must
never silently disappear. The record identifies its resource policy so the reader
does not have to guess.

Both modes preserve the same object identities, shared asset relationships, Part
hierarchies, mounts, physical state, active loads/drives and supported controller
state. Load reconstructs the graph before resolving cross-object links. Complete
mode must load with the original files and resource cache unavailable. Reference
mode must report missing or incompatible resources with their identifiers.
Neither mode promises to serialize arbitrary native/JavaScript closures; unsupported
custom callback state must fail explicitly or use a registered named factory.

## Execution checklist — 2026-09-20

Original execution checkpoints, reconciled against later implementation and
acceptance. The current summary above determines remaining work:

- [x] A. Migrate Animated, inherited fades/zoom, helper callbacks and easing to
  floating-point seconds; preserve explicit scheduler and old-data boundaries.
- [x] B. Implement programmed movement/spin rates, interval integration,
  interruption rules, floating-point scale and integer rotation directions.
- [x] C. Introduce independent Part identity/transforms, Sprite ownership,
  optional bone binding and safe retained native/script references.
- [x] D. Move physical state/operations to optional PhysicsBody, with shared
  NoPhysics, basic/Chipmunk implementations and one authoritative update path.
- [x] E. Connect authored bindings, Part content, sockets/attachments, explicit
  Part chains and physics relationships to final transform publication.
- [ ] F. Introduce owned immutable clip data and per-instance evaluation behind
  the compatibility path; establish parity before retiring runtime dependencies.
- [x] H. MVC theme/appearance composition, rotated/reflected rendering,
  clipping/hit testing and composite layout are implemented in both languages;
  View remains physics-free.
- [x] G. Complete references, Topics, generated bindings/docs and recorded
  desktop/headless/browser/iOS and feature-disabled acceptance for implemented APIs.
  Remaining Windows/Linux GUI/script and manual acceptance stays in the current summary.

Implemented portions (the stages below are not all complete):

- [x] Native Animated durations, stepping, helper callbacks and easing use seconds;
  V8/JSC bindings and focused timing tests cover fractional seconds.
- [x] Programmed movement/spin, eased rate integration, interruption and integer
  rotation directions are implemented and covered by native/script tests.
- [x] Native Part identity, independent local transforms, Sprite ownership,
  optional bone binding, hierarchy cycle checks and detached retained references.
- [x] V8/JSC Part bindings and factory-only construction; V8 identity and lifetime
  behavior covered by the Part spec.
- [x] Standalone basic PhysicsBody calculations, immutable shared NoPhysics,
  impulse/force and angular-impulse/torque separation, finite timed loads,
  exponential damping, and timestep partition tests.
- [x] Remove physical methods/state/integration from Animated and its inherited
  V8/JSC surface. Layers and MVC inherit programmed transforms without physics.
- [x] Add Sprite/Part setupPhysicsBody(), removePhysicsBody(), and read-only script `.physics` with shared `pdg.PhysicsBody.NoPhysics`.
  Retained bodies detach safely; owners advance basic bodies once per tick.
- [x] Integrate Sprite PhysicsBody with Chipmunk world stepping. Timed loads use
  their active seconds intervals; Chipmunk alone integrates body position.
- [x] Version physical snapshots separately from animation records, including
  body mode, state, material/damping, and pending finite/continuous loads.
- [x] Complete Part contact/constraint support and Chipmunk integration, basic
  collision/joint parity, browser body bindings and broader platform validation.
  Shared Collider and PhysicsConstraint contracts and graph snapshots are
  validated in native, V8, browser and iOS/JSC builds; see checkpoint 5.
- [x] Native and JavaScript MVC View inherit AnimatedAttributes; all visual subclasses
  inherit through View. Controllers and style/data objects remain separate.
- [x] MVC movement/size changes synchronize layout and clickable geometry;
  PortDraw advances views once in seconds; dialog and scrolling edits use
  Animated-aware setters. MVC does not receive a PhysicsBody or `.physics`.
- [x] Apply MVC rotation/reflection to rendering, exact clipping and inverse hit
  testing; visual children follow parent layout, draw order and visibility.
- [x] Finish floating-point scale, growth/stretch rate easing, animation control
  queries, animation serialization migration coverage, Wasm parity, API docs and
  feature-disabled builds. Full scene graph snapshots remain in checkpoint 5.

AnimatedAttributes implementation (C++, V8, JSC and Wasm bindings):

- [x] Combine Animated and Attributes without an ElementRef or physics body.
- [x] Add seconds-based continuous appearance tweens with easing, waits and per-channel interruption.
- [x] Keep blendMode, font, clipOverflow, lineStyle, textStyle, texture and fitType immediate-only.
- [x] Add delayed integer frame sequences and discrete fill-mode changes.
- [x] Share one affine transform with Animated; define 1x1 reference size, shear/reflection handling,
  coefficient interpolation and explicit rotation-direction controls.
- [x] Make C++ base-reference setters interrupt matching tracks; preserve current-value snapshot copies.
- [x] Expose both JavaScript method surfaces and safely convert the secondary Attributes base pointer.
- [x] Migrate View inheritance in C++ and JavaScript; continue stepping once per PortDraw without physics.
- [x] Add native and JavaScript coverage for transforms, appearance, snapshots, invalid requests and MVC stepping.
- [x] Add browser/Wasm AnimatedAttributes bindings and verify shared appearance/drawing specs plus the interactive control gallery. Browser physics/Part acceptance is also complete in checkpoint 5.
- [x] Explicit appearance channels override the selected ControlAttributes state;
  unset channels inherit the theme. Text retains its state foreground while taking
  View text metrics, opacity and blend overrides. Custom drawing uses withAppearance().
- [x] Live Drawing-element attribute associations are implemented.

Implemented contract and retained design notes:

- The animation target is Attributes itself. This replaces the earlier
  AnimatedElement proposal: no ElementRef is required to construct or advance it.
  `AnimatedAttributes : public Animated, public Attributes` provides programmed
  transforms/timing and drawing attributes in one object. Rendering/appearance
  knowledge stays in AnimatedAttributes, outside Animated.
- Add timed animation methods for all Attributes properties except `blendMode`,
  `font`, `clipOverflow`, `lineStyle`, `textStyle`, `texture`, and `fitType`. These
  seven remain available through their ordinary immediate Attributes setters;
  they do not acquire animation tracks. Texture crossfades are outside this design.
- Continuous appearance channels cover line color/thickness/opacity, fill
  color/opacity, linear-gradient endpoints and colors, radial-gradient center,
  radius and colors, rounded-corner radius, text size, image subsection rectangle,
  sphere rotation, polar/light offsets, and ambient-light color.
- Translation, rotation, scale, skew and transform are also in scope. Use one
  authoritative transform model: inherited Animated movement/spin/growth and
  Attributes transform operations must agree, including changes through either
  base interface. Decompose authored matrices into the same position, rotation, signed size and
  shear state, and compute the matrix without repeatedly accumulating deltas.
  The reference size is 1x1. Timed matrices interpolate affine coefficients and
  may pass through singular matrices; explicit rotations retain integer direction controls.
- `frame` remains animatable through sequences of integer frames. `fitType`
  is explicitly excluded from animation, including scheduled changes. Gradient
  type switches discretely while its numeric/color parameters can interpolate. Do not
  interpolate enum ordinals or imply automatic crossfades between gradient modes.
- No control-point, vertex, path or shape-morphing animation is introduced.
  Rounded corners, text size, subsection and transforms are rendering attributes;
  their animation does not rewrite stored Drawing geometry. Geometry edits remain
  explicit ElementRef operations.
- All durations, delays and steps use floating-point seconds. Easing, delays and
  interruption follow Animated. Define direct property setters to interrupt the
  corresponding channel without cancelling unrelated channels; setters that also
  change gradient/line modes need explicit, consistent channel behavior.
  AnimatedAttributes has neither a PhysicsBody nor `.physics`.
- Make the object usable wherever an Attributes argument is accepted, in both
  C++ and JavaScript. JavaScript needs both method surfaces and correct native
  base-pointer conversion; C++ multiple inheritance alone does not provide a
  second JavaScript prototype chain. Document type-check behavior explicitly.

Drawing-element live attributes — implemented 2026-09-25:

- `ElementRef.setLiveAttributes(attrs)` follows Attributes or AnimatedAttributes.
  `getAttributes()` still returns a copy; `setAttributes()` clears the association.
  `clearLiveAttributes()` freezes the current sample; `hasLiveAttributes()` queries it.
- Sources may be shared across elements/Drawings. The caller advances animations
  once per update; replay never advances a source. If the source is destroyed, its
  final values and resources remain available. Snapshots capture values only.
- ElementRef identities survive reorder/removal without retargeting other elements.
  Bounds and hit tests read live transforms, and inverse transforms map hits to
  the stored geometry. Geometry edits remain explicit.

AnimatedAttributes and MVC verification (2026-09-21):

- Native: 7/7 focused suites pass, including AnimatedAttributes, MVC View, Animated,
  PhysicsBody, Sprite/Part owners, Spriter playback and animation poses.
- Headless libraries build with GUI, Spriter and Chipmunk disabled; 4/4 focused
  native suites pass, including AnimatedAttributes and independent physics owners.
- JavaScript: AnimatedAttributes 10 tests / 77 assertions; MVC animation 9 / 82;
  existing MVC 44 / 154; existing Drawing/Attributes 53 / 162; Animated 50 / 182.
- `./test/demo --automated mvc` checks AnimatedAttributes inheritance,
  intermediate and final appearance, moved control layout and hit testing.
  Rotated MVC input coverage is described in the 2026-09-26 follow-up below.
- The C++ control gallery builds. JSC Attributes, Drawing, Port and registration
  bindings pass syntax checks; iOS project syntax validates. These are compile
  checks rather than JSC/iOS runtime acceptance.
- C++ and JavaScript HTML regenerate with AnimatedAttributes in the Animation and
  Graphics Topics and all appearance methods listed. Doxygen retains 77 warnings.
- Browser/Wasm: AnimatedAttributes and Drawing/Attributes pass 63 tests / 239
  assertions. The browser gallery passes its finite check with 46 real PortDraw
  frames, intermediate color, final opacity and moved control layout verified.
  Browser mouse input confirms button clicks, checkbox toggling, and default
  and themed dialogs. The existing browser MVC sample also passes.
- Wasm uses a native Animated base and a borrowed, adjusted Attributes pointer;
  JS View subclasses retain their own prototypes. Native drawing receives the
  current sample, and retained Drawing elements continue to copy it.
- The browser gallery is now `test/ui.html?test=mvc`; add `&automated=1`
  for a finite check. Shared browser specs accept `?specs=animatedattributes,drawing`.
  Build objects now track header dependencies to prevent stale animation ABI links.

Implementation decisions for A/B:

- Timed animation arguments are seconds regardless of numeric magnitude. This
  is an intentional API migration; old callers must divide millisecond durations
  by 1000. General timers and audio-duration APIs retain their documented units.
- Built-in and custom easing callbacks receive seconds, including when invoked
  by a remaining millisecond-based subsystem at an explicit conversion boundary.
- Existing rotateTo calls retain the raw unwrapped target by default
  (`rotationDirection_AsSpecified`). Callers can explicitly select Shortest,
  Clockwise or CounterClockwise after the easing argument. Positive local angles
  are clockwise; reflected parents can reverse the apparent world direction.
- Relative rotate preserves signed full turns by default. An explicit clockwise
  or counterclockwise selector chooses the sign of the requested travel magnitude.
  Equal absolute orientations request no extra turns; relative turns express them.
  Exact shortest-path half-turn ties use the positive direction. Direction picks
  the angular route; back/elastic easing can still overshoot or backtrack.
- Rate transitions integrate their eased rate over the interval. A direct
  position/orientation tween replaces programmed movement/spin on that channel;
  starting a programmed rate cancels a direct tween on its channel. Interruptions
  start from current state. Delayed requests acquire their starting value when
  the delay expires. No body is allocated for programmed motion or size changes.
- Serialized animation clocks need an explicit revision marker and double-second
  values. Old marked-by-layout integer-millisecond records are converted on read;
  no timing unit is inferred from a value's magnitude.

## Direction from the API review

- `Animated` describes programmed changes to one entity's transform: immediate
  changes, eased changes, continuous movement, and spin. It has no physical
  simulation, rendering, child collection, rig, bone, or multi-element duties.
- `move` / `moveTo`, rotation, spin, and `getSpin()` belong to `Animated`.
  `setMovement` sets rates immediately; `changeMovementTo` / `changeMovementBy`
  take explicit seconds and easing. `getMovement()` returns an `Offset` of rates per second.
- Growth, stretching, and resizing belong to `Animated`, including continuous
  growth/stretch rates, immediate size changes, and changes eased over a duration.
  They do not become PhysicsBody operations when a Sprite or Part has a body.
- Durations and easing can program a slowdown in movement, spin, growth, or
  stretching. Physical damping, friction, velocity, speed, mass, inertia, forces,
  impulses, torque, and angular momentum belong to `PhysicsBody`.
- Sprites, Parts, Layers, and visual MVC Views/controls are Animated objects.
  Only Sprites and Parts can have a `PhysicsBody`; body ownership is not a
  capability of `Animated`. MVC views have neither PhysicsBody nor `.physics`.
  Controllers and nonvisual style/data objects do not inherit Animated.
- Provide the same public PhysicsBody operations with PDG's basic calculations
  when Chipmunk is unavailable. Approximation quality can differ; API availability
  and the meaning of units and operations must remain consistent.
- Separate linear impulse from force over time, and angular impulse from torque
  over time. Neither a force nor a torque changes meaning at zero duration.
- Prefer `Part` for an independently addressable subsection of a Sprite.
- Every `Part` owns a transform, including a part with no artwork, bone binding,
  or physics body. A label selecting existing geometry is insufficient.
- Use `Part : public Animated` in C++ and expose the same inheritance in JavaScript.
  `Sprite` continues to inherit `Animated` for its whole-entity transform.
- A part can optionally bind to a bone. `getBoneId()` is always safe to call on
  a valid Part and returns the integer constant `boneId_None` when unbound.
  `isBoundToBone()` is optional convenience for readability/filtering, equivalent
  to comparing that result against `boneId_None`; it is never a required guard.
  Binding and Sprite ownership belong to `Part`, leaving `Animated` independent
  of hierarchy and skeletons.
- Separate Sprite ownership from bone binding, IK control, and physical
  constraints. A Part can have an optional bone binding and PhysicsBody and
  participate in zero or more controllers/constraints. Define explicitly which
  system publishes its final transform; these mechanisms can be combined.
- Make PDG-owned animation assets, clip evaluation, and per-instance state the
  destination architecture. Keep Spriter as an authoring/import format; replace
  SpriterPlusPlus runtime dependencies incrementally with verified parity.
- Allow explicit rotation direction whenever a rotation is animated over
  time. Preserve authored direction and deliberate full turns; cover Animated
  tweens and higher-level pose transitions/recovery, not just imported clips.
- Extend the Part design to cover attachments. The socket/content/attached
  Sprite model below is a recommendation for discussion, not a finalized API.
- Migrate all Animated public timing from integer milliseconds to floating-point
  seconds. Include its timed methods, public update entry, helper/easing callbacks,
  inherited callers, bindings, examples, and serialization compatibility.
- Modes and coordinate spaces use integer enum constants; authored names remain
  strings. The `.physics` / shared `NoPhysics` association is now implemented;
  broader relationship/drive policies below remain under development.

A physics body is an optional physical representation of a Sprite or Part.
Owning a transform does not require allocating a body. Parts and basic physical
motion must also be usable without Spriter or Chipmunk support. Recommended
composition is an optional PhysicsBody on each eligible owner, with one active
basic or Chipmunk implementation behind its public interface.

## Proposed responsibilities

| Type | Responsibility |
| --- | --- |
| `Animated` | One transform, logical dimensions/pivot, programmed movement/spin and growth/stretching, easing, delays, and animation helpers; no physical integration |
| `Part : Animated` | Independent subsection identity and transform; owning Sprite; optional bone binding, content, and physics association |
| `Sprite : Animated` | Whole-entity transform; optional PhysicsBody; part ownership; rendering and ordering; clip/rig evaluation; coordinating final publication |
| `SpriteLayer : Animated` and derived layers | Programmed layer transforms and layer behavior; no PhysicsBody |
| `View : AnimatedAttributes` and derived visual MVC controls | Programmed transforms, appearance and layout; rendering/input remain View responsibilities; no PhysicsBody or `.physics` |
| `PhysicsBody` | Physical velocity/speed/angular velocity, mass/inertia/angular momentum, impulses, forces/torques, damping, and physical properties; basic and Chipmunk implementations |
| Bone / rig | Skeletal hierarchy, skeletal pose, IK, and constraints; separate from part identity |
| Physics implementation / joint | Integration, collision geometry/materials, and physical relationships; body indices remain implementation details or explicitly low-level IDs |

The root Sprite and a Part share movement operations through `Animated`; neither
requires the base class to know what the entity contains. Opacity, fades, artwork,
frame selection, and visual bounds belong on visual owners, not `Animated`.

## PDG-owned animation assets and playback

Agreed direction: make PDG data authoritative at runtime and treat Spriter as an
import format. Retain Spriter authoring/export compatibility. This is a planned
replacement of the SpriterPlusPlus runtime dependency, not a claim that the
existing library is only a loader or that the replacement is already implemented.

Current SpriterPlusPlus responsibilities include loading authored tracks,
mainline/timeline key selection, interpolation, playback clocks, looping, image
and pivot selection, drawing order, character maps, and evaluated variables/tags.
PDG owns the newer rig/pose representation, overrides, modifier pipeline, IK,
independent transition timing/blending, trigger dispatch, targets, physical rigs,
and Drawing attachments. PDG performs the graphics calls, while Spriter objects
still supply much of the visual state and rendering traversal.

The current adapter reads evaluated Spriter locals into a PDG pose, applies PDG
controllers, and writes the final transforms back into Spriter objects for
rendering and queries. Independent clip sampling also creates a temporary
Spriter entity evaluator. These are runtime dependencies, not import-only work.

Recommended destination structure (type names remain illustrative):

| Component | Data and responsibility |
| --- | --- |
| Shared immutable animation asset | Part/bone definitions, clips, tracks, curves, images, pivots, presence/order, character maps, events, variables and tags |
| Per-Sprite animation instance | Playback clocks, transitions, Part instances, current pose/visual state, overrides, controller state and physics associations |
| PDG clip evaluator | Samples authored tracks at floating-point seconds to produce local pose, visual state and metadata; independent of rendering and physics |
| PDG final consumers | Rendering, bounds, sockets, attachments and collision queries consume the same published state directly |
| Spriter importer | Converts source IDs, coordinates, timing and authored semantics to the owned asset format; no Spriter objects in public Part APIs |

AnimationRig and AnimationPose already supply useful structure and evaluated
state. They do not contain a complete authored clip representation. Keep the
multi-element clip evaluator outside Animated. Convert file milliseconds to
floating-point seconds at import; seconds are the animation runtime/public unit.

Migration sequence and acceptance work:

- [ ] Define the owned asset/clip/track format and per-instance state boundary
  before freezing Part APIs; keep shared definitions immutable and IDs scoped to
  assets/revisions, with explicit per-instance Part identity.
- [ ] Inventory supported existing playback independently of the fixed-hierarchy
  pose adapter. Cover bone-free assets, changing active elements/hierarchies,
  metadata and visual state; specify any deliberate compatibility limits.
- [ ] Import SCML into PDG structures, including key curves, mainline/timeline
  relationships, authored rotation direction/hold, image swaps, per-key pivots,
  drawing order, character maps, events, variables and tags. Preserve existing
  resource loading. SCON, audio and atlases remain separately scoped extensions.
- [ ] Implement direct clip sampling and playback with seconds, boundary/loop
  behavior, seeking, paused state and retained clip times. Preserve deliberate
  turns; shortest-angle pose blending cannot substitute for authored rotation.
- [ ] Connect owned samples to existing PDG modifiers, IK, transitions, trigger
  dispatch and physics mapping without double stepping or duplicate events.
- [ ] Publish owned visual/spatial state directly to rendering, bounds, sockets,
  attachments and collision queries; remove the write-back into Spriter objects.
- [ ] Run both evaluators against representative fixtures and compare local and
  world transforms, reflection, directed rotations, visual selection/pivots/order,
  metadata and event behavior. Use the existing runtime as a baseline while
  documenting intentional corrections rather than preserving its known bugs.
- [ ] Keep a compatibility path while parity is incomplete; migrate loading,
  model caching, lifetime handling, bindings and build configurations before
  removing the dependency. Leave the third-party submodule itself unchanged.
- [ ] Verify C++/JavaScript, headless and GUI behavior, shared-asset instance
  isolation, and operation without SpriterPlusPlus. Measure sampling allocations
  and runtime costs rather than assuming a speedup from ownership alone.

## Part relationships: bones, IK, and physical constraints

For the intended generated-rig API, control modes, selection semantics and current
remaining work, use the [2026-09-23 rig plan](ANIMATION_PHYSICS_RIG_PLAN.md).
The design inventory below predates the completed independent Part IK work.

Agreed direction: ownership, transform relationships, and control are separate.
A Part belongs to its Sprite regardless of how it moves. An ordinary unbound
Part can follow the Sprite root through its own local transform without bones,
IK, a physics body, or a physical joint. Animated itself owns none of these
relationships; they are managed by Part, Sprite, and the relevant controllers.

| Mechanism | Responsibility | Structure |
| --- | --- | --- |
| Bone binding | Supplies a reference frame for a Part's independent local transform | A skeletal hierarchy is a tree; multiple Parts can bind to one bone |
| IK control | Calculates transforms along a defined chain to reach an endpoint target | Selects a chain/path and target; it needs existing relationships and does not establish ownership or attachment by itself |
| Physical joints, springs, constraints | Relate physical bodies through anchors, limits, springs, and other solver rules | A constraint graph can contain loops and connect otherwise unrelated Parts |

Use the term **physical constraints**, with Chipmunk and basic PDG implementations.
The basic implementation must provide the agreed public behavior with documented
approximations. The relationship does not depend on Chipmunk being available.
Do not force the skeletal tree, selected IK chains, and physical constraint graph
into a single parent pointer or mutually exclusive attachment type.

For an upper arm, forearm, and hand, the shoulder/elbow/wrist bone relationships
can establish a hierarchy, IK can choose joint rotations to reach a hand target,
and physical joints can connect corresponding bodies at those same locations.
The same arm can carry all these relationships; its control mode determines the
final transforms.

| Combination | Final-transform control |
| --- | --- |
| Bones with authored animation | Evaluated bone pose, composed with each Part's local transform |
| Bones with IK | Pose after the ordered IK solve, composed with Part-local transforms |
| Physical bodies with joints | Solved physical transforms; mapped bones and the skeleton can follow the result |
| IK with dynamic physical bodies | IK supplies a desired pose; a controller uses forces/motors to drive the bodies toward it, and physics supplies the final result |

The last combination is **active physical animation**, now explicitly included
in checkpoint 4 along with the passive relationships. It requires a controller between desired
pose and physical actuation. It is not implemented merely by running the existing
IK and passive-rig APIs together. A blocked or force-limited body can legitimately
fail to reach the IK target. Do not apply the desired IK pose over dynamic-body
transforms after the solve.

Bone binding and physics may coexist on a Part. When animation controls a
kinematic body, the evaluated bone/Part pose supplies its target. When a dynamic
body controls motion, the solved result supplies the final Part transform and
may feed mapped bones. Preserve the Part's binding identity while changing the
direction of control; `getBoneId()` reports the relationship, not which solver
currently controls motion. Multiple inputs may supply targets or restrictions,
but the publication policy must resolve one final transform for each Part and
prevent conflicting physical bodies from independently writing the same bone.

Direct IK over **Part chains without bones** is implemented through
`solveIK()` and scheduled `setIKTarget()`. Physical chains use
`setIKDriveTarget()` with explicit release, joint limits and bounded actuation.
An unbound Part still reports `boneId_None`. Mapped animation-physics Parts use
animation IK plus rig Driven control; independent Part IK rejects that mapping.

The former design-task checklist is covered by
[completed Part IK/control work](#part-ik-and-physical-control--completed-2026-09-22),
[checkpoint 4](#active-follow-up-checkpoints--2026-09-21), and the
[controller-to-test mapping](RIG_COVERAGE_AUDIT.md):

- [x] Separate ownership, binding, transform parenting, chain selection and
  physical constraint identities; validate incompatible/foreign endpoints.
- [x] Evaluate authored/procedural targets, IK and drives before the shared
  solve, then publish one authoritative physical result to final consumers.
- [x] Validate unbound chains, editable anchors/limits, conflicting controllers,
  explicit handoff, retained handles, snapshots and Basic/Chipmunk Part drives.
- [x] Verify combined animation IK + rig Driven control, external loads,
  collision blocking and exact elapsed-time accounting without double stepping.

Basic supports independent Part bodies/constraints/drives; animation rigs require
Chipmunk permanently.

## Attachments and Part composition (discussion)

The native/V8/JSC/WebAssembly model is implemented: Image/Drawing content, authored
binding/socket frames, and a dedicated animated mounting Part returned by
`Part.attachSprite(child, placement, childMount)`. A child mounting frame is sampled
once; placements use integer Snap/PreserveWorld constants. Sheared/singular root
placements and competing physics writers are diagnosed. The retained discussion
below also includes physical holding and future extensions. Keep content, attachment
relationships, Sprite ownership and physics control distinct.

| Concept | Recommended meaning |
| --- | --- |
| Part content | Image or Drawing content that moves with the Part; replacing artwork need not change Part identity, local transform, binding or controllers |
| Socket | A named transform-only Part used as a mounting frame; it can follow the root, a bone, or another Part and needs no artwork or physics body |
| Attachment | A relationship aligning a child Sprite's root or named mounting frame with a host Part/socket, plus a local offset |
| Attached Sprite | An independent Sprite retaining its own Parts, rig, clip playback and optional physics; attachment does not merge or transfer those Parts into the host Sprite |

For example, a character's hand Part can carry a `weaponGrip` socket. A sword
Sprite attaches by its own `grip` frame; its guard, blade, effects or independent
animation remain part of the sword. A simple decorative image can instead be
content on an ordinary Part. Do not turn every image into another Sprite.

Recommend supporting Part-relative transform parenting for mounting frames,
including a socket on an unbound Part. A Part's ordinary reference frame is the
Sprite root, a bone, or another Part; it has one transform parent at a time.
Sprite ownership remains unchanged. This transform tree does not replace IK
chains or the physical constraint graph, and no child collection moves into
Animated. Imported point/socket definitions should map to the same mounting
concept without creating competing copies of their transform state. getBoneId()
reports a Part's own binding, not a bone reached indirectly through its parent;
a Part-relative socket without its own bone binding returns boneId_None. An
attached Sprite's bone IDs remain scoped to its own rig.

In rigid-follow mode, align the child's selected mounting frame to the host
socket using the attachment offset. Both may have position and orientation;
the child's artwork pivot need not be its grip. Recommend a stable child-local
mounting frame initially; an animated child grip introduces an evaluation
dependency that must be scheduled explicitly. Reject cyclic dependencies.
Allow the attachment offset itself to be animated in the host socket frame.

Original policy discussion (the implemented mount contract above and API reference take precedence):

- Provide explicit snap-to-mount and preserve-world placement when attaching or
  reparenting, and preserve-world placement on detach. "World" is owning-layer
  space; define cross-layer conversions or reject incompatible layers. Specify
  singular-transform failures and avoid partial relationship changes.
- Make inherited position, rotation, scale/reflection and visual opacity policy
  explicit. Full spatial inheritance is a useful rigid-follow default, but the
  current Sprite attachment API only copies position and angle. Do not silently
  change that compatibility path. Physical bodies also need a scale policy.
- One child has one active rigid-follow attachment; reject ownership/attachment
  cycles. Distinct sockets or an explicit attachment collection can permit
  multiple children on a host. Slot replacement and occupancy are explicit.
- Retain the attached Sprite safely without changing the ownership of its Parts.
  Define detach, destruction, host Part removal and entity/rig replacement,
  including invalid handles and whether orphaned children remain in the layer.
- Define whether child rendering stays in layer order or is inserted around the
  host Part's artwork. Draw/update each child once, include child bounds where
  needed, and keep internal child ordering intact. Clip pause/time inheritance
  is a separate option, not an automatic consequence of spatial attachment.
- A rigid-follow attachment may drive a nonphysical or explicitly kinematic
  child. A dynamic child follows a physical joint/constraint or a target/drive
  controller; do not overwrite its solved transform every frame. The existing
  Part/PhysicsBody authority rules apply to both simple and composite children.
- Releasing a held object preserves its final pose. Decide separately whether
  to inherit linear/angular motion, including rotation about the host's pivot;
  a dynamic release needs measured or physical motion, not just getMovement().

The implemented API is `Part.attachSprite(child, placement, childMount)`,
returning a dedicated mounting Part. Offsets animate on that Part; child Sprite
identity and Part ownership remain independent. Snap/PreserveWorld placement,
cycle/lifetime validation, hierarchy layer transfer, nested rendering and
nonphysical/kinematic following are covered by checkpoint 3/5 tests.

The former attachment design checklist is consolidated into
[checkpoint 3/5](#active-follow-up-checkpoints--2026-09-21) and
[Part attachment references](../cxx/dox/part-methods.dox). Dynamic holding uses
shared physical constraints/drives rather than a rigid mount. Child grips are
sampled at attachment time; animated grips and automatic clip-clock inheritance
are not implemented promises of the current mount API.

## API inventory

Reconciled 2026-09-25. These are implemented surfaces unless explicitly marked
open; historical candidate names do not override public headers/references.

| Area | Current contract | Status |
| --- | --- | --- |
| Timing/programmed motion | Seconds, movement/spin/growth rates, eased integration, schedule controls and integer rotation routes | Implemented, native/V8/JSC/WebAssembly |
| Part identity/frames | Independent Sprite-owned Parts, safe bone/binding queries, local/world transforms, authored offsets and retained references | Implemented |
| Part composition | Image/Drawing content, sockets and independent mounted Sprites | Implemented, including kinematic sweeps and graph snapshots |
| Independent Part IK | Direct/scheduled chains, editable limits and force/torque-limited physical drives | Implemented in Basic and Chipmunk |
| PhysicsBody/Collider/PhysicsConstraint | Optional Sprite/Part components, shared NoPhysics/NoCollider, contacts, joints, drives and snapshots | Implemented; Basic has documented approximations |
| Animation physics | Generated/explicit shared rigs, modes, handoff, recovery, membership/transfers, loads, mass/inertia and reflection | Implemented; requires Chipmunk |
| PDG-owned clip runtime | Immutable authored tracks and independent evaluator, replacing runtime dependence on Spriter after parity | Open, checkpoint 6 |
| MVC appearance/transforms | Theme composition, rotation/reflection, clipping/hit testing and composite layout | Implemented, checkpoint 2 |
| Port clipping/drawing overflow | Single non-nested Port clip and clipOverflow for all drawing | Implemented, including MVC scrolling-view acceptance |
| Drawing element attributes | Explicit live association with Attributes/AnimatedAttributes, preserving default copy semantics | Implemented |

Illustrative calls using the implemented API:

```javascript
const forearm = sprite.findPart("forearm");
const boneId = forearm.getBoneId(); // Always safe; no preliminary guard.
if (boneId !== pdg.boneId_None) {
    // Use the binding. Bone IDs and Part IDs are distinct.
}

// Implemented inherited Animated operations; duration is seconds.
forearm.moveTo(new pdg.Point(12, 0), 0.25);
forearm.rotateTo(0.3, 0.5, pdg.easeOutQuad, pdg.rotationDirection_Clockwise);
forearm.setMovement(new pdg.Vector(20, 0));
forearm.changeMovementTo(0, 0, 0.5, pdg.easeOutQuad); // programmed slowdown
const movement = forearm.getMovement(); // Offset, rates per second

// Implemented null-object surface: no body means a safe no-op (debug diagnostic).
forearm.physics.applyImpulse(new pdg.Vector(4, 0));
forearm.physics.applyTorque(2, 0.25);
```

The calls above are implemented in native and all three script runtimes. Dynamic
bodies reject programmed movement/spin; immediate transform setters teleport a
body. The relationship, constraint and snapshot contracts are also implemented.

## Programmed movement and spin

Implemented native declarations on Animated<T> (Self is the selected owner type):

```cpp
Self& setMovement(const Vector& movement);
Self& setMovement(float xPerSecond, float yPerSecond);
Self& changeMovementTo(const Vector& movement, double seconds, EasingFunc easing = linearTween);
Self& changeMovementTo(float xPerSecond, float yPerSecond, double seconds, EasingFunc easing = linearTween);
Self& changeMovementBy(const Vector& delta, double seconds, EasingFunc easing = linearTween);
Offset getMovement() const;
Self& setSpin(float radiansPerSecond);
Self& changeSpinTo(float radiansPerSecond, double seconds, EasingFunc easing = linearTween);
Self& changeSpinBy(float deltaRadiansPerSecond, double seconds, EasingFunc easing = linearTween);
float getSpin() const;
```

Setters are immediate; change methods require explicit seconds. setGrowing and
setStretching establish constant logical-size rates; changeGrowingTo/By and
changeStretchingTo/By transition them over explicit seconds. Appearance change
methods likewise require seconds.

JavaScript uses the corresponding overloads, fractional `number` durations, and
integer easing constants (with existing custom-easing support considered during
binding migration). `getMovement()` returns an Offset, although its components
are rates in local distance units per second, not a last-frame displacement.

Recommended rate contract: a duration eases the current programmed movement rate
to the requested rate, beginning at the current value when interrupted. The
getter reports the current programmed rate, including intermediate values during
that transition. `getSpin()` behaves similarly in radians per second. These
getters do not report the derivative of a position/rotation tween or a body's
actual physical velocity. A zero duration sets the programmed rate immediately.

Easing movement or spin toward zero expresses a programmed slowdown. It does
not involve mass, momentum, drag, contact friction, or a physics solver. Growth
and stretch can use the same approach for programmed size changes; size damping
does not belong to the rigid-body interface.

- [x] Implement both movement overloads with the Offset return type; define
  finite inputs, duration/default behavior, interruption, `wait`, cancellation,
  and fractional-second behavior consistently in native and script APIs.
- [x] Extend spin-rate programming with the corresponding duration/easing
  behavior; distinguish programmed spin from physical angular velocity.
- [x] Define how rate animation combines with `moveTo` / `rotateTo` on the same
  channel, including stopping, pausing, and resuming. Avoid accidental double
  application of displacement or rotation.
- [x] Integrate an eased rate over the elapsed interval rather than applying only
  its endpoint value for the whole tick; specify accuracy and test different
  timestep partitions, interruptions, and a tick crossing transition completion.
- [x] Keep programmed rate transitions on Animated and physical velocity/load
  integration on PhysicsBody, with distinct ownership and timing contracts.
- [x] Retain growth, stretching, and resizing in Animated, including continuous
  rates and eased changes. Specify their easing/rate-control overloads and verify
  that they remain available to Layers and objects with no physics body.
- [x] Replace Animated friction controls with explicit programmed slowdown
  examples, including growth/stretching; preserve layering without allocating bodies.

## Direction for rotation over time

Agreed requirement: callers must be able to specify direction whenever they
request rotation over time. This applies to Animated on Sprites, Parts and Layers,
as well as APIs that request an interpolated orientation in pose transitions,
recovery and controllers. Immediate orientation setters need no travel direction.
All durations remain floating-point seconds and angles/rates remain radians and
radians per second.

Animated.rotateTo and rotate now accept an integer direction after easing.
AsSpecified preserves raw absolute targets and signed relative full turns.
Shortest resolves half-turn ties positively; delayed routes resolve at start.
Rig recovery and body drives also expose direction selectors. General per-track
pose-transition overrides remain separate owned-evaluator work.

Implemented Animated/drive/recovery integer constants:

| Mode | Intended meaning |
| --- | --- |
| `rotationDirection_Shortest` | Choose the shorter route to an equivalent target orientation; specify the exact half-turn tie rule |
| `rotationDirection_Clockwise` | Reach the target through clockwise travel in the documented frame |
| `rotationDirection_CounterClockwise` | Reach the target through counterclockwise travel in the documented frame |
| `rotationDirection_AsSpecified` | Preserve signed, unwrapped angular travel or the raw numeric target; retain deliberate multiple turns |

An orientation of 10 degrees reached from 350 degrees can mean a 20-degree turn
or a 340-degree turn. A requested relative turn of two full revolutions must not
collapse to no movement. The default is AsSpecified to retain existing raw
numeric interpolation; Shortest is an explicit opt-in.

Resolve a target to an unwrapped angular path and ease along that path. Preserve
the current unwrapped state on interruption; choose the new path from that state.
Do not independently wrap/interpolate each frame. Define extra-turn requests and
equal-orientation behavior explicitly rather than treating clockwise selection
alone as a request for a complete revolution.

Signed relative angles and signed spin rates already encode direction. Preserve
their signed magnitude and deliberate turns by default. If an explicit direction
selector is also accepted, define sign conflicts instead of silently discarding
one input. A spin-rate transition can legitimately cross zero and reverse; its
easing describes the rate change, not a target-orientation shortest-path choice.

Direction is relative to the documented rotation frame. A reflected ancestor can
reverse the apparent on-screen direction; local and layer/world requests need
explicit semantics and tests. Fixed-direction travel also needs an easing policy:
backtracking/overshooting curves can reverse the instantaneous motion, so either
restrict those curves for strict direction or explicitly distinguish a chosen
angular route from guaranteed monotonic rotation.

Authored key direction is per track/segment. Import Spriter's directed rotation
and hold/no-rotation semantics instead of substituting shortest-angle blending.
Pose transitions/recovery need a direction policy with per-bone/Part overrides;
one global clockwise choice is not enough for independently animated elements.
An IK bend-side choice is distinct from rotation travel direction. Physics torque
and angular impulses remain signed physical inputs, with no target-path selector.

- [x] Implement integer rotation-direction selectors for programmed rotation,
  physical drive targets and rig recovery, including validation, unwrapped
  travel, full turns, delayed/interrupted changes and reflected-frame tests.
  See [Animated](../../src/inc/pdg/sys/animated.h),
  [PhysicsBody tests](../../test/cxx/test-physicsbody.cpp), and
  [rig control tests](../../test/cxx/animation-physics-control-tests.inc).
- [ ] Define/import authored per-track rotation routes in the PDG-owned clip
  evaluator and verify track/transition parity. Current `AnimationPose::blend`
  uses shortest-angle blending; a general per-bone transition-route override is
  not supplied by the implemented Animated/drive direction selectors.

The owned-evaluator item belongs to
[checkpoint 6](#pdg-owned-animation-assets-and-playback), not unfinished rig recovery.

## Transform, binding, and ownership contracts to specify

The original transform/binding/ownership inventory is implemented for the
current Part API and consolidated into checkpoints 1, 3, 4 and 5:

- [x] Safe `boneId_None`/binding queries, independent Part IDs/local transforms,
  per-instance animation state and retained-handle lifecycle rules.
- [x] Sprite-, bone- and Part-relative frames, explicit world queries, authored
  binding/socket selection, binding mutation and final-pose publication.
- [x] Programmed transform/appearance separation, scale/pivot/reflection policy,
  imported artwork, Part content, mounts, physical authority and snapshots.

See [Part declarations](../../src/inc/pdg/sys/part.h),
[Part implementation](../../src/sys/sprite.cpp), and
[native owner regressions](../../test/cxx/test-physics-owners.cpp). The future
owned clip/track format remains in checkpoint 6; it is not needed to establish
these implemented Part signatures.

## Physics extraction status and migration

Property/solver API update: Sprite and Part expose `.physics` directly. C++ uses
a small forwarding reference backed by one private pointer, not an inactive body per
owner; `PhysicsBody::NoPhysics` is one shared immutable-in-behavior object. Dot
method calls, reference conversion and identity comparison are supported. Public
assignment is disabled; only setupPhysicsBody()/removePhysicsBody() change the
association. JavaScript compares
against `pdg.PhysicsBody.NoPhysics` (the existing `pdg.NoPhysics` alias is retained).
Removing a body restores the shared NoPhysics reference. Retained body references
remain detached and usable; they cannot be assigned to a different owner.
Solver selection uses `PhysicsSolver`, `physicsSolver_*`, `getSolver()`,
and the internal `Solver`/attachSolver()/detachSolver() interface.

The extraction is implemented in native code and V8/JSC. Remaining work is
tracked separately from the completed separation:

- [x] Animated contains no mass, physical velocity/speed/acceleration, forces,
  torque, or friction state. Movement/spin and growth/stretching remain programmed.
- [x] Sprite/Part body creation is explicit and idempotent. Reading `.physics`
  never allocates. Removing an owner/body leaves retained body references safe,
  detached, and manually step-able; NoPhysics is shared and immutable.
- [x] Body creation stops position/orientation programming. Dynamic bodies reject
  moveTo/rotateTo and movement/spin rates; immediate setters teleport. Size changes
  do not change configured inertia; callers set it explicitly on PhysicsBody.
- [x] Unbound Parts can have a basic body. Body positions, velocities and applied
  loads use owning-layer/world coordinates; publication converts to the Part frame.
- [x] Sprite bodies use Chipmunk on enabled layers, basic integration otherwise.
  Layer entry attaches an existing body; layer removal preserves it as basic.
  Physical velocities are never stored in Animated's programmed rate fields.
  Physical collision response requires explicit bodies; collision detection alone
  does not instantiate them. setupAnimationPhysics() explicitly creates its
  Sprite root body only after rig validation succeeds.
- [x] Finite forces/torques, delay boundaries, impulse units, damping, retained
  lifetime, physical serialization and no-double-integration have focused tests.
- [x] Integrate Part colliders/constraints into both shared worlds and expose
  mapped rig bodies through named Parts. Remove indexed Sprite body APIs.
- [x] Implement Basic contact/constraint approximations and Static/Kinematic/
  Dynamic authority, with bounded drives and documented solver limitations.
- [x] Complete browser owner/body bindings, JSC/iOS simulator runtime acceptance,
  and native headless/feature-disabled contracts. See
  [current validation](PHYSICS_RIG_VALIDATION.md); broader OS acceptance remains
  explicitly listed in the current summary.

Current-format physics snapshots and independent acceptance (2026-09-21):

- Physics snapshots support the current versioned PhysicsBody record.
  This format is independent of animation-timing serialization compatibility.
- [x] Serialize the complete current PhysicsBody for either ser_Forces or
  ser_Physics, including explicit inertia, mode, motion, and pending loads.
- [x] Restore current snapshots into fresh/existing bodies, restore shared
  NoPhysics associations, and retain programmed movement when no body is present.
- [x] Apply position-only snapshots to the active body so the next basic or
  Chipmunk step continues from the received position and rotation, including pivot.
- [x] Move Sprite/Part body lifecycle and snapshot tests into the independent
  pdg-physics-owners target, available when USE_SPRITER is off.
- Acceptance for this follow-up: five native suites pass with Spriter/Chipmunk;
  three native suites pass with GUI, Spriter, and Chipmunk disabled, now including
  Sprite/Part ownership and snapshots. The focused PhysicsBody JavaScript suite
  passes 7 tests / 110 assertions.
- Remaining snapshot acceptance includes broader serialization flag combinations,
  kinematic programmed-drive policies, and malformed-input/transaction coverage.
  Older physics records are outside this checklist.

Validation for this extraction (2026-09-21):

- Native GUI build and four focused CTest targets pass: animated contract,
  PhysicsBody, Spriter playback/owner physics, and animation pose.
- Seven focused JavaScript suites pass: animated, animated_programming, part,
  physicsbody, sprite, spritelayer, and animation_pose (103 tests, 1,095 assertions
  after the final read-only association correction). Native compile-time checks
  reject property assignment; runtime tests cover singleton identity, factory/removal
  transitions, retained bodies, and read-only JavaScript access.
- Headless library builds with both Spriter and Chipmunk disabled; the Animated
  and PhysicsBody contract targets pass in that configuration.
- JSC and Emscripten syntax checks pass; iOS project syntax validates. These are
  compile/project checks, not runtime acceptance on those platforms.
- Regenerated C++/JavaScript docs include PhysicsBody under Physics and remove
  the former Animated physics methods. Doxygen retains 77 existing warnings.
- Demo/API audit: visual aim and repeated playback checks pass, including IK,
  transitions and repeated Attack/Crumble. All six animation microbenchmark cases
  run (2,000 iterations each); C++ Bunnymark/PDGMark build, and the older C++
  visual demo passes syntax checking after updating its public drawing calls.
  This does not establish cross-platform performance baselines or full graphical
  benchmark completion.
- The earlier non-MVC checkpoint is commit `e3f854183`. MVC work remains outside
  that commit and untouched by the physics extraction.

Migration examples:

```javascript
// Programmed motion has no body or physical damping.
layer.setMovement(30, 0);
layer.changeMovementTo(0, 0, 0.5, pdg.easeOutQuad);

// Physical motion has explicit body ownership and seconds-based loads.
const body = sprite.setupPhysicsBody(2, 4); // mass, moment of inertia
sprite.physics.applyImpulse(new pdg.Vector(4, 0));
const forceId = body.applyForce(new pdg.Vector(8, 0), 0.25);
body.applyAngularImpulse(2);
body.applyTorque(8, 0.25);
body.setLinearDamping(0.7); // per second; independent of contact friction
```

Use explicit impulse calls for instantaneous physical changes. Physical
velocity uses `.physics`; programmed movement uses setMovement/getMovement.
Zero-duration force/torque contributes nothing.
`wait()` only schedules programmed animation; physical load delay is an explicit
seconds argument. Basic free motion integrates analytically; Chipmunk uses its
normal position/contact solve with interval-integrated load changes to velocity.

## PhysicsBody contract and implementations

Implemented entry points are summarized below. Sprite/Part factories retain one
body per owner; removing the association leaves retained body references safe.
Application points and loads currently use owning-layer/world coordinates;
additional coordinate-space selectors remain a possible extension:

```text
Sprite.physics / Part.physics -> PhysicsBody or shared NoPhysics (never null)
sprite.physics == PhysicsBody::NoPhysics -> no body instantiated (C++)
PhysicsBody.getVelocity() / setVelocity(Vector velocity)
PhysicsBody.getSpeed()
PhysicsBody.getAngularVelocity() / setAngularVelocity(double radiansPerSecond)
PhysicsBody.getAngularMomentum()
PhysicsBody.applyImpulse(Vector impulse)
PhysicsBody.applyImpulse(Vector impulse, Point worldPoint)
PhysicsBody.applyForce(Vector force, double durationSeconds)
PhysicsBody.applyAngularImpulse(double angularImpulse)
PhysicsBody.applyTorque(double torque, double durationSeconds)
```

Only Sprite and Part expose body ownership. Reading `.physics` must not create a
body. The shared NoPhysics default represents absence; an instantiated
basic body still performs physics when Chipmunk is unavailable. Basic and
Chipmunk implementations share the same public PhysicsBody interface. Chipmunk
must not also run the basic integrator or maintain competing motion state.

| Operation/state | Meaning for a dynamic body |
| --- | --- |
| Linear impulse `J` | Immediate momentum change; change in velocity is `J / mass`; no duration |
| Constant force `F` for `t` seconds | Momentum change `F * t`, integrated over the active interval |
| Angular impulse `K` | Immediate angular-momentum change; change in angular velocity is `K / inertia`; no duration |
| Constant torque `T` for `t` seconds | Angular-momentum change `T * t`, integrated over the active interval |
| Angular momentum | For the current 2D rigid body, `inertia * angularVelocity`; it is distinct from Animated spin |
| Off-center impulse/force | Also contributes angular impulse/torque through its lever arm about the center of mass |

These describe each operation's contribution; contacts, constraints, damping, and
other simultaneous forces can also change the resulting motion. Static/kinematic
body handling needs an explicit contract instead of applying dynamic-body formulas.

The original extraction checklist is implemented and consolidated into
[checkpoint 4/5](#active-follow-up-checkpoints--2026-09-21),
[shared colliders/constraints](#shared-colliders-and-body-constraints--approved-2026-09-22),
and the [rig plan](ANIMATION_PHYSICS_RIG_PLAN.md):

- [x] Seconds-based finite/delayed/continuous force and torque, cancellation,
  distinct linear/angular impulses, inertia, world application points and damping.
- [x] Common optional Sprite/Part PhysicsBodies, unbound physical Parts, shared
  contacts/joints, identifiable Part contact payloads and one integration path.
- [x] Consistent Basic/Chipmunk lifecycle and public operations, with documented
  approximation limits; layers and Animated remain free of PhysicsBody ownership.
- [x] Explicit physical authority, validated binding/body changes, unambiguous
  mapped-bone ownership, named Part control and safe retained references.
- [x] Shared active graph/rig snapshots, handoff, recovery and assembly queries.

[Body tests](../../test/cxx/test-physicsbody.cpp),
[owner tests](../../test/cxx/test-physics-owners.cpp), and
[handoff/IK tests](RIG_COVERAGE_AUDIT.md) replace the duplicated acceptance list.
Animation physics requires Chipmunk; this does not commit Basic to complex rigs.
Arbitrary live physical resizing and a momentum-conserving single-body merge
remain separate capabilities outside the completed rig scope.

## `.physics` and shared NoPhysics behavior

The null-object contract and focused native/V8/Wasm/JSC acceptance are implemented,
including explicit release/debug diagnostic checks.
A Sprite or Part always exposes `.physics`. With no body instantiated it returns
`pdg.PhysicsBody.NoPhysics`, a single public instance within a scripting runtime, implementing
the PhysicsBody interface. Layers and Animated do not expose this property.

| Property value | Meaning |
| --- | --- |
| `NoPhysics` | No body is instantiated; valid physics commands do nothing |
| Basic PhysicsBody | An instantiated body simulated with PDG calculations |
| Chipmunk PhysicsBody | An instantiated body simulated by Chipmunk |

Current behavior:

- Debug builds log a warning/error for ignored mutating calls, without throwing
  or asserting because a body is absent. Release builds quietly ignore them.
  Rate-limit diagnostics by method/call site so an update loop cannot flood logs.
- Make the singleton immutable and free of per-owner state. Calls must not store
  force, mass, velocity, callbacks, or queued operations, and must not influence
  other objects sharing NoPhysics. Ignored calls are never replayed on creation.
- Return the shared singleton from fluent no-op setters. Give queries explicit,
  safe defaults: presence is false and velocity is a fresh zero Vector; reads
  should not generate missing-setup warnings. Specify every return type/default,
  including mass, inertia, state snapshots, and joint handles. Do not return
  mutable shared vectors or imply that absent physical state is a simulated body.
- The `.physics` association is read-only in C++ and JavaScript. Use
  setupPhysicsBody()/removePhysicsBody() to change it. Callers can operate on the
  body through the property, but cannot replace it or transfer it to another owner.
- Use an identity check against `pdg.PhysicsBody.NoPhysics`
  for callers that require actual physical participation. Safe calls prevent a
  missing-body exception; they cannot guarantee that an intended effect occurred.
- A global singleton cannot reliably identify the originating Sprite/Part from
  a method call. Log method/call site. Owner-specific diagnostics would require
  an owner-aware proxy; never store a global mutable "last accessed owner".
- A cached reference to NoPhysics stays NoPhysics after the owner gains a body.
  Callers should read `.physics` when using the current association. If automatic
  retargeting of cached handles is desired, choose a stable per-owner proxy
  explicitly; that is a different identity/lifetime contract from a singleton.
- Missing-body safety applies to valid PhysicsBody calls. It does not suppress
  unrelated errors in actual bodies, invalid arguments, or invalid object
  references. Disposed-body and owner-removal behavior require their own defined
  lifetime rules; detaching must never leave a dangling native pointer.

- [x] Finalize the singleton versus per-owner proxy choice, property access,
  creation/removal APIs, and native/script identity and lifetime behavior.
- [x] Specify no-op return values for every PhysicsBody method and fresh value
  results for mutable types; separate absent state from basic simulation.
- [x] Implement debug diagnostics and release no-ops with no per-owner physics
  state or deferred command replay in NoPhysics.
- [x] Test absent/present transitions, ignored linear/angular operations, query
  defaults, fluent returns, two owners sharing the singleton, debug log throttling,
  release silence, cached handles, and destruction under the selected contract.
  Native/V8/Wasm/JSC tests cover association transitions, immutable shared state,
  fresh queries, fluent returns and retained handles. V8 forced-GC covers wrapper
  collection and owner destruction. Separate native debug/release tests verify
  query silence, method-level diagnostic throttling and no deferred loads after
  10,000 calls. Run with `ctest -R pdg-nophysics` after building the matching
  `pdg-nophysics-debug-tests` and `pdg-nophysics-release-tests` targets.

## Related Animated cleanup candidates

- [x] Keep easing/helpers and programmed transforms in Animated; keep artwork,
  Parts, clips, modifiers, IK and physical state on their owning APIs.
- [x] Implement tween pause/resume/cancel/status separately from clip/physics
  clocks, and migrate animation/helper/easing/force timing to seconds.
- [x] Remove physical operations from Animated and layers; document programmed
  slowdown and explicit versioned timing/scale/Part/physics snapshot boundaries.

## Integration and verification work

Completed integration checks are consolidated into checkpoints 1/3/4/5 and
[physics validation](PHYSICS_RIG_VALIDATION.md): matching native/script APIs,
bindings/source registration, fractional programming, Part lifecycle and frames,
Basic/Chipmunk contracts, authority, retained references, snapshots, references
and Topics. API-stability notes are applied in both languages; see
[the approved review](API_STABILITY_REVIEW.md).

Still open: PDG-owned immutable clip data/evaluation and the platform/manual gates
in the current summary. MVC implementation and scrolling-view acceptance are complete.
Do not repeat those as independent tasks for every old design inventory.

## Current implementation references

- [Spriter pose evaluation, sampling and publication adapter](../../src/sys/spriter/pdg_spriter_pose.cpp)
- [Spriter resource and document factory](../../src/sys/spriter/pdg_file_factory.cpp)
- [Animated public surface](../../src/inc/pdg/sys/animated.h)
- [Sprite public surface](../../src/inc/pdg/sys/sprite.h)
- [Bone, binding, and pose definitions](../../src/inc/pdg/sys/animationpose.h)
- [Physics definitions](../../src/inc/pdg/sys/animationphysics.h)
- [Physical-rig validation and impulse handling](../../src/sys/animationphysics.cpp)
- [Base motion integration](../../src/sys/animated.cpp)
- [Sprite scale, playback, and physics overrides](../../src/sys/sprite.cpp)


## Typed fluent animation interfaces

- [x] Keep animation state, serialization, scheduling and virtual behavior in
  non-template `AnimatedBase`; generic native callbacks use `AnimatedBase*`.
- [x] Add `Animated<T>` for setters, scheduled changes, helpers and schedule controls
  returning `T&`; Sprite, Part and SpriteLayer select their concrete owner types.
- [x] Keep appearance implementation in `AnimatedAttributesBase` and provide
  `AnimatedAttributes<T>` for typed appearance and inherited Attributes setters.
- [x] Use `AnimatedAttributes<>` for a standalone style and
  `AnimatedAttributes<View>` for View. Custom owners can choose their own T.
- [x] Preserve JavaScript class names, subclass identity, return-this behavior and
  helper callback identity across V8, JavaScriptCore and browser bindings.
- [x] Verify shared scheduling, derived virtual hooks and mixed fluent chains.

The template parameter is the selected owner, not a runtime most-derived type.
Button and other View subclasses inherit `View&`; TileLayer inherits `SpriteLayer&`.
Their additional methods remain available through the original variable. Extending
those hierarchies with further template parameters is a separate API decision.
Custom C++ owners that want assignment from Attributes should add
`using AnimatedAttributes<Owner>::operator=;` because C++ implicitly declares an
assignment operator in every derived class. Other fluent methods need no wrappers.

JavaScript consumers continue constructing `pdg.Animated()` and
`pdg.AnimatedAttributes()` and subclassing those ordinary JavaScript classes.
