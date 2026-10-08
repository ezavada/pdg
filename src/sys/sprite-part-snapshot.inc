namespace {
void validateProceduralFade(const SpriteJiggleState& j){
    for(double x:{j.fadeStart,j.fadeTarget,j.fadeElapsed,j.fadeDuration})if(!std::isfinite(x))throw std::runtime_error("Nonfinite jiggle fade");
    if(j.fadeStart<0||j.fadeStart>1||j.fadeTarget<0||j.fadeTarget>1||j.fadeElapsed<0||j.fadeDuration<0||(j.fadeDuration>0&&j.fadeElapsed>j.fadeDuration))throw std::runtime_error("Invalid jiggle fade");
}
uint32 proceduralSnapshotValues(ISerializer* writer,bool emit,const std::vector<double>& values) {SnapshotWriter out(writer,emit);out.integer(values.size());for(double v:values)out.real(v);return out.size();}
std::vector<double> readProceduralSnapshotValues(IDeserializer* reader){SnapshotReader in(reader);auto n=reader->deserialize_uint();if(n>50000)throw std::runtime_error("Procedural snapshot too large");std::vector<double> v;while(n--){double x=in.real();if(!std::isfinite(x))throw std::runtime_error("Nonfinite procedural state");v.push_back(x);}return v;}
}
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
        if(part->mProceduralOwner)size+=8;
        if (part->mHasIKLimits && !part->mIKConstraint) size += 16;
        if (const auto* ik = part->isIKDriven()?nullptr:part->mIKTarget.get()) {
            size += writer->sizeof_uint(ik->middle) + writer->sizeof_uint(ik->tip) + 8 + 1;
            SnapshotWriter out(writer,false);out.flag(ik->bend==1);out.real(ik->influence,1);out.text(part->mIKError);size+=out.size();
        }
        if(part->mJiggle){size+=proceduralSnapshotValues(writer,false,encodeJiggle(part->mJiggle->config));size+=proceduralSnapshotValues(writer,false,encodeJiggleState(part->mJiggle->state));std::vector<double> ids(part->mJiggleChain.begin(),part->mJiggleChain.end());size+=proceduralSnapshotValues(writer,false,ids);SnapshotWriter out(writer,false);for(double x:{part->mJiggle->fadeStart,part->mJiggle->fadeTarget,part->mJiggle->fadeElapsed,part->mJiggle->fadeDuration})out.real(x);size+=out.size();}
        if(part->mFABRIK){auto c=part->mFABRIK->config;c.chain=part->mFABRIK->chain;size+=proceduralSnapshotValues(writer,false,encodeFABRIK(c));}
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
        writer->serialize_1u((ik ? (ik->reached ? 3 : 1) : 0) | ((part->mHasIKLimits && !part->mIKConstraint) ? 4 : 0) | (part->mAnimationPhysicsBody ? 8 : 0) | (part->mJiggle?16:0) | (part->mFABRIK?32:0) | (part->mProceduralOwner?64:0));
        if(part->mProceduralOwner)writer->serialize_d(part->mProceduralBase);
        if (part->mHasIKLimits && !part->mIKConstraint) { writer->serialize_d(part->mIKMinAngle); writer->serialize_d(part->mIKMaxAngle); }
        if (ik) {
            writer->serialize_uint(ik->middle); writer->serialize_uint(ik->tip);
            writer->serialize_f(ik->target.x); writer->serialize_f(ik->target.y);
            writer->serialize_1u(ik->space);
            SnapshotWriter out(writer,true);out.flag(ik->bend==1);out.real(ik->influence,1);out.text(part->mIKError);
        }
        if(part->mJiggle){proceduralSnapshotValues(writer,true,encodeJiggle(part->mJiggle->config));proceduralSnapshotValues(writer,true,encodeJiggleState(part->mJiggle->state));std::vector<double> ids(part->mJiggleChain.begin(),part->mJiggleChain.end());proceduralSnapshotValues(writer,true,ids);SnapshotWriter out(writer,true);for(double x:{part->mJiggle->fadeStart,part->mJiggle->fadeTarget,part->mJiggle->fadeElapsed,part->mJiggle->fadeDuration})out.real(x);}
        if(part->mFABRIK){auto c=part->mFABRIK->config;c.chain=part->mFABRIK->chain;proceduralSnapshotValues(writer,true,encodeFABRIK(c));}
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
    std::vector<std::optional<double>> bases;
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
        if ((controller & ~127) || ((controller & 2) && !(controller & 1))) throw std::runtime_error("Invalid Part IK flags");
        bases.push_back((controller&64)?std::optional<double>(reader->deserialize_d()):std::nullopt);
        if(bases.back()&&!std::isfinite(*bases.back()))throw std::runtime_error("Invalid procedural base rotation");
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
        if(controller&16){auto configValues=readProceduralSnapshotValues(reader);ProceduralValues cv(configValues);auto config=decodeJiggle(cv);cv.end();auto stateValues=readProceduralSnapshotValues(reader);ProceduralValues sv(stateValues);auto state=decodeJiggleState(sv);sv.end();auto ids=readProceduralSnapshotValues(reader);part->mJiggle=std::make_shared<SpriteJiggleState>();part->mJiggle->config=config;part->mJiggle->state=state;for(double id:ids){if(id<0||id>=partId_None||id!=std::floor(id))throw std::runtime_error("Invalid saved jiggle Part ID");part->mJiggleChain.push_back(PartId(id));}SnapshotReader in(reader);part->mJiggle->fadeStart=in.real();part->mJiggle->fadeTarget=in.real();part->mJiggle->fadeElapsed=in.real();part->mJiggle->fadeDuration=in.real();validateProceduralFade(*part->mJiggle);}
        if(controller&32){auto values=readProceduralSnapshotValues(reader);ProceduralValues v(values);auto c=decodeFABRIK(v);v.end();part->mFABRIK=std::make_unique<Part::PartFABRIKState>();part->mFABRIK->chain=c.chain;part->mFABRIK->config=c;}
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
    for(auto* part:staged.mParts) {
        if(part->mFABRIK){auto saved=*part->mFABRIK;auto parts=part->proceduralParts(saved.chain);std::vector<Part*> rest(parts.begin()+1,parts.end());part->setFABRIKTarget(rest,Point(saved.config.targetX,saved.config.targetY),saved.config);}
        if(part->mJiggle){auto saved=*part->mJiggle;auto ids=part->mJiggleChain;auto parts=part->proceduralParts(ids);if(parts.empty()||parts.front()!=part)throw std::runtime_error("Invalid saved jiggle chain");std::vector<Part*> rest(parts.begin()+1,parts.end());part->setJiggle(saved.config,rest);part->setJiggleState(saved.state);*part->mJiggle=saved;}
    }
    for(size_t i=0;i<staged.mParts.size();++i){auto* part=staged.mParts[i];
        if(bool(part->mProceduralOwner)!=bool(bases[i]))throw std::runtime_error("Saved procedural ownership mismatch");
        if(bases[i])part->mProceduralBase=*bases[i];}
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
    bool procedural=std::any_of(mParts.begin(),mParts.end(),[](auto* p){return p->mJiggle||p->mFABRIK;});
    size+=writer->sizeof_uint(uint32(mParts.size())|(procedural?0x80000000u:0));
    for(auto* part:mParts) {
        part->validateSnapshot(true);
        size+=writer->sizeof_uint(part->mId);
        size+=part->Animated::getSerializedSize(writer);
        if(procedural){size+=1;if(part->mProceduralOwner)size+=8;
            if(part->mJiggle){size+=proceduralSnapshotValues(writer,false,encodeJiggle(part->mJiggle->config));size+=proceduralSnapshotValues(writer,false,encodeJiggleState(part->mJiggle->state));SnapshotWriter out(writer,false);for(double x:{part->mJiggle->fadeStart,part->mJiggle->fadeTarget,part->mJiggle->fadeElapsed,part->mJiggle->fadeDuration})out.real(x);size+=out.size();}
            if(part->mFABRIK){auto c=part->mFABRIK->config;c.chain=part->mFABRIK->chain;size+=proceduralSnapshotValues(writer,false,encodeFABRIK(c));}}

    }
    return size;
}
void Sprite::serializePartMotion(ISerializer* writer) const {
    writer->serialize_bool(!mParts.empty());
    if(mParts.empty())return;
    bool procedural=std::any_of(mParts.begin(),mParts.end(),[](auto* p){return p->mJiggle||p->mFABRIK;});
    writer->serialize_uint(uint32(mParts.size())|(procedural?0x80000000u:0));
    for(auto* part:mParts) {
        part->validateSnapshot(true);
        writer->serialize_uint(part->mId);part->Animated::serialize(writer);
        if(procedural){writer->serialize_1u((part->mProceduralOwner?1:0)|(part->mJiggle?2:0)|(part->mFABRIK?4:0));
            if(part->mProceduralOwner)writer->serialize_d(part->mProceduralBase);
            if(part->mJiggle){proceduralSnapshotValues(writer,true,encodeJiggle(part->mJiggle->config));proceduralSnapshotValues(writer,true,encodeJiggleState(part->mJiggle->state));SnapshotWriter out(writer,true);for(double x:{part->mJiggle->fadeStart,part->mJiggle->fadeTarget,part->mJiggle->fadeElapsed,part->mJiggle->fadeDuration})out.real(x);}
            if(part->mFABRIK){auto c=part->mFABRIK->config;c.chain=part->mFABRIK->chain;proceduralSnapshotValues(writer,true,encodeFABRIK(c));}}

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
    const auto encodedCount=reader->deserialize_bool() ? reader->deserialize_uint() : 0;
    const bool procedural=encodedCount&0x80000000u;const auto count=encodedCount&0x7fffffffu;
    if(!procedural&&std::any_of(mParts.begin(),mParts.end(),[](auto* p){return p->mJiggle||p->mFABRIK;}))throw std::runtime_error("Procedural topology changed; load an initial snapshot");
    if(count!=mParts.size())throw std::runtime_error("Part update topology changed; load a new initial Layer snapshot");
    using StagedPart=std::unique_ptr<Part,void(*)(Part*)>;
    std::vector<std::pair<Part*,StagedPart>> staged;std::set<PartId> seen;
    for(uint32 i=0;i<count;++i) {
        const auto id=reader->deserialize_uint();auto* part=getPart(id);
        if(!part || !seen.insert(id).second)throw std::runtime_error("Unknown or duplicate Part in animation update");
        StagedPart saved(new Part(nullptr,id,part->mName),[](Part* p){delete p;});
        saved->Animated::deserialize(reader);
        if(procedural){auto flags=reader->deserialize_1u();
            if(flags!=((part->mProceduralOwner?1:0)|(part->mJiggle?2:0)|(part->mFABRIK?4:0)))throw std::runtime_error("Procedural topology changed; load an initial snapshot");
            if(flags&1){double base=reader->deserialize_d();if(!std::isfinite(base))throw std::runtime_error("Nonfinite procedural base");saved->mProceduralBase=base;}
            if(flags&2){auto values=readProceduralSnapshotValues(reader);ProceduralValues v(values);auto config=decodeJiggle(v);v.end();validateAnimationJiggle(config);
                if(config.mode!=part->mJiggle->config.mode||config.chain!=part->mJiggle->config.chain||config.ik!=part->mJiggle->config.ik)throw std::runtime_error("Jiggle topology changed");
                values=readProceduralSnapshotValues(reader);ProceduralValues sv(values);auto state=decodeJiggleState(sv);sv.end();if(state.initialized&&state.joints.size()!=(config.mode==jiggleMode_Chain?config.chain.size():0))throw std::runtime_error("Jiggle state topology changed");
                saved->mJiggle=std::make_shared<SpriteJiggleState>(*part->mJiggle);saved->mJiggle->config=config;saved->mJiggle->state=state;
                SnapshotReader in(reader);saved->mJiggle->fadeStart=in.real();saved->mJiggle->fadeTarget=in.real();saved->mJiggle->fadeElapsed=in.real();saved->mJiggle->fadeDuration=in.real();validateProceduralFade(*saved->mJiggle);}
            if(flags&4){auto values=readProceduralSnapshotValues(reader);ProceduralValues v(values);auto c=decodeFABRIK(v);v.end();if(c.chain!=part->mFABRIK->chain)throw std::runtime_error("FABRIK topology changed");
                AnimationTransform root;auto pose=part->proceduralPose(part->proceduralParts(c.chain),root);auto local=c;local.chain.clear();for(size_t i=0;i<c.chain.size();++i)local.chain.push_back(i);solveAnimationFABRIK(pose,local,root);
                saved->mFABRIK=std::make_unique<Part::PartFABRIKState>(*part->mFABRIK);saved->mFABRIK->config=c;}}
        staged.emplace_back(part,std::move(saved));
    }
    for(auto& item:staged){item.first->adoptMotionSnapshot(*item.second);
        if(procedural){if(item.first->mProceduralOwner)item.first->mProceduralBase=item.second->mProceduralBase;
            if(item.second->mJiggle)*item.first->mJiggle=*item.second->mJiggle;
            if(item.second->mFABRIK)*item.first->mFABRIK=*item.second->mFABRIK;}}
    for(auto& item:staged)item.first->syncPhysicsTransform();
    updatePartAttachments();
}
