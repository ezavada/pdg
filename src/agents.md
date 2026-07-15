# Source Tree Agent Guide

This file applies to `src`.

## What Lives Here

- `src/sys` holds the core engine, rendering, resources, serialization, networking, sound, Spriter support, and platform-specific backends.
- `src/app` holds the C++ application/UI framework.
- `src/js` holds JavaScript-side runtime helpers and the JavaScript port of the application framework in `src/js/mvc-app`.
- `src/inc` holds public headers.
- `src/bindings` holds native/JavaScript binding layers plus generated interface output.

## Working Rules

- Keep public API changes synchronized across `src/inc`, `src/sys`, `src/bindings`, `src/js`, docs, and tests.
- Treat `src/app` and `src/js/mvc-app` as conceptual siblings. If you change shared application-framework behavior, check whether the JavaScript port should match.
- The C++ app framework already uses `eventType_PortDraw`-driven drawing paths. Preserve that model unless the task explicitly requires a rendering-architecture change.
- Respect the split between GUI-capable builds and headless builds. Avoid accidentally making headless code depend on ports, OpenGL, or GUI-only events.
- Keep platform-specific changes scoped to the right backend directory instead of adding new `#ifdef` branches in shared code when a platform file can own the difference.

## Generated And Derived Files

- `src/bindings/generated/**` is generated output.
- Prefer editing the inputs in `src/bindings/common`, `src/bindings/javascript`, `src/bindings/node`, `src/bindings/jsc-ios`, and the generator scripts under `tools`.
- If you touch generated bindings, document why regeneration was not used.

## Useful Mental Model

- Native engine behavior usually starts in `src/sys`.
- Public C++ surface area is exposed from `src/inc`.
- JavaScript exposure flows through the binding layer and runtime helper files.
- App-framework behavior may also need mirrored test coverage in `test/spec` or `test/misc`.

## Verification

- For binding or public API changes, run the smallest relevant spec coverage under `test/spec`.
- For rendering, UI, or event changes, check `test/ui_tests`, `test/misc`, and any affected client-side specs.
- For platform-specific work, verify the target platform files still compile cleanly and do not break other backends conceptually.
