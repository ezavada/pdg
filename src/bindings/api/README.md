# Interface metadata from implementation code

The binding and JavaScript implementation files own the metadata. There is no
separate interface inventory, contract table, or adapter registry to maintain.
`docs/javascript/pdg-js.json` and `src/js/interface_metadata_data.js` are outputs.
Generated metadata and all IDL formats group constants, properties, constructors,
and methods in separate sections, with namespace classes after namespace functions.
Each section, schemas, and object fields use alphabetical order, comparing names
case-insensitively with a deterministic
case-sensitive tie break. Ordering no longer depends on prior generated output.
Parameter, overload, and base-class arrays retain their source order because
those positions carry meaning. Existing formatter sections remain intact.

`tools/interface-metadata-source.js` preprocesses the shared native binding
sources with extraction macros. `BINDING_CLASS`, `SINGLETON_CLASS`, `WRAPPER_CLASS`,
and `FACADE_CLASS` declare native classes. Export and method registrations provide
their public names (including aliases) and native types; `METHOD_SIGNATURE` provides briefs, parameter
names, overloads, defaults, and return types. The extractor parses the JavaScript
helpers without executing them, reading their inline `@pdg-member` declarations,
class inheritance, and explicit native superclass assignments in `pdg.js`.
Neither extraction nor runtime queries construct engine objects or invoke API
methods or property getters.
The `WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM` and
`WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY` macros provide retained ownership.
`SINGLETON_MANAGER_INITIALIZER_IMPL` provides singleton export names; static
wrapper assignments supply facade exports such as `pdg.fs`. Access notes are
generated from those names. Explicit native base registrations take precedence;
an unambiguous native superclass assignment also supplies native base metadata.
Use `[this]` in `METHOD_SIGNATURE` or `"returns":"this"` in `@pdg-member` for methods returning the
same receiver. This derives the chaining contract directly, including inherited
methods; an object return type alone does not imply receiver identity. Briefs
describe the operation, using the existing `.dox` brief where available. Reference
headers resolve `this` to the containing class, while structured metadata and
`describeInterface()` report `this` explicitly. New-object results keep their object types
and ownership contracts. Generic native property setters also report `[this]`.
Signatures can reference shared `@pdg-schema` definitions using
`[object AnimationDrawableOptions] options` for a record/context or
`[function AnimationDrawableCallback] callback` for a callback. The extractor
keeps declared class types such as `[object Drawing]` as class references; schema
references become `object`/`function` parameters with a schema contract. Named
schema results work the same way. Unknown names and incompatible schema kinds
fail generation. These references replace separate parameter contract annotations.
Generated reference headers omit repetitive chaining comments and, by default,
inherited methods. Use `--include-inherited` when a comparison needs them.

Reusable declaration and registration groups use `METHODS_FROM(klass, base, ...)`
to identify their originating interface. For example, `EMITTER_METHODS` and
`HAS_EMITTER_METHODS` identify EventEmitter, and the shared layer event group
identifies SpriteLayer. This macro emits the methods unchanged during normal
binding generation. Extraction marks matching methods as inherited when the
origin is in the class's ancestry. Different signatures and methods outside the
group retain their own declarations; composition alone does not imply inheritance.
Per-method JSON inheritance annotations are unnecessary for these groups.

Details not expressed by those declarations live beside the relevant code:

- `@pdg-class` marks JavaScript public classes and adds otherwise unavailable class details.
  Native classes do not need a name-only annotation; their declaration and export
  macros already supply that information.
- `@pdg-member` declares constructors, properties, and helpers without signature
  calls, or adds native binding details to an existing method. It must not repeat
  a signature already supplied by that method's implementation.
- `@pdg-contract` describes chaining, owned results, parameter constraints,
  callbacks, and property shapes for the named member.
- `@pdg-schema` declares a shared record or callback shape at its binding code.
- `@pdg-adapter` identifies an existing C++ adapter beside its declaration.

Small declarations use a line comment; larger declarations use a block comment:

```cpp
WRAPPER_INITIALIZER_IMPL_CUSTOM(Polygon, ...)

/* @pdg-member
{
  "name": "Polygon.moveTo",
  "native_binding": {
    "overloads": [
      {
        "binding_name": "_moveToPoint",
        "parameters": ["point"],
        "signature": "pdg::Polygon&(const pdg::Point&)",
        "return_policy": "reference"
      },
      {
        "binding_name": "_moveToXY",
        "parameters": ["x", "y"],
        "signature": "pdg::Polygon&(float, float)",
        "return_policy": "reference"
      }
    ]
  }
}
*/
METHOD_IMPL(Polygon, MoveTo)
    METHOD_SIGNATURE("", [object Polygon], 2, ({[object Point] point|number x, number y}));
```

Native binding data remains separate from the boolean `native` flag. Exact
native signatures and return policies select C++ overloads; adapter IDs refer
to named C++ implementations with conversion and lifetime descriptions. The
Embind formatter uses `select_overload` so compilation checks these signatures.
Remaining unannotated custom Embind bindings still require migration; missing
native overload declarations fail explicitly instead of being guessed.

