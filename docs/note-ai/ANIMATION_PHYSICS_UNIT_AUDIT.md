# Animation and physics units

Reviewed 2026-09-27. PhysicsBody owns physical motion, seconds-based loads,
impulses, inertia and damping. Animated owns programmed movement and spin.
Parts support nonphysical/kinematic mounts; dynamic holding uses shared
constraints and drives. Imported animation rigs require Chipmunk.

## Units and integration

Use layer distance units `U` and application mass units `M` consistently:

| Quantity | Unit |
| --- | --- |
| Linear velocity | `U/s` |
| Angular velocity | radians/s |
| Linear impulse | `M*U/s` |
| Linear force | `M*U/s²` |
| Moment of inertia | `M*U²` |
| Angular impulse | `M*U²/s` |
| Torque | `M*U²/s²` |

Layer coordinates are passed to the physics solver; they are not automatically
SI meters. `applyImpulse` and `applyAngularImpulse` are instantaneous momentum
changes. `applyForce` and `applyTorque` integrate over an explicit duration in
seconds; zero duration contributes nothing. Continuous loads have cancellable
handles. Application points use owning-layer/world coordinates.

SpriteManager converts elapsed timer milliseconds to seconds. Articulated
updates substep desired targets and physics together, then publish final poses.
Playback and procedural clocks advance once across the update. Collision force
uses impulse divided by the actual solved timestep, with zero for a zero step.
Shared Basic and Chipmunk bodies use the same units and load-lifetime contract;
solver approximation and supported rig capabilities differ.

## Verification and references

```sh
./test/unit physicsbody animation_pose part
./test/unit cpp:pdg-physicsbody cpp:pdg-physics-owners cpp:pdg-spriter-playback
./test/rigs human
```

See [body contract tests](../../test/cxx/test-physicsbody.cpp),
[owner/mount tests](../../test/cxx/test-physics-owners.cpp),
[manager scheduling](../../src/sys/spritemanager.cpp),
[rig contract](ANIMATION_PHYSICS_RIG_PLAN.md), and
[platform validation](PHYSICS_RIG_VALIDATION.md).
