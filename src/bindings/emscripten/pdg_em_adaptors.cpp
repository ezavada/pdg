// this C++ file contains all the code that adapts between the JavaScript and C++ classes, which
// do not always have identical method signatures

#include "pdg_em_adaptors.h"
#include "pdg-lib.h"

#ifndef PDG_NO_GUI
#include "glfw/internals-glfw.h"
#endif

#include <emscripten.h>

#include <algorithm>
#include <stdexcept>
#include <memory>
#include <unordered_map>
#include <vector>


namespace pdg {

namespace {

emscripten::val pointToVal(const Point& point) {
    emscripten::val result = emscripten::val::object();
    result.set("x", point.x);
    result.set("y", point.y);
    return result;
}

void setModifierKeys(emscripten::val& event, const ModifierKeyInfo& info) {
    event.set("shift", info.shift);
    event.set("ctrl", info.ctrl);
    event.set("alt", info.alt);
    event.set("meta", info.meta);
}

void setMouseInfo(emscripten::val& event, const MouseInfo& info) {
    setModifierKeys(event, info);
    event.set("mousePos", pointToVal(info.mousePos));
    event.set("leftButton", info.leftButton);
    event.set("rightButton", info.rightButton);
    event.set("buttonNumber", info.buttonNumber);
    event.set("lastClickPos", pointToVal(info.lastClickPos));
    event.set("lastClickElapsed", static_cast<double>(info.lastClickElapsed));
}

}  // namespace

class EmscriptenEventBridge : public IEventHandler {
public:
    explicit EmscriptenEventBridge(const emscripten::val& jsEmitter)
        : mJsEmitter(jsEmitter), mRefs(0) {}

    void addRef() const throw() override { ++mRefs; }
    void release() const throw() override {
        if (--mRefs == 0) delete this;
    }

