# Test Agent Guide

This file applies to `test`.

## Test Layout

- `test/spec` contains the main Jasmine-based behavioral spec suite.
- `test/lib/spec_runner.js` is the shared runner helper used by both client and headless entry points.
- `test/client_test.js` is the GUI/client-oriented spec entry.
- `test/node_test.js` is the headless Node-oriented spec entry.
- `test/cxx` contains native C++ tests.
- `test/misc` contains focused regression, reproduction, and behavior probes.
- `test/ui_tests` contains GUI drawing and `PortDraw`-oriented tests.
- `test/perf` contains performance benchmarks, not just pass/fail correctness checks.
- `test/data` and `test/sprinter-private` hold assets and fixtures.

## Editing Guidance

- Prefer adding or updating the narrowest test that proves the changed behavior.
- If you change a public API or runtime contract, update both GUI/client and headless coverage when the behavior exists in both modes.
- Keep shared runner behavior centralized in `test/lib/spec_runner.js` rather than duplicating path or environment logic.
- Treat `test/perf` baselines as performance artifacts, not routine correctness fixtures.
- Treat large asset trees and licensed sample packs conservatively. Do not rename, reformat, or churn them unless the task truly requires it.

## Runtime Expectations

- The test runners create artifacts under `artifacts/test-results/...` via `PDG_TEST_*` environment variables.
- GUI-side tests may rely on `PortDraw` events and an actual PDG client runtime.
- Headless Node tests should stay usable without GUI dependencies.

## Verification

- For GUI/client specs, use the client entry path under `test`.
- For headless behavior, use `test/node` or the equivalent platform wrapper.
- For native changes, update or run the relevant files in `test/cxx`.
- When fixing regressions, prefer leaving a focused reproducer in `test/misc` or `test/spec`.
