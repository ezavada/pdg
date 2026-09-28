#include "pdg/sys/animationpose.h"
#include "pdg/sys/animationtargets.h"
#include "pdg/sys/animationcontroller.h"
#include <optional>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
constexpr double pi = 3.14159265358979323846;
int assertions = 0;
void expect(bool value, const char* message) {
    ++assertions;
    if (!value) { std::cerr << "Animation pose failed: " << message << '\n'; std::exit(EXIT_FAILURE); }
}
void near(double actual, double expected, const char* message) {
    expect(std::isfinite(actual) && std::abs(actual - expected) < 1e-9, message);
}
template<class Function> void rejects(Function function, const char* message) {
    try { function(); }
    catch (const std::exception&) { expect(true, message); return; }
    expect(false, message);
}
pdg::AnimationTransform translated(double x, double y = 0) {
    pdg::AnimationTransform transform; transform.x = x; transform.y = y; return transform;
}
}

void pipelineAndIK() {
    using namespace pdg;
    auto rig = AnimationRig::create({{"upper",animation_NoBone,{},5}, {"lower",0,translated(5),3}, {"tip",1,translated(3),0}});
    AnimationPose base(rig);
    AnimationPipeline pipeline;
    std::optional<AnimationPoseView> retained;
    std::optional<AnimationPose> owned;
    std::vector<int> order;
    double state = 0;
    pipeline.addModifier([&](auto view, const auto& context) {
        order.push_back(2); state += context.deltaSeconds;
        view.rotateLocal(0,state); retained = view; owned = view.copy();
    },animationStage_PreConstraint,2);
    pipeline.addModifier([&](auto, const auto&) { order.push_back(1); },animationStage_PreConstraint,1);
    pipeline.addModifier([&](auto, const auto&) { order.push_back(3); },animationStage_Constraint,-100);
    pipeline.addModifier([&](auto, const auto&) { order.push_back(4); },animationStage_PostConstraint,-100);
    auto final = pipeline.evaluate(base,{},0.25);
    expect(order == std::vector<int>({1,2,3,4}),"modifier stages and stable priority order");
    near(final.getLocalTransform(0).rotation,0.25,"seconds context preserves fractional integration");
    rejects([&] { retained->rotateLocal(0,1); },"retained pose view expires");
    near(owned->getLocalTransform(0).rotation,0.25,"owned callback snapshot survives");
    final = pipeline.evaluate(base,{},0.25);
    near(final.getLocalTransform(0).rotation,0.5,"fresh base prevents accumulated pose drift");
    near(pipeline.evaluate(base,{},0).getLocalTransform(0).rotation,0.5,"zero-seconds evaluation preserves integration state");
    const auto bad = pipeline.addModifier([](auto view,const auto&) {
        auto bone=view.getLocalTransform(0);bone.x=99;view.setLocalTransform(0,bone);throw std::runtime_error("expected modifier failure");
    },animationStage_PostConstraint);
    final = pipeline.evaluate(base,{},0);
    near(final.getLocalTransform(0).x,0,"failing modifier rolls back all pose writes");
    expect(!pipeline.isModifierEnabled(bad) && pipeline.getModifierError(bad)=="expected modifier failure","failing modifier disabled with diagnostic");
    rejects([&] { pipeline.setModifierEnabled(bad,true); },"failed callbacks require new registration");
    rejects([&] { pipeline.evaluate(base,{},-1); },"negative seconds rejected");
    rejects([&] { pipeline.addModifier([](auto,const auto&){},3); },"invalid modifier stage rejected");
    auto token=std::make_shared<int>(1);std::weak_ptr<int> weak=token;
    auto lifetime=pipeline.addModifier([token](auto,const auto&){});token.reset();
    expect(!weak.expired(),"registration retains callback captures");pipeline.removeModifier(lifetime);
    expect(weak.expired(),"removal releases callback captures");
    AnimationPipeline queued;int calls=0;bool first=true;AnimationModifierId later=0;
    queued.addModifier([&](auto,const auto&) {
        if(first) {first=false;queued.removeModifier(later);queued.addModifier([&](auto,const auto&){calls+=10;});}
    });
    later=queued.addModifier([&](auto,const auto&){++calls;});
    queued.evaluate(base,{},0);expect(calls==1,"registration changes wait until evaluation boundary");
    queued.evaluate(base,{},0);expect(calls==11,"deferred removal and addition take effect next evaluation");
    queued.clearModifiers();
    auto recursive=queued.addModifier([&](auto,const auto&){queued.evaluate(base,{},0);});
    queued.evaluate(base,{},0);expect(!queued.isModifierEnabled(recursive),"recursive evaluation rejected safely");
    auto changed=base.copy();changed.rotateLocal(0,1);
    queued.clearModifiers();queued.setSource(animationSource_Reference);
    near(queued.evaluate(changed,{},0).getLocalTransform(0).rotation,0,"reference source ignores clip transform");
    queued.setSource(animationSource_Procedural);queued.addModifier([](auto view,const auto&){view.rotateLocal(0,0.1);});
    near(queued.evaluate(changed,{},0).getLocalTransform(0).rotation,0.1,"procedural source starts from reference");

    AnimationTwoBoneIK config; config.root=0;config.middle=1;config.tip=2;config.targetX=4;config.targetY=3;
    for (int bend : {-1,1}) for (int xflip : {-1,1}) for(int yflip : {-1,1}) {
        auto pose=base.copy();AnimationTransform root;root.x=10;root.y=-5;root.rotation=0.3;root.scaleX=2*xflip;root.scaleY=2*yflip;
        config.bendDirection=bend;
        auto result=solveAnimationTwoBoneIK(pose,config,root);
        auto target=AnimationTransform::compose(root,translated(4,3));auto tip=pose.getWorldTransform(2,root);
        expect(result.reachable && !result.clamped && !result.limited,"reachable reflected/scaled IK solve");
        near(tip.x,target.x,"IK target x under root transform");near(tip.y,target.y,"IK target y under root transform");
    }
    auto pose=base.copy();config.targetX=100;config.targetY=0;
    auto result=solveAnimationTwoBoneIK(pose,config);
    expect(result.clamped && !result.reachable,"unreachable target clamps without stretch");near(result.reachError,92,"unreachable reach error");
    config.stretch=animationIK_Stretch;pose=base.copy();result=solveAnimationTwoBoneIK(pose,config);
    expect(result.stretched && result.reachable,"explicit stretch reaches distant target");
    config.stretch=animationIK_NoStretch;config.targetX=4;config.targetY=3;config.influence=0;pose=base.copy();
    solveAnimationTwoBoneIK(pose,config);near(pose.getLocalTransform(0).rotation,0,"zero influence preserves original root");near(pose.getLocalTransform(1).rotation,0,"zero influence preserves original elbow");
    config.influence=1;config.rootMin=0;config.rootMax=0;config.middleMin=0;config.middleMax=0;pose=base.copy();
    result=solveAnimationTwoBoneIK(pose,config);expect(result.limited && !result.reachable,"joint limits reported");
    config.rootMin=config.middleMin=-pi;config.rootMax=config.middleMax=pi;config.matchOrientation=true;config.targetRotation=0.7;pose=base.copy();
    solveAnimationTwoBoneIK(pose,config);near(pose.getGlobalTransform(2).rotation,0.7,"optional tip orientation");
    config.targetX=0;config.targetY=0;pose=base.copy();result=solveAnimationTwoBoneIK(pose,config);
    expect(result.clamped && std::isfinite(result.reachError),"coincident target folds unequal chain without NaN");
    auto equalRig=AnimationRig::create({{"a",animation_NoBone,{},3},{"b",0,translated(3),3},{"c",1,translated(3),0}});
    AnimationPose equal(equalRig);result=solveAnimationTwoBoneIK(equal,config);expect(result.reachable,"coincident equal-length chain reaches root");
    auto saved=pose.getLocalTransform(0);AnimationTransform singular;singular.scaleX=0;
    rejects([&]{solveAnimationTwoBoneIK(pose,config,singular);},"singular roots rejected atomically");near(pose.getLocalTransform(0).rotation,saved.rotation,"invalid IK preserves input");
    // Nonuniform scale is valid for PDG's component-transform composition.
    singular.scaleX=2;config.targetX=4;config.targetY=3;pose=base.copy();
    expect(solveAnimationTwoBoneIK(pose,config,singular).reachable,"nonuniform root reaches target");
    config.rootLength=0.1;rejects([&]{solveAnimationTwoBoneIK(pose,config);},"length mismatch rejected");
    config.rootLength=0;config.tip=0;rejects([&]{solveAnimationTwoBoneIK(pose,config);},"noncontiguous chain rejected");
}

