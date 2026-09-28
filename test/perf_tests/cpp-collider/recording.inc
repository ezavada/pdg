// Optional capture of actual benchmark trajectories for synchronized playback.
// Sample the quality groups or circle matrix described in the README; every body
// still participates in the full simulation. Capture occurs outside step timing.
struct Recording {
    struct Body {
        pdg::PhysicsBody *source;
        int index;
        double hx, hy;           // hy == 0 denotes a circle of radius hx
        double originX, originY; // independent moving pairs are recorded in local coordinates
    };
    bool enabled, chipmunk;
    std::string scene, owner;
    int simulationBodies, totalSteps;
    double sleepAfter;
    struct Pair {
        size_t firstBody;
        int column, row;
        double offset, contactSeconds, speed, releaseSeconds;
    };
    std::vector<Pair> pairs;
    std::vector<Body> bodies;
    std::vector<std::array<double, 4>> scenery; // x, y, half width, half height
    std::vector<std::vector<double>> frames;    // seconds, then x/y/angle/sleep per body
    Recording(const Options &options, bool native, const std::string &scenario)
        : enabled(!options.record.empty()), chipmunk(native), scene(scenario), owner(options.owner),
          simulationBodies(options.bodies), totalSteps(options.warmup + options.steps),
          sleepAfter(native ? options.sleepAfter : 0) {}
    void add(pdg::PhysicsBody *body, int index, double hx, double hy, double x = 0, double y = 0) {
        if (enabled)
            bodies.push_back({body, index, hx, hy, x, y});
    }
    void capture(int step) {
        if (!enabled || (step % 2 && step != totalSteps))
            return;
        std::vector<double> frame;
        frame.reserve(1 + 4 * bodies.size());
        frame.push_back(step * .01);
        for (const auto &body : bodies) {
            const auto state = body.source->getState();
            bool sleeping = false;
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            if (chipmunk)
                sleeping = cpBodyIsSleeping(static_cast<cpBody *>(body.source->nativeBody()));
#endif
            frame.insert(frame.end(), {state.x - body.originX, state.y - body.originY,
                                       state.rotation, double(sleeping)});
        }
        frames.push_back(std::move(frame));
    }
    void write(std::ostream &out) const {
        out << "{\"scene\":\"" << scene << "\",\"owner\":\"" << owner << "\",\"solver\":\""
            << (chipmunk ? "chipmunk" : "basic") << "\",\"simulationBodies\":" << simulationBodies
            << ",\"sleepAfter\":" << sleepAfter << ",\"frameSeconds\":0.02,\"bodies\":[";
        for (size_t i = 0; i < bodies.size(); ++i) {
            if (i)
                out << ',';
            out << '[' << bodies[i].index << ',' << bodies[i].hx << ',' << bodies[i].hy << ']';
        }
        out << "],\"pairs\":[";
        for (size_t i = 0; i < pairs.size(); ++i) {
            if (i)
                out << ',';
            const auto &p = pairs[i];
            out << '[' << p.firstBody << ',' << p.column << ',' << p.row << ',' << p.offset << ','
                << p.contactSeconds << ',' << p.speed << ',' << p.releaseSeconds << ']';
        }
        out << "],\"scenery\":[";
        for (size_t i = 0; i < scenery.size(); ++i) {
            if (i)
                out << ',';
            const auto &s = scenery[i];
            out << '[' << s[0] << ',' << s[1] << ',' << s[2] << ',' << s[3] << ']';
        }
        out << "],\"frames\":[";
        for (size_t i = 0; i < frames.size(); ++i) {
            if (i)
                out << ',';
            out << '[';
            for (size_t j = 0; j < frames[i].size(); ++j) {
                if (j)
                    out << ',';
                out << frames[i][j];
            }
            out << ']';
        }
        out << "]}";
    }
};
std::vector<Recording> recordings;
void finishRecording(Recording &recording) {
    if (!recording.enabled)
        return;
    // Only immutable numbers survive owner teardown, never borrowed pointers.
    for (auto &body : recording.bodies)
        body.source = nullptr;
    recordings.push_back(std::move(recording));
}
