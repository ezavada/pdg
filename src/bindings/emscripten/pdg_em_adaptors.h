// this header file contains all the code that adapts between the JavaScript and C++ classes, which
// do not always have identical method signatures

#include "pdg/framework.h"
#include "pdg/sys/attributes.h"
#include "pdg/sys/drawing.h"
#include "pdg/sys/particle.h"

#include "config-unix.h"

#include "../javascript/memblock.h"

#include <emscripten/val.h>
#include <memory>
#include <type_traits>
#include <utility>
#include "pdg_em_signature.h"

namespace pdg {

// Argument conversion is selected by the actual C++ parameter type, including
// overload-selected methods. No method-specific easing/evaluator thunk is needed.
EasingFunc emscriptenEasingArgument(double id);
AnimationEvaluator browserAnimationEvaluator(emscripten::val callback);
AnimationEventHandler browserAnimationEventHandler(emscripten::val callback);
// Specializations are generated from native_binding.ownership, once per type.
template<class T> struct EmscriptenRetained : std::false_type {};
template<class T> struct EmscriptenBorrowedIdentity : std::false_type {};
// Keep the definition visible wherever retention is instantiated, including
// optimized adapter builds that cannot borrow an out-of-line instantiation.
template<class T> std::shared_ptr<T> browserRetain(T* value) {
    if (!value) return nullptr;
    value->addRef();
    return std::shared_ptr<T>(value, [](T* object) { object->release(); });
}
template<class T, class... Args> struct EmscriptenRetainedConstructor {
    static std::shared_ptr<T> create(Args... args) {
        return browserRetain(new T(std::forward<Args>(args)...));
    }
};
RotatedRect browserCameraRect(const emscripten::val& value);
emscripten::val browserCameraRectValue(const RotatedRect& value);
template<class T, class = void> struct EmscriptenArgument {
    using Wire = T;
    static constexpr bool converted = false;
    static T from(Wire value) { return value; }
};
template<class T> struct EmscriptenArgument<T*, std::enable_if_t<EmscriptenRetained<std::remove_const_t<T>>::value>> {
    using Wire = std::shared_ptr<std::remove_const_t<T>>;
    static constexpr bool converted = true;
    static T* from(const Wire& value) { return value.get(); }
};
// References to retained objects share pointer retention, but cannot accept null.
template<class T> struct EmscriptenArgument<T&, std::enable_if_t<EmscriptenRetained<std::remove_const_t<T>>::value>> {
    using Wire = std::shared_ptr<std::remove_const_t<T>>;
    static constexpr bool converted = true;
    static T& from(const Wire& value) {
        if (!value) emscripten::val::global("TypeError").new_(std::string("Expected a non-null object reference")).throw_();
        return *value;
    }
};
// Native move inputs consume the object's contents, not its script handle.
template<class T> struct EmscriptenArgument<T&&> {
    using Wire = T&;
    static constexpr bool converted = true;
    static T&& from(Wire value) { return std::move(value); }
};
Quad emscriptenQuadFromVal(const emscripten::val& value);
emscripten::val emscriptenQuadValue(const Quad& value);
template<> struct EmscriptenArgument<const Quad&> {
    using Wire = emscripten::val;
    static constexpr bool converted = true;
    static Quad from(const Wire& value) { return emscriptenQuadFromVal(value); }
};
ParticleTrailOptions browserParticleTrailOptions(const emscripten::val& value);
template<> struct EmscriptenArgument<const ParticleTrailOptions&> {
    using Wire = emscripten::val;
    static constexpr bool converted = true;
    static ParticleTrailOptions from(const Wire& value) { return browserParticleTrailOptions(value); }
};
template<class T, class = void> struct EmscriptenResult {
    using Wire = T;
    static constexpr bool converted = false;
};
// A native move-only value is a fresh result. Transfer its storage to Embind;
// do not ask Embind's default value policy to invoke a deleted copy constructor.
template<class T> struct EmscriptenResult<T, std::enable_if_t<std::is_class_v<T> &&
    std::is_move_constructible_v<T> && !std::is_copy_constructible_v<T>>> {
    using Wire = std::unique_ptr<T>;
    static constexpr bool converted = true;
    static Wire from(T value) { return std::make_unique<T>(std::move(value)); }
};
template<class T> struct EmscriptenResult<T*, std::enable_if_t<EmscriptenRetained<T>::value>> {
    using Wire = std::shared_ptr<T>;
    static constexpr bool converted = true;
    static Wire from(T* value) { return browserRetain(value); }
};
template<class T> struct EmscriptenResult<T&, std::enable_if_t<EmscriptenRetained<T>::value>> {
    using Wire = std::shared_ptr<T>;
    static constexpr bool converted = true;
    static Wire from(T& value) { return browserRetain(&value); }
};
template<class T> struct EmscriptenResult<T*, std::enable_if_t<EmscriptenBorrowedIdentity<T>::value>> {
    using Wire = uintptr_t;
    static constexpr bool converted = true;
    static Wire from(T* value) { return reinterpret_cast<uintptr_t>(value); }
};
template<> struct EmscriptenArgument<const RotatedRect&> {
    using Wire = emscripten::val;
    static constexpr bool converted = true;
    static RotatedRect from(const Wire& value) { return browserCameraRect(value); }
};
template<> struct EmscriptenResult<RotatedRect> {
    using Wire = emscripten::val;
    static constexpr bool converted = true;
    static Wire from(const RotatedRect& value) { return browserCameraRectValue(value); }
};
template<> struct EmscriptenResult<Quad> {
    using Wire = emscripten::val;
    static constexpr bool converted = true;
    static Wire from(const Quad& value) { return emscriptenQuadValue(value); }
};
// The compiler selects const/non-const overloads from source-derived value types.
template<class Owner, class Result, class Argument> struct EmscriptenValueMethod {
    static constexpr auto select(Result (Owner::*method)(const Argument&) const) { return method; }
    static constexpr auto select(Result (Owner::*method)(const Argument&)) { return method; }
};
template<> struct EmscriptenArgument<EasingFunc> {
    using Wire = double;
    static constexpr bool converted = true;
    static EasingFunc from(Wire value) { return emscriptenEasingArgument(value); }
};
template<> struct EmscriptenArgument<AnimationEvaluator> {
    using Wire = emscripten::val;
    static constexpr bool converted = true;
    static AnimationEvaluator from(Wire value) { return browserAnimationEvaluator(value); }
};
template<> struct EmscriptenArgument<AnimationEventHandler> {
    using Wire = emscripten::val;
    static constexpr bool converted = true;
    static AnimationEventHandler from(Wire value) { return browserAnimationEventHandler(value); }
};

// Unconverted methods keep their original member pointer. Converted methods
// use a shared thunk; checked methods also translate std::exception to JS Error.
template<class Owner, class Signature> using EmscriptenMethodPointer = Signature Owner::*;
// A method inherited from an unregistered native interface must bind to the
// exposed concrete class, not to the interface's Embind type ID.
template<class Registered, auto Method> struct EmscriptenOwnMethod;
template<class Registered, class Owner, class Result, class... Args, Result (Owner::*Method)(Args...)>
struct EmscriptenOwnMethod<Registered, Method> {
    static constexpr auto pointer = static_cast<Result (Registered::*)(Args...)>(Method);
};
template<class Registered, class Owner, class Result, class... Args, Result (Owner::*Method)(Args...) const>
struct EmscriptenOwnMethod<Registered, Method> {
    static constexpr auto pointer = static_cast<Result (Registered::*)(Args...) const>(Method);
};
template<auto Method> struct EmscriptenMethod;
template<auto Method> struct EmscriptenCheckedMethod;
template<class Owner, class Result, class... Args, Result (Owner::*Method)(Args...)>
struct EmscriptenMethod<Method> {
    static typename EmscriptenResult<Result>::Wire call(Owner& owner, typename EmscriptenArgument<Args>::Wire... args) {
        if constexpr (EmscriptenResult<Result>::converted)
            return EmscriptenResult<Result>::from((owner.*Method)(EmscriptenArgument<Args>::from(args)...));
        else return (owner.*Method)(EmscriptenArgument<Args>::from(args)...);
    }
    static constexpr auto binding = [] {
        if constexpr (EmscriptenResult<Result>::converted || (EmscriptenArgument<Args>::converted || ...)) return &call;
        else return Method;
    }();
};
template<class Owner, class Result, class... Args, Result (Owner::*Method)(Args...)>
struct EmscriptenCheckedMethod<Method> {
    static typename EmscriptenResult<Result>::Wire call(Owner& owner, typename EmscriptenArgument<Args>::Wire... args) {
        try { return EmscriptenMethod<Method>::call(owner,args...); }
        catch (const std::exception& error) {
            emscripten::val::global("Error").new_(std::string(error.what())).throw_();
        }
    }
};

template<class Owner, class Result, class... Args, Result (Owner::*Method)(Args...) const>
struct EmscriptenMethod<Method> {
    static typename EmscriptenResult<Result>::Wire call(const Owner& owner, typename EmscriptenArgument<Args>::Wire... args) {
        if constexpr (EmscriptenResult<Result>::converted)
            return EmscriptenResult<Result>::from((owner.*Method)(EmscriptenArgument<Args>::from(args)...));
        else return (owner.*Method)(EmscriptenArgument<Args>::from(args)...);
    }
    static constexpr auto binding = [] {
        if constexpr (EmscriptenResult<Result>::converted || (EmscriptenArgument<Args>::converted || ...)) return &call;
        else return Method;
    }();
};
template<class Owner, class Result, class... Args, Result (Owner::*Method)(Args...) const>
struct EmscriptenCheckedMethod<Method> {
    static typename EmscriptenResult<Result>::Wire call(const Owner& owner, typename EmscriptenArgument<Args>::Wire... args) {
        try { return EmscriptenMethod<Method>::call(owner,args...); }
        catch (const std::exception& error) {
            emscripten::val::global("Error").new_(std::string(error.what())).throw_();
        }
    }
};

class FileManager;

// A public `this` result is supplied by JavaScript. Do not expose a native
// interface return (e.g. ISerializer&) solely to discard it in that wrapper.
template<auto Method, bool Checked> struct EmscriptenReceiverMethod;
template<class Owner, class Result, class... Args, Result (Owner::*Method)(Args...), bool Checked>
struct EmscriptenReceiverMethod<Method, Checked> {
    static void call(Owner& owner, typename EmscriptenArgument<Args>::Wire... args) {
        if constexpr (Checked) {
            try { (owner.*Method)(EmscriptenArgument<Args>::from(args)...); }
            catch (const std::exception& error) {
                emscripten::val::global("Error").new_(std::string(error.what())).throw_();
            }
        } else (owner.*Method)(EmscriptenArgument<Args>::from(args)...);
    }
};
template<class Owner, class Result, class... Args, Result (Owner::*Method)(Args...) const, bool Checked>
struct EmscriptenReceiverMethod<Method, Checked> {
    static void call(const Owner& owner, typename EmscriptenArgument<Args>::Wire... args) {
        if constexpr (Checked) {
            try { (owner.*Method)(EmscriptenArgument<Args>::from(args)...); }
            catch (const std::exception& error) {
                emscripten::val::global("Error").new_(std::string(error.what())).throw_();
            }
        } else (owner.*Method)(EmscriptenArgument<Args>::from(args)...);
    }
};

void emscriptenEventEmitterAddBridge(EventEmitter& emitter, long eventType,
                                     const emscripten::val& jsEmitter);
void emscriptenSpriteAddEventBridge(Sprite& emitter, long eventType,
                                    const emscripten::val& jsEmitter);
void emscriptenSpriteLayerAddEventBridge(SpriteLayer& emitter, long eventType,
                                         const emscripten::val& jsEmitter);
void emscriptenEventManagerAddEventBridge(EventManager& emitter, long eventType,
                                          const emscripten::val& jsEmitter);

// extend the config manager to handle API differences between C++ and Javascript

// TODO: add this to ConfigManager

class ConfigManagerWrap : public ConfigManagerUnix {
public:
    std::string& getConfigString(std::string& arg0);
    long getConfigLong(std::string& arg0);
    float getConfigFloat(std::string& arg0);
    bool getConfigBool(std::string& arg0);
};

// @pdg-adapter {"name":"ConfigManager.useConfig","value":{"symbol":"pdg::emscriptenConfigUseConfig","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"bool(pdg::ConfigManager&, const std::string&)"}}
bool emscriptenConfigUseConfig(ConfigManager& manager, const std::string& name);
/* @pdg-adapter
{
  "name": "config.get-string",
  "value": {
    "symbol": "pdg::emscriptenConfigGetString",
    "header": "src/bindings/emscripten/pdg_em_adaptors.h",
    "signature": "emscripten::val(pdg::ConfigManager&, const std::string&)",
    "conversions": {
      "result": "native-out-string-or-undefined"
    }
  }
}
*/
emscripten::val emscriptenConfigGetString(ConfigManager& manager, const std::string& key);
// @pdg-adapter {"name":"ConfigManager.getConfigLong","value":{"symbol":"pdg::emscriptenConfigGetLong","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"emscripten::val(pdg::ConfigManager&, const std::string&)"}}
emscripten::val emscriptenConfigGetLong(ConfigManager& manager, const std::string& key);
// @pdg-adapter {"name":"ConfigManager.getConfigFloat","value":{"symbol":"pdg::emscriptenConfigGetFloat","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"emscripten::val(pdg::ConfigManager&, const std::string&)"}}
emscripten::val emscriptenConfigGetFloat(ConfigManager& manager, const std::string& key);
// @pdg-adapter {"name":"ConfigManager.getConfigBool","value":{"symbol":"pdg::emscriptenConfigGetBool","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"emscripten::val(pdg::ConfigManager&, const std::string&)"}}
emscripten::val emscriptenConfigGetBool(ConfigManager& manager, const std::string& key);
// @pdg-adapter {"name":"ConfigManager.setConfigString","value":{"symbol":"pdg::emscriptenConfigSetString","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"void(pdg::ConfigManager&, const std::string&, const std::string&)"}}
void emscriptenConfigSetString(ConfigManager& manager, const std::string& key, const std::string& value);
// @pdg-adapter {"name":"ConfigManager.setConfigLong","value":{"symbol":"pdg::emscriptenConfigSetLong","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"void(pdg::ConfigManager&, const std::string&, long)"}}
void emscriptenConfigSetLong(ConfigManager& manager, const std::string& key, long value);
// @pdg-adapter {"name":"ConfigManager.setConfigFloat","value":{"symbol":"pdg::emscriptenConfigSetFloat","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"void(pdg::ConfigManager&, const std::string&, float)"}}
void emscriptenConfigSetFloat(ConfigManager& manager, const std::string& key, float value);
// @pdg-adapter {"name":"ConfigManager.setConfigBool","value":{"symbol":"pdg::emscriptenConfigSetBool","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"void(pdg::ConfigManager&, const std::string&, bool)"}}
void emscriptenConfigSetBool(ConfigManager& manager, const std::string& key, bool value);

// @pdg-adapter {"name":"MemBlock.MemBlock","value":{"symbol":"pdg::emscriptenCreateEmptyMemBlock","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"pdg::MemBlock*()","allow_raw_pointers":true}}
MemBlock* emscriptenCreateEmptyMemBlock();
SpriteLayer* emscriptenCreateSpriteLayer();
TileLayer* emscriptenCreateTileLayer();

#ifndef PDG_NO_GUI
emscripten::val emscriptenGraphicsGetCurrentScreenMode(GraphicsManager& manager, int screenNum);
emscripten::val emscriptenGraphicsGetNthSupportedScreenMode(GraphicsManager& manager, int n, int screenNum);
Port* emscriptenGraphicsCreateWindowPort(GraphicsManager& manager, const Rect& rect, const std::string& name, int bpp);
Port* emscriptenCreatePort(long width, long height);
uintptr_t emscriptenPortGetIdentity(Port& port);
Font* emscriptenGraphicsCreateFont(GraphicsManager& manager, const std::string& name, float scalingFactor);
void emscriptenPortDrawImage(Port& port, Image* image, const emscripten::val& destination, const Attributes& attributes);
void emscriptenPortDrawDrawing(Port& port, const Drawing& drawing, const emscripten::val& destination, const Attributes& attributes);
void emscriptenPortDrawText(Port& port, const std::string& text, const emscripten::val& destination, const Attributes& attributes);
int emscriptenPortGetTextWidth(Port& port, const std::string& text, int size, uint32 style, int len);
int emscriptenPortStartTrackingMouse(Port& port, const Rect& rect);
SpriteLayer* emscriptenCreateSpriteLayerForPort(Port* port);
TileLayer* emscriptenCreateTileLayerForPort(Port* port);
std::string emscriptenFontGetName(Font& font);
float emscriptenFontGetHeight(Font& font, int size, int style);
float emscriptenFontGetLeading(Font& font, int size, int style);
float emscriptenFontGetCapHeight(Font& font, int size, int style);
float emscriptenFontGetAscent(Font& font, int size, int style);
float emscriptenFontGetDescent(Font& font, int size, int style);
#ifdef PDG_SPRITER_SUPPORT
void emscriptenSpriteSeekAnimation(Sprite& sprite, const std::string& clip, double seconds);
void emscriptenSpriteTransitionToAnimation(Sprite& sprite, const std::string& clip, double seconds, double duration);
void emscriptenSpriteSetupAnimationPhysics(Sprite& sprite,emscripten::val values);
void emscriptenSpriteSetAnimationPhysicsMode(Sprite&,int,double,bool,double,int);
int emscriptenSpriteGetAnimationPhysicsMode(const Sprite&,double,bool);
void emscriptenSpriteSetAnimationPhysicsDriveSettings(Sprite&,double,double,double,double,int,double,bool);
emscripten::val emscriptenSpriteGetAnimationPhysicsDriveSettings(const Sprite&,uint32_t);
emscripten::val emscriptenSpriteGetAnimationPhysicsSetupWarnings(const Sprite& sprite);
uint32_t emscriptenSpriteAddAnimationDrawable(Sprite& sprite,emscripten::val callback,emscripten::val values,const std::string& slot);
emscripten::val emscriptenSpriteGetAnimationDrawBounds(const Sprite& sprite);
uint32_t emscriptenSpriteAddAnimationIK(Sprite& sprite, emscripten::val config, int order);
emscripten::val emscriptenSpriteGetAnimationIKResult(const Sprite& sprite, uint32_t id);
uint32_t emscriptenSpriteAddAnimationModifier(Sprite& sprite, emscripten::val callback, int stage, int order);
bool emscriptenSpriteEnableAnimationPose(Sprite& sprite, const std::string& clip);
emscripten::val emscriptenSpriteGetAnimationPose(const Sprite& sprite);
emscripten::val emscriptenSpriteSampleAnimationPose(const Sprite& sprite, const std::string& clip, double seconds);
emscripten::val emscriptenSpriteGetAnimationBoneNames(const Sprite& sprite);
emscripten::val emscriptenSpriteGetAnimationBindingNames(const Sprite& sprite);
emscripten::val emscriptenSpriteGetAnimationBoneTransform(const Sprite& sprite, const std::string& name, int space);
emscripten::val emscriptenSpriteGetAnimationBindingTransform(const Sprite& sprite, const std::string& name, int space);
void emscriptenSpriteSetAnimationBoneTransform(Sprite& sprite, const std::string& name, const emscripten::val& transform);
bool emscriptenSpriteHasAnimation(Sprite& sprite, const emscripten::val& animation);
void emscriptenSpriteStartAnimation(Sprite& sprite, const emscripten::val& animation);
void emscriptenSpriteBlendToAnimation(Sprite& sprite, const emscripten::val& animation, float blendTime);
void emscriptenSpriteApplyCharacterMap(Sprite& sprite, const std::string& name);
void emscriptenSpriteRemoveCharacterMap(Sprite& sprite, const std::string& name);
emscripten::val emscriptenSpriteGetAppliedCharacterMaps(const Sprite& sprite);
bool emscriptenSpriteHasAttachPoint(const Sprite& sprite, const std::string& name);
Offset emscriptenSpriteGetAttachPoint(const Sprite& sprite, const std::string& name);
void emscriptenSpriteAttachSprite(Sprite& sprite, Sprite* attached, const std::string& name);
Sprite* emscriptenSpriteGetAttachedSprite(const Sprite& sprite, const std::string& name);
void emscriptenSpriteActivateSubEntity(Sprite& sprite, const std::string& entity, const std::string& animation);
bool emscriptenSpriteIsCollisionActive(const Sprite& sprite, const std::string& name);
emscripten::val emscriptenSpriteGetCollisionBox(const Sprite& sprite, const std::string& name);
emscripten::val emscriptenSpriteGetCollisionBoxName(const Sprite& sprite, int index);
Sprite* emscriptenLayerCreateSpriteFromFile(SpriteLayer& layer, const std::string& path, const std::string& entity);
Sprite* emscriptenLayerCreateSpriteFromEntity(SpriteLayer& layer, const std::string& entity);
void emscriptenLayerApplyCharacterMap(SpriteLayer& layer, const std::string& name);
void emscriptenLayerRemoveCharacterMap(SpriteLayer& layer, const std::string& name);
#endif
#endif
#ifndef PDG_NO_SOUND
void emscriptenSoundChangePitch(Sound& sound, float target, ms_delta duration);
void emscriptenSoundChangeOffset(Sound& sound, int32 target, ms_delta duration);
void emscriptenSoundFadeOut(Sound& sound, ms_delta duration);
void emscriptenSoundFadeIn(Sound& sound, ms_delta duration);
void emscriptenSoundChangeVolume(Sound& sound, float target, ms_delta duration);
Sound* emscriptenResourceGetSound(ResourceManager& manager, const std::string& soundName);
#endif


Image* emscriptenCreateImage(const std::string& path);
ImageStrip* emscriptenCreateSnapshotImage();
emscripten::val browserSnapshotObject(const ISerializable* value);
ISerializable* browserSnapshotPointer(const emscripten::val& value);
ImageStrip* emscriptenCreateImageStrip(const std::string& path);
Sound* emscriptenCreateSound(const std::string& path);
/* @pdg-adapter
{
  "name": "image.bounds-at",
  "value": {
    "symbol": "pdg::emscriptenImageGetBoundsAt",
    "header": "src/bindings/emscripten/pdg_em_adaptors.h",
    "signature": "pdg::Rect(pdg::Image&, const pdg::Point&)",
    "conversions": {
      "at": "copy-point-for-mutable-native-reference"
    },
    "return_policy": "copy"
  }
}
*/
Rect emscriptenImageGetBoundsAt(Image& image, const Point& point);
Image* emscriptenImageGetSubsection(Image& image, const Rect& rect);

void emscriptenResourceSetLanguage(ResourceManager& manager, const std::string& language);
std::string emscriptenResourceGetLanguage(ResourceManager& manager);
int emscriptenResourceOpenFile(ResourceManager& manager, const std::string& filename);
std::string emscriptenResourceGetString(ResourceManager& manager, int id, int substring);
size_t emscriptenResourceGetSize(ResourceManager& manager, const std::string& resourceName);
// @pdg-adapter {"name":"ResourceManager.getResource","value":{"symbol":"pdg::emscriptenResourceGet","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"emscripten::val(pdg::ResourceManager&, const std::string&, int)"}}
emscripten::val emscriptenResourceGet(ResourceManager& manager, const std::string& resourceName, int maxSize);
Image* emscriptenResourceGetImage(ResourceManager& manager, const std::string& imageName);
ImageStrip* emscriptenResourceGetImageStrip(ResourceManager& manager, const std::string& imageName);

void emscriptenAttributesSetLineStyle(Attributes& attributes, int style);
void emscriptenAttributesSetFitType(Attributes& attributes, int fit);
void emscriptenAttributesSetBlendMode(Attributes& attributes, int mode);
void emscriptenAttributesSetTransform(Attributes& attributes, const emscripten::val& matrix);
Attributes* emscriptenAnimatedAttributesBase(AnimatedAttributesBase& self);
void emscriptenAnimatedAttributesChangeTransform(AnimatedAttributesBase& self, const emscripten::val& matrix, double seconds, int easing);

void emscriptenAttributesTransform(Attributes& attributes, const emscripten::val& matrix);
emscripten::val emscriptenAttributesGetTransform(Attributes& attributes);
int emscriptenAttributesGetLineStyle(Attributes& attributes);
int emscriptenAttributesGetGradientType(Attributes& attributes);
int emscriptenAttributesGetFitType(Attributes& attributes);
int emscriptenAttributesGetBlendMode(Attributes& attributes);

emscripten::val emscriptenElementGetControlPoints(ElementRef& element);
ElementRef* emscriptenDrawingAddText(Drawing& drawing, const std::string& text, const Rect& rect, const Attributes& attrs);
std::string emscriptenElementGetText(ElementRef& element);
void emscriptenElementSetText(ElementRef& element, const std::string& text);
// @pdg-adapter {"name":"Drawing.addText","value":{"symbol":"pdg::emscriptenDrawingAddText","header":"src/bindings/emscripten/pdg_em_adaptors.h","allow_raw_pointers":true}}
// @pdg-adapter {"name":"ElementRef.getText","value":{"symbol":"pdg::emscriptenElementGetText","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}
// @pdg-adapter {"name":"ElementRef.setText","value":{"symbol":"pdg::emscriptenElementSetText","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}
Attributes* emscriptenElementGetAttributes(ElementRef& element);
int emscriptenElementGetType(ElementRef& element);

// @pdg-adapter {"name":"FileManager.findFirst","value":{"symbol":"pdg::emscriptenFileFindFirst","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"emscripten::val(pdg::FileManager&, const std::string&)"}}
emscripten::val emscriptenFileFindFirst(FileManager& manager, const std::string& pattern);
/* @pdg-adapter
{
  "name": "file.find-next",
  "value": {
    "symbol": "pdg::emscriptenFileFindNext",
    "header": "src/bindings/emscripten/pdg_em_adaptors.h",
    "signature": "bool(pdg::FileManager&, emscripten::val)",
    "conversions": {
      "ioFindData": "inout-find-record"
    }
  }
}
*/
bool emscriptenFileFindNext(FileManager& manager, emscripten::val findData);
// @pdg-adapter {"name":"FileManager.findClose","value":{"symbol":"pdg::emscriptenFileFindClose","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"void(pdg::FileManager&, const emscripten::val&)"}}
void emscriptenFileFindClose(FileManager& manager, const emscripten::val& findData);

void emscriptenLogInitialize(LogManager& manager, const std::string& baseName, int mode);
void emscriptenLogWrite(LogManager& manager, int level, const std::string& category, const std::string& message);

// @pdg-adapter {"name":"TileLayer.loadMapData","value":{"symbol":"pdg::emscriptenTileLoadMapData","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"void(pdg::TileLayer&, const emscripten::val&, int, int, int, int)"}}
void emscriptenTileLoadMapData(TileLayer& layer, const emscripten::val& data, int width, int height, int dstX, int dstY);
int emscriptenTileGetType(TileLayer& layer, long x, long y);
void emscriptenTileSetType(TileLayer& layer, long x, long y, int tileType, int facing);
emscripten::val emscriptenTileGetTypeAndFacing(TileLayer& layer, long x, long y);

void emscriptenSerializerSerialize8(Serializer& serializer, double value);
void emscriptenSerializerSerializeString(Serializer& serializer, const std::string& value);
// @pdg-adapter {"name":"Serializer.serialize_mem","value":{"symbol":"pdg::emscriptenSerializerSerializeMem","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"void(pdg::Serializer&, const emscripten::val&)"}}
void emscriptenSerializerSerializeMem(Serializer& serializer, const emscripten::val& value);
uint32 emscriptenSerializerSizeofString(Serializer& serializer, const std::string& value);
// @pdg-adapter {"name":"Serializer.sizeof_mem","value":{"symbol":"pdg::emscriptenSerializerSizeofMem","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"uint32(pdg::Serializer&, const emscripten::val&)"}}
uint32 emscriptenSerializerSizeofMem(Serializer& serializer, const emscripten::val& value);
MemBlock* emscriptenSerializerGetData(Serializer& serializer);

double emscriptenDeserializerDeserialize8(Deserializer& deserializer);
std::string emscriptenDeserializerDeserializeString(Deserializer& deserializer);
MemBlock* emscriptenDeserializerDeserializeMem(Deserializer& deserializer);
// @pdg-adapter {"name":"Deserializer.setDataPtr","value":{"symbol":"pdg::emscriptenDeserializerSetData","header":"src/bindings/emscripten/pdg_em_adaptors.h","signature":"void(pdg::Deserializer&, const emscripten::val&)"}}
void emscriptenDeserializerSetData(Deserializer& deserializer, const emscripten::val& data);

uint32 emscriptenSpriteLayerGetSerializedSize(SpriteLayer& layer, Serializer& serializer);
void emscriptenSpriteLayerSerialize(SpriteLayer& layer, Serializer& serializer);
void emscriptenSpriteLayerDeserialize(SpriteLayer& layer, Deserializer& deserializer);

class FileManager : public Singleton<FileManager> {
public:
	static FileManager* createSingletonInstance();
//     findFirst();
//     findNext();
//     void findClose();
    std::string&  getApplicationDataDirectory();
    std::string&  getApplicationDirectory();
    std::string&  getApplicationResourceDirectory();
};

void setSerializationDebugMode(bool);

void emscriptenInit();
void emscriptenIdle();
void emscriptenQuit();
bool emscriptenIsQuitting();

enum {
    action_ErasePort = SpriteLayer::action_ErasePort,
    action_PreDrawLayer = SpriteLayer::action_PreDrawLayer,
    action_PostDrawLayer = SpriteLayer::action_PostDrawLayer,
    action_DrawPortComplete = SpriteLayer::action_DrawPortComplete,
    action_AnimationStart = SpriteLayer::action_AnimationStart,
    action_PreAnimateLayer = SpriteLayer::action_PreAnimateLayer,
    action_PostAnimateLayer = SpriteLayer::action_PostAnimateLayer,
    action_AnimationComplete = SpriteLayer::action_AnimationComplete,
    action_LayerFadeInComplete = SpriteLayer::action_FadeInComplete,
    action_LayerFadeOutComplete = SpriteLayer::action_FadeOutComplete
};

} // end namespace pdg

