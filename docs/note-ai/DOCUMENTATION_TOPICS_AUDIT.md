# Documentation Topics audit

Reviewed 2026-09-20 against the animation branch and regenerated with Doxygen 1.18.0.

## Scope and result

The audit covers the C++ engine SDK (`src/inc/pdg/sys`, including optional Spriter
and Chipmunk interfaces) and the root JavaScript `pdg` API declared in
`docs/javascript/pdg-js.h` / `pdg-js.json`. It includes public nested types,
interfaces, templates, exceptions, and documented event structures.

The separate MVC application frameworks are outside these two engine API
references: `docs/cxx/Doxyfile` explicitly excludes `pdg/app`, documented in
`src/inc/pdg/app/README.md`; JavaScript MVC has its own module and README under
`src/js/mvc-app`. The 2026-09-26 follow-up completes their theme/transform contracts. Private types and sections marked `INTERNAL` stay excluded.

| Reference | Indexed types with reachable topic membership | Exposed-class cross-check |
| --- | --- | --- |
| C++ | 119 / 119 across 18 topics | Public header definitions reviewed, including conditional native APIs |
| JavaScript | 62 / 62 across 10 topics | All 46 classes in the generated API inventory; the other 16 types document event objects |

Types can belong to more than one topic. Coverage means an actual entry in a
reachable topic's class table, not an incidental hyperlink in its description.

## Corrections

- Added C++ Animation sections for rigs/poses, modifiers and IK, targets, physics,
  artwork, and easing, with a task-oriented entry-point table and timing notes.
- Assigned missing C++ geometry, graphics, serialization, event, utility,
  synchronization, system-service, and manager classes. Added the familiar
  coordinate aliases (`Point`, `Offset`, `Vector`, `Rect`, `Quad`, `RotatedRect`)
  to Graphics as typedefs of their class templates.
- Unified the C++ `Network` / `Networking` groups. `EventEmitter` now belongs to
  Events; manager classes also appear under their relevant functional topics.
- Enabled optional Spriter and Chipmunk declarations for the C++ reference and
  expanded the event inheritance macros so their structures are parsed.
- Replaced the ineffective native-only Doxygen section label `C++` with `CXX`.
  Native class definitions, including `Initializer`, `log`, and `RefCountedImpl`,
  now appear with their actual members and template information.
- Completed JavaScript topic assignments for `Attributes`, `Drawing`, `ElementRef`,
  `Polygon`, `Spline`, `TileLayer`, `AnimationSpringTarget`, and
  `AnimationContactTarget`. Added a Sprites and layers topic in both references.
- Kept floating-point seconds as the animation timing convention and explicitly
  listed the existing integer-millisecond exceptions on the C++ Animation page.

## Animation-event follow-up

The class audit did not initially cover event constants or detect a missing
JavaScript event-payload declaration. The follow-up review found and corrected:

- `eventType_SpriteTriggerEvent` now has an Events entry in JavaScript.
- `SpriteTriggerEvent` now documents the portable JavaScript payload and belongs
  to Events, Animation, and Sprites. Its delivery guide is hosted by Events and
  cross-linked from Animation and Sprites. The native `SpriteTriggerEventInfo` already belonged to all three topics.
- Authored triggers use `eventType_SpriteTriggerEvent`; existing public event
  and action IDs are unchanged.
- Blend-completion documentation now covers both `blendToAnimation()` and
  `transitionToAnimation()`, delivered through `eventType_SpriteAnimate` with
  `action_AnimationBlendComplete`, independently of authored-trigger enablement.
- Documented floating-point second payload fields and native `frameTime` as an
  integer-millisecond compatibility field. The event ID is not exposed by the
  current V8/JavaScriptCore bridges; the browser bridge exposes it.

The repeatable audit now also checks every public event-type constant: **25/25
C++** and **20/20 JavaScript** are listed in Events. The C++ `eventType_last`
sentinel is excluded from that count.

## Repeating the check

After `make docs`, substitute the root `VERSION` value in this command:

```sh
node tools/check-missing-docs.js --topics artifacts/docs/site/pdg-docs-v<VERSION>
```

