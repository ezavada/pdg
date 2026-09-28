// Included inside namespace pdg. Resolve mount links only after the complete
// ordered Sprite/Part collection exists; draw order need not be parent-first.
uint32 SpriteLayer::mountSnapshotSize(ISerializer* writer) const {
    uint32 count = 0, size = 0;
    for (auto* sprite = mFirstSprite; sprite; sprite = sprite->mNextSprite)
        for (auto* part : sprite->mParts) if (auto* child = part->mAttachedSprite) {
            if (child->mLayer != this || child->mAttachmentPart != part)
                throw std::runtime_error("Layer snapshot contains an invalid mount relationship");
            ++count;
            size += writer->sizeof_uint(sprite->iid) + writer->sizeof_uint(part->mId) + writer->sizeof_uint(child->iid);
            SnapshotWriter out(writer,false);
            const auto& t=part->mChildMountInverse;
            const SpatialTransform defaults;
            const bool changed=t.a!=defaults.a || t.b!=defaults.b || t.c!=defaults.c || t.d!=defaults.d || t.tx!=defaults.tx || t.ty!=defaults.ty;
            if(out.flag(changed)) size+=6*8;
            out.text(part->mAttachmentError);size+=out.size();
        }
    return writer->sizeof_uint(count) + size;
}
void SpriteLayer::serializeMounts(ISerializer* writer) const {
    uint32 count = 0;
    for (auto* sprite = mFirstSprite; sprite; sprite = sprite->mNextSprite)
        for (auto* part : sprite->mParts) if (part->mAttachedSprite) ++count;
    writer->serialize_uint(count);
    for (auto* sprite = mFirstSprite; sprite; sprite = sprite->mNextSprite)
        for (auto* part : sprite->mParts) if (auto* child = part->mAttachedSprite) {
            writer->serialize_uint(sprite->iid); writer->serialize_uint(part->mId); writer->serialize_uint(child->iid);
            const auto& t = part->mChildMountInverse;
            const SpatialTransform defaults;
            SnapshotWriter out(writer,true);
            if(out.flag(t.a!=defaults.a || t.b!=defaults.b || t.c!=defaults.c || t.d!=defaults.d || t.tx!=defaults.tx || t.ty!=defaults.ty))
                for (double value : {t.a, t.b, t.c, t.d, t.tx, t.ty}) writer->serialize_d(value);
            out.text(part->mAttachmentError);
        }
}
void SpriteLayer::deserializeMounts(IDeserializer* reader) {
    const auto count = reader->deserialize_uint();
    if (count > 1000000) throw std::runtime_error("Too many Sprite mounts in Layer snapshot");
    for (uint32 i = 0; i < count; ++i) {
        auto* host = findSpriteByInternalId(reader->deserialize_uint());
        const auto partId = reader->deserialize_uint();
        auto* child = findSpriteByInternalId(reader->deserialize_uint());
        auto* part = host ? host->getPart(partId) : nullptr;
        SpatialTransform inverse;
        SnapshotReader in(reader);
        if(in.flag()) for (double* value : {&inverse.a, &inverse.b, &inverse.c, &inverse.d, &inverse.tx, &inverse.ty}) {
            *value = reader->deserialize_d();
            if (!std::isfinite(*value)) throw std::runtime_error("Invalid Sprite mounting frame");
        }
        inverse.inverse(); // reject singular mounting frames before linking
        std::string error=in.text();
        if (!part || !child || part->mAttachedSprite || child->mAttachmentPart ||
            child == host || child->attachmentReaches(host))
            throw std::runtime_error("Missing, duplicate or cyclic Sprite mount in Layer snapshot");
        if (child->physics != PhysicsBody::NoPhysics && child->physics.getMode() != physicsBody_Kinematic)
            throw std::runtime_error("Rigid Sprite mount requires an absent or kinematic body");
        child->addRef(); part->mAttachedSprite = child; child->mAttachmentPart = part;
        part->mChildMountInverse = inverse; part->mAttachmentError = std::move(error);
    }
}
