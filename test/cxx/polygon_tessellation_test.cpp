// Geometry coverage for tessellation, lazy cache reuse, and point invalidation.
// Build with polygon.cpp, spline.cpp and libtess2 in a GUI-capable configuration.
#include "pdg/sys/polygon.h"
#include "pdg/sys/spline.h"
#include <functional>
#include "tesselator.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

using pdg::Point;
using Points = std::vector<Point>;

// Only the standalone test target enables this friend; no test API is shipped.
namespace pdg {
struct PolygonTestAccess {
    static bool dirty(const Polygon& p) { return p.mTessellationDirty; }
    static const Points& cached(const Polygon& p) { return p.mCachedTessellation; }
    static const Points& read(const Polygon& p) { return p.tessellatedPoints(); }
};
}
using Cache = pdg::PolygonTestAccess;
static void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

static double cross(const Point& a, const Point& b, const Point& c) {
    return (double(b.x)-a.x)*(double(c.y)-a.y)-(double(b.y)-a.y)*(double(c.x)-a.x);
}
static double area(const Points& triangles) {
    double sum=0;
    for(size_t i=0;i+2<triangles.size();i+=3)
        sum+=std::abs(cross(triangles[i],triangles[i+1],triangles[i+2]))/2;
    return sum;
}
static Points reference(const Points& contour) {
    auto* tess=tessNewTess(nullptr);
    if(!tess) throw std::runtime_error("Cannot create reference tessellator");
    std::vector<TESSreal> input;
    for(const auto& p:contour) {input.push_back(p.x); input.push_back(p.y);}
    tessAddContour(tess,2,input.data(),sizeof(TESSreal)*2,int(contour.size()));
    if(!tessTesselate(tess,TESS_WINDING_ODD,TESS_POLYGONS,3,2,nullptr))
        throw std::runtime_error("Reference tessellation failed");
    Points result;
    auto* vertices=tessGetVertices(tess); auto* elements=tessGetElements(tess);
    for(int i=0;i<tessGetElementCount(tess)*3;++i) if(elements[i]!=TESS_UNDEF)
        result.emplace_back(vertices[elements[i]*2],vertices[elements[i]*2+1]);
    tessDeleteTess(tess);
    return result;
}
static bool covers(const Points& triangles,const Point& p) {
    for(size_t i=0;i+2<triangles.size();i+=3) {
        double a=cross(triangles[i],triangles[i+1],p);
        double b=cross(triangles[i+1],triangles[i+2],p);
        double c=cross(triangles[i+2],triangles[i],p);
        if ((a>=0&&b>=0&&c>=0)||(a<=0&&b<=0&&c<=0)) return true;
    }
    return false;
}
static void check(Points contour,const char* name) {
    for(int winding=0;winding<2;++winding) {
        const auto expected=reference(contour);
        const auto actual=pdg::Polygon(contour).tessellate();
        if(actual.size()%3 || std::abs(area(actual)-area(expected))>0.002)
            throw std::runtime_error(std::string(name)+": area mismatch");
        // Offset the sample grid to avoid edges and triangulation diagonals.
        for(float x=-110.123f;x<111;x+=3.17f) for(float y=-110.456f;y<111;y+=3.31f)
            if(covers(actual,Point(x,y))!=covers(expected,Point(x,y)))
                throw std::runtime_error(std::string(name)+": even-odd coverage mismatch");
        std::reverse(contour.begin(),contour.end());
    }
}
static void checkCurrent(pdg::Polygon& p) {
    Points contour;
    for (size_t i=0; i<p.getPointCount(); ++i) contour.push_back(p.getPoint(i));
    const Points expected = contour.size() < 3 ? Points() : reference(contour);
    const auto& actual = Cache::read(p);
    require(!Cache::dirty(p), "Cache still dirty after tessellation");
    require(actual.size()%3 == 0 && std::abs(area(actual)-area(expected)) < 0.02,
            "Cached geometry differs from current points");
    for(float x=-110.123f;x<111;x+=3.17f) for(float y=-110.456f;y<111;y+=3.31f)
        require(covers(actual,Point(x,y))==covers(expected,Point(x,y)), "Stale cached coverage");
    const Point* storage = actual.data();
    require(Cache::read(p).data()==storage, "Repeated read replaced cache storage");
}
static void checkCache() {
    const Points contour{{0,0},{100,0},{100,30},{30,30},{30,100},{0,100}};
    pdg::Polygon p(contour);
    require(Cache::dirty(p) && Cache::cached(p).empty(), "Construction eagerly tessellated");
    p.setPoint(1, Point(90,0));
    require(Cache::dirty(p) && Cache::cached(p).empty(), "Editing eagerly tessellated");
    checkCurrent(p);
    const Points saved=Cache::cached(p);
    auto copy=p.tessellate();
    copy[0]=Point(-999,-999);
    require(Cache::cached(p)==saved, "Public result aliases the cache");
    p.addPoint(p.getPoint(p.getPointCount()-1)); // filtered duplicate, no change
    require(!Cache::dirty(p), "Rejected duplicate invalidated cache");
    p.addSpline(nullptr);
    require(!Cache::dirty(p), "Null spline invalidated cache");
    try {p.setPoint(999, Point());} catch(const std::out_of_range&) {}
    require(!Cache::dirty(p), "Rejected setPoint invalidated cache");

    const std::vector<std::function<void(pdg::Polygon&)>> edits = {
        [](pdg::Polygon& q){q.addPoint(Point(-40,50));},
        [](pdg::Polygon& q){q.insertPoint(1,Point(45,-20));},
        [](pdg::Polygon& q){q.insertPoint(999,Point(-40,50));},
        [](pdg::Polygon& q){q.removePoint(2);},
        [](pdg::Polygon& q){q.setPoint(1,Point(-50,80));}, // creates crossing edges
        [](pdg::Polygon& q){q.clearPoints();},
        [](pdg::Polygon& q){pdg::Spline spline; spline.addSegment(Point(-20,80),
            Point(-50,30),Point(-50,-30),Point(0,0)); q.addSpline(&spline,0.25f);},
        [](pdg::Polygon& q){q.move(pdg::Offset(4,7));},
        [](pdg::Polygon& q){q.moveLeft(4);},
        [](pdg::Polygon& q){q.moveRight(4);},
        [](pdg::Polygon& q){q.moveUp(4);},
        [](pdg::Polygon& q){q.moveDown(4);},
        [](pdg::Polygon& q){q.moveXTo(-10);},
        [](pdg::Polygon& q){q.moveYTo(-10);},
        [](pdg::Polygon& q){q.moveTo(-10,-20);},
        [](pdg::Polygon& q){q.moveTo(Point(-10,-20));},
        [](pdg::Polygon& q){q.center(Point(20,30));},
        [](pdg::Polygon& q){q.center(pdg::Rect(10,20,50,60));},
        [](pdg::Polygon& q){q.scale(0.8f);},
        [](pdg::Polygon& q){q.horzScale(-0.8f);},
        [](pdg::Polygon& q){q.vertScale(0.8f);},
        [](pdg::Polygon& q){q.scaleAround(-0.8f,Point(50,50));},
        [](pdg::Polygon& q){q.rotate(0.4f);},
        [](pdg::Polygon& q){q.rotateAround(0.4f,Point(20,30));},
        [](pdg::Polygon& q){q.rotate(0.4f,Point(10,20));},
        [](pdg::Polygon& q){q+=pdg::Offset(4,7);},
        [](pdg::Polygon& q){q-=pdg::Offset(4,7);},
        [](pdg::Polygon& q){q.scale(0);}
    };
    for (const auto& edit : edits) {
        pdg::Polygon q(contour);
        checkCurrent(q);
        const auto previous=Cache::cached(q);
        edit(q);
        require(Cache::dirty(q), "Point mutation did not invalidate tessellation");
        require(Cache::cached(q)==previous, "Point mutation rebuilt tessellation eagerly");
        checkCurrent(q);
    }
    // Moving transfers the mesh and dirtiness, including moves over a warm cache.
    const auto* storage=Cache::read(p).data();
    pdg::Polygon moved(std::move(p));
    require(!Cache::dirty(moved) && Cache::read(moved).data()==storage, "Move lost warm cache");
    checkCurrent(moved);
    checkCurrent(p);
    pdg::Polygon assigned(contour);
    checkCurrent(assigned);
    assigned=std::move(moved);
    require(!Cache::dirty(assigned) && Cache::read(assigned).data()==storage, "Assignment lost warm cache");
    checkCurrent(assigned);
    checkCurrent(moved);
    assigned.setPoint(1,Point(70,20));
    moved=std::move(assigned);
    require(Cache::dirty(moved), "Assignment accepted stale cache");
    checkCurrent(moved);
    auto shifted=moved+pdg::Offset(10,20);
    auto shiftedBack=moved-pdg::Offset(10,20);
    auto scaled=moved*0.5f;
    checkCurrent(shifted); checkCurrent(shiftedBack); checkCurrent(scaled);
    moved.clearPoints(); checkCurrent(moved);
    moved.addPoint(Point(0,0)); moved.addPoint(Point(50,0)); checkCurrent(moved);
    moved.addPoint(Point(50,50)); checkCurrent(moved);
    require(!moved.tessellate().empty(), "Empty cache survived new points");
}

