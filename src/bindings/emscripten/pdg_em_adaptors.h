// this header file contains all the code that adapts between the JavaScript and C++ classes, which
// do not always have identical method signatures

#include "pdg/framework.h"

#include "config-unix.h"

#include "../javascript/memblock.h"

namespace pdg {

// extend the config manager to handle API differences between C++ and Javascript

// TODO: add this to ConfigManager

class ConfigManagerWrap : public ConfigManagerUnix {
public:
    std::string& getConfigString(std::string& arg0);
    long getConfigLong(std::string& arg0);
    float getConfigFloat(std::string& arg0);
    bool getConfigBool(std::string& arg0);
};

class FileManager : public Singleton<FileManager> {
public:
	static FileManager* createSingletonInstance();
//     findFirst();
//     findNext();
//     void findClose();
    std::string&  getApplicationDataDirectory();
    std::string&  getApplicationDirectory();
    std::string&  getApplicationResourceDirectory();
};

void setSerializationDebugMode(bool);

void emscriptenInit();
void emscriptenIdle();
void emscriptenQuit();
bool emscriptenIsQuitting();

enum {
    action_ErasePort = SpriteLayer::action_ErasePort,
    action_PreDrawLayer = SpriteLayer::action_PreDrawLayer,
    action_PostDrawLayer = SpriteLayer::action_PostDrawLayer,
    action_DrawPortComplete = SpriteLayer::action_DrawPortComplete,
    action_AnimationStart = SpriteLayer::action_AnimationStart,
    action_PreAnimateLayer = SpriteLayer::action_PreAnimateLayer,
    action_PostAnimateLayer = SpriteLayer::action_PostAnimateLayer,
    action_AnimationComplete = SpriteLayer::action_AnimationComplete,
    action_ZoomComplete = SpriteLayer::action_ZoomComplete,
    action_LayerFadeInComplete = SpriteLayer::action_FadeInComplete,
    action_LayerFadeOutComplete = SpriteLayer::action_FadeOutComplete
};

} // end namespace pdg
