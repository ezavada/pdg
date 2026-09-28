# Animation timing API audit

Reconciled 2026-09-25: the Animated/PhysicsBody timing migration is complete.
Public animation methods, stepping, helpers, easing and inherited fades/zoom use
floating-point seconds. Force/torque timing now belongs to PhysicsBody, with
explicit impulse methods and interval integration. Fractional values are tested
through native and script contracts.

Authored triggers expose clip-relative `timeSeconds` and update-relative
`offsetSeconds`. `frameTime` remains a compatibility millisecond field;
`SpriteLayerInfo.millisec`, TimerManager and OS clocks retain scheduler units.
Audio duration APIs are separate from this animation migration.

Current evidence: [Animated](../../src/inc/pdg/sys/animated.h),
[helper callback](../../src/inc/pdg/sys/ianimationhelper.h),
[event fields](../../src/inc/pdg/sys/events.h),
[Animated tests](../../test/cxx/test-animated-contract.cpp), and the
[completed migration checklist](PDG_ANIMATION_API_EXTENSION_CHECKLIST.md#floating-point-seconds-consistency).

## Current boundaries

Animation methods, helper callbacks and easing functions accept fractional
seconds. `blendToAnimation` uses seconds; playback/blend progress values are
normalized fractions. Movement, spin, growth and stretch rates are per second.
Frame indexes are integer identifiers; frame animation rates are frames/second.

TimerManager and internal scheduler ticks retain milliseconds. Convert elapsed
timer values once when passing them to animation APIs. Audio timing remains a
separate API contract. Serialized compatibility fields and the Spriter evaluator
may use milliseconds internally; those units do not change the public animation
contract.

Run `./test/unit animated animated_programming animated_chaining spriter_playback`
and `./test/unit cpp:pdg-animated-contract` for focused timing coverage. Use
`--node`, `--web --automated`, or `--ios` for script coverage on another runtime.
