# Animation showcase assets

Run `./test/demo spriter` from the repository root. Let the introductory
zoom complete to see the rock rise over two seconds and begin a gentle slide.

- **Leftmost Wonky:** original `spriter-samples/wonkyskeleton/wonkyskeleton.scml`,
  ordinary playback of Walk, Attack, Crumble and Idle at four-second intervals.
  Completed Attack and Crumble clips restart on each pass through the cycle.
  This preserves the optional Walk point/box tracks, Attack blur, and Crumble's
  changing hierarchy. No editable-pose controller is enabled on this Sprite.
- **Middle Wonky:** smooth Idle/Walk transitions every four seconds, with a
  0.65-second blend. He changes facing after each eight-second pair of clips.
  His head and empty hand follow the mouse only on the side he is facing.
- **Grey Guy:** idle playback plus foot IK on the rising/sliding rock, and
  spring-driven head/arm aiming toward the mouse on his right. A retained
  `pdg.Drawing` sword is attached to his front hand (`front_hand`), and that
  arm follows the cursor. Blade contact gives the spring
  a recoil impulse and briefly flashes the blade/contact point. It does not
  move the OS cursor. Press **I** to toggle his foot IK.

The middle Wonky uses the generated `wonkyskeleton.scml` beside this file.
It contains the original Idle and Walk motion/artwork, omitting Walk-only
debug tracks so it meets the current fixed-hierarchy pose adapter contract.
The original source sample is unchanged, and PNG references reuse its artwork.
Regenerate this asset with:

```sh
python3 test/lib/prepare-wonky-animation-demo.py
```

Controller geometry compensates for Grey Guy's nonuniform hand-bone scales.
New demo clocks, blends and spring updates use floating-point seconds; event
timestamps are converted from milliseconds at the existing event boundary.
The layer zoom duration also uses floating-point seconds.

Run the repeated nonlooping playback regression with:

```sh
./test/unit cpp:pdg-spriter-playback
```

It uses fixed simulation steps on the original Wonky asset to check two plays
each of Attack and Crumble, including restart from zero, intermediate progress,
natural completion, and remaining completed after extra time. It switches
through Walk and Idle between cycles and keeps editable-pose mode disabled.
Check aiming, sword placement, facing changes and the sliding-rock presentation
visually with `./test/demo spriter`.

Press **P** after the rock rises to run an arm physics cycle on the middle Wonky
and Grey Guy: attach a 1 kg accessory, release the arm to Dynamic, reflect X,
detach the accessory, reflect Y and restore facing, then recover to Kinematic and
resume animation. Aggregate mass increases only while holding the accessory.
Bodies are isolated from the bouncing balls for this acceptance check.
**B** toggles PDG's final-pose bone lines and joint markers on these two characters.
Controls are logged to the console.

The original leftmost Wonky remains on Spriter's legacy renderer so its
changing-hierarchy Crumble clip remains valid. Its debug bones are filled green
diamonds using authored bone dimensions. The human demo's Show Bones option and
this demo's B toggle use `setAnimationDebugDraw(animationDebug_Bones)`: PDG lines
and joint crosses from the final pose, including physical detachments. Neither
is a separately drawn demo skeleton.

Rig reflection, membership,
mass and recovery are covered by the animation-pose specs and native Spriter
regressions. The spinning-box collision regression runs in the native
`pdg-physics-owners` unit suite with both solvers.
