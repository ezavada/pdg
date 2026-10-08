#ifndef PDG_EM_BONE_H
#define PDG_EM_BONE_H
#include "pdg/sys/bone.h"
#include "pdg/sys/sprite.h"
#include <emscripten/bind.h>
#ifdef PDG_SPRITER_SUPPORT
namespace emscripten::internal {
template<> inline void raw_destructor<pdg::Bone>(pdg::Bone* bone){bone->release();}
}
namespace pdg {
template<class F> auto browserBoneCall(F operation)->decltype(operation()){
    try{return operation();}catch(const std::exception& error){emscripten::val::global("Error").new_(std::string(error.what())).throw_();}
}
inline std::shared_ptr<Bone> browserSpriteGetBone(Sprite& sprite,const emscripten::val& selector){return browserBoneCall([&]{
    Bone* bone;
    if(selector.typeOf().as<std::string>()=="string")bone=sprite.getBone(selector.as<std::string>().c_str());
    else {if(selector.typeOf().as<std::string>()!="number")throw std::invalid_argument("Invalid bone selector");const double id=selector.as<double>();if(!std::isfinite(id)||id<0||id>UINT32_MAX||std::floor(id)!=id)throw std::invalid_argument("Invalid bone selector");bone=sprite.getBone(static_cast<AnimationBoneId>(id));}
    bone->addRef();return std::shared_ptr<Bone>(bone,[](Bone* value){value->release();});
});}
inline Bone& browserBoneSetIKLimits(Bone& bone,const emscripten::val& first,const emscripten::val& second){return browserBoneCall([&]() -> Bone& {
    if(second.isUndefined())return bone.setIKLimits(*first.as<PhysicsConstraint*>(emscripten::allow_raw_pointers()));
    return bone.setIKLimits(first.as<double>(),second.as<double>());
});}

}
#endif // PDG_SPRITER_SUPPORT
// @pdg-adapter {"name":"Sprite.getBone","value":{"symbol":"pdg::browserSpriteGetBone","header":"src/bindings/emscripten/pdg_em_bone.h"}}
// @pdg-adapter {"name":"Bone.setIKLimits","value":{"symbol":"pdg::browserBoneSetIKLimits","header":"src/bindings/emscripten/pdg_em_bone.h","allow_raw_pointers":true}}
#endif
