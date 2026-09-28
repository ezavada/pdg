// The portable decoder must size pixels after palette/gray/transparency expansion.
#include "internals.h"
#include "image-impl.h"
#include "png/png.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

using Bytes = std::vector<unsigned char>;
static void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
static Bytes fixture(int colorType, int depth, bool transparent, const Bytes& row,
                     bool interlaced = false) {
    Bytes result;
    auto* png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    auto* info = png_create_info_struct(png);
    require(png && info, "Cannot create fixture writer");
    if (setjmp(png_jmpbuf(png))) throw std::runtime_error("Cannot write PNG fixture");
    png_set_write_fn(png, &result, [](png_structp p, png_bytep data, png_size_t size) {
        auto& bytes = *static_cast<Bytes*>(png_get_io_ptr(p));
        bytes.insert(bytes.end(), data, data+size);
    }, [](png_structp) {});
    png_set_IHDR(png, info, 3, 2, depth, colorType,
                 interlaced ? PNG_INTERLACE_ADAM7 : PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_color palette[] = {{255,0,0},{0,255,0},{0,0,255}};
    unsigned char alpha[] = {0,128,255};
    png_color_16 key{};
    key.gray=1; key.red=255; key.green=0; key.blue=0;
    if (colorType == PNG_COLOR_TYPE_PALETTE) png_set_PLTE(png, info, palette, 3);
    if (transparent) png_set_tRNS(png, info,
        colorType == PNG_COLOR_TYPE_PALETTE ? alpha : nullptr,
        colorType == PNG_COLOR_TYPE_PALETTE ? 3 : 0, &key);
    png_bytep rows[] = {const_cast<png_bytep>(row.data()), const_cast<png_bytep>(row.data())};
    png_set_rows(png, info, rows);
    png_write_png(png, info, PNG_TRANSFORM_IDENTITY, nullptr);
    png_destroy_write_struct(&png, &info);
    return result;
}
static void check(Bytes input, const Bytes& expectedRow, bool alpha) {
    unsigned char* pixels=nullptr;
    long width=0, height=0, bufferWidth=0, bufferHeight=0, pitch=0;
    int format=0;
    pdg::platform_initImageData(input.data(), input.size(), &pixels, &width, &height,
        &bufferWidth, &bufferHeight, &pitch, &format);
    const bool dimensions = pixels && width==3 && height==2 && bufferWidth==3 && bufferHeight==2;
    const bool layout = format==(alpha ? GL_RGBA : GL_RGB) && pitch==long(expectedRow.size());
    bool matches=dimensions && layout;
    if (matches) for (int y=0;y<2;++y) for (size_t x=0;x<expectedRow.size();++x)
        if (pixels[y*pitch+x]!=expectedRow[x]) matches=false;
    std::free(pixels);
    require(dimensions, "PNG dimensions missing or incorrect");
    require(layout, "PNG output format/row pitch ignores transformed channels");
    require(matches, "PNG pixels differ after expansion");
}
int main() {
    try {
        const Bytes rgb{255,0,0, 0,255,0, 0,0,255};
        const Bytes rgba{255,0,0,0, 0,255,0,128, 0,0,255,255};
        check(fixture(PNG_COLOR_TYPE_PALETTE,8,true,{0,1,2}),rgba,true);
        check(fixture(PNG_COLOR_TYPE_PALETTE,2,true,{0x18},true),rgba,true);
        check(fixture(PNG_COLOR_TYPE_PALETTE,8,false,{0,1,2}),rgb,false);
        check(fixture(PNG_COLOR_TYPE_RGB,8,false,rgb),rgb,false);
        check(fixture(PNG_COLOR_TYPE_RGB,8,true,rgb),{255,0,0,0, 0,255,0,255, 0,0,255,255},true);
        check(fixture(PNG_COLOR_TYPE_RGBA,8,false,rgba),rgba,true);
        check(fixture(PNG_COLOR_TYPE_GRAY,2,true,{0x18}),{0,0,0,255, 85,85,85,0, 170,170,170,255},true);
        check(fixture(PNG_COLOR_TYPE_GRAY_ALPHA,8,false,{10,20,30,40,50,60}),
            {10,10,10,20, 30,30,30,40, 50,50,50,60},true);
        check(fixture(PNG_COLOR_TYPE_RGBA,16,false,{255,255,0,0,0,0,0,0,
            0,0,255,255,0,0,128,128, 0,0,0,0,255,255,255,255}),rgba,true);
        for (bool afterPixels : {false,true}) {
            auto truncated=fixture(PNG_COLOR_TYPE_PALETTE,8,true,{0,1,2});
            truncated.resize(afterPixels ? truncated.size()-5 : 20);
            unsigned char* pixels=nullptr;
            long w=1,h=1,bw=1,bh=1,pitch=1; int format=0;
            pdg::platform_initImageData(truncated.data(),truncated.size(),&pixels,&w,&h,&bw,&bh,&pitch,&format);
            require(!pixels && !w && !h && !bw && !bh && !pitch, "Failed decode published partial pixels");
        }
        std::cout << "PASS: palette, tRNS, RGB/RGBA, grayscale, 16-bit and interlaced PNG decoding\n";
    } catch(const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
