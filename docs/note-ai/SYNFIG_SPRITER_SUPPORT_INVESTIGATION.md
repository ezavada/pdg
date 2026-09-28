# Synfig and Spriter support in PDG

Investigation: 2026-09-08. Scope: 2D PDG animation, including Chipmunk-driven pose inputs.

## Recommendation

Keep Spriter as the first interactive skeletal-animation backend. Add Synfig asset support first through offline rendering to image sequences or sprite sheets. If live Synfig vector deformation is a requirement, evaluate an optional libsynfig backend separately, with an explicit distribution-license decision and measured rendering costs.

For live physics-driven characters authored in either tool, an additional option is converting a deliberately restricted Synfig cutout rig into a PDG-owned skeletal asset format. This preserves editable joints but does not preserve arbitrary Synfig effects. It is a compiler project, not simply another image importer.

Supporting both authoring tools is much easier than supporting both complete runtime semantics.

## Evidence and limits

Inspected PDG's existing Sprite/SpriteLayer integration, SpriterPlusPlus sources and license, and Synfig's public source at commit `2be773c501c0a233848d1b7b7134d96e28c45bcd` (master retrieved for this investigation). The inspected root CMake version is 1.5.5; this is a source snapshot, not a claim about the latest stable release. Synfig was downloaded to a temporary directory for inspection, not added as a PDG dependency. No renderer was built or benchmarked.

