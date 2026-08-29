// this C++ file contains all the code that adapts between the JavaScript and C++ classes, which
// do not always have identical method signatures

#include "pdg_em_adaptors.h"
#include "pdg-lib.h"

#include <emscripten.h>


namespace pdg {

// extend the config manager to handle API differences between C++ and Javascript

std::string&  ConfigManagerWrap::getConfigString(std::string& arg0) {
    static std::string s = "";
    ConfigManagerUnix::getConfigString(arg0.c_str(), s);
    return s;
}

long ConfigManagerWrap::getConfigLong(std::string& arg0) {
    long n;
    ConfigManagerUnix::getConfigLong(arg0.c_str(), n);
    return n;
}

float ConfigManagerWrap::getConfigFloat(std::string& arg0) {
    float n;
    ConfigManagerUnix::getConfigFloat(arg0.c_str(), n);
    return n;
}

bool ConfigManagerWrap::getConfigBool(std::string& arg0) {
    bool n = false;
    ConfigManagerUnix::getConfigBool(arg0.c_str(), n);
    return n;
}

bool emscriptenConfigUseConfig(ConfigManager& manager, const std::string& name) {
    return manager.useConfig(name.c_str());
}

emscripten::val emscriptenConfigGetString(ConfigManager& manager, const std::string& key) {
    std::string value;
    if (!manager.getConfigString(key.c_str(), value)) return emscripten::val::undefined();
    return emscripten::val(value);
}

emscripten::val emscriptenConfigGetLong(ConfigManager& manager, const std::string& key) {
    long value = 0;
    if (!manager.getConfigLong(key.c_str(), value)) return emscripten::val::undefined();
    return emscripten::val(value);
}

emscripten::val emscriptenConfigGetFloat(ConfigManager& manager, const std::string& key) {
    float value = 0.0f;
    if (!manager.getConfigFloat(key.c_str(), value)) return emscripten::val::undefined();
    return emscripten::val(value);
}

emscripten::val emscriptenConfigGetBool(ConfigManager& manager, const std::string& key) {
    bool value = false;
    if (!manager.getConfigBool(key.c_str(), value)) return emscripten::val::undefined();
    return emscripten::val(value);
}

void emscriptenConfigSetString(ConfigManager& manager, const std::string& key, const std::string& value) {
    manager.setConfigString(key.c_str(), value);
}

void emscriptenConfigSetLong(ConfigManager& manager, const std::string& key, long value) {
    manager.setConfigLong(key.c_str(), value);
}

void emscriptenConfigSetFloat(ConfigManager& manager, const std::string& key, float value) {
    manager.setConfigFloat(key.c_str(), value);
}

void emscriptenConfigSetBool(ConfigManager& manager, const std::string& key, bool value) {
    manager.setConfigBool(key.c_str(), value);
}

MemBlock* emscriptenCreateEmptyMemBlock() {
    return new MemBlock(0);
}

Polygon* emscriptenPolygonIntersection(Polygon& polygon, const Polygon& other) {
    return new Polygon(polygon.intersection(other));
}

Polygon* emscriptenPolygonUnion(Polygon& polygon, const Polygon& other) {
    return new Polygon(polygon.unionWith(other));
}

void setSerializationDebugMode(bool mode) {
    ISerializer::s_DebugMode = mode;
}

void emscriptenInit() {
    static const char* argv[] = { "pdg-wasm" };
    pdg_LibSaveArgs(1, argv);
    pdg_LibInit();
}

void emscriptenIdle() {
    pdg_LibIdle();
}

void emscriptenQuit() {
    pdg_LibQuit();
}

bool emscriptenIsQuitting() {
    return pdg_LibIsQuitting();
}


// end stuff to add to C++ API

FileManager* FileManager::createSingletonInstance() {
    return new FileManager();
}
std::string& FileManager::getApplicationDataDirectory() {
    static std::string _wdstr;
    _wdstr.assign( OS::getApplicationDataDirectory() );
    return _wdstr;
}
std::string& FileManager::getApplicationDirectory() {
    static std::string _wdstr;
    _wdstr.assign( OS::getApplicationDirectory() );
    return _wdstr;
}
std::string& FileManager::getApplicationResourceDirectory() {
    static std::string _wdstr;
    _wdstr.assign( OS::getApplicationResourceDirectory() );
    return _wdstr;
}

void platform_cleanup() 
{
  EM_ASM(
     pdg_em_platform_cleanup();
  );
}

void platform_init(int argc, const char* argv[])
{
  EM_ASM({
     pdg_em_platform_init($0, $1);
  }, argc, argv);
}

void platform_pollEvents()
{
  EM_ASM(
     pdg_em_platform_pollEvents();
  );
}

void platform_initImageData(unsigned char* imageData, long imageDataLen, 
    unsigned char** outDataPtr, long* outWidth, long* outHeight, 
    long* outBufferWidth, long* outBufferHeight, long* outBufferPitch, 
    int* outFormat) 
{
  EM_ASM({
     pdg_em_platform_initImageData($0, $1, $2, $3, $4, $5, $6, $7, $8);
  }, imageData, imageDataLen, outDataPtr, outWidth, outHeight, outBufferWidth, outBufferHeight, outBufferPitch, outFormat);
}



} // end namespace pdg
