#ifndef PDG_PHYSICS_GRAPH_SNAPSHOT_H_INCLUDED
#define PDG_PHYSICS_GRAPH_SNAPSHOT_H_INCLUDED
#include "physics-snapshot-scope.h"
#include "pdg/sys/platform.h"
namespace pdg {
class Sprite;
class SpriteLayer;
class Part;
class Collider;
class PhysicsConstraint;
// Internal scene component records. Owner indices are local to this record;
// public collider identities remain unique in the receiving process.
class PhysicsGraphSnapshot {
    struct Owner {
        Sprite* sprite;
        Part* part;
        PhysicsBody& body() const;
        Collider& collider() const;
        Collider& setupCollider() const;
    };
    std::vector<Owner> owners;
    void append(const Sprite& sprite);
    uint32 bodyId(const PhysicsBody* body) const;
    std::vector<PhysicsConstraint*> constraints() const;
    uint32 encode(ISerializer* writer, bool emit) const;
public:
    explicit PhysicsGraphSnapshot(const Sprite& sprite);
    explicit PhysicsGraphSnapshot(const SpriteLayer& layer);
    std::vector<PhysicsBody*> bodies() const;
    void validate() const;
    uint32 size(ISerializer* writer) const { return encode(writer,false); }
    void write(ISerializer* writer) const { encode(writer,true); }
    void read(IDeserializer* reader);
};
}
#endif
