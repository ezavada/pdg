// -----------------------------------------------
// opengl-state-cache.cpp
//
// OpenGL State Caching to minimize redundant state changes
// Part of Scenario 1 optimizations for PDG
//
// Written by Ed Zavada, 2025
// Copyright (c) 2025, Dream Rock Studios, LLC
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

#include "pdg_project.h"

#ifndef PDG_NO_GUI

#include "opengl-state-cache.h"

#ifdef PDG_DEBUG_GL_STATE_CACHE
#include <iostream>
#endif

namespace pdg {

OpenGLStateCache::OpenGLStateCache()
: mCurrentTexture(0),
  mBlendEnabled(false),
  mTextureEnabled(false),
  mBlendSrc(GL_SRC_ALPHA),
  mBlendDst(GL_ONE_MINUS_SRC_ALPHA),
  mBlendKnown(false),
  mTextureKnown(false)
{
    #ifdef PDG_DEBUG_GL_STATE_CACHE
    mTextureSaves = 0;
    mBlendSaves = 0;
    mTexturingSaves = 0;
    #endif
}

void OpenGLStateCache::resetState() {
    // Reset texture binding cache to "unknown"
    mCurrentTexture = (GLuint)-1;  // Use -1 as "unknown" since 0 is a valid texture ID
    
    // Mark blend and texture state as unknown
    // This forces the first setBlending/setTexturing call to issue GL commands
    mBlendKnown = false;
    mTextureKnown = false;
}

void OpenGLStateCache::bindTexture(GLuint texture) {
    if (texture != mCurrentTexture) {
        glBindTexture(GL_TEXTURE_2D, texture);
        mCurrentTexture = texture;
    }
    #ifdef PDG_DEBUG_GL_STATE_CACHE
    else {
        mTextureSaves++;
    }
    #endif
}

void OpenGLStateCache::setBlending(bool enabled, GLenum src, GLenum dst) {
    #ifdef PDG_DEBUG_GL_STATE_CACHE
    bool changed = false;
    #endif
    
    // If we don't know the current state, always set it
    if (!mBlendKnown) {
        if (enabled) {
            glEnable(GL_BLEND);
            if (src != GL_SRC_ALPHA || dst != GL_ONE_MINUS_SRC_ALPHA) {
                glBlendFunc(src, dst);
            }
        } else {
            glDisable(GL_BLEND);
        }
        mBlendEnabled = enabled;
        mBlendSrc = src;
        mBlendDst = dst;
        mBlendKnown = true;
        #ifdef PDG_DEBUG_GL_STATE_CACHE
        changed = true;
        #endif
    }
    // If enabled state changed
    else if (enabled != mBlendEnabled) {
        if (enabled) {
            glEnable(GL_BLEND);
            glBlendFunc(src, dst);
        } else {
            glDisable(GL_BLEND);
        }
        mBlendEnabled = enabled;
        mBlendSrc = src;
        mBlendDst = dst;
        #ifdef PDG_DEBUG_GL_STATE_CACHE
        changed = true;
        #endif
    }
    // If enabled but blend func changed
    else if (enabled && (src != mBlendSrc || dst != mBlendDst)) {
        glBlendFunc(src, dst);
        mBlendSrc = src;
        mBlendDst = dst;
        #ifdef PDG_DEBUG_GL_STATE_CACHE
        changed = true;
        #endif
    }
    
    #ifdef PDG_DEBUG_GL_STATE_CACHE
    if (!changed) {
        mBlendSaves++;
    }
    #endif
}

void OpenGLStateCache::setTexturing(bool enabled) {
    // If we don't know the current state, always set it
    if (!mTextureKnown) {
        if (enabled) {
            glEnable(GL_TEXTURE_2D);
        } else {
            glDisable(GL_TEXTURE_2D);
        }
        mTextureEnabled = enabled;
        mTextureKnown = true;
    }
    // Only change if different
    else if (enabled != mTextureEnabled) {
        if (enabled) {
            glEnable(GL_TEXTURE_2D);
        } else {
            glDisable(GL_TEXTURE_2D);
        }
        mTextureEnabled = enabled;
    }
    #ifdef PDG_DEBUG_GL_STATE_CACHE
    else {
        mTexturingSaves++;
    }
    #endif
}

#ifdef PDG_DEBUG_GL_STATE_CACHE
void OpenGLStateCache::printStatistics() const {
    std::cout << "OpenGL State Cache Statistics:" << std::endl;
    std::cout << "  Texture binding saves: " << mTextureSaves << std::endl;
    std::cout << "  Blend state saves: " << mBlendSaves << std::endl;
    std::cout << "  Texturing state saves: " << mTexturingSaves << std::endl;
    std::cout << "  Total saves: " << (mTextureSaves + mBlendSaves + mTexturingSaves) << std::endl;
}

void OpenGLStateCache::resetStatistics() {
    mTextureSaves = 0;
    mBlendSaves = 0;
    mTexturingSaves = 0;
}
#endif

} // end namespace pdg

#endif // PDG_NO_GUI

