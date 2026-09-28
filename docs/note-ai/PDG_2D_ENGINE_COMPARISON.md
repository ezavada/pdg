# PDG 2D engine API and feature comparison

Saved from the conversation on 2026-09-27; updated with the motion-matching assessment and ranked worklist. Repository links use relative paths for portability.

Related: [ranked feature worklist](PDG_FEATURE_WORKLIST.md), including impact/difficulty definitions, priority groups, dependencies, and motion-matching prototype and production scopes.

**PDG is competitive in several runtime APIs, but Godot offers the strongest overall coverage for the range of 2D games you described.** Unity leads in several production systems; Phaser is the strongest fit for browser-oriented JavaScript development. PDG’s clearest advantages are its consistent animation interface, editable drawings, and explicit binary state-transfer APIs.

I inspected the current **private development checkout**, which contains substantially more functionality than the README describes. These findings should not be assumed to apply to the public release. This is a source/API comparison, not a benchmark or a full cross-platform validation.

Also, a correction to the earlier assessment: **PDG does have a browser target**, including Emscripten build tooling and browser tests. Its web build disables native networking, so browser support does not imply complete native API parity. See [browser build configuration](../../tools/pdg-js.mak).

“Best” below means my preferred implementation for the stated criterion. I count built-in features and identified official packages, and only functionality usable in 2D.

For graphics, animation, and simulation:

