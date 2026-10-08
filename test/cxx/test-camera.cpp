#include "pdg/sys/camera.h"
#include "pdg/sys/events.h"
#include "pdg/sys/ieventhandler.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace pdg;
static void near(double actual, double expected) {
    if (!std::isfinite(actual) || std::abs(actual-expected)>0.0001) throw std::runtime_error("Camera value mismatch");
}
struct ZoomHandler : IEventHandler {
    int count = 0;
    float zoom = 0;
    bool valid = true;
    bool handleEvent(EventEmitter* emitter, long type, void* data) noexcept override {
        auto* info = static_cast<CameraZoomInfo*>(data);
        valid = valid && type == eventType_ZoomComplete && emitter == info->camera;
        ++count; zoom = info->zoom; return false;
    }
};
static void checkTransformCaching() {
    Camera camera;
    auto view = camera.getViewTransform();
    near(view.a,1); near(view.d,1); near(view.tx,0); near(view.ty,0);
    // Repeat each query to exercise hits as well as synchronous changes.
    auto check = [&](const pdg::Point& anchor, float movement, float zoom,
                     double a, double b, double c, double d, double x, double y) {
        for (int i=0; i<2; ++i) {
            const auto v=camera.getViewTransform(anchor,movement,zoom);
            near(v.a,a); near(v.b,b); near(v.c,c); near(v.d,d); near(v.tx,x); near(v.ty,y);
        }
    };
    camera.setLocation(10,20);
    check(pdg::Point(),1,1,1,0,0,1,-10,-20);
    check(pdg::Point(100,50),1,1,1,0,0,1,90,30);
    check(pdg::Point(100,50),.5,1,1,0,0,1,95,40);
    camera.setZoom(4);
    check(pdg::Point(),1,.5,2,0,0,2,-20,-40);
    check(pdg::Point(),1,1,4,0,0,4,-40,-80);
    camera.setZoom(1).setLocation(0,0).setRotation(std::acos(-1.)/2);
    check(pdg::Point(),1,1,0,-1,1,0,0,0);
    camera.setScale(2,3);
    check(pdg::Point(),1,1,0,-3,2,0,0,0);
    camera.flipX();
    check(pdg::Point(),1,1,0,-3,-2,0,0,0);
    camera.flipY().setCenterOffset(Offset(2,3));
    check(pdg::Point(),1,1,0,3,-2,0,6,-6);
    camera.setCenterOffset(Offset(1,1));
    check(pdg::Point(),1,1,0,3,-2,0,2,-3);
    camera.setRotation(0).setScale(1,1).flipX().flipY().setCenterOffset(Offset()).setLocation(.2f,.3f);
    check(pdg::Point(),1,1,1,0,0,1,-.2,-.3);
    camera.setPixelSnapping();
    check(pdg::Point(),1,1,1,0,0,1,0,0);
    camera.setPixelSnapping(false);
    check(pdg::Point(),1,1,1,0,0,1,-.2,-.3);
    camera.setLocation(0,0);
    camera.getEffects().setLocation(3,4);
    check(pdg::Point(),1,1,1,0,0,1,-3,-4);
    camera.getEffects().setZoom(2);
    check(pdg::Point(10,10),1,1,2,0,0,2,4,2);
    camera.getEffects().setLocation(0,0).setZoom(1);
    check(pdg::Point(),1,1,1,0,0,1,0,0);
    camera.moveTo(10,20,1,linearTween).zoomTo(3,1,linearTween).animate(.5);
    check(pdg::Point(),1,1,2,0,0,2,-10,-20);
    camera.cancelSchedule().setLocation(0,0).setZoom(1);
    camera.setViewBounds(pdg::Rect(10,20,100,100));
    view=camera.getViewTransform(pdg::Point(),1,1,pdg::Rect(0,0,20,20)); near(view.tx,-10); near(view.ty,-20);
    camera.setViewBounds(pdg::Rect(20,30,100,100));
    view=camera.getViewTransform(pdg::Point(),1,1,pdg::Rect(0,0,20,20)); near(view.tx,-20); near(view.ty,-30);
    view=camera.getViewTransform(pdg::Point(),1,1,pdg::Rect(10,10,30,30)); near(view.tx,-10); near(view.ty,-20);
    camera.clearViewBounds();
    view=camera.getViewTransform(pdg::Point(),1,1,pdg::Rect(10,10,30,30)); near(view.tx,0); near(view.ty,0);
    camera.setScale(0,1);
    try {camera.getViewTransform(); throw std::runtime_error("Cached view hid invalid scale");}
    catch (const std::invalid_argument&) {}
    camera.setScale(1,1);
    check(pdg::Point(),1,1,1,0,0,1,0,0);
}
int main() {
    try {
        checkTransformCaching();
        Camera controls; Animated<> target; target.setLocation(100,200);
        controls.follow(target).animate(.1); near(controls.getLocation().x,100);
        controls.setDeadzone(pdg::Rect(-10,-10,10,10)); target.setLocation(105,200); controls.animate(.1); near(controls.getLocation().x,100);
        target.setLocation(120,200); controls.animate(.1); near(controls.getLocation().x,110);
        controls.setLocation(0,0); if (controls.isFollowing()) throw std::runtime_error("Manual pose did not take controller ownership");
        {Animated<> temporary; controls.follow(temporary);} controls.animate(.1); if (controls.isFollowing()) throw std::runtime_error("Following destroyed target");
        controls.clearViewBounds().setDeadzone(pdg::Rect()).setSmoothing(1).follow(target).animate(1); near(controls.getLocation().x,120*(1-std::exp(-1.)));
        controls.stopFollowing().setSmoothing(0).setLocation(0,0).setViewBounds(pdg::Rect(0,0,100,100));
        const pdg::Rect viewport(0,0,20,20); controls.setViewport(viewport); const auto bounded=controls.viewToWorld(pdg::Point(0,0)); near(bounded.x,0); near(bounded.y,0);
        controls.setViewport(viewport); const auto restored=controls.viewToWorld(controls.worldToView(pdg::Point(50,60))); near(restored.x,50); near(restored.y,60);
        controls.clearViewBounds().setLocation(100,200); controls.getEffects().playScript("shake"); controls.animate(.025);
        near(controls.getLocation().x,100); if (controls.worldToView(pdg::Point(100,200)).x==10) throw std::runtime_error("Effects stage missing from rendered view");
        controls.animate(.575); near(controls.getEffects().getLocation().x,0);
        controls.flash(1,.25); controls.animate(.125); if (controls.getFlashOpacity()<=0) throw std::runtime_error("Flash preset missing"); controls.animate(.125); near(controls.getFlashOpacity(),0);
        Camera camera;
        camera.hide().setOpacity(.25).moveTo(10,0,1,linearTween).animate(.5);
        if (!camera.isHidden()) throw std::runtime_error("Hidden Camera became visible");
        near(camera.getLocation().x,5);near(camera.getOpacity(),.25);
        camera.show().fadeTo(.75,1,linearTween).animate(.5);near(camera.getOpacity(),.5);
        camera.pauseSchedule().animate(1);near(camera.getOpacity(),.5);
        camera.resumeSchedule().animate(.5);near(camera.getOpacity(),.75);
        camera.cancelSchedule().setLocation(0,0).setOpacity(1);
        try {camera.setOpacity(-1);return 1;} catch(const std::invalid_argument&) {}
        try {camera.setOpacity(2);return 1;} catch(const std::invalid_argument&) {}
        {
            Camera source;
            auto* destination=new Camera(); destination->addRef();destination->hide();
            source.wait(1).cutTo(*destination);source.animate(.5);
            if(source.isHidden() || !destination->isHidden()) throw std::runtime_error("Cut executed early");
            source.pauseSchedule().animate(2);
            if(!destination->isHidden()) throw std::runtime_error("Paused cut executed");
            source.resumeSchedule().animate(.5);
            if(!source.isHidden() || destination->isHidden()) throw std::runtime_error("Cut visibility handoff mismatch");
            source.show();destination->hide();source.wait(1).cutTo(*destination).cancelSchedule().animate(2);
            if(source.isHidden() || !destination->isHidden()) throw std::runtime_error("Cancelled cut executed");
            try {source.matchCutTo(*destination,CameraMatchOptions());throw std::runtime_error("Headless match cut accepted");}
            catch(const std::logic_error&) {}
            try {source.matchFadeTo(*destination,CameraMatchOptions());throw std::runtime_error("Headless match fade accepted");}
            catch(const std::logic_error&) {}
            destination->release();
        }
        auto view = camera.getViewTransform(); near(view.transformPoint(pdg::Point(10,20)).x,10);
        camera.setLocation(10,20).setZoom(2);
        auto point = camera.getViewTransform(pdg::Point(100,50)).transformPoint(pdg::Point(15,25)); near(point.x,110); near(point.y,60);
        camera.setRotation(.7).setScale(2,3).flipX();
        view = camera.getViewTransform(pdg::Point(100,50));
        point = view.inverse().transformPoint(view.transformPoint(pdg::Point(17,34))); near(point.x,17); near(point.y,34);
        camera.setLocation(10.2f,20.3f).setPixelSnapping();
        view = camera.getViewTransform(); near(view.tx,std::round(view.tx)); near(camera.getLocation().x,10.2);
        Camera animated; animated.zoomTo(3,1,linearTween); animated.animate(.5); near(animated.getZoom(),2);
        animated.wait(.5).zoomTo(5,.5,linearTween); animated.animate(1); near(animated.getZoom(),5);
        ZoomHandler handler;
        animated.addHandler(&handler, eventType_ZoomComplete);
        animated.zoomTo(2,.5,linearTween).andThen().zoom(3,.5,linearTween);
        animated.animate(1); near(animated.getZoom(),6); near(handler.zoom,6);
        if (handler.count != 2 || !handler.valid) throw std::runtime_error("Camera completion mismatch");
        animated.zoomTo(7,1).cancelSchedule().animate(1);
        if (handler.count != 2) throw std::runtime_error("Cancelled zoom emitted completion");
        animated.removeHandler(&handler,eventType_ZoomComplete);
        auto* shared = new Camera(); shared->attach(); shared->attach(); shared->setMovement(4,0);
        shared->addHandler(&handler,eventType_ZoomComplete); shared->zoomTo(3,.5,linearTween);
        Camera::advanceAttached(.25); near(shared->getLocation().x,1); near(shared->getZoom(),2);
        if (handler.count != 2) throw std::runtime_error("Shared camera completed early");
        shared->detach(); Camera::advanceAttached(.25); near(shared->getLocation().x,2); near(shared->getZoom(),3);
        if (handler.count != 3 || !handler.valid) throw std::runtime_error("Shared completion count mismatch");
        shared->removeHandler(&handler,eventType_ZoomComplete); shared->detach();
        try { camera.setZoom(0); return 1; } catch(const std::invalid_argument&) {}
        camera.setScale(0,1); try { camera.getViewTransform(); return 1; } catch(const std::invalid_argument&) {}
        std::cout << "Camera transform, animation, and shared ownership checks passed\n";
    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
