// Independent circle pairs: impact offsets/times or force angles/magnitudes.
struct CirclePairLayout {
    int pairCount, columns, rows, worldColumns;
    bool touching;
    double pitch;
    static constexpr double separation = 6, maxOffset = 2.4;
    explicit CirclePairLayout(const Options &options, bool forceScene)
        : pairCount(options.bodies / 2), columns(std::min(5, pairCount)),
          rows((pairCount + columns - 1) / columns),
          worldColumns(int(std::ceil(std::sqrt(double((options.bodies + 1) / 2))))),
          touching(forceScene),
          // Center a compact world grid to limit float-coordinate rounding. Keep
          // pairs apart even after rebound/deflection. Force-pair speed is bounded
          // by work done while their centers remain at most two radii apart.
          pitch(std::ceil(12 + (forceScene ? 16 : 6 * std::sqrt(2.)) *
                                   (options.steps + options.warmup) * .01)) {}
    double offset(int pair) const {
        return rows > 1
                   ? (touching ? std::acos(-1.) / 2 : maxOffset) * (pair / columns) / (rows - 1)
                   : 0;
    }
    double seconds(int pair) const {
        return columns > 1 ? 10. - 9. * (pair % columns) / (columns - 1) : 10.;
    }
    double speed(int pair) const {
        if (touching)
            return .5 * std::pow(2., pair % columns);
        const double d = offset(pair);
        const double contactX = d < 2 ? std::sqrt(4 - d * d) : 0;
        return (separation - contactX) / (2 * seconds(pair));
    }
    int sampledRow(int row) const {
        const int count = std::min(6, rows);
        for (int i = 0; i < count; ++i)
            if (row == (count > 1 ? int(std::lround(double(i) * (rows - 1) / (count - 1))) : 0))
                return i;
        return -1;
    }
};

