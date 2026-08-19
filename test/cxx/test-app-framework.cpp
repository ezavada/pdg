#include "pdg/app/ControlAttributes.h"
#include "pdg/app/Application.h"
#include "pdg/app/Checkbox.h"
#include "pdg/app/Controller.h"
#include "pdg/app/Observer.h"
#include "pdg/app/RadioButton.h"
#include "pdg/app/Scrollbar.h"
#include "pdg/app/View.h"
#include "pdg/sys/initializer.h"
#include "pdg-main.h"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace {

void fail(const std::string& message)
{
    std::cerr << "Application framework test failed: " << message << '\n';
    std::exit(EXIT_FAILURE);
}

void expect(bool condition, const std::string& message)
{
    if (!condition) fail(message);
}

class RecordingObserver : public pdg::IObserver {
public:
    RecordingObserver(int id, std::vector<int>& calls) : mId(id), mCalls(calls) {}

    void notify(pdg::Subject* subject) override
    {
        expect(subject != nullptr, "observer received its subject");
        mCalls.push_back(mId);
    }

private:
    int mId;
    std::vector<int>& mCalls;
};

class TestApplication : public pdg::Application {
public:
    void initialize(int, const char**) override { initialized = true; }
    void cleanup() override { cleanedUp = true; }

    bool initialized = false;
    bool cleanedUp = false;
};

class TestController : public pdg::Controller {
public:
    explicit TestController(pdg::Application* app)
        : Controller(app, false, false, false, false, true) {}

    pdg::ControlAttributes getControlAttributes(pdg::ControlType type) override
    {
        return getControlAttributes(type, -1);
    }

    pdg::ControlAttributes getControlAttributes(pdg::ControlType type, int styleId) override
    {
        requestedType = type;
        requestedStyle = styleId;
        return pdg::ControlAttributes().stateForeground(
            pdg::ControlState::Normal, pdg::Color(12, 34, 56));
    }

    pdg::ControlType requestedType = pdg::ControlType::Other;
    int requestedStyle = -1;
};

class TestView : public pdg::View {
public:
    TestView(pdg::Controller* controller, const pdg::Rect& area)
        : View(controller, area) {}

    void drawSelf() override { ++drawCount; }
    int drawCount = 0;
};

void testObserverOrderingAndRemoval()
{
    pdg::Subject subject;
    std::vector<int> calls;
    RecordingObserver first(1, calls);
    RecordingObserver second(2, calls);

    subject.addObserver(&first);
    subject.addObserver(&second);
    subject.notifyObservers();
    expect(calls == std::vector<int>({2, 1}), "observers are notified newest first");

    calls.clear();
    subject.removeObserver(&second);
    subject.notifyObservers();
    expect(calls == std::vector<int>({1}), "removed observer is not notified");
}

void testApplicationManagerAccessors()
{
    TestApplication app;
    expect(&app.getEventManager() == &pdg::EventManager::instance(),
        "application exposes the event manager singleton");
    expect(&app.getResourceManager() == &pdg::ResourceManager::instance(),
        "application exposes the resource manager singleton");
    expect(&app.getTimerManager() == &pdg::TimerManager::instance(),
        "application exposes the timer manager singleton");
}

void testControllerHierarchyAndThemeHook()
{
    TestApplication app;
    TestController root(&app);
    TestController child(&app);
    root.addChild(&child);

    expect(&child.getTopController() == &root, "child resolves the top controller");
    expect(root.isActive(), "controllers begin active");
    root.setActive(false);
    expect(!root.isActive(), "controller active state can be changed");

    pdg::ControlAttributes theme = root.getControlAttributes(pdg::ControlType::Button, 42);
    expect(root.requestedType == pdg::ControlType::Button && root.requestedStyle == 42,
        "theme hook receives control type and style id");
    expect(theme.state(pdg::ControlState::Normal).hasForeground,
        "theme hook can return control attributes");
}