    bool handleEvent(EventEmitter*, long eventType, void* eventData) throw() override {
        try {
            emscripten::val event = emscripten::val::object();
            if (eventData && eventType == eventType_Shutdown) {
                const ShutdownInfo* info = static_cast<const ShutdownInfo*>(eventData);
                event.set("exitReason", info->exitReason);
                event.set("exitCode", info->exitCode);
            } else if (eventData && eventType == eventType_Timer) {
                const TimerInfo* info = static_cast<const TimerInfo*>(eventData);
                if (info->id <= 0) return false;
                event.set("id", info->id);
                event.set("millisec", static_cast<double>(info->millisec));
                event.set("msElapsed", static_cast<double>(info->msElapsed));
            } else if (eventData &&
                       (eventType == eventType_KeyDown || eventType == eventType_KeyUp)) {
                event.set("keyCode", static_cast<const KeyInfo*>(eventData)->keyCode);
            } else if (eventData && eventType == eventType_KeyPress) {
                const KeyPressInfo* info = static_cast<const KeyPressInfo*>(eventData);
                setModifierKeys(event, *info);
                event.set("unicode", info->unicode);
                event.set("isRepeating", info->isRepeating);
            } else if (eventData &&
                       (eventType == eventType_MouseDown || eventType == eventType_MouseUp ||
                        eventType == eventType_MouseMove)) {
                setMouseInfo(event, *static_cast<const MouseInfo*>(eventData));
            } else if (eventData &&
                       (eventType == eventType_MouseEnter || eventType == eventType_MouseLeave)) {
                const MouseTrackingInfo* info =
                    static_cast<const MouseTrackingInfo*>(eventData);
                setMouseInfo(event, *info);
                event.set("entering", info->entering);
                event.set("trackingRef", info->trackingRef);
            } else if (eventData && eventType == eventType_ScrollWheel) {
                const ScrollWheelInfo* info = static_cast<const ScrollWheelInfo*>(eventData);
                setModifierKeys(event, *info);
                event.set("horizDelta", info->horizDelta);
                event.set("vertDelta", info->vertDelta);
            } else if (eventData && eventType == eventType_PortResized) {
                const PortResizeInfo* info = static_cast<const PortResizeInfo*>(eventData);
                event.set("portIdentity", reinterpret_cast<uintptr_t>(info->port));
                event.set("screenPos", info->screenPos);
                event.set("oldScreenPos", info->oldScreenPos);
                event.set("oldWidth", info->oldWidth);
                event.set("oldHeight", info->oldHeight);
            } else if (eventData && eventType == eventType_SpriteLayer) {
                const SpriteLayerInfo* info = static_cast<const SpriteLayerInfo*>(eventData);
                event.set("action", info->action);
                event.set("actingLayer", mJsEmitter);
                event.set("millisec", static_cast<double>(info->millisec));
            } else if (eventData && eventType == eventType_SpriteCollide) {
                const SpriteCollideInfo* info = static_cast<const SpriteCollideInfo*>(eventData);
                event.set("action", info->action);
                event.set("actingSprite", mJsEmitter);
                event.set("inLayer", true);
                event.set("targetSprite", true);
                event.set("force", info->force);
                event.set("kineticEnergy", info->kineticEnergy);
                event.set("isFirstContact", info->isFirstContact);
                event.set("collisionName", info->collisionName
                    ? emscripten::val(info->collisionName) : emscripten::val::null());
                event.set("withCollisionName", info->withCollisionName
                    ? emscripten::val(info->withCollisionName) : emscripten::val::null());
            } else if (eventData && eventType == eventType_SpriteAnimate) {
                const SpriteAnimateInfo* info = static_cast<const SpriteAnimateInfo*>(eventData);
                event.set("action", info->action);
                event.set("actingSprite", mJsEmitter);
                event.set("inLayer", true);
                event.set("id", info->id);
            } else if (eventData && eventType == eventType_SoundEvent) {
                const SoundEventInfo* info = static_cast<const SoundEventInfo*>(eventData);
                event.set("eventCode", info->eventCode);
                event.set("sound", mJsEmitter);
            } else if (eventData && eventType == eventType_PortDraw) {
                const PortDrawInfo* info = static_cast<const PortDrawInfo*>(eventData);
                event.set("portIdentity", reinterpret_cast<uintptr_t>(info->port));
                event.set("frameNum", info->frameNum);
            }
            return mJsEmitter.call<bool>("__dispatchNativeEvent", eventType, event);
        } catch (...) {
            return false;
        }
    }

private:
    emscripten::val mJsEmitter;
    mutable int mRefs;
};

void emscriptenEventEmitterAddBridge(EventEmitter& emitter, long eventType,
                                     const emscripten::val& jsEmitter) {
    emitter.addHandler(new EmscriptenEventBridge(jsEmitter), eventType);
}

void emscriptenSpriteAddEventBridge(Sprite& emitter, long eventType,
                                    const emscripten::val& jsEmitter) {
    emitter.addHandler(new EmscriptenEventBridge(jsEmitter), eventType);
}

void emscriptenSpriteLayerAddEventBridge(SpriteLayer& emitter, long eventType,
                                         const emscripten::val& jsEmitter) {
    emitter.addHandler(new EmscriptenEventBridge(jsEmitter), eventType);
}

void emscriptenEventManagerAddEventBridge(EventManager& emitter, long eventType,
                                          const emscripten::val& jsEmitter) {
    emitter.addHandler(new EmscriptenEventBridge(jsEmitter), eventType);
}

SpriteLayer* emscriptenCreateSpriteLayer() {
#ifndef PDG_NO_GUI
    return createSpriteLayer(nullptr);
#else
    return createSpriteLayer();
#endif
}

TileLayer* emscriptenCreateTileLayer() {
#ifndef PDG_NO_GUI
    return createTileLayer(nullptr);
#else
    return createTileLayer();
#endif
}

SpriteLayer* emscriptenCreateSpriteLayerForPort(Port* port) {
#ifndef PDG_NO_GUI
    return createSpriteLayer(port);
#else
    return emscriptenCreateSpriteLayer();
#endif
}

TileLayer* emscriptenCreateTileLayerForPort(Port* port) {
#ifndef PDG_NO_GUI
    return createTileLayer(port);
#else
    return emscriptenCreateTileLayer();
#endif
}

#ifndef PDG_NO_GUI
emscripten::val emscriptenGraphicsGetCurrentScreenMode(GraphicsManager& manager, int screenNum) {
    Rect maxWindowRect;
    GraphicsManager::ScreenMode mode = manager.getCurrentScreenMode(screenNum, &maxWindowRect);
    emscripten::val result = emscripten::val::object();
    result.set("width", mode.width);
    result.set("height", mode.height);
    result.set("depth", mode.bpp);
    emscripten::val maxRect = emscripten::val::object();
    maxRect.set("left", maxWindowRect.left);
    maxRect.set("top", maxWindowRect.top);
    maxRect.set("right", maxWindowRect.right);
    maxRect.set("bottom", maxWindowRect.bottom);
    result.set("maxWindowRect", maxRect);
    return result;
}

emscripten::val emscriptenGraphicsGetNthSupportedScreenMode(GraphicsManager& manager, int n,
                                                            int screenNum) {
    GraphicsManager::ScreenMode mode = manager.getNthSupportedScreenMode(n, screenNum);
    emscripten::val result = emscripten::val::object();
    result.set("width", mode.width);
    result.set("height", mode.height);
    result.set("depth", mode.bpp);
    return result;
}

Port* emscriptenGraphicsCreateWindowPort(GraphicsManager& manager, const Rect& rect,
                                         const std::string& name, int bpp) {
    return manager.createWindowPort(rect, name.empty() ? nullptr : name.c_str(), bpp);
}

Port* emscriptenCreatePort(long width, long height) {
    return GraphicsManager::getSingletonInstance()->createWindowPort(
        Rect(0, 0, width, height), "PDG Emscripten Port", 0);
}

uintptr_t emscriptenPortGetIdentity(Port& port) {
    return reinterpret_cast<uintptr_t>(&port);
}

Font* emscriptenGraphicsCreateFont(GraphicsManager& manager, const std::string& name,
                                   float scalingFactor) {
    return manager.createFont(name.c_str(), scalingFactor);
}

static bool emscriptenDestinationIsRect(const emscripten::val& destination) {
    return !destination["right"].isUndefined() && !destination["bottom"].isUndefined();
}

void emscriptenPortDrawImage(Port& port, Image* image, const emscripten::val& destination,
                             const Attributes& attributes) {
    if (emscriptenDestinationIsRect(destination)) {
        port.drawImage(image, destination.as<Rect>(), attributes);
    } else {
        port.drawImage(image, destination.as<Point>(), attributes);
    }
}

void emscriptenPortDrawDrawing(Port& port, const Drawing& drawing,
                               const emscripten::val& destination, const Attributes& attributes) {
    if (emscriptenDestinationIsRect(destination)) {
        port.drawDrawing(drawing, destination.as<Rect>(), attributes);
    } else {
        port.drawDrawing(drawing, destination.as<Point>(), attributes);
    }
}

void emscriptenPortDrawText(Port& port, const std::string& text,
                            const emscripten::val& destination, const Attributes& attributes) {
    if (emscriptenDestinationIsRect(destination)) {
        port.drawText(text.c_str(), destination.as<Rect>(), attributes);
    } else {
        port.drawText(text.c_str(), destination.as<Point>(), attributes);
    }
}

int emscriptenPortGetTextWidth(Port& port, const std::string& text, int size, uint32 style, int len) {
    return port.getTextWidth(text.c_str(), size, style, len);
}

int emscriptenPortStartTrackingMouse(Port& port, const Rect& rect) {
    return port.startTrackingMouse(rect, nullptr);
}

void emscriptenPortDrawCircle(Port& port, const Point& center, float radius,
                              const Attributes& attributes) {
    port.drawCircle(center, radius, attributes);
}

void emscriptenPortDrawQuad(Port& port, const emscripten::val& quad,
                            const Attributes& attributes) {
    const emscripten::val points = quad["points"];
    port.drawQuad(Quad(points[0].as<Point>(), points[1].as<Point>(),
                       points[2].as<Point>(), points[3].as<Point>()),
                  attributes);
}

std::string emscriptenFontGetName(Font& font) {
    return font.getFontName();
}

float emscriptenFontGetHeight(Font& font, int size, int style) {
    return font.getFontHeight(size, static_cast<uint32>(style));
}

float emscriptenFontGetLeading(Font& font, int size, int style) {
    return font.getFontLeading(size, static_cast<uint32>(style));
}

float emscriptenFontGetAscent(Font& font, int size, int style) {
    return font.getFontAscent(size, static_cast<uint32>(style));
}

float emscriptenFontGetDescent(Font& font, int size, int style) {
    return font.getFontDescent(size, static_cast<uint32>(style));
}

void emscriptenDrawingDraw(Drawing& drawing, Port* port) {
    if (port) drawing.draw(port);
}

#ifdef PDG_SPRITER_SUPPORT
bool emscriptenSpriteHasAnimation(Sprite& sprite, const emscripten::val& animation) {
    return animation.typeOf().as<std::string>() == "number"
        ? sprite.hasAnimation(animation.as<int>())
        : sprite.hasAnimation(animation.isNull() ? "" : animation.as<std::string>().c_str());
}

void emscriptenSpriteStartAnimation(Sprite& sprite, const emscripten::val& animation) {
    if (animation.typeOf().as<std::string>() == "number") sprite.startAnimation(animation.as<int>());
    else sprite.startAnimation(animation.isNull() ? "" : animation.as<std::string>().c_str());
}

void emscriptenSpriteBlendToAnimation(Sprite& sprite, const emscripten::val& animation, float blendTime) {
    if (animation.typeOf().as<std::string>() == "number") sprite.blendToAnimation(animation.as<int>(), blendTime);
    else sprite.blendToAnimation(animation.isNull() ? "" : animation.as<std::string>().c_str(), blendTime);
}

void emscriptenSpriteApplyCharacterMap(Sprite& sprite, const std::string& name) { sprite.applyCharacterMap(name.c_str()); }
void emscriptenSpriteRemoveCharacterMap(Sprite& sprite, const std::string& name) { sprite.removeCharacterMap(name.c_str()); }

emscripten::val emscriptenSpriteGetAppliedCharacterMaps(const Sprite& sprite) {
    emscripten::val result = emscripten::val::array();
    std::vector<std::string> maps = sprite.getAppliedCharacterMaps();
    for (size_t i = 0; i < maps.size(); ++i) result.set(i, maps[i]);
    return result;
}

bool emscriptenSpriteHasAttachPoint(const Sprite& sprite, const std::string& name) { return sprite.hasAttachPoint(name.c_str()); }
Offset emscriptenSpriteGetAttachPoint(const Sprite& sprite, const std::string& name) { return sprite.getAttachPoint(name.c_str()); }
void emscriptenSpriteAttachSprite(Sprite& sprite, Sprite* attached, const std::string& name) { sprite.attachSprite(attached, name.c_str()); }
Sprite* emscriptenSpriteGetAttachedSprite(const Sprite& sprite, const std::string& name) { return sprite.getAttachedSprite(name.c_str()); }
void emscriptenSpriteActivateSubEntity(Sprite& sprite, const std::string& entity, const std::string& animation) { sprite.activateSubEntity(entity.c_str(), animation.c_str()); }
bool emscriptenSpriteIsCollisionActive(const Sprite& sprite, const std::string& name) { return sprite.isSpriterCollisionActive(name.c_str()); }
emscripten::val emscriptenSpriteGetCollisionBox(const Sprite& sprite, const std::string& name) {
    RotatedRect box = sprite.getSpriterCollisionBox(name.c_str());
    emscripten::val result = emscripten::val::object();
    result.set("left", box.left);
    result.set("top", box.top);
    result.set("right", box.right);
    result.set("bottom", box.bottom);
    result.set("radians", box.radians);
    emscripten::val center = emscripten::val::object();
    center.set("x", box.centerOffset.x);
    center.set("y", box.centerOffset.y);
    result.set("centerOffset", center);
    return result;
}
emscripten::val emscriptenSpriteGetCollisionBoxName(const Sprite& sprite, int index) {
    const char* name = sprite.getSpriterCollisionBoxName(index);
    return name ? emscripten::val(name) : emscripten::val::null();
}

Sprite* emscriptenLayerCreateSpriteFromFile(SpriteLayer& layer, const std::string& path, const std::string& entity) {
    return layer.createSpriteFromSpriterFile(path.c_str(), entity.empty() ? nullptr : entity.c_str());
}
Sprite* emscriptenLayerCreateSpriteFromEntity(SpriteLayer& layer, const std::string& entity) { return layer.createSpriteFromSpriterEntity(entity.c_str()); }
void emscriptenLayerApplyCharacterMap(SpriteLayer& layer, const std::string& name) { layer.applyCharacterMapToAll(name.c_str()); }
void emscriptenLayerRemoveCharacterMap(SpriteLayer& layer, const std::string& name) { layer.removeCharacterMapFromAll(name.c_str()); }
#endif
#endif

#ifndef PDG_NO_SOUND
void emscriptenSoundPlay(Sound& sound, float volume, int32 offsetX, float pitch,
                         ms_time fromMs, ms_delta lengthMs) {
    sound.play(volume, offsetX, pitch, fromMs, lengthMs);
}
void emscriptenSoundChangePitch(Sound& sound, float target, ms_delta duration) {
    sound.changePitch(target, duration);
}
void emscriptenSoundChangeOffset(Sound& sound, int32 target, ms_delta duration) {
    sound.changeOffsetX(target, duration);
}
void emscriptenSoundFadeOut(Sound& sound, ms_delta duration) { sound.fadeOut(duration); }
void emscriptenSoundFadeIn(Sound& sound, ms_delta duration) { sound.fadeIn(duration); }
void emscriptenSoundChangeVolume(Sound& sound, float target, ms_delta duration) {
    sound.changeVolume(target, duration);
}
Sound* emscriptenResourceGetSound(ResourceManager& manager, const std::string& soundName) {
    return manager.getSound(soundName.c_str());
}
#endif

// extend the config manager to handle API differences between C++ and Javascript

std::string&  ConfigManagerWrap::getConfigString(std::string& arg0) {
    static std::string s = "";
    ConfigManagerUnix::getConfigString(arg0.c_str(), s);
    return s;
}

long ConfigManagerWrap::getConfigLong(std::string& arg0) {
    long n;
    ConfigManagerUnix::getConfigLong(arg0.c_str(), n);
    return n;
}

float ConfigManagerWrap::getConfigFloat(std::string& arg0) {
    float n;
    ConfigManagerUnix::getConfigFloat(arg0.c_str(), n);
    return n;
}

bool ConfigManagerWrap::getConfigBool(std::string& arg0) {
    bool n = false;
    ConfigManagerUnix::getConfigBool(arg0.c_str(), n);
    return n;
}

bool emscriptenConfigUseConfig(ConfigManager& manager, const std::string& name) {
    return manager.useConfig(name.c_str());
}

emscripten::val emscriptenConfigGetString(ConfigManager& manager, const std::string& key) {
    std::string value;
    if (!manager.getConfigString(key.c_str(), value)) return emscripten::val::undefined();
    return emscripten::val(value);
}

emscripten::val emscriptenConfigGetLong(ConfigManager& manager, const std::string& key) {
    long value = 0;
    if (!manager.getConfigLong(key.c_str(), value)) return emscripten::val::undefined();
    return emscripten::val(value);
}

emscripten::val emscriptenConfigGetFloat(ConfigManager& manager, const std::string& key) {
    float value = 0.0f;
    if (!manager.getConfigFloat(key.c_str(), value)) return emscripten::val::undefined();
    return emscripten::val(value);
}

emscripten::val emscriptenConfigGetBool(ConfigManager& manager, const std::string& key) {
    bool value = false;
    if (!manager.getConfigBool(key.c_str(), value)) return emscripten::val::undefined();
    return emscripten::val(value);
}

void emscriptenConfigSetString(ConfigManager& manager, const std::string& key, const std::string& value) {
    manager.setConfigString(key.c_str(), value);
}

void emscriptenConfigSetLong(ConfigManager& manager, const std::string& key, long value) {
    manager.setConfigLong(key.c_str(), value);
}

void emscriptenConfigSetFloat(ConfigManager& manager, const std::string& key, float value) {
    manager.setConfigFloat(key.c_str(), value);
}

void emscriptenConfigSetBool(ConfigManager& manager, const std::string& key, bool value) {
    manager.setConfigBool(key.c_str(), value);
}

MemBlock* emscriptenCreateEmptyMemBlock() {
    return new MemBlock(0);
}

Polygon* emscriptenPolygonIntersection(Polygon& polygon, const Polygon& other) {
    return new Polygon(polygon.intersection(other));
}

Polygon* emscriptenPolygonUnion(Polygon& polygon, const Polygon& other) {
    return new Polygon(polygon.unionWith(other));
}

static EasingFunc emscriptenAnimatedEasing(int easing, int fallback) {
    int index = (easing >= 0 && easing < NUM_EASING_FUNCTIONS) ? easing : fallback;
    return gEasingFunctions[index];
}

emscripten::val emscriptenAnimatedGetRotatedBounds(Animated& animated) {
    RotatedRect bounds = animated.getRotatedBounds();
    emscripten::val result = emscripten::val::object();
    result.set("left", bounds.left);
    result.set("top", bounds.top);
    result.set("right", bounds.right);
    result.set("bottom", bounds.bottom);
    result.set("radians", bounds.radians);
    emscripten::val centerOffset = emscripten::val::object();
    centerOffset.set("x", bounds.centerOffset.x);
    centerOffset.set("y", bounds.centerOffset.y);
    result.set("centerOffset", centerOffset);
    return result;
}

void emscriptenAnimatedMoveTo(Animated& animated, const Point& point, ms_delta duration, int easing) {
    animated.moveTo(point, duration, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad));
}

