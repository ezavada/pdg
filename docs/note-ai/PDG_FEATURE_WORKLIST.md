# PDG feature worklist: user impact and implementation difficulty

Status: proposed priorities, not an implementation commitment.

Last reviewed: 2026-09-27.

Based on the [2D engine comparison](PDG_2D_ENGINE_COMPARISON.md), the current private development checkout, and the subsequent motion-matching assessment. Scores are engineering judgments, not measured user-demand scores or calendar estimates. Broad 2D use and browser support receive substantial weight.

Prioritize features that reduce everyday game-development work, then extend PDG's existing strengths in animation, procedural artwork, and state serialization. Matching every competing editor feature would be a much larger investment.

## Scoring and priority order

| Impact | Meaning | Difficulty | Meaning |
|---|---|---|---|
| **A** | Broad benefit or removes a major adoption barrier | **1** | Small, localized extension using existing infrastructure |
| **B** | Substantial benefit to several game types | **2** | Bounded feature with moderate implementation and integration work |
| **C** | Valuable to a narrower audience | **3** | Significant subsystem or cross-platform architectural work |
| **D** | Low incremental benefit relative to alternatives | **4** | Major new system, extensive tooling, or difficult correctness requirements |

Difficulty includes C++/JavaScript exposure, applicable browser support, documentation, and meaningful validation. Features that depend on another addition assume that prerequisite exists; their scores do **not** include its entire cost. Scores must be reassessed if scope, runtime support, or implementation assumptions change.

The requested ordering is:

**A1 → A2/B1 → A3/B2/C1 → A4/B3/C2/D1 → B4/C3/D2 → C4/D3 → D4**

Equivalently, assign A=1, B=2, C=3, D=4 and compute priority group = impact value + difficulty − 1. Items in a group have equal priority under this rule; dependencies can determine implementation order. These are priority bands, not release-sized batches. An A4 editor and a B3 networking feature share a band but represent different commitments.

IDs #1–38 preserve the original ranked list. #39 and #40 add the motion-matching prototype and production feature in their appropriate priority groups. IDs are stable references, not a strict execution order. All items below are proposed additions or extensions; references to existing capabilities identify foundations rather than completed worklist items.

## Priority 1: A1

No defensible A1 feature addition was identified in this comparison. Broadly transformative additions require more than a localized change. Useful small improvements are scored B1 rather than inflating their impact.

## Priority 2: A2 + B1

| ID | Score | Specific addition | User benefit and scope |
|---|---|---|---|
| 1 | **A2** | **Input actions and rebinding** | Named actions such as `jump`, `select`, and `pan`; keyboard/mouse/touch bindings; pressed/held/released state; input contexts; saved overrides. Games stop hard-coding device events throughout their logic. Gamepad backends are separate in #21. |
| 2 | **A2** | **Camera controller** | Target following, smoothing, deadzones, world bounds, look-ahead, screen/world conversion, and pixel snapping. Build on existing layer transforms. Split-screen rendering is outside this initial scope. |
| 3 | **A2** | **Composable tween sequences** | Repeat, yoyo, parallel groups, stagger, completion callbacks, and cancellation handles. Preserve PDG's fluent object API while expanding scheduling capabilities. |
| 4 | **A2** | **Savegame service** | Named slots, metadata, versioned envelopes, migration callbacks, application-state hooks, native file storage, and browser storage. Build on existing serialization; explicitly report unsupported state. |
| 5 | **A2** | **Generated TypeScript declarations and typed examples** | Accurate overloads, enums, callbacks, ownership notes, and native/browser availability. Generate from authoritative binding metadata to keep editor assistance synchronized with the API. |
| 6 | **B1** | **Camera effect helpers** | Shake, impulse, flash, and transition presets, with effects composed separately from persistent camera position. Small additions with frequent use in action games; integrate with #2. |
| 7 | **B1** | **Logical audio groups** | Master/music/effects/UI volume and mute controls, group fades, and persistent settings. Grouped playback control, not a DSP mixer. |
| 8 | **B1** | **Snapshot diagnostics** | Inspect selected fields, packet sizes, resource references, format versions, and omitted state. Make serialization problems understandable without decoding buffers manually. |