The command checks both generated class indexes against the class tables reachable
from their Topics pages, verifies class/group links and anchors, and cross-checks
the JavaScript class index against the generated API inventory. It also checks
public event-type constants against the Events topic. It exits nonzero
on missing memberships, missing exposed JavaScript classes/event types, or broken links.
This complements the manual C++ review; it cannot detect an arbitrary new native
class excluded from Doxygen's input or preprocessor configuration.

Validation passed for the regenerated references. Targeted audit-tool checks also
covered inline classes, missing memberships, incidental description links,
unreachable topic files, missing JavaScript exports, and broken anchors. Running
the audit against the older checked-in HTML correctly failed: C++ had 31/77
indexed types in topics; JavaScript had 53/59, with both animation target classes
also absent from its class index. The JavaScript Sprite page also lacked the new
IK methods. `make docs` now refreshes `docs/cxx/html`, `docs/javascript/html`, and
`docs/javascript/man` from the regenerated site as well as producing the archive
under `artifacts/docs/`. `--no-local-copy` retains artifact-only generation.
The JavaScript API declarations used by Doxygen must also be regenerated and
included with API changes; updating `.dox` descriptions alone cannot introduce
methods missing from `pdg-js.h`.

Doxygen still reports unrelated source-documentation warnings. Its man-page pass
also needed an existing automatic retry after a local Doxygen crash. Generation
and packaging completed successfully; no warnings were suppressed.

## C++ topic inventory

| Topic | Classes and structures |
| --- | --- |
| Animation | `Animated`, `IAnimationHelper`, `OffsetT`, `PointT`, `QuadT`, `RectT`, `RotatedRectT`, `Sprite`, `SpriteAnimateInfo`, `SpriteCollideInfo`, `SpriteJointBreakInfo`, `SpriteLayer`, `SpriteLayerInfo`, `SpriteTriggerEventInfo`, `TileLayer`, `VectorT` |
| Animation artwork and diagnostics | `AnimationDrawBounds`, `AnimationDrawableOptions`, `AnimationDrawingContext`, `AnimationDrawingSubmission`, `AnimationDrawings`, `Drawing`, `ElementRef` |
| Easing functions | Functions or constants; no classes |
| Pose modifiers and inverse kinematics | `AnimationCallbackScope`, `AnimationIKResult`, `AnimationModifierContext`, `AnimationPipeline`, `AnimationPoseView`, `AnimationTwoBoneIK` |
| Animation physics | `AnimationPhysicsBody`, `PhysicsBodyState`, `AnimationPhysicsDefinition`, `AnimationPhysicsJoint`, `AnimationPhysicsRig` |
| Rigs, poses, and transforms | `AnimationBinding`, `AnimationBone`, `AnimationMetadata`, `AnimationPose`, `AnimationRig`, `AnimationSocket`, `AnimationTagSet`, `AnimationTransform`, `AnimationVariable` |
| Spring and contact targets | `AnimationContactState`, `AnimationContactTarget`, `AnimationSpringTarget`, `AnimationTargetState` |
| Core utilities | `PDGException`, `RefCountedImpl`, `RefCountedObj`, `Singleton` |
| Events | `EventEmitter`, `EventManager`, `EventQueueEntry`, `IEventHandler`, `KeyInfo`, `KeyPressInfo`, `ModifierKeyInfo`, `MouseInfo`, `MouseTrackingInfo`, `NetConnect`, `NetData`, `NetDisconnect`, `NetError`, `PortDrawInfo`, `PortResizeInfo`, `ScrollWheelInfo`, `ShutdownInfo`, `SoundEventInfo`, `SpriteAnimateInfo`, `SpriteCollideInfo`, `SpriteJointBreakInfo`, `SpriteLayerInfo`, `SpriteTouchInfo`, `SpriteTriggerEventInfo`, `StartupInfo`, `TimerException`, `TimerInfo`, `TimerManager`, `UserData` |
| Graphics | `Attributes`, `Color`, `Drawing`, `ElementRef`, `Font`, `GraphicsManager`, `ISpriteDrawHelper`, `Image`, `ImageStrip`, `OffsetT`, `PointT`, `Polygon`, `Port`, `PortDrawInfo`, `PortResizeInfo`, `QuadT`, `RectT`, `Renderer`, `ResourceManager`, `RotatedRectT`, `ScreenMode`, `Spline`, `TileLayer`, `VectorT` |
| Managers | `ConfigManager`, `EventManager`, `GraphicsManager`, `LogManager`, `NetworkManager`, `ResourceManager`, `SoundManager`, `TimerManager` |
| Networking | `Internet`, `NetConnect`, `NetData`, `NetDisconnect`, `NetError`, `NetworkManager` |
| Physics | `ISpriteCollideHelper`, `SpriteCollideInfo`, `SpriteJointBreakInfo` |
| Serialization | `Deserializer`, `IDeserializer`, `ISerializable`, `ISerializer`, `Serializable`, `Serializer`, `bad_tag`, `out_of_data`, `sync_error`, `unknown_object` |
| Sound | `ResourceManager`, `Sound`, `SoundEventInfo`, `SoundManager` |
| Sprites and layers | `ISpriteCollideHelper`, `ISpriteDrawHelper`, `Sprite`, `SpriteCollideInfo`, `SpriteJointBreakInfo`, `SpriteLayer`, `SpriteLayerInfo`, `SpriteTouchInfo`, `SpriteTriggerEventInfo`, `TileLayer` |
| System services | `FindDataT`, `Initializer`, `LogManager`, `MemStats`, `OS`, `category`, `level`, `log` |
| Thread synchronization | `AutoCriticalSection`, `AutoMutex`, `AutoMutexNoThrow`, `CriticalSection`, `Mutex`, `Semaphore`, `timeout` |

