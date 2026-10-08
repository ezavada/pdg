// Included inside PDG_SPRITER_SUPPORT, namespace pdg, by sprite.cpp.
namespace {
void validateJiggleEdit() {
    if(AnimationPipeline::isInsideCallback())throw std::logic_error("Edit jiggle controls outside modifiers");
}
AnimationTransform jiggleWorldTarget(const AnimationPose& pose,const AnimationTwoBoneIK& c,const AnimationTransform& root) {
    AnimationTransform t;t.x=c.targetX;t.y=c.targetY;
    if(c.space==animationSpace_Rig)return AnimationTransform::compose(root,t);
    if(c.space==animationSpace_Local){auto parent=pose.getRig()->getBone(c.root).parent;return AnimationTransform::compose(parent==animation_NoBone?root:pose.getWorldTransform(parent,root),t);}
    return t;
}
void jiggleFade(SpriteJiggleState& j,double seconds) {
    if(j.config.enabled&&j.fadeDuration>0&&seconds>0){j.fadeElapsed=std::min(j.fadeDuration,j.fadeElapsed+seconds);j.config.influence=j.fadeStart+(j.fadeTarget-j.fadeStart)*j.fadeElapsed/j.fadeDuration;if(j.fadeElapsed==j.fadeDuration)j.fadeDuration=0;}
}
JiggleResult advanceSpriteJiggle(SpriteJiggleState& j,double x,double y,double seconds) {
    auto next=j;jiggleFade(next,seconds);next.result=stepJiggleTarget(next.config,next.state,x,y,seconds);j=std::move(next);return j.result;
}
void validateJiggleState(const JiggleState& s,size_t joints) {
    if(s.initialized && s.joints.size()!=joints)throw std::invalid_argument("Jiggle state topology mismatch");
    for(double v:{s.x,s.y,s.velocityX,s.velocityY})if(!std::isfinite(v))throw std::invalid_argument("Invalid jiggle state");
    for(const auto& j:s.joints)for(double v:{j.angle,j.velocity,j.desired,j.pivotX,j.pivotY,j.pivotVelocityX,j.pivotVelocityY})if(!std::isfinite(v))throw std::invalid_argument("Invalid jiggle joint state");
}
}
AnimationModifierId Sprite::addAnimationFABRIK(const AnimationFABRIK& config,int order) {
    if(config.chain.size()<3)throw std::invalid_argument("FABRIK requires two joints and endpoint");
    for(auto& [id,j]:mAnimationJiggle)if(j->config.mode==jiggleMode_Chain)for(auto bone:j->config.chain)if(std::find(config.chain.begin(),config.chain.end()-1,bone)!=config.chain.end()-1)throw std::logic_error("FABRIK overlaps jiggle rotations");
    for(auto& [id,ik]:mAnimationIK)for(auto bone:{ik->config.root,ik->config.middle})if(std::find(config.chain.begin(),config.chain.end()-1,bone)!=config.chain.end()-1)throw std::logic_error("FABRIK overlaps IK rotations");
    for(auto& [id,f]:mAnimationFABRIK)for(auto bone:config.chain)if(bone!=config.chain.back()&&std::find(f->config.chain.begin(),f->config.chain.end()-1,bone)!=f->config.chain.end()-1)throw std::logic_error("Overlapping FABRIK chain");
    auto candidate=getAnimationPose();auto state=std::make_shared<FABRIKState>();state->config=config;
    state->result=solveAnimationFABRIK(candidate,config,spriterRootTransform());
    const auto id=addAnimationModifier([this,state](AnimationPoseView view,const AnimationModifierContext& ctx){
        auto pose=view.copy();auto c=state->config;size_t n=c.chain.size()-1;
        if(c.minimum.empty()){c.minimum.assign(n,-std::numbers::pi);c.maximum.assign(n,std::numbers::pi);}
        for(size_t i=0;i<n;++i)if(auto b=mBones.find(c.chain[i]);b!=mBones.end())if(auto limits=b->second->rotationLimits(pose)){c.minimum[i]=std::max(c.minimum[i],limits->first);c.maximum[i]=std::min(c.maximum[i],limits->second);}
        auto result=solveAnimationFABRIK(pose,c,ctx.root);
        for(size_t i=0;i<n;++i)view.setLocalTransform(c.chain[i],pose.getLocalTransform(c.chain[i]));
        state->result=result;
    },animationStage_Constraint,order);
    mAnimationFABRIK.emplace(id,state);return id;
}
AnimationFABRIKResult Sprite::getAnimationFABRIKResult(AnimationModifierId id) const {
    auto pose=getAnimationPose();auto f=mAnimationFABRIK.find(id);if(f==mAnimationFABRIK.end())throw std::out_of_range("Unknown FABRIK ID");
    auto error=mAnimationPipeline->getModifierError(id);if(!error.empty())throw std::logic_error(error);
    return f->second->result;
}
AnimationModifierId Sprite::addAnimationJiggle(const AnimationJiggle& config,int order) {
    validateJiggleEdit();validateAnimationJiggle(config);auto candidate=getAnimationPose();auto j=std::make_shared<SpriteJiggleState>();j->config=config;
    if(config.mode==jiggleMode_IKTarget){
        auto ik=mAnimationIK.find(config.ik);if(ik==mAnimationIK.end())throw std::out_of_range("Jiggle requires an existing two-bone IK ID");
        if(ik->second->jiggle||order)throw std::logic_error("IK target has jiggle already, or nonzero decorator order");
        auto t=jiggleWorldTarget(candidate,ik->second->config,spriterRootTransform());j->result=stepJiggleTarget(config,j->state,t.x,t.y,0);
        auto id=addAnimationModifier([](auto,const auto&){},animationStage_PreConstraint);mAnimationJiggle[id]=j;ik->second->jiggle=j;return id;
    }
    for(auto bone:config.chain){for(auto& [id,ik]:mAnimationIK)if(bone==ik->config.root||bone==ik->config.middle)throw std::logic_error("Jiggle overlaps IK rotations");
        for(auto& [id,f]:mAnimationFABRIK)if(std::find(f->config.chain.begin(),f->config.chain.end()-1,bone)!=f->config.chain.end()-1)throw std::logic_error("Jiggle overlaps FABRIK rotations");
        for(auto& [id,other]:mAnimationJiggle)if(std::find(other->config.chain.begin(),other->config.chain.end(),bone)!=other->config.chain.end())throw std::logic_error("Overlapping jiggle chain");}
    j->result=solveAnimationJiggle(candidate,config,j->state,0,spriterRootTransform());
    auto id=addAnimationModifier([this,j](AnimationPoseView view,const AnimationModifierContext& ctx){
        auto next=*j;auto pose=view.copy();jiggleFade(next,ctx.simulationDeltaSeconds);std::vector<double> lo,hi;
        for(auto bone:j->config.chain){double a=-std::numbers::pi,b=std::numbers::pi;if(auto f=mBones.find(bone);f!=mBones.end())if(auto l=f->second->rotationLimits(pose)){a=l->first;b=l->second;}lo.push_back(a);hi.push_back(b);}
        next.result=solveAnimationJiggle(pose,next.config,next.state,ctx.simulationDeltaSeconds,ctx.root,lo,hi);
        for(auto bone:j->config.chain)view.setLocalTransform(bone,pose.getLocalTransform(bone));
        *j=std::move(next);
    },animationStage_PostConstraint,order);mAnimationJiggle[id]=j;return id;
}
AnimationJiggle Sprite::getAnimationJiggleOptions(AnimationModifierId id) const {return mAnimationJiggle.at(id)->config;}
void Sprite::setAnimationJiggleSettings(AnimationModifierId id,const AnimationJiggle& c) {
    validateJiggleEdit();validateAnimationJiggle(c);auto& j=*mAnimationJiggle.at(id);if(c.mode!=j.config.mode||c.chain!=j.config.chain||c.ik!=j.config.ik)throw std::invalid_argument("Jiggle topology is immutable");j.config=c;invalidateSpriterPose();
}
void Sprite::setAnimationJiggleEnabled(AnimationModifierId id,bool enabled){validateJiggleEdit();auto& j=*mAnimationJiggle.at(id);if(enabled&&!j.config.enabled)j.state={};j.config.enabled=enabled;invalidateSpriterPose();}
bool Sprite::isAnimationJiggleEnabled(AnimationModifierId id) const{return mAnimationJiggle.at(id)->config.enabled;}
void Sprite::setAnimationJiggleInfluence(AnimationModifierId id,double influence,double seconds){validateJiggleEdit();if(!std::isfinite(influence)||influence<0||influence>1||!std::isfinite(seconds)||seconds<0)throw std::invalid_argument("Invalid jiggle fade");auto& j=*mAnimationJiggle.at(id);j.fadeStart=j.config.influence;j.fadeTarget=influence;j.fadeElapsed=0;j.fadeDuration=seconds;if(!seconds)j.config.influence=influence;invalidateSpriterPose();}
void Sprite::resetAnimationJiggle(AnimationModifierId id){validateJiggleEdit();mAnimationJiggle.at(id)->state={};invalidateSpriterPose();getAnimationPose();}
void Sprite::kickAnimationJiggle(AnimationModifierId id,double x,double y,int joint){validateJiggleEdit();if(!std::isfinite(x)||!std::isfinite(y))throw std::invalid_argument("Invalid jiggle kick");getAnimationPose();auto& j=*mAnimationJiggle.at(id);if(!j.config.enabled)throw std::logic_error("Disabled jiggle");auto next=j.state;if(j.config.mode==jiggleMode_IKTarget){next.velocityX+=x;next.velocityY+=y;}else{if(joint<0||size_t(joint)>=next.joints.size())throw std::out_of_range("Unknown jiggle joint");next.joints[joint].velocity+=x;}validateJiggleState(next,j.config.chain.size());j.state=std::move(next);}
JiggleResult Sprite::getAnimationJiggleResult(AnimationModifierId id) const{getAnimationPose();return mAnimationJiggle.at(id)->result;}
JiggleState Sprite::getAnimationJiggleState(AnimationModifierId id) const{getAnimationPose();return mAnimationJiggle.at(id)->state;}
void Sprite::setAnimationJiggleState(AnimationModifierId id,const JiggleState& state){validateJiggleEdit();auto& j=*mAnimationJiggle.at(id);validateJiggleState(state,j.config.chain.size());j.state=state;invalidateSpriterPose();}
void Sprite::removeAnimationJiggle(AnimationModifierId id){(void)mAnimationJiggle.at(id);removeAnimationModifier(id);}
std::vector<double> Sprite::proceduralControl(int operation,const std::vector<double>& values) {
    ProceduralValues v(values);AnimationModifierId id=0;
    if(operation!=1&&operation!=3)id=v.integer();
    switch(operation){
    case 1:{auto c=decodeFABRIK(v);double order=v.real();v.end();if(order!=std::floor(order)||order<-2147483648.0||order>2147483647.0)throw std::invalid_argument("Invalid modifier order");return {double(addAnimationFABRIK(c,int(order)))};}
    case 2:v.end();return encodeFABRIKResult(getAnimationFABRIKResult(id));
    case 3:{auto c=decodeJiggle(v);double order=v.real();v.end();if(order!=std::floor(order)||order<-2147483648.0||order>2147483647.0)throw std::invalid_argument("Invalid modifier order");return {double(addAnimationJiggle(c,int(order)))};}
    case 4:v.end();return encodeJiggle(getAnimationJiggleOptions(id));
    case 5:{auto c=decodeJiggle(v);v.end();setAnimationJiggleSettings(id,c);break;}
    case 6:{bool enabled=v.flag();v.end();setAnimationJiggleEnabled(id,enabled);break;}
    case 7:v.end();return {double(isAnimationJiggleEnabled(id))};
    case 8:{double influence=v.real(),seconds=v.real();v.end();setAnimationJiggleInfluence(id,influence,seconds);break;}
    case 9:v.end();resetAnimationJiggle(id);break;
    case 10:{double x=v.real(),y=v.real(),joint=v.real();v.end();if(joint!=std::floor(joint)||joint<-1||joint>4096)throw std::invalid_argument("Invalid jiggle joint index");kickAnimationJiggle(id,x,y,int(joint));break;}
    case 11:v.end();return encodeJiggleResult(getAnimationJiggleResult(id));
    case 12:v.end();return encodeJiggleState(getAnimationJiggleState(id));
    case 13:{auto state=decodeJiggleState(v);v.end();setAnimationJiggleState(id,state);break;}
    case 14:v.end();removeAnimationJiggle(id);break;
    default:throw std::invalid_argument("Unknown procedural operation");
    }return {};
}
