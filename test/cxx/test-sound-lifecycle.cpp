// Exercise macOS sound ownership/list mutation without requiring an audio device.
#include "macosx/sound-macosx.h"
#include "macosx/sound-mgr-macosx.h"
#include "pdg/sys/initializer.h"
#include "pdg/sys/os.h"
#include <chrono>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <utility>

namespace {
int checks = 0;
void expect(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
struct Manager : pdg::SoundManagerMac {
    size_t active() const { return mSounds.size(); }
};
struct Sound : pdg::SoundMac {
    int& destroyed;
    std::function<void()> afterStop;
    Sound(Manager& manager, int& destroyedCount)
        : SoundMac(&manager, "wav"), destroyed(destroyedCount) {}
    ~Sound() override { ++destroyed; }
    void expire() {
        mPlaying = true;
        mDieAt = 1;
        mSndMgr->soundPlaying(this);
    }
    void stop() override {
        const auto callback = std::exchange(afterStop, {});
        SoundMac::stop();
        if (callback) callback();
    }
};
void completion() {
    int destroyed = 0;
    Manager manager;
    for (int i = 0; i < 3; ++i) (new Sound(manager, destroyed))->expire();
    manager.idle();
    expect(manager.active() == 0, "completion removes every sound, including the last entry");
    expect(destroyed == 3, "manager-only sounds are released after idle finishes");
    manager.idle();
    expect(destroyed == 3, "an empty subsequent pass does not reuse erased entries");
}
void mutations() {
    int destroyed = 0;
    Manager manager;
    auto* first = new Sound(manager, destroyed);
    auto* second = new Sound(manager, destroyed);
    auto* third = new Sound(manager, destroyed);
    first->expire(); second->expire(); third->expire();
    first->afterStop = [&] {
        second->stop();
        (new Sound(manager, destroyed))->expire();
    };
    manager.idle();
    expect(destroyed == 3 && manager.active() == 1,
        "stopping a peer and adding a sound cannot invalidate the current pass");
    manager.idle();
    expect(destroyed == 4 && manager.active() == 0, "new playback is processed on the following pass");
}
void externalOwner() {
    int destroyed = 0;
    Manager manager;
    auto* sound = new Sound(manager, destroyed);
    sound->addRef();
    sound->expire();
    manager.soundPlaying(sound);
    expect(manager.active() == 1, "repeated registration does not duplicate ownership");
    manager.idle();
    expect(destroyed == 0 && manager.active() == 0, "stopping preserves the caller's reference");
    sound->expire();
    manager.idle();
    expect(destroyed == 0, "a retained sound can be replayed after completion");
    sound->release();
    expect(destroyed == 1, "the last owner releases the native sound");
}
}
namespace pdg {
bool Initializer::allowHorizontalOrientation() noexcept { return true; }
bool Initializer::allowVerticalOrientation() noexcept { return true; }
const char* Initializer::getAppName(bool) noexcept { return "PDG Sound Lifecycle Tests"; }
const char* Initializer::getMainResourceFileName() noexcept { return nullptr; }
bool Initializer::installGlobalHandlers() noexcept { return false; }
bool Initializer::getGraphicsEnvironmentDimensions(Rect, Rect, long& width, long& height, uint8& depth) noexcept {
    width = height = 1; depth = 32; return false;
}
}
int main() {
    try {
        pdg::OS::getMilliseconds();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        completion(); mutations(); externalOwner();
        std::cout << "Sound lifecycle: " << checks << " checks passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
