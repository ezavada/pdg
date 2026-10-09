#ifndef PDG_SCRIPT_PARTICLE_TRAIL_OPTIONS_H
#define PDG_SCRIPT_PARTICLE_TRAIL_OPTIONS_H
#include "pdg/sys/particle.h"
#include <cmath>

namespace pdg {
// Field defaults and integer validation are shared by all script backends and
// semantic recorders. The readers preserve each VM's exception handling.
template<class NumberReader, class ColorReader>
ParticleTrailOptions readParticleTrailOptions(NumberReader number, ColorReader color) {
    ParticleTrailOptions result;
    result.lifetime=number("lifetime",result.lifetime);
    result.width=number("width",result.width);
    result.endWidth=number("endWidth",result.endWidth);
    result.endOpacity=number("endOpacity",result.endOpacity);
    result.minDistance=number("minDistance",result.minDistance);
    result.sampleInterval=number("sampleInterval",result.sampleInterval);
    result.breakDistance=number("breakDistance",result.breakDistance);
    const double count=number("maxPoints",result.maxPoints);
    if (!std::isfinite(count) || count<2 || count>4096 || std::floor(count)!=count)
        throw std::invalid_argument("Trail maxPoints must be an integer in [2,4096]");
    result.maxPoints=static_cast<uint32>(count);
    result.color=color(result.color);
    result.validate();
    return result;
}
}
#endif
