#include "pdg_spriter_file_document_wrapper.h"
#include "pdg/sys/os.h"
#include "pdg/sys/log.h"
#include <fstream>
#include <cstdio>
#include <string>

#ifdef _WIN32
    #include <process.h>
    #define getpid _getpid
#else
    #include <unistd.h>
#endif

namespace pdg {

PDGSpriterFileDocumentWrapper::PDGSpriterFileDocumentWrapper() {
    // Initialize the base class
}

void PDGSpriterFileDocumentWrapper::loadFile(std::string fileName) {
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGSpriterFileDocumentWrapper: Attempting to load file: %s", fileName.c_str()));
    
    // First try to load from ResourceManager
    if (tryLoadFromResource(fileName)) {
        SPRITER_DEBUG_ONLY(OS::_DOUT("PDGSpriterFileDocumentWrapper: Successfully loaded from resource: %s", fileName.c_str()));
        return;
    }
    
    // Fall back to file system loading using the base class method
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGSpriterFileDocumentWrapper: Falling back to file system: %s", fileName.c_str()));
    SpriterEngine::TinyXmlSpriterFileDocumentWrapper::loadFile(fileName);
}

bool PDGSpriterFileDocumentWrapper::tryLoadFromResource(const std::string& fileName) {
    try {
        ResourceManager* resMgr = ResourceManager::getSingletonInstance();
        if (!resMgr) {
            SPRITER_DEBUG_ONLY(OS::_DOUT("PDGSpriterFileDocumentWrapper: No ResourceManager instance"));
            return false;
        }
    
        // Check if ResourceManager has any files open
        std::string resourcePaths = resMgr->getResourcePaths();
        if (resourcePaths.empty()) {
            SPRITER_DEBUG_ONLY(OS::_DOUT("PDGSpriterFileDocumentWrapper: No resource files open"));
            return false;
        }
        
        // Check if the resource exists
        size_t resourceSize = resMgr->getResourceSize(fileName.c_str());
        if (resourceSize == 0) {
            SPRITER_DEBUG_ONLY(OS::_DOUT("PDGSpriterFileDocumentWrapper: Resource not found: %s", fileName.c_str()));
            return false;
        }
        
        SPRITER_DEBUG_ONLY(OS::_DOUT("PDGSpriterFileDocumentWrapper: Found resource, size: %zu bytes", resourceSize));
        
        // Load the resource into memory
        char* buffer = new char[resourceSize];
        bool success = resMgr->getResource(fileName.c_str(), buffer, resourceSize);
        
        if (!success) {
            SPRITER_DEBUG_ONLY(OS::_DOUT("PDGSpriterFileDocumentWrapper: Failed to load resource data: %s", fileName.c_str()));
            delete[] buffer;
            return false;
        }
        
        // Since we can't access the base class's private doc member,
        // we'll create a temporary file and let the base class load it
        // This is not ideal but it's the safest approach
        #ifdef _WIN32
            const char* tempDir = getenv("TEMP");
            if (!tempDir) tempDir = getenv("TMP");
            if (!tempDir) tempDir = ".";
            std::string tempFileName = std::string(tempDir) + "\\pdg_spriter_temp_" + std::to_string(getpid()) + ".scml";
        #else
            std::string tempFileName = "/tmp/pdg_spriter_temp_" + std::to_string(getpid()) + ".scml";
        #endif
        
        // Write the resource data to a temporary file
        std::ofstream tempFile(tempFileName, std::ios::binary);
        if (!tempFile.is_open()) {
            SPRITER_DEBUG_ONLY(OS::_DOUT("PDGSpriterFileDocumentWrapper: Failed to create temp file: %s", tempFileName.c_str()));
            delete[] buffer;
            return false;
        }
        
        tempFile.write(buffer, resourceSize);
        tempFile.close();
        delete[] buffer;
        
        // Load the temporary file using the base class method
        SpriterEngine::TinyXmlSpriterFileDocumentWrapper::loadFile(tempFileName);
        
        // Clean up the temporary file
        std::remove(tempFileName.c_str());
        
        return true;
    } catch (...) {
        SPRITER_DEBUG_ONLY(OS::_DOUT("PDGSpriterFileDocumentWrapper: Exception in tryLoadFromResource"));
        return false;
    }
}


} // namespace pdg
