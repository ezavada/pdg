# Rig regression checks

Run `./test/rigs` from the repository root (Windows: `test\rigs.bat` or
`test\rigs.ps1`). Use `--list` to see checks, `human` to select all human-rig
checks, or `human/ground` to select one check. Multiple selections are supported.

These are headless integration checks of real rig assets and their controllers.
They require the built PDG Node addon with Chipmunk physics. The runner selects
Node using `PDG_NODE`, the bundled `tools/node`, then `node` on `PATH`; its Node
version must match the addon build. Real-time physics checks can take several
minutes in total.

Each check runs sequentially in its own process, with a three-minute timeout.
Failures do not stop later checks. Logs and a JSON summary are written under
`artifacts/test-results/<platform>/rigs/`, respecting `PDG_TEST_*` directory
overrides. A failed check makes the runner exit nonzero.

## Adding a rig

Create `test/rig_tests/<rig-name>/` and add standalone `<check-name>.test.js`
files. The runner discovers them automatically; helpers should use other filenames.
Keep assets in `test/data/`. Resolve asset paths relative to `__dirname` so direct
invocation also works from other directories.

Checks must exit nonzero on failure and print a line beginning `PASS:` only after
all assertions complete. A zero exit without that marker is a failure, preventing
an unexpectedly stopped event loop from reporting success. Release PDG layers and
stop its run loop when finished.

The human rig currently covers reference artwork, ground IK, arm blocking,
ragdoll recovery, pushes, hand control, elbow twist artwork, pose editing, and
membership changes.
