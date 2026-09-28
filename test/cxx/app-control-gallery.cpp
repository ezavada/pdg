// Interactive draw/behavior test for the PDG C++ application controls.

#include "pdg/framework.h"
#include "pdg/app/ControlAttributes.h"
#include "pdg/app/RadioButton.h"
#include "pdg/app/ListBox.h"

#include <string>
#include <cmath>

namespace {

constexpr int kWindowWidth = 960;
constexpr int kWindowHeight = 840;

enum ViewId {
    kDefaultButton = 100,
    kDisabledButton,
    kThemedButton,
    kImageButton,
    kDefaultCheckbox,
    kDisabledCheckbox,
    kThemedCheckbox,
    kDefaultRadio,
    kDisabledRadio,
    kThemedRadio,
    kDefaultScrollbar,
    kThemedScrollbar,
    kDefaultDialogButton,
    kThemedDialogButton
};

class GalleryController;

class GalleryCanvas : public pdg::View {
public:
    GalleryCanvas(pdg::Controller* controller, const pdg::Rect& area)
        : View(controller, area) {}

    void drawSelf() override;
};

class DialogLabel : public pdg::View {
public:
    DialogLabel(pdg::Controller* controller, const pdg::Rect& area, std::string text)
        : View(controller, area), mText(std::move(text)) {}