void emscriptenAnimatedMove(Animated& animated, const Offset& offset, ms_delta duration, int easing) {
    animated.move(offset, duration, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad));
}

void emscriptenAnimatedGrow(Animated& animated, float factor, ms_delta duration, int easing) {
    animated.grow(factor, duration, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad));
}

void emscriptenAnimatedStretch(Animated& animated, float widthFactor, float heightFactor, ms_delta duration, int easing) {
    animated.stretch(widthFactor, heightFactor, duration, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad));
}

void emscriptenAnimatedResize(Animated& animated, float width, float height, ms_delta duration, int easing) {
    animated.resize(width, height, duration, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad));
}

void emscriptenAnimatedResizeTo(Animated& animated, float width, float height, ms_delta duration, int easing) {
    animated.resizeTo(width, height, duration, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad));
}

void emscriptenAnimatedRotate(Animated& animated, float radians, ms_delta duration, int easing) {
    animated.rotate(radians, duration, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad));
}

void emscriptenAnimatedRotateTo(Animated& animated, float radians, ms_delta duration, int easing) {
    animated.rotateTo(radians, duration, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad));
}

void emscriptenAnimatedChangeCenter(Animated& animated, const Offset& offset, ms_delta duration, int easing) {
    animated.changeCenter(offset, duration, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad));
}

