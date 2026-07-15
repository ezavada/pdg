# Docs Agent Guide

This file applies to `docs`.

## Purpose

This directory mixes three kinds of material:

- hand-authored project and API documentation sources
- generated API output
- engineering notes and analyses

Keep those categories separate when you edit.

## Source Of Truth

- High-level project overview comes from `README.md` and `docs/cxx/dox/index.dox`.
- C++ API doc sources live primarily under `docs/cxx/dox`.
- JavaScript doc sources live primarily under `docs/javascript/dox` plus the IDL/doc-generation flow in `tools/make-idl.js` and related scripts.
- `docs/note-ai` contains design notes, migration plans, and analysis. It is helpful context, not automatically authoritative.

## Do Not Edit Generated Output First

- `docs/cxx/html/**` is generated Doxygen output.
- `docs/javascript/html/**` is generated Doxygen output.
- `docs/javascript/man/**` is generated manual-page output.
- `docs/pdg-js.js` is generated.
- `docs/editor/pdg-js.h` is generated.

When documentation is wrong, prefer fixing the source comments, Doxygen input, IDL generation, or generation scripts and then regenerating.

## Editing Guidance

- Keep the project description consistent with PDG's stated goals: cross-platform 2D engine, C++ and JavaScript entry points, Node integration, engine/runtime focus rather than high-level game logic.
- If you update examples or API docs, check whether both the C++ and JavaScript surfaces need the same clarification.
- Preserve historical or third-party reference material unless the task is specifically to modernize or replace it.
- If you update generator behavior, also update any script or note that explains the workflow.

## Regeneration Paths

- C++ Doxygen regeneration is driven by `tools/generate-cxx-doxygen-docs.sh`.
- JavaScript doc regeneration is driven by `tools/generate-js-docs.sh` and `tools/regen-doxygen-docs.sh`.
- IDL/doc source generation flows through `tools/make-idl.js`.

## Verification

- After source doc changes, confirm the changed file is actually a source file and not just a generated artifact.
- After generator changes, verify the generated output lands in the expected directories and preserves stable filenames.
