# PDG animation architecture and remaining extensions

Reviewed 2026-09-27. The pose/controller, IK, Drawing, transition, trigger,
shared-physics, active-control, handoff, recovery and snapshot foundations are
implemented. Motion matching, PDG-owned clip evaluation and offline conversion
remain planned.

The [implementation checklist](PDG_ANIMATION_API_EXTENSION_CHECKLIST.md) owns
feature/acceptance status. The [API change list](ANIMATED_PART_API_CHANGE_LIST.md)
records the shared Part/PhysicsBody design and owned-playback backlog. The
[rig plan](ANIMATION_PHYSICS_RIG_PLAN.md) records generated/explicit rigs and
remaining manual/platform acceptance. See the
[Spriter inventory](ENHANCED_SPRITER_API_PROPOSAL.md) for format-specific gaps.

## Scope and boundaries

PDG supplies runtime animation and physics mechanisms; applications own game
rules, movement policy and action selection. Pose editing and IK work without
physics. Imported animation physics requires Chipmunk. General vector morphing,
weighted mesh skinning and a live libsynfig renderer remain outside this scope.
The SpriterPlusPlus and Node submodules are not patched for these features.

## Implemented foundation

- `Animated` supplies programmed transforms, movement/spin and growth/stretching.
  Its public durations, helper callbacks and easing use floating-point seconds.
- `Part : Animated` supplies independent identity, local transforms, optional
  bone bindings, artwork and collider/body associations. Sprite owns Parts.
- Sprite and Part expose optional PhysicsBody components through `.physics`;
  absent bodies use the shared NoPhysics object. Physical loads, velocities,
  inertia and impulses belong to PhysicsBody, independently of Animated.
- `AnimationRig` and `AnimationPose` represent hierarchy, local transforms and
  owned snapshots. The SCML adapter supports fixed hierarchy and track presence.
  Ordinary Spriter playback remains available for other topologies.
- `enableAnimationPose(referenceClip)` enables editable poses; failure reports
  `getAnimationRigError()`. Sampling and query results do not advance live time.
- `addAnimationModifier`, `addAnimationIK`, `seekAnimation` and
  `transitionToAnimation` operate through the Sprite facade. Modifier callbacks
  are synchronous and receive borrowed pose views; copy retained results.
- `addAnimationDrawable` supplies retained Drawing artwork or synchronous
  Drawing-producing callbacks. Rendering, sockets, attachment queries and
  collision geometry consume the same final published pose.
- SCML eventlines dispatch named triggers with clip-relative `timeSeconds` and
  update-relative `offsetSeconds`. Silent sampling and seeking do not replay
  crossed events. Typed variables/tags are sampled pose metadata.
- Explicit and generated physical rigs share editable Parts, colliders and
  constraints. Kinematic, Dynamic and Driven modes support explicit handoff,
  recovery, membership, reflection and graph snapshots.

Use the [animation reference](../cxx/dox/animation.dox),
[Part reference](../javascript/dox/part-methods.dox),
[timing contract](ANIMATION_TIMING_API_AUDIT.md), and
[physics units](ANIMATION_PHYSICS_UNIT_AUDIT.md) for current signatures and units.

## Evaluation and ownership

Each update starts from an authored or declared reference pose. Modifiers and IK
operate on that clean base; offsets do not accumulate from the previous final
pose. Stateful springs/contact locks retain their own explicit controller state.

Articulated simulation evaluates desired animation/IK, updates physical targets,
steps physics with coordinated substeps, then publishes the final pose. Dynamic
bodies remain authoritative. Sampling for targets must not advance playback or
emit triggers a second time. Animation IK and independent Part-chain IK have
different ownership rules; see the [coverage audit](RIG_COVERAGE_AUDIT.md).

One system owns root motion. Physical drives, animation and mounts must not
compete to write the same final transform. Physics body/constraint changes obey
locked-space and teardown lifetime rules. Callback-requested rig replacement,
broader topology support and additional diagnostic overlays remain explicit
checklist items.

## PDG-owned clip evaluation