## JavaScript topic inventory

| Topic | Classes and structures |
| --- | --- |
| Animation | `Animated`, `AnimationContactTarget`, `AnimationSpringTarget`, `Drawing`, `ElementRef`, `IAnimationHelper`, `Offset`, `Point`, `Quad`, `Rect`, `RotatedRect`, `Sprite`, `SpriteAnimateEvent`, `SpriteLayer`, `SpriteTriggerEvent`, `TileLayer`, `Vector` |
| Events | `EventEmitter`, `EventManager`, `IEventHandler`, `KeyEvent`, `KeyPressEvent`, `MouseEvent`, `MouseTrackingEvent`, `PortDrawEvent`, `PortResizedEvent`, `ScrollWheelEvent`, `ShutdownEvent`, `SoundEvent`, `SpriteAnimateEvent`, `SpriteBreakEvent`, `SpriteCollideEvent`, `SpriteLayerEvent`, `SpriteTouchEvent`, `SpriteTriggerEvent`, `TimerEvent`, `TimerManager` |
| Graphics | `Attributes`, `Color`, `Drawing`, `ElementRef`, `Font`, `GraphicsManager`, `ISpriteDrawHelper`, `Image`, `ImageStrip`, `Offset`, `Point`, `Polygon`, `Port`, `PortDrawEvent`, `PortResizedEvent`, `Quad`, `Rect`, `ResourceManager`, `RotatedRect`, `Spline`, `Sprite`, `SpriteLayer`, `TileLayer`, `Vector` |
| Key Code Constants | Functions or constants; no classes |
| Managers | `ConfigManager`, `EventManager`, `FileManager`, `GraphicsManager`, `LogManager`, `ResourceManager`, `SoundManager`, `TimerManager` |
| Networking | `NetClient`, `NetConnection`, `NetServer` |
| Physics | `AnimationContactTarget`, `AnimationSpringTarget`, `CpArbiter`, `CpConstraint`, `CpSpace`, `ISpriteCollideHelper`, `SpriteBreakEvent`, `SpriteCollideEvent` |
| Serialization | `Deserializer`, `ISerializable`, `MemBlock`, `Serializer` |
| Sound | `Sound`, `SoundEvent`, `SoundManager` |
| Sprites and layers | `ISpriteCollideHelper`, `ISpriteDrawHelper`, `Sprite`, `SpriteAnimateEvent`, `SpriteLayer`, `SpriteTriggerEvent`, `TileLayer` |
