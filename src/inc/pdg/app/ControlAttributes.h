// -----------------------------------------------
// ControlAttributes.h
//
// Application-control styling and behavior
// -----------------------------------------------

#ifndef PDG_CONTROL_ATTRIBUTES_H_INCLUDED
#define PDG_CONTROL_ATTRIBUTES_H_INCLUDED

#include "pdg/sys/attributes.h"

#include <array>
#include <functional>

namespace pdg {

class Port;
class Sound;

enum class ControlState {
    Normal,
    Hovered,
    Pressed,
    Disabled,
    Selected,
    SelectedDisabled,
    Decrement,
    DecrementPressed,
    Increment,
    IncrementPressed,
    Thumb,
    Count
};

enum class ControlType {
    Dialog,
    Button,
    Checkbox,
    RadioButton,
    Scrollbar,
    Other
};

struct ControlStateAttributes {
    using DrawRoutine = std::function<void(Port&, const Rect&, const ControlStateAttributes&)>;

    Attributes drawing;
    Image* image = nullptr;       // not owned
    Color foreground = PDG_BLACK_COLOR;
    DrawRoutine drawRoutine;
    bool hasDrawing = false;
    bool hasImage = false;
    bool hasForeground = false;
    bool hasDrawRoutine = false;

    ControlStateAttributes& drawAttributes(const Attributes& value);
    ControlStateAttributes& backgroundImage(Image* value);
    ControlStateAttributes& foregroundColor(const Color& value);
    ControlStateAttributes& customDraw(DrawRoutine value);
    void merge(const ControlStateAttributes& overrides);
};

// A control starts with its built-in defaults and merges the attributes
// supplied by its controller. This lets an application theme controls without
// subclassing them or adding application-specific code to PDG.
class ControlAttributes {
public:
    using ClickRoutine = std::function<void()>;

    ControlStateAttributes& state(ControlState value);
    const ControlStateAttributes& state(ControlState value) const;
    ControlAttributes& stateAttributes(ControlState state, const Attributes& value);
    ControlAttributes& stateImage(ControlState state, Image* value);
    ControlAttributes& stateForeground(ControlState state, const Color& value);
    ControlAttributes& stateDrawRoutine(ControlState state, ControlStateAttributes::DrawRoutine value);
    ControlAttributes& clickSound(Sound* value, float volume = 1.0f);
    ControlAttributes& clickRoutine(ClickRoutine value);

    Sound* getClickSound() const { return mClickSound; }
    float getClickVolume() const { return mClickVolume; }
    bool hasClickSound() const { return mHasClickSound; }
    bool hasClickRoutine() const { return mHasClickRoutine; }

    void merge(const ControlAttributes& overrides);
    void draw(Port& port, const Rect& area, ControlState state) const;
    void playClick() const;

private:
    static constexpr size_t stateIndex(ControlState value) {
        return static_cast<size_t>(value);
    }

    std::array<ControlStateAttributes, static_cast<size_t>(ControlState::Count)> mStates;
    Sound* mClickSound = nullptr;  // not owned
    float mClickVolume = 1.0f;
    ClickRoutine mClickRoutine;
    bool mHasClickSound = false;
    bool mHasClickRoutine = false;
};

} // namespace pdg

#endif // PDG_CONTROL_ATTRIBUTES_H_INCLUDED
