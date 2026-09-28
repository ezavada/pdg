// Ownership transfer preserves objects; it does not clone or retarget a skeleton.
Part* Sprite::transferPart(Part* part,bool descendants) {
    if(!part || !part->mSprite)throw std::invalid_argument("Transfer an owned Part");
    auto* source=part->mSprite;
    if(source==this)return part;
    if(source->mLayer!=mLayer)throw std::invalid_argument("Part transfers require the same layer, or both Sprites off-layer");
#ifdef PDG_SPRITER_SUPPORT
    if(AnimationPipeline::isInsideCallback() || source->mAnimationDrawings.isDrawing() || mAnimationDrawings.isDrawing())
        throw std::logic_error("Transfer Parts outside animation modifiers and drawing callbacks");
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mLayer && mLayer->mUseChipmunkPhysics && cpSpaceIsLocked(mLayer->getSpace()))
        throw std::logic_error("Transfer Parts outside locked physics callbacks");
#endif
    std::set<Part*> selected{part};
    if(descendants) {
        bool added=true;
        while(added) {
            added=false;
            for(auto* candidate:source->mParts)if(!selected.count(candidate)) {
                bool include=candidate->mParent && selected.count(candidate->mParent);
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
                const auto member=source->mAnimationPhysicsMembers.find(candidate);
                include=include || (member!=source->mAnimationPhysicsMembers.end() && selected.count(member->second));
                if(!include && candidate->mAnimationPhysicsBody) {
                    const auto rig=source->getAnimationRig();
                    for(auto bone=rig->getBone(candidate->mBone).parent;bone!=animation_NoBone;bone=rig->getBone(bone).parent)
                        for(auto* parent:selected)if(parent->mAnimationPhysicsBody && parent->mBone==bone)include=true;
                }
#endif
                if(include){selected.insert(candidate);added=true;}
            }
        }
    }
    if(selected.size()>uint64_t(partId_None)-mNextPartId)throw std::overflow_error("Part ID space exhausted");
    std::vector<Part*> moved,remaining;
    std::set<PhysicsBody*> bodies;
    for(auto* candidate:source->mParts) {
        if(selected.count(candidate)) {
            if(findPart(candidate->mName))throw std::invalid_argument("Transferred Part names must be unique in the destination Sprite");
            if(candidate->mAttachedSprite && candidate->mAttachedSprite->attachmentReaches(this))
                throw std::invalid_argument("Part transfer would create a Sprite attachment cycle");
            moved.push_back(candidate);
            if(candidate->physics.isPresent())bodies.insert(candidate->physics.operator->());
        } else remaining.push_back(candidate);
    }
    // An IK controller owns a chain in its Sprite's ID/frame namespace. Require
    // explicit handoff rather than silently moving or breaking that controller.
    for(auto* candidate:source->mParts)if(candidate->mIKTarget) {
        const auto& ik=*candidate->mIKTarget;
        if(selected.count(candidate) || selected.count(source->getPart(ik.middle)) || selected.count(source->getPart(ik.tip)))
            throw std::logic_error("Clear Part IK targets before transferring any controlled chain member");
    }
    for(auto* body:bodies)if(body->mDriveController && !body->mRigDrive)
        throw std::logic_error("Release the body's external controller before transferring its Part");

    struct Placement {Part* part;Part* parent;Point location;float angle;Offset scale;};
    std::vector<Placement> placements;
    for(auto* candidate:source->mParts) {
        const bool moving=selected.count(candidate);
        if(!moving && !(candidate->mParent && selected.count(candidate->mParent)))continue;
        auto* parent=candidate->mParent;
        // Moving roots become independent. Children left behind retain their
        // nearest remaining Part ancestor and their current world placement.
        if(moving && parent && !selected.count(parent))parent=nullptr;
        if(!moving)while(parent && selected.count(parent))parent=parent->mParent;
        if(moving && parent==candidate->mParent && parent)continue;
        Placement value{candidate,parent,{},0,{}};
        const auto frame=parent?parent->getTransform(partSpace_World):(moving?partRootTransform():source->partRootTransform());
        Part::decomposeMount(SpatialTransform::compose(frame.inverse(),candidate->getTransform(partSpace_World)),
                             value.location,value.angle,value.scale);
        placements.push_back(value);
    }
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
    auto members=source->mAnimationPhysicsMembers;
    std::vector<uint32_t> mapped;
    std::vector<Part*> mappedRemaining;
    if(source->mAnimationPhysics) {
        for(auto* p:moved)members.erase(p);
        for(auto& item:members)while(item.second && !members.count(item.second))item.second=source->mAnimationPhysicsMembers.at(item.second);
        std::vector<bool> attached;
        for(uint32_t i=0;i<source->mAnimationPhysicsParts.size();++i) {
            auto* p=source->mAnimationPhysicsParts[i];attached.push_back(members.count(p));
            if(selected.count(p))mapped.push_back(i);else mappedRemaining.push_back(p);
        }
        source->mAnimationPhysics->validateMembershipChange(attached);
        source->selectAnimationPhysicsMemberRoot(members); // Keep one attached skeletal body.
    }
#endif
    auto destination=mParts;destination.insert(destination.end(),moved.begin(),moved.end());
    // All semantic checks precede ownership, mass or topology changes.
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
    if(source->mAnimationPhysics) {
        source->updateAnimationPhysicsMembers(std::move(members),false);
        source->mAnimationPhysics->removeDetachedBodies(mapped);
        source->mAnimationPhysicsParts=std::move(mappedRemaining);
    }
#endif
    for(auto* body:bodies)for(uint32_t i=body->getConstraintCount();i>0;--i) {
        auto& joint=body->getConstraint(i-1);
        auto* other=&joint.getBodyA()==body?&joint.getBodyB():&joint.getBodyA();
        if(!bodies.count(other))joint.disconnect();
    }
    for(auto* p:moved) {
        p->mAnimationPhysicsBody=false;p->mBone=boneId_None;p->mRig.reset();
        p->mBinding=p->mSocket=UINT32_MAX;
        p->mSprite=this;p->mId=mNextPartId++;
    }
    source->mParts=std::move(remaining);mParts=std::move(destination);
    for(const auto& value:placements) {
        auto* p=value.part;p->setParentLink(value.parent);
        p->cancelProgrammedMotion();p->cancelAnimation(&p->mScaleX);p->cancelAnimation(&p->mScaleY);
        p->mLocation=value.location;p->mFacing=value.angle;p->mScaleX=value.scale.x;p->mScaleY=value.scale.y;
        p->mFlipX=p->mFlipY=false;
        p->clearIKLimits(); // Limits relative to a replaced parent frame no longer apply.
    }
    for(auto* p:moved)if(p->physics.isPresent()) {
        p->installPhysicsPublisher(p->physics);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if(auto* solver=dynamic_cast<PartBodySolver*>(p->physics->mSolver.get()))solver->changeOwner(this);
#endif
        p->syncPhysicsSolver();
    }
    source->refreshPartPhysics();refreshPartPhysics();
    source->updatePartAttachments();updatePartAttachments();
    return part;
}