Contracts retain the existing vocabulary: named `schemas`, `nullable`, `one_of`,
`literal`, state-dependent `condition`, and explicit ownership and lifetime.
A return type of `this` means the same receiver. Value-producing geometry methods
use an owned result contract instead. A missing member, parameter, or schema is
an error. `.dox` files own detailed behavioral prose and link to shared schemas.

Run `tools/node tools/build-interface-metadata.js` to regenerate the runtime
module, or use `--check` to detect stale output. CMake, Node packaging, and the
Emscripten makefile track the implementation files and regenerate this module.
Extraction requires the checked-out Node Acorn parser and a C++ preprocessor
(`clang`, `gcc`, or the executable specified by `PDG_METADATA_CPP`).

The runtime APIs work on native V8, Node, iOS JSC, and browser:

```js
pdg.getInterfaceMetadata();
pdg.getInterfaceMetadata('Polygon');
pdg.getInterfaceMetadata('Polygon', 'moveTo');
pdg.describeInterface('Polygon', 'moveTo');
```

Queries return independent copies and omit root exports absent from the build.
Constant values come from data descriptors; accessors remain unevaluated. Bad
selector types throw `TypeError`; unknown interfaces or members throw `RangeError`.
Native `METHOD_SIGNATURE` declarations have no runtime behavior. Use the structured
metadata API instead of calling native methods with `null` for introspection.

Regenerate references with `tools/make-idl-javascript.sh` and an up-to-date PDG
runtime. MVC retains separate `pdg-mvc-js.json` and `pdg-mvc-js.h` inventories.
For comparisons including inherited methods, pass `--include-inherited` to
that wrapper or directly to `tools/make-idl.js` with `--doxygen-h-format`,
or `--js-format`. JSON always includes inherited members;
the flag does not change native Embind registration.
Run `test/tools interface-metadata api-contracts` for extraction, contract, and
formatter checks; shared runtime specs live in `test/spec/interface_metadata.spec.js`.

### Structured declaration contracts

The shared contract vocabulary also supports:

- `items` for arrays and `values` for string-keyed dictionaries; `one_of` may
  reference recursive schemas (for example JSON data).
- Record `extends`, `methods`, `additional_properties` and an optional opaque
  `identity`. Class `mixins` supply public composition independently of the
  native wrapper superclass.
- Schema kinds `alias` (`value`), `constructor` (`params`/`returns`), `external`
  (`module`, `export`, optional `types_package`) and `event_map` (`entries` from
  symbolic numeric constants to payload contracts).
- Member `event_map` relationships identify the selector and callback parameters,
  return contract and optional fallback payload. The TypeScript generator uses
  these relationships to infer event callback parameters.
- Parameter `rest` and contract `when_type` for an explicitly selected overload
  type. The latter refines matching parameters without widening other overloads.
- Explicit `builtin: "object"` or `"unknown"` for genuinely opaque/open data.
  Bare unresolved `object`, `array` and `function` signatures remain omissions.
- Return-contract `variants`, selected by `runtimes`, for backend differences.
  Every variant contains its actual type contract.

Class `construction.kind` distinguishes `public`, `factory`, `singleton`,
`borrowed` and `abstract`. Public construction is inferred from explicit
constructor members; factory/singleton policies are extracted from wrapper
macros where possible. A non-public policy cannot coexist with a constructor.

The loader supplies `runtime_profile` when installing metadata. The captured
runtime and graphics/sound/network capabilities identify the generated inventory;
they do not certify other builds or every instance member. TypeScript declarations
and their coverage report retain that scope. Keep release profile validation
separate from declaration completeness.

Animated script composition uses `batch()/endBatch()`, `series()/endSeries()`,
`andAlso()`, `playScript()`, `mark(name, saveState = true)` and
`jumpToMark(name, restoreState = true)` in C++ and JavaScript. `Troupe` inherits
that surface and manages borrowed nested Animated membership. `stagger(seconds)`
offsets the whole selected block per member and adds no delay on one target.
Keep native builders, shared binding macros, browser generation and method
references aligned when changing these contracts.

Animation lifecycle handlers use `on(event, handler)` on the selected operand.
`started` and `finished` are local to that operand; `mark`, `yoyo`, `repeat`,
`scriptFinished` and `untilFired` propagate through enclosing blocks.
Handlers receive `AnimationEvent` records after scheduler publication. Sprite
numeric `on()` continues to return an event subscription; string lifecycle
events return the receiver. Callback resources reject portable snapshots.

The same lifecycle registration is available through `onStarted(handler)`,
`onFinished(handler)`, `onScriptFinished(handler)`, `onMark(handler)`,
`onYoyo(handler)`, `onRepeat(handler)` and `onUntilFired(handler)`.
Each helper returns the receiver and preserves `on()` scope and timing.
