// -----------------------------------------------
// font-fallback.cpp
//
// Font fallback system implementation
//
// Written by Ed Zavada, 2024
// Copyright (c) 2024, Dream Rock Studios, LLC
//
// -----------------------------------------------

#include "pdg_project.h"

#ifndef PDG_NO_GUI

#include "font-fallback.h"
#include "font-impl.h"
#include "pdg/sys/os.h"
#include "pdg/sys/graphics.h"
#include "pdg/sys/port.h"

//#define PDG_DEBUG_FONT

#ifdef PDG_DEBUG_FONT
  #define FONT_DEBUG_ONLY(x) DEBUG_ONLY(x)
#else
  #define FONT_DEBUG_ONLY(x)
#endif

#ifdef PLATFORM_MACOSX
#include "graphics-macosx.h"
#include "internals-macosx.h"
extern "C" bool CGFontGetGlyphsForUnichars(CGFontRef, pdg::utf16char[], CGGlyph[], size_t);
#endif

#ifdef PLATFORM_WIN32
#include "graphics-win32.h"
#include "internals-win32.h"
#ifndef GGI_MARK_NONEXISTING_GLYPHS
#define GGI_MARK_NONEXISTING_GLYPHS 0x0001
#endif
#endif

namespace pdg {

FontFallbackManager& FontFallbackManager::getInstance() {
    static FontFallbackManager instance;
    return instance;
}

FontFallbackManager::FontFallbackManager() : mGraphicsManager(nullptr) {
}

FontFallbackManager::~FontFallbackManager() {
    // Release all cached fallback fonts
    for (std::map<std::string, FontImpl*>::iterator it = mFallbackFontCache.begin(); 
         it != mFallbackFontCache.end(); ++it) {
        if (it->second) {
            it->second->release();
        }
    }
    mFallbackFontCache.clear();
}

void FontFallbackManager::initialize(GraphicsManager* gfxMgr) {
    mGraphicsManager = gfxMgr;
}

std::vector<std::string> FontFallbackManager::getPlatformFallbackFonts() {
    std::vector<std::string> fallbacks;
    
    fallbacks.push_back("Arial Unicode MS");  // Wide coverage if installed
#ifdef PLATFORM_MACOSX
    // macOS fallback fonts in priority order
    fallbacks.push_back("Hiragino Sans");     // Japanese
    fallbacks.push_back("PingFang SC");       // Simplified Chinese
    fallbacks.push_back("PingFang TC");       // Traditional Chinese
    fallbacks.push_back("Apple SD Gothic Neo"); // Korean
    fallbacks.push_back("Thonburi");          // Thai
#endif

#ifdef PLATFORM_WIN32
    // Windows fallback fonts
    fallbacks.push_back("Microsoft YaHei");   // Chinese
    fallbacks.push_back("Meiryo");            // Japanese
    fallbacks.push_back("Malgun Gothic");     // Korean
    fallbacks.push_back("Leelawadee");        // Thai
#endif
    fallbacks.push_back("Arial");             // Basic Latin/Cyrillic/Greek
    return fallbacks;
}

bool FontFallbackManager::fontSupportsChar(FontImpl* font, utf16char ch, int size, uint32 style) {
    if (!font) return false;
    
#ifdef PLATFORM_MACOSX
    FontImplMac* macFont = dynamic_cast<FontImplMac*>(font);
    if (!macFont) return false;
    
    MacAPI::PrivateOSFontRef fontRef = macFont->getMacFont(size, style);
    if (!fontRef) return false;
    
    MacAPI::CGGlyph glyph = 0;
    utf16char chars[1] = { ch };
    
    // CGFontGetGlyphsForUnichars returns true if successful
    // A glyph ID of 0 means the character is not in the font
    bool result = CGFontGetGlyphsForUnichars(fontRef, chars, &glyph, 1);
    
    return result && (glyph != 0);
#endif

#ifdef PLATFORM_WIN32
    FontImplWin* winFont = dynamic_cast<FontImplWin*>(font);
    if (!winFont) return false;
    
    WinAPI::HFONT hFont = winFont->getWindowsFont(size, style);
    if (!hFont) return false;
    
    // Create a temporary DC to query the font
    WinAPI::HDC hdc = WinAPI::CreateCompatibleDC(NULL);
    WinAPI::HFONT oldFont = (WinAPI::HFONT)WinAPI::SelectObject(hdc, hFont);
    
    // GetGlyphIndicesW returns 0xFFFF for missing glyphs
    WCHAR wch = (WCHAR)ch;
    WORD glyphIndex = 0;
    DWORD result = WinAPI::GetGlyphIndicesW(hdc, &wch, 1, &glyphIndex, GGI_MARK_NONEXISTING_GLYPHS);
    
    WinAPI::SelectObject(hdc, oldFont);
    WinAPI::DeleteDC(hdc);
    
    // Check if glyph exists (not 0xFFFF)
    return (result != GDI_ERROR) && (glyphIndex != 0xFFFF);
#endif

    return false;  // Platform not supported
}

FontImpl* FontFallbackManager::loadFallbackFont(const std::string& fontName, float scalingFactor) {
    if (!mGraphicsManager) {
        return nullptr;
    }
    
    // Create cache key
    char key[256];
    std::snprintf(key, sizeof(key), "%s_%.2f", fontName.c_str(), scalingFactor);
    std::string cacheKey(key);
    
    // Check if already loaded
    std::map<std::string, FontImpl*>::iterator it = mFallbackFontCache.find(cacheKey);
    if (it != mFallbackFontCache.end()) {
        return it->second;
    }
    
    // Load the font
    Font* font = mGraphicsManager->createFont(fontName.c_str(), scalingFactor);
    FontImpl* fontImpl = dynamic_cast<FontImpl*>(font);
    
    if (fontImpl) {
        // Cache it
        mFallbackFontCache[cacheKey] = fontImpl;
    }
    
    return fontImpl;
}

FontImpl* FontFallbackManager::findFontForChar(utf16char ch, const std::vector<FontImpl*>& fallbackChain, int size, uint32 style) {
    // Try each font in the fallback chain
    for (size_t i = 0; i < fallbackChain.size(); i++) {
        FontImpl* font = fallbackChain[i];
        if (font && fontSupportsChar(font, ch, size, style)) {
            return font;
        }
    }
    return nullptr;
}

std::vector<FontImpl*> FontFallbackManager::getFallbackChain(FontImpl* primaryFont, int size, uint32 style) {
    std::vector<FontImpl*> chain;
    
    // Primary font is always first
    if (primaryFont) {
        chain.push_back(primaryFont);
    }
    
    // Add fallback fonts
    std::vector<std::string> fallbackNames = getPlatformFallbackFonts();
    float scalingFactor = primaryFont ? primaryFont->mScalingFactor : 1.0f;
    
    for (size_t i = 0; i < fallbackNames.size(); i++) {
        const std::string& fontName = fallbackNames[i];
        
        // Skip if it's the same as the primary font
        if (primaryFont && fontName == primaryFont->getFontName()) {
            continue;
        }
        
        // Try to load the fallback font
        FontImpl* fallbackFont = loadFallbackFont(fontName, scalingFactor);
        if (fallbackFont) {
            chain.push_back(fallbackFont);
        }
    }
    
    return chain;
}

std::vector<TextRun> FontFallbackManager::splitIntoRuns(
    const utf16string& text, 
    FontImpl* primaryFont, 
    int size, 
    uint32 style,
    Port* port
) {
    std::vector<TextRun> runs;
    
    if (text.empty() || !primaryFont) {
        return runs;
    }
    
    FONT_DEBUG_ONLY({
        // Convert full text to UTF-8 for logging
        std::string fullUtf8Text;
        utf16string textCopy = text;
        OS::utf16to8(fullUtf8Text, textCopy);
        OS::_DOUT("FontFallbackManager::splitIntoRuns: text='%s', primaryFont='%s', size=%d", 
            fullUtf8Text.c_str(), primaryFont->getFontName().c_str(), size);
    });
    
    std::vector<FontImpl*> fallbackChain = getFallbackChain(primaryFont, size, style);
    
    int runStart = 0;
    FontImpl* currentFont = primaryFont;
    int currentXOffset = 0;
    
    for (size_t i = 0; i < text.length(); i++) {
        utf16char ch = text[i];
        
        // Find which font supports this character
        FontImpl* fontForChar = findFontForChar(ch, fallbackChain, size, style);
        
        // If no font found, use primary font (will show box)
        if (!fontForChar) {
            fontForChar = primaryFont;
            FONT_DEBUG_ONLY(OS::_DOUT("  No font found for char U+%04X, using primary font", (unsigned int)ch));
        }
        
        // Check if we need to start a new run
        if (fontForChar != currentFont) {
            // Save the previous run
            if (i > runStart) {
                int runLength = i - runStart;
                utf16string runText = text.substr(runStart, runLength);
                
                // Convert to UTF-8 for width calculation
                std::string utf8Text;
                OS::utf16to8(utf8Text, runText);
                
                // Calculate actual run width using the current font
                Font* oldFont = port ? port->getCurrentFont() : nullptr;
                if (port && currentFont) {
                    port->setFont(currentFont);
                }
                int runWidth = port ? port->getTextWidth(utf8Text.c_str(), size, style) : (runLength * size / 2);
                if (port && oldFont) {
                    port->setFont(oldFont);
                }
                
                FONT_DEBUG_ONLY(OS::_DOUT("  Run %d: startIndex=%d, length=%d, font='%s', xOffset=%d, width=%d, text='%s'",
                    (int)runs.size(), runStart, runLength, currentFont ? currentFont->getFontName().c_str() : "null", 
                    currentXOffset, runWidth, utf8Text.c_str()));
                
                runs.push_back(TextRun(runStart, runLength, currentFont, currentXOffset, runWidth));
                currentXOffset += runWidth;
            }
            
            // Start new run
            runStart = i;
            currentFont = fontForChar;
            FONT_DEBUG_ONLY(OS::_DOUT("  Switching to font '%s' at index %d for char U+%04X", 
                fontForChar ? fontForChar->getFontName().c_str() : "null", (int)i, (unsigned int)ch));
        }
    }
    
    // Add the final run
    if (runStart < (int)text.length()) {
        int runLength = text.length() - runStart;
        utf16string runText = text.substr(runStart, runLength);
        
        // Convert to UTF-8 for width calculation
        std::string utf8Text;
        OS::utf16to8(utf8Text, runText);
        
        // Calculate actual run width
        Font* oldFont = port ? port->getCurrentFont() : nullptr;
        if (port && currentFont) {
            port->setFont(currentFont);
        }
        int runWidth = port ? port->getTextWidth(utf8Text.c_str(), size, style) : (runLength * size / 2);
        if (port && oldFont) {
            port->setFont(oldFont);
        }
        
        FONT_DEBUG_ONLY(OS::_DOUT("  Run %d (final): startIndex=%d, length=%d, font='%s', xOffset=%d, width=%d, text='%s'",
            (int)runs.size(), runStart, runLength, currentFont ? currentFont->getFontName().c_str() : "null", 
            currentXOffset, runWidth, utf8Text.c_str()));
        
        runs.push_back(TextRun(runStart, runLength, currentFont, currentXOffset, runWidth));
    }
    
    FONT_DEBUG_ONLY(OS::_DOUT("FontFallbackManager::splitIntoRuns: Created %d runs", (int)runs.size()));
    
    return runs;
}

} // end namespace pdg

#endif // PDG_NO_GUI

