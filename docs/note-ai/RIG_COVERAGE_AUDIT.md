# Rig handoff and IK coverage — 2026-09-25

The two remaining engine handoff/IK checkboxes were broader than the missing
coverage. Most cases already had regressions; they are now checked with the
following evidence rather than left open as new implementation work.

| Contract | Executable coverage |
| --- | --- |
| Rig/manual takeover requires explicit release; whole-rig/subtree rejection is atomic; last successful manual update wins; invalid updates preserve targets | `animationPhysicsControl()` in `test/cxx/animation-physics-control-tests.inc`; `test/spec/animation_pose.spec.js` |
| Part IK owns the entire chain; raw clear/mode/manual takeover rejects; explicit clear releases peers; manual-to-IK rejects before partial installation | `drivenPartIK()` in `test/cxx/part-ik-tests.inc`, Basic and Chipmunk, with/without a tip body |
| Repeated Part IK targets preserve captured offsets after impulses; invalid replacements preserve controller; actual endpoint governs reached state | `drivenPartIK()` (including both snapshot resource modes) |
| External forces/impulses coexist with drives | `drivenPartIK()`, `physicsSprite()` in `test-spriter-playback.cpp`, and new `animationIKDrivenControl()` |
| Animation IK feeds desired physics targets without teleporting the final pose; physical endpoint converges and follows later target changes | New `animationIKDrivenControl()` |
| No duplicate time integration or query-driven resampling | `physicsSprite()`, `scheduledPartIK()` in `test-physics-owners.cpp`, and new `animationIKDrivenControl()`. Legitimate speed-limited solver substeps sample separately; summed elapsed time is exact. |
| Force/torque caps, shared joint limits, full turns, shortest/directional routes | `animationPhysicsControl()`, `drivenPartIK()`, `test-physicsbody.cpp` |
| Blocked targets and collision-blocked Kinematic recovery stay physical until clear; completion happens once; interruptions do not emit success | `animationPhysicsControl()` contact/recovery regressions |

Animation IK on imported rigs and Part-chain IK are different controllers.
Part-chain IK intentionally rejects mapped animation-physics Parts; use
`addAnimationIK()` plus rig Driven mode there. Whole-chain release tests cover
independent Part IK, not an unsupported controller combination.

New coverage added in this pass: explicit subtree takeover rejection,
manual-to-Part-IK rejection/release, and the combined animation IK + Driven
physical endpoint, external loads, repeated target and sampling path.

## Real characters

Run `./test/demo spriter` for the adapted Wonky Skeleton and Grey Guy's live
reflections, 1 kg accessory attach/detach, aggregate mass and arm recovery.
P runs the physical cycle; B toggles PDG bones. Aiming, sword placement and
presentation are checked visually. Shared rig contracts are covered by the unit
suites above; manual real-character obstacle/contact acceptance remains separate.

`./test/unit cpp:pdg-spriter-playback` checks two complete Attack/Crumble cycles
on the original Wonky asset using fixed simulation steps, including restart,
intermediate progress, natural completion and staying stopped afterward.
`./test/unit cpp:pdg-physics-owners` includes spinning-box contacts with both solvers.

`./test/rigs human` runs the nine human-rig integration checks for reference
artwork, ground IK, blocking, ragdoll recovery, pushes, hand control, twists,
pose editing and membership. See [rig checks](../../test/rig_tests/README.md).

## Linux

`test/docker/physics` provides a repeatable
Ubuntu 24.04 native ARM64 run with a read-only checkout and isolated build volume.
It runs four Chipmunk/Spriter targets and three Basic/feature-disabled targets.
Fresh Linux builds exposed and now fix a missing `<cstdint>` include, bundled PNG
configuration, and propagated JPEG/zlib/OpenSSL native link dependencies.

Animation physics requires Chipmunk permanently. The Basic solver remains for
simple shared-body use; it is not a future animation-rig backend. Linux desktop
and JavaScript runtime testing, and Windows runtime testing, are not implied by
these native headless results.
