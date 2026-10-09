// Shared collider geometry queries. Included by collider.cpp inside namespace pdg.
namespace {
bool queryHitLess(const CollisionQueryHit& a, const CollisionQueryHit& b) {
    if (a.distance != b.distance) return a.distance < b.distance;
    if (a.collider->getId() != b.collider->getId()) return a.collider->getId() < b.collider->getId();
    return a.shapeId < b.shapeId;
}
Point closestSegment(const Point& p, const Point& a, const Point& b) {
    const auto ab = subtract(b,a);
    const double length2 = dot(ab,ab);
    return a + times(ab, length2 ? std::clamp(dot(subtract(p,a),ab)/length2,0.0,1.0) : 0);
}
struct QueryNearest { Point point; Vector normal; double distance; };
QueryNearest queryNearest(const Geometry& g, const Point& p, bool filled = true) {
    Point closest = g.center;
    Point boundaryNormal;
    bool inside = false;
    if (g.points.size() == 2) closest = closestSegment(p,g.points[0],g.points[1]);
    else if (g.points.size() >= 3) {
        double best = INFINITY, area = 0;
        bool positive = false, negative = false;
        for (size_t i=0;i<g.points.size();++i) {
            const auto a=g.points[i], b=g.points[(i+1)%g.points.size()];
            area += double(a.x)*b.y-double(a.y)*b.x;
            const auto ab=subtract(b,a), ap=subtract(p,a);
            const double side=double(ab.x)*ap.y-double(ab.y)*ap.x;
            positive |= side>0; negative |= side<0;
            const auto q=closestSegment(p,a,b), d=subtract(p,q);
            const double distance2=dot(d,d);
            if (distance2<best) {
                best=distance2; closest=q;
                const double length=std::hypot(ab.x,ab.y);
                boundaryNormal=length ? Point(ab.y/length,-ab.x/length) : Point();
            }
        }
        inside = area != 0 && !(positive && negative);
        if (area<0) boundaryNormal=times(boundaryNormal,-1);
    }
    const auto offset=subtract(p,closest);
    const double length=std::hypot(offset.x,offset.y);
    if (filled && (inside || length <= g.radius)) return {p,Vector(),0};
    if (!length) return {closest,Vector(boundaryNormal.x,boundaryNormal.y),0};
    const auto normal=times(offset,1/length);
    return {closest + times(normal,g.radius),Vector(normal.x,normal.y),length-g.radius};
}
bool rayCircle(const Point& start, const Point& delta, const Point& center,
               double radius, double& fraction) {
    const auto offset=subtract(start,center);
    const double a=dot(delta,delta), b=dot(offset,delta), c=dot(offset,offset)-radius*radius;
    if (!a) return false;
    const double discriminant=b*b-a*c;
    if (discriminant<0) return false;
    const double t=(-b-std::sqrt(discriminant))/a;
    if (t<0 || t>1) return false;
    fraction=t; return true;
}
bool rayCapsule(const Point& start, const Point& delta, const Point& a,
                const Point& b, double radius, double& fraction) {
    double best=INFINITY, t;
    if (rayCircle(start,delta,a,radius,t)) best=t;
    if (rayCircle(start,delta,b,radius,t)) best=std::min(best,t);
    const auto edge=subtract(b,a);
    const double length=std::hypot(edge.x,edge.y);
    if (length) {
        const Point tangent(edge.x/length,edge.y/length), normal(-tangent.y,tangent.x);
        const auto offset=subtract(start,a);
        const double speed=dot(delta,normal), origin=dot(offset,normal);
        if (speed) for (double side : {-radius,radius}) {
            t=(side-origin)/speed;
            const double along=dot(offset,tangent)+t*dot(delta,tangent);
            if (t>=0 && t<=1 && along>=0 && along<=length) best=std::min(best,t);
        }
    }
    if (!std::isfinite(best)) return false;
    fraction=best; return true;
}
bool queryCast(const Geometry& g, const CollisionQueryGeometry& query, CollisionQueryHit& hit) {
    const auto initial=queryNearest(g,query.start);
    if (initial.distance<=query.radius) {
        hit.point=initial.point; hit.initialOverlap=true; return true;
    }
    const auto delta=subtract(query.end,query.start);
    double fraction=INFINITY, t;
    if (g.points.empty()) {
        if (rayCircle(query.start,delta,g.center,g.radius+query.radius,t)) fraction=t;
    } else if (g.points.size()==2) {
        if (rayCapsule(query.start,delta,g.points[0],g.points[1],g.radius+query.radius,t)) fraction=t;
    } else {
        for (size_t i=0;i<g.points.size();++i)
            if (rayCapsule(query.start,delta,g.points[i],g.points[(i+1)%g.points.size()],query.radius,t))
                fraction=std::min(fraction,t);
    }
    if (!std::isfinite(fraction)) return false;
    const auto center=query.start+times(delta,fraction);
    auto nearest=queryNearest(g,center,false);
    hit.point=nearest.point; hit.normal=nearest.normal;
    hit.fraction=fraction; hit.distance=fraction*std::hypot(delta.x,delta.y);
    return true;
}
void validateQuery(const CollisionQueryGeometry& query) {
    finitePoint(query.start); finitePoint(query.end);
    if (!std::isfinite(query.radius) || query.radius<0 ||
        !std::isfinite(query.maxDistance) || query.maxDistance<0)
        throw std::invalid_argument("Query radii and distances must be finite and nonnegative");
    if (query.kind==CollisionQueryKind::Box) {
        const auto& b=query.box;
        for (double value : {double(b.left),double(b.top),double(b.right),double(b.bottom),double(b.radians),double(b.centerOffset.x),double(b.centerOffset.y)})
            if (!std::isfinite(value)) throw std::invalid_argument("Query box must be finite");
        if (b.right<=b.left || b.bottom<=b.top) throw std::invalid_argument("Query box must have positive dimensions");
    }
}
}
CollisionQueryBuffer::CollisionQueryBuffer(uint32_t capacity):mCapacity(capacity) {
    if (capacity>1048576) throw std::invalid_argument("Query capacity exceeds 1048576");
    mHits.reserve(capacity);
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    INIT_SCRIPT_OBJECT(mCollisionQueryBufferScriptObj);
#endif
}
CollisionQueryBuffer::~CollisionQueryBuffer() { resetHits(); }
void CollisionQueryBuffer::requireWritable() const {
    if(mQuerying)throw std::logic_error("Query buffer is already in use");
}
void CollisionQueryBuffer::clear() { requireWritable(); resetHits(); }
void CollisionQueryBuffer::setCapacity(uint32_t capacity) {
    requireWritable();
    if (capacity>1048576) throw std::invalid_argument("Query capacity exceeds 1048576");
    resetHits(); mHits.reserve(capacity); mCapacity=capacity;
}
void CollisionQueryBuffer::beginQuery() { requireWritable(); resetHits(); mQuerying=true; }
void CollisionQueryBuffer::resetHits() {
    for (auto& hit:mHits) hit.collider->release();
    mHits.clear(); mOverflow=false;
}
void CollisionQueryBuffer::configure(uint32_t layers, uint32_t categories, bool sensors) {
    requireWritable();
    scriptOptions = {}; scriptOptions.layerMask=layers; scriptOptions.categoryMask=categories;
    scriptOptions.includeSensors=sensors;
}
const CollisionQueryHit& CollisionQueryBuffer::getHit(uint32_t index) const {
    if (index>=mHits.size()) throw std::out_of_range("Query hit index");
    return mHits[index];
}
void CollisionQueryBuffer::insert(const CollisionQueryHit& hit) {
    auto at=std::lower_bound(mHits.begin(),mHits.end(),hit,queryHitLess);
    if (mHits.size()==mCapacity) {
        mOverflow=true;
        if (at==mHits.end()) return;
        const auto index=at-mHits.begin();
        mHits.back().collider->release(); mHits.pop_back(); at=mHits.begin()+index;
    }
    hit.collider->addRef(); mHits.insert(at,hit);
}
void queryColliders(const std::vector<Collider*>& input, const CollisionQueryGeometry& query,
                    const CollisionQueryOptions& options, CollisionQueryBuffer& results) {
    validateQuery(query);
    struct Guard {
        CollisionQueryBuffer& buffer;
        Guard(CollisionQueryBuffer& b):buffer(b){buffer.beginQuery();}
        ~Guard(){buffer.endQuery();}
    } guard(results);
    struct Snapshot { std::shared_ptr<Collider> owner; std::vector<Geometry> pieces; };
    std::vector<Snapshot> snapshot;
    std::set<uint64_t> seen;
    for (auto* c:input) {
        if (!c || !c->isEnabled() || !c->isAttached() || !seen.insert(c->getId()).second ||
            !(c->getCategory() & options.categoryMask) || (!options.includeSensors && c->isSensor()) ||
            std::find(options.excludedColliders.begin(),options.excludedColliders.end(),c)!=options.excludedColliders.end() ||
            std::find(options.excludedBodies.begin(),options.excludedBodies.end(),&c->getPhysicsBody())!=options.excludedBodies.end()) continue;
        Snapshot s{retain(c),{}};
        const auto frame=c->transform();
        for (const auto& shape:c->shapes()) appendGeometry(s.pieces,shape,frame);
        snapshot.push_back(std::move(s));
    }
    Geometry region;
    region.center=query.start; region.radius=query.radius;
    if (query.kind==CollisionQueryKind::Capsule) region.points={query.start,query.end};
    if (query.kind==CollisionQueryKind::Box) {
        const auto quad=query.box.getQuad();
        region.points.assign(quad.points,quad.points+4);
    }
    std::optional<CollisionQueryHit> nearestHit;
    try {
        for (const auto& s:snapshot) {
            if (options.predicate && !options.predicate(*s.owner)) continue;
            std::map<CollisionShapeId,CollisionQueryHit> hits;
            for (const auto& piece:s.pieces) {
                CollisionQueryHit hit; hit.collider=s.owner.get(); hit.shapeId=piece.id;
                bool found=false;
                if (query.kind==CollisionQueryKind::Cast) found=queryCast(piece,query,hit);
                else if (query.kind==CollisionQueryKind::Nearest) {
                    const auto n=queryNearest(piece,query.start);
                    found=n.distance<=query.maxDistance;
                    hit.point=n.point; hit.normal=n.normal; hit.distance=n.distance;
                } else if (query.kind==CollisionQueryKind::Point || query.kind==CollisionQueryKind::Circle)
                    found=queryNearest(piece,query.start).distance<=query.radius;
                else { ColliderContact contactInfo; found=contact(piece,region,contactInfo); }
                if (found) {
                    auto [at,inserted]=hits.emplace(piece.id,hit);
                    if (!inserted && hit.distance<at->second.distance) at->second=hit;
                }
            }
            for (const auto& [id,hit]:hits) {
                if (query.kind==CollisionQueryKind::Nearest) {
                    if (!nearestHit || queryHitLess(hit,*nearestHit)) nearestHit=hit;
                } else results.insert(hit);
            }
        }
        if (nearestHit) results.insert(*nearestHit);
    } catch (...) { results.resetHits(); throw; }
}
