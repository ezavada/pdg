// -----------------------------------------------
//  port-renderer.cpp
//
// Implementation of the Renderer interface for the Port class
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

#include "pdg/msvcfix.h"  // fix non-standard MSVC

#include "pdg/sys/port.h"
#include "pdg/sys/renderer.h"
#include "pdg/sys/graphics.h"
#include "pdg/sys/drawing.h"
#include "graphics-opengl.h"
#include "image-opengl.h"
#include "include-opengl.h"
#include "pdg/sys/os.h"
#include <cmath>


namespace pdg {

    // helper function to make a rounded rect polygon
    void MakeRoundedRectPolygon(const Rect& rect, float xRadius, float yRadius, Polygon& polygon);

    // Helper structure to hold calculated texture UV coordinates
    struct TextureUVBounds {
        float uMin, vMin, uMax, vMax;  // UV coordinates in texture space
        Rect drawRect;                  // Adjusted drawing rectangle for fit modes
        bool useDrawRect;               // Whether to use drawRect instead of original shape
    };

    // Helper function to calculate proper UV coordinates based on fitType
    // Takes into account texture buffer size vs actual image size, and applies fitType
    TextureUVBounds calculateTextureFitUVs(Image* texture, const Rect& shapeBounds, FitType fitType) {
        TextureUVBounds result;
        result.useDrawRect = false;
        
        if (!texture) {
            result.uMin = result.vMin = 0.0f;
            result.uMax = result.vMax = 1.0f;
            return result;
        }
        
        ImageOpenGL* imgOpenGL = static_cast<ImageOpenGL*>(texture);
        
        // Get actual image dimensions and buffer dimensions
        float imgWidth = (float)texture->width;
        float imgHeight = (float)texture->height;
        float bufferWidth = (float)imgOpenGL->mBufferWidth;
        float bufferHeight = (float)imgOpenGL->mBufferHeight;
        
        // Calculate texture coordinates accounting for buffer padding
        // The actual image only occupies a portion of the power-of-2 texture buffer
        float texU = imgWidth / bufferWidth;
        float texV = imgHeight / bufferHeight;
        
        // Apply edge clamping if enabled to prevent sampling edge pixels
        if (imgOpenGL->mUseEdgeClamp) {
            float clampX = 1.0f / (2.0f * imgWidth);
            float clampY = 1.0f / (2.0f * imgHeight);
            result.uMin = clampX;
            result.vMin = clampY;
            result.uMax = texU - clampX;
            result.vMax = texV - clampY;
        } else {
            result.uMin = 0.0f;
            result.vMin = 0.0f;
            result.uMax = texU;
            result.vMax = texV;
        }
        
        // For fit modes other than fill and tile, we need to adjust the drawing area
        if (fitType != fit_Fill && fitType != fit_Tile && fitType != fit_TileX && fitType != fit_TileY) {
            float shapeWidth = shapeBounds.width();
            float shapeHeight = shapeBounds.height();
            float imgAspect = imgWidth / imgHeight;
            float shapeAspect = shapeWidth / shapeHeight;
            
            Rect fitRect(imgWidth, imgHeight);
            
            if (fitType == fit_Inside) {
                // Scale to fit inside, maintaining aspect ratio
                if (shapeAspect > imgAspect) {
                    // Shape is wider than image, fit to height
                    float scale = shapeHeight / imgHeight;
                    fitRect.scale(scale);
                } else {
                    // Shape is taller than image, fit to width
                    float scale = shapeWidth / imgWidth;
                    fitRect.scale(scale);
                }
                fitRect.center(shapeBounds.centerPoint());
                result.drawRect = fitRect;
                result.useDrawRect = true;
                
            } else if (fitType == fit_Overflow || fitType == fit_Clipped) {
                // Scale to overflow/fill, maintaining aspect ratio
                if (shapeAspect < imgAspect) {
                    // Shape is taller than image, fit to height (overflow width)
                    float scale = shapeHeight / imgHeight;
                    fitRect.scale(scale);
                } else {
                    // Shape is wider than image, fit to width (overflow height)
                    float scale = shapeWidth / imgWidth;
                    fitRect.scale(scale);
                }
                fitRect.center(shapeBounds.centerPoint());
                
                if (fitType == fit_Clipped) {
                    // For clipped mode, adjust UVs to show only the portion that fits
                    float uvScaleX = shapeWidth / fitRect.width();
                    float uvScaleY = shapeHeight / fitRect.height();
                    float uvCenterX = (result.uMin + result.uMax) / 2.0f;
                    float uvCenterY = (result.vMin + result.vMax) / 2.0f;
                    float uvHalfW = (result.uMax - result.uMin) / 2.0f * uvScaleX;
                    float uvHalfH = (result.vMax - result.vMin) / 2.0f * uvScaleY;
                    result.uMin = uvCenterX - uvHalfW;
                    result.uMax = uvCenterX + uvHalfW;
                    result.vMin = uvCenterY - uvHalfH;
                    result.vMax = uvCenterY + uvHalfH;
                } else {
                    // For overflow, use the fitted rect
                    result.drawRect = fitRect;
                    result.useDrawRect = true;
                }
            } else if (fitType == fit_Width) {
                float scale = shapeWidth / imgWidth;
                fitRect.scale(scale);
                fitRect.center(shapeBounds.centerPoint());
                result.drawRect = fitRect;
                result.useDrawRect = true;
            } else if (fitType == fit_Height) {
                float scale = shapeHeight / imgHeight;
                fitRect.scale(scale);
                fitRect.center(shapeBounds.centerPoint());
                result.drawRect = fitRect;
                result.useDrawRect = true;
            }
        }
        
        return result;
    }

    // -----------------------------------------------------------------------------------
    // Port Renderer interface implementation
    // -----------------------------------------------------------------------------------

    void Port::drawLine(const Point& from, const Point& to, const Attributes& attrs) {
        // Apply transformation if needed
        Point transformedFrom = from;
        Point transformedTo = to;
        
        if (attrs.getTransform() != glm::mat3(1.0f)) {  // not identity matrix
            glm::vec3 fromVec = attrs.getTransform() * glm::vec3(from.x, from.y, 1.0f);
            glm::vec3 toVec = attrs.getTransform() * glm::vec3(to.x, to.y, 1.0f);
            transformedFrom = Point(fromVec.x, fromVec.y);
            transformedTo = Point(toVec.x, toVec.y);
        }

        // Apply color with opacity
        Color lineColor = attrs.getLineColor();
        lineColor.alpha *= attrs.getLineOpacity();

        // Get port implementation for OpenGL access
        PortImpl& port = static_cast<PortImpl&>(*this);
        Rect drawableRect = port.drawableRect();
        
        // Check for lines entirely outside the drawable area
        if (from.x < drawableRect.left && to.y < drawableRect.left) return;
        if (from.x > drawableRect.right && to.y > drawableRect.right) return;
        if (from.y < drawableRect.top && to.y < drawableRect.top) return;
        if (from.y > drawableRect.bottom && to.y > drawableRect.bottom) return;

        // Set up OpenGL state
        port.setOpenGLModesForDrawing(lineColor.alpha < 1.0f, attrs.getBlendMode());
        
        // Set line color
        glColor4f(lineColor.red, lineColor.green, lineColor.blue, lineColor.alpha);
        
        // Set line width if thickness > 1.0f
        if (attrs.getLineThickness() > 1.0f) {
            glLineWidth(attrs.getLineThickness());
        }
        
        // Draw the line directly with OpenGL
        glBegin(GL_LINES);
        glVertex2f(transformedFrom.x, transformedFrom.y);
        glVertex2f(transformedTo.x, transformedTo.y);
        glEnd();
        
        // Reset line width if it was changed
        if (attrs.getLineThickness() > 1.0f) {
            glLineWidth(1.0f);
        }
        
        // Mark port as needing redraw
        port.mNeedRedraw = true;
    }

    void Port::drawRect(const Rect& rect, const Attributes& attrs) {

        // Handle rounded corners by creating and drawing a polygon
        if (attrs.getRoundedCornerRadius() > 0.0f) {
            float xRadius = attrs.getRoundedCornerRadius();
            float yRadius = attrs.getRoundedCornerRadius();
            Polygon polygon;
            MakeRoundedRectPolygon(rect, xRadius, yRadius, polygon);
            drawPolygon(polygon, attrs);
            return;
        }

        // everything else is just a quad
        drawQuad(rect, attrs);
        return;
    }

