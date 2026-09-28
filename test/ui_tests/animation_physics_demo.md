# Human animation rig

Run from the repository root with a GUI build that includes Spriter:

```sh
./test/demo animation-physics
```

The demo combines the full human character, authored animation, foot IK on
a tilting ground platform, a physical obstacle for her waving arm, and whole-body
ragdoll with an assisted return to animation. Soft and hard shoulder pushes
demonstrate automatic recovery and contact with a wall on the waving side.
Isolated hand control and mouse dragging demonstrate single-bone release and
explicit handoff between animation tracking and a manual physical drive.
Elbow removal and a 10 kg dumbbell exercise explicit rig membership and mass changes.
Pose me pauses the simulation controls for interactive, held IK poses.

| Key | Action |
| --- | --- |
| 1 | Play the eight-second weight-shift loop |
| 2 | Play the six-second hello wave |
| 3 | Show the neutral reference pose |
| Space | Pause / resume |
| B | Show / hide PDG's animation bone debug overlay |
| C | Show / hide actual capsule colliders and each body's mass in kg |
| P | Enter Pose me / blend back to weight shifting |
| R | Restart the selected clip, or reset the pose while posing |
| [ / ] | In Pose me, rotate the selected hand or foot by 5 degrees |
| X | In Pose me, reverse the selected arm's elbow bend and implied hand twist |
| G | Slow ground tilt: ten seconds per sweep / return to level |
| F | Fast ground tilt: one second per sweep / return to level |
| L | Make only the waving hand limp / restore its previous control mode |
| Drag the waving hand | Pull the arm manually; release to resume Driven animation |
| O | Block the waving arm / remove the blocker |
| D | Release the whole body as a ragdoll; also interrupts recovery |
| U | Lift the torso, restore the pose, and blend back to weight shifting |
| S | Soft push against the right, non-waving shoulder |
| H | Hard push toward the wall on the waving side |
| E | Detach / restore her right forearm and hand at the elbow (viewer left) |
| W | Hold / drop a 10 kg dumbbell in her right hand |
| Escape | Close |

Click or drag the timeline to pause and inspect any point in the selected clip.
The demo opens on the stationary reference pose, with debug drawing off.

**Pose me** captures the current pose, pauses the clip and floor motion, and
switches the attached rig to Kinematic. Drag either hand or foot to place it
with two-bone IK; drag the pelvis to move the body while preserving the four
limb targets; drag the torso or head handle sideways to tilt it. Releasing a
handle holds the resulting pose. L/R labels use the character's own sides.
Select a hand or foot to enable the rotation buttons. Selecting a hand also
enables **Flip selected elbow**, which changes the elbow's bend side and uses
the existing implied-twist hand artwork.

The existing joint envelopes remain active, and bones never stretch. An amber
handle and target marker show when a requested target cannot be reached within
those limits. Posing edits animation targets; it is not a physical grab and
does not resolve collisions with the floor or wall. Floor planting is suspended
so either foot can be lifted. Other simulation actions and clip seeking are
disabled while posing. Restore any detached arm and drop the dumbbell before
entering; an active arm blocker is removed on entry.

**Reset pose** restores the reference stance on the current slope. **Return to
animation** blends the edited pose into weight shifting over 0.5 seconds and
restores the original foot-planting controllers. The floor remains at its held
angle until a tilt control is selected. Bones and capsule/mass overlays remain
available in this mode. These controls use the public pose modifiers and
`addAnimationIK()` API in `test/data/human-rig/pose-control.js`.

**Show capsules + masses** outlines all 16 body colliders in cyan, labels each
body's current mass in kilograms, and shows their total. The overlay reads the
actual capsule endpoints/radii and physical transforms, including the adjusted
pelvis, torso, head and foot shapes. It follows animation, manual dragging,
ragdoll and recovery. Labels use L/R for the character's own sides. Bone debug
can be toggled independently.

**Detach right elbow** releases the forearm and hand together, retaining their
wrist joint. They fall onto the floor independently while the rest keeps its
animation and IK. A held dumbbell belongs to the hand's assembly subtree and
stays connected to the detached piece. The total drops by the removed masses;
the other masses do not change. Capsule labels mark detached bodies as “free”.
**Restore right elbow** deliberately resets the limb beside the upper arm,
registers its bodies again, and recreates the elbow pivot and angular limit.
This reset is demo behavior; the membership API itself never teleports bodies.