void authoredOffsetIK() {
    using namespace pdg;
    // Non-axis-aligned offsets, nonuniform scales on ancestors AND joints, and
    // odd-axis reflections exercise the component-transform solver contract.
    for (int flipX : {-1, 1}) for (int flipY : {-1, 1}) for (int bend : {-1, 1}) {
        auto parent = translated(3, -2); parent.rotation = .35;
        parent.scaleX = 1.5 * flipX; parent.scaleY = .8 * flipY;
        auto upper = translated(1, 2); upper.rotation = -.4;
        upper.scaleX = -.6; upper.scaleY = 1.3;
        auto lower = translated(5, .7); lower.rotation = .6;
        lower.scaleX = .7; lower.scaleY = 1.2;
        auto tip = translated(3, -.5);
        auto rig = AnimationRig::create({{"parent", animation_NoBone, parent, 0},
            {"upper", 0, upper, 0}, {"lower", 1, lower, 0}, {"tip", 2, tip, 0}});
        AnimationTransform world; world.x = 10; world.y = -7; world.rotation = .2;
        world.scaleX = 2; world.scaleY = 3;
        AnimationTwoBoneIK config; config.root = 1; config.middle = 2; config.tip = 3;
        config.space = animationSpace_World; config.bendDirection = bend;
        config.matchOrientation = true; config.targetRotation = .8;
        for (double offset : {4.0, 5.0, 6.0}) {
            AnimationPose pose(rig); auto animated = lower; animated.x = offset;
            pose.setLocalTransform(2, animated);
            auto reachablePose = pose.copy(); reachablePose.rotateLocal(1, .4);
            reachablePose.rotateLocal(2, -.7);
            auto target = reachablePose.getWorldTransform(3, world);
            config.targetX = target.x; config.targetY = target.y;
            auto result = solveAnimationTwoBoneIK(pose, config, world);
            expect(result.reachable && !result.stretched && !result.clamped,
                   "nonuniform reflected chain with animated offsets reaches target");
            auto actual = pose.getWorldTransform(3, world);
            near(actual.x, target.x, "authored-offset IK x");
            near(actual.y, target.y, "authored-offset IK y");
            near(actual.rotation, .8, "nonuniform reflected tip orientation");
            near(pose.getLocalTransform(2).x, offset, "IK preserves animated child offset");
            near(pose.getLocalTransform(2).scaleX, lower.scaleX, "IK preserves authored nonuniform scale");
            near(pose.getLocalTransform(0).rotation, parent.rotation, "IK preserves ancestor");
        }
        AnimationPose invalid(rig); auto collapsed = lower; collapsed.x = collapsed.y = 0;
        invalid.setLocalTransform(2, collapsed);
        rejects([&] { solveAnimationTwoBoneIK(invalid, config, world); }, "inferred zero length rejected");
        near(invalid.getLocalTransform(1).rotation, upper.rotation, "invalid inferred solve is atomic");
    }
}

