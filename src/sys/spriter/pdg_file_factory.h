#ifndef PDG_FILE_FACTORY_H_INCLUDED
#define PDG_FILE_FACTORY_H_INCLUDED

#include "spriterengine/override/spriterfiledocumentwrapper.h"
#include "spriterengine/override/filefactory.h"
#include "spriterengine/override/imagefile.h"
#include "spriterengine/override/soundfile.h"
#include "spriterengine/override/atlasfile.h"

namespace pdg {

class SpriteLayer;

class PDGFileFactory : public SpriterEngine::FileFactory {
public:
    PDGFileFactory(SpriteLayer* layer);
    virtual ~PDGFileFactory();

    // FileFactory interface
    virtual SpriterEngine::SpriterFileDocumentWrapper* newScmlDocumentWrapper() override;
    virtual SpriterEngine::SpriterFileDocumentWrapper* newSconDocumentWrapper() override;

  #ifndef PDG_NO_GUI
    virtual SpriterEngine::ImageFile* newImageFile(const std::string& initialFilePath, 
                                                  SpriterEngine::point initialDefaultPivot, 
                                                  SpriterEngine::atlasdata atlasData) override;
    virtual SpriterEngine::SoundFile* newSoundFile(const std::string& initialFilePath) override;
  #endif
    virtual SpriterEngine::AtlasFile* newAtlasFile(const std::string& initialFilePath) override;
private:
    // Helper methods
    std::string resolvePath(const std::string& filePath);
    SpriteLayer* mLayer;
};

} // namespace pdg

#endif // PDG_FILE_FACTORY_H_INCLUDED
