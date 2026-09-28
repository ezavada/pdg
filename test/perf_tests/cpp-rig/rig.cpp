// Articulated engine throughput, including animation publication, without drawing.
#include "pdg/sys/initializer.h"
#include "pdg/sys/sprite.h"
#include "pdg/sys/spritelayer.h"
#include "pdg/sys/animationphysics.h"
#include "pdg-main.h"
#include "spritemanager.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <vector>
namespace {
using Clock=std::chrono::steady_clock;
double milliseconds(Clock::time_point start){return std::chrono::duration<double,std::milli>(Clock::now()-start).count();}
struct Rig {pdg::Sprite* sprite;pdg::Sprite* axle;};
}
namespace pdg {
bool Initializer::allowHorizontalOrientation() throw() { return true; }
bool Initializer::allowVerticalOrientation() throw() { return true; }
const char *Initializer::getAppName(bool) throw() { return "PDG Rig Performance"; }
const char *Initializer::getMainResourceFileName() throw() { return nullptr; }
bool Initializer::installGlobalHandlers() throw() { return false; }
bool Initializer::getGraphicsEnvironmentDimensions(Rect, Rect, long &w, long &h, uint8 &d) throw() {
    w = h = 1;
    d = 32;
    return false;
}
} // namespace pdg
int main() {
    try {
        if(pdg::main_initManagers()!=0)throw std::runtime_error("Manager initialization failed");
        const auto path=(std::filesystem::path(__FILE__).parent_path()/"../../data/wheel-chains/wheel.scml").lexically_normal().string();
        std::cout<<"rigs,parts,setup_ms,mean_step_ms,p95_step_ms,mode_switch_ms,flip_ms\n";
        for(int count:{1,10,50,100}) {
#ifdef PDG_NO_GUI
            auto* layer=pdg::createSpriteLayer();
#else
            auto* layer=pdg::createSpriteLayer(nullptr);
#endif
            layer->setUseChipmunkPhysics(true);layer->setGravity(981);layer->setDamping(1);
            std::vector<Rig> rigs;
            auto start=Clock::now();
            for(int n=0;n<count;++n) {
                auto* sprite=layer->createSpriteFromSpriterFile(path.c_str());
                sprite->pauseAnimation();sprite->enableAnimationPose("reference");sprite->setLocation(n*500,0);
                pdg::AnimationPhysicsDefinition def;def.rootMode=pdg::animationRoot_Follow;
                pdg::AnimationPhysicsBody wheel;wheel.bone=0;wheel.mass=12;wheel.length=0;wheel.radius=50;def.bodies.push_back(wheel);
                for(int chain=0;chain<3;++chain)for(int link=0;link<5;++link) {
                    const bool weight=link==4;const auto index=uint32_t(def.bodies.size());
                    pdg::AnimationPhysicsBody b;b.bone=index;b.mass=weight?2:.5;b.length=weight?0:35;b.radius=weight?10:4;b.offsetX=b.length/2;def.bodies.push_back(b);
                    pdg::AnimationPhysicsJoint j;j.parent=link?index-1:0;j.child=index;
                    const double angle=(-90+chain*120)*3.14159265358979323846/180;
                    j.parentX=link?17.5:50*std::cos(angle);j.parentY=link?0:50*std::sin(angle);j.childX=-b.length/2;
                    j.minAngle=-1e9;j.maxAngle=1e9;def.joints.push_back(j);
                }
                sprite->setupAnimationPhysics(def);
                for(const auto& name:sprite->getPartNames())sprite->findPart(name)->collider.setCollisionMask(0);
                auto* axle=layer->createSprite();axle->setLocation(n*500,0);axle->setupPhysicsBody().setMode(pdg::physicsBody_Kinematic);
                axle->physics.createPivotJoint(sprite->findPart("wheel")->physics);
                sprite->physics.addContinuousTorque(300000);
                rigs.push_back({sprite,axle});
            }
            const double setup=milliseconds(start);
            auto tick=[&]{pdg::SpriteManager::getSingletonInstance()->stepAnimationPhysics(10);layer->animateLayer(10);};
            for(int i=0;i<50;++i)tick();
            std::vector<double> samples;
            for(int i=0;i<200;++i){start=Clock::now();tick();samples.push_back(milliseconds(start));}
            double sum=0;for(double ms:samples)sum+=ms;std::sort(samples.begin(),samples.end());
            start=Clock::now();
            for(auto r:rigs){r.sprite->physics.stopAllForces();r.sprite->setAnimationPhysicsDriveSettings({100000,100000,4,1},"wheel");r.sprite->setAnimationPhysicsMode(pdg::animationPhysics_Driven,"wheel",false,0);r.sprite->setAnimationPhysicsMode(pdg::animationPhysics_Dynamic,"wheel",false,0);}
            const double switches=milliseconds(start);
            start=Clock::now();for(auto r:rigs){r.sprite->setFlipX(true);r.sprite->setFlipX(false);}
            const double flips=milliseconds(start);
            for(auto r:rigs)if(!std::isfinite(r.sprite->physics.getMomentOfInertia()+r.sprite->physics.getAngularMomentum()))throw std::runtime_error("Nonfinite assembly");
            std::cout<<count<<','<<count*16<<','<<setup<<','<<sum/samples.size()<<','<<samples[size_t(samples.size()*.95)]<<','<<switches<<','<<flips<<std::endl;
            pdg::cleanupLayer(layer);
        }
        return 0;
    }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