    void Port::drawQuad(const Quad& quad, const Attributes& attrs) {
        // Get port implementation for OpenGL access
        PortImpl& port = static_cast<PortImpl&>(*this);

        // Apply colors with opacity
        Color lineColor = attrs.getLineColor();
        lineColor.alpha *= attrs.getLineOpacity();
        Color fillColor = attrs.getFillColor();
        fillColor.alpha *= attrs.getFillOpacity();
        LineStyle lineStyle = attrs.getLineStyle();

        // Determine the quad to draw based on texture fitting (if texture is present)
        Quad drawQuad = quad;
        TextureUVBounds uvBounds;
        uvBounds.uMin = uvBounds.vMin = 0.0f;
        uvBounds.uMax = uvBounds.vMax = 1.0f;
        uvBounds.useDrawRect = false;
        
        Image* texture = attrs.getTexture();
        if (texture && texture->width > 0 && texture->height > 0) {
            // Calculate fit based on ORIGINAL quad bounds (before transformation)
            Rect originalBounds = quad.getBounds();
            FitType fitType = attrs.getFitType();
            uvBounds = calculateTextureFitUVs(texture, originalBounds, fitType);
            
            // Determine which quad to draw (original or fitted)
            if (uvBounds.useDrawRect) {
                // Create a fitted quad in original coordinate space
                drawQuad = Quad(uvBounds.drawRect);
            }
        }
        
        // NOW apply transformation to the (possibly fitted) quad
        Quad transformedQuad = drawQuad;
        if (attrs.getTransform() != glm::mat3(1.0f)) {  // not identity matrix
            for (int i = 0; i < 4; i++) {
                glm::vec3 transformed = attrs.getTransform() * glm::vec3(drawQuad.points[i].x, drawQuad.points[i].y, 1.0f);
                transformedQuad.points[i] = Point(transformed.x, transformed.y);
            }
        }
        
        // Check if quad is within drawable area
        if (transformedQuad.getBounds().intersection(port.drawableRect()).empty()) return;

        // Handle texture first (highest priority)
        if (texture && texture->width > 0 && texture->height > 0) {
            ImageOpenGL* imgOpenGL = static_cast<ImageOpenGL*>(texture);
            
            // Set up the image with this port if it's not already set
            if (imgOpenGL && imgOpenGL->mPort != &port) {
                imgOpenGL->setPort(&port);
            }
            
            // Apply texture opacity
            uint8 originalOpacity = texture->getOpacity();
            if (attrs.getFillOpacity() < 1.0f) {
                texture->setOpacity((uint8)(255 * attrs.getFillOpacity()));
            }
            
            FitType fitType = attrs.getFitType();
            
            // Bind the texture using the image's bindTexture method
            if (imgOpenGL) {
                imgOpenGL->bindTexture();
                port.setOpenGLModesForDrawing(texture->getOpacity() < 255, attrs.getBlendMode());
                
                // Set color to white so texture shows properly
                glColor4f(1.0f, 1.0f, 1.0f, (float)texture->getOpacity() / 255.0f);
                
                // Handle tile modes specially
                if (fitType == fit_Tile || fitType == fit_TileX || fitType == fit_TileY) {
                    // For tiling, calculate how many times to repeat the texture
                    float imgWidth = (float)texture->width;
                    float imgHeight = (float)texture->height;
                    Rect originalBounds = quad.getBounds();
                    float shapeWidth = originalBounds.width();
                    float shapeHeight = originalBounds.height();
                    
                    float uRepeat = (fitType == fit_Tile || fitType == fit_TileX) ? (shapeWidth / imgWidth) : 1.0f;
                    float vRepeat = (fitType == fit_Tile || fitType == fit_TileY) ? (shapeHeight / imgHeight) : 1.0f;
                    
                    // Scale UV max by repeat count, but keep buffer scaling
                    uvBounds.uMax = uvBounds.uMax * uRepeat;
                    uvBounds.vMax = uvBounds.vMax * vRepeat;
                    
                    // Set texture wrapping mode for tiling
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                }
                
                // Draw quad with texture coordinates
                // For non-rectangular quads, use a fan triangulation from the center
                // to minimize texture distortion. This creates 4 triangles sharing a center point.
                // Quad point indices: lftTop=0, rgtTop=1, rgtBot=2, lftBot=3
                
                // Calculate center point using bilinear interpolation (u=0.5, v=0.5)
                float centerX = (transformedQuad.points[lftTop].x + transformedQuad.points[rgtTop].x +
                                 transformedQuad.points[rgtBot].x + transformedQuad.points[lftBot].x) * 0.25f;
                float centerY = (transformedQuad.points[lftTop].y + transformedQuad.points[rgtTop].y +
                                 transformedQuad.points[rgtBot].y + transformedQuad.points[lftBot].y) * 0.25f;
                
                // Calculate center UV coordinates
                float centerU = (uvBounds.uMin + uvBounds.uMax) * 0.5f;
                float centerV = (uvBounds.vMin + uvBounds.vMax) * 0.5f;
                
                // Draw 4 triangles in a fan from center
                glBegin(GL_TRIANGLES);
                
                // Triangle 1: lftTop -> rgtTop -> center
                glTexCoord2f(uvBounds.uMin, uvBounds.vMin);
                glVertex2f(transformedQuad.points[lftTop].x, transformedQuad.points[lftTop].y);
                glTexCoord2f(uvBounds.uMax, uvBounds.vMin);
                glVertex2f(transformedQuad.points[rgtTop].x, transformedQuad.points[rgtTop].y);
                glTexCoord2f(centerU, centerV);
                glVertex2f(centerX, centerY);
                
                // Triangle 2: rgtTop -> rgtBot -> center
                glTexCoord2f(uvBounds.uMax, uvBounds.vMin);
                glVertex2f(transformedQuad.points[rgtTop].x, transformedQuad.points[rgtTop].y);
                glTexCoord2f(uvBounds.uMax, uvBounds.vMax);
                glVertex2f(transformedQuad.points[rgtBot].x, transformedQuad.points[rgtBot].y);
                glTexCoord2f(centerU, centerV);
                glVertex2f(centerX, centerY);
                
                // Triangle 3: rgtBot -> lftBot -> center
                glTexCoord2f(uvBounds.uMax, uvBounds.vMax);
                glVertex2f(transformedQuad.points[rgtBot].x, transformedQuad.points[rgtBot].y);
                glTexCoord2f(uvBounds.uMin, uvBounds.vMax);
                glVertex2f(transformedQuad.points[lftBot].x, transformedQuad.points[lftBot].y);
                glTexCoord2f(centerU, centerV);
                glVertex2f(centerX, centerY);
                
                // Triangle 4: lftBot -> lftTop -> center
                glTexCoord2f(uvBounds.uMin, uvBounds.vMax);
                glVertex2f(transformedQuad.points[lftBot].x, transformedQuad.points[lftBot].y);
                glTexCoord2f(uvBounds.uMin, uvBounds.vMin);
                glVertex2f(transformedQuad.points[lftTop].x, transformedQuad.points[lftTop].y);
                glTexCoord2f(centerU, centerV);
                glVertex2f(centerX, centerY);
                
                glEnd();
                
                // Restore texture wrapping mode if we changed it
                if (fitType == fit_Tile || fitType == fit_TileX || fitType == fit_TileY) {
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                }
                
                glDisable(GL_TEXTURE_2D);
                glDisable(GL_BLEND);
            }
            
            // Restore original opacity
            texture->setOpacity(originalOpacity);
        }
        // Handle gradients
        else if (attrs.getGradientType() != gradientType_None) {
            if (attrs.getGradientType() == gradientType_Linear) {
                // Get gradient start and end points
                Point gradientStart = attrs.getGradientStart();
                Point gradientEnd = attrs.getGradientEnd();
                Color startColor = attrs.getGradientStartColor();
                Color endColor = attrs.getGradientEndColor();
                
                // Apply fill opacity to gradient colors
                startColor.alpha *= attrs.getFillOpacity();
                endColor.alpha *= attrs.getFillOpacity();
                
                // Draw gradient directly with OpenGL using proper start/end points
                port.setOpenGLModesForDrawing((startColor.alpha < 1.0f) || (endColor.alpha < 1.0f), attrs.getBlendMode());
                
                // Calculate gradient vector and length
                float gradientDx = gradientEnd.x - gradientStart.x;
                float gradientDy = gradientEnd.y - gradientStart.y;
                float gradientLength = sqrt(gradientDx * gradientDx + gradientDy * gradientDy);
                
                // Helper function to calculate color at a point
                auto calculateGradientColor = [&](float x, float y) -> Color {
                    if (gradientLength == 0.0f) return startColor;
                    
                    // Project point onto gradient line
                    float dx = x - gradientStart.x;
                    float dy = y - gradientStart.y;
                    float projection = (dx * gradientDx + dy * gradientDy) / (gradientLength * gradientLength);
                    
                    // Clamp to [0, 1] range
                    projection = std::max(0.0f, std::min(1.0f, projection));
                    
                    // Interpolate colors
                    Color result;
                    result.red = startColor.red + (endColor.red - startColor.red) * projection;
                    result.green = startColor.green + (endColor.green - startColor.green) * projection;
                    result.blue = startColor.blue + (endColor.blue - startColor.blue) * projection;
                    result.alpha = startColor.alpha + (endColor.alpha - startColor.alpha) * projection;
                    return result;
                };
                
                // Use GL_QUADS for proper gradient interpolation on non-rectangular quads
                // Quad point indices: lftTop=0, rgtTop=1, rgtBot=2, lftBot=3
                glBegin(GL_QUADS);
                // lftTop (point 0)
                Color color0 = calculateGradientColor(transformedQuad.points[0].x, transformedQuad.points[0].y);
                glColor4f(color0.red, color0.green, color0.blue, color0.alpha);
                glVertex2f(transformedQuad.points[0].x, transformedQuad.points[0].y);
                // rgtTop (point 1)
                Color color1 = calculateGradientColor(transformedQuad.points[1].x, transformedQuad.points[1].y);
                glColor4f(color1.red, color1.green, color1.blue, color1.alpha);
                glVertex2f(transformedQuad.points[1].x, transformedQuad.points[1].y);
                // rgtBot (point 2)
                Color color2 = calculateGradientColor(transformedQuad.points[2].x, transformedQuad.points[2].y);
                glColor4f(color2.red, color2.green, color2.blue, color2.alpha);
                glVertex2f(transformedQuad.points[2].x, transformedQuad.points[2].y);
                // lftBot (point 3)
                Color color3 = calculateGradientColor(transformedQuad.points[3].x, transformedQuad.points[3].y);
                glColor4f(color3.red, color3.green, color3.blue, color3.alpha);
                glVertex2f(transformedQuad.points[3].x, transformedQuad.points[3].y);
                glEnd();
            }
            else if (attrs.getGradientType() == gradientType_Radial) {
                // Get radial gradient parameters
                Point center = attrs.getRadialGradientCenter();
                float radius = attrs.getRadialGradientRadius();
                Color centerColor = attrs.getRadialGradientCenterColor();
                Color endColor = attrs.getRadialGradientEndColor();
                
                // Apply fill opacity to gradient colors
                centerColor.alpha *= attrs.getFillOpacity();
                endColor.alpha *= attrs.getFillOpacity();
                
                // Draw radial gradient directly with OpenGL
                port.setOpenGLModesForDrawing((centerColor.alpha < 1.0f) || (endColor.alpha < 1.0f), attrs.getBlendMode());
                
                // Helper function to calculate color at a point based on distance from center
                auto calculateRadialGradientColor = [&](float x, float y) -> Color {
                    if (radius == 0.0f) return centerColor;
                    
                    // Calculate distance from center
                    float dx = x - center.x;
                    float dy = y - center.y;
                    float distance = sqrt(dx * dx + dy * dy);
                    
                    // Normalize distance by radius and clamp to [0, 1]
                    float t = std::max(0.0f, std::min(1.0f, distance / radius));
                    
                    // Interpolate colors
                    Color result;
                    result.red = centerColor.red + (endColor.red - centerColor.red) * t;
                    result.green = centerColor.green + (endColor.green - centerColor.green) * t;
                    result.blue = centerColor.blue + (endColor.blue - centerColor.blue) * t;
                    result.alpha = centerColor.alpha + (endColor.alpha - centerColor.alpha) * t;
                    return result;
                };
                
                // Draw as triangle fan from center point to create proper radial gradient
                glBegin(GL_TRIANGLE_FAN);
                
                // Center point - always gets the center color
                glColor4f(centerColor.red, centerColor.green, centerColor.blue, centerColor.alpha);
                glVertex2f(center.x, center.y);
                
                // Now add the 4 corners and close the fan
                // Bottom-left (point 0)
                Color color0 = calculateRadialGradientColor(transformedQuad.points[0].x, transformedQuad.points[0].y);
                glColor4f(color0.red, color0.green, color0.blue, color0.alpha);
                glVertex2f(transformedQuad.points[0].x, transformedQuad.points[0].y);
                
                // Bottom-right (point 1)
                Color color1 = calculateRadialGradientColor(transformedQuad.points[1].x, transformedQuad.points[1].y);
                glColor4f(color1.red, color1.green, color1.blue, color1.alpha);
                glVertex2f(transformedQuad.points[1].x, transformedQuad.points[1].y);
                
                // Top-right (point 2)
                Color color2 = calculateRadialGradientColor(transformedQuad.points[2].x, transformedQuad.points[2].y);
                glColor4f(color2.red, color2.green, color2.blue, color2.alpha);
                glVertex2f(transformedQuad.points[2].x, transformedQuad.points[2].y);
                
                // Top-left (point 3)
                Color color3 = calculateRadialGradientColor(transformedQuad.points[3].x, transformedQuad.points[3].y);
                glColor4f(color3.red, color3.green, color3.blue, color3.alpha);
                glVertex2f(transformedQuad.points[3].x, transformedQuad.points[3].y);
                
                // Close the fan by repeating the first corner
                glColor4f(color0.red, color0.green, color0.blue, color0.alpha);
                glVertex2f(transformedQuad.points[0].x, transformedQuad.points[0].y);
                
                glEnd();
            }
        } else if (fillColor.alpha > 0.0f) {
            // Fill with solid color using direct OpenGL
            port.setOpenGLModesForDrawing(fillColor.alpha < 1.0f, attrs.getBlendMode());
            glColor4f(fillColor.red, fillColor.green, fillColor.blue, fillColor.alpha);
            
            // Use GL_QUADS for proper rendering of non-rectangular quads
            // Quad point indices: lftTop=0, rgtTop=1, rgtBot=2, lftBot=3
            glBegin(GL_QUADS);
            glVertex2f(transformedQuad.points[0].x, transformedQuad.points[0].y); // lftTop
            glVertex2f(transformedQuad.points[1].x, transformedQuad.points[1].y); // rgtTop
            glVertex2f(transformedQuad.points[2].x, transformedQuad.points[2].y); // rgtBot
            glVertex2f(transformedQuad.points[3].x, transformedQuad.points[3].y); // lftBot
            glEnd();
        }

        // Draw outline if needed
        if (lineStyle != lineStyle_None && attrs.getLineThickness() > 0.0f && lineColor.alpha > 0.0f) {
            port.setOpenGLModesForDrawing(lineColor.alpha < 1.0f, attrs.getBlendMode());
            glColor4f(lineColor.red, lineColor.green, lineColor.blue, lineColor.alpha);
            
            if (attrs.getLineThickness() > 1.0f) {
                glLineWidth(attrs.getLineThickness());
            }
            
            glBegin(GL_LINE_LOOP);
            glVertex2f(transformedQuad.points[0].x, transformedQuad.points[0].y);
            glVertex2f(transformedQuad.points[1].x, transformedQuad.points[1].y);
            glVertex2f(transformedQuad.points[2].x, transformedQuad.points[2].y);
            glVertex2f(transformedQuad.points[3].x, transformedQuad.points[3].y);
            glEnd();
            
            if (attrs.getLineThickness() > 1.0f) {
                glLineWidth(1.0f);
            }
        }
        
        // Mark port as needing redraw
        port.mNeedRedraw = true;
    }

