// Isolated C++17 translation unit: Spriter's JSON header predates C++20.
#include "quick.h"
#include "../../deps/SpriterPlusPlus/nlohmann-json/json.hpp"
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
namespace perf {
using Json = nlohmann::json;
void Quick::init(int argc, const char** argv, const std::string& baselinePath) {
    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--quick") enabled = true;
        else if (arg == "--automated") throw std::runtime_error("Use --quick for short performance tests");
        else if (arg == "--warmup-seconds" || arg == "--sample-seconds" || arg == "--load-factor" || arg == "--output") {
            if (++i == argc) throw std::runtime_error(arg + " requires a value");
            if (arg == "--output") { output = argv[i]; continue; }
            std::string text = argv[i]; size_t end = 0;
            double value = std::stod(text, &end);
            if (end != text.size() || !std::isfinite(value) || value < (arg == "--warmup-seconds" ? 0 : .001) || value > (arg == "--load-factor" ? 10 : 60))
                throw std::runtime_error("Invalid " + arg);
            if (arg == "--warmup-seconds") warmup = value;
            else if (arg == "--sample-seconds") seconds = value;
            else factor = value;
        }
    }
    if (enabled) {
        // The engine reads this at draw time, so its initial window is included.
      #ifdef _WIN32
        if (_putenv_s("PDG_PERF_UNCAPPED", "1") != 0)
      #else
        if (setenv("PDG_PERF_UNCAPPED", "1", 1) != 0)
      #endif
            throw std::runtime_error("Cannot disable performance frame pacing");
        std::ifstream input(baselinePath);
        if (!input) throw std::runtime_error("Cannot read baseline: " + baselinePath);
        Json data; input >> data;
        if (data.count("bunnymarkScore")) baseline["bunnies"] = data["bunnymarkScore"].get<double>();
        else for (auto it = data["tests"].begin(); it != data["tests"].end(); ++it)
            baseline[it.key()] = it.value()["objectsAt60FPS"].get<double>();
        for (const auto& entry : baseline)
            if (!std::isfinite(entry.second) || entry.second <= 0) throw std::runtime_error("Invalid baseline capacity");
    }
}
void Quick::write(const std::string& name) {
    Json samples = Json::object(); long score = 0;
    for (const auto& entry : tests) {
        const auto& s = entry.second; score += s.score;
        samples[entry.first] = {{"synthetic", true}, {"fixedLoad", s.fixedLoad},
            {"loadFactor", s.fixedLoad / s.referenceLoad}, {"referenceLoad", s.referenceLoad},
            {"referenceScore", s.referenceScore}, {"targetFPS", s.targetFPS}, {"estimatedCapacity", s.estimatedCapacity},
            {"score", s.score}, {"averageFPS", s.averageFPS}, {"totalFrames", s.totalFrames},
            {"durationSeconds", s.durationSeconds}, {"warmupSeconds", s.warmupSeconds},
            {"requestedSampleSeconds", s.requestedSampleSeconds}, {"atOrAboveTarget", s.averageFPS >= s.targetFPS * .98},
            {"frameTime", {{"meanMs", s.meanMs}, {"minMs", s.minMs}, {"maxMs", s.maxMs},
                {"percentile95Ms", s.percentile95Ms}, {"percentile99Ms", s.percentile99Ms}}}};
    }
    std::time_t time = std::time(nullptr); char timestamp[32];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", std::gmtime(&time));
    const std::string markName = name == "cpp-bunnymark" ? "QuickBunnyMark" : "QuickPDGMark";
    Json result = {{"testName", markName}, {"benchmarkId", name}, {"language", "C++"},
        {"mode", "quick"}, {"synthetic", true}, {"timestamp", timestamp},
        {"measurement", "frame-start intervals; linear load/FPS extrapolation"},
        {"loadFactor", factor}, {"framePacing", "uncapped"}, {"requestedEngineFPS", nullptr},
        {"requestedSwapInterval", 0}, {"tests", samples}, {"compositeScore", score}};
    if (name == "cpp-bunnymark") result["bunnymarkScore"] = score;
    const auto filename = output.empty() ? "test/perf_tests/" + name + "_quick_results.json" : output;
    std::ofstream file(filename); file << result.dump(2) << '\n'; file.close();
    if (!file) throw std::runtime_error("Cannot write result: " + filename);
    std::cout << markName << " score: " << score << "\nResults: " << filename << std::endl;
}
}
