#ifndef PDG_BONE_INSTANCE_INFO_H
#define PDG_BONE_INSTANCE_INFO_H

#ifndef PDG_NO_GUI

// for debug rendering, so only include if we have a GUI

#include "spriterengine/objectinfo/boneinstanceinfo.h"
#include "pdg/sys/coordinates.h"

namespace pdg {

class Port;

class PDGBoneInstanceInfo : public SpriterEngine::BoneInstanceInfo
{
public:
    PDGBoneInstanceInfo(SpriterEngine::point size, Port* port);
    
    void render() override;
    
    void setPort(Port* port);

private:
    Port* mPort;
    SpriterEngine::point mSize;
    pdg::Quad mQuad;
};

}

#endif // !PDG_NO_GUI

#endif // PDG_BONE_INSTANCE_INFO_H
