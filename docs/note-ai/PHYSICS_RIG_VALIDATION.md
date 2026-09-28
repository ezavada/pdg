# Physics rig integration validation — 2026-09-25

Scope: Sprite-owned finite/continuous loads and stable force handles, aggregate
inertia/angular momentum, live physical reflection, and the separate wheel demo's
signed torque, coasting, finite braking and flip controls. No new public method
signatures or generated binding changes are needed.

| Runtime/check | Result |
| --- | --- |
| Native CTest: physics owners, Spriter playback, PhysicsBody | 3/3 suites pass |
| Headless Chipmunk: physics owners, Spriter playback | 2/2 suites pass |
| Headless Basic, Spriter disabled: physics owners, PhysicsBody | 2/2 suites pass |
| Desktop V8: animation pose | 31 tests, 829 assertions, no failures |
| Headless Node: animation pose | 31 tests, 815 assertions, no failures |
| Headless Node: PhysicsBody | 13 tests, 350 assertions, no failures |
| WebAssembly/browser: animation pose, PhysicsBody, Collider | 60 specs, 1,742 assertions, no failures |
| iOS/JSC simulator: animation pose | 31 tests, 829 assertions, no failures |
| Wheel demo finite native/browser sequence | Both pass |
| Browser wheel controls using pointer input | Torque, coast, brake, flip, release/regrip and frame reset pass |
| `make pdg-node` | Builds/packages v1.1.0; package test passes; no compiler warnings |
| C++ and JavaScript Doxygen regeneration | Succeeds with existing 65-warning baseline |

The native regressions cover load delay/duration and cancellation, root changes,
Kinematic intervals, saved load continuation, COM inertia and spin/orbital angular
momentum. Reflection coverage includes explicit/generated setup, preexisting
flips, rotated frames, moving bodies, edited anchors/limits and asymmetric
colliders, retained identities, detached bones, snapshots, recovery and atomic
external-angular-constraint rejection. The final native runs include reflection
after recovery has completed.

The wheel's automated sequence uses sustained 80 N m torque, then reflection,
bounded braking, release and regrip. Native results: 143.725 cm resting radial
extension, 189.095 cm mean spinning extension, 190.516 cm peak extension and
3.169 cm maximum pivot error (4 cm acceptance bound). The demo and benchmark
use the engine's shared bodies and constraints; there is no artificial outward
force. [Rig-count measurements](../../test/perf_tests/cpp-rig/RESULTS.md) cover setup,
simulation, mode switching and live reflection.

Reproduce the CTest coverage with `./test/unit cpp:pdg-physicsbody
cpp:pdg-physics-owners cpp:pdg-spriter-playback` (one command). Run the script
suites with `./test/unit animation_pose physicsbody collider`, adding `--node`,
`--ios`, or `--web --no-build --automated` to select another runtime.
For the wheel, see [its demo instructions](../../test/ui_tests/wheel_chains_demo.md).
Documentation was generated outside the checkout with
`tools/build-docs.sh --output-dir /private/tmp/pdg-physics-completion-docs --no-local-copy`.

Limits and outstanding acceptance:

- Imported animation physics rigs require Chipmunk. The feature-disabled Basic
  checks validate shared bodies/constraints and capability guards, not a Basic
  imported-rig implementation.
- External angular constraints must be disconnected before reflecting a rig.
  The wheel demo handles its axle/brake connections explicitly. Detached bodies
  stay in place; registered loads and manual targets retain world coordinates.
- These runtime results cover macOS, browser and the iOS simulator, not Windows,
  Linux or physical iOS hardware. Existing iOS conversion warnings remain.
- Grey Guy/Wonky Skeleton visual acceptance remains separate from the synthetic
  and wheel fixtures. Arbitrary live physical scaling and a momentum-conserving
  merge into one body are not implemented by this pass.
- `node tools/check-missing-docs.js --topics docs` still reports existing omissions:
  Particle/ParticleEmitter in the JavaScript class index and ParticleBreak in both
  Events topics. No edited physics API page introduced a Doxygen warning.

