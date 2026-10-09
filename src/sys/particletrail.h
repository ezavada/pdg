#ifndef PDG_PARTICLE_TRAIL_INTERNAL_H
#define PDG_PARTICLE_TRAIL_INTERNAL_H
#include "pdg/sys/particle.h"
#include <algorithm>
#include <cmath>
#include <vector>

namespace pdg {
class Port;
// Simulation history contains no Particle, body or emitter references. A layer
// can retain a fading tail after its source has expired.
class ParticleTrail {
public:
    struct Sample { Point position; double time; float opacity; };
    ParticleTrailOptions options;
    std::vector<Sample> ring;
    size_t first=0, count=0;
    double time=0, nextSample=0;
    Sample head{};
    bool initialized=false;
    explicit ParticleTrail(const ParticleTrailOptions& settings) : options(settings), ring(settings.maxPoints) {}
    const Sample& at(size_t i) const { return ring[(first+i)%ring.size()]; }
    void push(const Sample& sample) {
        if (count && std::hypot(sample.position.x-at(count-1).position.x,sample.position.y-at(count-1).position.y)<1e-6) return;
        if(count==ring.size()) { first=(first+1)%ring.size(); --count; }
        ring[(first+count++)%ring.size()]=sample;
    }
    void reset(const Point& position, float opacity) {
        first=count=0; time=0; nextSample=options.sampleInterval;
        head={position,0,opacity}; initialized=true; push(head);
    }
    void prune() {
        const double cutoff=time-options.lifetime;
        // Keep one point preceding the cutoff to clip the oldest segment exactly.
        while(count>1 && at(1).time<=cutoff) { first=(first+1)%ring.size();--count; }
    }
    bool empty() const { return !initialized || time-head.time>=options.lifetime; }
    void age(double seconds) { time+=seconds; prune(); }
    void advance(double seconds,const Point& position,float opacity) {
        if(!initialized)reset(position,opacity);
        if(seconds<=0)return;
        const auto previous=head.position;
        const double start=time;
        time+=seconds;
        const double distance=std::hypot(position.x-previous.x,position.y-previous.y);
        if(options.breakDistance>0 && distance>options.breakDistance) { reset(position,opacity);return; }
        // Bound work after a long tick by both the age window and ring capacity.
        const double earliest=std::max(time-options.lifetime,time-options.sampleInterval*(options.maxPoints-1));
        if(nextSample<earliest)nextSample+=std::ceil((earliest-nextSample)/options.sampleInterval)*options.sampleInterval;
        // The iteration cap also protects very large finite times, where adding
        // a small interval can no longer change the floating-point timestamp.
        for(size_t n=0;n<options.maxPoints && nextSample<=time+1e-10;++n) {
            const double t=std::clamp((nextSample-start)/seconds,0.0,1.0);
            Point p(previous.x+(position.x-previous.x)*t,previous.y+(position.y-previous.y)*t);
            if(!count || std::hypot(p.x-at(count-1).position.x,p.y-at(count-1).position.y)>=options.minDistance)
                push({p,nextSample,float(head.opacity+(opacity-head.opacity)*t)});
            nextSample+=options.sampleInterval;
        }
        if(distance>1e-6)head={position,time,opacity};
        prune();
    }
    // Drawing uses a temporary head between fixed samples, without consuming a
    // history slot. Stopping leaves its timestamp fixed so the whole tail ages.
    std::vector<Sample> samples() const {
        std::vector<Sample> result;
        if(empty())return result;
        result.reserve(count+1);
        for(size_t i=0;i<count;++i)result.push_back(at(i));
        if(result.empty() || std::hypot(head.position.x-result.back().position.x,head.position.y-result.back().position.y)>1e-6)
            result.push_back(head);
        const double cutoff=time-options.lifetime;
        if(result.size()>1 && result.front().time<cutoff) {
            auto& a=result.front();const auto& b=result[1];
            const double t=std::clamp((cutoff-a.time)/(b.time-a.time),0.0,1.0);
            a.position=Point(a.position.x+(b.position.x-a.position.x)*t,a.position.y+(b.position.y-a.position.y)*t);
            a.opacity+=float((b.opacity-a.opacity)*t);a.time=cutoff;
        }
        return result;
    }
};
#ifndef PDG_NO_GUI
void drawParticleTrail(Port& port,const ParticleTrail& trail,const SpatialTransform& view);
#endif
}
#endif