    void drawSelf() override {
        mPort->drawText(mText.c_str(), mViewArea.leftTop() + pdg::Point(12, 28),
            pdg::Attributes().textSize(17).fillColor(PDG_BLACK_COLOR));
    }

private:
    std::string mText;
};

class PreviewDialog : public pdg::Dialog {
public:
    PreviewDialog(pdg::Controller* parent, bool themed)
        : Dialog(parent, 360, 150, dialog_Standard, 1) {
        auto* label = new DialogLabel(this, getDialogRect(), themed
            ? "Custom draw routine for dialog background"
            : "Default PDG dialog background");
        addView(label, 2);

        pdg::Point buttonPoint(getDialogRect().right - 112, getDialogRect().bottom - 44);
        auto* close = new pdg::Button(this,
            pdg::Rect(buttonPoint, 90, 30), 1);
        close->setText("Close");
        addView(close, 1);
    }
};

class ScrollingGallery : public pdg::ScrollingView {
public:
    explicit ScrollingGallery(pdg::Controller* controller)
        : ScrollingView(controller,pdg::Rect(330,642,590,792),0,bind_None) {
        setViewArea(pdg::Rect(330,642,590,1002)); setRotation(.035f);
    }
    bool animate(double seconds) override {
        mTime+=seconds;
        const float top=642-60*(1-std::cos(mTime));
        setViewArea(pdg::Rect(330,top,590,top+360));
        return View::animate(seconds);
    }
    void drawSelf() override {
        for (int row=0;row<12;++row) {
            const float y=mViewArea.top+row*30;
            mPort->drawRect(pdg::Rect(300,y,620,y+30),pdg::Attributes().fillColor(
                row%2 ? pdg::Color(199,230,247) : pdg::Color(240,250,255)));
            const std::string text="Scrolling row "+std::to_string(row+1);
            mPort->drawText(text.c_str(),pdg::Point(342,y+21),pdg::Attributes().textSize(14).fillColor(pdg::Color(36,71,102)));
        }
    }
private:
    double mTime=0;
};

class AnimatedGalleryButton : public pdg::Button {
public:
    AnimatedGalleryButton(pdg::Controller* controller, const pdg::Rect& area, int id)
        : Button(controller,area,id) {
        fillColor(pdg::Color(46,125,173)).roundedCorners(4);
        setRotation(-.12f);
    }
    bool animate(double seconds) override {
        mRemaining -= seconds;
        if (mRemaining <= 0) {
            mForward = !mForward;
            mRemaining = 2;
            rotateTo(mForward ? .12f : -.12f,2);
            moveTo(pdg::Point(mForward ? 170 : 160,673),2);
            changeFillColor(mForward ? pdg::Color(117,69,184) : pdg::Color(46,125,173),2);
            changeRoundedCorners(mForward ? 18 : 4,2);
        }
        return Button::animate(seconds);
    }
private:
    double mRemaining = 0;
    bool mForward = false;
};

class GalleryController : public pdg::Controller {
public:
    explicit GalleryController(pdg::Application* app, pdg::Image* exampleImage)
        : Controller(app), mCanvas(nullptr), mUseThemedDialog(false), mClickCount(0),
          mStatus("Click any enabled control") {
        pdg::Rect area = mPort->getDrawingArea();
        mCanvas = new GalleryCanvas(this, area);
        addViewBehind(mCanvas);

        addButton(pdg::Rect(55, 125, 225, 165), kDefaultButton, "Default button", {});
        auto* disabled = addButton(pdg::Rect(55, 180, 225, 220), kDisabledButton,
            "Disabled", {});
        disabled->setEnabled(false);

        pdg::ControlAttributes themedButton;
        themedButton
            .stateDrawRoutine(pdg::ControlState::Normal, drawAccentButton)
            .stateDrawRoutine(pdg::ControlState::Hovered, drawAccentButton)
            .stateDrawRoutine(pdg::ControlState::Pressed, drawPressedAccentButton)
            .stateForeground(pdg::ControlState::Normal, PDG_WHITE_COLOR)
            .stateForeground(pdg::ControlState::Hovered, PDG_WHITE_COLOR)
            .stateForeground(pdg::ControlState::Pressed, PDG_WHITE_COLOR)
            .clickRoutine([this]() { setStatus("Custom button click routine ran"); });
        addButton(pdg::Rect(535, 125, 705, 165), kThemedButton, "Draw routine", themedButton);

        pdg::ControlAttributes imageButton;
        const pdg::ControlState states[] = {pdg::ControlState::Normal,pdg::ControlState::Hovered,
            pdg::ControlState::Pressed,pdg::ControlState::Disabled};
        const pdg::Color overlays[] = {pdg::Color(0.f,0.f,0.f,0.f),pdg::Color(1.f,.8f,.35f,.12f),
            pdg::Color(0.f,0.f,0.f,.28f),pdg::Color(.65f,.65f,.65f,.65f)};
        for (int i=0;i<4;++i) imageButton.stateImage(states[i],exampleImage)
            .stateAttributes(states[i],pdg::Attributes().fillColor(overlays[i]))
            .stateForeground(states[i],pdg::Color(255,235,179));
        addButton(pdg::Rect(730, 125, 900, 165), kImageButton, "Image state", imageButton);

        addCheckbox(pdg::Rect(55, 245, 360, 277), kDefaultCheckbox,
            "Default checkbox", {});
        auto* disabledCheckbox = addCheckbox(pdg::Rect(55, 277, 360, 309),
            kDisabledCheckbox, "Disabled checkbox", {});
        disabledCheckbox->setEnabled(false);
        pdg::ControlAttributes themedCheck;
        themedCheck
            .stateForeground(pdg::ControlState::Normal, pdg::Color(45, 68, 140))
            .stateForeground(pdg::ControlState::Selected, pdg::Color(164, 48, 92))
            .clickRoutine([this]() { setStatus("Custom checkbox toggled"); });
        addCheckbox(pdg::Rect(535, 245, 850, 277), kThemedCheckbox,
            "Override text colors", themedCheck);

        addRadio(pdg::Rect(55, 315, 370, 345), kDefaultRadio, {});
        auto* disabledRadio = addRadio(pdg::Rect(130, 355, 430, 385),
            kDisabledRadio, {});
        disabledRadio->setEnabled(false);
        pdg::ControlAttributes themedRadio;
        themedRadio
            .stateForeground(pdg::ControlState::Normal, pdg::Color(36, 94, 72))
            .stateForeground(pdg::ControlState::Selected, pdg::Color(190, 75, 30))
            .clickRoutine([this]() { setStatus("Custom radio selection changed"); });
        addRadio(pdg::Rect(535, 315, 850, 345), kThemedRadio, themedRadio);

		auto* defaultScrollbar = new pdg::Scrollbar(this, pdg::Rect(55, 402, 370, 424),
			pdg::Scrollbar::HORIZONTAL, 35, 10, 110);
		addView(defaultScrollbar, kDefaultScrollbar);
		pdg::ControlAttributes themedScrollbarAttributes;
		themedScrollbarAttributes
			.stateAttributes(pdg::ControlState::Normal,
				pdg::Attributes().fillColor(pdg::Color(224, 216, 246)))
			.stateAttributes(pdg::ControlState::Decrement,
				pdg::Attributes().fillColor(pdg::Color(136, 119, 206)).roundedCorners(4))
			.stateAttributes(pdg::ControlState::Increment,
				pdg::Attributes().fillColor(pdg::Color(136, 119, 206)).roundedCorners(4))
			.stateAttributes(pdg::ControlState::Thumb,
				pdg::Attributes().fillColor(pdg::Color(164, 48, 92)).roundedCorners(6));
		auto* themedScrollbar = new pdg::Scrollbar(this, pdg::Rect(535, 402, 850, 424),
			pdg::Scrollbar::HORIZONTAL, 65, 10, 110);
		themedScrollbar->setAttributes(themedScrollbarAttributes);
		addView(themedScrollbar, kThemedScrollbar);

		addButton(pdg::Rect(55, 447, 255, 487), kDefaultDialogButton,
            "Open default dialog", {});
		addButton(pdg::Rect(535, 447, 735, 487), kThemedDialogButton,
            "Open themed dialog", themedButton);
        auto* animated = new AnimatedGalleryButton(this,pdg::Rect(55,654,265,692),200);
        animated->setText("Animated - click me");
        addView(animated,200);
        addButton(pdg::Rect(55,727,265,765),201,"Reflected - click me",{})->setFlipX(true);
        addView(new ScrollingGallery(this),202);
        auto* list=new pdg::ListBox(this,pdg::Rect(640,650,895,780),6,PDG_WHITE_COLOR,pdg::Color(178,214,255));
        for (const char* text : {"Alpha","Bravo","Charlie","Delta","Echo","Foxtrot","Golf","Hotel"})
            list->addToList(text,PDG_BLACK_COLOR);
        addView(list,203);
        // Keep the scrollbar after its owner for front-to-back input routing.
        list->setRotation(-.035f).resizeTo(230,list->getHeight(),1,pdg::linearTween);
    }