## Handoff/IK, Part artwork colliders and stability notes — follow-up

See [RIG_COVERAGE_AUDIT.md](RIG_COVERAGE_AUDIT.md) for the reconciled checklist
and controller-to-test mapping. New Part frame/box adapters are exposed in C++,
V8, JSC and WebAssembly and retain source selection through snapshots. Native
coverage includes editable Drawing bounds, strip-frame alpha changes, reflection,
explicit additions, both resource modes and tagged/untagged records. The shared
mask reader now validates strip pixels against the complete underlying buffer.
iOS bounds checks also exposed an existing concave-polygon merge loop indexing an
erased piece; the loop now stops before touching either piece after a merge.

Linux native validation now has a repeatable entry point:
`bash test/docker/physics`. On ARM64 Ubuntu 24.04, all four Chipmunk/Spriter
suites and all three Basic/feature-disabled suites pass. This does not cover
Linux desktop/JavaScript or Windows. Basic animation-rig support is explicitly
out of scope permanently; animation physics requires Chipmunk.

The user-approved API stability policy is applied to 52 JavaScript classes and
55 corresponding/native C++ classes/interfaces. Existing numeric levels are
retained, Level 2 is named Evolving, and serialization API stability explicitly
does not guarantee a fixed snapshot format. MVC's family policy is documented in
both overviews and its JavaScript README. Both references regenerate with the
existing 65-warning baseline. `tools/check-api-stability.py --site <site>` checks
coverage, shared ratings and rendered notes; `tools/check-missing-docs.js --topics
<site>` checks class/event navigation (all pass).

Follow-up validation results:

| Runtime/check | Result |
| --- | --- |
| Native CTest: owners, Spriter playback, PhysicsBody, animation pose | 4/4 pass |
| Linux Docker ARM64: Chipmunk/Spriter and Basic/feature-disabled | 7/7 pass |
| Desktop V8 complete suite before final collider fixes | 1,333 tests, 8,919 assertions, no failures |
| Desktop V8 focused final collider suite | 17 tests, 597 assertions, no failures |
| Headless Node: collider and animation pose | 49 tests, 1,420 assertions, no failures |
| WebAssembly/browser: collider, animation pose, PhysicsBody | 62 specs, 1,781 assertions, no failures |
| iOS/JSC: animation pose | 32 tests, 850 assertions, no failures |
| iOS/JSC: collider after polygon merge fix | 17 tests, 592 assertions, no failures |
| Grey Guy/Wonky physical cycles | Both pass, including physical reflected hand positions, mass and one completion each |
| Existing full showcase playback/foot IK probe | Pass; two Attack and Crumble cycles, blends, facing and rock contact |
| Documentation stability and topic/event checks | Pass in both language references |
| Final `make pdg-node` | Packages v1.1.0, package smoke test passes, no compiler warnings |

Native window capture was unavailable; automated rendering/playback results are
not a screenshot-based visual review.

## Headless Node validation fixes

The four failures in the initial full Node run are resolved. Text-style constants
and Image/ImageStrip object serialization were incorrectly guarded by
`PDG_NO_GUI` in the bindings, despite the underlying Attributes and image-data
APIs being available headless. V8 and JSC now expose those capabilities in both
build modes; image deserialization returns the native image wrapper headless too.

Parts and Particles still require a graphics build to accept Drawing artwork.
Their artwork-only specs now check the owner's `setDrawing` capability rather
than assuming `createDrawing` implies support. Part hierarchy, identity, tween,
drive and resource-policy restoration remain covered in a separate headless-safe
test. Additional regression checks cover text styles and Image, ImageStrip and
frame-view object snapshots with both resource policies.

| Check | Result |
| --- | --- |
| Fresh `make pdg-node` | Build and package smoke test pass; no compiler warnings |
| Complete headless Node suite | 1,225 tests, 8,408 assertions, no failures |
| Complete desktop V8 suite, including Part/Particle artwork | 1,335 tests, 8,990 assertions, no failures |
| iOS/JSC serialization suite | 29 tests, 396 assertions, no failures |
