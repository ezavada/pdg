#include "pdg_file_factory.h"
#include "pdg/sys/os.h"
#include "pdg/sys/log.h"
#include "pdg/sys/os.h"
#include "pdg/sys/image.h"
#include "pdg/sys/resource.h"
#include "pdg/sys/spritelayer.h"
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

PDGFileFactory::PDGFileFactory(SpriteLayer* layer) {
    mLayer = layer;
}

PDGFileFactory::~PDGFileFactory() {
    mLayer = nullptr;
}

SpriterEngine::SpriterFileDocumentWrapper* PDGFileFactory::newScmlDocumentWrapper() {
    // Use our custom PDG wrapper that supports ResourceManager loading
    return new pdg::PDGSpriterFileDocumentWrapper();
}

SpriterEngine::SpriterFileDocumentWrapper* PDGFileFactory::newSconDocumentWrapper() {
    // FIXME: For now, return nullptr - SpriterPlusPlus's JSON parsing is broken
    // We'll implement this later when we resolve the nlohmann-json issues
    return nullptr;
}

#ifndef PDG_NO_GUI
SpriterEngine::ImageFile* PDGFileFactory::newImageFile(const std::string& initialFilePath, 
                                                       SpriterEngine::point initialDefaultPivot, 
                                                       SpriterEngine::atlasdata atlasData) {   
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
        Port* port = mLayer->getSpritePort();
        return new pdg::PDGImageFile(initialFilePath, initialDefaultPivot, pdgImage, port);
    } else {
        DEBUG_ONLY(OS::_DOUT("PDGFileFactory: Failed to load image: %s", initialFilePath.c_str()));
        // Return a basic wrapper even if loading failed, so SpriterPlusPlus can continue
        return new SpriterEngine::ImageFile(initialFilePath, initialDefaultPivot);
    }
}

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
    if (filePath[0] == '/' || (filePath.length() > 2 && filePath[1] == ':' && (filePath[2] == '\\' || filePath[2] == '/'))) {
        return filePath;
    }
    
    // Otherwise, make it relative to the application resource directory
    std::string fullPath = OS::getApplicationResourceDirectory();
    fullPath += filePath;
    return OS::makeCanonicalPath(fullPath.c_str());
}

} // namespace pdg
