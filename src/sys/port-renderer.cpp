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
#include <bit>
#include <numbers>

#include "pdg/msvcfix.h"  // fix non-standard MSVC

#include "pdg/sys/port.h"
#include "port-clip.h"
#include "particletrail.h"
#include "pdg/sys/camera.h"
#include "pdg/sys/renderer.h"
#include "pdg/sys/graphics.h"
#include "pdg/sys/drawing.h"
#include "graphics-opengl.h"
#include "image-opengl.h"
#include "include-opengl.h"
#include "pdg/sys/os.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <optional>


namespace pdg {
    void Camera::drawEffects(Port& port) const {
        const Rect viewport=getViewport();
        if (!std::isfinite(viewport.left) || !std::isfinite(viewport.top) || !std::isfinite(viewport.right) || !std::isfinite(viewport.bottom) || viewport.right<viewport.left || viewport.bottom<viewport.top)
            throw std::invalid_argument("Camera viewport must be finite and ordered");
        const float opacity=getFlashOpacity();
        if (opacity>0) {
            Port::ScreenDrawingScope scope(port); Attributes attributes;
            attributes.fillColor(Color(1.f,1.f,1.f,opacity)); port.drawRect(viewport,attributes);
        }
    }


    Camera* Port::getCamera() const {
        if (!mCamera) {
            auto* camera=new Camera();
            camera->mOwnerPort=const_cast<Port*>(this);
            camera->attach(); mCamera=camera;
        }
        return mCamera;
    }
    void Port::queueCameraEffects(Camera* camera) {
        if (!camera || std::find(mFrameCameras.begin(),mFrameCameras.end(),camera)!=mFrameCameras.end()) return;
        camera->addRef(); mFrameCameras.push_back(camera);
    }
    void Port::finishCameraEffects() {
        if (mCamera) queueCameraEffects(mCamera);
        auto cameras=std::move(mFrameCameras); mFrameCameras.clear();
        struct Release { std::vector<Camera*>& cameras; ~Release(){for(auto* camera:cameras)camera->release();} } release{cameras};
        for (auto* camera:cameras) camera->drawEffects(*this);
    }
    glm::mat3 Port::getCameraTransform() {
        const auto view = getCamera()->viewportTransform();
        return glm::mat3(view.a,view.b,0, view.c,view.d,0, view.tx,view.ty,1);
    }
    Point Port::worldToPort(const Point& point) {
        const auto p = getCameraTransform()*glm::vec3(point.x,point.y,1); return Point(p.x,p.y);
    }
    Point Port::portToWorld(const Point& point) {
        const auto p = glm::inverse(getCameraTransform())*glm::vec3(point.x,point.y,1); return Point(p.x,p.y);
    }
    // One composition at the outer drawing operation, including retained Drawings.
    class ScopedCameraDrawing {
        Port& port;
        // Nested scopes borrow the outer scope's attributes. Even the outer
        // scope needs storage only when the camera actually changes the view.
        std::optional<Attributes> transformed;
        const Attributes& prepare(const Attributes& input) {
            if (!port.isCameraDrawingEnabled()) return input;
            const auto view = port.getCameraTransform();
            if (view == glm::mat3(1.0f)) return input;
            transformed.emplace(input);
            transformed->setTransform(view * input.getTransform());
            return *transformed;
        }
    public:
        const Attributes& attributes;
        ScopedCameraDrawing(Port& p, const Attributes& input) : port(p), attributes(prepare(input)) {
            ++port.mCameraDrawingDepth;
        }
        ~ScopedCameraDrawing() { --port.mCameraDrawingDepth; }
        ScopedCameraDrawing(const ScopedCameraDrawing&) = delete;
        ScopedCameraDrawing& operator=(const ScopedCameraDrawing&) = delete;
    };

    // Helper structure to hold calculated texture UV coordinates
    struct TextureUVBounds {
        float uMin, vMin, uMax, vMax;  // UV coordinates in texture space
        Rect drawRect;                  // Adjusted drawing rectangle for fit modes
        bool useDrawRect;               // Whether to use drawRect instead of original shape
    };

    namespace {
    // Bound solid-fill vertices before submission. In particular, ES1 can render
    // incorrect clipped edges when an oversized scrolling background surrounds
    // the entire viewport. Clip each tessellated triangle so concave/crossing
    // contours retain their even-odd fill, including disconnected visible pieces.
    void drawClippedTriangle(const Point& a, const Point& b, const Point& c, const Rect& bounds) {
        std::array<Point, 8> polygon{{a, b, c}};
        int count = 3;
        const float edges[] = {bounds.left, bounds.right, bounds.top, bounds.bottom};
        for (int edge = 0; edge < 4 && count; ++edge) {
            std::array<Point, 8> output;
            int size = 0;
            const bool xAxis = edge < 2, above = (edge % 2) == 0;
            auto distance = [&](const Point& p) {
                return ((xAxis ? p.x : p.y) - edges[edge]) * (above ? 1 : -1);
            };
            Point previous = polygon[count-1];
            float previousDistance = distance(previous);
            for (int i = 0; i < count; ++i) {
                const Point& current = polygon[i];
                const float currentDistance = distance(current);
                if ((currentDistance >= 0) != (previousDistance >= 0)) {
                    const float t = previousDistance / (previousDistance - currentDistance);
                    Point intersection(previous.x + t * (current.x - previous.x),
                                       previous.y + t * (current.y - previous.y));
                    if (xAxis) intersection.x = edges[edge]; else intersection.y = edges[edge];
                    output[size++] = intersection;
                }
                if (currentDistance >= 0) output[size++] = current;
                previous = current; previousDistance = currentDistance;
            }
            polygon = output; count = size;
        }
        for (int i = 1; i + 1 < count; ++i) {
            glVertex2f(polygon[0].x, polygon[0].y);
            glVertex2f(polygon[i].x, polygon[i].y);
            glVertex2f(polygon[i+1].x, polygon[i+1].y);
        }
    }