// @pdg-adapter {"name":"LogManager.initialize","value":{"symbol":"pdg::emscriptenLogInitialize","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"LogManager.writeLogEntry","value":{"symbol":"pdg::emscriptenLogWrite","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}



// @pdg-adapter {"name":"ResourceManager.setLanguage","value":{"symbol":"pdg::emscriptenResourceSetLanguage","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"ResourceManager.getLanguage","value":{"symbol":"pdg::emscriptenResourceGetLanguage","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"ResourceManager.openResourceFile","value":{"symbol":"pdg::emscriptenResourceOpenFile","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"ResourceManager.getImage","value":{"symbol":"pdg::emscriptenResourceGetImage","header":"src/bindings/emscripten/pdg_em_adaptors.h","allow_raw_pointers":true}}

// @pdg-adapter {"name":"ResourceManager.getImageStrip","value":{"symbol":"pdg::emscriptenResourceGetImageStrip","header":"src/bindings/emscripten/pdg_em_adaptors.h","allow_raw_pointers":true}}

// @pdg-adapter {"name":"ResourceManager.getString","value":{"symbol":"pdg::emscriptenResourceGetString","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"ResourceManager.getResourceSize","value":{"symbol":"pdg::emscriptenResourceGetSize","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Serializer.serialize_8","value":{"symbol":"pdg::emscriptenSerializerSerialize8","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Serializer.serialize_str","value":{"symbol":"pdg::emscriptenSerializerSerializeString","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Serializer.sizeof_str","value":{"symbol":"pdg::emscriptenSerializerSizeofString","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Serializer.getDataPtr","value":{"symbol":"pdg::emscriptenSerializerGetData","header":"src/bindings/emscripten/pdg_em_adaptors.h","allow_raw_pointers":true}}

