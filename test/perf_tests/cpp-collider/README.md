# Collider and PhysicsBody performance

This native benchmark runs **2,000 dynamic PhysicsBodies and 2,000 Colliders**
through both the basic PDG solver and Chipmunk. It includes owner updates,
collision detection, contact response and native contact notifications. It does
not open a window, render, load artwork or execute JavaScript.

[Current measurements](CONTACT_REUSE_RESULTS.md) compare basic and Chipmunk
across five workloads for Sprite and Part owners, including sleeping and physical
accuracy, on an Apple M5 Max.

From the repository root, after configuring the engine:

```sh
cmake --build build/darwin/arm64/pdg --target pdg-collider-perf -j6
build/darwin/arm64/pdg/src/pdg-collider-perf --json /tmp/collider-sprites.json
build/darwin/arm64/pdg/src/pdg-collider-perf --owner part --json /tmp/collider-parts.json
```

Use your configured CMake build directory in place of `build/darwin/arm64/pdg` on
other platforms. The target is available with `BUILD_TESTING=ON` and links the
optimized `pdg-lib`, even when correctness tests link the debug engine. On a
multi-configuration generator, select Release and use its executable directory.
No display connection is required; headless builds are supported.

## Watch side by side

Generate a standalone browser player from the native benchmark:

```sh
cmake --build build/darwin/arm64/pdg --target pdg-collider-perf -j6
python3 test/perf_tests/cpp-collider/make-viewer.py
open artifacts/collider-viewer/index.html
```

Basic appears on the left, Chipmunk on the right, with synchronized clocks and
identical camera scales. Select separated circles approaching one another, touching
circles driven by opposing forces, stacks, piles or joint chains; switch between Sprite and Part owners or enable Chipmunk
sleeping. Use Play, slow motion, single steps and the timeline to compare motion.

This is **recorded playback of the actual C++ solvers**, including their initial
warmup, for 21.2 simulated seconds. Each run still simulates 2,000 dynamic bodies.
The player shows the first stack, chain or pile. Circle tests show all five speed
or force columns and six sampled rows covering the full offset or angle range.
Each circle pair is shown in its own local cell; pairs are spaced far apart in the
actual simulation to avoid collisions with neighboring pairs. Bodies can leave
their displayed cells after impact or separation. It does not run physics in
the browser or support dragging bodies. No server or internet connection is needed;
open the generated HTML in any modern browser. Generation takes a few minutes.

Use `--binary /path/to/pdg-collider-perf` for other build directories/platforms.
`--owner sprite`, `--steps 600` or `--no-sleep` shorten recording; `--output` changes
the HTML destination. Both solvers must be available in the executable. The
benchmark's `--record playback.json` option captures the sampled trajectories
without packaging them. Use runs **without recording** for performance measurements;
the player is for comparing physical behavior, and its playback speed is unrelated
to solver throughput.

## Circle workloads

| Scene | Rows, top to bottom | Columns, left to right |
| --- | --- | --- |
| `approach` | Right circle starts progressively lower: head-on through glancing impacts to a clear miss | First contact at 10, 7.75, 5.5, 3.25 and 1 seconds |
| `contacts` | Opposing forces rotate from directly inward (0°) to straight up/down (90°) | Force magnitude on each body: 0.5, 1, 2, 4 and 8 |

Both scenes use **1,000 independent pairs**, arranged as five columns and 200
rows. Each circle has radius 1, mass 1 and inertia 0.5. Gravity, friction, damping
and sleeping are disabled. Sprite and Part versions use the same physical inputs;
Parts belong to one host Sprite with no body or collider. The viewer uses cyan
for the initially left circle and orange for the right circle.

**Separated circles (`approach`).** Centers begin 6 units apart horizontally.
The right circle's vertical offset increases from 0 to 2.4 units (1.2 diameters).
Both circles move toward one another at equal horizontal speeds. For a colliding
pair with offset `d`, each speed is `(6 - sqrt(4 - d*d)) / (2*time)`, so first
contact occurs at the column's stated time regardless of row. For misses, speed
is `6 / (2*time)` and that time marks the closest pass. Restitution is 1 to show
elastic rebounds and deflection. With 2,000 bodies, 830 pairs should hit and 170
should miss. Validation checks that completed encounters occur near the scheduled
time, clear misses do not collide, and pairs never hit their neighbors.

