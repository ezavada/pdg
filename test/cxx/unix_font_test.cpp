// Include the backend to exercise its private FreeType glyph selection without
// requiring a window. Unused renderer functions are removed by section GC.
#include "../../src/sys/unix/graphics-unix-opengl.cpp"
#include <iostream>
#include <stdexcept>
static bool installedGlyph(uint32 codePoint) {
    FcPattern* pattern=FcPatternCreate();
    FcObjectSet* objects=FcObjectSetBuild(FC_CHARSET, nullptr);
    FcFontSet* fonts=FcFontList(nullptr, pattern, objects);
    bool found=false;
    if (fonts) for (int i=0; i<fonts->nfont; ++i) {
        FcCharSet* characters=nullptr;
        if (FcPatternGetCharSet(fonts->fonts[i], FC_CHARSET, 0, &characters)==FcResultMatch &&
            FcCharSetHasChar(characters, codePoint)) { found=true; break; }
    }
    if (fonts) FcFontSetDestroy(fonts);
    FcObjectSetDestroy(objects);
    FcPatternDestroy(pattern);
    return found;
}
int main() {
    try {
        FcInit();
        for (uint32 cp : {0x3053u, 0x4f60u, 0xc548u, 0x0e2au}) if (!installedGlyph(cp)) {
            std::cout << "SKIP: install Noto core and CJK fonts for multilingual fallback coverage\n";
            return 77;
        }
        pdg::FontImplUnix font(nullptr, "Arial", 1);
        if (!font.setPixelSize(24)) throw std::runtime_error("Primary font missing");
        FT_Face primary=font.face();
        for (uint32 cp : {0x3053u, 0x4f60u, 0xc548u, 0x0e2au}) {
            auto* face=font.selectFace(cp);
            if (!face || !FT_Get_Char_Index(face, cp) || !font.loadGlyph(cp, 0, true) || !face->glyph->bitmap.rows)
                throw std::runtime_error("Fallback glyph missing (install Noto core and CJK fonts)");
        }
        font.selectFace('A');
        if (font.face()!=primary) throw std::runtime_error("Primary font not restored after fallback");
        const char* text="Hello こんにちは 안녕하세요 สวัสดี 你好";
        const float width=pdg::measureText(font, text, std::strlen(text), 24, 0);
        const float larger=pdg::measureText(font, text, std::strlen(text), 48, 0);
        if (!(width>0 && larger>width*1.8 && larger<width*2.2))
            throw std::runtime_error("Mixed fallback measurement does not track font size");
        std::cout << "PASS: Japanese, Mandarin, Korean and Thai fallback glyphs and mixed text widths\n";
    } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
