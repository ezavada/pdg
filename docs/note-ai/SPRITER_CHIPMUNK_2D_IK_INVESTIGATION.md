# Spriter, IK and physics-driven animation

Reviewed 2026-09-27. PDG implements hierarchy-aware pose modification, two-bone
animation IK, independent Part-chain IK, physics target adapters and physical
animation rigs. See the [animation architecture](PDG_ANIMATION_API_EXTENSION_PROPOSAL.md)
and [rig plan](ANIMATION_PHYSICS_RIG_PLAN.md) for scope and remaining work.

## Distinct mechanisms

| Mechanism | Input | Result |
| --- | --- | --- |
| IK | Hand/foot target, lengths, bend side and limits | Joint transforms approaching the target |
| Secondary motion | Impulses, spring/contact targets | Offsets with inertia and damping |
| Active rig | Desired animation/IK plus bodies, constraints and drives | Physical motion tracking the desired pose |

Chipmunk is not an animation-aware IK solver. PDG solves the pose constraints and
coordinates their desired targets with the physical bodies. Impulses and forces
must be integrated into motion; they are not bone angles. Use explicit
PhysicsBody impulse/load operations with the [documented units](ANIMATION_PHYSICS_UNIT_AUDIT.md).

## Ownership and propagation

Pose changes rebuild descendants and publish matching image, socket, attachment
and collision-query transforms. The adapter starts from a fresh base pose; it
does not accumulate offsets from the previous result. Directly changing an
internal Spriter object is not a substitute for the PDG pose APIs.

Animation IK uses `Sprite.addAnimationIK()` on a supported pose rig. Independent
Part-chain IK owns its configured chain and rejects animation-physics mapped
Parts. For physical animation limbs, feed animation IK into rig Driven mode.
Explicit release controls transitions between manual drives and other owners.

Desired targets and physics advance through coordinated articulated substeps.
Dynamic bodies determine final physical transforms; visual-only pose editing
must not leave colliders behind. Root, bone and owning-layer coordinate spaces
remain explicit, including reflected/nonuniform visual transforms. Contacts,
body lifetimes and recovery are coordinated through the shared component APIs.

## Verification

`./test/unit animation_pose part physicsbody` exercises script contracts.
`./test/unit cpp:pdg-spriter-playback cpp:pdg-physics-owners` covers native
handoff, driven endpoints, loads, ownership, contact and recovery.
`./test/rigs human` checks the real asset/controllers; use
`./test/demo animation-physics` for interactive visual acceptance.

See the [handoff/IK coverage audit](RIG_COVERAGE_AUDIT.md) for specific regressions
and [platform validation](PHYSICS_RIG_VALIDATION.md) for verified configurations.
