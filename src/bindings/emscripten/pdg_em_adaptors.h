// this header file contains all the code that adapts between the JavaScript and C++ classes, which
// do not always have identical method signatures

#include "pdg/framework.h"
#include "pdg/sys/attributes.h"
#include "pdg/sys/drawing.h"

#include "config-unix.h"

#include "../javascript/memblock.h"

#include <emscripten/val.h>

namespace pdg {

class FileManager;

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
Polygon* emscriptenPolygonIntersection(Polygon& polygon, const Polygon& other);
Polygon* emscriptenPolygonUnion(Polygon& polygon, const Polygon& other);

emscripten::val emscriptenAnimatedGetRotatedBounds(Animated& animated);
void emscriptenAnimatedMoveTo(Animated& animated, const Point& point, ms_delta duration, int easing);
void emscriptenAnimatedMove(Animated& animated, const Offset& offset, ms_delta duration, int easing);
void emscriptenAnimatedGrow(Animated& animated, float factor, ms_delta duration, int easing);
void emscriptenAnimatedStretch(Animated& animated, float widthFactor, float heightFactor, ms_delta duration, int easing);
void emscriptenAnimatedResize(Animated& animated, float width, float height, ms_delta duration, int easing);
void emscriptenAnimatedResizeTo(Animated& animated, float width, float height, ms_delta duration, int easing);
void emscriptenAnimatedRotate(Animated& animated, float radians, ms_delta duration, int easing);
void emscriptenAnimatedRotateTo(Animated& animated, float radians, ms_delta duration, int easing);
void emscriptenAnimatedChangeCenter(Animated& animated, const Offset& offset, ms_delta duration, int easing);
void emscriptenAnimatedChangeCenterTo(Animated& animated, const Offset& offset, ms_delta duration, int easing);
bool emscriptenAnimatedAnimate(Animated& animated, ms_delta elapsed);

Image* emscriptenCreateImage(const std::string& path);
ImageStrip* emscriptenCreateImageStrip(const std::string& path);
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