For #3, [Phaser's tween controls](https://docs.phaser.io/phaser/concepts/tweens) provide a useful functionality baseline. PDG's opportunity is comparable composition while retaining consistent object methods.

## Priority 3: A3 + B2 + C1

| ID | Score | Specific addition | User benefit and scope |
|---|---|---|---|
| 9 | **A3** | **Modern tilemap runtime and Tiled import** | Larger tile identifiers, multiple tilesets, chunks, animated tiles, object layers, custom properties, and collision metadata. Start with orthogonal maps; add isometric/hex support explicitly rather than silently approximating it. |
| 10 | **A3** | **World collision-query API** | Raycasts, circle/box/capsule sweeps, region overlaps, nearest points, filtering, and allocation-conscious result buffers. Define consistent behavior across supported physics configurations. |
| 11 | **A3** | **Scene lifecycle and simulation clocks** | Scene-owned objects, timers, and subscriptions; predictable teardown; pause groups; time scaling; fixed-step simulation and render interpolation. Define behavior when UI continues while gameplay pauses. |
| 12 | **A3** | **Responsive UI layout and focus navigation** | Row/column/grid containers, anchors, minimum/preferred sizes, DPI scaling, keyboard focus, and controller navigation hooks. Extend existing Views rather than introduce a competing UI hierarchy. |
| 13 | **A3** | **Public materials, shaders, and render passes** | Custom uniforms, texture inputs, mesh drawing, offscreen passes, and supported native/browser shader paths. Unlock effects currently requiring renderer changes. |
| 14 | **A3** | **Asynchronous asset loading and lifetime management** | Load handles, progress, cancellation, dependency tracking, resource groups, and controlled release. Keep decoding/loading work from producing avoidable gameplay stalls. |
| 15 | **A3** | **Integrated runtime profiler** | Frame timeline, script/native timings, draw calls, allocations, physics costs, and serialization bandwidth; remote inspection for browser/mobile. Reuse existing instrumentation where possible. |
| 16 | **B2** | **Grid and graph pathfinding** | A* with weighted terrain, square/hex neighbors, blocked cells, reusable search storage, and frame-budgeted searches. Useful for strategy, tactical, and top-down games without requiring navigation meshes. |
| 17 | **B2** | **Text elements in retained Drawings** | Editable text, existing font/style support, bounds, alignment, wrapping, hit-testing, and serialization. Complete a gap in PDG's procedural artwork abstraction. Advanced international text is separate in #26. |
| 18 | **B2** | **Long-chain IK solvers** | FABRIK and CCD, joint limits, convergence controls, and diagnostic results, integrated with existing pose modifiers. Extend beyond two-bone chains. |
| 19 | **B2** | **Snapshot interpolation** | Timestamped snapshot buffers, interpolation of supported transforms, teleport handling, and bounded extrapolation. Make received state look smooth without requiring application authors to rebuild this layer. |

For #9, the [Tiled format](https://doc.mapeditor.org/en/stable/reference/json-map-format/) offers an established content pipeline. A documented supported subset is a useful first release; “supports Tiled” should not imply every orientation and data feature immediately.

## Priority 4: A4 + B3 + C2 + D1

