// Collision/physics throughput without rendering, V8, or a display connection.
#include "pdg/sys/initializer.h"
#include "pdg/sys/sprite.h"
#include "pdg/sys/spritelayer.h"
#include "pdg-main.h"
#include "spritemanager.h"
#include <algorithm>
#include <array>
#include <limits>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using Clock = std::chrono::steady_clock;
struct Options {
    int bodies = 2000, steps = 2000, warmup = 120;
    std::string solver = "both", scenario = "both", owner = "sprite", json;
    std::string broadphase = "tree", record;
    double cellSize = 2, sleepAfter = 0;
    int hashCells = 0, iterations = 10;
};
struct Result {
    std::string solver, scenario, owner;
    int bodies, steps, warmup;
    double setupMs, meanMs, medianMs, p95Ms, maxMs, bodyStepsPerSecond;
    uint64_t contacts;
    double checksum;
    std::string broadphase;
    double cellSize = 0, sleepAfter = 0;
    int hashCells = 0, iterations = 0, staticColliders = 0, staticBodies = 0, constraints = 0;
    bool quality = false;
    double finalMaxPenetration = 0, finalRmsPenetration = 0;
    double finalMaxJointError = 0, finalRmsJointError = 0;
    double tailRmsSpeed = 0, tailRmsAngularSpeed = 0, tailRmsStepMotion = 0;
    double settledAtSeconds = -1;
    int sleepingBodies = 0, escapedBodies = 0;
    int collidedPairs = 0, expectedHitPairs = 0, missPairs = 0;
    double maxContactTimeError = 0;
    int releasedPairs = 0, drivenPairs = 0;
};
int positiveInteger(const char *text) {
    size_t used = 0;
    const auto value = std::stol(text, &used);
    if (used != std::string(text).size() || value <= 0 || value > 1000000)
        throw std::invalid_argument("Counts must be integers from 1 through 1000000");
    return int(value);
}
double number(const char *text, bool allowZero = false) {
    size_t used = 0;
    const double value = std::stod(text, &used);
    if (used != std::string(text).size() || !std::isfinite(value) || value < 0 ||
        (!allowZero && value == 0))
        throw std::invalid_argument("Expected a finite positive number");
    return value;
}
Options parse(int argc, char **argv) {
    Options result;
    for (int i = 1; i < argc; ++i) {
        const std::string option = argv[i];
        if (option == "--quick") continue; // Already a fixed-work benchmark.
        if (option == "--help") {
            std::cout
                << "pdg-collider-perf [--bodies 2000] [--steps 2000] [--warmup 120]\n"
                   "  [--solver both|basic|chipmunk]\n"
                   "  [--scenario both|sparse|contacts|approach|stack|chain|pile|quality|all]\n"
                   "  [--owner sprite|part] [--json results.json]\n"
                   "  [--broadphase tree|hash] [--cell-size 2] [--hash-cells 20000]\n"
                   "  [--iterations 10] [--sleep-after 0] [--record playback.json]\n";
            std::exit(0);
        }
        if (++i == argc)
            throw std::invalid_argument("Missing value for " + option);
        if (option == "--bodies")
            result.bodies = positiveInteger(argv[i]);
        else if (option == "--steps")
            result.steps = positiveInteger(argv[i]);
        else if (option == "--warmup")
            result.warmup = positiveInteger(argv[i]);
        else if (option == "--solver")
            result.solver = argv[i];
        else if (option == "--scenario")
            result.scenario = argv[i];
        else if (option == "--owner")
            result.owner = argv[i];
        else if (option == "--json")
            result.json = argv[i];
        else if (option == "--record")
            result.record = argv[i];
        else if (option == "--broadphase")
            result.broadphase = argv[i];
        else if (option == "--cell-size")
            result.cellSize = number(argv[i]);
        else if (option == "--hash-cells")
            result.hashCells = positiveInteger(argv[i]);
        else if (option == "--iterations")
            result.iterations = positiveInteger(argv[i]);
        else if (option == "--sleep-after")
            result.sleepAfter = number(argv[i], true);
        else
            throw std::invalid_argument("Unknown option " + option);
    }
    if (result.solver != "both" && result.solver != "basic" && result.solver != "chipmunk")
        throw std::invalid_argument("Unknown solver");
    if (result.broadphase != "tree" && result.broadphase != "hash")
        throw std::invalid_argument("Unknown broadphase");
    if (result.sleepAfter > 0 && (result.scenario == "both" || result.scenario == "sparse" ||
                                  result.scenario == "contacts" || result.scenario == "approach" ||
                                  result.scenario == "all"))
        throw std::invalid_argument("Sleeping is only available for quality scenes");
    if (!result.hashCells)
        result.hashCells = result.bodies * 10;
    if (result.scenario != "both" && result.scenario != "sparse" && result.scenario != "contacts" &&
        result.scenario != "approach" && result.scenario != "stack" && result.scenario != "chain" &&
        result.scenario != "pile" && result.scenario != "quality" && result.scenario != "all")
        throw std::invalid_argument("Unknown scenario");
    if (result.owner != "sprite" && result.owner != "part")
        throw std::invalid_argument("Unknown owner");
    if (result.bodies < 2)
        throw std::invalid_argument("At least two bodies are required");
    return result;
}
double milliseconds(Clock::duration value) {
    return std::chrono::duration<double, std::milli>(value).count();
}
void configure(const Options &options, bool chipmunk, pdg::SpriteLayer &layer, double gravity) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    layer.setUseChipmunkPhysics(chipmunk);
    layer.setGravity(chipmunk ? gravity : 0);
    layer.setDamping(1);
    auto *space = pdg::SpriteManager::getSingletonInstance()->mSpace;
    cpSpaceSetIterations(space, options.iterations);
    cpSpaceSetIdleSpeedThreshold(space, .05);
    cpSpaceSetSleepTimeThreshold(space, options.sleepAfter > 0 ? options.sleepAfter : INFINITY);
    if (chipmunk && options.broadphase == "hash")
        cpSpaceUseSpatialHash(space, options.cellSize, options.hashCells);
