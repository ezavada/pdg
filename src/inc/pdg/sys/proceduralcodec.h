#ifndef PDG_PROCEDURAL_CODEC_H
#define PDG_PROCEDURAL_CODEC_H
#include "pdg/sys/animationcontroller.h"
#include <cmath>
#include <stdexcept>
namespace pdg {
// Internal value transport shared by native script bindings, browser and snapshots.
class ProceduralValues {
    const std::vector<double>& values;size_t at=0;
public:
    explicit ProceduralValues(const std::vector<double>& v):values(v){}
    double real(){if(at==values.size()||!std::isfinite(values[at]))throw std::invalid_argument("Invalid procedural values");return values[at++];}
    uint32_t integer(){double n=real();if(n<0||n>4294967295.0||n!=std::floor(n))throw std::invalid_argument("Invalid procedural integer");return uint32_t(n);}
    bool flag(){auto n=integer();if(n>1)throw std::invalid_argument("Invalid procedural boolean");return n;}
    std::vector<uint32_t> ids(){auto n=integer();if(n>4096)throw std::invalid_argument("Procedural chain too long");std::vector<uint32_t> v;for(uint32_t i=0;i<n;++i)v.push_back(integer());return v;}
    void end(){if(at!=values.size())throw std::invalid_argument("Unexpected procedural values");}
};
inline void appendIDs(std::vector<double>& v,const std::vector<uint32_t>& ids){v.push_back(ids.size());v.insert(v.end(),ids.begin(),ids.end());}
inline std::vector<double> encodeFABRIK(const AnimationFABRIK& c){std::vector<double> v={c.targetX,c.targetY,c.influence,c.tolerance,double(c.space),double(c.maxIterations),double(c.bendDirection)};appendIDs(v,c.chain);v.push_back(c.minimum.size());v.insert(v.end(),c.minimum.begin(),c.minimum.end());v.insert(v.end(),c.maximum.begin(),c.maximum.end());return v;}
inline AnimationFABRIK decodeFABRIK(ProceduralValues& v){AnimationFABRIK c;c.targetX=v.real();c.targetY=v.real();c.influence=v.real();c.tolerance=v.real();c.space=v.integer();c.maxIterations=v.integer();double bend=v.real();if(bend!=1&&bend!=-1)throw std::invalid_argument("Invalid FABRIK bend direction");c.bendDirection=int(bend);c.chain=v.ids();auto n=v.integer();if(n>4096)throw std::invalid_argument("Too many FABRIK limits");for(uint32_t i=0;i<n;++i)c.minimum.push_back(v.real());for(uint32_t i=0;i<n;++i)c.maximum.push_back(v.real());return c;}
inline std::vector<double> encodeFABRIKResult(const AnimationFABRIKResult& r){return {r.solveError,r.reachError,double(r.iterations),double(r.converged),double(r.reached),double(r.limited),double(r.withinGeometricReach)};}
inline std::vector<double> encodeJiggle(const AnimationJiggle& c){std::vector<double> v={double(c.mode),double(c.ik)};appendIDs(v,c.chain);v.insert(v.end(),{c.frequency,c.dampingRatio,c.influence,c.inertia,c.maxAngle,c.length,c.gravityX,c.gravityY,c.maxDistance,c.maxSpeed,c.maxAngularSpeed,c.maxStepSeconds,c.teleportDistance,c.teleportAngle,double(c.maxSubsteps),double(c.enabled),double(c.resetOnSeek),double(c.resetOnTeleport)});v.push_back(c.joints.size());for(const auto& j:c.joints){v.push_back(j.bone);for(auto member:{&AnimationJiggleJoint::length,&AnimationJiggleJoint::frequency,&AnimationJiggleJoint::dampingRatio,&AnimationJiggleJoint::inertia,&AnimationJiggleJoint::maxAngle,&AnimationJiggleJoint::maxAngularSpeed,&AnimationJiggleJoint::gravityX,&AnimationJiggleJoint::gravityY}){v.push_back(bool(j.*member));if(j.*member)v.push_back(*(j.*member));}}return v;}
inline AnimationJiggle decodeJiggle(ProceduralValues& v){AnimationJiggle c;c.mode=v.integer();c.ik=v.integer();c.chain=v.ids();c.frequency=v.real();c.dampingRatio=v.real();c.influence=v.real();c.inertia=v.real();c.maxAngle=v.real();c.length=v.real();c.gravityX=v.real();c.gravityY=v.real();c.maxDistance=v.real();c.maxSpeed=v.real();c.maxAngularSpeed=v.real();c.maxStepSeconds=v.real();c.teleportDistance=v.real();c.teleportAngle=v.real();c.maxSubsteps=v.integer();c.enabled=v.flag();c.resetOnSeek=v.flag();c.resetOnTeleport=v.flag();auto count=v.integer();if(count>4096)throw std::invalid_argument("Too many jiggle joint overrides");while(count--){AnimationJiggleJoint j;j.bone=v.integer();for(auto member:{&AnimationJiggleJoint::length,&AnimationJiggleJoint::frequency,&AnimationJiggleJoint::dampingRatio,&AnimationJiggleJoint::inertia,&AnimationJiggleJoint::maxAngle,&AnimationJiggleJoint::maxAngularSpeed,&AnimationJiggleJoint::gravityX,&AnimationJiggleJoint::gravityY})if(v.flag())j.*member=v.real();c.joints.push_back(j);}return c;}
inline std::vector<double> encodeJiggleState(const JiggleState& s){std::vector<double> v={double(s.initialized),s.x,s.y,s.velocityX,s.velocityY,double(s.joints.size())};for(auto& j:s.joints)v.insert(v.end(),{j.angle,j.velocity,j.desired,j.pivotX,j.pivotY,j.pivotVelocityX,j.pivotVelocityY});return v;}
inline JiggleState decodeJiggleState(ProceduralValues& v){JiggleState s;s.initialized=v.flag();s.x=v.real();s.y=v.real();s.velocityX=v.real();s.velocityY=v.real();auto n=v.integer();if(n>4096)throw std::invalid_argument("Too many jiggle states");for(uint32_t i=0;i<n;++i)s.joints.push_back({v.real(),v.real(),v.real(),v.real(),v.real(),v.real(),v.real()});return s;}
inline std::vector<double> encodeJiggleResult(const JiggleResult& r){return {r.lagDistance,r.influence,r.simulatedSeconds,r.desiredX,r.desiredY,r.filteredX,r.filteredY,r.effectiveX,r.effectiveY,double(r.substeps),double(r.limited),double(r.reset)};}
}
#endif
