#include "pdg_project.h"

#include "pdg/sys/sound.h"
#include "pdg-lib.h"

#include <emscripten.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

namespace pdg {

MemStats gSoundStats;

EM_JS(int, pdg_audio_create, (const char* data, int length, const char* mime), {
    if (typeof Audio === 'undefined' || typeof Blob === 'undefined' ||
        typeof URL === 'undefined') return 0;
    Module.pdgAudioObjects = Module.pdgAudioObjects || new Map();
    Module.pdgNextAudioId = (Module.pdgNextAudioId || 0) + 1;
    var bytes = HEAPU8.slice(data, data + length);
    var url = URL.createObjectURL(new Blob([bytes], { type: UTF8ToString(mime) }));
    var audio = new Audio(url);
    audio.preload = 'auto';
    Module.pdgAudioObjects.set(Module.pdgNextAudioId, { audio: audio, url: url, stopTimer: 0 });
    return Module.pdgNextAudioId;
});

EM_JS(void, pdg_audio_destroy, (int id), {
    var objects = Module.pdgAudioObjects;
    var entry = objects && objects.get(id);
    if (!entry) return;
    if (entry.stopTimer) clearTimeout(entry.stopTimer);
    entry.audio.pause();
    entry.audio.removeAttribute('src');
    entry.audio.load();
    URL.revokeObjectURL(entry.url);
    objects.delete(id);
});

EM_JS(void, pdg_audio_play, (int id, double fromSeconds, double lengthSeconds), {
    var entry = Module.pdgAudioObjects && Module.pdgAudioObjects.get(id);
    if (!entry) return;
    if (entry.stopTimer) clearTimeout(entry.stopTimer);
    try { entry.audio.currentTime = Math.max(0, fromSeconds); } catch (_) {}
    var promise = entry.audio.play();
    if (promise && promise.catch) promise.catch(function() {});
    if (lengthSeconds >= 0) {
        entry.stopTimer = setTimeout(function() { entry.audio.pause(); }, lengthSeconds * 1000);
    }
});

EM_JS(void, pdg_audio_stop, (int id, int rewind), {
    var entry = Module.pdgAudioObjects && Module.pdgAudioObjects.get(id);
    if (!entry) return;
    if (entry.stopTimer) clearTimeout(entry.stopTimer);
    entry.audio.pause();
    if (rewind) try { entry.audio.currentTime = 0; } catch (_) {}
});

EM_JS(void, pdg_audio_resume, (int id), {
    var entry = Module.pdgAudioObjects && Module.pdgAudioObjects.get(id);
    if (!entry) return;
    var promise = entry.audio.play();
    if (promise && promise.catch) promise.catch(function() {});
});

EM_JS(void, pdg_audio_set_loop, (int id, int loop), {
    var entry = Module.pdgAudioObjects && Module.pdgAudioObjects.get(id);
    if (entry) entry.audio.loop = !!loop;
});

EM_JS(void, pdg_audio_set_volume, (int id, double volume), {
    var entry = Module.pdgAudioObjects && Module.pdgAudioObjects.get(id);
    if (entry) entry.audio.volume = Math.max(0, Math.min(1, volume));
});

EM_JS(void, pdg_audio_set_rate, (int id, double rate), {
    var entry = Module.pdgAudioObjects && Module.pdgAudioObjects.get(id);
    if (entry) entry.audio.playbackRate = Math.max(0.0625, Math.min(16, rate));
});

EM_JS(void, pdg_audio_seek, (int id, double seconds, int relative), {
    var entry = Module.pdgAudioObjects && Module.pdgAudioObjects.get(id);
    if (!entry) return;
    try {
        var target = relative ? entry.audio.currentTime + seconds : seconds;
        entry.audio.currentTime = Math.max(0, target);
    } catch (_) {}
});

class SoundEmscripten;
static class SoundManagerEmscripten* sSoundManager = nullptr;

class SoundManagerEmscripten : public SoundManager {
public:
    SoundManagerEmscripten() : mVolume(1.0f), mMuted(false) { sSoundManager = this; }
    ~SoundManagerEmscripten() override { sSoundManager = nullptr; }

    void setVolume(float level) override;
    void setMute(bool muted) override;
    void idle() override {}
    void stopAllSounds() override;
    bool isShuttingDown() const override { return pdg_LibIsQuitting(); }

    void add(SoundEmscripten* sound) { mSounds.push_back(sound); }
    void remove(SoundEmscripten* sound) {
        mSounds.erase(std::remove(mSounds.begin(), mSounds.end(), sound), mSounds.end());
    }
    float outputVolume(float volume) const { return mMuted ? 0.0f : volume * mVolume; }

private:
    std::vector<SoundEmscripten*> mSounds;
    float mVolume;
    bool mMuted;
};

class SoundEmscripten : public Sound {
public:
    SoundEmscripten(SoundManagerEmscripten* manager, const char* name,
                    const char* data, long length)
        : mManager(manager), mHandle(0), mPitch(0.0f), mOffsetX(0) {
        std::string mime = mimeForName(name ? name : "");
        mHandle = pdg_audio_create(data, static_cast<int>(length), mime.c_str());
        mCurrentVolume = 1.0f;
        mManager->add(this);
        gSoundStats.cxxObjsAllocated++;
    }

