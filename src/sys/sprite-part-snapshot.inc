// Included inside namespace pdg. Part records belong to their Sprite; the
// inherited Animated record is only one component of a complete Part snapshot.
void Part::validateSnapshot(bool layerGraph) const {
    if (mAttachedSprite && !layerGraph)
        throw std::runtime_error("Save mounted Sprite relationships through a SpriteLayer snapshot");
    if (mIKTarget) calculateIK(mSprite->getPart(mIKTarget->middle), mSprite->getPart(mIKTarget->tip),
        mIKTarget->target, mIKTarget->space, mIKTarget->bend, mIKTarget->influence, isIKDriven()?mIKTarget.get():nullptr);
    if (mRig && !hasCurrentRig()) throw std::runtime_error("Rebind or unbind stale authored Parts before saving");
    if (!mHelpers.empty()) throw std::runtime_error("Part snapshots cannot save callback helpers");
    if (mName.find('\0') != std::string::npos) throw std::runtime_error("Part snapshot names cannot contain NUL");
    for (const auto& animation : mAnimations)
        if (std::find(gEasingFunctions, gEasingFunctions + NUM_BUILTIN_EASINGS, animation.easing)
                == gEasingFunctions + NUM_BUILTIN_EASINGS)
            throw std::runtime_error("Part snapshots cannot save custom easing callbacks");
}
uint32 Sprite::partSnapshotSize(ISerializer* writer) const {
    uint32 size = writer->sizeof_uint(mNextPartId) + writer->sizeof_uint(mParts.size());
    for (auto* part : mParts) {
        size += writer->sizeof_uint(part->mId) + writer->sizeof_str(part->mName.c_str());
        size += writer->sizeof_uint(part->mParent ? part->mParent->mId : partId_None);
        size += part->Animated::getSerializedSize(writer);
        size += SpriteAnimationSnapshot::bindingSize(*part,writer) + 1;
        if (part->mHasIKLimits && !part->mIKConstraint) size += 16;
        if (const auto* ik = part->isIKDriven()?nullptr:part->mIKTarget.get()) {
            size += writer->sizeof_uint(ik->middle) + writer->sizeof_uint(ik->tip) + 8 + 1;
            SnapshotWriter out(writer,false);out.flag(ik->bend==1);out.real(ik->influence,1);out.text(part->mIKError);size+=out.size();
        }
        size += writer->sizeof_bool(part->mDrawing != nullptr);
#ifndef PDG_NO_GUI
        if (part->mDrawing) size += drawingSerializedSize(part->mDrawing.get(), writer);
#endif
    }
    for (auto* part : mParts) size += part->physics->getSerializedSize(writer);
    return size;
}
void Sprite::serializeParts(ISerializer* writer) const {
    writer->serialize_uint(mNextPartId); writer->serialize_uint(mParts.size());
    for (auto* part : mParts) {
        writer->serialize_uint(part->mId); writer->serialize_string(part->mName);
        writer->serialize_uint(part->mParent ? part->mParent->mId : partId_None);
        part->Animated::serialize(writer);
        SpriteAnimationSnapshot::writeBinding(*part,writer);
        const auto* ik = part->isIKDriven()?nullptr:part->mIKTarget.get();
        writer->serialize_1u((ik ? (ik->reached ? 3 : 1) : 0) | ((part->mHasIKLimits && !part->mIKConstraint) ? 4 : 0) | (part->mAnimationPhysicsBody ? 8 : 0));
        if (part->mHasIKLimits && !part->mIKConstraint) { writer->serialize_d(part->mIKMinAngle); writer->serialize_d(part->mIKMaxAngle); }
        if (ik) {
            writer->serialize_uint(ik->middle); writer->serialize_uint(ik->tip);
            writer->serialize_f(ik->target.x); writer->serialize_f(ik->target.y);
            writer->serialize_1u(ik->space);
            SnapshotWriter out(writer,true);out.flag(ik->bend==1);out.real(ik->influence,1);out.text(part->mIKError);
        }
        writer->serialize_bool(part->mDrawing != nullptr);
#ifndef PDG_NO_GUI
        if (part->mDrawing) serializeDrawing(part->mDrawing.get(), writer);
#endif
    }
    // Parent links are established before any body publishes its world pose.
    for (auto* part : mParts) part->physics->serialize(writer);
}
void Sprite::deserializeParts(IDeserializer* reader) {
    const auto nextId = reader->deserialize_uint(), count = reader->deserialize_uint();
    if (count > 1000000) throw std::runtime_error("Too many Parts in Sprite snapshot");
    Sprite staged;
    staged.mLocation = mLocation; staged.mFacing = mFacing;
    staged.mScaleX = mScaleX; staged.mScaleY = mScaleY;
    staged.mFlipX = mFlipX; staged.mFlipY = mFlipY;
    SpriteAnimationSnapshot::clone(*this,staged);
    std::vector<PartId> parents;
    std::vector<std::unique_ptr<Part::IKTarget>> controllers;
    std::vector<std::string> controllerErrors;
    std::set<PartId> ids; std::set<std::string> names;
    for (uint32 i = 0; i < count; ++i) {
        const auto id = reader->deserialize_uint();
        const auto nameLength = reader->deserialize_strGetLen();
        if (nameLength == 0 || nameLength > 1000000) throw std::runtime_error("Invalid Part name length");
        std::string name; reader->deserialize_string(name);
        if (id == partId_None || id >= nextId || !ids.insert(id).second || name.empty() ||
            name.find('\0') != std::string::npos || !names.insert(name).second)
            throw std::runtime_error("Invalid or duplicate Part identity");
        parents.push_back(reader->deserialize_uint());
        auto part = std::unique_ptr<Part, void(*)(Part*)>(new Part(&staged, id, name), [](Part* p) { delete p; });
        part->Animated::deserialize(reader);
        SpriteAnimationSnapshot::readBinding(*part,reader);
        if (part->hasCurrentRig() && parents.back()!=partId_None) throw std::runtime_error("Authored Part cannot also have a Part parent");
        const auto controller = reader->deserialize_1u();
        if ((controller & ~15) || ((controller & 2) && !(controller & 1))) throw std::runtime_error("Invalid Part IK flags");
        const bool rigBody=controller & 8;
        if(rigBody && (controller & 7))throw std::runtime_error("Mapped rig body has independent Part IK");
        if (controller & 4) {
            const double lo=reader->deserialize_d(),hi=reader->deserialize_d();
            part->setIKLimits(lo,hi);
        }
        std::unique_ptr<Part::IKTarget> ik;
        std::string error;
        if (controller & 1) {
            ik = std::make_unique<Part::IKTarget>();
            ik->middle = reader->deserialize_uint(); ik->tip = reader->deserialize_uint();
            ik->target.x = reader->deserialize_f(); ik->target.y = reader->deserialize_f();
            ik->space = reader->deserialize_1u();
            const bool bend = reader->deserialize_bool();
            SnapshotReader in(reader);
            ik->bend = bend ? 1 : -1; ik->influence = in.real(1);
            ik->reached = (controller & 2) != 0;
            error=in.text();
        }
        controllers.push_back(std::move(ik)); controllerErrors.push_back(std::move(error));
        const bool artwork = reader->deserialize_bool();
        if (artwork) {
#ifndef PDG_NO_GUI
            part->mDrawing = deserializeDrawing(reader);
            if (!part->mDrawing) throw std::runtime_error("Missing Part Drawing content");
#else
            throw std::runtime_error("Part artwork snapshots require a GUI-capable build");
#endif
        }
        part->mAnimationPhysicsBody=rigBody;
        staged.mParts.push_back(part.get()); part->addRef(); part.release();
    }
    for (size_t i = 0; i < staged.mParts.size(); ++i) {
        if (parents[i] == partId_None) continue;
        auto* parent = staged.getPart(parents[i]);
        if (!parent) throw std::runtime_error("Missing Part parent in Sprite snapshot");
        // Links may point forward in creation order; setParentPart rejects cycles.
        staged.mParts[i]->setParentPart(parent);
    }
    for (auto* part : staged.mParts) {
        const auto mode = reader->deserialize_1u();
        if (mode == physicsBody_None) {
            if(part->mAnimationPhysicsBody)throw std::runtime_error("Missing mapped rig body");
            continue;
        }
        if (mode < physicsBody_Dynamic || mode > physicsBody_Static)
            throw std::runtime_error("Invalid Part body mode");
        auto body = std::make_unique<PhysicsBody>();
        if(part->mAnimationPhysicsBody)part->initializeAnimationPhysicsBody(*body);
        else part->initializePhysicsBody(*body, true);
        body.release();
        part->physics->deserialize(reader, mode);
    }
    // Resolve controllers only after every identity, parent link and body exists.
    for (size_t i = 0; i < staged.mParts.size(); ++i) {
        if (!controllers[i]) continue;
        auto* part = staged.mParts[i]; const auto& ik = *controllers[i];
        part->setIKTarget(staged.getPart(ik.middle), staged.getPart(ik.tip), ik.target, ik.space, ik.bend, ik.influence);
        part->mIKTarget->reached = ik.reached; part->mIKError = std::move(controllerErrors[i]);
    }
    clearParts();
    mParts.swap(staged.mParts); mNextPartId = nextId;
    for (auto* part : mParts) part->mSprite = this;
    for (auto* part : mParts) part->syncPhysicsSolver();
}

