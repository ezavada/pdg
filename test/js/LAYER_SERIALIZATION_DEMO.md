# Live SpriteLayer serialization demo

From the repository root:

```sh
./test/demo layer-serialization
```

For the browser:

```sh
./test/demo --web layer-serialization
```

The runner builds and serves the demo. Use `--no-build` to reuse an existing WASM build.

The left layer runs JavaScript motion, scheduled move/rotate sequences, bouncing
physics bodies using the basic solver, and a two-joint Part IK arm. Move the mouse
inside the left IK panel to steer its target; otherwise it follows a moving goal.
Artwork uses portable `pdg.Drawing` objects and needs no external assets.

The right layer starts empty. A `ser_Full` snapshot in `serialization_Complete`
mode creates its sprites, Parts, physics state, colliders and shared artwork.
Subsequent packets use the selected update fields. The transport is an in-process
serialized-buffer handoff, not a network socket or prerecorded playback.

## Update controls

Click the buttons or use these shortcuts:

| Control | Action |
| --- | --- |
| M | Micro: positions/rotation/frame and Z-order (`ser_Micro`) |
| P | Pose + Parts: Micro, sizes and animations/Part state |
| U | Standard: all seven update categories (`ser_Update`); the default |
| 1 / 2 / 3 | Request 5 / 20 / 50 updates per second |
| A | Toggle target animation processing; initially off |
| C | Toggle target collision processing; initially off |
| L | Disconnect/reconnect packet delivery |
| Space | Pause/resume the source simulation |
| R | Send a fresh complete snapshot of the current source |
| Escape | Close |

The second row provides independent checkboxes for Positions, Z-order, Sizes,
Animations / Parts, Motion, Forces and Physics. Hover over a control for its
meaning. Changing selections changes subsequent packets without silently
sending a new initial snapshot. Omitted fields retain their previous values;
they are not reset or cancelled. Updates send selected state, not differences
against a previous packet. Unchecking everything still sends record metadata;
use **L** to stop sending entirely. Pausing the source stops its simulation but
keeps the chosen packet cadence running.

Some fields have shared payloads:

- **Animations / Parts** includes sampled Part transforms, rates and schedules,
  including solved IK poses, as well as Sprite/Layer schedules and playback.
- **Motion** carries programmed movement/spin/growth, rather than body velocity.
- **Forces or Physics** includes the shared root PhysicsBody record: body pose,
  velocity, settings, forces and drives. To exclude those records, uncheck both.
  Disabling Positions alone therefore does not exclude physics body positions.
- **Micro** uses signed 16-bit integer Sprite positions, with fractional pixels
  discarded. It does not carry Part poses. Pose + Parts uses the broader format.

Artwork, Part topology, collider definitions and controller configuration are
established by the initial snapshot. Structural/artwork changes and changes to
Part physics/IK-controller configuration require a fresh initial snapshot.

## Target processing

The two target toggles are independent, and their choices survive incoming
updates and replacement snapshots.

**Animation ON** advances received schedules, constant motion and basic physics
bodies between packets. **Collisions ON** enables contact detection and response.
Collision resolution can separate existing overlaps even with animation OFF;
ongoing physical movement requires animation ON. Both layers use separate basic
solver worlds and do not collide with each other. Bodies leaving the bin with
collisions OFF are clipped to their own display panel.

Source JavaScript motion, schedule restarts and IK goal updates always run only
on the left. A disconnected target with animation ON can finish its received
schedule and continue moving physical bodies, but will not restart source scripts
or generate new IK goals. With both target controls OFF, disconnecting freezes
the received scene. There is no interpolation; low update rates deliberately
look stepped in that mode.

Try **M + A + C**, then **L**, to see a smaller packet stream and local motion.
Use **P** to restore the IK arm's updates. Use **U** or **R** to resynchronize after
experiments; toggling a field off does not remove the state received earlier.

## Measurements and checks

The HUD shows **bytes/sec** as the sum of actual buffer sizes delivered in the
last second, including a complete snapshot if one was sent in that window.
It also shows the latest initial snapshot bytes, latest update bytes, cumulative
bytes, actual updates/sec, requested update rate and packet age. Sizes include
PDG stream headers; no socket/protocol overhead is added. The actual update rate
is bounded by engine ticks and the rendering environment.

**Position gap now** is the largest distance between corresponding Sprite or
Part origins in layer coordinates, excluding the panels' screen offsets. It is
expected to grow when updates omit fields, while disconnected, or when target
processing runs locally. It is a position comparison, not an orientation/scale
comparison or an assertion that every difference is an error.

Finite checks exercise all 128 update-field combinations, bandwidth reduction
with Micro, selective Part transfer, object identity, a disconnected frozen
target, target schedule/body advancement, stopping after another packet, and
independent collision response. Full updates must still restore exact poses.

```sh
./test/demo --automated layer-serialization
test/emscripten/ui_emscripten --no-build --test layer-serialization
```
