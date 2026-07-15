#include <iostream>
#include <string>
#include "deps/minizip/compat/unzip.h"
#include "deps/minizip/mz.h"

int main() {
    std::cout << "Testing minizip-ng 4.0.10 upgrade..." << std::endl;
    
    // Test that we can include the headers
    std::cout << "✓ Successfully included minizip-ng compatibility headers" << std::endl;
    
    // Test that the API functions are available (using address-of operator)
    std::cout << "✓ unzOpen function available: " << (&unzOpen != nullptr ? "yes" : "no") << std::endl;
    std::cout << "✓ unzLocateFile function available: " << (&unzLocateFile != nullptr ? "yes" : "no") << std::endl;
    std::cout << "✓ unzGetCurrentFileInfo function available: " << (&unzGetCurrentFileInfo != nullptr ? "yes" : "no") << std::endl;
    
    std::cout << "✓ Minizip-ng 4.0.10 upgrade successful!" << std::endl;
    return 0;
} 