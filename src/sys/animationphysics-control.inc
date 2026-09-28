// Included inside namespace pdg. Control state borrows the Sprite-owned bodies.
namespace {
constexpr double physicsTurn = 6.28318530717958647692;
double physicalRoute(double target, double current, int direction) {
    double delta = target-current;
    if (direction != rotationDirection_AsSpecified) {
        delta = std::fmod(delta, physicsTurn);
        if (direction == rotationDirection_Clockwise && delta < 0) delta += physicsTurn;
        if (direction == rotationDirection_CounterClockwise && delta > 0) delta -= physicsTurn;
        if (direction == rotationDirection_Shortest) {
            if (delta > physicsTurn/2) delta -= physicsTurn;
            if (delta <= -physicsTurn/2) delta += physicsTurn;
        }
    }
    require(finite(current+delta), "Physical angular route overflow");
    return current+delta;
}
void validatePhysicalDirection(int direction) {
    require(direction >= rotationDirection_AsSpecified && direction <= rotationDirection_CounterClockwise,
            "Invalid physical rotation direction");
}
AnimationTransform relativePhysicalFrame(const AnimationTransform& frame, const AnimationTransform& world) {
    const double c=std::cos(frame.rotation), s=std::sin(frame.rotation);
    return {c*(world.x-frame.x)+s*(world.y-frame.y), -s*(world.x-frame.x)+c*(world.y-frame.y), world.rotation-frame.rotation};
}
AnimationTransform physicalStateFrame(const PhysicsBodyState& state) { return {state.x,state.y,state.rotation}; }
}
struct AnimationPhysicsRig::Control {
    struct Body {
        PhysicsBody* body = nullptr;
        int mode = animationPhysics_Dynamic, destination = animationPhysics_Dynamic;
        int parent = -1;
        std::optional<AnimationPhysicsDriveSettings> settings;
        bool recovering = false, routeReady = false, attached = true;
        double duration = 0, elapsed = 0, routeOffset = 0;
        double previousTargetAngle = 0;
        int routeDirection = rotationDirection_Shortest;
        double recoveryX = 0, recoveryY = 0, motorSeconds = 0;
        cpConstraint* recoveryMotor = nullptr; // owned by Storage::joints
        AnimationTransform start, target, desired, localTarget;
        bool hasTargetSample = false;
    };
    std::vector<Body> bodies;
    std::vector<uint32_t> order;
    std::vector<AnimationPhysicsRecovery> requests;
    AnimationTransform anchor, published;
    bool hasAnchor = false;
};
AnimationTransform AnimationPhysicsRig::targetFrame(uint32_t index, const AnimationPose& desired,
                                                    const AnimationTransform& root) const {
    const auto& def=mDefinition.bodies[index];
    auto bone=desired.getWorldTransform(def.bone,root);
    bone.scaleX=mStorage->scales[index].first;bone.scaleY=mStorage->scales[index].second;
    return generatedBodyFrame(bone,def);
}
void AnimationPhysicsRig::attachBodies(const std::vector<PhysicsBody*>& bodies) {
    require(bodies.size()==mDefinition.bodies.size(),"Physical control body mapping mismatch");
    auto control=std::make_unique<Control>();control->bodies.resize(bodies.size());
    for (size_t i=0;i<bodies.size();++i) {
        auto& entry=control->bodies[i];entry.body=bodies[i];
        entry.mode=entry.destination=bodies[i]->getMode()==physicsBody_Kinematic?animationPhysics_Kinematic:animationPhysics_Dynamic;
        for (auto parent=mRig->getBone(mDefinition.bodies[i].bone).parent; parent!=animation_NoBone;parent=mRig->getBone(parent).parent) {
            auto it=std::find_if(mDefinition.bodies.begin(),mDefinition.bodies.end(),[&](const auto& b){return b.bone==parent;});
            if(it!=mDefinition.bodies.end()){entry.parent=int(it-mDefinition.bodies.begin());break;}
        }
    }
    for(auto bone:mOrder)for(uint32_t i=0;i<bodies.size();++i)
        if(mDefinition.bodies[i].bone==bone)control->order.push_back(i);
    mControl=std::move(control);
    for (size_t i=0;i<bodies.size();++i) configureMode(i,mControl->bodies[i].mode);
}
void AnimationPhysicsRig::releaseControls() {
    if (!mControl) return;
    for(auto& entry:mControl->bodies) {
        auto& body=*entry.body;
        if(body.mDriveController==this){body.mDriveController=nullptr;body.mRigDrive=false;body.mDrive=PhysicsDriveState();}
        body.mCoordinateMode={};
    }
    mControl.reset();
}
std::vector<uint32_t> AnimationPhysicsRig::select(std::optional<AnimationBoneId> bone, bool descendants) const {
    if (!mControl) throw std::logic_error("Physical control bodies are not attached");
    if (bone && *bone>=mRig->getBoneCount()) throw std::out_of_range("Unknown animation bone");
    std::vector<uint32_t> result;
    for(uint32_t i=0;i<mDefinition.bodies.size();++i) {
        if(!mControl->bodies[i].attached)continue;
        auto id=mDefinition.bodies[i].bone;
        if(!bone || id==*bone) {result.push_back(i);continue;}
        if(descendants) for(id=mRig->getBone(id).parent;id!=animation_NoBone;id=mRig->getBone(id).parent)
            if(id==*bone){result.push_back(i);break;}
    }
    if(result.empty())throw std::invalid_argument("Selection has no physical bodies");
    return result;
}
bool AnimationPhysicsRig::isBodyAttached(uint32_t index) const {
    return mControl && mControl->bodies.at(index).attached;
}
void AnimationPhysicsRig::validateMembershipChange(const std::vector<bool>& attached) const {
    require(mControl && attached.size()==mControl->bodies.size(),"Invalid rig membership mapping");
    if(cpSpaceIsLocked(mStorage->space))throw std::logic_error("Change rig membership outside physics callbacks");
    for(size_t i=0;i<attached.size();++i) {
        const auto& entry=mControl->bodies[i];const auto& body=*entry.body;
        if(entry.recovering)throw std::logic_error("Finish or cancel recovery before changing rig membership");
        if(attached[i]!=entry.attached && ((body.mDriveController && body.mDriveController!=this) ||
            (!body.mDriveController && body.mDrive.enabled)))
            throw std::logic_error("Explicitly release manual or Part IK drives before changing rig membership");
    }
}
void AnimationPhysicsRig::setMembership(const std::vector<bool>& attached,uint32_t root) {
    validateMembershipChange(attached);
    require(root<attached.size() && attached[root],"The physical root must remain attached");
    // Membership edits cancel pending completion notices; they never emit a
    // successful recovery for a selection whose membership has changed.
    mControl->requests.clear();
    for(size_t i=0;i<attached.size();++i) {
        auto& entry=mControl->bodies[i];
        const int previousParent=entry.parent;
        if(entry.attached!=attached[i]) {
            configureMode(i,animationPhysics_Dynamic);
            entry.destination=animationPhysics_Dynamic;entry.recovering=false;
            entry.routeReady=entry.hasTargetSample=false;entry.attached=attached[i];
        }
        // Skip removed ancestors when choosing the remaining control hierarchy.
        entry.parent=-1;
        for(auto ancestor=mRig->getBone(mDefinition.bodies[i].bone).parent;ancestor!=animation_NoBone;ancestor=mRig->getBone(ancestor).parent) {
            for(size_t j=0;j<attached.size();++j)if(attached[j] && mDefinition.bodies[j].bone==ancestor){entry.parent=int(j);break;}
            if(entry.parent>=0)break;
        }
        if(entry.parent!=previousParent)entry.routeReady=entry.hasTargetSample=false;
        if(entry.recoveryMotor) {
            // A later recovery may have a different parent after detachment.
            if(cpSpaceContainsConstraint(mStorage->space,entry.recoveryMotor))cpSpaceRemoveConstraint(mStorage->space,entry.recoveryMotor);
            auto& joints=mStorage->joints;std::erase(joints, entry.recoveryMotor);
            cpConstraintFree(entry.recoveryMotor);entry.recoveryMotor=nullptr;
        }
    }
    mDefinition.rootBody=root;
}
void AnimationPhysicsRig::removeDetachedBodies(const std::vector<uint32_t>& indices) {
    if(indices.empty())return;
    require(mControl && mStorage->shapes.empty(),"Body transfer requires a shared component rig");
    std::vector<bool> removed(mDefinition.bodies.size());
    for(auto i:indices) {
        require(i<removed.size() && !removed[i] && !mControl->bodies[i].attached,
                "Detach each mapped body before transferring it");
        removed[i]=true;
    }
    require(!removed[mDefinition.rootBody],"The physical root must remain in the rig");
    std::vector<int> remap(removed.size(),-1);
    auto definition=mDefinition;definition.bodies.clear();definition.joints.clear();
    auto control=*mControl;control.bodies.clear();control.order.clear();control.requests.clear();
    std::vector<cpBody*> bodies;std::vector<std::pair<double,double>> scales;
    std::vector<AnimationBoneId> order;
    for(size_t i=0;i<removed.size();++i)if(!removed[i]) {
        remap[i]=bodies.size();bodies.push_back(mStorage->bodies[i]);scales.push_back(mStorage->scales[i]);
        definition.bodies.push_back(mDefinition.bodies[i]);control.bodies.push_back(mControl->bodies[i]);
    }
    definition.rootBody=remap[mDefinition.rootBody];
    for(auto joint:mDefinition.joints)if(!removed[joint.parent] && !removed[joint.child]) {
        joint.parent=remap[joint.parent];joint.child=remap[joint.child];definition.joints.push_back(joint);
    }
    for(auto& entry:control.bodies)if(entry.parent>=0)entry.parent=remap[entry.parent];
    for(auto i:mControl->order)if(!removed[i]){control.order.push_back(remap[i]);order.push_back(mDefinition.bodies[i].bone);}
    // Shared observers remove native shapes/joints before the borrowed body dies.
    // Public PhysicsBody and constraint identities remain alive on their Parts.
    for(auto i:indices) {
        auto& entry=mControl->bodies[i];entry.body->detachSolver();entry.body->mCoordinateMode={};
        auto* native=mStorage->bodies[i];registry().erase(native);
        if(cpSpaceContainsBody(mStorage->space,native))cpSpaceRemoveBody(mStorage->space,native);
        cpBodyFree(native);
    }
    mDefinition=std::move(definition);*mControl=std::move(control);
    mStorage->bodies=std::move(bodies);mStorage->scales=std::move(scales);mOrder=std::move(order);
}
int AnimationPhysicsRig::getMode(const std::vector<uint32_t>& selection) const {
    int result=mControl->bodies.at(selection.at(0)).mode;
    for(auto i:selection)if(mControl->bodies.at(i).mode!=result)return animationPhysics_Mixed;
    return result;
}
void AnimationPhysicsRig::configureMode(uint32_t index,int mode) {
    auto& entry=mControl->bodies[index];auto& body=*entry.body;
    if(entry.recoveryMotor && cpSpaceContainsConstraint(mStorage->space,entry.recoveryMotor))
        cpSpaceRemoveConstraint(mStorage->space,entry.recoveryMotor);
    if(entry.recoveryMotor)reinterpret_cast<cpSimpleMotor*>(entry.recoveryMotor)->jAcc=0;
    body.syncState();
    body.mMode=mode==animationPhysics_Kinematic?physicsBody_Kinematic:physicsBody_Dynamic;
    body.configureSolver();body.commitState(false);
    if(body.mDriveController==this){body.mDrive=PhysicsDriveState();body.mDriveController=nullptr;body.mRigDrive=false;}
    if(mode!=animationPhysics_Dynamic){body.mDriveController=this;body.mRigDrive=true;}
    entry.mode=mode;
    // Preserve scheduled loads and release velocities. Only the rig's own drive is removed.
}
void AnimationPhysicsRig::setDriveSettings(const AnimationPhysicsDriveSettings& settings,
                                           const std::vector<uint32_t>& selection) {
    const double omega=physicsTurn*settings.frequency;
    require(finite(settings.maxForce)&&settings.maxForce>=0&&finite(settings.maxTorque)&&settings.maxTorque>=0&&
        finite(settings.frequency)&&settings.frequency>0&&finite(settings.dampingRatio)&&settings.dampingRatio>=0&&
        finite(omega*omega)&&finite(2*settings.dampingRatio*omega)&&
        finite(std::min(omega*omega*settings.frequency,2*settings.dampingRatio*omega*omega*omega*.25)),
        "Invalid animation physics drive settings");
    validatePhysicalDirection(settings.direction);
    if(cpSpaceIsLocked(mStorage->space))throw std::logic_error("Change rig control outside physics callbacks");
    for(auto i:selection) {auto& b=mControl->bodies.at(i);b.settings=settings;b.routeReady=false;}
}
std::optional<AnimationPhysicsDriveSettings> AnimationPhysicsRig::getDriveSettings(uint32_t index) const {
    return mControl->bodies.at(index).settings;
}
void AnimationPhysicsRig::setMode(int mode,const std::vector<uint32_t>& selection,double seconds,int direction,
    const AnimationPose& desired,const AnimationTransform& root,AnimationPhysicsRecovery request) {
    require(mode>=animationPhysics_Kinematic&&mode<=animationPhysics_Driven,"Invalid animation physics mode");
    require(finite(seconds)&&seconds>=0,"Recovery duration must be finite nonnegative seconds");
    validatePhysicalDirection(direction);validatePose(desired,root);
    if(cpSpaceIsLocked(mStorage->space))throw std::logic_error("Change rig control outside physics callbacks");
    // Stage every target and ownership check before changing any selected body.
    auto next=mControl->bodies;
    bool reanchor=!mControl->hasAnchor;
    for(auto i:selection)if(next.at(i).parent<0 && next[i].mode==animationPhysics_Dynamic)reanchor=true;
    const auto anchor=reanchor?root:mControl->anchor;
    for(auto i:selection) {
        auto& entry=next.at(i);auto& body=*entry.body;
        if ((body.mDriveController && body.mDriveController!=this) || (!body.mDriveController && body.mDrive.enabled))
            throw std::logic_error("Explicitly release the manual or Part IK drive before changing rig control");
        if(mode==animationPhysics_Driven&&!entry.settings)throw std::logic_error("Configure drive settings before selecting Driven");
        auto target=targetFrame(i,desired,anchor);
        auto current=physicalStateFrame(body.getState());
        if(entry.parent>=0) {
            target=relativePhysicalFrame(targetFrame(entry.parent,desired,anchor),target);
            current=relativePhysicalFrame(physicalStateFrame(next[entry.parent].body->getState()),current);
        }
        const int routeDirection=mode==animationPhysics_Driven && seconds==0?entry.settings->direction:direction;
        const double routed=physicalRoute(target.rotation,current.rotation,routeDirection);
        entry.start=current;entry.routeOffset=routed-target.rotation;entry.routeReady=true;
        entry.previousTargetAngle=target.rotation;entry.routeDirection=routeDirection;
        entry.duration=seconds;entry.elapsed=0;entry.destination=mode;
        entry.recoveryX=entry.recoveryY=0;
        entry.recovering=mode!=animationPhysics_Dynamic&&seconds>0;
        entry.target=entry.desired=target;
        entry.localTarget=entry.recovering?current:target;entry.hasTargetSample=true;
        if(!entry.recovering)entry.localTarget.rotation=routed;
    }
    // An overlapping command cancels the old selection's completion notification.
    // Nonoverlapping bodies in that selection may still finish their transition.
    auto& requests=mControl->requests;
    std::erase_if(requests, [&](const auto& r){
        if(r.disabled)return true;
        for(auto i:selection)if(std::find(r.bodies.begin(),r.bodies.end(),i)!=r.bodies.end())return true;
        return false;
    });
    mControl->bodies=std::move(next);
    mControl->anchor=anchor;mControl->published=root;mControl->hasAnchor=true;
    for(auto i:selection) {
        auto& entry=mControl->bodies[i];
        configureMode(i,entry.recovering?animationPhysics_Driven:mode);
    }
    if(mode==animationPhysics_Kinematic && seconds==0)for(auto i:mControl->order) {
        if(std::find(selection.begin(),selection.end(),i)==selection.end())continue;
        auto& entry=mControl->bodies[i];auto target=entry.desired;target.rotation+=entry.routeOffset;
        if(entry.parent>=0)target=AnimationTransform::compose(physicalStateFrame(mControl->bodies[entry.parent].body->getState()),target);
        auto state=entry.body->getState();state.x=target.x;state.y=target.y;state.rotation=target.rotation;
        entry.body->mState=state;entry.body->commitState(false);
    }
    if(mode!=animationPhysics_Dynamic) {
        request.mode=mode;request.bodies=selection;requests.push_back(std::move(request));
    }
}
void AnimationPhysicsRig::publishedRoot(const AnimationTransform& root) {
    if(mControl)mControl->published=root;
}
double AnimationPhysicsRig::bodyReflection(uint32_t index) const {
    const auto& scale=mStorage->scales.at(index);
    return scale.first*scale.second<0 ? -1 : 1;
}
void AnimationPhysicsRig::reflect(const AnimationTransform& root, bool flipX, bool flipY,
                                  const std::vector<PhysicsBody*>& members) {
    if (!flipX && !flipY) return;
    require(mControl && !cpSpaceIsLocked(mStorage->space),"Flip physical rigs outside the physical solve");
    const std::set<PhysicsBody*> included(members.begin(),members.end());
    std::set<PhysicsConstraint*> joints;
    for (auto* b:members) for (auto* j:b->mConstraints) joints.insert(j);
    // A boundary angular constraint relates two different coordinate policies.
    // Reject before changing anything; ordinary external pivots remain anchored.
    for (auto* j:joints) if (j->mType>=constraint_RotarySpring &&
        (included.count(j->mA)!=included.count(j->mB)))
        throw std::logic_error("Disconnect external angular constraints before reflecting a physical rig");
    const double sx=flipX?-1:1, sy=flipY?-1:1, sign=sx*sy;
    const double c=std::cos(root.rotation), s=std::sin(root.rotation);
    const double a=c*c*sx+s*s*sy, b=c*s*(sx-sy), d=s*s*sx+c*c*sy;
    const double angleOffset=(sign<0?2*root.rotation:0)+(flipX?physicsTurn/2:0);
    auto worldFrame=[&](AnimationTransform& t) {
        const double x=t.x-root.x,y=t.y-root.y;
        t.x=root.x+a*x+b*y;t.y=root.y+b*x+d*y;
        t.rotation=sign*t.rotation+angleOffset;
    };
    std::vector<PhysicsBodyState> states;
    states.reserve(members.size());
    for (auto* body:members) {
        auto state=body->getState();
        AnimationTransform frame{state.x,state.y,state.rotation};worldFrame(frame);
        const double vx=state.velocityX,vy=state.velocityY;
        state.x=frame.x;state.y=frame.y;state.rotation=frame.rotation;
        state.velocityX=a*vx+b*vy;state.velocityY=b*vx+d*vy;state.angularVelocity*=sign;
        for(double value:{state.x,state.y,state.rotation,state.velocityX,state.velocityY,state.angularVelocity})
            require(finite(value),"Reflected physical state is not representable");
        states.push_back(state);
    }
    for(auto* j:joints) if(j->mType==constraint_Gear)
        require(finite(sign*j->mValue2+angleOffset*(j->mValue1-1)),"Reflected gear phase is not representable");
    // Everything below is an in-place isometry. Retained bodies, constraints,
    // colliders and force handles stay alive; world-space loads keep their frame.
    for(size_t i=0;i<members.size();++i) {
        auto* body=members[i];body->mState=states[i];body->mKinematicCaptured=body->mKinematicDriven=false;
        body->commitState(false);
    }
    for (auto* j:joints) {
        if(included.count(j->mA)){j->mAnchorA.y*=sign;j->mGroove.y*=sign;}
        if(included.count(j->mB))j->mAnchorB.y*=sign;
        switch(j->mType) {
        case constraint_RotarySpring: j->mValue1*=sign;break;
        case constraint_RotaryLimit:
            if(sign<0){const double low=j->mValue1;j->mValue1=-j->mValue2;j->mValue2=-low;}break;
        case constraint_Ratchet: j->mValue1*=sign;j->mValue2*=sign;j->mValue3*=sign;break;
        case constraint_Gear: j->mValue2=sign*j->mValue2+angleOffset*(j->mValue1-1);break;
        case constraint_Motor: j->mValue1*=sign;break;
        default: break;
        }
        j->mAnchorsDirty=true; // Discard the solver's impulses for the old frame.
    }
    for(size_t i=0;i<mControl->bodies.size();++i) {
        auto& entry=mControl->bodies[i];if(!entry.attached)continue;
        mStorage->scales[i].first*=sx;mStorage->scales[i].second*=sy;
        auto relative=[&](AnimationTransform& t) {
            if(entry.parent<0)worldFrame(t);else{t.y*=sign;t.rotation*=sign;}
        };
        relative(entry.start);relative(entry.desired);relative(entry.localTarget);worldFrame(entry.target);
        entry.routeReady=entry.hasTargetSample=false;
        entry.recoveryX=entry.recoveryY=0;
        if(entry.recoveryMotor) {
            if(cpSpaceContainsConstraint(mStorage->space,entry.recoveryMotor))cpSpaceRemoveConstraint(mStorage->space,entry.recoveryMotor);
            auto& list=mStorage->joints;std::erase(list, entry.recoveryMotor);
            cpConstraintFree(entry.recoveryMotor);entry.recoveryMotor=nullptr;
        }
    }
    // The target frame is translated about the displayed origin, but its
    // orientation remains the Sprite orientation with signed scale carrying flip.
    auto& control=*mControl;
    const double x=control.anchor.x-root.x,y=control.anchor.y-root.y;
    control.anchor.x=root.x+a*x+b*y;control.anchor.y=root.y+b*x+d*y;
    control.anchor.scaleX*=sx;control.anchor.scaleY*=sy;
    control.published=root;control.published.scaleX*=sx;control.published.scaleY*=sy;
}
void AnimationPhysicsRig::frameChanged(const AnimationTransform& root) {
    if(!mControl)return;
    auto& control=*mControl;
    if(!control.hasAnchor){control.anchor=control.published=root;control.hasAnchor=true;return;}
    // Consume gameplay edits before a pose query can publish the followed frame.
    // Publishing the solved root is observation, not another drive command.
    control.anchor.x+=root.x-control.published.x;
    control.anchor.y+=root.y-control.published.y;
    control.anchor.rotation+=root.rotation-control.published.rotation;
    control.published=root;
}
void AnimationPhysicsRig::prepareControls(const AnimationPose& pose,const AnimationTransform& root,double seconds) {
    if(!mControl) { // Standalone definition adapter, without Sprite-owned PhysicsBodies.
        for(uint32_t i=0;i<mDefinition.bodies.size();++i)if(cpBodyGetType(body(i))==CP_BODY_TYPE_KINEMATIC) {
            const auto target=targetFrame(i,pose,root);auto* b=body(i);const auto p=cpBodyGetPosition(b);
            cpBodySetVelocity(b,seconds>0?cpv((target.x-p.x)/seconds,(target.y-p.y)/seconds):cpvzero);
            cpBodySetAngularVelocity(b,seconds>0?(target.rotation-cpBodyGetAngle(b))/seconds:0);
        }
        return;
    }
    auto& control=*mControl;
    frameChanged(root);
    std::vector<AnimationTransform> frames;frames.reserve(control.bodies.size());
    for(uint32_t i=0;i<control.bodies.size();++i)frames.push_back(targetFrame(i,pose,control.anchor));
    for(auto i:control.order) {
        auto& entry=control.bodies[i];auto& b=*entry.body;
        if(!entry.attached || entry.mode==animationPhysics_Dynamic)continue;
        auto target=frames[i];auto state=b.getState();PhysicsBodyState parentState;
        if(entry.parent>=0){parentState=control.bodies[entry.parent].body->getState();target=relativePhysicalFrame(frames[entry.parent],target);}
        auto current=physicalStateFrame(state);
        if(entry.parent>=0)current=relativePhysicalFrame(physicalStateFrame(parentState),current);
        const auto settings=entry.settings.value_or(AnimationPhysicsDriveSettings{});
        if(!entry.routeReady) {
            entry.routeOffset=physicalRoute(target.rotation,current.rotation,settings.direction)-target.rotation;
            entry.routeDirection=settings.direction;
            entry.routeReady=true;
        } else if(entry.routeDirection!=rotationDirection_AsSpecified) {
            // Imported poses can wrap a small wrist oscillation across 0/2pi.
            // Keep the selected route continuous; otherwise both the spring
            // error and target angular velocity demand a spurious full turn.
            const double delta=std::remainder(target.rotation-entry.previousTargetAngle,physicsTurn);
            entry.routeOffset+=entry.previousTargetAngle+delta-target.rotation;
        }
        entry.previousTargetAngle=target.rotation;
        target.rotation+=entry.routeOffset;
        entry.desired=target;
        if(entry.recovering) {
            entry.elapsed=std::min(entry.duration,entry.elapsed+seconds);
            const double t=entry.elapsed/entry.duration, blend=t*t*(3-2*t);
            target.x=entry.start.x+(target.x-entry.start.x)*blend;
            target.y=entry.start.y+(target.y-entry.start.y)*blend;
            target.rotation=entry.start.rotation+(target.rotation-entry.start.rotation)*blend;
        }
        double targetVX=0,targetVY=0,targetAngular=0;
        if(seconds>0 && entry.hasTargetSample) {
            targetVX=(target.x-entry.localTarget.x)/seconds;targetVY=(target.y-entry.localTarget.y)/seconds;
            targetAngular=(target.rotation-entry.localTarget.rotation)/seconds;
        }
        entry.localTarget=target;entry.hasTargetSample=true;
        // The relative target is carried by the actual physical parent, not its
        // animation world pose. Equal/opposite actuation preserves free-fall motion.
        if(entry.parent>=0) {
            const auto& parent=control.bodies[entry.parent];
            const auto frame=entry.mode==animationPhysics_Kinematic && parent.mode==animationPhysics_Kinematic ? parent.target : physicalStateFrame(parentState);
            target=AnimationTransform::compose(frame,target);
        }
        entry.target=target;
        if(entry.mode==animationPhysics_Kinematic) {
            cpBodySetVelocity(body(i),seconds>0?cpv((target.x-state.x)/seconds,(target.y-state.y)/seconds):cpvzero);
            cpBodySetAngularVelocity(body(i),seconds>0?(target.rotation-state.rotation)/seconds:0);
            continue;
        }
        auto& drive=b.mDrive;
        drive.enabled=true;drive.x=target.x;drive.y=target.y;drive.rotation=target.rotation;
        drive.frequency=settings.frequency;drive.dampingRatio=settings.dampingRatio;
        drive.maxForce=settings.maxForce;drive.maxTorque=settings.maxTorque;
        if(!entry.settings) {
            // Transient recovery servo only. Deliberate Driven mode always needs
            // caller-selected force caps. Scale recovery bounds to this segment.
            const double omega=physicsTurn*drive.frequency;
            drive.maxForce=b.getMass()*std::max(mDefinition.bodies[i].length,1e-3)*omega*omega;
            drive.maxTorque=b.getMomentOfInertia()*omega*omega;
        }
        if(seconds<=0)continue;
        const double omega=physicsTurn*drive.frequency,k=omega*omega,d=2*drive.dampingRatio*omega;
        const double denominator=1+d*seconds+k*seconds*seconds;
        // Implicit spring feedback includes the position error's change during
        // this step, as well as the velocity damper. Omitting k*dt here makes
        // stiff drives lose damping as the timestep grows.
        const double velocityGain=d+k*seconds;
        double vx=targetVX,vy=targetVY,angular=targetAngular,mass=b.getMass(),inertia=b.getMomentOfInertia();
        PhysicsBody* parent=nullptr;
        if(entry.parent>=0) {
            parent=control.bodies[entry.parent].body;
            const double c=std::cos(parentState.rotation),s=std::sin(parentState.rotation);
            vx=parentState.velocityX-parentState.angularVelocity*(target.y-parentState.y)+c*targetVX-s*targetVY;
            vy=parentState.velocityY+parentState.angularVelocity*(target.x-parentState.x)+s*targetVX+c*targetVY;
            angular=parentState.angularVelocity+targetAngular;
            if(parent->getMode()==physicsBody_Dynamic){mass=1/(1/mass+1/parent->getMass());inertia=1/(1/inertia+1/parent->getMomentOfInertia());}
        }
        double recoveryX=0,recoveryY=0;
        if(entry.recovering) {
            // Bounded integral correction removes steady gravity/load error while
            // recovering. It never increases the caller's force/torque caps.
            const double gain=std::min(k*drive.frequency,d*k*.25);
            entry.recoveryX+=gain*(entry.localTarget.x-current.x)*seconds;
            entry.recoveryY+=gain*(entry.localTarget.y-current.y)*seconds;
            // These accumulators are divided by the implicit denominator below.
            // Bound their *resulting* force/torque, so heavy damping does not
            // silently reduce the steady load the configured drive can support.
            const double limit=drive.maxForce/mass*denominator,magnitude=std::hypot(entry.recoveryX,entry.recoveryY);
            if(magnitude>limit){entry.recoveryX*=limit/magnitude;entry.recoveryY*=limit/magnitude;}
            recoveryX=entry.recoveryX;recoveryY=entry.recoveryY;
            if(entry.parent>=0) {
                const double c=std::cos(parentState.rotation),s=std::sin(parentState.rotation);
                recoveryX=c*entry.recoveryX-s*entry.recoveryY;recoveryY=s*entry.recoveryX+c*entry.recoveryY;
            }
        }
        drive.forceX=mass*(k*(target.x-state.x)-velocityGain*(state.velocityX-vx)+recoveryX)/denominator;
        drive.forceY=mass*(k*(target.y-state.y)-velocityGain*(state.velocityY-vy)+recoveryY)/denominator;
        const double magnitude=std::hypot(drive.forceX,drive.forceY);
        if(magnitude>drive.maxForce){drive.forceX*=drive.maxForce/magnitude;drive.forceY*=drive.maxForce/magnitude;}
        drive.torque=std::clamp(inertia*(k*(target.rotation-state.rotation)-velocityGain*(state.angularVelocity-angular))/denominator,-drive.maxTorque,drive.maxTorque);
        if(entry.recovering) {
            // Solve the recovering angular drive alongside the articulated
            // joints. An explicit torque based only on segment-center inertia
            // cannot stably control a small segment carrying a large branch.
            if(!entry.recoveryMotor) {
                entry.recoveryMotor=cpSimpleMotorNew(entry.parent>=0?body(entry.parent):cpSpaceGetStaticBody(mStorage->space),body(i),0);
                mStorage->joints.push_back(entry.recoveryMotor);
                cpConstraintSetCollideBodies(entry.recoveryMotor,false);
            }
            const double rate=targetAngular+k/velocityGain*(entry.localTarget.rotation-current.rotation);
            cpSimpleMotorSetRate(entry.recoveryMotor,-rate);
            entry.motorSeconds=seconds;
            cpConstraintSetMaxForce(entry.recoveryMotor,drive.maxTorque);
            if(!cpSpaceContainsConstraint(mStorage->space,entry.recoveryMotor))cpSpaceAddConstraint(mStorage->space,entry.recoveryMotor);
            drive.torque=0;
        }
        require(finite(drive.forceX)&&finite(drive.forceY)&&finite(drive.torque),"Animation drive load overflow");
        cpBodyApplyForceAtWorldPoint(body(i),cpv(drive.forceX,drive.forceY),cpv(state.x,state.y));
        cpBodySetTorque(body(i),cpBodyGetTorque(body(i))+drive.torque);
        if(parent&&parent->getMode()==physicsBody_Dynamic) {
            cpBodyApplyForceAtWorldPoint(body(entry.parent),cpv(-drive.forceX,-drive.forceY),cpv(state.x,state.y));
            cpBodySetTorque(body(entry.parent),cpBodyGetTorque(body(entry.parent))-drive.torque);
        }
    }
    // Imported joints have private storage, but obey the same dormant rule.
    for(auto* joint:mStorage->joints) {
        // Recovery motors have a narrower lifetime than ordinary rig joints.
        if(cpConstraintIsSimpleMotor(joint))continue;
        const bool active=cpBodyGetType(cpConstraintGetBodyA(joint))==CP_BODY_TYPE_DYNAMIC||cpBodyGetType(cpConstraintGetBodyB(joint))==CP_BODY_TYPE_DYNAMIC;
        if(active&&!cpSpaceContainsConstraint(mStorage->space,joint))cpSpaceAddConstraint(mStorage->space,joint);
        if(!active&&cpSpaceContainsConstraint(mStorage->space,joint))cpSpaceRemoveConstraint(mStorage->space,joint);
    }
}
std::vector<AnimationPhysicsRecovery> AnimationPhysicsRig::finishStep(const AnimationPose&,const AnimationTransform&) {
    std::vector<AnimationPhysicsRecovery> completed;
    if(!mControl)return completed;
    for(uint32_t i=0;i<mControl->bodies.size();++i) {
        auto& entry=mControl->bodies[i];
        if(!entry.attached)continue;
        if(entry.mode==animationPhysics_Driven) {
            auto target=entry.localTarget;
            if(entry.parent>=0)target=AnimationTransform::compose(physicalStateFrame(mControl->bodies[entry.parent].body->getState()),target);
            auto& drive=entry.body->mDrive;drive.x=target.x;drive.y=target.y;drive.rotation=target.rotation;
            if(entry.recovering && entry.recoveryMotor && entry.motorSeconds>0)
                drive.torque=reinterpret_cast<cpSimpleMotor*>(entry.recoveryMotor)->jAcc/entry.motorSeconds;
        }
        if(!entry.recovering||entry.elapsed<entry.duration)continue;
        if(entry.destination==animationPhysics_Kinematic) {
            // A child can already match its relative pose while its ancestor is
            // still returning through world space. Keep it physical until that
            // ancestor settles: a kinematic child otherwise imposes an infinite
            // mass pivot on the recovering parent using the previous frame's
            // transform, which can inject energy into the connected chain.
            bool waiting=false;
            for(auto parent=entry.parent;parent>=0;parent=mControl->bodies[parent].parent)
                if(mControl->bodies[parent].recovering){waiting=true;break;}
            if(waiting)continue;
        }
        auto actual=physicalStateFrame(entry.body->getState());
        if(entry.parent>=0)actual=relativePhysicalFrame(physicalStateFrame(mControl->bodies[entry.parent].body->getState()),actual);
        const double tolerance=std::max(1e-6,mDefinition.bodies[i].length*1e-3);
        if(std::hypot(actual.x-entry.desired.x,actual.y-entry.desired.y)>tolerance||std::abs(actual.rotation-entry.desired.rotation)>1e-3)continue;
        entry.recovering=false;configureMode(i,entry.destination);
    }
    auto& requests=mControl->requests;
    for(auto it=requests.begin();it!=requests.end();) {
        if(std::any_of(it->bodies.begin(),it->bodies.end(),[&](auto i){return mControl->bodies[i].recovering;})){++it;continue;}
        completed.push_back(*it);it=requests.erase(it);
    }
    return completed;
}
