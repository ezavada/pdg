#ifndef PDG_COLLISION_QUERY_H_INCLUDED
#define PDG_COLLISION_QUERY_H_INCLUDED

#include "pdg/sys/collider.h"
#include <optional>

namespace pdg {
class SpriteLayer;

/** Scene query selection. Layer references and exclusions are borrowed during
 * the synchronous query. Masks select layers first, then collider categories.
 * The predicate runs once per eligible collider against a geometry snapshot;
 * it must not mutate the scene or recursively query it. Exceptions propagate.
 */
struct CollisionQueryOptions {
    uint32_t layerMask = UINT32_MAX, categoryMask = UINT32_MAX;
    bool includeSensors = true;
    uint32_t maxHits = 16;
    std::optional<std::vector<SpriteLayer*>> layers;
    std::vector<Collider*> excludedColliders;
    std::vector<PhysicsBody*> excludedBodies;
    std::function<bool(const Collider&)> predicate;
};

/** One public shape hit. Single-hit scene returns and their copies retain collider.
 * Buffer records borrow the buffer's reference until clear/reuse/destruction.
 * point and normal use scene world coordinates. Cast distance is travelled
 * distance; nearest distance is distance to filled geometry. Initial overlaps
 * have fraction/distance zero and a zero normal (no unique entry surface).
 * Their point is the closest filled-geometry point, possibly inside the target.
 * Overlaps expose identity only; their other fields remain zero.
 */
struct CollisionQueryHit {
    Collider* collider = nullptr;
    CollisionShapeId shapeId = collisionShape_None;
    Point point;
    Vector normal;
    double fraction = 0, distance = 0;
    bool initialOverlap = false;
private:
    friend class Scene;
    // Single-hit scene returns own a reference independently of any buffer.
    std::shared_ptr<Collider> mRetention;
    void retainCollider() {
        collider->addRef();
        mRetention = std::shared_ptr<Collider>(collider, [](Collider* c){ c->release(); });
    }
};

/// @cond INTERNAL
/** Reusable bounded results, sorted by distance, collider ID, then shape ID.
 * Overflow retains the nearest/earliest capacity hits. Geometry snapshot and
 * scratch storage may allocate; result storage is reserved at construction.
 */
class CollisionQueryBuffer : public RefCountedObj {
public:
    explicit CollisionQueryBuffer(uint32_t capacity = 16);
    ~CollisionQueryBuffer() override;
    CollisionQueryBuffer(const CollisionQueryBuffer&) = delete;
    CollisionQueryBuffer& operator=(const CollisionQueryBuffer&) = delete;
    uint32_t getCapacity() const { return mCapacity; }
    uint32_t getCount() const { return uint32_t(mHits.size()); }
    bool isOverflowed() const { return mOverflow; }
    void clear();
    const CollisionQueryHit& getHit(uint32_t index) const;
    Collider* getCollider(uint32_t index) const { return getHit(index).collider; }
    uint32_t getShapeId(uint32_t index) const { return getHit(index).shapeId; }
    double getPointX(uint32_t index) const { return getHit(index).point.x; }
    double getPointY(uint32_t index) const { return getHit(index).point.y; }
    double getNormalX(uint32_t index) const { return getHit(index).normal.x; }
    double getNormalY(uint32_t index) const { return getHit(index).normal.y; }
    Point getPoint(uint32_t index) const { return getHit(index).point; }
    Vector getNormal(uint32_t index) const { return getHit(index).normal; }
    double getFraction(uint32_t index) const { return getHit(index).fraction; }
    double getDistance(uint32_t index) const { return getHit(index).distance; }
    bool getInitialOverlap(uint32_t index) const { return getHit(index).initialOverlap; }
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    SCRIPT_OBJECT_REF mCollisionQueryBufferScriptObj;
#endif
    /// @cond INTERNAL
    void insert(const CollisionQueryHit& hit);
    CollisionQueryOptions scriptOptions;
    void configure(uint32_t layers, uint32_t categories, bool sensors);
    void selectLayers() { requireWritable(); scriptOptions.layers.emplace(); }
    void addLayer(SpriteLayer* layer) { requireWritable(); if(!scriptOptions.layers) selectLayers(); scriptOptions.layers->push_back(layer); }
    void excludeCollider(Collider* collider) { requireWritable(); scriptOptions.excludedColliders.push_back(collider); }
    void excludeBody(PhysicsBody* body) { requireWritable(); scriptOptions.excludedBodies.push_back(body); }
    void setPredicate(std::function<bool(const Collider&)> predicate) { requireWritable(); scriptOptions.predicate=std::move(predicate); }
    void setCapacity(uint32_t capacity);
    void beginQuery();
    void endQuery() { mQuerying=false; }
    void resetHits();
    /// @endcond
private:
    uint32_t mCapacity;
    bool mOverflow = false;
    bool mQuerying = false;
    void requireWritable() const;
    std::vector<CollisionQueryHit> mHits;
};

enum class CollisionQueryKind { Point, Circle, Box, Capsule, Cast, Nearest };
struct CollisionQueryGeometry {
    CollisionQueryKind kind;
    Point start{}, end{};
    double radius = 0, maxDistance = 0;
    RotatedRect box{};
};
void queryColliders(const std::vector<Collider*>& colliders,
    const CollisionQueryGeometry& query, const CollisionQueryOptions& options,
    CollisionQueryBuffer& results);
/// @endcond
}
#endif