void targetAdapters(){
    for(double damping:{0.0,3.0,20.0,40.0}){
        pdg::AnimationSpringTarget whole(1,100,damping),split(1,100,damping);
        whole.applyImpulse(4,2);split.applyImpulse(4,2);
        auto expected=whole.update(10,-3,.25);for(int i=0;i<25;++i)split.update(10,-3,.01);auto actual=split.getState();
        near(actual.x,expected.x,"spring subdivision position");near(actual.velocityY,expected.velocityY,"spring subdivision velocity");
    }
    pdg::AnimationSpringTarget recoil(2,0,0);recoil.applyImpulse(4,-2);auto state=recoil.update(0,0,.25);
    near(state.x,.5,"recoil impulse divided by mass");near(state.y,-.25,"recoil fractional seconds");
    auto frozen=recoil.update(99,99,0);near(frozen.x,state.x,"paused spring preserves integration state");
    bool rejected=false;try{recoil.update(0,0,-1);}catch(const std::invalid_argument&){rejected=true;}expect(rejected,"spring rejects negative seconds");near(recoil.getState().x,state.x,"invalid spring step is atomic");
    pdg::AnimationSpringTarget damped(1,0,2);damped.applyImpulse(2,0);near(damped.update(0,0,10).x,1-std::exp(-20),"zero stiffness damped target");
    pdg::AnimationContactTarget lock;lock.lockWorld(4,5);auto contact=lock.update(.2,true,true);expect(contact.locked,"world contact retained");near(contact.x,4,"world contact position");
    pdg::AnimationTransform platform;platform.x=10;platform.y=20;platform.rotation=3.14159265358979323846/2;
    lock.lockPlatform(10,22,7,platform);platform.x=30;platform.rotation=0;
    contact=lock.update(.1,true,true,7,platform);near(contact.x,32,"moving platform translation and rotation");near(contact.y,20,"platform local lock persists");
    contact=lock.update(.125,true,true,8,platform,.5);expect(!contact.locked,"changed support releases contact");near(contact.influence,.75,"contact fades in seconds");
    contact=lock.update(1,true,true,7,platform,.5);near(contact.influence,0,"lost contact remains released");
    lock.lockWorld(1,2);contact=lock.update(0,true,false,0,{},.25);expect(!contact.locked,"unreachable contact releases");near(contact.influence,1,"zero-time release starts continuous fade");
}

