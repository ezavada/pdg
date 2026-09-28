// Skeleton-derived initial geometry. Kept independent of Spriter and solvers so
// authored reference poses and headless builds use the same generation rules.
namespace {
AnimationTransform physicsLocal(const AnimationTransform& parent, AnimationTransform world) {
    if (!parent.isValid() || parent.scaleX == 0 || parent.scaleY == 0)
        throw std::invalid_argument("Physical reference frame is singular");
    const double x = world.x - parent.x, y = world.y - parent.y;
    const double c = std::cos(parent.rotation), s = std::sin(parent.rotation);
    world.x = (c*x+s*y)/parent.scaleX; world.y = (-s*x+c*y)/parent.scaleY;
    world.rotation = (world.rotation-parent.rotation)*(parent.scaleX*parent.scaleY < 0 ? -1 : 1);
    world.scaleX /= parent.scaleX; world.scaleY /= parent.scaleY;
    return world;
}
double physicalScale(const AnimationTransform& world) {
    const double scale = std::abs(world.scaleX);
    if (!world.isValid() || scale <= 0 || world.scaleY == 0)
        throw std::invalid_argument("Generated physical bone frames must be nonsingular");
    return scale;
}
void validateGeneratedRoot(const AnimationTransform& root) {
    const auto scale=physicalScale(root);
    if (std::abs(scale-std::abs(root.scaleY))>1e-8*scale)
        throw std::invalid_argument("Generated physical rigs require uniform Sprite root scale");
}
AnimationTransform generatedBodyFrame(const AnimationTransform& bone, const AnimationPhysicsBody& body) {
    auto frame=AnimationTransform::compose(bone,{body.offsetX,body.offsetY});
    frame.rotation=bone.rotation+std::atan2(bone.scaleY*std::sin(body.offsetRotation),bone.scaleX*std::cos(body.offsetRotation));
    frame.scaleX=frame.scaleY=1;
    return frame;
}
}
AnimationBoneId selectAnimationPhysicsRoot(const AnimationRig& rig, AnimationBoneId requested) {
    if (!rig.getBoneCount()) throw std::invalid_argument("Physical rig needs skeletal bones");
    if (requested != animation_NoBone) { rig.getBone(requested); return requested; }
    const auto named = rig.findBone("root");
    if (named != animation_NoBone) return named;
    std::vector<size_t> descendants(rig.getBoneCount(), 0);
    for (AnimationBoneId id = 0; id < rig.getBoneCount(); ++id)
        for (auto parent = rig.getBone(id).parent; parent != animation_NoBone; parent = rig.getBone(parent).parent)
            ++descendants[parent];
    return std::max_element(descendants.begin(), descendants.end()) - descendants.begin();
}
AnimationPhysicsDefinition generateAnimationPhysicsDefinition(const AnimationPose& current,
        const AnimationTransform& root, double totalMass, AnimationBoneId requested,
        double unitsPerMeter, std::vector<std::string>& diagnostics) {
    if (!std::isfinite(totalMass) || totalMass <= 0 || !std::isfinite(unitsPerMeter) || unitsPerMeter <= 0)
        throw std::invalid_argument("Total mass and unitsPerMeter must be finite positive numbers");
    const auto rig = current.getRig();
    const auto selected = selectAnimationPhysicsRoot(*rig, requested);
    validateGeneratedRoot(root);
    AnimationPose reference(rig);
    AnimationPhysicsDefinition result; result.generated = true; result.rootMode = animationRoot_Follow;
    std::vector<std::vector<AnimationBoneId>> children(rig->getBoneCount());
    std::vector<uint32_t> indices(rig->getBoneCount(), UINT32_MAX);
    for (AnimationBoneId id = 0; id < rig->getBoneCount(); ++id) {
        const auto parent = rig->getBone(id).parent;
        if (parent != animation_NoBone) children[parent].push_back(id);
    }
    std::vector<double> lengths;
    long double totalLength = 0;
    for (AnimationBoneId id = 0; id < rig->getBoneCount(); ++id) {
        const auto& bone = rig->getBone(id);
        const auto ref = reference.getWorldTransform(id, root);
        const double scale = physicalScale(ref);
        physicalScale(current.getWorldTransform(id, root));
        Point a, b;
        if (!children[id].empty()) {
            std::vector<Point> points;
            if (children[id].size() == 1) points.push_back(Point());
            for (auto child : children[id]) {
                const auto connection = physicsLocal(ref, reference.getWorldTransform(child, root));
                points.emplace_back(connection.x, connection.y);
            }
            double distance = -1;
            for (size_t i = 0; i < points.size(); ++i) for (size_t j = i+1; j < points.size(); ++j) {
                const double next = std::hypot((double(points[i].x)-points[j].x)*ref.scaleX, (double(points[i].y)-points[j].y)*ref.scaleY);
                if (next > distance) { distance = next; a = points[i]; b = points[j]; }
            }
        } else {
            bool haveBounds = false;
            double left = 0, right = 0, top = 0, bottom = 0;
            for (AnimationBindingId binding = 0; binding < rig->getBindingCount(); ++binding) {
                const auto& art = rig->getBinding(binding);
                if (art.bone != id || art.kind != animationBinding_Image || !art.hasImageBounds) continue;
                for (double x : {-art.pivotX*art.imageWidth, (1-art.pivotX)*art.imageWidth})
                    for (double y : {-art.pivotY*art.imageHeight, (1-art.pivotY)*art.imageHeight}) {
                        const auto point = AnimationTransform::compose(art.reference, {x,y});
                        if (!haveBounds) { left=right=point.x; top=bottom=point.y; haveBounds=true; }
                        else { left=std::min(left,point.x);right=std::max(right,point.x);top=std::min(top,point.y);bottom=std::max(bottom,point.y); }
                    }
            }
            // Major axis of the union in bone-local coordinates. Unlike a
            // diagonal this does not inflate a rectangular limb's length.
            if (haveBounds) {
                if ((right-left)*std::abs(ref.scaleX) >= (bottom-top)*std::abs(ref.scaleY)) { a=Point(left,(top+bottom)/2);b=Point(right,(top+bottom)/2); }
                else { a=Point((left+right)/2,top);b=Point((left+right)/2,bottom); }
                diagnostics.push_back(bone.name + ": inferred capsule axis from reference artwork bounds");
            } else diagnostics.push_back(bone.name + ": reference artwork bounds unavailable; no inferred segment");
        }
        double length = std::hypot(double(b.x)-a.x,double(b.y)-a.y);
        if (length == 0 && id == selected) {
            length = unitsPerMeter*.001/scale; a=Point();b=Point(length,0);
            diagnostics.push_back(bone.name + ": used designated-root 1 mm fallback");
        }
        if (length == 0) { diagnostics.push_back(bone.name + ": skipped zero-length or unresolved segment"); continue; }
        AnimationPhysicsBody body;
        body.bone=id;
        body.length=std::hypot((double(b.x)-a.x)*ref.scaleX,(double(b.y)-a.y)*ref.scaleY);
        body.radius=.1*body.length;
        body.offsetX=(double(a.x)+b.x)/2;body.offsetY=(double(a.y)+b.y)/2;
        body.offsetRotation=std::atan2(double(b.y)-a.y,double(b.x)-a.x);
        if (!std::isfinite(body.length) || !std::isfinite(body.radius) || body.radius <= 0)
            throw std::invalid_argument("Inferred physical geometry is not representable");
        indices[id]=uint32_t(result.bodies.size());
        if (id == selected) result.rootBody=indices[id];
        result.bodies.push_back(body);lengths.push_back(body.length);totalLength+=body.length;
    }
    std::vector<AnimationTransform> frames;
    for (size_t i = 0; i < result.bodies.size(); ++i) {
        auto& body = result.bodies[i];
        body.mass=scaledPhysicalValue(totalMass,lengths[i],double(totalLength));
        if (!std::isfinite(body.mass) || body.mass <= 0) throw std::invalid_argument("Generated mass is not representable");
        const auto world=generatedBodyFrame(current.getWorldTransform(body.bone,root),body);
        frames.push_back({world.x,world.y,world.rotation}); // physical anchors are unscaled body coordinates
    }
    for (size_t i = 0; i < result.bodies.size(); ++i) {
        const auto id=result.bodies[i].bone;
        auto parent=rig->getBone(id).parent;
        while (parent != animation_NoBone && indices[parent] == UINT32_MAX) parent=rig->getBone(parent).parent;
        if (parent == animation_NoBone) continue; // separate skeleton trees remain separate components
        AnimationPhysicsJoint joint;joint.parent=indices[parent];joint.child=uint32_t(i);
        const auto connection=current.getWorldTransform(id,root);
        const auto a=physicsLocal(frames[joint.parent],connection), b=physicsLocal(frames[i],connection);
        joint.parentX=a.x;joint.parentY=a.y;joint.childX=b.x;joint.childY=b.y;
        joint.maxForce=std::numeric_limits<double>::infinity();
        result.joints.push_back(joint);
    }
    return result;
}