    void Port::drawPolygon(const Polygon& polygon, const Attributes& attrs) {
        // Get port implementation for OpenGL access
        PortImpl& port = static_cast<PortImpl&>(*this);

        // Apply colors with opacity
        Color lineColor = attrs.getLineColor();
        lineColor.alpha *= attrs.getLineOpacity();
        Color fillColor = attrs.getFillColor();
        fillColor.alpha *= attrs.getFillOpacity();
        LineStyle lineStyle = attrs.getLineStyle();

        // Determine the polygon to draw based on texture fitting (if texture is present)
        Polygon drawPolygon;
        TextureUVBounds uvBounds;
        uvBounds.uMin = uvBounds.vMin = 0.0f;
        uvBounds.uMax = uvBounds.vMax = 1.0f;
        uvBounds.useDrawRect = false;
        
        // Copy points from the original polygon
        for (size_t i = 0; i < polygon.getPointCount(); i++) {
            drawPolygon.addPoint(polygon.getPoint(i));
        }
        
        Image* texture = attrs.getTexture();
        if (texture) {
            // Calculate fit based on ORIGINAL polygon bounds (before transformation)
            Rect originalBounds = polygon.getBounds();
            FitType fitType = attrs.getFitType();
            uvBounds = calculateTextureFitUVs(texture, originalBounds, fitType);
            
            // For fit modes that adjust the drawing area, scale the polygon
            if (uvBounds.useDrawRect) {
                float scaleX = uvBounds.drawRect.width() / originalBounds.width();
                float scaleY = uvBounds.drawRect.height() / originalBounds.height();
                Point originalCenter = originalBounds.centerPoint();
                Point newCenter = uvBounds.drawRect.centerPoint();
                
                // Scale and reposition each point of the polygon
                for (size_t i = 0; i < drawPolygon.getPointCount(); i++) {
                    Point p = drawPolygon.getPoint(i);
                    float dx = p.x - originalCenter.x;
                    float dy = p.y - originalCenter.y;
                    p.x = newCenter.x + dx * scaleX;
                    p.y = newCenter.y + dy * scaleY;
                    drawPolygon.setPoint(i, p);
                }
            }
        }
        
        // NOW apply transformation to the (possibly fitted) polygon
        Polygon transformedPolygon;
        for (size_t i = 0; i < drawPolygon.getPointCount(); i++) {
            transformedPolygon.addPoint(drawPolygon.getPoint(i));
        }
        
        if (attrs.getTransform() != glm::mat3(1.0f)) {  // not identity matrix
            // Transform all points in the polygon
            for (size_t i = 0; i < drawPolygon.getPointCount(); i++) {
                Point originalPoint = drawPolygon.getPoint(i);
                glm::vec3 transformed = attrs.getTransform() * glm::vec3(originalPoint.x, originalPoint.y, 1.0f);
                transformedPolygon.setPoint(i, Point(transformed.x, transformed.y));
            }
        }
        
        // Check if polygon is within drawable area
        if (transformedPolygon.empty()) return;
        if (transformedPolygon.getBounds().intersection(port.drawableRect()).empty()) return;

        // Handle texture first (highest priority)
        if (texture) {
            // Apply texture opacity
            uint8 originalOpacity = texture->getOpacity();
            if (attrs.getFillOpacity() < 1.0f) {
                texture->setOpacity((uint8)(255 * attrs.getFillOpacity()));
            }
            
            // For polygons, we need to calculate texture coordinates based on original bounding box
            Rect originalBounds = polygon.getBounds();
            Rect drawBounds = drawPolygon.getBounds();
            FitType fitType = attrs.getFitType();
            
            // Check if texture is an ImageStrip
            ImageStrip* imgStrip = dynamic_cast<ImageStrip*>(texture);
            if (imgStrip && imgStrip->frames > 0) {
                int frame = attrs.getFrame();
                if (frame < 0 || frame >= imgStrip->frames) {
                    frame = 0; // Default to first frame
                }
                // For ImageStrip, draw each triangle with texture coordinates
                // Pass both transformed (for drawing) and fitted (for UV mapping)
                drawTexturedPolygon(texture, transformedPolygon, drawPolygon, drawBounds, fitType);
            } else {
                // Draw regular texture on polygon
                // Pass both transformed (for drawing) and fitted (for UV mapping)
                drawTexturedPolygon(texture, transformedPolygon, drawPolygon, drawBounds, fitType);
            }
            
            // Restore original opacity
            texture->setOpacity(originalOpacity);
        }
        // Handle gradients
        else if (attrs.getGradientType() != gradientType_None) {
            if (attrs.getGradientType() == gradientType_Linear) {
                // Get gradient start and end points
                Point gradientStart = attrs.getGradientStart();
                Point gradientEnd = attrs.getGradientEnd();
                Color startColor = attrs.getGradientStartColor();
                Color endColor = attrs.getGradientEndColor();
                
                // Apply fill opacity to gradient colors
                startColor.alpha *= attrs.getFillOpacity();
                endColor.alpha *= attrs.getFillOpacity();
                
                // Draw gradient directly with OpenGL using proper start/end points
                port.setOpenGLModesForDrawing((startColor.alpha < 1.0f) || (endColor.alpha < 1.0f), attrs.getBlendMode());
                
                // Calculate gradient vector and length
                float gradientDx = gradientEnd.x - gradientStart.x;
                float gradientDy = gradientEnd.y - gradientStart.y;
                float gradientLength = sqrt(gradientDx * gradientDx + gradientDy * gradientDy);
                
                // Helper function to calculate color at a point
                auto calculateGradientColor = [&](float x, float y) -> Color {
                    if (gradientLength == 0.0f) return startColor;
                    
                    // Project point onto gradient line
                    float dx = x - gradientStart.x;
                    float dy = y - gradientStart.y;
                    float projection = (dx * gradientDx + dy * gradientDy) / (gradientLength * gradientLength);
                    
                    // Clamp to [0, 1] range
                    projection = std::max(0.0f, std::min(1.0f, projection));
                    
                    // Interpolate colors
                    Color result;
                    result.red = startColor.red + (endColor.red - startColor.red) * projection;
                    result.green = startColor.green + (endColor.green - startColor.green) * projection;
                    result.blue = startColor.blue + (endColor.blue - startColor.blue) * projection;
                    result.alpha = startColor.alpha + (endColor.alpha - startColor.alpha) * projection;
                    return result;
                };
                
                // Triangulate the polygon and draw with gradient colors
                size_t pointCount = transformedPolygon.getPointCount();
                if (pointCount >= 3) {
                    // Use triangle fan for simple polygons
                    glBegin(GL_TRIANGLE_FAN);
                    
                    // First vertex (center-ish point for fan)
                    Point centerPoint = transformedPolygon.getPoint(0);
                    Color centerColor = calculateGradientColor(centerPoint.x, centerPoint.y);
                    glColor4f(centerColor.red, centerColor.green, centerColor.blue, centerColor.alpha);
                    glVertex2f(centerPoint.x, centerPoint.y);
                    
                    // Add all vertices with their gradient colors
                    for (size_t i = 0; i < pointCount; i++) {
                        Point p = transformedPolygon.getPoint(i);
                        Color vertexColor = calculateGradientColor(p.x, p.y);
                        glColor4f(vertexColor.red, vertexColor.green, vertexColor.blue, vertexColor.alpha);
                        glVertex2f(p.x, p.y);
                    }
                    
                    // Close the fan by repeating the first vertex
                    Point firstPoint = transformedPolygon.getPoint(0);
                    Color firstColor = calculateGradientColor(firstPoint.x, firstPoint.y);
                    glColor4f(firstColor.red, firstColor.green, firstColor.blue, firstColor.alpha);
                    glVertex2f(firstPoint.x, firstPoint.y);
                    
                    glEnd();
                }
            }
            else if (attrs.getGradientType() == gradientType_Radial) {
                // Get radial gradient parameters
                Point center = attrs.getRadialGradientCenter();
                float radius = attrs.getRadialGradientRadius();
                Color centerColor = attrs.getRadialGradientCenterColor();
                Color endColor = attrs.getRadialGradientEndColor();
                
                // Apply fill opacity to gradient colors
                centerColor.alpha *= attrs.getFillOpacity();
                endColor.alpha *= attrs.getFillOpacity();
                
                // Draw radial gradient directly with OpenGL
                port.setOpenGLModesForDrawing((centerColor.alpha < 1.0f) || (endColor.alpha < 1.0f), attrs.getBlendMode());
                
                // Helper function to calculate color at a point based on distance from center
                auto calculateRadialGradientColor = [&](float x, float y) -> Color {
                    if (radius == 0.0f) return centerColor;
                    
                    // Calculate distance from center
                    float dx = x - center.x;
                    float dy = y - center.y;
                    float distance = sqrt(dx * dx + dy * dy);
                    
                    // Normalize distance by radius and clamp to [0, 1]
                    float t = std::max(0.0f, std::min(1.0f, distance / radius));
                    
                    // Interpolate colors
                    Color result;
                    result.red = centerColor.red + (endColor.red - centerColor.red) * t;
                    result.green = centerColor.green + (endColor.green - centerColor.green) * t;
                    result.blue = centerColor.blue + (endColor.blue - centerColor.blue) * t;
                    result.alpha = centerColor.alpha + (endColor.alpha - centerColor.alpha) * t;
                    return result;
                };
                
                // Draw as triangle fan from gradient center point to create proper radial gradient
                size_t pointCount = transformedPolygon.getPointCount();
                if (pointCount >= 3) {
                    glBegin(GL_TRIANGLE_FAN);
                    
                    // Center point of the radial gradient - always gets the center color
                    glColor4f(centerColor.red, centerColor.green, centerColor.blue, centerColor.alpha);
                    glVertex2f(center.x, center.y);
                    
                    // Add all polygon vertices with their gradient colors
                    for (size_t i = 0; i < pointCount; i++) {
                        Point p = transformedPolygon.getPoint(i);
                        Color vertexColor = calculateRadialGradientColor(p.x, p.y);
                        glColor4f(vertexColor.red, vertexColor.green, vertexColor.blue, vertexColor.alpha);
                        glVertex2f(p.x, p.y);
                    }
                    
                    // Close the fan by repeating the first polygon vertex
                    Point firstPoint = transformedPolygon.getPoint(0);
                    Color firstVertexColor = calculateRadialGradientColor(firstPoint.x, firstPoint.y);
                    glColor4f(firstVertexColor.red, firstVertexColor.green, firstVertexColor.blue, firstVertexColor.alpha);
                    glVertex2f(firstPoint.x, firstPoint.y);
                    
                    glEnd();
                }
            }
        } else if (attrs.hasFill()) {
            // Fill with solid color using direct OpenGL
            port.setOpenGLModesForDrawing(fillColor.alpha < 1.0f, attrs.getBlendMode());
            glColor4f(fillColor.red, fillColor.green, fillColor.blue, fillColor.alpha);
            
            size_t pointCount = transformedPolygon.getPointCount();
            if (pointCount < 3) return; // Need at least 3 points for a polygon

            // Check if polygon is self-intersecting or complex
            bool needsTessellation = (pointCount > 3) && 
                                    (pointCount > 6 || transformedPolygon.isSelfIntersecting());
            
            if (pointCount == 3) {
                // Simple triangle - just draw it
                glBegin(GL_TRIANGLES);
                for (size_t i = 0; i < 3; i++) {
                    Point p = transformedPolygon.getPoint(i);
                    glVertex2f(p.x, p.y);
                }
                glEnd();
            } else if (needsTessellation) {
                // Use libtess2 tessellation for self-intersecting or complex polygons
                std::vector<Point> triangles = transformedPolygon.tessellate();
                
                // Render each triangle
                glBegin(GL_TRIANGLES);
                for (size_t i = 0; i < triangles.size(); i++) {
                    Point p = triangles[i];
                    glVertex2f(p.x, p.y);
                }
                glEnd();
            } else {
                // Use GL_TRIANGLE_FAN for simple convex polygons (4-6 points, not self-intersecting)
                glBegin(GL_TRIANGLE_FAN);
                Point center = transformedPolygon.getPoint(0);
                glVertex2f(center.x, center.y);
                
                for (size_t i = 1; i < pointCount; i++) {
                    Point p = transformedPolygon.getPoint(i);
                    glVertex2f(p.x, p.y);
                }
                if (pointCount > 2) {
                    Point second = transformedPolygon.getPoint(1);
                    glVertex2f(second.x, second.y);
                }
                glEnd();
            }
        }
 
        // Draw outline if needed
        if (lineStyle != lineStyle_None && attrs.getLineThickness() > 0.0f && lineColor.alpha > 0.0f) {
            port.setOpenGLModesForDrawing(lineColor.alpha < 1.0f, attrs.getBlendMode());
            glColor4f(lineColor.red, lineColor.green, lineColor.blue, lineColor.alpha);
            
            if (attrs.getLineThickness() > 1.0f) {
                glLineWidth(attrs.getLineThickness());
            }
            
            glBegin(GL_LINE_LOOP);
            size_t pointCount = transformedPolygon.getPointCount();
            for (size_t i = 0; i < pointCount; i++) {
                Point p = transformedPolygon.getPoint(i);
                glVertex2f(p.x, p.y);
            }
            glEnd();
            
            if (attrs.getLineThickness() > 1.0f) {
                glLineWidth(1.0f);
            }
        }
        
        // Mark port as needing redraw
        port.mNeedRedraw = true;
    }

