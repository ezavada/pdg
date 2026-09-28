#ifndef PDG_LAYER_SNAPSHOT_SCOPE_H_INCLUDED
#define PDG_LAYER_SNAPSHOT_SCOPE_H_INCLUDED
namespace pdg {
class ISerializer;
class SpriteLayer;
// A Layer record owns its cross-Sprite mount table. Its Sprite records may
// omit those links only while this exact writer is saving/sizing that Layer.
// Standalone Sprite saves must not silently lose attachment relationships.
class LayerSnapshotScope {
    inline static thread_local const LayerSnapshotScope* current = nullptr;
    const LayerSnapshotScope* previous;
    const ISerializer* writer;
    const SpriteLayer* layer;
public:
    LayerSnapshotScope(const ISerializer* out, const SpriteLayer* owner)
        : previous(current), writer(out), layer(owner) { current = this; }
    ~LayerSnapshotScope() { current = previous; }
    LayerSnapshotScope(const LayerSnapshotScope&) = delete;
    LayerSnapshotScope& operator=(const LayerSnapshotScope&) = delete;
    static bool contains(const ISerializer* out, const SpriteLayer* owner) {
        return owner && current && current->writer == out && current->layer == owner;
    }
};
}
#endif