**Hold 10 kg dumbbell** creates an independent physical Part, registers it under
the right hand, and connects it with a pivot plus a 1:1 gear that preserves grip
orientation. It raises the original 50 kg character's total to 60 kg. Bounded
angular drives hold the arm against the load, using the demo's 16 kg lifting
target and damped response. **Drop** disconnects the grip and removes its mass
from the assembly; the weight remains physical and collides with floor/wall.
Press again to place the same weight back in the hand. Membership controls are
available while standing, outside recovery and manual-hand control. Whole-body
recovery leaves detached pieces on the floor and resumes the load-bearing arm
drives if the dumbbell is still held.

The headless regression is `./test/rigs human/membership`.

**Slow tilt / Fast tilt** ease from the current slope to +10 degrees, then sweep
between +10 and −10 degrees. Slow takes ten seconds per direction; fast takes
one second, including the initial tilt from level. Pressing the active mode
again returns smoothly to level (up to five seconds for slow, half a second
for fast). Selecting the other speed keeps the current angle and begins its
next sweep from there. Ground motion
continues while the clip is paused, so the timeline can hold an upper-body pose
while inspecting the legs. Bone debug also shows orange ankle-target crosses.

`ground.js` registers one `addAnimationIK()` thigh–shin–foot chain per leg and
updates the targets in `onPreAnimateLayer()`. The targets retain each shoe's
ankle-to-sole offset and rotate around the ground pivot; a post-constraint
modifier aligns the shoes with the slope. PDG's two-bone solver keeps each hip
fixed, so a pre-constraint modifier lowers the pelvis only enough to keep both
targets reachable. It preserves the authored sideways weight shift and leg
lengths. The feet and the rest of the body remain under kinematic control until
ragdoll is selected. The physical floor extends beyond the viewport in both
directions, far enough to catch a full-length sideways fall. Its visible
portion is clipped to the figure panel.

**Limp hand** releases only `left_hand` to Dynamic, leaving the upper arm and
forearm in their current modes. Gravity bends the wrist within its joint limits.
If necessary, the button starts the wave so this is easy to see. Press it again
to recover the hand to its previous Kinematic or Driven mode over 0.5 seconds.
The other bones keep following the clip, including while the hand is limp.

**Drag the waving hand** by its blue/amber ring on the viewer's right. The demo
first releases the upper-arm subtree to Dynamic, then calls the hand's
`setDriveTarget()` with a 60 N force cap, 3 Hz frequency, damping ratio 2.5,
and zero torque so the wrist can rotate freely within its limits. The cursor
offset is preserved at grab time. A line shows the requested target; the hand
can lag behind it or be stopped by joints and obstacles.

Mouse release explicitly calls `clearDrive()` before restoring the subtree to
Driven. Its usual bounded animation drives pull the physical arm back toward
the current clip. This handoff does not teleport it or force it to Kinematic.
Ragdoll, push, recovery and a new blocker sequence release a current grab before
taking control. Single-hand recovery completion is tracked separately from the
whole-body recovery events. The demo does not add a last-target-wins exercise.

**Implied forearm twist** uses the hand artwork as a 2D pose cue: the open waving
hand represents no twist, the resting hand approximately 90 degrees, and the
semi-open flipped variant represents the inward-bending 135–180-degree pose.
Dragging the hand inward across the body selects the opposite elbow bend range;
the same rule is mirrored for both arms and also follows authored pose targets.
The new silhouette follows the supplied thumb-out hand reference.

An elbow crossing between the two projections temporarily admits either bend
direction, then reinstates its 2-degree stop short of straight and 150-degree
flexion limit on the selected side. This avoids applying a reversed stop against
an already bent arm. Near-straight drags use hysteresis; directly backward targets
keep the existing side. Releasing the grab restores animation tracking and its
usual bend direction. The flipped artwork remains until the physical elbow has
crossed back. This is a demo pose convention, not a simulated third rotation axis.

**Block waving arm** restarts the wave and makes the upper arm, forearm, and
hand Driven. A static bar obstructs the lift through normal physics contacts.
Removing it leaves the arm Driven so it can rise toward the animation pose;
pause at the high part of the wave to inspect contact and release. Only this
arm collides with the bar. Ground tilt and foot IK remain available.
Both elbows have mirrored rotary limits that stop extension **2 degrees short
of straight**, keeping physical bending on the natural side of the joint.