void testViewAndControllerRegistration()
{
    TestApplication app;
    TestController controller(&app);
    auto* view = new TestView(&controller, pdg::Rect(10, 20, 110, 70));
    controller.addView(view, 17);

    expect(controller.getView<TestView>(17) == view, "controller retrieves a typed view by id");
    expect(view->isVisible() && view->isEnabled(), "view begins visible and enabled");
    view->hide();
    expect(!view->isVisible(), "view can be hidden");
    view->show();
    view->setEnabled(false);
    expect(view->isVisible() && !view->isEnabled(), "view visibility and enabled state are independent");

    view->addClickablePart(pdg::Rect(0, 0, 25, 25), 3);
    expect(view->getPartClicked(pdg::Point(20, 30)) == 3,
        "clickable parts use local coordinates and global hit testing");
    view->removeClickablePart(3);
    expect(view->getPartClicked(pdg::Point(20, 30)) == pdg::View::CLICKED_PART_NONE,
        "clickable parts can be removed");
}

void testStatefulControlsAndThemedClickBehavior()
{
    TestApplication app;
    TestController controller(&app);

    int checkboxClicks = 0;
    pdg::Checkbox checkbox(&controller, pdg::Rect(0, 0, 150, 25));
    checkbox.setAttributes(pdg::ControlAttributes()
        .clickRoutine([&checkboxClicks]() { ++checkboxClicks; }));
    expect(!checkbox.isChecked(), "checkbox begins unchecked");
    checkbox.doClick(pdg::Checkbox::CLICK_ID_CHECKBOX);
    expect(checkbox.isChecked() && checkboxClicks == 1,
        "checkbox toggles and runs themed click behavior");

    int radioClicks = 0;
    pdg::RadioButton radio(&controller, pdg::Rect(0, 0, 300, 30), -1, 3);
    radio.setString(0, "One");
    radio.setString(1, "Two");
    radio.setString(2, "Three");
    radio.setAttributes(pdg::ControlAttributes()
        .clickRoutine([&radioClicks]() { ++radioClicks; }));
    expect(radio.getSelectedIndex() == 0, "radio group begins at its first option");
    radio.doClick(2);
    expect(radio.getSelectedIndex() == 2 && radioClicks == 1,
        "radio group changes selection and runs themed click behavior");

    pdg::Scrollbar scrollbar(&controller, pdg::Rect(0, 0, 200, 20),
        pdg::Scrollbar::HORIZONTAL, 0, 10, 100);
    expect(controller.requestedType == pdg::ControlType::Scrollbar &&
        controller.requestedStyle == static_cast<int>(pdg::Scrollbar::HORIZONTAL),
        "scrollbar passes orientation to the theme hook");
    expect(scrollbar.getCurrentPosition() == 0 && scrollbar.getScrollRange() == 90,
        "scrollbar exposes its initial position and range");
    scrollbar.setCurrentPosition(50);
    expect(scrollbar.getCurrentPosition() == 50, "scrollbar position can be changed");
    scrollbar.setCurrentPosition(500);
    expect(scrollbar.getCurrentPosition() == 90, "scrollbar position clamps to its maximum");
}

void testStateAccessAndFluentSetters()
{
    pdg::ControlAttributes attributes;
    const pdg::Color foreground(20, 40, 60);
    pdg::Attributes drawing;

    pdg::ControlAttributes& result = attributes
        .stateAttributes(pdg::ControlState::Normal, drawing)
        .stateForeground(pdg::ControlState::Hovered, foreground);

    expect(&result == &attributes, "setters return the receiver");
    expect(attributes.state(pdg::ControlState::Normal).hasDrawing,
        "drawing presence is recorded");
    expect(attributes.state(pdg::ControlState::Hovered).hasForeground,
        "foreground presence is recorded");
}

void testPartialMergeAndForegroundPreservation()
{
    pdg::ControlAttributes base;
    base.stateAttributes(pdg::ControlState::Normal, pdg::Attributes())
        .stateForeground(pdg::ControlState::Normal, pdg::Color(10, 20, 30));

    pdg::ControlAttributes overrides;
    overrides.stateForeground(pdg::ControlState::Hovered, pdg::Color(40, 50, 60));
    base.merge(overrides);

    expect(base.state(pdg::ControlState::Normal).hasDrawing,
        "partial merge preserves normal drawing");
    expect(base.state(pdg::ControlState::Normal).hasForeground,
        "partial merge preserves normal foreground");
    expect(base.state(pdg::ControlState::Hovered).hasForeground,
        "partial merge adds hovered foreground");
}

