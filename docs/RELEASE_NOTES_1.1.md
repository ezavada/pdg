# PDG v1.1 release notes

PDG 1.1 expands skeletal animation, articulated physics, scene snapshots and
rendering, and consolidates the cross-platform test workflow. It also reorganizes
the animation and physics APIs; existing applications should review the migration
guidance below.

Version: **1.1.0**. These notes compare the `ik` branch at `2ccb99f41` with
**v1.0.0 on `main`**, commit `ee2e18dfdd2fdfd3e3ac5f643efbab531ac52070`.
Validation scope is recorded below.

## Features

- **Editable skeletal animation and IK.** Inspect and modify poses, sample clips
  without disturbing playback, transition to a particular clip time, attach
  custom Drawing artwork, and solve hand/foot targets through the animation API.
- **Composable sprites and shared physics.** Sprite-owned Parts have independent
  transforms, artwork, colliders and optional PhysicsBodies. Shared constraints,
  Part-chain IK and bounded drives support articulated objects and attachments.
- **Physical animation rigs.** Generate a dynamic capsule rig from an animation
  skeleton or author one explicitly. Switch whole rigs, bones or subtrees between
  Kinematic, Dynamic and Driven control, with handoff, recovery, membership changes
  and live reflection.
- **Scene and resource snapshots.** Save and restore supported Sprite/Layer
  graphs, shared artwork, imported animation assets, Parts, constraints and active
  rig state using embedded resources or external references.
- **Particles and emitters.** Create lightweight effects with captured templates,
  bursts, continuous emission, lifetimes, optional physics and attached emitters.
- **Animated graphics and UI.** AnimatedAttributes adds transform and appearance
  animation to Drawing elements and MVC views. Offscreen ports provide persistent
  RGBA surfaces with snapshot or live images. Clipping, themed controls and
  transformed input handling are expanded across native and script interfaces.
- **Updated runtime and development workflow.** Node.js advances to v24.21.0;
  native code adopts more standard C++ facilities. Unified test commands cover
  unit, visual, demo, rig, tooling and performance suites, with reproducible
  benchmark reports and pinned comparison baselines.

## Compatibility and migration

**This release contains breaking C++ and JavaScript API changes.** Applications
using animation, Sprite physics, collision shortcuts or saved physics state
should review these changes before upgrading.

| v1.0 usage | v1.1 usage or behavior |
| --- | --- |
| Integer-millisecond animation durations, stepping and helper/easing callbacks | Floating-point **seconds**, including inherited fades and layer zoom. For example, an animation duration of `1000` becomes `1.0`. TimerManager and internal scheduler timestamps retain their documented millisecond units; do not convert unrelated APIs blindly. |
| `move`, `rotate` and `resize` for relative Animated changes | `moveBy`, `rotateBy` and `resizeBy`. Absolute operations retain the corresponding `...To` names. |
| Programmed motion through velocity/speed/acceleration methods | `setMovement` / `getMovement`, `changeMovementTo` / `changeMovementBy`, and `stopMovement`. Physical velocity belongs to PhysicsBody. |
| `startGrowing` / `startStretching` | `setGrowing` / `setStretching`; explicit change methods animate the rates over seconds. |
| Sprite-specific `setEntityScale` | The shared floating-point `setScale` and scale-animation APIs. |
| Physical mass, velocity, friction, force and torque on Animated/Sprite | Explicit `setupPhysicsBody()` and the owner’s `.physics` association. Layers and plain Animated objects do not own physical bodies. |
| An instantaneous `applyForce` or `applyTorque` selected by a duration constant | `applyImpulse` or `applyAngularImpulse`. Finite force/torque calls take explicit seconds; zero duration contributes no impulse. |
| Sprite collision-mode/radius/mask helpers and `ISpriteCollideHelper` | Shared Collider geometry, filters and queries through `.collider`; `setupFrameCollider` and `setupAnimationCollider` provide artwork adapters. |
| Sprite joint/static/elasticity shortcuts | PhysicsBody modes, material properties and PhysicsConstraint operations. |
| Assuming a `.physics` or `.collider` read creates a component | Absent associations return shared `NoPhysics` / `NoCollider` objects. Call the owner’s setup method to allocate a component. |
| Existing serialized physics layouts | The current versioned PhysicsBody/scene records. Older physics records are not supported; animation-timing compatibility is handled separately. |
| C++ subclasses or helpers written against the old Animated type | The `AnimatedBase` / `Animated<T>` hierarchy and typed fluent return values. Animation helpers receive an `AnimatedBase*` and elapsed seconds. |
| Custom Mutex/CriticalSection/scoped locking wrappers | Standard `std::mutex`, `std::lock_guard` and `std::unique_lock`. |

