#ifndef PDG_SCENE_H_INCLUDED
#define PDG_SCENE_H_INCLUDED
#include "pdg/sys/eventemitter.h"
#include "pdg/sys/refcounted.h"
#include "pdg/sys/spatialtransform.h"
#include "pdg/sys/userdata.h"
#include "pdg/sys/collisionquery.h"
#include <memory>
#include <map>
#include <vector>
#include <cstdint>
namespace pdg {
class SpriteManager;
class SpriteLayer;
class Camera;
class Sprite;
class AnimatedBase;
class Port;
/** Owns layers, an isolated physics world, a camera and logical timers.
 * pause() freezes simulation and owned timers while drawing remains enabled.
 * removeLayer() transfers responsibility to the caller; disposeLayer() destroys.
 * Scenes draw in construction order, above legacy layers. Use separate scenes
 * for gameplay and an independently animated HUD. release() follows PDG's native
 * reference-count convention; explicitly dispose() to end a scene's lifetime.
 */
class Scene : public EventEmitter, public RefCountedObj {
public:
    Scene();
    ~Scene() override;
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    void addLayer(SpriteLayer* layer);
    void removeLayer(SpriteLayer* layer);
    void disposeLayer(SpriteLayer* layer);
    SpriteLayer* createSpriteLayer();
#ifndef PDG_NO_GUI
    SpriteLayer* createSpriteLayer(Port* port);
#endif
    int getLayerCount() const;
    SpriteLayer* getLayer(int index) const;
    /** Query current authoritative geometry without advancing simulation.
     * Available while paused and before the first step. Queries during advance,
     * drawing or a query predicate are rejected. Results retain hit colliders.
     * Single-hit calls return an optional retained hit. Multiple-hit calls return
     * scene-owned storage, valid until the next query or scene disposal.
     * CollisionQueryOptions::maxHits caps multiple-hit results (default 16).
     */
    /// Closest accepted hit, retaining its collider; empty optional if no match.
    std::optional<CollisionQueryHit> raycast(const Point& start, const Point& end, const CollisionQueryOptions& options = {});
    std::optional<CollisionQueryHit> sweepCircle(const Point& center, double radius, const Vector& delta, const CollisionQueryOptions& options = {});
    const std::vector<CollisionQueryHit>& raycast(const Point& start, const Point& end, uint32_t maxHits, const CollisionQueryOptions& options = {});
    const std::vector<CollisionQueryHit>& sweepCircle(const Point& center, double radius, const Vector& delta, uint32_t maxHits, const CollisionQueryOptions& options = {});
    const std::vector<CollisionQueryHit>& overlapPoint(const Point& point, const CollisionQueryOptions& options = {});
    const std::vector<CollisionQueryHit>& overlapCircle(const Point& center, double radius, const CollisionQueryOptions& options = {});
    const std::vector<CollisionQueryHit>& overlapBox(const RotatedRect& box, const CollisionQueryOptions& options = {});
    const std::vector<CollisionQueryHit>& overlapCapsule(const Point& start, const Point& end, double radius, const CollisionQueryOptions& options = {});
    /// @cond INTERNAL
    uint32_t raycast(const Point& start, const Point& end, const CollisionQueryOptions& options, CollisionQueryBuffer& results);
    uint32_t sweepCircle(const Point& center, double radius, const Vector& delta, const CollisionQueryOptions& options, CollisionQueryBuffer& results);
    uint32_t overlapPoint(const Point& point, const CollisionQueryOptions& options, CollisionQueryBuffer& results);
    uint32_t overlapCircle(const Point& center, double radius, const CollisionQueryOptions& options, CollisionQueryBuffer& results);
    uint32_t overlapBox(const RotatedRect& box, const CollisionQueryOptions& options, CollisionQueryBuffer& results);
    uint32_t overlapCapsule(const Point& start, const Point& end, double radius, const CollisionQueryOptions& options, CollisionQueryBuffer& results);
    uint32_t raycast(const Point& start, const Point& end, CollisionQueryBuffer& results) { return raycast(start, end, results.scriptOptions, results); }
    uint32_t sweepCircle(const Point& center, double radius, const Vector& delta, CollisionQueryBuffer& results) { return sweepCircle(center, radius, delta, results.scriptOptions, results); }
    uint32_t overlapPoint(const Point& point, CollisionQueryBuffer& results) { return overlapPoint(point, results.scriptOptions, results); }
    uint32_t overlapCircle(const Point& center, double radius, CollisionQueryBuffer& results) { return overlapCircle(center, radius, results.scriptOptions, results); }
    uint32_t overlapBox(const RotatedRect& box, CollisionQueryBuffer& results) { return overlapBox(box, results.scriptOptions, results); }
    uint32_t overlapCapsule(const Point& start, const Point& end, double radius, CollisionQueryBuffer& results) { return overlapCapsule(start, end, radius, results.scriptOptions, results); }
    uint32_t queryNearestPoint(const Point& point, double maxDistance, CollisionQueryBuffer& results);
    /// @endcond
    /// Filled geometry: points inside a shape return themselves at distance zero.
    std::optional<CollisionQueryHit> nearestPoint(const Point& point, double maxDistance, const CollisionQueryOptions& options = {});
    void pause();
    void resume();
    bool isPaused() const { return mPaused; }
    void setTimeScale(double scale);
    double getTimeScale() const { return mScale; }
    /// Zero selects variable-step timing; positive seconds select fixed steps.
    void setFixedStep(double seconds);
    double getFixedStep() const { return mFixedStep; }
    void setInterpolation(bool enabled);
    bool isInterpolationEnabled() const { return mInterpolate; }
    /// Manual scenes advance only through advance(seconds), useful for tests/replay.
    void setManual(bool manual);
    bool isManual() const { return mManual; }
    void advance(double seconds);
    double getSimulationTime() const { return mTime; }
    double getDroppedTime() const { return mDropped; }
    double getInterpolationAlpha() const;
    std::uint64_t getTick() const { return mTick; }
    void setInputEnabled(bool enabled) { mInputEnabled=enabled; }
    bool isInputEnabled() const { return mInputEnabled && !mDisposed; }
    /// Default retained camera; layers may override it. Camera advancement has one scene owner.
    Camera* getCamera() const { return mCamera; }
    void setCamera(Camera* camera);
    void startTimer(long id, double delayMs, bool oneShot=true, UserData* data=nullptr);
    void cancelTimer(long id);
    void cancelAllTimers();
    void delayTimer(long id, double delayMs);
    void pauseTimer(long id);
    void unpauseTimer(long id);
    bool isTimerPaused(long id) const;
    double getWhenTimerFiresNext(long id) const;
    /// Own an exact external registration; disconnect automatically on disposal.
    std::uint64_t subscribe(EventEmitter& emitter, IEventHandler* handler, long type);
    void unsubscribe(std::uint64_t subscription);
    bool postEvent(long type, void* data, EventEmitter* from=nullptr) override;
    void dispose();
    bool isDisposed() const { return mDisposed; }
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    SCRIPT_OBJECT_REF mSceneScriptObj;
#endif
    /// @cond INTERNAL
    static void advanceAll();
    static void disposeAll();
    static SpriteLayer* findLayer(long id);
    static std::vector<SpriteLayer*> layersInDrawOrder();
    static void dispatch(EventEmitter*, long, void*);
    static void claimCamera(Camera*, Scene*);
    static void releaseCamera(Camera*, Scene*);
    SpatialTransform presentationTransform(Sprite*) const;
    Sprite* mDrawingSprite=nullptr;
    SpriteManager* manager() const { return mManager.get(); }
    /// @endcond
private:
    struct Timer;
    struct Subscription;
    struct Pose { double x=0,y=0,angle=0,sx=1,sy=1; bool operator==(const Pose&) const = default; };
    struct History { std::weak_ptr<AnimatedBase*> life; Pose previous,current; };
    std::unique_ptr<SpriteManager> mManager;
    Camera* mCamera=nullptr;
    std::map<long,std::shared_ptr<Timer>> mTimers;
    std::map<std::uint64_t,std::shared_ptr<Subscription>> mSubscriptions;
    std::map<Sprite*,History> mHistory;
    std::map<Camera*,unsigned> mCameras;
    bool mPaused=false,mManual=false,mInputEnabled=true,mDisposed=false,mInterpolate=false,mAdvancing=false;
    double mScale=1,mFixedStep=0,mAccumulator=0,mTime=0,mDropped=0,mLastHost=0,mFrozenAlpha=0;
    std::uint64_t mTick=0,mTimerOrder=0,mSubscriptionOrder=0;
    unsigned mEventDepth=0;
    bool mQuerying=false;
    std::unique_ptr<CollisionQueryBuffer> mQueryBuffer;
    std::vector<CollisionQueryHit> mQueryResults;
    const std::vector<CollisionQueryHit>& queryMany(const CollisionQueryGeometry&, const CollisionQueryOptions&);
    uint32_t query(const CollisionQueryGeometry&, const CollisionQueryOptions&, CollisionQueryBuffer&);
    bool acceptsEvents() const override { return !mDisposed; }
    void requireLive() const;
    void step(double seconds);
    void finishDisposal();
    void capture(bool before);
    static Pose pose(Sprite*);
};
}
#endif
