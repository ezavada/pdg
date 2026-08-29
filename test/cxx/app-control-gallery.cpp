// Interactive draw/behavior test for the PDG C++ application controls.

#include "pdg/framework.h"
#include "pdg/app/ControlAttributes.h"
#include "pdg/app/RadioButton.h"

#include <string>

namespace {

constexpr int kWindowWidth = 960;
constexpr int kWindowHeight = 640;

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
        if (exampleImage) imageButton.stateImage(pdg::ControlState::Normal, exampleImage);
        imageButton.stateForeground(pdg::ControlState::Normal, PDG_WHITE_COLOR);
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
    }

    pdg::ControlAttributes getControlAttributes(pdg::ControlType type) override {
        pdg::ControlAttributes attributes;
        if (mUseThemedDialog && type == pdg::ControlType::Dialog) {
            attributes.stateDrawRoutine(pdg::ControlState::Normal,
                [](pdg::Port& port, const pdg::Rect& area,
                   const pdg::ControlStateAttributes&) {
                    port.drawRect(area, pdg::Attributes()
                        .fillGradient(area.leftTop(), pdg::Color(244, 236, 255),
                                      area.rightBottom(), pdg::Color(178, 211, 255))
                        .lineColor(pdg::Color(74, 57, 145)).lineThickness(5).roundedCorners(12));
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
        port.drawRect(area, pdg::Attributes()
            .fillGradient(area.leftTop(), pdg::Color(94, 86, 220),
                          area.rightBottom(), pdg::Color(38, 167, 190))
            .lineColor(pdg::Color(30, 30, 80)).lineThickness(2).roundedCorners(10));
    }

    static void drawPressedAccentButton(pdg::Port& port, const pdg::Rect& area,
                                        const pdg::ControlStateAttributes&) {
        port.drawRect(area, pdg::Attributes().fillColor(pdg::Color(42, 83, 135))
            .lineColor(PDG_WHITE_COLOR).lineThickness(2).roundedCorners(10));
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
        .lineColor(pdg::Color(185, 191, 202)).roundedCorners(10));
    mPort->drawRect(overridePanel, pdg::Attributes().fillColor(pdg::Color(250, 248, 255))
        .lineColor(pdg::Color(124, 109, 180)).lineThickness(2).roundedCorners(10));
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
            std::string(pdg::OS::getApplicationResourceDirectory()) + "yinyang.png";
        const std::string paths[] = {
            resourceImage,
            "test/data/yinyang.png",
            "../test/data/yinyang.png",
            "../../../../test/data/yinyang.png",
            "yinyang.png"
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
