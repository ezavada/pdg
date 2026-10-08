// Rig coordination sits above the shared body/collider/constraint snapshot.
uint32 AnimationPhysicsRig::snapshotRecord(ISerializer* writer, bool emit) const {
    if(!mControl || cpSpaceIsLocked(mStorage->space))throw std::logic_error("Save rig state outside the physical solve");
    SnapshotWriter out(writer,emit);
    out.byte(1);out.flag(mDefinition.generated);out.byte(mDefinition.rootMode);
    out.integer(mDefinition.rootBody);out.flag(mDefinition.selfCollisions);
    out.integer(mDefinition.bodies.size());
    for(const auto& b:mDefinition.bodies) {
        out.integer(b.bone);out.byte(b.mode);
        for(double n:{b.mass,b.length,b.radius,b.offsetX,b.offsetY,b.offsetRotation,b.friction,b.elasticity})out.real(n);
        out.integer(b.categories);out.integer(b.mask);
    }
    // Definition joints are retained as setup metadata only. The graph record
    // carries the actual edited, broken, removed or added constraints.
    out.integer(mDefinition.joints.size());
    for(const auto& j:mDefinition.joints) {
        out.integer(j.parent);out.integer(j.child);
        for(double n:{j.parentX,j.parentY,j.childX,j.childY,j.minAngle,j.maxAngle})out.real(n);
        out.real(j.maxForce,INFINITY);out.flag(j.collide);
    }
    const auto transform=[&](const AnimationTransform& t) {
        for(double n:{t.x,t.y,t.rotation,t.scaleX,t.scaleY,t.alpha})out.real(n);
    };
    out.flag(mControl->hasAnchor);transform(mControl->anchor);transform(mControl->published);
    for(size_t i=0;i<mControl->bodies.size();++i) {
        const auto& b=mControl->bodies[i];
        out.real(mStorage->scales[i].first,1);out.real(mStorage->scales[i].second,1);
        out.byte(b.mode);out.byte(b.destination);out.signedInteger(b.parent,-1);
        out.flag(b.attached);out.flag(b.recovering);out.flag(b.routeReady);out.flag(b.hasTargetSample);
        out.byte(b.routeDirection);
        for(double n:{b.duration,b.elapsed,b.routeOffset,b.previousTargetAngle,b.recoveryX,b.recoveryY,b.motorSeconds})out.real(n);
        transform(b.start);transform(b.target);transform(b.desired);transform(b.localTarget);
        if(out.flag(bool(b.settings))) {
            const auto& s=*b.settings;
            for(double n:{s.maxForce,s.maxTorque,s.frequency,s.dampingRatio})out.real(n);
            out.byte(s.direction);
        }
    }
    out.integer(mControl->requests.size());
    for(const auto& r:mControl->requests) {
        out.integer(r.bone);out.flag(r.includeDescendants);out.flag(r.disabled);out.byte(r.mode);
        out.integer(r.bodies.size());for(auto i:r.bodies)out.integer(i);
    }
    return out.size();
}
std::unique_ptr<AnimationPhysicsRig> AnimationPhysicsRig::restoreSnapshot(IDeserializer* reader,
    const AnimationPose& desired,const AnimationTransform& root,const std::vector<PhysicsBody*>& bodies,std::function<void()> moved) {
    SnapshotReader in(reader);
    auto valid=[](bool ok){if(!ok)throw std::runtime_error("Invalid animation physics snapshot");};
    auto count=[&]{auto n=in.integer();valid(n<=65536);return n;};
    auto number=[&](double fallback=0){double n=in.real(fallback);valid(std::isfinite(n));return n;};
    valid(in.byte()==1);AnimationPhysicsDefinition def;
    def.generated=in.flag();def.rootMode=in.byte();def.rootBody=in.integer();def.selfCollisions=in.flag();
    const auto size=count();valid(size && size==bodies.size());
    for(uint32 i=0;i<size;++i) {
        AnimationPhysicsBody b;b.bone=in.integer();b.mode=in.byte();
        for(auto* n:{&b.mass,&b.length,&b.radius,&b.offsetX,&b.offsetY,&b.offsetRotation,&b.friction,&b.elasticity})*n=number();
        b.categories=in.integer();b.mask=in.integer();def.bodies.push_back(b);
    }
    for(auto n=count();n;--n) {
        AnimationPhysicsJoint j;j.parent=in.integer();j.child=in.integer();
        for(auto* v:{&j.parentX,&j.parentY,&j.childX,&j.childY,&j.minAngle,&j.maxAngle})*v=number();
        j.maxForce=in.real(INFINITY);j.collide=in.flag();def.joints.push_back(j);
    }
    valid(def.rootMode==animationRoot_Fixed || def.rootMode==animationRoot_Follow);
    auto construction=def;construction.rootMode=animationRoot_Fixed; // Initial-mode restrictions do not describe the saved mixed state.
    auto rig=std::make_unique<AnimationPhysicsRig>(nullptr,construction,desired,root,0,0,0,true);
    rig->mDefinition=def;
    auto control=std::make_unique<Control>();control->bodies.resize(size);
    auto transform=[&]{AnimationTransform t;for(auto* n:{&t.x,&t.y,&t.rotation,&t.scaleX,&t.scaleY,&t.alpha})*n=number();valid(t.isValid());return t;};
    control->hasAnchor=in.flag();control->anchor=transform();control->published=transform();
    for(size_t i=0;i<size;++i) {
        auto& b=control->bodies[i];b.body=bodies[i];
        auto& scale=rig->mStorage->scales[i];scale.first=number(1);scale.second=number(1);valid(scale.first!=0 && scale.second!=0);
        b.mode=in.byte();b.destination=in.byte();b.parent=in.signedInteger(-1);
        b.attached=in.flag();b.recovering=in.flag();b.routeReady=in.flag();b.hasTargetSample=in.flag();
        b.routeDirection=in.byte();validatePhysicalDirection(b.routeDirection);
        for(auto* n:{&b.duration,&b.elapsed,&b.routeOffset,&b.previousTargetAngle,&b.recoveryX,&b.recoveryY,&b.motorSeconds})*n=number();
        b.start=transform();b.target=transform();b.desired=transform();b.localTarget=transform();
        valid(b.mode<=animationPhysics_Driven && b.destination<=animationPhysics_Driven && b.parent>=-1 && b.parent<int(size) && b.parent!=int(i));
        valid(b.duration>=0 && b.elapsed>=0 && b.motorSeconds>=0);
        valid(!b.recovering || (b.attached && b.mode==animationPhysics_Driven && b.destination!=animationPhysics_Dynamic && b.duration>0));
        valid(b.attached || (b.mode==animationPhysics_Dynamic && !b.recovering));
        valid(b.body && b.body->getMode()==(b.mode==animationPhysics_Kinematic?physicsBody_Kinematic:physicsBody_Dynamic));
        if(in.flag()) {
            AnimationPhysicsDriveSettings s;for(auto* n:{&s.maxForce,&s.maxTorque,&s.frequency,&s.dampingRatio})*n=number();s.direction=in.byte();
            validatePhysicalDirection(s.direction);
            const double w=physicsTurn*s.frequency;
            valid(s.maxForce>=0 && s.maxTorque>=0 && s.frequency>0 && s.dampingRatio>=0 && finite(w*w) && finite(2*s.dampingRatio*w));
            b.settings=s;
        }
        valid(b.mode!=animationPhysics_Driven || b.recovering || b.settings.has_value());
    }
    valid(control->bodies[def.rootBody].attached);
    for(size_t i=0;i<size;++i) {
        int parent=-1;
        for(auto bone=rig->mRig->getBone(def.bodies[i].bone).parent;bone!=animation_NoBone;bone=rig->mRig->getBone(bone).parent) {
            for(size_t j=0;j<size;++j)if(control->bodies[j].attached && def.bodies[j].bone==bone){parent=int(j);break;}
            if(parent>=0)break;
        }
        valid(control->bodies[i].parent==parent);
    }
    for(auto bone:rig->mOrder)for(uint32 i=0;i<size;++i)if(def.bodies[i].bone==bone)control->order.push_back(i);
    std::set<uint32> requested;
    for(auto n=count();n;--n) {
        AnimationPhysicsRecovery r;r.bone=in.integer();r.includeDescendants=in.flag();r.disabled=in.flag();r.mode=in.byte();
        valid((r.bone==animation_NoBone || r.bone<rig->mRig->getBoneCount()) && r.mode<=animationPhysics_Driven);
        for(auto c=count();c;--c){auto i=in.integer();valid(i<size && control->bodies[i].attached && requested.insert(i).second);r.bodies.push_back(i);}
        valid(!r.bodies.empty());control->requests.push_back(std::move(r));
    }
    // Validation precedes adopting any restored body. Preserve its serialized
    // manual drive, loads, material, velocity and sampled rig-drive diagnostics.
    rig->mControl=std::move(control);
    for(size_t i=0;i<size;++i) {
        auto& b=rig->mControl->bodies[i];
        b.body->attachSolver(rig->createBodySolver(i,moved));
        if(b.mode!=animationPhysics_Dynamic){b.body->mDriveController=rig.get();b.body->mRigDrive=true;}
    }
    return rig;
}
void AnimationPhysicsRig::moveToSpace(cpSpace* space) {
    require(space && !cpSpaceIsLocked(space),"Restore physical rigs into an unlocked physics world");
    if(space==mStorage->space)return;
    // Remove native graph observers before moving the bodies. Shared collider
    // and constraint handles survive and recreate their native objects on use.
    if(mControl)for(auto& b:mControl->bodies)b.body->clearSolverObservers();
    for(auto* joint:mStorage->joints){if(cpSpaceContainsConstraint(mStorage->space,joint))cpSpaceRemoveConstraint(mStorage->space,joint);cpConstraintFree(joint);}
    mStorage->joints.clear();
    if(mControl)for(auto& b:mControl->bodies)b.recoveryMotor=nullptr;
    require(mStorage->shapes.empty(),"Standalone primitive rigs cannot migrate between worlds");
    for(auto* b:mStorage->bodies){cpSpaceRemoveBody(mStorage->space,b);cpSpaceAddBody(space,b);}
    if(mStorage->ownsSpace)cpSpaceFree(mStorage->space);
    mStorage->space=space;mStorage->ownsSpace=false;
}

void AnimationPhysicsRig::adoptMovedSpace(cpSpace* space) {
    if(mStorage->ownsSpace && mStorage->space!=space)cpSpaceFree(mStorage->space);
    mStorage->space=space;mStorage->ownsSpace=false;
}