    pdg::ControlAttributes getControlAttributes(pdg::ControlType type) override {
        pdg::ControlAttributes attributes;
        if (mUseThemedDialog && type == pdg::ControlType::Dialog) {
            attributes.stateDrawRoutine(pdg::ControlState::Normal,
                [](pdg::Port& port, const pdg::Rect& area,
                   const pdg::ControlStateAttributes&) {
                    port.drawRect(pdg::Rect(area).shrink(2.5f), pdg::Attributes()
                        .fillGradient(area.leftTop(), pdg::Color(244, 236, 255),
                                      area.rightBottom(), pdg::Color(178, 211, 255))
                        .lineStyle(pdg::lineStyle_Solid).lineColor(pdg::Color(74, 57, 145)).lineThickness(5).roundedCorners(12));
                });
        }
        return attributes;
    }

    bool doLeftClick(const pdg::MouseInfo* mi, pdg::View* view, int id, int part) override {
        bool handled = Controller::doLeftClick(mi, view, id, part);
        if (id == kDefaultDialogButton || id == kThemedDialogButton) {
            mUseThemedDialog = id == kThemedDialogButton;
            new PreviewDialog(this, mUseThemedDialog);
            mUseThemedDialog = false;
            return true;
        }
        if (handled) {
            ++mClickCount;
            if (id == kDefaultButton) setStatus("Default button clicked");
            else if (id == kImageButton) setStatus("Image-backed button clicked");
            else if (id == kDefaultCheckbox) setStatus("Default checkbox toggled");
            else if (id == kDefaultRadio) setStatus("Default radio selection changed");
        }
        return handled;
    }

    const std::string& status() const { return mStatus; }
    int clickCount() const { return mClickCount; }

private:
    static void drawAccentButton(pdg::Port& port, const pdg::Rect& area,
                                 const pdg::ControlStateAttributes&) {
        port.drawRect(pdg::Rect(area).shrink(1), pdg::Attributes()
            .fillGradient(area.leftTop(), pdg::Color(94, 86, 220),
                          area.rightBottom(), pdg::Color(38, 167, 190))
            .lineStyle(pdg::lineStyle_Solid).lineColor(pdg::Color(30, 30, 80)).lineThickness(2).roundedCorners(10));
    }

    static void drawPressedAccentButton(pdg::Port& port, const pdg::Rect& area,
                                        const pdg::ControlStateAttributes&) {
        port.drawRect(pdg::Rect(area).shrink(1), pdg::Attributes().fillColor(pdg::Color(42, 83, 135))
            .lineStyle(pdg::lineStyle_Solid).lineColor(PDG_WHITE_COLOR).lineThickness(2).roundedCorners(10));
    }

    pdg::Button* addButton(const pdg::Rect& rect, int id, const char* text,
                           const pdg::ControlAttributes& attributes) {
        auto* button = new pdg::Button(this, rect, id);
        button->setText(text);
        button->setAttributes(attributes);
        button->setWantsMouseOvers(true);
        addView(button, id);
        return button;
    }

    pdg::Checkbox* addCheckbox(const pdg::Rect& rect, int id, const char* text,
                               const pdg::ControlAttributes& attributes) {
        auto* checkbox = new pdg::Checkbox(this, rect);
        checkbox->setString(text);
        checkbox->setAttributes(attributes);
        addView(checkbox, id);
        return checkbox;
    }

    pdg::RadioButton* addRadio(const pdg::Rect& rect, int id,
                               const pdg::ControlAttributes& attributes) {
        auto* radio = new pdg::RadioButton(this, rect, -1, 3);
        radio->setString(0, "One");
        radio->setString(1, "Two");
        radio->setString(2, "Three");
        radio->setAttributes(attributes);
        addView(radio, id);
        return radio;
    }

    void setStatus(const char* status) {
        mStatus = status;
        if (mCanvas) mCanvas->draw();
    }

