// Included inside namespace pdg after Sprite and Part implementations.
namespace {
constexpr double ikTurn = 6.28318530717958647692;
double ikBoundAngle(double angle, double current, const Part& joint) {
    if (!joint.hasIKLimits()) return current + std::remainder(angle-current, ikTurn);
    const double lo=joint.getIKMinAngle(), hi=joint.getIKMaxAngle();
    const double first=std::ceil((lo-angle)/ikTurn), last=std::floor((hi-angle)/ikTurn);
    if (first<=last) return angle+std::clamp(std::round((current-angle)/ikTurn),first,last)*ikTurn;
    return std::abs(std::remainder(angle-lo,ikTurn)) <= std::abs(std::remainder(angle-hi,ikTurn)) ? lo : hi;
}
}
Part& Part::setIKLimits(double minAngle, double maxAngle) {
    if (!std::isfinite(minAngle) || !std::isfinite(maxAngle) ||
        std::abs(minAngle)>std::numeric_limits<float>::max() || std::abs(maxAngle)>std::numeric_limits<float>::max() ||
        minAngle>maxAngle || maxAngle-minAngle>ikTurn)
        throw std::invalid_argument("IK limits require finite ordered radians spanning at most one turn");
    clearIKLimits(); mIKMinAngle=minAngle; mIKMaxAngle=maxAngle; mHasIKLimits=true; return *this;
}
bool Part::validateIKLimitConstraint(const PhysicsConstraint& constraint) const {
    if (constraint.getType()!=constraint_RotaryLimit || !constraint.isActive())
        throw std::logic_error("IK limits require an active rotary-limit constraint");
    if (!mSprite || physics==PhysicsBody::NoPhysics || (!mParent && hasCurrentRig()) || mAnimationPhysicsBody)
        throw std::logic_error("Linked IK limits require an independent Part body and an ordinary parent frame");
    const PhysicsBody& parent=mParent?static_cast<const PhysicsBody&>(mParent->physics):static_cast<const PhysicsBody&>(mSprite->physics);
    const PhysicsBody& child=physics;
    const bool forward=&constraint.getBodyA()==&parent && &constraint.getBodyB()==&child;
    const bool reverse=&constraint.getBodyB()==&parent && &constraint.getBodyA()==&child;
    if (parent==PhysicsBody::NoPhysics || (!forward && !reverse) || parent.world()!=child.world())
        throw std::logic_error("IK limit endpoints must be this Part and its immediate parent Part or Sprite");
    const auto frame=physicsFrame();
    const double x2=frame.a*frame.a+frame.b*frame.b, y2=frame.c*frame.c+frame.d*frame.d;
    if (!(x2>0) || !std::isfinite(x2+y2) || frame.a*frame.d-frame.b*frame.c<=0 ||
        std::abs(x2-y2)>1e-6*std::max(x2,y2) || std::abs(frame.a*frame.c+frame.b*frame.d)>1e-6*x2 ||
        (mFlipX?-mScaleX:mScaleX)<=0 || (mFlipY?-mScaleY:mScaleY)<=0 ||
        std::abs(std::remainder(std::atan2(frame.b,frame.a)-parent.getState().rotation,ikTurn))>1e-5)
        throw std::logic_error("Linked IK limits require an unreflected uniform parent frame aligned with its body");
    const double lo=constraint.getMinAngle(),hi=constraint.getMaxAngle();
    if (hi-lo>ikTurn || std::abs(lo)>std::numeric_limits<float>::max() || std::abs(hi)>std::numeric_limits<float>::max())
        throw std::logic_error("Linked IK limits must fit Part rotations and span at most one turn");
    return forward;
}
Part& Part::setIKLimits(PhysicsConstraint& constraint) {
    validateIKLimitConstraint(constraint);
    constraint.addRef(); clearIKLimits(); mIKConstraint=&constraint; mHasIKLimits=true;
    return *this;
}
Part& Part::clearIKLimits() {
    if (mIKConstraint) { mIKConstraint->release(); mIKConstraint=nullptr; }
    mHasIKLimits=false; mIKMinAngle=mIKMaxAngle=0; return *this;
}
double Part::getIKMinAngle() const {
    if (!mIKConstraint) return mIKMinAngle;
    return validateIKLimitConstraint(*mIKConstraint)?mIKConstraint->getMinAngle():-mIKConstraint->getMaxAngle();
}
double Part::getIKMaxAngle() const {
    if (!mIKConstraint) return mIKMaxAngle;
    return validateIKLimitConstraint(*mIKConstraint)?mIKConstraint->getMaxAngle():-mIKConstraint->getMinAngle();
}
void Part::validateIKJoint(const Part& child, const Point& offset) const {
    const PhysicsBody& a=physics; const PhysicsBody& b=child.physics;
    if (a==PhysicsBody::NoPhysics || b==PhysicsBody::NoPhysics) return;
    const auto frame=getTransform(partSpace_World);
    const double angle=a.getState().rotation, c=std::cos(angle), s=std::sin(angle);
    const double x=frame.a*offset.x+frame.c*offset.y, y=frame.b*offset.x+frame.d*offset.y;
    const Point expected(c*x+s*y,-s*x+c*y);
    const double tolerance=1e-5*std::max(1.0,std::hypot(double(expected.x),double(expected.y)));
    for (uint32_t i=0;i<a.getConstraintCount();++i) {
        const auto& joint=a.getConstraint(i);
        const bool forward=&joint.getBodyA()==&a && &joint.getBodyB()==&b;
        const bool reverse=&joint.getBodyB()==&a && &joint.getBodyA()==&b;
        if ((!forward && !reverse) || (joint.mType!=constraint_Pivot && joint.mType!=constraint_Pin)) continue;
        const auto pa=forward?joint.mAnchorA:joint.mAnchorB, pb=forward?joint.mAnchorB:joint.mAnchorA;
        if (std::hypot(pa.x-expected.x,pa.y-expected.y)>tolerance || std::hypot(pb.x,pb.y)>tolerance ||
            (joint.mType==constraint_Pin && joint.mValue1>tolerance))
            throw std::logic_error("Physical IK pivot/pin anchors must match the Part joint offsets and child origin: " + mName + " -> " + child.mName + "; expected parent anchor (" + std::to_string(expected.x) + ", " + std::to_string(expected.y) + "), got (" + std::to_string(pa.x) + ", " + std::to_string(pa.y) + ")");
    }
}

