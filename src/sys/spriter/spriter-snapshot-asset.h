#ifndef PDG_SPRITER_SNAPSHOT_ASSET_H_INCLUDED
#define PDG_SPRITER_SNAPSHOT_ASSET_H_INCLUDED
#include "pdg/sys/serializable.h"
#include <map>
#include <memory>
#include <string>
namespace SpriterEngine { class SpriterModel; }
namespace pdg {
class Image;
// The imported document and its shared images form one serializable resource.
// Models own factories which retain this resource; the reverse cache is weak.
class SpriterSnapshotAsset : public Serializable<SpriterSnapshotAsset> {
public:
    uint32 getMyClassTag() const override { return 0xFFFFFF0A; }
    uint32 getSerializedSize(ISerializer*) const override;
    void serialize(ISerializer*) const override;
    void deserialize(IDeserializer*) override;
    static std::shared_ptr<SpriterSnapshotAsset> share(SpriterSnapshotAsset*);
    static void registerType();
    static std::string loadDocument(const std::string& path);
    std::shared_ptr<SpriterEngine::SpriterModel> model();
    void validate() const;
    const std::string& getDocument() const { return mDocument; }
    void setDocument(std::string document);
    std::string path;
    std::map<std::string,std::shared_ptr<Image>> images;
    bool restored = false;
private:
    const std::string& encodedDocument() const;
    std::string mDocument;
    mutable std::string mCompressedDocument;
    mutable bool mCompressionReady = false;
    std::weak_ptr<SpriterEngine::SpriterModel> mModel;
};
}
#endif
