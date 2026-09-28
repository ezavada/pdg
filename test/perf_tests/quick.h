#ifndef PDG_PERF_QUICK_H
#define PDG_PERF_QUICK_H
#include <chrono>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

namespace perf {
struct Sample {
    int fixedLoad;
    double referenceLoad, referenceScore, targetFPS, estimatedCapacity;
    long score;
    double averageFPS;
    size_t totalFrames;
    double durationSeconds, warmupSeconds, requestedSampleSeconds;
    double meanMs, minMs, maxMs, percentile95Ms, percentile99Ms;
};
struct Quick {
    bool enabled = false;
    double warmup = 1, seconds = 3, factor = 1.5;
    std::string output;
    std::map<std::string, double> baseline;
    std::map<std::string, Sample> tests;
    double start = -1, previous = -1, elapsed = 0;
    std::vector<double> frames;
    void init(int argc, const char** argv, const std::string& baselinePath);
    void write(const std::string& name);
    static double now() {
        return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }
    void reset() { start = previous = -1; elapsed = 0; frames.clear(); }
    bool tick(double time = now()) {
        if (start < 0) start = time;
        if (time - start < warmup * 1000) return false;
        if (previous >= 0) {
            if (time <= previous) throw std::runtime_error("Non-increasing performance clock");
            frames.push_back(time - previous); elapsed += time - previous;
        }
        previous = time;
        return elapsed >= seconds * 1000 && frames.size() >= 2;
    }
    Sample result(int load, double referenceLoad, double referenceScore, double targetFPS = 60) {
        if (frames.size() < 2 || elapsed <= 0) throw std::runtime_error("Incomplete performance sample");
        double fps = frames.size() * 1000 / elapsed;
        auto sorted = frames; std::sort(sorted.begin(), sorted.end());
        return {load, referenceLoad, referenceScore, targetFPS, load * fps / targetFPS,
            std::lround(referenceScore * load / referenceLoad * fps / targetFPS), fps,
            frames.size(), elapsed / 1000, warmup, seconds, elapsed / frames.size(),
            sorted.front(), sorted.back(), sorted[size_t(std::ceil(sorted.size() * .95)) - 1],
            sorted[size_t(std::ceil(sorted.size() * .99)) - 1]};
    }
    int load(double reference, const std::string& test = "") const {
        return int(std::ceil(reference * factor * (test == "polygon" ? 8.0 / 3.0 : 1.0)));
    }
};
}
#endif
