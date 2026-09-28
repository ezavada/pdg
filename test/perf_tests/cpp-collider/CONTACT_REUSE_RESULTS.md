# Basic vs Chipmunk — current results

<!-- [physics-solver-results] -->
Latest measurements with all implemented improvements, **2,000 dynamic bodies and colliders** per test. Stack and pile tests add static supports; chains add static anchors.

<strong>Mean time per simulation step, in milliseconds. Lower is faster.</strong> Each step advances 0.01 simulated seconds.

| Test | Owner | Basic | Chipmunk | Chipmunk with sleeping |
| --- | --- | ---: | ---: | ---: |
| Approaching circle pairs | Sprite | 0.536 | 0.789 | — |
| Approaching circle pairs | Part | 0.540 | 0.749 | — |
| Touching pairs with angled forces | Sprite | 0.566 | 0.818 | — |
| Touching pairs with angled forces | Part | 0.561 | 0.765 | — |
| Stacks of 10 boxes | Sprite | 1.559 | 2.346 | 1.499 |
| Stacks of 10 boxes | Part | 1.469 | 2.218 | 1.010 |
| Chains of 10 pivoted links | Sprite | 1.200 | 1.805 | 1.720 |
| Chains of 10 pivoted links | Part | 1.125 | 1.632 | 1.701 |
| Piles of 40 boxes | Sprite | 2.953 | 2.292 | 1.421 |
| Piles of 40 boxes | Part | 3.091 | 2.211 | 1.389 |

Basic and the main Chipmunk column keep all bodies awake. The last column enables Chipmunk sleeping after 0.5 seconds of inactivity; its timing includes the initial awake period. All 2,000 stack and pile bodies eventually slept. No chain bodies slept. “—” means sleeping was not tested for that workload.

The approach grid varies vertical offset by row and first-contact time from 10 to 1 seconds by column. Both solvers hit all 830 intended pairs and avoid all 170 misses, with at most 0.01 seconds of contact-time error. The touching grid varies force direction from inward to vertical and magnitude from 0.5 to 8; both solvers release 995 pairs and keep the five head-on pairs under force.

<strong>Physical accuracy and settling, with sleeping disabled.</strong> Errors are maximum world distances at the end of the run; lower is better. Boxes are 2 units wide. Settling times include warmup; “Unsettled” means the scene had not settled by 21.2 simulated seconds.

| Test | Owner | Error measured | Basic error | Chipmunk error | Basic settled at | Chipmunk settled at |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Stacks of 10 boxes | Sprite | Box overlap | 0.790635 | 0.001428 | Unsettled | 6.50 s |
| Stacks of 10 boxes | Part | Box overlap | 0.790635 | 0.001296 | Unsettled | 1.20 s |
| Chains of 10 pivoted links | Sprite | Joint anchor separation | 0.046692 | 0.000002 | Unsettled | Unsettled |
| Chains of 10 pivoted links | Part | Joint anchor separation | 0.046692 | 0.000002 | Unsettled | Unsettled |
| Piles of 40 boxes | Sprite | Box overlap | 0.897555 | 0.096559 | Unsettled | 11.93 s |
| Piles of 40 boxes | Part | Box overlap | 0.965468 | 0.097151 | Unsettled | 10.82 s |

Settling requires every body below 0.05 units/second and 0.05 radians/second for a full simulated second. No bodies escaped their test areas.

<strong>Measurement setup:</strong> Apple M5 Max, 48 GiB RAM, macOS arm64; optimized native engine, contact listeners enabled, no rendering or JavaScript. Chipmunk uses the default bounding-box tree and 10 solver iterations. All tests use 120 warmup steps. Circle results are medians of three run means over 2,000 measured steps; stack, chain and pile results each use one run of 2,000 measured steps. Small timing differences in the single-run tests should not be treated as conclusive. Measured 2026-09-22.

<!-- [physics-solver-results] -->

[Test definitions and run commands](README.md) · [Circle measurement data](circle-pair-measurements.json) · [Quality measurement data](contact-reuse-measurements.json)