| ID | Score | Specific addition | User benefit and scope |
|---|---|---|---|
| 20 | **A4** | **Visual scene and UI editor** | Scene hierarchy, property inspection, placement, reusable objects, undo/redo, asset references, and play-in-editor. A major adoption improvement, but a substantial product in its own right. |
| 21 | **B3** | **Portable gamepad support** | Device discovery, hot-plugging, standard mappings, axes, deadzones, multiple players, and supported vibration. Connect native and browser backends to #1. |
| 22 | **B3** | **Browser-compatible networking** | WebSocket client/server adapters behind the existing message API, connection lifecycle, backpressure, and explicit capabilities. Browser runtime is client-only; servers run natively. Start with reliable delivery; add other transports separately. |
| 23 | **B3** | **Character movement controller** | Move-and-slide, slope limits, floor snapping, one-way and moving platforms, and separation of intended motion from collision response. Depends on #10. |
| 24 | **B3** | **Audio bus mixer and effects** | Routing, metering, ducking, filters, compressor/limiter, reverb, and defined browser behavior. Extend #7 into a real mixing system. |
| 25 | **B3** | **2D lighting and shadows** | Normal-mapped sprites, point/directional lights, occluders, shadow controls, and light masks. Depends on #13. |
| 26 | **B3** | **International text and localization** | Font fallback, shaping, bidirectional text, IME integration, pluralization, translated resources, and RTL layout support. Benefits text-heavy and internationally released games. |
| 27 | **B3** | **Asset hot reload** | Reload textures, Drawings, maps, and supported animation assets while preserving live object identity. Build on #14; arbitrary script-state migration is outside this scope. |
| 28 | **B3** | **True snapshot deltas and structural updates** | Change tracking, baselines, create/delete operations, topology changes, resynchronization, and schema negotiation. Extend selective-field serialization into a more complete state-transfer system. |
| 29 | **B3** | **Animation state graphs and blending layers** | Named states, conditional transitions, parameters, bone masks, additive layers, and runtime inspection, integrated with procedural modifiers and physical control. A visual graph editor is additional tooling rather than a prerequisite for the runtime API. |
| 39 | **C2** | **One-rig motion-matching prototype** | Offline pose/movement feature table, normalized weighted search, selection of clip and timestamp, continuation bias, legal-state filters, existing transitions, and cost visualization. Compare against a state-machine baseline before building a general production system. |

PDG already has a [proposed browser transport plan](WEB_NETWORK_TRANSPORT_PLAN.md). It reduces design uncertainty for #22 but does not make implementation a small task. The WebSocket-first worklist scope is a proposed staging choice, not a claim that the broader WebTransport plan has been implemented or replaced.

For #23, [Godot's CharacterBody2D](https://docs.godotengine.org/en/stable/classes/class_characterbody2d.html) is a useful behavioral reference. Supporting slopes and moving platforms reliably is harder than adding a convenient movement method.

## Priority 5: B4 + C3 + D2

| ID | Score | Specific addition | User benefit and scope |
|---|---|---|---|
| 30 | **B4** | **Weighted 2D mesh skinning and import** | Deformable sprite meshes, bone weights, attachments, and a supported authoring/import pipeline. Integrate with existing pose, IK, and physics systems. |
| 31 | **B4** | **GPU visual particles** | Batched/GPU simulation, curves, trails, subemitters, preview tooling, and explicit backend limits or fallbacks. Keep existing physical particles for gameplay objects. |
| 32 | **B4** | **High-level multiplayer replication** | Authority, spawning/despawning, RPC, interest management, bandwidth budgets, interpolation, and reconnection. Build on #19, #22, and #28. Prediction should have a separately defined scope. |
| 33 | **B4** | **Production Android support** | Runtime backend, lifecycle, input/audio, packaging, device validation, and release tooling. Broadens mobile reach but requires continuing platform maintenance. |
| 34 | **C3** | **Navigation meshes and crowd avoidance** | Polygon navigation, agent sizes, dynamic obstacles, and local avoidance. Valuable for particular top-down games; #16 serves many projects earlier. |
| 35 | **C3** | **Remote asset catalogs and content updates** | Versioned manifests, downloadable bundles, cache validation, dependency handling, and recovery from interrupted updates. Build on #14. |
| 40 | **C3** | **Production motion matching for compatible 2D rigs** | Generalize a successful #39 prototype into database tooling, movement/contact metadata, query/search APIs, stable selection, gameplay/event constraints, transition-quality controls, and diagnostics across supported runtimes. **Alternative B3** if sophisticated character animation becomes a primary product focus. |

The alternative B3 rating for #40 places it in priority group 4; it changes the audience weighting, not the implementation scope or difficulty. Retain C3 as the broad-2D baseline unless that strategic focus is adopted.

## Priority 6: C4 + D3

