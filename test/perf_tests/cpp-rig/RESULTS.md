# Articulated rig measurements — 2026-09-25

Local native run on Apple M5 Max, macOS 26.7 (25G229), using the optimized
`pdg-lib` and `pdg-rig-perf` CMake target. Run from the repository root with
`build/darwin/arm64/pdg/src/pdg-rig-perf` after the other validation builds finished.

All times are milliseconds. Each simulation interval advances 10 ms; the engine
may subdivide it for fast angular motion. Setup, mode changes and flip timings
cover the entire row, not an individual rig.

| Rigs | Physical Parts | Setup | Mean interval | p95 interval | Mode round trip | X-flip round trip |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 1 | 16 | 0.436 | 0.221 | 0.344 | 0.008 | 0.010 |
| 10 | 160 | 0.735 | 1.904 | 2.902 | 0.038 | 0.050 |
| 50 | 800 | 2.547 | 10.309 | 15.750 | 0.177 | 0.229 |
| 100 | 1,600 | 4.867 | 21.565 | 33.682 | 0.330 | 0.459 |

Each rig has 16 physical Parts, a coordinating Sprite body, a Kinematic axle,
30 internal constraints and one axle pivot. Measurements use 50 warmup intervals
and 200 recorded intervals, gravity and sustained 30 N m wheel torque. Mode timing
switches each wheel Dynamic → Driven → Dynamic. Reflection timing flips every
assembly horizontally and back. Final aggregate inertia/momentum must be finite.

Ten rigs fit comfortably inside a 10 ms interval on this machine; 50 rigs already
exceed that budget on average. These are single-run observations, not frame-rate
guarantees or regression thresholds. Collision masks exclude contacts; drawing,
JavaScript, floor contacts and collision-heavy crowds are not measured. Setup's
first row also includes initial cache costs. See [README.md](README.md) for the
fixture and reproduction details.
