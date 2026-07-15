// -----------------------------------------------
// opengl-state-cache.h
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

#ifndef PDG_OPENGL_STATE_CACHE_H_INCLUDED
#define PDG_OPENGL_STATE_CACHE_H_INCLUDED

#include "pdg_project.h"

#ifndef PDG_NO_GUI

#include "include-opengl.h"

namespace pdg {

/**
 * OpenGLStateCache - Tracks and minimizes OpenGL state changes
 * 
 * This class caches the current OpenGL state and only issues state change
 * commands when the state actually needs to change. This significantly
 * reduces the number of OpenGL calls and state validation overhead.
 * 
 * Key optimizations:
 * - Tracks texture binding (avoid redundant glBindTexture)
 * - Tracks blend mode (avoid redundant glEnable/glDisable GL_BLEND)
 * - Tracks texture mode (avoid redundant glEnable/glDisable GL_TEXTURE_2D)
 * - Tracks blend function (avoid redundant glBlendFunc)
 * 
 * Usage:
 *   OpenGLStateCache cache;
 *   cache.bindTexture(textureId);      // Only binds if different
 *   cache.setBlending(true);           // Only enables if not already enabled
 *   cache.setTexturing(true);          // Only enables if not already enabled
 */
class OpenGLStateCache {
private:
    GLuint mCurrentTexture;
    bool mBlendEnabled;
    bool mTextureEnabled;
    GLenum mBlendSrc;
    GLenum mBlendDst;
    
    // Track whether we've set these states yet (unknown until first set)
    bool mBlendKnown;
    bool mTextureKnown;
    
    // Statistics (optional, for performance analysis)
    #ifdef PDG_DEBUG_GL_STATE_CACHE
    int mTextureSaves;
    int mBlendSaves;
    int mTexturingSaves;
    #endif
    
public:
    OpenGLStateCache();
    
    /**
     * Resets the state cache - call at the start of each frame
     * Marks all state as unknown, forcing GL calls until state is set
     */
    void resetState();
    
    /**
     * Bind a texture, but only if it's different from the currently bound texture
     * @param texture The OpenGL texture ID to bind (0 to unbind)
     */
    void bindTexture(GLuint texture);
    
    /**
     * Enable or disable blending
     * Only issues GL call if state is different from cached state
     * @param enabled True to enable blending, false to disable
     * @param src Source blend function (default: GL_SRC_ALPHA)
     * @param dst Destination blend function (default: GL_ONE_MINUS_SRC_ALPHA)
     */
    void setBlending(bool enabled, GLenum src = GL_SRC_ALPHA, 
                     GLenum dst = GL_ONE_MINUS_SRC_ALPHA);
    
    /**
     * Enable or disable 2D texturing
     * Only issues GL call if state is different from cached state
     * @param enabled True to enable GL_TEXTURE_2D, false to disable
     */
    void setTexturing(bool enabled);
    
    /**
     * Get currently bound texture ID (according to cache)
     */
    GLuint getCurrentTexture() const { return mCurrentTexture; }
    
    #ifdef PDG_DEBUG_GL_STATE_CACHE
    /**
     * Print statistics about how many state changes were saved
     */
    void printStatistics() const;
    
    /**
     * Reset statistics counters
     */
    void resetStatistics();
    #endif
};

} // end namespace pdg

#endif // PDG_NO_GUI

#endif // PDG_OPENGL_STATE_CACHE_H_INCLUDED

