#ifndef PDG_POINT_INSTANCE_INFO_H
#define PDG_POINT_INSTANCE_INFO_H

#ifndef PDG_NO_GUI

// for debug rendering, so only include if we have a GUI

#include "spriterengine/objectinfo/pointinstanceinfo.h"

namespace pdg {

class Port;

class PDGPointInstanceInfo : public SpriterEngine::PointInstanceInfo
{
public:
    PDGPointInstanceInfo(Port* port);
    
    void render() override;
    
    void setPort(Port* port);
    
    // SpriterPlusPlus integration methods
    void setObjectToLinear(SpriterEngine::UniversalObjectInterface *bObject, SpriterEngine::real t, SpriterEngine::UniversalObjectInterface *resultObject) override;
    void setToBlendedLinear(SpriterEngine::UniversalObjectInterface *aObject, SpriterEngine::UniversalObjectInterface *bObject, SpriterEngine::real t, SpriterEngine::real blendRatio, SpriterEngine::ObjectRefInstance *blendedRefInstance = 0) override;
    
    // Point name management
    void setPointName(const std::string& pointName) { 
        #ifdef PDG_DEBUG_SPRITER
            pdg::OS::_DOUT("PDGPointInstanceInfo: Setting point name to '%s'", pointName.c_str());
        #endif
        mPointName = pointName; 
    }
    const std::string& getPointName() const { return mPointName; }

private:
    Port* mPort;
    std::string mPointName;  // Store the actual point name from Spriter
};

}

#endif // PDG_NO_GUI

#endif // PDG_POINT_INSTANCE_INFO_H
