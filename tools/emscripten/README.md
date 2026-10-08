# Emscripten binding generation

Run from the repository root with Node and the C++ preprocessor available:

```sh
node tools/emscripten/generate.js
node tools/emscripten/generate.js --check
./test/tools emscripten-generation interface-metadata api-contracts
./test/unit --web --automated byte_arrays memblock configmanager filemanager polygon spline api_chaining
```

Generation uses `buildApi()` from `tools/build-interface-metadata.js`, without
loading a PDG runtime. The same source-owned declarations supply the JavaScript
IDL and TypeScript types. WebAssembly builds generate bindings before linking;
the makefile's `check-emscripten-bindings` target checks without modifying output.
`make-idl.js --embind-format` reports the replacement command.

## Sources and outputs

| Source | Purpose |
| --- | --- |
| `@pdg-class` annotations | Native class type, browser base, constructors, build guards and value-object fields |
| `@pdg-member` annotations | Browser participation, renamed entry points, native overloads and policies |
| `@pdg-adapter` annotations | Native adapter symbols and their declarations, signatures and lifetime information |
| `pdg_em_metadata.h` | Browser-specific mappings for shared exports and adapter entry points |
| `pdg_em_custom.inc` | Explicit custom adapter chains and lifecycle helpers |
| `manual-bindings.json` | API fingerprints requiring review when remaining manual contracts change |

The last three files live under `src/bindings/emscripten`. The generator writes
`pdg.embind`, `pdg_em_generated.js`, and `coverage.json` there. Do not edit those
outputs. There is no `pdg.embind.in` template: classes, inheritance, constants,
value objects, constructors and routine method registrations come from metadata.

## Remaining manual inventory review

The [manual member review](manual-bindings-review.json) covers all **72 entries**
remaining in `manual-bindings.json`. The [adapter review](adapter-bindings-review.json)
separately covers all **117 explicit adapter mappings**. Each mapping has one
primary reason; these are source audits, not runtime conformance claims.
Tooling tests require both reviews to match the current coverage inventory.

Current coverage is **917 generated**, **72 manual-unverified**, and **117 adapter**
entries. Following the signature audit, 29 manual registrations and 53 explicit
adapters moved to generation (82 additional generated entries). Domain-specific
JavaScript validation wrappers remain where needed; native generation coverage
does not mean all JavaScript wrappers are generated.

| Remaining manual reason | Members |
| --- | ---: |
| Defaults and validation still written in JavaScript | 17 |
| Overloads, argument reshaping and call dispatch | 8 |
| Structured records and collections | 8 |
| Callback interfaces and lifetimes | 7 |
| Serialization interfaces and script-object registry | 10 |
| Resource factories and Spriter lookup | 4 |
| Binary spans and 64-bit number representation | 6 |
| Platform forwarding, browser timers and placeholders | 9 |
| Chipmunk user-data and owner queries | 3 |

The manual status split is **50 implemented**, **4 guarded by Spriter support**,
**14 with no browser implementation found**, and **4 placeholders**. In particular:

- Three Chipmunk type/owner queries still lack browser mappings; the other
  65 methods use generated C-function dispatch.
- `EventManager.getDeviceOrientation` returns zero angles; `isButtonDown`,
  `isKeyDown` and `isRawKeyDown` return `false` unconditionally in the browser.
- The other 11 missing mappings are three fullscreen methods,
  `Serializer.serialize_ref`, `Serializer.sizeof_ref`,
  `Deserializer.deserialize_ref`, `Serializer.serialize_8u`, both Sprite drawing
  helper setters, `TileLayer.checkCollision` and `TileLayer.getMapData`.
  `Sprite.changeFramesImage` now has a generated native registration.

| Remaining adapter reason | Mappings |
| --- | ---: |
| C string conversion and lookup | 34 |
| Structured records, arrays and matrices | 20 |
| Output parameters and result assembly | 10 |
| Overload, shape and omitted argument dispatch | 11 |
| Binary spans and backing storage | 7 |
| Enums and 64-bit numeric representation | 17 |
| Serialization interface upcasts | 3 |
| Animation callback contexts and lifetime | 2 |
| File search handle lifecycle | 3 |
| Factories and platform integration | 5 |
| Legacy sound argument shape | 5 |

