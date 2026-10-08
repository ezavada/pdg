// Included inside namespace pdg with Spriter support enabled.
bool Sprite::isAnimationPhysicsPartAttached(const Part* part) const {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    return part && mAnimationPhysics && mAnimationPhysicsMembers.count(const_cast<Part*>(part));
#else
    return false;
#endif
}
#ifdef PDG_USE_CHIPMUNK_PHYSICS
uint32_t Sprite::selectAnimationPhysicsMemberRoot(const std::map<Part*,Part*>& members) const {
    const auto rig=getAnimationRig();const auto& definitions=mAnimationPhysics->definition().bodies;
    uint32_t result=uint32_t(definitions.size());size_t largest=0;
    for(uint32_t i=0;i<definitions.size();++i) {
        if(!members.count(mAnimationPhysicsParts[i]))continue;
        const auto bone=definitions[i].bone;
        if(rig->getBone(bone).name=="root")return i;
        size_t children=0;
        for(const auto& member:members)for(auto* parent=member.second;parent;) {
            if(parent==mAnimationPhysicsParts[i]){++children;break;}
            const auto found=members.find(parent);parent=found==members.end()?nullptr:found->second;
        }
        if(result==definitions.size() || children>largest){result=i;largest=children;}
    }
    if(result==definitions.size())throw std::logic_error("Keep at least one skeleton body attached; disable the rig to remove the assembly");
    return result;
}
void Sprite::updateAnimationPhysicsMembers(std::map<Part*,Part*> members,bool disconnectBoundary) {
    if(AnimationPipeline::isInsideCallback() || (getSpace() && cpSpaceIsLocked(getSpace())))
        throw std::logic_error("Change rig membership outside animation and physics callbacks");
    auto& rig=animationPhysicsControl();
    // Restoring a skipped ancestor restores the logical skeletal hierarchy,
    // even when its children stayed attached. Accessory parenting is explicit.
    const auto skeleton=getAnimationRig();
    for(auto* part:mAnimationPhysicsParts)if(members.count(part)) {
        Part* parent=nullptr;
        for(auto bone=skeleton->getBone(part->getBoneId()).parent;bone!=animation_NoBone;bone=skeleton->getBone(bone).parent) {
            for(auto* candidate:mAnimationPhysicsParts)if(candidate->getBoneId()==bone && members.count(candidate)){parent=candidate;break;}
            if(parent)break;
        }
        members.at(part)=parent;
    }
    std::vector<bool> attached;
    for(auto* part:mAnimationPhysicsParts)attached.push_back(members.count(part)!=0);
    rig.validateMembershipChange(attached);
    const uint32_t oldRoot=rig.definition().rootBody;
    const auto root=attached[oldRoot]?oldRoot:selectAnimationPhysicsMemberRoot(members);
    std::vector<PhysicsBody*> bodies,removed;
    // Keep mapped bodies in definition order; accessories follow Part order.
    long double total=0;
    for(auto* part:mAnimationPhysicsParts)if(members.count(part)){bodies.push_back(part->physics.operator->());total+=part->physics.getMass();}
    for(auto* part:mParts)if(members.count(part) && !part->mAnimationPhysicsBody){bodies.push_back(part->physics.operator->());total+=part->physics.getMass();}
    if(!std::isfinite(double(total)) || total<=0)throw std::invalid_argument("Assembly mass must remain finite and positive");
    for(const auto& old:mAnimationPhysicsMembers)if(!members.count(old.first))removed.push_back(old.first->physics.operator->());
    std::vector<std::function<void(int)>> coordinators(attached.size());
    for(size_t i=0;i<attached.size();++i)if(attached[i]) {
        const auto bone=rig.definition().bodies[i].bone;
        coordinators[i]=[this,bone](int mode) {
            if(mode==physicsBody_Static)throw std::invalid_argument("Mapped animation bodies cannot be Static");
            setAnimationPhysicsMode(mode==physicsBody_Dynamic?animationPhysics_Dynamic:animationPhysics_Kinematic,bone);
        };
    }
    // No topology or ownership changes until all validation/allocation succeeds.
    rig.setMembership(attached,root);
    for(auto* body:removed) {
        body->mAssemblyOwner=nullptr;
        for(uint32_t i=disconnectBoundary?body->getConstraintCount():0;i>0;--i) {
            auto& joint=body->getConstraint(i-1);
            auto* other=&joint.getBodyA()==body?&joint.getBodyB():&joint.getBodyA();
            if(std::find(removed.begin(),removed.end(),other)==removed.end())joint.disconnect();
        }
    }
    for(size_t i=0;i<attached.size();++i)mAnimationPhysicsParts[i]->physics->mCoordinateMode=std::move(coordinators[i]);
    for(auto* body:bodies)body->mAssemblyOwner=physics.operator->();
    physics->mAssemblyBodies=std::move(bodies);
    physics->mAssemblyRoot=mAnimationPhysicsParts[root]->physics.operator->();
    mAnimationPhysicsMembers=std::move(members);
    if(root!=oldRoot)mAnimationPhysicsRootOverride=animation_NoBone;
    invalidateSpriterPose();
}
#endif
Sprite& Sprite::attachAnimationPhysicsPart(Part* part,Part* parent) {
    if(recordOperation("attachAnimationPhysicsPart", captureAnimationArguments(part, parent))) return *this;
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    animationPhysicsControl();
    if(!part || part->getSprite()!=this || !part->physics.isPresent())
        throw std::invalid_argument("Attach a physical Part owned by this Sprite");
    if(parent && !isAnimationPhysicsPartAttached(parent))throw std::invalid_argument("Parent must be an attached rig Part");
    if(isAnimationPhysicsPartAttached(part)) {
        if(parent && mAnimationPhysicsMembers.at(part)!=parent)throw std::logic_error("Detach a component before changing its assembly parent");
        return *this;
    }
    if(part->physics->mAssemblyOwner)throw std::logic_error("Detach the component from its previous assembly first");
    if(part->mAnimationPhysicsBody) {
        Part* expected=nullptr;const auto skeleton=getAnimationRig();
        for(auto bone=skeleton->getBone(part->getBoneId()).parent;bone!=animation_NoBone;bone=skeleton->getBone(bone).parent) {
            for(auto* candidate:mAnimationPhysicsParts)if(candidate->getBoneId()==bone && isAnimationPhysicsPartAttached(candidate)){expected=candidate;break;}
            if(expected)break;
        }
        if(parent && parent!=expected)throw std::invalid_argument("A mapped Part retains its animation hierarchy");
        parent=expected;
    } else if(part->mParent || part->getBoneId()!=boneId_None || part->mBinding!=animation_NoBinding || part->mSocket!=animation_NoSocket || part->mAttachedSprite)
        throw std::invalid_argument("An accessory must be an independent physical Part; connect it using PhysicsConstraints");
    auto members=mAnimationPhysicsMembers;members.emplace(part,parent);
    updateAnimationPhysicsMembers(std::move(members));
#else
    throw std::logic_error("Physical animation is unavailable in this build");
#endif
    return *this;
}
Sprite& Sprite::detachAnimationPhysicsPart(Part* part,bool descendants) {
    if(recordOperation("detachAnimationPhysicsPart", captureAnimationArguments(part, descendants))) return *this;
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    animationPhysicsControl();
    if(!part || part->getSprite()!=this)throw std::invalid_argument("Expected a Part owned by this Sprite");
    if(!isAnimationPhysicsPartAttached(part))return *this;
    auto members=mAnimationPhysicsMembers;
    for(const auto& member:mAnimationPhysicsMembers) {
        bool selected=member.first==part;
        if(descendants)for(auto* parent=member.second;parent;parent=mAnimationPhysicsMembers.at(parent))
            if(parent==part){selected=true;break;}
        if(selected)members.erase(member.first);
    }
    for(auto& member:members)while(member.second && !members.count(member.second))member.second=mAnimationPhysicsMembers.at(member.second);
    updateAnimationPhysicsMembers(std::move(members));
#else
    throw std::logic_error("Physical animation is unavailable in this build");
#endif
    return *this;
}