Additional migration details:

- Immediate animation setters and timed change methods have distinct contracts.
  Timed changes require an explicit duration; the old `duration_Instantaneous`
  and `duration_Constant` constants are not exported.
- Dynamic PhysicsBodies own physical position/orientation and reject competing
  programmed movement/spin. Immediate transform setters can teleport a body;
  use forces, impulses or drives for simulated motion.
- C++ applications need a C++20 compiler **and standard library**, including
  `std::format`. The main branch already selected C++20 in CMake; v1.1 expands
  the implementation’s use of those facilities. The iOS deployment target rises
  from **15.0 to 16.3**.
- Rebuild the PDG Node addon against the selected Node runtime after updating the
  Node dependency. Source builds support Python **3.9–3.14**.

See the [Animated reference](cxx/dox/animated-api.dox),
[PhysicsBody reference](javascript/dox/physicsbody-methods.dox),
[Collider reference](javascript/dox/collider-methods.dox), and
[snapshot reference](cxx/dox/sprite-serialization.dox) for exact contracts.

## Detailed changes

### Animation programming and timing

- Separate programmed transform animation from physical integration. Animated
  retains movement, spin, size, scale, pivots, easing and scheduling; PhysicsBody
  owns physical motion and loads.
- Convert public animation durations, manual stepping, animation-helper callbacks
  and easing inputs to fractional seconds. Convert scheduler/evaluator units at
  explicit internal boundaries and version serialized timing records.
- Add floating-point scale independent of logical size, with timed scale changes.
- Add continuous movement, spin, growth and stretch rates and eased rate changes.
  Integrate rates across intervals, including delayed starts, interruptions and
  updates that cross completion boundaries.
- Add explicit rotation direction: as specified, shortest path, clockwise or
  counterclockwise. Preserve signed full turns and define half-turn ties.
- Complete `andThen()` / `wait()` scheduling and typed fluent chaining. Add
  schedule pause, resume, cancellation and status without conflating tween state
  with clip playback, constant rates or physics.
- Fix animation-helper lifetime and garbage-collection behavior, including
  callbacks retained by native owners and teardown after their owners disappear.

### Skeletal poses, playback and IK

- Add AnimationRig and AnimationPose representations with validated hierarchy,
  owned snapshots, stable bone/binding queries and local/rig/world transforms.
- Add an opt-in SCML pose adapter for fixed-hierarchy assets. Bone edits propagate
  to descendant bones, image bindings, sockets, attachments and collision geometry.
- Add silent `sampleAnimationPose`, atomic `seekAnimation`, and
  `transitionToAnimation` with independently timed source and destination clips.
  Preserve continuity when transitions are interrupted.
- Add ordered procedural modifiers with synchronous borrowed pose views,
  explicit source modes, error reporting, rollback and failed-modifier disabling.
- Add two-bone animation IK with explicit lengths, limits, bend side, influence,
  coordinate spaces and reach diagnostics, including reflected poses.
- Add spring and contact target adapters for recoil, hand targets and foot locks
  on moving supports. Expose sampled variables and tags with their authored types.
- Add retained Drawing attachments and Drawing-producing callbacks, with slot
  ordering, bounds, shared artwork, removal and callback-lifetime handling.
- Deliver authored SCML eventline triggers with copied names, clip-relative
  `timeSeconds`, update-relative `offsetSeconds`, and defined ordering across
  loops, transitions and entity changes. Sampling and seeking remain silent.
- Add per-Sprite bone/socket/box debug drawing and graphics-capability checks;
  correct debug transforms and destination-port routing.