    void Port::drawSpline(const Spline& spline, const Attributes& attrs) {
        if (!attrs.hasLine()) return;
        // Apply colors with opacity
        Color lineColor = attrs.getLineColor();
        lineColor.alpha *= attrs.getLineOpacity();

        // Calculate number of samples based on actual segment count
        // Use 20 samples per segment for smooth curves
        int samplesPerSegment = 20;
        float maxU = spline.getMaxU();
        int segmentCount = (int)maxU;  // maxU equals the number of segments
        int numSegments = segmentCount * samplesPerSegment;

        // Get port implementation for OpenGL access
        PortImpl& port = static_cast<PortImpl&>(*this);
        
        // FIXME: add bounds checking

        // Draw the spline using existing Port method for now
        if (numSegments < 2) numSegments = 2;

        if (maxU <= 0.0f) return;  // No segments to draw
        
        port.setOpenGLModesForDrawing(lineColor.alpha < 1.0f, attrs.getBlendMode());
        glColor4f(lineColor.red, lineColor.green, lineColor.blue, lineColor.alpha); 
        if (attrs.getLineThickness() > 1.0f) {
            glLineWidth(attrs.getLineThickness());
        }

        Point lastPoint = spline.getFirstOrder(0.0f);
        glBegin(GL_LINE_STRIP);
        glVertex2f(lastPoint.x, lastPoint.y);
        for (int i = 0; i <= numSegments; i++) {
            float u = ((float)i / (float)numSegments) * maxU;
            Point currentPoint = spline.getFirstOrder(u);
            if (currentPoint.distanceSquared(lastPoint) < 1.0f) continue; // skip if the point is too close to the last point
            glVertex2f(currentPoint.x, currentPoint.y);
            lastPoint = currentPoint;
        }
        glEnd();
        
        if (attrs.getLineThickness() > 1.0f) {
            glLineWidth(1.0f);
        }

     }