The reviews record concrete conversion requirements and next steps. For example,
Font style adapters preserve signed inputs before casting to uint32; replacing
those with direct unsigned Embind inputs rejects previously accepted `-1`.
Serializer interface upcasts, output arguments, byte-storage lifetime and
callback context lifetimes need more than pointer/reference qualifiers.

Support bindings, properties and JavaScript-only helpers are outside both public
method inventories. Missing implementations and placeholders require functionality
work, not just a different coverage label.

## Declaring browser mappings

Enable a class with a source-owned annotation:

```cpp
// @pdg-class {"name":"Example","native_binding":{"type":"pdg::Example","browser":{"generate":true,"constructors":[{"types":[]}]}}}
```

The class must already exist in the source inventory. Existing class annotations
should be extended rather than duplicated. Classes are emitted before their
native subclasses. `browser.base` overrides the shared native base when browser
composition differs; `null` explicitly registers no native base. A `browser.type`
override selects a backend-specific native implementation. `browser.guard`
accepts a macro name, `!MACRO`, or an array of conditions that must all hold,
and wraps the whole class. Member guards use the same syntax.

Own native instance methods are generated automatically for every generated
class unless its custom fragment already registers that public name or `_name`.
A routine `Example.getCount` needs no member annotation: the generator
derives `&pdg::Example::getCount`. **Unambiguous native methods do not need a
repeated C++ signature.** Compilation verifies the member pointer.
Overloaded methods require exact `signature` or `overloads` metadata;
JavaScript parameter types cannot establish native constness or references.
Simple coordinate forwarding bodies are an exception: the extractor records
the native call and local argument/result types as `native_value_call`. The
compiler selects the const or non-const `const T&` overload through
`EmscriptenValueMethod`. The rule requires one native call and an immediate
value conversion of its result; postprocessing remains manual. This preserves
the native RotatedRect argument even where the public API accepts Rect.
`binding_name` names an internal browser entry point, `symbol` overrides a native
symbol, and `allow_raw_pointers` / `return_policy` declare explicit Embind policies.

Set class `browser.defaults.exceptions: "javascript"` to translate
`std::exception` failures into JavaScript `Error` objects with the original
`what()` message for generated native instance methods, including const getters.
The generator emits the shared `EmscriptenCheckedMethod` adapter. Every generated
native class generates its own native instance methods directly from the public
IDL; no class-level `defaults.generate: true` is needed. Ordinary methods need
no `@pdg-member` annotation or empty `native_binding` object. Constructors, static methods,
JavaScript helpers, inherited copies and value-object field registrations are
excluded from this default. `browser.defaults.generate: false` can explicitly
disable automatic methods for a class.
Methods requiring conversion beyond the shared argument-type rules must declare
`browser.generate: false` or an explicit adapter mapping; the default does not
discover arbitrary native ABI differences.
For example:

```cpp
// @pdg-class {"name":"Example","native_binding":{"type":"pdg::Example","browser":{"generate":true,"defaults":{"exceptions":"javascript"}}}}
// @pdg-member {"name":"Example.setValue","native_binding":{"signature":"pdg::Example&(float)"}}
// @pdg-member {"name":"Example.customCallback","native_binding":{"browser":{"generate":false}}}
```

For native instance methods, the existing public `returns: "this"` contract
implies `return_policy: "reference"`; it need not be repeated in native mappings.
`EmscriptenReceiverMethod` discards the native result and JavaScript supplies the
original receiver. An unregistered native interface such as `ISerializer&` does
not need an Embind registration solely to support call chaining.
`EmscriptenOwnMethod` binds inherited member pointers to the exposed concrete
class, so methods inherited from an unregistered interface remain callable too.
Explicit return policies take precedence, including per-overload policies.
Adapters and private support bindings retain their explicit ownership policies.

Overloaded checked methods use the same exact `signature` metadata as ordinary
methods. A constexpr member-pointer cast selects the overload, since Embind's
`select_overload` is not constexpr. Member `browser.exceptions` overrides the
class default: `"native"` uses a direct call, `"javascript"` translates errors.
Member `browser.generate: false` leaves a method manual. These defaults belong
to the declaring class and do not propagate through native inheritance.
Constructors, static/root functions, free adapters and private support bindings
do not inherit the exception default. Explicitly requesting JavaScript exception
translation on a non-member mapping is rejected, as are unknown policies.