// @pdg-adapter {"name":"Deserializer.deserialize_8","value":{"symbol":"pdg::emscriptenDeserializerDeserialize8","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Deserializer.deserialize_str","value":{"symbol":"pdg::emscriptenDeserializerDeserializeString","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Deserializer.deserialize_mem","value":{"symbol":"pdg::emscriptenDeserializerDeserializeMem","header":"src/bindings/emscripten/pdg_em_adaptors.h","allow_raw_pointers":true}}


// @pdg-adapter {"name":"SpriteLayer.getSerializedSize","value":{"symbol":"pdg::emscriptenSpriteLayerGetSerializedSize","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"SpriteLayer.serialize","value":{"symbol":"pdg::emscriptenSpriteLayerSerialize","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"SpriteLayer.deserialize","value":{"symbol":"pdg::emscriptenSpriteLayerDeserialize","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}



// @pdg-adapter {"name":"TileLayer.getTileTypeAt","value":{"symbol":"pdg::emscriptenTileGetType","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"TileLayer.setTileTypeAt","value":{"symbol":"pdg::emscriptenTileSetType","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"TileLayer.getTileTypeAndFacingAt","value":{"symbol":"pdg::emscriptenTileGetTypeAndFacing","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Image.getSubsection","value":{"symbol":"pdg::emscriptenImageGetSubsection","header":"src/bindings/emscripten/pdg_em_adaptors.h","allow_raw_pointers":true}}