int main() {
    try {
        check({{0,0},{100,0},{100,100},{0,100}},"rectangle");
        check({{-80,-10},{30,-70},{90,40}},"triangle");
        for(int count=4;count<=10;++count) {
            Points polygon;
            for(int i=0;i<count;++i) {
                double angle=0.17+i*6.283185307179586/count;
                polygon.emplace_back(float(std::cos(angle)*90+std::sin(angle)*12),float(std::sin(angle)*65));
            }
            check(polygon,"convex transformed polygon");
        }
        check({{0,0},{100,0},{100,30},{30,30},{30,100},{0,100}},"concave L");
        check({{0,0},{100,100},{100,0},{0,100}},"bow tie");
        Points star;
        for(int i:{0,2,4,1,3}) {
            double angle=i*6.283185307179586/5;
            star.emplace_back(float(std::cos(angle)*100),float(std::sin(angle)*100));
        }
        check(star,"crossing pentagram with same-sign turns");
        check({{0,0},{50,0},{100,0},{100,100},{0,100}},"collinear edge");
        check({{0,0},{100,0},{100,100},{0,100},{0,0}},"repeated endpoint");
        if(!pdg::Polygon().tessellate().empty()) throw std::runtime_error("Empty polygon produced triangles");
        checkCache();
        std::cout<<"PASS: lazy cache, point invalidation, moves,  convex, concave, crossing, collinear and reversed polygon coverage\n";
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n'; return 1;}
}