- Correct phase-aligned blend duration/progress, paused behavior, selection and
  natural completion. Fix attachment reference cleanup and translated, rotated,
  scaled and reflected socket/box geometry.
- Preserve ordinary playback for unsupported editable-pose topologies, including
  Wonky’s changing-hierarchy Crumble clip. Repeated nonlooping playback has
  deterministic restart/progress/completion regression coverage.

### Parts, artwork and attachment composition

- Add Sprite-owned Parts with stable IDs/names, independent local transforms,
  parent relationships, optional bone/artwork/socket bindings and world queries.
- Support Image and shared Drawing content on Parts, independently of whether
  they have a PhysicsBody or Collider.
- Add rigid mounted Sprites that retain their own Parts and animation playback.
  Preserve mount groups across layer transfer and publish kinematic targets before
  the shared physics solve.
- Add direct and scheduled Part-chain IK, joint limits, persistent controller
  state and force/torque-limited physical target tracking.
- Add explicit ownership and release rules between Part IK, animation control
  and manual drives. Reject conflicting takeovers before partially changing a chain.
- Add cross-Sprite Part transfers with retained component identity and explicit
  destination-rig attachment. Retained handles remain safe after detachment or
  owner removal.

### Physics bodies, colliders and constraints

- Introduce common PhysicsBody, Collider and PhysicsConstraint APIs for Sprite
  and Part components, with shared null-object associations and explicit setup/removal.
- Support Basic and Chipmunk solvers through the same body/constraint surface,
  with documented approximation and capability differences.
- Separate linear/angular impulses from finite, delayed and continuous loads.
  Add force handles, cancellation, inertia, angular momentum and damping semantics.
- Add bounded drives with target position, rotation and velocity, rotation-route
  selection, force/torque caps and explicit manual handoff.
- Add shared circle, box, capsule, simple concave polygon and image-mask collider
  geometry, compound shapes, sensors, filtering, material overrides and queries.
- Add Sprite/Part artwork colliders from frames, Drawing bounds and named authored
  animation boxes; preserve source-shape identities and explicit added geometry.
- Consolidate contacts and response through shared components. Correct solved-step
  impulse/force reporting, fallback response, coincident-center handling and
  contact/lifetime behavior during callbacks and removal.
- Expose shared joints, springs, limits, motors and other constraints with editable
  anchors and settings. Retained disconnected constraints remain queryable.
- Add angular-speed break thresholds and events identifying the body, Part,
  measured speed, threshold and optional relative reference.
- Expand coverage for Basic/Chipmunk contacts, spinning-box collisions, stacks,
  chains, drives and snapshot continuation; add a solver comparison report/viewer.

### Generated and authored physical rigs

- Generate capsule bodies and skeleton-connected pivot joints with
  `setupPhysicsFromAnimationRig`, length-weighted mass distribution, root selection
  and zero-length-bone handling. Physics setup is explicit; loading artwork alone
  does not create a physical rig.
- Put explicitly authored and generated animation rigs on the same editable
  Part/body/collider/constraint graph.
- Add whole-rig, bone and subtree Kinematic, Dynamic and Driven control, including
  IK-fed drives, explicit release, recovery and completion notifications.
- Coordinate desired-target sampling with articulated physics substeps, then
  publish final physical poses without duplicate playback advancement.
- Support Fixed/Follow frame policies, moving supports and gameplay root targets.
- Support attaching/detaching rig Parts, accessory loads, cross-Sprite transfers,
  aggregate mass/inertia queries and root-directed impulses.
- Scale component mass/inertia proportionally for whole-assembly mass edits;
  component edits and membership changes update assembly totals.
- Add live physical reflection with body, collider, anchor, limit and frame
  handling. External angular constraints require the documented release policy.
- Preserve active modes, membership, loads, drives, desired poses and interrupted
  recovery through graph snapshots.

### Serialization and resources

- Add complete embedded-resource and external-reference serialization modes.
  Complete imported-animation saves can restore their supported assets without
  the original source files; external mode validates required resources.
- Preserve Image pixels or named sources, strips, frames/subsections, opacity,
  edge clamping and shared source images. Runtime-modified images retain embedded pixels.
