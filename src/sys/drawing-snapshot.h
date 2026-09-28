#ifndef PDG_DRAWING_SNAPSHOT_H_INCLUDED
#define PDG_DRAWING_SNAPSHOT_H_INCLUDED
#include "pdg/sys/global_types.h"
#include <memory>
namespace pdg {
class Drawing;
class ISerializer;
class IDeserializer;
// Internal graph records preserve editable Drawing storage identity. Part/Sprite
// records own the public save/load entry points and resource policy.
uint32 drawingSerializedSize(const Drawing* drawing, ISerializer* writer);
void serializeDrawing(const Drawing* drawing, ISerializer* writer);
std::shared_ptr<Drawing> deserializeDrawing(IDeserializer* reader);
}
#endif