| ID | Score | Specific addition | User benefit and scope |
|---|---|---|---|
| 36 | **C4** | **Rollback simulation framework** | Tick-indexed input, state restoration, resimulation, deterministic-state auditing, and desynchronization diagnostics. Serialization alone does not establish deterministic physics or application behavior. |
| 37 | **C4** | **Visual gameplay scripting** | Event sheets or graphs, debugging, serialization, API exposure, and version migration. Could attract a new audience but creates another programming environment to maintain. |

## Priority 7: D4

| ID | Score | Specific addition | Why it comes last |
|---|---|---|---|
| 38 | **D4** | **Complete built-in art-authoring suite** | Pixel painting, tileset creation, and skeletal-art authoring would duplicate mature external tools. Good importers and round-trip workflows deliver much of the user benefit at lower cost. Separate from the scene editor in #20. |

## Motion-matching implementation boundaries

The [competitive analysis](PDG_2D_ENGINE_COMPARISON.md#motion-matching-fit-readiness-and-competitive-opportunity) records the current API foundations and competitive assessment. The older [motion-matching investigation](SPRITER_MOTION_MATCHING_INVESTIGATION.md) remains useful design context, but its missing-API list predates `sampleAnimationPose()` and `transitionToAnimation(clip, timeSeconds, durationSeconds)`.

The prototype and production work are distinct milestones. #39 validates whether matching helps a representative PDG game; #40 delivers a reusable supported feature. Prototype work may inform production but is not assumed to be production-quality infrastructure.

- Use one compatible rigid 2D rig initially, with idle, walk/run, starts, stops, reversals, and explicit contact/speed metadata. No mesh-skinning or long-chain IK prerequisite is required.
- Extract features from the actual playback evaluator. In-place clips need authored speed or a virtual root trajectory; zero root displacement is not evidence of zero intended speed.
- Build the query from the continuous base pose, actual movement, and desired trajectory. Keep environmental IK corrections separate from the initial matching domain.
- Score the natural continuation, use switching thresholds/hysteresis, and retain legal-state filters. Do not skip attack windows or duplicate authored events to improve matching cost.
- Keep gameplay/physics ownership of the root explicit. A prototype may use an application controller; the production movement controller in #23 is useful but not a hard prerequisite.
- Reuse current sampling, destination-time transitions, pose modifiers, and contact targets. Verify event semantics and behavior when transitions are interrupted before adding more advanced smoothing.
- Start with linear search and profile. A neural network, a general retargeting system, and a visual animation-graph editor are outside the first implementation.

Evaluate against a competent state-machine baseline using held-out movement sequences, wall collisions, moving supports, pause/resume, and repeated transition interruptions. Measure transition frequency, pose/velocity discontinuity, planted-foot sliding, root/foot error, responsiveness, event correctness, CPU time, and database memory. This review did not run those experiments.

## Recommended execution sequence

1. **#1–5:** input actions, cameras, richer tweening, savegames, and TypeScript support.
2. **#9–11:** tilemaps, collision queries, and scene/time infrastructure.
3. **#17–19:** retained text, longer-chain IK, and snapshot interpolation.
4. **#22, #28, #29:** browser networking, true state deltas, and animation graphs.
5. **#39:** run the bounded motion-matching experiment before committing to the full animation-graph editor or mesh-skinning pipeline. It can move earlier within the animation workstream because those systems are not prerequisites.
6. Choose the next major investment from **UI/tooling**, **rendering**, or **multiplayer**, based on actual games using PDG. Promote #40 if #39 demonstrates useful gains and character animation becomes a priority.

Dependency order takes precedence over priority ties. Examples include #10 before #23, #13 before #25, #14 before #27/#35, and #19/#22/#28 before #32. Support modules such as navigation and character movement can remain optional so the runtime stays focused on reusable building blocks.

## Opportunities for category leadership

- **Animation:** fluent object control + composable sequences + procedural IK + physical rigs + animation graphs, with motion matching if validated.
- **Procedural artwork:** editable Drawings + retained text + hit-testing + animation + serialization.
- **State transfer:** complete snapshots + structural deltas + interpolation + browser/native transport.

These combinations could distinguish PDG. Input, tilemaps, layout, and tooling would make those strengths practical for more developers. Feature count alone does not demonstrate category leadership; representative games and comparative validation must establish the user benefit.
