#include "pdg/sys/animatedattributes.h"
#include <cmath>
#include <array>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace pdg;
static int checks=0;
void expect(bool ok,const char* message) { ++checks; if(!ok) throw std::runtime_error(message); }
void near(double actual,double expected,const char* message) { expect(std::isfinite(actual)&&std::abs(actual-expected)<0.0001,message); }
template<class F> void rejects(F fn) { bool failed=false; try { fn(); } catch(const std::invalid_argument&) { failed=true; } expect(failed,"invalid request rejected"); }
struct Inspect : IAnimationHelper {
    bool animate(AnimatedBase* a,double) override {
        auto* attrs=dynamic_cast<AnimatedAttributes<>*>(a);
        near(attrs->getFillOpacity(),.5,"helper sees appearance sample");
        near(attrs->getTransform()[2][0],5,"helper sees movement matrix");
        return false;
    }
    bool ownedByAnimated() override { return false; }
};
void transformNear(const Attributes& attrs, float a, float b, float c, float d, float x, float y) {
    const auto& matrix=attrs.getTransform();
    near(matrix[0][0],a,"transform xx");near(matrix[0][1],b,"transform xy");
    near(matrix[1][0],c,"transform yx");near(matrix[1][1],d,"transform yy");
    near(matrix[2][0],x,"transform tx");near(matrix[2][1],y,"transform ty");
}

struct StyledOwner : AnimatedAttributes<StyledOwner> {
    using AnimatedAttributes<StyledOwner>::operator=;
    int visits = 0;
    StyledOwner& mark() { ++visits; return *this; }
};
void fluentOwners() {
    static_assert(std::is_same_v<decltype(std::declval<AnimatedAttributes<>&>().moveTo(1, 2, .5)), AnimatedAttributes<>&>);
    static_assert(std::is_same_v<decltype(std::declval<StyledOwner&>().fillOpacity(1).moveBy(1, 2, .5).andThen().changeFillOpacity(0, .25)), StyledOwner&>);
    static_assert(std::is_same_v<decltype(std::declval<StyledOwner&>() = std::declval<const Attributes&>()), StyledOwner&>);
    StyledOwner style;
    StyledOwner& result = style.fillOpacity(1).setLocation(0, 0).mark()
        .moveTo(10, 20, .5, linearTween).andThen()
        .changeFillOpacity(0, .25, linearTween).andThen().grow(2, .25, linearTween).mark();
    expect(&result == &style && style.visits == 2, "mixed chains retain their concrete owner");
    style.animate(.5);
    near(style.getLocation().x, 10, "movement completes before appearance starts");
    near(style.getFillOpacity(), 1, "appearance waits for movement");
    style.animate(.125);
    near(style.getFillOpacity(), .5, "appearance advances on the shared schedule");
    near(style.getWidth(), 1, "growth waits for appearance");
    style.animate(.375);
    near(style.getFillOpacity(), 0, "appearance completes");
    near(style.getWidth(), 2, "growth completes after appearance");

    AnimatedBase& motion = style;
    AnimatedAttributesBase& appearance = style;
    Attributes& drawing = style;
    expect(static_cast<AnimatedBase*>(&appearance) == &motion, "appearance and motion share one base");
    appearance.changeFrames(2, 6, 1);
    motion.cancelSchedule();
    style.animate(1);
    expect(!motion.hasScheduledAnimations(), "base cancellation clears derived appearance tracks");
    Attributes replacement;
    replacement.translation(Offset(7, 8)).fillOpacity(.75);
    drawing = replacement;
    near(style.getLocation().x, 7, "assignment through Attributes updates animated state");
    near(style.getFillOpacity(), .75, "assignment through Attributes updates appearance");
    glm::mat3 matrix(1); matrix[2][0] = 12;
    drawing.setTransform(matrix);
    near(style.getLocation().x, 12, "base transform setter invokes the derived implementation");
    AnimatedAttributes copied(replacement);
    near(copied.getLocation().y, 8, "standalone template deduction preserves Attributes construction");
}

