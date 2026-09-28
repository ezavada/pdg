# Automatic animation physics rigs and control modes

Planning update: 2026-09-25. Status: **dynamic rig generation, root selection, mass accounting and body angular-speed breaks implemented; Kinematic/Dynamic/Driven control, explicit handoff, recovery, membership and cross-Sprite Part transfers implemented; explicit/generated Sprite rigs share editable components and support active snapshots, whole-rig loads, rotational queries and live reflection**.

This records the agreed direction from the rig-generation, body-control and IK
discussion. It extends the existing imported physical-rig implementation and
checkpoint 5 snapshot work. Setup/root calls, mode/drive coordination, recovery,
body angular-speed breaks and the shared graph are implemented. The API spelling
and defaults below describe those contracts; remaining work is acceptance and
deferred enhancements. The [decision status](#decision-status) separates agreed
requirements, settled user choices and engineering follow-ups.

Related: [active API checklist](ANIMATED_PART_API_CHANGE_LIST.md),
[animation implementation checklist](PDG_ANIMATION_API_EXTENSION_CHECKLIST.md).

The human demo is accepted at its current checkpoint. Joint placement/contour
corrections and the current elbow/knee behavior are complete for that scope.
Editable constraint anchors and the demo's held-IK "pose me" mode are now
implemented. Other demo enhancements below remain deferred alongside the
remaining engine acceptance and broader API backlog.

## Agreed behavior

- `Sprite.setupPhysicsFromAnimationRig(totalMass)` explicitly creates the full
  physical rig. Every included body starts **dynamic**, with physics active.
  Loading an animation alone does not create physics.
- Use skeleton connectivity for physical joints. Skip genuinely zero-length
  non-root bones when allocating bodies and distributing mass. Keep them in the
  animation skeleton and traverse them when selecting descendants. If the
  designated root's calculated length is zero, assign it a **1 mm physical length**
  and include its body in the rig and mass distribution.
- Infer length from the farthest-apart child connection points. With one child,
  use the bone's own joint to that child's joint; with no children, infer length
  from the bone's artwork. Use stable reference geometry rather than a changing
  animation frame.
- Generate capsules with radius `0.1 * length`, editable afterward. Default to
  pivot joints with free rotation when no explicit limits exist, unlimited
  constraint strength, breaking and self-collision disabled, and no initial drive.
- Route whole-Sprite impulses to the selected physical root body. Choose a bone
  named `root` automatically; otherwise choose the bone with the largest total
  descendant count. Allow an explicit root override.
- Initially distribute total mass by included bone length:
  `mass[i] = totalMass * length[i] / sum(includedLengths)`.
- While a physical rig represents the Sprite, `sprite.physics.getMass()` reports
  its components' total mass. `sprite.physics.setMass(totalMass)` proportionally
  scales their current masses and inertia. A Part mass edit changes that body's
  mass/inertia and the reported total, without changing other Parts' masses.
  Component masses remain authoritative; no separate stored percentage is needed.
- Attaching a component adds its existing mass to the total; detaching one removes
  its mass. Neither operation redistributes mass among the remaining components.
- Expose generated bodies through `findPart(boneName).physics`. Body properties,
  colliders and constraints remain independently editable through their existing
  owner/component APIs rather than another large rig configuration object.
- Support whole-rig, one-bone, and bone-plus-descendants control changes.
- Support Kinematic, Dynamic and Driven rig control. **Driven is a dynamic body
  with an animation/IK target controller**, not a fourth PhysicsBody mode.
- Require explicit release before a different controller takes over a body's
  drive. Within manual control, the last successful `setDriveTarget()` wins,
  including calls from different scripts; no release is needed between updates.
- IK produces a desired pose. Kinematic control follows it; free dynamic bodies
  do not automatically follow it; driven bodies approach it through bounded
  forces/torques. The final solved physical pose remains authoritative.
- Recovery takes a configurable `recoveryTime`, default 0.5 seconds. Emit a Sprite
  event only on recovery completion; use normal collision events for blocking.
  Do not add recovery-start or recovery-blocked events.
- Preserve existing Sprite flipping semantics. The user was describing existing
  support, not requesting a new render-only flip or visual/collider separation.
- Allow a rotation-speed threshold on any PhysicsBody and emit a Sprite Break
  event when it is exceeded. This includes a spinning shaft with no joint. Keep
  existing Chipmunk braking/constraint behavior; no new braking solver is required.

## Implemented control and recovery contract

- Whole-rig, bone and skeleton-subtree selectors preserve bodies, colliders and
  joints. Direct body mode edits use the same coordinator; Static is rejected.
  Kinematic joints stay configured but dormant. Mixed queries report actual modes.
- Desired animation/IK evaluation runs once per animation update, separately from
  physical publication. Driven limbs actuate relative to physical parents with
  equal/opposite reactions; components without a physical ancestor use a world target.
- Rig and Part IK drive claims require explicit release. Manual drive updates
  remain last-successful-call-wins. Settings are retained, copied by getters and
  validated before selection changes.
- Positive recovery blends targets over the requested duration, then waits until
  each body's position/angle error reaches tolerance (0.1% of segment length,
  minimum 1e-6 layer units, and 0.001 radians). During recovery the actual mode is
  Driven. Stored settings bound recovery; unconfigured Kinematic recovery uses a
  temporary 4 Hz, critically damped servo with per-body caps of
  `mass * max(length, .001) * (2*pi*4)^2` and `inertia * (2*pi*4)^2`.
  Bounded integral correction removes steady gravity/load error during recovery.
  Driven itself still requires explicit settings. Contacts, limits or
  weak settings may extend recovery indefinitely. Normal collision events report
  blocking; there is no additional blocked/start event.
- `action_AnimationPhysicsRecoveryComplete` uses `eventType_SpriteAnimate` with
  `SpriteAnimationPhysicsRecoveryInfo` and JS `onAnimationPhysicsRecoveryComplete`.
  Fields identify the Sprite/layer/event, bone/wholeRig/includeDescendants,
  destination mode, bodyCount and whether the rig was disabled.
- Overlapping commands cancel the old selection's completion notification;
  unaffected bodies can finish. Any mode change cancels pending disable. Disable
  retains the full rig until recovery completes; zero tears down immediately.
  Engine destruction/layer removal uses immediate teardown without recovery events.
- Active-rig snapshots preserve desired poses, membership, modes, drive ownership
  and recovery. Cross-Sprite Part transfers are implemented; live reflection is implemented; arbitrary physical resizing remains outside this scope.

## Current implementation and gaps

Verified against the current source, not older planning inventories:

- `Sprite.setupAnimationPhysics(definition)` accepts explicit capsule/body/joint
  definitions. Both explicit and generated Sprite rigs expose shared Colliders and
  PhysicsConstraints through their named Parts. Mapped offset edits, rebinding and removal remain restricted while enabled. Runtime control modes now share the generated-rig coordinator.
- `AnimationBone.length` exists, but the SCML adapter initializes it to zero
  (unspecified). Display widths are deliberately not treated as physical lengths.
  Automatic generation cannot interpret every current zero as a zero-length bone.
- The 112 inspected SCML files in `test/data/spriter-samples` and
  `test/sprinter-private` have no exported physical joint-limit fields. Grey Guy
  and Wonky Skeleton each have 15 bones with artwork. Some private variants have
  unused terminal bones, but no explicit helper classification was found.