- Preserve Sprite frame artwork and playback, independent Parts, mounted Sprites,
  Drawing graphs, body/constraint relationships and supported animation controllers.
- Restore Layer graphs through staged validation before adoption. Preserve shared
  identity and reject invalid references, incompatible topology and truncated data.
- Support incremental Part transform updates against matching identities;
  topology, artwork and physics-controller changes require the appropriate full state.
- Retain imported animation models independently of their source Layers and
  restore clips, character maps, overrides, transitions and built-in IK state.
- Compact default/boolean fields and visual coordinates/colors; deduplicate shared
  assets and losslessly compress embedded XML when beneficial. Visual color
  quantization is eight-bit and compact coordinates can discard less than 0.001
  per encoded component; physics state and relevant transform inputs retain their
  documented floating-point precision.
- Harden object-length decoding, bounds/truncation checks, shared-resource size
  accounting and serialization buffer ownership.

### Particles

- Add Particle and ParticleEmitter interfaces in C++ and JavaScript, with
  whole-particle artwork, programmed animation and optional physics/collision.
- Capture templates for burst or continuous emission, including supported
  settings and remaining scheduled animation.
- Support attached emitters for trails, fractional emission accumulation, lifetimes
  and per-layer budgets. Emitted particles become independent layer members.
- Keep particles and emitters transient: Layer snapshots omit them, and initial
  scene restoration clears live effects. Applications recreate effects from their
  own configuration after loading.

### Rendering and offscreen graphics

- Add graphics-backed offscreen ports without a main window, persistent RGBA
  pixels, explicit clearing and configurable drawing origins.
- Add copied snapshot images and live shared-surface images from offscreen ports,
  with image lifetime preserved across port/context closure.
- Implement a single Port clip rectangle and reset operation, plus consistent
  `clipOverflow` behavior across drawing operations.
- Add live Attributes/AnimatedAttributes associations on Drawing elements, stable
  element identity and explicit freezing/replacement. Snapshots capture values,
  not the live association or its animation schedule.
- Expand shared/nested Drawing replay, composed transforms, local/pixel strokes,
  opacity, blend modes, bounds, culling and image-state restoration.
- Correct polygon filling for concave and self-intersecting contours, and texture
  mapping under skew, rotation and reflection. Cache tessellation lazily until
  points change and reuse it across attribute transforms.
- Fix browser texture loading, tiling and transparency, textured cube mapping,
  stroke opacity/compositing edge cases and invalid texture handling.
- Fix portable PNG decoding to use transformed channels and row sizes, preventing
  corruption in transparent palette images such as CanvasMark ships.
- Add font cap-height metrics across graphics backends and bindings.

### MVC application framework

- Make visual Views inherit AnimatedAttributes in C++ and JavaScript, supporting
  animated transforms and appearance without physical-body ownership.
- Compose explicit appearance overrides with control state themes, images and
  custom drawing. Keep rendering and input transforms aligned under rotation,
  reflection, scaling and non-default pivots.
- Implement clipped scrolling, inverse hit testing and composite control layout.
- Improve buttons, dialogs, checkbox/radio indicators, borders, text placement and
  scrollbar rendering.
- Capture pointer presses on the original view, cancel activation on outside
  release, and reset pressed state on exit, removal or deactivation.
- Expand native, script and browser interaction coverage for controls, dialogs,
  scrolling, theming, transformed input and lifecycle behavior.

### Runtime, portability and build changes

- Update the Node submodule from **v24.3.0 to v24.21.0 LTS**, including the
  corresponding iOS JavaScriptCore native-source bundle.
- Link Node’s split `node_base` and dependency archives with required registration
  and rescan behavior. Include portable libpng configuration in fresh addon packages.
- Validate cached Node builds against the source/runtime version, avoid certifying
  failed builds, and build POSIX runtime/libraries together. Align Python selection
  and Windows tool refresh with the upgraded dependency.
- Use public Node shutdown/environment cleanup and release native singleton script
  handles at the correct isolate lifetime boundary. Cover worker teardown and
  embedded automatic-exit behavior.
- Initialize headless layer event flags so optimized snapshots cannot accidentally
  restore a layer as static. Fix nullable ownership in iOS physics-break events.