void emscriptenAnimatedChangeCenterTo(Animated& animated, const Offset& offset, ms_delta duration, int easing) {
    animated.changeCenterTo(offset, duration, emscriptenAnimatedEasing(easing, EasingFuncIds::easeInOutQuad));
}

bool emscriptenAnimatedAnimate(Animated& animated, ms_delta elapsed) {
    return animated.animate(elapsed);
}

Image* emscriptenCreateImage(const std::string& path) {
    return Image::createImageFromFile(path.c_str());
}

ImageStrip* emscriptenCreateImageStrip(const std::string& path) {
    return ImageStrip::createImageStripFromFile(path.c_str());
}

Sound* emscriptenCreateSound(const std::string& path) {
    return Sound::createSoundFromFile(path.c_str());
}

Rect emscriptenImageGetBoundsAt(Image& image, const Point& point) {
    Point mutablePoint(point);
    return image.getImageBounds(mutablePoint);
}

Image* emscriptenImageGetSubsection(Image& image, const Rect& rect) {
    Rect mutableRect(rect);
    return image.getSubsection(mutableRect);
}

void emscriptenResourceSetLanguage(ResourceManager& manager, const std::string& language) {
    manager.setLanguage(language.c_str());
}

std::string emscriptenResourceGetLanguage(ResourceManager& manager) {
    return manager.getLanguage();
}

