#ifndef PDG_ANIMATION_RECORDER_H_INCLUDED
#define PDG_ANIMATION_RECORDER_H_INCLUDED
#include "pdg/sys/animated.h"
#include "pdg/sys/camera.h"
#include "pdg/sys/sprite.h"
#include "pdg/sys/animationphysics.h"
namespace pdg {
// Keep composite options from retaining dangling Sprite pointers between recording
// and playback. Other object arguments use the same native weak identity handles.
inline std::any captureRecorderMatchOptions(CameraMatchOptions options) {
    auto source = captureAnimationObject(options.matchSource);
    auto target = captureAnimationObject(options.matchTarget);
    options.matchSource = nullptr;
    options.matchTarget = nullptr;
    return AnimationResolvedArgument{[options, source, target]() mutable -> std::any {
        options.matchSource = dynamic_cast<Sprite*>(source.get());
        options.matchTarget = dynamic_cast<Sprite*>(target.get());
        if (!options.matchSource || !options.matchTarget) throw std::bad_any_cast();
        return options;
    }, {}};
}
// Shared native dispatch for script-language command recorders. Decode all
// arguments before appending a command, so invalid input never edits the graph.
template<class Reader>
void recordScriptCommand(AnimatedBase& target, int id, int count, const Reader& read) {
#include "pdg/sys/animation-recorder-dispatch.inc"
}
}
#endif