- Replace custom mutex wrappers with standard synchronization; implement the
  coalescing Semaphore wakeup with mutex/condition-variable primitives.
- Adopt `std::chrono::steady_clock`, `std::filesystem`, fixed-width integer types,
  `std::bit_cast`, `std::span`, owned containers, `std::source_location` and other
  standard-library facilities. Replace the custom Mersenne Twister with `std::mt19937`.
- Remove obsolete compiler/math/type workarounds; make `ms_time` and `ms_delta`
  explicitly 64-bit. Raise the iOS deployment target to 16.3.

### Tests, demos, benchmarks and documentation

- Add common `test/unit`, `test/ui` and `test/demo` selection across native,
  Node, browser and iOS runtimes, with POSIX, PowerShell and batch entry points.
- Discover configured native CTest suites through `cpp:` selections. Share
  browser/iOS spec catalogs and capability gates.
- Add interactive visual navigation, pause/resume, fresh per-page state and
  finite `--automated` runs with reports and meaningful failure exit codes.
- Add `test/rigs` with automatic per-rig discovery and nine isolated human-rig
  checks; add `test/tools` for harness, build-cache and performance-tooling checks.
- Consolidate process-lifetime, garbage-collection, module-loading and rendering
  regressions into maintained suites, and remove obsolete experiments/diagnostics.
- Provide 38 UI pages, including compositing, transform pivots and offscreen
  live/snapshot comparisons, and seven demos: Astra, particles, human rigs,
  wheel/chains, MVC controls, the Spriter showcase and live Layer serialization.
- Add automated browser checks of navigation, paused framebuffers, clock continuity
  and demo/MVC interaction; provide repeatable isolated Linux physics validation.
- Add `test/perf` for eight native benchmarks, browser rendering marks and supported
  Node workloads. QuickBunnyMark, QuickPDGMark and QuickCanvasMark use fixed loads,
  warm-up/measurement periods, raw frame statistics and synthetic scores.
- Uncap Quick rendering measurements without changing normal application pacing.
  Record calibration/provenance, pin native/browser baselines and report per-test
  and subsection comparisons. Fixed-work animation, collider and rig benchmarks
  retain throughput/step-time measurements rather than synthetic rendering scores.
- Expand and regenerate C++/JavaScript API references, topic/event coverage,
  stability labels and manual pages. Document current test workflows and remove
  obsolete test references and superseded engineering guidance.

## Validation and remaining limits

Recorded branch validation includes macOS native/embedded Node, the headless
Node addon, browser WebAssembly and the iOS simulator. The Node upgrade checkpoint
passed 16 native CTest suites and 1,388 embedded JavaScript unit tests, 1,251 Node unit tests,
1,368 browser tests and 1,366 simulator tests. Later targeted checks cover the
test migrations and all nine rig checks. These counts describe recorded runs,
not a promise that every build exposes the same tests.

Linux Ubuntu ARM64 validation includes headless native C++, embedded Node and
the addon. Windows scripts were checked, but Windows runtime acceptance and
Linux GUI validation remain outstanding. Simulator results do not establish
physical-device acceptance. See the [Node upgrade validation](note-ai/NODE_24_21_UPGRADE.md)
and [physics validation](note-ai/PHYSICS_RIG_VALIDATION.md) for configurations and limits.

- Imported physical animation rigs require **Chipmunk**; Basic remains available
  for shared simple bodies/constraints. Graphics-dependent APIs are unavailable
  in headless builds.
- Editable SCML poses require supported fixed hierarchy and track presence.
  Ordinary playback has a separate compatibility path for other assets.
- Arbitrary application callbacks and transient effects are not automatically
  serialized as executable state. Follow the resource and callback restrictions
  in the snapshot references.
- Motion matching, a PDG-owned replacement for Spriter clip evaluation, Synfig
  conversion, SCON/atlas loading and authored Spriter soundline playback remain
  future work; they are not v1.1 features.

Use the [test guide](../test/README.md), [rig guide](../test/rig_tests/README.md)
and [performance guide](../test/perf_tests/README.md) to reproduce the relevant checks.
