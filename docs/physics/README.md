# Physics solver comparison

`solver-comparison.dox` extends the Physics topic in both language references.
It includes the marked results section in
[`CONTACT_REUSE_RESULTS.md`](../../test/perf_tests/cpp-collider/CONTACT_REUSE_RESULTS.md),
so the published tables share the benchmark report's source.

`collider-viewer.html` is a generated, self-contained snapshot of verified native
benchmark recordings and the current player. Do not edit its embedded data or
JavaScript manually. It contains all five scenes, both owner types and optional
Chipmunk sleeping, with 2,000 bodies per run and 21.2 simulated seconds.

Regeneration commands and recording definitions are in the
[benchmark README](../../test/perf_tests/cpp-collider/README.md#published-physics-documentation).
Doxygen copies the snapshot through `HTML_EXTRA_FILES`; it is included in both
local references and packaged documentation, without running a simulation during
the docs build. Refresh the snapshot explicitly after tuning and verification.
