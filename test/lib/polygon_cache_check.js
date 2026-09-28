'use strict';

// Compare a repeatedly drawn/edited polygon with fresh geometry after each edit.
// Shared by the native probe and the browser shape-fill regression.
module.exports = function checkPolygonCache(pdg) {
    const ports = [];
    function surface() {
        const port = pdg.gfx.createOffscreenPort(new pdg.Rect(160, 160));
        if (!port) throw Error('Cannot create polygon cache regression surface');
        ports.push(port);
        return port;
    }
    function fresh(polygon) {
        const copy = new pdg.Polygon();
        for (let i = 0; i < polygon.getPointCount(); ++i) copy.insertPoint(i, polygon.getPoint(i));
        return copy;
    }
    let checked = 0;
    try {
        const target = surface(), oracle = surface(), source = surface();
        source.clear(new pdg.Color(0, 0, 1, 1));
        source.drawRect(new pdg.Rect(0, 0, 80, 160), new pdg.Attributes()
            .fillColor(new pdg.Color(1, 0, 0, 1)).lineStyle(pdg.lineStyle_None));
        const texture = new pdg.Image(source, pdg.CopyPixels);
        const polygon = new pdg.Polygon();
        [[20,20],[130,20],[130,60],[60,60],[60,130],[20,130]].forEach(([x,y]) =>
            polygon.addPoint(new pdg.Point(x,y)));
        const edits = [
            () => {}, // warm cache
            () => {}, // reuse it through all fill modes and transforms
            () => polygon.setPoint(1, new pdg.Point(30,120)), // crossing contour
            () => polygon.insertPoint(2, new pdg.Point(140,90)),
            () => polygon.removePoint(3),
            () => polygon.addPoint(new pdg.Point(10,80)),
            () => polygon.move(new pdg.Offset(5,-5)),
            () => polygon.rotateAround(0.3, new pdg.Point(80,80)),
            () => polygon.scaleAround(-0.8, new pdg.Point(80,80)),
            () => polygon.clearPoints(),
            () => [[30,30],[125,30],[125,125],[30,125]].forEach(([x,y]) =>
                polygon.addPoint(new pdg.Point(x,y)))
        ];
        edits.forEach((edit, stage) => {
            edit();
            const copy = fresh(polygon);
            for (let fill = 0; fill < 5; ++fill) {
                const attrs = new pdg.Attributes().lineStyle(pdg.lineStyle_None).fillOpacity(0.7);
                if (fill === 0) attrs.fillColor(new pdg.Color(1,0,0,1));
                if (fill === 1) attrs.fillGradient(new pdg.Point(20,20), new pdg.Color(1,0,0,1),
                    new pdg.Point(130,130), new pdg.Color(0,1,0,1));
                if (fill === 2) attrs.fillRadialGradient(new pdg.Point(80,80),
                    new pdg.Color(1,0,0,1), 80, new pdg.Color(0,1,0,1));
                if (fill >= 3) attrs.texture(texture).fitType(fill === 3 ? pdg.fit_Inside : pdg.fit_Tile);
                if (stage % 2) attrs.rotation(0.2, new pdg.Point(80,80)).scale(-0.9,0.8,new pdg.Point(80,80));
                target.clear(new pdg.Color(0,0,0,1));
                oracle.clear(new pdg.Color(0,0,0,1));
                target.drawPolygon(polygon, attrs);
                oracle.drawPolygon(copy, attrs);
                const actual = new pdg.Image(target, pdg.CopyPixels);
                const expected = new pdg.Image(oracle, pdg.CopyPixels);
                for (let y = 2; y < 160; y += 5) for (let x = 2; x < 160; x += 5) {
                    const a = actual.getPixel(x,y), b = expected.getPixel(x,y);
                    for (const channel of ['red','green','blue','alpha']) {
                        if (Math.abs(a[channel]-b[channel]) > 0.02)
                            throw Error('Stale polygon cache: stage '+stage+', fill '+fill+', pixel '+x+','+y);
                    }
                }
                ++checked;
            }
        });
        return {renderComparisons:checked};
    } finally {
        ports.reverse().forEach(port => pdg.gfx.closeGraphicsPort(port));
    }
};
