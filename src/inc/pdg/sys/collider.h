#ifndef PDG_COLLIDER_H_INCLUDED
#define PDG_COLLIDER_H_INCLUDED

#include "pdg/sys/physicsbody.h"
#include "pdg/sys/physicsconstraint.h"
#include "pdg/sys/spatialtransform.h"
#include "pdg/sys/polygon.h"
#include <functional>
#include <limits>
#include <map>
#include <memory>

namespace pdg {
class Image;
class AnimationRig;
class Collider;
class CollisionWorld;
using CollisionShapeId = uint32_t;
constexpr CollisionShapeId collisionShape_None = 0;
enum CollisionShapeType : int { collisionShape_Circle = 1, collisionShape_Convex = 2, collisionShape_Polygon = 3, collisionShape_ImageMask = 4, collisionShape_Capsule = 5 };
enum ColliderSource : int { colliderSource_Explicit = 0, colliderSource_Frame = 1, colliderSource_Animation = 2 };
enum FrameColliderMode : int { frameCollider_Bounds = 0, frameCollider_AlphaMask = 1 };
enum CollisionPhase : int { collision_Begin = 0, collision_Stay = 1, collision_End = 2 };

/** One contact, oriented from collider to other. Coordinates use the owning world.
 * Shape IDs remain stable until removed. Sensors, sleeping contacts and End
 * contacts have zero impulse. Chipmunk contacts reuse its solved manifold; point
 * is the mean contact midpoint and penetration is its greatest overlap depth.
 * Collider pointers are borrowed for the duration of contact dispatch.
 * @ingroup Physics Events
 */
struct ColliderContact {
    Collider *collider = nullptr;
    Collider *other = nullptr;
    CollisionShapeId shape = collisionShape_None, otherShape = collisionShape_None;
    int phase = collision_Begin;
    Point point;
    Vector normal, impulse;
    double penetration = 0;
    bool sensor = false;
};

/** Optional collision geometry, independent of artwork, animation and body ownership.
 * Sprite, Part and Particle factories own their colliders; retain a returned native reference
 * with addRef/release to keep it after removal. Local shapes follow the owner's
 * affine transform. Bodyless colliders are externally positioned surfaces; sensors
 * only report overlap. Circles and capsules are exact under uniform scale;
 * nonuniform scale/shear approximates curved boundaries with 32 segments per
 * full turn. Solid response requires a dynamic PhysicsBody.
 * @ingroup Physics
 */
class Collider : public RefCountedObj {
    friend class CollisionWorld;
    /// @cond INTERNAL
    friend class PhysicsGraphSnapshot;
    friend class Sprite;
    friend class Particle;
    friend class Part;
    /// @endcond