    // Repeat within the image, not its backing buffer. WebGL 1 cannot repeat
    // NPOT textures, and repeating a padded texture would include the padding.
    // Split triangles at tile boundaries in UV space, preserving their mapping
    // through skew, rotation and the tessellation of concave/crossing contours.
    class TextureTriangles {
    public:
        struct Vertex { Point position; float u, v; };

        TextureTriangles(const ImageOpenGL& image, const TextureUVBounds& uv,
                         const Rect& bounds, FitType fit)
            : uMin(uv.uMin), vMin(uv.vMin), uMax(uv.uMax), vMax(uv.vMax) {
            tiled = fit == fit_Tile || fit == fit_TileX || fit == fit_TileY;
            if (tiled) {
                uRepeat = fit == fit_TileY ? 1.0f : bounds.width() / image.width;
                vRepeat = fit == fit_TileX ? 1.0f : bounds.height() / image.height;
                uMin = vMin = 0;
                uMax = static_cast<float>(image.width) / image.mBufferWidth;
                vMax = static_cast<float>(image.height) / image.mBufferHeight;
                splitTiles = image.width != image.mBufferWidth || image.height != image.mBufferHeight ||
                    image.mBufferWidth <= 0 || image.mBufferHeight <= 0 ||
                    !std::has_single_bit(static_cast<unsigned long>(image.mBufferWidth)) ||
                    !std::has_single_bit(static_cast<unsigned long>(image.mBufferHeight));
                glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &savedS);
                glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, &savedT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, splitTiles ? GL_CLAMP_TO_EDGE : GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, splitTiles ? GL_CLAMP_TO_EDGE : GL_REPEAT);
            }
            glBegin(GL_TRIANGLES);
        }

