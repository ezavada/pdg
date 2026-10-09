// Included inside namespace pdg, with Spriter support enabled.
AnimationBoneId Sprite::animationPhysicsBone(const char* name) const {
    const auto rig=getAnimationRig();
    if(!rig || !name)throw std::invalid_argument("Expected an animation bone name");
    const auto bone=rig->findBone(name);
    if(bone==animation_NoBone)throw std::invalid_argument("Unknown animation bone");
    return bone;
}
#ifdef PDG_USE_CHIPMUNK_PHYSICS
AnimationPhysicsRig& Sprite::animationPhysicsControl() const {
    if(!mAnimationPhysics)throw std::logic_error("Sprite has no physical animation rig");
    return *mAnimationPhysics;
}
#endif
Sprite& Sprite::changeAnimationPhysicsMode(int mode,std::optional<AnimationBoneId> bone,bool descendants,
                                           double seconds,int direction,bool disabling) {
    if(AnimationPipeline::isInsideCallback())throw std::logic_error("Change physical control outside modifiers");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    auto& rig=animationPhysicsControl();
    const auto selection=rig.select(bone,descendants);
    AnimationPhysicsRecovery request;request.bone=bone.value_or(animation_NoBone);
    request.includeDescendants=descendants;request.disabled=disabling;
    rig.setMode(mode,selection,seconds,direction,*mAnimationDesired,spriterRootTransform(),request);
    invalidateSpriterPose();
#else
    throw std::logic_error("Physical animation is unavailable in this build");
#endif
    return *this;
}
Sprite& Sprite::setAnimationPhysicsMode(int mode,double seconds,int direction) {
    if(recordOperation("setAnimationPhysicsMode", captureAnimationArguments(mode, seconds, direction))) return *this;
    return changeAnimationPhysicsMode(mode,{},false,seconds,direction);
}
Sprite& Sprite::setAnimationPhysicsMode(int mode,AnimationBoneId bone,bool descendants,double seconds,int direction) {
    if(recordOperation("setAnimationPhysicsMode", captureAnimationArguments(mode, bone, descendants, seconds, direction))) return *this;
    return changeAnimationPhysicsMode(mode,bone,descendants,seconds,direction);
}
Sprite& Sprite::setAnimationPhysicsMode(int mode,const char* bone,bool descendants,double seconds,int direction) {
    if(recordOperation("setAnimationPhysicsMode", captureAnimationArguments(mode, bone, descendants, seconds, direction))) return *this;
    return setAnimationPhysicsMode(mode,animationPhysicsBone(bone),descendants,seconds,direction);
}
int Sprite::getAnimationPhysicsMode() const {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    auto& rig=animationPhysicsControl();return rig.getMode(rig.select({},false));
#else
    throw std::logic_error("Physical animation is unavailable in this build");
#endif
}
int Sprite::getAnimationPhysicsMode(AnimationBoneId bone,bool descendants) const {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    auto& rig=animationPhysicsControl();return rig.getMode(rig.select(bone,descendants));
#else
    throw std::logic_error("Physical animation is unavailable in this build");
#endif
}
int Sprite::getAnimationPhysicsMode(const char* bone,bool descendants) const { return getAnimationPhysicsMode(animationPhysicsBone(bone),descendants); }
Sprite& Sprite::setAnimationPhysicsDriveSettings(const AnimationPhysicsDriveSettings& settings) {
    if(recordOperation("setAnimationPhysicsDriveSettings", captureAnimationArguments(settings))) return *this;
    if(AnimationPipeline::isInsideCallback())throw std::logic_error("Change physical control outside modifiers");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    auto& rig=animationPhysicsControl();rig.setDriveSettings(settings,rig.select({},false));
#else
    throw std::logic_error("Physical animation is unavailable in this build");
#endif
    return *this;
}
Sprite& Sprite::setAnimationPhysicsDriveSettings(const AnimationPhysicsDriveSettings& settings,AnimationBoneId bone,bool descendants) {
    if(recordOperation("setAnimationPhysicsDriveSettings", captureAnimationArguments(settings, bone, descendants))) return *this;
    if(AnimationPipeline::isInsideCallback())throw std::logic_error("Change physical control outside modifiers");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    auto& rig=animationPhysicsControl();rig.setDriveSettings(settings,rig.select(bone,descendants));
#else
    throw std::logic_error("Physical animation is unavailable in this build");
#endif
    return *this;
}
Sprite& Sprite::setAnimationPhysicsDriveSettings(const AnimationPhysicsDriveSettings& settings,const char* bone,bool descendants) {
    if(recordOperation("setAnimationPhysicsDriveSettings", captureAnimationArguments(settings, bone, descendants))) return *this;
    return setAnimationPhysicsDriveSettings(settings,animationPhysicsBone(bone),descendants);
}
std::optional<AnimationPhysicsDriveSettings> Sprite::getAnimationPhysicsDriveSettings(AnimationBoneId bone) const {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    auto& rig=animationPhysicsControl();return rig.getDriveSettings(rig.select(bone,false).front());
#else
    throw std::logic_error("Physical animation is unavailable in this build");
#endif
}
std::optional<AnimationPhysicsDriveSettings> Sprite::getAnimationPhysicsDriveSettings(const char* bone) const {return getAnimationPhysicsDriveSettings(animationPhysicsBone(bone));}
void Sprite::disableAnimationPhysics(double seconds,int direction) {
    if(!std::isfinite(seconds)||seconds<0||direction<rotationDirection_AsSpecified||direction>rotationDirection_CounterClockwise)
        throw std::invalid_argument("Invalid recovery duration or direction");
    if(AnimationPipeline::isInsideCallback())throw std::logic_error("Change physical control outside modifiers");
    if(!isAnimationPhysicsEnabled())return;
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(seconds==0) {
        if((getSpace() && cpSpaceIsLocked(getSpace())))throw std::logic_error("Change physical control outside physics callbacks");
        for(auto* part:mAnimationPhysicsParts) {
            const auto& body=static_cast<PhysicsBody&>(part->physics);
            if((body.mDriveController && body.mDriveController!=mAnimationPhysics.get()) || (!body.mDriveController && body.mDrive.enabled))
                throw std::logic_error("Explicitly release manual or Part IK drives before disabling animation physics");
        }
        AnimationPhysicsRecovery request;request.disabled=true;request.bodies=mAnimationPhysics->select({},false);
        releaseAnimationPhysics();notifyAnimationPhysicsRecovery(request);return;
    }
#endif
    changeAnimationPhysicsMode(animationPhysics_Kinematic,{},false,seconds,direction,true);
}
void Sprite::notifyAnimationPhysicsRecovery(const AnimationPhysicsRecovery& recovery) {
    SpriteAnimationPhysicsRecoveryInfo info{};
    info.action=action_AnimationPhysicsRecoveryComplete;info.actingSprite=this;info.inLayer=mLayer;info.id=gNextSpriteEventId++;
    info.bone=recovery.bone;info.wholeRig=recovery.bone==animation_NoBone;info.includeDescendants=recovery.includeDescendants;
    info.mode=recovery.mode;info.bodyCount=recovery.bodies.size();info.disabled=recovery.disabled;
    const bool retained=refs>0;if(retained)addRef();
    struct Release{Sprite* sprite;~Release(){if(sprite)sprite->release();}} release{retained?this:nullptr};
    postEvent(eventType_SpriteAnimate,&info);
}
#ifdef PDG_USE_CHIPMUNK_PHYSICS
void Sprite::finishAnimationPhysics() {
    if(!mAnimationPhysics||!mAnimationDesired)return;
    const auto completed=mAnimationPhysics->finishStep(*mAnimationDesired,spriterRootTransform());
    for(const auto& recovery:completed)if(recovery.disabled){releaseAnimationPhysics();break;}
    for(const auto& recovery:completed)notifyAnimationPhysicsRecovery(recovery);
}
#endif
