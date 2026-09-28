#include "pdg/sys/physicsbody.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace pdg;
namespace {
void expect(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
void checkQueries() {
    const auto& none = PhysicsBody::NoPhysics;
    expect(!none.isPresent() && !none.isAttached(), "NoPhysics must remain absent");
    expect(none.getMode() == physicsBody_None && none.getSolver() == physicsSolver_None,
        "NoPhysics must have no physical mode or solver");
    expect(none.getMass() == 0 && none.getMomentOfInertia() == 0, "NoPhysics has no mass or inertia");
    expect(none.getLinearDamping() == 0 && none.getAngularDamping() == 0 &&
        none.getFriction() == 0 && none.getRestitution() == 0, "NoPhysics query defaults");
    auto state = none.getState();
    expect(state.x == 0 && state.y == 0 && state.rotation == 0 &&
        state.velocityX == 0 && state.velocityY == 0 && state.angularVelocity == 0,
        "NoPhysics must not retain motion");
    auto velocity = none.getVelocity();
    state.x = 12; velocity.x = 9;
    expect(none.getState().x == 0 && none.getVelocity().x == 0, "Queries must return independent values");
}
}
int main(int argc, char* argv[]) {
    try {
        checkQueries();
        if (argc > 1 && std::string(argv[1]) == "--queries-only") return EXIT_SUCCESS;
        auto& first = PhysicsBody::NoPhysics;
        auto& second = PhysicsBody::NoPhysics;
        // An update loop must neither flood diagnostics nor queue ignored loads.
        for (int i = 0; i < 10000; ++i) {
            expect(&first.applyImpulse(Vector(3, 4)) == &second, "No-op setters return the singleton");
            expect(&second.applyAngularImpulse(2) == &first, "No-op angular impulse remains shared");
            expect(first.applyTorque(1, .25) == physicsForce_None, "No-op loads have no handle");
        }
        first.step(1);
        checkQueries();
        PhysicsBody body;
        body.step(1);
        expect(body.getSpeed() == 0 && body.getAngularVelocity() == 0,
            "A real body must not inherit ignored singleton commands");
        std::cout << "NoPhysics diagnostics contract passed\n";
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