#else
    (void)options;
    (void)layer;
    (void)gravity;
    if (chipmunk)
        throw std::runtime_error("This build has no Chipmunk solver");
#endif
}
void configuration(Result &result, const Options &options, bool chipmunk) {
    result.broadphase = chipmunk ? options.broadphase : "sweep";
    result.cellSize = chipmunk && options.broadphase == "hash" ? options.cellSize : 0;
    result.hashCells = chipmunk && options.broadphase == "hash" ? options.hashCells : 0;
    result.iterations = chipmunk ? options.iterations : 0;
    result.sleepAfter = chipmunk ? options.sleepAfter : 0;
}
void advance(bool chipmunk, pdg::SpriteLayer &layer) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (chipmunk)
        pdg::SpriteManager::getSingletonInstance()->stepAnimationPhysics(10);
#else
    (void)chipmunk;
#endif
    layer.animateLayer(10);
}
void validate(const pdg::PhysicsBody &body, bool chipmunk) {
    using namespace pdg;
    if (body.getSolver() != (chipmunk ? physicsSolver_Chipmunk : physicsSolver_Basic))
        throw std::runtime_error("Body did not use the requested solver");
    const auto state = body.getState();
    for (double value : {state.x, state.y, state.rotation, state.velocityX, state.velocityY,
                         state.angularVelocity})
        if (!std::isfinite(value))
            throw std::runtime_error("Nonfinite physical state in benchmark");
}
#include "recording.inc"