int emscriptenResourceOpenFile(ResourceManager& manager, const std::string& filename) {
    return manager.openResourceFile(filename.c_str());
}

std::string emscriptenResourceGetString(ResourceManager& manager, int id, int substring) {
    std::string value;
    manager.getString(value, static_cast<short>(id), static_cast<short>(substring));
    return value;
}

size_t emscriptenResourceGetSize(ResourceManager& manager, const std::string& resourceName) {
    return manager.getResourceSize(resourceName.c_str());
}

emscripten::val emscriptenResourceGet(ResourceManager& manager, const std::string& resourceName, int maxSize) {
    size_t resourceSize = manager.getResourceSize(resourceName.c_str());
    size_t bufferSize = maxSize < 0 ? resourceSize : std::min(resourceSize, static_cast<size_t>(maxSize));
    if (bufferSize == 0) return emscripten::val(false);

    std::string value(bufferSize, '\0');
    if (!manager.getResource(resourceName.c_str(), value.data(), bufferSize)) {
        return emscripten::val(false);
    }
    return emscripten::val(value);
}

Image* emscriptenResourceGetImage(ResourceManager& manager, const std::string& imageName) {
    return manager.getImage(imageName.c_str());
}

ImageStrip* emscriptenResourceGetImageStrip(ResourceManager& manager, const std::string& imageName) {
    return manager.getImageStrip(imageName.c_str());
}

void emscriptenAttributesSetLineStyle(Attributes& attributes, int style) {
    attributes.lineStyle(static_cast<LineStyle>(style));
}

void emscriptenAttributesSetFitType(Attributes& attributes, int fit) {
    attributes.fitType(static_cast<FitType>(fit));
}

void emscriptenAttributesSetBlendMode(Attributes& attributes, int mode) {
    attributes.blendMode(static_cast<BlendMode>(mode));
}