// @pdg-adapter {"name":"Attributes.lineStyle","value":{"symbol":"pdg::emscriptenAttributesSetLineStyle","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Attributes.fitType","value":{"symbol":"pdg::emscriptenAttributesSetFitType","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Attributes.transform","value":{"symbol":"pdg::emscriptenAttributesTransform","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Attributes.setTransform","value":{"symbol":"pdg::emscriptenAttributesSetTransform","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Attributes.blendMode","value":{"symbol":"pdg::emscriptenAttributesSetBlendMode","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Attributes.getLineStyle","value":{"symbol":"pdg::emscriptenAttributesGetLineStyle","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Attributes.getGradientType","value":{"symbol":"pdg::emscriptenAttributesGetGradientType","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Attributes.getTransform","value":{"symbol":"pdg::emscriptenAttributesGetTransform","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Attributes.getBlendMode","value":{"symbol":"pdg::emscriptenAttributesGetBlendMode","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"Attributes.getFitType","value":{"symbol":"pdg::emscriptenAttributesGetFitType","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"AnimatedAttributes.changeTransform","value":{"symbol":"pdg::emscriptenAnimatedAttributesChangeTransform","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"ElementRef.type","value":{"symbol":"pdg::emscriptenElementGetType","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"ElementRef.getControlPoints","value":{"symbol":"pdg::emscriptenElementGetControlPoints","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"ElementRef.getAttributes","value":{"symbol":"pdg::emscriptenElementGetAttributes","header":"src/bindings/emscripten/pdg_em_adaptors.h","allow_raw_pointers":true}}

