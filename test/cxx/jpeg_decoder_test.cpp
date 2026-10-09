// Verify that the portable decoder and linked libjpeg agree on their ABI.
#include "internals.h"
#include "image-impl.h"
#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
#include <cstdlib>

namespace pdg {
void platform_initJPEGData(unsigned char*, long, unsigned char**, long*, long*, long*, long*, long*, int*);
}
int main(int argc, char** argv) {
    if (argc < 2) return 1;
    for (int i = 1; i < argc; ++i) {
        std::ifstream file(argv[i], std::ios::binary);
        std::vector<unsigned char> bytes{std::istreambuf_iterator<char>(file), {}};
        unsigned char* pixels = nullptr;
        long w=0,h=0,bw=0,bh=0,pitch=0; int format=0;
        pdg::platform_initJPEGData(bytes.data(), bytes.size(), &pixels, &w, &h, &bw, &bh, &pitch, &format);
        bool varied=false;
        if (pixels) for (long j=1; j<pitch*h; ++j) if (pixels[j]!=pixels[0]) { varied=true; break; }
        const bool valid=pixels && w>0 && h>0 && w==bw && h==bh && pitch==w*3 && format==GL_RGB && varied;
        std::free(pixels);
        if (!valid) { std::cerr << "Failed JPEG decode: " << argv[i] << '\n'; return 1; }
    }
    std::cout << "PASS: UI JPEG textures decode with nonuniform RGB pixels\n";
}