void emscriptenAttributesRotate(Attributes& attributes, float radians, const Point& center) {
    attributes.rotation(radians, center);
}

void emscriptenAttributesScale(Attributes& attributes, float xFactor, float yFactor, const Point& center) {
    attributes.scale(xFactor, yFactor, center);
}

void emscriptenAttributesSkew(Attributes& attributes, float xSkew, float ySkew, const Point& center) {
    attributes.skew(xSkew, ySkew, center);
}

void emscriptenAttributesTransform(Attributes& attributes, const emscripten::val& matrix) {
    if (!emscripten::val::global("Array").call<bool>("isArray", matrix) || matrix["length"].as<int>() != 9) {
        throw std::invalid_argument("Attributes.transform requires an array of 9 numbers");
    }

    glm::mat3 nativeMatrix;
    for (int column = 0; column < 3; ++column) {
        for (int row = 0; row < 3; ++row) {
            emscripten::val value = matrix[column * 3 + row];
            if (value.typeOf().as<std::string>() != "number") {
                throw std::invalid_argument("Attributes.transform requires an array of 9 numbers");
            }
            nativeMatrix[column][row] = value.as<float>();
        }
    }
    attributes.transform(nativeMatrix);
}

emscripten::val emscriptenAttributesGetTransform(Attributes& attributes) {
    const glm::mat3& matrix = attributes.getTransform();
    emscripten::val result = emscripten::val::array();
    for (int column = 0; column < 3; ++column) {
        for (int row = 0; row < 3; ++row) {
            result.set(column * 3 + row, matrix[column][row]);
        }
    }
    return result;
}

int emscriptenAttributesGetLineStyle(Attributes& attributes) {
    return static_cast<int>(attributes.getLineStyle());
}

int emscriptenAttributesGetGradientType(Attributes& attributes) {
    return static_cast<int>(attributes.getGradientType());
}

int emscriptenAttributesGetFitType(Attributes& attributes) {
    return static_cast<int>(attributes.getFitType());
}

int emscriptenAttributesGetBlendMode(Attributes& attributes) {
    return static_cast<int>(attributes.getBlendMode());
}

Drawing* emscriptenCreateDrawing() {
    return Drawing::create();
}

ElementRef* emscriptenDrawingAddSpline(Drawing& drawing, Spline& spline, const Attributes& attributes) {
    return drawing.addSpline(std::move(spline), attributes);
}

ElementRef* emscriptenDrawingAddPolygon(Drawing& drawing, Polygon& polygon, const Attributes& attributes) {
    return drawing.addPolygon(std::move(polygon), attributes);
}

emscripten::val emscriptenElementGetControlPoints(ElementRef& element) {
    emscripten::val result = emscripten::val::array();
    const std::vector<Point>& points = element.getControlPoints();
    for (size_t i = 0; i < points.size(); ++i) {
        emscripten::val point = emscripten::val::object();
        point.set("x", points[i].x);
        point.set("y", points[i].y);
        result.set(i, point);
    }
    return result;
}

Attributes* emscriptenElementGetAttributes(ElementRef& element) {
    Attributes* attributes = new Attributes();
    element.getAttributes(*attributes);
    return attributes;
}

int emscriptenElementGetType(ElementRef& element) {
    return static_cast<int>(element.type());
}

static std::unordered_map<int, std::unique_ptr<FindDataT>> sEmscriptenFindData;
static int sEmscriptenNextFindId = 1;

static void emscriptenUpdateFindObject(emscripten::val& object, int id, const FindDataT& data, bool found) {
    object.set("_pdgFindId", id);
    object.set("nodeName", found ? data.nodeName : "");
    object.set("isDirectory", found && data.isDirectory);
    object.set("found", found);
}

emscripten::val emscriptenFileFindFirst(FileManager&, const std::string& pattern) {
    std::unique_ptr<FindDataT> data(new FindDataT());
    data->privateData = nullptr;
    bool found = OS::findFirst(pattern.c_str(), *data);
    emscripten::val result = emscripten::val::object();
    if (!found) {
        OS::findClose(*data);
        emscriptenUpdateFindObject(result, 0, *data, false);
        return result;
    }

    int id = sEmscriptenNextFindId++;
    emscriptenUpdateFindObject(result, id, *data, true);
    sEmscriptenFindData.emplace(id, std::move(data));
    return result;
}

bool emscriptenFileFindNext(FileManager&, emscripten::val findData) {
    int id = findData["_pdgFindId"].as<int>();
    auto foundData = sEmscriptenFindData.find(id);
    if (foundData == sEmscriptenFindData.end()) return false;
    bool found = OS::findNext(*foundData->second);
    emscriptenUpdateFindObject(findData, id, *foundData->second, found);
    return found;
}

void emscriptenFileFindClose(FileManager&, const emscripten::val& findData) {
    int id = findData["_pdgFindId"].as<int>();
    auto foundData = sEmscriptenFindData.find(id);
    if (foundData == sEmscriptenFindData.end()) return;
    OS::findClose(*foundData->second);
    sEmscriptenFindData.erase(foundData);
}

void emscriptenLogInitialize(LogManager& manager, const std::string& baseName, int mode) {
    manager.initialize(baseName.c_str(), mode);
}

void emscriptenLogWrite(LogManager& manager, int level, const std::string& category, const std::string& message) {
    manager.writeLogEntry(static_cast<int8>(level), category.c_str(), message.c_str());
}