Native member arguments use `EmscriptenArgument<T>` conversion traits, selected
from the actual C++ method signature. `EasingFunc` accepts a numeric easing ID
and validates it before looking up the native function; `AnimationEvaluator`
accepts a JavaScript function through the shared evaluator adapter. The
`EmscriptenMethod<Method>::binding` selector preserves the original member pointer
when no conversion is needed. Checked methods apply the same conversions inside
their exception boundary. Overloaded methods still require an exact native
signature, but need no easing-only forwarding function.

The existing class `native_binding.ownership: "retained"` contract also generates
an `EmscriptenRetained<T>` specialization. Native `T*` parameters then accept
`shared_ptr<T>` handles and borrow their pointers for the call. Native `T*`
results acquire one reference with `addRef()` and return a shared handle whose
deleter calls `release()`. Null results remain null. These rules cover both
factories and getters without per-method annotations. They apply to pointer
parameters/results; native reference returns keep their existing policy.

For a generated retained class, registration includes
`.smart_ptr<std::shared_ptr<T>>("ClassHandle")`. A constructor with `types` instead
uses `.smart_ptr_constructor` and the shared `EmscriptenRetainedConstructor`:
allocation acquires a reference and handle destruction calls `release()`.
Existing custom smart-handle registrations are preserved without duplication.
Factory-only classes get handle registration without a public constructor.
Set `public: true` on a constructor mapping only when it covers the complete
public constructor contract; generation checks the declared parameter count and
records that constructor in API coverage. Overloaded factory APIs such as Image
remain separately reviewed.

Class `browser.pointer_policy: "borrowed"` supplies raw-pointer permission to
methods accepting that type and reference return policy to native getters.
For borrowed classes with `remember_receiver`, native getters return an identity
instead of constructing a deletable handle. JavaScript resolves it to the
registered object. Module factories register the original handle. This prevents
an owner lookup such as `Sprite.getLayer()` from deleting its layer when resolving
a duplicate wrapper. Borrowed references do not extend the owner's lifetime.

This replaces the routine ownership adapters for SpriteLayer's particle/sprite
factories and membership methods, Sprite's part lookups/transfers, and camera
getters on SpriteLayer and Port. Exception-only registrations use the class
exception policy. Structural conversions, reference-to-pointer adapters and
factories with additional loading behavior still require their own adapters.

Use `adapter` to select a declared `@pdg-adapter` when JavaScript and C++ need
conversion. Native adapter code owns conversion, exception handling and lifetime
behavior. A member may override its adapter's pointer/return policy for a
specific registration without duplicating the adapter declaration. Its registration is generated just like a direct method. The binding
translation unit must include its header. Ordinary adapters need no repeated
signature; overloaded adapters do.

Additional native entry points for an existing public method can be described
with `browser.registrations`, containing `name`, `signature` and optional
`return_policy` entries. This handles, for example, Polygon's separate native
point/rectangle centering entry points without inventing another public API.

Public constants use member mappings with `browser.generate`, optional `symbol`,
and optional `cast` (`int`, `unsigned` or `double`). Class constructors declare
native `types`, or a `factory` symbol and its pointer policy. Value-object class
mappings use `browser.kind: "value_object"`, native `type`, `binding_name` and
`fields`; the generator emits the field registrations.

Class `browser.support_bindings` entries generate backend helpers and existing
compatibility exports that lack a separate public IDL entry. Each supplies a
`name` and native mapping such as `symbol`, optional `signature`, and policies.
These are counted separately and do not create public API declarations. This
keeps internal event bridges, native identity helpers and existing aliases out
of custom C++ fragments when a direct registration suffices.

## Public JavaScript wrappers

Class `browser.events` declares event families once: an event constant, payload
discriminator field and method-to-action map. `extends` reuses another class's
families, and `selector` names an action-selecting subscription method such as
`on`. The generator checks the declarations and emits JavaScript subscriptions,
not nonexistent C++ methods. The shared installer preserves callback receivers,
filters actions/touches, returns handlers with cancellation, and rejects unknown
selector actions and invalid callbacks. It runs after the browser event bridge
installs `IEventHandler`. SpriteLayer reuses Sprite's families and adds layer events;
TileLayer inherits the installed helpers.

