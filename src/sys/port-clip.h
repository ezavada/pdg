#ifndef PDG_PORT_CLIP_H_INCLUDED
#define PDG_PORT_CLIP_H_INCLUDED
#include "pdg/sys/port.h"
#include <algorithm>
namespace pdg {
// Internal operation scope; the public Port still has one replaceable clip rectangle.
class ScopedPortClip {
    Port* port;
    Rect saved;
public:
    ScopedPortClip(Port* p, const Rect& bounds, const Attributes& attrs, float padding = 0)
        : port(attrs.getClipOverflow() ? p : nullptr) {
        if (!port) return;
        saved = port->getClipRect();
        Quad q(bounds);
        for (auto& point : q.points) {
            const auto v = attrs.getTransform() * glm::vec3(point.x, point.y, 1);
            point = Point(v.x, v.y);
        }
        Rect clip = q.getBounds();
        clip.left -= padding; clip.top -= padding;
        clip.right += padding; clip.bottom += padding;
        port->setClipRect(saved.intersection(clip));
    }
    ~ScopedPortClip() { if (port) port->setClipRect(saved); }
    ScopedPortClip(const ScopedPortClip&) = delete;
    ScopedPortClip& operator=(const ScopedPortClip&) = delete;
};
}
#endif
