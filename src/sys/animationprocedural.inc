// Included inside namespace pdg by animationcontroller.cpp. Pure pose math.
namespace {
void proceduralChain(const AnimationPose& pose, const std::vector<AnimationBoneId>& chain) {
    require(!chain.empty(), "Empty procedural chain");
    for(size_t i=0;i<chain.size();++i) {
        const auto& bone=pose.getRig()->getBone(chain[i]);
        require(i==0 || bone.parent==chain[i-1], "Procedural chain must contain contiguous parent/child joints");
        require(std::find(chain.begin(),chain.begin()+i,chain[i])==chain.begin()+i, "Duplicate procedural joint");
    }
}
AnimationJiggle jointJiggle(const AnimationJiggle& c,AnimationBoneId bone) {
    auto next=c;next.joints.clear();for(const auto& j:c.joints)if(j.bone==bone){
        if(j.length)next.length=*j.length;
        if(j.frequency)next.frequency=*j.frequency;
        if(j.dampingRatio)next.dampingRatio=*j.dampingRatio;
        if(j.inertia)next.inertia=*j.inertia;
        if(j.maxAngle)next.maxAngle=*j.maxAngle;
        if(j.maxAngularSpeed)next.maxAngularSpeed=*j.maxAngularSpeed;
        if(j.gravityX)next.gravityX=*j.gravityX;
        if(j.gravityY)next.gravityY=*j.gravityY;
    }
    return next;
}
double proceduralBound(double angle,double current,double lo,double hi) {
    require(std::isfinite(lo)&&std::isfinite(hi)&&lo<=hi&&hi-lo<=2*pi+1e-9,"Invalid procedural angle interval");
    const double first=std::ceil((lo-angle)/(2*pi)),last=std::floor((hi-angle)/(2*pi));
    if(first<=last)return angle+std::clamp(std::round((current-angle)/(2*pi)),first,last)*2*pi;
    return std::abs(std::remainder(angle-lo,2*pi))<=std::abs(std::remainder(angle-hi,2*pi))?lo:hi;
}
AnimationTransform proceduralParent(const AnimationPose& p,AnimationBoneId id,const AnimationTransform& root) {
    const auto parent=p.getRig()->getBone(id).parent;
    return parent==animation_NoBone?root:p.getWorldTransform(parent,root);
}
void proceduralLimits(size_t count,const std::vector<double>& lo,const std::vector<double>& hi) {
    require((lo.empty()&&hi.empty())||(lo.size()==count&&hi.size()==count),"Procedural limits must match rotating joints");
    for(size_t i=0;i<lo.size();++i)proceduralBound(0,0,lo[i],hi[i]);
}
}
AnimationFABRIKResult solveAnimationFABRIK(AnimationPose& output,const AnimationFABRIK& c,const AnimationTransform& root) {
    proceduralChain(output,c.chain);
    require(c.chain.size()>=3,"FABRIK requires two joints and an endpoint");
    require(std::isfinite(c.targetX)&&std::isfinite(c.targetY)&&std::isfinite(c.influence)&&c.influence>=0&&c.influence<=1&&
        std::isfinite(c.tolerance)&&c.tolerance>0&&c.maxIterations>=1&&c.maxIterations<=256&&
        (c.bendDirection==1||c.bendDirection==-1)&&c.space>=0&&c.space<=2,"Invalid FABRIK configuration");
    const size_t n=c.chain.size()-1;
    proceduralLimits(n,c.minimum,c.maximum);validatePose(output,root);
    const auto external=proceduralParent(output,c.chain.front(),root);nonsingular(external);
    AnimationTransform target;target.x=c.targetX;target.y=c.targetY;
    if(c.space!=animationSpace_World)target=AnimationTransform::compose(c.space==animationSpace_Rig?root:external,target);
    std::vector<AnimationTransform> local,positions(n+1);
    for(auto id:c.chain)local.push_back(output.getLocalTransform(id));
    const auto incoming=local;
    auto forward=[&](){auto parent=external;for(size_t i=0;i<=n;++i){positions[i]=AnimationTransform::compose(parent,local[i]);nonsingular(positions[i]);parent=positions[i];}};
    forward();const auto origin=positions[0];std::vector<double> lengths;
    double total=0,longest=0;
    for(size_t i=0;i<n;++i){double length=std::hypot(positions[i+1].x-positions[i].x,positions[i+1].y-positions[i].y);
        require(std::isfinite(length)&&length>1e-10,"FABRIK requires finite positive joint lengths");lengths.push_back(length);total+=length;longest=std::max(longest,length);}
    require(std::isfinite(total),"FABRIK length overflow");
    AnimationFABRIKResult result;
    for(size_t i=0;i<c.minimum.size();++i){double bounded=proceduralBound(local[i].rotation,local[i].rotation,c.minimum[i],c.maximum[i]);
        result.limited|=std::abs(bounded-local[i].rotation)>1e-9;local[i].rotation=bounded;}
    forward();auto best=local;
    auto error=[&](){return std::hypot(positions[n].x-target.x,positions[n].y-target.y);};
    double bestError=error(),distance=std::hypot(target.x-origin.x,target.y-origin.y);
    result.withinGeometricReach=distance<=total+c.tolerance&&distance>=std::max(0.0,2*longest-total)-c.tolerance;
    // Deterministic asymmetric seed releases straight chains from folded-target stalls.
    if(bestError>c.tolerance&&distance<total)for(size_t i=0;i<n;++i)local[i].rotation+=c.bendDirection*.015*(i%2?-1:1);
    auto place=[](AnimationTransform& a,const AnimationTransform& b,double length){
        double dx=a.x-b.x,dy=a.y-b.y,d=std::hypot(dx,dy);
        if(d<1e-12){dx=std::cos(a.rotation);dy=std::sin(a.rotation);d=1;}
        a.x=b.x+dx*length/d;a.y=b.y+dy*length/d;
    };
    // Keep chain-local arrays throughout each pass. Repeated hierarchy walks and
    // per-joint pose invalidation would otherwise make long chains quadratic.
    for(int pass=0;pass<c.maxIterations&&bestError>c.tolerance;++pass){
        forward();positions[n].x=target.x;positions[n].y=target.y;
        for(size_t i=n;i-->0;)place(positions[i],positions[i+1],lengths[i]);
        positions[0]=origin;auto parent=external;
        for(size_t i=0;i<n;++i){
            place(positions[i+1],positions[i],lengths[i]);
            auto a=AnimationTransform::compose(parent,local[i]),b=AnimationTransform::compose(a,local[i+1]);
            double desired=local[i].rotation+reflection(parent)*std::remainder(std::atan2(positions[i+1].y-a.y,positions[i+1].x-a.x)-std::atan2(b.y-a.y,b.x-a.x),2*pi);
            if(!c.minimum.empty()){double bounded=proceduralBound(desired,local[i].rotation,c.minimum[i],c.maximum[i]);result.limited|=std::abs(bounded-desired)>1e-9;desired=bounded;}
            local[i].rotation=desired;parent=AnimationTransform::compose(parent,local[i]);positions[i]=parent;
            positions[i+1]=AnimationTransform::compose(parent,local[i+1]);
        }
        result.iterations=pass+1;double e=error();require(std::isfinite(e),"FABRIK overflow");
        if(e<bestError){bestError=e;best=local;}
    }
    result.solveError=bestError;result.converged=bestError<=c.tolerance;
    if(c.influence>0){
        std::vector<AnimationTransform> transforms;for(AnimationBoneId id=0;id<output.getRig()->getBoneCount();++id)transforms.push_back(output.getLocalTransform(id));
        for(size_t i=0;i<n;++i){auto applied=incoming[i];applied.rotation+=std::remainder(best[i].rotation-applied.rotation,2*pi)*c.influence;
            if(!c.minimum.empty())applied.rotation=proceduralBound(applied.rotation,applied.rotation,c.minimum[i],c.maximum[i]);
            transforms[c.chain[i]]=applied;}
        auto candidate=output.copy();candidate.setLocalTransforms(transforms);validatePose(candidate,root);output=std::move(candidate);
    }
    auto endpoint=output.getWorldTransform(c.chain.back(),root);result.reachError=std::hypot(endpoint.x-target.x,endpoint.y-target.y);
    result.reached=result.reachError<=c.tolerance;return result;
}
void validateAnimationJiggle(const AnimationJiggle& c) {
    require(c.mode!=jiggleMode_IKTarget||c.chain.empty(),"Target jiggle cannot have a chain");
    std::vector<AnimationBoneId> seen;
    for(const auto& j:c.joints){require(c.mode==jiggleMode_Chain&&std::find(c.chain.begin(),c.chain.end(),j.bone)!=c.chain.end()&&std::find(seen.begin(),seen.end(),j.bone)==seen.end(),"Invalid or duplicate jiggle joint override");seen.push_back(j.bone);validateAnimationJiggle(jointJiggle(c,j.bone));}
    require(c.mode==jiggleMode_Chain||c.mode==jiggleMode_IKTarget,"Invalid jiggle mode");
    require(std::isfinite(c.frequency)&&c.frequency>0&&c.frequency<=60&&std::isfinite(c.dampingRatio)&&c.dampingRatio>=0&&c.dampingRatio<=4&&
        std::isfinite(c.influence)&&c.influence>=0&&c.influence<=1&&std::isfinite(c.inertia)&&c.inertia>=0&&c.inertia<=1&&
        std::isfinite(c.maxAngle)&&c.maxAngle>0&&c.maxAngle<=pi&&std::isfinite(c.length)&&c.length>=0&&
        std::isfinite(c.gravityX)&&std::isfinite(c.gravityY)&&std::isfinite(c.maxDistance)&&c.maxDistance>0&&std::isfinite(c.maxSpeed)&&c.maxSpeed>0&&
        std::isfinite(c.maxAngularSpeed)&&c.maxAngularSpeed>0&&std::isfinite(c.maxStepSeconds)&&c.maxStepSeconds>0&&c.maxStepSeconds<=1.0/30&&
        c.maxSubsteps>0&&c.maxSubsteps<=64&&std::isfinite(c.teleportDistance)&&c.teleportDistance>0&&std::isfinite(c.teleportAngle)&&c.teleportAngle>0&&c.teleportAngle<=pi,"Invalid jiggle settings");
}
namespace {
void proceduralSpring(double& x,double& v,double target,const AnimationJiggle& c,double dt,double acceleration=0) {
    const double w=2*pi*c.frequency;
    AnimationSpringTarget spring(1,w*w,2*w*c.dampingRatio);
    spring.setState({x,0,v,0});auto s=spring.update(target+acceleration/(w*w),0,dt);x=s.x;v=s.velocityX;
}
}
JiggleResult stepJiggleTarget(const AnimationJiggle& c,JiggleState& output,double x,double y,double seconds) {
    validateAnimationJiggle(c);require(std::isfinite(x)&&std::isfinite(y)&&std::isfinite(seconds)&&seconds>=0,"Invalid jiggle target/delta");
    auto state=output;JiggleResult r;r.influence=c.influence;r.desiredX=x;r.desiredY=y;
    bool reset=!state.initialized||(c.enabled&&seconds>0&&(seconds>c.maxStepSeconds*c.maxSubsteps||(c.resetOnTeleport&&std::hypot(x-state.x,y-state.y)>c.teleportDistance)));
    if(reset){state.x=x;state.y=y;state.velocityX=state.velocityY=0;state.initialized=true;r.reset=true;}
    if(c.enabled&&seconds>0&&!reset){r.substeps=std::max(1,int(std::ceil(seconds/c.maxStepSeconds)));double dt=seconds/r.substeps;
        for(int i=0;i<r.substeps;++i){proceduralSpring(state.x,state.velocityX,x,c,dt,c.gravityX);proceduralSpring(state.y,state.velocityY,y,c,dt,c.gravityY);
            double speed=std::hypot(state.velocityX,state.velocityY);if(speed>c.maxSpeed){state.velocityX*=c.maxSpeed/speed;state.velocityY*=c.maxSpeed/speed;r.limited=true;}
            double dx=state.x-x,dy=state.y-y,d=std::hypot(dx,dy);if(d>c.maxDistance){state.x=x+dx*c.maxDistance/d;state.y=y+dy*c.maxDistance/d;double dot=(state.velocityX*dx+state.velocityY*dy)/(d*d);if(dot>0){state.velocityX-=dot*dx;state.velocityY-=dot*dy;}r.limited=true;}
        }r.simulatedSeconds=seconds;}
    r.filteredX=state.x;r.filteredY=state.y;r.lagDistance=std::hypot(state.x-x,state.y-y);
    r.effectiveX=x+(c.enabled?c.influence:0)*(state.x-x);r.effectiveY=y+(c.enabled?c.influence:0)*(state.y-y);output=std::move(state);return r;
}
JiggleResult solveAnimationJiggle(AnimationPose& output,const AnimationJiggle& c,JiggleState& saved,double seconds,const AnimationTransform& root,
                                const std::vector<double>& minimum,const std::vector<double>& maximum) {
    validateAnimationJiggle(c);require(c.mode==jiggleMode_Chain,"Expected chain jiggle");proceduralChain(output,c.chain);proceduralLimits(c.chain.size(),minimum,maximum);
    require(std::isfinite(seconds)&&seconds>=0,"Invalid jiggle delta");auto pose=output.copy();auto state=saved;validatePose(pose,root);
    JiggleResult r;r.influence=c.influence;bool initialize=!state.initialized||state.joints.size()!=c.chain.size()||(c.enabled&&seconds>c.maxStepSeconds*c.maxSubsteps);
    if(initialize){state.joints.resize(c.chain.size());r.reset=true;}
    r.substeps=c.enabled&&seconds>0&&!initialize?std::max(1,int(std::ceil(seconds/c.maxStepSeconds))):0;
    for(size_t i=0;i<c.chain.size();++i){auto id=c.chain[i];auto tuning=jointJiggle(c,id);auto desired=output.getWorldTransform(id,root);auto parent=proceduralParent(pose,id,root);nonsingular(desired);nonsingular(parent);auto& j=state.joints[i];
        double length=tuning.length?tuning.length:output.getRig()->getBone(id).length;
        if(!length&&i+1<c.chain.size()){auto next=output.getLocalTransform(c.chain[i+1]);length=std::hypot(next.x,next.y);}
        require(std::isfinite(length)&&length>1e-10,"Jiggle joint requires a positive lever length");
        bool jump=c.enabled&&seconds>0&&c.resetOnTeleport&&(std::hypot(desired.x-j.pivotX,desired.y-j.pivotY)>c.teleportDistance||std::abs(std::remainder(desired.rotation-j.desired,2*pi))>c.teleportAngle);
        if(initialize||jump){j={desired.rotation,0,desired.rotation,desired.x,desired.y,0,0};r.reset=true;}
        double wanted=j.angle+std::remainder(desired.rotation-j.angle,2*pi);
        if(r.substeps&&!jump){double vx=(desired.x-j.pivotX)/seconds,vy=(desired.y-j.pivotY)/seconds;
            double ax=(vx-j.pivotVelocityX)/seconds,ay=(vy-j.pivotVelocityY)/seconds;
            for(int k=0;k<r.substeps;++k){double acceleration=(std::cos(j.angle)*(tuning.gravityY-tuning.inertia*ay)-std::sin(j.angle)*(tuning.gravityX-tuning.inertia*ax))/length;
                proceduralSpring(j.angle,j.velocity,wanted,tuning,seconds/r.substeps,acceleration);j.velocity=std::clamp(j.velocity,-tuning.maxAngularSpeed,tuning.maxAngularSpeed);}
            j.pivotVelocityX=vx;j.pivotVelocityY=vy;j.pivotX=desired.x;j.pivotY=desired.y;j.desired=desired.rotation;}
        auto local=output.getLocalTransform(id);double worldBase=AnimationTransform::compose(parent,local).rotation;
        double delta=std::remainder(j.angle-worldBase,2*pi),bounded=std::clamp(delta,-tuning.maxAngle,tuning.maxAngle);if(delta!=bounded){if(c.enabled&&seconds>0){j.angle=worldBase+bounded;j.velocity=0;}r.limited=true;}
        double applied=local.rotation+reflection(parent)*bounded*(c.enabled?c.influence:0);
        if(!minimum.empty()){double limited=proceduralBound(applied,local.rotation,minimum[i],maximum[i]);if(std::abs(limited-applied)>1e-9){if(c.enabled&&seconds>0)j.velocity=0;r.limited=true;}applied=limited;}
        if(c.enabled&&c.influence>0){local.rotation=applied;pose.setLocalTransform(id,local);}
    }
    state.initialized=true;if(r.substeps)r.simulatedSeconds=seconds;validatePose(pose,root);output=std::move(pose);saved=std::move(state);return r;
}
