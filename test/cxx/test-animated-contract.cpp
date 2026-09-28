#include "pdg/sys/animated.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <functional>

using namespace pdg;
namespace {
int checks=0;
void expect(bool ok,const char* message) {++checks;if(!ok)throw std::runtime_error(message);}
void near(double actual,double expected,const char* message,double tolerance=0.0001) {
    if (!std::isfinite(actual) || std::abs(actual-expected)>tolerance) {
        std::cerr<<message<<": "<<actual<<" expected "<<expected<<'\n';
        expect(false,message);
    }
    ++checks;
}
template<class F> void rejects(F fn,const char* message) {
    try {fn();} catch(const std::exception&) {++checks;return;}
    expect(false,message);
}
class Subject:public Animated<Subject> {public:using AnimatedBase::animate;Subject()=default;~Subject()=default;};

class HookOwner : public Animated<HookOwner> {
public:
    int moves = 0;
    using AnimatedBase::animate;
protected:
    void moveToImpl(const Point& target, double seconds, EasingFunc easing) override {
        ++moves;
        AnimatedBase::moveToImpl(target, seconds, easing);
    }
};
void fluentDispatch() {
    static_assert(std::is_same_v<decltype(std::declval<Subject&>().setMovement(1, 2).moveBy(2, 3, .5)), Subject&>);
    HookOwner owner;
    AnimatedBase& base = owner;
    expect(&owner.moveTo(1, 2, .5, linearTween) == &owner, "typed movement returns the concrete owner");
    base.moveTo(Point(4, 6), .5, linearTween);
    expect(owner.moves == 2, "typed and common-base calls invoke the virtual movement hook");
    owner.animate(.5);
    near(owner.getLocation().x, 4, "virtual movement shares the normal scheduler");
    Animated<> standalone;
    static_assert(std::is_same_v<decltype(standalone.wait(.5).moveTo(1, 2, .5)), Animated<>&>);
    expect(&standalone.setLocation(3, 4) == &standalone, "standalone Animated retains its own type");
}

struct Helper:public IAnimationHelper {
    double seconds=0;
    bool animate(AnimatedBase*,double dt) override {seconds+=dt;return true;}
    bool ownedByAnimated() override {return false;}
};
struct OwnedHelper : IAnimationHelper {
    int& destroyed;
    std::function<bool(AnimatedBase*)> callback;
    OwnedHelper(int& count, std::function<bool(AnimatedBase*)> function)
        : destroyed(count), callback(function) {}
    ~OwnedHelper() override { ++destroyed; }
    bool animate(AnimatedBase* owner, double) override { return callback(owner); }
};
void helperLifetimes() {
    Subject a, b;
    int destroyed = 0, calls = 0;
    auto* shared = new OwnedHelper(destroyed, [&](AnimatedBase*) { ++calls; return false; });
    a.addAnimationHelper(shared).addAnimationHelper(shared);
    b.addAnimationHelper(shared);
    a.animate(.1);
    expect(calls == 1 && destroyed == 0, "completed helper remains owned by its other registration");
    b.animate(.1);
    expect(calls == 2 && destroyed == 1, "final registration releases shared helper once");

    int secondCalls = 0;
    auto* second = new OwnedHelper(destroyed, [&](AnimatedBase*) { ++secondCalls; return true; });
    auto* first = new OwnedHelper(destroyed, [&](AnimatedBase* owner) {
        owner->clearAnimationHelpers();
        expect(destroyed == 1, "clearing does not delete the running helper or pending snapshot");
        return true;
    });
    a.addAnimationHelper(first).addAnimationHelper(second);
    a.animate(.1); a.animate(.1);
    expect(secondCalls == 0 && destroyed == 3, "cleared callbacks are skipped and released after iteration");

    OwnedHelper* restarted = nullptr;
    int restarts = 0;
    restarted = new OwnedHelper(destroyed, [&](AnimatedBase* owner) {
        ++restarts;
        if (restarts == 1) owner->removeAnimationHelper(restarted).addAnimationHelper(restarted);
        return false;
    });
    a.addAnimationHelper(restarted); a.animate(.1);
    expect(restarts == 1 && destroyed == 3, "old completion cannot remove the newly added registration");
    a.animate(.1);
    expect(restarts == 2 && destroyed == 4, "new registration first runs on the next tick");

    int nested = 0;
    a.addAnimationHelper(new OwnedHelper(destroyed, [&](AnimatedBase*) {
        ++nested; a.animate(.01); return false;
    }));
    a.animate(.1);
    expect(nested == 1 && destroyed == 5, "recursive animation does not re-enter its running helper");
    {
        Subject owner;
        owner.addAnimationHelper(new OwnedHelper(destroyed, [](AnimatedBase*) { return true; }));
    }
    expect(destroyed == 6, "owner destruction releases remaining registrations");
    rejects([&] { a.addAnimationHelper(nullptr); }, "null helper rejected");
}
void sequencing() {
    Subject a;
    expect(&a.andThen()==&a,"andThen returns the receiver even without a prior operation");
    a.wait(.25).moveTo(10,0,.5,linearTween).andThen().moveTo(20,0,.5,linearTween);
    a.animate(.5); near(a.getLocation().x,5,"sequence includes predecessor wait and preserves first move");
    a.animate(.25); near(a.getLocation().x,10,"predecessor reaches target before second move");
    a.animate(.25); near(a.getLocation().x,15,"successor samples predecessor endpoint");
    a.animate(.25); near(a.getLocation().x,20,"second move completes");
    expect(!a.hasScheduledAnimations(),"completed sequence leaves no pending tracks");

    a.setLocation(Point(0,0)).moveTo(10,0,.5,linearTween).andThen().moveBy(5,0,.5,linearTween);
    a.animate(.75); near(a.getLocation().x,12.5,"relative chained movement uses its start value");
    a.animate(.25); near(a.getLocation().x,15,"relative chained movement reaches its own target");
    a.setSize(10,20).resizeTo(20,40,.5,linearTween).andThen().grow(2,.5,linearTween);
    a.animate(.75); near(a.getWidth(),30,"chained factor uses preceding size");
    a.animate(.25); near(a.getHeight(),80,"chained growth scales both dimensions");
    a.setRotation(0).rotateBy(1,.5,linearTween).andThen().rotateBy(2,.5,linearTween);
    a.animate(.75); near(a.getRotation(),2,"relative rotation starts from predecessor endpoint");
    a.animate(.25); near(a.getRotation(),3,"relative rotation sequence completes");

    a.setLocation(Point(0,0)).moveTo(40,0,2,linearTween).changeScaleTo(2,2,.5,linearTween).andThen().moveTo(20,0,.5,linearTween);
    a.animate(.75); near(a.getLocation().x,15,"andThen uses latest operation and interrupts a competing older track only at its start");
    a.cancelSchedule().setLocation(Point(0,0));
    a.moveTo(10,0,1,linearTween).andThen().moveTo(20,0,1,linearTween).moveTo(30,0,1,linearTween);
    a.animate(.5); near(a.getLocation().x,15,"plain timed request interrupts an existing sequence");
    a.cancelSchedule().setLocation(Point(0,0));
    a.moveTo(10,0,.5,linearTween).andThen().moveTo(20,0,.5,linearTween).pauseSchedule();
    a.animate(2); near(a.getLocation().x,0,"pause freezes predecessor and chained delay");
    a.resumeSchedule().animate(1); near(a.getLocation().x,20,"resume advances entire chain in one tick");
    a.moveTo(30,0,.5,linearTween).andThen();
    rejects([&]{a.moveTo(40,0,0,linearTween);},"instant successor is rejected");
    a.moveTo(40,0,.5,linearTween);a.animate(1);near(a.getLocation().x,40,"rejection preserves pending sequencing");
    a.andThen();rejects([&]{a.moveTo(50,0);},"completed predecessor still requires timed successor");
    a.moveTo(50,0,.5,linearTween);a.animate(.5);near(a.getLocation().x,50,"completed predecessor adds no delay to timed successor");

    Subject whole, split;
    for (auto* p : {&whole,&split})
        p->changeMovementTo(10,0,.5,linearTween).andThen().changeMovementTo(0,0,.5,linearTween);
    whole.animate(1); for (int i=0;i<10;++i) split.animate(.1);
    near(whole.getLocation().x,5,"chained rates integrate both ramps");
    near(split.getLocation().x,whole.getLocation().x,"sequence integration is independent of timestep partitions");
    a.cancelSchedule().setLocation(Point(0,0)).moveTo(10,0,.5,linearTween).andThen().changeMovementTo(20,0,.5,linearTween);
    a.animate(1.25);near(a.getLocation().x,20,"direct movement hands over to programmed rate at boundary");a.stopMovement();
    a.moveTo(30,0,1,linearTween);a.animate(.25);a.andThen().changeScaleTo(3,3,.5,linearTween);
    a.animate(.75);near(a.getScale().x,2,"andThen uses predecessor remaining time after stepping");
    a.animate(.5);near(a.getScale().x,3,"successor completes after remaining predecessor time");
    a.moveTo(40,0,1).andThen().wait(0);
    rejects([&]{a.changeScaleTo(4,4,0);},"wait zero still requires a duration");
    a.changeScaleTo(4,4,.5,linearTween);a.animate(.5);
    near(a.getScale().x,4,"explicit wait replaces pending sequence timing");
    a.cancelSchedule();expect(!a.hasScheduledAnimations(),"cancel removes every queued step");
}

void chaining() {
    Subject a;
    AnimatedBase& result = a.moveTo(1,2,.1).moveBy(1,2,.1).moveBy(Offset(1,2),.1)
        .moveTo(Point(1,2),.1).changeScaleTo(2,2,.1).resizeTo(3,4,.1).resizeBy(1,2,.1)
        .grow(2,.1).stretch(2,3,.1).rotateTo(1,.1).rotateBy(1,.1)
        .changeCenterOffsetTo(1,2,.1).changeCenterOffsetTo(Offset(1,2),.1)
        .changeCenterOffsetBy(1,2,.1).changeCenterOffsetBy(Offset(1,2),.1)
        .wait(.1).cancelSchedule().clearAnimationHelpers();
    expect(&result == &a, "all timed mutations return the original object");
}
double callbackElapsed=0,callbackDuration=0;
float capture(double elapsed,float start,float change,double duration) {
    callbackElapsed=elapsed;callbackDuration=duration;
    return start+change*elapsed/duration;
}
void timing() {
    Subject a;
    a.moveTo(Point(10,20),.00025,linearTween);
    a.animate(.000125);near(a.getLocation().x,5,"sub-millisecond tween midpoint");
    a.animate(.000125);near(a.getLocation().y,20,"sub-millisecond completion");
    a.moveTo(Point(0,0));a.wait(.125).moveTo(Point(8,0),.25,linearTween);
    a.animate(.1875);near(a.getLocation().x,2,"delay crossing consumes only active interval");
    a.animate(.1875);near(a.getLocation().x,8,"delayed tween completion");
    a.wait(.125);
    rejects([&]{a.moveTo(Point(20,0),0,linearTween);},"instant delayed change rejected");
    a.moveTo(Point(20,0),.1,linearTween);
    a.animate(.125);near(a.getLocation().x,8,"rejected immediate operation leaves wait intact");
    a.animate(.1);near(a.getLocation().x,20,"valid timed replacement executes");
    Helper helper;a.addAnimationHelper(&helper);a.animate(.03125);
    near(helper.seconds,.03125,"helper receives seconds");a.removeAnimationHelper(&helper);
    a.moveTo(Point(30,0),.5,capture);a.animate(.125);
    near(callbackElapsed,.125,"custom easing receives fractional elapsed seconds");
    near(callbackDuration,.5,"custom easing receives fractional duration seconds");
    for(int i=0;i<NUM_BUILTIN_EASINGS;++i) {
        near(gEasingFunctions[i](0,2,5,.25),2,"easing initial value");
        near(gEasingFunctions[i](.25,2,5,.25),7,"easing final value");
        near(gEasingFunctions[i](0,2,5,0),7,"zero-duration easing is target");
    }
    near(easeInBounce(.125,0,1,.25),.234375,"bounce preserves fractional time");
    rejects([&]{a.animate(-.1);},"negative step rejected");
    rejects([&]{a.wait(std::numeric_limits<double>::infinity());},"infinite wait rejected");
    rejects([&]{a.moveTo(Point(1,2),-.1);},"negative tween rejected");
}
void rates() {
    Subject a;
    a.setMovement(Vector(20,-8));a.animate(.25);
    near(a.getLocation().x,5,"movement x rate per second");
    near(a.getLocation().y,-2,"movement y rate per second");
    a.changeMovementTo(0,0,.5,linearTween);a.animate(.25);
    near(a.getMovement().x,10,"current eased movement rate");
    near(a.getLocation().x,8.75,"integrated rate midpoint");
    a.animate(.5);near(a.getLocation().x,10,"rate completion with constant tail");
    Subject coarse,fine;
    coarse.changeMovementTo(40,0,.75,easeInOutQuad);fine.changeMovementTo(40,0,.75,easeInOutQuad);
    coarse.animate(1);for(int i=0;i<100;++i)fine.animate(.01);
    near(coarse.getLocation().x,25,"eased rate interval and tail");
    near(fine.getLocation().x,coarse.getLocation().x,"rate timestep partition independence");
    coarse.changeMovementTo(0,0,.5);coarse.animate(.125);
    const double rate=coarse.getMovement().x;
    coarse.changeMovementTo(60,0,.25);near(coarse.getMovement().x,rate,"rate interruption retains current value");
    coarse.animate(.25);near(coarse.getMovement().x,60,"interrupted rate reaches target");
    a.setMovement(100,0);a.moveTo(Point(0,0),.5,linearTween);a.animate(.25);
    near(a.getLocation().x,5,"position tween replaces movement");near(a.getMovement().x,0,"position stops programmed rate");
    a.setMovement(4,0);a.animate(.25);near(a.getLocation().x,6,"rate replaces position tween");
    a.changeSpinTo(4,.5);a.animate(.25);near(a.getSpin(),2,"current eased spin");
    near(a.getRotation(),.25,"spin integrates its rate");
    a.animate(.5);near(a.getRotation(),2,"spin completion integrates constant tail");
    a.changeSpinTo(-4,.5);a.animate(.5);near(a.getRotation(),2,"reversing spin integrates through zero");
    a.setSize(10,20).setStretching(8,-4);a.animate(.25);
    near(a.getWidth(),12,"stretch width per second");near(a.getHeight(),19,"stretch height per second");
    a.stopStretching();a.animate(1);near(a.getWidth(),12,"stop stretching");
}
void scaleAndGrowth() {
    Subject a;
    a.setSize(10,20).setScale(.5f,2);
    near(a.getWidth(),10,"scale preserves logical width");
    near(a.getRotatedBounds().width(),5,"bounds include horizontal scale");
    a.changeScaleTo(-1,0,.5,linearTween);a.animate(.25);
    near(a.getScale().x,-.25,"signed fractional scale sample");
    a.setScale(3);a.animate(1);near(a.getScale().y,3,"immediate scale cancels both channels");
    a.changeStretchingTo(8,-4,.5,linearTween);a.animate(.25);
    near(a.getStretching().x,4,"eased growth rate");near(a.getWidth(),10.5,"integrated growth rate");
    a.animate(.5);near(a.getWidth(),14,"growth integration includes constant tail");
    a.changeGrowingTo(100,1);a.setWidth(20);a.animate(.25);
    near(a.getWidth(),24.875,"width setter preserves separately configured growth rate");
    a.resizeTo(30,40,.5,linearTween);a.animate(.5);
    near(a.getHeight(),40,"resize cancels growth transitions");near(a.getStretching().y,0,"resize clears rates");
    a.changeGrowingTo(100,1);a.stopGrowing();a.animate(1);near(a.getWidth(),30,"stop clears rate tween");
    Subject coarse,fine;
    coarse.changeStretchingTo(40,-8,.75,easeInOutQuad);fine.changeStretchingTo(40,-8,.75,easeInOutQuad);
    coarse.animate(1);for(int i=0;i<100;++i)fine.animate(.01);
    near(coarse.getWidth(),25,"growth area");near(fine.getWidth(),coarse.getWidth(),"growth partition independence");
    a.changeScaleTo(2,2,1);rejects([&]{a.setScale(NAN);},"invalid scale rejected");
    expect(a.hasScheduledAnimations(),"invalid scale preserves tween");
    rejects([&]{a.changeGrowingTo(1,-.1);},"negative growth duration rejected");
}
void tweenControls() {
    Subject a;Helper helper;a.addAnimationHelper(&helper);
    expect(!a.hasScheduledAnimations() && !a.isSchedulePaused(),"initial tween state");
    a.wait(.5).changeScaleTo(3,5,1,linearTween);a.animate(.25);a.pauseSchedule();a.animate(2);
    near(a.getScale().x,1,"pause freezes delay");near(helper.seconds,2.25,"helpers continue while paused");
    a.resumeSchedule();a.animate(.75);near(a.getScale().x,2,"resume consumes remaining delay");
    a.pauseSchedule();a.animate(2);near(a.getScale().x,2,"pause freezes active tween");
    a.cancelSchedule();expect(!a.hasScheduledAnimations() && a.isSchedulePaused(),"cancel retains paused state");
    a.resumeSchedule();a.animate(2);near(a.getScale().x,2,"cancel holds sampled scale");
    a.changeMovementTo(8,0,1,linearTween);a.animate(.5);a.pauseSchedule();
    const float x=a.getLocation().x;a.animate(1);
    near(a.getMovement().x,4,"paused rate holds current rate");near(a.getLocation().x,x+4,"held movement continues");
    a.resumeSchedule();a.animate(.5);near(a.getMovement().x,8,"rate transition resumes");
    a.wait(10);a.cancelSchedule();a.changeScaleTo(4,4,0);near(a.getScale().x,4,"cancel clears pending wait");
    a.removeAnimationHelper(&helper);
}
void rotations() {
    const float pi=3.14159265358979323846f;
    Subject a;a.setRotation(350*pi/180);
    a.rotateTo(10*pi/180,.5,linearTween,rotationDirection_Shortest);a.animate(.25);
    near(a.getRotation(),2*pi,"shortest path crosses wrap unwrapped");
    a.animate(.25);near(a.getRotation(),370*pi/180,"shortest path endpoint remains unwrapped");
    a.setRotation(0);a.rotateTo(pi/2,.5,linearTween,rotationDirection_CounterClockwise);a.animate(.25);
    near(a.getRotation(),-3*pi/4,"counterclockwise absolute route");
    a.setRotation(0);a.rotateBy(4*pi,.5,linearTween);a.animate(.5);
    near(a.getRotation(),4*pi,"relative two full turns retained");
    a.rotateBy(2*pi,.5,linearTween,rotationDirection_CounterClockwise);a.animate(.5);
    near(a.getRotation(),2*pi,"explicit relative direction selects travel sign");
    a.setRotation(0);a.wait(.25).rotateBy(pi,.5,linearTween);a.setRotation(.5);
    // Immediate setter cancels a pending rotation by design.
    a.animate(1);near(a.getRotation(),.5,"immediate rotation cancels pending tween");
    a.rotateTo(2*pi,.5,linearTween);a.animate(.25);
    const double now=a.getRotation();a.rotateTo(0,.5,linearTween,rotationDirection_Clockwise);a.animate(.25);
    near(a.getRotation(),(now+2*pi)/2,"rotation interruption starts from current unwrapped angle");
    a.setRotation(0);a.rotateTo(pi,.5,linearTween,rotationDirection_Shortest);a.animate(.25);
    near(a.getRotation(),pi/2,"positive half-turn tie");
    a.setRotation(0);a.rotateTo(-pi,.5,linearTween,rotationDirection_Shortest);a.animate(.25);
    near(a.getRotation(),pi/2,"negative half-turn tie chooses positive route");
    rejects([&]{a.rotateTo(0,.5,linearTween,42);},"invalid rotation direction rejected");
}
void normalizedAPI() {
    Subject a;
    a.setLocation(3,4).setSize(Offset(10,20)).resizeBy(2,3);
    const AnimatedBase& sample=a;
    near(sample.getLocation().x,3,"numeric location setter");
    near(sample.getSize().x,12,"size setter and immediate relative resize");
    near(sample.getSize().y,23,"size Offset preserves both dimensions");
    sample.getBoundingBox();sample.getRotatedBounds();sample.getRotation();
    sample.getCenterOffset();sample.getSpin();sample.isFlippedX();sample.isFlippedY();

    a.setMovement(2,0).changeMovementTo(6,0,.5,linearTween).andThen().changeMovementBy(Vector(4,0),.5,linearTween);
    a.setSpin(2).changeSpinTo(4,.5,linearTween).andThen().changeSpinBy(2,.5,linearTween);
    a.setGrowing(4).changeGrowingTo(8,.5,linearTween).andThen().changeGrowingBy(4,.5,linearTween);
    a.setScale(2,3).changeScaleTo(4,5,.5,linearTween).andThen().changeScaleBy(1,-2,.5,linearTween);
    a.animate(1);
    near(a.getMovement().x,10,"relative movement resolves predecessor rate");
    near(a.getLocation().x,9,"relative rate integration");
    near(a.getSpin(),6,"relative spin resolves predecessor rate");
    near(a.getRotation(),4,"relative spin integration");
    near(a.getStretching().x,12,"relative growth resolves predecessor rate");
    near(a.getWidth(),20,"growth changes logical size");
    near(a.getScale().x,5,"relative scale adds rather than multiplies");
    near(a.getScale().y,3,"relative scale adds signed delta");
    a.setSize(Offset(40,50));a.animate(.25);
    near(a.getWidth(),43,"immediate size preserves constant growth");
    a.stopMovement().stopSpinning().stopGrowing();
    a.resizeTo(100,100,1).stopStretching();a.animate(1);
    near(a.getWidth(),43,"growth stop cancels scheduled resizing too");
    a.wait(.25);
    rejects([&]{a.setGrowing(8);},"constant growth cannot be scheduled");
    rejects([&]{a.setStretching(8,9);},"constant stretch cannot be scheduled");
    a.changeStretchingBy(4,8,.5,linearTween);a.animate(.75);
    near(a.getStretching().x,4,"failed immediate call preserves pending sequence");
    near(a.getStretching().y,8,"relative stretch has independent rates");
}

}
int main() {
    try {fluentDispatch();normalizedAPI();helperLifetimes();chaining();sequencing();timing();rates();rotations();scaleAndGrowth();tweenControls();std::cout<<"Animated contract passed "<<checks<<" assertions\n";}
    catch(const std::exception& error) {std::cerr<<error.what()<<'\n';return EXIT_FAILURE;}
    return EXIT_SUCCESS;
}