void inheritedTransforms() {
    const float pi=std::acos(-1.f);
    AnimatedAttributes<> style;
    AnimatedBase& motion=style;
    Attributes& attributes=style;
    motion.setLocation(Point(10,20)).setSize(2,3).setScale(4,5).setRotation(pi/2);
    // Copy before getTransform(): stored Attributes values must already be current.
    Attributes immediate(attributes);
    transformNear(immediate,0,8,-15,0,10,20);
    motion.moveBy(2,3).grow(2).stretch(.5f,2).rotateBy(-pi/2);
    transformNear(attributes,8,0,0,60,12,23);
    transformNear(immediate,0,8,-15,0,10,20);

    style.setSize(1,1);style.setTransform(glm::mat3(1));
    motion.moveTo(Point(8,12),2,linearTween).resizeTo(4,6,2,linearTween)
        .changeScaleTo(3,5,2,linearTween).rotateTo(pi,2,linearTween,rotationDirection_Clockwise);
    style.animate(1);
    Attributes midpoint(attributes);
    transformNear(midpoint,0,5,-10.5f,0,4,6);
    motion.pauseSchedule();style.animate(1);
    transformNear(attributes,0,5,-10.5f,0,4,6);
    motion.resumeSchedule();style.animate(1);
    transformNear(attributes,-12,0,0,-30,8,12);
    transformNear(midpoint,0,5,-10.5f,0,4,6);

    style.setSize(1,1);style.setTransform(glm::mat3(1));
    motion.setMovement(4,6).setSpin(pi).setStretching(2,4);
    style.animate(.5);
    transformNear(Attributes(attributes),0,2,-3,0,2,3);
    motion.stopMovement().stopSpinning().stopStretching();
    style.animate(.5);transformNear(attributes,0,2,-3,0,2,3);

    style.setSize(1,1);style.setTransform(glm::mat3(1));
    motion.setCenterOffset(Offset(1,2)).setRotation(pi/2);
    transformNear(attributes,0,1,-1,0,3,1);
    motion.setScale(2,3);
    transformNear(attributes,0,2,-3,0,7,0);
}
void composedTransforms() {
    const float pi=std::acos(-1.f);
    AnimatedAttributes<> style;
    style.setLocation(Point(10,20)).rotateTo(pi/2);
    style.translation(Offset(4,0));
    near(style.getLocation().x,10,"translation follows rotated local axes, x");
    near(style.getLocation().y,24,"translation follows rotated local axes, y");
    style.scale(2,3);transformNear(style,0,2,-3,0,10,24);
    style.rotation(-pi/2);transformNear(style,3,0,0,2,10,24);
    near(style.getWidth(),1,"matrix composition preserves logical width");
    near(style.getHeight(),1,"matrix composition preserves logical height");
    near(style.getScale().x,3,"matrix composition updates independent scale");
    style.setLocation(Point(5,6)).rotateTo(0).setScale(2,1);
    transformNear(style,2,0,0,1,5,6);
    style.setTransform(glm::mat3(1));
    style.translation(Offset(4,7)).rotation(.3f,Point(2,3)).scale(2,3,Point(1,2));
    Attributes plain;
    plain.translation(Offset(4,7)).rotation(.3f,Point(2,3)).scale(2,3,Point(1,2));
    for(int c=0;c<3;++c)for(int r=0;r<3;++r)
        near(style.getTransform()[c][r],plain.getTransform()[c][r],"Attributes composition retains pivot semantics");
    style.scale(.5f);
    plain.scale(.5f);
    for(int c=0;c<3;++c)for(int r=0;r<3;++r)
        near(style.getTransform()[c][r],plain.getTransform()[c][r],"uniform scale overload");
}
void preservedLogicalSize() {
    AnimatedAttributes<> style;
    Attributes& attrs=style;
    style.setScale(2);attrs.scale(3);
    near(style.getWidth(),1,"mixed scale leaves width alone");near(style.getHeight(),1,"mixed scale leaves height alone");
    near(style.getScale().x,6,"mixed scale x");near(style.getScale().y,6,"mixed scale y");
    style.setSize(10,20).setScale(2,3);attrs.scale(3,4);
    transformNear(style,60,0,0,240,0,0);
    near(style.getWidth(),10,"base Attributes preserves width");near(style.getHeight(),20,"base Attributes preserves height");
    style.grow(2);transformNear(style,120,0,0,480,0,0);
    near(style.getWidth(),20,"grow changes logical width");near(style.getScale().x,6,"grow preserves independent scale");
    style.changeScaleTo(1,1,1,linearTween);style.animate(.5);
    transformNear(style,70,0,0,260,0,0);
    near(style.getWidth(),20,"timed scale preserves width");near(style.getHeight(),40,"timed scale preserves height");
    attrs.translation(Offset(2,3));
    near(style.getScale().x,3.5,"translation preserves scale");
    expect(!style.hasScheduledAnimations(),"composition interrupts transform tween");
    style.setSize(10,20).setScale(-2,3).setRotation(.4);
    attrs.translation(Offset(1,2));
    near(style.getRotation(),.4,"translation preserves signed-scale rotation");near(style.getScale().x,-2,"translation preserves reflection");
    attrs.scale(-3,0);near(style.getScale().x,6,"negative scale composes");near(style.getScale().y,0,"zero scale composes");
    attrs.translation(Offset(1,2));near(style.getRotation(),.4,"collapsed translation keeps rotation");
    style.setScale(1,2);near(style.getWidth(),10,"restoring collapsed scale keeps size");
    const auto restored=style.getTransform();near(std::hypot(restored[1][0],restored[1][1]),40,"collapsed direction can be restored");
    glm::mat3 rankOne(1);rankOne[0]=glm::vec3(2,0,0);rankOne[1]=glm::vec3(3,0,0);
    style.setTransform(rankOne);transformNear(style,2,0,3,0,0,0);
    near(style.getWidth(),10,"rank-one matrix keeps width");near(style.getHeight(),20,"rank-one matrix keeps height");
    style.setScale(.4,.5);transformNear(style,4,0,10,0,0,0);
    glm::mat3 target(1);target[0][0]=20;target[1][1]=60;
    style.setTransform(target);near(style.getScale().x,2,"replacement matrix scale x");near(style.getScale().y,3,"replacement matrix scale y");
    target[0][0]=40;target[1][1]=100;
    style.changeTransform(target,1);style.animate(.5);
    near(style.getWidth(),10,"matrix tween preserves width");near(style.getHeight(),20,"matrix tween preserves height");
    near(style.getScale().x,3,"matrix tween scale x");near(style.getScale().y,4,"matrix tween scale y");
    style.animate(.5);
    style.changeSkew(.5,.25,1);style.animate(1);
    near(style.getWidth(),10,"skew keeps width");near(style.getHeight(),20,"skew keeps height");
    style.setSize(0,20).setScale(2,3);attrs.scale(3,4);
    near(style.getWidth(),0,"zero logical width stays zero");near(style.getScale().x,6,"hidden scale remains available");
    rejects([&]{style.setTransform(glm::mat3(1));});
    near(style.getWidth(),0,"incompatible matrix does not change zero width");
    style.setSize(10,20);style.setTransform(glm::mat3(1));
    style.resizeTo(20,40,1,linearTween);
    style.andThen().changeTransform(target,1);
    style.animate(2);near(style.getWidth(),20,"queued matrix preserves completed resize");near(style.getScale().x,2,"queued matrix uses completed reference size");
    AnimatedAttributes<> zero;
    zero.resizeTo(0,1,.5,linearTween);
    zero.andThen().changeTransform(glm::mat3(1),.5);
    rejects([&]{zero.animate(.5);});
    expect(!zero.hasScheduledAnimations(),"incompatible queued matrix is removed");
    zero.setSize(1,1);zero.setScale(2);zero.scale(3);
    near(zero.getScale().x,6,"can continue after incompatible queued matrix");
    zero.setSize(0,1);zero.resizeTo(2,1,.5,linearTween);
    zero.andThen().changeTransform(glm::mat3(1),.5);zero.animate(1);
    near(zero.getWidth(),2,"queued matrix uses restored logical dimension");near(zero.getScale().x,.5,"queued restored dimension scale");
    for (bool flip : {false,true}) {
        style.setSize(-10,20).setFlipY(flip);
        for (const auto& columns : {std::array<float,4>{2,3,4,5}, {0,0,3,4}, {-2,0,0,3}, {2,0,3,0}, {0,0,0,0}}) {
            glm::mat3 matrix(1);matrix[0]=glm::vec3(columns[0],columns[1],0);matrix[1]=glm::vec3(columns[2],columns[3],0);
            matrix[2]=glm::vec3(4,7,1);
            style.setTransform(matrix);
            transformNear(style,columns[0],columns[1],columns[2],columns[3],4,7);
            near(style.getWidth(),-10,"matrix preserves signed logical width");
            expect(style.isFlippedY()==flip,"matrix preserves explicit flip");
        }
    }
}
int main() { try {
    preservedLogicalSize();
    fluentOwners();inheritedTransforms();
    composedTransforms();
    AnimatedAttributes<> immediate;
    Attributes& immediateBase=immediate;
    immediate.wait(0);
    rejects([&]{immediate.translation(Offset(1,2));});
    rejects([&]{immediate.rotation(.5f);});
    rejects([&]{immediate.scale(2.f);});
    rejects([&]{immediateBase.fillOpacity(.5);});
    rejects([&]{immediateBase.fitType(fit_Fill);});
    rejects([&]{immediate.changeFrames(1,4,0);});
    rejects([&]{immediate.changeTransform(glm::mat3(1),0);});
    immediate.changeFillOpacity(.5,1);immediate.animate(1);
    near(immediate.getFillOpacity(),.5,"positive duration consumes pending wait after rejection");
    immediate.fillOpacity(.25);near(immediate.getFillOpacity(),.25,"attribute setter updates immediately");
    AnimatedAttributes<> delayed;
    delayed.wait(1).changeFillOpacity(0,1);
    expect(!delayed.animate(.25),"waiting alone is not an attribute change");
    expect(!delayed.animate(0),"zero step does not change attributes");
    expect(delayed.animate(1),"appearance-only changes are reported");
    AnimatedAttributes<> a;
    Attributes& base=a;
    a.fillColor(Color(1.f,0.f,0.f));
    a.changeFillColor(Color(0.f,0.f,1.f),2).changeLineThickness(5,2).changeFillOpacity(0,2);
    a.moveTo(pdg::Point(10,20),2,linearTween);
    Inspect helper; a.addAnimationHelper(&helper);
    expect(a.animate(1),"appearance changes reported");
    near(a.getFillColor().red,.5,"color midpoint"); near(a.getLineThickness(),3,"line midpoint");
    base.lineThickness(9); a.animate(1);
    near(a.getLineThickness(),9,"base setter cancels only its channel"); near(a.getFillColor().blue,1,"unrelated channel completes");
    a.ambientLight(Color(.1f,.2f,.3f,.4f));
    Attributes snapshot(a), assigned; assigned=a;
    near(snapshot.getAmbientLight().red,.1,"copy captures ambient light"); near(assigned.getAmbientLight().alpha,.4,"assignment captures ambient light");
    a.changeAmbientLight(Color(1.f,1.f,1.f),1);a.animate(1);
    near(snapshot.getAmbientLight().red,.1,"snapshot independent");
    a.wait(.5).changeTextSize(20,.5); a.animate(.25); near(a.getTextSize(),12,"seconds wait");
    a.animate(.5);near(a.getTextSize(),16,"partial active time after wait");a.animate(.25);near(a.getTextSize(),20,"wait completion");
    a.changeTextSize(40,1); rejects([&]{a.changeTextSize(3,-1);});a.animate(.5);near(a.getTextSize(),30,"rejection preserves old track");
    a.fillColor(Color(1.f,1.f,1.f));
    a.wait(.5).changeFillGradient(pdg::Point(1,2),Color(1.f,0.f,0.f),pdg::Point(10,20),Color(0.f,0.f,1.f),1);
    a.animate(.25);expect(a.getGradientType()==gradientType_None,"gradient waits");
    a.animate(.5);expect(a.getGradientType()==gradientType_Linear,"gradient switches discretely");near(a.getGradientEnd().x,2.5,"gradient interpolates");
    base.fillColor(Color(0.f,1.f,0.f));a.animate(1);expect(a.getGradientType()==gradientType_None,"solid fill interrupts gradient");near(a.getGradientEnd().x,2.5,"gradient parameters canceled");
    a.changeFillRadialGradient(pdg::Point(4,8),Color(1.f,1.f,1.f),10,Color(0.f,0.f,0.f),2);a.animate(1);near(a.getRadialGradientRadius(),5,"radius tween");
    a.changeRoundedCorners(8,2).changeSubsection(Rect(2,4,10,20),2).changePolarOffset(Offset(2,4),2).changeLightOffset(Offset(6,8),2);
    a.animate(1);near(a.getRoundedCornerRadius(),4,"corner tween");near(a.getSubsection().bottom,10,"subsection tween");near(a.getPolarOffset().x,1,"polar tween");near(a.getLightOffset().y,4,"light tween");
    a.frame(7);a.wait(1).changeFrames(2,5,1);a.animate(.5);expect(a.getFrame()==7,"frame wait keeps original");a.animate(.5);expect(a.getFrame()==2,"first integer frame");a.animate(.25);expect(a.getFrame()==3,"equal frame bins");a.animate(1);expect(a.getFrame()==5,"last frame held");
    a.changeFrames(4,1,1);a.animate(.5);expect(a.getFrame()==2,"reverse sequence");base.frame(9);a.animate(1);expect(a.getFrame()==9,"immediate frame interrupts");
    a.sphereRotation(6);a.changeSphereRotation(.2,1,linearTween,rotationDirection_Clockwise);a.animate(.5);expect(a.getSphereRotation()>6,"sphere direction");
    a.setTransform(glm::mat3(1));a.setLocation(Point(10,20));near(base.getTransform()[2][0],10,"Animated location reflected in Attributes");
    a.moveTo(pdg::Point(20,30),1,linearTween);a.animate(.5);near(base.getTransform()[2][0],15,"Animated reflected in Attributes");
    auto matrix=base.getTransform();a.animate(0);for(int c=0;c<3;++c)for(int r=0;r<3;++r)near(base.getTransform()[c][r],matrix[c][r],"matrix does not accumulate");
    base.skew(.2,.3);matrix=base.getTransform();Attributes copied(a);for(int c=0;c<3;++c)for(int r=0;r<3;++r)near(copied.getTransform()[c][r],matrix[c][r],"shear snapshot");
    a.setTransform(glm::mat3(1));glm::mat3 target(1);target[2][0]=20;target[0][0]=3;a.changeTransform(target,2);a.animate(1);near(a.getLocation().x,10,"matrix location");near(a.getWidth(),1,"matrix preserves reference size");near(a.getScale().x,2,"matrix scale");
    rejects([&]{ a.moveTo(pdg::Point(0,0),-1,linearTween); });
    a.animate(.25); near(a.getLocation().x,12.5,"rejected component request preserves matrix tween");
    a.changeScaleTo(4,5,.5);a.animate(.5);near(a.getScale().x,4,"timed scale interrupts matrix tween");
    a.changeTransform(target,2);a.animate(.5);
    a.setLocation(pdg::Point(4,5));a.animate(1);near(a.getLocation().x,4,"component setter interrupts matrix");
    a.setTransform(glm::mat3(1));a.changeScaleTo(2,3,1);a.animate(1);near(a.getTransform()[1][1],3,"scale channel");
    a.rotateTo(1,1,linearTween,rotationDirection_Clockwise);a.animate(1);near(a.getRotation(),1,"rotation channel");
    glm::mat3 singular(1);singular[0]=glm::vec3(0);singular[1]=glm::vec3(3,4,0);a.setTransform(singular);near(a.getTransform()[1][0],3,"singular affine preserved");
    target[0][2]=1;rejects([&]{a.changeTransform(target,1);});rejects([&]{a.animate(std::numeric_limits<double>::infinity());});
    AnimatedAttributes<> paused;
    paused.setSize(10,20).setScale(2,3);
    near(paused.getWidth(),10,"Attributes logical size separate from scale");
    near(paused.getTransform()[0][0],20,"Attributes matrix combines size and scale");
    near(paused.getTransform()[1][1],60,"Attributes matrix vertical scale");
    paused.changeFillOpacity(0,1);paused.changeFrames(1,4,1);paused.animate(.5);
    paused.pauseSchedule();paused.animate(1);near(paused.getFillOpacity(),.5,"appearance paused");
    expect(paused.getFrame()==3,"frame sequence paused");
    AnimatedBase& animated=paused;animated.cancelSchedule();paused.frame(8);paused.resumeSchedule();paused.animate(1);
    near(paused.getFillOpacity(),.5,"appearance cancel retains sample");expect(paused.getFrame()==8,"canceled frame sequence cannot overwrite manual frame");
    glm::mat3 canceled(1);canceled[2][0]=100;paused.changeTransform(canceled,1);paused.animate(.25);
    animated.cancelSchedule();paused.setMovement(4,0);const float x=paused.getLocation().x;
    paused.animate(.5);near(paused.getLocation().x,x+2,"cancel matrix clears auxiliary playback state");
    AnimatedAttributes<> sequence;
    sequence.changeFrames(1,4,1).andThen().changeFrames(8,5,1);
    sequence.animate(.5); expect(sequence.getFrame()==3,"queued frames preserve predecessor");
    sequence.animate(.5); expect(sequence.getFrame()==8,"frame successor starts at boundary");
    sequence.animate(.5); expect(sequence.getFrame()==6,"queued reverse frames");
    sequence.animate(.5); expect(sequence.getFrame()==5,"queued frame endpoint");
    sequence.changeFillGradient(Point(),Color(1.f,0.f,0.f),Point(10,20),Color(0.f,0.f,1.f),1)
        .andThen().changeFillColor(Color(0.f,1.f,0.f),1)
        .andThen().changeFillRadialGradient(Point(2,4),Color(1.f,1.f,1.f),10,Color(0.f,0.f,0.f),1);
    sequence.animate(.5); expect(sequence.getGradientType()==gradientType_Linear,"future fill preserves mode");
    near(sequence.getGradientEnd().x,5,"future fill preserves parameters");
    sequence.animate(.5); expect(sequence.getGradientType()==gradientType_None,"solid successor mode");
    sequence.animate(1); expect(sequence.getGradientType()==gradientType_Radial,"radial successor mode");
    sequence.animate(.5); near(sequence.getRadialGradientRadius(),5,"radial successor samples");
    sequence.cancelSchedule().setTransform(glm::mat3(1));
    glm::mat3 nextMatrix(1); nextMatrix[2][0]=20;
    sequence.moveTo(Point(10,0),1,linearTween);
    sequence.andThen().changeTransform(nextMatrix,1).andThen().moveTo(Point(30,0),1,linearTween);
    sequence.animate(.5); near(sequence.getLocation().x,5,"queued matrix preserves movement");
    sequence.animate(1); near(sequence.getLocation().x,15,"matrix starts from completed movement");
    sequence.animate(1); near(sequence.getLocation().x,25,"component starts from completed matrix");
    sequence.animate(.5); near(sequence.getLocation().x,30,"matrix/component sequence endpoint");
    sequence.setTransform(glm::mat3(1));
    sequence.changeScaleTo(2,3,1,linearTween);
    sequence.andThen().changeSkew(.5f,.25f,1);
    sequence.animate(2); near(sequence.getTransform()[0][1],1.5,"queued skew uses future matrix");
    near(sequence.getTransform()[1][0],.5,"queued skew second coefficient");
    sequence.changeTransform(nextMatrix,1).andThen().changeTransform(glm::mat3(1),1);
    sequence.animate(.5); sequence.setLocation(Point(7,8)); sequence.animate(3);
    near(sequence.getLocation().x,7,"immediate component cancels queued matrices");
    std::shared_ptr<Attributes::LiveSample> live;
    {
        AnimatedAttributes<> source;
        live=source.liveSample();
        expect(live==source.liveSample(), "live sample shares identity");
        source.moveTo(20,30,1,linearTween).changeFillOpacity(0,1,linearTween);
        source.animate(.5);
        near(live->get().getTransform()[2][0],10,"live animated transform");
        near(live->get().getFillOpacity(),.5,"live animated appearance");
    }
    near(live->get().getTransform()[2][1],15,"source destruction retains final transform");
    near(live->get().getFillOpacity(),.5,"source destruction retains final appearance");
    std::cout<<checks<<" AnimatedAttributes checks passed\n";
} catch(const std::exception& e) { std::cerr<<e.what()<<'\n';return 1; } }