int main() {
    targetAdapters();
    using namespace pdg;
    pipelineAndIK();
    authoredOffsetIK();
    // Deliberately out of parent order: stable IDs must not be reordered.
    std::vector<AnimationBone> bones{
        {"hand", 2, translated(5), 3},
        {"shoulder", animation_NoBone, translated(2, 3), 10},
        {"forearm", 1, translated(10), 5},
        {"unrelated", animation_NoBone, translated(-10), 0}
    };
    std::vector<AnimationSocket> sockets{
        {"grip", 0, translated(3)},
        {"root_socket", animation_NoBone, translated(-4)}
    };
    auto rig = AnimationRig::create(bones, sockets, 17);
    expect(rig->getRevision() == 17 && rig->getBoneCount() == 4, "immutable rig metadata");
    expect(rig->findBone("hand") == 0 && rig->findSocket("grip") == 0, "stable IDs");
    expect(rig->findBone("missing") == animation_NoBone && rig->findSocket("missing") == animation_NoSocket, "missing name sentinels");
    AnimationPose pose(rig), independent(rig);
    near(pose.getGlobalTransform(0).x, 17, "out-of-order parent propagation");
    near(pose.getSocketTransform(0).x, 20, "socket uses final bone pose");
    auto snapshot = pose.copy();
    pose.rotateLocal(1, pi / 2);
    near(pose.getGlobalTransform(0).x, 2, "ancestor rotation moves descendant x");
    near(pose.getGlobalTransform(0).y, 18, "ancestor rotation moves descendant y");
    near(pose.getSocketTransform(0).y, 21, "ancestor rotation moves socket");
    near(pose.getGlobalTransform(3).x, -10, "unrelated branch unchanged");
    near(independent.getGlobalTransform(0).x, 17, "shared rig instances isolated");
    near(snapshot.getGlobalTransform(0).x, 17, "owned snapshot isolated");
    auto returned = pose.getLocalTransform(1); returned.x = 999;
    near(pose.getLocalTransform(1).x, 2, "returned transform is an owned value");

    AnimationTransform world = translated(100, 50); world.scaleX = 2; world.scaleY = 1;
    // Spriter's non-affine composition is not associative: the world scale
    // must enter before traversing the rotated shoulder and its descendants.
    near(pose.getWorldTransform(0, world).x, 104, "world hierarchy x");
    near(pose.getWorldTransform(0, world).y, 83, "world nonuniform scale at each parent");
    near(pose.getWorldSocketTransform(0, world).y, 89, "world socket follows scaled hierarchy");
    near(pose.getWorldSocketTransform(1, world).x, 92, "root-relative socket");
    world.scaleX = -2;
    near(pose.getWorldTransform(0, world).x, 96, "mirrored hierarchy x");
    near(pose.getWorldTransform(0, world).y, 83, "mirrored hierarchy y");
    near(pose.getWorldTransform(0, world).rotation, -pi / 2, "reflection reverses local angle");

    pose.resetToReference();
    near(pose.getGlobalTransform(0).x, 17, "reference reset removes edits");
    auto alpha = pose.getLocalTransform(1); alpha.alpha = 0.5; pose.setLocalTransform(1, alpha);
    alpha = pose.getLocalTransform(2); alpha.alpha = 0.4; pose.setLocalTransform(2, alpha);
    near(pose.getGlobalTransform(0).alpha, 0.2, "inherited alpha");
    world.alpha = 0.5;
    near(pose.getWorldSocketTransform(0, world).alpha, 0.1, "world socket inherited alpha");

    auto invalid = pose.getLocalTransform(0); invalid.x = std::numeric_limits<double>::quiet_NaN();
    rejects([&] { pose.setLocalTransform(0, invalid); }, "nonfinite edit rejected");
    near(pose.getLocalTransform(0).x, 5, "rejected edit leaves pose unchanged");
    rejects([&] { pose.rotateLocal(0, std::numeric_limits<double>::infinity()); }, "nonfinite rotation rejected");
    std::vector<AnimationTransform> all(4);
    all[0].x = 42; all[3].alpha = -1;
    rejects([&] { pose.setLocalTransforms(all); }, "batch validation is atomic");
    near(pose.getLocalTransform(0).x, 5, "invalid batch did not write earlier bones");
    rejects([&] { pose.setLocalTransforms({}); }, "batch size validation");
    rejects([&] { pose.getGlobalTransform(animation_NoBone); }, "invalid bone ID");
    rejects([&] { pose.getSocketTransform(animation_NoSocket); }, "invalid socket ID");
    rejects([&] { AnimationPose missing(nullptr); }, "null rig validation");

    AnimationPose from(rig), to(rig);
    auto left = from.getLocalTransform(1); left.rotation = 170 * pi / 180; from.setLocalTransform(1, left);
    auto right = left; right.rotation = -170 * pi / 180; right.x = 12; to.setLocalTransform(1, right);
    auto blend = AnimationPose::blend(from, to, 0.5);
    near(blend.getLocalTransform(1).rotation, pi, "shortest-angle interpolation");
    near(blend.getLocalTransform(1).x, 7, "translation interpolation");
    near(AnimationPose::blend(from, to, 0).getLocalTransform(1).rotation, left.rotation, "zero influence exact");
    near(AnimationPose::blend(from, to, 1).getLocalTransform(1).rotation, right.rotation, "full influence exact");
    near(from.getLocalTransform(1).x, 2, "blend leaves source unchanged");
    rejects([&] { AnimationPose::blend(from, to, -0.1); }, "negative influence rejected");
    rejects([&] { AnimationPose::blend(from, to, std::numeric_limits<double>::quiet_NaN()); }, "NaN influence rejected");
    AnimationPose different(AnimationRig::create(bones, sockets, 18));
    rejects([&] { AnimationPose::blend(from, different, 0.5); }, "different revision rejected");
    AnimationPose unrelated(AnimationRig::create(bones, sockets, 17));
    rejects([&] { AnimationPose::blend(from, unrelated, 0.5); }, "same revision number does not imply same rig");

    rejects([&] { AnimationRig::create(bones, sockets, 0); }, "revision zero rejected");
    auto badBones = bones; badBones[1].parent = 0;
    rejects([&] { AnimationRig::create(badBones); }, "parent cycle rejected");
    badBones = bones; badBones[0].parent = 0;
    rejects([&] { AnimationRig::create(badBones); }, "self parent rejected");
    badBones = bones; badBones[0].parent = 200;
    rejects([&] { AnimationRig::create(badBones); }, "missing parent rejected");
    badBones = bones; badBones[0].name = "shoulder";
    rejects([&] { AnimationRig::create(badBones); }, "duplicate name rejected");
    badBones = bones; badBones[0].length = -1;
    rejects([&] { AnimationRig::create(badBones); }, "negative length rejected");
    auto badSockets = sockets; badSockets[0].bone = 200;
    rejects([&] { AnimationRig::create(bones, badSockets); }, "invalid socket parent rejected");
    badSockets = sockets; badSockets[0].name = badSockets[1].name;
    rejects([&] { AnimationRig::create(bones, badSockets); }, "duplicate socket rejected");
    AnimationPose empty(AnimationRig::create({}, {{"origin", animation_NoBone, {}}}));
    near(empty.getSocketTransform(0).x, 0, "empty rig supports root socket");
    world.scaleX = 0;
    expect(pose.getWorldTransform(0, world).isValid(), "singular forward transform remains defined");
    auto bindingRig = AnimationRig::create(bones, {{"grip", 0, translated(3), 0}}, 19,
        {{"grip", 0, animationBinding_Point, translated(3)},
         {"art", 2, animationBinding_Image, translated(1)}});
    AnimationPose bound(bindingRig);
    bound.setBindingLocalTransform(0, translated(4));
    near(bound.getSocketTransform(0).x, 21, "socket reads animated binding local pose");
    bound.rotateLocal(1, pi / 2);
    near(bound.getSocketTransform(0).y, 22, "animated socket follows edited hierarchy");
    near(bound.getBindingTransform(1).y, 14, "artwork binding follows edited hierarchy");
    auto boundCopy = bound.copy(); bound.setBindingLocalTransform(0, translated(9));
    near(boundCopy.getSocketTransform(0).y, 22, "binding snapshots are independent");
    rejects([&] { bound.setBindingLocalTransform(0, invalid); }, "nonfinite binding edit rejected");
    rejects([&] { AnimationRig::create(bones, {{"bad", 0, {}, 5}}, 1, {}); }, "invalid socket binding rejected");
    AnimationMetadata firstMetadata{{{"", "speed", 2.0}, {"hand", "count", 0}, {"", "mode", std::string("idle")}}, {{"hand", {"contact"}}}};
    AnimationMetadata secondMetadata{{{"", "speed", 6.0}, {"hand", "count", 7}, {"", "mode", std::string("reach")}}, {{"hand", {}}}};
    from.setMetadata(firstMetadata); to.setMetadata(secondMetadata);
    auto metadataBlend = AnimationPose::blend(from, to, 0.5);
    near(std::get<double>(metadataBlend.getMetadata().variables[0].value), 4, "numeric metadata interpolates");
    expect(std::get<int>(metadataBlend.getMetadata().variables[1].value) == 3, "integer metadata uses evaluator truncation");
    expect(std::get<std::string>(metadataBlend.getMetadata().variables[2].value) == "reach", "string metadata switches at halfway");
    expect(metadataBlend.getMetadata().tags[0].tags.empty(), "tag sets switch at halfway");
    expect(AnimationPose::blend(from, to, 0.25).getMetadata().tags[0].tags.size() == 1, "source tags before halfway");
    expect(from.getMetadata().tags[0].tags.size() == 1, "metadata blend does not change its inputs");
    auto invalidMetadata = firstMetadata;
    invalidMetadata.variables[0].value = std::numeric_limits<double>::quiet_NaN();
    rejects([&] { from.setMetadata(invalidMetadata); }, "nonfinite metadata rejected");
    near(std::get<double>(from.getMetadata().variables[0].value), 2, "metadata validation is atomic");
    from.resetToReference();
    expect(from.getMetadata().variables.empty(), "structural reference reset clears sampled metadata");
    std::cout << "Animation pose: " << assertions << " assertions passed\n";
}
