#ifndef PDG_OBJECT_FACTORY_H_INCLUDED
#define PDG_OBJECT_FACTORY_H_INCLUDED

#include "spriterengine/override/objectfactory.h"

namespace pdg {

class PDGObjectFactory : public SpriterEngine::ObjectFactory {
public:
    PDGObjectFactory() = default;
    ~PDGObjectFactory() override = default;

    // ObjectFactory interface
    virtual SpriterEngine::SpriteObjectInfo* newSpriteObjectinfo() override;
    virtual SpriterEngine::TriggerObjectInfo* newTriggerObjectInfo(std::string triggerName) override;
    virtual SpriterEngine::BoxInstanceInfo* newBoxInstanceInfo(SpriterEngine::point size) override;

  #ifndef PDG_NO_GUI
    // Debug rendering, only include if we have a GUI
	  virtual SpriterEngine::PointInstanceInfo* newPointInstanceInfo() override;
	  virtual SpriterEngine::BoneInstanceInfo* newBoneInstanceInfo(SpriterEngine::point size) override;
  #endif

};

} // namespace pdg

#endif // PDG_OBJECT_FACTORY_H_INCLUDED
