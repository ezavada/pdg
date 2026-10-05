// Included inside namespace pdg after the complete Sprite/Part declarations.
PhysicsBody& PhysicsGraphSnapshot::Owner::body() const {
    return part ? static_cast<PhysicsBody&>(part->physics) : static_cast<PhysicsBody&>(sprite->physics);
}
Collider& PhysicsGraphSnapshot::Owner::collider() const {
    return part ? static_cast<Collider&>(part->collider) : static_cast<Collider&>(sprite->collider);
}
Collider& PhysicsGraphSnapshot::Owner::setupCollider() const {
    return part ? part->setupCollider() : sprite->setupCollider();
}
void PhysicsGraphSnapshot::append(const Sprite& sprite) {
    owners.push_back({const_cast<Sprite*>(&sprite),nullptr});
    for (auto* part:sprite.mParts) owners.push_back({const_cast<Sprite*>(&sprite),part});
}
PhysicsGraphSnapshot::PhysicsGraphSnapshot(const Sprite& sprite) { append(sprite); }
PhysicsGraphSnapshot::PhysicsGraphSnapshot(const SpriteLayer& layer) {
    for (auto* sprite=layer.mFirstSprite;sprite;sprite=sprite->mNextSprite) append(*sprite);
}
std::vector<PhysicsBody*> PhysicsGraphSnapshot::bodies() const {
    std::vector<PhysicsBody*> result;
    for (const auto& owner:owners) if (owner.body().isPresent()) result.push_back(&owner.body());
    return result;
}
uint32 PhysicsGraphSnapshot::bodyId(const PhysicsBody* body) const {
    if (!body) return 0; // use owner body
    for (size_t i=0;i<owners.size();++i) if (&owners[i].body()==body && body->isPresent()) {
        auto* layer=owners[i].sprite->mLayer;
        if(!owners[i].part && layer && !(layer->mSerFlags & (ser_Forces|ser_Physics)))
            throw std::runtime_error("Physics graph references require root body state in the selected serialization flags");
        return i+1;
    }
    throw std::runtime_error("Physics snapshot references a body outside the saved Sprite/Layer");
}
std::vector<PhysicsConstraint*> PhysicsGraphSnapshot::constraints() const {
    std::vector<PhysicsConstraint*> result;
    std::set<PhysicsConstraint*> seen;
    for (const auto& owner:owners) for (auto* joint:owner.body().mConstraints)
        if (seen.insert(joint).second) result.push_back(joint);
    // Preserve each body's public constraint order even when owner order differs
    // from joint creation order. Consecutive local entries form a DAG because
    // constraints are appended at creation on both endpoints.
    std::map<PhysicsConstraint*,size_t> index;
    for(size_t i=0;i<result.size();++i)index[result[i]]=i;
    std::vector<std::vector<size_t>> after(result.size());
    std::vector<size_t> incoming(result.size(),0);
    for(const auto& owner:owners) {
        const auto& list=owner.body().mConstraints;
        for(size_t i=1;i<list.size();++i) {
            const auto a=index.at(list[i-1]),b=index.at(list[i]);
            after[a].push_back(b);++incoming[b];
        }
    }
    std::set<size_t> ready;
    for(size_t i=0;i<result.size();++i)if(!incoming[i])ready.insert(i);
    std::vector<PhysicsConstraint*> ordered;
    while(!ready.empty()) {
        auto i=*ready.begin();ready.erase(ready.begin());ordered.push_back(result[i]);
        for(auto next:after[i])if(!--incoming[next])ready.insert(next);
    }
    if(ordered.size()!=result.size())throw std::runtime_error("Inconsistent constraint ordering in physics graph");
    return ordered;
}
void PhysicsGraphSnapshot::validate() const {
    const auto joints=constraints();
    for (const auto& owner:owners) {
        if (auto* part=owner.part) {
            if (part->mIKConstraint && std::find(joints.begin(),joints.end(),part->mIKConstraint)==joints.end())
                throw std::runtime_error("Cannot snapshot a disconnected IK limit; clear or replace its link first");
            if (part->isIKDriven()) for(auto* body:part->mIKTarget->bodies) if(body)bodyId(body);
        }
        if (owner.body().mBreakReference) { bodyId(&owner.body()); bodyId(owner.body().mBreakReference); }
        const auto& collider=owner.collider();
        if (!collider.isPresent()) continue;
        if (collider.mCollisionFilter || collider.mHandler)
            throw std::runtime_error("Collider snapshots cannot save callback filters or handlers");
#ifdef PDG_SPRITER_SUPPORT
        if (owner.part && collider.mGeometrySource==colliderSource_Animation &&
            (!collider.mAnimationSourceRig.lock() || !owner.part->getSprite() ||
             collider.mAnimationSourceRig.lock()!=owner.part->getSprite()->getAnimationRig()))
            throw std::runtime_error("Select a current Part animation collider source before saving");
#endif
        bodyId(collider.mCompoundBody);
        collider.refreshGeometry();
    }
    for (auto* joint:constraints()) { bodyId(joint->mA); bodyId(joint->mB); }
}
uint32 PhysicsGraphSnapshot::encode(ISerializer* writer, bool emit) const {
    SnapshotWriter out(writer,emit);
    auto byte=[&](uint8 n) { out.byte(n); };
    auto integer=[&](uint32 n) { out.integer(n); };
    auto number=[&](double n, double fallback=0) { out.real(n,fallback); };
    auto point=[&](const Point& p) { out.point(p); };
    auto string=[&](const std::string& s) { out.text(s); };
    auto points=[&](const std::vector<Point>& list) { integer(list.size());for(const auto& p:list)point(p); };
    byte(5); // Part authored-box selector and setup-local mapping
    integer(owners.size());
    for (const auto& owner:owners) out.optionalInteger(bodyId(owner.body().mBreakReference));
    for (const auto& owner:owners) {
        const auto& c=owner.collider(); if(!out.flag(c.isPresent()))continue;
        c.refreshGeometry();
        out.flag(c.mEnabled);out.flag(c.mSensor);out.flag(c.mWantsContactEvents);
        out.optionalInteger(c.mCategory,1);out.optionalInteger(c.mMask,UINT32_MAX);out.optionalInteger(c.mGroup);
        number(c.mFriction,-1);number(c.mRestitution,-1);out.optionalInteger(bodyId(c.mCompoundBody));
        byte(c.mGeometrySource);
        if(owner.part && c.mGeometrySource==colliderSource_Animation) {
            string(c.mAnimationBox);
            for(double value:{c.mSourceLocal.a,c.mSourceLocal.b,c.mSourceLocal.c,c.mSourceLocal.d,c.mSourceLocal.tx,c.mSourceLocal.ty})number(value);
        }
        if (out.flag(c.mFrameMode!=frameCollider_AlphaMask || c.mAlphaThreshold!=128)) { byte(c.mFrameMode);byte(c.mAlphaThreshold); }
        integer(c.mNextShape);integer(c.mSourceIds.size());
        for(const auto& item:c.mSourceIds){string(item.first);integer(item.second);}
        integer(c.mShapes.size());
        for(const auto& shape:c.mShapes) {
            integer(shape.id);byte(shape.type);out.flag(shape.source);string(shape.name);
            if(shape.type==collisionShape_Circle){point(shape.center);number(shape.radius);}
            else if(shape.type==collisionShape_Capsule){point(shape.vertices[0]);point(shape.vertices[1]);number(shape.radius);}
            else if(shape.type==collisionShape_Convex)points(shape.vertices);
            else {integer(shape.pieces.size());for(const auto& piece:shape.pieces)points(piece);}
        }
    }
    const auto joints=constraints();integer(joints.size());
    for(auto* c:joints) {
        byte(c->mType);integer(bodyId(c->mA));integer(bodyId(c->mB));
        if(c->mType<=constraint_Spring){point(c->mAnchorA);point(c->mAnchorB);}
        if(c->mType==constraint_Groove)point(c->mGroove);
        if(c->mType!=constraint_Pivot && c->mType!=constraint_Groove)number(c->mValue1);
        if(c->mType==constraint_Slide || (c->mType>=constraint_Spring && c->mType<=constraint_Gear))number(c->mValue2);
        if(c->mType==constraint_Spring || c->mType==constraint_RotarySpring || c->mType==constraint_Ratchet)number(c->mValue3);
        number(c->mMaxForce,std::numeric_limits<double>::infinity());
        for(double value:{c->mBreakForce,c->mImpulse,c->mForce})number(value);
        out.flag(c->mCollideBodies);
    }
    uint32 links=0,controllers=0;
    for(const auto& owner:owners) if(auto* part=owner.part) { if(part->mIKConstraint)++links;if(part->isIKDriven())++controllers; }
    integer(links);
    for(size_t i=0;i<owners.size();++i) if(auto* p=owners[i].part) if(p->mIKConstraint) {
        integer(i+1);integer(std::find(joints.begin(),joints.end(),p->mIKConstraint)-joints.begin()+1);
    }
    integer(controllers);
    for(size_t i=0;i<owners.size();++i) if(auto* p=owners[i].part) if(p->isIKDriven()) {
        const auto& ik=*p->mIKTarget;
        integer(i+1);integer(ik.middle);integer(ik.tip);point(ik.target);
        byte(ik.space);out.flag(ik.bend==1);number(ik.influence,1);out.flag(ik.reached);string(p->mIKError);
        point(ik.rootOffset);point(ik.middleOffset);point(ik.tipOffset);number(ik.tipAngle);
        for(double value:{ik.maxForce,ik.maxTorque,ik.frequency,ik.dampingRatio})number(value);
        for(auto* b:ik.bodies)integer(bodyId(b));
    }
    return out.size();
}
void PhysicsGraphSnapshot::read(IDeserializer* reader) {
    SnapshotReader in(reader);
    auto fail=[] { throw std::runtime_error("Invalid physics graph snapshot"); };
    auto count=[&] { auto n=reader->deserialize_uint();if(n>1000000)fail();return n; };
    auto number=[&](double fallback=0) { double n=in.real(fallback);if(!std::isfinite(n))fail();return n; };
    auto point=[&] { Point p=in.point();if(!std::isfinite(p.x)||!std::isfinite(p.y))fail();return p; };
    auto string=[&] { return in.text(); };
    size_t remainingPoints=2000000;
    auto points=[&] { auto n=count();if(n>remainingPoints)fail();remainingPoints-=n;std::vector<Point> result;result.reserve(n);while(n--)result.push_back(point());return result; };
    auto body=[&](uint32 id)->PhysicsBody& { if(!id||id>owners.size()||!owners[id-1].body().isPresent())fail();return owners[id-1].body(); };
    const auto revision=reader->deserialize_1u();
    if((revision!=3 && revision!=4 && revision!=5) || count()!=owners.size())fail();
    if(revision>=4) for(const auto& owner:owners) {
        const auto reference=in.optionalInteger();
        auto& source=owner.body();
        if(reference) {
            if(!source.isPresent() || !source.mBreakAngularSpeed)fail();
            const bool notified=source.mBreakNotified;
            source.setBreakAngularSpeed(source.mBreakAngularSpeed,&body(reference));
            source.mBreakNotified=notified;
        }
    }
    for(const auto& owner:owners) owner.body().disconnect();
    // Layer loading calls this on its staged graph, before publishing any owner.
    for(const auto& owner:owners) {
        bool present=in.flag();
        if(owner.part)owner.part->removeCollider();else owner.sprite->removeCollider();
        if(!present)continue;
        const bool enabled=in.flag(),sensor=in.flag(),contacts=in.flag();
        const auto category=in.optionalInteger(1),mask=in.optionalInteger(UINT32_MAX),group=in.optionalInteger();
        const auto friction=number(-1),restitution=number(-1);
        if((friction<0&&friction!=-1)||(restitution<0&&restitution!=-1)||restitution>1)fail();
        const auto compound=in.optionalInteger();if(compound)body(compound);
        const auto source=reader->deserialize_1u();
        std::string boxName;SpatialTransform sourceLocal;
        if(revision>=5 && owner.part && source==colliderSource_Animation) {
            boxName=string();if(boxName.empty())fail();
            sourceLocal.a=number();sourceLocal.b=number();sourceLocal.c=number();sourceLocal.d=number();
            sourceLocal.tx=number();sourceLocal.ty=number();sourceLocal.inverse();
        }
        int mode=frameCollider_AlphaMask,threshold=128;
        if(in.flag()){mode=reader->deserialize_1u();threshold=reader->deserialize_1u();}
        if(source>colliderSource_Animation || mode>frameCollider_AlphaMask || !threshold || (revision<5&&owner.part&&source!=colliderSource_Explicit))fail();
        const auto next=reader->deserialize_uint();
        std::map<std::string,CollisionShapeId> sourceIds;std::set<CollisionShapeId> reserved,active;
        auto validId=[&](CollisionShapeId id) { if(!id||(next&&id>=next))fail(); };
        for(auto n=count();n;--n) { auto name=string();auto id=reader->deserialize_uint();validId(id);if(name.empty()||!reserved.insert(id).second||!sourceIds.emplace(name,id).second)fail(); }
        if(source==colliderSource_Explicit&&!sourceIds.empty())fail();
        std::vector<Collider::Shape> shapes;
        for(auto n=count();n;--n) {
            Collider::Shape shape;shape.id=reader->deserialize_uint();validId(shape.id);if(!active.insert(shape.id).second)fail();
            shape.type=reader->deserialize_1u();shape.source=in.flag();shape.name=string();
            if(shape.source) { auto it=sourceIds.find(shape.name);if(it==sourceIds.end()||it->second!=shape.id)fail(); }
            else if(reserved.count(shape.id))fail();
            if(shape.type==collisionShape_Circle){shape.center=point();shape.radius=number();}
            else if(shape.type==collisionShape_Capsule) {
				if(remainingPoints<2)fail();
				remainingPoints-=2;
                shape.vertices={point(),point()};shape.radius=number();
            }
            else if(shape.type==collisionShape_Convex)shape.vertices=points();
            else if(shape.type==collisionShape_ImageMask || shape.type==collisionShape_Polygon)
                for(auto pieces=count();pieces;--pieces)shape.pieces.push_back(points());
            else fail();
            // Reuse the geometry validators; persisted decomposition is only
            // accepted for masks, whose individual pieces must be convex.
            Collider checked;
            if(shape.type==collisionShape_Circle) {
				if(!shape.vertices.empty()||!shape.pieces.empty())fail();
				checked.addCircle(shape.radius,shape.center);
            } else if(shape.type==collisionShape_Capsule) {
                checked.addCapsule(shape.vertices[0],shape.vertices[1],shape.radius);
            } else if(shape.type==collisionShape_Convex) {
                checked.addPolygon(shape.vertices);
                shape.pieces=checked.mShapes.back().pieces;
                if(shape.type==collisionShape_Convex && !shape.pieces.empty())fail();
            } else if(shape.type==collisionShape_ImageMask || shape.type==collisionShape_Polygon) {
                if(!shape.vertices.empty() || (shape.type==collisionShape_Polygon && shape.pieces.empty()))fail();
                for(const auto& piece:shape.pieces){checked.setPolygon(piece);if(!checked.mShapes.back().pieces.empty())fail();}
            } else fail();
            shapes.push_back(std::move(shape));
        }
        auto& c=owner.setupCollider();
        if(source==colliderSource_Frame) {
            if(owner.part)owner.part->setupFrameCollider(mode,threshold);else owner.sprite->setupFrameCollider(mode,threshold);
        } else if(source==colliderSource_Animation) {
            if(owner.part){owner.part->setupAnimationCollider(boxName);c.mSourceLocal=sourceLocal;}
            else owner.sprite->setupAnimationCollider();
        }
        c.mShapes=std::move(shapes);c.mSourceIds=std::move(sourceIds);c.mNextShape=next;
        c.mEnabled=enabled;c.mSensor=sensor;c.mWantsContactEvents=contacts;
        c.mFrameMode=mode;c.mAlphaThreshold=threshold;
        c.mCategory=category;c.mMask=mask;c.mGroup=group;c.mFriction=friction;c.mRestitution=restitution;
        if(compound)c.setPhysicsBody(body(compound));
    }
    std::vector<PhysicsConstraint*> joints;
    for(auto n=count();n;--n) {
        const auto type=reader->deserialize_1u();
        auto& a=body(reader->deserialize_uint());auto& b=body(reader->deserialize_uint());
        Point pa,pb,groove; double x=0,y=0,z=0;
        if(type<constraint_Pin||type>constraint_Motor)fail();
        if(type<=constraint_Spring){pa=point();pb=point();}
        if(type==constraint_Groove)groove=point();
        if(type!=constraint_Pivot && type!=constraint_Groove)x=number();
        if(type==constraint_Slide || (type>=constraint_Spring && type<=constraint_Gear))y=number();
        if(type==constraint_Spring || type==constraint_RotarySpring || type==constraint_Ratchet)z=number();
        const auto maxForce=in.real(std::numeric_limits<double>::infinity()),breakForce=number(),impulse=number(),force=number();
        bool flags=in.flag();
        if(&a==&b||type<constraint_Pin||type>constraint_Motor||std::isnan(maxForce)||maxForce<0||breakForce<0||impulse<0||force<0)fail();
        if((type==constraint_Pin&&x<0)||(type==constraint_Slide&&(x<0||y<x))||
           (type==constraint_Groove&&std::hypot(pa.x-groove.x,pa.y-groove.y)<=1e-8)||
           (type==constraint_Spring&&(x<0||y<0||z<0))||
           (type==constraint_RotarySpring&&(y<0||z<0))||
           (type==constraint_RotaryLimit&&x>y)||((type==constraint_Ratchet||type==constraint_Gear)&&x==0))fail();
        auto& c=a.createConstraint(b,type,pa,pb,groove,x,y,z);
        c.mMaxForce=maxForce;c.mBreakForce=breakForce;c.mCollideBodies=flags;c.mImpulse=impulse;c.mForce=force;
        joints.push_back(&c);
    }
    std::set<Part*> linked,driven;
    auto part=[&](uint32 id)->Part* { if(!id||id>owners.size()||!owners[id-1].part)fail();return owners[id-1].part; };
    for(auto n=count();n;--n) {
        auto* p=part(reader->deserialize_uint());auto id=reader->deserialize_uint();
        if(!id||id>joints.size()||!linked.insert(p).second||p->hasIKLimits())fail();
        p->setIKLimits(*joints[id-1]);
    }
    for(auto n=count();n;--n) {
        auto* p=part(reader->deserialize_uint());if(!driven.insert(p).second||p->hasIKTarget())fail();
        auto ik=std::make_unique<Part::IKTarget>();ik->owner=p;ik->physical=true;
        ik->middle=reader->deserialize_uint();ik->tip=reader->deserialize_uint();ik->target=point();
        ik->space=reader->deserialize_1u();ik->bend=in.flag()?1:-1;
        ik->influence=number(1);ik->reached=in.flag();
        auto error=string();
        ik->rootOffset=point();ik->middleOffset=point();ik->tipOffset=point();ik->tipAngle=number();if(!std::isfinite(ik->tipAngle))fail();
        ik->maxForce=number();ik->maxTorque=number();ik->frequency=number();ik->dampingRatio=number();
        if(ik->maxForce<0||ik->maxTorque<0||ik->frequency<=0||ik->dampingRatio<0||
           !std::isfinite(std::pow(6.28318530717958647692*ik->frequency,2))||
           !std::isfinite(2*ik->dampingRatio*(6.28318530717958647692*ik->frequency)))fail();
        auto* middle=p->mSprite->getPart(ik->middle),*tip=p->mSprite->getPart(ik->tip);
        Part* chain[3]={p,middle,tip};
        for(int i=0;i<3;++i) {
            const auto id=reader->deserialize_uint();
            if(!chain[i]||(!id&&(i!=2||chain[i]->physics!=PhysicsBody::NoPhysics)))fail();
            if(!id)continue;
            auto& b=body(id);if(&b!=&static_cast<PhysicsBody&>(chain[i]->physics)||b.mDriveController)fail();
            b.addRef();ik->bodies[i]=&b;
        }
        p->validateIKOverlap(middle,tip,true);
        // Claim before validation so the sampled owned drives are not mistaken
        // for independent drives. The temporary releases claims on any failure.
        ik->ownsDrives=true;for(auto* b:ik->bodies)if(b)b->mDriveController=p;
        p->calculateIK(middle,tip,ik->target,ik->space,ik->bend,ik->influence,ik.get());
        if(p->mParent)p->mParent->validateIKJoint(*p,ik->rootOffset);
        p->validateIKJoint(*middle,ik->middleOffset);middle->validateIKJoint(*tip,ik->tipOffset);
        p->mIKTarget=std::move(ik);p->mIKError=std::move(error);
    }

}