Value-return conversion is declared once on the returned class, beside its
JavaScript implementation. For example, Rect uses
`native_binding.browser.return_value: {"arguments":["$"]}` and Color uses
`{"arguments":["red","green","blue","alpha"]}`. `$` passes the entire native
value; other entries select fields as constructor arguments. Point, Offset,
Vector, Rect, RotatedRect, Quad and Color declare these rules. RotatedRect preserves
its angle and center offset; Quad construction copies its points.

For every generated method returning one of these public types, the generator
derives a conversion wrapper and the native name `_` plus the public name.
There is no per-method conversion annotation. Explicit `binding_name` still
overrides naming when necessary: Polygon's `centerPoint` getter uses
`_centerPointValue` because `_centerPoint` already names a centering overload.
Primitive returns and engine object handles have no value-construction rule.
Null and undefined results pass through; non-null values become independent
public class instances with their normal prototypes.

`installReturns` installs these conversions before handwritten argument adapters
and mixins capture public methods. Argument normalization can call that generated
method without repeating return conversion. Optional guarded exports are skipped
when absent; missing required entry points fail installation. Methods still in
the manual inventory are not automatically migrated, and arrays/unions require
their existing adapters. The rule applies to single declared class return types.

Borrowed argument views are also declared once on the expected class. Attributes
uses `native_binding.browser.argument` with
`{"alternatives":[{"type":"AnimatedAttributes","borrow":"_attributes"}]}`.
The generator derives argument positions from method signatures, including
variants sharing one native adapter. These variants must agree on the converted
slots; differing conversions require an overload-specific policy. The runtime
rejects unrelated and deleted alternative objects, borrows the adjusted native
base for the call, and never copies or deletes it. Constructors and mixins use
the generated `adaptArgument` helper with the same type rule.

Generated functions combine argument adaptation, validation, receiver tracking
and return conversion. The early and final installers merge policies on the same
function instead of stacking wrappers. Calls reuse their original arguments
unless a conversion changes a value; numeric conversion and borrowed-base
adjustment share at most one argument-array copy. For fixed-arity argument
adapters, the generator emits a direct call that needs no argument array even
when borrowing a base view. Mismatched arity and extracted numeric validation
use the shared validation path. Ordinary Attributes pass
through unchanged. Port drawing no longer needs handwritten conversion or
fluent-return method lists.
Helper modules are resolved during initialization so later calls still work if
an application replaces the browser's global module loader.

Retained class returns instead use a shared identity registry scoped to the
browser runtime. Repeated lookups return the existing live JavaScript object;
duplicate Embind handles release only their extra reference. Deleted wrappers
can be replaced, and the registry keeps weak references. Constructors and the
remaining custom adapters use this same registry for physics objects and cameras.
Class `browser.remember_receiver: true` also registers receivers of generated
instance methods, so native owner lookups can find a layer after membership or
factory calls. This is set once on SpriteLayer. Sprite factory cleanup tracking
and argument dispatch/validation remain where they do additional work.

The public `returns: "this"` contract also derives the native `_method` name
and a wrapper returning the original JavaScript receiver, including its concrete
subclass identity. No per-method name override or chaining wrapper is needed.
Animation script controls use these same names (`_group`, `_repeat`, `_stopIt`,
and so on). Playback/control wrappers still register evaluator owners; evaluator
arguments and ordinary easing arguments use the shared conversion rules below.
Early wrappers make single native entries available before mixins are copied;
`installReceivers` runs after argument adapters to preserve identity even when
an adapter discards the native result. Generated dispatchers receive that policy
without another wrapper; handwritten dispatchers remain opaque and are wrapped
when needed to preserve their behavior. Native errors
propagate unchanged. These rules apply to generated methods; manual mappings
retain their existing wrappers.

