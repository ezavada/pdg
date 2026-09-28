# Linux physics validation

Run `bash test/docker/physics` from a Docker-enabled host. It builds an Ubuntu
24.04 toolchain image and runs native C++ physics-owner, PhysicsBody and pose
tests, plus Spriter playback with Chipmunk. A second headless build disables both
Spriter and Chipmunk to check shared Basic-solver contracts and capability guards.

The checkout is mounted read-only. A named `pdg-physics-linux-build` volume holds
the isolated source copy and incremental Linux builds. Logs and JUnit results go
to `artifacts/test-results/linux-docker/`. `PDG_JOBS` defaults to 6.

This lane does not validate a Linux desktop, JavaScript runtime, or imported rigs
on the Basic solver. Animation physics requires Chipmunk by design.
