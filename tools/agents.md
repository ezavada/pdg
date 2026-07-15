# Tools Agent Guide

This file applies to `tools`.

## Purpose

This directory contains the repo's development plumbing: binding generation, documentation generation, packaging, profiling, Node-plugin support, and helper utilities.

## High-Value Scripts

- `gen-script-interface.sh` and `gen-script-interface.ps1` generate binding output under `src/bindings/generated`.
- `make-idl.js` drives IDL and related generated interface/doc artifacts.
- `generate-js-docs.sh`, `generate-cxx-doxygen-docs.sh`, and `regen-doxygen-docs.sh` drive documentation generation.
- `make-node-module.sh` and `tools/node-pdg` handle the Node package/plugin side.
- Profiling helpers such as the DTrace scripts and GC-monitor docs support performance investigations.

## Editing Guidance

- When a generated artifact is wrong, fix the generator or its inputs here before patching emitted files elsewhere.
- Keep Windows and POSIX workflows aligned when both script variants exist.
- Prefer extending an existing script over adding a one-off helper if the workflow is part of normal development.
- `tools/node-pdg` is packaging/build integration for the Node plugin, so changes there often need a matching pass in `src` and sometimes `package.json`.
- Treat vendored tool trees such as `tools/npm`, `tools/jasmine`, and packaged archives conservatively.

## Documentation And Profiling Notes

- If you change developer workflows, update the corresponding README or script comments in this directory.
- Profiling helpers are platform-specific by design. Keep their assumptions explicit instead of pretending they are portable.

## Verification

- For generator changes, verify output paths, filenames, and headers remain stable.
- For packaging changes, verify the consuming build or wrapper still points at the expected artifacts.
- For script changes, prefer a small dry run or targeted invocation over broad regeneration when possible.
