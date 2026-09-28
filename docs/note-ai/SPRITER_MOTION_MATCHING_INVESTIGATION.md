# Motion matching with PDG's Spriter implementation

Reviewed 2026-09-27. Scope: 2D rigid Spriter rigs, including future converted Synfig rigs. Motion matching remains a proposed controller; the pose, IK and independent-time transition foundation is implemented.

## Feasibility

Motion matching can sit above Spriter as an animation-selection controller. Build a searchable database of sampled poses and movement descriptors. At runtime, compare the current pose and desired future movement against the database, choose a clip **and time**, and transition smoothly into that sample.

It does not require 3D, motion capture, or a neural network. Hand-authored Spriter clips are suitable, provided they contain enough varied movement to make selection useful. The first implementation should use ordinary weighted nearest-neighbor search. A few idle/walk/run loops may benefit more from a simple state machine or phase-aware selector; motion matching becomes more valuable with starts, stops, reversals, speed changes and varied transitions.

Ubisoft describes matching trajectory, facing, style and foot continuity through a database search. Our proposed 2D adaptation retains this structure with fewer coordinates and PDG-specific constraints. [Ubisoft's motion-matching overview](https://www.ubisoft.com/en-us/studio/laforge/news/VjEIwquaIyEZZSw5RZI0V/drecon-datadriven-responsive-control-of-physicsbased-characters)

## What to index

Preprocess clips using the same bundled Spriter evaluator that will play them. Sample a canonical root pose and record:

| Feature | Role |
| --- | --- |
| Clip ID and sample time | Identifies the selected entry point |
| Root-relative feet, hip and optionally hands | Pose similarity |
| Corresponding point velocities | Distinguishes similar poses moving in different directions |
| Intended speed/facing and future displacement | Chooses motion that follows player/controller intent |
| Foot contact states | Avoids unnecessary support-foot changes |
| Locomotion/action/style tags | Restricts valid candidates |
| Remaining valid continuation | Avoids entering a one-shot at its unusable end |

Use a shared rig definition identifying feet, hips, root and sockets. Angles should use wrapped differences or sine/cosine features. Normalize feature dimensions and weight groups so pixels, velocities and angles do not compete on accidental numeric scales. Clamp normalization denominators for constant features.

For a side-view character, horizontal speed, grounded/airborne state and left/right facing may be more useful than a generic 3D-style facing vector. For top-down cutout art, separate view-direction variants may be necessary: rotating a sideways picture does not create a new perspective. Filter incompatible rigs, visual orientations, parent layouts and image variants before searching. Mirrored candidates require consistent bone/contact mappings.

**In-place animation needs movement metadata.** A walk cycle whose Sprite root never moves has zero measured root trajectory. Do not infer walking speed from that zero. Supply authored speed or a virtual root-displacement curve, or estimate it from labeled planted-foot motion and validate the estimate. Genuine starts/stops need varying displacement curves, not just a constant speed label.

Store contact intervals explicitly at first. Position/velocity heuristics are possible but stylized animation, in-place roots and elevated steps make automatic detection unreliable. Handle cyclic sampling across loop boundaries and exclude unsupported future horizons near nonlooping clip ends.

The research reference uses root-relative foot positions/velocities and future trajectory descriptors; the particular feature set and horizons here should be tuned for the 2D game rather than copied literally. [Learned Motion Matching paper](https://theorangeduck.com/media/uploads/other_stuff/Learned_Motion_Matching.pdf)

## Runtime selection

Construct a query from the current continuous base pose, actual controller velocity and desired future movement. For example, predict positions at several short horizons using the controller's acceleration rules. These are intent estimates, not guaranteed future physical positions. If Chipmunk blocks the character, include actual velocity/contact state so input alone does not keep selecting a full-speed run into a wall.

A starting cost is:

```text
cost = pose_error + velocity_error + trajectory_error
     + contact_mismatch_penalty + transition_penalty
```

Each term is normalized and weighted. Hard constraints such as grounded/airborne mode, allowed attack phase or compatible rig should filter the candidate set instead of relying solely on large penalties.

Always score the current animation's natural continuation. Only jump if another result improves enough to justify a transition. Use hysteresis/minimum dwell and a bounded search cadence, while retaining immediate searches for meaningful state changes. Continue normal playback between searches; do not choose an unrelated pose every rendered frame. Start with a linear scan and profile before adding a spatial index.

Use a small high-level state machine for locomotion, jump, attack and hit reaction. Motion matching can operate inside those legal states. It should not skip weapon windup or repeatedly seek through damage events just to improve pose similarity. No eligible result should fall back to a defined legal animation, not an invalid nearest sample.

## Current foundation and remaining work

`Sprite.sampleAnimationPose(clip, timeSeconds)` provides silent owned samples.
`seekAnimation` selects an explicit time, and `transitionToAnimation` crossfades
to an independently timed destination. Public times are floating-point seconds.
The pose adapter rebuilds descendants and publishes consistent artwork, sockets
and collision geometry; animation IK and shared physical rigs use that foundation.
See the [animation architecture](PDG_ANIMATION_API_EXTENSION_PROPOSAL.md).

The matcher still needs a feature database, normalization, eligibility filters,
search, continuation scoring, contact-aware selection and an application-facing
controller. Inertialized transitions are a possible later extension to the
existing crossfade path. Frequent interruption requires continuity tests, not
another assumed sampling or pose-writeback API.

Feature extraction/search must remain silent. Runtime destination playback emits
subsequent triggers under the transition ownership contract; do not replay
crossed action events merely to inspect candidate samples.

## How IK fits

Motion matching chooses a good *authored movement*. IK adapts the chosen pose to current targets. They are complementary, and either can exist without the other.

```text
Input + Chipmunk/controller state
              |
     predict desired movement
              |
   motion-match clip + timestamp
              |
   sample and smooth transition
              |
  IK / foot locks / hand targets
              |
 rebuild final parts and sockets
              |
  collision-query pose + drawing
```

Use a consistent pose domain for matching: initially query the continuous blended/inertialized base pose before IK, since the database contains authored poses without environmental corrections. Supply contact/target state separately. Matching final IK-corrected joints against an uncorrected database can cause repeated poor selections or oscillation. More advanced candidate scoring can estimate IK correction cost for a shortlist, but is not needed initially.

### Foot planting example

The player releases movement while the left foot supports the character. Search for a stopping sample with similar joint positions/velocities and compatible left-foot contact. Smooth into it. Maintain the left-foot target in world space, and solve the hip/knee chain as the physical root continues decelerating.

Preserve that contact target across animation transitions until release. On moving platforms, store the target relative to the contacted body and reconstruct its world position each update. Release or fade the lock on liftoff, loss of ground or excessive reach error. Cap correction and use limited visual pelvis adjustment if needed; IK cannot conceal an indefinitely wrong movement speed or an impossible stop.

Contact state therefore needs its own continuity/hysteresis. A crossfade should not instantly alternate between two clips' conflicting foot-lock flags. Source contact metadata is a starting point, while real support queries validate it.

### Hands and physics targets

Motion matching can choose a suitable reach, carry or impact-recovery pose. Arm IK then keeps the hand on a moving handle or a spring-driven Chipmunk target. Give overlapping constraints a defined priority—for example support feet, torso adjustment, then hands—and explicit influence weights. For unrelated cosmetic secondary motion, a damped angular offset may be enough without IK.

Matching does not generate physical forces and IK does not enforce physical balance. A full active ragdoll would be a separate controller that tracks the matched pose with joints/springs. That is outside the initial proposal.

Foot locking and simulation/animation synchronization are established companion techniques, but require limits when controller motion differs from the available animation. [Code vs Data Driven Displacement](https://theorangeduck.com/page/code-vs-data-driven-displacement)

## Root ownership and update order

For the first PDG version, retain gameplay/Chipmunk ownership of Sprite root position. Use authored or virtual root movement for matching and bounded playback-rate correction; do not also apply animation root displacement to the same body. Remove extracted root travel from the visual pose where necessary to avoid double movement.

PDG coordinates desired animation/IK targets with articulated physics substeps,
then publishes final poses. A matcher must join that sequence without advancing
playback or emitting events twice. Physically authoritative limbs track desired
targets through drives; post-solve visual corrections must not disconnect their
artwork from the physical shapes.

If actual control consistently exceeds the speed/acceleration represented in the database, accept a bounded visual mismatch, tune the data/controller, or fall back. Motion matching and IK cannot invent missing movement coverage.

## Relationship to Synfig conversion

Converted Synfig SCML can enter the same preprocessing pipeline as native Spriter assets. Preserve canonical bone/socket mappings, clip tags, reference lengths and optionally contact/virtual-root metadata in the converter manifest. Extract features from the **converted Spriter playback** so matching reflects what PDG actually displays, rather than an ideal source pose that conversion approximated.

Keep per-rig databases initially. Cross-character matching requires compatible topology and scale normalization/retargeting; character maps alone do not establish compatibility. Rigs classified as sampled source-constraint motion may reproduce authored playback but are not automatically suitable for arbitrary runtime IK edits.

## Recommended prototype

1. Use one side-view rig with idle, walk, run, start and stop clips plus explicit contact/speed metadata. Compare against an ordinary state-machine baseline.
2. Build an offline feature table and visualize the winning clip/time and individual costs. First confirm selection and natural continuation with hard transitions in a debug-only experiment.
3. Implement independent destination-time transitions, resolve blend units and verify event behavior. This is the main runtime prerequisite.
4. Add one planted-foot two-bone IK chain and compare matching-only against matching-plus-IK.
5. Measure transition frequency, pose/velocity discontinuity, planted-foot sliding, root/foot error, responsiveness and CPU/database memory cost.

Use held-out movement sequences: accelerate, stop mid-stride, reverse, collide with a wall, stand on a moving platform, pause/resume and switch repeatedly during a transition. Test unreachable IK targets, reflected rigs, nonlooping endpoints and event duplication. A useful first success is fewer visible pops and less foot sliding than the baseline without weakening gameplay responsiveness.

This can be phased: pose/trajectory-based clip selection first, true clip-and-time matching once transitions exist, then IK correction. Do not call simple speed-to-clip switching full motion matching.

Related: [Spriter/Chipmunk IK investigation](SPRITER_CHIPMUNK_2D_IK_INVESTIGATION.md), [Synfig rig conversion plan](SYNFIG_TO_SPRITER_RIG_CONVERSION_PLAN.md).
