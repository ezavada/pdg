# Animation API extension implementation checklist

Reconciled: 2026-09-25. Design: [animation proposal](PDG_ANIMATION_API_EXTENSION_PROPOSAL.md).
Related: [Spriter integration status](ENHANCED_SPRITER_API_PROPOSAL.md).

`[x]` means implemented and verified for the stated scope. `[ ]` remains open, including partial work. Milestones are not complete merely because their first subtask is checked. Verification is recorded below; no untested platform parity is implied. All implementation is PDG-owned; leave the SpriterPlusPlus and Node submodules unchanged.

Follow-up API design: the [Animated / PhysicsBody / Part / Sprite change list](ANIMATED_PART_API_CHANGE_LIST.md) records Part inheritance, programmed movement/spin and growth/stretching, optional PhysicsBody ownership on Sprites/Parts, basic and Chipmunk implementations, and separate linear/angular impulse and force/torque APIs. Its current remaining-work summary is the active API backlog; completed follow-ups are reconciled here rather than counted twice.

The [Part relationship tasks](ANIMATED_PART_API_CHANGE_LIST.md#part-relationships-bones-ik-and-physical-constraints) track composable bone binding, IK, physical constraints and transform-control transitions. Independent Part-chain IK, physical IK drives, imported-rig generation and coordinated control are implemented. The [automatic animation physics rig plan](ANIMATION_PHYSICS_RIG_PLAN.md) records their tests and remaining platform/manual acceptance.

The follow-up list also tracks [owned assets and a PDG clip evaluator](ANIMATED_PART_API_CHANGE_LIST.md#pdg-owned-animation-assets-and-playback), [rotation direction](ANIMATED_PART_API_CHANGE_LIST.md#direction-for-rotation-over-time), and [Part/socket/attached-Sprite design](ANIMATED_PART_API_CHANGE_LIST.md#attachments-and-part-composition-discussion). Use the change list's current summary and dated acceptance entries for implementation status; dated verification logs below preserve the evidence available at each checkpoint. They are historical records, not additional open tasks. The rig plan now describes implemented runtime APIs and explicitly lists its remaining acceptance work.

## Planning and reusable existing work

- [x] Audit the enhancement proposal against implementation and bindings; distinguish complete, partial and missing behavior.
- [x] Update the animation proposal to reuse loading/model sharing, character maps, sockets, collision queries and EventEmitter.
- [x] Incorporate trigger delivery, sampled tags/variables, runtime debug controls, final-pose consumers and cache/lifetime contracts.
- [x] Separate sound, SCON, atlases, preloading and general nested entities from the animation foundation.
- [x] Apply the seconds-only public animation timing contract to sampling, seek, transitions and modifier context. Internal evaluator conversion remains private.
- [x] Use integer enum constants for coordinate spaces, snapshot binding kinds and metadata types; reject invalid script selectors without coercion. Future drawing placement and modifier stage use the same convention.

## Stage 0 — repair and specify existing behavior

### Floating-point seconds consistency

The migration is implemented. Scheduler/OS timestamps and explicitly retained
compatibility fields remain milliseconds; public animation durations, stepping,
helpers and easing use floating-point seconds. See the
[timing audit](ANIMATION_TIMING_API_AUDIT.md) and
[completed execution checklist](ANIMATED_PART_API_CHANGE_LIST.md#execution-checklist--2026-09-20).

- [x] Migrate Animated movement, rates, size, rotation, pivot, wait and inherited
  Sprite/layer fade/zoom durations to seconds, including public animate stepping.
- [x] Move force/torque timing to PhysicsBody, with interval integration,
  fractional durations, delays and explicit impulse APIs.
- [x] Migrate IAnimationHelper and built-in/custom easing callbacks to seconds
  through C++, V8, JSC and WebAssembly.
- [x] Define authored-trigger timeSeconds (clip-relative) and offsetSeconds
  (update-relative); retain frameTime and SpriteLayerInfo.millisec as explicitly
  millisecond compatibility/scheduler fields rather than silently changing units.
- [x] Update callers, bindings, examples and versioned snapshots together; test
  fractional timing and single conversion at the scheduler/evaluator boundary.

Evidence: [Animated contract tests](../../test/cxx/test-animated-contract.cpp),
[PhysicsBody tests](../../test/cxx/test-physicsbody.cpp),
[event fields](../../src/inc/pdg/sys/events.h), and the later checkpoint acceptance
in the API change list.

### Playback and transitions

- [x] Preserve the floating-point seconds argument; convert to evaluator milliseconds once.
- [x] Report normalized blend progress and complete once at the actual duration, including large steps and nonpositive durations.
- [x] Freeze blend time and visible pose while paused/stopped; resume without losing the blend.
- [x] Synchronize start/blend/pause/resume state for name and ID overloads; cancel obsolete completion events.
- [x] Validate animation names/IDs without mutating playback; reject nonfinite durations without side effects.
- [x] Cover nonlooping source completion during a longer blend, finished-state reporting and resuming a completed clip.
- [x] Cancel obsolete completion notifications when a new selection/transition replaces a blend; independent-time interruption continuity remains stage 4.
- [x] Document that clip selection retains per-clip time, stop pauses, and resume restarts a naturally finished clip; entity changes rebuild name lookup and release attachments.
- [x] Extend native regression coverage for retained clip times and same-entity selection; validate entity/clip combinations before mutating playback, including script regressions.
- [x] Test intermediate poses/progress, pause/resume, cancellation and invalid inputs in native and script paths; test real completion counts in scripts and independent instances natively.

### Coordinates, queries and lifetime

- [x] Define existing attachment query coordinates; keep world position and sprite-relative offset conversions explicit.
- [x] Apply root translation/rotation/scale/reflection once to socket and box queries in builds with/without Chipmunk; verify a physics body updates the evaluated root.
- [x] Make flip setters idempotent so repeated `setFlipX/Y` calls do not invert geometry again.
- [x] Follow attached children from evaluated position/angle without duplicate root translation.
- [x] Define/test rigid Part mounts for nonphysical/kinematic children, pre-solve target sweeps and competing-writer rejection. Dynamic holding uses shared constraints/drives. The legacy Sprite attachment facade retains its narrower transform policy; see checkpoint 3 in the API change list.
- [x] Derive box query/hit-test/broad-phase geometry consistently, including pivot, scale, reflection and active/inactive tracks.
- [x] Invalidate query bounds on root changes, clip/entity switches and paused reevaluation.
- [x] Release attachment references on replacement, detach, entity changes and parent destruction; reject null/self/cyclic attachments.
- [x] Verify meaningful translated, rotated, scaled/reflected fixtures; test missing/inactive names and instance isolation.
- [x] Restore post-draw helper behavior for Spriter sprites, including suppression by the pre-draw helper.
- [x] Validate reflected image quads, pivots, layer-to-port transforms, current port selection and shared-image opacity restoration, including draw failure, using a GUI-capable recording port.
- [x] Correct quad conversion, immediate layer rotation caches, and inverse point/rectangle conversion; verify round trips.
- [x] Exercise actual Spriter/custom artwork through native/browser showcase and framebuffer checks, alongside recording-port culling tests.
- [ ] Complete manual visual acceptance of real-character culling and scene-obstacle contacts; automated rendering is not visual approval. See the rig plan for Grey Guy/Wonky scope.
- [x] Document implemented SCML trigger dispatch separately from unimplemented authored sound playback; sound flags alone do not establish playback.
- [x] Audit collision impulse/force units and actual physics timestep in the [physics audit](ANIMATION_PHYSICS_UNIT_AUDIT.md); actual-step collision/joint force and fallback response corrections now have native tests. The subsequent PhysicsBody migration also resolves timed force/torque inconsistencies.

## Stage 1 — immutable rig and editable pose

- [x] Define PDG-owned bone/socket IDs, nonzero rig revisions, explicit reference transforms and optional authored lengths.
- [x] Define artwork binding IDs and typed sampled entity/object variables and tag sets with the SCML adapter.
- [x] Implement validated immutable fixed-hierarchy rig construction: unique names, valid parents, no cycles, finite transforms.
- [x] Implement independent local-pose storage, copy/snapshots, dirty descendant rebuilding and same-rig/revision blend checks.
- [x] Match Spriter translation/rotation/scale/reflection composition; compare two-level world transforms directly with Spriter across 36 root-transform cases.
- [x] Reject nonfinite local/batch edits atomically; permit singular forward transforms and compose nonuniform roots through the complete hierarchy.
- [x] Implement root/rig/world socket queries and shortest-angle local pose blending without modifying either input.
- [x] Build a PDG SCML adapter using the evaluator loader's document, with stable bone/image/point/box metadata, explicit reference-clip selection and unsupported-rig diagnostics.
- [ ] Add versioned sidecar reference/length configuration; do not infer IK lengths from display widths.
- [ ] Extend adapter support beyond fully active fixed spatial hierarchies only after defining topology/presence semantics.
- [x] Sample bones and bindings into a fresh base pose; rebuild descendants and write images/sockets/boxes from one final pose, including existing phase-aligned blends.
- [x] Provide standalone native rig/pose construction and owned snapshots in `pdg/sys/animationpose.h`, independent of GUI, physics, scripting and Spriter.
- [x] Expose Sprite rig/pose capability, diagnostics, names, local/rig/world queries, owned snapshots and persistent absolute local bone overrides.
- [x] Generate V8/JSC bindings from common sources; verify V8 Node/client and implement/test the equivalent WebAssembly facade. JSC/iOS simulator runtime acceptance is recorded in the API change list and physics validation record.
- [x] Expose typed entity/object tags and variables in snapshots, with declared defaults, absent-value/tag semantics, authored numeric interpolation and halfway discrete blend selection.
- [x] Add the fixed-hierarchy arm fixture with three rigid parts, a hand socket and a box; prove descendant propagation, independent snapshots/instances, and actual submitted image-quad rotation.
- [x] Route opt-in pose adapter state through the existing Sprite facade and its single playback clock; retain ordinary playback for unsupported rigs.
- [x] Introduce dedicated controller source/transition/modifier state through this same facade without creating a second live clock.
- [x] Scope rig IDs/revisions to source metadata and shared reference-rig identity; invalidate published geometry for entity/reference, override, root and opacity changes, including paused evaluation.
- [x] Add controller/modifier revisions and borrowed-view invalidation as those APIs land.

## Stage 1a — bone drawing and debug controls

- [x] Add registration handles, borrowed contexts, local bounds and before-all/after-all drawing.
- [x] Use shared pdg.Drawing artwork and Attributes with explicit registration stroke-width units (supersedes the initial primitive-command API).
- [x] Implement named-slot insertion/replacement and stable registration order; diagnose missing slots (changing/inactive spatial topology remains unsupported).
- [x] Apply final pose, sprite/layer/port transforms, reflection and inherited alpha once; restore drawing state.
- [x] Include custom bounds in visual culling and support an explicit uncullable fallback.
- [x] Release callbacks on removal/destruction/rig changes; defer in-callback edits and disable failing callbacks safely.
- [x] Expose per-instance integer bone/socket/box debug flags from the final pose; apply root/reflection/layer transforms and alpha once, with explicit port-pixel strokes.
- [x] Verify debug geometry, helper suppression/post-helper, instance isolation, invalid flags and global-state restoration on draw failure with a GUI recording port.
- [x] Expose/debug-test native, V8 and WebAssembly APIs with explicit GUI capability; headless setters accept zero and reject nonzero flags. JSC/iOS simulator runtime coverage is recorded in the later checkpoint acceptance.
- [ ] Add clip/blend state and constraint diagnostic overlays.
- [x] Provide native/JS parity; make headless capability explicit and suppress draw callbacks there.
- [x] Verify mixed Spriter/custom art, helpers, culling, ordering, cleanup, alpha and instance isolation with recording-port tests; verify image binding and actual custom-draw pixels in browser WebGL.

## Stage 2 — procedural evaluation

- [x] Add clip/reference/procedural sources and one per-sprite controller update/publish boundary.
- [x] Add ordered pre-constraint/constraint/post-constraint stages and synchronous borrowed-pose callbacks.
- [x] Resample a fresh base pose each update and apply persistent absolute overrides without drift.
- [x] Retain procedural integration state separately when modifier callbacks and sources are added.
- [x] Queue modifier registration/removal/source changes until the current evaluation ends; invalidate borrowed views after invocation.
- [ ] Queue rig replacement requested from callbacks. Current behavior rejects playback/entity/rig/layer changes inside a modifier with a diagnostic; successful external rig changes release callbacks.
- [x] Roll back a failing modifier's pose edits, report it and disable it; release native/script callback references.
- [x] Test no drift, stable order, pause/manual reevaluation, exception cleanup and native/headless/script parity.

## Stage 3 — two-bone IK

- [x] Validate ancestry, lengths, scales, handedness, limits and singular chains.
- [x] Implement analytic solve, bend preference, optional target orientation and explicit stretch policy.
- [x] Convert local/rig/world targets explicitly; reject unconverted cross-layer inputs.
- [x] Apply influence with shortest-angle local blending and rebuild descendants.
- [x] Report reach error, reachability, clamping and limit status.
- [x] Test reachable/unreachable/coincident/zero-length/reflected cases, zero influence and shared-chain ordering.
- [x] Reuse the drawing/socket/box fixture to prove every consumer follows the solved pose.

## Stage 4 — silent sampling, transitions and triggers

- [x] Implement independent `sampleAnimationPose(clip, timeSeconds)` without changing playback, tags, callbacks or events on the live sprite; verify fractional/negative/wrapped times, nonloop endpoint clamping and invalid input.
- [x] Implement atomic `seek` and independently timed `transitionTo`, preserving existing phase-aligned blending separately.
- [x] Define interruption, topology/discrete-value switches, pause, large-step and loop semantics.
- [x] Dispatch authored triggers through EventEmitter with stable payloads and lifetime-safe references.
- [x] Specify event ownership during crossfade and seek policy; deliver once over loop/multiple-loop boundaries.
- [x] Keep extra samples, debug queries and rendering silent; test seek/sample/crossfade/loop/event ordering.
- [x] Version authored/controller/IK and active-rig snapshot state in both resource modes. Built-in state resumes; unsupported arbitrary callback state rejects explicitly. See checkpoint 5 in the API change list.
- [ ] Validate queue-disabled trigger delivery (`PDG_NO_EVENT_QUEUE`), including destructive/reentrant native handlers. The recorded trigger acceptance uses the event queue.

## Stage 5 — physics target adapters

- [x] Establish tested impulse/force/time units and root-motion ownership.
- [x] Add recoil, contact-lock and spring/body target adapters over pose/IK APIs.
- [x] Retain contact locks in world or moving-platform-local coordinates; release/fade on lost support/liftoff/reach failure.
- [x] Drive contact windows from typed metadata; keep game-specific movement policy external.
- [x] Test moving-platform translation/rotation, changed support, metadata liftoff, fade and bounded-reach release.
- [ ] Exercise a complete contact controller across clip transitions with an explicit kinematic policy for ordinary attached children.

## Stage 6 — partial and passive physical rigs

The original passive-rig foundation is now integrated with the shared Part,
PhysicsBody, Collider and PhysicsConstraint graph. Private rig-only shapes and
joints are no longer a second runtime representation.

- [x] Preserve explicit definitions while exposing editable shared components.
- [x] Evaluate animation/IK targets before physics and publish solved poses afterward.
- [x] Support passive, partial and full rigs, safe lifecycle/contact dispatch,
  root ownership and recovery without overwriting the solved pose.
- [x] Cover unequal timesteps, contacts, joints, removal and final-pose authority.

The [rig plan](ANIMATION_PHYSICS_RIG_PLAN.md) owns current implementation and
acceptance detail; stage 8 below summarizes the completed active controls.

## Stage 7 — motion matching

- [ ] Compile versioned root-relative runtime-pose features, velocities, tags and contacts from silent samples.
- [ ] Declare in-place speeds/root trajectories, compatibility mapping and source/evaluator cache keys.
- [ ] Implement normalized weighted linear search, eligibility filters, stable ties, continuation scoring and hysteresis.
- [ ] Select from pre-IK state; transition through stage 4 and provide contacts separately to correction.
- [ ] Provide an optional reference controller and baseline comparison for continuity, foot sliding, memory and CPU.

## Stage 8 — active ragdoll

Implemented for Chipmunk, independently of stage 7 motion matching. The
[rig plan](ANIMATION_PHYSICS_RIG_PLAN.md),
[handoff/IK coverage audit](RIG_COVERAGE_AUDIT.md), and
[validation record](PHYSICS_RIG_VALIDATION.md) replace the duplicated design-task
inventory formerly here.

- [x] Generate Dynamic bodies/joints from reference skeleton/artwork geometry,
  select/override the root, apply its 1 mm fallback, and distribute mass by length.
- [x] Expose editable shared Parts, colliders and constraints; maintain aggregate
  mass/inertia, attach/detach membership and cross-Sprite Part transfers.
- [x] Implement whole-rig/bone/subtree Kinematic, Dynamic and Driven controls,
  parent-relative bounded drives, animation-plus-IK targets and explicit handoff.
- [x] Implement collision-aware recovery, completion-only events, interruption,
  root/frame policies, body overspeed notifications and live reflection.
- [x] Restore active rigs, component edits, desired poses, membership, ownership,
  drives and recovery through complete/external-resource snapshots.
- [x] Subdivide articulated physics updates with sampled targets, including fast
  chains and detached dynamic bodies; verify impacts, motor caps and solver stability.
  This uses the existing manager clock/catch-up policy, not a new global fixed clock.
- [x] Validate native, headless Node, desktop V8, browser and iOS/JSC simulator
  contracts; verify Basic's explicit unsupported-rig diagnostics and benchmark rigs.
- [ ] Complete Windows runtime and Linux GUI/JavaScript acceptance, plus manual
  real-character visual/contact checks. Linux native Docker tests already pass.

Animation physics permanently requires Chipmunk. Basic remains available for
simple shared bodies/constraints; it is not a future animation-rig solver.

## Offline assets and release gates

- [ ] After stage 1 schema stabilizes, implement the separate rigid Synfig-to-SCML/PNG/manifest conversion plan.
- [ ] Report omitted morphing/skew/constraints explicitly and test destination-runtime poses.
- [x] Register native pose sources in CMake, Node packaging, web build and iOS (core in all three source lists; SCML adapter in the synchronized Spriter source group); validate Xcode project syntax.
- [x] Regenerate affected V8/JSC interfaces from common inputs and add source `.dox` documentation for the implemented Sprite pose API.
- [x] Regenerate implemented C++/JavaScript references and bindings; verify Topics, class/event navigation and approved API-stability notes.
- [ ] Refresh published documentation/editor artifacts for the eventual broader release; this is a release gate, not missing references for implemented APIs.
- [x] Run relevant native, headless Node and GUI-capable V8 client regressions for this slice; record unavailable display/JSC/mobile/platform checks below.
- [x] Add/run a reproducible Node API-cost benchmark for snapshots, sampling, seek/publication, script callbacks, IK and transition selection.
- [x] Benchmark rig setup, steady physics, control switching and reflection at 1/10/50/100 rigs; see [rig results](../../test/perf_tests/cpp-rig/RESULTS.md).
- [ ] Benchmark sustained transition allocation/memory and future matcher search; establish application frame-budget targets separately.

## Verification

Run maintained checks from the repository root:

```sh
./test/unit animated animation_pose spriter_playback physicsbody part
./test/unit cpp:pdg-animation-pose cpp:pdg-spriter-playback cpp:pdg-physics-owners
./test/unit --node animation_pose spriter_playback
./test/unit --web --automated animation_pose spriter_playback
./test/unit --ios animation_pose spriter_playback
./test/rigs human
./test/demo spriter
./test/demo animation-physics
./test/perf animation-pipeline cpp-rig
```

See [the testing guide](../../test/README.md) for capability gates, artifacts and
selection. [Node 24.21 validation](NODE_24_21_UPGRADE.md),
[physics platform validation](PHYSICS_RIG_VALIDATION.md), and
[handoff/IK coverage](RIG_COVERAGE_AUDIT.md) record concrete results and limits.
The benchmark guide explains fixed-work measurements separately from rendering
scores. Current controller/rig snapshots, coordinated physics substeps and
seconds-based APIs are covered by the shared unit suites above.

## Drawing integration revision — 2026-09-20

Replace the animation-only primitive stream with the existing `pdg.Drawing` API.

- [x] Retain shared editable drawing contents across animation registrations, nested drawings and element references; reject containment cycles.
- [x] Implement common Drawing replay with composed transforms, inherited opacity/blend, destination mapping and nested drawings.
- [x] Preserve image opacity on success/failure, transformed curves and explicit local/pixel stroke widths.
- [x] Accept persistent Drawing objects and synchronous callbacks returning Drawing; keep pose inspection contexts borrowed.
- [x] Update native, V8, JavaScriptCore and WebAssembly bindings, docs and examples together.
- [x] Test ownership, edits, nested transforms, opacity, ordering, culling, callback errors, invalid results and headless behavior.
- [x] Run native regressions and Node/client/browser specs; record platform limitations accurately.

Verified on macOS arm64, 2026-09-20:

| Configuration | Result |
| --- | --- |
| Native GUI, Spriter + Chipmunk | All 4 CTest targets pass, including expanded shared/nested Drawing and animation rendering regressions |
| Node/V8 headless | Animation 19 tests / 449 assertions; Drawing 53 / 162; zero failures/skips |
| Embedded GUI/V8 | Animation 19 / 462; Drawing 53 / 162; zero failures/skips; drawing callbacks executed |
| WebAssembly / Chrome WebGL | Animation 19 / 466; Drawing 53 / 162; zero failures; enum/float diagnostic promoted to error during build |
| JavaScriptCore | Regenerated animation and Drawing bindings pass C++20 syntax checking with enum/float diagnostic promoted to error; runtime not exercised |

The native recording port checks composed destination/element/bone/root/layer transforms, reflection, local/pixel strokes, inherited opacity, slot ordering/replacement, conservative culling, deferred registration and callback failure cleanup. Nested Drawing and ElementRef owners keep contents editable after original Drawing handles are released; containment cycles are rejected. Browser framebuffer checks verify nested persistent artwork after explicit Embind wrapper deletion and an ensuing ElementRef color edit. The browser Drawing suite exposed and now covers a previously unbound Quad value type. The common renderer also applies spline transforms, conservatively culls transformed arcs, preserves image opacity, and includes transformed quad/arc/degenerate-line geometry in bounds.

Drawing contents are shared mutable application state, so callback failure cancels submission but does not undo artwork edits. Culling still uses explicit registration bounds (including strokes), or the uncullable fallback. Full iOS/JSC, Windows/Linux and human visual review remain outside this verification. Logs: `/tmp/pdg-drawing-refactor/`.

## Ordinary Spriter debug drawing correction — 2026-09-20

- [x] Apply the active drawing layer's transform and destination port to ordinary
  Spriter bone, point and box debug rendering, matching the artwork path. Preserve
  correct routing after changing ports or moving a Sprite between layers.
- [x] Anchor bone diamonds at the evaluated bone origin, apply signed scale about
  that origin, and share collision-query geometry for debug boxes. Do not rescale
  an already evaluated point position; keep its origin marker readable in pixels.
- [x] Correct the main demo's character placement for its final 0.25 layer zoom;
  use the authored `Walk` and `idle` clip names. The prior GC monitor import fix
  allows the demo to start with normal module-relative resolution.
- [x] Reproduce the original mismatch with a recording-port regression, then
  verify bone/image alignment, reflection, layer rotation/zoom/origin, point
  placement, collision boxes, port replacement and Sprite layer changes.

Validation: native GUI Spriter **677 assertions** and standalone pose **144** pass;
headless Spriter **499 assertions** pass; desktop animation **19 tests / 463
assertions** pass. A temporary live demo probe verified final port positions
`(280, 560)` and `(520, 560)` after the introductory zoom in the 800-by-600 window.
The desktop app was rebuilt, and the user visually confirmed that the corrected
demo looked right. Automated window screenshot capture was unavailable; the
broader visual-culling gate remains open. Logs are under
`/tmp/pdg-debug-*.log` and `/tmp/pdg-demo-position-check.log`.


## Grey Guy rising-rock IK demo — 2026-09-20

- [x] Reuse the first 64-by-64 frame of CanvasMark's `asteroid1.png` in
  `test/js/main.js`; place its support surface beneath Grey Guy's screen-left
  foot (`front_thigh` / `front_shin` / `front_foot` in the authored rig).
- [x] Keep the authored `idle` clip as the source. Preserve the other leg and
  upper-body animation; constrain the ankle while retaining the foot's resting
  orientation so the visible sole sits on the rock.
- [x] Support Grey Guy's nonuniform effective bone scales and animated joint
  offsets in native two-bone IK. Zero length fields use rig-declared lengths or,
  if absent, current child offsets. Keep explicit/declared length checks and
  reject singular scales and zero-length segments. Update C++ and JS doc sources.
- [x] Hold the rock below the sole during the introductory zoom. Start its
  **2.0-second** rise from the layer's zoom-complete event, engage IK at contact,
  and stop at the original demonstrated height (32 display pixels above ground).
  Keep timing calculations in floating-point seconds and convert event
  millisecond timestamps at the boundary.
- [x] Draw the rock and cyan ankle target through the same layer
  transform. Add an **I** toggle to compare constrained motion with authored idle.
- [x] Verify reflected/nonuniform joint chains, changing offsets, preserved
  unconstrained bones, foot artwork and orientation, a full Grey Guy idle cycle,
  runtime drawing, zoom/rise sequencing and toggle restoration.

Run from the repository root: `./pdg test/js/main.js`. After the existing
10-second zoom, the rock rises for two seconds. Press **I** to toggle IK.

Validation: native GUI Spriter **1,412 assertions**, headless Spriter **1,234**,
and standalone pose **328** in each build pass. Desktop JavaScript animation
tests pass **20 tests / 490 assertions**. Both rebuilt native configurations
produced no compiler warnings. The user visually confirmed the initial static
rock demo. An instrumented 14.5-second run of the revised demo observed 497
waiting frames, 100 rising frames, arrival on the first frame after 2.0 seconds,
sub-pixel target error throughout contact, and working off/on restoration.
Logs: `/tmp/pdg-rock-{native,headless,client}-tests.log` and
`/tmp/pdg-rock-rise-check.log`.


## Expanded visual animation showcase — 2026-09-20

- [x] Add automatic Idle/Walk transitions on the middle Wonky at four-second
  intervals, with 0.65-second blends and alternating facing after each pair.
- [x] Add spring-driven head/empty-hand mouse tracking on that Wonky, limited
  to his facing side; restore the authored pose when tracking disengages.
- [x] Attach a retained `pdg.Drawing` sword to Grey Guy's hand, compensating
  for nonuniform bone scale. Add right-side mouse tracking and a small spring
  recoil/contact flash when the blade reaches the cursor, with overlap rearming.
- [x] Add a second, leftmost Wonky using the untouched original asset and
  ordinary playback. Cycle Walk/Attack/Crumble/Idle to retain optional tracks
  and changing-hierarchy behavior alongside the editable-pose demonstration.
- [x] Supply a reproducible generated Idle/Walk asset for the middle Wonky;
  preserve the source asset and reuse its images. Document the demo controls
  and regeneration command in `test/data/animation-demo/README.md`.
- [x] Gently slide the rock after its two-second rise and use
  `AnimationContactTarget` to keep the ankle target fixed relative to it.
Aiming, facing changes, blade contact/recoil and rock presentation are checked
visually with `./test/demo spriter`. The ordinary and editable-pose paths use
separate Wonky assets so changing-hierarchy clips remain available alongside IK.

### Showcase replay and sword-hand follow-up

- [x] Resume each newly selected original Wonky clip so completed nonlooping
  Attack/Crumble animations rewind and play on subsequent cycles. Keep the
  existing API behavior that clip selection preserves playback positions.
- [x] Move Grey Guy's sword and aiming IK to `front_arm` / `front_forarm` /
  `front_hand`, drawing before `p_hand_idle_0` with a grip aligned to that fist.
- [x] Check repeated Attack/Crumble playback on the original Wonky asset with
  fixed simulation steps in `./test/unit cpp:pdg-spriter-playback`: two starts at
  zero, intermediate progress, natural completion and staying completed after
  extra time, with Walk/Idle selection between cycles.

Verify front-hand grip alignment, reachable sword contact, recoil/rearming and
facing-side tracking visually in `./test/demo spriter`.
