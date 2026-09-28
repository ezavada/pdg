// Included by pdg_file_factory.cpp inside namespace pdg.
namespace {
constexpr uint32 spriterDocumentLimit = 64 * 1024 * 1024;
constexpr uint8 spriterAssetFormat = 3;
enum SpriterDocumentEncoding : uint8 { spriterDocument_Raw = 0, spriterDocument_Deflate = 1 };
uint64_t spriterDocumentFingerprint(const std::string& bytes) {
    uint64_t hash=14695981039346656037ULL;
    for(unsigned char value:bytes){hash^=value;hash*=1099511628211ULL;}return hash;
}
std::string inflateSpriterDocument(std::string& payload, uint32 length) {
    std::string document(length, '\0');
    z_stream stream = z_stream();
    stream.next_in = reinterpret_cast<Bytef*>(payload.data());
    stream.avail_in = static_cast<uInt>(payload.size());
    stream.next_out = reinterpret_cast<Bytef*>(document.data());
    stream.avail_out = length;
    if (inflateInit(&stream) != Z_OK)
        throw std::runtime_error("Cannot initialize Spriter XML decompression");
    const int status = inflate(&stream, Z_FINISH);
    const bool complete = status == Z_STREAM_END && stream.total_out == length && stream.avail_in == 0;
    inflateEnd(&stream);
    if (!complete) throw std::runtime_error("Invalid compressed Spriter XML payload or length");
    return document;
}
}
void SpriterSnapshotAsset::registerType() {
    static const bool registered=[] { IDeserializer::registerClass<SpriterSnapshotAsset>();return true; }();
    (void)registered;
}
std::shared_ptr<SpriterSnapshotAsset> SpriterSnapshotAsset::share(SpriterSnapshotAsset* asset) {
    registerType();asset->addRef();return {asset,[](SpriterSnapshotAsset* p){p->release();}};
}
std::string SpriterSnapshotAsset::loadDocument(const std::string& path) {
    auto* resources=ResourceManager::getSingletonInstance();
    try { if(resources && !resources->getResourcePaths().empty()) {
        const auto size=resources->getResourceSize(path.c_str());
        if(size>spriterDocumentLimit)throw std::runtime_error("Spriter document exceeds snapshot size limit");
        if(size) {
            std::string data(size,'\0');
            if(resources->getResource(path.c_str(),&data[0],size))return data;
        }
    }
    } catch(const std::exception&) { /* Absolute paths can be outside an open resource root. */ }
    std::ifstream file(path,std::ios::binary|std::ios::ate);
    if(!file)throw std::runtime_error("Missing Spriter document: "+path);
    const auto size=file.tellg();
    if(size<=0||size>spriterDocumentLimit)throw std::runtime_error("Invalid Spriter document size: "+path);
    std::string data(static_cast<size_t>(size),'\0');file.seekg(0);
    if(!file.read(&data[0],size))throw std::runtime_error("Cannot read Spriter document: "+path);
    return data;
}
void SpriterSnapshotAsset::setDocument(std::string document) {
    mDocument = std::move(document);
    mCompressedDocument.clear();
    mCompressionReady = false;
    mModel.reset();
}
const std::string& SpriterSnapshotAsset::encodedDocument() const {
    if (!mCompressionReady) {
        // Only retain compression when it wins. A same-size output buffer bounds
        // the temporary allocation; Z_BUF_ERROR means raw storage is preferable.
        std::string compressed(mDocument.size(), '\0');
        uLongf length = static_cast<uLongf>(compressed.size());
        const int status = compress2(reinterpret_cast<Bytef*>(compressed.data()), &length,
            reinterpret_cast<const Bytef*>(mDocument.data()), static_cast<uLong>(mDocument.size()), 6);
        if (status != Z_OK && status != Z_BUF_ERROR)
            throw std::runtime_error("Cannot compress Spriter XML document");
        if (status == Z_OK && length < mDocument.size()) {
            compressed.resize(length);
            // Release the original-size scratch allocation when caching the bytes.
            mCompressedDocument.assign(compressed.data(), compressed.size());
        }
        mCompressionReady = true;
    }
    return mCompressedDocument.empty() ? mDocument : mCompressedDocument;
}
void SpriterSnapshotAsset::validate() const {
    if(path.empty()||mDocument.empty()||mDocument.find('\0')!=std::string::npos)
        throw std::runtime_error("Imported animation has no supported source document");
    if(mDocument.size()>spriterDocumentLimit)
        throw std::runtime_error("Spriter document exceeds snapshot size limit");
    for(const auto& item:images)if(!item.second)
        throw std::runtime_error("Missing Spriter image: "+item.first);
}
uint32 SpriterSnapshotAsset::getSerializedSize(ISerializer* writer) const {
    validate();uint64_t size=1+writer->sizeof_bool(writer->getResourceMode()==serialization_ExternalReferences);
    size+=writer->sizeof_str(path.c_str())+8+writer->sizeof_uint(images.size());
    if(writer->getResourceMode()==serialization_Complete) {
        const auto& payload=encodedDocument();
        size+=1+writer->sizeof_uint(mDocument.size())+writer->sizeof_mem(payload.data(),payload.size());
    }
    for(const auto& item:images)size+=writer->sizeof_str(item.first.c_str())+writer->sizeof_obj(item.second.get());
    if(size>UINT32_MAX)throw std::overflow_error("Imported animation snapshot is too large");
    return uint32(size);
}
void SpriterSnapshotAsset::serialize(ISerializer* writer) const {
    validate();const bool external=writer->getResourceMode()==serialization_ExternalReferences;
    writer->serialize_1u(spriterAssetFormat);
    writer->serialize_bool(external);writer->serialize_string(path);
    const auto hash=spriterDocumentFingerprint(mDocument);writer->serialize_4u(hash>>32);writer->serialize_4u(hash);
    if(!external) {
        const auto& payload=encodedDocument();
        writer->serialize_1u(mCompressedDocument.empty()?spriterDocument_Raw:spriterDocument_Deflate);
        writer->serialize_uint(mDocument.size());writer->serialize_mem(payload.data(),payload.size());
    }
    writer->serialize_uint(images.size());
    for(const auto& item:images){writer->serialize_string(item.first);writer->serialize_obj(item.second.get());}
}
void SpriterSnapshotAsset::deserialize(IDeserializer* reader) {
    if(reader->deserialize_1u()!=spriterAssetFormat)throw std::runtime_error("Unsupported imported animation asset format");
    const bool external=reader->deserialize_bool();
    auto string=[&](uint32 limit){if(reader->deserialize_strGetLen()>limit)throw std::runtime_error("Imported animation string too long");std::string s;reader->deserialize_string(s);if(s.find('\0')!=std::string::npos)throw std::runtime_error("Invalid imported animation string");return s;};
    path=string(1000000);const uint64_t hi=reader->deserialize_4u(),lo=reader->deserialize_4u();
    if(external) setDocument(loadDocument(path));
    else {
        const auto encoding=reader->deserialize_1u();
        const auto length=reader->deserialize_uint(),stored=reader->deserialize_memGetLen();
        if(encoding>spriterDocument_Deflate || !length || length>spriterDocumentLimit ||
           !stored || stored>spriterDocumentLimit || (encoding==spriterDocument_Raw && stored!=length))
            throw std::runtime_error("Invalid Spriter XML encoding or size");
        std::string payload(stored,'\0');
        if(reader->deserialize_mem(payload.data(),stored)!=stored)throw std::runtime_error("Truncated Spriter XML payload");
        if(encoding==spriterDocument_Deflate) {
            setDocument(inflateSpriterDocument(payload,length));
            if(payload.size()<mDocument.size())mCompressedDocument=std::move(payload);
        } else setDocument(std::move(payload));
        mCompressionReady=true;
    }
    if(spriterDocumentFingerprint(mDocument)!=((hi<<32)|lo))throw std::runtime_error("Spriter document changed since saving: "+path);
    const auto count=reader->deserialize_uint();if(count>1000000)throw std::runtime_error("Too many Spriter image resources");
    images.clear();
    for(uint32 i=0;i<count;++i) {
        auto name=string(1000000);auto* object=reader->deserialize_obj();auto* image=dynamic_cast<Image*>(object);
        if(!image){if(object)object->release();throw std::runtime_error("Missing Spriter image resource: "+name);}
        auto retained=std::shared_ptr<Image>(image,[](Image* p){p->release();});
        if(name.empty()||!images.emplace(name,std::move(retained)).second)throw std::runtime_error("Duplicate Spriter image resource");
    }
    restored=true;mModel.reset();validate();
}
std::shared_ptr<SpriterEngine::SpriterModel> SpriterSnapshotAsset::model() {
    if(auto value=mModel.lock())return value;
    validate();auto files=std::make_unique<PDGFileFactory>(share(this));auto objects=std::make_unique<PDGObjectFactory>();
    // Transfer factories before loading: a failed delegated SpriterModel(path,
    // ...) constructor would also destroy them while our guards still own them.
    auto result=std::make_shared<SpriterEngine::SpriterModel>(files.get(),objects.get());
    files.release();objects.release();result->loadFile(path);mModel=result;return result;
}
