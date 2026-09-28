// c++ -std=c++17 test/lib/perf_measurement.test.cpp -o /tmp/pdg-perf-measurement && /tmp/pdg-perf-measurement
#include "../perf_tests/quick.h"
#include <cassert>
#include <iostream>
int main() {
    perf::Quick sampler;
    assert(sampler.load(4600, "polygon") == 18400);
    assert(sampler.load(31500, "bunnies") == 47250);
    assert(!sampler.tick(0));
    assert(!sampler.tick(999));
    assert(!sampler.tick(1000));
    for (int t = 1020; t <= 4000; t += 20) assert(sampler.tick(t) == (t == 4000));
    auto result = sampler.result(150, 100, 120);
    assert(result.averageFPS == 50);
    assert(result.estimatedCapacity == 125);
    assert(result.score == 150);
    assert(result.totalFrames == 150);
    assert(result.percentile99Ms == 20);
    sampler.reset();
    bool threw = false;
    try { sampler.result(150, 100, 120); } catch (const std::runtime_error&) { threw = true; }
    assert(threw);
    std::cout << "PASS: native perf sampling and weighted extrapolation\n";
}