Result runCirclePairs(const Options &options, bool chipmunk, bool touching) {
    using namespace pdg;
    const CirclePairLayout layout(options, touching);
    uint64_t notifications = 0;
    bool foreignContact = false, forceRemovalFailed = false;
    double simulationTime = 0;
    std::vector<double> firstContact(layout.pairCount, -1), released(layout.pairCount, -1);
    std::vector<PhysicsForceId> forces(options.bodies, physicsForce_None);
    std::vector<PhysicsBody *> bodies;
    std::vector<Collider *> colliders;
    bodies.reserve(options.bodies);
    colliders.reserve(options.bodies);
    Recording recording(options, chipmunk, touching ? "contacts" : "approach");
    const auto setupStart = Clock::now();
    auto *manager = SpriteManager::getSingletonInstance();
    // Declare the layer after callback captures, so teardown cannot outlive them.
    std::unique_ptr<SpriteLayer, void (*)(SpriteLayer *)> layer(SpriteManager::createSpriteLayer(),
                                                                SpriteManager::cleanupLayer);
    manager->addLayer(layer.get());
    configure(options, chipmunk, *layer, 0);
    layer->enableCollisions();
    Sprite *host = options.owner == "part" ? layer->createSprite() : nullptr;
    auto initialize = [&](auto &owner, int index) {
        const int pair = index / 2, column = pair % layout.columns, row = pair / layout.columns;
        const bool right = index % 2, paired = pair < layout.pairCount;
        const double x = (pair % layout.worldColumns - layout.worldColumns / 2) * layout.pitch;
        const double y = (pair / layout.worldColumns - layout.worldColumns / 2) * layout.pitch;
        const double value = paired ? layout.offset(pair) : 0;
        const double offset = touching ? 0 : value;
        owner.setLocation(x + (right ? 1 : -1) * (touching ? 1 : CirclePairLayout::separation / 2),
                          y + (right ? 1 : -1) * offset / 2);
        auto &body = owner.setupPhysicsBody(1, .5);
        body.setRestitution(touching ? 0 : 1).setFriction(0);
        if (paired && touching) {
            const double force = layout.speed(pair) * (right ? -1 : 1);
            forces[index] =
                body.addContinuousForce(Vector(force * std::cos(value), -force * std::sin(value)));
        } else
            body.setVelocity(Vector(paired ? (right ? -1 : 1) * layout.speed(pair) : 0, 0));
        auto &collider = owner.setupCollider().setCircle(1);
        collider.setContactHandler([&, index, pair](const ColliderContact &contact) {
            if (contact.phase == collision_End) {
                if (touching && pair < layout.pairCount && released[pair] < 0) {
                    released[pair] = simulationTime;
                    for (int i = pair * 2; i < pair * 2 + 2; ++i) {
                        if (!bodies[i]->removeForce(forces[i]))
                            forceRemovalFailed = true;
                        forces[i] = physicsForce_None;
                    }
                }
                return;
            }
            ++notifications;
            if (pair >= layout.pairCount || contact.other != colliders[index ^ 1]) {
                foreignContact = true;
                return;
            }
            if (firstContact[pair] < 0)
                firstContact[pair] = simulationTime;
        });
        bodies.push_back(&body);
        colliders.push_back(&collider);
        const int sampleRow = layout.sampledRow(row);
        if (recording.enabled && paired && sampleRow >= 0) {
            if (!right)
                recording.pairs.push_back({recording.bodies.size(), column, sampleRow, value,
                                           (touching ? 0 : layout.seconds(pair)),
                                           layout.speed(pair), -1});
            recording.add(&body, index, 1, 0, x, y);
        }
    };
    for (int i = 0; i < options.bodies; ++i) {
        if (host)
            initialize(*host->createPart("approach " + std::to_string(i)), i);
        else
            initialize(*layer->createSprite(), i);
    }
    // Inspect exact initial tangency at t=0, so even an immediately separating
    // vertical pair receives End and can cancel both force handles on that step.
    if (touching)
        layer->animateLayer(0);
    const double setupMs = milliseconds(Clock::now() - setupStart);
    auto step = [&](int index) {
        simulationTime = (index + 1) * .01;
        advance(chipmunk, *layer);
    };
    recording.capture(0);
    for (int i = 0; i < options.warmup; ++i) {
        step(i);
        recording.capture(i + 1);
    }
    notifications = 0;
    std::vector<double> timings;
    timings.reserve(options.steps);
    double total = 0, checksum = 0;
    for (int i = 0; i < options.steps; ++i) {
        const auto start = Clock::now();
        step(options.warmup + i);
        const double elapsed = milliseconds(Clock::now() - start);
        timings.push_back(elapsed);
        total += elapsed;
        recording.capture(options.warmup + i + 1);
    }
    for (auto *body : bodies) {
        validate(*body, chipmunk);
        const auto state = body->getState();
        checksum += state.x + state.y + state.rotation;
    }
    if (foreignContact)
        throw std::runtime_error("Moving circles collided outside their own pair");
    std::sort(timings.begin(), timings.end());
    const auto percentile = [&](double fraction) {
        return timings[size_t(std::ceil(fraction * timings.size())) - 1];
    };
    Result result{chipmunk ? "chipmunk" : "basic",
                  touching ? "contacts" : "approach",
                  options.owner,
                  options.bodies,
                  options.steps,
                  options.warmup,
                  setupMs,
                  total / options.steps,
                  percentile(.5),
                  percentile(.95),
                  timings.back(),
                  double(options.bodies) * options.steps * 1000 / total,
                  notifications,
                  checksum,
                  ""};
    for (int pair = 0; pair < layout.pairCount; ++pair) {
        const double offset = layout.offset(pair), expectedTime = layout.seconds(pair);
        if (touching) {
            if (firstContact[pair] < 0)
                throw std::runtime_error("Force pair did not start in contact");
            if (released[pair] >= 0) {
                ++result.releasedPairs;
            } else
                ++result.drivenPairs;
            continue;
        }
        if (offset < 2)
            ++result.expectedHitPairs;
        else if (offset > 2)
            ++result.missPairs;
        if (firstContact[pair] >= 0) {
            ++result.collidedPairs;
            if (offset > 2.001)
                throw std::runtime_error(
                    "Moving circle miss row collided: pair " + std::to_string(pair) + " offset " +
                    std::to_string(offset) + " time " + std::to_string(firstContact[pair]));
            const double error = std::abs(firstContact[pair] - expectedTime);
            result.maxContactTimeError = std::max(result.maxContactTimeError, error);
            if (error > .06)
                throw std::runtime_error("Moving circle contact time differs from its column");
        } else if (offset < 1.99 && simulationTime >= expectedTime + .06) {
            throw std::runtime_error("Moving circle pair failed to collide");
        }
    }
    if (touching) {
        for (auto &pair : recording.pairs)
            pair.releaseSeconds = released[recording.bodies[pair.firstBody].index / 2];
        if (forceRemovalFailed)
            throw std::runtime_error("A released circle force was not removed");
    }
    configuration(result, options, chipmunk);
    finishRecording(recording);
    return result;
}
