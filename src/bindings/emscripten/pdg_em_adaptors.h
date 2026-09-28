// this header file contains all the code that adapts between the JavaScript and C++ classes, which
// do not always have identical method signatures

#include "pdg/framework.h"
#include "pdg/sys/attributes.h"
#include "pdg/sys/drawing.h"

#include "config-unix.h"

#include "../javascript/memblock.h"

#include <emscripten/val.h>

namespace pdg {

// Turn native validation failures into JavaScript Error objects, retaining what().
template<auto Method> struct EmscriptenCheckedMethod;
template<class Owner, class Result, class... Args, Result (Owner::*Method)(Args...)>
struct EmscriptenCheckedMethod<Method> {
    static Result call(Owner& owner, Args... args) {
        try { return (owner.*Method)(args...); }
        catch (const std::exception& error) {
            emscripten::val::global("Error").new_(std::string(error.what())).throw_();
        }
    }
};

class FileManager;

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

bool emscriptenConfigUseConfig(ConfigManager& manager, const std::string& name);
emscripten::val emscriptenConfigGetString(ConfigManager& manager, const std::string& key);
emscripten::val emscriptenConfigGetLong(ConfigManager& manager, const std::string& key);
emscripten::val emscriptenConfigGetFloat(ConfigManager& manager, const std::string& key);
emscripten::val emscriptenConfigGetBool(ConfigManager& manager, const std::string& key);
void emscriptenConfigSetString(ConfigManager& manager, const std::string& key, const std::string& value);
void emscriptenConfigSetLong(ConfigManager& manager, const std::string& key, long value);
void emscriptenConfigSetFloat(ConfigManager& manager, const std::string& key, float value);
void emscriptenConfigSetBool(ConfigManager& manager, const std::string& key, bool value);

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
void emscriptenPortDrawCircle(Port& port, const Point& center, float radius,
                              const Attributes& attributes);
void emscriptenPortDrawQuad(Port& port, const emscripten::val& quad,
                            const Attributes& attributes);
SpriteLayer* emscriptenCreateSpriteLayerForPort(Port* port);
TileLayer* emscriptenCreateTileLayerForPort(Port* port);
std::string emscriptenFontGetName(Font& font);
float emscriptenFontGetHeight(Font& font, int size, int style);
float emscriptenFontGetLeading(Font& font, int size, int style);
float emscriptenFontGetCapHeight(Font& font, int size, int style);
float emscriptenFontGetAscent(Font& font, int size, int style);
float emscriptenFontGetDescent(Font& font, int size, int style);
void emscriptenDrawingDraw(Drawing& drawing, Port* port);
#ifdef PDG_SPRITER_SUPPORT
void emscriptenSpriteSeekAnimation(Sprite& sprite, const std::string& clip, double seconds);
void emscriptenSpriteTransitionToAnimation(Sprite& sprite, const std::string& clip, double seconds, double duration);
void emscriptenSpriteSetupAnimationPhysics(Sprite& sprite,emscripten::val values);
void emscriptenSpriteDisableAnimationPhysics(Sprite& sprite,double seconds,int direction);
void emscriptenSpriteSetAnimationPhysicsMode(Sprite&,int,double,bool,double,int);
int emscriptenSpriteGetAnimationPhysicsMode(const Sprite&,double,bool);
void emscriptenSpriteSetAnimationPhysicsDriveSettings(Sprite&,double,double,double,double,int,double,bool);
emscripten::val emscriptenSpriteGetAnimationPhysicsDriveSettings(const Sprite&,uint32_t);
void emscriptenSpriteSetupPhysicsFromAnimationRig(Sprite& sprite,double mass,double units);
void emscriptenSpriteAttachAnimationPhysicsPart(Sprite& sprite,Part* part,Part* parent);
void emscriptenSpriteDetachAnimationPhysicsPart(Sprite& sprite,Part* part,bool descendants);
void emscriptenSpriteSetAnimationPhysicsRoot(Sprite& sprite,uint32_t bone);
void emscriptenSpriteClearAnimationPhysicsRoot(Sprite& sprite);
uint32_t emscriptenSpriteGetAnimationPhysicsRoot(const Sprite& sprite);
emscripten::val emscriptenSpriteGetAnimationPhysicsSetupWarnings(const Sprite& sprite);
uint32_t emscriptenSpriteAddAnimationDrawable(Sprite& sprite,emscripten::val callback,emscripten::val values,const std::string& slot);
void emscriptenSpriteSetAnimationDrawableEnabled(Sprite& sprite,uint32_t id,bool enabled);
std::string emscriptenSpriteGetAnimationDrawableError(const Sprite& sprite,uint32_t id);
emscripten::val emscriptenSpriteGetAnimationDrawBounds(const Sprite& sprite);
uint32_t emscriptenSpriteAddAnimationIK(Sprite& sprite, emscripten::val config, int order);
void emscriptenSpriteSetAnimationIKTarget(Sprite& sprite, uint32_t id, double x, double y, int space);
emscripten::val emscriptenSpriteGetAnimationIKResult(const Sprite& sprite, uint32_t id);
uint32_t emscriptenSpriteAddAnimationModifier(Sprite& sprite, emscripten::val callback, int stage, int order);
void emscriptenSpriteSetAnimationSource(Sprite& sprite, int source);
std::string emscriptenSpriteGetAnimationModifierError(const Sprite& sprite, uint32_t id);
void emscriptenSpriteSetAnimationDebugDraw(Sprite& sprite, int flags);
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
void emscriptenSoundPlay(Sound& sound, float volume, int32 offsetX, float pitch,
                         ms_time fromMs, ms_delta lengthMs);
void emscriptenSoundChangePitch(Sound& sound, float target, ms_delta duration);
void emscriptenSoundChangeOffset(Sound& sound, int32 target, ms_delta duration);
void emscriptenSoundFadeOut(Sound& sound, ms_delta duration);
void emscriptenSoundFadeIn(Sound& sound, ms_delta duration);
void emscriptenSoundChangeVolume(Sound& sound, float target, ms_delta duration);
Sound* emscriptenResourceGetSound(ResourceManager& manager, const std::string& soundName);
#endif
Polygon* emscriptenPolygonIntersection(Polygon& polygon, const Polygon& other);
Polygon* emscriptenPolygonUnion(Polygon& polygon, const Polygon& other);

emscripten::val emscriptenAnimatedGetRotatedBounds(AnimatedBase& animated);
emscripten::val emscriptenSpriteGetFrameRotatedBounds(Sprite& sprite, int frame);
void emscriptenAnimatedMoveTo(AnimatedBase& animated, const Point& value, double seconds, int easing);
void emscriptenAnimatedMoveBy(AnimatedBase& animated, const Offset& value, double seconds, int easing);
void emscriptenAnimatedChangeMovementTo(AnimatedBase& animated, const Vector& value, double seconds, int easing);
void emscriptenAnimatedChangeMovementBy(AnimatedBase& animated, const Vector& value, double seconds, int easing);
void emscriptenAnimatedChangeCenterOffsetTo(AnimatedBase& animated, const Offset& value, double seconds, int easing);
void emscriptenAnimatedChangeCenterOffsetBy(AnimatedBase& animated, const Offset& value, double seconds, int easing);
void emscriptenAnimatedGrow(AnimatedBase& animated, float value, double seconds, int easing);
void emscriptenAnimatedRotateTo(AnimatedBase& animated, float value, double seconds, int easing, int direction);
void emscriptenAnimatedRotateBy(AnimatedBase& animated, float value, double seconds, int easing, int direction);
void emscriptenAnimatedChangeSpinTo(AnimatedBase& animated, float value, double seconds, int easing);
void emscriptenAnimatedChangeSpinBy(AnimatedBase& animated, float value, double seconds, int easing);
void emscriptenAnimatedChangeGrowingTo(AnimatedBase& animated, float value, double seconds, int easing);
void emscriptenAnimatedChangeGrowingBy(AnimatedBase& animated, float value, double seconds, int easing);
void emscriptenAnimatedStretch(AnimatedBase& animated, float x, float y, double seconds, int easing);
void emscriptenAnimatedResizeTo(AnimatedBase& animated, float x, float y, double seconds, int easing);
void emscriptenAnimatedResizeBy(AnimatedBase& animated, float x, float y, double seconds, int easing);
void emscriptenAnimatedChangeScaleTo(AnimatedBase& animated, float x, float y, double seconds, int easing);
void emscriptenAnimatedChangeScaleBy(AnimatedBase& animated, float x, float y, double seconds, int easing);
void emscriptenAnimatedChangeStretchingTo(AnimatedBase& animated, float x, float y, double seconds, int easing);
void emscriptenAnimatedChangeStretchingBy(AnimatedBase& animated, float x, float y, double seconds, int easing);
bool emscriptenAnimatedAnimate(AnimatedBase& animated, double elapsed);

Image* emscriptenCreateImage(const std::string& path);
ImageStrip* emscriptenCreateSnapshotImage();
ImageStrip* emscriptenCreateImageStrip(const std::string& path);
Sound* emscriptenCreateSound(const std::string& path);
Rect emscriptenImageGetBoundsAt(Image& image, const Point& point);
Image* emscriptenImageGetSubsection(Image& image, const Rect& rect);

void emscriptenResourceSetLanguage(ResourceManager& manager, const std::string& language);
std::string emscriptenResourceGetLanguage(ResourceManager& manager);
int emscriptenResourceOpenFile(ResourceManager& manager, const std::string& filename);
std::string emscriptenResourceGetString(ResourceManager& manager, int id, int substring);
size_t emscriptenResourceGetSize(ResourceManager& manager, const std::string& resourceName);
emscripten::val emscriptenResourceGet(ResourceManager& manager, const std::string& resourceName, int maxSize);
Image* emscriptenResourceGetImage(ResourceManager& manager, const std::string& imageName);
ImageStrip* emscriptenResourceGetImageStrip(ResourceManager& manager, const std::string& imageName);

void emscriptenAttributesSetLineStyle(Attributes& attributes, int style);
void emscriptenAttributesSetFitType(Attributes& attributes, int fit);
void emscriptenAttributesSetBlendMode(Attributes& attributes, int mode);
void emscriptenAttributesRotate(Attributes& attributes, float radians, const Point& center);
void emscriptenAttributesScale(Attributes& attributes, float xFactor, float yFactor, const Point& center);
void emscriptenAttributesSkew(Attributes& attributes, float xSkew, float ySkew, const Point& center);
void emscriptenAttributesSetTransform(Attributes& attributes, const emscripten::val& matrix);
Attributes* emscriptenAnimatedAttributesBase(AnimatedAttributesBase& self);
void emscriptenAnimatedAttributesChangeLineColor(AnimatedAttributesBase& self, const Color& target, double seconds, int easing);
void emscriptenAnimatedAttributesChangeLineThickness(AnimatedAttributesBase& self, float target, double seconds, int easing);
void emscriptenAnimatedAttributesChangeLineOpacity(AnimatedAttributesBase& self, float target, double seconds, int easing);
void emscriptenAnimatedAttributesChangeFillColor(AnimatedAttributesBase& self, const Color& target, double seconds, int easing);
void emscriptenAnimatedAttributesChangeFillOpacity(AnimatedAttributesBase& self, float target, double seconds, int easing);
void emscriptenAnimatedAttributesChangeRoundedCorners(AnimatedAttributesBase& self, float target, double seconds, int easing);
void emscriptenAnimatedAttributesChangeTextSize(AnimatedAttributesBase& self, float target, double seconds, int easing);
void emscriptenAnimatedAttributesChangeSubsection(AnimatedAttributesBase& self, const Rect& target, double seconds, int easing);
void emscriptenAnimatedAttributesChangePolarOffset(AnimatedAttributesBase& self, const Offset& target, double seconds, int easing);
void emscriptenAnimatedAttributesChangeLightOffset(AnimatedAttributesBase& self, const Offset& target, double seconds, int easing);
void emscriptenAnimatedAttributesChangeAmbientLight(AnimatedAttributesBase& self, const Color& target, double seconds, int easing);
void emscriptenAnimatedAttributesChangeSkew(AnimatedAttributesBase& self, float x, float y, double seconds, int easing);
void emscriptenAnimatedAttributesChangeSphereRotation(AnimatedAttributesBase& self, float radians, double seconds, int easing, int direction);
void emscriptenAnimatedAttributesChangeFrames(AnimatedAttributesBase& self, int first, int last, double seconds, int easing);
void emscriptenAnimatedAttributesChangeFillGradient(AnimatedAttributesBase& self, const Point& start, const Color& startColor, const Point& end, const Color& endColor, double seconds, int easing);
void emscriptenAnimatedAttributesChangeFillRadialGradient(AnimatedAttributesBase& self, const Point& center, const Color& centerColor, float radius, const Color& endColor, double seconds, int easing);
void emscriptenAnimatedAttributesChangeTransform(AnimatedAttributesBase& self, const emscripten::val& matrix, double seconds, int easing);

void emscriptenAttributesTransform(Attributes& attributes, const emscripten::val& matrix);
emscripten::val emscriptenAttributesGetTransform(Attributes& attributes);
int emscriptenAttributesGetLineStyle(Attributes& attributes);
int emscriptenAttributesGetGradientType(Attributes& attributes);
int emscriptenAttributesGetFitType(Attributes& attributes);
int emscriptenAttributesGetBlendMode(Attributes& attributes);

Drawing* emscriptenCreateDrawing();
ElementRef* emscriptenDrawingAddSpline(Drawing& drawing, Spline& spline, const Attributes& attributes);
ElementRef* emscriptenDrawingAddPolygon(Drawing& drawing, Polygon& polygon, const Attributes& attributes);
emscripten::val emscriptenElementGetControlPoints(ElementRef& element);
Attributes* emscriptenElementGetAttributes(ElementRef& element);
int emscriptenElementGetType(ElementRef& element);

emscripten::val emscriptenFileFindFirst(FileManager& manager, const std::string& pattern);
bool emscriptenFileFindNext(FileManager& manager, emscripten::val findData);
void emscriptenFileFindClose(FileManager& manager, const emscripten::val& findData);

void emscriptenLogInitialize(LogManager& manager, const std::string& baseName, int mode);
void emscriptenLogWrite(LogManager& manager, int level, const std::string& category, const std::string& message);
void emscriptenLogSetLevel(LogManager& manager, int level);
int emscriptenLogGetLevel(LogManager& manager);

void emscriptenTileDefineSet(TileLayer& layer, int tileWidth, int tileHeight, Image* tiles);
void emscriptenTileSetWorldSize(TileLayer& layer, long width, long height);
int emscriptenTileGetType(TileLayer& layer, long x, long y);
void emscriptenTileSetType(TileLayer& layer, long x, long y, int tileType, int facing);
emscripten::val emscriptenTileGetTypeAndFacing(TileLayer& layer, long x, long y);

void emscriptenSerializerSerialize8(Serializer& serializer, double value);
void emscriptenSerializerSerialize4(Serializer& serializer, int value);
void emscriptenSerializerSerialize2(Serializer& serializer, int value);
void emscriptenSerializerSerialize1(Serializer& serializer, int value);
void emscriptenSerializerSerializeFloat(Serializer& serializer, double value);
void emscriptenSerializerSerializeDouble(Serializer& serializer, double value);
void emscriptenSerializerSerializePoint(Serializer& serializer, const Point& value);
void emscriptenSerializerSerializeVector(Serializer& serializer, const Vector& value);
void emscriptenSerializerSerializeString(Serializer& serializer, const std::string& value);
void emscriptenSerializerSerializeMem(Serializer& serializer, const std::string& value);
void emscriptenSerializerSerializeRotatedRect(Serializer& serializer, const emscripten::val& value);
void emscriptenSerializerSerializeQuad(Serializer& serializer, const emscripten::val& value);
uint32 emscriptenSerializerSizeofString(Serializer& serializer, const std::string& value);
uint32 emscriptenSerializerSizeofPoint(Serializer& serializer, const Point& value);
uint32 emscriptenSerializerSizeofVector(Serializer& serializer, const Vector& value);
uint32 emscriptenSerializerSizeofMem(Serializer& serializer, const std::string& value);
uint32 emscriptenSerializerSizeofRotatedRect(Serializer& serializer, const emscripten::val& value);
uint32 emscriptenSerializerSizeofQuad(Serializer& serializer, const emscripten::val& value);
MemBlock* emscriptenSerializerGetData(Serializer& serializer);

double emscriptenDeserializerDeserialize8(Deserializer& deserializer);
int emscriptenDeserializerDeserialize4(Deserializer& deserializer);
int emscriptenDeserializerDeserialize2(Deserializer& deserializer);
int emscriptenDeserializerDeserialize1(Deserializer& deserializer);
double emscriptenDeserializerDeserializeFloat(Deserializer& deserializer);
double emscriptenDeserializerDeserializeDouble(Deserializer& deserializer);
Point emscriptenDeserializerDeserializePoint(Deserializer& deserializer);
Vector emscriptenDeserializerDeserializeVector(Deserializer& deserializer);
std::string emscriptenDeserializerDeserializeString(Deserializer& deserializer);
MemBlock* emscriptenDeserializerDeserializeMem(Deserializer& deserializer);
emscripten::val emscriptenDeserializerDeserializeRotatedRect(Deserializer& deserializer);
emscripten::val emscriptenDeserializerDeserializeQuad(Deserializer& deserializer);
void emscriptenDeserializerSetData(Deserializer& deserializer, MemBlock& data);

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
    action_ZoomComplete = SpriteLayer::action_ZoomComplete,
    action_LayerFadeInComplete = SpriteLayer::action_FadeInComplete,
    action_LayerFadeOutComplete = SpriteLayer::action_FadeOutComplete
};

} // end namespace pdg
