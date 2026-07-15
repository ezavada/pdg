#ifndef PDG_SPRITER_FILE_DOCUMENT_WRAPPER_H
#define PDG_SPRITER_FILE_DOCUMENT_WRAPPER_H

#include "example/override/tinyxmlspriterfiledocumentwrapper.h"
#include "pdg/sys/resource.h"

#ifdef PDG_DEBUG_SPRITER
  #define SPRITER_DEBUG_ONLY(x) DEBUG_ONLY(x)
#else
  #define SPRITER_DEBUG_ONLY(x)
#endif

namespace pdg {

class PDGSpriterFileDocumentWrapper : public SpriterEngine::TinyXmlSpriterFileDocumentWrapper {
public:
    PDGSpriterFileDocumentWrapper();
    
    void loadFile(std::string fileName) override;

private:
    bool tryLoadFromResource(const std::string& fileName);
};

} // namespace pdg

#endif // PDG_SPRITER_FILE_DOCUMENT_WRAPPER_H
