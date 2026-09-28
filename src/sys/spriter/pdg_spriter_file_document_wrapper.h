#ifndef PDG_SPRITER_FILE_DOCUMENT_WRAPPER_H
#define PDG_SPRITER_FILE_DOCUMENT_WRAPPER_H
#include "example/override/tinyxmlspriterfiledocumentwrapper.h"
#include "pdg_spriter_pose.h"
#include "spriter-snapshot-asset.h"
namespace pdg {
// Own the XML document so resource and snapshot loads can parse memory directly.
class PDGSpriterFileDocumentWrapper : public SpriterEngine::SpriterFileDocumentWrapper {
public:
    PDGSpriterFileDocumentWrapper(std::shared_ptr<SpriterRigCatalog> catalog,
        std::shared_ptr<SpriterSnapshotAsset> asset);
    void loadFile(std::string fileName) override;
private:
    SpriterEngine::SpriterFileElementWrapper* newElementWrapperFromFirstElement() override;
    SpriterEngine::SpriterFileElementWrapper* newElementWrapperFromFirstElement(const std::string&) override;
    tinyxml2::XMLDocument mDocument;
    std::shared_ptr<SpriterRigCatalog> mRigCatalog;
    std::shared_ptr<SpriterSnapshotAsset> mAsset;
};
}
#endif