// @pdg-adapter {"name":"pdg.idle","value":{"symbol":"pdg::emscriptenIdle","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"pdg.quit","value":{"symbol":"pdg::emscriptenQuit","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"pdg.createSpriteLayer","value":{"symbol":"pdg::emscriptenCreateSpriteLayer","header":"src/bindings/emscripten/pdg_em_adaptors.h","allow_raw_pointers":true}}

// @pdg-adapter {"name":"pdg.createTileLayer","value":{"symbol":"pdg::emscriptenCreateTileLayer","header":"src/bindings/emscripten/pdg_em_adaptors.h","allow_raw_pointers":true}}



// @pdg-adapter {"name":"browser.emscriptenSpriteHasAnimation","value":{"symbol":"pdg::emscriptenSpriteHasAnimation","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteSeekAnimation","value":{"symbol":"pdg::emscriptenSpriteSeekAnimation","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteTransitionToAnimation","value":{"symbol":"pdg::emscriptenSpriteTransitionToAnimation","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteSetupAnimationPhysics","value":{"symbol":"pdg::emscriptenSpriteSetupAnimationPhysics","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}







// @pdg-adapter {"name":"browser.emscriptenSpriteGetAnimationPhysicsSetupWarnings","value":{"symbol":"pdg::emscriptenSpriteGetAnimationPhysicsSetupWarnings","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteSetAnimationPhysicsMode","value":{"symbol":"pdg::emscriptenSpriteSetAnimationPhysicsMode","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteGetAnimationPhysicsMode","value":{"symbol":"pdg::emscriptenSpriteGetAnimationPhysicsMode","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteSetAnimationPhysicsDriveSettings","value":{"symbol":"pdg::emscriptenSpriteSetAnimationPhysicsDriveSettings","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteGetAnimationPhysicsDriveSettings","value":{"symbol":"pdg::emscriptenSpriteGetAnimationPhysicsDriveSettings","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}


