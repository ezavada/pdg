# Synfig rigs through PDG's existing Spriter runtime

Scope: offline conversion of bones, rigid artwork and bone-driven motion. Vector morphing, weighted skinning and bitmap deformation are deferred. This is a proposed design based on source inspection, not an implemented exporter.

## Recommended output

Build a standalone converter that emits:

```text
character.scml       # skeleton, image parts, named animation clips
parts/*.png          # unchanged bitmaps or rasterized static artwork
character.rig.json  # stable IDs, source mapping, sockets, optional IK hints
conversion.json     # supported features, omissions, measured error
```

Use SCML first because PDG already loads it via `PDGSpriterFileDocumentWrapper` and has SCML fixtures. No new game-side Synfig loader, renderer or dependency is needed. The rig manifest is proposed metadata, not an API PDG currently consumes. Basic playback and compatible fixed-hierarchy pose/IK assets should work without
that manifest; a future sidecar importer could consume its additional metadata.

The important distinction is **baking motion into bone tracks**, not baking a character into video frames. Bones and rigid image attachments remain separate in the exported SCML.

## Supported authoring profile

| Synfig construct | Initial conversion policy |
| --- | --- |
| Named bones with fixed parents | Preserve hierarchy and stable names/IDs |
| Animated bone translation and rotation | Export local transform tracks |
| Scale or changing bone length | Support only when destination hierarchy reproduces the result; otherwise diagnose |
| A bitmap attached rigidly to one bone | Reuse/copy its image, export its pivot and bone-relative transform |
| Static vector artwork attached as one rigid part | Rasterize once in part-local space, then animate it as an image |
| Bone-driven expressions or constraints | Evaluate offline and sample their output; do not export the expression/solver |
| Whole-part opacity and visibility | Map to supported alpha/mainline presence semantics |
| Part stacking changes | Export mainline z-order changes where representable |
| Named reference points | Export Spriter points where supported; validate PDG attachment behavior |
| Weighted vertices, skeleton deformation, morphs | Exclude from the supported profile and report precisely |
| Skew, masks, cross-part blend effects | Reject unless a static part can be rasterized independently without changing the intended result |
| Animated reparenting/subentities | Defer in the first version; detect rather than silently flatten |

“Ignore deformation” must not mean silently producing a broken character. Default to actionable diagnostics identifying the layer and feature. An explicit export profile can omit unsupported layers, or freeze selected artwork at a declared reference time, while reporting the visual loss. Never present frozen deformed artwork as a faithful deformation conversion.

An author should organize a character as rigid parts such as torso, upper arm, forearm and hand. Each part has one owning bone. Geometry whose vertices are driven by different bones is outside this profile even if all its movement originates from bones.

## Use Synfig to evaluate Synfig

Prefer a standalone build-time exporter linked to libsynfig over a hand-written SIF expression interpreter. It can read the actual evaluated bone transforms, resolve links and sample curves using Synfig's semantics. Shipping the exporter and its dependencies is separate from shipping PDG; its license/distribution needs are covered in the parent investigation.

A small direct-SIF parser is possible for a sharply constrained subset, but becomes expensive as soon as linked values, interpolation modes, canvases and bone-specific scale behavior enter the input. Even with libsynfig, the exporter must interpret artwork ownership and layer context; bone enumeration alone does not identify a renderable character.

Use a manifest to select the canvas/skeleton, map parts to source layers and bones, define a reference pose, choose pixels per source unit, and name clips by time range. Automatic detection can assist, but ambiguous ownership should require explicit author mapping. Source names need not be unique: preserve source IDs and generate unique destination names deterministically.

## Conversion pipeline

1. **Inspect and validate.** Resolve selected bones, parent graph, artwork, links and resources. Detect cycles, unsupported layers and changing parents. Limit the first version to a fixed hierarchy and representable transforms.
2. **Prepare images.** Reuse source bitmaps when possible. Rasterize static vector parts with skeletal placement removed, retaining part-local extents and pivot. Add transparent padding and retain the offset introduced by cropping. Whole-document screenshots are unsuitable because they lose hidden parts and separation.
3. **Evaluate clips.** Sample the source at requested times, obtaining bone frames and each part's final transform in a consistent coordinate space, including enclosing canvas/group transforms.
4. **Fit destination transforms.** Convert coordinates and derive bone/part-local transforms under the *actual Spriter composition rules*. Preserve bone parents rather than exporting independent world-positioned images.
5. **Write SCML.** Emit image folders/files, entity object information, bone/object timelines, mainline references and named animations. Add point timelines for declared sockets. Start with synchronized sample times and unoptimized mainlines for clarity.
6. **Validate with the destination runtime.** Load through the bundled SpriterPlusPlus/PDG path, evaluate at independent times, and compare joints and transformed image corners with the source. Reduce redundant keys only after this passes.

### Transform conversion is the main engineering risk

Do not copy Synfig angles and scales field-for-field. Source `ValueNode_Bone` distinguishes local length scaling from inherited scaling, and `ValueNode_BoneLink` can enable/disable translation, rotation, skew and individual scale axes. Those combinations are not all ordinary Spriter parenting.