    void Port::drawEllipse(const Point& center, float xRadius, float yRadius, const Attributes& attrs) {
        // Get port implementation for OpenGL access
        PortImpl& port = static_cast<PortImpl&>(*this);
        
        // Apply colors with opacity
        Color lineColor = attrs.getLineColor();
        lineColor.alpha *= attrs.getLineOpacity();
        Color fillColor = attrs.getFillColor();
        fillColor.alpha *= attrs.getFillOpacity();
        LineStyle lineStyle = attrs.getLineStyle();

        // Determine the radii to draw based on texture fitting (if texture is present)
        float drawXRadius = xRadius;
        float drawYRadius = yRadius;
        Point drawCenter = center;
        TextureUVBounds uvBounds;
        uvBounds.uMin = uvBounds.vMin = 0.0f;
        uvBounds.uMax = uvBounds.vMax = 1.0f;
        uvBounds.useDrawRect = false;
        
        Image* texture = attrs.getTexture();
        if (texture) {
            // Calculate fit based on ORIGINAL ellipse bounds (before transformation)
            Rect originalBounds(center.x - xRadius, center.y - yRadius,
                              center.x + xRadius, center.y + yRadius);
            FitType fitType = attrs.getFitType();
            uvBounds = calculateTextureFitUVs(texture, originalBounds, fitType);
            
            // Adjust radii based on fitted rectangle
            if (uvBounds.useDrawRect) {
                drawXRadius = uvBounds.drawRect.width() / 2.0f;
                drawYRadius = uvBounds.drawRect.height() / 2.0f;
                drawCenter = uvBounds.drawRect.centerPoint();
            }
        }
        
        // NOW apply transformation to the (possibly fitted) ellipse
        bool hasTransform = (attrs.getTransform() != glm::mat3(1.0f));
        Point transformedCenter = drawCenter;
        if (hasTransform) {
            glm::vec3 transformed = attrs.getTransform() * glm::vec3(drawCenter.x, drawCenter.y, 1.0f);
            transformedCenter = Point(transformed.x, transformed.y);
        }
        
        // Calculate transformed bounds for culling
        Rect transformedBounds(transformedCenter.x - drawXRadius, transformedCenter.y - drawYRadius,
                             transformedCenter.x + drawXRadius, transformedCenter.y + drawYRadius);

        // Handle texture first (highest priority)
        if (texture) {
            ImageOpenGL* imgOpenGL = static_cast<ImageOpenGL*>(texture);
            
            // Set up the image with this port if it's not already set
            if (imgOpenGL && imgOpenGL->mPort != &port) {
                imgOpenGL->setPort(&port);
            }
            
            // Apply texture opacity
            uint8 originalOpacity = texture->getOpacity();
            if (attrs.getFillOpacity() < 1.0f) {
                texture->setOpacity((uint8)(255 * attrs.getFillOpacity()));
            }
            
            FitType fitType = attrs.getFitType();
            
            // Bind the texture using the image's bindTexture method
            if (imgOpenGL) {
                imgOpenGL->bindTexture();
                port.setOpenGLModesForDrawing(texture->getOpacity() < 255, attrs.getBlendMode());
                
                // Set color to white so texture shows properly
                glColor4f(1.0f, 1.0f, 1.0f, (float)texture->getOpacity() / 255.0f);
            
                // Handle tile modes specially
                if (fitType == fit_Tile || fitType == fit_TileX || fitType == fit_TileY) {
                    float imgWidth = (float)texture->width;
                    float imgHeight = (float)texture->height;
                    float shapeWidth = 2.0f * drawXRadius;
                    float shapeHeight = 2.0f * drawYRadius;
                    
                    float uRepeat = (fitType == fit_Tile || fitType == fit_TileX) ? (shapeWidth / imgWidth) : 1.0f;
                    float vRepeat = (fitType == fit_Tile || fitType == fit_TileY) ? (shapeHeight / imgHeight) : 1.0f;
                    
                    uvBounds.uMax = uvBounds.uMax * uRepeat;
                    uvBounds.vMax = uvBounds.vMax * vRepeat;
                    
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                }
            
                // Draw ellipse using triangle fan with rectangular texture mapping
                const int segments = 32; // Number of segments for smooth circle
                glBegin(GL_TRIANGLE_FAN);
                
                // Center point with center UV coordinates
                float centerU = (uvBounds.uMin + uvBounds.uMax) / 2.0f;
                float centerV = (uvBounds.vMin + uvBounds.vMax) / 2.0f;
                glTexCoord2f(centerU, centerV);
                glVertex2f(transformedCenter.x, transformedCenter.y);
                
                // Calculate bounds for UV mapping (in original space)
                Rect uvMappingBounds(drawCenter.x - drawXRadius, drawCenter.y - drawYRadius,
                                    drawCenter.x + drawXRadius, drawCenter.y + drawYRadius);
                
                for (int i = 0; i <= segments; i++) {
                    float angle = 2.0f * M_PI * i / segments;
                    float x = drawCenter.x + drawXRadius * cos(angle);
                    float y = drawCenter.y + drawYRadius * sin(angle);
                    
                    // Apply transformation to the vertex
                    float transformedX = x;
                    float transformedY = y;
                    if (hasTransform) {
                        glm::vec3 transformed = attrs.getTransform() * glm::vec3(x, y, 1.0f);
                        transformedX = transformed.x;
                        transformedY = transformed.y;
                    }
                    
                    // Calculate rectangular texture coordinates (not radial)
                    // Map based on original (untransformed) position
                    float texU = uvBounds.uMin + (x - uvMappingBounds.left) / uvMappingBounds.width() * (uvBounds.uMax - uvBounds.uMin);
                    float texV = uvBounds.vMin + (y - uvMappingBounds.top) / uvMappingBounds.height() * (uvBounds.vMax - uvBounds.vMin);
                    glTexCoord2f(texU, texV);
                    glVertex2f(transformedX, transformedY);
                }
                glEnd();
                
                // Restore texture wrapping mode if we changed it
                if (fitType == fit_Tile || fitType == fit_TileX || fitType == fit_TileY) {
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                }
                
                glDisable(GL_TEXTURE_2D);
                glDisable(GL_BLEND);
            }
            
            // Restore original opacity
            texture->setOpacity(originalOpacity);
        }
        // Handle gradients
        else if (attrs.getGradientType() == gradientType_Linear) {
            // Get gradient start and end points
            Point gradientStart = attrs.getGradientStart();
            Point gradientEnd = attrs.getGradientEnd();
            Color startColor = attrs.getGradientStartColor();
            Color endColor = attrs.getGradientEndColor();
            
            // Apply fill opacity to gradient colors
            startColor.alpha *= attrs.getFillOpacity();
            endColor.alpha *= attrs.getFillOpacity();
            
            // Draw linear gradient directly with OpenGL
            port.setOpenGLModesForDrawing((startColor.alpha < 1.0f) || (endColor.alpha < 1.0f), attrs.getBlendMode());
            
            // Calculate gradient vector and length
            float gradientDx = gradientEnd.x - gradientStart.x;
            float gradientDy = gradientEnd.y - gradientStart.y;
            float gradientLength = sqrt(gradientDx * gradientDx + gradientDy * gradientDy);
            
            // Helper function to calculate color at a point
            auto calculateGradientColor = [&](float x, float y) -> Color {
                if (gradientLength == 0.0f) return startColor;
                
                // Project point onto gradient line
                float dx = x - gradientStart.x;
                float dy = y - gradientStart.y;
                float projection = (dx * gradientDx + dy * gradientDy) / (gradientLength * gradientLength);
                
                // Clamp to [0, 1] range
                projection = std::max(0.0f, std::min(1.0f, projection));
                
                // Interpolate colors
                Color result;
                result.red = startColor.red + (endColor.red - startColor.red) * projection;
                result.green = startColor.green + (endColor.green - startColor.green) * projection;
                result.blue = startColor.blue + (endColor.blue - startColor.blue) * projection;
                result.alpha = startColor.alpha + (endColor.alpha - startColor.alpha) * projection;
                return result;
            };
            
            // Draw ellipse using triangle fan with gradient colors
            const int segments = 32;
            glBegin(GL_TRIANGLE_FAN);
            
            // Center point
            Color centerColor = calculateGradientColor(transformedCenter.x, transformedCenter.y);
            glColor4f(centerColor.red, centerColor.green, centerColor.blue, centerColor.alpha);
            glVertex2f(transformedCenter.x, transformedCenter.y);
            
            for (int i = 0; i <= segments; i++) {
                float angle = 2.0f * M_PI * i / segments;
                float x = center.x + xRadius * cos(angle);
                float y = center.y + yRadius * sin(angle);
                
                // Apply transformation to each vertex
                if (hasTransform) {
                    glm::vec3 transformed = attrs.getTransform() * glm::vec3(x, y, 1.0f);
                    Color vertexColor = calculateGradientColor(transformed.x, transformed.y);
                    glColor4f(vertexColor.red, vertexColor.green, vertexColor.blue, vertexColor.alpha);
                    glVertex2f(transformed.x, transformed.y);
                } else {
                    Color vertexColor = calculateGradientColor(x, y);
                    glColor4f(vertexColor.red, vertexColor.green, vertexColor.blue, vertexColor.alpha);
                    glVertex2f(x, y);
                }
            }
            glEnd();
        }
        else if (attrs.getGradientType() == gradientType_Radial) {
            // Get radial gradient parameters
            Point gradCenter = attrs.getRadialGradientCenter();
            float gradRadius = attrs.getRadialGradientRadius();
            Color centerColor = attrs.getRadialGradientCenterColor();
            Color endColor = attrs.getRadialGradientEndColor();
            
            // Apply fill opacity to gradient colors
            centerColor.alpha *= attrs.getFillOpacity();
            endColor.alpha *= attrs.getFillOpacity();
            
            // Draw radial gradient directly with OpenGL
            port.setOpenGLModesForDrawing((centerColor.alpha < 1.0f) || (endColor.alpha < 1.0f), attrs.getBlendMode());
            
            // Helper function to calculate color at a point based on distance from center
            auto calculateRadialGradientColor = [&](float x, float y) -> Color {
                if (gradRadius == 0.0f) return centerColor;
                
                // Calculate distance from center
                float dx = x - gradCenter.x;
                float dy = y - gradCenter.y;
                float distance = sqrt(dx * dx + dy * dy);
                
                // Normalize distance by radius and clamp to [0, 1]
                float t = std::max(0.0f, std::min(1.0f, distance / gradRadius));
                
                // Interpolate colors
                Color result;
                result.red = centerColor.red + (endColor.red - centerColor.red) * t;
                result.green = centerColor.green + (endColor.green - centerColor.green) * t;
                result.blue = centerColor.blue + (endColor.blue - centerColor.blue) * t;
                result.alpha = centerColor.alpha + (endColor.alpha - centerColor.alpha) * t;
                return result;
            };
            
            // Draw ellipse using triangle fan from gradient center with radial gradient colors
            const int segments = 32;
            glBegin(GL_TRIANGLE_FAN);
            
            // Center point of the radial gradient - always gets the center color
            glColor4f(centerColor.red, centerColor.green, centerColor.blue, centerColor.alpha);
            glVertex2f(gradCenter.x, gradCenter.y);
            
            for (int i = 0; i <= segments; i++) {
                float angle = 2.0f * M_PI * i / segments;
                float x = center.x + xRadius * cos(angle);
                float y = center.y + yRadius * sin(angle);
                
                // Apply transformation to each vertex
                if (hasTransform) {
                    glm::vec3 transformed = attrs.getTransform() * glm::vec3(x, y, 1.0f);
                    Color vertexColor = calculateRadialGradientColor(transformed.x, transformed.y);
                    glColor4f(vertexColor.red, vertexColor.green, vertexColor.blue, vertexColor.alpha);
                    glVertex2f(transformed.x, transformed.y);
                } else {
                    Color vertexColor = calculateRadialGradientColor(x, y);
                    glColor4f(vertexColor.red, vertexColor.green, vertexColor.blue, vertexColor.alpha);
                    glVertex2f(x, y);
                }
            }
            glEnd();
        }
        // Fill oval if needed using direct OpenGL
        else if (attrs.hasFill()) {
            port.setOpenGLModesForDrawing(fillColor.alpha < 1.0f, attrs.getBlendMode());
            glColor4f(fillColor.red, fillColor.green, fillColor.blue, fillColor.alpha);
            
            // Draw ellipse using triangle fan
            const int segments = 32; // Number of segments for smooth circle
            glBegin(GL_TRIANGLE_FAN);
            
            // Use the pre-calculated transformed center
            glVertex2f(transformedCenter.x, transformedCenter.y); // Center point
            
            for (int i = 0; i <= segments; i++) {
                float angle = 2.0f * M_PI * i / segments;
                float x = center.x + xRadius * cos(angle);
                float y = center.y + yRadius * sin(angle);
                
                // Apply transformation to each vertex
                if (hasTransform) {
                    glm::vec3 transformed = attrs.getTransform() * glm::vec3(x, y, 1.0f);
                    glVertex2f(transformed.x, transformed.y);
                } else {
                    glVertex2f(x, y);
                }
            }
            glEnd();
        }

        // Draw outline if needed using direct OpenGL
        if (lineStyle != lineStyle_None && attrs.getLineThickness() > 0.0f && lineColor.alpha > 0.0f) {
            port.setOpenGLModesForDrawing(lineColor.alpha < 1.0f, attrs.getBlendMode());
            glColor4f(lineColor.red, lineColor.green, lineColor.blue, lineColor.alpha);
            
            if (attrs.getLineThickness() > 1.0f) {
                glLineWidth(attrs.getLineThickness());
            }
            
            // Draw ellipse outline using line loop
            const int segments = 32; // Number of segments for smooth circle
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < segments; i++) {
                float angle = 2.0f * M_PI * i / segments;
                float x = center.x + xRadius * cos(angle);
                float y = center.y + yRadius * sin(angle);
                
                // Apply transformation to each vertex
                if (hasTransform) {
                    glm::vec3 transformed = attrs.getTransform() * glm::vec3(x, y, 1.0f);
                    glVertex2f(transformed.x, transformed.y);
                } else {
                    glVertex2f(x, y);
                }
            }
            glEnd();
            
            if (attrs.getLineThickness() > 1.0f) {
                glLineWidth(1.0f);
            }
        }
        