// @pdg-adapter {"name":"browser.emscriptenSpriteAddAnimationDrawable","value":{"symbol":"pdg::emscriptenSpriteAddAnimationDrawable","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}



// @pdg-adapter {"name":"browser.emscriptenSpriteGetAnimationDrawBounds","value":{"symbol":"pdg::emscriptenSpriteGetAnimationDrawBounds","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteAddAnimationIK","value":{"symbol":"pdg::emscriptenSpriteAddAnimationIK","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}


// @pdg-adapter {"name":"browser.emscriptenSpriteGetAnimationIKResult","value":{"symbol":"pdg::emscriptenSpriteGetAnimationIKResult","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteAddAnimationModifier","value":{"symbol":"pdg::emscriptenSpriteAddAnimationModifier","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}




// @pdg-adapter {"name":"browser.emscriptenSpriteEnableAnimationPose","value":{"symbol":"pdg::emscriptenSpriteEnableAnimationPose","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteGetAnimationPose","value":{"symbol":"pdg::emscriptenSpriteGetAnimationPose","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteSampleAnimationPose","value":{"symbol":"pdg::emscriptenSpriteSampleAnimationPose","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteGetAnimationBoneNames","value":{"symbol":"pdg::emscriptenSpriteGetAnimationBoneNames","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteGetAnimationBindingNames","value":{"symbol":"pdg::emscriptenSpriteGetAnimationBindingNames","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteGetAnimationBoneTransform","value":{"symbol":"pdg::emscriptenSpriteGetAnimationBoneTransform","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteGetAnimationBindingTransform","value":{"symbol":"pdg::emscriptenSpriteGetAnimationBindingTransform","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteSetAnimationBoneTransform","value":{"symbol":"pdg::emscriptenSpriteSetAnimationBoneTransform","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteStartAnimation","value":{"symbol":"pdg::emscriptenSpriteStartAnimation","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteApplyCharacterMap","value":{"symbol":"pdg::emscriptenSpriteApplyCharacterMap","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteRemoveCharacterMap","value":{"symbol":"pdg::emscriptenSpriteRemoveCharacterMap","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteGetAppliedCharacterMaps","value":{"symbol":"pdg::emscriptenSpriteGetAppliedCharacterMaps","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteBlendToAnimation","value":{"symbol":"pdg::emscriptenSpriteBlendToAnimation","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteHasAttachPoint","value":{"symbol":"pdg::emscriptenSpriteHasAttachPoint","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteGetAttachPoint","value":{"symbol":"pdg::emscriptenSpriteGetAttachPoint","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteAttachSprite","value":{"symbol":"pdg::emscriptenSpriteAttachSprite","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteActivateSubEntity","value":{"symbol":"pdg::emscriptenSpriteActivateSubEntity","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteGetCollisionBox","value":{"symbol":"pdg::emscriptenSpriteGetCollisionBox","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteIsCollisionActive","value":{"symbol":"pdg::emscriptenSpriteIsCollisionActive","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSpriteGetCollisionBoxName","value":{"symbol":"pdg::emscriptenSpriteGetCollisionBoxName","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenLayerApplyCharacterMap","value":{"symbol":"pdg::emscriptenLayerApplyCharacterMap","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenLayerRemoveCharacterMap","value":{"symbol":"pdg::emscriptenLayerRemoveCharacterMap","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenFontGetName","value":{"symbol":"pdg::emscriptenFontGetName","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}
// @pdg-adapter {"name":"browser.emscriptenFontGetHeight","value":{"symbol":"pdg::emscriptenFontGetHeight","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}
// @pdg-adapter {"name":"browser.emscriptenFontGetLeading","value":{"symbol":"pdg::emscriptenFontGetLeading","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}
// @pdg-adapter {"name":"browser.emscriptenFontGetCapHeight","value":{"symbol":"pdg::emscriptenFontGetCapHeight","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}
// @pdg-adapter {"name":"browser.emscriptenFontGetAscent","value":{"symbol":"pdg::emscriptenFontGetAscent","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}
// @pdg-adapter {"name":"browser.emscriptenFontGetDescent","value":{"symbol":"pdg::emscriptenFontGetDescent","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}






