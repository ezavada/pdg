// Test-build-only owner for exercising borrowed Chipmunk bindings. All returned
// handles are valid only until this fixture is deleted; do not delete the handles.
#include <memory>
#include <vector>
class BrowserChipmunkFixture {
    cpSpace* space_ = cpSpaceNew();
    cpBody* a_ = cpBodyNew(1, 1);
    cpBody* b_ = cpBodyNew(1, 1);
    cpShape* shapeA_ = cpCircleShapeNew(a_, 2, cpvzero);
    cpShape* shapeB_ = cpCircleShapeNew(b_, 2, cpvzero);
    emscripten::val callback_ = emscripten::val::undefined();
    std::vector<cpConstraint*> joints_;
public:
    BrowserChipmunkFixture() {
        cpBodySetPosition(b_, cpv(3, 0));
        cpSpaceAddBody(space_, a_); cpSpaceAddBody(space_, b_);
        cpSpaceAddShape(space_, shapeA_); cpSpaceAddShape(space_, shapeB_);
        auto* handler = cpSpaceAddDefaultCollisionHandler(space_);
        handler->userData = this;
        handler->preSolveFunc = [](cpArbiter* arb, cpSpace*, cpDataPointer data) -> cpBool {
            auto& callback = static_cast<BrowserChipmunkFixture*>(data)->callback_;
            if (!callback.isUndefined()) callback(
                emscripten::val(arb, emscripten::return_value_policy::reference()));
            return cpFalse; // Keep the overlap stable for first/ongoing contact tests.
        };
        joints_ = {
            cpPinJointNew(a_, b_, cpvzero, cpvzero),
            cpSlideJointNew(a_, b_, cpvzero, cpvzero, 0, 10),
            cpPivotJointNew2(a_, b_, cpvzero, cpvzero),
            cpGrooveJointNew(a_, b_, cpv(0, 0), cpv(10, 0), cpvzero),
            cpDampedSpringNew(a_, b_, cpvzero, cpvzero, 3, 5, 2),
            cpDampedRotarySpringNew(a_, b_, 0, 5, 2),
            cpRotaryLimitJointNew(a_, b_, -1, 1),
            cpRatchetJointNew(a_, b_, 0, 1),
            cpGearJointNew(a_, b_, 0, 1),
            cpSimpleMotorNew(a_, b_, 1)
        };
    }
    ~BrowserChipmunkFixture() {
        for (auto* joint : joints_) cpConstraintFree(joint);
        cpSpaceRemoveShape(space_, shapeA_); cpSpaceRemoveShape(space_, shapeB_);
        cpShapeFree(shapeA_); cpShapeFree(shapeB_);
        cpSpaceRemoveBody(space_, a_); cpSpaceRemoveBody(space_, b_);
        cpBodyFree(a_); cpBodyFree(b_); cpSpaceFree(space_);
    }
    cpSpace* space() { return space_; }
    cpConstraint* joint(unsigned index) { return joints_.at(index); }
    void withContact(emscripten::val callback) {
        callback_ = callback;
        cpSpaceStep(space_, 1.0/60);
        callback_ = emscripten::val::undefined();
    }
};
EMSCRIPTEN_BINDINGS(pdg_chipmunk_test_fixture) {
    emscripten::class_<BrowserChipmunkFixture>("_ChipmunkTestFixture")
        .constructor<>()
        .function("space", &BrowserChipmunkFixture::space, emscripten::return_value_policy::reference())
        .function("joint", &BrowserChipmunkFixture::joint, emscripten::return_value_policy::reference())
        .function("withContact", &BrowserChipmunkFixture::withContact);
}