    GalleryCanvas* mCanvas;
    bool mUseThemedDialog;
    int mClickCount;
    std::string mStatus;
};

void GalleryCanvas::drawSelf() {
    auto* gallery = static_cast<GalleryController*>(mController);
    mPort->drawRect(mViewArea, pdg::Attributes().fillColor(pdg::Color(238, 241, 246)));
    mPort->drawText("PDG C++ App Framework Control Gallery", pdg::Point(40, 48),
        pdg::Attributes().textSize(25).textStyle(pdg::textStyle_Bold).fillColor(pdg::Color(30, 38, 55)));
    mPort->drawText("Hover, press, click, toggle, and open both dialogs.", pdg::Point(40, 76),
        pdg::Attributes().textSize(14).fillColor(pdg::Color(70, 78, 92)));

    pdg::Rect defaultPanel(30, 92, 450, 500);
    pdg::Rect overridePanel(510, 92, 930, 500);
    mPort->drawRect(defaultPanel, pdg::Attributes().fillColor(PDG_WHITE_COLOR)
        .lineStyle(pdg::lineStyle_Solid).lineColor(pdg::Color(185, 191, 202)).roundedCorners(10));
    mPort->drawRect(overridePanel, pdg::Attributes().fillColor(pdg::Color(250, 248, 255))
        .lineStyle(pdg::lineStyle_Solid).lineColor(pdg::Color(124, 109, 180)).lineThickness(2).roundedCorners(10));
    mPort->drawText("Built-in defaults", pdg::Point(50, 116),
        pdg::Attributes().textSize(17).textStyle(pdg::textStyle_Bold).fillColor(pdg::Color(45, 52, 66)));
    mPort->drawText("Per-control overrides", pdg::Point(530, 116),
        pdg::Attributes().textSize(17).textStyle(pdg::textStyle_Bold).fillColor(pdg::Color(74, 57, 145)));
    mPort->drawText("Disabled:", pdg::Point(55, 375),
        pdg::Attributes().textSize(13).fillColor(pdg::Color(100, 106, 116)));

    std::string status = "Behavior: " + gallery->status() + "   |   handled clicks: "
        + std::to_string(gallery->clickCount());
    mPort->drawRect(pdg::Rect(30, 525, 930, 590), pdg::Attributes()
        .fillColor(pdg::Color(32, 39, 54)).roundedCorners(8));
    mPort->drawText(status.c_str(), pdg::Point(50, 557),
        pdg::Attributes().textSize(16).fillColor(PDG_WHITE_COLOR));
    mPort->drawText("Live appearance / transforms      Clipped scrolling      Composite list",
        pdg::Point(50,622),pdg::Attributes().textSize(16).fillColor(pdg::Color(50,60,80)));
    mPort->drawText("Overrides demonstrated: state colors, image, custom draw routine, click routine.",
        pdg::Point(50, 580), pdg::Attributes().textSize(12).fillColor(pdg::Color(190, 203, 225)));
}

class GalleryApplication : public pdg::Application {
public:
    GalleryApplication() : mController(nullptr), mExampleImage(nullptr) {}

    void initialize(int argc, const char** argv) override {
        (void)argc;
        (void)argv;
        const std::string resourceImage =
            std::string(pdg::OS::getApplicationResourceDirectory()) + "wood-brass-button.png";
        const std::string paths[] = {
            resourceImage,
            "test/data/wood-brass-button.png",
            "../test/data/wood-brass-button.png",
            "../../../../test/data/wood-brass-button.png",
            "wood-brass-button.png"
        };
        for (const std::string& path : paths) {
            try {
                mExampleImage = pdg::Image::createImageFromFile(path.c_str());
                if (mExampleImage) break;
            } catch (...) {}
        }
        mController = new GalleryController(this, mExampleImage);
    }

    void cleanup() override {
        delete mController;
        mController = nullptr;
        if (mExampleImage) {
            mExampleImage->release();
            mExampleImage = nullptr;
        }
    }

private:
    GalleryController* mController;
    pdg::Image* mExampleImage;
};

} // namespace

namespace pdg {

bool Initializer::allowHorizontalOrientation() throw() { return true; }
bool Initializer::allowVerticalOrientation() throw() { return true; }
const char* Initializer::getAppName(bool) throw() { return "PDG Control Gallery"; }
const char* Initializer::getMainResourceFileName() throw() { return nullptr; }

bool Initializer::installGlobalHandlers() throw() {
    new GalleryApplication();
    return true;
}

bool Initializer::getGraphicsEnvironmentDimensions(Rect, Rect, long& width, long& height,
                                                    uint8& depth) throw() {
    width = kWindowWidth;
    height = kWindowHeight;
    depth = 32;
    return false;
}

} // namespace pdg
