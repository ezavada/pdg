// Included in collider.cpp's anonymous namespace. Quality measurements are
// independent of solver contact reports and stay outside the timed region.
struct QualityBox {
    pdg::PhysicsBody *body = nullptr;
    double x = 0, y = 0, angle = 0, hx = 1, hy = 1;
    int index = -1, group = -1;
    double left = 0, right = 0, top = 0, bottom = 0;
    void update() {
        if (body) {
            const auto state = body->getState();
            x = state.x;
            y = state.y;
            angle = state.rotation;
        }
        const double c = std::abs(std::cos(angle)), s = std::abs(std::sin(angle));
        const double rx = c * hx + s * hy, ry = s * hx + c * hy;
        left = x - rx;
        right = x + rx;
        top = y - ry;
        bottom = y + ry;
    }
};
double penetration(const QualityBox &a, const QualityBox &b) {
    const double ca = std::cos(a.angle), sa = std::sin(a.angle);
    const double cb = std::cos(b.angle), sb = std::sin(b.angle);
    double depth = std::numeric_limits<double>::infinity();
    for (const auto &axis :
         std::array<std::array<double, 2>, 4>{{{ca, sa}, {-sa, ca}, {cb, sb}, {-sb, cb}}}) {
        const double nx = axis[0], ny = axis[1];
        const double ra = a.hx * std::abs(nx * ca + ny * sa) + a.hy * std::abs(-nx * sa + ny * ca);
        const double rb = b.hx * std::abs(nx * cb + ny * sb) + b.hy * std::abs(-nx * sb + ny * cb);
        const double overlap = ra + rb - std::abs((b.x - a.x) * nx + (b.y - a.y) * ny);
        if (overlap <= 0)
            return 0;
        depth = std::min(depth, overlap);
    }
    return depth;
}
struct QualityJoint {
    pdg::PhysicsBody *a;
    pdg::PhysicsBody *b;
    pdg::Point anchorA, anchorB;
    static std::array<double, 2> world(const pdg::PhysicsBody &body, const pdg::Point &local) {
        const auto state = body.getState();
        const double c = std::cos(state.rotation), s = std::sin(state.rotation);
        return {state.x + c * local.x - s * local.y, state.y + s * local.x + c * local.y};
    }
    double error() const {
        const auto p = world(*a, anchorA), q = world(*b, anchorB);
        return std::hypot(p[0] - q[0], p[1] - q[1]);
    }
};
void checkQualityMetrics() {
    const QualityBox a{nullptr, 0, 0, 0, 1, 1};
    QualityBox b{nullptr, 1.75, 0, 0, 1, 1};
    if (std::abs(penetration(a, b) - .25) > 1e-8)
        throw std::runtime_error("Quality metric failed known box overlap");
    b.x = 3;
    if (penetration(a, b) != 0)
        throw std::runtime_error("Quality metric failed separated boxes");
    b.x = 2;
    b.angle = std::acos(-1.0) / 4;
    if (std::abs(penetration(a, b) - (std::sqrt(2.0) - 1)) > 1e-8)
        throw std::runtime_error("Quality metric failed rotated box overlap");
    pdg::PhysicsBody first, second;
    first.teleport(pdg::Point(3, 4), std::acos(-1.0) / 2);
    second.teleport(pdg::Point(3, 5.25), 0);
    QualityJoint joint{&first, &second, pdg::Point(1, 0), pdg::Point()};
    if (std::abs(joint.error() - .25) > 1e-6)
        throw std::runtime_error("Quality metric failed transformed joint anchors");
}
Result runQuality(const Options &options, bool chipmunk, const std::string &scene) {
    using namespace pdg;
    const bool chain = scene == "chain", pile = scene == "pile";
    const int perGroup = pile ? 40 : 10;
    const int groups = (options.bodies + perGroup - 1) / perGroup;
    uint64_t notifications = 0;
    const auto setupStart = Clock::now();
    auto *manager = SpriteManager::getSingletonInstance();
    std::unique_ptr<SpriteLayer, void (*)(SpriteLayer *)> layer(SpriteManager::createSpriteLayer(),
                                                                SpriteManager::cleanupLayer);
    manager->addLayer(layer.get());
    configure(options, chipmunk, *layer, 9.8);
    layer->enableCollisions();
    Sprite *host = options.owner == "part" ? layer->createSprite() : nullptr;
    std::vector<PhysicsBody *> bodies, anchors;
    std::vector<QualityBox> boxes;
    std::vector<QualityJoint> joints;
    Recording recording(options, chipmunk, scene);
    bodies.reserve(options.bodies);
    auto origin = [&](int group) { return group * (chain ? 26.0 : pile ? 16.0 : 12.0); };
    auto obstacle = [&](double x, double y, double hx, double hy, int group) {
        auto *owner = layer->createSprite();
        owner->setLocation(x, y);
        owner->setupCollider()
            .setBox(pdg::Rect(-hx, -hy, hx, hy))
            .setRestitution(0)
            .setFriction(.6);
        boxes.push_back({nullptr, x, y, 0, hx, hy, -1, group});
        if (recording.enabled && group == 0)
            recording.scenery.push_back({x, y, hx, hy});
    };
    for (int g = 0; g < groups; ++g) {
        if (chain) {
            auto *anchor = layer->createSprite();
            anchor->setLocation(origin(g), 0);
            anchors.push_back(&anchor->setupPhysicsBody().setMode(physicsBody_Static));
        } else {
            obstacle(origin(g), .5, pile ? 7 : 4, .5, g);
            if (pile) {
                obstacle(origin(g) - 7.5, -10, .5, 10, g);
                obstacle(origin(g) + 7.5, -10, .5, 10, g);
            }
        }
    }
    const int staticColliders = int(boxes.size());
    // Integer PRNG gives the same initial piles on every platform and solver.
    uint32_t seed = 0x706467;
    auto random = [&] {
        seed = seed * 1664525u + 1013904223u;
        return double(seed >> 8) / 16777216.0;
    };
    auto initialize = [&](auto &owner, int i) {
        const int group = i / perGroup, cell = i % perGroup;
        const double x = origin(group) + (chain  ? 2 * cell + 1
                                          : pile ? (cell % 5 - 2) * 2.1 + (random() - .5) * .15
                                                 : 0);
        const double y = chain ? 0 : pile ? -2.5 - (cell / 5) * 2.2 : -1 - 2 * cell;
        const double angle = pile ? (random() - .5) * .12 : 0;
        const double hy = chain ? .2 : 1;
        owner.setLocation(x, y).setRotation(angle);
        auto &body = owner.setupPhysicsBody(1, (4 + 4 * hy * hy) / 12);
        body.setRestitution(0).setFriction(.6);
        if (chain)
            body.setLinearDamping(.4).setAngularDamping(.4);
        // Native gravity permits sleeping; the basic solver has no world gravity.
        // Both scenes experience the same 9.8 units/s^2 acceleration.
        if (!chipmunk)
            body.addContinuousForce(Vector(0, 9.8));
        owner.setupCollider()
            .setBox(pdg::Rect(-1, -hy, 1, hy))
            .setContactHandler([&](const ColliderContact &c) {
                if (c.phase != collision_End)
                    ++notifications;
            });
        if (chain) {
            auto *previous = cell ? bodies.back() : anchors[group];
            const pdg::Point a(cell ? 1 : 0, 0), b(-1, 0);
            previous->createPivotJoint(body, a, b);
            joints.push_back({previous, &body, a, b});
        }
        bodies.push_back(&body);
        if (group == 0)
            recording.add(&body, i, 1, hy);
        boxes.push_back({&body, x, y, angle, 1, hy, i, group});
    };
    for (int i = 0; i < options.bodies; ++i) {
        if (host)
            initialize(*host->createPart("quality " + std::to_string(i)), i);
        else
            initialize(*layer->createSprite(), i);
    }
    const double setupMs = milliseconds(Clock::now() - setupStart);
    recording.capture(0);
    for (int i = 0; i < options.warmup; ++i) {
        advance(chipmunk, *layer);
        recording.capture(i + 1);
    }
    notifications = 0;
    std::vector<PhysicsBodyState> previous;
    for (auto *body : bodies)
        previous.push_back(body->getState());
    std::vector<double> timings;
    double total = 0, speed2 = 0, angular2 = 0, motion2 = 0;
    uint64_t tailSamples = 0;
    int quietSteps = 0;
    double settled = -1;
    const int tailStart = options.steps - std::min(options.steps, 100); // final simulated second
    for (int i = 0; i < options.steps; ++i) {
        const auto start = Clock::now();
        advance(chipmunk, *layer);
        const double elapsed = milliseconds(Clock::now() - start);
        timings.push_back(elapsed);
        total += elapsed;
        recording.capture(options.warmup + i + 1);
        double maxSpeed2 = 0, maxAngular = 0;
        for (size_t j = 0; j < bodies.size(); ++j) {
            validate(*bodies[j], chipmunk);
            const auto state = bodies[j]->getState();
            const double v2 = state.velocityX * state.velocityX + state.velocityY * state.velocityY;
            maxSpeed2 = std::max(maxSpeed2, v2);
            maxAngular = std::max(maxAngular, std::abs(state.angularVelocity));
            if (i >= tailStart) {
                speed2 += v2;
                angular2 += state.angularVelocity * state.angularVelocity;
                const double dx = state.x - previous[j].x, dy = state.y - previous[j].y;
                motion2 += dx * dx + dy * dy;
                ++tailSamples;
            }
            previous[j] = state;
        }
        if (maxSpeed2 < .05 * .05 && maxAngular < .05) {
            if (++quietSteps == 100)
                settled = (options.warmup + i - 99) * .01;
        } else {
            quietSteps = 0;
            settled = -1;
        }
    }
    Result result{};
    result.solver = chipmunk ? "chipmunk" : "basic";
    result.scenario = scene;
    result.owner = options.owner;
    result.bodies = options.bodies;
    result.steps = options.steps;
    result.warmup = options.warmup;
    result.setupMs = setupMs;
    result.meanMs = total / options.steps;
    std::sort(timings.begin(), timings.end());
    result.medianMs = timings[size_t(std::ceil(.5 * timings.size())) - 1];
    result.p95Ms = timings[size_t(std::ceil(.95 * timings.size())) - 1];
    result.maxMs = timings.back();
    result.bodyStepsPerSecond = double(options.bodies) * options.steps * 1000 / total;
    result.contacts = notifications;
    result.quality = true;
    result.staticColliders = staticColliders;
    result.staticBodies = int(anchors.size());
    result.constraints = int(joints.size());
    result.tailRmsSpeed = std::sqrt(speed2 / tailSamples);
    result.tailRmsAngularSpeed = std::sqrt(angular2 / tailSamples);
    result.tailRmsStepMotion = std::sqrt(motion2 / tailSamples);
    result.settledAtSeconds = settled;
    configuration(result, options, chipmunk);
    // Common OBB overlap metric, computed after simulation for both solvers.
    for (auto &box : boxes)
        box.update();
    std::sort(boxes.begin(), boxes.end(),
              [](const auto &a, const auto &b) { return a.left < b.left; });
    double overlap2 = 0;
    size_t overlaps = 0;
    for (size_t i = 0; i < boxes.size(); ++i) {
        const auto &a = boxes[i];
        for (size_t j = i + 1; j < boxes.size() && boxes[j].left < a.right; ++j) {
            const auto &b = boxes[j];
            if ((!a.body && !b.body) || b.top >= a.bottom || a.top >= b.bottom)
                continue;
            // Adjacent links intentionally meet at their pivot and do not collide.
            if (chain && a.group == b.group && std::abs(a.index - b.index) == 1)
                continue;
            const double depth = penetration(a, b);
            if (depth > 0) {
                result.finalMaxPenetration = std::max(result.finalMaxPenetration, depth);
                overlap2 += depth * depth;
                ++overlaps;
            }
        }
    }
    result.finalRmsPenetration = overlaps ? std::sqrt(overlap2 / overlaps) : 0;
    double error2 = 0;
    for (const auto &joint : joints) {
        const double error = joint.error();
        result.finalMaxJointError = std::max(result.finalMaxJointError, error);
        error2 += error * error;
    }
    result.finalRmsJointError = joints.empty() ? 0 : std::sqrt(error2 / joints.size());
    for (size_t i = 0; i < bodies.size(); ++i) {
        const auto state = bodies[i]->getState();
        result.checksum += state.x + state.y + state.rotation;
        if (!chain &&
            (state.y > 2 || std::abs(state.x - origin(int(i) / perGroup)) > (pile ? 8 : 5)))
            ++result.escapedBodies;
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if (chipmunk && cpBodyIsSleeping(static_cast<cpBody *>(bodies[i]->nativeBody())))
            ++result.sleepingBodies;
#endif
    }
    // Quality and timing have no arbitrary pass/fail threshold. Poor settling,
    // overlap or escaped bodies remain visible in the report instead of hidden.
    finishRecording(recording);
    return result;
}
