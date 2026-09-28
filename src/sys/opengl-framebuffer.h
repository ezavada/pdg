// Internal framebuffer entry points for desktop GL, OpenGL ES 1, and WebGL.
#ifndef PDG_OPENGL_FRAMEBUFFER_H_INCLUDED
#define PDG_OPENGL_FRAMEBUFFER_H_INCLUDED
#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif
#include "include-opengl.h"
#if !defined(PLATFORM_WIN32) && !defined(PLATFORM_MACOSX) && !defined(__EMSCRIPTEN__)
#include <GL/glext.h>
#endif
#ifndef GL_FRAMEBUFFER
#define GL_FRAMEBUFFER 0x8D40
#define GL_FRAMEBUFFER_BINDING 0x8CA6
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_RENDERBUFFER 0x8D41
#define GL_RENDERBUFFER_BINDING 0x8CA7
#define GL_DEPTH_COMPONENT16 0x81A5
#endif
namespace pdg { namespace framebuffer {
#ifdef PLATFORM_WIN32
using GenFramebuffersProc = void (APIENTRY *)(GLsizei n, GLuint* ids);
inline GenFramebuffersProc GenFramebuffers = nullptr;
using DeleteFramebuffersProc = void (APIENTRY *)(GLsizei n, const GLuint* ids);
inline DeleteFramebuffersProc DeleteFramebuffers = nullptr;
using BindFramebufferProc = void (APIENTRY *)(GLenum target, GLuint id);
inline BindFramebufferProc BindFramebuffer = nullptr;
using FramebufferTexture2DProc = void (APIENTRY *)(GLenum target, GLenum attachment, GLenum textureTarget, GLuint texture, GLint level);
inline FramebufferTexture2DProc FramebufferTexture2D = nullptr;
using CheckFramebufferStatusProc = GLenum (APIENTRY *)(GLenum target);
inline CheckFramebufferStatusProc CheckFramebufferStatus = nullptr;
using GenRenderbuffersProc = void (APIENTRY *)(GLsizei n, GLuint* ids);
inline GenRenderbuffersProc GenRenderbuffers = nullptr;
using DeleteRenderbuffersProc = void (APIENTRY *)(GLsizei n, const GLuint* ids);
inline DeleteRenderbuffersProc DeleteRenderbuffers = nullptr;
using BindRenderbufferProc = void (APIENTRY *)(GLenum target, GLuint id);
inline BindRenderbufferProc BindRenderbuffer = nullptr;
using RenderbufferStorageProc = void (APIENTRY *)(GLenum target, GLenum format, GLsizei width, GLsizei height);
inline RenderbufferStorageProc RenderbufferStorage = nullptr;
using FramebufferRenderbufferProc = void (APIENTRY *)(GLenum target, GLenum attachment, GLenum renderbufferTarget, GLuint renderbuffer);
inline FramebufferRenderbufferProc FramebufferRenderbuffer = nullptr;
using BlendFuncSeparateProc = void (APIENTRY *)(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
inline BlendFuncSeparateProc BlendFuncSeparate = nullptr;
inline bool available() {
    if (!GenFramebuffers) GenFramebuffers = reinterpret_cast<GenFramebuffersProc>(wglGetProcAddress("glGenFramebuffers"));
    if (!DeleteFramebuffers) DeleteFramebuffers = reinterpret_cast<DeleteFramebuffersProc>(wglGetProcAddress("glDeleteFramebuffers"));
    if (!BindFramebuffer) BindFramebuffer = reinterpret_cast<BindFramebufferProc>(wglGetProcAddress("glBindFramebuffer"));
    if (!FramebufferTexture2D) FramebufferTexture2D = reinterpret_cast<FramebufferTexture2DProc>(wglGetProcAddress("glFramebufferTexture2D"));
    if (!CheckFramebufferStatus) CheckFramebufferStatus = reinterpret_cast<CheckFramebufferStatusProc>(wglGetProcAddress("glCheckFramebufferStatus"));
    if (!GenRenderbuffers) GenRenderbuffers = reinterpret_cast<GenRenderbuffersProc>(wglGetProcAddress("glGenRenderbuffers"));
    if (!DeleteRenderbuffers) DeleteRenderbuffers = reinterpret_cast<DeleteRenderbuffersProc>(wglGetProcAddress("glDeleteRenderbuffers"));
    if (!BindRenderbuffer) BindRenderbuffer = reinterpret_cast<BindRenderbufferProc>(wglGetProcAddress("glBindRenderbuffer"));
    if (!RenderbufferStorage) RenderbufferStorage = reinterpret_cast<RenderbufferStorageProc>(wglGetProcAddress("glRenderbufferStorage"));
    if (!FramebufferRenderbuffer) FramebufferRenderbuffer = reinterpret_cast<FramebufferRenderbufferProc>(wglGetProcAddress("glFramebufferRenderbuffer"));
    if (!BlendFuncSeparate) BlendFuncSeparate = reinterpret_cast<BlendFuncSeparateProc>(wglGetProcAddress("glBlendFuncSeparate"));
    return GenFramebuffers && DeleteFramebuffers && BindFramebuffer && FramebufferTexture2D && CheckFramebufferStatus && GenRenderbuffers && DeleteRenderbuffers && BindRenderbuffer && RenderbufferStorage && FramebufferRenderbuffer && BlendFuncSeparate;
}
#else
inline bool available() { return true; }
inline void GenFramebuffers(GLsizei n, GLuint* ids) {
#if defined(PLATFORM_OPENGLES)
    return glGenFramebuffersOES(n, ids);
#elif defined(PLATFORM_MACOSX)
    return glGenFramebuffersEXT(n, ids);
#else
    return glGenFramebuffers(n, ids);
#endif
}
inline void DeleteFramebuffers(GLsizei n, const GLuint* ids) {
#if defined(PLATFORM_OPENGLES)
    return glDeleteFramebuffersOES(n, ids);
#elif defined(PLATFORM_MACOSX)
    return glDeleteFramebuffersEXT(n, ids);
#else
    return glDeleteFramebuffers(n, ids);
#endif
}
inline void BindFramebuffer(GLenum target, GLuint id) {
#if defined(PLATFORM_OPENGLES)
    return glBindFramebufferOES(target, id);
#elif defined(PLATFORM_MACOSX)
    return glBindFramebufferEXT(target, id);
#else
    return glBindFramebuffer(target, id);
#endif
}
inline void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textureTarget, GLuint texture, GLint level) {
#if defined(PLATFORM_OPENGLES)
    return glFramebufferTexture2DOES(target, attachment, textureTarget, texture, level);
#elif defined(PLATFORM_MACOSX)
    return glFramebufferTexture2DEXT(target, attachment, textureTarget, texture, level);
#else
    return glFramebufferTexture2D(target, attachment, textureTarget, texture, level);
#endif
}
inline GLenum CheckFramebufferStatus(GLenum target) {
#if defined(PLATFORM_OPENGLES)
    return glCheckFramebufferStatusOES(target);
#elif defined(PLATFORM_MACOSX)
    return glCheckFramebufferStatusEXT(target);
#else
    return glCheckFramebufferStatus(target);
#endif
}
inline void GenRenderbuffers(GLsizei n, GLuint* ids) {
#if defined(PLATFORM_OPENGLES)
    return glGenRenderbuffersOES(n, ids);
#elif defined(PLATFORM_MACOSX)
    return glGenRenderbuffersEXT(n, ids);
#else
    return glGenRenderbuffers(n, ids);
#endif
}
inline void DeleteRenderbuffers(GLsizei n, const GLuint* ids) {
#if defined(PLATFORM_OPENGLES)
    return glDeleteRenderbuffersOES(n, ids);
#elif defined(PLATFORM_MACOSX)
    return glDeleteRenderbuffersEXT(n, ids);
#else
    return glDeleteRenderbuffers(n, ids);
#endif
}
inline void BindRenderbuffer(GLenum target, GLuint id) {
#if defined(PLATFORM_OPENGLES)
    return glBindRenderbufferOES(target, id);
#elif defined(PLATFORM_MACOSX)
    return glBindRenderbufferEXT(target, id);
#else
    return glBindRenderbuffer(target, id);
#endif
}
inline void RenderbufferStorage(GLenum target, GLenum format, GLsizei width, GLsizei height) {
#if defined(PLATFORM_OPENGLES)
    return glRenderbufferStorageOES(target, format, width, height);
#elif defined(PLATFORM_MACOSX)
    return glRenderbufferStorageEXT(target, format, width, height);
#else
    return glRenderbufferStorage(target, format, width, height);
#endif
}
inline void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbufferTarget, GLuint renderbuffer) {
#if defined(PLATFORM_OPENGLES)
    return glFramebufferRenderbufferOES(target, attachment, renderbufferTarget, renderbuffer);
#elif defined(PLATFORM_MACOSX)
    return glFramebufferRenderbufferEXT(target, attachment, renderbufferTarget, renderbuffer);
#else
    return glFramebufferRenderbuffer(target, attachment, renderbufferTarget, renderbuffer);
#endif
}
inline void BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) {
#if defined(PLATFORM_OPENGLES)
    return glBlendFuncSeparateOES(srcRGB, dstRGB, srcAlpha, dstAlpha);
#elif defined(PLATFORM_MACOSX)
    return glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
#else
    return glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
#endif
}
 #endif
} }
#endif
