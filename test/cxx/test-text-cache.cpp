#include "textcache-opengl.h"
#include <cstdlib>
#include <stdexcept>

namespace {
class ProbeFont final : public pdg::FontImpl {
public:
    ProbeFont() : FontImpl(nullptr, "cache-probe", 1) {}
    int released = 0;
    void releaseFontMetrics(pdg::FontMetricsInfo* metrics) override {
        ++released; FontImpl::releaseFontMetrics(metrics);
    }
    pdg::FontMetricsInfo* getFontMetrics(int size, uint32 style) override {
        auto* result = static_cast<pdg::FontMetricsInfo*>(std::calloc(1, sizeof(pdg::FontMetricsInfo)));
        result->size = size; result->style = style;
        result->ascent = 10; result->descent = 3;
        return result;
    }
};
void check(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}
}
void testTextCache() {
    auto* font = new ProbeFont;
    font->addRef();
    {
        pdg::TextCache cache(3, 100);
        auto find = [&](const char* text, int len = 1, uint32 style = 0) {
            return cache.find(text, len, font, 12, style);
        };
        auto* a = find("a"); a->width = 7; a->measured = true;
        find("b")->width = 8;
        find("c")->width = 9;
        check(find("a") == a, "cache hits retain entry and promote recency");
        find("d");
        check(find("a")->width == 7, "recent entry survives eviction");
        check(find("b")->width == 0, "least recently used entry is evicted");
        check(cache.count() == 3, "entry limit enforced");
        check(find("abcd", 1) == find("a"), "partial string key uses byte length");
        check(find("a", 1, pdg::textStyle_Centered) == find("a"), "alignment shares raster and metrics");
        check(find("a", 1, pdg::textStyle_Bold) != find("a"), "raster styles have separate keys");
        auto* recent = find("z"); recent->textureBytes = 80;
        cache.uploaded(recent); cache.uploaded(recent);
        check(cache.bytes() == 80, "upload accounting is idempotent");
        auto* other = find("y"); other->textureBytes = 80;
        cache.uploaded(other);
        check(cache.count() == 1 && cache.bytes() == 80, "memory budget evicts older textures");
        cache.invalidateTextures();
        check(cache.bytes() == 0 && cache.count() == 1, "invalidation preserves entries and resets bytes");
        check(find("y") == other, "invalidation does not reinsert an existing entry");
        other->textureBytes = 50; cache.uploaded(other);
        check(cache.bytes() == 50 && cache.count() == 1, "reupload after invalidation remains owned once");
        cache.clear(); check(cache.count() == 0 && cache.bytes() == 0, "clear releases all entries");
    }
    for (int size = 1; size <= TEXT_INFO_CACHE_SIZE + 20; ++size) font->getFontAscent(size);
    check(font->released >= 20, "font metric eviction releases platform resources");
    font->release();
}