Numeric validation is also inferred from the shared C++ method body. The metadata
preprocessor records `REQUIRE_ARG_COUNT` and the supported `REQUIRE_NUMBER_ARG`,
`REQUIRE_INT32_ARG`, `REQUIRE_UINT32_ARG`, and 8/16/24/32-bit range macros.
`argument_validation` records exact arity, numeric type, integer bounds, and any
Int32/Uint32 conversion. A complete, uninterrupted validation prefix immediately
after the method signature is required. The binding macros' `CR` formatting
tokens count as whitespace, so shared size-query and animation macros participate.
Conditional checks, partial coverage,
optional arguments, overload branches and unsupported types do not opt into this
rule. There are no method-name exceptions or added member annotations.

For generated methods, this rule derives the underscore entry point and an early
public forwarding wrapper. `installValidation` merges validation into generated
methods, or wraps a remaining handwritten adapter. It checks the numeric type, applies any declared
conversion, then checks bounds, preserving native return values and exceptions.
For example, unsigned fixed-width serialization rejects fractional and nonfinite
inputs with `TypeError`, while `serialize_uint` accepts numeric nonfinite values
and converts them to zero. Signed 8/16-bit serialization converts to Int32 before
checking bounds. Null and nonnumeric inputs are rejected. Numeric conversions
follow V8/ECMAScript Int32/Uint32 semantics; existing JavaScriptCore conversion
macros differ for some negative/fractional inputs and are not changed here.
Arity failures use V8's `Error` behavior; JavaScriptCore currently uses `SyntaxError`.
The extracted rules participate in manual-mapping fingerprints too.

Set `browser.wrapper` to `{}` to generate a public wrapper. It supplies IDL
defaults, validates supported argument types, dispatches mapped overloads, and
returns the original receiver when the IDL says `this`. Remove the corresponding
handwritten wrapper when migrating it. These wrappers also apply the type-level
return rule, when present, after dispatch; multiple native entry points require
this argument wrapper to select the call.

Class `browser.defaults.arguments: "idl"` derives these wrappers for required
scalar parameters and simple optional scalar/class parameters too. This preserves
scalar type checks when handwritten forwarding wrappers are removed. Explicit native signatures, adapters and
overload registrations retain their own dispatch. A declared null default is
accepted without widening unrelated required class parameters to nullable types.

Argument conversion can also be declared once on a schema. `AnimationEvaluator`
declares `native_binding.browser.argument: "animation-evaluator"`; generated
wrappers use it for both `when` and `until`. The shared JavaScript bridge resolves
the actual playback target through a weak owner registry, preserving the
original JavaScript receiver even when a named script plays on another object.
The native adapter retains the callback, requires a synchronous boolean result,
and propagates callback errors. A missing live target wrapper is an error.

The source extractor recognizes native `easingIdToFunc(parameter)` and
`gEasingFunctions[parameter]` conversions and annotates the matching numeric
parameter with the `EasingFunction` contract. This uses neither method names nor
a required parameter name. Its schema selects native argument conversion; the
C++ `EasingFunc` trait performs the conversion itself. Defaults come from IDL.
Flat scalar/callback signatures using these schema rules get argument wrappers
automatically. Explicit native signatures, overload mappings and structural
adapters retain their existing dispatch unless `browser.wrapper` opts in.
For example, matrix animation still needs a matrix adapter, while `diminish`,
`increase`, `slowDown` and `speedUp` need no method-specific easing adapter.

Supported validation includes primitives, native class instances, Uint8Array,
unions, nullable types, aliases, records, arrays, dictionaries and function
values. A native value object accepting plain records needs a structural
contract; `object ClassName` checks for an instance. Unsupported types fail
wrapper generation. `browser.wrapper.constraints` supplies named parameter
`min`/`max` constraints.

Value-object classes can declare `browser.construct_from` with primitive types
accepted by their public JavaScript constructor. Generated overloads accept those
inputs and construct the value once, after choosing the overload. Color declares
`["string", "number"]` for color names and packed numeric colors; existing Color
instances and structural color records pass through unchanged. Null remains
invalid unless the parameter explicitly permits it.

Validation passes records and byte views through unchanged. Callbacks pass
through unless their schema selects a shared argument adapter. Other native
field conversion, callback retention, object identity and ownership rules still
require adapters. Byte wrappers introduce no payload copies; adapters retain
their existing copy/borrow behavior.

## Custom code and coverage

All 54 public classes have been audited for redundant browser mapping metadata:

