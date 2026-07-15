#include "pdg_project.h"
#include "internals.h"
#include <iostream>

int main() {
    const char* testPaths[] = {
        "../deps/scml-pp/samples/wonkyskeleton/wonkyskeleton.scml",
        "./deps/scml-pp/samples/wonkyskeleton/wonkyskeleton.scml",
        "deps/scml-pp/samples/wonkyskeleton/wonkyskeleton.scml",
        "/deps/scml-pp/samples/wonkyskeleton/wonkyskeleton.scml",
        "/absolute/path",
        "relative/path",
        "../relative/path"
    };
    
    int numPaths = sizeof(testPaths) / sizeof(testPaths[0]);
    
    for (int i = 0; i < numPaths; i++) {
        bool isAbsolute = os_isAbsolutePath(testPaths[i]);
        std::cout << "Path: '" << testPaths[i] << "' -> isAbsolute: " << (isAbsolute ? "true" : "false") << std::endl;
    }
    
    return 0;
}
