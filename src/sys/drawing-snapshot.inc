// Included inside namespace pdg after DrawingImpl's declaration.
// All content is embedded; referenced Image resources follow the writer policy.
struct DrawingSnapshot {
    using Storage = DrawingImpl::Storage;
    static void registerStorage() {
        static const bool registered = [] { IDeserializer::registerClass<Storage>(); return true; }();
        (void)registered;
    }
    static std::shared_ptr<Storage> newStorage() {
        registerStorage();
        auto* storage = new Storage(); storage->addRef();
        return std::shared_ptr<Storage>(storage, [](Storage* value) { value->release(); });
    }
    static const Storage* storage(const Drawing* drawing) {
        if (!drawing) return nullptr;
        const auto* impl = dynamic_cast<const DrawingImpl*>(drawing);
        if (!impl) throw std::runtime_error("Cannot save custom Drawing implementations");
        return impl->storage.get();
    }
    template<class A, class F> static void colors(A& a, F visit) {
        static const Attributes defaults;
        for (auto member : {&Attributes::mLineColor, &Attributes::mFillColor,
                &Attributes::mGradientStartColor, &Attributes::mGradientEndColor,
                &Attributes::mRadialGradientCenterColor, &Attributes::mRadialGradientEndColor,
                &Attributes::mAmbientLight}) visit(a.*member, defaults.*member);
    }
    // Pixel-space appearance only. Physics and dimensionless matrix components
    // never pass through the lossy coordinate serializer.
    template<class A, class F> static void coordinates(A& a, F visit) {
        visit(a.mLineThickness, a.mTextSize, 1.f, 12.f);
        visit(a.mRoundedCornerRadius, a.mRadialGradientRadius, 0.f, 0.f);
        for (auto* point : {&a.mGradientStart, &a.mGradientEnd, &a.mRadialGradientCenter})
            visit(point->x, point->y, 0.f, 0.f);
        visit(a.mPolarOffset.x, a.mPolarOffset.y, 0.f, 0.f);
        visit(a.mLightOffset.x, a.mLightOffset.y, 0.f, 0.f);
        visit(a.mSubsection.left, a.mSubsection.top, 0.f, 0.f);
        visit(a.mSubsection.right, a.mSubsection.bottom, 0.f, 0.f);
        visit(a.mTransform[2][0], a.mTransform[2][1], 0.f, 0.f);
    }
    template<class A, class F> static void floats(A& a, F visit) {
        visit(a.mLineOpacity, 1.f); visit(a.mFillOpacity, 1.f); visit(a.mSphereRotation, 0.f);
        for (int x=0;x<3;++x) for (int y=0;y<3;++y)
            if (x!=2 || y==2) visit(a.mTransform[x][y], x==y ? 1.f : 0.f);
    }
    template<class A, class F> static void integers(A& a, F visit) {
        visit(a.mLineStyle, lineStyle_Auto); visit(a.mGradientType, gradientType_None);
        visit(a.mBlendMode, blendMode_Normal); visit(a.mTextStyle, textStyle_Plain);
        visit(a.mFrame, 0); visit(a.mFitType, fit_Fill);
    }
    static void finite(float value) {
        if (!std::isfinite(value)) throw std::runtime_error("Non-finite Drawing snapshot value");
    }
    static void validColor(const Color& color) {
        for (float channel : {color.red, color.green, color.blue, color.alpha})
            if (!std::isfinite(channel) || channel<0 || channel>1)
                throw std::runtime_error("Drawing snapshot color channels must be between zero and one");
    }
    static bool differentColor(const Color& a, const Color& b) {
        return a.red!=b.red || a.green!=b.green || a.blue!=b.blue || a.alpha!=b.alpha;
    }
    static uint32 encodeAttributes(const Attributes& a, ISerializer* writer, bool emit) {
        if (a.mFont) throw std::runtime_error("Drawing snapshots do not yet embed Font resources");
        bool changed=a.mClipOverflow || a.mTexture;
        colors(a, [&](const Color& c, const Color& d) { validColor(c); changed |= differentColor(c,d); });
        coordinates(a, [&](float x,float y,float dx,float dy) { finite(x);finite(y);changed |= x!=dx || y!=dy; });
        floats(a, [&](float v,float d) { finite(v);changed |= SnapshotWriter::different(v,d); });
        integers(a, [&](int v,int d) { changed |= v!=d; });
        SnapshotWriter out(writer,emit); uint32 size=0;
        if (!out.flag(changed)) return out.size();
        colors(a, [&](const Color& c,const Color& d) {
            if (out.flag(differentColor(c,d))) {
                if (emit) writer->serialize_color(c); else size+=writer->sizeof_color(c);
            }
        });
        coordinates(a, [&](float x,float y,float dx,float dy) {
            if (out.flag(x!=dx || y!=dy)) out.visual(Offset(x,y));
        });
        floats(a, [&](float v,float d) { out.floating(v,d); });
        integers(a, [&](int v,int d) { out.signedInteger(v,d); });
        out.flag(a.mClipOverflow); out.object(a.mTexture);
        return size+out.size();
    }
    static uint32 attributesSize(const Attributes& a, ISerializer* writer) { return encodeAttributes(a,writer,false); }
    static void writeAttributes(const Attributes& a, ISerializer* writer) { encodeAttributes(a,writer,true); }
    static std::shared_ptr<Image> readImage(IDeserializer* reader) {
        auto* object=reader->deserialize_obj();
        auto* image=dynamic_cast<Image*>(object);
        if (object && !image) { object->release(); throw std::runtime_error("Expected Drawing image resource"); }
        return std::shared_ptr<Image>(image, [](Image* value) { if(value)value->release(); });
    }
    static std::shared_ptr<Image> readAttributes(Attributes& a, IDeserializer* reader) {
        a=Attributes(); SnapshotReader in(reader);
        if (!in.flag()) return {};
        colors(a, [&](Color& c,const Color& d) { c=in.flag() ? reader->deserialize_color() : d; });
        coordinates(a, [&](float& x,float& y,float dx,float dy) {
            const auto p=in.flag() ? in.visual() : Offset(dx,dy); x=p.x;y=p.y;
        });
        floats(a, [&](float& v,float d) { v=in.floating(d); finite(v); });
        integers(a, [&](auto& v,int d) { v=static_cast<std::remove_reference_t<decltype(v)>>(in.signedInteger(d)); });
        if (a.mLineStyle<lineStyle_Auto || a.mLineStyle>lineStyle_DashDotDot ||
            a.mGradientType<gradientType_None || a.mGradientType>gradientType_Radial ||
            a.mBlendMode<blendMode_Normal || a.mBlendMode>blendMode_Lighten || a.mFitType<fit_None || a.mFitType>fit_Tile)
            throw std::runtime_error("Invalid Drawing attribute mode");
        a.mClipOverflow=in.flag();
        auto texture=in.flag() ? readImage(reader) : std::shared_ptr<Image>();
        a.texture(texture.get()); return texture;
    }
    static void validatePoints(const std::vector<Point>& points) {
        if (points.size() > 1000000) throw std::runtime_error("Too many Drawing control points");
        for (const auto& point : points) { finite(point.x); finite(point.y); }
    }
    static uint32 pointsSize(const std::vector<Point>& points, ISerializer* writer) {
        validatePoints(points);
        uint32 size = writer->sizeof_uint(points.size());
        for (const auto& point : points) size += writer->sizeof_point(point);
        return size;
    }
    static void writePoints(const std::vector<Point>& points, ISerializer* writer) {
        validatePoints(points);
        writer->serialize_uint(points.size());
        for (const auto& point : points) writer->serialize_point(point);
    }
    static std::vector<Point> readPoints(IDeserializer* reader) {
        const auto count = reader->deserialize_uint();
        if (count > 1000000) throw std::runtime_error("Too many Drawing control points");
        std::vector<Point> points; points.reserve(count);
        for (uint32 i = 0; i < count; ++i) {
            const auto point = reader->deserialize_point(); finite(point.x); finite(point.y);
            points.push_back(point);
        }
        return points;
    }
    static uint32 splineSize(const Spline& spline, ISerializer* writer) { return 1+writer->sizeof_bool(spline.mLooping); }
    static void writeSpline(const Spline& spline, ISerializer* writer) {
        writer->serialize_1u(spline.mType); writer->serialize_bool(spline.mLooping);
    }
    static Spline readSpline(IDeserializer* reader, const std::vector<Point>& points) {
        const auto type = reader->deserialize_1u(); const bool loop = reader->deserialize_bool();
        if (type < SPLINE_HERMITE || type > SPLINE_NATURAL_CUBIC)
            throw std::runtime_error("Invalid Drawing spline type");
        Spline spline(type); for (auto point : points) spline.addPoint(point);
        spline.mLooping = loop; return spline;
    }
};