  public:
    Collider();
    ~Collider() override;
    Collider(const Collider &) = delete;
    Collider &operator=(const Collider &) = delete;
    static Collider NoCollider;
    void addRef() const noexcept override {
        if (mPresent)
            RefCountedObj::addRef();
    }
    void release() const noexcept override {
        if (mPresent)
            RefCountedObj::release();
    }
    bool operator==(const Collider &other) const { return this == &other; }
    bool operator!=(const Collider &other) const { return this != &other; }
    bool isPresent() const { return mPresent; }
    bool isAttached() const { return bool(mTransform); }
    uint64_t getId() const { return mId; }
    Collider &setEnabled(bool enabled);
    bool isEnabled() const { return mPresent && mEnabled; }
    Collider &setSensor(bool sensor);
    bool isSensor() const { return mSensor; }
    /// Override contact material; defaults come from the body, or neutral 1 without a body.
    Collider &setFriction(double friction);
    Collider &setRestitution(double restitution);
    double getFriction() const;
    double getRestitution() const;
    Collider &useBodyMaterial();
    Collider &setCategory(uint32_t category);
    uint32_t getCategory() const { return mCategory; }
    Collider &setCollisionMask(uint32_t mask);
    uint32_t getCollisionMask() const { return mMask; }
    Collider &setGroup(uint32_t group);
    uint32_t getGroup() const { return mGroup; }
    /// Replace all geometry with one circle in the owner's local coordinates.
    Collider &setCircle(double radius, const Point &center = Point());
    /// Replace all geometry with one local rectangle.
    Collider &setBox(const Rect &bounds);
    CollisionShapeId addCircle(double radius, const Point &center = Point());
    /// Endpoints are local cap centers; equal endpoints describe a circle.
    Collider &setCapsule(const Point &start, const Point &end, double radius);
    CollisionShapeId addCapsule(const Point &start, const Point &end, double radius);
    CollisionShapeId addBox(const Rect &bounds);
    /// Simple polygons in either winding; concave regions are decomposed into convex pieces.
    /// Geometry is copied. Self-intersections and degenerate outlines are rejected.
    CollisionShapeId addPolygon(const std::vector<Point> &vertices);
    CollisionShapeId addPolygon(const Polygon &polygon);
    CollisionShapeId addPolygon(std::initializer_list<Point> vertices) { return addPolygon(std::vector<Point>(vertices)); }
    Collider &setPolygon(const std::vector<Point> &vertices);
    Collider &setPolygon(const Polygon &polygon);
    Collider &setPolygon(std::initializer_list<Point> vertices) { return setPolygon(std::vector<Point>(vertices)); }
    Collider &setImageMask(Image &image, const Rect &localBounds, int alphaThreshold = 128);
    CollisionShapeId addImageMask(Image &image, const Rect &localBounds, int alphaThreshold = 128);
    int getGeometrySource() const { return mGeometrySource; }
    bool isSourceShape(CollisionShapeId shape) const;
    std::string getShapeName(CollisionShapeId shape) const;
    int getShapeType(CollisionShapeId shape) const;
    double getCircleRadius(CollisionShapeId shape) const;
    Point getCapsuleStart(CollisionShapeId shape) const;
    Point getCapsuleEnd(CollisionShapeId shape) const;
    double getCapsuleRadius(CollisionShapeId shape) const;
    bool removeShape(CollisionShapeId shape);
    Collider &clearShapes();
    uint32_t getShapeCount() const { refreshGeometry(); return uint32_t(mShapes.size()); }
    CollisionShapeId getShapeId(uint32_t index) const;
    Rect getBounds() const;
    bool contains(const Point &worldPoint) const;
    /// Geometric query; ignores category/mask/group and enabled/sensor flags.
    bool overlaps(const Collider &other) const;
    /// Select an explicit compound body; the collider retains it until reset/detach.
    Collider &setPhysicsBody(PhysicsBody &body);
    /// Follow the current physics association of the owner (the default).
    Collider &useOwnerPhysics();
    PhysicsBody &getPhysicsBody() const;
    /// Optional native listener. Callbacks run after solving and may remove owners.
    Collider &setContactHandler(std::function<void(const ColliderContact &)> handler);
    /// Predicate invoked before response. Exceptions reject the pair and populate getContactError().
    Collider &setCollisionFilter(std::function<bool(const Collider &, const Collider &)> filter);
    const std::string &getContactError() const { return mContactError; }
    /// Opt in to owner event delivery. Native contact listeners are independent.
    Collider &setWantsContactEvents(bool wanted);
    bool getWantsContactEvents() const { return mWantsContactEvents; }
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    SCRIPT_OBJECT_REF mColliderScriptObj;
#endif
    /// @cond INTERNAL
    void attach(std::function<SpatialTransform()> transform, std::function<PhysicsBody &()> body,
                std::function<const void *()> world = {});
    void detach();
    SpatialTransform transform() const;
    struct Shape {
        CollisionShapeId id;
        int type;
        Point center;
        double radius = 0;
        std::vector<Point> vertices; // Capsule: exactly two cap centers; convex: outline.
        // Multiple convex solver pieces still represent one public shape ID.
        std::vector<std::vector<Point>> pieces;
        std::string name;
        bool source = false;
    };
    const std::vector<Shape> &shapes() const { refreshGeometry(); return mShapes; }
    using GeometryProvider = std::function<bool(std::vector<Shape> &)>;
    void useGeometrySource(int source, GeometryProvider provider);
    void refreshGeometry() const;
    static Shape imageMaskShape(Image &image, const Rect &pixels, const Rect &localBounds, int alphaThreshold);
    bool passesCollisionFilter(const Collider &other) const;
    void syncNative(void *space, const void *world = nullptr);
    const void *world() const { return mOwnerWorld ? mOwnerWorld() : mWorld; }
    void setWorldFilter(std::function<bool(const void *)> filter) {
        if (mPresent)
            mWorldFilter = std::move(filter);
    }
    bool canCollideWith(const Collider &other) const;
    void dispatch(const ColliderContact &contact);
    void setEventSink(std::function<void(const ColliderContact &)> sink) {
        if (mPresent)
            mEventSink = std::move(sink);
    }
    /// @endcond
  private:
    explicit Collider(bool absent);
    bool ignores(const char *operation) const;
    const void *mWorld = nullptr;
    std::function<bool(const void *)> mWorldFilter;
    bool mPresent = true, mEnabled = true, mSensor = false;
    uint64_t mId = 0;
    uint32_t mCategory = 1, mMask = UINT32_MAX, mGroup = 0;
    mutable CollisionShapeId mNextShape = 1;
    mutable std::vector<Shape> mShapes;
    mutable std::map<std::string, CollisionShapeId> mSourceIds;
    GeometryProvider mGeometryProvider;
    int mGeometrySource = colliderSource_Explicit;
    int mFrameMode = frameCollider_AlphaMask, mAlphaThreshold = 128;
    std::string mAnimationBox;
    std::weak_ptr<const AnimationRig> mAnimationSourceRig;
    SpatialTransform mSourceLocal;
    void stopGeometrySource();
    const Shape &findShape(CollisionShapeId id) const;
    std::function<bool(const Collider &, const Collider &)> mCollisionFilter;
    std::function<SpatialTransform()> mTransform;
    std::function<PhysicsBody &()> mOwnerBody;
    std::function<const void *()> mOwnerWorld;
    std::function<void(const ColliderContact &)> mHandler, mEventSink;
    bool mWantsContactEvents = false;
    double mFriction = -1, mRestitution = -1;
    mutable std::string mContactError;
    SpatialTransform mDetachedTransform;
    PhysicsBody *mCompoundBody = nullptr;
    struct Native;
    std::unique_ptr<Native> mNative;
};

/** Read-only association. Only its owner may create/remove the collider.
 * An absent association occupies one pointer and shares Collider::NoCollider.
 * @ingroup Physics
 */
template <class Owner> class ColliderRef {
    friend Owner;
    Collider *mCollider = &Collider::NoCollider;
    ColliderRef() = default;

  public:
    ColliderRef(const ColliderRef &) = delete;
    ColliderRef &operator=(const ColliderRef &) = delete;
    ColliderRef &operator=(Collider &) = delete;
    operator Collider &() const { return *mCollider; }
    Collider *operator->() const { return mCollider; }
    bool operator==(const Collider &value) const { return mCollider == &value; }
    bool operator!=(const Collider &value) const { return mCollider != &value; }
    friend bool operator==(const Collider &a, const ColliderRef &b) { return b == a; }
    friend bool operator!=(const Collider &a, const ColliderRef &b) { return b != a; }
    /// \copydoc Collider::isPresent
    bool isPresent() const { return mCollider->isPresent(); }
    /// \copydoc Collider::isAttached
    bool isAttached() const { return mCollider->isAttached(); }
    /// \copydoc Collider::getId
    uint64_t getId() const { return mCollider->getId(); }
    /// \copydoc Collider::setEnabled
    Collider &setEnabled(bool enabled) { return mCollider->setEnabled(enabled); }
    /// \copydoc Collider::isEnabled
    bool isEnabled() const { return mCollider->isEnabled(); }
    /// \copydoc Collider::setSensor
    Collider &setSensor(bool sensor) { return mCollider->setSensor(sensor); }
    /// \copydoc Collider::isSensor
    bool isSensor() const { return mCollider->isSensor(); }
    Collider &setFriction(double value) { return mCollider->setFriction(value); }
    Collider &setRestitution(double value) { return mCollider->setRestitution(value); }
    double getFriction() const { return mCollider->getFriction(); }
    double getRestitution() const { return mCollider->getRestitution(); }
    Collider &useBodyMaterial() { return mCollider->useBodyMaterial(); }
    /// \copydoc Collider::setCategory
    Collider &setCategory(uint32_t category) { return mCollider->setCategory(category); }
    /// \copydoc Collider::getCategory
    uint32_t getCategory() const { return mCollider->getCategory(); }
    /// \copydoc Collider::setCollisionMask
    Collider &setCollisionMask(uint32_t mask) { return mCollider->setCollisionMask(mask); }
    /// \copydoc Collider::getCollisionMask
    uint32_t getCollisionMask() const { return mCollider->getCollisionMask(); }
    /// \copydoc Collider::setGroup
    Collider &setGroup(uint32_t group) { return mCollider->setGroup(group); }
    /// \copydoc Collider::getGroup
    uint32_t getGroup() const { return mCollider->getGroup(); }
    /// \copydoc Collider::setCircle
    Collider &setCircle(double radius, const Point &center = Point()) {
        return mCollider->setCircle(radius, center);
    }
    /// \copydoc Collider::setBox
    Collider &setBox(const Rect &bounds) { return mCollider->setBox(bounds); }
    /// \copydoc Collider::addCircle
    CollisionShapeId addCircle(double radius, const Point &center = Point()) {
        return mCollider->addCircle(radius, center);
    }
    /// \copydoc Collider::setCapsule
    Collider &setCapsule(const Point &start, const Point &end, double radius) {
        return mCollider->setCapsule(start, end, radius);
    }
    /// \copydoc Collider::addCapsule
    CollisionShapeId addCapsule(const Point &start, const Point &end, double radius) {
        return mCollider->addCapsule(start, end, radius);
    }
    /// \copydoc Collider::addBox
    CollisionShapeId addBox(const Rect &bounds) { return mCollider->addBox(bounds); }
    /// \copydoc Collider::addPolygon
    CollisionShapeId addPolygon(const std::vector<Point> &vertices) {
        return mCollider->addPolygon(vertices);
    }
    CollisionShapeId addPolygon(const Polygon &polygon) { return mCollider->addPolygon(polygon); }
    Collider &setPolygon(const std::vector<Point> &vertices) { return mCollider->setPolygon(vertices); }
    Collider &setPolygon(const Polygon &polygon) { return mCollider->setPolygon(polygon); }
    CollisionShapeId addPolygon(std::initializer_list<Point> vertices) { return mCollider->addPolygon(vertices); }
    Collider &setPolygon(std::initializer_list<Point> vertices) { return mCollider->setPolygon(vertices); }
    Collider &setImageMask(Image &image, const Rect &bounds, int threshold = 128) { return mCollider->setImageMask(image,bounds,threshold); }
    CollisionShapeId addImageMask(Image &image, const Rect &bounds, int threshold = 128) { return mCollider->addImageMask(image,bounds,threshold); }
    int getGeometrySource() const { return mCollider->getGeometrySource(); }
    bool isSourceShape(CollisionShapeId id) const { return mCollider->isSourceShape(id); }
    std::string getShapeName(CollisionShapeId id) const { return mCollider->getShapeName(id); }
    int getShapeType(CollisionShapeId id) const { return mCollider->getShapeType(id); }
    double getCircleRadius(CollisionShapeId id) const { return mCollider->getCircleRadius(id); }
    /// \copydoc Collider::getCapsuleStart
    Point getCapsuleStart(CollisionShapeId shape) const { return mCollider->getCapsuleStart(shape); }
    /// \copydoc Collider::getCapsuleEnd
    Point getCapsuleEnd(CollisionShapeId shape) const { return mCollider->getCapsuleEnd(shape); }
    /// \copydoc Collider::getCapsuleRadius
    double getCapsuleRadius(CollisionShapeId shape) const { return mCollider->getCapsuleRadius(shape); }
    Collider &setCollisionFilter(std::function<bool(const Collider &,const Collider &)> filter) { return mCollider->setCollisionFilter(std::move(filter)); }
    /// \copydoc Collider::removeShape
    bool removeShape(CollisionShapeId shape) { return mCollider->removeShape(shape); }
    /// \copydoc Collider::clearShapes
    Collider &clearShapes() { return mCollider->clearShapes(); }
    /// \copydoc Collider::getShapeCount
    uint32_t getShapeCount() const { return mCollider->getShapeCount(); }
    /// \copydoc Collider::getShapeId
    CollisionShapeId getShapeId(uint32_t index) const { return mCollider->getShapeId(index); }
    /// \copydoc Collider::getBounds
    Rect getBounds() const { return mCollider->getBounds(); }
    /// \copydoc Collider::contains
    bool contains(const Point &worldPoint) const { return mCollider->contains(worldPoint); }
    /// \copydoc Collider::overlaps
    bool overlaps(const Collider &other) const { return mCollider->overlaps(other); }
    /// \copydoc Collider::setPhysicsBody
    Collider &setPhysicsBody(PhysicsBody &body) { return mCollider->setPhysicsBody(body); }
    /// \copydoc Collider::useOwnerPhysics
    Collider &useOwnerPhysics() { return mCollider->useOwnerPhysics(); }
    /// \copydoc Collider::getPhysicsBody
    PhysicsBody &getPhysicsBody() const { return mCollider->getPhysicsBody(); }
    /// \copydoc Collider::setContactHandler
    Collider &setContactHandler(std::function<void(const ColliderContact &)> handler) {
        return mCollider->setContactHandler(std::move(handler));
    }
    Collider &setWantsContactEvents(bool wanted) {
        return mCollider->setWantsContactEvents(wanted);
    }
    bool getWantsContactEvents() const { return mCollider->getWantsContactEvents(); }
    /// \copydoc Collider::getContactError
    const std::string &getContactError() const { return mCollider->getContactError(); }
};

/** Solver-independent collision traversal. Worlds borrow registered owners, and
 * retain colliders while dispatching. No Sprite or rendering dependency.
 * @ingroup Physics
 */
class CollisionWorld {
  public:
    CollisionWorld();
    ~CollisionWorld();
    CollisionWorld(const CollisionWorld &) = delete;
    CollisionWorld &operator=(const CollisionWorld &) = delete;
    /// Detect/resolve a collected world frame, then deliver begin/stay/end contacts.
    void step(const std::vector<Collider *> &colliders, double seconds,
              std::function<bool(const Collider &, const Collider &)> pairFilter = {});

    /// @cond INTERNAL
    struct StepStatistics {
        size_t nativeContacts = 0;
        size_t fallbackShapeTests = 0;
    };
    const StepStatistics &getStepStatistics() const { return mStatistics; }
    /// @endcond
  private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
    StepStatistics mStatistics;
};
} // namespace pdg
#endif