The [official developer overview](https://wiki.synfig.org/Dev%3AContribute_to_Code) identifies libsynfig as the shared engine behind the GUI and CLI. Older wiki implementation notes are treated as historical; API/build claims below were checked against source.

## Does Synfig have a library like SpriterPlusPlus?

Yes: **libsynfig**, a C++ animation evaluation and rendering library in `synfig-core`. However, its abstraction is an animated document and compositing graph, rather than a compact game-character instance that emits textured pieces.

Verified source interfaces:

| Requirement | Synfig source evidence |
| --- | --- |
| Separately linkable library | `synfig-core/src/synfig/CMakeLists.txt` declares `add_library(libsynfig SHARED ...)` and exports a CMake configuration |
| Load document | `loadcanvas.h`: `open_canvas_as(FileSystem::Identifier, ...)` |
| Evaluate at time | `canvas.h`: `Canvas::set_time(Time)` |
| Render into application-owned pixels | `target_scanline.h`: `Target_Scanline` with frame/scanline callbacks; `target.h`: canvas and render-description setters |
| Discover bones | `valuenodes/valuenode_bone.h`: named lookup, bone map and ordered bones |
| Drive bone parameters | `valuenode_bone.cpp`: origin, angle and parent links; `valuenode.h`: named link access; `valuenodes/valuenode_const.h`: mutable constant values |
| Offline sprite-sheet export | `modules/mod_png/trgt_png_spritesheet.cpp` |

These are building blocks for an adapter, not a verified game-runtime SDK with PDG-ready clips, events, sockets or IK. See the pinned [library target](https://github.com/synfig/synfig/blob/2be773c501c0a233848d1b7b7134d96e28c45bcd/synfig-core/src/synfig/CMakeLists.txt), [render target](https://github.com/synfig/synfig/blob/2be773c501c0a233848d1b7b7134d96e28c45bcd/synfig-core/src/synfig/target_scanline.h), and [bone interface](https://github.com/synfig/synfig/blob/2be773c501c0a233848d1b7b7134d96e28c45bcd/synfig-core/src/synfig/valuenodes/valuenode_bone.h).

## Comparison for PDG

| Area | Spriter / existing SpriterPlusPlus backend | Synfig / libsynfig |
| --- | --- | --- |
| Primary strength | Articulated bitmap characters and game-oriented playback | Vector morphing, bitmap deformation, layered effects and compositing |
| PDG integration today | Already integrated: loading, playback, blending, character maps, subentities, events, attachments and collision boxes | New loader, instance lifecycle, render output, metadata and bindings |
| Rendering fit | PDG image/file factories feed its existing drawing path | Initial full-fidelity route is render-to-pixels, then PDG texture upload |
| Runtime physics | Use the implemented pose/IK and shared physical-rig APIs | Drive selected graph controls before evaluation; mapping and invalidation unproven |
| Deformation | Inspected path primarily transforms textured pieces | Bone influence on vector artwork and skeleton deformation of bitmap artwork |
| Asset scale | Piece textures can be reused across poses | Vectors can be rerendered at a chosen resolution; rasterized output still has a resolution |
| Game semantics | Existing clips and gameplay-facing conventions | Define clip ranges, event tracks, sockets and hitboxes in an adapter/manifest |
| Performance expectation | Better fit for many independently animated characters | Cost depends on rendered pixels and graph/effect complexity; must benchmark |
| Build impact | Existing compilation and feature flags | Substantial dependency and packaging work, especially mobile/web |
| Runtime license | Local SpriterPlusPlus LICENSE is zlib | GPL-covered core; materially different distribution requirements |

Synfig's [official feature description](https://www.synfig.org/) documents vector tweening, numerous layer/effect types, bones and bitmap skeleton distortion. These features explain its visual appeal, but are also why a general Synfig-to-Spriter conversion cannot preserve everything.

No benchmark was run, so the performance comparison is an architectural expectation, not a measured speed ratio. Do not infer that Synfig cannot run interactively, or that its OpenGL source guarantees an efficient shared-texture integration. GPU context ownership and rendering coverage require separate validation.

## Four support strategies

### 1. Offline Synfig rendering: lowest integration cost

Run Synfig during asset production to export PNG frames or its existing PNG sprite-sheet target, then load those through PDG's frame-animation path. Add a manifest with frame rectangles, durations, origin/pivot, clip names, loop behavior and optional authored event/hitbox data. Verify PDG frame limits and atlas paging for large clips.

Benefits: preserves rendered artwork and effects at the exported resolution; no libsynfig dependency in the game; straightforward desktop/mobile/web consumption.

Costs: texture memory and export time; no runtime internal bone edits, IK, arbitrary vector zoom or continuous deformation. Chipmunk can move/rotate the whole sprite or select reaction clips, but cannot reposition a baked elbow. Frame-sampled sockets can be exported separately, but do not restore a live rig.

A hybrid can export separate rigid parts and animate them in PDG, but once parts are separated this becomes a restricted rig-conversion workflow and requires ownership/pivot metadata.

Synfig documents [PNG and sprite-sheet rendering targets](https://wiki.synfig.org/Render_options); the inspected PNG module confirms the sprite-sheet implementation still exists.

### 2. Live libsynfig rendering: highest fidelity

Create an optional backend that initializes the core/modules, loads a document, owns an independent mutable instance, applies named external controls, evaluates at the requested time, and renders one frame into an application-owned buffer. Convert pixel format/color/alpha conventions and update a reusable PDG texture.

Required engineering:

- Package core and required modules, fonts and linked media; resolve file identifiers through PDG resource conventions. Test document variants and missing resources rather than assuming all native formats work identically.
- Establish independent graph ownership per character. Do not mutate a cached shared document and accidentally change every instance. Verify clone/load caches and nested canvases.
- Build a one-frame target with explicit dimensions, canvas bounds and timing. Avoid rendering an entire timeline on each PDG tick.
- Measure CPU evaluation, rasterization, conversion, upload, allocations and worst-frame latency. Cache only when both time and external input state are unchanged.
- Define update/render thread ownership; avoid concurrent mutation of a graph while its renderer reads it.
- Add manifest-based clip ranges, events, sockets and hitboxes. Rendering pixels alone cannot supply semantic collision shapes.
- Keep Synfig unavailable as an explicit capability/build state on unsupported targets; do not silently substitute baked playback when a game requires live controls.

The inspected core CMake configuration requires packages including sigc++, GLib/GLibmm/GIOmm, libxml++, FFTW, PNG, JPEG, FreeType, FriBidi and HarfBuzz, plus zlib, Intl and threads. Additional dependencies are optional, and libltdl is linked. These are current configuration requirements, not proof that each is intrinsically necessary for a reduced renderer. The root CMake unconditionally adds Studio, so a core-only integration also needs an appropriate build/packaging entry point. See [core dependency configuration](https://github.com/synfig/synfig/blob/2be773c501c0a233848d1b7b7134d96e28c45bcd/synfig-core/src/CMakeLists.txt).

Windows/macOS/Linux support in Synfig does not establish iOS or Emscripten support. Shared-library/module loading and dependency cross-compilation need explicit investigation for PDG's targets.

### 3. Restricted Synfig-to-runtime conversion: preserves interactivity

The focused follow-up is [Synfig-to-Spriter rig conversion](SYNFIG_TO_SPRITER_RIG_CONVERSION_PLAN.md): emit SCML and rigid image parts, reuse PDG's existing runtime, and distinguish preserved articulation from sampled source constraint motion.

Define a supported authoring subset: rigid image parts, fixed parent hierarchy, pivots, transform tracks, named bones, sockets and hitboxes. Rasterize vector artwork into reusable parts offline; retain their transform animation as data. Either emit compatible Spriter data or a neutral PDG rig format.

This can share PDG's IK/Chipmunk layer and avoid embedding libsynfig. But arbitrary vector morphs, weighted deformation, masks, filters, expressions and animated reparenting do not reduce to textured rigid parts. Unsupported constructs must be rejected or explicitly baked. Sample complex animation curves to a documented error tolerance when exact conversion is unavailable.

No maintained general-purpose Synfig-to-Spriter converter was established in this investigation. Budget this as new exporter/compiler work, including asset validation and visual regression tests. Reusing Synfig's evaluator in a standalone build-time exporter is a separate option from copying its code into PDG.

### 4. External live renderer: specialized use only

A separate process could accept time/control inputs and return rendered frames. It adds IPC, frame-transfer latency, synchronization and deployment complexity, and fits poorly with mobile/browser delivery. It may be useful for authoring previews or tools. Do not treat a process boundary as an automatic licensing exemption; the coupling and distribution model still matter.

## Shared PDG architecture for both

Introduce a small internal animation-backend interface behind Sprite while retaining existing public Spriter behavior. Keep legacy `isSpriterSprite`, Spriter event IDs and Spriter-specific collision calls meaningful; add generic APIs separately rather than making them secretly mean any backend.

Common responsibilities: load/create instance, sample time, play/pause/seek, obtain bounds, render, report events, read named sockets and report capabilities. Advanced capabilities should be explicit: pose access, external parameters, IK, deformable mesh, character maps, hitboxes and subentities. A raster backend must not claim skeletal capabilities.

Keep backend objects out of JavaScript APIs. New public features need C++ declarations, source bindings, generated V8/JSC outputs and checks of Emscripten/mobile adapters, consistent with existing repository guidance. Existing SpriterPlusPlus submodule contents should remain unchanged.

The shared physics bridge should own semantic inputs such as hand target, aim angle, recoil impulse and influence weight. Each backend maps them differently:

```text
Chipmunk body/contact results
           |
    PDG control state / IK
           |
     +-----+------------------+
     |                        |
Spriter pose adapter     Synfig control adapter
     |                        |
rebuild descendants      evaluate value-node graph
     |                        |
draw image parts        render into PDG texture
```

The [Spriter/Chipmunk note](SPRITER_CHIPMUNK_2D_IK_INVESTIGATION.md) describes the implemented PDG pose/IK and physics ownership model. Synfig offers a promising alternative insertion point: wrap an authored angle expression with a procedural offset, or bind a dedicated exported control value. Replacing an animated value with a constant would discard its animation. Preserve the authored graph and test invalidation at unchanged time, when only physics input changes.

Synfig's bone lookup and graph links make this plausible, but no working live override was demonstrated. A core-source search did not identify a dedicated IK solver; historical roadmap claims or third-party templates should not be treated as a supported runtime API. Keep the proposed two-bone IK solver PDG-owned and test it independently.

PDG physical rigs sample desired poses before coordinated physics substeps and
publish final poses afterward. A future Synfig backend must follow that ownership
and scheduling contract without advancing time or emitting events twice.
Attachments, hitboxes and drawing must consume the same finalized pose.

## Licensing affects the architecture

PDG's local license is MIT-style and SpriterPlusPlus uses zlib. Synfig's repository declares GPLv3; inspected core headers include GPLv2-or-later notices. Neither is a permissive runtime grant or LGPL. Audit the chosen version and module inventory before distribution.

GNU's published interpretation is that static or dynamic linking to a GPL library makes the distributed combination subject to GPL requirements. This can fit a GPL-distributed PDG application, but is not the same distribution model as today's permissive runtime. Making the backend optional does not remove those requirements from builds that include it. Confirm the intended product distribution with qualified counsel before committing to embedded delivery. [GNU linking FAQ](https://www.gnu.org/licenses/gpl-faq.html.en#IfLibraryIsGPL)

Using Synfig offline to render your own artwork generally does not make the output GPL merely because the tool is GPL; output content and asset licenses still matter. This is a major practical advantage of the offline path. [GNU output FAQ](https://www.gnu.org/licenses/gpl-faq.html.en#WhatCaseIsOutputGPL)

## Staged implementation and acceptance checks

1. **Offline asset spike — small relative scope.** Export a representative Synfig clip, import frames/manifest into PDG, verify timing, alpha, pivot, bounds and texture budget. This proves useful dual-tool support without a second live runtime.
2. **Shared controls and Spriter pose spike — medium scope.** Complete the two-bone/physics experiment and define capabilities around actual needs, preserving existing Spriter tests.
3. **Optional desktop libsynfig spike — substantial scope.** Build core/modules separately; render a one-frame target; animate two independent instances; modify a named bone control while paused; verify its influenced artwork and a socket move together. Include both a simple cutout and a vector/effect-heavy example.
4. **Choose live integration or restricted conversion.** Compare asset fidelity, maintenance and distribution needs with measured costs. Only then commit to mobile/web ports, general rig metadata or complex blending.

Benchmark 1, 10 and 100 independent instances at several output sizes, recording cold load, steady-state time, p95/p99 frame time, memory and upload bandwidth. Treat these as workloads to measure, not promised supported counts. Test repeated seeks, clip loops, pause/resume, physics impulses, reflected/rotated roots, cleanup and two instances sharing source assets without sharing mutable pose state.

No calendar estimate is justified before the minimal core build and live-input spike. The offline path is bounded; full live support includes a renderer port, resource system, animation semantics, bindings and distribution work.
