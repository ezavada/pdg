'use strict';

// K3D assigns (0,0), (1,0), (1,1), (0,1) to a quad's four face vertices.
// A textured Polygon instead derives UVs from its axis-aligned bounds, which
// loses that correspondence when a projected cube face rotates or tilts.
module.exports = function install(pdg, K3D) {
    const original = K3D.SolidRenderer.prototype.renderPolygon;
    K3D.SolidRenderer.prototype.renderPolygon = function(ctx, obj, face, fillColor) {
        if (face.texture !== null && face.texture !== undefined && ctx.port) {
            const texture = obj.textures[face.texture];
            const image = texture && typeof texture._getPDGImage === 'function'
                ? texture._getPDGImage() : texture;
            if (image) {
                const points = face.vertices.map(index => {
                    const point = obj.screencoords[index];
                    return ctx.transformPoint ? ctx.transformPoint(point.x, point.y)
                        : new pdg.Point(point.x + (ctx.state ? ctx.state.translateX : 0),
                            point.y + (ctx.state ? ctx.state.translateY : 0));
                });
                const attrs = new pdg.Attributes().fillOpacity(ctx.state ? ctx.state.globalAlpha : 1);
                if (points.length === 4) {
                    ctx.port.drawImage(image, new pdg.Quad(points[0], points[1], points[2], points[3]),
                        attrs.fitType(pdg.fit_Fill));
                } else {
                    // Retain the existing general-polygon behavior for non-cube faces.
                    const polygon = new pdg.Polygon();
                    points.forEach(point => polygon.addPoint(point));
                    ctx.port.drawPolygon(polygon, attrs.texture(image));
                    if (typeof polygon.delete === 'function') polygon.delete();
                }
                if (typeof attrs.delete === 'function') attrs.delete();
                return;
            }
        }
        return original.call(this, ctx, obj, face, fillColor);
    };
};
