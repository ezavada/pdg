# iOS Agent Guide

This file applies to `ios`.

## What Lives Here

- `pdg.xcodeproj` defines the iOS build and packaging setup.
- `pdg-Info.plist` and `InfoPlist.strings` hold app metadata.
- `test/main.js` is the iOS JavaScript test entry point.

## Editing Guidance

- Keep Xcode project edits minimal and intentional. `project.pbxproj` is easy to churn accidentally.
- iOS behavior usually spans this directory plus `src/sys/ios`, `src/sys/ipad`, and `src/bindings/jsc-ios`.
- The iOS build uses generated JavaScriptCore-facing bindings from `src/bindings/generated/jsc`. Prefer regenerating those files instead of hand-editing them.
- If you change app startup or runtime wiring, check both the Xcode project metadata and the native iOS platform files.
- If you change the iOS test harness, keep it aligned with `test/js/unit_test.js`, since `ios/test/main.js` is just a focused entry wrapper.

## Verification

- Verify plist or project-file changes for correctness and keep unrelated UUID churn out of commits.
- For runtime changes, validate that the iOS entry path still resolves `PDG_ROOT`, loads the intended test, and matches the current unit test flow.