| Class group | Generation policy |
| --- | --- |
| All 42 generated native classes, including the eight retained animation/physics classes | Generate own native instance methods by default; custom registrations and explicit exclusions preserve specialized adapters |
| Five native value objects | Generate field registrations and retain type-level value conversion rules |
| Remaining seven classes | JavaScript implementations or other non-generated registrations; no automatic native member generation |

Member annotations retain ABI overload signatures, adapters, renamed entry
points, capability guards, pointer handling and argument-wrapper configuration.
Fluent return policies are inferred or inherited from shared adapters, including
native overloads. Constructors and backend support bindings remain explicit.

`pdg_em_custom.inc` contains sections delimited by `@pdg-custom ClassName` and
`@pdg-end-custom`; `pdg` is the root-function section. Class sections are appended
to the generated registration chain. Duplicate sections, unscoped code and
unknown owners fail generation. A custom `.function("method", ...)` or
`.function("_method", ...)` takes precedence over automatic method generation;
no duplicate `generate:false` annotation is needed. Explicitly generated entries
that collide with custom native names fail generation. Use these fragments for custom lambda adapters,
exception-translation wrappers and code whose native mapping still needs work.
They should not accumulate routine registrations already expressible in metadata.
All `_Extra` macros have been removed; custom code is visible directly in these
sections rather than hidden behind another macro layer.

The class-wide audit covered all 54 public classes. SpriteLayer now has only its
two Spriter-loading factories explicitly excluded; TileLayer's own exclusions
are map-byte ownership and collision output parameters. Repeated subclass
exclusions for inherited implementations have been removed.

Remaining exclusions describe actual conversion or dispatch gaps:

| Area | Remaining custom work |
| --- | --- |
| Animation helpers | Callback ID registration/removal and JavaScript bookkeeping; native clear is generated |
| Sprites, images and tile maps | Loading, component reference returns, serializer interface pointers, buffer ownership, output parameters and draw callbacks |
| Chipmunk wrappers | User-data recovery for constraint type and Sprite owners; borrowed-handle lifetime contracts |
| Event/graphics/timer managers | Platform functions, fullscreen argument conversion and native-only timer user data |
| Serialization/logging | 64-bit number conversion, script references and byte-span input |

The eight retained classes keep only specialized methods and lifecycle support
in their custom fragments. The coverage report retains those APIs as manual;
an exclusion is not evidence
that a browser implementation exists.

The generated `src/bindings/emscripten/coverage.json` records current registration
and API coverage counts. Its wrapper counts describe installation policies;
receiver and validation policies can merge into an existing function, so their
sum is not the number of JavaScript wrapper functions. Registration and API
counts differ because methods may have multiple native entry points,
constructors may be wrapped, and custom headers also register bindings.

`manual-unverified` is not a claim that a method is missing, or that it works in
the browser. It marks native API contracts whose complete mapping still needs
review. Fingerprints include referenced schemas and owner mappings, so changes
require explicit review. After migrating a member, remove its fingerprint.
For a member remaining manual, inspect its implementation before updating its
fingerprint with the exported `fingerprint(member, owner, api)` helper. There is
no bulk command that silently accepts contract changes.

Generation rejects unclassified new APIs, changed manual contracts, stale manual
entries and duplicate generated registrations. Compiling and running browser
specs remains required: arbitrary C++ macros are not parsed to prove absence of
all conflicts with generated registrations. Keep native ownership and callback
lifetime contracts explicit rather than adding method-name exceptions to the
generator.

## Receiver-first C APIs

The shared binding implementation marks the actual native call with
`PDG_NATIVE_C_CALL(function, self, ...)`. Property macros use the same marker,
so getter/setter declarations supply their C symbols without per-member IDL
annotations. `PDG_NATIVE_C_CASE(predicate)` supplies native type predicates for
conditional properties. These macros execute normal C calls for V8/JSC;
metadata extraction records them as `native_c_dispatch` cases.

The generator emits one reusable `EmscriptenCDispatch` adapter, deriving the
receiver and native parameter types from the C function signature. It forwards
arguments in order. `cpVect` input uses the x/y value shape; the declared public
return type selects Point, Offset or Vector. Numeric and boolean results retain
their declared JavaScript types, and setters retain receiver returns for call
chaining. Unsupported transformations fail generation.