Part::IKTarget::~IKTarget() {
    stopDrives();
    for (auto* body : bodies) if (body) {
        if (ownsDrives && body->mDriveController==owner) body->mDriveController=nullptr;
        body->release();
    }
}
void Part::IKTarget::stopDrives() {
    if (ownsDrives) for (auto* body : bodies)
        if (body && body->mDriveController==owner) body->mDrive=PhysicsDriveState();
}
Part::IKSolution Part::calculateIK(Part* middle, Part* tip, const Point& target, int space, int bend,
                                  double influence, const IKTarget* drive) const {
    if (!mSprite || !middle || !tip || middle->mSprite!=mSprite || tip->mSprite!=mSprite ||
        middle->mParent!=this || tip->mParent!=middle)
        throw std::invalid_argument("IK requires three contiguous Parts in the same Sprite");
    if (space<partSpace_Local || space>partSpace_World || (bend!=1 && bend!=-1) ||
        !std::isfinite(target.x) || !std::isfinite(target.y) || !std::isfinite(influence) || influence<0 || influence>1)
        throw std::invalid_argument("Invalid Part IK target, coordinate space, bend direction or influence");
    if (!drive) { validateProgrammedTransform();middle->validateProgrammedTransform();tip->validateProgrammedTransform(); }
    else {
        const Part* joints[3]={this,middle,tip};
        for (int i=0;i<3;++i) {
            const auto& body=static_cast<PhysicsBody&>(joints[i]->physics);
            if (joints[i]->mAnimationPhysicsBody)
                throw std::logic_error("Part-chain drives require independent Parts, not mapped rig bodies");
            if (i==2 && !drive->bodies[i] && body==PhysicsBody::NoPhysics) continue;
            if (&body!=drive->bodies[i] || body.getMode()!=physicsBody_Dynamic ||
                (body.mDriveController && body.mDriveController!=this) ||
                (!body.mDriveController && body.isDriveEnabled()))
                throw std::logic_error("Part IK requires the same dynamic bodies and exclusive drive ownership");
        }
    }
    // Read live ranges once before choosing any pose or publishing any drive.
    const double rootMin=getIKMinAngle(),rootMax=getIKMaxAngle();
    const double middleMin=middle->getIKMinAngle(),middleMax=middle->getIKMaxAngle();
    if (drive) {
        validateIKJoint(*middle,drive->middleOffset);
        middle->validateIKJoint(*tip,drive->tipOffset);
        if (mParent) mParent->validateIKJoint(*this,drive->rootOffset);
    }
    const double sx=mScaleX*(mFlipX?-1:1),sy=mScaleY*(mFlipY?-1:1);
    if(sx==0 || sy==0 || std::abs(std::abs(sx)-std::abs(sy))>1e-6*std::max(std::abs(sx),std::abs(sy)))
        throw std::invalid_argument("Part IK requires a nonsingular uniform root scale");
    const auto parent=physicsFrame();const auto inverse=parent.inverse();
    Point wanted=target;
    if(space==partSpace_Sprite)wanted=mSprite->partRootTransform().transformPoint(target);
    if(space!=partSpace_Local)wanted=inverse.transformPoint(wanted);
    const auto origin=drive?drive->rootOffset:mLocation;
    const auto a=drive?drive->middleOffset:middle->mLocation, b=drive?drive->tipOffset:tip->mLocation;
    const double ax=a.x*sx, ay=a.y*sy;
    const double bx=b.x*middle->mScaleX*(middle->mFlipX?-1:1);
    const double by=b.y*middle->mScaleY*(middle->mFlipY?-1:1);
    const double length1=std::hypot(ax,ay),length2=std::abs(sx)*std::hypot(bx,by);
    if(!std::isfinite(length1+length2) || length1<=1e-8 || length2<=1e-8)
        throw std::invalid_argument("Part IK requires finite nonzero joint offsets, independent of artwork size");
    const double x=wanted.x-origin.x,y=wanted.y-origin.y;
    const double cosine=std::clamp((x*x+y*y-length1*length1-length2*length2)/(2*length1*length2),-1.0,1.0);
    const double elbow=bend*std::acos(cosine);
    const double direction=std::atan2(y,x)-std::atan2(length2*std::sin(elbow),length1+length2*std::cos(elbow));
    const double rootAngle=direction-std::atan2(ay,ax);
    const double middleAngle=std::atan2(std::sin(direction+elbow-rootAngle)/sy,
        std::cos(direction+elbow-rootAngle)/sx)-std::atan2(by,bx);
    double bestRoot=0,bestMiddle=0,bestError=std::numeric_limits<double>::infinity();
    auto consider=[&](double r,double m) {
        r=ikBoundAngle(r,mFacing,*this);m=ikBoundAngle(m,middle->mFacing,*middle);
        const double vx=ax+sx*(std::cos(m)*bx-std::sin(m)*by), vy=ay+sy*(std::sin(m)*bx+std::cos(m)*by);
        const double dx=std::cos(r)*vx-std::sin(r)*vy-x, dy=std::sin(r)*vx+std::cos(r)*vy-y;
        const double error=dx*dx+dy*dy;
        if(error<bestError-1e-12) {bestError=error;bestRoot=r;bestMiddle=m;}
    };
    consider(rootAngle,middleAngle); // requested bend wins equal-error ties
    if(mHasIKLimits || middle->mHasIKLimits) {
        const double alternate=std::atan2(y,x)-std::atan2(-length2*std::sin(elbow),length1+length2*std::cos(elbow));
        const double r=alternate-std::atan2(ay,ax);
        consider(r,std::atan2(std::sin(alternate-elbow-r)/sy,std::cos(alternate-elbow-r)/sx)-std::atan2(by,bx));
    }
    // At a constrained optimum either a joint is at its limit, or the ordinary
    // analytic solution reaches the target. Optimize the free angle at each edge.
    if(mHasIKLimits) for(double r:{rootMin,rootMax}) {
        const double vx=std::cos(r)*x+std::sin(r)*y-ax,vy=-std::sin(r)*x+std::cos(r)*y-ay;
        consider(r,std::atan2(vy/sy,vx/sx)-std::atan2(by,bx));
    }
    if(middle->mHasIKLimits) for(double m:{middleMin,middleMax}) {
        const double vx=ax+sx*(std::cos(m)*bx-std::sin(m)*by),vy=ay+sy*(std::sin(m)*bx+std::cos(m)*by);
        consider(std::atan2(y,x)-std::atan2(vy,vx),m);
    }
    auto blend=[&](double angle,double current,const Part& joint) {
        if(joint.hasIKLimits()) {
            current=std::clamp(current,joint.getIKMinAngle(),joint.getIKMaxAngle());
            return float(std::clamp(current+(angle-current)*influence,joint.getIKMinAngle(),joint.getIKMaxAngle()));
        }
        return float(current+std::remainder(angle-current,ikTurn)*influence);
    };
    return {blend(bestRoot,mFacing,*this),blend(bestMiddle,middle->mFacing,*middle),
        parent.transformPoint(wanted),1e-4*std::max(1.0,length1+length2)};
}

