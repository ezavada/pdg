#ifndef PDG_SPRITER_TRANSFORM_H_INCLUDED
#define PDG_SPRITER_TRANSFORM_H_INCLUDED

#include "pdg/sys/coordinates.h"
#include "spriterengine/objectinfo/universalobjectinterface.h"
#include <algorithm>

namespace pdg {
// Evaluated Spriter objects already include the sprite root. Preserve the
// authored pivot and signed scale, rotating around that world-space pivot.
inline RotatedRect spriterBoxRect(SpriterEngine::UniversalObjectInterface& object) {
    const auto position = object.getPosition();
    const auto scale = object.getScale();
    const auto size = object.getSize();
    const auto pivot = object.getPivot();
    const double width = size.x * scale.x, height = size.y * scale.y;
    const double x0 = -pivot.x * width, x1 = (1.0 - pivot.x) * width;
    const double y0 = -pivot.y * height, y1 = (1.0 - pivot.y) * height;
    Rect bounds(position.x + std::min(x0, x1), position.y + std::min(y0, y1),
                position.x + std::max(x0, x1), position.y + std::max(y0, y1));
    return RotatedRect(bounds, object.getAngle(), Point(position.x, position.y) - bounds.centerPoint());
}
}
#endif
