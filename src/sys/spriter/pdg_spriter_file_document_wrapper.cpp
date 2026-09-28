#include "pdg_spriter_file_document_wrapper.h"
#include "example/override/tinyxmlspriterfileelementwrapper.h"
#include <stdexcept>
namespace pdg {
PDGSpriterFileDocumentWrapper::PDGSpriterFileDocumentWrapper(std::shared_ptr<SpriterRigCatalog> catalog,
    std::shared_ptr<SpriterSnapshotAsset> asset) : mRigCatalog(std::move(catalog)),mAsset(std::move(asset)) {}
void PDGSpriterFileDocumentWrapper::loadFile(std::string fileName) {
    if(!mAsset->restored) {
        mAsset->path=fileName;
        try { mAsset->setDocument(SpriterSnapshotAsset::loadDocument(fileName)); }
        catch(...) { mAsset->setDocument(std::string());mDocument.Clear();return; }
    }
    if(mDocument.Parse(mAsset->getDocument().c_str())!=tinyxml2::XML_NO_ERROR ||
       !mDocument.FirstChildElement("spriter_data")) {
        if(mAsset->restored)throw std::runtime_error("Invalid Spriter XML document: "+fileName);
        mAsset->setDocument(std::string());mDocument.Clear();return;
    }
    if(mRigCatalog)mRigCatalog->read(*this,fileName);
}
SpriterEngine::SpriterFileElementWrapper* PDGSpriterFileDocumentWrapper::newElementWrapperFromFirstElement() {
    return new SpriterEngine::TinyXmlSpriterFileElementWrapper(mDocument.FirstChildElement());
}
SpriterEngine::SpriterFileElementWrapper* PDGSpriterFileDocumentWrapper::newElementWrapperFromFirstElement(const std::string& name) {
    return new SpriterEngine::TinyXmlSpriterFileElementWrapper(mDocument.FirstChildElement(name.c_str()));
}
}
