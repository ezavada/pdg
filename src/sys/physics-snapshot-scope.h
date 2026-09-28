#ifndef PDG_PHYSICS_SNAPSHOT_SCOPE_H_INCLUDED
#define PDG_PHYSICS_SNAPSHOT_SCOPE_H_INCLUDED
#include <algorithm>
#include <vector>
namespace pdg {
class ISerializer;
class IDeserializer;
class PhysicsBody;
// Only a containing graph record may serialize bodies with external links.
// Keep this header independent of Sprite/Collider for the standalone body builds.
class PhysicsSnapshotScope {
    inline static thread_local const PhysicsSnapshotScope* current = nullptr;
    const PhysicsSnapshotScope* previous;
    const ISerializer* writer;
    std::vector<PhysicsBody*> owners;
public:
    PhysicsSnapshotScope(const ISerializer* out, std::vector<PhysicsBody*> bodies)
        : previous(current), writer(out), owners(std::move(bodies)) { current=this; }
    ~PhysicsSnapshotScope() { current=previous; }
    PhysicsSnapshotScope(const PhysicsSnapshotScope&)=delete;
    static bool contains(const ISerializer* out, const PhysicsBody* body) {
        for (auto* scope=current; scope; scope=scope->previous)
            if (scope->writer==out && std::find(scope->owners.begin(),scope->owners.end(),body)!=scope->owners.end()) return true;
        return false;
    }
};
class PhysicsGraphReadScope {
    inline static thread_local const IDeserializer* current = nullptr;
    const IDeserializer* previous;
public:
    explicit PhysicsGraphReadScope(const IDeserializer* reader) : previous(current) { current=reader; }
    ~PhysicsGraphReadScope() { current=previous; }
    PhysicsGraphReadScope(const PhysicsGraphReadScope&)=delete;
    static bool contains(const IDeserializer* reader) { return current==reader; }
};
}
#endif