uint32 DrawingImpl::Storage::getSerializedSize(ISerializer* writer) const {
    if (elements.size() > 1000000) throw std::runtime_error("Too many Drawing elements");
    uint32 size = 1 + writer->sizeof_uint(elements.size());
    for (const auto& item : elements) {
        const auto type = item.first; const auto* element = item.second;
        size += 1 + DrawingSnapshot::attributesSize(Attributes(element->appearance()), writer);
        size += DrawingSnapshot::pointsSize(element->controlPoints, writer);
        switch (type) {
        case type_Line: case type_Rect: case type_Quad: case type_Polygon: break;
        case type_Spline: size += DrawingSnapshot::splineSize(static_cast<const SplineElement*>(element)->spline,writer); break;
        case type_Arc: {
            const auto* arc = static_cast<const ArcElement*>(element);
            for (float value : {arc->xRadius, arc->yRadius, arc->startAngle, arc->endAngle}) DrawingSnapshot::finite(value);
            size += writer->sizeof_offset(Offset(arc->xRadius, arc->yRadius)) + 8; break;
        }
        case type_Ellipse: {
            const auto* ellipse = static_cast<const EllipseElement*>(element);
            DrawingSnapshot::finite(ellipse->xRadius); DrawingSnapshot::finite(ellipse->yRadius);
            size += writer->sizeof_offset(Offset(ellipse->xRadius, ellipse->yRadius)); break;
        }
        case type_Image: case type_ImageStrip:
            size += 8 + writer->sizeof_obj(static_cast<const ImageElement*>(element)->image); break;
        case type_Drawing:
            size += drawingSerializedSize(static_cast<const DrawingElement*>(element)->drawing.get(), writer); break;
        default: throw std::runtime_error("Unsupported Drawing element type");
        }
    }
    return size;
}
void DrawingImpl::Storage::serialize(ISerializer* writer) const {
    writer->serialize_1u(4); writer->serialize_uint(elements.size());
    for (const auto& item : elements) {
        const auto type = item.first; const auto* element = item.second;
        writer->serialize_1u(type);
        DrawingSnapshot::writeAttributes(Attributes(element->appearance()), writer);
        DrawingSnapshot::writePoints(element->controlPoints, writer);
        switch (type) {
        case type_Line: case type_Rect: case type_Quad: case type_Polygon: break;
        case type_Spline: DrawingSnapshot::writeSpline(static_cast<const SplineElement*>(element)->spline, writer); break;
        case type_Arc: {
            const auto* arc = static_cast<const ArcElement*>(element);
            for (float value : {arc->xRadius, arc->yRadius, arc->startAngle, arc->endAngle}) DrawingSnapshot::finite(value);
            writer->serialize_offset(Offset(arc->xRadius, arc->yRadius));
            writer->serialize_f(arc->startAngle); writer->serialize_f(arc->endAngle);
            break;
        }
        case type_Ellipse: {
            const auto* ellipse = static_cast<const EllipseElement*>(element);
            DrawingSnapshot::finite(ellipse->xRadius); DrawingSnapshot::finite(ellipse->yRadius);
            writer->serialize_offset(Offset(ellipse->xRadius, ellipse->yRadius)); break;
        }
        case type_Image: case type_ImageStrip: {
            const auto* image = static_cast<const ImageElement*>(element);
            writer->serialize_4(image->numFrames); writer->serialize_4(image->frameNumber);
            writer->serialize_obj(image->image); break;
        }
        case type_Drawing:
            serializeDrawing(static_cast<const DrawingElement*>(element)->drawing.get(), writer); break;
        default: throw std::runtime_error("Unsupported Drawing element type");
        }
    }
}
void DrawingImpl::Storage::deserialize(IDeserializer* reader) {
    if (reader->deserialize_1u() != 4) throw std::runtime_error("Unsupported Drawing record");
    const auto count = reader->deserialize_uint();
    if (count > 1000000) throw std::runtime_error("Too many Drawing elements");
    struct Loading {
        bool& value;
        explicit Loading(bool& flag) : value(flag) { value = true; }
        ~Loading() { value = false; }
    } guard(loading);
    Storage staged;
    for (uint32 i = 0; i < count; ++i) {
        const auto type = static_cast<ElementType>(reader->deserialize_1u());
        Attributes attrs;
        auto texture = DrawingSnapshot::readAttributes(attrs, reader); // retain until Element takes its reference
        const auto points = DrawingSnapshot::readPoints(reader);
        auto require = [&](size_t count) { if (points.size() != count) throw std::runtime_error("Invalid Drawing geometry"); };
        auto number = [&] { float value = reader->deserialize_f(); DrawingSnapshot::finite(value); return value; };
        std::unique_ptr<Element> element;
        switch (type) {
        case type_Line: require(2); element.reset(new LineElement(points[0], points[1], attrs)); break;
        case type_Rect: case type_Quad: {
            require(4); Quad quad; for (int p = 0; p < 4; ++p) quad.points[p] = points[p];
            element.reset(new QuadElement(quad, attrs)); break;
        }
        case type_Spline: {
            auto spline = DrawingSnapshot::readSpline(reader, points);
            element.reset(new SplineElement(std::move(spline), attrs)); break;
        }
        case type_Polygon: {
            Polygon polygon(points); element.reset(new PolygonElement(std::move(polygon), attrs)); break;
        }
        case type_Arc: {
            require(3); const auto radii = reader->deserialize_offset();
            DrawingSnapshot::finite(radii.x); DrawingSnapshot::finite(radii.y);
            const float start = number(), end = number();
            element.reset(new ArcElement(points[0], radii.x, radii.y, start, end, attrs)); break;
        }
        case type_Ellipse: {
            require(5); const auto radii = reader->deserialize_offset();
            DrawingSnapshot::finite(radii.x); DrawingSnapshot::finite(radii.y);
            element.reset(new EllipseElement(points[0], radii.x, radii.y, attrs)); break;
        }
        case type_Image: case type_ImageStrip: {
            require(4); const int frames = reader->deserialize_4(), frame = reader->deserialize_4();
            auto image = DrawingSnapshot::readImage(reader);
            if (!image || frames < 1) throw std::runtime_error("Invalid Drawing image");
            auto* part = new ImageElement(Rect(points[0], points[2]), *image, frame, attrs);
            part->numFrames = frames; element.reset(part); break;
        }
        case type_Drawing: {
            require(4); auto drawing = deserializeDrawing(reader);
            if (!drawing) throw std::runtime_error("Missing nested Drawing");
            element.reset(new DrawingElement(Rect(points[0], points[2]), *drawing, attrs)); break;
        }
        default: throw std::runtime_error("Unsupported Drawing element type");
        }
        element->controlPoints = points;
        staged.elements.emplace_back(type, element.get()); element.release();
    }
    elements.swap(staged.elements); dirty = true;
}

uint32 drawingSerializedSize(const Drawing* drawing, ISerializer* writer) {
    return writer->sizeof_obj(DrawingSnapshot::storage(drawing));
}
void serializeDrawing(const Drawing* drawing, ISerializer* writer) {
    writer->serialize_obj(DrawingSnapshot::storage(drawing));
}
std::shared_ptr<Drawing> deserializeDrawing(IDeserializer* reader) {
    DrawingSnapshot::registerStorage();
    auto* object = reader->deserialize_obj();
    if (!object) return {};
    auto* storage = dynamic_cast<DrawingImpl::Storage*>(object);
    if (!storage || storage->loading) {
        object->release(); throw std::runtime_error("Invalid or cyclic Drawing reference");
    }
    auto shared = std::shared_ptr<DrawingImpl::Storage>(storage, [](auto* value) { value->release(); });
    return std::make_shared<DrawingImpl>(std::move(shared));
}
