#include "pdg/sys/animated.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>

using namespace pdg;
namespace {
int checks=0;
void expect(bool condition,const char* message) { ++checks; if (!condition) throw std::runtime_error(message); }
void near(double actual,double expected,const char* message) {
    ++checks; if (!std::isfinite(actual) || std::abs(actual-expected)>.0001) {
        std::cerr<<message<<": "<<actual<<" expected "<<expected<<'\n'; throw std::runtime_error(message);
    }
}
template<class F> void rejects(F action,const char* message) {
    ++checks; try {action();} catch(const std::exception&) {return;} throw std::runtime_error(message);
}
void deleteDefinitions() {
    auto& definition=AnimatedBase::defineScript("scripts-delete");
    definition.moveBy(10,0,1,linearTween).endScript();
    // A wrapper's retained shell must be safe after deletion, with its graph freed.
    definition.addRef();
    Animated<> target; target.playScript("scripts-delete"); target.animate(.25);
    expect(Animated<>::deleteScript("scripts-delete"),"delete removes an existing definition");
    expect(!AnimatedBase::hasScriptDefinition("scripts-delete"),"deleted definition is absent");
    expect(!AnimatedBase::deleteScript("scripts-delete"),"missing delete returns false");
    rejects([]{AnimatedBase::deleteScript("");},"empty deletion name rejects");
    rejects([&]{target.playScript("scripts-delete");},"new playback of deleted name rejects");
    rejects([&]{definition.moveBy(1,0,1);},"retained deleted recorder rejects mutation");
    rejects([&]{definition.endScript();},"deleted recorder rejects sealing");
    AnimatedBase::defineScript("scripts-delete").moveBy(20,0,1,linearTween).endScript();
    target.animate(.75); near(target.getLocation().x,10,"running instance keeps original definition");
    Animated<> replacement; replacement.playScript("scripts-delete").animate(1);
    near(replacement.getLocation().x,20,"deleted name can be redefined independently");
    definition.release(); AnimatedBase::deleteScript("scripts-delete");
    auto resource=std::make_shared<int>(1); std::weak_ptr<int> lifetime=resource;
    auto& captured=AnimatedBase::defineScript("scripts-delete-capture"); captured.addRef();
    captured.moveBy(1,0,1).onFinished([resource](const AnimationEvent&){}).endScript();
    resource.reset(); expect(!lifetime.expired(),"definition owns captured handler resources");
    AnimatedBase::deleteScript("scripts-delete-capture");
    expect(lifetime.expired(),"deletion releases resources despite a retained recorder wrapper");
    captured.release();
}
void definitions() {
    auto& definition=AnimatedBase::defineScript("scripts-move");
    static_assert(std::is_same_v<decltype(definition.moveBy(1,0,.5).yoyo()),AnimationScript&>);
    definition.moveBy(10,20,1,linearTween);
    rejects([&]{definition.getLocation();},"recorders reject live target state getters");
    definition.endScript();
    rejects([&]{definition.moveBy(1,0,1);},"sealed definitions reject mutation");
    rejects([]{AnimatedBase::defineScript("scripts-move");},"duplicate names reject");
    Animated<> first,second;
    first.setLocation(100,200).playScript("scripts-move"); second.setLocation(-10,-20).playScript("scripts-move");
    first.animate(.5); second.animate(.25);
    near(first.getLocation().x,105,"first target baseline"); near(second.getLocation().x,-7.5,"independent target cursor");
    first.animate(.5); near(first.getLocation().y,220,"first target final offset");
    second.animate(.75); near(second.getLocation().y,0,"second target final offset");
    rejects([&]{first.playScript("scripts-missing");},"unknown invocation rejects");
    near(first.getLocation().x,110,"rejected invocation preserves target");
    auto& draft=AnimatedBase::defineScript("scripts-draft"); draft.moveBy(2,0,1,linearTween);
    first.playScript("scripts-draft"); draft.moveBy(0,3,1,linearTween); first.animate(1);
    near(first.getLocation().y,220,"draft publication captures immutable copy");
    AnimatedBase::defineScript("scripts-recursive").playScript("scripts-recursive").endScript();
    rejects([&]{first.playScript("scripts-recursive");},"recursive invocation rejected before playback");
}
void composition() {
    AnimatedBase::defineScript("scripts-sequence").batch().wait(.1).wait(.1).moveBy(10,0,.2,linearTween)
        .andThen().wait(.1).moveBy(20,0,.2,linearTween).endBatch().endScript();
    Animated<> one,partitioned;
    one.playScript("scripts-sequence"); partitioned.playScript("scripts-sequence"); one.animate(.7);
    for (int i=0;i<7;++i) partitioned.animate(.1);
    near(one.getLocation().x,30,"large update crosses dependencies and delays");
    near(partitioned.getLocation().x,30,"partitioned update agrees");
    AnimatedBase::defineScript("scripts-shake").moveBy(10,0,.1,linearTween).yoyo().repeat(2).diminish(0,.6).endScript();
    Animated<> shake; shake.setLocation(100,200).playScript("scripts-shake");
    shake.animate(.1); near(shake.getLocation().x,100+10*5./6,"gain is relative to baseline");
    shake.animate(.2); near(shake.getLocation().x,105,"repetition gain continues across cycles");
    shake.animate(.3); near(shake.getLocation().x,100,"shake returns to baseline without drift");
    Animated<> live; live.batch().moveBy(5,0,.2,linearTween).yoyo().endBatch().repeat(1); live.animate(.8);
    near(live.getLocation().x,0,"live groups publish at update boundary");
    Animated<> playback; playback.playScript("scripts-move").yoyo(); playback.animate(2);
    near(playback.getLocation().x,0,"modifiers compose named invocation before activation");
}
void branches() {
    int calls=0;
    AnimatedBase::defineScript("scripts-branch").when([&](const AnimationEvaluationContext& context) {
        ++calls; return context.target.getLocation().x<50;
    }).moveBy(10,0,.2,linearTween).otherwise().moveBy(-10,0,.2,linearTween).endOtherwise().yoyo().endScript();
    expect(calls==0,"conditions do not run while recording");
    Animated<> first,second; first.playScript("scripts-branch"); second.setLocation(100,0).playScript("scripts-branch");
    first.animate(.2); second.animate(.2);
    near(first.getLocation().x,10,"true branch"); near(second.getLocation().x,90,"false branch");
    first.animate(.2); second.animate(.2);
    near(first.getLocation().x,0,"reverse selected true path"); near(second.getLocation().x,100,"reverse selected false path");
    expect(calls==2,"reverse does not reevaluate condition");
    bool finish=false;
    AnimatedBase::defineScript("scripts-until").moveBy(100,0,10,linearTween)
        .until([&](const AnimationEvaluationContext&){return finish;}).andThen().moveBy(5,0,.1,linearTween).endScript();
    Animated<> target; target.playScript("scripts-until"); target.animate(1); near(target.getLocation().x,10,"until progresses normally");
    finish=true; target.animate(.1); near(target.getLocation().x,15,"until retains sample and releases dependent in same update");
    AnimatedBase::defineScript("scripts-throws").when([](const AnimationEvaluationContext&)->bool {throw std::runtime_error("evaluator error");})
        .moveBy(10,0,1).endWhen().endScript();
    Animated<> failure; failure.playScript("scripts-throws"); rejects([&]{failure.animate(.1);},"exceptions fail playback");
    failure.animate(1); near(failure.getLocation().x,0,"failed playback remains stopped");
}
void controlsAndClocks() {
    Animated<> target; target.setLocation(100,0).playScript("scripts-move"); target.animate(.2); target.pauseIt(); target.animate(.5);
    near(target.getLocation().x,102,"pause holds script cursor"); target.resumeIt().animate(.3);
    near(target.getLocation().x,105,"resume continues cursor"); target.stopIt(); target.animate(1);
    near(target.getLocation().x,105,"stop holds current sample"); target.restartIt();
    near(target.getLocation().x,100,"restart restores captured baseline"); target.animate(1);
    near(target.getLocation().x,110,"restart replays resolved operation");
    Animated<> amplified; amplified.setLocation(100,0).moveBy(10,0,1,linearTween).increase(3,1);
    amplified.animate(.5); near(amplified.getLocation().x,110,"increase ramps displacement around baseline");
    amplified.animate(.5); near(amplified.getLocation().x,130,"increase reaches final multiplier");
    Animated<> immediate; immediate.moveBy(10,0,1,linearTween).increase(2,0).animate(1);
    near(immediate.getLocation().x,20,"instant increase applies multiplier");
    rejects([&]{immediate.moveBy(1,0,1).increase(.5,1);},"increase rejects decreasing factors");
    AnimatedBase::defineScript("scripts-rate").moveBy(100,0,3,linearTween).speedUp(2,1).endScript();
    Animated<> whole,split; whole.playScript("scripts-rate"); split.playScript("scripts-rate");
    whole.animate(1); for(int i=0;i<10;++i) split.animate(.1);
    near(whole.getLocation().x,50,"clock integrates rate envelope"); near(split.getLocation().x,50,"clock is independent of update partition");
    whole.animate(.75); near(whole.getLocation().x,100,"accelerated completion");
}
void liveControlsAndCopies() {
    Animated<> target;
    target.setLocation(100,0).moveBy(10,0,.2,linearTween).yoyo().repeat(1)
        .andThen().wait(.1).playScript("scripts-move");
    target.animate(.8); near(target.getLocation().x,100,"ordinary fluent operation retains its replay path");
    target.animate(.1); near(target.getLocation().x,100,"live dependent waits for the entire repeated block");
    target.animate(1); near(target.getLocation().x,110,"named invocation follows a live block completion");
    Animated<> paused;
    paused.batch().moveBy(20,0,1,linearTween).endBatch().pauseIt(); paused.animate(.5);
    near(paused.getLocation().x,0,"pending selected group can be paused before publication");
    paused.resumeIt().animate(.5); near(paused.getLocation().x,10,"published selected group resumes");
    paused.animate(.5); paused.restartIt().animate(.5); near(paused.getLocation().x,10,"completed selected child can restart independently");
    Animated<> source,copy;
    source.playScript("scripts-shake").animate(.1); copy.copyAnimationStateFrom(source);
    source.animate(.1); near(copy.getLocation().x,10*5./6,"clone cursor is independent");
    copy.animate(.5); near(copy.getLocation().x,0,"clone keeps its own baselines and modifier clocks");
    Animated<> rate;
    rate.changeMovementTo(20,0,1,linearTween);
    rejects([&]{rate.yoyo();},"unsupported reversal rejects without canceling existing rate animation");
    rate.animate(1); near(rate.getLocation().x,10,"failed modifier preserves programmed movement");
    auto& flip=AnimatedBase::defineScript("scripts-flip"); flip.flipX().andThen().moveBy(2,0,.1,linearTween).endScript();
    Animated<> flipped; flipped.setCenterOffset(Offset(3,0)).playScript("scripts-flip").animate(.1);
    expect(flipped.isFlippedX(),"script records discrete flip at activation"); near(flipped.getCenterOffset().x,-3,"flip updates pivot");
    rejects([]{AnimatedBase::defineScript("scripts-flip-reverse").flipX().yoyo();},"irreversible discrete command is rejected explicitly");
}
void sharedClockAndOwnership() {
    AnimatedBase::defineScript("scripts-delayed-motion").wait(.5).moveBy(10,0,.5,linearTween).endScript();
    Animated<> delayed; delayed.setMovement(10,0).playScript("scripts-delayed-motion").animate(1);
    near(delayed.getLocation().x,15,"delayed script captures the activation-time pose");
    near(delayed.getMovement().x,0,"script pose channels cancel competing programmed rates");
    AnimatedBase::defineScript("scripts-programmed-rate").changeMovementTo(20,0,1,linearTween).endScript();
    Animated<> whole,split; whole.setMovement(10,0).playScript("scripts-programmed-rate"); split.setMovement(10,0).playScript("scripts-programmed-rate");
    whole.animate(1); for(int i=0;i<10;++i) split.animate(.1);
    near(whole.getLocation().x,15,"script rate uses Animated's exact integration");
    near(split.getLocation().x,15,"script rate integration is independent of frame partition");
    whole.animate(1); near(whole.getLocation().x,35,"completed programmed rate continues normally");
    AnimatedBase::defineScript("scripts-rate-dependency").changeMovementBy(10,0,.5,linearTween)
        .andThen().changeMovementBy(10,0,.5,linearTween).endScript();
    Animated<> rates; rates.setMovement(10,0).playScript("scripts-rate-dependency").animate(1);
    near(rates.getLocation().x,20,"sequential rate profiles integrate within the shared clock");
    near(rates.getMovement().x,30,"relative rate successor samples its predecessor");
    AnimatedBase::defineScript("scripts-clock-dependency").moveBy(100,0,3,linearTween).speedUp(2,1)
        .andThen().moveBy(10,0,.25,linearTween).endScript();
    Animated<> accelerated; accelerated.playScript("scripts-clock-dependency").animate(2);
    near(accelerated.getLocation().x,110,"clock completion releases its successor within a large update");
    Animated<> edited; edited.playScript("scripts-move").animate(.2); edited.setLocation(50,60).animate(.5);
    near(edited.getLocation().x,50,"immediate edits cancel owned script position channels");
    near(edited.getLocation().y,60,"canceling script position preserves the edited sample");
    Animated<> reverse; reverse.playScript("scripts-move").yoyo().animate(1.2); reverse.setLocation(50,60).animate(.5);
    near(reverse.getLocation().x,50,"reverse playback respects new channel ownership");
    int polls=0;
    AnimatedBase::defineScript("scripts-poll-count").moveBy(1,0,1,linearTween)
        .until([&](const AnimationEvaluationContext&){++polls;return false;}).endScript();
    Animated<> polled; polled.playScript("scripts-poll-count").animate(.1);
    expect(polls==1,"activation bookkeeping does not add an extra until evaluation");
    polled.animate(.1); expect(polls==2,"until checks again at the next real tick");
}
void lateConstruction() {
    Animated<> wrapped; wrapped.playScript("scripts-move").yoyo().repeat(1).diminish(0,4); wrapped.animate(4);
    near(wrapped.getLocation().x,0,"live published wrapper ownership survives repeated acquisitions");
    Animated<> replay; replay.batch().moveBy(10,0,.5,linearTween).andThen().moveBy(20,0,.5,linearTween).endBatch();
    replay.animate(.25); replay.stopIt().restartIt(); replay.animate(1); near(replay.getLocation().x,30,"restart preserves the selected block's completion dependency");

    Animated<> late; late.playScript("scripts-move").animate(.25);
    late.andThen().wait(.2); late.animate(.25);
    late.moveBy(50,0,.5,linearTween); late.animate(1.2);
    near(late.getLocation().x,60,"late dependency joins actual completion and delay");
    Animated<> pending; pending.batch().moveBy(10,0,.5,linearTween).endBatch().andThen();
    pending.animate(.25); pending.moveBy(20,0,.5,linearTween); pending.animate(.75);
    near(pending.getLocation().x,30,"live pending placement survives update publication");
    Animated<> selection; selection.playScript("scripts-move").animate(.1);
    selection.moveBy(50,0,.5,linearTween).yoyo(); selection.animate(1);
    near(selection.getLocation().x,1,"new ordinary operation selects its own operand");
    Animated<> cancelled; cancelled.playScript("scripts-sequence").animate(.3);
    cancelled.setLocation(500,500); cancelled.animate(2);
    near(cancelled.getLocation().x,500,"cancellation does not release success-dependent successors");
}
void seriesAndMarks() {
    bool blocked=false;
    Animated<> axes;
    axes.moveBy(0,100,4,linearTween).moveBy(100,0,2,linearTween)
        .andAlso().rotateBy(3.14159265f,2,linearTween)
        .until([&](const AnimationEvaluationContext&){return blocked;});
    axes.animate(.5);
    near(axes.getLocation().x,25,"horizontal chain progresses alongside ordinary vertical movement");
    near(axes.getLocation().y,12.5,"horizontal movement leaves vertical track intact");
    blocked=true; axes.animate(.5);
    near(axes.getLocation().x,25,"blocked chain stops horizontal movement");
    near(axes.getRotation(),3.14159265/4,"blocked chain stops rotation");
    near(axes.getLocation().y,25,"vertical track continues after chain stops");
    axes.animate(3); near(axes.getLocation().y,100,"vertical track completes independently");
    Animated<> recordedAxes;
    blocked=false;
    recordedAxes.batch().moveBy(0,100,4,linearTween).moveBy(100,0,2,linearTween)
        .andAlso().rotateBy(1,2,linearTween)
        .until([&](const AnimationEvaluationContext&){return blocked;}).endBatch();
    recordedAxes.animate(.5); blocked=true; recordedAxes.animate(.5);
    near(recordedAxes.getLocation().x,25,"recorded horizontal chain stops");
    near(recordedAxes.getLocation().y,25,"recorded vertical track remains outside chain");
    Animated<> immediate;
    immediate.moveBy(0,100).moveBy(100,0,2,linearTween).andAlso().rotateBy(1,2,linearTween)
        .until([](const AnimationEvaluationContext&){return true;});
    immediate.animate(.5); near(immediate.getLocation().y,100,"durationless moveBy is an immediate offset");
    Animated<> rates;
    rates.setMovement(0,10).moveBy(100,0,2,linearTween).animate(1);
    near(rates.getLocation().y,10,"horizontal moveBy preserves vertical programmed rate");
    Animated<> target;
    target.series().moveBy(10,0,.2,linearTween).rotateBy(1,.3,linearTween).endSeries();
    target.animate(.2); near(target.getLocation().x,10,"series movement completes first");
    near(target.getRotation(),0,"series rotation starts after movement");
    target.animate(.15); near(target.getRotation(),.5,"series successor progresses");
    bool done=false;
    Animated<> parallel;
    parallel.series().moveBy(10,0,1,linearTween).andAlso().rotateBy(1,2,linearTween)
        .until([&](const AnimationEvaluationContext&){return done;}).moveBy(5,0,.2,linearTween).endSeries();
    parallel.animate(.5); near(parallel.getLocation().x,5,"parallel series movement");
    near(parallel.getRotation(),.25,"parallel series rotation");
    done=true; parallel.animate(.2); near(parallel.getLocation().x,10,"until releases series successor");
    near(parallel.getRotation(),.25,"until stops whole andAlso chain");
    AnimatedBase::defineScript("scripts-marks").series().moveBy(10,0,.2,linearTween).mark("home")
        .moveBy(20,0,.4,linearTween).endSeries().endScript();
    Animated<> marks; marks.playScript("scripts-marks"); marks.animate(.4);
    near(marks.getLocation().x,20,"mark followed by movement");
    marks.jumpToMark("home"); near(marks.getLocation().x,10,"jump restores visited mark state");
    marks.animate(.2); near(marks.getLocation().x,20,"jump resumes operation following mark");
    marks.jumpToMark("home",false); marks.animate(.4);
    near(marks.getLocation().x,40,"jump without restore recaptures relative movement");
    Animated<> forward; forward.playScript("scripts-marks").jumpToMark("home"); forward.animate(.4);
    near(forward.getLocation().x,20,"unvisited mark skips earlier movement without state restore");
    AnimatedBase::defineScript("scripts-jump-loop").series().mark("again").moveBy(10,0,.2,linearTween)
        .jumpToMark("again",false).endSeries().endScript();
    Animated<> loop; loop.playScript("scripts-jump-loop"); loop.animate(.5);
    near(loop.getLocation().x,25,"recorded jumps carry unused update time and accumulate without restore");
    Animated<> delayed; delayed.series().moveBy(10,0,.2,linearTween).wait(.1).moveBy(5,0,.2,linearTween).endSeries();
    delayed.animate(.25); near(delayed.getLocation().x,10,"series wait preserves implicit completion dependency");
    delayed.animate(.25); near(delayed.getLocation().x,15,"series delay releases following operation");
    Animated<> pending; pending.moveBy(10,0,.2,linearTween).andAlso(); pending.animate(.1);
    near(pending.getLocation().x,0,"live andAlso does not publish before its successor arrives");
    pending.rotateBy(1,.2,linearTween).until([](const AnimationEvaluationContext&){return false;}); pending.animate(.2);
    near(pending.getLocation().x,10,"live andAlso completes construction after an update");
    Animated<> invalid; rejects([&]{invalid.series().endBatch();},"batch cannot close series");
}
void lifecycleHandlers() {
    std::vector<std::string> events;
    AnimatedBase::defineScript("scripts-events").series().mark("home")
        .moveBy(10,0,.1,linearTween).yoyo().repeat(2).endSeries()
        .onMark([&](const AnimationEvent& event) { expect(event.markName=="home","mark handler identifies label"); events.push_back(event.type); })
        .onYoyo([&](const AnimationEvent& event) { expect(event.reverse,"yoyo event reports reverse leg"); events.push_back(event.type); })
        .onRepeat([&](const AnimationEvent& event) { expect(event.iteration>=1 && event.iteration<=2,"repeat event counts additional cycles"); events.push_back(event.type); }).endScript();
    Animated<> target;
    int finished=0,named=0;
    target.playScript("scripts-events").onFinished([&](const AnimationEvent& event) {
        ++finished; expect(event.scriptName=="scripts-events","completion identifies script");
        near(event.target.getLocation().x,0,"handler sees published animation state");
        event.target.moveBy(0,5); // Graph edits are safe after scheduler publication.
    }).onScriptFinished([&](const AnimationEvent&){++named;});
    expect(events.empty(),"handlers do not run while recording or registering");
    target.animate(.6);
    expect(events==std::vector<std::string>{"mark","yoyo","repeat","yoyo","repeat","yoyo"},"lifecycle events follow traversal order across a large update");
    expect(finished==1 && named==1,"selected script finishes once rather than once per child");
    near(target.getLocation().y,5,"completion handler can mutate target");
    target.animate(.1); expect(finished==1,"completed handlers do not fire again on later updates");
    bool blocked=false; int interruptions=0,ended=0;
    Animated<> interrupted;
    interrupted.moveBy(10,0,1,linearTween).andAlso().rotateBy(1,1,linearTween).until([&](const AnimationEvaluationContext&){return blocked;})
        .onUntilFired([&](const AnimationEvent& event){++interruptions;near(event.elapsedSeconds,.25,"interruption reports local time");})
        .onFinished([&](const AnimationEvent&){++ended;});
    interrupted.animate(.25); blocked=true; interrupted.animate(.25); interrupted.animate(1);
    expect(interruptions==1 && ended==1,"until interruption and wrapper completion each notify once");
    Animated<> natural;
    natural.moveBy(1,0,.1).until([](const AnimationEvaluationContext&){return false;})
        .onUntilFired([&](const AnimationEvent&){++interruptions;}).animate(.2);
    expect(interruptions==1,"natural completion does not report an until interruption");
    Animated<> a,b; Troupe troupe; int collective=0;
    troupe.add(a).add(b).moveBy(1,0,.1).stagger(.1).onFinished([&](const AnimationEvent& event){
        ++collective; expect(&event.target==&troupe,"collective completion target is the Troupe");
    }).animate(.2);
    expect(collective==1,"Troupe completion notifies once after last member");
    rejects([&]{target.on("",[](const AnimationEvent&){});},"empty event names reject");
    rejects([&]{target.onFinished({});},"empty lifecycle handlers reject");
    int starts=0,successes=0;
    Animated<> stopped;
    stopped.moveBy(1,0,1).onStarted([&](const AnimationEvent&){++starts;})
        .onFinished([&](const AnimationEvent&){++successes;});
    stopped.animate(.1); stopped.stopIt(); stopped.animate(2);
    expect(starts==1 && successes==0,"stop does not report successful completion or repeat activation");
    int errors=0; Animated<> failing;
    failing.moveBy(1,0,.1).onFinished([&](const AnimationEvent&){++errors;throw std::runtime_error("handler failed");});
    rejects([&]{failing.animate(.1);},"handler errors propagate");
    failing.animate(.1); expect(errors==1,"failed callback is not replayed");
}
void customEvents() {
    AnimatedBase::defineScript("scripts-custom-event").series()
        .moveBy(10,0,.1,linearTween).triggerEvent("arrived").moveBy(10,0,.1,linearTween)
        .endSeries().repeat(1).endScript();
    Animated<> target; int calls=0;
    target.playScript("scripts-custom-event").on("arrived",[&](const AnimationEvent& event) {
        ++calls; expect(event.type=="arrived" && event.scriptName=="scripts-custom-event","custom event identifies script");
        expect(&event.target==&target,"custom event identifies target");
    });
    expect(calls==0,"recorded custom events wait for execution");
    target.animate(.05); expect(calls==0,"custom event waits for preceding operation");
    target.animate(.05); expect(calls==1,"script fires event when step is reached");
    target.animate(.3); expect(calls==2,"repeated script fires event again");
    Animated<> live; int immediate=0;
    live.moveBy(1,0,1).on("signal",[&](const AnimationEvent&){++immediate;});
    live.triggerEvent("signal"); expect(immediate==1,"live custom event fires immediately");
    live.animate(.1); live.triggerEvent("signal"); expect(immediate==2,"active selection handles custom event");
    for(const auto* name : {"started","finished","scriptFinished","mark","yoyo","repeat","untilFired","eventType_MouseDown",""})
        rejects([&]{live.triggerEvent(name);},"PDG event names are reserved");
    Animated<> unhandled;
    unhandled.playScript("scripts-custom-event").animate(.4);
    near(unhandled.getLocation().x,20,"unhandled custom events do not interrupt repeated playback");
    Animated<> only; int zero=0;
    only.series().on("signal",[&](const AnimationEvent&){++zero;}).triggerEvent("signal").endSeries();
    only.animate(.1); expect(zero==1,"event-only script fires once");
}
void troupes() {
    Animated<> first,second; first.setLocation(100,0); second.setLocation(200,0);
    Troupe inner,outer; inner.add(first); outer.add(inner).add(first).add(second);
    expect(outer.getMemberCount()==3,"direct troupe membership count");
    expect(outer.animationTargets().size()==2,"nested membership deduplicates targets");
    rejects([&]{inner.add(outer);},"nested troupe cycles reject");
    outer.series().moveBy(10,0,.2,linearTween).rotateBy(1,.2,linearTween).endSeries();
    outer.animate(.2); near(first.getLocation().x,110,"troupe moves first relative to own baseline");
    near(second.getLocation().x,210,"troupe moves second relative to own baseline");
    near(first.getRotation(),0,"troupe series waits collectively");
    first.animate(.2); second.animate(.2);
    near(first.getLocation().x,110,"ordinary member update does not double troupe animation");
    outer.animate(.1); near(first.getRotation(),.5,"troupe series successor first");
    near(second.getRotation(),.5,"troupe series successor second");
    outer.remove(second); outer.animate(.1);
    near(second.getRotation(),.5,"removed member stops receiving troupe animation");
    near(first.getRotation(),1,"remaining member finishes");
    Troupe reversible; reversible.add(first).add(second);
    reversible.moveBy(10,0,.2,linearTween).yoyo(); reversible.animate(.4);
    near(first.getLocation().x,110,"troupe yoyo restores first baseline");
    near(second.getLocation().x,210,"troupe yoyo restores second baseline");
    reversible.moveBy(10,0,1,linearTween).diminish(0,1); reversible.animate(.5);
    near(first.getLocation().x,112.5,"troupe gain uses member baseline");
    near(second.getLocation().x,212.5,"troupe gain preserves member offsets");
    reversible.restartIt(); near(first.getLocation().x,110,"troupe restart restores member baseline");
    reversible.animate(1); near(first.getLocation().x,110,"troupe diminution finishes at baseline");
    reversible.series().mark("pose").moveBy(20,0,.4,linearTween).endSeries(); reversible.animate(.2);
    reversible.jumpToMark("pose"); near(first.getLocation().x,110,"troupe mark restores first member");
    near(second.getLocation().x,210,"troupe mark restores second member");
    reversible.animate(.2); near(second.getLocation().x,220,"troupe mark resumes member animation");
    Animated<> rates; Troupe rateTroupe; rateTroupe.add(rates).changeMovementTo(10,0,1,linearTween);
    rateTroupe.animate(.5); rates.animate(.5);
    near(rates.getLocation().x,1.25,"troupe integrates movement profile once across owner updates");
    rateTroupe.animate(.5); rates.animate(.5);
    near(rates.getLocation().x,5,"troupe completes movement profile without duplicate integration");
    rates.animate(.1); near(rates.getLocation().x,6,"completed troupe rate remains ordinary constant movement");
    Animated<> interrupted; Troupe interruptTroupe; interruptTroupe.add(interrupted).moveBy(100,0,1,linearTween);
    interruptTroupe.animate(.2); interrupted.setLocation(500,0); interruptTroupe.animate(.2);
    near(interrupted.getLocation().x,500,"member setter interrupts troupe channel");
}
void staggering() {
    Animated<> first,second,single;
    single.moveBy(10,0,.2,linearTween).stagger(.1).animate(.2);
    near(single.getLocation().x,10,"single-target stagger adds no delay");
    Troupe troupe; troupe.add(first).add(second);
    troupe.batch().moveBy(10,0,.2,linearTween).rotateBy(1,.2,linearTween).endBatch().stagger(.1)
        .andThen().moveBy(5,0,.1,linearTween);
    troupe.animate(.1);
    near(first.getLocation().x,5,"first stagger member starts immediately");
    near(second.getLocation().x,0,"second stagger member begins after interval");
    near(first.getRotation(),.5,"stagger offsets whole batch");
    near(second.getRotation(),0,"second batch rotation shares delay");
    troupe.animate(.15);
    near(first.getLocation().x,10,"stagger successor waits for last member");
    near(second.getLocation().x,7.5,"second stagger member progresses");
    troupe.animate(.15);
    near(first.getLocation().x,15,"stagger joins before successor");
    near(second.getLocation().x,15,"all stagger members complete successor");
    rejects([&]{troupe.stagger(-1);},"negative stagger rejects");
    bool stop=true;
    Troupe stopped; stopped.add(first).add(second);
    stopped.moveBy(10,0,1,linearTween).stagger(.2).until([&](const AnimationEvaluationContext&){return stop;});
    stopped.animate(1); near(first.getLocation().x,15,"until ends stagger first member");
    near(second.getLocation().x,15,"until prevents pending stagger member activation");
}
void validation() {
    AnimatedBase::defineScript("scripts-conflict").moveBy(10,0,1).moveBy(20,0,1).endScript();
    Animated<> conflict;
    rejects([&]{conflict.playScript("scripts-conflict");},"parallel writers reject before target mutation");
    near(conflict.getLocation().x,0,"invalid conflicting definition leaves target unchanged");
    AnimatedBase::defineScript("scripts-zero-loop").moveBy(1,0,0).repeat().endScript();
    rejects([&]{conflict.playScript("scripts-zero-loop");},"statically zero duration infinite loop rejects before playback");

    auto& draft=AnimatedBase::defineScript("scripts-validation");
    rejects([&]{draft.batch().diminish(0,1);},"empty context has no outer operand");
    rejects([&]{draft.endBatch();},"empty group rejects closure");
    draft.moveBy(1,0,1);
    rejects([&]{draft.endWhen();},"mismatched closure rejects"); draft.endBatch();
    draft.when([](const AnimationEvaluationContext&){return true;}).moveBy(2,0,1).otherwise().moveBy(3,0,1);
    rejects([&]{draft.endWhen();},"alternative requires endOtherwise"); draft.endOtherwise().endScript();
    auto& pending=AnimatedBase::defineScript("scripts-pending"); pending.moveBy(1,0,1).andThen();
    rejects([&]{pending.endScript();},"trailing placement rejects publication"); pending.moveBy(2,0,1).endScript();
    auto& rates=AnimatedBase::defineScript("scripts-rate-reversal"); rates.changeMovementTo(10,0,1);
    rejects([&]{rates.yoyo();},"rate reversal explicitly rejects unsupported trajectory");
    rates.endScript();
    rejects([]{AnimatedBase::defineScript("scripts-empty").endScript();},"empty script rejects publication");
}
}
void unsupportedOperations() {
    int fired=0;
    AnimatedBase::defineScript("unsupported-fade")
        .series().fadeOut(1.).moveBy(10,0,.5).endSeries().endScript();
    Animated<> target;
    target.playScript("unsupported-fade").on("unsupportedOp",[&](const AnimationEvent& event) {
        ++fired; expect(event.operationName=="fadeOut","unsupported event names operation");
        expect(&event.target==&target,"unsupported event identifies target");
    });
    target.animate(.5); expect(fired==1,"unsupported operation emits once on activation");
    near(target.getLocation().x,0,"unsupported operation preserves its duration");
    target.animate(.75); near(target.getLocation().x,5,"dependent starts after unsupported duration");
    expect(fired==1,"unsupported operation does not emit every update");
    target.animate(.25); near(target.getLocation().x,10,"script completes after unsupported operation");
    rejects([&]{target.triggerEvent("unsupportedOp");},"unsupportedOp is a reserved lifecycle event");
}
int main() {
    try { deleteDefinitions(); unsupportedOperations(); definitions(); composition(); branches(); controlsAndClocks(); liveControlsAndCopies(); sharedClockAndOwnership(); lateConstruction(); seriesAndMarks(); lifecycleHandlers(); customEvents(); troupes(); staggering(); validation();
        std::cout<<checks<<" animation script checks passed\n"; return 0;
    } catch(const std::exception& error) { std::cerr<<error.what()<<'\n'; return 1; }
}
