#include "pdg_object_factory.h"

#include "spriterengine/objectinfo/spriteobjectinfo.h"
#include "spriterengine/objectinfo/triggerobjectinfo.h"

#ifndef PDG_NO_GUI
  #include "pdg_point_instance_info.h"
  #include "pdg_bone_instance_info.h"
#endif // !PDG_NO_GUI

#include "pdg_box_instance_info.h"

namespace pdg {

SpriterEngine::TriggerObjectInfo* PDGObjectFactory::newTriggerObjectInfo(std::string triggerName) {
    // Create a basic trigger object info
    return new SpriterEngine::TriggerObjectInfo();
}

SpriterEngine::SpriteObjectInfo* PDGObjectFactory::newSpriteObjectinfo() {
    // Create a basic sprite object info
    return new SpriterEngine::SpriteObjectInfo();
}

SpriterEngine::BoxInstanceInfo* PDGObjectFactory::newBoxInstanceInfo(SpriterEngine::point size) {
    // Create a PDG box instance info - available in both GUI and non-GUI modes
#ifndef PDG_NO_GUI
    return new pdg::PDGBoxInstanceInfo(size, nullptr);
#else
    return new pdg::PDGBoxInstanceInfo(size);
#endif
}

#ifndef PDG_NO_GUI
SpriterEngine::PointInstanceInfo* PDGObjectFactory::newPointInstanceInfo() {
    // Create a PDG point instance info for debug rendering
    return new pdg::PDGPointInstanceInfo(nullptr);
}

SpriterEngine::BoneInstanceInfo* PDGObjectFactory::newBoneInstanceInfo(SpriterEngine::point size) {
    // Create a PDG bone instance info for debug rendering
    return new pdg::PDGBoneInstanceInfo(size, nullptr);
}

#endif // !PDG_NO_GUI

} // namespace pdg
