#ifndef PDG_EM_CAMERA_H
#define PDG_EM_CAMERA_H
#include "pdg/sys/camera.h"
namespace pdg {
inline RotatedRect browserCameraRect(const emscripten::val& value) {
    RotatedRect rect(Rect(value["left"].as<float>(),value["top"].as<float>(),value["right"].as<float>(),value["bottom"].as<float>()));
    if (!value["radians"].isUndefined()) rect.radians=value["radians"].as<float>();
    if (!value["centerOffset"].isUndefined()) rect.centerOffset=Offset(value["centerOffset"]["x"].as<float>(),value["centerOffset"]["y"].as<float>());
    return rect;
}
inline emscripten::val browserCameraRectValue(const RotatedRect& rect) {
    auto value=emscripten::val::object();
    value.set("left",rect.left); value.set("top",rect.top); value.set("right",rect.right); value.set("bottom",rect.bottom); value.set("radians",rect.radians);
    auto offset=emscripten::val::object(); offset.set("x",rect.centerOffset.x); offset.set("y",rect.centerOffset.y); value.set("centerOffset",offset);
    return value;
}
}

EMSCRIPTEN_BINDINGS(pdg_camera) {
    using namespace emscripten; using namespace pdg;
    constant("eventType_ZoomComplete", static_cast<int>(eventType_ZoomComplete));
    constant("camera_Crossfade", static_cast<int>(camera_Crossfade));
    constant("camera_WipeLeft", static_cast<int>(camera_WipeLeft));
    constant("camera_WipeRight", static_cast<int>(camera_WipeRight));
    constant("camera_WipeUp", static_cast<int>(camera_WipeUp));
    constant("camera_WipeDown", static_cast<int>(camera_WipeDown));
    constant("camera_LumaFade", static_cast<int>(camera_LumaFade));
    constant("camera_WhipLeft", static_cast<int>(camera_WhipLeft));
    constant("camera_WhipRight", static_cast<int>(camera_WhipRight));
    constant("camera_WhipUp", static_cast<int>(camera_WhipUp));
    constant("camera_WhipDown", static_cast<int>(camera_WhipDown));
    constant("matchSource", static_cast<int>(matchSource));
    constant("matchSourceAndSize", static_cast<int>(matchSourceAndSize));
    constant("matchTarget", static_cast<int>(matchTarget));
    constant("matchTargetAndSize", static_cast<int>(matchTargetAndSize));
    constant("ser_LayerDraw", static_cast<int>(ser_LayerDraw));

}

#endif
