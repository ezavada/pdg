#ifndef PDG_SPATIAL_TRANSFORM_H_INCLUDED
#define PDG_SPATIAL_TRANSFORM_H_INCLUDED

#include "pdg/sys/coordinates.h"
#include <cmath>
#include <stdexcept>

namespace pdg {
/** Rendering-independent affine transform. Points map to
 * (a*x + c*y + tx, b*x + d*y + ty). Composition preserves shear and reflection.
 * @ingroup Animation
 */
struct SpatialTransform {
    double a = 1, b = 0, c = 0, d = 1, tx = 0, ty = 0;
    static SpatialTransform fromTRS(double x, double y, double radians,
                                    double scaleX = 1, double scaleY = 1) {
        const double cosine = std::cos(radians), sine = std::sin(radians);
        return {cosine*scaleX, sine*scaleX, -sine*scaleY, cosine*scaleY, x, y};
    }
    static SpatialTransform compose(const SpatialTransform& parent, const SpatialTransform& local) {
        return {parent.a*local.a + parent.c*local.b, parent.b*local.a + parent.d*local.b,
                parent.a*local.c + parent.c*local.d, parent.b*local.c + parent.d*local.d,
                parent.a*local.tx + parent.c*local.ty + parent.tx,
                parent.b*local.tx + parent.d*local.ty + parent.ty};
    }
    Point transformPoint(const Point& p) const {
        return Point(a*p.x + c*p.y + tx, b*p.x + d*p.y + ty);
    }
    SpatialTransform inverse() const {
        const double determinant = a*d - b*c;
        if (!std::isfinite(determinant) || determinant == 0)
            throw std::invalid_argument("Cannot invert a singular spatial transform");
        return {d/determinant, -b/determinant, -c/determinant, a/determinant,
                (c*ty - d*tx)/determinant, (b*tx - a*ty)/determinant};
    }
};
}
#endif
