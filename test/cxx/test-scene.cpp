#include "pdg/sys/scene.h"
#include "pdg/sys/spritelayer.h"
#include "pdg/sys/sprite.h"
#include "pdg/sys/camera.h"
#include "pdg/sys/initializer.h"
#include "pdg/sys/ieventhandler.h"
#include "pdg/sys/events.h"
#include "pdg/sys/part.h"
#include "pdg/sys/particle.h"
#include "pdg/sys/image.h"
#ifndef PDG_NO_GUI
#include "image-opengl.h"
#endif
#include <cstring>
#include "pdg-main.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
namespace pdg {
bool Initializer::allowHorizontalOrientation() throw(){return true;}
bool Initializer::allowVerticalOrientation() throw(){return true;}
const char* Initializer::getAppName(bool) throw(){return "Scene tests";}
const char* Initializer::getMainResourceFileName() throw(){return nullptr;}
bool Initializer::installGlobalHandlers() throw(){return false;}
bool Initializer::getGraphicsEnvironmentDimensions(Rect,Rect,long& width,long& height,uint8& depth) throw(){width=height=1;depth=32;return false;}
}
namespace {
void check(bool value,const char* message){if(!value)throw std::runtime_error(message);}
void checkNear(double value,double expected){check(std::abs(value-expected)<.0001,"Unexpected scene simulation value");}
class Count : public pdg::IEventHandler {
public:int count=0;
    bool handleEvent(pdg::EventEmitter*,long,void*) noexcept override{++count;return true;}
};
#include "scene-collision-query-tests.inc"
}
int main(){
    using namespace pdg;
    try{
        check(main_initManagers()==0,"Initialize managers");
        collisionQueryChecks();
        Scene game,ui;game.setManual(true);ui.setManual(true);
        Scene::advanceAll();check(!game.isDisposed(),"Host pump preserves stack scene lifetime");
        auto* l=game.createSpriteLayer();auto* hud=ui.createSpriteLayer();
        auto* player=l->createSprite();auto* indicator=hud->createSprite();
        player->setMovement(100,0);indicator->setMovement(20,0);
        auto* counter=new Count();counter->addRef();game.addHandler(counter,eventType_Timer);
        game.startTimer(7,100,false);game.advance(.1);ui.advance(.1);game.pause();
        for(int i=0;i<5;++i){game.advance(.1);ui.advance(.1);}
        checkNear(player->getLocation().x,10);checkNear(indicator->getLocation().x,12);check(counter->count==1,"Gameplay timer paused");
        game.resume();game.advance(.1);checkNear(player->getLocation().x,20);check(counter->count==2,"Gameplay timer resumed");
        game.pauseTimer(7);game.pause();game.resume();game.advance(.1);check(counter->count==2,"Scene resume preserves timer-local pause");
        game.getCamera()->setMovement(10,0);game.advance(.1);checkNear(game.getCamera()->getLocation().x,1);
        game.pause();game.advance(.1);checkNear(game.getCamera()->getLocation().x,1);game.resume();
        check(l->getEffectiveCamera()==game.getCamera(),"Scene camera inherited");
        game.removeLayer(l);check(l->getNthSprite(0)==player,"Detach keeps sprite alive");
        game.dispose();ui.addLayer(l);ui.advance(.1);checkNear(player->getLocation().x,50);ui.disposeLayer(l);
        check(ui.getLayerCount()==1,"disposeLayer preserves HUD layer");counter->release();
        Scene fixed;fixed.setManual(true);fixed.setFixedStep(1.0/60);fixed.setInterpolation(true);
        fixed.advance(.1);check(fixed.getTick()==6,"Fixed clock retains fractional precision");checkNear(fixed.getSimulationTime(),.1);
        auto* interpolated=fixed.createSpriteLayer()->createSprite();interpolated->setMovement(60,0);
        fixed.advance(1.0/60+.5/60);checkNear(interpolated->getLocation().x,1);
        checkNear(fixed.presentationTransform(interpolated).transformPoint(interpolated->getLocation()).x,.5);
        fixed.pause();checkNear(fixed.presentationTransform(interpolated).transformPoint(interpolated->getLocation()).x,.5);
        interpolated->setLocation(10,0);checkNear(fixed.presentationTransform(interpolated).transformPoint(interpolated->getLocation()).x,10);
        fixed.resume();fixed.setInterpolation(false);fixed.setFixedStep(1.0/60);
        fixed.pause();fixed.advance(10);fixed.resume();fixed.advance(1.0/60);check(fixed.getTick()==8,"Pause adds no debt");
        Scene subscriber,source;subscriber.setManual(true);source.setManual(true);
        auto* external=new Count();external->addRef();subscriber.subscribe(source,external,eventType_Timer);
        source.startTimer(1,10,false);source.advance(.01);check(external->count==1,"Scene subscription receives source events");
        subscriber.dispose();source.advance(.01);check(external->count==1,"Disposal disconnects subscription");external->release();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        Scene physics,next;physics.setManual(true);next.setManual(true);
        auto* pl=physics.createSpriteLayer();pl->setUseChipmunkPhysics(true);auto* body=pl->createSprite();
        body->setupPhysicsBody().setVelocity(Vector(20,0));physics.advance(.1);double x=body->getLocation().x;
        physics.pause();next.advance(.1);physics.advance(.1);checkNear(body->getLocation().x,x);
        auto* oldWorld=pl->getSpace();physics.removeLayer(pl);check(pl->getSpace()!=oldWorld,"Detached layer has unstepped storage world");
        next.addLayer(pl);next.advance(.1);check(body->getLocation().x>x,"Transferred body resumes in destination scene");
#endif
        std::cout<<"Scene lifecycle, timers, HUD, camera, fixed-step and physics checks passed\n";
        return 0;
    }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
