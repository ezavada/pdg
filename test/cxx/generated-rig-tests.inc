void generatedRigGeometry() {
    using namespace pdg;
    std::vector<AnimationBone> bones{
        {"trunk",animation_NoBone,{},0}, {"left",0,{-3,0},0}, {"right",0,{5,0},0},
        {"helper",1,{},0}, {"tip",3,{},0}, {"root",animation_NoBone,{},0}};
    AnimationBinding art{"leaf",4,animationBinding_Image,{2,1,.5},true,6,2,.25,.5};
    auto rig=AnimationRig::create(bones,{},1,{art});AnimationPose pose(rig);
    expect(selectAnimationPhysicsRoot(*rig)==5,"exact root name wins over descendant count");
    expect(selectAnimationPhysicsRoot(*rig,1)==1,"explicit root wins");
    bones[5].name="island";
    rig=AnimationRig::create(bones,{},1,{art});pose=AnimationPose(rig);
    expect(selectAnimationPhysicsRoot(*rig)==0,"all descendants count for automatic root");
    auto tied=AnimationRig::create({{"childA",2,{},0},{"childB",3,{},0},
        {"treeA",animation_NoBone,{},0},{"treeB",animation_NoBone,{},0}});
    expect(selectAnimationPhysicsRoot(*tied)==2,"equal descendant counts select the lowest stable bone ID");
    std::vector<std::string> warnings;
    auto def=generateAnimationPhysicsDefinition(pose,{},80,5,1000,warnings);
    expect(def.bodies.size()==3,"zero connection bones skip while artwork and designated root survive");
    expect(def.bodies[0].bone==0 && def.bodies[1].bone==4 && def.bodies[2].bone==5,"stable bone order");
    near(def.bodies[0].length,8,"branch uses farthest child connection points");
    near(def.bodies[0].offsetX,1,"branch center follows chosen pair");
    near(def.bodies[0].radius,.8,"capsule radius is ten percent of length");
    near(def.bodies[1].length,6*std::cos(.5)+2*std::sin(.5),"leaf union respects image transform");
    near(def.bodies[2].length,1,"one millimeter converted to application units");
    expect(def.rootBody==2 && def.joints.size()==1,"disconnected root remains its own component");
    expect(def.joints[0].parent==0 && def.joints[0].child==1,"joint skips zero-length ancestors");
    expect(std::isinf(def.joints[0].maxForce),"unlimited pivot strength by default");
    double total=0;for(const auto& body:def.bodies)total+=body.mass;
    near(total,80,"only included segments receive mass");
    expect(!warnings.empty(),"inference and skipped bones produce diagnostics");
    bones[0].name="root";bones[5].name="other";
    auto positive=AnimationRig::create(bones,{},1,{art});
    def=generateAnimationPhysicsDefinition(AnimationPose(positive),{},80,animation_NoBone,100000,warnings);
    near(def.bodies[0].length,8,"positive root length is not clamped by fallback");
    AnimationTransform reflected{0,0,0,-2,2};
    def=generateAnimationPhysicsDefinition(pose,reflected,80,5,1000,warnings);
    near(def.bodies.back().length,1,"fallback stays one millimeter in physical body units after owner scaling");
    bool rejected=false;
    try { generateAnimationPhysicsDefinition(pose,{0,0,0,2,1},80,5,1000,warnings); }
    catch(const std::invalid_argument&) { rejected=true; }
    expect(rejected,"unsupported nonuniform physical scale is explicit");
    auto stretched=AnimationRig::create({{"base",animation_NoBone,{0,0,0,2,1},0},{"tip",0,{3,4},0}}, {}, 1,
        {{"tipArt",1,animationBinding_Image,{},true,2,1,0,.5}});
    def=generateAnimationPhysicsDefinition(AnimationPose(stretched),{},10,animation_NoBone,1,warnings);
    near(def.bodies[0].length,std::hypot(6,4),"nonuniform authored bone scales measure physical connection distance");
    near(def.bodies[0].radius,def.bodies[0].length*.1,"physical capsule thickness is independent of bone display scale");
    near(def.joints[0].parentX,def.bodies[0].length/2,"pivot uses rigid body coordinates after nonuniform bone scaling");
    near(def.joints[0].parentY,0,"pivot aligns with capsule axis after nonuniform bone scaling");
    auto single=AnimationRig::create({{"root",animation_NoBone,{},0}});
    def=generateAnimationPhysicsDefinition(AnimationPose(single),{},12,animation_NoBone,1,warnings);
    near(def.bodies[0].length,.001,"default meter units give one millimeter root");
    near(def.bodies[0].mass,12,"fallback root alone receives entire mass");
    PhysicsBody body(2,6);body.setVelocity(3,4).setAngularVelocity(5);body.setMass(4);
    near(body.getMomentOfInertia(),12,"ordinary mass edits also scale inertia");
    near(body.getVelocity().x,3,"mass edits preserve linear velocity");
    near(body.getAngularVelocity(),5,"mass edits preserve angular velocity");
    rejected=false;try{body.setMass(std::numeric_limits<double>::max());}catch(const std::invalid_argument&){rejected=true;}
    expect(rejected && body.getMass()==4 && body.getMomentOfInertia()==12,"inertia overflow rejects before mass mutation");
    PhysicsBody large(1e200,1e200);
    large.setMass(1e200);expect(large.getMomentOfInertia()==1e200,"unchanged mass avoids intermediate inertia overflow");
    large.setMass(1e-200);expect(std::abs(large.getMomentOfInertia()/1e-200-1)<1e-12,"representable inertia scaling avoids intermediate ratio underflow");
}