// Incremental animation updates preserve Part/artwork identity. They transfer
// sampled local poses and schedules; topology/resources/controllers remain in
// the initial record. A topology change requires a fresh initial snapshot.
uint32 Sprite::partMotionSize(ISerializer* writer) const {
    uint32 size=writer->sizeof_bool(!mParts.empty());
    if(mParts.empty())return size;
    size+=writer->sizeof_uint(mParts.size());
    for(auto* part:mParts) {
        part->validateSnapshot(true);
        size+=writer->sizeof_uint(part->mId);
        size+=part->Animated::getSerializedSize(writer);
    }
    return size;
}
void Sprite::serializePartMotion(ISerializer* writer) const {
    writer->serialize_bool(!mParts.empty());
    if(mParts.empty())return;
    writer->serialize_uint(mParts.size());
    for(auto* part:mParts) {
        part->validateSnapshot(true);
        writer->serialize_uint(part->mId);part->Animated::serialize(writer);
    }
}
void Part::adoptMotionSnapshot(const Part& saved) {
    const auto from=saved.tweenFields(),to=tweenFields();
    for(size_t i=0;i<to.size();++i)*const_cast<float*>(to[i])=*from[i];
    mAnimations=saved.mAnimations;
    for(auto& animation:mAnimations) {
        const auto field=std::find(from.begin(),from.end(),animation.value);
        animation.value=const_cast<float*>(to.at(field-from.begin()));
    }
    mDelaySeconds=saved.mDelaySeconds;mWaitPending=saved.mWaitPending;
    mAppendAnimation=saved.mAppendAnimation;mAnimationOperation=saved.mAnimationOperation;
    mSchedulePaused=saved.mSchedulePaused;mFlipX=saved.mFlipX;mFlipY=saved.mFlipY;
}
void Sprite::deserializePartMotion(IDeserializer* reader) {
    const auto count=reader->deserialize_bool() ? reader->deserialize_uint() : 0;
    if(count!=mParts.size())throw std::runtime_error("Part update topology changed; load a new initial Layer snapshot");
    using StagedPart=std::unique_ptr<Part,void(*)(Part*)>;
    std::vector<std::pair<Part*,StagedPart>> staged;std::set<PartId> seen;
    for(uint32 i=0;i<count;++i) {
        const auto id=reader->deserialize_uint();auto* part=getPart(id);
        if(!part || !seen.insert(id).second)throw std::runtime_error("Unknown or duplicate Part in animation update");
        StagedPart saved(new Part(nullptr,id,part->mName),[](Part* p){delete p;});
        saved->Animated::deserialize(reader);
        staged.emplace_back(part,std::move(saved));
    }
    for(auto& item:staged)item.first->adoptMotionSnapshot(*item.second);
    for(auto& item:staged)item.first->syncPhysicsTransform();
    updatePartAttachments();
}