Result runSparse(const Options &options, bool chipmunk) {
    using namespace pdg;
    uint64_t notifications = 0;
    const auto setupStart = Clock::now();
    auto *manager = SpriteManager::getSingletonInstance();
    // The manager's factory allocates; registration is a separate internal step.
    std::unique_ptr<SpriteLayer, void (*)(SpriteLayer *)> layer(SpriteManager::createSpriteLayer(),
                                                                SpriteManager::cleanupLayer);
    manager->addLayer(layer.get());
    configure(options, chipmunk, *layer, 0);
    layer->enableCollisions();
    Sprite *host = options.owner == "part" ? layer->createSprite() : nullptr;
    std::vector<PhysicsBody *> bodies;
    bodies.reserve(options.bodies);
    Recording recording(options, chipmunk, "sparse");
    const int columns = int(std::ceil(std::sqrt(double(options.bodies))));
    auto initialize = [&](auto &owner, int index) {
        const int cell = index;
        const double x = (cell % columns) * 10.0;
        const double y = (cell / columns) * 10.0;
        owner.setLocation(x, y);
        auto &body = owner.setupPhysicsBody(1, .5);
        body.setRestitution(0).setFriction(.3);
        body.setVelocity(Vector(.1, .15)); // coherent motion preserves sparse spacing
        owner.setupCollider().setCircle(1).setContactHandler([&](const ColliderContact &c) {
            if (c.phase != collision_End)
                ++notifications;
        });
        bodies.push_back(&body);
        if (cell % columns < 3 && cell / columns < 3)
            recording.add(&body, index, 1, 0);
    };
    for (int i = 0; i < options.bodies; ++i) {
        if (host)
            initialize(*host->createPart("body " + std::to_string(i)), i);
        else
            initialize(*layer->createSprite(), i);
    }
    const double setupMs = milliseconds(Clock::now() - setupStart);
    auto step = [&] { advance(chipmunk, *layer); };
    recording.capture(0);
    for (int i = 0; i < options.warmup; ++i) {
        step();
        recording.capture(i + 1);
    }
    notifications = 0;
    std::vector<double> timings;
    timings.reserve(options.steps);
    double total = 0;
    for (int i = 0; i < options.steps; ++i) {
        const auto beforeContacts = notifications;
        const auto start = Clock::now();
        step();
        const double elapsed = milliseconds(Clock::now() - start);
        timings.push_back(elapsed);
        total += elapsed;
        recording.capture(options.warmup + i + 1);
        if (notifications != beforeContacts)
            throw std::runtime_error("Sparse scene unexpectedly collided");
    }
    double checksum = 0;
    for (auto *body : bodies) {
        validate(*body, chipmunk);
        const auto state = body->getState();
        checksum += state.x + state.y + state.rotation;
    }
    if (notifications != 0)
        throw std::runtime_error("Sparse scene unexpectedly collided");
    std::sort(timings.begin(), timings.end());
    const auto percentile = [&](double fraction) {
        return timings[size_t(std::ceil(fraction * timings.size())) - 1];
    };
    Result result{chipmunk ? "chipmunk" : "basic",
                  "sparse",
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
    configuration(result, options, chipmunk);
    finishRecording(recording);
    return result;
}
#include "quality.inc"
#include "circle-pairs.inc"

void writeJson(std::ostream &out, const std::vector<Result> &results) {
    out << std::setprecision(10)
        << "{\n  \"stepSeconds\": 0.01,\n  \"rendering\": false,\n"
           "  \"contactListeners\": true,\n  \"results\": [\n";
    for (size_t i = 0; i < results.size(); ++i) {
        const auto &r = results[i];
        if (i)
            out << ",\n";
        out << "    {\"solver\": \"" << r.solver << "\", \"scenario\": \"" << r.scenario
            << "\", \"owner\": \"" << r.owner << "\", \"bodies\": " << r.bodies
            << ", \"colliders\": " << (r.bodies + r.staticColliders) << ", \"steps\": " << r.steps
            << ", \"warmup\": " << r.warmup << ", \"setupMs\": " << r.setupMs
            << ", \"meanMs\": " << r.meanMs << ", \"medianMs\": " << r.medianMs
            << ", \"p95Ms\": " << r.p95Ms << ", \"maxMs\": " << r.maxMs
            << ", \"bodyStepsPerSecond\": " << r.bodyStepsPerSecond
            << ", \"contactNotifications\": " << r.contacts << ", \"checksum\": " << r.checksum
            << ", \"broadphase\": \"" << r.broadphase << "\", \"cellSize\": " << r.cellSize
            << ", \"hashCells\": " << r.hashCells << ", \"iterations\": " << r.iterations
            << ", \"sleepAfterSeconds\": " << r.sleepAfter
            << ", \"staticBodies\": " << r.staticBodies
            << ", \"staticColliders\": " << r.staticColliders
            << ", \"constraints\": " << r.constraints;
        if (r.scenario == "contacts")
            out << ", \"releasedPairs\": " << r.releasedPairs
                << ", \"drivenPairs\": " << r.drivenPairs;
        if (r.scenario == "approach")
            out << ", \"collidedPairs\": " << r.collidedPairs
                << ", \"expectedHitPairs\": " << r.expectedHitPairs
                << ", \"missPairs\": " << r.missPairs
                << ", \"maxContactTimeErrorSeconds\": " << r.maxContactTimeError;
        if (r.quality) {
            out << ", \"finalMaxPenetration\": " << r.finalMaxPenetration
                << ", \"finalRmsPenetration\": " << r.finalRmsPenetration
                << ", \"finalMaxJointError\": " << r.finalMaxJointError
                << ", \"finalRmsJointError\": " << r.finalRmsJointError
                << ", \"tailRmsSpeed\": " << r.tailRmsSpeed
                << ", \"tailRmsAngularSpeed\": " << r.tailRmsAngularSpeed
                << ", \"tailRmsStepMotion\": " << r.tailRmsStepMotion
                << ", \"sleepingBodies\": " << r.sleepingBodies
                << ", \"escapedBodies\": " << r.escapedBodies << ", \"settledAtSeconds\": ";
            if (r.settledAtSeconds < 0)
                out << "null";
            else
                out << r.settledAtSeconds;
        }
        out << "}";
    }
    out << "\n  ]\n}\n";
}
} // namespace
namespace pdg {
bool Initializer::allowHorizontalOrientation() throw() { return true; }
bool Initializer::allowVerticalOrientation() throw() { return true; }
const char *Initializer::getAppName(bool) throw() { return "PDG Collider Performance"; }
const char *Initializer::getMainResourceFileName() throw() { return nullptr; }
bool Initializer::installGlobalHandlers() throw() { return false; }
bool Initializer::getGraphicsEnvironmentDimensions(Rect, Rect, long &w, long &h, uint8 &d) throw() {
    w = h = 1;
    d = 32;
    return false;
}
} // namespace pdg
int main(int argc, char **argv) {
    try {
        const auto options = parse(argc, argv);
        if (pdg::main_initManagers() != 0)
            throw std::runtime_error("Manager initialization failed");
        checkQualityMetrics();
        std::vector<Result> results;
        if (!options.record.empty())
            std::cout << "Recording representative groups; use recording-disabled runs for timing "
                         "comparisons.\n";
        std::cout << "PDG collision/physics benchmark: " << options.bodies
                  << " bodies + colliders; owner=" << options.owner
                  << "; 0.01-second steps; no rendering; contact listeners enabled\n"
                  << "solver    scenario    mean ms   median ms   p95 ms   max ms\n";
        for (bool chipmunk : {false, true}) {
            if (options.solver != "both" && options.solver != (chipmunk ? "chipmunk" : "basic"))
                continue;
#ifndef PDG_USE_CHIPMUNK_PHYSICS
            if (chipmunk) {
                if (options.solver == "chipmunk")
                    throw std::runtime_error("This build has no Chipmunk solver");
                std::cout << "Chipmunk unavailable in this build; skipping.\n";
                continue;
            }
#endif
            for (const std::string scene :
                 {"sparse", "contacts", "approach", "stack", "chain", "pile"}) {
                const bool quality = scene == "stack" || scene == "chain" || scene == "pile";
                if (options.scenario != "all" && options.scenario != scene &&
                    !(options.scenario == "both" && (scene == "approach" || scene == "contacts")) &&
                    !(options.scenario == "quality" && quality))
                    continue;
                const auto r = quality               ? runQuality(options, chipmunk, scene)
                               : scene == "approach" ? runCirclePairs(options, chipmunk, false)
                               : scene == "contacts" ? runCirclePairs(options, chipmunk, true)
                                                     : runSparse(options, chipmunk);
                results.push_back(r);
                std::cout << std::fixed << std::setprecision(3) << std::setw(9) << r.solver << ' '
                          << std::setw(8) << r.scenario << ' ' << std::setw(10) << r.meanMs << ' '
                          << std::setw(11) << r.medianMs << ' ' << std::setw(8) << r.p95Ms << ' '
                          << std::setw(8) << r.maxMs << std::endl;
                if (scene == "contacts")
                    std::cout << "  released pairs=" << r.releasedPairs
                              << " still driven=" << r.drivenPairs << "\n";
                if (scene == "approach")
                    std::cout << "  collided pairs=" << r.collidedPairs << '/' << r.expectedHitPairs
                              << " expected eventual hits; miss pairs=" << r.missPairs
                              << "; maximum first-contact timing error=" << r.maxContactTimeError
                              << " s\n";
                if (quality)
                    std::cout << "  penetration=" << r.finalMaxPenetration
                              << " joint error=" << r.finalMaxJointError
                              << " tail RMS speed=" << r.tailRmsSpeed
                              << " sleeping=" << r.sleepingBodies << " escaped=" << r.escapedBodies
                              << " settled at=" << r.settledAtSeconds << " s (-1: unsettled)\n";
            }
        }
        if (!options.json.empty()) {
            std::ofstream out(options.json);
            if (!out)
                throw std::runtime_error("Cannot open JSON output");
            writeJson(out, results);
            if (!out)
                throw std::runtime_error("Cannot write JSON output");
        }
        if (!options.record.empty()) {
            std::ofstream out(options.record);
            if (!out)
                throw std::runtime_error("Cannot open playback output");
            out << std::setprecision(10) << "{\"version\":1,\"recordings\":[";
            for (size_t i = 0; i < recordings.size(); ++i) {
                if (i)
                    out << ',';
                recordings[i].write(out);
            }
            out << "]}\n";
            if (!out)
                throw std::runtime_error("Cannot write playback output");
        }
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Collider benchmark failed: " << e.what() << '\n';
        return 1;
    }
}
