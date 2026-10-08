#include "pdg/sys/collider.h"
#include "pdg/sys/collisionquery.h"
#include <numbers>
#include "image-impl.h"
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <map>
#include <mutex>
#include <set>
#include <stdexcept>
#include <unordered_map>
#ifdef PDG_USE_CHIPMUNK_PHYSICS
#include "chipmunk/chipmunk.h"
#endif

namespace pdg {
namespace {
constexpr double epsilon = 1e-7;
void finitePoint(const Point &p) {
    if (!std::isfinite(p.x) || !std::isfinite(p.y))
        throw std::invalid_argument("Collision coordinates must be finite");
}
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
Point subtract(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
Point times(const Point &a, double s) { return Point(a.x * s, a.y * s); }
struct Geometry {
    CollisionShapeId id = collisionShape_None;
    Point center;
    double radius = 0;
    std::vector<Point> points;
};
Geometry geometry(const Collider::Shape &shape, const SpatialTransform &t,
                  const std::vector<Point> *piece = nullptr) {
    Geometry g;
    g.id = shape.id;
    if (shape.type == collisionShape_Circle || shape.type == collisionShape_Capsule) {
        const bool segment = shape.type == collisionShape_Capsule && shape.vertices[0] != shape.vertices[1];
        const auto start = shape.type == collisionShape_Capsule ? shape.vertices[0] : shape.center;
        const auto end = segment ? shape.vertices[1] : start;
        g.center = t.transformPoint(Point((double(start.x) + end.x) * .5, (double(start.y) + end.y) * .5));
        const double x = std::hypot(t.a, t.b), y = std::hypot(t.c, t.d);
        if (std::abs(x - y) <= epsilon * std::max(1.0, x) &&
            std::abs(t.a * t.c + t.b * t.d) <= epsilon * std::max(1.0, x * y)) {
            g.radius = shape.radius * x;
            if (segment) g.points = {t.transformPoint(start), t.transformPoint(end)};
            return g;
        }
        constexpr double pi = std::numbers::pi;
        const double facing = segment ? std::atan2(double(end.y)-start.y, double(end.x)-start.x) : 0;
        // Two semicircles plus straight sides; a collapsed segment uses the
        // same 32-edge approximation as an affinely deformed circle.
        for (int i = 0; i < (segment ? 34 : 32); ++i) {
            const auto center = segment && i >= 17 ? end : start;
            const double angle = segment ? facing + (i < 17 ? pi*.5 + i*pi/16 : -pi*.5 + (i-17)*pi/16) : i*pi/16;
            g.points.push_back(t.transformPoint(Point(center.x + shape.radius * std::cos(angle),
                                                       center.y + shape.radius * std::sin(angle))));
        }
    } else {
        for (const auto &point : piece ? *piece : shape.vertices)
            g.points.push_back(t.transformPoint(point));
        for (const auto &point : g.points) {
            g.center.x += point.x;
            g.center.y += point.y;
        }
        if (!g.points.empty()) {
            g.center.x /= g.points.size();
            g.center.y /= g.points.size();
        }
    }
    return g;
}
template<class Visitor>
void eachGeometry(const Collider::Shape &shape, const SpatialTransform &frame, Visitor visit) {
    if (shape.pieces.empty()) { if(shape.type!=collisionShape_ImageMask) visit(geometry(shape, frame)); }
    else for (const auto &piece : shape.pieces) visit(geometry(shape, frame, &piece));
}
void appendGeometry(std::vector<Geometry> &out, const Collider::Shape &shape, const SpatialTransform &frame) {
    eachGeometry(shape, frame, [&](Geometry g) { out.push_back(std::move(g)); });
}
std::pair<double, double> project(const Geometry &g, const Point &axis) {
    if (g.points.empty()) {
        const double v = dot(g.center, axis);
        return {v - g.radius, v + g.radius};
    }
    double low = dot(g.points.front(), axis), high = low;
    for (const auto &p : g.points) {
        const auto v = dot(p, axis);
        low = std::min(low, v);
        high = std::max(high, v);
    }
    return {low - g.radius, high + g.radius};
}
bool contact(const Geometry &a, const Geometry &b, ColliderContact &result, double tolerance = 0) {
    std::vector<Point> axes;
    auto edges = [&](const Geometry &g) {
        for (size_t i = 0; i < g.points.size(); ++i) {
            const auto delta = subtract(g.points[(i + 1) % g.points.size()], g.points[i]);
            const double len = std::hypot(delta.x, delta.y);
            if (len > epsilon)
                axes.emplace_back(-delta.y / len, delta.x / len);
        }
    };
    edges(a);
    edges(b);
    if (a.points.size() == 2 || b.points.size() == 2) {
        // A capsule is a segment expanded by a disk. Alongside edge normals,
        // vertex-pair axes cover the rounded vertices of the Minkowski
        // difference, including end-cap contacts and polygon corners.
        const auto vertex = [](const Geometry &g, size_t i) { return g.points.empty() ? g.center : g.points[i]; };
        for (size_t i = 0; i < std::max(size_t(1), a.points.size()); ++i)
            for (size_t j = 0; j < std::max(size_t(1), b.points.size()); ++j) {
                const auto delta = subtract(vertex(b,j), vertex(a,i));
                const double length = std::hypot(delta.x, delta.y);
                if (length > epsilon) axes.push_back(times(delta, 1/length));
            }
    } else if (a.points.empty() && b.points.empty()) {
        const auto d = subtract(b.center, a.center);
        const double length = std::hypot(d.x, d.y);
        axes.push_back(length > epsilon ? times(d, 1 / length) : Point(1, 0));
    } else if (a.points.empty() || b.points.empty()) {
        const auto &circle = a.points.empty() ? a : b;
        const auto &poly = a.points.empty() ? b : a;
        auto closest = poly.points.front();
        double best = std::numeric_limits<double>::infinity();
        for (const auto &p : poly.points) {
            const auto d = subtract(p, circle.center);
            double dist = dot(d, d);
            if (dist < best) {
                best = dist;
                closest = p;
            }
        }
        const auto d = subtract(closest, circle.center);
        const double len = std::hypot(d.x, d.y);
        if (len > epsilon)
            axes.push_back(times(d, 1 / len));
    }
    if (axes.empty())
        return false;
    double depth = std::numeric_limits<double>::infinity();
    Point normal;
    for (auto axis : axes) {
        auto pa = project(a, axis), pb = project(b, axis);
        if (pa.second + tolerance < pb.first || pb.second + tolerance < pa.first)
            return false;
        // Includes containment, unlike intersection length alone.
        double forward = pa.second - pb.first, backward = pb.second - pa.first;
        if (backward < forward) {
            axis = times(axis, -1);
            forward = backward;
        }
        if (forward < depth) {
            depth = forward;
            normal = axis;
        }
    }
    result.normal = Vector(normal.x, normal.y);
    result.penetration = std::max(0.0, depth);
    // Use the tangential midpoint and midpoint of the two supporting planes.
    const Point tangent(-normal.y, normal.x);
    const auto an = project(a, normal), bn = project(b, normal), at = project(a, tangent),
               bt = project(b, tangent);
    const double n = (an.second + bn.first) * .5;
    const double t = (std::max(at.first, bt.first) + std::min(at.second, bt.second)) * .5;
    result.point = Point(normal.x * n + tangent.x * t, normal.y * n + tangent.y * t);
    return true;
}

std::vector<Point> polygonPoints(const Polygon &polygon) {
    std::vector<Point> points;
    for (size_t i = 0; i < polygon.getPointCount(); ++i) points.push_back(polygon.getPoint(i));
    return points;
}
std::vector<std::vector<Point>> polygonPieces(std::vector<Point> points) {
    if (points.size() > 1 && points.front() == points.back()) points.pop_back();
    if (points.size() < 3 || points.size() > 4096)
        throw std::invalid_argument("Collision polygons require 3 to 4096 vertices");
    for (const auto &p : points) finitePoint(p);
    auto cross = [](Point a, Point b, Point c) {
        return (double(b.x)-a.x)*(double(c.y)-a.y)-(double(b.y)-a.y)*(double(c.x)-a.x);
    };
    auto on = [&](Point a, Point b, Point p) {
        return std::abs(cross(a,b,p)) <= epsilon && p.x >= std::min(a.x,b.x)-epsilon &&
            p.x <= std::max(a.x,b.x)+epsilon && p.y >= std::min(a.y,b.y)-epsilon &&
            p.y <= std::max(a.y,b.y)+epsilon;
    };
    // Reject crossings, repeated nonadjacent vertices and overlapping edges.
    for (size_t i=0; i<points.size(); ++i) {
        const auto a=points[i], b=points[(i+1)%points.size()];
        if (a==b) throw std::invalid_argument("Collision polygon has a zero-length edge");
        for (size_t j=i+1; j<points.size(); ++j) {
            if(j==i+1 || (i==0 && j+1==points.size())) continue;
            const auto c=points[j], d=points[(j+1)%points.size()];
            const double abC=cross(a,b,c), abD=cross(a,b,d), cdA=cross(c,d,a), cdB=cross(c,d,b);
            if ((abC*abD<0 && cdA*cdB<0) || on(a,b,c) || on(a,b,d) || on(c,d,a) || on(c,d,b))
                throw std::invalid_argument("Collision polygon must be simple (no crossing or touching edges)");
        }
    }
    bool changed=true;
    while(changed && points.size()>3) {
        changed=false;
        for(size_t i=0; i<points.size(); ++i) {
            const auto a=points[(i+points.size()-1)%points.size()], b=points[i], c=points[(i+1)%points.size()];
            if(std::abs(cross(a,b,c))<=epsilon) {
                if(!on(a,c,b)) throw std::invalid_argument("Collision polygon has a folded edge");
                points.erase(points.begin()+i); changed=true; break;
            }
        }
    }
    double area=0;
    for(size_t i=1;i+1<points.size();++i) area+=cross(points[0],points[i],points[i+1]);
    if(std::abs(area)<=epsilon) throw std::invalid_argument("Collision polygon must have positive area");
    if(area<0) std::reverse(points.begin(),points.end());
    bool convex=true;
    for(size_t i=0;i<points.size();++i)
        if(cross(points[i],points[(i+1)%points.size()],points[(i+2)%points.size()])<=epsilon) convex=false;
    if(convex) return {points};
    // Reuse PDG's headless-capable ear-clipping triangulation, after validating
    // simplicity and winding. A partial triangulation must never become a hull.
    const auto triangles=Polygon(points).triangulate();
    if(triangles.size()!=3*(points.size()-2)) throw std::invalid_argument("Cannot triangulate collision polygon");
    std::vector<std::vector<Point>> pieces;
    for(size_t i=0;i<triangles.size();i+=3) pieces.push_back({triangles[i],triangles[i+1],triangles[i+2]});
    // Merge adjacent triangles wherever their union is convex, reducing seams.
    changed=true;
    while(changed) {
        changed=false;
        // A successful merge erases b. Stop before indexing either piece again.
        for(size_t a=0;!changed&&a<pieces.size();++a) for(size_t b=a+1;!changed&&b<pieces.size();++b)
            for(size_t i=0;!changed&&i<pieces[a].size();++i) for(size_t j=0;!changed&&j<pieces[b].size();++j) {
                const auto &x=pieces[a], &y=pieces[b];
                if(x[i]!=y[(j+1)%y.size()] || x[(i+1)%x.size()]!=y[j]) continue;
                std::vector<Point> joined;
                for(size_t k=0;k<x.size();++k) joined.push_back(x[(i+1+k)%x.size()]);
                for(size_t k=2;k<y.size();++k) joined.push_back(y[(j+k)%y.size()]);
                bool good=true;
                for(size_t k=0;k<joined.size();++k)
                    if(cross(joined[k],joined[(k+1)%joined.size()],joined[(k+2)%joined.size()]) < -epsilon) good=false;
                if(!good) continue;
                pieces[a]=std::move(joined);pieces.erase(pieces.begin()+b);changed=true;
            }
    }
    return pieces;
}

} // namespace

struct Collider::Native {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    cpSpace *space = nullptr;
    cpBody *body = nullptr;
    bool ownsBody = false;
    std::vector<cpShape *> shapes;
    std::vector<double> signature;
    PhysicsBody *physical = nullptr;
    Collider *owner = nullptr;
    std::vector<CollisionShapeId> shapeIds;
    struct Contact {
        Native *other;
        ColliderContact value;
    };
    // Both endpoints index the same arbiter. The reciprocal entry is removed
    // before either Native is destroyed, so these links never retain owners.
    std::unordered_map<cpArbiter *, Contact> contacts;
    CollisionShapeId shapeId(cpShape *shape) const {
        const auto it = std::find(shapes.begin(), shapes.end(), shape);
        return it == shapes.end() ? collisionShape_None : shapeIds[size_t(it - shapes.begin())];
    }
    static void endpoints(cpArbiter *arb, Native *&a, Native *&b, cpShape *&sa, cpShape *&sb) {
        cpArbiterGetShapes(arb, &sa, &sb);
        a = static_cast<Native *>(cpShapeGetUserData(sa));
        b = static_cast<Native *>(cpShapeGetUserData(sb));
    }
    static void separate(cpArbiter *arb, cpSpace *, void *) {
        Native *a, *b;
        cpShape *sa, *sb;
        endpoints(arb, a, b, sa, sb);
        if (a)
            a->contacts.erase(arb);
        if (b)
            b->contacts.erase(arb);
    }
    static cpBool preSolve(cpArbiter *arb, cpSpace *space, void *) {
        Native *a, *b;
        cpShape *sa, *sb;
        endpoints(arb, a, b, sa, sb);
        if (!a || !b || !a->owner->isEnabled() || !b->owner->isEnabled() ||
            !a->owner->canCollideWith(*b->owner) ||
            !a->owner->getPhysicsBody().permitsCollisionWith(b->owner->getPhysicsBody())) {
            separate(arb, space, nullptr);
            return false;
        }
        auto *ownerA=a->owner,*ownerB=b->owner;
        ownerA->addRef();ownerB->addRef();
        std::shared_ptr<Collider> keepA(ownerA,[](Collider *c){c->release();}),keepB(ownerB,[](Collider *c){c->release();});
        const bool allowed=ownerA->passesCollisionFilter(*ownerB)&&ownerB->passesCollisionFilter(*ownerA);
        if(ownerA->mNative.get()!=a || ownerB->mNative.get()!=b) return false;
        if(!allowed) { separate(arb,space,nullptr);return false; }
        const auto points = cpArbiterGetContactPointSet(arb);
        if (!points.count)
            return false;
        ColliderContact c;
        c.collider = a->owner;
        c.other = b->owner;
        c.shape = a->shapeId(sa);
        c.otherShape = b->shapeId(sb);
        c.normal = Vector(points.normal.x, points.normal.y);
        c.sensor = cpShapeGetSensor(sa) || cpShapeGetSensor(sb);
        for (int i = 0; i < points.count; ++i) {
            c.point.x +=
                (points.points[i].pointA.x + points.points[i].pointB.x) / (2 * points.count);
            c.point.y +=
                (points.points[i].pointA.y + points.points[i].pointB.y) / (2 * points.count);
            c.penetration = std::max(c.penetration, -points.points[i].distance);
        }
        a->contacts[arb] = {b, c};
        std::swap(c.collider, c.other);
        std::swap(c.shape, c.otherShape);
        c.normal = Vector(-c.normal.x, -c.normal.y);
        b->contacts[arb] = {a, c};
        return true;
    }
    static void postSolve(cpArbiter *arb, cpSpace *, void *) {
        Native *a, *b;
        cpShape *sa, *sb;
        endpoints(arb, a, b, sa, sb);
        // Chipmunk reports the impulse on A; PDG reports the impulse on other.
        const auto impulse = cpArbiterTotalImpulse(arb);
        if (a) {
            auto it = a->contacts.find(arb);
            if (it != a->contacts.end())
                it->second.value.impulse = Vector(-impulse.x, -impulse.y);
        }
        if (b) {
            auto it = b->contacts.find(arb);
            if (it != b->contacts.end())
                it->second.value.impulse = Vector(impulse.x, impulse.y);
        }
    }
    void beginStep() {
        // Sleeping contacts persist without another pre/post-solve callback.
        // They still produce Stay, but must not repeat a prior frame's impulse.
        for (auto &[arb, contact] : contacts)
            contact.value.impulse = Vector();
    }
    ~Native() {
        for (const auto &[arb, contact] : contacts)
            contact.other->contacts.erase(arb);
        contacts.clear();
        if (physical)
            physical->removeSolverObserver(owner);
        for (auto *shape : shapes)
            cpShapeSetUserData(shape, nullptr);
        if (space && cpSpaceIsLocked(space)) {
            auto *deferred = new Native;
            deferred->space = space;
            deferred->body = body;
            deferred->ownsBody = ownsBody;
            deferred->shapes = std::move(shapes);
            space = nullptr;
            body = nullptr;
            ownsBody = false;
            cpSpaceAddPostStepCallback(
                deferred->space,
                [](cpSpace *, void *key, void *) { delete static_cast<Native *>(key); }, deferred,
                nullptr);
            return;
        }
        for (auto *shape : shapes) {
            if (cpShapeGetSpace(shape))
                cpSpaceRemoveShape(space, shape);
            cpShapeFree(shape);
        }
        if (ownsBody && body) {
            if (cpBodyGetSpace(body))
                cpSpaceRemoveBody(space, body);
            cpBodyFree(body);
        }
    }
#endif
};
Collider::Collider() {
    static std::atomic<uint64_t> next(1);
    mId = next.fetch_add(1);
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    INIT_SCRIPT_OBJECT(mColliderScriptObj);
#endif
}
Collider::Collider(bool) : mPresent(false), mEnabled(false), mCategory(0), mMask(0) {
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    INIT_SCRIPT_OBJECT(mColliderScriptObj);
#endif
}
Collider Collider::NoCollider(false);
Collider::~Collider() { detach(); }
bool Collider::ignores(const char *operation) const {
    if (mPresent)
        return false;
#ifndef NDEBUG
    static std::mutex mutex;
    static std::set<std::string> reported;
    std::lock_guard<std::mutex> lock(mutex);
    if (reported.insert(operation).second)
        std::fprintf(stderr, "PDG NoCollider: ignored %s; create a collider first\n", operation);
#else
    (void)operation;
#endif
    return true;
}
Collider &Collider::setEnabled(bool value) {
    if (!ignores("setEnabled")) {
        mEnabled = value;
        if (!value)
            mNative.reset();
    }
    return *this;
}
Collider &Collider::setSensor(bool value) {
    if (!ignores("setSensor"))
        mSensor = value;
    return *this;
}
Collider &Collider::setFriction(double value) {
    if (ignores("setFriction"))
        return *this;
    if (!std::isfinite(value) || value < 0)
        throw std::invalid_argument("Contact friction must be finite and nonnegative");
    mFriction = value;
    return *this;
}
Collider &Collider::setRestitution(double value) {
    if (ignores("setRestitution"))
        return *this;
    if (!std::isfinite(value) || value < 0 || value > 1)
        throw std::invalid_argument("Contact restitution must be between zero and one");
    mRestitution = value;
    return *this;
}
double Collider::getFriction() const {
    return !mPresent                                    ? 0
           : mFriction >= 0                             ? mFriction
           : getPhysicsBody() == PhysicsBody::NoPhysics ? 1
                                                        : getPhysicsBody().getFriction();
}
double Collider::getRestitution() const {
    return !mPresent                                    ? 0
           : mRestitution >= 0                          ? mRestitution
           : getPhysicsBody() == PhysicsBody::NoPhysics ? 1
                                                        : getPhysicsBody().getRestitution();
}
Collider &Collider::useBodyMaterial() {
    if (!ignores("useBodyMaterial"))
        mFriction = mRestitution = -1;
    return *this;
}
Collider &Collider::setCategory(uint32_t value) {
    if (!ignores("setCategory"))
        mCategory = value;
    return *this;
}
Collider &Collider::setCollisionMask(uint32_t value) {
    if (!ignores("setCollisionMask"))
        mMask = value;
    return *this;
}
Collider &Collider::setGroup(uint32_t value) {
    if (!ignores("setGroup"))
        mGroup = value;
    return *this;
}
void Collider::stopGeometrySource() {
    mGeometryProvider={}; mGeometrySource=colliderSource_Explicit; mSourceIds.clear();
    for(auto &shape:mShapes) shape.source=false;
}
void Collider::useGeometrySource(int source, GeometryProvider provider) {
    if(ignores("useGeometrySource")) return;
    // Validate the first result before replacing the current geometry/provider.
    std::vector<Shape> shapes; provider(shapes);
    for(auto &shape:shapes) { if(!mNextShape) throw std::overflow_error("Collision shape IDs exhausted"); shape.id=mNextShape++; shape.source=true; }
    std::map<std::string,CollisionShapeId> ids;
    for(const auto &shape:shapes) ids.emplace(shape.name,shape.id);
    mShapes=std::move(shapes);mSourceIds=std::move(ids);mGeometryProvider=std::move(provider);mGeometrySource=source;
}
void Collider::refreshGeometry() const {
    if(!mGeometryProvider) return;
    std::vector<Shape> shapes;
    if(!mGeometryProvider(shapes)) return;
    auto ids=mSourceIds; auto next=mNextShape;
    for(auto &shape:shapes) {
        auto it=ids.find(shape.name);
        if(it==ids.end()) { if(!next) throw std::overflow_error("Collision shape IDs exhausted"); it=ids.emplace(shape.name,next++).first; }
        shape.id=it->second;shape.source=true;
    }
    for(const auto &shape:mShapes) if(!shape.source) shapes.push_back(shape);
    mShapes=std::move(shapes);mSourceIds=std::move(ids);mNextShape=next;
}
const Collider::Shape &Collider::findShape(CollisionShapeId id) const {
    refreshGeometry();
    for(const auto &shape:mShapes) if(shape.id==id) return shape;
    throw std::out_of_range("Unknown collision shape ID");
}
bool Collider::isSourceShape(CollisionShapeId id) const { return findShape(id).source; }
std::string Collider::getShapeName(CollisionShapeId id) const { return findShape(id).name; }
int Collider::getShapeType(CollisionShapeId id) const { return findShape(id).type; }
double Collider::getCircleRadius(CollisionShapeId id) const {
    const auto &shape=findShape(id);
    if(shape.type!=collisionShape_Circle) throw std::invalid_argument("Shape is not a circle");
    return shape.radius;
}
Point Collider::getCapsuleStart(CollisionShapeId id) const {
    const auto &shape = findShape(id);
    if (shape.type != collisionShape_Capsule) throw std::invalid_argument("Shape is not a capsule");
    return shape.vertices[0];
}
Point Collider::getCapsuleEnd(CollisionShapeId id) const {
    const auto &shape = findShape(id);
    if (shape.type != collisionShape_Capsule) throw std::invalid_argument("Shape is not a capsule");
    return shape.vertices[1];
}
double Collider::getCapsuleRadius(CollisionShapeId id) const {
    const auto &shape = findShape(id);
    if (shape.type != collisionShape_Capsule) throw std::invalid_argument("Shape is not a capsule");
    return shape.radius;
}
Collider::Shape Collider::imageMaskShape(Image &image, const Rect &pixels, const Rect &bounds, int threshold) {
    if(threshold<1 || threshold>255) throw std::invalid_argument("Alpha threshold must be from 1 to 255");
    for(float v:{pixels.left,pixels.top,pixels.right,pixels.bottom,bounds.left,bounds.top,bounds.right,bounds.bottom})
        if(!std::isfinite(v)) throw std::invalid_argument("Image mask bounds must be finite");
    auto *impl=dynamic_cast<ImageImpl*>(&image);
    // Pixel rectangles address the full atlas; ImageStrip::getWidth() reports
    // one frame rather than the underlying pixel buffer's width.
    const auto pixelWidth=impl ? impl->width : image.getWidth();
    if(pixels.left<0 || pixels.top<0 || pixels.right>pixelWidth || pixels.bottom>image.getHeight() ||
       pixels.width()<=0 || pixels.height()<=0 || bounds.width()<=0 || bounds.height()<=0 ||
       std::floor(pixels.left)!=pixels.left || std::floor(pixels.top)!=pixels.top ||
       std::floor(pixels.right)!=pixels.right || std::floor(pixels.bottom)!=pixels.bottom)
        throw std::invalid_argument("Image mask requires valid integer pixel bounds and positive local dimensions");
    if(impl) impl->requireSnapshotPixels();
    image.retainAlpha();
    auto alpha=[&](int x,int y) { return impl && impl->bpp==8 ? static_cast<const uint8*>(impl->data)[y*impl->pitch+x] : image.getAlphaValue(x,y); };
    std::vector<Rect> rectangles;
    std::map<std::pair<int,int>,size_t> previous;
    for(int y=int(pixels.top);y<int(pixels.bottom);++y) {
        std::map<std::pair<int,int>,size_t> current;
        for(int x=int(pixels.left);x<int(pixels.right);) {
            if(alpha(x,y)<threshold) { ++x; continue; }
            int begin=x++;while(x<int(pixels.right)&&alpha(x,y)>=threshold)++x;
            const auto key=std::make_pair(begin,x);auto found=previous.find(key);
            size_t index;
            if(found!=previous.end()) { index=found->second;rectangles[index].bottom=y+1; }
            else {
                if(rectangles.size()==65536) throw std::invalid_argument("Image mask exceeds 65536 convex pieces");
                index=rectangles.size();rectangles.emplace_back(begin,y,x,y+1);
            }
            current.emplace(key,index);
        }
        previous=std::move(current);
    }
    Shape shape{0,collisionShape_ImageMask,Point(),0,{}, {},{},false};
    for(auto r:rectangles) {
        r.left=bounds.left+(r.left-pixels.left)*bounds.width()/pixels.width();
        r.right=bounds.left+(r.right-pixels.left)*bounds.width()/pixels.width();
        r.top=bounds.top+(r.top-pixels.top)*bounds.height()/pixels.height();
        r.bottom=bounds.top+(r.bottom-pixels.top)*bounds.height()/pixels.height();
        shape.pieces.push_back({Point(r.left,r.top),Point(r.right,r.top),Point(r.right,r.bottom),Point(r.left,r.bottom)});
    }
    return shape;
}
CollisionShapeId Collider::addImageMask(Image &image,const Rect &bounds,int threshold) {
    if(ignores("addImageMask")) return collisionShape_None;
    auto shape=imageMaskShape(image,Rect(0,0,image.getWidth(),image.getHeight()),bounds,threshold);
    if(!mNextShape) throw std::overflow_error("Collision shape IDs exhausted");
    shape.id=mNextShape++;mShapes.push_back(std::move(shape));return mShapes.back().id;
}
Collider &Collider::setImageMask(Image &image,const Rect &bounds,int threshold) {
    if(ignores("setImageMask")) return *this;
    addImageMask(image,bounds,threshold);auto shape=std::move(mShapes.back());
    stopGeometrySource();mShapes.clear();mShapes.push_back(std::move(shape));return *this;
}
Collider &Collider::setCollisionFilter(std::function<bool(const Collider &,const Collider &)> filter) {
    if(!ignores("setCollisionFilter")) mCollisionFilter=std::move(filter);
    return *this;
}
bool Collider::passesCollisionFilter(const Collider &other) const {
    auto filter=mCollisionFilter;
    try { return !filter || filter(*this,other); }
    catch(const std::exception &e) { mContactError=e.what(); }
    catch(...) { mContactError="Collision filter threw an unknown exception"; }
    return false;
}
CollisionShapeId Collider::addCircle(double radius, const Point &center) {
    if (ignores("addCircle"))
        return collisionShape_None;
    finitePoint(center);
    if (!std::isfinite(radius) || radius <= 0)
        throw std::invalid_argument("Collision radius must be finite and positive");
    if (!mNextShape)
        throw std::overflow_error("Collision shape IDs exhausted");
    mShapes.push_back({mNextShape++, collisionShape_Circle, center, radius, {}, {}, {}, false});
    return mShapes.back().id;
}
CollisionShapeId Collider::addCapsule(const Point &start, const Point &end, double radius) {
    if (ignores("addCapsule")) return collisionShape_None;
    finitePoint(start); finitePoint(end);
    if (!std::isfinite(radius) || radius <= 0)
        throw std::invalid_argument("Collision radius must be finite and positive");
    if (!mNextShape) throw std::overflow_error("Collision shape IDs exhausted");
    mShapes.push_back({mNextShape, collisionShape_Capsule, Point(), radius, {start, end}, {}, {}, false});
    return mNextShape++;
}
Collider &Collider::setCapsule(const Point &start, const Point &end, double radius) {
    if (ignores("setCapsule")) return *this;
    addCapsule(start, end, radius);
    auto shape = std::move(mShapes.back());
    stopGeometrySource(); mShapes.clear(); mShapes.push_back(std::move(shape));
    return *this;
}
CollisionShapeId Collider::addPolygon(const std::vector<Point> &vertices) {
    if (ignores("addPolygon")) return collisionShape_None;
    auto pieces = polygonPieces(vertices);
    if (!mNextShape) throw std::overflow_error("Collision shape IDs exhausted");
    Shape shape{mNextShape, collisionShape_Polygon, Point(), 0, {}, {}, {}, false};
    if(pieces.size()==1) { shape.type=collisionShape_Convex; shape.vertices=std::move(pieces.front()); }
    else shape.pieces=std::move(pieces);
    mShapes.push_back(std::move(shape));
    return mNextShape++;
}
CollisionShapeId Collider::addPolygon(const Polygon &polygon) { return addPolygon(polygonPoints(polygon)); }
Collider &Collider::setPolygon(const std::vector<Point> &vertices) {
    if (ignores("setPolygon")) return *this;
    addPolygon(vertices);
    auto shape=std::move(mShapes.back());
    stopGeometrySource(); mShapes.clear(); mShapes.push_back(std::move(shape));
    return *this;
}
Collider &Collider::setPolygon(const Polygon &polygon) { return setPolygon(polygonPoints(polygon)); }
CollisionShapeId Collider::addBox(const Rect &r) {
    if (ignores("addBox"))
        return collisionShape_None;
    if (!std::isfinite(r.left) || !std::isfinite(r.right) || !std::isfinite(r.top) ||
        !std::isfinite(r.bottom) || r.right <= r.left || r.bottom <= r.top)
        throw std::invalid_argument("Collision box must have finite positive dimensions");
    return addPolygon({Point(r.left, r.top), Point(r.right, r.top), Point(r.right, r.bottom),
                       Point(r.left, r.bottom)});
}
Collider &Collider::setCircle(double radius, const Point &center) {
    if (ignores("setCircle"))
        return *this;
    const auto id = addCircle(radius, center);
    auto shape = std::move(mShapes.back());
    stopGeometrySource();
    mShapes.clear();
    mShapes.push_back(std::move(shape));
    (void)id;
    return *this;
}
Collider &Collider::setBox(const Rect &bounds) {
    if (ignores("setBox"))
        return *this;
    addBox(bounds);
    auto shape = std::move(mShapes.back());
    stopGeometrySource();
    mShapes.clear();
    mShapes.push_back(std::move(shape));
    return *this;
}
bool Collider::removeShape(CollisionShapeId id) {
    if (ignores("removeShape"))
        return false;
    refreshGeometry();
    if(mSourceIds.end()!=std::find_if(mSourceIds.begin(),mSourceIds.end(),[&](const auto &entry){return entry.second==id;}))
        throw std::logic_error("Cannot remove a shape controlled by a frame or animation source");
    auto i =
        std::find_if(mShapes.begin(), mShapes.end(), [id](const Shape &s) { return s.id == id; });
    if (i == mShapes.end())
        return false;
    mShapes.erase(i);
    mNative.reset();
    return true;
}
Collider &Collider::clearShapes() {
    if (!ignores("clearShapes")) {
        stopGeometrySource();
        mShapes.clear();
        mNative.reset();
    }
    return *this;
}
CollisionShapeId Collider::getShapeId(uint32_t index) const {
    refreshGeometry();
    if (index >= mShapes.size())
        throw std::out_of_range("Collision shape index");
    return mShapes[index].id;
}
SpatialTransform Collider::transform() const {
    return mTransform ? mTransform() : mDetachedTransform;
}
Rect Collider::getBounds() const {
    refreshGeometry();
    if (mShapes.empty())
        return Rect();
    double l = INFINITY, t = INFINITY, r = -INFINITY, b = -INFINITY;
    const auto frame = transform();
    for (const auto &s : mShapes) {
        eachGeometry(s, frame, [&](const Geometry &g) {
        const auto x = project(g, Point(1, 0)), y = project(g, Point(0, 1));
        l = std::min(l, x.first);
        r = std::max(r, x.second);
        t = std::min(t, y.first);
        b = std::max(b, y.second);
        });
    }
    return std::isfinite(l) ? Rect(l, t, r, b) : Rect();
}
bool Collider::contains(const Point &p) const {
    refreshGeometry();
    finitePoint(p);
    Geometry point;
    point.center = p;
    for (const auto &s : mShapes) {
        bool hit=false;
        eachGeometry(s, transform(), [&](const Geometry &g) { ColliderContact c; hit=hit||contact(g,point,c); });
        if(hit) return true;
    }
    return false;
}
bool Collider::overlaps(const Collider &other) const {
    refreshGeometry(); other.refreshGeometry();
    const auto a = transform(), b = other.transform();
    ColliderContact c;
    for (const auto &x : mShapes)
        for (const auto &y : other.mShapes)
            {
                bool hit=false;
                eachGeometry(x,a,[&](const Geometry &gx) { eachGeometry(y,b,[&](const Geometry &gy) { hit=hit||contact(gx,gy,c); }); });
                if(hit) return true;
            }
    return false;
}
Collider &Collider::setPhysicsBody(PhysicsBody &body) {
    if (ignores("setPhysicsBody"))
        return *this;
    if (body == PhysicsBody::NoPhysics)
        throw std::invalid_argument(
            "Compound collision association requires an instantiated PhysicsBody");
    if (body.world() != world())
        throw std::invalid_argument(
            "Compound collision geometry and body must belong to the same world");
    body.addRef();
    if (mCompoundBody)
        mCompoundBody->release();
    mCompoundBody = &body;
    mNative.reset();
    return *this;
}
Collider &Collider::useOwnerPhysics() {
    if (!ignores("useOwnerPhysics")) {
        if (mCompoundBody)
            mCompoundBody->release();
        mCompoundBody = nullptr;
        mNative.reset();
    }
    return *this;
}
PhysicsBody &Collider::getPhysicsBody() const {
    return mCompoundBody ? *mCompoundBody : mOwnerBody ? mOwnerBody() : PhysicsBody::NoPhysics;
}
void Collider::attach(std::function<SpatialTransform()> transform,
                      std::function<PhysicsBody &()> body, std::function<const void *()> world) {
    if (!mPresent)
        throw std::logic_error("Cannot attach NoCollider");
    if (mTransform)
        throw std::logic_error("Collider already attached");
    mTransform = std::move(transform);
    mOwnerBody = std::move(body);
    mOwnerWorld = std::move(world);
}
void Collider::detach() {
    // Freeze the last artwork pose while the owner still exists. Teardown must
    // remain safe even if its current source can no longer provide geometry.
    try { refreshGeometry(); } catch (...) {}
    stopGeometrySource();
    mNative.reset();
    if (mTransform) {
        try {
            mDetachedTransform = mTransform();
        } catch (...) {
        }
    }
    mTransform = {};
    mOwnerBody = {};
    mOwnerWorld = {};
    mHandler = {};
    mCollisionFilter = {};
    mEventSink = {};
    mWorldFilter = {};
    mWorld = nullptr;
    if (mCompoundBody) {
        mCompoundBody->release();
        mCompoundBody = nullptr;
    }
}
Collider &Collider::setContactHandler(std::function<void(const ColliderContact &)> handler) {
    if (!ignores("setContactHandler"))
        mHandler = std::move(handler);
    return *this;
}
Collider &Collider::setWantsContactEvents(bool value) {
    if (!ignores("setWantsContactEvents"))
        mWantsContactEvents = value;
    return *this;
}
void Collider::dispatch(const ColliderContact &c) {
    auto handler = mHandler;
    try {
        if (handler)
            handler(c);
        auto sink = mEventSink;
        if (mWantsContactEvents && sink)
            sink(c);
        mContactError.clear();
    } catch (const std::exception &e) {
        mContactError = e.what();
    } catch (...) {
        mContactError = "Collision handler threw an unknown exception";
    }
}
bool Collider::canCollideWith(const Collider &other) const {
    if (mWorldFilter)
        return mWorldFilter(other.world());
    if (other.mWorldFilter)
        return other.mWorldFilter(world());
    return world() == other.world();
}
void Collider::syncNative(void *nativeSpace, const void *world) {
    if (!mPresent)
        return;
    refreshGeometry();
    mWorld = world;
    if (!world)
        mWorldFilter = {};
    // Detaching or transferring an explicitly associated body must not leave
    // geometry driving a body outside this collider's world.
    if (mCompoundBody && (!mCompoundBody->isAttached() || mCompoundBody->world() != world))
        useOwnerPhysics();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    auto *space = static_cast<cpSpace *>(nativeSpace);
    if (!space || !isEnabled() || mShapes.empty()) {
        mNative.reset();
        return;
    }
    if (cpSpaceIsLocked(space))
        throw std::logic_error("Update colliders outside the physical solve");
    auto &physics = getPhysicsBody();
    auto *body = static_cast<cpBody *>(physics.nativeBody());
    // A basic dynamic body is integrated by the basic world, not silently attached.
    if (physics != PhysicsBody::NoPhysics && !body) {
        mNative.reset();
        return;
    }
    const auto frame = transform();
    if (std::abs(frame.a * frame.d - frame.b * frame.c) < epsilon) {
        mNative.reset();
        return;
    }
    const auto state = physics.getState();
    const auto inverse = body
                             ? SpatialTransform::fromTRS(state.x, state.y, state.rotation).inverse()
                             : SpatialTransform();
    const auto local = SpatialTransform::compose(inverse, frame);
    std::vector<double> signature{local.a,
                                  local.b,
                                  local.c,
                                  local.d,
                                  local.tx,
                                  local.ty,
                                  double(mCategory),
                                  double(mMask),
                                  double(mGroup),
                                  double(mSensor),
                                  getFriction(),
                                  getRestitution(),
                                  double(body ? cpBodyGetType(body) : CP_BODY_TYPE_STATIC)};
    for (const auto &shape : mShapes) {
        signature.insert(signature.end(), {double(shape.id), double(shape.type), shape.radius,
                                           shape.center.x, shape.center.y});
        signature.push_back(double(shape.vertices.size()));
        for (const auto &p : shape.vertices) signature.insert(signature.end(), {p.x, p.y});
        for (const auto &piece : shape.pieces) {
            signature.push_back(double(piece.size()));
            for (const auto &p : piece) signature.insert(signature.end(), {p.x, p.y});
        }
    }
    if (mNative && mNative->space == space &&
        ((body && mNative->body == body) || (!body && mNative->ownsBody)) &&
        mNative->signature.size() == signature.size()) {
        bool same = true;
        for (size_t i = 0; i < signature.size(); ++i) {
            double tolerance = i < 6 ? 1e-6 * std::max(1.0, std::abs(signature[i])) : 0;
            if (body && (i == 4 || i == 5)) {
                // Animated owners publish float positions; native bodies retain
                // doubles. Subtracting those world positions leaves float-sized
                // roundoff in this local offset, especially far from the origin.
                // Do not rebuild shapes (and discard warm-started contacts) for
                // changes below the precision of the published owner transform.
                const double x = std::max({1.0, std::abs(frame.tx), std::abs(state.x)});
                const double y = std::max({1.0, std::abs(frame.ty), std::abs(state.y)});
                const double roundoff =
                    std::numeric_limits<float>::epsilon() *
                    (i == 4 ? std::abs(inverse.a) * x + std::abs(inverse.c) * y
                            : std::abs(inverse.b) * x + std::abs(inverse.d) * y);
                tolerance = std::max(tolerance, roundoff);
            }
            if (std::abs(mNative->signature[i] - signature[i]) > tolerance) {
                same = false;
                break;
            }
        }
        if (same) {
            mNative->beginStep();
            return;
        }
    }
    mNative.reset();
    auto next = std::make_unique<Native>();
    next->space = space;
    next->body = body;
    next->owner = this;
    next->signature = std::move(signature);
    if (!body) {
        next->body = cpBodyNewStatic();
        next->ownsBody = true;
        cpSpaceAddBody(space, next->body);
    }
    for (const auto &shape : mShapes) {
        eachGeometry(shape, local, [&](const Geometry &g) {
        cpShape *native = nullptr;
        if (g.points.empty())
            native = cpCircleShapeNew(next->body, g.radius, cpv(g.center.x, g.center.y));
        else if (g.points.size() == 2)
            native = cpSegmentShapeNew(next->body, cpv(g.points[0].x, g.points[0].y),
                                        cpv(g.points[1].x, g.points[1].y), g.radius);
        else {
            std::vector<cpVect> vertices;
            for (const auto &p : g.points)
                vertices.push_back(cpv(p.x, p.y));
            native = cpPolyShapeNew(next->body, int(vertices.size()), vertices.data(),
                                    cpTransformIdentity, 0);
        }
        cpShapeSetFilter(native, cpShapeFilterNew(mGroup, mCategory, mMask));
        cpShapeSetSensor(native, mSensor);
        cpShapeSetFriction(native, getFriction());
        cpShapeSetElasticity(native, getRestitution());
        cpShapeSetCollisionType(native, 0x434f4c4c);
        cpShapeSetUserData(native, next.get());
        cpSpaceAddShape(space, native);
        next->shapes.push_back(native);
        next->shapeIds.push_back(shape.id);
        });
    }
    if(next->shapes.empty()) return;
    if (body) {
        next->physical = &physics;
        next->owner = this;
        physics.addSolverObserver(this, [this] { mNative.reset(); });
    }
    auto *handler = cpSpaceAddCollisionHandler(space, 0x434f4c4c, 0x434f4c4c);
    handler->preSolveFunc = Native::preSolve;
    handler->postSolveFunc = Native::postSolve;
    handler->separateFunc = Native::separate;
    mNative = std::move(next);
#else
    (void)nativeSpace;
#endif
}

namespace {
using Key = std::tuple<uint64_t, uint32_t, uint64_t, uint32_t>;
struct SavedContact {
    std::shared_ptr<Collider> a, b;
    ColliderContact contact;
};
std::shared_ptr<Collider> retain(Collider *c) {
    c->addRef();
    return std::shared_ptr<Collider>(c, [](Collider *p) { p->release(); });
}
void resolve(ColliderContact &c, double seconds) {
    if (c.sensor || seconds <= 0)
        return;
    auto &a = c.collider->getPhysicsBody();
    auto &b = c.other->getPhysicsBody();
    if (&a == &b && a != PhysicsBody::NoPhysics)
        return;
    const double ia = a.getMode() == physicsBody_Dynamic ? 1 / a.getMass() : 0;
    const double ib = b.getMode() == physicsBody_Dynamic ? 1 / b.getMass() : 0;
    if (ia + ib == 0)
        return;
    const auto sa = a.getState(), sb = b.getState();
    const Point ra(c.point.x - sa.x, c.point.y - sa.y), rb(c.point.x - sb.x, c.point.y - sb.y);
    const double ja = a.getMode() == physicsBody_Dynamic ? 1 / a.getMomentOfInertia() : 0;
    const double jb = b.getMode() == physicsBody_Dynamic ? 1 / b.getMomentOfInertia() : 0;
    const Point n(c.normal.x, c.normal.y), t(-n.y, n.x);
    auto cross = [](const Point &x, const Point &y) { return x.x * y.y - x.y * y.x; };
    const Point v(
        sb.velocityX - sb.angularVelocity * rb.y - sa.velocityX + sa.angularVelocity * ra.y,
        sb.velocityY + sb.angularVelocity * rb.x - sa.velocityY - sa.angularVelocity * ra.x);
    const double closing = dot(v, n), an = cross(ra, n), bn = cross(rb, n);
    const double restitution = c.collider->getRestitution() * c.other->getRestitution();
    const double impulse =
        closing < 0 ? -(1 + restitution) * closing / (ia + ib + an * an * ja + bn * bn * jb) : 0;
    const double at = cross(ra, t), bt = cross(rb, t);
    const double friction = c.collider->getFriction() * c.other->getFriction();
    const double slide = std::clamp(-dot(v, t) / (ia + ib + at * at * ja + bt * bt * jb),
                                    -friction * impulse, friction * impulse);
    c.impulse = Vector(n.x * impulse + t.x * slide, n.y * impulse + t.y * slide);
    a.applyContactImpulse(Vector(-c.impulse.x, -c.impulse.y), c.point);
    b.applyContactImpulse(c.impulse, c.point);
    const double correction = std::max(0.0, c.penetration - .001) * .8 / (ia + ib);
    a.correctContactPosition(Vector(-n.x * correction * ia, -n.y * correction * ia));
    b.correctContactPosition(Vector(n.x * correction * ib, n.y * correction * ib));
}
} // namespace
struct CollisionWorld::Impl {
    std::map<Key, SavedContact> previous;
    bool stepping = false;
};
CollisionWorld::CollisionWorld() : mImpl(std::make_unique<Impl>()) {}
CollisionWorld::~CollisionWorld() = default;
void CollisionWorld::step(const std::vector<Collider *> &input, double seconds,
                          std::function<bool(const Collider &, const Collider &)> pairFilter) {
    if (!std::isfinite(seconds) || seconds < 0)
        throw std::invalid_argument("Collision step requires nonnegative finite seconds");
    if (mImpl->stepping)
        throw std::logic_error("Collision dispatch cannot recursively step its world");
    struct Guard {
        bool &flag;
        Guard(bool &f) : flag(f) { flag = true; }
        ~Guard() { flag = false; }
    } guard(mImpl->stepping);
    std::vector<std::shared_ptr<Collider>> colliders;
    for (auto *c : input)
        if (c && c->isEnabled() && c->isAttached()) { c->refreshGeometry(); colliders.push_back(retain(c)); }
    std::sort(colliders.begin(), colliders.end(),
              [](const auto &a, const auto &b) { return a->getId() < b->getId(); });
    colliders.erase(std::unique(colliders.begin(), colliders.end()), colliders.end());
    mStatistics = StepStatistics();
    std::map<Key, SavedContact> current;
    auto permitted = [&](const Collider &a, const Collider &b) {
        if (!a.canCollideWith(b) || (pairFilter && !pairFilter(a, b)))
            return false;
        if (!(a.mCategory & b.mMask) || !(b.mCategory & a.mMask) ||
            (a.mGroup && a.mGroup == b.mGroup))
            return false;
        auto &ab = a.getPhysicsBody();
        auto &bb = b.getPhysicsBody();
        return !(&ab == &bb && ab != PhysicsBody::NoPhysics) && ab.permitsCollisionWith(bb);
    };
    auto save = [&](const std::shared_ptr<Collider> &a, const std::shared_ptr<Collider> &b,
                    ColliderContact c) {
        const Key key(a->mId, c.shape, b->mId, c.otherShape);
        c.phase = mImpl->previous.count(key) ? collision_Stay : collision_Begin;
        auto [it, inserted]=current.emplace(key, SavedContact{a, b, c});
        if(!inserted) {
            auto &saved=it->second.contact;
            const Vector total(saved.impulse.x+c.impulse.x,saved.impulse.y+c.impulse.y);
            if(c.penetration>saved.penetration) saved=c;
            saved.impulse=total;
        }
    };
    std::vector<std::shared_ptr<Collider>> fallback;
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (seconds > 0) {
        // Contact callbacks already performed narrow-phase detection, including
        // sensors and kinematic pairs. Reuse their stable shape IDs and manifold.
        std::set<cpSpace *> spaces;
        size_t nativeCount = 0;
        for (const auto &c : colliders) {
            if (c->mNative) {
                ++nativeCount;
                spaces.insert(c->mNative->space);
            }
        }
        // Do not allocate a native lookup table for an entirely basic world.
        if (nativeCount) {
            std::unordered_map<const Collider *, size_t> selected;
            selected.reserve(nativeCount);
            for (size_t i = 0; i < colliders.size(); ++i)
                if (colliders[i]->mNative)
                    selected.emplace(colliders[i].get(), i);
            for (const auto &a : colliders)
                if (a->mNative) {
                    for (const auto &[arb, entry] : a->mNative->contacts) {
                        const auto &c = entry.value;
                        if (a->mId >= c.other->mId)
                            continue;
                        const auto found = selected.find(c.other);
                        if (found == selected.end())
                            continue;
                        const auto &b = colliders[found->second];
                        if (!permitted(*a, *b))
                            continue;
                        save(a, b, c);
                        ++mStatistics.nativeContacts;
                    }
                }
        }
        if (nativeCount == colliders.size() && spaces.size() == 1) {
            // Chipmunk skips static/static pairs. Only those require PDG geometry;
            // ordinary all-native frames do no second broad or narrow phase.
            for (const auto &c : colliders)
                if (cpBodyGetType(c->mNative->body) == CP_BODY_TYPE_STATIC)
                    fallback.push_back(c);
        } else
            fallback = colliders; // mixed solvers/spaces require cross-pair detection
    } else
        fallback = colliders; // zero-time inspection has no new native solve
#else
    fallback = colliders;
#endif
    // Keep the fallback for basic, mixed-solver and static/static pairs. Native
    // bounds come from Chipmunk; transform native geometry only for a fallback pair.
    struct Proxy {
        std::shared_ptr<Collider> collider;
        Rect bounds;
        std::vector<Geometry> shapes;
        void *nativeSpace = nullptr;
        bool nativeStatic = false;
    };
    std::vector<Proxy> proxies;
    if (fallback.size() > 1)
        for (const auto &c : fallback) {
            if (c->mShapes.empty())
                continue;
            Proxy proxy{c, Rect(), {}};
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            if (seconds > 0 && c->mNative) {
                proxy.nativeSpace = c->mNative->space;
                proxy.nativeStatic = cpBodyGetType(c->mNative->body) == CP_BODY_TYPE_STATIC;
                auto bounds = cpShapeGetBB(c->mNative->shapes.front());
                for (size_t i = 1; i < c->mNative->shapes.size(); ++i)
                    bounds = cpBBMerge(bounds, cpShapeGetBB(c->mNative->shapes[i]));
                proxy.bounds = Rect(bounds.l, bounds.b, bounds.r, bounds.t);
            } else
#endif
            {
                const auto frame = c->transform();
                if (std::abs(frame.a * frame.d - frame.b * frame.c) < epsilon)
                    continue;
                proxy.bounds = c->getBounds();
                for (const auto &shape : c->mShapes)
                    appendGeometry(proxy.shapes, shape, frame);
            }
            proxies.push_back(std::move(proxy));
        }
    std::sort(proxies.begin(), proxies.end(), [](const Proxy &a, const Proxy &b) {
        return a.bounds.left < b.bounds.left ||
               (a.bounds.left == b.bounds.left && a.collider->getId() < b.collider->getId());
    });
    for (size_t i = 0; i < proxies.size(); ++i)
        for (size_t j = i + 1; j < proxies.size(); ++j) {
            if (proxies[j].bounds.left > proxies[i].bounds.right + .1)
                break;
            if (proxies[j].bounds.top > proxies[i].bounds.bottom + .1 ||
                proxies[i].bounds.top > proxies[j].bounds.bottom + .1)
                continue;
            Proxy *ap = &proxies[i], *bp = &proxies[j];
            if (ap->nativeSpace && ap->nativeSpace == bp->nativeSpace &&
                !(ap->nativeStatic && bp->nativeStatic))
                continue;
            if (ap->collider->getId() > bp->collider->getId())
                std::swap(ap, bp);
            auto a = ap->collider, b = bp->collider;
            if (!permitted(*a, *b) || !a->passesCollisionFilter(*b) || !b->passesCollisionFilter(*a) ||
                !a->isAttached() || !b->isAttached() || !a->isEnabled() || !b->isEnabled())
                continue;
            for (auto *proxy : {ap, bp})
                if (proxy->shapes.empty()) {
                    const auto frame = proxy->collider->transform();
                    for (const auto &shape : proxy->collider->mShapes)
                        appendGeometry(proxy->shapes, shape, frame);
                }
            for (const auto &as : ap->shapes)
                for (const auto &bs : bp->shapes) {
                    ColliderContact c;
                    c.collider = a.get();
                    c.other = b.get();
                    c.shape = as.id;
                    c.otherShape = bs.id;
                    c.sensor = a->mSensor || b->mSensor;
                    ++mStatistics.fallbackShapeTests;
                    if (!contact(as, bs, c))
                        continue;
                    if (seconds > 0)
                        resolve(c, seconds);
                    save(a, b, c);
                }
        }
    std::vector<SavedContact> events;
    for (const auto &entry : current)
        events.push_back(entry.second);
    for (const auto &[key, old] : mImpl->previous)
        if (!current.count(key)) {
            auto end = old;
            end.contact.phase = collision_End;
            end.contact.impulse = Vector();
            end.contact.penetration = 0;
            events.push_back(std::move(end));
        }
    mImpl->previous = std::move(current);
    for (const auto &event : events) {
        auto c = event.contact;
        event.a->dispatch(c);
        std::swap(c.collider, c.other);
        std::swap(c.shape, c.otherShape);
        c.normal = Vector(-c.normal.x, -c.normal.y);
        c.impulse = Vector(-c.impulse.x, -c.impulse.y);
        event.b->dispatch(c);
    }
}
#include "collisionquery.inc"
} // namespace pdg