void testBackgroundSourcePrecedence()
{
    pdg::ControlAttributes attributes;
    attributes.stateAttributes(pdg::ControlState::Normal, pdg::Attributes());

    pdg::ControlAttributes imageOverride;
    // A null pointer is intentional: presence and ownership are separate.
    imageOverride.stateImage(pdg::ControlState::Normal, nullptr);
    attributes.merge(imageOverride);
    const pdg::ControlStateAttributes& imageState = attributes.state(pdg::ControlState::Normal);
    expect(imageState.hasImage, "image override records explicit presence");
    expect(!imageState.hasDrawing, "image override removes lower-level drawing");
    expect(!imageState.hasDrawRoutine, "image override removes lower-level draw routine");

    pdg::ControlAttributes routineOverride;
    routineOverride.stateDrawRoutine(pdg::ControlState::Normal,
        [](pdg::Port&, const pdg::Rect&, const pdg::ControlStateAttributes&) {});
    attributes.merge(routineOverride);
    const pdg::ControlStateAttributes& routineState = attributes.state(pdg::ControlState::Normal);
    expect(routineState.hasDrawRoutine, "draw routine override is selected");
    expect(!routineState.hasImage, "draw routine override removes image");
    expect(!routineState.hasDrawing, "draw routine override removes drawing");
}

void testImageDrawingModifiersSurviveMerge()
{
    pdg::ControlAttributes attributes;
    pdg::ControlAttributes overrides;
    overrides.stateImage(pdg::ControlState::Pressed, nullptr)
        .stateAttributes(pdg::ControlState::Pressed, pdg::Attributes());
    attributes.merge(overrides);

    const pdg::ControlStateAttributes& state = attributes.state(pdg::ControlState::Pressed);
    expect(state.hasImage, "image remains selected when modifiers are supplied");
    expect(state.hasDrawing, "image drawing modifiers survive merge");
}

void testClickBehaviorAndPrecedence()
{
    int routineCalls = 0;
    pdg::ControlAttributes attributes;
    attributes.clickSound(nullptr, 0.35f)
        .clickRoutine([&routineCalls]() { ++routineCalls; });

    expect(attributes.hasClickSound(), "click sound presence is recorded");
    expect(attributes.hasClickRoutine(), "click routine presence is recorded");
    expect(attributes.getClickVolume() == 0.35f, "click volume is retained");
    attributes.playClick();
    expect(routineCalls == 1, "click routine takes precedence and executes");

    pdg::ControlAttributes override;
    int overrideCalls = 0;
    override.clickRoutine([&overrideCalls]() { ++overrideCalls; });
    attributes.merge(override);
    attributes.playClick();
    expect(routineCalls == 1 && overrideCalls == 1,
        "higher-level click routine replaces lower-level routine");
}

} // namespace

namespace pdg {

bool Initializer::allowHorizontalOrientation() throw() { return true; }
bool Initializer::allowVerticalOrientation() throw() { return true; }
const char* Initializer::getAppName(bool) throw() { return "PDG App Framework Tests"; }
const char* Initializer::getMainResourceFileName() throw() { return nullptr; }
bool Initializer::installGlobalHandlers() throw() { return false; }
bool Initializer::getGraphicsEnvironmentDimensions(Rect, Rect, long& width, long& height,
                                                    uint8& depth) throw()
{
    width = 1;
    height = 1;
    depth = 32;
    return false;
}

} // namespace pdg

int main()
{
    expect(pdg::main_initManagers() == 0, "PDG managers initialize for framework tests");
    testObserverOrderingAndRemoval();
    testApplicationManagerAccessors();
    testControllerHierarchyAndThemeHook();
    testViewAndControllerRegistration();
    testStatefulControlsAndThemedClickBehavior();
    testStateAccessAndFluentSetters();
    testPartialMergeAndForegroundPreservation();
    testBackgroundSourcePrecedence();
    testImageDrawingModifiersSurviveMerge();
    testClickBehaviorAndPrecedence();
    std::cout << "Application framework tests passed\n";
    return EXIT_SUCCESS;
}