| Feature/API surface | Best choice and criterion | How it compares with current PDG |
|---|---|---|
| **Basic sprite drawing and transforms** | **No decisive winner** | PDG already covers the essential operations. Drawing, moving, scaling, rotating, and animating sprites are not meaningful differentiators by themselves. |
| **Consistent object-motion API** | **PDG — direct, object-oriented control** | The shared `Animated<T>` interface provides movement, rotation, resizing, changing motion rates, easing, and scheduling across multiple object types. It offers unusually consistent semantics without requiring a separate tween object for routine motion. |
| **General-purpose tweening** | **Phaser — breadth and composition** | Phaser supports arbitrary object properties, multiple targets, loops, yoyo, stagger, callbacks, and chains. PDG’s `wait()`/`andThen()` scheduling is convenient but narrower. Godot’s generic property/method tweening is another strong option. [Phaser tweens](https://docs.phaser.io/phaser/concepts/tweens), [Godot Tween](https://docs.godotengine.org/en/stable/classes/class_tween.html). |
| **Editable procedural drawings** | **PDG — retained, individually editable drawing elements** | `Drawing` combines nested artwork, editable control points, element ordering, live attributes, and element hit-testing. That is particularly useful for procedural board pieces, diagrams, and interactive vector-like artwork. The advantage is this integrated abstraction, not exclusive access to drawing primitives. |
| **Low-level rendering customization** | **LÖVE — compact programmable graphics API** | Shaders, meshes, canvases, and explicit sprite batches provide substantially more application-level rendering control. PDG has offscreen rendering and useful drawing attributes, but I did not find a comparable general public shader/material API. [LÖVE graphics](https://www.love2d.org/wiki/love.graphics). |
| **2D lighting and material workflow** | **Unity URP — integrated authoring and rendering** | Its dedicated 2D lights and shadows provide a workflow PDG currently lacks. PDG’s gradients, blend modes, and shaded-sphere helper do not amount to a scene lighting system. Godot is also strong here. [Unity 2D lighting](https://docs.unity3d.com/6000.0/Documentation/Manual/urp/Lights-2D-intro.html). |
| **Tilemaps and terrain construction** | **Godot — combined runtime and editor capability** | Terrain connections, reusable patterns, and integrated tilemap editing reduce both code and content-production work. PDG’s `TileLayer` supplies a relatively basic grid/image-sheet/map-data API. [Godot tilemaps](https://docs.godotengine.org/en/stable/tutorials/2d/using_tilemaps.html). |
| **Skeletal character authoring and deformation** | **Unity’s official 2D Animation package** | Sprite mesh and skinning tools offer a broader character-art workflow. PDG’s rig and Part APIs are substantial, but I did not find an equivalent weighted sprite-mesh deformation and editing workflow. [Unity Skinning Editor](https://docs.unity3d.com/Packages/com.unity.2d.animation@10.0/manual/SkinningEditor.html). |
| **Procedural IK and physical characters** | **Split: Godot for solver variety; PDG for direct integration** | Godot exposes two-bone IK, CCDIK, FABRIK, jiggle, and physical-bone modifiers, although this API is marked experimental. PDG combines pose modifiers, two-bone IK, spring/contact targets, physical Parts, rig-generated bodies/joints, and recovery controls. PDG is competitive here; neither deserves an unconditional win. [Godot modifiers](https://docs.godotengine.org/en/stable/classes/class_skeletonmodification2d.html). |
| **Motion matching for 2D rigs** | **No verified winner in this comparison; a PDG opportunity** | PDG has pose sampling, transitions to a specified clip/time, modifiers, and contact targets, but no motion-matching database/search controller was identified. A production matcher could connect these existing strengths. No engine is credited here merely for having a 3D motion-matching system; usable 2D support would need separate verification. See the motion-matching assessment below. |
| **General 2D physics API** | **Unity — query breadth and tooling** | PDG has substantial bodies, joints, forces, drives, colliders, filters, and contact callbacks. Unity goes further in public raycasts, shape casts, overlap queries, distance queries, and associated inspection tools. I did not find comparable world-query coverage in PDG’s public headers. [Unity Physics2D](https://docs.unity3d.com/6000.0/Documentation/ScriptReference/Physics2D.html). |
| **Platformer character movement** | **Godot — programmable character controller** | `CharacterBody2D` supplies movement-and-sliding, floor/slope handling, and platform behavior. PDG provides lower-level pieces from which to build those policies. Construct is preferable when you want an immediately usable behavior with minimal programming. [Godot CharacterBody2D](https://docs.godotengine.org/en/stable/classes/class_characterbody2d.html), [Construct Platform](https://www.construct.net/en/make-games/manuals/construct-3/behavior-reference/platform). |
| **Particles** | **Godot for visual effects; PDG for individually physical particles** | Godot provides a dedicated GPU particle system with configurable materials and trails. PDG particles can carry `Drawing` artwork, colliders, physics bodies, and child emitters—useful for gameplay debris. These solve different problems: Godot’s GPU particles do not collide with ordinary `PhysicsBody2D` objects. [Godot particles](https://docs.godotengine.org/en/stable/classes/class_gpuparticles2d.html). |
| **Camera behavior API** | **Phaser — convenient explicit 2D controls** | Follow smoothing, deadzones, bounds, multiple cameras, and effects are packaged as camera operations. PDG supports layer translation, rotation, zoom, linked movement, and coordinate conversion, but more camera policy falls to application code. [Phaser cameras](https://docs.phaser.io/phaser/concepts/cameras). |

The PDG side of these judgments comes primarily from [Animated](../../src/inc/pdg/sys/animated.h), [Drawing](../../src/inc/pdg/sys/drawing.h), [Sprite rig/physics controls](../../src/inc/pdg/sys/sprite.h), [Collider](../../src/inc/pdg/sys/collider.h), and [TileLayer](../../src/inc/pdg/sys/tilelayer.h).

For game structure, services, and production work:

| Feature/API surface | Best choice and criterion | How it compares with current PDG |
|---|---|---|
| **Navigation and pathfinding** | **Godot — integrated 2D coverage** | AStar2D/AStarGrid2D and navigation agents cover important strategy and top-down game needs. I found no equivalent PDG runtime subsystem; you would implement or integrate it. [Godot 2D navigation](https://docs.godotengine.org/en/stable/tutorials/navigation/navigation_introduction_2d.html). |
| **Input mapping and rebinding** | **Unity Input System — breadth** | Actions, control schemes, composite bindings, and interactive rebinding sit above raw device events. PDG exposes lower-level input events but lacks a comparable action-mapping layer in the surface inspected. [Unity bindings](https://docs.unity3d.com/Packages/com.unity.inputsystem@1.11/manual/ActionBindings.html). |
| **UI, layout, and localization** | **Godot — complete integrated workflow** | Its controls, containers, themes, and localization support address complex menus and strategy-game interfaces. PDG does have a real MVC/control framework with animated views, clipping, theming, and common widgets; its layout and localization facilities are narrower. Godot also handles bidirectional UI concerns. [Godot internationalization](https://docs.godotengine.org/en/stable/tutorials/i18n/internationalizing_games.html). |
| **Audio mixing and effects** | **Godot — accessible integrated mixer** | Audio buses, routing, effect chains, and meters exceed PDG’s playback, looping, fades, pitch, and horizontal positioning controls. Unity is also strong. For Godot web exports, bus effects require Stream playback rather than the default Sample mode. [Godot audio buses](https://docs.godotengine.org/en/stable/tutorials/audio/audio_buses.html). |
| **Timers and scene time** | **Phaser — coordinated scene clock** | Scene clocks connect timers to pause and time scaling. PDG’s ID-based timer control is useful, but does not establish an overall advantage over coordinated scene-time systems. [Phaser time](https://docs.phaser.io/phaser/concepts/time). |
| **Binary engine-state snapshots and selected updates** | **PDG — explicit runtime-state API** | Full SpriteLayer snapshots and selectable update fields directly support transferring engine-managed state. This is more specialized than ordinary object/JSON serialization. Important limits are explained below. |
| **Adding conventional savegames quickly** | **Construct 3 — least implementation work** | Built-in Save/Load and JSON save-state operations make this a game feature with little plumbing. PDG gives more explicit binary-state control, but the developer must assemble more of the savegame system. [Construct savegames](https://www.construct.net/en/tutorials/savegames-11). |
| **High-level multiplayer** | **Godot — built-in replication facilities** | RPC and scene replication facilities reduce the work between “transport some bytes” and “replicate game objects.” PDG’s networking and serialization are useful ingredients but do not provide an equivalent complete replication layer. [Godot MultiplayerSpawner](https://docs.godotengine.org/en/stable/classes/class_multiplayerspawner.html). |
| **Asset loading and downloadable content** | **Unity Addressables — production breadth** | Asynchronous loading, dependency management, catalogs, and remote content go beyond PDG’s resource lookup, caching, directory/ZIP access, and language selection. Addressables is an official package. [Addressables API](https://docs.unity3d.com/Packages/com.unity.addressables@1.20/api/UnityEngine.AddressableAssets.Addressables.html). |
| **Traditional 2D room and sequence authoring** | **GameMaker — focused integrated workflow** | Room/layer editing and editable sequences let developers construct levels and presentation visually. PDG has runtime primitives but no comparable integrated content editor in this checkout. [GameMaker rooms](https://manual.gamemaker.io/monthly/en/The_Asset_Editors/Rooms.htm), [sequences](https://manual.gamemaker.io/lts/en/The_Asset_Editors/Sequences.htm). |
| **Visual gameplay construction** | **Construct 3 — behaviors and event sheets** | It turns common gameplay policies into configurable features. In PDG those policies usually become application code. This matters most for rapid prototypes and developers who prefer visual programming. [Construct Platform behavior](https://www.construct.net/en/make-games/manuals/construct-3/behavior-reference/platform). |
| **Iteration and deployment workflow** | **Defold — cohesive 2D production pipeline** | Its editor, hot reload, device debugging, profiling, and deployment pipeline are integrated. PDG has build/test tooling, but requires more engineering involvement to obtain a similar development experience. [Defold overview](https://defold.com/product/). |
| **Profiling and diagnostics** | **Unity — integrated production tooling** | In particular, its 2D physics profiler exposes engine-level behavior directly. PDG’s logs, memory instrumentation, benchmarks, and Node debugging are useful, but are not an equivalent integrated profiler experience. [Unity Physics 2D Profiler](https://docs.unity.com/en-us/engine/6000.3/manual/unity2d/2d-physics/physics-2d-profiler). |
| **Browser-oriented JavaScript development** | **Phaser — natural platform fit** | JavaScript/TypeScript and a browser-oriented runtime avoid a native-engine binding/build boundary. PDG’s browser target is real, but its native Node facilities cannot simply be assumed available there. [Phaser overview](https://docs.phaser.io/phaser/getting-started/what-is-phaser). |
| **C++ engine API plus native Node integration** | **PDG — this specific architectural requirement** | Among this group, PDG most directly serves a project wanting both a C++ runtime API and JavaScript/Node access to that runtime, including headless use. This is a narrower advantage than “best scripting support.” [PDG integration description](../../README.md). |

**The PDG wins need some qualification to be useful.**

Its **animation consistency** is a real API-design advantage. A developer can apply the same movement and scheduling vocabulary to sprites, Parts, particles, and animated views. That reduces the number of concepts needed for common work. Phaser wins when animation means orchestrating arbitrary properties and complex repeated sequences; PDG can win when it means directly controlling engine objects.

Its **Drawing abstraction** is particularly relevant to board games and procedural interfaces. A drawing is reusable artwork whose elements remain individually editable and hit-testable. That can save application code compared with reconstructing draw commands or creating a separate scene object for every shape. However, retained Drawing elements currently exclude text, and this advantage does not extend to programmable GPU effects. See [Drawing element types](../../src/inc/pdg/sys/drawing.h).

Its **serialization API** is one of the strongest differentiators. The current implementation can reconstruct sprites, Parts, colliders, physics state, and shared artwork, then send selected categories of updates. But:

- Selected-field updates are **not automatically differences against the previous packet**.
- Scripts and callbacks are not captured as running application logic.
- Structural changes can require another full snapshot.
- Transient particles are explicitly not serializable.
- This does not itself provide interpolation, rollback, or deterministic networking.

Those boundaries are visible in the [serialization demo](../../test/js/LAYER_SERIALIZATION_DEMO.md) and [Particle API](../../src/inc/pdg/sys/particle.h). I would call PDG the strongest fit here for **explicit binary transfer of supported engine state**, while Construct wins for simply adding save/load to a game.

PDG’s **procedural character/physics integration** also deserves more credit than a basic feature checklist would give it. Generating physical bodies from a rig, changing physical control per bone, attaching/detaching Parts, and recovering toward animation are meaningful capabilities. I would shortlist PDG for a game built around physically manipulated characters. I would still prototype the actual character before ranking it above Godot or Unity.

Finally, the board-game-related `Action`, `Request`, and `Update` classes are useful scaffolding, but the central [GameEngine contract](../../src/inc/pdg/app/GameEngine.h) leaves game behavior to subclasses. They should not be counted as implemented rules, AI, or a complete turn-management system.

For choosing between each alternative and PDG, my recommendation is:

| Alternative | Main reason to choose it over PDG |
|---|---|
| **Godot** | You want broad 2D capability—especially tilemaps, navigation, UI, and character movement—with less supporting infrastructure to build. |
| **Unity** | You prioritize sophisticated 2D content workflows, physics queries, input handling, asset delivery, and profiling. |
| **GameMaker** | Your game centers on conventional rooms, sprites, and authored sequences, and editor productivity matters most. |
| **Defold** | You want an integrated Lua-based development and deployment workflow across web and native targets. |
| **Phaser** | The browser is the primary platform and JavaScript/TypeScript is the preferred development environment. |
| **Construct 3** | You want common gameplay and savegame features assembled quickly through visual tools. |
| **LÖVE** | You want a small Lua framework with flexible low-level graphics control and are comfortable building higher-level systems. |

**I would choose PDG when its runtime architecture is itself valuable to the game:** shared C++/JavaScript integration, procedural editable artwork, direct animation/physics manipulation, or explicit engine-state snapshots. For an otherwise unspecified platformer, strategy game, or board game, I would start with Godot and require a concrete PDG advantage to justify the additional application and tooling work.

## Motion matching: fit, readiness, and competitive opportunity

Motion matching belongs beside animation state graphs, with its own work item. It searches authored samples for the **clip and timestamp** that best match the current pose, movement, and desired trajectory. Selecting a walk or run clip from a speed threshold alone is not full motion matching. The underlying pose-database search does not inherently require 3D, motion capture, or machine learning. [Motion-matching research](https://staticctf.ubisoft.com/J3yJr34U2pZ2Ieem48Dwy9uqj5PNUQTn/2EVXGPN6ynTrrJaaAUHmZS/060e223cce6a84e47e925105cac5e17f/Learned_Motion_Matching.pdf).

Its strongest applications are richly animated platformers, brawlers, and character-focused top-down games. It provides much less value for board games, simple frame-based retro animation, or strategy games dominated by small units. Enough authored movement variety is necessary to outperform a straightforward state machine.

The conceptual animation flow is:

```text
Gameplay state and movement intent
                ↓
Legal animation choices: locomotion, attack, jump, etc.
                ↓
Motion matching selects clip + timestamp
                ↓
Transition / pose blending
                ↓
IK, foot locks, procedural adjustments
                ↓
Final displayed pose
```

A state machine still determines which actions are legal. Matching selects appropriate motion within those constraints; IK adapts the selected pose to the environment. A full visual animation-graph editor is not a prerequisite. This diagram describes conceptual responsibilities, not a replacement for the engine's physics/update scheduling contract.

### Existing PDG foundations

The [motion-matching investigation](SPRITER_MOTION_MATCHING_INVESTIGATION.md) separates the implemented foundation from the planned matcher. The current [Sprite API](../../src/inc/pdg/sys/sprite.h) and [implementation](../../src/sys/sprite.cpp) provide:

- `sampleAnimationPose(clip, timeSeconds)`.
- `transitionToAnimation(clip, timeSeconds, durationSeconds)`.
- Pose modifiers, two-bone IK, and spring/contact targets.

The [animation pose specs](../../test/spec/animation_pose.spec.js) include a test for silent sampling/seeking and subsequent authored events. Those tests were inspected, not run for this comparison. These additions remove important prerequisites; they do not constitute a motion matcher. Matcher integration must follow the current desired-target/physics/final-pose schedule and transition event policy.

### Remaining production work

| Addition | Purpose |
|---|---|
| Offline database builder | Sample compatible clips and extract joint positions, velocities, contact states, and movement descriptors. |
| Movement metadata | Supply intended speed or virtual root trajectories for in-place animations whose actual root displacement is zero. |
| Runtime query and search | Combine current base pose, actual movement, and predicted intent; normalize and weight matching costs. Start with a linear search and optimize after profiling. |
| Selection stability | Score natural continuation, require sufficient improvement before switching, and prevent rapid oscillation between samples. |
| Gameplay constraints | Filter incompatible rigs, facing/image variants, and invalid endpoints; preserve legal action windows and defined event behavior. |
| Transition quality and diagnostics | Inspect winning samples and cost terms; measure popping, foot sliding, responsiveness, CPU cost, and database memory. |

For a first version, match against the continuous base pose before environmental IK corrections and supply contact state separately. Keep gameplay/physics ownership of root movement explicit. Motion matching should not silently apply a second root displacement or skip attack events to improve pose similarity.

### Ranking and implementation recommendation

| Scope | Rating | Priority group |
|---|---|---|
| One-rig prototype using existing sampling and transitions; worklist #39 | **C2** | **4:** A4 / B3 / C2 / D1 |
| Production motion matching for compatible 2D rigs; worklist #40 | **C3** | **5:** B4 / C3 / D2 |
| The same production feature if sophisticated character animation becomes a primary strategic focus | **B3** | **4:** A4 / B3 / C2 / D1 |

The baseline ranking uses broad 2D user impact. B3 is an alternative weighting, not a second implementation or an approved change in product direction. The C2 prototype is an experiment, not delivery of the complete production feature.

Prototype before committing to the full animation-graph editor or mesh-skinning pipeline. Use one rig with idle, walk/run, starts, stops, reversals, and explicit movement/contact metadata. Compare against a competent state-machine baseline using held-out movement sequences, wall collisions, moving supports, and interrupted transitions. Measure discontinuities, foot sliding, responsiveness, event correctness, CPU cost, and memory.

If the prototype improves those outcomes, **motion matching + procedural IK + physical rig controls** could distinguish PDG. This remains a competitive opportunity to validate, not a demonstrated category win. See the [ranked worklist](PDG_FEATURE_WORKLIST.md) for the broader investment sequence.