For ordinary rigid transforms, converting world frames and deriving the parent-relative frame is a useful starting point. It is not sufficient for general scale: the inspected Spriter `TransformProcessor` multiplies scales componentwise, adjusts angle under reflection, then scales/rotates child positions. This does not reproduce every affine hierarchy Synfig can evaluate.

Fit and reconstruct with those destination rules, then compare the result. Reject residual shear/nonrepresentable corner motion above tolerance. Adding more time samples cannot repair a spatial transform the runtime cannot express.

Define source-to-SCML axis direction, angle units, pixel scale and pivot convention once. The bundled loader converts SCML angles from degrees to radians and has coordinate/pivot inversion behavior. Verify a translated, rotated and mirrored fixture through that loader rather than applying a guessed Y flip twice.

### Preserve rotation and timing

Begin with a bounded dense sample interval, include source waypoints and discrete changes, then adaptively refine where destination playback exceeds error tolerance. Test intermediate times beyond just midpoints. Arbitrary expressions can oscillate between probes, so set a maximum sample interval and report the sampling limits rather than claiming exact reproduction.

Use destination image-corner error and joint/endpoint error in pixels, plus angle checks where needed. Preserve unwrapped rotations and SCML `spin`; a 360-degree turn must not collapse into no movement. Convert time to integer milliseconds carefully, handle rounding collisions, and verify loop seams and clip endpoints.

Changing length is particularly subtle: exporting a longer debug bone is not enough to move its child or stretch its image. Child offsets and image transforms must reproduce the source motion. Store declared rest lengths separately for future IK.

## Playback fidelity versus live rig behavior

Report these separately for each export:

- **Articulated rig:** fixed hierarchy and ordinary rigid inheritance; intended to remain meaningful under future PDG pose edits.
- **Sampled motion:** source constraints/expressions were resolved into tracks; playback can match, but the source constraint behavior is not preserved.

For example, a hand that selectively ignores its parent's rotation can be reproduced during an authored clip with compensating keys. After PDG rotates the parent with IK, those keys do not automatically recompute the compensation. Either reject that rig for an articulated export, or explicitly classify it as sampled motion. Do not imply that successful playback proves interactive equivalence.

Similarly, an IK template used in Synfig can produce exportable bone tracks if Synfig evaluates it successfully. That does not import the template's target controls or IK algorithm. A new hand target at runtime still requires PDG's own IK/pose layer.

## What PDG needs—and what it does not

**Authored playback:** aim for zero runtime changes. Converted SCML and images should use the current sprite creation, animation selection and blending APIs. Verify attachment/collision behavior against current fixtures; do not expand the runtime merely to accommodate a converter error.

**Chipmunk-driven movement:** use the implemented pose/IK and shared physical-rig APIs for compatible native Spriter assets. The converter's rig manifest can preserve bone names, reference transforms, lengths, sockets and optional bend/limit hints. Those hints should be explicit author data where Synfig does not provide them. They must not be fabricated from bone width or visual shape.

No SpriterPlusPlus submodule changes are proposed. No Synfig object should appear in PDG's C++ or JavaScript runtime API. More advanced source capabilities can be recorded in the manifest for later backends, but current exports must remain honest about what was retained.

## Smallest useful prototype

Use one Synfig arm: shoulder, elbow, hand; three rigid parts; a named hand socket; a looping bend clip and a multi-turn rotation clip. Include a nonzero root translation and a reflected case. Begin with translation/rotation and uniform scale; add harder scaling only after exact rigid mapping works.

Success means:

1. The converter exports ordinary SCML and PNG files that existing PDG loads.
2. Joints, image corners, pivots and socket positions match at sampled and independent validation times within declared tolerances.
3. Exported bones remain individually identifiable and parented; images are not flattened.
4. Looping, seeking and blending use existing Spriter behavior without regressions.
5. A deformation layer produces a useful unsupported-feature report.
6. A selectively inherited bone link is distinguished from a fully articulated rig.

The first deliverable should be this exporter plus fixtures and conversion diagnostics, not a generic animation-backend refactor. Once that works, test a real character before widening the supported Synfig profile.

## Source references

Source snapshot inspected: Synfig `2be773c501c0a233848d1b7b7134d96e28c45bcd`.

- [Synfig bone-link evaluation and inheritance switches](https://github.com/synfig/synfig/blob/2be773c501c0a233848d1b7b7134d96e28c45bcd/synfig-core/src/synfig/valuenodes/valuenode_bonelink.cpp)
- [Synfig bone transform evaluation](https://github.com/synfig/synfig/blob/2be773c501c0a233848d1b7b7134d96e28c45bcd/synfig-core/src/synfig/valuenodes/valuenode_bone.cpp)
- Local `deps/SpriterPlusPlus/spriterengine/objectref/transformprocessor.cpp` and `loading/spriterdocumentloader.cpp`: destination composition and SCML conventions.
- Local `src/sys/spriter/pdg_spriter_file_document_wrapper.cpp` and `test/data/spriter-samples/`: current loading path and fixtures.
- [Broader support investigation](SYNFIG_SPRITER_SUPPORT_INVESTIGATION.md) and [PDG pose/physics investigation](SPRITER_CHIPMUNK_2D_IK_INVESTIGATION.md).