// @pdg-adapter {"name":"browser.emscriptenPortGetTextWidth","value":{"symbol":"pdg::emscriptenPortGetTextWidth","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenPortStartTrackingMouse","value":{"symbol":"pdg::emscriptenPortStartTrackingMouse","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}



// @pdg-adapter {"name":"browser.emscriptenPortDrawImage","value":{"symbol":"pdg::emscriptenPortDrawImage","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenPortDrawDrawing","value":{"symbol":"pdg::emscriptenPortDrawDrawing","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenPortDrawText","value":{"symbol":"pdg::emscriptenPortDrawText","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenGraphicsGetCurrentScreenMode","value":{"symbol":"pdg::emscriptenGraphicsGetCurrentScreenMode","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenGraphicsGetNthSupportedScreenMode","value":{"symbol":"pdg::emscriptenGraphicsGetNthSupportedScreenMode","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenGraphicsCreateWindowPort","value":{"symbol":"pdg::emscriptenGraphicsCreateWindowPort","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenGraphicsCreateFont","value":{"symbol":"pdg::emscriptenGraphicsCreateFont","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}



// @pdg-adapter {"name":"browser.emscriptenSoundChangePitch","value":{"symbol":"pdg::emscriptenSoundChangePitch","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSoundChangeOffset","value":{"symbol":"pdg::emscriptenSoundChangeOffset","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSoundFadeOut","value":{"symbol":"pdg::emscriptenSoundFadeOut","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSoundFadeIn","value":{"symbol":"pdg::emscriptenSoundFadeIn","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenSoundChangeVolume","value":{"symbol":"pdg::emscriptenSoundChangeVolume","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}

// @pdg-adapter {"name":"browser.emscriptenResourceGetSound","value":{"symbol":"pdg::emscriptenResourceGetSound","header":"src/bindings/emscripten/pdg_em_adaptors.h"}}
