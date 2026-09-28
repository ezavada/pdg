# Wheel and chains

A separate physics demo: a 12 kg wheel with three four-link chains attached at
120-degree intervals. Each link weighs 0.5 kg and each end weight is 2 kg, for a
24 kg assembly. Distances are centimeters; gravity is 981 cm/s².

Run from the repository root:

```sh
./test/demo wheel-chains
```

Browser: `./test/demo --web wheel-chains`. Use `--no-build` to reuse an existing
WebAssembly build.

| Control | Action |
| --- | --- |
| Drag wheel | Move the supporting axle smoothly |
| + / − | Add/subtract 10 N m of motor torque, between −120 and +120 N m |
| C | Remove motor torque and coast |
| K | Apply a brake limited to 120 N m |
| Space | Pause / resume the demo |
| S | Shake the axle sideways |
| D | Release the assembly, or catch its axle at the current position |
| B | Toggle engine bone debug drawing |
| X / Y | Flip horizontally/vertically in the Sprite's frame |
| F | Switch Fixed/Follow frame policy and reset |
| R / Escape | Reset / close |

The wheel and chains are Dynamic. A pivot to a separate Kinematic axle holds the
wheel's center while allowing it to turn. The controls register sustained torque
through `sprite.physics.addContinuousTorque()` and remove its handle when torque
changes. Positive torque turns clockwise. Opposing torque slows a spinning wheel
and eventually reverses it; zero torque preserves momentum, with ordinary damping
and gravity still acting. Braking uses a zero-rate motor with a finite torque cap.
In centimeter units, one N m is 10,000 kg cm²/s².

There are no outward forces or chain animation targets. The joint constraints
supply the centripetal acceleration that turns the chains. At sufficient speed
they extend against gravity; their changing configuration affects acceleration.
The readout displays the whole assembly's instantaneous inertia and angular
momentum about its center of mass, in kg m² and kg m²/s.

Flipping reflects actual bodies, velocities, artwork, collider frames, and live
joint anchors. The demo explicitly releases and recreates its outside axle/brake
constraints around the flip, keeping the supporting axle at the wheel center.
Registered torque retains its world direction, so it may oppose the reflected
spin. The engine preserves internal component and constraint identities.

The white cross marks the Sprite frame. Follow publishes wheel translation;
Fixed leaves the frame independent. Neither policy follows wheel rotation.
Release removes support and motor torque, preserving solved motion. Links may
pass through one another because self-collisions are disabled; the floor is physical.

`test/data/wheel-chains/generate.js` produces the reference-only `wheel.scml`.
`rig.js` configures shared bodies/constraints and PDG Drawing artwork. Pivot
measurements read live constraint anchors, including edits made by reflection.

Omit `--wait` for the finite native check, or run from the repository root:

```sh
./test/emscripten/ui_emscripten --no-build --test wheel-chains
```

Checks cover movement, shaking, torque-driven extension, finite states, joint
continuity, mass, reflection, bounded braking, release, Follow publication, and
regrip. Native regressions also cover Fixed/Kinematic/Driven control, force timing
and cancellation, reflected recovery, and active-rig snapshots. See
[the native benchmark](../perf_tests/cpp-rig/README.md) for rig-count measurements.
