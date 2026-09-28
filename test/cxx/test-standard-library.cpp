// Regression coverage for the standard-library replacements in the engine.
#include "pdg/sys/os.h"
#include "pdg/sys/serializer.h"
#include "pdg/sys/deserializer.h"
#include "pdg/sys/timermanager.h"
#include "pdg/sys/initializer.h"
#include "internals.h"
#include "memblock.h"
#include "color-utils.h"
#include <array>
#include <bit>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <set>
#include <stdexcept>
#include <thread>
#include <vector>

namespace {
int assertions = 0;
void expect(bool ok, const char* message) {
    ++assertions;
    if (!ok) throw std::runtime_error(message);
}

std::unique_ptr<pdg::Deserializer> reader(pdg::Serializer& writer) {
    auto* copy = std::malloc(writer.getDataSize());
    if (!copy) throw std::bad_alloc();
    std::memcpy(copy, writer.getDataPtr(), writer.getDataSize());
    return std::make_unique<pdg::Deserializer>(copy, writer.getDataSize());
}

void cssColors() {
    using pdg::Color;
    Color color;
    expect(pdg::parseCssColor("#abc", color) && color == 0xaabbccu, "short hex expands each nibble");
    expect(pdg::parseCssColor("#AbC", color) && color == 0xaabbccu, "uppercase hex digits work");
    expect(pdg::parseCssColor("#123456", color) && color == 0x123456u, "long hex parses exactly");
    expect(pdg::parseCssColor("black", color) && color == 0u && color.alpha == 1, "black is a valid opaque color");
    expect(pdg::parseCssColor("aliceblue", color) && color == 0xf0f8ffu, "first named color remains available");
    expect(pdg::parseCssColor("yellowgreen", color) && color == 0x9acd32u, "last named color remains available");
    expect(Color::makeColor("#f00") == 0xff0000u, "public Color factory uses checked parser");
    expect(Color::makeColor(nullptr) == 0u, "null input has the default color");
    for (const char* invalid : {"", "#", "#0", "#00", "#0000", "#00000", "#0000000", "#ggg", "#12 345", "#ff00gg", "notacolor"}) {
        color = Color(1.f, 0.f, 0.f);
        expect(!pdg::parseCssColor(invalid, color) && color == 0xff0000u, "invalid CSS leaves output unchanged");
        expect(Color::makeColor(invalid) == 0u, "invalid CSS keeps the factory default");
    }
    expect(!pdg::parseCssColor(std::string_view("#abc\0junk", 9), color), "embedded null does not truncate input");
}

void randomNumbers() {
    // This must be the first RNG call: the old implementation deadlocked here.
    expect(pdg::OS::gameCriticalRandom() == 3499211612u, "unseeded RNG uses the historical default seed");
    for (unsigned long seed : {0ul, 1ul, 5489ul, 0xfffffffful}) {
        pdg::OS::srand(seed);
        std::mt19937 reference(seed);
        for (int i = 0; i < 2000; ++i)
            expect(pdg::OS::gameCriticalRandom() == reference(), "seeded MT sequence remains unchanged");
    }
}

void buffers() {
    pdg::MemBlock empty(0);
    expect(empty.getByte(0) == 0 && empty.getBytes(0, 20).empty(), "empty byte access is safe");
    char data[] = {'a', '\0', static_cast<char>(0xff), 'z'};
    pdg::MemBlock block(data, sizeof(data), false);
    expect(block.getByte(2) == 255 && block.getByte(4) == 0, "byte reads are unsigned and bounded");
    expect(block.getBytes(3, 4) == "z", "slice length is clamped to available bytes");
    expect(block.getBytes(2, std::numeric_limits<size_t>::max()).size() == 2, "slice length cannot overflow");
    expect(block.getBytes(std::numeric_limits<size_t>::max(), 1).empty(), "invalid slice start is empty");
    const auto first = block.getData();
    const auto second = block.getBytes(3, 1);
    expect(first == std::string(data, sizeof(data)) && second == "z", "results own independent strings");
}

void serialization() {
    const std::array<uint32, 5> floats = {0, 0x80000000u, 0x3f800000u, 0x7f800000u, 0x7fc12345u};
    const std::array<uint64, 5> doubles = {0, 0x8000000000000000ull, 0x3ff0000000000000ull,
        0x7ff0000000000000ull, 0x7ff8123456789abcull};
    pdg::Serializer writer;
    writer.setSendTags(false);
    for (auto bits : floats) writer.serialize_f(std::bit_cast<float>(bits));
    for (auto bits : doubles) writer.serialize_d(std::bit_cast<double>(bits));
    auto input = reader(writer);
    size_t offset = 0;
    for (auto bits : floats) {
        expect(std::bit_cast<uint32>(input->deserialize_f()) == bits, "float payload bits survive roundtrip");
        for (int shift = 24; shift >= 0; shift -= 8)
            expect(writer.getData()[offset++] == ((bits >> shift) & 255), "float wire bytes remain big endian");
    }
    for (auto bits : doubles) {
        expect(std::bit_cast<uint64>(input->deserialize_d()) == bits, "double payload bits survive roundtrip");
        for (int shift = 56; shift >= 0; shift -= 8)
            expect(writer.getData()[offset++] == ((bits >> shift) & 255), "double wire bytes remain big endian");
    }
    for (bool tagged : {false, true}) {
        pdg::Serializer growing;
        growing.setSendTags(tagged);
        growing.serialize_bool(true);
        std::vector<uint8> payload(100000, 0xa5), restored(payload.size());
        growing.serialize_mem(payload.data(), payload.size());
        growing.serialize_bool(false);
        growing.serialize_bool(true);
        growing.serialize_str("skip without an output buffer");
        growing.serialize_4u(1234);
        auto copy = reader(growing);
        expect(copy->deserialize_bool(), "first packed boolean survives reallocation");
        expect(copy->deserialize_mem(restored.data(), restored.size()) == restored.size() && restored == payload,
            "large payload survives vector growth");
        expect(!copy->deserialize_bool() && copy->deserialize_bool(), "later bits update the original packed byte");
        expect(copy->deserialize_str(nullptr, 0) == 0 && copy->deserialize_4u() == 1234,
            "zero-size string destination skips data without writing");
    }
    // The stream tag and memory tag must fit as well as a near-block-sized payload.
    pdg::Serializer boundary;
    std::vector<uint8> payload(65536 + 1015, 7), restored(payload.size());
    boundary.serialize_mem(payload.data(), payload.size());
    auto copy = reader(boundary);
    expect(copy->deserialize_mem(restored.data(), restored.size()) == restored.size() && restored == payload,
        "first tagged payload handles an allocation boundary");
}

struct TestTimers : pdg::TimerManager {};
void timing() {
    static_assert(sizeof(ms_time) == 8 && sizeof(ms_delta) == 8);
    const auto before = pdg::OS::getMilliseconds();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    expect(pdg::OS::getMilliseconds() >= before + 1, "elapsed clock advances monotonically");
    TestTimers timers;
    constexpr ms_delta delay = 1ll << 34;
    timers.startTimer(1, delay, true);
    expect(timers.msTillNextFire() > (1ll << 33), "timer deadline exceeds 32-bit milliseconds");
    timers.pauseTimer(1);
    expect(timers.msTillNextFire() == std::numeric_limits<ms_delta>::max(), "paused timers do not schedule a wakeup");
    timers.cancelTimer(1);
}

struct Files {
    std::filesystem::path root;
    std::string savedDirectory = pdg::OS::getApplicationDirectory();
    Files() : root(std::filesystem::temp_directory_path() /
        ("pdg-cxx20-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()))) {
        if (!std::filesystem::create_directory(root)) throw std::runtime_error("temporary directory exists");
        root = std::filesystem::canonical(root);
        pdg::os_setApplicationDirectory(root.string().c_str());
    }
    ~Files() {
        pdg::os_setApplicationDirectory(savedDirectory.c_str());
        std::error_code ignored;
        std::filesystem::remove_all(root, ignored);
    }
};
void filesystem() {
    using pdg::OS;
    Files files;
    std::filesystem::create_directory(files.root / "folder");
    std::ofstream(files.root / "one.txt") << "one";
    std::ofstream(files.root / "two.txt") << "two";
    expect(OS::makeCanonicalPath("folder/../one.txt") == (files.root / "one.txt").string(),
        "relative paths use the application directory");
    expect(OS::makeCanonicalPath("folder/../missing/file", false) == (files.root / "missing/file").string(),
        "lexical normalization works for nonexistent paths");
    pdg::FindDataT found{};
    std::set<std::string> names;
    bool more = OS::findFirst("*.txt", found);
    while (more) {
        expect(!found.isDirectory, "file match is not a directory");
        names.emplace(found.nodeName);
        more = OS::findNext(found);
    }
    OS::findClose(found);
    OS::findClose(found);
    expect(names == std::set<std::string>{"one.txt", "two.txt"}, "wildcard iteration returns each match");
    expect(!OS::findFirst("missing/*.txt", found), "missing directory yields no matches");
    OS::findClose(found);
    expect(OS::findFirst("folder", found) && found.isDirectory, "directory flag is preserved");
    OS::findClose(found);
    const auto source = (files.root / "one.txt").string(), destination = (files.root / "renamed.txt").string();
    expect(OS::renameFile(source.c_str(), destination.c_str()), "rename reports success");
    expect(!OS::renameFile(source.c_str(), destination.c_str()), "rename reports a missing source");
    expect(OS::deleteFile(destination.c_str()) && !OS::deleteFile(destination.c_str()), "delete reports success then failure");
    std::error_code error;
    std::filesystem::create_directory_symlink("folder", files.root / "link", error);
    if (!error) {
        expect(OS::makeCanonicalPath("link/missing") == (files.root / "folder/missing").string(),
            "relative symlinks resolve before a nonexistent tail");
        expect(OS::makeCanonicalPath("link/missing", false) == (files.root / "link/missing").string(),
            "symlink resolution can be disabled");
    }
}
}

namespace pdg {
bool Initializer::allowHorizontalOrientation() noexcept { return true; }
bool Initializer::allowVerticalOrientation() noexcept { return true; }
const char* Initializer::getAppName(bool) noexcept { return "PDG Standard Library Tests"; }
const char* Initializer::getMainResourceFileName() noexcept { return nullptr; }
bool Initializer::installGlobalHandlers() noexcept { return false; }
bool Initializer::getGraphicsEnvironmentDimensions(Rect, Rect, long& width, long& height, uint8& depth) noexcept {
    width = height = 1; depth = 32; return false;
}
}
int main() {
    try {
        randomNumbers(); buffers(); serialization(); timing(); filesystem(); cssColors();
        std::cout << "Standard library: " << assertions << " assertions passed\n";
        return EXIT_SUCCESS;
    } catch (const std::exception& error) {
        std::cerr << "Standard library regression: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