        ~TextureTriangles() {
            glEnd();
            if (tiled) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, savedS);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, savedT);
            }
        }

        Vertex vertex(const Point& p, float u, float v) const { return {p, u * uRepeat, v * vRepeat}; }

        void triangle(const Vertex& a, const Vertex& b, const Vertex& c) const {
            if (!splitTiles) { emit(a); emit(b); emit(c); return; }
            const int firstX = static_cast<int>(std::floor(std::min({a.u,b.u,c.u})));
            const int firstY = static_cast<int>(std::floor(std::min({a.v,b.v,c.v})));
            const int lastX = static_cast<int>(std::ceil(std::max({a.u,b.u,c.u}))) - 1;
            const int lastY = static_cast<int>(std::ceil(std::max({a.v,b.v,c.v}))) - 1;
            for (int y = firstY; y <= lastY; ++y) {
                for (int x = firstX; x <= lastX; ++x) {
                    std::array<Vertex, 8> polygon{{a,b,c}};
                    int count = 3;
                    clip(polygon, count, true, x, true);
                    clip(polygon, count, true, x+1, false);
                    clip(polygon, count, false, y, true);
                    clip(polygon, count, false, y+1, false);
                    for (int i = 1; i+1 < count; ++i) {
                        emit(polygon[0], x, y); emit(polygon[i], x, y); emit(polygon[i+1], x, y);
                    }
                }
            }
        }

    private:
        static void clip(std::array<Vertex, 8>& polygon, int& count, bool uAxis, float edge, bool above) {
            if (!count) return;
            std::array<Vertex, 8> output{};
            int size = 0;
            auto distance = [&](const Vertex& p) { return ((uAxis ? p.u : p.v) - edge) * (above ? 1 : -1); };
            Vertex previous = polygon[count-1];
            float previousDistance = distance(previous);
            for (int i = 0; i < count; ++i) {
                const Vertex& current = polygon[i];
                const float currentDistance = distance(current);
                if ((currentDistance >= 0) != (previousDistance >= 0)) {
                    const float t = previousDistance / (previousDistance - currentDistance);
                    Vertex intersection{
                        Point(previous.position.x + t * (current.position.x - previous.position.x),
                              previous.position.y + t * (current.position.y - previous.position.y)),
                        previous.u + t * (current.u - previous.u), previous.v + t * (current.v - previous.v)};
                    if (uAxis) intersection.u = edge; else intersection.v = edge;
                    output[size++] = intersection;
                }
                if (currentDistance >= 0) output[size++] = current;
                previous = current; previousDistance = currentDistance;
            }
            polygon = output; count = size;
        }

        void emit(const Vertex& p, int tileX = 0, int tileY = 0) const {
            glTexCoord2f(uMin + (p.u - tileX) * (uMax - uMin), vMin + (p.v - tileY) * (vMax - vMin));
            glVertex2f(p.position.x, p.position.y);
        }
        float uMin, vMin, uMax, vMax, uRepeat = 1, vRepeat = 1;
        bool tiled = false, splitTiles = false;
        GLint savedS = GL_CLAMP_TO_EDGE, savedT = GL_CLAMP_TO_EDGE;
    };
    }

    // helper function to make a rounded rect polygon
    void MakeRoundedRectPolygon(const Rect& rect, float xRadius, float yRadius, Polygon& polygon);

    // OpenGL interpolates vertex colors linearly. Radial color needs interior
    // samples as well: tessellation vertices alone can all lie outside the
    // gradient radius, even when its center is inside a filled triangle.
    struct RadialPolygonGradient {
        Point center;
        float radius;
        Color startColor, endColor;

        float factor(const Point& p) const {
            return radius <= 0.0f ? 0.0f : std::min(1.0f, std::hypot(p.x - center.x, p.y - center.y) / radius);
        }

        void vertex(const Point& p, float t) const {
            glColor4f(startColor.red + (endColor.red - startColor.red) * t,
                      startColor.green + (endColor.green - startColor.green) * t,
                      startColor.blue + (endColor.blue - startColor.blue) * t,
                      startColor.alpha + (endColor.alpha - startColor.alpha) * t);
            glVertex2f(p.x, p.y);
        }

        void triangle(const Point& a, const Point& b, const Point& c,
                      float ta, float tb, float tc, int depth = 0) const {
            Point ab((a.x + b.x) * 0.5f, (a.y + b.y) * 0.5f);
            Point bc((b.x + c.x) * 0.5f, (b.y + c.y) * 0.5f);
            Point ca((c.x + a.x) * 0.5f, (c.y + a.y) * 0.5f);
            float tab = factor(ab), tbc = factor(bc), tca = factor(ca);
            float error = std::max({std::abs(tab - (ta + tb) * 0.5f),
                                    std::abs(tbc - (tb + tc) * 0.5f),
                                    std::abs(tca - (tc + ta) * 0.5f),
                                    std::abs(factor(Point((a.x + b.x + c.x) / 3.0f,
                                                         (a.y + b.y + c.y) / 3.0f)) - (ta + tb + tc) / 3.0f)});

            // Test the closest points too, so a small gradient between the
            // midpoint samples cannot be mistaken for a constant-color region.
            float maxEdgeSquared = 0.0f;
            auto checkEdge = [&](const Point& p, const Point& q, float tp, float tq) {
                float dx = q.x - p.x, dy = q.y - p.y;
                float lengthSquared = dx * dx + dy * dy;
                maxEdgeSquared = std::max(maxEdgeSquared, lengthSquared);
                if (lengthSquared == 0.0f) return;
                float u = std::clamp(((center.x - p.x) * dx + (center.y - p.y) * dy) / lengthSquared, 0.0f, 1.0f);
                error = std::max(error, std::abs(factor(Point(p.x + u * dx, p.y + u * dy)) - (tp + u * (tq - tp))));
            };
            checkEdge(a, b, ta, tb);
            checkEdge(b, c, tb, tc);
            checkEdge(c, a, tc, ta);
            float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
            if (area != 0.0f) {
                float wb = ((center.x - a.x) * (c.y - a.y) - (center.y - a.y) * (c.x - a.x)) / area;
                float wc = ((b.x - a.x) * (center.y - a.y) - (b.y - a.y) * (center.x - a.x)) / area;
                float wa = 1.0f - wb - wc;
                if (wa >= 0.0f && wb >= 0.0f && wc >= 0.0f) {
                    error = std::max(error, std::abs(wa * ta + wb * tb + wc * tc));
                }
            }

            // Refine when sampled color error exceeds one 8-bit step. Limit
            // work for very small gradients or very large coordinates.
            if (error > 1.0f / 255.0f && depth < 8 && maxEdgeSquared > 1.0f) {
                triangle(a, ab, ca, ta, tab, tca, depth + 1);
                triangle(ab, b, bc, tab, tb, tbc, depth + 1);
                triangle(ca, bc, c, tca, tbc, tc, depth + 1);
                triangle(ab, bc, ca, tab, tbc, tca, depth + 1);
            } else {
                vertex(a, ta);
                vertex(b, tb);
                vertex(c, tc);
            }
        }
    };

    // Choose enough vertices to keep the maximum gap between an ellipse and
    // its polygonal approximation below a quarter of a screen pixel.
    static int calculateEllipseSegments(const Point& center, float xRadius, float yRadius,
                                        const glm::mat3& transform, bool hasTransform) {
        float screenXRadius = std::abs(xRadius);
        float screenYRadius = std::abs(yRadius);

        if (hasTransform) {
            glm::vec3 transformedCenter = transform * glm::vec3(center.x, center.y, 1.0f);
            glm::vec3 transformedX = transform * glm::vec3(center.x + xRadius, center.y, 1.0f);
            glm::vec3 transformedY = transform * glm::vec3(center.x, center.y + yRadius, 1.0f);
            screenXRadius = std::hypot(transformedX.x - transformedCenter.x,
                                       transformedX.y - transformedCenter.y);
            screenYRadius = std::hypot(transformedY.x - transformedCenter.x,
                                       transformedY.y - transformedCenter.y);
        }

        constexpr float maxError = 0.25f;
        constexpr int minSegments = 32;
        constexpr int maxSegments = 512;
        float screenRadius = std::max(screenXRadius, screenYRadius);
        if (screenRadius <= maxError) return minSegments;

        float cosine = std::clamp(1.0f - maxError / screenRadius, -1.0f, 1.0f);
        int segments = static_cast<int>(std::ceil(std::numbers::pi / std::acos(cosine)));
        return std::clamp(segments, minSegments, maxSegments);
    }

    // Tessellate a joined, centered outline in screen pixels. GL_LINE_LOOP
    // leaves gaps at thick joins and WebGL implementations may only support width 1.
    static void drawClosedStroke(PortImpl& port, const std::vector<Point>& points,
                                 float thickness, const Color& color, BlendMode blend) {
        if (points.size() < 3 || thickness <= 0) return;
        std::vector<Point> normals(points.size());
        for (size_t i = 0; i < points.size(); ++i) {
            const Point& a = points[i];
            const Point& b = points[(i+1)%points.size()];
            const float length = std::hypot(b.x-a.x, b.y-a.y);
            normals[i] = length > 0.00001f ? Point(-(b.y-a.y)/length, (b.x-a.x)/length) : Point();
        }
        std::vector<Point> joins(points.size());
        for (size_t i = 0; i < points.size(); ++i) {
            const Point a = normals[(i+points.size()-1)%points.size()];
            const Point b = normals[i];
            const float denominator = 1 + a.x*b.x + a.y*b.y;
            const float scale = denominator > 0.125f ? 1/denominator : 1;
            joins[i] = Point((a.x+b.x)*scale, (a.y+b.y)*scale);
        }
        port.setOpenGLModesForDrawing(true, blend);
        const float half = thickness/2;
        auto vertex = [&](size_t i, float offset, float alpha) {
            glVertexColor4f(color.red, color.green, color.blue, color.alpha*alpha);
            glVertex2f(points[i].x+joins[i].x*offset, points[i].y+joins[i].y*offset);
        };
        const float offsets[] = {-half-0.5f, -half, half, half+0.5f};
        const float coverage[] = {0,1,1,0};
        // Three joined strips: outside fringe, solid stroke, inside fringe.
        // Bound batches by the ES1 emulation color-array capacity (1024 floats).
        for (int band = 0; band < 3; ++band) {
            for (size_t start = 0; start < points.size(); start += 120) {
                const size_t end = std::min(start+120, points.size());
                glBegin(GL_TRIANGLE_STRIP);
                for (size_t i = start; i <= end; ++i) {
                    const size_t index = i%points.size();
                    vertex(index, offsets[band], coverage[band]);
                    vertex(index, offsets[band+1], coverage[band+1]);
                }
                glEnd();
            }
        }
    }

    void drawParticleTrail(Port& output,const ParticleTrail& trail,const SpatialTransform& view) {
        const auto points=trail.samples();
        if(points.size()<2)return;
        auto& port=static_cast<PortImpl&>(output);
        std::vector<Offset> normals(points.size()-1),joins(points.size());
        for(size_t i=0;i<normals.size();++i) {
            const auto delta=points[i+1].position-points[i].position;
            const double length=std::hypot(delta.x,delta.y);
            normals[i]=length>1e-6 ? Offset(-delta.y/length,delta.x/length) : Offset();
        }
        joins.front()=normals.front();joins.back()=normals.back();
        for(size_t i=1;i+1<points.size();++i) {
            const auto a=normals[i-1],b=normals[i];
            const double denominator=1+a.x*b.x+a.y*b.y;
            if(denominator<.125) joins[i]=b; // bounded join at reversals/sharp corners
            else joins[i]=Offset((a.x+b.x)/denominator,(a.y+b.y)/denominator);
        }
        port.setOpenGLModesForDrawing(true,blendMode_Normal);
        const auto& options=trail.options;
        auto vertex=[&](size_t i,float side,float fringe,float coverage) {
            const auto& sample=points[i];
            const float age=std::clamp(float((trail.time-sample.time)/options.lifetime),0.f,1.f);
            const float width=options.width+(options.endWidth-options.width)*age;
            const auto join=joins[i];
            const double scale=std::hypot(view.a*join.x+view.c*join.y,view.b*join.x+view.d*join.y);
            const double offset=side*(width*.5+(scale>1e-6 ? fringe/scale : 0));
            const auto p=view.transformPoint(Point(sample.position.x+join.x*offset,sample.position.y+join.y*offset));
            const float alpha=options.color.alpha*sample.opacity*(1+(options.endOpacity-1)*age)*coverage*std::min(1.0,double(width)*scale);
            glVertexColor4f(options.color.red,options.color.green,options.color.blue,alpha);
            glVertex2f(p.x,p.y);
        };
        // Solid center plus a one-pixel antialias fringe. Keep batches within
        // the browser's emulated fixed-function vertex/color array capacity.
        for(int band=0;band<3;++band)for(size_t start=0;start+1<points.size();start+=120) {
            const size_t end=std::min(start+120,points.size()-1);
            glBegin(GL_TRIANGLE_STRIP);
            for(size_t i=start;i<=end;++i) {
                if(band==0) {vertex(i,-1,0,1);vertex(i,1,0,1);}
                if(band==1) {vertex(i,-1,1,0);vertex(i,-1,0,1);}
                if(band==2) {vertex(i,1,0,1);vertex(i,1,1,0);}
            }
            glEnd();
        }
    }

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

    Port& Port::drawLine(const Point& from, const Point& to, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        ScopedPortClip clip(this, Rect(std::min(from.x,to.x), std::min(from.y,to.y), std::max(from.x,to.x), std::max(from.y,to.y)), attrs, std::max(0.5f, attrs.getLineThickness()/2));
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
        
        Rect lineBounds(std::min(transformedFrom.x, transformedTo.x), std::min(transformedFrom.y, transformedTo.y),
                        std::max(transformedFrom.x, transformedTo.x), std::max(transformedFrom.y, transformedTo.y));
        const float padding = std::max(0.5f, attrs.getLineThickness()/2);
        lineBounds.left -= padding; lineBounds.top -= padding;
        lineBounds.right += padding; lineBounds.bottom += padding;
        if (lineBounds.intersection(drawableRect).empty()) return *this;

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
        return *this;
    }

    Port& Port::drawRect(const Rect& rect, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;

        // Handle rounded corners by creating and drawing a polygon
        if (attrs.getRoundedCornerRadius() > 0.0f) {
            float xRadius = attrs.getRoundedCornerRadius();
            float yRadius = attrs.getRoundedCornerRadius();
            Polygon polygon;
            MakeRoundedRectPolygon(rect, xRadius, yRadius, polygon);
            drawPolygon(polygon, attrs);
            return *this;
        }

        // everything else is just a quad
        drawQuad(rect, attrs);
        return *this;
    }

    Port& Port::drawQuad(const Quad& quad, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        ScopedPortClip clip(this, quad.getBounds(), attrs);
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
        if (transformedQuad.getBounds().intersection(port.drawableRect()).empty()) return *this;

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
                port.setOpenGLModesForDrawing(texture->getOpacity() < 255 || imgOpenGL->mTextureFormat == GL_RGBA, attrs.getBlendMode(), imgOpenGL->usesPremultipliedAlpha());
                
                // Set color to white so texture shows properly
                imgOpenGL->setDrawColor();
                
                // Keep the existing four-triangle mapping for distorted quads.
                {
                    TextureTriangles triangles(*imgOpenGL, uvBounds, quad.getBounds(), fitType);
                    const Point center((transformedQuad.points[0].x + transformedQuad.points[1].x +
                                        transformedQuad.points[2].x + transformedQuad.points[3].x) * 0.25f,
                                       (transformedQuad.points[0].y + transformedQuad.points[1].y +
                                        transformedQuad.points[2].y + transformedQuad.points[3].y) * 0.25f);
                    const auto middle = triangles.vertex(center, 0.5f, 0.5f);
                    const std::array<TextureTriangles::Vertex, 4> corners{{
                        triangles.vertex(transformedQuad.points[0], 0, 0),
                        triangles.vertex(transformedQuad.points[1], 1, 0),
                        triangles.vertex(transformedQuad.points[2], 1, 1),
                        triangles.vertex(transformedQuad.points[3], 0, 1)}};
                    for (int i = 0; i < 4; ++i) triangles.triangle(corners[i], corners[(i+1)%4], middle);
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

            // GL_QUADS has undefined fill behavior for concave quads. Tessellate
            // the contour so convex, concave, and self-intersecting quads all use
            // the same even-odd fill rule as general polygons.
            Polygon fillPolygon;
            for (const Point& point : transformedQuad.points) {
                fillPolygon.addPoint(point);
            }
            const std::vector<Point>& triangles = fillPolygon.tessellatedPoints();
            glBegin(GL_TRIANGLES);
            const Rect clipBounds = port.drawableRect();
            for (size_t i = 0; i + 2 < triangles.size(); i += 3) {
                drawClippedTriangle(triangles[i], triangles[i+1], triangles[i+2], clipBounds);
            }
            glEnd();
        }

        // Draw outline if needed
        if (lineStyle != lineStyle_None && attrs.getLineThickness() > 0.0f && lineColor.alpha > 0.0f) {
            drawClosedStroke(port, std::vector<Point>(transformedQuad.points, transformedQuad.points+4),
                attrs.getLineThickness(), lineColor, attrs.getBlendMode());
        }
        
        // Mark port as needing redraw
        port.mNeedRedraw = true;
        return *this;
    }

    Port& Port::drawPolygon(const Polygon& polygon, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        ScopedPortClip clip(this, polygon.getBounds(), attrs);
        // Get port implementation for OpenGL access
        PortImpl& port = static_cast<PortImpl&>(*this);

        // Apply colors with opacity
        Color lineColor = attrs.getLineColor();
        lineColor.alpha *= attrs.getLineOpacity();
        Color fillColor = attrs.getFillColor();
        fillColor.alpha *= attrs.getFillOpacity();
        LineStyle lineStyle = attrs.getLineStyle();

        if (polygon.empty()) return *this;

        // Fit and transform the source contour at draw time. Keep tessellation
        // on the source Polygon so changing Attributes never rebuilds its mesh.
        const Rect originalBounds = polygon.getBounds();
        Rect drawBounds = originalBounds;
        glm::mat3 fitting(1.0f);
        Image* texture = attrs.getTexture();
        // Match quad rendering: a failed image load has no usable texture,
        // so continue through the gradient/solid fill path.
        if (texture && (texture->width <= 0 || texture->height <= 0)) texture = nullptr;
        if (texture) {
            const auto uvBounds = calculateTextureFitUVs(texture, originalBounds, attrs.getFitType());
            if (uvBounds.useDrawRect) {
                if (originalBounds.empty()) return *this;
                drawBounds = uvBounds.drawRect;
                const float scaleX = drawBounds.width() / originalBounds.width();
                const float scaleY = drawBounds.height() / originalBounds.height();
                const Point originalCenter = originalBounds.centerPoint();
                const Point newCenter = drawBounds.centerPoint();
                fitting[0][0] = scaleX;
                fitting[1][1] = scaleY;
                fitting[2][0] = newCenter.x - originalCenter.x * scaleX;
                fitting[2][1] = newCenter.y - originalCenter.y * scaleY;
            }
        }
        const glm::mat3 transform = attrs.getTransform() * fitting;
        const bool hasTransform = transform != glm::mat3(1.0f);
        const auto transformPoint = [&](const Point& p) {
            if (!hasTransform) return p;
            const auto result = transform * glm::vec3(p.x, p.y, 1.0f);
            return Point(result.x, result.y);
        };
        // The transformed contour is needed for culling and the stroke, but
        // never for tessellation (including even-odd intersection vertices).
        std::vector<Point> outline;
        outline.reserve(polygon.getPointCount());
        Point first = transformPoint(polygon.getPoint(0));
        Rect transformedBounds(first.x, first.y, first.x, first.y);
        for (size_t i = 0; i < polygon.getPointCount(); ++i) {
            Point p = transformPoint(polygon.getPoint(i));
            outline.push_back(p);
            transformedBounds.left = std::min(transformedBounds.left, p.x);
            transformedBounds.right = std::max(transformedBounds.right, p.x);
            transformedBounds.top = std::min(transformedBounds.top, p.y);
            transformedBounds.bottom = std::max(transformedBounds.bottom, p.y);
        }
        if (transformedBounds.intersection(port.drawableRect()).empty()) return *this;

        // Handle texture first (highest priority).
        if (texture) {
            uint8 originalOpacity = texture->getOpacity();
            if (attrs.getFillOpacity() < 1.0f) {
                texture->setOpacity((uint8)(255 * attrs.getFillOpacity()));
            }
            drawTexturedPolygonImpl(texture, polygon, drawBounds, attrs.getTransform(), attrs.getFitType(), fitting);
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
                
                // All fills use the same even-odd tessellation, including
                // intersection vertices and holes in self-crossing contours.
                const std::vector<Point>& triangles = polygon.tessellatedPoints();
                glBegin(GL_TRIANGLES);
                for (const Point& local : triangles) {
                    const Point p = transformPoint(local);
                    Color color = calculateGradientColor(p.x, p.y);
                    glColor4f(color.red, color.green, color.blue, color.alpha);
                    glVertex2f(p.x, p.y);
                }
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
                
                // Refine only the filled triangles to preserve radial shading
                // without a fan that crosses concave gaps or fills contour holes.
                RadialPolygonGradient gradient{center, radius, centerColor, endColor};
                const std::vector<Point>& triangles = polygon.tessellatedPoints();
                glBegin(GL_TRIANGLES);
                for (size_t i = 0; i + 2 < triangles.size(); i += 3) {
                    const Point a = transformPoint(triangles[i]);
                    const Point b = transformPoint(triangles[i + 1]);
                    const Point c = transformPoint(triangles[i + 2]);
                    gradient.triangle(a, b, c, gradient.factor(a), gradient.factor(b), gradient.factor(c));
                }
                glEnd();
            }
        } else if (attrs.hasFill()) {
            // Fill with solid color using direct OpenGL
            port.setOpenGLModesForDrawing(fillColor.alpha < 1.0f, attrs.getBlendMode());
            glColor4f(fillColor.red, fillColor.green, fillColor.blue, fillColor.alpha);
            
            const std::vector<Point>& triangles = polygon.tessellatedPoints();
            glBegin(GL_TRIANGLES);
            for (const Point& local : triangles) {
                const Point p = transformPoint(local);
                glVertex2f(p.x, p.y);
            }
            glEnd();
        }

        if (lineStyle != lineStyle_None && attrs.getLineThickness() > 0.0f && lineColor.alpha > 0.0f) {
            drawClosedStroke(port, outline, attrs.getLineThickness(), lineColor, attrs.getBlendMode());
        }

        // Mark port as needing redraw
        port.mNeedRedraw = true;
        return *this;
    }

    Port& Port::drawSpline(const Spline& spline, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        ScopedPortClip clip(this, spline.getBounds(), attrs, std::max(0.5f, attrs.getLineThickness()/2));
        if (!attrs.hasLine()) return *this;
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

        if (maxU <= 0.0f) return *this;  // No segments to draw
        
        port.setOpenGLModesForDrawing(lineColor.alpha < 1.0f, attrs.getBlendMode());
        glColor4f(lineColor.red, lineColor.green, lineColor.blue, lineColor.alpha); 
        if (attrs.getLineThickness() > 1.0f) {
            glLineWidth(attrs.getLineThickness());
        }

        auto transformPoint = [&](const Point& p) {
            const auto value = attrs.getTransform() * glm::vec3(p.x, p.y, 1);
            return Point(value.x, value.y);
        };
        Point lastPoint = transformPoint(spline.getFirstOrder(0.0f));
        glBegin(GL_LINE_STRIP);
        glVertex2f(lastPoint.x, lastPoint.y);
        for (int i = 0; i <= numSegments; i++) {
            float u = ((float)i / (float)numSegments) * maxU;
            Point currentPoint = transformPoint(spline.getFirstOrder(u));
            if (currentPoint.distanceSquared(lastPoint) < 1.0f) continue; // skip if the point is too close to the last point
            glVertex2f(currentPoint.x, currentPoint.y);
            lastPoint = currentPoint;
        }
        glEnd();
        
        if (attrs.getLineThickness() > 1.0f) {
            glLineWidth(1.0f);
        }
        return *this;
    }

    Port& Port::drawEllipse(const Point& center, float xRadius, float yRadius, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        ScopedPortClip clip(this, Rect(center.x-std::abs(xRadius), center.y-std::abs(yRadius), center.x+std::abs(xRadius), center.y+std::abs(yRadius)), attrs);
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
        if (texture && (texture->width <= 0 || texture->height <= 0)) texture = nullptr;
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

        const int segments = calculateEllipseSegments(drawCenter, drawXRadius, drawYRadius,
                                                      attrs.getTransform(), hasTransform);
        
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
                port.setOpenGLModesForDrawing(texture->getOpacity() < 255 || imgOpenGL->mTextureFormat == GL_RGBA, attrs.getBlendMode(), imgOpenGL->usesPremultipliedAlpha());
                
                // Set color to white so texture shows properly
                imgOpenGL->setDrawColor();
            
                {
                    const Rect uvMappingBounds(drawCenter.x - drawXRadius, drawCenter.y - drawYRadius,
                                               drawCenter.x + drawXRadius, drawCenter.y + drawYRadius);
                    TextureTriangles triangles(*imgOpenGL, uvBounds, uvMappingBounds, fitType);
                    const auto middle = triangles.vertex(transformedCenter, 0.5f, 0.5f);
                    auto edge = [&](int i) {
                        const float angle = 2.0f * std::numbers::pi * i / segments;
                        const float x = std::cos(angle), y = std::sin(angle);
                        const auto p = attrs.getTransform() *
                            glm::vec3(drawCenter.x + drawXRadius*x, drawCenter.y + drawYRadius*y, 1);
                        return triangles.vertex(Point(p.x,p.y), (x+1)*0.5f, (y+1)*0.5f);
                    };
                    auto previous = edge(0);
                    for (int i = 1; i <= segments; ++i) {
                        const auto current = edge(i);
                        triangles.triangle(middle, previous, current);
                        previous = current;
                    }
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
            glBegin(GL_TRIANGLE_FAN);
            
            // Center point
            Color centerColor = calculateGradientColor(transformedCenter.x, transformedCenter.y);
            glColor4f(centerColor.red, centerColor.green, centerColor.blue, centerColor.alpha);
            glVertex2f(transformedCenter.x, transformedCenter.y);
            
            for (int i = 0; i <= segments; i++) {
                float angle = 2.0f * std::numbers::pi * i / segments;
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
            glBegin(GL_TRIANGLE_FAN);
            
            // Center point of the radial gradient - always gets the center color
            glColor4f(centerColor.red, centerColor.green, centerColor.blue, centerColor.alpha);
            glVertex2f(gradCenter.x, gradCenter.y);
            
            for (int i = 0; i <= segments; i++) {
                float angle = 2.0f * std::numbers::pi * i / segments;
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
            glBegin(GL_TRIANGLE_FAN);
            
            // Use the pre-calculated transformed center
            glVertex2f(transformedCenter.x, transformedCenter.y); // Center point
            
            for (int i = 0; i <= segments; i++) {
                float angle = 2.0f * std::numbers::pi * i / segments;
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
            std::vector<Point> outline;
            for (int i = 0; i < segments; ++i) {
                const float angle = 2.0f*std::numbers::pi*i/segments;
                const glm::vec3 p = attrs.getTransform() * glm::vec3(
                    center.x+xRadius*std::cos(angle), center.y+yRadius*std::sin(angle), 1);
                outline.emplace_back(p.x, p.y);
            }
            drawClosedStroke(port, outline, attrs.getLineThickness(), lineColor, attrs.getBlendMode());
        }
        
        // Mark port as needing redraw
        port.mNeedRedraw = true;
        return *this;
    }


    Port& Port::drawArc(const Point& center, float xRadius, float yRadius, float startAngle, float endAngle, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        ScopedPortClip clip(this, Rect(center.x-std::abs(xRadius), center.y-std::abs(yRadius), center.x+std::abs(xRadius), center.y+std::abs(yRadius)), attrs, std::max(0.5f, attrs.getLineThickness()/2));
        if (!attrs.hasLine()) return *this;
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
        const auto& matrix = attrs.getTransform();
        const float extentX = std::hypot(matrix[0][0]*xRadius, matrix[1][0]*yRadius) + attrs.getLineThickness()/2;
        const float extentY = std::hypot(matrix[0][1]*xRadius, matrix[1][1]*yRadius) + attrs.getLineThickness()/2;
        Rect arcBounds(transformedCenter.x-extentX, transformedCenter.y-extentY,
                       transformedCenter.x+extentX, transformedCenter.y+extentY);
        if (arcBounds.intersection(port.drawableRect()).empty()) return *this;

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
            float screenAngle = angle - std::numbers::pi/2;
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
        return *this;
    }

    void MakeRoundedRectPolygon(const Rect& rect, float xRadius, float yRadius, Polygon& polygon) {
        xRadius = std::min(xRadius, rect.width() / 2);
        yRadius = std::min(yRadius, rect.height() / 2);
        const Point centers[] = {
            Point(rect.right-xRadius, rect.top+yRadius),
            Point(rect.right-xRadius, rect.bottom-yRadius),
            Point(rect.left+xRadius, rect.bottom-yRadius),
            Point(rect.left+xRadius, rect.top+yRadius)
        };
        const int segments = std::clamp(calculateEllipseSegments(Point(), xRadius, yRadius,
            glm::mat3(1.0f), false) / 4, 8, 32);
        for (int corner = 0; corner < 4; ++corner) {
            // Include both tangent points. Preserve deliberately sampled curve
            // points even when they are less than addPoint's minimum distance apart.
            for (int i = 0; i <= segments; ++i) {
                const float angle = (corner - 1 + float(i)/segments) * std::numbers::pi/2;
                const Point point(centers[corner].x + xRadius*std::cos(angle),
                                  centers[corner].y + yRadius*std::sin(angle));
                if (polygon.getPointCount() && point.distance(polygon.getPoint(polygon.getPointCount()-1)) < 0.0001f) continue;
                if (corner == 3 && i == segments && polygon.getPointCount() &&
                    point.distance(polygon.getPoint(0)) < 0.0001f) continue;
                polygon.insertPoint(polygon.getPointCount(), point);
            }
        }
    }

    // -----------------------------------------------------------------------------------
    // New Renderer interface methods for images, drawings, text, and spheres
    // -----------------------------------------------------------------------------------

    Port& Port::drawImage(Image* img, const Point& loc, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        if (!img) return *this;
        drawImage(img, Rect(loc, img->getWidth(), img->getHeight()), attrs);
        return *this;
    }

    Port& Port::drawImage(Image* img, const Rect& rect, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        drawImage(img, Quad(rect), attrs);
        return *this;
    }
    
    Port& Port::drawImage(Image* img, const Quad& quad, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        if (!img) return *this;
        ScopedPortClip clip(this, quad.getBounds(), attrs);
        struct RestoreOpacity {
            Image* image; uint8 opacity;
            ~RestoreOpacity() { image->setOpacity(opacity); }
        } restore{img, img->getOpacity()};
        img->setOpacity(static_cast<uint8>(restore.opacity * std::clamp(attrs.getFillOpacity(), 0.0f, 1.0f)));
        img->setPort(this);
        auto* strip = dynamic_cast<ImageStrip*>(img);
        const int frame = strip && attrs.getFrame() >= 0 && attrs.getFrame() < strip->frames ? attrs.getFrame() : 0;
        Rect source(img->getWidth(), img->getHeight());
        if (!attrs.getSubsection().empty()) source = source.intersection(attrs.getSubsection());
        if (source.empty()) return *this;
        if (strip) source += Offset(frame * img->getWidth(), 0);
        const float width = std::hypot(quad.points[1].x-quad.points[0].x, quad.points[1].y-quad.points[0].y);
        const float height = std::hypot(quad.points[3].x-quad.points[0].x, quad.points[3].y-quad.points[0].y);
        if (width <= 0 || height <= 0) return *this;
        auto point = [&](float x, float y) {
            const auto& q = quad.points;
            const float u=x/width, v=y/height;
            const auto p = (1-u)*(1-v)*glm::vec2(q[0].x,q[0].y) + u*(1-v)*glm::vec2(q[1].x,q[1].y)
                         + u*v*glm::vec2(q[2].x,q[2].y) + (1-u)*v*glm::vec2(q[3].x,q[3].y);
            const auto t = attrs.getTransform()*glm::vec3(p,1);
            return Point(t.x,t.y);
        };
        auto draw = [&](const Rect& destination, bool crop) {
            Rect visible = crop ? destination.intersection(Rect(width,height)) : destination;
            if (visible.empty()) return;
            Rect pixels(source.left + (visible.left-destination.left)/destination.width()*source.width(),
                        source.top + (visible.top-destination.top)/destination.height()*source.height(),
                        source.left + (visible.right-destination.left)/destination.width()*source.width(),
                        source.top + (visible.bottom-destination.top)/destination.height()*source.height());
            Quad q; q.points[0]=point(visible.left,visible.top); q.points[1]=point(visible.right,visible.top);
            q.points[2]=point(visible.right,visible.bottom); q.points[3]=point(visible.left,visible.bottom);
            img->drawSection(q,pixels);
        };
        const FitType fit = attrs.getFitType();
        if (fit == fit_Tile || fit == fit_TileX || fit == fit_TileY) {
            const float tileWidth = fit == fit_TileY ? width : source.width();
            const float tileHeight = fit == fit_TileX ? height : source.height();
            for (float y=0; y<height; y+=tileHeight)
                for (float x=0; x<width; x+=tileWidth)
                    draw(Rect(x,y,x+tileWidth,y+tileHeight),true);
        } else {
            float w=width, h=height;
            if (fit != fit_Fill) {
                float scale=1;
                if (fit == fit_Width) scale=width/source.width();
                else if (fit == fit_Height) scale=height/source.height();
                else if (fit == fit_Inside) scale=std::min(width/source.width(),height/source.height());
                else if (fit == fit_Overflow || fit == fit_Clipped) scale=std::max(width/source.width(),height/source.height());
                w=source.width()*scale; h=source.height()*scale;
            }
            draw(Rect((width-w)/2,(height-h)/2,(width+w)/2,(height+h)/2), attrs.getClipOverflow() || fit == fit_Clipped);
        }
        if (attrs.hasLine() || attrs.hasFill()) drawQuad(quad, attrs);
        return *this;
    }

    Port& Port::drawDrawing(const Drawing& drawing, const Point& loc, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        glm::mat3 offset(1);
        offset[2] = glm::vec3(loc.x, loc.y, 1);
        Attributes parent(attrs);
        parent.setTransform(attrs.getTransform() * offset);
        drawing.drawTransformed(this, parent);
        return *this;
    }

    Port& Port::drawDrawing(const Drawing& drawing, const Rect& rect, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        Attributes parent(attrs);
        parent.setTransform(attrs.getTransform() * drawing.destinationTransform(Quad(rect)));
        drawing.drawTransformed(this, parent);
        return *this;
    }

    Port& Port::drawText(const char* text, const Point& loc, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this, true);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        if (!text) return *this;
        
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
        
        Font* metrics = font ? font : getCurrentFont(style);
        const float width = getTextWidth(text, int(size), style);
        float left = loc.x;
        if (style & textStyle_Centered) left -= width/2;
        else if (style & textStyle_RightJustified) left -= width;
        Rect ink(left, loc.y - (metrics ? metrics->getFontAscent(int(size),style) : size),
                 left + width, loc.y + (metrics ? metrics->getFontDescent(int(size),style) : 0));
        ScopedPortClip clip(this, ink, attrs);

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
                return *this;
            }
            
            // Use the same measured baseline bounds for layout and overflow clipping.
            const Rect textRect = ink;

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
            return *this;
        }
        
        // No transformation - use simple point-based drawing
        drawText(text, loc, (int)size, style, textColor);
        
        // Restore original font
        if (font && originalFont) {
            setFont(originalFont);
        }
        return *this;
    }

    Port& Port::drawText(const char* text, const Rect& rect, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this, true);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        ScopedPortClip clip(this, rect, attrs);
        if (!text) return *this;
        
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
            return *this;
        }
        
        // No transformation - use simple rect-based drawing
        drawText(text, rect, (int)size, style, textColor);
        
        // Restore original font
        if (font && originalFont) {
            setFont(originalFont);
        }
        return *this;
    }

    Port& Port::drawSphere(const Point& center, float radius, const Attributes& inputAttrs) {
        ScopedOffscreenDrawing offscreenScope(this);
        ScopedCameraDrawing cameraScope(*this, inputAttrs);
        const Attributes& attrs = cameraScope.attributes;
        ScopedPortClip clip(this, Rect(center.x-radius, center.y-radius, center.x+radius, center.y+radius), attrs);
        // Preserve the complete affine view, including anisotropic scale and
        // reflection, while the sphere renderer builds its local 3D geometry.
        static_cast<PortImpl&>(*this).setOpenGLModesForDrawing(false);
        const auto& t=attrs.getTransform();
        const GLfloat matrix[16]={t[0][0],t[0][1],0,0, t[1][0],t[1][1],0,0,
                                  0,0,1,0, t[2][0],t[2][1],0,1};
        glPushMatrix(); glMultMatrixf(matrix);
        struct RestoreMatrix { ~RestoreMatrix() { glPopMatrix(); } } restoreMatrix;
        const Point& transformedCenter = center;
        const float transformedRadius = radius;
        
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
        return *this;
    }

    // Helper method to draw textured polygons
    void Port::drawTexturedPolygon(Image* texture, const Polygon& polygon, const Rect& bounds, const glm::mat3& transform, FitType fitType) {
        drawTexturedPolygonImpl(texture, polygon, bounds, transform, fitType, glm::mat3(1.0f));
    }

    void Port::drawTexturedPolygonImpl(Image* texture, const Polygon& polygon, const Rect& bounds,
                                       const glm::mat3& transform, FitType fitType, const glm::mat3& fitting) {
        ScopedOffscreenDrawing offscreenScope(this);
        if (!texture || polygon.getPointCount() < 3 || bounds.empty()) return;
        
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
            port.setOpenGLModesForDrawing(texture->getOpacity() < 255 || imgOpenGL->mTextureFormat == GL_RGBA, blendMode_Normal, imgOpenGL->usesPremultipliedAlpha());
            
            // Set color to white so texture shows properly
            imgOpenGL->setDrawColor();
            
            // Tessellate in local space so crossing-contour intersections get
            // the same UV mapping as authored vertices. Tile clipping then
            // preserves those triangles and the even-odd holes between them.
            const std::vector<Point>& vertices = polygon.tessellatedPoints();
            {
                TextureTriangles triangles(*imgOpenGL, uvBounds, bounds, fitType);
                auto vertex = [&](const Point& local) {
                    const auto fitted = fitting * glm::vec3(local.x,local.y,1);
                    const Point p(fitted.x, fitted.y);
                    const auto position = transform * fitted;
                    return triangles.vertex(Point(position.x,position.y),
                        (p.x-bounds.left)/bounds.width(), (p.y-bounds.top)/bounds.height());
                };
                for (size_t i = 0; i+2 < vertices.size(); i += 3)
                    triangles.triangle(vertex(vertices[i]), vertex(vertices[i+1]), vertex(vertices[i+2]));
            }

            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
        }
    }

} // end namespace pdg
