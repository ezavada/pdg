# Test Agent Guide

This file applies to `test`.

## Test Layout

- `test/spec` contains the main Jasmine-based behavioral spec suite.
- `test/lib/spec_runner.js` is the shared runner helper used by the native and Node unit entry points.
- `test/js/unit_test.js` is the native unit-spec entry.
- `test/js/unit_node_test.js` is the Node unit-spec entry.
- `test/cxx` contains native C++ tests.
- `test/rig_tests` contains asset/controller integration checks, run with `test/rigs`.
- `test/lib` contains shared harnesses, tooling checks (`test/tools`), and build-support payloads.
- `test/spec/fixtures` contains subprocess inputs used by behavioral specs.
- `test/ui_tests` contains GUI drawing and `PortDraw`-oriented tests.
- `test/perf_tests` contains performance benchmarks, not just pass/fail correctness checks.
- `test/data` holds assets and fixtures.

## Editing Guidance

- Prefer adding or updating the narrowest test that proves the changed behavior.
- If you change a public API or runtime contract, update both native and Node coverage when the behavior exists in both modes.
- Keep shared runner behavior centralized in `test/lib/spec_runner.js` rather than duplicating path or environment logic.
- Treat `test/perf_tests` baselines as performance artifacts, not routine correctness fixtures.
- Treat large asset trees and licensed sample packs conservatively. Do not rename, reformat, or churn them unless the task truly requires it.

## Runtime Expectations

- The test runners create artifacts under `artifacts/test-results/...` via `PDG_TEST_*` environment variables.
- GUI-side tests may rely on `PortDraw` events and a graphics-capable PDG runtime.
- Node unit tests should stay usable without GUI dependencies.

## Verification

- For native specs, use `test/unit` or the equivalent platform wrapper.
- For headless behavior, use `test/unit --node` or the equivalent platform wrapper.
- For native changes, update or run the relevant files in `test/cxx`.
- When fixing regressions, add coverage to `test/spec`, `test/cxx`, or the relevant `test/rig_tests` suite.
- Use `test/ui` for visual pages and `test/demo` for interactive demos; `test/README.md` documents all runners.
