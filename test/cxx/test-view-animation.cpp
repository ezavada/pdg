#include "pdg/app/View.h"
#include "pdg/sys/initializer.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include "pdg/app/Button.h"
#include "pdg/app/ScrollingView.h"

using namespace pdg;
struct ProbeView : View {
    ProbeView(const pdg::Rect& area, int binding=0) : View(nullptr,nullptr,area,binding) {}
    void drawSelf() override {}
};
struct ProbeScroll : ScrollingView {
    ProbeScroll() : ScrollingView(nullptr, nullptr, pdg::Rect(-10,10,80,60), 0, bind_None) {}
    void drawSelf() override {}
};
static int checks=0;
static void expect(bool ok, const char* message) {
    ++checks; if (!ok) throw std::runtime_error(message);
}
static void near(float value, float expected, const char* message) {
    expect(std::isfinite(value) && std::abs(value-expected)<.001, message);
}
void testTextCache();
int main() {
    try {
        testTextCache();
        static_assert(std::is_base_of_v<AnimatedAttributes<View>, View>);
        static_assert(std::is_base_of_v<Attributes, Button>);
        static_assert(std::is_base_of_v<AnimatedBase, Button>);
        static_assert(std::is_base_of_v<AnimatedBase, ScrollingView>);
        static_assert(std::is_same_v<decltype(std::declval<View&>().fillOpacity(1).moveTo(1, 2, .5).andThen().changeLineThickness(2, .5)), View&>);
        ProbeView chained(pdg::Rect(0, 0, 100, 40));
        View& chainResult = chained.fillOpacity(1).moveBy(10, 20, .5, linearTween)
            .andThen().changeFillOpacity(0, .5, linearTween);
        expect(&chainResult == &chained, "view chains return the same View");
        chained.animate(.75);
        near(chained.getViewArea().left, 10, "fluent movement updates view layout");
        near(chained.getFillOpacity(), .5, "view appearance follows movement on one schedule");
        ProbeView styled(pdg::Rect(10,20,110,60));
        styled.setScale(2);static_cast<Attributes&>(styled).scale(3);
        near(styled.getWidth(),100,"attribute scale keeps view logical width");
        near(styled.getViewArea().width(),100,"attribute scale keeps layout width");
        near(styled.getScale().x,6,"view shares composed scale");
        styled.grow(2);
        near(styled.getViewArea().width(),200,"growth still changes view layout");
        near(styled.getScale().x,6,"growth keeps composed scale");
        ProbeView v(pdg::Rect(10,20,110,60));
        near(v.getLocation().x,60,"location is layout center");
        v.changeFillOpacity(0,1);
        v.animate(.5);
        near(v.getFillOpacity(),.5,"view appearance uses seconds");
        const Attributes& drawingAttributes=v;
        near(drawingAttributes.getTransform()[0][0],100,"unit drawing scales to view width");
        near(drawingAttributes.getTransform()[2][0],60,"unit drawing translates to view center");
        v.addClickablePart(pdg::Rect(0,0,100,40),7);
        v.moveBy(100,40,.5,linearTween); v.animate(.25);
        near(v.getViewArea().left,60,"fractional-second movement updates layout");
        near(v.getViewArea().top,40,"movement y updates layout");
        expect(v.getPartClicked(pdg::Point(65,45))==7,"click geometry follows movement");
        expect(!v.pointInViewArea(pdg::Point(15,25)),"old area no longer clickable");
        v.animate(.25); v.grow(2,.5,linearTween); v.animate(.5);
        near(v.getWidth(),200,"inherited growth resizes the view");
        near(v.getLocation().x,160,"growth preserves center");
        expect(v.getPartClicked(v.localToGlobal(pdg::Point(180,70)))==7,"click geometry resizes");
        v.setViewArea(pdg::Rect(20,30,100,90));
        near(v.getLocation().x,60,"setting layout updates Animated");
        v.setMovement(20,0); v.animate(.25);
        near(v.getViewArea().left,25,"programmed movement updates layout");
        ProbeView bound(pdg::Rect(10,20,110,60),View::Bind::Grow);
        bound.portResized(pdg::Rect(0,0,200,100),pdg::Rect(0,0,300,200));
        near(bound.getWidth(),200,"port resize updates width");
        near(bound.getHeight(),140,"port resize updates height");
        near(bound.getLocation().x,110,"port resize updates center");
        ProbeView transformed(pdg::Rect(40,50,160,90));
        transformed.addClickablePart(pdg::Rect(0,0,25,40),9);
        transformed.setRotation(1.0f).setFlipX(true);
        pdg::Point world=transformed.localToGlobal(pdg::Point(10,20));
        pdg::Point local=transformed.globalToLocal(world);
        near(local.x,10,"rotation/reflection inverse x"); near(local.y,20,"rotation/reflection inverse y");
        expect(transformed.getPartClicked(world)==9,"transformed clickable region");
        expect(!transformed.pointInViewVisibleArea(pdg::Point(42,52)),"rotated corner is not clickable");
        transformed.setScale(0);expect(!transformed.pointInViewVisibleArea(world),"singular view is not clickable");
        ProbeView parent(pdg::Rect(20,20,180,100)), child(pdg::Rect(30,30,80,60));
        child.setParentView(&parent);parent.moveBy(10,15);
        near(child.getViewArea().left,40,"child follows parent x");near(child.getViewArea().top,45,"child follows parent y");
        parent.setRotation(.4f);child.setFlipY(true);
        world=child.localToGlobal(pdg::Point(5,10));near(child.globalToLocal(world).x,5,"composite inverse transform");
        bool rejected=false;try { parent.setParentView(&child); } catch (const std::invalid_argument&) { rejected=true; }
        expect(rejected,"reject parenting cycle");
        parent.hide();expect(!child.isVisible(),"parent hides children");
        Attributes theme;theme.fillColor(PDG_RED_COLOR).lineThickness(7).roundedCorners(12).textSize(24);
        ProbeView appearance(pdg::Rect(100,40));
        near(appearance.getDrawingAttributes(theme).getTextSize(),24,"unset appearance inherits theme");
        appearance.lineThickness(1).roundedCorners(0).textSize(12).fillColor(PDG_BLUE_COLOR);
        const Attributes composed=appearance.getDrawingAttributes(theme);
        near(composed.getLineThickness(),1,"explicit default overrides theme");
        near(composed.getRoundedCornerRadius(),0,"explicit zero overrides theme");
        near(composed.getTextSize(),12,"explicit default text size overrides theme");
        near(appearance.getDrawingAttributes(theme,true).getFillColor().red,1,"label retains theme foreground");
        near(theme.getLineThickness(),7,"theme is not mutated");
        ProbeScroll scrolling;
        scrolling.setViewArea(pdg::Rect(-50,-50,200,200));
        expect(scrolling.pointInViewVisibleArea(pdg::Point(20,20)),"scrolling frame accepts visible content");
        expect(!scrolling.pointInViewVisibleArea(pdg::Point(90,20)),"scrolling frame excludes overflow");
        scrolling.setRotation(.4f);scrolling.setFlipX(true);
        const auto inFrame=scrolling.localToGlobal(pdg::Point(70,70));
        expect(scrolling.pointInViewVisibleArea(inFrame),"scrolling viewport transforms with content");
        scrolling.setViewFrame(pdg::Rect(30,30,80,60));
        expect(!scrolling.pointInViewVisibleArea(inFrame),"resized viewport updates transformed hit region");
        std::cout << "View animation: " << checks << " checks passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n'; return 1;
    }
}

// Engine linkage hooks; this test does not initialize graphics or create a window.
namespace pdg {
bool Initializer::allowHorizontalOrientation() throw() { return true; }
bool Initializer::allowVerticalOrientation() throw() { return true; }
const char* Initializer::getAppName(bool) throw() { return "PDG View Animation Tests"; }
const char* Initializer::getMainResourceFileName() throw() { return nullptr; }
bool Initializer::installGlobalHandlers() throw() { return false; }
bool Initializer::getGraphicsEnvironmentDimensions(pdg::Rect, pdg::Rect, long& width, long& height, uint8& depth) throw() {
    width = height = 1; depth = 32; return false;
}
}