    ~SoundEmscripten() override {
        if (sSoundManager == mManager) mManager->remove(this);
        pdg_audio_destroy(mHandle);
        gSoundStats.cxxObjsFreed++;
    }

    void play(float vol, int32 offsetX, float pitch, ms_time fromMs, ms_delta lenMs) override {
        setVolume(vol);
        setOffsetX(offsetX);
        setPitch(pitch);
        mPaused = false;
        pdg_audio_set_loop(mHandle, mLoopSound);
        pdg_audio_play(mHandle, static_cast<double>(fromMs) / 1000.0,
                       lenMs < 0 ? -1.0 : static_cast<double>(lenMs) / 1000.0);
    }

    void start() override { play(mCurrentVolume, mOffsetX, mPitch, 0, -1); }
    void stop() override { mPaused = false; pdg_audio_stop(mHandle, true); }
    void pause() override { mPaused = true; pdg_audio_stop(mHandle, false); }
    void resume() override { mPaused = false; pdg_audio_resume(mHandle); }

    Sound& setLooping(bool looping) override {
        Sound::setLooping(looping);
        pdg_audio_set_loop(mHandle, looping);
        return *this;
    }

    Sound& setVolume(float level) override {
        mCurrentVolume = std::max(0.0f, std::min(1.0f, level));
        applyVolume();
        return *this;
    }

    Sound& setPitch(float pitchOffset) override {
        mPitch = pitchOffset;
        pdg_audio_set_rate(mHandle, std::pow(2.0, static_cast<double>(pitchOffset)));
        return *this;
    }

    void changePitch(float targetOffset, ms_delta, EasingFunc) override { setPitch(targetOffset); }

    Sound& setOffsetX(int32 offsetX) override {
        // HTMLAudioElement has no portable panner; keep the value so a future
        // WebAudio graph can adopt it without changing the public contract.
        mOffsetX = offsetX;
        return *this;
    }

    void changeOffsetX(int32 targetOffset, ms_delta, EasingFunc) override { setOffsetX(targetOffset); }
    void fadeOut(ms_delta fadeMs, EasingFunc easing) override {
        changeVolume(0.0f, fadeMs, easing);
        if (fadeMs == 0) stop();
    }
    void fadeIn(ms_delta fadeMs, EasingFunc easing) override {
        setVolume(0.0f);
        start();
        changeVolume(1.0f, fadeMs, easing);
    }
    void changeVolume(float level, ms_delta, EasingFunc) override { setVolume(level); }

    Sound& skip(ms_delta milliseconds) override {
        pdg_audio_seek(mHandle, static_cast<double>(milliseconds) / 1000.0, true);
        return *this;
    }
    Sound& skipTo(ms_time milliseconds) override {
        pdg_audio_seek(mHandle, static_cast<double>(milliseconds) / 1000.0, false);
        return *this;
    }

    void applyVolume() { pdg_audio_set_volume(mHandle, mManager->outputVolume(mCurrentVolume)); }

private:
    static std::string mimeForName(const std::string& name) {
        std::string::size_type dot = name.find_last_of('.');
        std::string ext = dot == std::string::npos ? "" : name.substr(dot + 1);
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        if (ext == "mp3") return "audio/mpeg";
        if (ext == "ogg" || ext == "oga") return "audio/ogg";
        if (ext == "m4a" || ext == "mp4") return "audio/mp4";
        if (ext == "aac") return "audio/aac";
        return "audio/wav";
    }

    SoundManagerEmscripten* mManager;
    int mHandle;
    float mPitch;
    int32 mOffsetX;
};

void SoundManagerEmscripten::setVolume(float level) {
    mVolume = std::max(0.0f, std::min(1.0f, level));
    for (SoundEmscripten* sound : mSounds) sound->applyVolume();
}

void SoundManagerEmscripten::setMute(bool muted) {
    mMuted = muted;
    for (SoundEmscripten* sound : mSounds) sound->applyVolume();
}

void SoundManagerEmscripten::stopAllSounds() {
    std::vector<SoundEmscripten*> sounds = mSounds;
    for (SoundEmscripten* sound : sounds) if (sound) sound->stop();
}

SoundManager* SoundManager::createSingletonInstance() {
    return new SoundManagerEmscripten();
}

Sound* Sound::createSoundFromData(const char* soundName, char* soundData, long soundDataLen) {
    if (!soundData || soundDataLen <= 0) return nullptr;
    return new SoundEmscripten(static_cast<SoundManagerEmscripten*>(
        SoundManager::getSingletonInstance()), soundName, soundData, soundDataLen);
}

Sound* Sound::createSoundFromFile(const char* soundFileName) {
    if (!soundFileName) return nullptr;
    std::ifstream file(soundFileName, std::ios::binary);
    if (!file) return nullptr;
    std::vector<char> bytes((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
    return bytes.empty() ? nullptr : createSoundFromData(soundFileName, bytes.data(), bytes.size());
}

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
Sound* Sound::createEmptySoundForIntrospection() {
    static const char emptyWav[] = { 'R', 'I', 'F', 'F' };
    return createSoundFromData("empty.wav", const_cast<char*>(emptyWav), sizeof(emptyWav));
}
#endif

} // namespace pdg
