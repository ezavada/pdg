#include "pdg/sys/bone.h"
#include "pdg/sys/sprite.h"
#include "pdg/sys/animationcontroller.h"
#include <algorithm>
#include <numbers>
namespace pdg {
#ifdef PDG_SPRITER_SUPPORT
Bone::Bone(Sprite* owner,std::shared_ptr<const AnimationRig> rig,AnimationBoneId id)
    :mOwner(owner),mRig(std::move(rig)),mId(id),mSample(mRig->getBone(id).reference) {
    mModes.fill(-1);
    mReferenceHeight=mRig->getBone(id).length;
    if(mReferenceHeight<=0) for(AnimationBoneId child=0;child<mRig->getBoneCount();++child)
        if(mRig->getBone(child).parent==id) mReferenceHeight=std::max(mReferenceHeight,std::hypot(mRig->getBone(child).reference.x,mRig->getBone(child).reference.y));
    mReferenceHeight=std::max(1.0,mReferenceHeight);mReferenceWidth=std::max(1.0,mReferenceHeight*.2);
    mWidth=mReferenceWidth;mHeight=mReferenceHeight;
    mCenterOffset=Offset(mSample.x,mSample.y);
    mLocation=Point(mSample.x,mSample.y);mFacing=mSample.rotation;mScaleX=mSample.scaleX;mScaleY=mSample.scaleY;
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    INIT_SCRIPT_OBJECT(mBoneScriptObj);
#endif
}
uint32 Bone::getSerializedSize(ISerializer*) const {throw std::logic_error("Bone controls are runtime handles and cannot be serialized");}
void Bone::serialize(ISerializer*) const {throw std::logic_error("Bone controls are runtime handles and cannot be serialized");}
void Bone::deserialize(IDeserializer*) {throw std::logic_error("Bone controls are runtime handles and cannot be deserialized");}
Bone::~Bone(){if(mLimit)mLimit->release();}
void Bone::validateScriptRead() const {AnimatedBase::validateScriptRead();if(!mOwner)throw std::logic_error("Bone belongs to an inactive rig");}
void Bone::validateTransformEdit() const {validateScriptRead();if(AnimationPipeline::isInsideCallback())throw std::logic_error("Edit Bone controls outside pose callbacks");}
void Bone::validateSampledRequest(std::initializer_list<ScriptValue> values,double seconds,EasingFunc easing,uint8 mode) const {
    validateTransformEdit();
    if(!std::isfinite(seconds)||seconds<0||!easing)throw std::invalid_argument("Bone durations must be finite nonnegative seconds with valid easing");
    for(const auto& value:values){
        if(!std::isfinite(value.target))throw std::invalid_argument("Bone targets must be finite");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if(mOwner->mAnimationPhysics && (value.field==5 || value.field==6)) {
            const double base=value.field==5?mSample.scaleX:mSample.scaleY;
            const double target=mode==animationMode_Assign?value.target:mode==animationMode_Add?base+value.target:base*value.target;
            if(std::abs(target-base)>1e-7)throw std::logic_error("Disable animation physics before scaling a bone; use resize for its physical dimensions");
        }
#endif
        if(value.field==3 || value.field==4){const auto size=getSize();const double current=value.field==3?size.x:size.y;
            const double target=mode==animationMode_Assign?value.target:mode==animationMode_Add?current+value.target:current*value.target;
            if(target<0)throw std::invalid_argument("Bone dimensions must be nonnegative");}
    }
}
void Bone::invalidate(){mOwner=nullptr;cancelSchedule();}
void Bone::animationValuesChanged(){if(mInfluence==0){mModes.fill(-1);mFlipX=mFlipY=false;}if(mOwner)mOwner->invalidateSpriterPose();}
std::vector<const float*> Bone::tweenFields() const {auto fields=AnimatedBase::tweenFields();fields.push_back(&mInfluence);return fields;}
bool Bone::prepareSampledAnimation(unsigned field,uint8 mode,float current) {
    validateTransformEdit();
    if(!isRecordingOperation() && !mAnimating)mOwner->getAnimationPose();
    if(field>=9){if(field<14)return prepareSampledAnimation(field==9?0:field==10?1:field==11?2:field==12?3:4,animationMode_Add,*(tweenFields()[field==9?0:field==10?1:field==11?2:field==12?3:4]));return false;}
    if(mInfluence==0){mModes.fill(-1);mFlipX=mFlipY=false;mInfluence=1;}
    auto fields=tweenFields();auto* value=const_cast<float*>(fields[field]);
    const int next=mode;
    if(mModes[field]==next && !(field==2 && next==animationMode_Assign))return false;
    double base=0;
    switch(field){case 0:base=mSample.x;break;case 1:base=mSample.y;break;case 2:base=mSample.rotation;break;
        case 3:base=mReferenceWidth;break;case 4:base=mReferenceHeight;break;case 5:base=mSample.scaleX;break;case 6:base=mSample.scaleY;break;case 7:base=mRig->getBone(mId).reference.x;break;case 8:base=mRig->getBone(mId).reference.y;break;}
    const bool factor=mode==animationMode_Multiply;
    const double controlled=mModes[field]<0?base:mModes[field]==0?current:mModes[field]==2?base*current:base+current;
    double displayed=base+(controlled-base)*mInfluence;
    if(field==2 && next==animationMode_Assign)if(auto limits=rotationLimits(mOwner->getAnimationPose())){
        const double middle=(limits->first+limits->second)*.5;
        displayed=std::clamp(middle+std::remainder(displayed-middle,2*std::numbers::pi),limits->first,limits->second);
    }
    *value=next==0?displayed:factor?(base==0?1:displayed/base):displayed-base;
    mModes[field]=next;
    return true;
}
void Bone::sample(const AnimationPose& pose){
    mSample=pose.getLocalTransform(mId);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mOwner->mAnimationPhysics && mGeometryRig!=mOwner->mAnimationPhysics.get()){
        const auto& definition=mOwner->mAnimationPhysics->definition();
        for(const auto& body:definition.bodies)if(body.bone==mId){
            const auto world=pose.getWorldTransform(mId,mOwner->spriterRootTransform());const double scale=std::abs(world.scaleX);
            if(scale>0){mReferenceWidth=2*body.radius/scale;mReferenceHeight=(body.length+2*body.radius)/scale;
                if(mModes[3]<0)mWidth=mReferenceWidth;
                if(mModes[4]<0)mHeight=mReferenceHeight;}
        }
        mGeometryRig=mOwner->mAnimationPhysics.get();
    }
#endif
}
void Bone::flipChanged(bool x,bool y){
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mOwner && mOwner->mAnimationPhysics)throw std::logic_error("Disable animation physics before reflecting one bone; use Sprite flip for the physical assembly");
#endif
    if(x)mCenterOffset.x=-mCenterOffset.x;
    if(y)mCenterOffset.y=-mCenterOffset.y;
    animationValuesChanged();}
