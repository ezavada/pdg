#include "pdg_spriter_wrapper.h"
#include "pdg/sys/os.h"
#include "pdg/sys/log.h"
#include "spriterengine/global/settings.h"

namespace pdg {

PDGSpriterWrapper::PDGSpriterWrapper() 
    : mModel(nullptr), mFileFactory(nullptr), mObjectFactory(nullptr) {
    #ifndef PDG_NO_GUI
        mPort = nullptr;
    #endif
}

PDGSpriterWrapper::~PDGSpriterWrapper() {
    if (mModel) {
        delete mModel;
        mModel = nullptr;
    }
    if (mFileFactory) {
        delete mFileFactory;
        mFileFactory = nullptr;
    }
    if (mObjectFactory) {
        delete mObjectFactory;
        mObjectFactory = nullptr;
    }
}

bool PDGSpriterWrapper::loadFile(const std::string& filePath) {
    // Clean up any existing model
    if (mModel) {
        delete mModel;
        mModel = nullptr;
    }
    
    // Create factories
    if (!mFileFactory) {
        mFileFactory = new PDGFileFactory();
    }
    if (!mObjectFactory) {
        mObjectFactory = new PDGObjectFactory();
    }
    
    // Enable debug rendering
    SpriterEngine::Settings::renderDebugPoints = true;
    SpriterEngine::Settings::renderDebugBones = true;
    SpriterEngine::Settings::renderDebugBoxes = true;
    
    try {
        // Create the SpriterModel with our factories
        mModel = new SpriterEngine::SpriterModel(filePath, mFileFactory, mObjectFactory);
        return true;
    } catch (const std::exception& e) {
        OS::_DOUT("PDGSpriterWrapper: Failed to load file %s: %s", filePath.c_str(), e.what());
        return false;
    }
}

SpriterEngine::EntityInstance* PDGSpriterWrapper::createEntityInstance(const std::string& entityName) {
    if (!mModel) {
        OS::_DOUT("PDGSpriterWrapper: No model loaded");
        return nullptr;
    }
    
    try {
        SpriterEngine::EntityInstance* instance = mModel->getNewEntityInstance(entityName);
        DEBUG_ONLY(
            if (instance) {
                OS::_DOUT("PDGSpriterWrapper: Successfully created entity instance for %s", entityName.c_str());
            } else {
                OS::_DOUT("PDGSpriterWrapper: Failed to create entity instance for %s (returned null)", entityName.c_str());
            }
        )
        return instance;
    } catch (const std::exception& e) {
        DEBUG_ONLY(OS::_DOUT("PDGSpriterWrapper: Failed to create entity instance for %s: %s", entityName.c_str(), e.what()));
        return nullptr;
    }
}

SpriterEngine::EntityInstance* PDGSpriterWrapper::createEntityInstance(int entityId) {
    if (!mModel) {
        OS::_DOUT("PDGSpriterWrapper: No model loaded");
        return nullptr;
    }
    
    try {
        return mModel->getNewEntityInstance(entityId);
    } catch (const std::exception& e) {
        OS::_DOUT("PDGSpriterWrapper: Failed to create entity instance for ID %d: %s", entityId, e.what());
        return nullptr;
    }
}

#ifndef PDG_NO_GUI
void PDGSpriterWrapper::setPort(Port* port) {
    mPort = port;
    if (mObjectFactory) {
        mObjectFactory->setPort(port);
    }
    
    // Also set the port on all PDGImageFile objects in the model
    if (mModel && mPort) {
        // Get all image files from the model and set their ports
        // Since SpriterPlusPlus doesn't expose image files directly,
        // we'll iterate through all folders and files to find PDGImageFile objects
        for (int folderIndex = 0; folderIndex < mModel->folderCount(); folderIndex++) {
            SpriterEngine::Folder* folder = mModel->folder(folderIndex);
            if (folder) {
                for (int fileIndex = 0; fileIndex < folder->fileCount(); fileIndex++) {
                    SpriterEngine::File* file = folder->file(fileIndex);
                    if (file) {
                        // Check if this is a PDGImageFile
                        PDGImageFile* pdgFile = dynamic_cast<PDGImageFile*>(file);
                        if (pdgFile) {
                            pdgFile->setPort(port);
                        }
                    }
                }
            }
        }
    }
}
#endif

} // namespace pdg