void emscriptenLogSetLevel(LogManager& manager, int level) {
    manager.setLogLevel(static_cast<int8>(level));
}

int emscriptenLogGetLevel(LogManager& manager) {
    return manager.getLogLevel();
}

void emscriptenTileDefineSet(TileLayer& layer, int tileWidth, int tileHeight, Image* tiles) {
    layer.defineTileSet(tileWidth, tileHeight, tiles);
}

void emscriptenTileSetWorldSize(TileLayer& layer, long width, long height) {
    layer.setWorldSize(width, height);
}

int emscriptenTileGetType(TileLayer& layer, long x, long y) {
    return layer.getTileTypeAt(x, y);
}

void emscriptenTileSetType(TileLayer& layer, long x, long y, int tileType, int facing) {
    layer.setTileTypeAt(x, y, static_cast<uint8>(tileType), static_cast<TileLayer::TFacing>(facing));
}

emscripten::val emscriptenTileGetTypeAndFacing(TileLayer& layer, long x, long y) {
    TileLayer::TFacing facing;
    int tileType = layer.getTileTypeAt(x, y, &facing);
    emscripten::val result = emscripten::val::object();
    result.set("tileType", tileType - static_cast<int>(facing));
    result.set("facing", static_cast<int>(facing));
    return result;
}

static RotatedRect emscriptenRotatedRectFromVal(const emscripten::val& value) {
    RotatedRect result(Rect(
        value["left"].as<float>(), value["top"].as<float>(),
        value["right"].as<float>(), value["bottom"].as<float>()),
        value["radians"].as<float>());
    emscripten::val center = value["centerOffset"];
    if (!center.isUndefined() && !center.isNull()) {
        result.centerOffset = Offset(center["x"].as<float>(), center["y"].as<float>());
    }
    return result;
}

static Quad emscriptenQuadFromVal(const emscripten::val& value) {
    emscripten::val points = value["points"];
    return Quad(
        Point(points[0]["x"].as<float>(), points[0]["y"].as<float>()),
        Point(points[1]["x"].as<float>(), points[1]["y"].as<float>()),
        Point(points[2]["x"].as<float>(), points[2]["y"].as<float>()),
        Point(points[3]["x"].as<float>(), points[3]["y"].as<float>()));
}

void emscriptenSerializerSerialize8(Serializer& serializer, double value) {
    serializer.serialize_8(static_cast<int64>(value));
}

void emscriptenSerializerSerialize4(Serializer& serializer, int value) {
    serializer.serialize_4(static_cast<int32>(value));
}

void emscriptenSerializerSerialize2(Serializer& serializer, int value) {
    serializer.serialize_2(static_cast<int16>(value));
}

void emscriptenSerializerSerialize1(Serializer& serializer, int value) {
    serializer.serialize_1(static_cast<int8>(value));
}

void emscriptenSerializerSerializeFloat(Serializer& serializer, double value) {
    serializer.serialize_f(static_cast<float>(value));
}

void emscriptenSerializerSerializeDouble(Serializer& serializer, double value) {
    serializer.serialize_d(value);
}

void emscriptenSerializerSerializePoint(Serializer& serializer, const Point& value) {
    serializer.serialize_point(value);
}

void emscriptenSerializerSerializeVector(Serializer& serializer, const Vector& value) {
    serializer.serialize_vector(value);
}

void emscriptenSerializerSerializeString(Serializer& serializer, const std::string& value) {
    serializer.serialize_str(value.c_str());
}

void emscriptenSerializerSerializeMem(Serializer& serializer, const std::string& value) {
    serializer.serialize_mem(value.data(), static_cast<uint32>(value.size()));
}

void emscriptenSerializerSerializeRotatedRect(Serializer& serializer, const emscripten::val& value) {
    serializer.serialize_rotr(emscriptenRotatedRectFromVal(value));
}

void emscriptenSerializerSerializeQuad(Serializer& serializer, const emscripten::val& value) {
    serializer.serialize_quad(emscriptenQuadFromVal(value));
}

uint32 emscriptenSerializerSizeofString(Serializer& serializer, const std::string& value) {
    return serializer.sizeof_str(value.c_str());
}

uint32 emscriptenSerializerSizeofPoint(Serializer& serializer, const Point& value) {
    return serializer.sizeof_point(value);
}

uint32 emscriptenSerializerSizeofVector(Serializer& serializer, const Vector& value) {
    return serializer.sizeof_vector(value);
}

uint32 emscriptenSerializerSizeofMem(Serializer& serializer, const std::string& value) {
    return serializer.sizeof_mem(value.data(), static_cast<uint32>(value.size()));
}

uint32 emscriptenSerializerSizeofRotatedRect(Serializer& serializer, const emscripten::val& value) {
    return serializer.sizeof_rotr(emscriptenRotatedRectFromVal(value));
}

uint32 emscriptenSerializerSizeofQuad(Serializer& serializer, const emscripten::val& value) {
    return serializer.sizeof_quad(emscriptenQuadFromVal(value));
}

MemBlock* emscriptenSerializerGetData(Serializer& serializer) {
    return new MemBlock(reinterpret_cast<char*>(serializer.getDataPtr()), serializer.getDataSize(), false);
}

double emscriptenDeserializerDeserialize8(Deserializer& deserializer) {
    return static_cast<double>(deserializer.deserialize_8());
}

