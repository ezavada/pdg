// Included in SpriteAnimationSnapshot's public section.
static uint32 physicsRecord(const Sprite& s,ISerializer* writer,bool emit) {
    SnapshotWriter out(writer,emit);uint32 nested=0;
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
    out.integer(s.mAnimationPhysicsRootOverride);
    out.real(s.mAnimationPhysicsUnitsPerMeter,1);
    out.integer(s.mAnimationPhysicsSetupWarnings.size());for(const auto& warning:s.mAnimationPhysicsSetupWarnings)out.text(warning);
    if(out.flag(bool(s.mAnimationPhysics))) {
        if(!s.mAnimationDesired || s.physics.getMode()!=physicsBody_Kinematic)throw std::runtime_error("Invalid coordinating rig body");
        out.byte(s.mAnimationSavedBodyType);out.real(s.mAnimationSavedMass);out.real(s.mAnimationSavedMoment);
        out.integer(uint64_t(s.mAnimationSavedFilter.group)>>32);out.integer(uint32_t(s.mAnimationSavedFilter.group));
        out.integer(s.mAnimationSavedFilter.categories);out.integer(s.mAnimationSavedFilter.mask);
        nested+=encodePose(*s.mAnimationDesired,writer,emit);
        out.integer(s.mAnimationPhysicsParts.size());for(auto* part:s.mAnimationPhysicsParts)out.integer(part->mId);
        out.integer(s.mAnimationPhysicsMembers.size());for(auto* part:s.mParts) {
            const auto it=s.mAnimationPhysicsMembers.find(part);if(it==s.mAnimationPhysicsMembers.end())continue;
            out.integer(part->mId);out.integer(it->second?it->second->mId:partId_None);
        }
        nested+=s.mAnimationPhysics->snapshotRecord(writer,emit);
    }
#else
    out.integer(UINT32_MAX);out.real(1,1);out.integer(0);out.flag(false);
#endif
    return out.size()+nested;
}
static void readPhysics(Sprite& s,IDeserializer* reader) {
    SnapshotReader in(reader);
    const auto rootOverride=in.integer();const auto units=in.real(1);
    if(!std::isfinite(units)||units<=0)throw std::runtime_error("Invalid physical rig units");
    auto count=[&]{auto n=in.integer();if(n>65536)throw std::runtime_error("Rig snapshot exceeds count limit");return n;};
    std::vector<std::string> warnings;for(auto n=count();n;--n)warnings.push_back(in.text());
    const bool active=in.flag();
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
    auto valid=[](bool ok){if(!ok)throw std::runtime_error("Invalid Sprite rig snapshot");};
    valid(rootOverride==animation_NoBone || (s.getAnimationRig() && rootOverride<s.getAnimationRig()->getBoneCount()));
    s.mAnimationPhysicsRootOverride=rootOverride;s.mAnimationPhysicsUnitsPerMeter=units;s.mAnimationPhysicsSetupWarnings=std::move(warnings);
    if(!active) {
        for(auto* p:s.mParts)valid(!p->mAnimationPhysicsBody);
        return;
    }
    valid(s.mAnimationPoseAdapter && s.physics.isPresent() && s.physics.getMode()==physicsBody_Kinematic);
    auto type=in.byte();valid(type<=CP_BODY_TYPE_STATIC);s.mAnimationSavedBodyType=cpBodyType(type);
    // Chipmunk reports infinite mass/moment for kinematic and static roots.
    s.mAnimationSavedMass=in.real();s.mAnimationSavedMoment=in.real();
    valid(s.mAnimationSavedMass>0 && s.mAnimationSavedMoment>0);
    const uint64_t high=in.integer(),low=in.integer();s.mAnimationSavedFilter.group=cpGroup((high<<32)|low);
    s.mAnimationSavedFilter.categories=in.integer();s.mAnimationSavedFilter.mask=in.integer();
    auto desired=readPose(reader,s.getAnimationRig());
    std::vector<Part*> parts;std::vector<PhysicsBody*> bodies;std::set<Part*> seen;
    for(auto n=count();n;--n) {
        auto* p=s.getPart(in.integer());valid(p && p->mAnimationPhysicsBody && p->physics.isPresent() && seen.insert(p).second);
        valid(p->hasCurrentRig() && p->mBone!=animation_NoBone && !p->mParent && p->mBinding==animation_NoBinding && p->mSocket==animation_NoSocket);
        parts.push_back(p);bodies.push_back(p->physics.operator->());
    }
    for(auto* p:s.mParts)valid(!p->mAnimationPhysicsBody || seen.count(p));
    std::map<Part*,Part*> members;
    for(auto n=count();n;--n) {
        auto* p=s.getPart(in.integer());const auto parentId=in.integer();auto* parent=s.getPart(parentId);
        valid(p && p->physics.isPresent() && (parentId==partId_None || parent) && p!=parent);
        valid(members.emplace(p,parent).second);
        if(!p->mAnimationPhysicsBody)valid(!p->mParent && !p->hasCurrentRig() && !p->mAttachedSprite);
    }
    for(const auto& item:members) {
        std::set<Part*> chain{item.first};
        for(auto* parent=item.second;parent;) {
            valid(chain.insert(parent).second);const auto it=members.find(parent);valid(it!=members.end());parent=it->second;
        }
    }
    auto rig=AnimationPhysicsRig::restoreSnapshot(reader,*desired,s.spriterRootTransform(),bodies,[&s]{s.invalidateSpriterPose();});
    const auto& def=rig->definition();long double total=0;
    for(size_t i=0;i<parts.size();++i) {
        valid(parts[i]->mBone==def.bodies[i].bone && bool(members.count(parts[i]))==rig->isBodyAttached(i));
    }
    for(const auto& member:members)total+=member.first->physics.getMass();
    valid(std::isfinite(double(total)) && total>0);
    // Keep ownership coherent even if a subsequent graph record is malformed.
    s.mAnimationPhysicsParts=std::move(parts);s.mAnimationPhysicsMembers=std::move(members);
    s.mAnimationDesired=std::make_unique<AnimationPose>(desired->copy());s.mAnimationPhysics=std::move(rig);s.mAnimationPhysics->owner=&s;
    s.physics->mAssemblyBodies.clear();
    for(auto* part:s.mAnimationPhysicsParts)if(s.isAnimationPhysicsPartAttached(part))s.physics->mAssemblyBodies.push_back(part->physics.operator->());
    for(auto* part:s.mParts)if(!part->mAnimationPhysicsBody && s.isAnimationPhysicsPartAttached(part))s.physics->mAssemblyBodies.push_back(part->physics.operator->());
    for(auto* b:s.physics->mAssemblyBodies)b->mAssemblyOwner=s.physics.operator->();
    s.physics->mAssemblyRoot=s.mAnimationPhysicsParts[def.rootBody]->physics.operator->();
    for(auto* p:s.mAnimationPhysicsParts)if(s.isAnimationPhysicsPartAttached(p)) {
        const auto bone=p->mBone;
        p->physics->mCoordinateMode=[&s,bone](int mode) {
            if(mode==physicsBody_Static)throw std::invalid_argument("Mapped animation bodies cannot be Static");
            s.setAnimationPhysicsMode(mode==physicsBody_Dynamic?animationPhysics_Dynamic:animationPhysics_Kinematic,bone);
        };
    }
    s.publishAnimationPhysics();
#else
    if(active)throw std::runtime_error("Physical rig snapshots require Spriter and Chipmunk support");
#endif
}
