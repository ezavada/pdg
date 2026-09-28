# Engineering notes

For commands, runtime requirements, selection and artifacts, use the
[test suite guide](../../test/README.md). Notes describe a specific design,
investigation or validation scope; public API source references and current
code remain authoritative.

## Current test and validation references

- [Node 24.21 validation](NODE_24_21_UPGRADE.md): recorded native, Node, browser,
  simulator and Linux results; test counts describe that run.
- [Rig coverage](RIG_COVERAGE_AUDIT.md): maintained handoff/IK, playback and
  real-asset regression coverage.
- [Physics validation](PHYSICS_RIG_VALIDATION.md): tested configurations and limits.
- [Performance investigation](PERFORMANCE_INVESTIGATION_2026-09.md): measured
  rendering changes; [benchmark guide](../../test/perf_tests/README.md) for reproduction.
- [Timing](ANIMATION_TIMING_API_AUDIT.md) and
  [physics units](ANIMATION_PHYSICS_UNIT_AUDIT.md): current unit boundaries and checks.

## Design and implementation work

- [Feature priorities](PDG_FEATURE_WORKLIST.md)
- [Animation architecture](PDG_ANIMATION_API_EXTENSION_PROPOSAL.md) and
  [implementation checklist](PDG_ANIMATION_API_EXTENSION_CHECKLIST.md)
- [Part/PhysicsBody API work](ANIMATED_PART_API_CHANGE_LIST.md)
- [Physical rig contract and acceptance](ANIMATION_PHYSICS_RIG_PLAN.md)
- [Spriter integration gaps](ENHANCED_SPRITER_API_PROPOSAL.md)
- [Renderer status and future work](opengl-optimization-analysis.md)
- [Motion matching investigation](SPRITER_MOTION_MATCHING_INVESTIGATION.md)
- [Rigid Synfig conversion plan](SYNFIG_TO_SPRITER_RIG_CONVERSION_PLAN.md)
- [Web transport plan](WEB_NETWORK_TRANSPORT_PLAN.md)

Planned features are not supported APIs until implemented and verified. Keep
open work distinct from completed features and from platform/manual acceptance.