int emscriptenDeserializerDeserialize4(Deserializer& deserializer) {
    return deserializer.deserialize_4();
}

int emscriptenDeserializerDeserialize2(Deserializer& deserializer) {
    return deserializer.deserialize_2();
}

int emscriptenDeserializerDeserialize1(Deserializer& deserializer) {
    return deserializer.deserialize_1();
}

double emscriptenDeserializerDeserializeFloat(Deserializer& deserializer) {
    return deserializer.deserialize_f();
}

double emscriptenDeserializerDeserializeDouble(Deserializer& deserializer) {
    return deserializer.deserialize_d();
}

Point emscriptenDeserializerDeserializePoint(Deserializer& deserializer) {
    return deserializer.deserialize_point();
}

Vector emscriptenDeserializerDeserializeVector(Deserializer& deserializer) {
    return deserializer.deserialize_vector();
}

std::string emscriptenDeserializerDeserializeString(Deserializer& deserializer) {
    std::string result;
    deserializer.deserialize_string(result);
    if (!result.empty() && result.back() == '\0') result.pop_back();
    return result;
}

MemBlock* emscriptenDeserializerDeserializeMem(Deserializer& deserializer) {
    uint32 size = deserializer.deserialize_memGetLen();
    MemBlock* result = new MemBlock(size);
    deserializer.deserialize_mem(result->ptr, size);
    return result;
}

emscripten::val emscriptenDeserializerDeserializeRotatedRect(Deserializer& deserializer) {
    RotatedRect value = deserializer.deserialize_rotr();
    emscripten::val result = emscripten::val::object();
    result.set("left", value.left);
    result.set("top", value.top);
    result.set("right", value.right);
    result.set("bottom", value.bottom);
    result.set("radians", value.radians);
    emscripten::val center = emscripten::val::object();
    center.set("x", value.centerOffset.x);
    center.set("y", value.centerOffset.y);
    result.set("centerOffset", center);
    return result;
}

emscripten::val emscriptenDeserializerDeserializeQuad(Deserializer& deserializer) {
    Quad value = deserializer.deserialize_quad();
    emscripten::val points = emscripten::val::array();
    for (int i = 0; i < 4; ++i) {
        emscripten::val point = emscripten::val::object();
        point.set("x", value.points[i].x);
        point.set("y", value.points[i].y);
        points.call<void>("push", point);
    }
    emscripten::val result = emscripten::val::object();
    result.set("points", points);
    return result;
}

void emscriptenDeserializerSetData(Deserializer& deserializer, MemBlock& data) {
    deserializer.setDataPtr(data.ptr, static_cast<uint32>(data.bytes));
}

uint32 emscriptenSpriteLayerGetSerializedSize(SpriteLayer& layer, Serializer& serializer) {
    return layer.getSerializedSize(&serializer);
}

void emscriptenSpriteLayerSerialize(SpriteLayer& layer, Serializer& serializer) {
    layer.serialize(&serializer);
}

void emscriptenSpriteLayerDeserialize(SpriteLayer& layer, Deserializer& deserializer) {
    layer.deserialize(&deserializer);
}

void setSerializationDebugMode(bool mode) {
    ISerializer::s_DebugMode = mode;
}

void emscriptenInit() {
    static const char* argv[] = { "pdg-wasm" };
    pdg_LibSaveArgs(1, argv);
    pdg_LibInit();
}

void emscriptenIdle() {
    pdg_LibIdle();
}

void emscriptenQuit() {
    pdg_LibQuit();
}

bool emscriptenIsQuitting() {
    return pdg_LibIsQuitting();
}


// end stuff to add to C++ API

FileManager* FileManager::createSingletonInstance() {
    return new FileManager();
}
std::string& FileManager::getApplicationDataDirectory() {
    static std::string _wdstr;
    _wdstr.assign( OS::getApplicationDataDirectory() );
    return _wdstr;
}
std::string& FileManager::getApplicationDirectory() {
    static std::string _wdstr;
    _wdstr.assign( OS::getApplicationDirectory() );
    return _wdstr;
}
std::string& FileManager::getApplicationResourceDirectory() {
    static std::string _wdstr;
    _wdstr.assign( OS::getApplicationResourceDirectory() );
    return _wdstr;
}

static bool sEmscriptenGlfwInitialized = false;

void platform_cleanup() 
{
#ifndef PDG_NO_GUI
  if (sEmscriptenGlfwInitialized) {
    glfwTerminate();
    sEmscriptenGlfwInitialized = false;
  }
#endif
  EM_ASM(
     pdg_em_platform_cleanup();
  );
}

void platform_init(int argc, const char* argv[])
{
#ifndef PDG_NO_GUI
  if (EM_ASM_INT({
      return typeof window !== 'undefined' &&
             typeof window.addEventListener === 'function' &&
             typeof document !== 'undefined';
  })) {
    glfwInitIfNeeded();
    sEmscriptenGlfwInitialized = true;
  }
#endif
  EM_ASM({
     pdg_em_platform_init($0, $1);
  }, argc, argv);
}

void platform_pollEvents()
{
#ifndef PDG_NO_GUI
  if (sEmscriptenGlfwInitialized) glfwPollEvents();
#endif
  EM_ASM(
     pdg_em_platform_pollEvents();
  );
}

} // end namespace pdg