Offset Bone::getCenterOffset() const {
    validateScriptRead();const auto& r=mRig->getBone(mId).reference;
    const auto component=[&](unsigned i,double base,double value){if(mModes[i]<0)return base;const double target=mModes[i]==0?value:base+value;return base+(target-base)*mInfluence;};
    return Offset(component(7,r.x,mCenterOffset.x),component(8,r.y,mCenterOffset.y));
}
Rect Bone::getBoundingBox() const {return getRotatedBounds().getBounds();}
RotatedRect Bone::getRotatedBounds() const {
    const auto position=getLocation();const auto scale=getScale(),size=getSize();
    double axis=0,longest=0;
    for(AnimationBoneId child=0;child<mRig->getBoneCount();++child)if(mRig->getBone(child).parent==mId){const auto& r=mRig->getBone(child).reference;const double n=std::hypot(r.x,r.y);if(n>longest){longest=n;axis=std::atan2(r.y,r.x);}}
    Offset capsuleCenter;bool physical=false;
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mOwner->mAnimationPhysics)for(const auto& body:mOwner->mAnimationPhysics->definition().bodies)if(body.bone==mId){axis=body.offsetRotation;capsuleCenter=Offset(body.offsetX,body.offsetY);physical=true;break;}
#endif
    const double angle=getRotation()+std::atan2(scale.y*std::sin(axis),scale.x*std::cos(axis));
    const double length=size.y*std::hypot(scale.x*std::cos(axis),scale.y*std::sin(axis));
    const double width=size.x*std::hypot(scale.x*std::sin(axis),scale.y*std::cos(axis));
    Point center(position.x+std::cos(angle)*length/2,position.y+std::sin(angle)*length/2);
    if(physical){const double rotation=getRotation(),c=std::cos(rotation),s=std::sin(rotation);center=Point(position.x+c*scale.x*capsuleCenter.x-s*scale.y*capsuleCenter.y,position.y+s*scale.x*capsuleCenter.x+c*scale.y*capsuleCenter.y);}
    Rect rect(width,length);rect.center(center);
    return RotatedRect(rect,angle-std::numbers::pi/2);
}
Point Bone::getLocation() const {validateScriptRead();const auto t=mOwner->getAnimationBoneTransform(getName().c_str());return Point(t.x,t.y);}
float Bone::getRotation() const {validateScriptRead();return mOwner->getAnimationBoneTransform(getName().c_str()).rotation;}
Offset Bone::getScale() const {validateScriptRead();const auto t=mOwner->getAnimationBoneTransform(getName().c_str());return Offset(t.scaleX,t.scaleY);}
Offset Bone::getSize() const {
    validateScriptRead();const double w=mModes[3]<0?mReferenceWidth:mModes[3]==0?mWidth:mModes[3]==2?mReferenceWidth*mWidth:mReferenceWidth+mWidth;
    const double h=mModes[4]<0?mReferenceHeight:mModes[4]==0?mHeight:mModes[4]==2?mReferenceHeight*mHeight:mReferenceHeight+mHeight;
    return Offset(mReferenceWidth+(w-mReferenceWidth)*mInfluence,mReferenceHeight+(h-mReferenceHeight)*mInfluence);
}
Bone& Bone::diminish(float influence,double seconds,EasingFunc easing){
    validateTransformEdit();if(!std::isfinite(influence)||influence<0||influence>1)throw std::invalid_argument("Bone influence must be between zero and one");
    if(recordScriptAnimation({{animationChannel_BaseCount,influence}},seconds,easing,animationMode_Assign,rotationDirection_AsSpecified,0,CLASSTAG_BONE))return *this;
    beginAnimationRequest();scheduleAnimation(&mInfluence,influence,seconds,easing);finishAnimationRequest();animationValuesChanged();return *this;
}
Bone& Bone::setIKLimits(double minimum,double maximum){
    if(recordOperation("setIKLimits",captureAnimationArguments(minimum,maximum)))return *this;
    validateTransformEdit();if(!std::isfinite(minimum)||!std::isfinite(maximum)||maximum<minimum||maximum-minimum>2*std::numbers::pi)throw std::invalid_argument("Invalid bone angle limits");
    clearIKLimits();mMinimum=minimum;mMaximum=maximum;mHasLimits=true;animationValuesChanged();return *this;
}
Bone& Bone::setIKLimits(PhysicsConstraint& constraint){
    if(recordOperation("setIKLimits",captureAnimationArguments(constraint)))return *this;
    validateTransformEdit();if(!constraint.isActive()||constraint.getType()!=constraint_RotaryLimit)throw std::invalid_argument("Bone requires an active rotary limit");
    auto* part=mOwner->findPart(getName());
    auto parentId=mRig->getBone(mId).parent;Part* parent=nullptr;
    for(;parentId!=animation_NoBone;parentId=mRig->getBone(parentId).parent){parent=mOwner->findPart(mRig->getBone(parentId).name);if(parent && parent->physics!=PhysicsBody::NoPhysics)break;}
    PhysicsBody& parentBody=parentId==animation_NoBone?static_cast<PhysicsBody&>(mOwner->physics):static_cast<PhysicsBody&>(parent->physics);
    if(parentBody==PhysicsBody::NoPhysics || (&constraint.getBodyA()!=&parentBody && &constraint.getBodyB()!=&parentBody))throw std::invalid_argument("Rotary limit must connect this bone and its physical parent");
    if(!part || (part->physics!=constraint.getBodyA() && part->physics!=constraint.getBodyB()))throw std::invalid_argument("Rotary limit must connect this bone's physical Part");
    clearIKLimits();constraint.addRef();mLimit=&constraint;mHasLimits=true;animationValuesChanged();return *this;
}
Bone& Bone::clearIKLimits(){if(recordOperation("clearIKLimits",{}))return *this;validateTransformEdit();if(mLimit)mLimit->release();mLimit=nullptr;mHasLimits=false;animationValuesChanged();return *this;}
bool Bone::hasIKLimits() const {validateScriptRead();return bool(rotationLimits(mOwner->getAnimationPose()));}
double Bone::getIKMinAngle() const {validateScriptRead();auto limits=rotationLimits(mOwner->getAnimationPose());return limits?limits->first:0;}
double Bone::getIKMaxAngle() const {validateScriptRead();auto limits=rotationLimits(mOwner->getAnimationPose());return limits?limits->second:0;}
std::optional<std::pair<double,double>> Bone::rotationLimits(const AnimationPose& pose) const {
    if(mHasLimits && !mLimit)return std::pair(mMinimum,mMaximum);
    PhysicsConstraint* constraint=mLimit;
    auto* child=mOwner->findPart(mRig->getBone(mId).name);
    if(!constraint && child && child->hasIKLimits()){
        if(child->mIKConstraint){if(child->mIKConstraint->isActive())constraint=child->mIKConstraint;}
        else return std::pair(child->mIKMinAngle,child->mIKMaxAngle);
    }
    auto parentId=mRig->getBone(mId).parent;Part* parent=nullptr;
    for(;parentId!=animation_NoBone;parentId=mRig->getBone(parentId).parent){parent=mOwner->findPart(mRig->getBone(parentId).name);if(parent && parent->physics!=PhysicsBody::NoPhysics)break;}
    if(parentId==animation_NoBone)parent=nullptr;
    PhysicsBody& parentBody=parent?static_cast<PhysicsBody&>(parent->physics):static_cast<PhysicsBody&>(mOwner->physics);
    if(!constraint && child && parentBody!=PhysicsBody::NoPhysics)for(uint32_t i=0;i<child->physics.getConstraintCount();++i){auto& c=child->physics.getConstraint(i);if(c.getType()==constraint_RotaryLimit && (&c.getBodyA()==&parentBody || &c.getBodyB()==&parentBody)){constraint=&c;break;}}
    if(constraint && constraint->isActive()){
        if(!child || parentBody==PhysicsBody::NoPhysics)throw std::logic_error("Bone rotary limit requires a physical parent");
        const bool forward=&constraint->getBodyA()==&parentBody && &constraint->getBodyB()==&static_cast<PhysicsBody&>(child->physics);
        const bool reverse=&constraint->getBodyB()==&parentBody && &constraint->getBodyA()==&static_cast<PhysicsBody&>(child->physics);
        if(!forward && !reverse)throw std::logic_error("Bone rotary limit must connect its parent");
        auto zero=pose.copy();auto local=zero.getLocalTransform(mId);local.rotation=0;zero.setLocalTransform(mId,local);
        const auto root=mOwner->spriterRootTransform();const auto a=parent?zero.getWorldTransform(parentId,root):root,b=zero.getWorldTransform(mId,root);
        const auto offset=[](const AnimationTransform& frame,double rotation){return std::atan2(frame.scaleY*std::sin(rotation),frame.scaleX*std::cos(rotation));};
        const double constant=std::remainder(b.rotation+offset(b,child->getRotation())-a.rotation-offset(a,parent?parent->getRotation():0),2*std::numbers::pi);
        const double sign=a.scaleX*a.scaleY<0?-1:1;
        const double minimum=forward?constraint->getMinAngle():-constraint->getMaxAngle(),maximum=forward?constraint->getMaxAngle():-constraint->getMinAngle();
        const double lo=(minimum-constant)/sign,hi=(maximum-constant)/sign;
        return std::pair(std::min(lo,hi),std::max(lo,hi));
    }
    for(const auto& [id,state]:mOwner->mAnimationIK){const auto& c=state->config;if(c.root==mId && c.rootMax-c.rootMin<2*std::numbers::pi)return std::pair(c.rootMin,c.rootMax);if(c.middle==mId && c.middleMax-c.middleMin<2*std::numbers::pi)return std::pair(c.middleMin,c.middleMax);}
    return {};
}
void Bone::apply(AnimationPose& pose,bool constraintsOnly){
    auto local=pose.getLocalTransform(mId);
    if(!constraintsOnly){
        const auto fields=tweenFields();double* components[]={&local.x,&local.y,&local.rotation,nullptr,nullptr,&local.scaleX,&local.scaleY};
        for(unsigned i=0;i<7;++i)if(components[i] && mModes[i]>=0){double& value=*components[i];const double controlled=mModes[i]==0?*fields[i]:mModes[i]==2?value*(*fields[i]):value+(*fields[i]);value+=(controlled-value)*mInfluence;}
        const auto& reference=mRig->getBone(mId).reference;
        if(mModes[7]>=0)local.x+=(mModes[7]==0?mCenterOffset.x-reference.x:mCenterOffset.x)*mInfluence;
        if(mModes[8]>=0)local.y+=(mModes[8]==0?mCenterOffset.y-reference.y:mCenterOffset.y)*mInfluence;
        if(mFlipX)local.scaleX*=1-2*mInfluence;
        if(mFlipY)local.scaleY*=1-2*mInfluence;
        const double width=mModes[3]<0?mReferenceWidth:mModes[3]==0?mWidth:mModes[3]==2?mReferenceWidth*mWidth:mReferenceWidth+mWidth;
        const double height=mModes[4]<0?mReferenceHeight:mModes[4]==0?mHeight:mModes[4]==2?mReferenceHeight*mHeight:mReferenceHeight+mHeight;
        if(width<0||height<0)throw std::invalid_argument("Bone dimensions must be nonnegative");
        // Imported bones can extend in any direction. Resize connections along
        // the reference longitudinal axis and its perpendicular, preserving
        // each child's sampled motion and size.
        double ax=1,ay=0;double longest=0;
        for(AnimationBoneId child=0;child<mRig->getBoneCount();++child)if(mRig->getBone(child).parent==mId){const auto& r=mRig->getBone(child).reference;const double n=std::hypot(r.x,r.y);if(n>longest){longest=n;ax=r.x/n;ay=r.y/n;}}
        const double sx=1+(width/mReferenceWidth-1)*mInfluence,sy=1+(height/mReferenceHeight-1)*mInfluence;
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if(mOwner->mAnimationPhysics){
            auto& rig=*mOwner->mAnimationPhysics;
            if(rig.resizeBone(mId,sx,sy))for(const auto& body:rig.definition().bodies)if(body.bone==mId)if(auto* part=mOwner->findPart(getName())){
                part->mLocation=Point(body.offsetX,body.offsetY);
                part->collider.setCapsule(Point(-body.length/2,0),Point(body.length/2,0),body.radius);
            }
        }
#endif
        for(AnimationBoneId child=0;child<mRig->getBoneCount();++child)if(mRig->getBone(child).parent==mId){auto t=pose.getLocalTransform(child);const double along=t.x*ax+t.y*ay,across=-t.x*ay+t.y*ax;t.x=along*sy*ax-across*sx*ay;t.y=along*sy*ay+across*sx*ax;pose.setLocalTransform(child,t);}
    }
    if(const auto limits=rotationLimits(pose)){
        const auto [lo,hi]=*limits;const double middle=(lo+hi)*.5;
        const double angle=middle+std::remainder(local.rotation-middle,2*std::numbers::pi);
        local.rotation=std::clamp(angle,lo,hi);
    }
    pose.setLocalTransform(mId,local);
}
#include "animation-operations-bone.inc"
#endif // PDG_SPRITER_SUPPORT
}