**Touching circles (`contacts`).** Centers start exactly 2 units apart horizontally,
with no initial velocity and restitution 0. The left force is
`F * (cos(angle), -sin(angle))`; the right force is its opposite. On the first
contact-End event, both continuous forces are removed and never restarted.
The circles then continue under their existing velocities and normal collision
response. A zero-time contact inspection establishes the initial contact so even
a vertical pair that separates on its first step can cancel its forces. The top
row stays pressed together; lower rows slide apart. Yellow arrows show active
forces and disappear when a cell changes to “coasting.” JSON reports released
and still-driven pair counts; validation checks that force handles were removed.

From the repository root:

```sh
# Both circle tests, both solvers (default):
build/darwin/arm64/pdg/src/pdg-collider-perf --json /tmp/circle-pairs.json

# Individual scenes / Part owners:
build/darwin/arm64/pdg/src/pdg-collider-perf --scenario approach --owner part
build/darwin/arm64/pdg/src/pdg-collider-perf --scenario contacts --owner part
```

The simulation uses **0.01-second steps**, with 120 warmup steps followed by 2,000
measured steps by default: 21.2 simulated seconds total. Encounter times are
measured from initialization, including warmup. Runs shorter than 10 seconds do
not reach every approach collision. The benchmark runs as fast as possible;
reported milliseconds are wall time per step, unrelated to playback speed.

Options include `--bodies`, `--warmup`, `--steps`, `--solver basic|chipmunk|both`,
`--scenario approach|contacts|both|stack|chain|pile|quality|all`, `--owner sprite|part`,
and `--json PATH`. `both` means the two circle tests. With an odd body count, the
last body is stationary and unpaired; smaller counts use fewer rows/columns.
Counts must be positive integers, with at least two bodies. `--solver both` skips
Chipmunk if it was disabled at build time; explicitly requesting Chipmunk fails.

`--scenario sparse` remains available as a no-contact integration microbenchmark:
separated circles move together at velocity (0.1, 0.15), with radius 1, friction
0.3 and restitution 0. It is not shown in the visual player.

JSON includes setup time, mean/median/p95/maximum step time, body-steps per second,
contact notification counts and a final-state checksum. Setup, recording and
teardown are excluded from step timing. Contact callbacks, including force
cancellation, are included. Use repeated trials without another build or benchmark
competing for CPU time. There is no machine-dependent timing pass/fail threshold.
These numbers measure native engine work; they do not include rendering or
JavaScript callbacks. The solvers need not produce identical trajectories.

## Contact reuse and spatial hashing

Chipmunk now supplies the shared Collider events from its own contact manifolds.
PDG does not repeat broad/narrow-phase detection for pairs already solved in the
same native space. Basic, mixed-solver, static/static and zero-time queries retain
PDG's geometry path. Sleeping native contacts keep emitting Stay with zero new
impulse. The native regression suite verifies this, including sensors, shape
removal and wake/teleport transitions.

The engine still uses Chipmunk's default bounding-box tree. Spatial hashing is a
**broad-phase option**, independent of its iterative impulse solver. The benchmark
can choose either, without changing the engine default:

```sh
build/darwin/arm64/pdg/src/pdg-collider-perf --solver chipmunk --broadphase tree --json /tmp/tree.json
build/darwin/arm64/pdg/src/pdg-collider-perf --solver chipmunk --broadphase hash --cell-size 2 --hash-cells 20000 --json /tmp/hash.json
```

