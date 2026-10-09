// Particle headers and constants; retained class registrations are generated.
#ifndef PDG_EM_PARTICLES_H
#define PDG_EM_PARTICLES_H
#include "pdg/sys/particle.h"
#include "pdg/sys/particleemitter.h"

EMSCRIPTEN_BINDINGS(pdg_particles) {
    using namespace emscripten; using namespace pdg;

    constant("eventType_ParticleBreak",eventType_ParticleBreak);
}
#endif
