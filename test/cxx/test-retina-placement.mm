// Read actual native framebuffer pixels on both regular and Retina displays.
#import <AppKit/AppKit.h>
#include "graphics-opengl.h"
#include "internals.h"
#include "glfw/internals-glfw.h"
#include "pdg-main.h"
#include "pdg/sys/initializer.h"
#include "pdg/sys/attributes.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <stdexcept>
#include <vector>

namespace {
void expect(bool ok, const char* message) {
    if (!ok) throw std::runtime_error(message);
}
void checkWindow(NSPoint position, bool retina) {
    using namespace pdg;
    auto& manager = GraphicsManager::instance();
    auto* port = static_cast<pdg::PortImpl*>(manager.createWindowPort(pdg::Rect(64, 48), "PDG placement test"));
    platform_destroyWindow(port->mPlatformWindowRef);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, retina ? GLFW_TRUE : GLFW_FALSE);
    auto* window = glfwCreateWindow(64, 48, "PDG placement test", nullptr, nullptr);
    expect(window != nullptr, "native window created");
    port->mPlatformWindowRef = window;
    glfwSetWindowPos(window, position.x, position.y);
    glfwMakeContextCurrent(window);
    glfwPollEvents();
    long width, height, drawableWidth, drawableHeight;
    platform_getWindowContentSize(window, &width, &height);
    platform_getWindowDrawableSize(window, &drawableWidth, &drawableHeight);
    expect(width == 64 && height == 48, "port content dimensions stay in window coordinates");
    handle_framebuffersize_callback(window, drawableWidth, drawableHeight);
    expect(port->getDrawingArea().width() == 64 && port->getDrawingArea().height() == 48,
        "framebuffer resize does not move logical drawing coordinates");
    graphics_startDrawing(port);
    GLint viewport[4]; glGetIntegerv(GL_VIEWPORT, viewport);
    expect(viewport[2] == drawableWidth && viewport[3] == drawableHeight, "viewport covers entire drawable");
    const int scale = retina ? 2 : 1;
    expect(drawableWidth == width * scale && drawableHeight == height * scale, "expected display backing scale exercised");
    auto pixels = [&] {
        graphics_flushText();
        std::vector<unsigned char> data(drawableWidth * drawableHeight * 4);
        glReadPixels(0, 0, drawableWidth, drawableHeight, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
        return data;
    };
    Attributes red; red.fillColor(PDG_RED_COLOR).lineOpacity(0);
    std::vector<unsigned char> data;
    for (auto clip : {pdg::Rect(24, 18, 36, 28), pdg::Rect(24.5f, 18.5f, 36.5f, 28.5f)}) {
        graphics_startDrawing(port);
        port->setClipRect(clip);
        port->drawRect(pdg::Rect(20, 16, 40, 32), red);
        auto actual = pixels();
        for (int y = 0; y < drawableHeight; ++y) for (int x = 0; x < drawableWidth; ++x) {
            const float logicalX = (x + .5f) / scale;
            const float logicalY = (drawableHeight - y - .5f) / scale;
            const bool inside = logicalX >= clip.left && logicalX < clip.right
                && logicalY >= clip.top && logicalY < clip.bottom;
            expect((actual[(y * drawableWidth + x) * 4] > 200) == inside,
                "rectangle and fractional clip occupy requested framebuffer coordinates");
        }
        if (clip.left == 24) data = std::move(actual);
    }
    // Nonzero port origins must not introduce a second offset into clipping.
    port->setPortRects(pdg::Rect(10, 20, 74, 68));
    port->setClipRect(pdg::Rect(34, 38, 46, 48));
    graphics_startDrawing(port);
    port->drawRect(pdg::Rect(30, 36, 50, 52), red);
    expect(pixels() == data, "translated port origin preserves local drawing and clipping placement");
    port->setPortRects(pdg::Rect(64, 48));
    graphics_startDrawing(port);
    Attributes white; white.textSize(12).fillColor(PDG_WHITE_COLOR);
    port->drawText("MM", pdg::Point(20, 30), white);
    data = pixels();
    int count = 0;
    for (int y = 0; y < drawableHeight; ++y) for (int x = 0; x < drawableWidth; ++x) {
        if (data[(y * drawableWidth + x) * 4] > 80) {
            ++count;
            expect(x >= 19 * scale && x < 45 * scale && y >= 17 * scale && y < 34 * scale,
                "text appears around the requested baseline");
        }
    }
    expect(count > 20 * scale, "text rendered into requested region");
    auto* font = static_cast<pdg::FontImpl*>(port->getCurrentFont());
    auto* first = port->getTextFromCache("MM", 2, font, 12, 0);
    expect(first->atlas != nullptr, "short text uses an atlas page");
    port->drawText("Hi", pdg::Point(40, 30), white);
    auto* second = port->getTextFromCache("Hi", 2, font, 12, 0);
    expect(second->atlas == first->atlas, "different labels share a texture page");
    graphics_startDrawing(port);
    Attributes green; green.textSize(12).fillColor(PDG_GREEN_COLOR);
    Attributes blue; blue.fillColor(PDG_BLUE_COLOR).lineStyle(lineStyle_None);
    Attributes redText; redText.textSize(12).fillColor(PDG_RED_COLOR);
    port->drawText("MM", pdg::Point(20, 30), redText);
    port->drawRect(port->getDrawingArea(), blue);
    port->drawText("MM", pdg::Point(20, 30), green);
    data = pixels();
    int greenPixels = 0;
    for (size_t offset = 0; offset < data.size(); offset += 4) {
        expect(data[offset] == 0, "shape drawn after text covers the earlier label");
        greenPixels += data[offset + 1] > 80;
    }
    expect(greenPixels > 20 * scale, "text drawn after shape remains visible");
    // Numeric glyph reuse must keep alignment and remain close to the full
    // platform raster, including its fractional advances and antialiasing.
    for (const char* label : {"012345", "Score 123"}) {
        graphics_startDrawing(port);
        port->mDigitCacheEnabled = true;
        port->drawText(label, pdg::Point(4, 30), white);
        auto segmented = pixels();
        const int length = std::strlen(label);
        auto* numeric = port->getTextFromCache(label, length, font, 12, 0);
        expect(numeric->texture == 0, "new numeric label reuses glyph masks without allocating a whole raster");
        const int labelWidth = port->getTextWidth(label, 12, 0);
        const pdg::Rect bounds(4, 30 - std::ceil(font->getFontAscent(12)),
            4 + labelWidth, 30 + std::ceil(font->getFontDescent(12)));
        graphics_startDrawing(port);
        graphics_drawTextRaster(*port, label, length, pdg::Quad(bounds), 12, 0, PDG_WHITE_COLOR);
        auto reference = pixels();
        double error = 0;
        for (size_t offset = 0; offset < reference.size(); offset += 4)
            error += std::abs(int(reference[offset]) - int(segmented[offset]));
        expect(error / (255.0 * drawableWidth * drawableHeight) < .025,
            "numeric glyph masks retain platform raster placement and antialiasing");
        expect(port->getTextWidth(label, 12, 0) == labelWidth, "numeric reuse preserves exact measured width");
        expect(numeric->texture != 0, "repeated label can use a single whole-string raster");
    }
    port->mTextChurnFrames = 0;
    port->mTextLabelsDrawn = port->mNewTextLabels = 0;
    for (int frame = 0; frame < 4; ++frame) {
        graphics_startDrawing(port);
        expect(!port->mDigitCacheEnabled, "stable labels preserve original atlas allocation order");
        port->drawText("Stable 999", pdg::Point(4, 30), white);
    }
    port->mTextChurnFrames = 0;
    port->mTextLabelsDrawn = port->mNewTextLabels = 0;
    for (int frame = 0; frame < 3; ++frame) {
        graphics_startDrawing(port);
        const auto label = std::string("N ") + std::to_string(900 + frame);
        port->drawText(label.c_str(), pdg::Point(4, 30), white);
    }
    expect(port->mDigitCacheEnabled, "sustained changing labels enable digit reuse");
    expect(port->getTextFromCache("N 902", 5, font, 12, 0)->texture == 0,
        "changing counter uses existing glyph masks");
    for (int frame = 0; frame < 3; ++frame) {
        graphics_startDrawing(port);
        port->drawText("N 902", pdg::Point(4, 30), white);
    }
    expect(!port->mDigitCacheEnabled, "returning to stable labels disables digit segmentation");
    // Exercise GPU page eviction, rather than just synthetic LRU bookkeeping.
    Attributes large; large.textSize(32).textStyle(textStyle_Italic).fillColor(PDG_WHITE_COLOR);
    for (int i = 0; i < 5000; ++i) {
        const auto label = std::string("atlas ") + std::to_string(i);
        port->drawText(label.c_str(), pdg::Point(0, 35), large);
    }
    graphics_flushText();
    expect(port->mTextCache.bytes() <= 16 * 1024 * 1024 && port->mTextCache.count() <= 4096,
        "GPU text atlas stays within cache limits after changing thousands of labels");
    graphics_startDrawing(port);
    port->drawText("MM", pdg::Point(20, 30), white);
    data = pixels();
    count = 0;
    for (int y = 0; y < drawableHeight; ++y) for (int x = 0; x < drawableWidth; ++x) {
        if (data[(y * drawableWidth + x) * 4] > 80) {
            ++count;
            expect(x >= 19 * scale && x < 45 * scale && y >= 17 * scale && y < 34 * scale,
                "text placement survives atlas eviction and reupload");
        }
    }
    expect(count > 20 * scale, "evicted label renders correctly when reused");
    std::cout << "Placement passed at " << scale << "x (" << drawableWidth << "x" << drawableHeight << ")\n";
    manager.closeGraphicsPort(port);
    glfwDefaultWindowHints();
}
}
namespace pdg {
bool Initializer::allowHorizontalOrientation() throw() { return true; }
bool Initializer::allowVerticalOrientation() throw() { return true; }
const char* Initializer::getAppName(bool) throw() { return "PDG Placement Tests"; }
const char* Initializer::getMainResourceFileName() throw() { return nullptr; }
bool Initializer::installGlobalHandlers() throw() { return false; }
bool Initializer::getGraphicsEnvironmentDimensions(Rect, Rect, long& width, long& height, uint8& depth) throw() {
    width = height = 1; depth = 32; return false;
}
}
int main() { @autoreleasepool {
    try {
        expect(pdg::main_initManagers() == 0, "managers initialized");
        bool testedRetina = false;
        const CGFloat desktopTop = NSMaxY([[NSScreen screens] firstObject].frame);
        for (NSScreen* screen in [NSScreen screens]) {
            if (screen.backingScaleFactor == 2) {
                checkWindow(NSMakePoint(screen.frame.origin.x + 50, desktopTop - NSMaxY(screen.frame) + 100), true);
                testedRetina = true;
                break;
            }
        }
        checkWindow(NSMakePoint(50, 100), false);
        if (!testedRetina) std::cout << "No 2x Retina display attached; 1x placement checked only\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
} }