The generated rig has a total mass of **50 kg**. `arm-blocker.js` estimates joint
strength from a **16 kg load at the middle of the hand**, with the arm extended
horizontally, plus support for the downstream segments' own mass. This gives
approximately 109, 55, and 13 N·m at the shoulder, elbow, and wrist. These are
drive limits based on the chosen load target, not a measured lifting trial.
The positional and angular drives share each joint's torque budget, accounting
for the positional force's lever arm. Their frequencies are 12, 9, and about
8.5 Hz, with damping ratio 3.5 to reduce contact and release oscillation.
The wrist frequency compensates for the shorter capsule's lower inertia,
preserving its angular tracking stiffness and torque limit.

When the arm contacts the bar, the hand switches to its default resting artwork.
After contact ends, the clip's normal hand selection resumes. A short 0.12-second
contact grace period prevents artwork flicker between adjacent contact samples.

**Soft push / Hard push** apply a short force to the torso at the right shoulder
pivot (the viewer's left), directed toward the viewer's right. A visible arrow
marks the push point. The rig becomes Dynamic so the force and its torque move
the body through its existing joints. Soft uses 80 N for 0.18 seconds and starts
recovery after 0.25 seconds; hard uses 650 N for 0.22 seconds. These are demo
settings for the 50 kg rig. The hard push reaches a static wall on the waving
side, then starts recovery 0.35 seconds after contact. A 1.8-second fallback
starts recovery if another pose or obstruction prevents reaching the wall.

Both pushes automatically use the torso-led recovery described below. The leg
IK targets remain at the original stance on the current ground slope; joint
drives return the feet to those targets, lower the soles onto the floor, and
blend back into weight shifting. The soft push stays clear of the wall.
Clip controls and further pushes are disabled until recovery finishes. D cancels
automatic recovery and leaves a ragdoll; U starts recovery immediately.

**Ragdoll** removes the blocker, pauses the clip, and releases all 16 bodies.
The floor moves with the displayed ground. The foot colliders fit the traced
soles. The `capsuleTuning` settings in `ragdoll.js` adjust the reference colliders:
the head is 16 cm wide and 26 cm tall (including its rounded ends), moved 1 cm
up from the original fit; the neck is 5 cm wide; the torso radius is reduced by
3 cm; and the pelvis is moved 5 cm down and 2 cm toward her anatomical left
(the viewer's right).
Both hand capsules are 30% shorter end to end, keeping their widths and centers.
These adjustments retain the bone positions and masses. Inertia is recalculated
for the final shapes and masses before sizing the recovery drives.
For this female demo rig, the torso and pelvis exchange their generated masses:
the pelvis is approximately **3.32 kg**, and the torso **2.60 kg**. The total
remains 50 kg.
The code-only `femaleRig` setting in `human.js` enables this profile. Set it to
`false` to use the original torso/pelvis mass distribution.

**Recover** is an assisted lift, not a get-up animation. A force-limited pivot
pulls the top center of the torso (the neck base) toward its original reference
position, with 5 cm of temporary clearance so the dangling shoes can unfold
above the floor. All limbs remain Dynamic during the lift. Once the torso arrives,
joint drives restore the reference pose while the lift continues supporting it.
The pivots retain bone lengths, so this stage uses angular drives rather than
also pulling the body centers toward position targets. Hip and ankle drives
allow for supporting the whole body, not just the mass below each joint.

Once the pose is close, the support lowers her onto the floor. When every bone
is within 2 cm and 5 degrees of the standing reference pose, the demo
captures the physical pose and transfers control to Kinematic. It fades that
captured pose's influence to zero over 0.5 seconds while transitioning to the
playing `weight_shift` clip. Foot IK runs after this blend. Drive strength is
not faded while it still supports the character. The normal physics-recovery
event reports the control handoff; animation-blend completion marks the end of
the demo's recovery sequence. Resting hand art is used throughout recovery.
Press D to interrupt any stage.

`joint-limits.js` installs mirrored rotary limits on all 15 connections. These
are practical envelopes for this frontal 2D character, not anatomical 3D ranges:

| Connection | Range |
| --- | --- |
| Pelvis to torso | ±25° |
| Torso to neck | ±20° |
| Neck to head | ±25° |
| Shoulder | 150° outward lift and 25° inward from the bind pose |
| Elbow | 2°–150° flexion on the side selected by implied twist; temporary crossing range during a change of side |
| Wrist | ±55° |
| Hip | ±75° from the bind pose |
| Knee | 0°–150° flexion, with mirrored bend directions |
| Ankle | ±50° from the bind pose |

Recovery and subsequent animation targets are clamped to these envelopes. The
initial traced reference silhouette is preserved before the first recovery.
Bone debug marks the torso lift point in blue during recovery.

## Character and assets

`test/data/human-rig/human.scml` is a generated, editable Spriter SCML project.
Its 19 transparent PNG assets are included in the adjacent `images` directory,
so the project also displays its silhouette artwork when opened in Spriter.
The outlines are extracted from the rightmost stationary figure in the supplied
second image, preserved as `test/data/human-rig/reference.jpg`. This includes the
bob haircut and hair gaps, sleeve corners, shirt-waist notches, cropped trouser
hems, ankles, hands and shoes. The two sides retain their original asymmetry.
The figure is assigned a height of 170 cm, and the reference view uses the
source image's pixel scale (518 pixels tall). Bone-local coordinates use cm.

The skeleton has 16 bones: a pelvis named `root`, torso, neck, head, paired upper
arms, forearms, hands, thighs, shins, and feet. Shoulder, elbow, hip, and knee are
joint locations, not segment names. Left/right always mean the character's own
sides; her left hand waves on the viewer's right. The hand contours retain the
source image's finger shapes, without separately articulated fingers or toes.
Both wrist joints sit 3 cm toward the elbow from the original traced landmarks.
The forearm and hand cutouts meet at those pivots, including the open and
semi-open hand variants, while the assembled reference silhouette is retained.

The `reference` clip establishes the bind pose. `weight_shift` moves the pelvis
between two resting stances with a small counter-rotation of the torso and head.
`wave_hello` raises the left arm, waves at the wrist/forearm, lifts the greeting,
and lowers the arm. At full reach, the waving shoulder rises 4 cm on the viewer's
right and the head tilts 6 degrees toward the viewer's left. These accents ease
in with the high reach and ease out as the arm lowers. The wrist swings about
10 degrees each side of alignment with the forearm, in phase with the forearm's
wave; the resting hand bend returns during lowering.
Both clips loop back to their initial poses. The SCML's leg poses are baked with
fixed ankle positions for standalone playback. The demo layers runtime IK over
them to plant the feet on its moving ground.

The wave switches to an open hand at **0.27 seconds**, then returns to the resting
hand at **5.22 seconds**. The open hand is traced from the first waving figure in
the same reference image. These are discrete image keys in the SCML. The demo's
hand drawable callback selects the corresponding retained Drawing from the
current animation time, so seeking backward, restarting, and changing clips
also select the correct hand. The fingers remain part of a single hand cutout.
The open waving artwork is inset 1 cm toward the wrist; the semi-open cross-body
artwork is inset 2 cm on both sides. These drawing offsets also set the PNG/SCML
pivots and leave the skeleton and physical capsules in place.

The demo creates one retained `pdg.Drawing` per artwork variant, using
`Drawing.addPolygon()`. Polygon coordinates use millimeters, and the PNGs use
one pixel per millimeter;
an `Attributes.scale(0.1)` transform places the Drawings in rig centimeters.
This preserves traced detail with the existing polygon point filtering.
The demo attaches each Drawing with `Sprite.addAnimationDrawable()` at
`animationDraw_ReplaceSlot`. All segments use the same silhouette fill. The
pelvis has a rounded underside extending to the crotch. Shoulders, elbows,
wrists, neck, waist, knees, and ankles have rounded ends shared by the adjoining
pieces, plus a narrow overlap along internal seams. The initial joint extensions
stay inside the resting silhouette. Both upper torso sides
widen continuously toward the shoulders. Both sleeve undersides belong to the
upper-arm artwork, so lifting either arm reveals the cuff and the torso edge
underneath. Bone debug
uses the existing `setAnimationDebugDraw(animationDebug_Bones)` API.

Both inner upper-arm edges and elbow ends use fitted cubic curves based on the
marked corrections. These replace the old cut boundaries and join the retained
edges with matching tangents. The forearm's elbow cap similarly flows into its
two existing sides. Sleeve and wrist details retain their traced contours.

`reference-trace.js` stores image-coordinate contours, joint landmarks and a
source comparison mask. `human.js` converts those contours to each bone's local
frame for both PDG Drawings and PNGs. `generate.js` authors the clips and
rasterizes the outlines for Spriter. `hand-twist-art.js` supplies the smoothed
semi-open hand contour, mirrored for the other side; these two extra assets are
selected by the runtime twist rule. Regenerate the SCML and images with:

```sh
tools/node test/data/human-rig/generate.js
```

To redo the image extraction or adjust the anatomical split/joint landmarks,
edit and run `python3 test/data/human-rig/trace-reference.py` first. It uses macOS
`sips`, or Pillow on other platforms. This dependency is only for retracing;
ordinary SCML/PNG generation still uses Node alone. The extraction isolates the
connected near-black silhouette and excludes the ground between the shoes.

## Verification

Omitting `--wait` plays both full cycles, checks all 16 bones and drawings,
checks planted-foot drift and visible hip/hand motion, exercises bone debug,
then seeks across both hand-swap boundaries in both directions and changes clips.
Ground tilt runs during playback; paused checks also sample nine slopes from
−10 to +10 degrees, verifying ankle positions, shoe angles and unstretched IK.
It also checks driven-arm contact, the resting hand on contact, joint
separation, the 50 kg total, and the arm lifting with open-hand art after release.
Finally it releases the whole ragdoll, checks floor contact, recovers it, and
checks the return to the playing weight-shift clip and its planted feet.
It then applies both shoulder pushes, requires wall contact only for the hard
push, and verifies two more automatic recoveries with feet on their IK targets.
It releases and restores only the hand, pulls it with a manual drive and hands
control back to the rig, then checks three one-second tilt endpoints. Joint
continuity and foot IK are checked throughout these stages.
It finishes by entering Pose me, dragging and releasing a hand, checking that
the pose holds, then returning to animation with the feet planted again.
It exits with a nonzero status on failure.

The C++ Spriter suite also runs the human blocker at 5, 10, 16, 33, and 47 ms
animation intervals, checking contact, joint continuity, release, and settling.
Active physical rigs subdivide delayed physics ticks to at most 10 ms; rigs
with more than eight bodies use at most 5 ms. Articulated rigs also receive
additional solver passes to propagate contact and recovery-motor impulses.

Run all rig checks, or select an individual human-rig regression:

```sh
./test/rigs                         # all rig regressions
./test/rigs human                   # all human-rig checks
./test/rigs human/reference
./test/rigs human/ground
./test/rigs human/blocker
./test/rigs human/ragdoll
./test/rigs human/pushes
./test/rigs human/hand
./test/rigs human/twist
./test/rigs human/pose
./test/rigs human/membership
```

The reference check loads the generated SCML through PDG, verifies that Polygon
retains every traced vertex, and compares the assembled pose against the extracted binary
silhouette at original resolution. The smoothed arm corrections yield 99.66%
overlap with the original 42,374-pixel mask (8 missing and 134 additional pixels).
The check allows at most 0.5% difference for these contour refinements. It compares
silhouette masks, rather than JPEG edge colors or the background.
The same check samples eleven articulated poses, including a pose with both arms
raised, checking solid coverage at the joints and crotch and checking that no
body piece becomes disconnected.

The ground check verifies sweep timing and toggle continuity, then checks actual
sole contour points against the surface across all three clips and five slopes.
It also checks unchanged leg lengths and restoration of the level reference pose.
The push check exercises both strengths on level ground and ±10-degree slopes,
including a raised waving arm, actual wall contacts, recovery events, final IK
placement, and cancellation of automatic recovery.
The hand check combines an abrupt drag with fast floor motion, checks bounded
force and wrist continuity, rejects a rig takeover without manual release,
and verifies restoration and interruption. The native physics-owner regression
also pulls against a fixed pivot: continuous forces must enter Chipmunk's
velocity solve rather than moving bodies apart before the joints react.
The twist check exercises inward bends on both arms, hand-variant selection,
joint continuity through the change of bend direction, release back to animation,
and whole-body recovery after an interrupted inward grab.
The pose check covers both arms, a raised foot, pelvis/torso/head edits, joint
limits, unreachable targets, held poses, elbow reversal, wrist rotation, reset,
smooth return, and repeated entry on a tilted floor.

The shared `test/ui` catalog includes the demo. In the browser, use
`test/ui.html?test=animation-physics`; add `&automated=1` for the finite check.
Rebuild the WebAssembly test runtime after regenerating assets, since SCML and
PNG files are embedded in that runtime. Run its browser check with:

```sh
./test/emscripten/ui_emscripten --no-build --test animation-physics
```
