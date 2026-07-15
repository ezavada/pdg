// -----------------------------------------------
// font-fallback.h
//
// Font fallback system for handling missing glyphs
//
// Written by Ed Zavada, 2024
// Copyright (c) 2024, Dream Rock Studios, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -----------------------------------------------

#ifndef PDG_FONT_FALLBACK_H_INCLUDED
#define PDG_FONT_FALLBACK_H_INCLUDED

#include "pdg_project.h"

#ifndef PDG_NO_GUI

#include <string>
#include <vector>
#include <map>
#include "pdg/sys/global_types.h"
#include "pdg/sys/os.h"

namespace pdg {

// Forward declarations
class Font;
class FontImpl;
class GraphicsManager;
class Port;

// Represents a segment of text that can be rendered with a single font
struct TextRun {
    int startIndex;      // UTF-16 character index where this run starts
    int length;          // Number of UTF-16 characters in this run
    FontImpl* font;      // Font to use for this run
    int xOffset;         // X offset in pixels from the start of the text
    int width;           // Width of this run in pixels
    
    TextRun() : startIndex(0), length(0), font(nullptr), xOffset(0), width(0) {}
    TextRun(int start, int len, FontImpl* f, int offset, int w) 
        : startIndex(start), length(len), font(f), xOffset(offset), width(w) {}
};

// Font fallback manager
class FontFallbackManager {
public:
    static FontFallbackManager& getInstance();
    
    // Initialize with graphics manager (call once at startup)
    void initialize(GraphicsManager* gfxMgr);
    
    // Get fallback font chain for a given primary font
    std::vector<FontImpl*> getFallbackChain(FontImpl* primaryFont, int size, uint32 style);
    
    // Split text into runs based on font support
    // Returns a vector of TextRun structures
    std::vector<TextRun> splitIntoRuns(
        const utf16string& text, 
        FontImpl* primaryFont, 
        int size, 
        uint32 style,
        Port* port
    );
    
    // Check if a font supports a specific Unicode character
    bool fontSupportsChar(FontImpl* font, utf16char ch, int size, uint32 style);
    
    // Find a font that supports a specific character
    FontImpl* findFontForChar(utf16char ch, const std::vector<FontImpl*>& fallbackChain, int size, uint32 style);
    
private:
    FontFallbackManager();
    ~FontFallbackManager();
    
    // Platform-specific fallback font names
    std::vector<std::string> getPlatformFallbackFonts();
    
    // Load a fallback font by name
    FontImpl* loadFallbackFont(const std::string& fontName, float scalingFactor);
    
    // Graphics manager for creating fonts
    GraphicsManager* mGraphicsManager;
    
    // Cache of loaded fallback fonts (key: fontName_scalingFactor)
    std::map<std::string, FontImpl*> mFallbackFontCache;
};

} // end namespace pdg

#endif // PDG_NO_GUI
#endif // PDG_FONT_FALLBACK_H_INCLUDED