        // Mark port as needing redraw
        port.mNeedRedraw = true;
    }


    void Port::drawArc(const Point& center, float xRadius, float yRadius, float startAngle, float endAngle, const Attributes& attrs) {
        if (!attrs.hasLine()) return;
        // Apply transformation if needed
        Point transformedCenter = center;
        bool needsTransform = false;
        if (attrs.getTransform() != glm::mat3(1.0f)) {  // not identity matrix
            glm::vec3 transformed = attrs.getTransform() * glm::vec3(center.x, center.y, 1.0f);
            transformedCenter = Point(transformed.x, transformed.y);
            needsTransform = true;
        }

        // Get port implementation for OpenGL access
        PortImpl& port = static_cast<PortImpl&>(*this);
        
        // Check if arc is within drawable area
        Rect arcBounds = Rect(transformedCenter.x - xRadius, transformedCenter.y - yRadius, 
                             transformedCenter.x + xRadius, transformedCenter.y + yRadius);
        if (arcBounds.intersection(port.drawableRect()).empty()) return;

        // Apply colors with opacity
        Color lineColor = attrs.getLineColor();
        lineColor.alpha *= attrs.getLineOpacity();

        // Draw arc using direct OpenGL
        port.setOpenGLModesForDrawing(lineColor.alpha < 1.0f, attrs.getBlendMode());
        glColor4f(lineColor.red, lineColor.green, lineColor.blue, lineColor.alpha);
        
        if (attrs.getLineThickness() > 1.0f) {
            glLineWidth(attrs.getLineThickness());
        }
        
        // Draw arc using line strip
        const int segments = 32; // Number of segments for smooth arc
        float angleStep = (endAngle - startAngle) / segments;
        
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= segments; i++) {
            float angle = startAngle + i * angleStep;
            // Convert from mathematical angle (0 = right) to screen angle (0 = up)
            float screenAngle = angle - M_PI/2;
            float x = center.x + xRadius * cos(screenAngle);
            float y = center.y + yRadius * sin(screenAngle);
            if (needsTransform) {
                glm::vec3 transformed = attrs.getTransform() * glm::vec3(x, y, 1.0f);
                glVertex2f(transformed.x, transformed.y);
            }
            else {
                glVertex2f(x, y);
            }
        }
        glEnd();
        
        if (attrs.getLineThickness() > 1.0f) {
            glLineWidth(1.0f);
        }
        
        // Mark port as needing redraw
        port.mNeedRedraw = true;
    }

    void MakeRoundedRectPolygon(const Rect& rect, float xRadius, float yRadius, Polygon& polygon) {
        if (xRadius > rect.width() / 2) {
            xRadius = rect.width() / 2;
        }
        if (yRadius > rect.height() / 2) {
            yRadius = rect.height() / 2;
        }    
        // Create a proper rounded rectangle polygon
        const int segments = 8; // Number of segments per quarter circle     
        // Top edge (left to right)
        polygon.addPoint(Point(rect.left + xRadius, rect.top));
        polygon.addPoint(Point(rect.right - xRadius, rect.top));       
        // Top-right corner arc
        Point topRightCenter = Point(rect.right - xRadius, rect.top + yRadius);
        for (int i = 1; i < segments; i++) {
            float angle = -M_PI/2 + (i * M_PI/2) / segments; // -90° to 0°
            float x = topRightCenter.x + xRadius * cos(angle);
            float y = topRightCenter.y + yRadius * sin(angle);
            polygon.addPoint(Point(x, y));
        }    
        // Right edge (top to bottom)
        polygon.addPoint(Point(rect.right, rect.bottom - yRadius));     
        // Bottom-right corner arc
        Point bottomRightCenter = Point(rect.right - xRadius, rect.bottom - yRadius);
        for (int i = 1; i < segments; i++) {
            float angle = 0 + (i * M_PI/2) / segments; // 0° to 90°
            float x = bottomRightCenter.x + xRadius * cos(angle);
            float y = bottomRightCenter.y + yRadius * sin(angle);
            polygon.addPoint(Point(x, y));
        }  
        // Bottom edge (right to left)
        polygon.addPoint(Point(rect.left + xRadius, rect.bottom));      
        // Bottom-left corner arc
        Point bottomLeftCenter = Point(rect.left + xRadius, rect.bottom - yRadius);
        for (int i = 1; i < segments; i++) {
            float angle = M_PI/2 + (i * M_PI/2) / segments; // 90° to 180°
            float x = bottomLeftCenter.x + xRadius * cos(angle);
            float y = bottomLeftCenter.y + yRadius * sin(angle);
            polygon.addPoint(Point(x, y));
        }   
        // Left edge (bottom to top)
        polygon.addPoint(Point(rect.left, rect.top + yRadius));
        // Top-left corner arc
        Point topLeftCenter = Point(rect.left + xRadius, rect.top + yRadius);
        for (int i = 1; i < segments; i++) {
            float angle = M_PI + (i * M_PI/2) / segments; // 180° to 270°
            float x = topLeftCenter.x + xRadius * cos(angle);
            float y = topLeftCenter.y + yRadius * sin(angle);
            polygon.addPoint(Point(x, y));
        }
    }

    // -----------------------------------------------------------------------------------
    // New Renderer interface methods for images, drawings, text, and spheres
    // -----------------------------------------------------------------------------------

    void Port::drawImage(Image* img, const Point& loc, const Attributes& attrs) {
        if (!img) return;
        
        // If there's a transformation (rotation/scale/etc), we need to draw as a quad
        if (attrs.getTransform() != glm::mat3(1.0f)) {
            // Create a rectangle for the image at the given location
            Rect imageRect(loc.x, loc.y, loc.x + img->width, loc.y + img->height);
            
            // Use the drawImage(Rect) version which handles transformations properly
            drawImage(img, imageRect, attrs);
            return;
        }
        
        // No transformation - use simple point drawing
        // Save current image opacity
        uint8 originalOpacity = img->getOpacity();
        
        // Apply opacity from attributes
        if (attrs.getFillOpacity() < 1.0f) {
            img->setOpacity((uint8)(255 * attrs.getFillOpacity()));
        }
        
        // Handle ImageStrip frame selection
        ImageStrip* imgStrip = dynamic_cast<ImageStrip*>(img);
        if (imgStrip && imgStrip->frames > 0) {
            int frame = attrs.getFrame();
            if (frame < 0 || frame >= imgStrip->frames) {
                frame = 0; // Default to first frame
            }
            drawImage(imgStrip, frame, loc);
        } else {
            drawImage(img, loc);
        }
        
        // Restore original opacity
        img->setOpacity(originalOpacity);
    }

    void Port::drawImage(Image* img, const Rect& rect, const Attributes& attrs) {
        drawImage(img, Quad(rect), attrs);
    }
    
    void Port::drawImage(Image* img, const Quad& quad, const Attributes& attrs) {
        if (!img) return;
        
        // Apply transformation if needed
        if (attrs.getTransform() != glm::mat3(1.0f)) {
            // Transform all four corners of the quad
            glm::vec3 topLeft = attrs.getTransform() * glm::vec3(quad.points[0].x, quad.points[0].y, 1.0f);
            glm::vec3 topRight = attrs.getTransform() * glm::vec3(quad.points[1].x, quad.points[1].y, 1.0f);
            glm::vec3 bottomRight = attrs.getTransform() * glm::vec3(quad.points[2].x, quad.points[2].y, 1.0f);
            glm::vec3 bottomLeft = attrs.getTransform() * glm::vec3(quad.points[3].x, quad.points[3].y, 1.0f);
            
            // Create transformed quad
            Quad transformedQuad;
            transformedQuad.points[0] = Point(topLeft.x, topLeft.y);
            transformedQuad.points[1] = Point(topRight.x, topRight.y);
            transformedQuad.points[2] = Point(bottomRight.x, bottomRight.y);
            transformedQuad.points[3] = Point(bottomLeft.x, bottomLeft.y);
            
            // Draw as quad instead of rect
            drawImage(img, transformedQuad);
            if (attrs.hasLine() || attrs.hasFill()) {
                drawQuad(transformedQuad, attrs);
            }
            return;
        }
        
        // Save current image opacity
        uint8 originalOpacity = img->getOpacity();
        
        // Apply opacity from attributes
        if (attrs.getFillOpacity() < 1.0f) {
            img->setOpacity((uint8)(255 * attrs.getFillOpacity()));
        }
        
        // Handle ImageStrip frame selection and fit type
        // For Quad, fitType applies to the bounding rect of the quad
        Rect quadBounds = quad.getBounds();
        ImageStrip* imgStrip = dynamic_cast<ImageStrip*>(img);
        if (imgStrip && imgStrip->frames > 0) {
            int frame = attrs.getFrame();
            if (frame < 0 || frame >= imgStrip->frames) {
                frame = 0; // Default to first frame
            }
            drawImage(imgStrip, frame, quadBounds, attrs.getFitType(), attrs.getClipOverflow());
        } else {
            drawImage(img, quadBounds, attrs.getFitType(), attrs.getClipOverflow());
        }
        
        // Restore original opacity
        img->setOpacity(originalOpacity);
        if (attrs.hasLine() || attrs.hasFill()) {
            drawQuad(quad, attrs);
        }
    }

    void Port::drawDrawing(const Drawing& drawing, const Point& loc, const Attributes& attrs) {
        // Apply transformation if needed
        Point transformedLoc = loc;
        if (attrs.getTransform() != glm::mat3(1.0f)) {
            glm::vec3 transformed = attrs.getTransform() * glm::vec3(loc.x, loc.y, 1.0f);
            transformedLoc = Point(transformed.x, transformed.y);
        }
        
        // For now, delegate to the existing Drawing::draw method
        // TODO: Apply attributes like opacity, blend modes, etc.
        const_cast<Drawing&>(drawing).draw(this);
    }

    void Port::drawDrawing(const Drawing& drawing, const Rect& rect, const Attributes& attrs) {
        // Apply transformation if needed
        Rect transformedRect = rect;
        if (attrs.getTransform() != glm::mat3(1.0f)) {
            // Transform all four corners of the rectangle
            glm::vec3 topLeft = attrs.getTransform() * glm::vec3(rect.left, rect.top, 1.0f);
            glm::vec3 topRight = attrs.getTransform() * glm::vec3(rect.right, rect.top, 1.0f);
            glm::vec3 bottomRight = attrs.getTransform() * glm::vec3(rect.right, rect.bottom, 1.0f);
            glm::vec3 bottomLeft = attrs.getTransform() * glm::vec3(rect.left, rect.bottom, 1.0f);
            
            // Create transformed quad
            Quad transformedQuad;
            transformedQuad.points[0] = Point(topLeft.x, topLeft.y);
            transformedQuad.points[1] = Point(topRight.x, topRight.y);
            transformedQuad.points[2] = Point(bottomRight.x, bottomRight.y);
            transformedQuad.points[3] = Point(bottomLeft.x, bottomLeft.y);
            
            // Draw as quad instead of rect
            // For now, just draw at the transformed location
            drawDrawing(drawing, Point(transformedQuad.points[0].x, transformedQuad.points[0].y), attrs);
            return;
        }
        
        // For now, delegate to the existing Drawing::draw method
        // TODO: Apply attributes like opacity, blend modes, scaling to fit rect, etc.
        const_cast<Drawing&>(drawing).draw(this);
    }

    void Port::drawText(const char* text, const Point& loc, const Attributes& attrs) {
        if (!text) return;
        
        // Get text properties from attributes
        float size = attrs.getTextSize();
        uint32 style = attrs.getTextStyle();
        Font* font = attrs.getFont();
        
        // Apply font if specified
        Font* originalFont = nullptr;
        if (font) {
            originalFont = getCurrentFont();
            setFont(font);
        }
        
        // Get color from fill attributes (text color)
        Color textColor = attrs.getFillColor();
        textColor.alpha *= attrs.getFillOpacity();
        
        // Apply transformation if needed
        if (attrs.getTransform() != glm::mat3(1.0f)) {
            // For transformed text, we need to create a bounding rectangle and transform it to a quad
            // Get font metrics to calculate text bounds
            Font* currentFont = font ? font : getCurrentFont();
            if (!currentFont) {
                // Restore font if needed
                if (font && originalFont) {
                    setFont(originalFont);
                }
                return;
            }
            
            int textWidth = getTextWidth(text, (int)size, style);
            float textHeight = currentFont->getFontHeight((int)size, style);
            
            // Create a rectangle for the text based on its location and size
            // The location point is the baseline, so we need to account for that
            Rect textRect;
            textRect.left = loc.x;
            textRect.top = loc.y - textHeight * 0.8f; // Approximate ascent
            textRect.right = textRect.left + textWidth;
            textRect.bottom = loc.y + textHeight * 0.2f; // Approximate descent
            
            // Adjust for text justification
            if (style & textStyle_Centered) {
                textRect.left -= textWidth / 2.0f;
                textRect.right -= textWidth / 2.0f;
            } else if (style & textStyle_RightJustified) {
                textRect.left -= textWidth;
                textRect.right -= textWidth;
            }
            
            // Transform all four corners of the rectangle
            glm::vec3 topLeft = attrs.getTransform() * glm::vec3(textRect.left, textRect.top, 1.0f);
            glm::vec3 topRight = attrs.getTransform() * glm::vec3(textRect.right, textRect.top, 1.0f);
            glm::vec3 bottomRight = attrs.getTransform() * glm::vec3(textRect.right, textRect.bottom, 1.0f);
            glm::vec3 bottomLeft = attrs.getTransform() * glm::vec3(textRect.left, textRect.bottom, 1.0f);
            
            // Create transformed quad
            Quad transformedQuad;
            transformedQuad.points[0] = Point(topLeft.x, topLeft.y);
            transformedQuad.points[1] = Point(topRight.x, topRight.y);
            transformedQuad.points[2] = Point(bottomRight.x, bottomRight.y);
            transformedQuad.points[3] = Point(bottomLeft.x, bottomLeft.y);
            
            // Draw as quad with proper attributes
            drawText(text, transformedQuad, (int)size, style, textColor);
            
            // Restore original font
            if (font && originalFont) {
                setFont(originalFont);
            }
            return;
        }
        
        // No transformation - use simple point-based drawing
        drawText(text, loc, (int)size, style, textColor);
        
        // Restore original font
        if (font && originalFont) {
            setFont(originalFont);
        }
    }

    void Port::drawText(const char* text, const Rect& rect, const Attributes& attrs) {
        if (!text) return;
        
        // Get text properties from attributes
        float size = attrs.getTextSize();
        uint32 style = attrs.getTextStyle();
        Font* font = attrs.getFont();
        
        // Apply font if specified
        Font* originalFont = nullptr;
        if (font) {
            originalFont = getCurrentFont();
            setFont(font);
        }
        
        // Get color from fill attributes (text color)
        Color textColor = attrs.getFillColor();
        textColor.alpha *= attrs.getFillOpacity();
        
        // Apply transformation if needed
        if (attrs.getTransform() != glm::mat3(1.0f)) {
            // Transform all four corners of the rectangle
            glm::vec3 topLeft = attrs.getTransform() * glm::vec3(rect.left, rect.top, 1.0f);
            glm::vec3 topRight = attrs.getTransform() * glm::vec3(rect.right, rect.top, 1.0f);
            glm::vec3 bottomRight = attrs.getTransform() * glm::vec3(rect.right, rect.bottom, 1.0f);
            glm::vec3 bottomLeft = attrs.getTransform() * glm::vec3(rect.left, rect.bottom, 1.0f);
            
            // Create transformed quad
            Quad transformedQuad;
            transformedQuad.points[0] = Point(topLeft.x, topLeft.y);
            transformedQuad.points[1] = Point(topRight.x, topRight.y);
            transformedQuad.points[2] = Point(bottomRight.x, bottomRight.y);
            transformedQuad.points[3] = Point(bottomLeft.x, bottomLeft.y);
            
            // Draw as quad with proper attributes (not hardcoded!)
            drawText(text, transformedQuad, (int)size, style, textColor);
            
            // Restore original font
            if (font && originalFont) {
                setFont(originalFont);
            }
            return;
        }
        
        // No transformation - use simple rect-based drawing
        drawText(text, rect, (int)size, style, textColor);
        
        // Restore original font
        if (font && originalFont) {
            setFont(originalFont);
        }
    }

    void Port::drawSphere(const Point& center, float radius, const Attributes& attrs) {
        // Apply transformation if needed
        Point transformedCenter = center;
        float transformedRadius = radius;
        
        if (attrs.getTransform() != glm::mat3(1.0f)) {
            glm::vec3 transformed = attrs.getTransform() * glm::vec3(center.x, center.y, 1.0f);
            transformedCenter = Point(transformed.x, transformed.y);
            // For uniform scaling, we can extract the scale factor from the transform
            // For now, assume the transform only affects position
        }
        
        // Get sphere properties from attributes
        float rotation = attrs.getSphereRotation();
        Offset polarOffset = attrs.getPolarOffset();
        Offset lightOffset = attrs.getLightOffset();
        Color ambientLight = attrs.getAmbientLight();
        Image* texture = attrs.getTexture();
        
        // Apply opacity to texture if it exists
        if (texture) {
            uint8 originalOpacity = texture->getOpacity();
            if (attrs.getFillOpacity() < 1.0f) {
                texture->setOpacity((uint8)(255 * attrs.getFillOpacity()));
            }
            
            // Check if texture is an ImageStrip
            ImageStrip* imgStrip = dynamic_cast<ImageStrip*>(texture);
            if (imgStrip && imgStrip->frames > 0) {
                int frame = attrs.getFrame();
                if (frame < 0 || frame >= imgStrip->frames) {
                    frame = 0; // Default to first frame
                }
                drawTexturedSphere(imgStrip, frame, transformedCenter, transformedRadius, rotation, polarOffset, lightOffset, ambientLight);
            } else {
                drawTexturedSphere(texture, transformedCenter, transformedRadius, rotation, polarOffset, lightOffset, ambientLight);
            }
            
            // Restore original opacity
            texture->setOpacity(originalOpacity);
        } else {
            // No texture specified - draw as a solid colored sphere with 3D lighting
            Color fillColor = attrs.getFillColor();
            fillColor.alpha *= attrs.getFillOpacity();
            
            drawColoredSphere(fillColor, transformedCenter, transformedRadius, rotation, polarOffset, lightOffset, ambientLight);
        }
    }

    // Helper method to draw textured polygons
    void Port::drawTexturedPolygon(Image* texture, const Polygon& transformedPolygon, const Polygon& untransformedPolygon, const Rect& bounds, FitType fitType) {
        if (!texture || transformedPolygon.getPointCount() < 3) return;
        
        ImageOpenGL* imgOpenGL = static_cast<ImageOpenGL*>(texture);
        
        // Get port implementation for OpenGL access
        PortImpl& port = static_cast<PortImpl&>(*this);
        
        // Set up the image with this port if it's not already set
        if (imgOpenGL && imgOpenGL->mPort != &port) {
            imgOpenGL->setPort(&port);
        }
        
        // Calculate proper UV coordinates based on fitType
        TextureUVBounds uvBounds = calculateTextureFitUVs(texture, bounds, fitType);
        
        // Bind the texture using the image's bindTexture method
        if (imgOpenGL) {
            imgOpenGL->bindTexture();
            port.setOpenGLModesForDrawing(texture->getOpacity() < 255, blendMode_Normal);
            
            // Set color to white so texture shows properly
            glColor4f(1.0f, 1.0f, 1.0f, (float)texture->getOpacity() / 255.0f);
            
            // Handle tile modes specially
            if (fitType == fit_Tile || fitType == fit_TileX || fitType == fit_TileY) {
                // For tiling, calculate how many times to repeat the texture
                float imgWidth = (float)texture->width;
                float imgHeight = (float)texture->height;
                float shapeWidth = bounds.width();
                float shapeHeight = bounds.height();
                
                float uRepeat = (fitType == fit_Tile || fitType == fit_TileX) ? (shapeWidth / imgWidth) : 1.0f;
                float vRepeat = (fitType == fit_Tile || fitType == fit_TileY) ? (shapeHeight / imgHeight) : 1.0f;
                
                // Scale UV max by repeat count
                uvBounds.uMax = uvBounds.uMax * uRepeat;
                uvBounds.vMax = uvBounds.vMax * vRepeat;
                
                // Set texture wrapping mode for tiling
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            }
            
            size_t pointCount = transformedPolygon.getPointCount();
            
            // Helper lambda to map point to UV coordinates
            // Uses untransformed point position for UV calculation
            auto pointToUV = [&](size_t index) -> std::pair<float, float> {
                Point p = untransformedPolygon.getPoint(index);
                float u = uvBounds.uMin + (p.x - bounds.left) / bounds.width() * (uvBounds.uMax - uvBounds.uMin);
                float v = uvBounds.vMin + (p.y - bounds.top) / bounds.height() * (uvBounds.vMax - uvBounds.vMin);
                return std::make_pair(u, v);
            };
        
            // For simple convex polygons, use triangle fan
            if (pointCount <= 6) {
                glBegin(GL_TRIANGLE_FAN);
                
                // Center point (first vertex) - UV from untransformed, position from transformed
                Point center = transformedPolygon.getPoint(0);
                auto centerUV = pointToUV(0);
                glTexCoord2f(centerUV.first, centerUV.second);
                glVertex2f(center.x, center.y);
                
                // All vertices with texture coordinates
                for (size_t i = 0; i < pointCount; i++) {
                    Point p = transformedPolygon.getPoint(i);
                    auto uv = pointToUV(i);
                    glTexCoord2f(uv.first, uv.second);
                    glVertex2f(p.x, p.y);
                }
                
                // Close the fan
                Point first = transformedPolygon.getPoint(0);
                auto firstUV = pointToUV(0);
                glTexCoord2f(firstUV.first, firstUV.second);
                glVertex2f(first.x, first.y);
                
                glEnd();
            } else {
                // For complex polygons, use triangulation
                // Note: triangulation operates on the transformed polygon
                std::vector<Point> triangles = transformedPolygon.triangulate();
                
                // We need to map triangulated points back to original indices
                // This is complex, so for now just use bounding box mapping
                glBegin(GL_TRIANGLES);
                for (size_t i = 0; i < triangles.size(); i++) {
                    Point p = triangles[i];
                    // Find closest point in untransformed polygon for UV
                    // This is an approximation for triangulated points
                    float u = uvBounds.uMin + (p.x - bounds.left) / bounds.width() * (uvBounds.uMax - uvBounds.uMin);
                    float v = uvBounds.vMin + (p.y - bounds.top) / bounds.height() * (uvBounds.vMax - uvBounds.vMin);
                    glTexCoord2f(u, v);
                    glVertex2f(p.x, p.y);
                }
                glEnd();
            }
            
            // Restore texture wrapping mode if we changed it
            if (fitType == fit_Tile || fitType == fit_TileX || fitType == fit_TileY) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }
        
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
        }
    }

} // end namespace pdg