- `PhysicsBody` already exposes mass, inertia, materials, damping, motion, forces
  and drives. `setMass()` now scales inertia proportionally, including ordinary
  bodies; explicit `setupPhysicsBody(mass, inertia)` still assigns the pair. Drives
  use owning-layer world targets and require dynamic bodies.
- `setupPhysicsFromAnimationRig(totalMass, unitsPerMeter = 1)` now creates a full
  dynamic rig with shared capsule Colliders and pivot PhysicsConstraints. Generated
  rigs report component total mass through the coordinating body; whole/part mass
  edits scale inertia. Repeat setup reapplies the original length-based fractions
  without replacing components. Disable transfers the total and root velocity back,
  retaining the single body's previously configured inertia. The explicit configuration path uses the same shared graph and mass contract.
- Shared `PhysicsConstraint` supports enumeration through its bodies, angle-limit
  edits, force/break limits and collision policy. Explicit pivots/rotary limits and generated pivots are all in that collection. Capsule Collider
  geometry and public body-local anchor/groove editing are implemented. Body angular-speed
  thresholds emit notifications, not a speed ceiling; existing motors target a rate and `setBreakForce()` tests force/torque.
- `eventType_SpriteBreak` / `SpriteJointBreakInfo` now supports solver-independent
  body overspeed with reason, body, Part, speed, threshold and optional reference.
  Legacy joint fields remain; body notifications have no joint. Shared Collider contacts support owner
  Sprite delivery through `eventType_ColliderContact`.
- Direct Part IK and physical Part IK already exist for independent Part chains.
  Mapped rig bodies use the animation controller; physical Part IK remains for independent contiguous Part chains. Animation IK feeds rig desired poses.
- Sprite flipping changes the root frame consumed by poses, Parts and attachments.
  Explicit setup accepts unit scale magnitudes with reflection. Generated setup
  accepts reflected uniform Sprite scale and nonuniform bone scales. Live flips
  reflect attached bodies, velocities, collider frames, anchors and angular limits,
  preserving shared identities. Detached parts stay independent. External angular
  constraints require explicit disconnection; external linear anchors stay fixed.
  Arbitrary animated physical resizing is outside the agreed flip requirement.
- Initial snapshots restore active explicit/generated Sprite rigs, including
  bone/control/root ownership and the current edited component graph. Layer loads
  stage the graph before adoption; standalone Sprite loads retain their existing
  non-atomic replacement contract. Callback serialization remains unsupported.

Implementation references: [body API](../../src/inc/pdg/sys/physicsbody.h),
[constraint API](../../src/inc/pdg/sys/physicsconstraint.h),
[physical rig](../../src/sys/animationphysics.cpp),
[Spriter adapter](../../src/sys/spriter/pdg_spriter_pose.cpp),
[Part IK](../../src/sys/part-ik.inc).

## Intended public API

Keep rig coordination on Sprite, physical values on PhysicsBody, geometry on
Collider and mechanical relationships on PhysicsConstraint. Do not add physics
ownership to Animated or SpriteLayer. Reuse the established `setup...`,
`setAnimation...`, `getAnimation...` families, integer selectors and fluent setters.

Implemented setup/root and control surface; optional arguments below describe the JavaScript facade:

