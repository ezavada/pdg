#include "../snapshot-codec.h"
#include "pdg_file_factory.h"
#include "pdg/sys/os.h"
#include "pdg/sys/log.h"
#include "pdg/sys/os.h"
#include "pdg/sys/image.h"
#include "pdg/sys/resource.h"
#include "pdg/sys/iserializer.h"
#include "pdg/sys/ideserializer.h"
#include "pdg_object_factory.h"
#include "spriterengine/model/spritermodel.h"
#include <fstream>
#include <zlib.h>
#include <stdexcept>
#include "spriterengine/override/spriterfiledocumentwrapper.h"

#ifndef PDG_NO_GUI
  #include "pdg/sys/graphics.h"
  #include "pdg_image_file.h"
  #include "spriterengine/override/imagefile.h"
  #include "spriterengine/override/soundfile.h"
#endif // !PDG_NO_GUI

#include "spriterengine/override/atlasfile.h"

// Use our custom PDG document wrapper that supports ResourceManager
#include "pdg_spriter_file_document_wrapper.h"

#ifdef PDG_DEBUG_SPRITER
  #define SPRITER_DEBUG_ONLY(x) DEBUG_ONLY(x)
#else
  #define SPRITER_DEBUG_ONLY(x)
#endif


namespace pdg {

#include "spriter-snapshot-asset.inc"
PDGFileFactory::PDGFileFactory() : PDGFileFactory(SpriterSnapshotAsset::share(new SpriterSnapshotAsset())) {}
PDGFileFactory::PDGFileFactory(std::shared_ptr<SpriterSnapshotAsset> asset)
    : mRigCatalog(std::make_shared<SpriterRigCatalog>()),mAsset(std::move(asset)) {}
PDGFileFactory::~PDGFileFactory() = default;

SpriterEngine::SpriterFileDocumentWrapper* PDGFileFactory::newScmlDocumentWrapper() {
    // Use our custom PDG wrapper that supports ResourceManager loading
    return new pdg::PDGSpriterFileDocumentWrapper(mRigCatalog,mAsset);
}

SpriterEngine::SpriterFileDocumentWrapper* PDGFileFactory::newSconDocumentWrapper() {
    // FIXME: For now, return nullptr - SpriterPlusPlus's JSON parsing is broken
    // We'll implement this later when we resolve the nlohmann-json issues
    return nullptr;
}

SpriterEngine::ImageFile* PDGFileFactory::newImageFile(const std::string& initialFilePath, 
                                                       SpriterEngine::point initialDefaultPivot, 
                                                       SpriterEngine::atlasdata atlasData) {   
    if(mAsset->restored) {
        const auto found=mAsset->images.find(initialFilePath);
        if(found==mAsset->images.end()||!found->second)throw std::runtime_error("Missing saved Spriter image: "+initialFilePath);
#ifndef PDG_NO_GUI
        return new PDGImageFile(initialFilePath,initialDefaultPivot,found->second.get());
#else
        return new SpriterEngine::ImageFile(initialFilePath,initialDefaultPivot);
#endif
    }
    // Try to load the image using PDG's loading methods
    Image* pdgImage = nullptr;
    
    // First, try to load as a resource (if ResourceManager has files open)
    ResourceManager* resMgr = ResourceManager::getSingletonInstance();
    if (resMgr) {
        // Check if ResourceManager has any files open before trying to use it
        std::string resourcePaths = resMgr->getResourcePaths();
        if (!resourcePaths.empty()) {
            try {
                pdgImage = resMgr->getImage(initialFilePath.c_str());
                if (pdgImage) {
                    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGFileFactory: Loaded image as resource: %s", initialFilePath.c_str()));
                }
            } catch (...) {
                // ResourceManager might throw if no files are open, ignore and try direct file loading
            }
        }
    }
    
    // If resource loading failed, try direct file loading
    if (!pdgImage) {
        std::string resolvedPath = resolvePath(initialFilePath);
        try {
            pdgImage = Image::createImageFromFile(resolvedPath.c_str());
            if (pdgImage) {
                SPRITER_DEBUG_ONLY(OS::_DOUT("PDGFileFactory: Loaded image from file: %s", resolvedPath.c_str()));
            }
        } catch (...) {
            DEBUG_ONLY(OS::_DOUT("PDGFileFactory: Failed to load image from file: %s", resolvedPath.c_str()));
        }
    }
    
    if (pdgImage) {
        // Create a PDG-specific ImageFile wrapper that holds the actual PDG Image
        SPRITER_DEBUG_ONLY(OS::_DOUT("PDGFileFactory: Successfully loaded image: %s (pivot: %.2f, %.2f)", 
                  initialFilePath.c_str(), initialDefaultPivot.x, initialDefaultPivot.y);)
        
        // Create a proper PDGImageFile wrapper that wraps the PDG Image
        auto image = std::unique_ptr<Image, void(*)(Image*)>(pdgImage, [](Image* p) { p->release(); });
        pdgImage->addRef();mAsset->images[initialFilePath]=std::shared_ptr<Image>(pdgImage,[](Image* p){p->release();});
#ifndef PDG_NO_GUI
        return new pdg::PDGImageFile(initialFilePath, initialDefaultPivot, image.get());
#else
        return new SpriterEngine::ImageFile(initialFilePath,initialDefaultPivot);
#endif
    } else {
        DEBUG_ONLY(OS::_DOUT("PDGFileFactory: Failed to load image: %s", initialFilePath.c_str()));
        // Return a basic wrapper even if loading failed, so SpriterPlusPlus can continue
        mAsset->images[initialFilePath]=nullptr;
        return new SpriterEngine::ImageFile(initialFilePath, initialDefaultPivot);
    }
}

#ifndef PDG_NO_GUI
SpriterEngine::SoundFile* PDGFileFactory::newSoundFile(const std::string& initialFilePath) {
    std::string resolvedPath = resolvePath(initialFilePath);
    
    // For now, just log that we're trying to load a sound but don't actually load it
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGFileFactory: Would load sound: %s", resolvedPath.c_str()));
    
    // Create a basic SoundFile wrapper that doesn't actually load the sound
    // This is a temporary solution until we implement proper PDG sound integration
    return new SpriterEngine::SoundFile(initialFilePath);
}
#endif // !PDG_NO_GUI

SpriterEngine::AtlasFile* PDGFileFactory::newAtlasFile(const std::string& initialFilePath) {
    // For now, return nullptr as we're not implementing atlas support yet
    return nullptr;
}

std::string PDGFileFactory::resolvePath(const std::string& filePath) {
    // If it's already an absolute path, return as is
    if (filePath.empty()) return filePath;
    if (filePath[0] == '/' || (filePath.length() > 2 && filePath[1] == ':' && (filePath[2] == '\\' || filePath[2] == '/'))) {
        return filePath;
    }
    
    // Otherwise, make it relative to the application resource directory
    std::string fullPath = OS::getApplicationResourceDirectory();
    fullPath += filePath;
    return OS::makeCanonicalPath(fullPath.c_str());
}

} // namespace pdg
