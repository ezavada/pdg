#include "pdg/sys/animationphysics.h"
#include "physics-scaling.h"
#include "snapshot-codec.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>
namespace pdg {
#include "animationphysics-generation.inc"
AnimationPhysicsDefinition decodeAnimationPhysicsDefinition(const std::vector<double> &values) {
    size_t cursor = 0;
    auto number = [&]() {
        if (cursor >= values.size() || !std::isfinite(values[cursor]))
            throw std::invalid_argument("Invalid physical rig configuration");
        return values[cursor++];
    };
    auto integer = [&](double max) {
        double v = number();
        if (v < 0 || v > max || v != std::floor(v))
            throw std::invalid_argument("Invalid physical rig integer");
        return uint32_t(v);
    };
    AnimationPhysicsDefinition def;
    def.version = integer(4294967295.0);
    def.rootMode = integer(1);
    def.rootBody = integer(4294967295.0);
    def.selfCollisions = integer(1);
    const auto count = integer(65536);
    def.bodies.reserve(count);
    for (uint32_t i = 0; i < count; ++i) {
        AnimationPhysicsBody b;
        b.bone = integer(4294967294.0);
        b.mode = integer(1);
        b.mass = number();
        b.length = number();
        b.radius = number();
        b.offsetX = number();
        b.offsetY = number();
        b.offsetRotation = number();
        b.friction = number();
        b.elasticity = number();
        b.categories = integer(4294967295.0);
        b.mask = integer(4294967295.0);
        def.bodies.push_back(b);
    }
    const auto joints = integer(65536);
    def.joints.reserve(joints);
    for (uint32_t i = 0; i < joints; ++i) {
        AnimationPhysicsJoint j;
        j.parent = integer(4294967295.0);
        j.child = integer(4294967295.0);
        j.parentX = number();
        j.parentY = number();
        j.childX = number();
        j.childY = number();
        j.minAngle = number();
        j.maxAngle = number();
        j.maxForce = number();
        j.collide = integer(1);
        def.joints.push_back(j);
    }
    if (cursor != values.size())
        throw std::invalid_argument("Unexpected physical rig configuration values");
    return def;
}
} // namespace pdg