SpriterPlusPlus still supplies authored track evaluation, playback state and
render traversal. PDG-owned rig/pose snapshots do not yet replace that evaluator.
The [owned-playback plan](ANIMATED_PART_API_CHANGE_LIST.md#pdg-owned-animation-assets-and-playback)
defines an incremental replacement with parity checks for authored curves,
rotation routes, track presence/order, pivots, character maps, metadata and events.
Keep source import, shared immutable clip data, per-instance state and final
render/query consumers separate.

## Motion matching

Build a database from sampled destination-runtime poses: root-relative joints/velocities, contact labels, movement descriptors, clip/time and compatibility tags. In-place clips require declared speed or virtual root trajectories. Converted Synfig assets are indexed after conversion, using the same rig mapping.

An optional matcher selects clip/time from controller intent and the continuous pre-IK base pose. Use normalized weighted distance, hard eligibility filters, natural-continuation scoring and hysteresis. Start with a linear search. High-level action policy remains caller-owned.

The matcher calls `Sprite.transitionToAnimation`; the procedural layer and IK refine the result. Match against a consistent pre-IK pose domain and supply contacts separately, avoiding feedback from terrain-corrected joints into an uncorrected database. IK helps maintain feet/hands but cannot invent missing motion coverage or correct unlimited root mismatch.

Keep feature extraction, nearest-neighbor search and pose transitions independently testable. A reference locomotion controller can demonstrate use without hardcoding side-view movement rules into Sprite.

## Synfig asset workflow

Use a standalone converter to emit SCML plus rigid PNG parts and a rig manifest. Preserve bones, ordinary parent relationships and representable transform tracks; sample source expressions offline. Report whether an export preserves articulation or only reproduces sampled source-constraint motion.

Static vector parts can be rasterized once. Deformation/morphing and nonrepresentable skew are reported or explicitly omitted/frozen under an export profile, never silently claimed as supported. No Synfig runtime API or dependency is added to PDG. Refer to the dedicated conversion plan for coordinate, interpolation and source-evaluation details.

## Compatibility, capability and performance contracts

- Existing Sprite APIs remain valid; new controller access is opt-in. Preserve Spriter-specific names/event IDs rather than redefining them for all animation types.
- Expose capabilities such as rig access, pose editing, independent sampling, IK and physics rig. Frame-only sprites report unsupported skeletal operations clearly.
- Support C++ and generated JavaScript bindings through source-of-truth inputs. Verify V8, JSC, Emscripten and relevant mobile paths; do not hand-edit generated outputs.
- Keep pose math, IK and evaluation usable headlessly. Rendering and Chipmunk remain feature-gated separately.
- Cache IDs and use reusable pose buffers. Recalculate dirty hierarchies in batches; avoid allocation and script crossings per bone for native solvers. Benchmark before promising character counts.
- Use versioned rig/feature caches keyed by source content, evaluator version, coordinate conventions and extraction settings.
- Deterministic ordering is required; cross-platform bit-identical physics or replay is not promised. Record search tie-breaks and explicit state where reproducibility matters.

## Verification

Use [test/README.md](../../test/README.md) for current runners and artifacts.
Focused script suites include `animated`, `part`, `physicsbody`, `animation_pose`
and `spriter_playback`. Native CTest suites cover pose math, playback, physics
owners and body contracts. `test/rigs` checks real human assets/controllers;
`test/demo spriter` and `test/demo animation-physics` support visual acceptance.

Measure API costs and rig workloads with `test/perf animation-pipeline cpp-rig`.
A passing unit test or benchmark does not establish visual or platform parity.

## Investigation references

- [Motion matching](SPRITER_MOTION_MATCHING_INVESTIGATION.md)
- [Synfig support](SYNFIG_SPRITER_SUPPORT_INVESTIGATION.md)
- [Rigid Synfig conversion](SYNFIG_TO_SPRITER_RIG_CONVERSION_PLAN.md)
- [IK and physical ownership](SPRITER_CHIPMUNK_2D_IK_INVESTIGATION.md)
