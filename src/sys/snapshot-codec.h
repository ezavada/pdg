#ifndef PDG_SNAPSHOT_CODEC_H_INCLUDED
#define PDG_SNAPSHOT_CODEC_H_INCLUDED

#include "pdg/sys/iserializer.h"
#include "pdg/sys/ideserializer.h"
#include <cmath>
#include <cstdint>
#include <limits>
#include <stdexcept>

namespace pdg {
// Internal snapshot fields. Sizing and emission follow the same traversal, but
// emission never advances the speculative sizeof cursor. Object identity and
// packed-bit bookkeeping remain the responsibility of ISerializer.
class SnapshotWriter {
    ISerializer* out;
    bool emit;
    uint64_t length = 0;
public:
    SnapshotWriter(ISerializer* writer, bool writing) : out(writer), emit(writing) {}
    uint32 size() const {
        if (length > UINT32_MAX) throw std::overflow_error("Snapshot record is too large");
        return uint32(length);
    }
    bool flag(bool value) {
        if (emit) out->serialize_bool(value); else length += out->sizeof_bool(value);
        return value;
    }
    void byte(uint8 value) { if (emit) out->serialize_1u(value); else ++length; }
    void integer(uint32 value) { if (emit) out->serialize_uint(value); else length += out->sizeof_uint(value); }
    void signedInteger(int32 value, int32 fallback = 0) {
        if (flag(value != fallback)) { if (emit) out->serialize_4(value); else length += 4; }
    }
    void optionalInteger(uint32 value, uint32 fallback = 0) { if (flag(value != fallback)) integer(value); }
    static bool different(double value, double fallback) {
        return value != fallback || (value == 0 && std::signbit(value) != std::signbit(fallback));
    }
    void real(double value, double fallback = 0) {
        if (flag(different(value, fallback))) { if (emit) out->serialize_d(value); else length += 8; }
    }
    void floating(float value, float fallback = 0) {
        if (flag(different(value, fallback))) { if (emit) out->serialize_f(value); else length += 4; }
    }
    void point(const Point& value) {
        if (flag(different(value.x, 0) || different(value.y, 0))) {
            if (emit) { out->serialize_f(value.x); out->serialize_f(value.y); } else length += 8;
        }
    }
    void visual(const Offset& value) {
        if (!std::isfinite(value.x) || !std::isfinite(value.y)) throw std::runtime_error("Non-finite visual coordinate");
        if (emit) out->serialize_offset(value); else length += out->sizeof_offset(value);
    }
    void text(const std::string& value) {
        if (flag(!value.empty())) { if (emit) out->serialize_string(value); else length += out->sizeof_str(value.c_str()); }
    }
    void object(const ISerializable* value) {
        if (flag(value != nullptr)) { if (emit) out->serialize_obj(value); else length += out->sizeof_obj(value); }
    }
};
class SnapshotReader {
    IDeserializer* in;
public:
    explicit SnapshotReader(IDeserializer* reader) : in(reader) {}
    bool flag() { return in->deserialize_bool(); }
    uint8 byte() { return in->deserialize_1u(); }
    uint32 integer() { return in->deserialize_uint(); }
    uint32 optionalInteger(uint32 fallback = 0) { return flag() ? integer() : fallback; }
    int32 signedInteger(int32 fallback = 0) { return flag() ? in->deserialize_4() : fallback; }
    double real(double fallback = 0) { return flag() ? in->deserialize_d() : fallback; }
    float floating(float fallback = 0) { return flag() ? in->deserialize_f() : fallback; }
    Point point() {
        Point value;
        if (flag()) { value.x=in->deserialize_f(); value.y=in->deserialize_f(); }
        return value;
    }
    Offset visual() {
        auto value=in->deserialize_offset();
        if (!std::isfinite(value.x) || !std::isfinite(value.y)) throw std::runtime_error("Non-finite visual coordinate");
        return value;
    }
    std::string text(uint32 limit = 1000000) {
        std::string value;
        if (flag()) {
            if (in->deserialize_strGetLen() > limit) throw std::runtime_error("Snapshot string exceeds limit");
            in->deserialize_string(value);
            if (value.find('\0') != std::string::npos) throw std::runtime_error("Invalid snapshot string");
        }
        return value;
    }
    ISerializable* object() { return flag() ? in->deserialize_obj() : nullptr; }
};
}
#endif