| Call | Result and contract |
| --- | --- |
| `setupPhysicsFromAnimationRig(totalMass, unitsPerMeter = 1)` | Returns the Sprite. Requires a finite positive mass and an enabled, supported animation rig. Initial creation builds and activates all included bodies as Dynamic. The optional distance-unit conversion applies to the 1 mm root fallback. Implemented for Chipmunk layers. |
| `attachAnimationPhysicsPart(part, parent = null)` | Register a same-Sprite physical Part. Skeletal parent is inferred; accessory parent is logical membership only. No joint creation or teleport. |
| `detachAnimationPhysicsPart(part, includeDescendants = true)` | Remove the selected assembly members, disconnect boundary joints and release skeletal control to Dynamic; preserve internal joints and masses. |
| `isAnimationPhysicsPartAttached(part)` | Query generated assembly membership, independent of joint connectivity. |
| `getAnimationPhysicsSetupWarnings()` | Returns a copied array of inference/skipped-segment/root-fallback diagnostics from the last successful generated setup. Implemented. |
| `setAnimationPhysicsMode(mode, bone?, includeDescendants = false, recoveryTime = 0.5, direction = rotationDirection_AsSpecified)` | Returns the Sprite. Changes selected existing bodies without replacement or mass redistribution; recovery to animation control uses the requested seconds. Zero requests immediate recovery. |
| `getAnimationPhysicsMode(bone?, includeDescendants = false)` | Returns their common control mode, or the query-only `animationPhysics_Mixed` value. |
| `setAnimationPhysicsRoot(bone)` | Returns the Sprite. Selects an explicit root by name or bone ID; requires an enabled pose. Validate an active rig's physical mapping before changing its root. |
| `getAnimationPhysicsRoot()` | Returns the selected `AnimationBoneId` for the current rig, whether automatic or explicit. |
| `clearAnimationPhysicsRoot()` | Returns the Sprite. Removes the override and reapplies automatic root selection. |
| `setAnimationPhysicsDriveSettings(settings, bone?, includeDescendants = false)` | Returns the Sprite. Configures the [drive settings record](#drive-settings-record) without changing control mode; changes take effect on already Driven bodies. |
| `getAnimationPhysicsDriveSettings(bone)` | Returns a copy of the five-field [drive settings record](#drive-settings-record), including resolved defaults, or null if unconfigured. Requires a single included bone; does not return an ambiguous aggregate. |

Use a native `AnimationPhysicsMode` enum with exported integer constants
`animationPhysics_Kinematic`, `animationPhysics_Dynamic`,
`animationPhysics_Driven`, and query-only `animationPhysics_Mixed`. Reject Mixed as
a setter argument. Keep `physicsBody_Dynamic`, `physicsBody_Kinematic`, and
`physicsBody_Static` unchanged; there is no `physicsBody_Driven`.

For mode/drive-setting methods that accept whole-rig or subtree selection, provide
a whole-rig overload, an `AnimationBoneId` overload and a `const char*` bone-name
overload. Native fluent
methods return `Sprite&`; JavaScript returns the same Sprite wrapper. This avoids
repurposing `boneId_None`/`animation_NoBone` to mean all bones. Bone IDs belong to
the current rig revision, not a physical-body array or Part ID.

For optional bone selectors, JavaScript omission/undefined selects the whole rig.
Explicit null, unknown names, invalid IDs, nonboolean descendant flags and invalid
modes throw. A selected
zero-length bone is permitted as a subtree root when included descendants exist;
a selection with no physical bodies throws. Whole-rig selection always includes
all generated bodies. Resolve descendants through the skeletal hierarchy, not
the independently editable Part-parent or constraint graph.

### Root selection and impulse routing

Selection order is explicit override, exact bone name `root`, then greatest total
descendant count. Interpret "total number of children" as all skeletal descendants,
including descendants reached through skipped zero-length bones. Recommended tie
break: lowest stable bone ID in the current rig. Selection uses the skeleton, not
the independently editable Part-parent or constraint graph.

`sprite.physics.applyImpulse(impulse)` routes to that root's actual component body,
not the coordinating kinematic Sprite body and not a mass-weighted split. Preserve
the world-point overload: an impulse at a point uses the root body's lever arm.
Direct Part impulses continue to target the selected Part. A kinematic root does
not become dynamic merely because an impulse was requested; follow the existing
body-mode contract.

Select the root before filtering zero-length bones. If that root's resolved length
is zero, assign it a 1 mm physical length and create its own component body; whole-
Sprite impulses therefore still target the designated root. Apply this exception
to both automatic and explicit root selection. It is a fallback for zero, not a
minimum imposed on already positive lengths. Preserve the authored skeleton/IK
geometry; the synthetic length belongs to generated physics geometry.

PDG physics dimensions use application/layer distance units. The implemented
optional `unitsPerMeter` setup argument supplies this conversion; its documented
default is 1 (meter coordinates for the fallback). For example, 1000 gives a
one-unit 1 mm segment. Only the fallback is converted; authored reference lengths
already use the rig's units. Effective bone scale is accounted for before the
length-weighted mass calculation. Changing this setting on a live rig requires
explicit teardown. No pixel-to-meter ratio is inferred.

Fixed/Follow translation and whole-Sprite movement/rotation targets work with
mixed body modes. Follow preserves Sprite rotation/scale while publishing the
selected body's translation; gameplay edits update the desired frame before pose
queries can publish the physical frame. Dynamic components are not teleported.
Finite/continuous forces and torques route to the selected root. Force IDs and
lifetimes belong to the Sprite, so root changes and snapshots preserve cancellation.
Inertia and angular momentum queries aggregate attached members about their current
center of mass, including parallel-axis offsets and orbital motion respectively.

### Assembly mass and per-body inertia

Use the existing PhysicsBody mass methods for both a single-body Sprite and a
Sprite represented by an articulated rig.

| Existing call | Intended behavior while a physical rig represents the Sprite |
| --- | --- |
| `sprite.physics.getMass()` | Sum the configured masses of participating component bodies, including kinematic components. The coordinating Sprite body is not an additional contribution. |
| `sprite.physics.setMass(totalMass)` | Scale all participating masses and inertia by `totalMass / currentTotalMass`, preserving their current distribution. |
| `sprite.findPart(name).physics.getMass()` | Return that component body's own mass. |
| `sprite.findPart(name).physics.setMass(mass)` | Change only that component's mass, scale its inertia by `mass / oldMass`, and update the Sprite's reported total. |

Masses remain finite positive values in the application's mass units. Setters
retain their existing fluent PhysicsBody return type in C++ and JavaScript.
Implement the contract on the actual owner-associated PhysicsBody so retained
native references and script wrappers agree; a JavaScript-only forwarding layer
would leave inconsistent behavior.

For unchanged geometry, proportional inertia scaling preserves each component's
existing inertia-to-mass ratio, including deliberate inertia tuning. Keep linear
and angular velocities unchanged, as current mass edits do; this does not conserve
momentum. Individual bodies retain explicit `setMomentOfInertia()` overrides.
Whole-rig `getMomentOfInertia()` is the current pose's locked inertia about its
center of mass: `sum(I_i + m_i * |r_i - COM|²)`. `getAngularMomentum()` includes
spin and orbital motion about that same COM. These are computed from current
member states, include Kinematic members, and exclude the proxy and detached bodies.
The aggregate inertia setter still rejects; tune component inertia directly.

Actual component masses are the source of truth. Compute the total on demand or
maintain an invalidated cache; do not keep a separately editable total. A fraction
is derived as `componentMass / totalMass`, not stored as another mass property.
Assembly membership determines what is counted, not arbitrary joint connectivity.
Initially use the rig's explicitly registered components; do not automatically
include unrelated Parts, mounted Sprites or externally constrained bodies. Count
each body once, regardless of hierarchy depth or Kinematic/Dynamic/Driven mode.

An explicit attachment to the rig adds the component's existing mass to the sum;
detachment removes it. Preserve all other component masses and inertia. A transfer
between assemblies subtracts from one total and adds to the other without counting
the body twice. Changing mass on an individual component likewise changes the sum.

Changing the total is an atomic component update: validate all resulting masses
and inertia before applying any. Preserve body identities, geometry, velocities,
loads, joints, control modes and drive settings. Public assembly mass must remain
separate from the coordinating body's solver mass/inverse mass; the root stays
kinematic and gains no extra simulated mass.

When disabling the rig and returning to a single body, carry the current total
mass into that body rather than restoring a stale pre-rig mass. The rule for its
inertia and motion keeps the previously configured single-body inertia and the
selected root's velocity. This is not a momentum-conserving merge. Retained
component handles after teardown cease contributing to the Sprite's total.

The agreed rebalancing operation is whole-Sprite `setMass()`, which preserves
current proportions. Child edits and membership changes adjust the total instead.
Do not add a fixed-total child-redistribution API to the current scope; that was an
optional suggestion, not a missing requirement. Reapplying the original bone-length
distribution remains a distinct reconfiguration.

### Drive settings record

`AnimationPhysicsDriveSettings` describes how strongly and responsively a bone's
drive follows its desired animation/IK pose. It has the same five fields in C++
and JavaScript:

| Field | Meaning | Requirement/default |
| --- | --- | --- |
| `maxForce` | Maximum magnitude of the drive's linear force contribution. | Required, finite, nonnegative; mass times owning-layer distance units per second squared. |
| `maxTorque` | Maximum magnitude of the drive's turning torque contribution. | Required, finite, nonnegative; inertia units times radians per second squared. |
| `frequency` | Spring response frequency: higher values request faster, stiffer tracking, subject to force/torque limits. This is neither animation playback speed nor an RPM limit. | Default 4; finite positive cycles/second (Hz). |
| `dampingRatio` | Damping of tracking oscillations: 0 requests no drive damping; 1 corresponds to critical damping in the ideal unconstrained spring model. Actual motion also depends on contacts, joints and force/torque limits. | Default 1; finite nonnegative, dimensionless. |
| `direction` | Angular route to the target: shortest, clockwise, counterclockwise or as specified, using the existing rotation-direction constants. | Default `rotationDirection_Shortest`, matching PhysicsBody drives. |

Force/torque caps apply to each selected body's drive, not a budget shared by the
selection. They do not cap contact forces, independent loads or angular velocity.
The record contains no mass, inertia, joint-angle limits, target pose or current
applied force. Physical properties remain on the body/constraints; animation and
IK supply the target. Current drive output/error belongs in drive-state queries.

The getter returns stored settings even while that bone is Kinematic or Dynamic;
use `getAnimationPhysicsMode(bone)` to check whether tracking is active. Editing
the returned copy has no effect until passed back to the settings setter.

Require settings before selecting Driven; validate the entire selection before
changing anything. Zero force or torque disables that actuation channel. Do not
invent a universally suitable default force from the body mass. Native settings
queries return `std::optional<AnimationPhysicsDriveSettings>`; JavaScript returns
a copied object or null. Missing bodies/rigs remain errors, not an unconfigured
settings result.

Each settings call replaces the selected bodies' settings, applying the documented
defaults to omitted optional fields; it is not a partial merge. Preserve authored
unwrapped turns under `rotationDirection_AsSpecified`. Define the direction frame
for relative drives and reflected rigs, and retain the resolved angular route
across ticks instead of independently wrapping each target. Physical joint limits
remain authoritative when they prevent a requested route.

### Drive ownership and explicit release

One active controller owns a body's drive: rig tracking, physical Part IK, or
manual control. Installing a different controller while ownership is held throws
without changing the existing controller or target. Validate a whole-rig/subtree
request before changing any selected body; a conflict must not cause a partial
handoff.

| Current controller | Explicit release operation |
| --- | --- |
| Rig animation/IK tracking | Set the selected bone/subtree to `animationPhysics_Dynamic` to release its rig tracking. |
| Physical Part IK | Call `clearIKTarget()` on the Part that owns the IK controller; release its complete chain of drives. |
| Manual drive | Call `PhysicsBody.clearDrive()` before assigning a different controller. |

Changing rig modes can reconfigure/release that rig's own control, but cannot
silently clear another owner's manual or Part IK drive. Likewise, a raw body
`clearDrive()` must not bypass a rig/IK owner's coordinated release operation.

For an unclaimed dynamic body, `setDriveTarget()` installs manual control. Further
successful calls replace that manual drive's complete target/settings in execution
order: **the last call wins**, even when different scripts made the calls. No
additional caller identities, priority system or per-update release are required.
Invalid calls leave the last valid target intact. This update rule does not allow
`setDriveTarget()` to take over a body still owned by rig tracking or Part IK.

Repeated updates from the same rig/IK controller remain valid. Animation IK that
modifies the rig's desired pose, and ordinary forces/impulses, do not themselves
request drive ownership. Releasing control preserves physical motion and independent
loads; returning to rig tracking requires an explicit mode change.

### Planned usage

Example of the **planned API**, assuming pose setup has succeeded and these bone
names exist (force/torque limits must be tuned for the game's units):

```js
sprite.setupPhysicsFromAnimationRig(70); // Full dynamic rig immediately.
sprite.physics.setMass(84); // Scale every component's mass and inertia by 1.2.
// sprite.physics.getMass() now reports 84, including kinematic components later.
sprite.setAnimationPhysicsMode(pdg.animationPhysics_Kinematic);

// Let the forearm and hand go limp while the rest follows animation.
sprite.setAnimationPhysicsMode(pdg.animationPhysics_Dynamic, 'forearm', true);

// Recover that subtree's ability to follow animation/IK using physical drives.
sprite.setAnimationPhysicsDriveSettings({
    maxForce: 120, maxTorque: 60, frequency: 4, dampingRatio: 1
}, 'forearm', true);
sprite.setAnimationPhysicsMode(pdg.animationPhysics_Driven, 'forearm', true);

const settings = sprite.getAnimationPhysicsDriveSettings('forearm');
// { maxForce: 120, maxTorque: 60, frequency: 4, dampingRatio: 1,
//   direction: pdg.rotationDirection_Shortest }

sprite.findPart('forearm').physics.setFriction(0.8).setAngularDamping(0.2);
```

Retain `supportsAnimationPhysics()`, `isAnimationPhysicsEnabled()` and
`disableAnimationPhysics()`. The recovery default is now
`disableAnimationPhysics(recoveryTime = 0.5, direction = rotationDirection_AsSpecified)`;
explicit zero requests immediate recovery. Kinematic does not mean disabled. Use the recovery
parameter on existing operations rather than a separate transition-method family.
`setupAnimationPhysics(definition)` is the explicit-authoring path on the
same shared graph/controller model. `setAnimationPhysicsMode` controls both
explicit and generated rigs.

## Generation, tuning and lifetime contract

Use these agreed length rules in a stable reference pose, in a consistent frame:

| Child count | Length source |
| --- | --- |
| Two or more | Maximum distance between child connection points on this bone. |
| One | Distance from this bone's own joint to the child's connection point. |
| None | Infer from artwork assigned to this bone, respecting its pivot/transform. |

After resolving length, replace zero with 1 mm for the designated root only,
converted to the application's distance units. Include that fallback length in
the mass-distribution numerator and denominator. Other resolved zero-length bones
remain excluded; unresolved lengths still require a diagnostic/fallback decision.

Implemented placement uses the farthest pair as axis and midpoint. Leaf inference
uses the major axis through the center of the union of reference image bounds in
bone-local coordinates, respecting pivots and binding transforms. Authored SCML
file dimensions work without GUI image loading. Missing bounds are diagnosed and
skipped; the designated root still gets its explicit fallback. Disconnected trees
remain separate component trees, with only the selected root driving Sprite follow.

Agreed capsule thickness: `radius = 0.1 * length` (diameter is 20% of length),
including the designated root's fallback physical length. This is the generated
starting geometry; callers can tune each Part's Collider afterward. Broad torsos
or thin shafts may need that tuning. Artwork inference for terminal-bone length
does not change the agreed proportional-radius default.

Agreed joint defaults:

| Property | Agreed default | Optional tuning |
| --- | --- | --- |
| Connection | Pivot/hinge at the skeletal joint | Spring/compliant connection for deliberately stretchy objects. |
| Angular range | Free rotation where no explicit limit metadata exists | Authored limits or chosen presets; a reference-pose window is possible but arbitrary. |
| Constraint strength | Shared constraints' default unlimited `maxForce` | A finite force/torque cap allows the joint to yield under load. |
| Break threshold | Disabled until configured | Explicit application-authored force/torque thresholds. |
| Drive | None on initial Dynamic setup | Enable bounded tracking explicitly through Driven mode. |
| Internal collisions | Off initially, matching the current rig default | Enable nonadjacent self-collisions; normally keep directly joined bodies from colliding. |

- [x] Resolve the agreed reference lengths, distinguishing unspecified importer
  values from true zero lengths, then initialize bodies from the current pose.
  Define the leaf-artwork estimator/fallback without implicitly changing IK length
  semantics. `getAnimationPhysicsSetupWarnings()` records inferred/skipped geometry.
  Nonuniform bone scale is resolved into physical lengths and rigid Part frames.
- [x] Apply the designated-root 1 mm exception before filtering and mass
  distribution. Resolve the physical-unit conversion explicitly, keep positive
  lengths unchanged, and record when the root fallback was used.
- [x] Generate capsules with the agreed `0.1 * length` radius and joint defaults;
  resolve center offsets and shape-derived inertia. Connect each
  included child to its nearest included ancestor at the appropriate skeletal
  joint location, preserving skipped transforms. Handle disconnected/multiple
  roots explicitly and reject rigs with no usable segments.
- [x] Distribute mass over included segments only. Avoid counting the Sprite's
  coordinating root body as another share of totalMass. Implement the agreed
  [assembly mass contract](#assembly-mass-and-per-body-inertia) through existing
  PhysicsBody methods, including aggregate invalidation after component changes.
- [x] Use retained shared Parts, PhysicsBodies, Colliders and PhysicsConstraints,
  including editable collision filters and joint limits. Define creation/reuse
  rules for pre-existing named Parts and reject ownership/topology conflicts
  before mutating caller-owned state. Generated bodies/colliders/pivots and named
  Part conflict validation are implemented for both setup paths. Explicit definitions
  create shared pivot/rotary-limit pairs; zero-length explicit capsules become circles.
- [x] Recommended repeated-setup contract: for the same generated topology,
  reapply the original length-based mass proportions while preserving object identity,
  geometry edits, motion, loads, modes, drive settings and external constraints.
  This deliberately replaces per-body mass overrides. A changed rig/topology
  requires explicit teardown/rebuild, not hidden replacement. Initial creation
  starts Dynamic; subsequent reconfiguration does not reset control modes. Ordinary
  total-mass edits use `sprite.physics.setMass()` and preserve tuned proportions.
- [x] Provide shape-derived initial inertia and proportional component inertia
  updates for both direct and whole-rig mass edits. Audit compatibility of applying
  that mass/inertia rule uniformly to ordinary bodies. For an ordinary single body,
  `setupPhysicsBody(mass, inertia)` still applies its explicit pair without double
  scaling. Define that setup call's behavior on an active assembly before exposing
  an ambiguous aggregate inertia argument. Implemented policy: reject that call
  on the active coordinating body; component setup still applies its explicit pair.
- [x] Preserve generated total mass on return to single-body physics. Keep the
  previously configured single-body inertia and use selected-root velocity; this
  is not a momentum-conserving merge. Retained old bodies cease contributing.
- [x] Physical-rig membership: `attachAnimationPhysicsPart(part, parent)` and
  `detachAnimationPhysicsPart(part, includeDescendants = true)` preserve masses
  and inertia and update totals without redistribution. Boundary joints disconnect;
  internal joints and physical artwork remain. `isAnimationPhysicsPartAttached()`
  exposes membership. Accessories keep their own control; detached skeleton bodies
  become Dynamic and are excluded from whole-rig modes/recovery. Reattachment and
  joint creation are explicit. Parts remain owned by the same Sprite.
- [x] Restore membership and mass accounting in active explicit/generated rig snapshots.
- [x] Transfer Parts/subtrees between Sprites with `destination.transferPart(part, includeDescendants = true)`. Preserve public objects, world placement, internal joints and component state; release source membership/bone bindings, allocate destination IDs, and attach to the receiving assembly explicitly. Part-owned artwork moves; source animation assets remain with their Sprite. Transfers require a shared layer (or both off-layer) and explicit Part IK handoff.
- [x] Add capsule geometry through Collider: `setCapsule()/addCapsule()` and
  endpoint/radius queries, with one stable shape ID, both solvers, native/script
  bindings and snapshot support. Uniformly scaled capsules are exact; nonuniform
  scale/shear uses the same curved-outline approximation policy as circles.
- [x] Expose generated constraints through `getConstraintCount()/getConstraint()` and retain
  their handles during mode changes. Query/edit body-local anchors with
  `getAnchorA/B()`, `setAnchorA/B()` and atomic `setAnchors()`. Groove tracks use
  `getGrooveStart/End()` and atomic `setGroove()`; their B endpoint uses `setAnchorB()`.
  Both solvers adopt edits on the next step; snapshots store current geometry.
  Bodies, colliders, mass/inertia and distance/rest settings stay unchanged.
  These edits do not retarget bones or Part IK offsets; live frame integration
  remains in its separate checklist below.
  Verified with Basic/Chipmunk native solves (including locked-space edits and
  sleeping-body wakeup), native/Desktop/Node/browser snapshot regressions,
  headless/no-Chipmunk syntax checks and JSC binding compilation. JSC/iOS runtime
  validation remains part of the broader engine acceptance work below.
- [x] Use configured PDG constraints for explicit limits and translate them under
  reflection. Current supported SCML contains no joint-limit metadata; observed
  animation ranges are never imported as hard limits. Generated pivots impose no
  rotary constraint, allowing full turns. Explicit definitions carry supplied
  min/max angles, and shared constraints retain subsequent edits.
- [x] Preserve retained Part/body/constraint handles through disable/remove and
  membership changes. Disable retains Parts and detaches physical associations.
  Existing locked-space teardown defers to a post-step callback; setup/membership
  and reflection reject at unsafe boundaries before changing live state. Shared
  owner/snapshot/transfer regressions cover retained native/script references.

## Body rotation-speed thresholds and Break events

Implemented independently of rig generation/control on 2026-09-23.

- [x] `PhysicsBody.setBreakAngularSpeed(radiansPerSecond, referenceBody?)`,
  `getBreakAngularSpeed()` and `getBreakAngularSpeedReference()` have matching
  C++, V8, JSC and browser bindings. The setter is fluent, accepts finite
  nonnegative radians/second and uses zero for disabled. 3,000 RPM is about
  314.16 rad/s in either direction.
- [x] Measure absolute speed by default; an optional reference compares
  `abs(body.angularVelocity - referenceBody.angularVelocity)` without a joint.
  The reference must be a different present body in the same layer, or both
  bodies must be unlayered. The link is weak. Removing/destroying its body or
  detecting a world mismatch disables monitoring instead of changing to absolute.
- [x] Sample solved angular velocities after each positive-duration world step,
  before restoring temporary Chipmunk kinematic sweep rates. Detached basic
  bodies sample after `step()`. Peaks between samples are not reconstructed.
  Equality does not trigger; returning at/below the limit rearms the next event.
  Identical settings preserve the latch; changed settings rearm; invalid edits
  preserve both configuration and notification state.
- [x] Deliver `eventType_SpriteBreak` with `reason=physicsBreak_AngularSpeed`,
  `action=action_BodyBreak`, body, optional Part/referenceBody, measured angularSpeed
  and breakAngularSpeed. Part events route through their owning Sprite. Legacy
  joint fields remain compatible and are null/zero on body notifications.
  Detached native bodies can install a native-only `setBreakHandler()` callback.
- [x] Keep notification separate from braking and topology edits. Neither handled
  nor unhandled body overspeed clamps speed, disconnects joints or splits artwork.
  Existing Chipmunk braking/motors and joint-force break behavior are unchanged.
- [x] Save thresholds, reference identities and excursion latches in body/graph
  snapshots. Reject references outside the saved graph and native callback closures.
  Restoration does not repeat the already reported excursion.
- [x] Cover boundaries, both directions, rotating references, owner routing,
  mutation during callbacks, reference removal and snapshots in native/script tests.

Authoritative method references: [C++](../cxx/dox/physicsbody-angular-speed.dox),
[JavaScript](../javascript/dox/physicsbody-angular-speed.dox), and
[Break event fields](../javascript/dox/structpdg_1_1_sprite_break_event.dox).

## Control modes, IK and transitions

| Rig control | Body mode | Target and authority |
| --- | --- | --- |
| Kinematic | `physicsBody_Kinematic` | Desired animation/IK pose supplies swept body targets. Contacts cannot displace the body. |
| Dynamic | `physicsBody_Dynamic` | No animation tracking drive. Forces, contacts and constraints determine the final pose. |
| Driven | `physicsBody_Dynamic` | Desired animation/IK pose supplies bounded drive targets; the solved physical pose remains authoritative. |

- [x] Evaluate clips/procedural modifiers and IK once into a separate desired pose;
  apply kinematic targets and drives before the shared solve, then publish one
  final physical pose to artwork, sockets, attachments, colliders and queries.
  Do not write direct IK over dynamic results after solving.
- [x] Reuse existing rig `addAnimationIK()/setAnimationIKTarget()` desired-pose
  operations, and the independent Part `setIKTarget()/setIKDriveTarget()` contracts.
  Share solving/control infrastructure without assuming a bone hierarchy equals
  a Part-parent hierarchy. Imported rig integration is a separate acceptance item.
- [x] Allow whole-rig, single-bone and subtree changes without replacing bodies or
  constraints. Single-bone selection does not disconnect either end; kinematic
  neighbors can restrain the selected dynamic segment. Keep kinematic-to-kinematic
  joints configured but dormant, restoring solver participation when required.
- [x] Synchronize control state with direct `.physics.setMode()` edits. Recommended
  policy: single-body edits route through the owner's transition coordinator;
  Dynamic releases only that rig-owned tracking drive, Kinematic takes pose
  control. Reject Static for mapped rig bodies initially. Never report stale
  Driven state over a kinematic body. Preserve unrelated controller protections.
- [x] Enforce one drive owner per body. Rig tracking, Part IK drives and manual
  body drives require the [explicit release contract](#drive-ownership-and-explicit-release)
  before a different controller takes over. For manual target updates, the last
  successful `setDriveTarget()` wins without intermediate release or script-owner
  identities. Keep world-space target semantics and reject conflicting ownership
  atomically; a manual drive does not claim to be animation tracking.
- [x] Preserve pose and sampled linear/angular velocity when releasing kinematic
  control. Enabling/disabling a drive preserves physical motion and independent
  loads. Retain drive settings when leaving Driven so reactivation is deliberate
  and inexpensive.
- [x] Add `recoveryTime = 0.5` seconds to recovery-capable mode changes and disable;
  require finite nonnegative values and let zero request immediate takeover. Free
  Dynamic release is immediate; the parameter controls recovery toward animation
  control rather than delaying every mode change. Preserve explicit angular-route
  selection. Keep artwork, bodies and colliders consistent throughout recovery.
- [x] Emit one Sprite recovery-completion event for a completed selection, with
  enough source/selection information for the caller. Use the established Sprite
  animation event pattern (`action_AnimationPhysicsRecoveryComplete` and
  `SpriteAnimationPhysicsRecoveryInfo`). Do not
  emit recovery-start or recovery-blocked events. Contacts that block recovery
  continue through the normal collision event path without duplicate contact
  notifications. A contact does not suppress a distinct completion event.
- [x] Define interrupted recovery and physically blocked deadline handling before
  claiming completion. Expose actual control/body state during recovery and keep
  event continuation consistent. Active-rig snapshots preserve this recovery/completion state. Retain solver associations for as
  long as recovery needs them, then perform the single-body handoff on disable.
- [x] Keep geometric IK success/error distinct from actual physical reach/error.
  A feasible desired pose may be blocked by contacts, limits or insufficient
  force. Reuse body drive-state diagnostics where their meaning remains accurate.
- [x] Specify parent-relative limb tracking and root actuation separately. Favor
  joint-relative actuation for limbs so a character can retain its desired bend
  while falling; do not silently pull every segment toward fixed world targets.
  Any new relative drive must apply appropriate reaction forces/torques and retain
  existing manual world-drive behavior.
- [x] Implement root-name/descendant-count selection, explicit overrides and
  whole-Sprite impulse routing, including the root's own 1 mm fallback body.
  Live reassignment to an included body preserves identities/mass. Selecting a
  previously skipped bone requires disable/select/setup so no hidden rebuild occurs.
- [x] Root detachment selects an attached named root, otherwise the largest
  remaining assembly branch; ties use body definition order. Impulses follow the
  new root. At least one skeletal member must remain until rig disable.
- [x] Reuse `animationRoot_Fixed` / `animationRoot_Follow` with mixed-mode Sprite
  rigs and gameplay movement/rotation targets. Pose/Part queries no longer consume
  a pending movement target before the solve; followed translation does not feed
  back into Driven targets. Follow publishes translation and preserves Sprite
  rotation/scale. The standalone passive adapter retains its all-Dynamic restriction.
  Native regression covers both frame policies, queried edits, scheduled movement,
  root rotation, preserved joints/mass, bounded Driven targets and Dynamic release.
  The separate wheel-and-chains demo exercises this in native V8 and WebAssembly.
- [x] Preserve existing whole-Sprite flipping across drawing, bone/Part queries,
  sockets and collisions. Verify flip-before-setup and live flip behavior; define
  consistent physical reflection/ownership handling. Do not introduce render-only
  mirroring or change ordinary Sprite flipping. Arbitrary animated scaling is a
  separate capability decision, not implied by flip support.

## Snapshots and acceptance

- [x] Restore shared graph identities and bone mapping, skipped-bone
  topology, root ownership, selected modes, drive settings/ownership, desired
  targets, recovery state and actual body state. Save current edited components,
  not stale values from the original generated definition. Native coverage includes
  both setup paths, both resource modes, tagged/untagged streams, edited colliders,
  detached manual drives, attached accessories, malformed records and pending
  recovery/disable continuation. Shared JavaScript coverage exercises the facade.
- [x] Save explicit root overrides, recovery timing/completion state and body
  speed thresholds/reference/notification state. Preserve event continuation
  without duplicate completion or Break events after restore.
- [x] Restore mass membership and component values before exposing the Sprite's
  aggregate mass; rebuild any cache rather than restoring a conflicting second
  total. Preserve the agreed mass handoff through snapshots and rig teardown.
- [x] Stage/validate a Layer restore before adopting it into the live world; preserve
  external graph links and same-scene retained identities where the snapshot
  contract promises them. Initial Layer loads replace scene owners, matching the
  existing snapshot contract. Verify continuation in complete and external-resource
  modes. Do not mark checkpoint 5 complete on generation support alone.
- [x] Cover tagged/untagged records, shared resources, malformed input, repeated
  setup, zero/unknown lengths, root fallbacks, skipped non-root bones, leaf/branch
  geometry and mass sums.
- [x] Verify generated whole-Sprite scaling after mass/inertia tuning, individual
  Part edits, unrelated-body exclusion, atomic invalid-input handling, retained
  native/script references, unchanged velocities and disable-to-single-body mass.
- [x] Test mixed-mode generated membership totals, accessory registration,
  subtree detachment, preserved motion/inertia, internal versus boundary joints,
  retained handles, manual-drive rejection, root replacement and removal/disable.
  Human demo regression covers a 10 kg load, elbow detachment and reattachment,
  dropped-weight floor contact, and recovery excluding detached limbs.
  The dumbbell collider uses local artwork units, and dynamic detached/accessory
  bodies retain physics substeps even while the remaining skeleton is Kinematic.
  Native delayed-frame regressions and browser drop checks verify level-floor
  contact without the excessive rebound or sideways launch.
- [x] Verify named-root precedence, total descendant counts, ties, explicit roots,
  the 1 mm zero-root exception and root-only impulse delivery including world-point
  lever arms. Test unit conversion, unchanged positive root lengths, mass accounting,
  all three agreed bone-length cases and missing leaf artwork.
- [x] Verify default 0.5-second recovery, explicit zero/custom durations, selection
  interruption, one completion event and normal collision reporting for blocking.
- [x] Test all control modes, single/subtree selection across skipped bones,
  Mixed queries, invalid selections, conflicting drive ownership, transitions,
  disabled/paused animation versus continuing physics, forces and contact response.
- [x] Test each controller handoff with and without explicit release, whole-chain
  Part IK release and atomic subtree rejection. Verify last-call-wins manual
  updates across callers, unchanged targets after invalid calls, repeated same-owner
  updates and force/impulse coexistence without releasing the drive.
- [x] Verify animation-plus-IK-driven motion, blocked targets, force/torque caps,
  joint limits, rotation routes/full turns, physical endpoint error and absence
  of duplicate per-tick sampling.
- [x] Verify targeted synthetic rigs and the wheel demo, and benchmark setup,
  steady physics, mode switching and live reflection with 1/10/50/100 rigs.
  See [measurements](../../test/perf_tests/cpp-rig/RESULTS.md) and the
  [validation record](PHYSICS_RIG_VALIDATION.md).
- [x] Grey Guy/Wonky Skeleton live reflection, accessory attachment/detachment,
  mass accounting and arm recovery in `test/js/main.js` (P); PDG bone overlay (B).
  Finite rendering/playback checks pass. Source artwork and original Wonky's
  legacy debug path are preserved. See [coverage audit](RIG_COVERAGE_AUDIT.md).
- [ ] Manual visual acceptance of real-character physical contact/blocking with
  scene obstacles; the reflection/accessory check isolates its bodies from the
  existing bouncing-ball scene.

### Human demo checkpoint — accepted; further work paused

- [x] Establish the full human animation foundation in
  `test/ui_tests/animation_physics_test.js`: a proportioned 16-bone skeleton,
  generated SCML with weight-shift and greeting clips, per-segment silhouette
  Drawings, planted feet, bone-debug toggle and timeline inspection. Includes
  checked desktop/browser playback; see `test/ui_tests/animation_physics_demo.md`.
- [x] Add a 50 kg driven-arm blocker and whole-body ragdoll to the human demo,
  with all 15 joint limits, a wide tilting floor, torso-led assisted recovery,
  shoe clearance, and a fading physical-pose handoff to weight-shift animation.
  Headless checks cover completion, interrupted lifts and both tilt directions;
  desktop and browser checks cover the full demo sequence.
- [x] Add soft/hard pushes at the non-waving shoulder, a wall on the waving side,
  and automatic torso-led recovery into weight shifting with foot IK. Cover
  both strengths on level/tilted ground, hard-push wall contact and interruption.
- [x] Extend the human demo with isolated hand release/restoration, mouse-driven
  manual hand control with explicit release back to Driven, and one-second
  ground-tilt sweeps alongside the original ten-second mode. Verify joint
  continuity, bounded pulling, handoff/interruption and planted-foot IK.
- [x] Add "pose me": held hand/foot IK targets, pelvis translation, torso/head
  rotation, wrist/foot rotation, selectable elbow bend side and existing twist
  artwork. Retain bone lengths and joint envelopes; show unreachable targets.
  Suspend floor planting and competing demo actions while posing; reset to the
  reference stance or blend back to weight shifting with foot IK restored.
  Native/headless regression and browser mouse checks cover posing and return.
  Validation on 2026-09-24: the full native demo and focused pose/ground/twist
  checks pass. Browser mouse checks cover placement, elbow flip, reset and return.
  Follow-up: the full browser sequence now passes. The wave failure came from
  wall-clock checks advancing ahead of throttled simulation. The demo now uses
  simulation elapsed time, and the browser runner uses real time with background
  throttling disabled. Kinematic floor/lift movement uses physics-step helpers;
  recovery no longer estimates a support velocity from a previous frame's duration.
- [x] Correct joint placement and round/blend the adjoining artwork at the
  shoulders, elbows, hips, neck, knees and ankles. Sleeve ownership and wrist/hand
  offsets are tuned. The requested joint transitions are complete for this
  checkpoint; further silhouette polish is a separate deferred enhancement.
- [x] Complete the demo's elbow/knee behavior for the accepted scope. Inward
  arm targets imply forearm twist, select semi-open flipped hand art and reverse
  the elbow range with a smooth physical crossing. Knees use mirrored angular
  limits and IK bend directions derived from the reference leg geometry; they
  do not dynamically reverse their limits like elbows. Additional conditional
  rules are not an outstanding requirement for this checkpoint.

### Deferred demo enhancements

- [ ] Further body-shape and silhouette polish beyond the completed joint fixes.
- [ ] Improve the soft/hard shoulder pushes and the character's response.
- [ ] Add "stand up" as a separate recovery mode, getting up from the floor and
  returning to weight shifting alongside the existing assisted torso-lift mode.
- [ ] Demonstrate a collision-blocked transition back to **Kinematic** in the
  human demo. The existing blocked wave already covers a Driven arm meeting an
  obstacle and resuming its animation after removal. The remaining case is a
  requested Kinematic recovery waiting for clearance before completing. The
  earlier arm prototype's falling-chain regression remains in the native tests
  and keeps recovering children physical until their ancestors settle.
  Last-target-wins remains part of the API and regression coverage; the user
  explicitly excluded it from the human demo's remaining scope.

### Remaining engine acceptance

- [x] Verify the shared public contract on native C++, V8, JSC/iOS and WebAssembly,
  including headless Chipmunk and feature-disabled Basic diagnostics. See the
  [validation record](PHYSICS_RIG_VALIDATION.md) for counts and supported builds.
- [x] Document the permanent solver boundary: animation physics requires
  Chipmunk. Basic supports simple shared bodies/constraints and will not be
  expanded into a complex animation-physics solver.
- [x] Linux ARM64 Docker native validation: four Chipmunk/Spriter suites and
  three Basic/feature-disabled suites. Reproduce with `bash test/docker/physics`.
- [ ] Windows runtime acceptance and Linux GUI/JavaScript runtime acceptance.
- [x] Update authoritative headers and both language references for the implemented
  API; existing wrappers forward the same methods. Regenerate documentation and
  verify defaults, units, signatures, fluent returns and native/script regressions.
  The 2026-09-25 pass changes behavior behind existing signatures; no new binding
  method or generated binding edit is required.

### Separate wheel-and-chains demo

- [x] Add `test/ui_tests/wheel_chains_test.js` and an independent `wheel-chains`
  catalog/browser entry. A Dynamic wheel held by a Kinematic axle carries three
  Dynamic four-link chains and end weights; drag, shake, signed torque, release/regrip, engine
  bone drawing and Fixed/Follow reset controls expose whole-rig movement.
- [x] Use shared Sprite/Part physics, pivots and PDG Drawing artwork. Chain motion
  comes from the solver, with no artificial outward force. Fast angular motion
  reduces the shared rig timestep to limit pivot drift (minimum 1 ms).
- [x] Automated native/browser checks cover mass, finite body state, pivot drift,
  outward extension, Dynamic release, Follow publication and regrip. Browser mouse
  checks additionally exercise dragging, spin and Fixed-frame release.
- [x] Dynamic wheel on a separate Kinematic axle, signed torque controls, coasting,
  bounded braking, live X/Y flips and aggregate rotational readouts. The demo
  releases its external brake before reflecting and recreates it afterward.
  The human demo remains separate.

## Decision status

The previous seven-item list mixed agreed requirements with smaller design and
implementation tasks, making it appear that answered questions remained open.
The original discussion now stands as follows. "Agreed" describes the design;
it does not mean the feature has been implemented.

| Original topic | Status | Recorded outcome |
| --- | --- | --- |
| 1. Whole-Sprite impulses | Agreed | Apply the impulse to the selected physical root. |
| 2. Root selection | Agreed | Explicit override, otherwise `root`, otherwise greatest total descendant count; give the designated root 1 mm physical length if calculated length is zero. |
| 3. Generated geometry | Agreed | Child-point/artwork length rules; capsule radius `0.1 * length`; pivot joints, free unauthored rotation, unlimited constraint strength, breaking/self-collision off and no initial drive. |
| 4. Drive ownership | Agreed | Explicit release between controllers; the last successful manual `setDriveTarget()` wins without release between updates. |
| 5. Recovery | Agreed | Configurable `recoveryTime = 0.5` seconds; completion event only; normal collisions report blocking. |
| 6. Mass and membership | Agreed | Parent mass scales component masses/inertia; child mass edits and attach/detach change the total without redistributing other masses. |
| 7. Overspeed | Agreed | Threshold on any PhysicsBody emits Break; existing Chipmunk braking stays unchanged. |

Automatic full-Dynamic setup, Kinematic/Dynamic/Driven selection, IK as a desired-
pose producer, editable shared physics components and existing flipping semantics
also remain agreed. Do not reopen them because their implementation has unchecked
tasks.

### User decisions complete

All choices from this design discussion are agreed, including explicit drive
release and last-call-wins manual target updates. There are no remaining user
choices in that list. Implementation and the engineering follow-ups below remain;
do not confuse their unchecked status with unanswered user decisions.

### Engineering follow-ups

The following still require technical design or implementation, but they are not
additional user approvals or reasons to keep the original questions open. Keep
them in the implementation checklist and produce concrete API/behavior proposals
where needed. This classification does not claim that their designs are complete.

- Completed: explicit unit conversion, deterministic root ties, reference-artwork
  bounds, missing-art diagnostics and generated capsule placement.
- Completed: whole-Sprite movement/rotation targets and mixed Fixed/Follow control.
- Completed: continuous/finite force and torque routing, stable Sprite-owned IDs,
  root reassignment, snapshot continuation, and current-COM inertia/angular momentum.
  Off-center loads capture the root lever arm at submission. World loads keep
  their frame through flips. Pending loads age while a root is Kinematic without
  exerting force; registration against a Kinematic root returns zero. Component
  load IDs remain independent. The single-body handoff policy remains unchanged.
- Completed: controller ownership, parent-relative actuation, direct body-mode edits,
  and interrupted/blocked recovery. Root changes reject during pending recovery;
  explicit/generated membership edits are implemented and reject during active recovery.
- Recovery events and native/script signatures are implemented. Active-rig
  snapshot continuation is implemented; wider visual acceptance and performance
  measurements remain. Body overspeed events, rearming, reference lifetime
  and snapshot continuation are implemented in their independent section above.

Unchecked items remain engineering follow-ups; completed work is labeled explicitly.
Cross-Sprite Part transfers and explicit destination membership are implemented. Explicit/generated Sprite rigs use
the shared component graph, and active-rig snapshots, mixed control and recovery
are implemented.

## Shared rig and snapshot validation (2026-09-24)

Part-transfer follow-up: `receiver.transferPart(part, includeDescendants = true)`
moves retained objects and Part-owned artwork, preserves world placement/internal
joints, disconnects boundary joints and releases source rig membership/bindings.
Destination rig membership is explicit. IDs are scoped to the new owner; source
animation assets stay with the source. Transfers require a shared layer or both
owners off-layer; active Part IK requires explicit release. Basic/Chipmunk native
tests cover single/subtree transfers, conflict rejection, root reassignment,
detached driven descendants, source teardown and both snapshot resource modes.
Native owner/playback suites pass 2/2. Node Part/pose suites pass 46 tests/1,043
assertions (the GUI-only artwork test is excluded); desktop passes 47 tests/1,068
assertions; browser passes 47 specs/1,071 assertions. Feature-disabled syntax
checks pass. V8/JSC bindings and API declarations are regenerated; this does not
claim a new iOS runtime run.

- Native Spriter playback and physics-owner suites: 2/2 pass. Coverage includes
  both rig setup paths, complete/external resources, tagged/untagged records,
  edited colliders and joints, mixed modes, detached bodies, accessories, root
  selection, aggregate mass and teardown.
- Recovery resumes from a displaced physical pose without early or duplicate
  completion; pending disable also resumes. Truncated graph records leave the
  destination Layer intact. Standalone Sprite replacement remains non-atomic.
- JavaScript animation-pose suites: Node 29 tests/741 assertions; desktop
  29 tests/755 assertions; browser 29 specs/758 assertions. All pass.
- Native, Node and WebAssembly builds pass. Affected translation units pass
  syntax checks with GUI/Chipmunk disabled, both with and without Spriter.
  No new iOS runtime validation is claimed.
- C++/JavaScript references regenerated and active-rig serialization details
  verified in both class pages; Doxygen retains the existing 65-warning baseline.

## Control-stage validation (2026-09-23)

- Native CTest: 11/11 suites; Spriter regression includes 1,592 assertions.
- Desktop JavaScript animation-pose suite: 27 tests, 678 assertions.
- Browser suite: 1,297 specs, 8,153 assertions; no failures.
- Headless Spriter checks pass with and without Chipmunk; JSC bindings and the
  native API example pass syntax checks (no iOS runtime claim).
- Coverage includes atomic selection/ownership rejection, skipped ancestors,
  mode/body identity and mass continuity, sampled release velocity, retained
  loads, relative-drive momentum, angular routes, blocked and interrupted
  recovery, gravity compensation, stopped animation and completion payloads.
- C++/JS documentation regenerated with the existing 65-warning baseline and
  passing topic coverage. Visual sample acceptance and benchmarks remain open.

## Physics integration acceptance — 2026-09-25

- [x] Sprite-owned finite/continuous force and torque IDs, root routing and root
  replacement; component forces remain independent. Registration, cancellation,
  delays/durations, kinematic intervals and snapshot continuation use the existing API.
- [x] Aggregate inertia and angular momentum about the current assembly COM.
- [x] Live X/Y reflection and flip-before-setup for explicit/generated Sprite rigs,
  including edited anchors, rotary limits, asymmetric collision shapes, velocities,
  detached limbs, retained handles, active snapshots and interrupted recovery.
  External angular constraints and locked-solver/pose-callback changes reject atomically.
- [x] Native shared-body and playback tests, headless Chipmunk and feature-disabled
  Basic builds, desktop V8, browser and iOS/JSC animation physics contract runs.
  See the [validation record](PHYSICS_RIG_VALIDATION.md) for final counts and platform limits.
- [x] Separate wheel demo torque, braking and live-flip acceptance in native/browser.
- [x] Dedicated optimized rig-count benchmark: `test/perf_tests/cpp-rig/README.md`.

Animation physics requires Chipmunk by design; the Basic solver supports simple
shared PhysicsBodies/constraints and is not planned to support animation rigs. Arbitrary
live physical scaling and a momentum-conserving single-body merge are separate
capabilities, not additions to this pass. Windows runtime measurements, Linux GUI/JavaScript validation and additional
manual character-contact acceptance are not implied by the completed native Linux
and macOS checks.
The broader MVC, animation-runtime and Drawing/Part artwork backlog stays separate.
