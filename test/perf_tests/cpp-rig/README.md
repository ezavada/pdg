# Articulated rig benchmark

Build and run from the repository root:

```sh
cmake --build build/darwin/arm64/pdg --target pdg-rig-perf -j8
build/darwin/arm64/pdg/src/pdg-rig-perf
```

Requires Spriter and Chipmunk. Links the optimized native engine and opens no
window. Each rig is the wheel demo's 16 physical Parts plus a Kinematic axle and
the coordinating Sprite body. Thirty internal constraints and one axle pivot
connect each assembly. A sustained 30 N m torque powers each wheel against gravity.
Collision masks exclude contacts, isolating articulated control and joint costs.

CSV reports total setup time, mean/p95 wall time per 10 ms simulation interval,
a Dynamic → Driven → Dynamic round trip, and a horizontal-flip round trip for
1, 10, 50 and 100 rigs. Each run warms up for 50 intervals and measures 200.
Physics may subdivide an interval as angular speed increases. Mode/flip timings
cover all rigs in that row. Setup includes loading the fixture, with the first
row also paying initial resource/cache costs.

This measures the real engine, including pose/controller publication and shape
synchronization, without drawing or JavaScript. It is not a cross-platform frame
budget or a collision-heavy crowd benchmark. See [RESULTS.md](RESULTS.md) for the
recorded machine and measurements.
