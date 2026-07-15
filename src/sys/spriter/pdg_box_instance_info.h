#ifndef PDG_BOX_INSTANCE_INFO_H
#define PDG_BOX_INSTANCE_INFO_H

#include "spriterengine/objectinfo/boxinstanceinfo.h"

namespace pdg {

#ifndef PDG_NO_GUI
class Port;
#endif

class PDGBoxInstanceInfo : public SpriterEngine::BoxInstanceInfo
{
public:
    #ifndef PDG_NO_GUI
    PDGBoxInstanceInfo(SpriterEngine::point size, Port* port);
    #else
    PDGBoxInstanceInfo(SpriterEngine::point size);
    #endif
    
    void render() override;
    
    #ifndef PDG_NO_GUI
    void setPort(Port* port);
    #endif
    
    // SpriterPlusPlus integration methods
    void setObjectToLinear(SpriterEngine::UniversalObjectInterface *bObject, SpriterEngine::real t, SpriterEngine::UniversalObjectInterface *resultObject) override;
    void setToBlendedLinear(SpriterEngine::UniversalObjectInterface *aObject, SpriterEngine::UniversalObjectInterface *bObject, SpriterEngine::real t, SpriterEngine::real blendRatio, SpriterEngine::ObjectRefInstance *blendedRefInstance = 0) override;
    
    // Box name management - available in both GUI and non-GUI modes
    void setBoxName(const std::string& boxName) { mBoxName = boxName; }
    const std::string& getBoxName() const { return mBoxName; }

private:
    #ifndef PDG_NO_GUI
    Port* mPort;
    #endif
    SpriterEngine::point mSize;
    std::string mBoxName;  // Store the actual box name from Spriter
};

}

#endif // PDG_BOX_INSTANCE_INFO_H