`--cell-size` defaults to 2 world units (the circles' diameter); `--hash-cells`
defaults to ten times `--bodies`. These apply only to Chipmunk. Compare separate
processes for tree and hash, and try cell sizes 1, 2 and 4. One run uses the selected
index for every native scene; it never silently attempts to change a hash back
into a tree. Chipmunk's author recommends the tree generally and suggests the hash
for large numbers of similar-size objects. See the
[author's spatial-index guidance](https://files.slembcke.net/chipmunk/release/ChipmunkLatest-Docs/).

## Physical quality: stacks, chains and piles

```sh
# Both solvers; 20 measured simulated seconds, plus 1.2 seconds warmup:
build/darwin/arm64/pdg/src/pdg-collider-perf --scenario quality --steps 2000 --json /tmp/quality.json
build/darwin/arm64/pdg/src/pdg-collider-perf --scenario quality --steps 2000 --owner part --json /tmp/quality-parts.json

# Let Chipmunk sleep quiet bodies after half a second:
build/darwin/arm64/pdg/src/pdg-collider-perf --solver chipmunk --scenario quality --steps 2000 --sleep-after .5 --json /tmp/quality-sleep.json
```

`--scenario stack|chain|pile` selects one quality case; `quality` selects all three;
`all` includes both original throughput cases as well. The default `both` retains
only `sparse` and `contacts`. `--iterations` sets Chipmunk's solver iteration count
(default 10). There is no matching basic-solver iteration option.

| Scene | Arrangement |
| --- | --- |
| `stack` | Groups of ten 2×2 boxes, initially stacked on a bodyless floor |
| `chain` | Groups of ten 2×0.4 links, pivoted end-to-end from a static anchor; initially horizontal |
| `pile` | Groups of forty 2×2 boxes dropped into separate bins, with deterministic positional and angular perturbations |

All quality cases have 2,000 dynamic bodies and colliders by default. Floors and
walls add bodyless static colliders; chains add one static body per group and one
pivot per dynamic link. JSON reports these extras separately. Part runs put the
dynamic bodies on independent Parts of one host Sprite; supporting scenery and
anchors remain Sprites in both owner variants. Final partial groups are supported.
Mass is 1; box inertia uses `(width² + height²)/12`, friction is 0.6 and restitution
is zero. Chains use linear/angular damping of 0.4 per second. Gravity is 9.8 world
units per second squared: native world gravity for Chipmunk, continuous body force
for the basic solver. Their integration and constraint algorithms differ; these
are equal physical inputs, not an expectation of identical trajectories.

Quality checks and measurements run **outside step timing**:

- Final maximum and RMS penetration use the same oriented-box separating-axis
  calculation for both solvers, including scenery. RMS covers overlapping pairs.
  Adjacent chain links are excluded because their pivot joint suppresses collision.
- Final maximum and RMS joint error measure the distance between the two world
  anchors of each pivot, independently of either solver's constraint statistics.
- Tail RMS linear speed (units/second), angular speed (radians/second) and movement
  per step (world units) cover the final simulated second, or all measured steps
  for shorter runs. Movement includes drift and positional correction; it is a
  residual-motion measure, not a spectral measurement of jitter.
- Settling requires **every** dynamic body below 0.05 units/second and 0.05
  radians/second for at least one simulated second. JSON reports the beginning
  of the final sustained quiet interval, including warmup in the time origin;
  `null` means the run has not settled. Motion resuming cancels an earlier result.
- Escaped bodies count stack/pile bodies below the floor or beyond their support
  area's horizontal limits. Sleeping bodies count actual native sleeping bodies. Chipmunk may retain a small
  cached velocity while a body sleeps; step motion then remains zero.
  These prevent a collapsed or departed scene from masquerading as good settling.

`--sleep-after 0` disables sleeping (default). Positive values enable it only in
Chipmunk quality scenes, with idle speed 0.05 units/second; the basic solver has no
sleeping implementation. Throughput scenes reject sleeping so they keep all bodies
active. Native collision slop remains Chipmunk's default 0.1 world units. Sleep and
iteration options are recorded in JSON. Larger iteration counts, tighter slop or
different scene scales can change both quality and cost; compare equal settings.

The executable checks the shared penetration and joint-error calculations against
known separated, overlapping, rotated and transformed-anchor examples before
running. It rejects nonfinite state and incorrect solver selection; physical
quality is reported rather than hidden behind arbitrary pass/fail thresholds.

## Published Physics documentation

Both the C++ and JavaScript Physics topic pages include the comparison tables and
this viewer. The tables come directly from `CONTACT_REUSE_RESULTS.md`; the shared
Doxygen source is `docs/physics/solver-comparison.dox`. The verified viewer snapshot
in `docs/physics/collider-viewer.html` contains losslessly compressed recordings.
Doxygen copies it into each reference and the downloadable documentation archive.
Ordinary docs builds do not compile or run the benchmark.

After recording and checking a new comparison, refresh the published snapshot:

```sh
python3 test/perf_tests/cpp-collider/make-viewer.py --from-viewer artifacts/collider-viewer/index.html --compact --output docs/physics/collider-viewer.html
tools/build-docs.sh
```

To update only the viewer UI while retaining the published simulations, use
`--from-viewer docs/physics/collider-viewer.html` with the same output path.
The packager reads the entire input before writing the result. It uses the current
`viewer.html` and `viewer.js` sources and supports both compressed and plain saved
viewers. Compression preserves every recorded number and frame. Current browsers
with `DecompressionStream` support can open the compressed file offline; the
uncompressed format remains the default for developer recordings.
