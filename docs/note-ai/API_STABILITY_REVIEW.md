# API stability review — approved 2026-09-25

The user approved this proposal on 2026-09-25. Apply the same policy and shared-class ratings to the JavaScript and C++ source
references. JavaScript-only wrappers and C++-only types need their own entries.

## Findings

- Existing class notes use three levels: 1 Experimental, 2 Unstable, 3 Stable.
  They mix `\warning`, `\note` and `\pre`; stability is not a calling precondition.
- Level 3 currently promises unconditional backward compatibility. That should
  describe an API evolution policy, with an explicit exception for announced
  breaking releases, rather than imply that every future release is compatible.
- The newer physics, Parts, particles, Drawing, animation targets and animated
  appearance APIs have no consistent class-level rating.
- Several old Level 1 notes say the interface was introduced recently. That
  wording is stale for long-standing callback interfaces.
- Stable serialization method signatures must not imply stable snapshot bytes.
  Physics graph revisions, resource policies and supported record versions have
  their own compatibility contracts.
- Support and stability are separate: animation physics requires Chipmunk in
  both languages; a stable API can still have platform/build prerequisites.

## Proposed common wording

Use `\note` consistently, with a link to one stability-policy section in each
language's overview. Do not put these notes on individual methods unless a method
has a different status from its class.

1. **API Stability: 1 — Experimental.** This API is exploratory. Its signatures,
   behavior, or availability may change without a compatibility period.
2. **API Stability: 2 — Evolving.** This API is implemented and supported, but its
   contract is still settling. Compatibility is preserved where practical;
   breaking changes are documented in release notes.
3. **API Stability: 3 — Stable.** This public contract is established. Compatible
   changes are expected; intentional breaking changes require an announced
   breaking release and migration guidance.

Keep the existing numeric levels. Rename Level 2 from “Unstable” to “Evolving”
to describe API evolution without implying that the implementation is unreliable.
Ratings are maintenance commitments, not a consequence of test counts alone.

## Proposed ratings

| Classes/families | Proposal | Reason |
| --- | --- | --- |
| ConfigManager, EventEmitter, EventManager, Font, LogManager, TimerManager, Serializer, Deserializer | Retain 3 | Existing published commitment; clarify snapshot-format exception for serialization. |
| Color, Point, Offset, Vector, Rect, Quad, RotatedRect | Add 3 | Established basic value/geometry contracts. This does not promise unchanged numeric precision or snapshot representation. |
| IEventHandler, ISerializable | Add 3 | Established callback/protocol contracts underlying the existing stable managers and serialization APIs. |
| Animated, Sprite, SpriteLayer, TileLayer, Port, GraphicsManager, Image, ImageStrip, FileManager, MemBlock, ResourceManager, NetClient, NetConnection, NetServer, Sound | Retain 2, with new wording | No evidence-based reason to expand their compatibility commitment during current API work. |
| IAnimationHelper, ISpriteDrawHelper | Change 1 to 2 | Long-standing, exercised callback APIs; animation timing and the surrounding interface are still evolving. |
| AnimatedAttributes, Attributes, Drawing, ElementRef, Polygon, Spline | Add 2 | Recent graphics/appearance work and planned live associations still affect the contract. |
| Part, PhysicsBody, PhysicsConstraint, Collider, Particle, ParticleEmitter | Add 2 | Implemented, tested public APIs with recent additions and ongoing contract changes. |
| AnimationContactTarget, AnimationSpringTarget and native pose/rig/controller utilities | Add 2 | Recent animation integration; use the same rating on corresponding language surfaces. |
| MVC views, controls, application and appearance classes | Add 2 | Layout, transformed rendering/input and theme composition are implemented (2026-09-26); this API remains evolving. |
| CpSpace, CpConstraint | Retain 1 | Low-level solver wrappers; do not equate them with the supported shared PhysicsBody/PhysicsConstraint facade. |
| CpArbiter | Retain 2 | Existing rating; remains a low-level, solver-specific surface. |
| SoundManager | Retain 1 | No audio-specific review or validation justifies promotion in this task. |

Plain result/options/event structures inherit the owning API family's policy
unless a separate note is necessary. C++ templates and internal implementation
types should not acquire public stability promises merely because Doxygen lists
them. Native-only public utilities must be inventoried during the approved pass.

## Proposed application checks

- Keep one class note per language, even where several `.dox` files contribute
  to the class description. Do not duplicate a note in every method family.
- Add missing Particle/ParticleEmitter index links and ParticleBreak Events links
  while verifying navigation for the approved notes.
- Regenerate both references; check class pages, links and warning baseline.
- Add a small coverage check for rated public classes so later additions do not
  silently omit their stability note.

Approved: common wording, Level 2 rename, and the rating table above.

Implementation inventory: native geometry is documented on PointT/OffsetT/VectorT/RectT/QuadT/RotatedRectT. AnimatedBase and AnimatedAttributesBase inherit Level 2; native AnimationRig, AnimationPose, AnimationPoseView, AnimationPipeline, AnimationPhysicsRig, AnimationDrawingContext and AnimationDrawings also receive Level 2. Internal leases/scopes/storage do not. Native ISerializer/IDeserializer share Level 3 with the corresponding public serialization protocols. FileManager, NetClient/NetConnection/NetServer, MemBlock and Cp wrappers are JavaScript-only surfaces. MVC is covered by the common overview policy and its JavaScript README because the engine Doxyfile deliberately excludes C++ app headers.

Verification: 52 JavaScript and 55 C++ class/interface notes; all exposed JavaScript classes rated, shared ratings agree, generated notes and policy links present. Both topic/class/event audits pass. Regeneration retains the 65-warning baseline. Run `python3 tools/check-api-stability.py --site <generated-site>` to repeat the stability checks.