#ifdef PDG_USE_CHIPMUNK_PHYSICS
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <stdexcept>
namespace pdg {
namespace {
std::map<cpBody *, AnimationPhysicsRig *> &registry() {
    static std::map<cpBody *, AnimationPhysicsRig *> entries;
    return entries;
}
void require(bool ok, const char *message) {
    if (!ok)
        throw std::invalid_argument(message);
}
bool finite(double v) {
    return std::isfinite(v);
}
AnimationTransform localFromWorld(const AnimationTransform &parent,
                                  const AnimationTransform &world) {
    const double x = world.x - parent.x, y = world.y - parent.y, c = std::cos(parent.rotation),
                 s = std::sin(parent.rotation);
    require(parent.scaleX != 0 && parent.scaleY != 0, "Physical pose parent has singular scale");
    auto out = world;
    out.x = (c * x + s * y) / parent.scaleX;
    out.y = (-s * x + c * y) / parent.scaleY;
    out.rotation =
        (world.rotation - parent.rotation) * (parent.scaleX * parent.scaleY < 0 ? -1 : 1);
    out.scaleX = world.scaleX / parent.scaleX;
    out.scaleY = world.scaleY / parent.scaleY;
    // Preserve sampled local alpha separately: zero alpha is legal.
    return out;
}
} // namespace
struct AnimationPhysicsRig::Storage {
    cpSpace *space;
    bool ownsSpace;
    std::vector<cpBody *> bodies;
    std::vector<cpShape *> shapes;
    std::vector<cpConstraint *> joints;
    std::vector<std::pair<double,double>> scales;
    explicit Storage(cpSpace *value) : space(value ? value : cpSpaceNew()), ownsSpace(!value) {}
    ~Storage() {
        for (auto *c : joints) {
            if (cpSpaceContainsConstraint(space, c))
                cpSpaceRemoveConstraint(space, c);
            cpConstraintFree(c);
        }
        for (auto *s : shapes) {
            if (cpSpaceContainsShape(space, s))
                cpSpaceRemoveShape(space, s);
            cpShapeFree(s);
        }
        for (auto *b : bodies) {
            registry().erase(b);
            if (cpSpaceContainsBody(space, b))
                cpSpaceRemoveBody(space, b);
            cpBodyFree(b);
        }
        if(ownsSpace)cpSpaceFree(space);
    }
};
#include "animationphysics-control.inc"
#include "animationphysics-snapshot.inc"
void AnimationPhysicsRig::validatePose(const AnimationPose &pose,
                                       const AnimationTransform &root) const {
    require(pose.getRig() == mRig, "Physical rig pose belongs to a different rig");
    require(root.isValid(), "Invalid physical rig root");
    if (mDefinition.generated) validateGeneratedRoot(root);
    for (const auto &def : mDefinition.bodies) {
        const auto world = pose.getWorldTransform(def.bone, root);
        if (mDefinition.generated) physicalScale(world);
        else require(std::abs(std::abs(world.scaleX) - 1) < 1e-8 && std::abs(std::abs(world.scaleY) - 1) < 1e-8,
                     "Explicit physical rigs require unit effective bone scale magnitudes");
    }
}
AnimationPhysicsRig::AnimationPhysicsRig(cpSpace* space,const AnimationPhysicsDefinition& definition,
    const AnimationPose& pose,const AnimationTransform& root,double vx,double vy,double angular)
    : AnimationPhysicsRig(space,definition,pose,root,vx,vy,angular,false) {
    require(space!=nullptr,"Standalone physical rigs require a physics world");
}
AnimationPhysicsRig::AnimationPhysicsRig(cpSpace *space,
                                         const AnimationPhysicsDefinition &definition,
                                         const AnimationPose &pose, const AnimationTransform &root,
                                         double vx, double vy, double angular, bool sharedComponents)
    : mDefinition(definition), mRig(pose.getRig()) {
    auto storage = std::make_unique<Storage>(space);
    space=storage->space;
    require(!cpSpaceIsLocked(space),
            "Create physical rigs outside locked physics callbacks");
    require(definition.version == 1, "Unsupported physical rig definition version");
    require(!definition.bodies.empty(), "Physical rig needs at least one body");
    require(definition.rootMode == animationRoot_Fixed ||
                definition.rootMode == animationRoot_Follow,
            "Invalid physical root mode");
    require(definition.rootBody < definition.bodies.size(), "Invalid physical root body");
    require(finite(vx) && finite(vy) && finite(angular),
            "Physical initial velocities must be finite");
    std::set<AnimationBoneId> used;
    for (const auto &b : definition.bodies) {
        require(b.bone < mRig->getBoneCount() && used.insert(b.bone).second,
                "Duplicate or invalid physical bone");
        require(b.mode == animationBody_Dynamic || b.mode == animationBody_Kinematic,
                "Invalid physical body mode");
        require(finite(b.mass) && b.mass > 0 && finite(b.length) && b.length >= 0 &&
                    finite(b.radius) && b.radius > 0,
                "Invalid physical mass or shape dimensions");
        require(finite(b.offsetX) && finite(b.offsetY) && finite(b.offsetRotation),
                "Invalid physical body offset");
        require(finite(b.friction) && b.friction >= 0 && finite(b.elasticity) &&
                    b.elasticity >= 0 && b.elasticity <= 1,
                "Invalid physical material");
    }
    // Sprite-owned bodies have the coordinator that separates gameplay targets
    // from the followed physical frame, including mixed kinematic/dynamic rigs.
    // The standalone passive adapter has no such controller.
    if (definition.rootMode == animationRoot_Follow && !sharedComponents) {
        const auto &b = definition.bodies[definition.rootBody];
        require(b.mode == animationBody_Dynamic,
                "Following root requires a dynamic top-level bone");
        require(std::none_of(definition.bodies.begin(), definition.bodies.end(),
                             [](const auto &v) { return v.mode == animationBody_Kinematic; }),
                "Passive following rigs cannot contain animated anchors");
    }
    for (const auto &j : definition.joints) {
        require(j.parent < definition.bodies.size() && j.child < definition.bodies.size() &&
                    j.parent != j.child,
                "Invalid physical joint bodies");
        require(definition.bodies[j.parent].mode == animationBody_Dynamic ||
                    definition.bodies[j.child].mode == animationBody_Dynamic,
                "Joint needs a dynamic body");
        require(finite(j.parentX) && finite(j.parentY) && finite(j.childX) && finite(j.childY) &&
                    finite(j.minAngle) && finite(j.maxAngle) && j.minAngle <= j.maxAngle &&
                    (finite(j.maxForce) || (definition.generated && j.maxForce == INFINITY)) && j.maxForce > 0,
                "Invalid physical joint anchors, limits or force");
    }
    validatePose(pose, root);
    if (!sharedComponents) for(const auto& def:definition.bodies) {
        const auto world=pose.getWorldTransform(def.bone,root);
        require(world.scaleX>0 && world.scaleY>0,"Standalone physical rigs require unreflected frames");
    }
    // Map parents before children even if the supplied definition is unordered.
    for (const auto &b : definition.bodies)
        mOrder.push_back(b.bone);
    auto depth = [&](AnimationBoneId b) {
        size_t d = 0;
        for (; b != animation_NoBone; b = mRig->getBone(b).parent)
            ++d;
        return d;
    };
    std::stable_sort(mOrder.begin(), mOrder.end(),
                     [&](auto a, auto b) { return depth(a) < depth(b); });
    for (const auto &def : definition.bodies) {
        const auto bone=pose.getWorldTransform(def.bone,root);
        storage->scales.emplace_back(bone.scaleX,bone.scaleY);
        const auto t = generatedBodyFrame(bone,def);
        const cpVect a = cpv(-def.length / 2, 0), b = cpv(def.length / 2, 0);
        const auto moment = cpMomentForSegment(def.mass, a, b, def.radius);
        require(finite(moment) && moment > 0, "Physical body moment is invalid");
        auto *body = def.mode == animationBody_Kinematic ? cpBodyNewKinematic()
                                                         : cpBodyNew(def.mass, moment);
        storage->bodies.push_back(body);
        cpBodySetPosition(body, cpv(t.x, t.y));
        cpBodySetAngle(body, t.rotation);
        cpBodySetVelocity(body, cpv(vx - angular * (t.y - root.y), vy + angular * (t.x - root.x)));
        cpBodySetAngularVelocity(body, angular);
        cpSpaceAddBody(space, body);
        if (sharedComponents || definition.generated) continue; // Sprite installs the shared graph.
        auto *shape = cpSegmentShapeNew(body, a, b, def.radius);
        storage->shapes.push_back(shape);
        cpShapeSetFriction(shape, def.friction);
        cpShapeSetElasticity(shape, def.elasticity);
        cpShapeSetFilter(shape, cpShapeFilterNew(definition.selfCollisions
                                                     ? CP_NO_GROUP
                                                     : reinterpret_cast<cpGroup>(this),
                                                 def.categories, def.mask));
        // Same engine dispatch as Sprite shapes, resolved via registry rather than user data casts.
        cpShapeSetCollisionType(shape, 1111); // CP_COLLIDE_TYPE_SPRITE
        cpSpaceAddShape(space, shape);
    }
    for (const auto &def : definition.joints) {
        if (sharedComponents || definition.generated) break;
        auto *a = storage->bodies[def.parent];
        auto *b = storage->bodies[def.child];
        for (auto *joint :
             {cpPivotJointNew2(a, b, cpv(def.parentX, def.parentY), cpv(def.childX, def.childY)),
              cpRotaryLimitJointNew(a, b, def.minAngle, def.maxAngle)}) {
            storage->joints.push_back(joint);
            cpConstraintSetMaxForce(joint, def.maxForce);
            cpConstraintSetCollideBodies(joint, def.collide);
            cpSpaceAddConstraint(space, joint);
        }
    }
    mStorage = std::move(storage);
    for (auto *b : mStorage->bodies)
        registry()[b] = this;
}
AnimationPhysicsRig::~AnimationPhysicsRig() {
    if(mControl)for(auto& entry:mControl->bodies)entry.body->detachSolver();
    releaseControls();
    if (!mStorage)
        return;
    for (auto *body : mStorage->bodies)
        registry().erase(body);
    if (cpSpaceIsLocked(mStorage->space)) {
        auto *storage = mStorage.release();
        cpSpaceAddPostStepCallback(
            storage->space,
            [](cpSpace *, void *key, void *) { delete static_cast<Storage *>(key); }, storage,
            nullptr);
    }
}
void AnimationPhysicsRig::prepare(const AnimationPose &pose, const AnimationTransform &root,
                                  double seconds) {
    require(finite(seconds) && seconds >= 0,
            "Physical animation step must be nonnegative finite seconds");
    validatePose(pose, root);
    prepareControls(pose, root, seconds);
}
namespace {
// Borrow a constrained body. The Sprite detaches these adapters before releasing
// the rig's shape/joint/body storage; retained PhysicsBodies then use basic motion.
class RigBodySolver final : public PhysicsBody::Solver {
    cpBody* mBody;
    std::function<void()> mMoved;
public:
    void* nativeBody() const override { return mBody; }
    RigBodySolver(cpBody* body, std::function<void()> moved) : mBody(body), mMoved(std::move(moved)) {}
    PhysicsBodyState readState() const override {
        const auto p = cpBodyGetPosition(mBody), v = cpBodyGetVelocity(mBody);
        return {p.x, p.y, cpBodyGetAngle(mBody), v.x, v.y, cpBodyGetAngularVelocity(mBody)};
    }
    void writeState(const PhysicsBodyState& state) override {
        const auto before = readState();
        const bool moved = before.x != state.x || before.y != state.y || before.rotation != state.rotation;
        if (before.x != state.x || before.y != state.y) cpBodySetPosition(mBody, cpv(state.x, state.y));
        if (before.rotation != state.rotation) cpBodySetAngle(mBody, state.rotation);
        if (before.velocityX != state.velocityX || before.velocityY != state.velocityY)
            cpBodySetVelocity(mBody, cpv(state.velocityX, state.velocityY));
        if (before.angularVelocity != state.angularVelocity) cpBodySetAngularVelocity(mBody, state.angularVelocity);
        if (moved) {
            auto* space = cpBodyGetSpace(mBody);
            if (space && !cpSpaceIsLocked(space)) cpSpaceReindexShapesForBody(space, mBody);
            mMoved();
        }
    }
    void addForce(double x, double y, double torque) override {
        if (x != 0 || y != 0) cpBodySetForce(mBody, cpvadd(cpBodyGetForce(mBody), cpv(x, y)));
        if (torque != 0) cpBodySetTorque(mBody, cpBodyGetTorque(mBody)+torque);
    }
    void configure(const PhysicsBody& settings) override {
        auto* space = cpBodyGetSpace(mBody);
        if (space && cpSpaceIsLocked(space)) throw std::logic_error("Change rig body modes outside physics callbacks");
        const auto type = settings.getMode() == physicsBody_Kinematic ? CP_BODY_TYPE_KINEMATIC : CP_BODY_TYPE_DYNAMIC;
        if (cpBodyGetType(mBody) != type) cpBodySetType(mBody, type);
        if (cpBodyGetType(mBody) == CP_BODY_TYPE_DYNAMIC) {
            cpBodySetMass(mBody, settings.getMass());
            cpBodySetMoment(mBody, settings.getMomentOfInertia());
        }
        cpBodyEachShape(mBody, [](cpBody*, cpShape* shape, void* data) {
            const auto& settings = *static_cast<const PhysicsBody*>(data);
            cpShapeSetFriction(shape, settings.getFriction());
            cpShapeSetElasticity(shape, settings.getRestitution());
        }, const_cast<PhysicsBody*>(&settings));
    }
};
}
std::unique_ptr<PhysicsBody::Solver> AnimationPhysicsRig::createBodySolver(uint32_t index, std::function<void()> moved) {
    return std::make_unique<RigBodySolver>(body(index), std::move(moved));
}
PhysicsBodyState AnimationPhysicsRig::getBodyState(uint32_t i) const {
    auto *b = body(i);
    auto p = cpBodyGetPosition(b), v = cpBodyGetVelocity(b);
    return {p.x, p.y, cpBodyGetAngle(b), v.x, v.y, cpBodyGetAngularVelocity(b)};
}
cpBody *AnimationPhysicsRig::body(uint32_t i) const {
    if (i >= mStorage->bodies.size())
        throw std::out_of_range("Unknown physical body index");
    return mStorage->bodies[i];
}
AnimationPhysicsRig *AnimationPhysicsRig::find(cpBody *b) {
    auto it = registry().find(b);
    return it == registry().end() ? nullptr : it->second;
}
uint32_t AnimationPhysicsRig::bodyIndex(cpBody *b) const {
    auto it = std::find(mStorage->bodies.begin(), mStorage->bodies.end(), b);
    if (it == mStorage->bodies.end())
        throw std::invalid_argument("Body belongs to another physical rig");
    return it - mStorage->bodies.begin();
}
void AnimationPhysicsRig::setRootBody(uint32_t index) {
    body(index); // validate before changing selection
    if (mControl && !mControl->requests.empty()) throw std::logic_error("Finish or cancel recovery before changing the physical root");
    mDefinition.rootBody = index;
}
AnimationTransform AnimationPhysicsRig::followingRoot(const AnimationPose &desired,
                                                      const AnimationTransform &root) const {
    if (mDefinition.rootMode != animationRoot_Follow)
        return root;
    const auto &def = mDefinition.bodies[mDefinition.rootBody];
    auto state = getBodyState(mDefinition.rootBody);
    auto sampled = desired.getWorldTransform(def.bone, root);
    sampled.scaleX=mStorage->scales[mDefinition.rootBody].first;sampled.scaleY=mStorage->scales[mDefinition.rootBody].second;
    const double offsetAngle=std::atan2(sampled.scaleY*std::sin(def.offsetRotation),sampled.scaleX*std::cos(def.offsetRotation));
    const double boneAngle = state.rotation - offsetAngle, c = std::cos(boneAngle),
                 s = std::sin(boneAngle);
    const double x = state.x - c * def.offsetX*sampled.scaleX + s * def.offsetY*sampled.scaleY,
                 y = state.y - s * def.offsetX*sampled.scaleX - c * def.offsetY*sampled.scaleY;
    auto result = root;
    result.x += x - sampled.x;
    result.y += y - sampled.y;
    return result;
}
AnimationPose AnimationPhysicsRig::publish(const AnimationPose &desired,
                                           const AnimationTransform &root) const {
    validatePose(desired, root);
    auto pose = desired.copy();
    for (auto id : mOrder) {
        auto it = std::find_if(mDefinition.bodies.begin(), mDefinition.bodies.end(),
                               [&](const auto &b) { return b.bone == id; });
        const size_t index = it - mDefinition.bodies.begin();
        const auto state = getBodyState(index);
        auto world = pose.getWorldTransform(id, root);
        world.scaleX=mStorage->scales[index].first;world.scaleY=mStorage->scales[index].second;
        const double offsetAngle=std::atan2(world.scaleY*std::sin(it->offsetRotation),world.scaleX*std::cos(it->offsetRotation));
        world.rotation = state.rotation - offsetAngle;
        const double c = std::cos(world.rotation), s = std::sin(world.rotation);
        world.x = state.x - c * it->offsetX*world.scaleX + s * it->offsetY*world.scaleY;
        world.y = state.y - s * it->offsetX*world.scaleX - c * it->offsetY*world.scaleY;
        const auto parent = mRig->getBone(id).parent;
        const auto frame = parent == animation_NoBone ? root : pose.getWorldTransform(parent, root);
        auto local = localFromWorld(frame, world);
        local.alpha = desired.getLocalTransform(id).alpha;
        pose.setLocalTransform(id, local);
    }
    return pose;
}
} // namespace pdg
#endif
