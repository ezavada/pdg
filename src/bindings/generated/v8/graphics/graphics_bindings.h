// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/graphics_bindings.h
//    $PDG_ROOT/src/bindings/javascript/v8/pdg_script_macros.h
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



#ifndef PDG_GRAPHICS_BINDINGS_H_INCLUDED
#define PDG_GRAPHICS_BINDINGS_H_INCLUDED

#include "pdg_project.h"

#include "pdg_script_impl.h"
#include "pdg_script_interface.h"

#ifndef PDG_NO_APP_FRAMEWORK
#define PDG_NO_APP_FRAMEWORK
#endif
#include "pdg/framework.h"
#include "pdg/sys/drawing.h"
#include "pdg/sys/renderer.h"

#include <cstdlib>

namespace pdg
{

    Image* New_Image(const v8::FunctionCallbackInfo<v8::Value>& args);

    class ImageWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Image* getCppObject() { return cppPtr_; }
        protected:
            Image* cppPtr_;

            ImageWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~ImageWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Image* cppObj);
            ImageWrap(Image* obj) : cppPtr_(obj) {}

            static void GetTransparentColor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetTransparentColor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetOpacity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetOpacity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetImageBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSubsection (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetEdgeClamping (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RetainData (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RetainAlpha (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PrepareToRasterize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAlphaValue (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPixel (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    ImageStrip* New_ImageStrip(const v8::FunctionCallbackInfo<v8::Value>& args);

    class ImageStripWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            ImageStrip* getCppObject() { return cppPtr_; }
        protected:
            ImageStrip* cppPtr_;

            ImageStripWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~ImageStripWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, ImageStrip* cppObj);
            ImageStripWrap(ImageStrip* obj) : cppPtr_(obj) {}

            static void GetTransparentColor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetTransparentColor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetOpacity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetOpacity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetImageBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSubsection (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetEdgeClamping (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RetainData (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RetainAlpha (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PrepareToRasterize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAlphaValue (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPixel (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFrameWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFrameWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetNumFrames (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetNumFrames (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFrame (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    Spline* New_Spline(const v8::FunctionCallbackInfo<v8::Value>& args);

    class SplineWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Spline* getCppObject() { return cppPtr_; }
        protected:
            Spline* cppPtr_;

            SplineWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~SplineWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Spline* cppObj);
            SplineWrap(Spline* obj) : cppPtr_(obj) {}

            static void GetFirstOrder (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSecondOrder (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddSegment (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPointCount (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMaxU (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    Polygon* New_Polygon(const v8::FunctionCallbackInfo<v8::Value>& args);

    class PolygonWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Polygon* getCppObject() { return cppPtr_; }
        protected:
            Polygon* cppPtr_;

            PolygonWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~PolygonWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Polygon* cppObj);
            PolygonWrap(Polygon* obj) : cppPtr_(obj) {}

            static void AddPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddSpline (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void InsertPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RemovePoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPointCount (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClearPoints (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CenterPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Contains (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Equals (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Empty (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Move (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveLeft (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveRight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveUp (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveDown (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveXTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveYTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveTo (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Center (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Scale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void HorzScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void VertScale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ScaleAround (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Rotate (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RotateAround (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Intersection (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void UnionWith (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    ElementRef* New_ElementRef(const v8::FunctionCallbackInfo<v8::Value>& args);

    class ElementRefWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            ElementRef* getCppObject() { return cppPtr_; }
        protected:
            ElementRef* cppPtr_;

            ElementRefWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~ElementRefWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, ElementRef* cppObj);
            ElementRefWrap(ElementRef* obj) : cppPtr_(obj) {}

            static void Type (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetControlPoints (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetControlPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAttributes (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetAttributes (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ChangeControlPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveForward (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveBackward (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveToFront (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void MoveToBack (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Remove (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    Attributes* New_Attributes(const v8::FunctionCallbackInfo<v8::Value>& args);

    class AttributesWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Attributes* getCppObject() { return cppPtr_; }
        protected:
            Attributes* cppPtr_;

            AttributesWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~AttributesWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Attributes* cppObj);
            AttributesWrap(Attributes* obj) : cppPtr_(obj) {}

            static void LineColor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LineThickness (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LineOpacity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetLineStyle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FillColor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FillOpacity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FillGradient (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void FillRadialGradient (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void RoundedCorners (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Translation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Rotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Scale (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Skew (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Transform (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetBlendMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void TextSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void TextStyle (const v8::FunctionCallbackInfo<v8::Value>& args);
#ifndef PDG_NO_GUI
            static void SetFont (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
            static void Frame (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFitType (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ClipOverflow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Subsection (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SphereRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void PolarOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void LightOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AmbientLight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Texture (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLineColor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLineThickness (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLineOpacity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLineStyle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFillColor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFillOpacity (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRoundedCornerRadius (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGradientType (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGradientStart (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGradientEnd (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGradientStartColor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetGradientEndColor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRadialGradientCenter (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRadialGradientRadius (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRadialGradientCenterColor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetRadialGradientEndColor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetTransform (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBlendMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetTextSize (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetTextStyle (const v8::FunctionCallbackInfo<v8::Value>& args);
#ifndef PDG_NO_GUI
            static void GetFont (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
            static void GetFrame (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFitType (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetClipOverflow (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSubsection (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetSphereRotation (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetPolarOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetLightOffset (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetAmbientLight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetTexture (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    Drawing* New_Drawing(const v8::FunctionCallbackInfo<v8::Value>& args);

    class DrawingWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Drawing* getCppObject() { return cppPtr_; }
        protected:
            Drawing* cppPtr_;

            DrawingWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~DrawingWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Drawing* cppObj);
            DrawingWrap(Drawing* obj) : cppPtr_(obj) {}

            static void AddLine (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddSpline (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddRect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddArc (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddQuad (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddPolygon (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddEllipse (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddImage (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddImageStrip (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void AddDrawing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetElementCount (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetElement (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetElementHitBy (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CenterPoint (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void Empty (const v8::FunctionCallbackInfo<v8::Value>& args);
#ifndef PDG_NO_GUI
            static void Draw (const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
    };

#ifndef PDG_NO_GUI

    GraphicsManager* New_GraphicsManager(const v8::FunctionCallbackInfo<v8::Value>& args);

    class GraphicsManagerWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            GraphicsManager* getCppObject() { return cppPtr_; }
        protected:
            GraphicsManager* cppPtr_;

            GraphicsManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~GraphicsManagerWrap();

        public:
            static GraphicsManager* getSingletonInstance();
        public:
            static v8::Local<v8::Object> GetScriptSingletonInstance(v8::Isolate* isolate);
        protected:
            static v8::Persistent<v8::Object> instance_;
            static bool instanced_;

            static void GetNumScreens (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetNumSupportedScreenModes (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetNthSupportedScreenMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCurrentScreenMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetScreenBounds (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetScreenMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateWindowPort (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateFullScreenPort (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CloseGraphicsPort (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CloseAllGraphicsPorts (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void CreateFont (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMainPort (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SwitchToFullScreenMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SwitchToWindowMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void InFullScreenMode (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFPS (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetTargetFPS (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetTargetFPS (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetMouse (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    class FontWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Font* getCppObject() { return cppPtr_; }
        protected:
            Font* cppPtr_;

            FontWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~FontWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Font* cppObj);
            FontWrap(Font* obj) : cppPtr_(obj) {}

            static void GetFontName (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFontHeight (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFontLeading (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFontAscent (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetFontDescent (const v8::FunctionCallbackInfo<v8::Value>& args);
    };

    class PortWrap : public jswrap::ObjectWrap
    {
        public:
            static void Init(v8::Isolate* isolate, v8::Local<v8::Object> target);
            static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        protected:
            static v8::Persistent<v8::FunctionTemplate> constructorTpl_;
        public:
            Port* getCppObject() { return cppPtr_; }
        protected:
            Port* cppPtr_;

            PortWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
            ~PortWrap();

        public:
            static v8::Local<v8::Object> NewFromCpp(v8::Isolate* isolate, Port* cppObj);
            PortWrap(Port* obj) : cppPtr_(obj) {}

            static void GetClipRect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetClipRect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCursor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetCursor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetDrawingArea (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawLine (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawSpline (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawText (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawImage (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetTextWidth (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void GetCurrentFont (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFont (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFontForStyle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void SetFontScalingFactor (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StartTrackingMouse (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void StopTrackingMouse (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void ResetCursor (const v8::FunctionCallbackInfo<v8::Value>& args);

            static void DrawRect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawQuad (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawPolygon (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawEllipse (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawArc (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawBezier (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawCircle (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawVector (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawRoundedRect (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawDrawing (const v8::FunctionCallbackInfo<v8::Value>& args);
            static void DrawSphere (const v8::FunctionCallbackInfo<v8::Value>& args);
    };
#endif
#endif

}