Joint-property dispatch uses Chipmunk's native predicates, independent of
user-data strings. Unsupported getters return `undefined` (also reflected in
IDL and TypeScript); setters throw `TypeError` before reaching joint-specific
Chipmunk assertions. `REQUIRE_C_INDEX_ARG` defines shared integer and dynamic
bounds checks for contact indices. Values outside the int32 domain produce
`TypeError`; integer indices outside the current contact count produce `RangeError`.

`test/unit --web --automated chipmunk_bindings` exercises all 65 migrated methods
with real spaces, all ten joint types, and contacts during collision callbacks.
The native fixture is compiled only for `WASM_BUILD=test`; it owns the borrowed
handles and is excluded from debug/release distributions. These checks do not
establish a new public handle-ownership or lifetime API.

## Native qualifiers in METHOD_SIGNATURE

Object types can carry a native pointer, lvalue-reference or rvalue-reference qualifier, with
optional pointee/referent `const`:

```cpp
METHOD_SIGNATURE("", [object PhysicsConstraint&], 1, (
    [object PhysicsBody&] other,
    [object Point const&] anchor = Point(0,0),
    [object Point const&] otherAnchor = Point(0,0)
));
```

The parser preserves public `object PhysicsBody` / `object Point` types and
records `native_qualifiers: {indirection: "reference", const: true/false}` on
parameters and `native_return_qualifiers` on the method. `*` records `pointer`;
`&&` records `rvalue-reference`, as used by the moving Drawing inputs.
Both leading and trailing referent const syntax are accepted. Multiple pointer
levels and top-level pointer const are rejected rather than
silently discarded. Unqualified signatures retain their existing behavior.

Generated member registrations check qualified native types against the actual
C++ member pointer at compile time, including argument position, pointee const,
return type and arity. Public variants that omit trailing arguments can share
one native signature. Explicit overloads are checked separately. A direct
native call that reorders its named arguments supplies `native_parameter_order`
from the implementation body. Native value conversions use their extracted
local type (for example Rect to RotatedRect). Explicit adapter functions and
extra browser registrations describe a separate ABI; their explicit C++
signatures remain authoritative instead of applying an unrelated public shape. Native method constness comes from the selected C++ member pointer.

Qualifiers describe access, not ownership or public nullability. Existing class
ownership metadata chooses retention versus borrowing. Retained `T&` results
retain the object's address and use the same canonical JavaScript identity as
retained pointer results. Retained `T&` and `const T&` inputs use checked handles;
null references are rejected before dereferencing. Pointer inputs retain their
public null/default rules. Const input does not imply TypeScript `Readonly<T>`.
Const retained results require an explicit exposure policy; generation rejects
them rather than casting away const to expose a mutable handle.
Fluent `this` calls discard the native result directly and return the original
JavaScript receiver, without retaining a temporary result handle.

Value-reference inputs keep structural value conversion. Value-object field
metadata supplies the accepted record shape. Constructor defaults such as
`Point(0,0)` create fresh values through parsed literal arguments, never eval.

The initial ownership migration covered 38 of 45 reviewed methods. The follow-up
also generates the seven previously held for argument/overload review:
`Part.attachSprite`, `Part.setupFrameCollider`, `Sprite.setupFrameCollider`,
`PhysicsBody.setBreakAngularSpeed`, and Camera's `transitionTo`, `lumaFadeTo`,
and `whipPanTo`. Existing domain validation remains in the public wrappers.
Component property readers and constructor identity helpers are outside that
method inventory. `Camera.getEffects()` returns a retained `Camera&` result.

Native `T&&` inputs now move from the existing script handle's object, without
transferring ownership of the handle itself. Move-only by-value results use a
fresh `unique_ptr`-owned result, avoiding Embind's copy constructor path. Quad
and RotatedRect arguments/results share structural value conversions. Qualified
native pointers also derive Embind's raw-pointer allowance; this enables the
call ABI and does not itself imply ownership transfer.

Native qualifiers never change value copies
into borrowed objects. In particular, const-reference Color/Point/Offset/Rect
results are still independent script values, and native by-value Polygon and
Attributes results remain values even when a wrapper allocates their storage.
