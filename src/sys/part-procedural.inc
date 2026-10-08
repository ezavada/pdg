// Independent Part adapters, included by sprite.cpp in namespace pdg.
namespace {
void stepPartJiggleFade(SpriteJiggleState& j,double dt) {
    if(j.config.enabled&&dt>0&&j.fadeDuration>0){j.fadeElapsed=std::min(j.fadeDuration,j.fadeElapsed+dt);j.config.influence=j.fadeStart+(j.fadeTarget-j.fadeStart)*j.fadeElapsed/j.fadeDuration;if(j.fadeElapsed==j.fadeDuration)j.fadeDuration=0;}
}
}
std::vector<Part*> Part::proceduralParts(const std::vector<PartId>& ids) const {
    std::vector<Part*> parts;for(auto id:ids){auto* p=mSprite?mSprite->getPart(id):nullptr;if(!p)throw std::logic_error("Detached procedural joint");parts.push_back(p);}return parts;
}
AnimationPose Part::proceduralPose(const std::vector<Part*>& parts,AnimationTransform& root) const {
    if(parts.empty()||parts[0]!=this||!mSprite)throw std::invalid_argument("Invalid Part procedural root");
    auto frame=physicsFrame();Point location;float angle;Offset scale;decomposeMount(frame,location,angle,scale);
    if(std::abs(std::abs(scale.x)-std::abs(scale.y))>1e-5*std::max(std::abs(scale.x),std::abs(scale.y)))throw std::invalid_argument("Procedural Part parent frame must be uniform");
    root.x=location.x;root.y=location.y;root.rotation=angle;root.scaleX=scale.x;root.scaleY=scale.y;
    std::vector<AnimationBone> bones;
    for(size_t i=0;i<parts.size();++i){auto* p=parts[i];if(!p||p->mSprite!=mSprite||(i&&p->mParent!=parts[i-1])||p->hasCurrentRig())throw std::invalid_argument("Procedural Parts require an independent contiguous chain");
        p->validateProgrammedTransform();double sx=p->mScaleX*(p->mFlipX?-1:1),sy=p->mScaleY*(p->mFlipY?-1:1);
        if(!std::isfinite(sx+sy)||sx==0||sy==0||std::abs(std::abs(sx)-std::abs(sy))>1e-5*std::max(std::abs(sx),std::abs(sy)))throw std::invalid_argument("Procedural Part scales must be nonsingular and uniform");
        AnimationTransform t;t.x=p->mLocation.x;t.y=p->mLocation.y;t.rotation=p->mFacing;t.scaleX=sx;t.scaleY=sy;
        bones.push_back({p->mName,i?AnimationBoneId(i-1):animation_NoBone,t,0});}
    return AnimationPose(AnimationRig::create(std::move(bones)));
}
void Part::applyProceduralPose(const std::vector<Part*>& parts,const AnimationPose& pose,size_t count) {
    for(size_t i=0;i<count;++i){auto* p=parts[i];p->mApplyingProcedural=true;p->setRotation(pose.getLocalTransform(i).rotation);p->mApplyingProcedural=false;}
}
void Part::claimProcedural(const std::vector<Part*>& parts) {
    for(auto* p:parts){if(p->mProceduralOwner&&p->mProceduralOwner!=this)throw std::logic_error("Overlapping procedural Part controllers");
        for(auto* other:mSprite->mParts)if(other->mIKTarget&&(p==other||p->mId==other->mIKTarget->middle||(other->isIKDriven()&&p->mId==other->mIKTarget->tip)))throw std::logic_error("Procedural chain overlaps Part IK");}
    releaseProcedural();for(auto* p:parts){p->mProceduralBase=p->mFacing;p->mProceduralOwner=this;}
}
void Part::releaseProcedural(){if(mSprite)for(auto* p:mSprite->mParts)if(p->mProceduralOwner==this){p->mFacing=p->mProceduralBase;p->mProceduralOwner=nullptr;p->syncPhysicsTransform();}}
void Part::restoreProceduralBase(){if(mProceduralOwner)mFacing=mProceduralBase;}
AnimationFABRIKResult Part::solveFABRIK(const std::vector<Part*>& following,const Point& target,const AnimationFABRIK& options) {
    if(mJiggle&&mJiggle->config.mode==jiggleMode_Chain)throw std::logic_error("FABRIK overlaps chain jiggle");
    std::vector<Part*> parts{this};parts.insert(parts.end(),following.begin(),following.end());AnimationTransform root;auto pose=proceduralPose(parts,root);auto c=options;c.chain.clear();c.minimum.clear();c.maximum.clear();
    for(size_t i=0;i+1<parts.size();++i)for(auto* other:mSprite->mParts)if(other->mIKTarget&&(parts[i]==other||parts[i]->mId==other->mIKTarget->middle))throw std::logic_error("FABRIK overlaps Part IK");
    for(size_t i=0;i<parts.size();++i){c.chain.push_back(i);if(i+1<parts.size()){if(parts[i]->mProceduralOwner&&parts[i]->mProceduralOwner!=this)throw std::logic_error("Part rotation owned by another controller");c.minimum.push_back(parts[i]->hasIKLimits()?parts[i]->getIKMinAngle():-std::numbers::pi);c.maximum.push_back(parts[i]->hasIKLimits()?parts[i]->getIKMaxAngle():std::numbers::pi);}}
    c.targetX=target.x;c.targetY=target.y; // Part Sprite frame differs from the chain parent's frame.
    if(c.space==partSpace_Sprite){auto world=mSprite->partRootTransform().transformPoint(target);c.targetX=world.x;c.targetY=world.y;c.space=animationSpace_World;}
    auto r=solveAnimationFABRIK(pose,c,root);if(c.influence>0){for(size_t i=0;i+1<parts.size();++i){parts[i]->cancelAnimation(&parts[i]->mDeltaFacingPerMs);parts[i]->mDeltaFacingPerMs=0;}applyProceduralPose(parts,pose,parts.size()-1);}return r;
}
Part& Part::setFABRIKTarget(const std::vector<Part*>& following,const Point& target,const AnimationFABRIK& options) {
    if(mJiggle&&mJiggle->config.mode==jiggleMode_Chain)throw std::logic_error("Clear chain jiggle before installing FABRIK");
    std::vector<Part*> parts{this};parts.insert(parts.end(),following.begin(),following.end());AnimationTransform root;auto pose=proceduralPose(parts,root);auto c=options;c.chain.clear();for(size_t i=0;i<parts.size();++i)c.chain.push_back(i);c.targetX=target.x;c.targetY=target.y;solveAnimationFABRIK(pose,c,root);
    std::vector<Part*> rotating(parts.begin(),parts.end()-1);claimProcedural(rotating);auto state=std::make_unique<PartFABRIKState>();state->config=options;state->config.targetX=target.x;state->config.targetY=target.y;for(auto* p:parts)state->chain.push_back(p->mId);mFABRIK=std::move(state);return *this;
}
AnimationFABRIKResult Part::getFABRIKResult() const {if(!mFABRIK)throw std::logic_error("No FABRIK controller");return mFABRIK->result;}
Part& Part::setJiggle(const AnimationJiggle& config,const std::vector<Part*>& following) {
    if(config.mode==jiggleMode_Chain&&mFABRIK)throw std::logic_error("Clear FABRIK before installing chain jiggle");
    auto checked=config;if(checked.mode==jiggleMode_Chain){checked.chain.clear();checked.chain.push_back(mId);for(auto* p:following)if(p)checked.chain.push_back(p->mId);}validateAnimationJiggle(checked);auto j=std::make_shared<SpriteJiggleState>();j->config=config;std::vector<Part*> parts{this};parts.insert(parts.end(),following.begin(),following.end());
    if(config.mode==jiggleMode_IKTarget){if(!mIKTarget||!following.empty())throw std::logic_error("Target jiggle requires scheduled Part IK");Point target=mIKTarget->target;if(mIKTarget->space==partSpace_Local)target=physicsFrame().transformPoint(target);else if(mIKTarget->space==partSpace_Sprite)target=mSprite->partRootTransform().transformPoint(target);j->result=stepJiggleTarget(config,j->state,target.x,target.y,0);}
    else{AnimationTransform root;auto pose=proceduralPose(parts,root);j->config=checked;auto local=checked;local.chain.clear();for(size_t i=0;i<parts.size();++i)local.chain.push_back(i);
        for(auto& override:local.joints){auto f=std::find_if(parts.begin(),parts.end(),[&](Part* p){return p->mId==override.bone;});if(f==parts.end())throw std::invalid_argument("Unknown jiggle Part override");override.bone=f-parts.begin();}
        j->result=solveAnimationJiggle(pose,local,j->state,0,root);claimProcedural(parts);}

    mJiggleChain.clear();for(auto* p:parts)mJiggleChain.push_back(p->mId);mJiggle=std::move(j);return *this;
}
Part& Part::clearJiggle(){if(mJiggle&&mJiggle->config.mode==jiggleMode_Chain)releaseProcedural();mJiggle.reset();mJiggleChain.clear();mProceduralError.clear();return *this;}
AnimationJiggle Part::getJiggleOptions() const {if(!mJiggle)throw std::logic_error("No jiggle controller");return mJiggle->config;}
Part& Part::setJiggleSettings(const AnimationJiggle& c){validateAnimationJiggle(c);if(!mJiggle||c.mode!=mJiggle->config.mode||c.chain!=mJiggle->config.chain)throw std::invalid_argument("Jiggle topology mismatch");mJiggle->config=c;return *this;}
Part& Part::setJiggleEnabled(bool enabled){if(!mJiggle)throw std::logic_error("No jiggle controller");if(enabled&&!mJiggle->config.enabled)mJiggle->state={};mJiggle->config.enabled=enabled;return *this;}
bool Part::isJiggleEnabled() const{return getJiggleOptions().enabled;}
Part& Part::setJiggleInfluence(double influence,double seconds){if(!mJiggle||!std::isfinite(influence)||influence<0||influence>1||!std::isfinite(seconds)||seconds<0)throw std::invalid_argument("Invalid jiggle fade");auto& j=*mJiggle;j.fadeStart=j.config.influence;j.fadeTarget=influence;j.fadeElapsed=0;j.fadeDuration=seconds;if(!seconds)j.config.influence=influence;return *this;}
Part& Part::resetJiggle(){if(!mJiggle)throw std::logic_error("No jiggle controller");mJiggle->state={};stepProcedural(0);if(mJiggle->config.mode==jiggleMode_IKTarget)applyIKTarget(0);return *this;}
Part& Part::kickJiggle(double x,double y,int joint){if(!mJiggle||!mJiggle->config.enabled||!std::isfinite(x)||!std::isfinite(y))throw std::invalid_argument("Invalid jiggle kick");auto state=mJiggle->state;if(mJiggle->config.mode==jiggleMode_IKTarget){state.velocityX+=x;state.velocityY+=y;}else{if(joint<0||size_t(joint)>=state.joints.size())throw std::out_of_range("Unknown jiggle joint");state.joints[joint].velocity+=x;}return setJiggleState(state);}
JiggleResult Part::getJiggleResult() const{if(!mJiggle)throw std::logic_error("No jiggle controller");return mJiggle->result;}
JiggleState Part::getJiggleState() const{if(!mJiggle)throw std::logic_error("No jiggle controller");return mJiggle->state;}
Part& Part::setJiggleState(const JiggleState& s){if(!mJiggle||s.joints.size()!=mJiggle->state.joints.size())throw std::invalid_argument("Jiggle state topology mismatch");for(double v:{s.x,s.y,s.velocityX,s.velocityY})if(!std::isfinite(v))throw std::invalid_argument("Nonfinite jiggle state");for(auto& j:s.joints)for(double v:{j.angle,j.velocity,j.desired,j.pivotX,j.pivotY,j.pivotVelocityX,j.pivotVelocityY})if(!std::isfinite(v))throw std::invalid_argument("Nonfinite jiggle state");mJiggle->state=s;return *this;}
bool Part::stepProcedural(double seconds) {
    try{
        if(mFABRIK){auto parts=proceduralParts(mFABRIK->chain);std::vector<Part*> rest(parts.begin()+1,parts.end());mFABRIK->result=solveFABRIK(rest,Point(mFABRIK->config.targetX,mFABRIK->config.targetY),mFABRIK->config);mProceduralError.clear();return true;}
        if(!mJiggle||mJiggle->config.mode!=jiggleMode_Chain)return false;
        auto parts=proceduralParts(mJiggleChain);AnimationTransform root;auto pose=proceduralPose(parts,root);auto next=*mJiggle;stepPartJiggleFade(next,seconds);std::vector<double> lo,hi;for(auto* p:parts){lo.push_back(p->hasIKLimits()?p->getIKMinAngle():-std::numbers::pi);hi.push_back(p->hasIKLimits()?p->getIKMaxAngle():std::numbers::pi);}
        auto local=next.config;local.chain.clear();for(size_t i=0;i<parts.size();++i)local.chain.push_back(i);for(auto& override:local.joints){auto f=std::find(mJiggleChain.begin(),mJiggleChain.end(),override.bone);if(f==mJiggleChain.end())throw std::invalid_argument("Unknown jiggle override");override.bone=f-mJiggleChain.begin();}
        next.result=solveAnimationJiggle(pose,local,next.state,seconds,root,lo,hi);applyProceduralPose(parts,pose,parts.size());*mJiggle=std::move(next);mProceduralError.clear();return true;
    }catch(const std::exception& e){mProceduralError=e.what();if(mJiggle)mJiggle->state.initialized=false;return false;}
}
std::vector<double> Part::proceduralControl(int operation,const std::vector<double>& values) {
    ProceduralValues v(values);
    auto following=[&](const std::vector<uint32_t>& ids){std::vector<Part*> p;for(auto id:ids){auto* part=mSprite?mSprite->getPart(id):nullptr;if(!part)throw std::invalid_argument("Unknown Part joint");p.push_back(part);}return p;};
    switch(operation){
    case 1:case 2:{auto c=decodeFABRIK(v);v.end();auto p=following(c.chain);if(operation==1)return encodeFABRIKResult(solveFABRIK(p,Point(c.targetX,c.targetY),c));setFABRIKTarget(p,Point(c.targetX,c.targetY),c);break;}
    case 3:v.end();return encodeFABRIKResult(getFABRIKResult());
    case 4:{auto c=decodeJiggle(v);v.end();auto p=following(c.chain);setJiggle(c,p);break;}
    case 5:v.end();clearJiggle();break;
    case 6:v.end();return {double(hasJiggle())};
    case 7:v.end();{auto c=getJiggleOptions();c.chain=mJiggleChain;if(!c.chain.empty())c.chain.erase(c.chain.begin());return encodeJiggle(c);}
    case 8:{auto c=decodeJiggle(v);v.end();c.chain=mJiggle->config.chain;setJiggleSettings(c);break;}
    case 9:{bool enabled=v.flag();v.end();setJiggleEnabled(enabled);break;}
    case 10:v.end();return {double(isJiggleEnabled())};
    case 11:{double influence=v.real(),seconds=v.real();v.end();setJiggleInfluence(influence,seconds);break;}
    case 12:v.end();resetJiggle();break;
    case 13:{double x=v.real(),y=v.real();auto joint=v.integer();v.end();kickJiggle(x,y,joint);break;}
    case 14:v.end();return encodeJiggleResult(getJiggleResult());
    case 15:v.end();return encodeJiggleState(getJiggleState());
    case 16:{auto state=decodeJiggleState(v);v.end();setJiggleState(state);break;}
    default:throw std::invalid_argument("Unknown Part procedural operation");
    }return {};
}
