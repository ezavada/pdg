# `ik` branch API documentation audit

Audited against `main` at `ee2e18dfdd2fdfd3e3ac5f643efbab531ac52070`, with the branch at `4a8383a3c`, on 2026-09-21. This records documentation work; current implementations remain the authority for behavior.

## Scope and result

The initial generated JavaScript inventory contained 148 distinct added methods after removing inherited copies:

| API | Added methods |
| --- | ---: |
| Animated | 11 |
| Part | 27 |
| PhysicsBody | 39 |
| Sprite | 50 |
| Attributes | 1 |
| AnimatedAttributes | 20 |

Checking the JavaScript source found another ten helper methods/functions missing from generated declarations: four AnimationSpringTarget methods, five AnimationContactTarget methods, and animationHasTag(). Their two constructors also lacked generated signatures. These declarations are now supplied by `docs/javascript/excluded-function-docs.js`.

The completed pass covers all of those APIs, the two helper constructors, relevant AnimatedAttributes overrides, and the changed growth/spin/directed-rotation/wait contracts. It provides **175 typed JavaScript signature entries** including overloads and the previously approved addAnimationDrawable() entries. There are **277 explicit native signature entries**, with PhysicsBodyRef forwarding documentation inherited from its corresponding PhysicsBody methods. Native-only rig, pose, pipeline, drawing, spatial-transform, and physics utilities are included. MVC animation and layout hooks are documented in the native headers, JavaScript source, and MVC README.

Private engine plumbing, deleted APIs, and unrelated legacy methods were not expanded into new application documentation.

## Standard applied

- Concrete method summaries, complete named parameters, units and coordinate spaces, return semantics, failure behavior, and relevant cross-links.
- Distinct typed overloads instead of ambiguous object parameters or combined parameter names.
- Prerequisite Notes before examples.
- Shared options and returned-state schemas in bordered sections with stable anchors. Related methods link to the authoritative schema.
- Explicit ownership, borrowed callback lifetimes, snapshot independence, deferred mutations, and retained-object behavior after removal.
- JavaScript examples using actual binding conventions; separate C++ examples using native types and ownership.
- Method details on their owning class pages. Per-method topic assignments were removed where they would relocate those details to group pages.

The source remains in `docs/javascript/dox`, `docs/cxx/dox`, and native/JavaScript comments. Generated references and bindings were regenerated, not edited by hand.

## Contract and navigation corrections

- Preserved the Drawing-returning callback contract and approved examples for addAnimationDrawable().
- Documented Part.setParentPart() and setParentPart(Part) separately, avoiding an invented explicit-undefined default.
- Split Part.attachSprite(), PhysicsBody.applyImpulse(), and PhysicsBody.applyForce() into their supported argument variants.
- Corrected setTransform() metadata to report its chaining return value.
- Restored the spring/contact helper declarations and their method references.
- Corrected the outdated claim that Part bodies could not join a Chipmunk world.
- Clarified independent transform scale versus logical dimensions, physical versus programmed motion, and seconds-based timing.
- Added PhysicsBodyState to the Physics topic.
- Corrected the manual-page index generator to link into `man3/` and exclude its own index. Clean regeneration also refreshes aliases whose owning documentation page changed.

No engine behavior was changed for this audit.

## Verification

- Rebuilt the native PDG executable and regenerated its bindings and JavaScript IDL.
- Executed 49 documentation examples against the real runtime using the arm Spriter fixture, plus assertions for overloads, omitted-parent behavior, chaining, physics state, and owned helper snapshots. The previously approved drawable examples were also checked against the runtime during their documentation pass.
- Compiled 12 native documentation examples with the checkout's C++ build flags; this was a syntax check, not a native rendering test.
- Checked all 175 JavaScript and 277 native documented signatures in Doxygen XML for summaries, detailed documentation, and parameter coverage.
- Confirmed ten shared boxes on class pages in each language, without invalid paragraph nesting.
- Ran `tools/build-docs.sh` from the updated sources to replace all three generated trees with clean output.
- Passed `node tools/check-missing-docs.js --topics docs`: all 125 C++ and 65 JavaScript classes/structures, and all indexed public event types, appear in Topics.
- Checked all 1,255 manual index targets and 1,196 manual aliases resolve.
- Source whitespace checks passed. Existing unrelated Doxygen warnings remain; no new warnings originate in the edited API entries. Doxygen's generated man files retain its normal trailing whitespace.

The reusable standard and workflow are captured in [the pdg-documentation skill](../../.codex/skills/pdg-documentation/SKILL.md).
