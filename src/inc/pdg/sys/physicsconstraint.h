#ifndef PDG_PHYSICS_CONSTRAINT_H_INCLUDED
#define PDG_PHYSICS_CONSTRAINT_H_INCLUDED
#include "pdg/sys/coordinates.h"
#include "pdg/sys/refcounted.h"
#include <memory>
#include <limits>
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
#include "pdg_script_bindings.h"
#endif
namespace pdg {
class PhysicsBody;
enum PhysicsConstraintType : int {
    constraint_Pin = 1,
    constraint_Slide,
    constraint_Pivot,
    constraint_Groove,
    constraint_Spring,
    constraint_RotarySpring,
    constraint_RotaryLimit,
    constraint_Ratchet,
    constraint_Gear,
    constraint_Motor
};
/** Retainable physical relationship between two bodies, independent of owner type.
 * Bodies retain active constraints; addRef/release to retain a native handle after
 * disconnect. Body removal disconnects its constraints. Detached handles remain
 * queryable and return NoPhysics for their former endpoints. Angles are radians,
 * positive relative angles/rates turn body B clockwise relative to A. Angular
 * rates are radians/second; anchors are unscaled body-local distance coordinates.
 * Basic uses bounded sequential impulses; Chipmunk uses its native constraints.
 * Neither solver promises an identical trajectory. Constraint creation requires
 * real, distinct bodies; collision geometry is optional.
 * @ingroup Physics
 */
class PhysicsConstraint : public RefCountedObj {
    friend class PhysicsBody;
    friend class Part;
    friend class AnimationPhysicsRig;
    /// @cond INTERNAL
    friend class PhysicsGraphSnapshot;
    /// @endcond

  public:
    ~PhysicsConstraint() override;
    int getType() const { return mType; }
    bool isActive() const { return mA && mB; }
    bool isBroken() const { return mBroken; }
    PhysicsBody &getBodyA() const;
    PhysicsBody &getBodyB() const;
    /** Copied, unscaled body-local anchors. A requires pin/slide/pivot/spring;
     * B also supports groove. Angular-only constraints throw. */
    Point getAnchorA() const;
    Point getAnchorB() const;
    PhysicsConstraint& setAnchorA(const Point& anchor);
    PhysicsConstraint& setAnchorB(const Point& anchor);
    /** Atomically edit both anchors on pin/slide/pivot/spring constraints.
     * Finite coordinates required. Bodies, colliders, inertia and distance/rest
     * settings are unchanged. Solvers use edits on the next step; disconnected
     * handles remain editable without reconnecting. */
    PhysicsConstraint& setAnchors(const Point& anchorA, const Point& anchorB);
    Point getGrooveStart() const;
    Point getGrooveEnd() const;
    /** Groove only: atomically edit body A's track; endpoints must differ. */
    PhysicsConstraint& setGroove(const Point& start, const Point& end);
    PhysicsConstraint &setMaxForce(double force);
    double getMaxForce() const { return mMaxForce; }
    /// Zero disables breaking; linear constraints use force, angular ones torque.
    PhysicsConstraint &setBreakForce(double force);
    double getBreakForce() const { return mBreakForce; }
    PhysicsConstraint &setCollideBodies(bool collide);
    bool getCollideBodies() const { return mCollideBodies; }
    double getImpulse() const { return mImpulse; }
    double getForce() const { return mForce; }
    /** Rotary-limit angles: body B relative to A, in radians. Other types throw. */
    double getMinAngle() const;
    double getMaxAngle() const;
    PhysicsConstraint& setAngleLimits(double minAngle, double maxAngle);
    /// Idempotent. A retained handle remains safe after both endpoints are released.
    void disconnect();
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    SCRIPT_OBJECT_REF mPhysicsConstraintScriptObj;
#endif
    /// @cond INTERNAL
    void prepareNative();
    void finishStep(double seconds);
    void solveBasic(double seconds);
    /// @endcond
  private:
    PhysicsConstraint(PhysicsBody &a, PhysicsBody &b, int type, const Point &anchorA,
                      const Point &anchorB, const Point &groove, double value1, double value2,
                      double value3);
    PhysicsBody *mA;
    PhysicsBody *mB;
    int mType;
    Point mAnchorA, mAnchorB, mGroove;
    double mValue1, mValue2, mValue3;
    double mMaxForce = std::numeric_limits<double>::infinity(), mBreakForce = 0;
    double mImpulse = 0, mForce = 0;
    bool mCollideBodies = false, mBroken = false;
    bool mAnchorsDirty = false;
    struct Native;
    std::unique_ptr<Native> mNative;
};
} // namespace pdg
#endif
