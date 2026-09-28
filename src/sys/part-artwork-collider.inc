// Sprite/Part artwork adapters share Collider's source IDs and explicit additions.
Collider& Part::setupFrameCollider(int mode, int threshold) {
    if(mode!=frameCollider_Bounds && mode!=frameCollider_AlphaMask)
        throw std::invalid_argument("Unknown frame collider mode");
    if(threshold<1 || threshold>255)throw std::invalid_argument("Alpha threshold must be from 1 to 255");
    auto provider=[this,mode,threshold,cachedImage=std::shared_ptr<Image>(),cachedPixels=Rect(),mask=Collider::Shape()]
        (std::vector<Collider::Shape>& shapes) mutable {
        Image* image=nullptr;Rect pixels;Quad destination;
        if(mDrawing) {
            if(mDrawing->empty())return true;
            if(mode==frameCollider_Bounds)destination=Quad(mDrawing->getBounds());
            else if(!mDrawing->getImageFrame(image,pixels,destination))
                throw std::logic_error("AlphaMask Part colliders require single-image artwork; use Bounds for Drawings");
        } else {
#ifdef PDG_SPRITER_SUPPORT
            if(!hasCurrentRig() || mBinding==animation_NoBinding)return true;
            const auto& binding=mRig->getBinding(mBinding);
            if(binding.kind!=animationBinding_Image)throw std::logic_error("Frame collider requires an image binding");
#ifndef PDG_NO_GUI
            mSprite->refreshSpriterPose();
            auto* object=mSprite->mEntityInstance->objectIfExistsOnCurrentFrame(binding.name);
            auto* file=object?dynamic_cast<PDGImageFile*>(object->getImage()):nullptr;
            if(!file || !(image=file->getPDGImage()))return true;
            pixels=image->getImageBounds();const auto pivot=object->getPivot();
            destination=Quad(Rect(-pivot.x*pixels.width(),-pivot.y*pixels.height(),
                (1-pivot.x)*pixels.width(),(1-pivot.y)*pixels.height()));
#else
            throw std::logic_error("Authored image frame colliders require a GUI build");
#endif
#else
            return true;
#endif
        }
        const auto& a=destination.points[0];const auto& b=destination.points[1];const auto& d=destination.points[3];
        for(const auto& p:destination.points)if(!std::isfinite(p.x)||!std::isfinite(p.y))
            throw std::invalid_argument("Part artwork bounds must be finite");
        const double determinant=(b.x-a.x)*(d.y-a.y)-(b.y-a.y)*(d.x-a.x);
        if(std::abs(determinant)<1e-12)return true;
        Collider::Shape shape{0,collisionShape_Convex,Point(),0,{}, {},"frame",true};
        if(mode==frameCollider_AlphaMask) {
            if(!image)throw std::logic_error("Part alpha source has no image");
            if(cachedImage.get()!=image || pixels!=cachedPixels) {
                auto next=Collider::imageMaskShape(*image,pixels,Rect(0,0,1,1),threshold);
                image->addRef();cachedImage=std::shared_ptr<Image>(image,[](Image* p){p->release();});
                cachedPixels=pixels;mask=std::move(next);
            }
            shape=mask;shape.name="frame";shape.source=true;
            for(auto& piece:shape.pieces)for(auto& p:piece)
                p=Point(a.x+(b.x-a.x)*p.x+(d.x-a.x)*p.y,a.y+(b.y-a.y)*p.x+(d.y-a.y)*p.y);
        } else shape.vertices.assign(std::begin(destination.points),std::end(destination.points));
        shapes.push_back(std::move(shape));return true;
    };
    const bool created=collider==Collider::NoCollider;
    auto& result=setupCollider();
    try { result.useGeometrySource(colliderSource_Frame,std::move(provider));
        result.mFrameMode=mode;result.mAlphaThreshold=threshold;result.mAnimationBox.clear(); }
    catch(...) {if(created)removeCollider();throw;}
    return result;
}

Collider& Part::setupAnimationCollider(const std::string& name) {
#ifndef PDG_SPRITER_SUPPORT
    throw std::logic_error("Animation collider sources require Spriter support");
#else
    const auto rig=mSprite?mSprite->getAnimationRig():nullptr;
    const auto id=rig?rig->findBinding(name):animation_NoBinding;
    if(id==animation_NoBinding || rig->getBinding(id).kind!=animationBinding_Box)
        throw std::invalid_argument("Expected a named collision box in the owner's enabled animation pose");
    const auto local=getTransform(partSpace_Local).inverse();
    auto* owner=mSprite;
    auto provider=[this,rig,owner,name,local](std::vector<Collider::Shape>& shapes) {
        if(mSprite!=owner || !mSprite || mSprite->getAnimationRig()!=rig)return true;
        const auto box=mSprite->getSpriterCollisionBox(name.c_str());
        if(box.width()<=0 || box.height()<=0)return true;
        // The source is relative to the current authored parent, with setup's
        // local offset removed. Subsequent Part motion therefore carries it.
        const auto frame=physicsFrame();
        if(std::abs(frame.a*frame.d-frame.b*frame.c)<1e-12)return true;
        const auto offset=collider.getGeometrySource()==colliderSource_Animation ? collider->mSourceLocal : local;
        const auto inverse=SpatialTransform::compose(offset,frame.inverse());
        Collider::Shape shape{0,collisionShape_Convex,Point(),0,{}, {},name,true};
        for(const auto& p:box.getQuad().points)shape.vertices.push_back(inverse.transformPoint(p));
        shapes.push_back(std::move(shape));return true;
    };
    const bool created=collider==Collider::NoCollider;
    auto& result=setupCollider();
    const auto old=result.mSourceLocal;result.mSourceLocal=local;
    try {result.useGeometrySource(colliderSource_Animation,std::move(provider));result.mAnimationBox=name;result.mAnimationSourceRig=rig;}
    catch(...) {result.mSourceLocal=old;if(created)removeCollider();throw;}
    return result;
#endif
}
