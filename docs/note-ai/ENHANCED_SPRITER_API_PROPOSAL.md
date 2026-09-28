# Spriter integration status and remaining work

Reviewed 2026-09-27 against the current source checkout. Public signatures and
contracts live in the [Sprite header](../../src/inc/pdg/sys/sprite.h) and the
[animation reference](../cxx/dox/animation.dox). Implementation and
acceptance work is tracked in the [animation checklist](PDG_ANIMATION_API_EXTENSION_CHECKLIST.md),
[API change list](ANIMATED_PART_API_CHANGE_LIST.md), and
[rig plan](ANIMATION_PHYSICS_RIG_PLAN.md).

## Implemented integration

PDG loads SCML through SpriterPlusPlus, shares models within a layer and keeps
per-Sprite playback state. It supports character maps, animation selection,
phase-aligned blending, named attachment points and authored collision-box queries.
`activateSubEntity` selects an entity; it is not a general nested-entity editor.

For supported fixed-hierarchy assets, the PDG pose adapter provides owned pose
snapshots, binding queries, silent sampling, seek, independent-time transitions,
typed variables/tags, modifiers, IK, custom Drawing attachments and debug drawing.
Authored SCML eventlines dispatch named trigger events with seconds-based times.
Part artwork, colliders, shared PhysicsBodies/constraints, explicit/generated
rigs, control handoff, recovery, membership and snapshots use PDG's shared APIs.
Imported animation physics requires Chipmunk.

The adapter does not accept changing track presence or hierarchy. Ordinary
playback still handles assets such as the original Wonky Crumble clip. PDG-owned
clip evaluation remains planned; SpriterPlusPlus still performs runtime sampling.

## Separate backlog

These capabilities need their own implementation and acceptance work:

- SCML-authored soundline playback and events. The sound UI fixture plays PDG
  sounds explicitly; it does not supply a Spriter audio adapter.
- SCON and texture-atlas loading. The PDG file factory does not implement them.
- Explicit model/entity preloading and broader nested-entity management.
- Metadata access outside the supported pose-adapter topology.
- Additional state/constraint overlays and measured cache/pooling improvements.

Do not infer public methods or event constants from possible future designs.
The [feature worklist](PDG_FEATURE_WORKLIST.md) and
[owned playback plan](ANIMATED_PART_API_CHANGE_LIST.md#pdg-owned-animation-assets-and-playback)
record broader priorities.

## Verification

```sh
./test/unit spriter_playback animation_pose spriter_animblend spriter_attach spriter_collisions spriter_events
./test/unit cpp:pdg-spriter-playback cpp:pdg-animation-pose
./test/rigs
./test/demo spriter
```

Select `--node`, `--web --automated`, or `--ios` on script unit runs to validate
another runtime. Availability depends on the build; a pass on one target does
not establish platform parity. See the [testing guide](../../test/README.md).
