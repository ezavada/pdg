#ifndef PDG_FILE_FACTORY_H_INCLUDED
#define PDG_FILE_FACTORY_H_INCLUDED

#include "spriterengine/override/spriterfiledocumentwrapper.h"
#include "spriterengine/override/filefactory.h"
#include "spriterengine/override/imagefile.h"
#include "spriterengine/override/soundfile.h"
#include "spriterengine/override/atlasfile.h"
#include "pdg_spriter_pose.h"
#include "spriter-snapshot-asset.h"

namespace pdg {

class PDGFileFactory : public SpriterEngine::FileFactory {
public:
    PDGFileFactory();
    explicit PDGFileFactory(std::shared_ptr<SpriterSnapshotAsset> asset);
    SpriterSnapshotAsset& snapshotAsset() const { return *mAsset; }
    virtual ~PDGFileFactory();

    // FileFactory interface
    virtual SpriterEngine::SpriterFileDocumentWrapper* newScmlDocumentWrapper() override;
    virtual SpriterEngine::SpriterFileDocumentWrapper* newSconDocumentWrapper() override;

    virtual SpriterEngine::ImageFile* newImageFile(const std::string& initialFilePath, 
                                                  SpriterEngine::point initialDefaultPivot, 
                                                  SpriterEngine::atlasdata atlasData) override;
  #ifndef PDG_NO_GUI
    virtual SpriterEngine::SoundFile* newSoundFile(const std::string& initialFilePath) override;
  #endif
    virtual SpriterEngine::AtlasFile* newAtlasFile(const std::string& initialFilePath) override;
    std::shared_ptr<SpriterRigCatalog> rigCatalog() const { return mRigCatalog; }
private:
    std::shared_ptr<SpriterRigCatalog> mRigCatalog;
    std::shared_ptr<SpriterSnapshotAsset> mAsset;
    // Helper methods
    std::string resolvePath(const std::string& filePath);
};

} // namespace pdg

#endif // PDG_FILE_FACTORY_H_INCLUDED