void Part::validateIKOverlap(Part* middle, Part* tip, bool physical) const {
    for (auto* root : mSprite->mParts) {
        if (root==this || !root->mIKTarget) continue;
        const auto& other=*root->mIKTarget;
        for (auto id : {mId,middle->mId,physical?tip->mId:partId_None}) {
            if (id==partId_None) continue;
            if(id==root->mId || id==other.middle || (other.physical && id==other.tip))
                throw std::logic_error("Part IK controllers cannot write the same joint");
        }
    }
}
bool Part::solveIK(Part* middle, Part* tip, const Point& target, int space, int bend, double influence) {
    const auto solution=calculateIK(middle,tip,target,space,bend,influence);
    if(influence>0) {
        cancelAnimation(&mDeltaFacingPerMs);middle->cancelAnimation(&middle->mDeltaFacingPerMs);
        mDeltaFacingPerMs=middle->mDeltaFacingPerMs=0;
        setRotation(solution.rootAngle);middle->setRotation(solution.middleAngle);
    }
    const auto actual=tip->getTransform(partSpace_World);
    return std::hypot(actual.tx-solution.worldTarget.x,actual.ty-solution.worldTarget.y)<=solution.tolerance;
}
Part& Part::setIKTarget(Part* middle, Part* tip, const Point& target, int space, int bend, double influence) {
    calculateIK(middle,tip,target,space,bend,influence);
    validateIKOverlap(middle,tip,false);
    auto config=std::make_unique<IKTarget>();
    config->middle=middle->mId;config->tip=tip->mId;
    config->target=target;config->space=space;config->bend=bend;config->influence=influence;config->reached=false;
    mIKTarget=std::move(config);mIKError.clear();return *this;
}
Part& Part::setIKDriveTarget(Part* middle, Part* tip, const Point& target, double maxForce, double maxTorque,
                            int space, int bend, double influence, double frequency, double dampingRatio) {
    if(!middle || !tip || !mSprite) throw std::invalid_argument("Physical IK requires an owned Part chain");
    for(double value:{maxForce,maxTorque,frequency,dampingRatio})
        if(!std::isfinite(value) || value<0) throw std::invalid_argument("IK drive limits and damping must be finite and nonnegative");
    const double omega=ikTurn*frequency;
    if(frequency==0 || !std::isfinite(omega*omega) || !std::isfinite(2*dampingRatio*omega))
        throw std::invalid_argument("IK drive frequency and damping must produce finite positive-frequency coefficients");
    auto config=std::make_unique<IKTarget>();config->owner=this;config->physical=true;
    config->middle=middle->mId;config->tip=tip->mId;config->target=target;
    config->space=space;config->bend=bend;config->influence=influence;config->reached=false;
    config->maxForce=maxForce;config->maxTorque=maxTorque;config->frequency=frequency;config->dampingRatio=dampingRatio;
    const bool same=mIKTarget && mIKTarget->physical && mIKTarget->middle==middle->mId && mIKTarget->tip==tip->mId;
    config->rootOffset=same?mIKTarget->rootOffset:mLocation;
    config->middleOffset=same?mIKTarget->middleOffset:middle->mLocation;
    config->tipOffset=same?mIKTarget->tipOffset:tip->mLocation;
    config->tipAngle=same?mIKTarget->tipAngle:tip->mFacing;
    Part* joints[3]={this,middle,tip};
    for(int i=0;i<3;++i) if(joints[i]->physics!=PhysicsBody::NoPhysics) {
        config->bodies[i]=&static_cast<PhysicsBody&>(joints[i]->physics);config->bodies[i]->addRef();
    }
    calculateIK(middle,tip,target,space,bend,influence,config.get());
    validateIKOverlap(middle,tip,true);
    mIKTarget.reset(); // release previous claims only after validating the replacement
    mIKTarget=std::move(config);mIKTarget->ownsDrives=true;
    for(auto* body:mIKTarget->bodies) if(body) body->mDriveController=this;
    mIKError.clear();return *this;
}
Part& Part::clearIKTarget() {mIKTarget.reset();mIKError.clear();return *this;}
bool Part::isIKTargetReached() const {
    if(!mIKTarget) return false;
    if(!mIKTarget->physical) return mIKTarget->reached;
    if(!mIKError.empty()) return false;
    try {
        const auto& ik=*mIKTarget;
        auto* middle=mSprite?mSprite->getPart(ik.middle):nullptr;
        auto* tip=mSprite?mSprite->getPart(ik.tip):nullptr;
        const auto solution=calculateIK(middle,tip,ik.target,ik.space,ik.bend,ik.influence,&ik);
        const auto actual=tip->getTransform(partSpace_World);
        return std::hypot(actual.tx-solution.worldTarget.x,actual.ty-solution.worldTarget.y)<=solution.tolerance;
    } catch(const std::exception&) {return false;}
}
bool Part::applyIKTarget() {
    if(!mIKTarget) return false;
    auto& ik=*mIKTarget;
    auto* middle=mSprite?mSprite->getPart(ik.middle):nullptr;
    auto* tip=mSprite?mSprite->getPart(ik.tip):nullptr;
    try {
        if(!ik.physical) {
            const float before=mFacing,middleBefore=middle?middle->mFacing:0;
            ik.reached=solveIK(middle,tip,ik.target,ik.space,ik.bend,ik.influence);mIKError.clear();
            return mFacing!=before || (middle && middle->mFacing!=middleBefore);
        }
        const auto solution=calculateIK(middle,tip,ik.target,ik.space,ik.bend,ik.influence,&ik);
        auto local=[](Part* p,const Point& offset,float angle) {
            return SpatialTransform::fromTRS(offset.x,offset.y,angle,p->mScaleX*(p->mFlipX?-1:1),p->mScaleY*(p->mFlipY?-1:1));
        };
        const auto rootFrame=SpatialTransform::compose(physicsFrame(),local(this,ik.rootOffset,solution.rootAngle));
        const auto middleFrame=SpatialTransform::compose(rootFrame,local(middle,ik.middleOffset,solution.middleAngle));
        const auto tipFrame=SpatialTransform::compose(middleFrame,local(tip,ik.tipOffset,ik.tipAngle));
        const SpatialTransform frames[3]={rootFrame,middleFrame,tipFrame};
        double angles[3]={std::atan2(rootFrame.b,rootFrame.a),std::atan2(middleFrame.b,middleFrame.a),std::atan2(tipFrame.b,tipFrame.a)};
        if (mIKConstraint) {
            const PhysicsBody& parent=mParent?static_cast<const PhysicsBody&>(mParent->physics):static_cast<const PhysicsBody&>(mSprite->physics);
            angles[0]=parent.getState().rotation+solution.rootAngle;
        } else angles[0]=ik.bodies[0]->getState().rotation+std::remainder(angles[0]-ik.bodies[0]->getState().rotation,ikTurn);
        if (middle->mIKConstraint) angles[1]=angles[0]+solution.middleAngle;
        for(int i=0;i<3;++i) if(ik.bodies[i]) {
            if(ik.bodies[i]->mDriveController!=this) throw std::logic_error("Physical IK body was detached; install a new target");
            if(ik.influence==0) ik.bodies[i]->mDrive=PhysicsDriveState();
            else ik.bodies[i]->setDriveTargetImpl(Point(frames[i].tx,frames[i].ty),angles[i],
                ik.maxForce,ik.maxTorque,ik.frequency,ik.dampingRatio,
                ((i==0 && mIKConstraint) || (i==1 && middle->mIKConstraint))?rotationDirection_AsSpecified:rotationDirection_Shortest);
        }
        mIKError.clear();return true;
    } catch(const std::exception& error) {
        ik.stopDrives();ik.reached=false;mIKError=error.what();return false;
    }
}
