// -----------------------------------------------
// ControlAttributes.cpp
// -----------------------------------------------

#include "pdg/app/ControlAttributes.h"
#include "pdg/sys/port.h"
#include "pdg/sys/sound.h"

#include <utility>

namespace pdg {

ControlStateAttributes& ControlStateAttributes::drawAttributes(const Attributes& value) {
    drawing = value;
    hasDrawing = true;
    return *this;
}

ControlStateAttributes& ControlStateAttributes::backgroundImage(Image* value) {
    image = value;
    hasImage = true;
    return *this;
}

ControlStateAttributes& ControlStateAttributes::foregroundColor(const Color& value) {
    foreground = value;
    hasForeground = true;
    return *this;
}

ControlStateAttributes& ControlStateAttributes::customDraw(DrawRoutine value) {
    drawRoutine = std::move(value);
    hasDrawRoutine = true;
    return *this;
}

void ControlStateAttributes::merge(const ControlStateAttributes& overrides) {
    // Images, draw routines, and simple drawing attributes are alternative
    // background sources. An image-only override must replace a lower-level
    // fallback drawing or that drawing will be composited over the image.
    if (overrides.hasDrawRoutine) {
        drawRoutine = overrides.drawRoutine;
        hasDrawRoutine = true;
        image = nullptr;
        hasImage = false;
        drawing = Attributes();
        hasDrawing = false;
    } else if (overrides.hasImage) {
        backgroundImage(overrides.image);
        drawRoutine = DrawRoutine();
        hasDrawRoutine = false;
        if (!overrides.hasDrawing) {
            drawing = Attributes();
            hasDrawing = false;
        }
    } else if (overrides.hasDrawing) {
        drawAttributes(overrides.drawing);
        image = nullptr;
        hasImage = false;
        drawRoutine = DrawRoutine();
        hasDrawRoutine = false;
    }
    if (overrides.hasDrawing && (overrides.hasImage || overrides.hasDrawRoutine)) {
        drawAttributes(overrides.drawing);
    }
    if (overrides.hasForeground) foregroundColor(overrides.foreground);
}

ControlStateAttributes& ControlAttributes::state(ControlState value) {
    return mStates[stateIndex(value)];
}

const ControlStateAttributes& ControlAttributes::state(ControlState value) const {
    return mStates[stateIndex(value)];
}

ControlAttributes& ControlAttributes::stateAttributes(ControlState value, const Attributes& attributes) {
    state(value).drawAttributes(attributes);
    return *this;
}

ControlAttributes& ControlAttributes::stateImage(ControlState value, Image* image) {
    state(value).backgroundImage(image);
    return *this;
}

ControlAttributes& ControlAttributes::stateForeground(ControlState value, const Color& color) {
    state(value).foregroundColor(color);
    return *this;
}

ControlAttributes& ControlAttributes::stateDrawRoutine(ControlState value, ControlStateAttributes::DrawRoutine routine) {
    state(value).customDraw(std::move(routine));
    return *this;
}

ControlAttributes& ControlAttributes::clickSound(Sound* sound, float volume) {
    mClickSound = sound;
    mClickVolume = volume;
    mHasClickSound = true;
    return *this;
}

ControlAttributes& ControlAttributes::clickRoutine(ClickRoutine routine) {
    mClickRoutine = std::move(routine);
    mHasClickRoutine = true;
    return *this;
}

void ControlAttributes::merge(const ControlAttributes& overrides) {
    for (size_t i = 0; i < mStates.size(); ++i) {
        mStates[i].merge(overrides.mStates[i]);
    }
    if (overrides.mHasClickSound) {
        clickSound(overrides.mClickSound, overrides.mClickVolume);
    }
    if (overrides.mHasClickRoutine) {
        clickRoutine(overrides.mClickRoutine);
    }
}

void ControlAttributes::draw(Port& port, const Rect& area, ControlState value) const {
    const ControlStateAttributes* selected = &state(value);
    const ControlStateAttributes& normal = state(ControlState::Normal);
    if (selected->hasDrawRoutine && selected->drawRoutine) {
        selected->drawRoutine(port, area, *selected);
    } else if (selected->hasImage && selected->image) {
        port.drawImage(selected->image, area, selected->hasDrawing ? selected->drawing : Attributes());
    } else if (selected->hasDrawing) {
        port.drawRect(area, selected->drawing);
    } else if (selected != &normal) {
        if (normal.hasDrawRoutine && normal.drawRoutine) {
            normal.drawRoutine(port, area, normal);
        } else if (normal.hasImage && normal.image) {
            port.drawImage(normal.image, area, normal.hasDrawing ? normal.drawing : Attributes());
        } else if (normal.hasDrawing) {
            port.drawRect(area, normal.drawing);
        }
    }
}

void ControlAttributes::playClick() const {
    if (mHasClickRoutine && mClickRoutine) {
        mClickRoutine();
    } else if (mHasClickSound && mClickSound) {
#ifndef PDG_NO_SOUND
        mClickSound->play(mClickVolume);
#endif
    }
}

} // namespace pdg
