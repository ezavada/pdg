# 2,000-body measurements — 2026-09-22

Apple M5 Max, 48 GiB RAM, macOS arm64. Optimized native `pdg-lib` and benchmark,
using the working tree based on `d0b449039` with the Collider/PhysicsConstraint
implementation and independent-Part publication fix. Each row is measured in
three separate runs, alternating Sprite and Part owners. No concurrent build or
other test was running during these measurements.

Each scene has **2,000 dynamic bodies and 2,000 circle colliders**, sleeping
disabled, native contact listeners enabled, and no rendering. Each run uses 120
warmup steps and 600 measured steps of 0.01 simulated seconds. See
[README.md](README.md) for commands, geometry, forces and exclusions.

Times below are milliseconds of wall time per simulation step. “Mean” and “p95”
are the medians of the three run-level statistics; the range shows all three means.

| Owner | Solver | Scene | Mean | Mean range | p95 |
| --- | --- | --- | ---: | ---: | ---: |
| sprite | basic | sparse | 0.507 | 0.494–0.510 | 0.544 |
| sprite | basic | contacts | 0.811 | 0.778–0.829 | 0.933 |
| sprite | chipmunk | sparse | 0.946 | 0.940–0.953 | 1.077 |
| sprite | chipmunk | contacts | 2.403 | 2.382–2.467 | 4.515 |
| part | basic | sparse | 0.502 | 0.501–0.503 | 0.525 |
| part | basic | contacts | 0.774 | 0.772–0.776 | 0.804 |
| part | chipmunk | sparse | 1.673 | 1.665–1.677 | 1.758 |
| part | chipmunk | contacts | 2.568 | 2.526–2.678 | 4.681 |

Every contact scene delivered 1,200,000 notifications over the measured steps:
1,000 pairs × 2 recipients × 600 steps. Sparse scenes delivered zero. All final
body positions, rotations and velocities were finite. Each measured step also
verified the expected number of contact notifications outside its timed region.
These are CPU simulation measurements,
not frame-rate predictions or a solver-accuracy comparison.

The initial 2,000-Part trial exposed redundant whole-host refreshes during each
independent Part's body publication. Publication now refreshes dependent children
when needed and updates a leaf's own attachment directly. The measurements above
include that correction. Parent/child, physical attachment, and lifetime behavior
remain covered by the native owner regression suite.

Raw per-run JSON was written to `/tmp/pdg-collider-perf-{sprite,part}-{1,2,3}.json`
during validation. New runs can record their own JSON with `--json`; these sample
numbers are observations, not pass/fail thresholds.
