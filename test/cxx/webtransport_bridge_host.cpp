#include "pdg_webtransport.h"
#include <iostream>
#include <string>

// Line-oriented driver for native protocol/lifecycle integration tests.
int main() {
    std::string request;
    while (std::getline(std::cin, request)) {
        char* result = pdg_wt_command(request.c_str());
        std::cout << (result ? result : "null") << std::endl;
        pdg_wt_free(result);
    }
}
