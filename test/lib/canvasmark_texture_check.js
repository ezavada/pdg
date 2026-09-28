'use strict';

// Pixel regression for the same adapter used by CanvasMark's rotating cubes.
module.exports = function checkCanvasMarkTexture(pdg) {
    const install = require('../perf_tests/canvasmark2013/k3d-pdg');
    const ports = [];
    function surface(size) {
        const port = pdg.gfx.createOffscreenPort(new pdg.Rect(size, size));
        if (!port) throw Error('Cannot create texture regression surface');
        ports.push(port); return port;
    }
    let checked = 0, fallbacks = 0;
    try {
        const source = surface(64), target = surface(320);
        const colors = [[1,0,0], [0,1,0], [0,0,1], [1,1,0]];
        [[0,0,32,32], [32,0,64,32], [32,32,64,64], [0,32,32,64]].forEach((r,i) => {
            source.drawRect(new pdg.Rect(...r), new pdg.Attributes()
                .fillColor(new pdg.Color(...colors[i],1)).lineStyle(pdg.lineStyle_None));
        });
        const texture = new pdg.Image(source, pdg.CopyPixels);
        function Renderer() {}
        Renderer.prototype.renderPolygon = function() { ++fallbacks; };
        install(pdg, {SolidRenderer:Renderer});
        const renderer = new Renderer();
        const faces = [
            [[40,40],[260,40],[260,260],[40,260]],
            [[40,30],[270,90],[210,260],[25,180]],
            [[155,20],[290,145],[160,285],[20,160]],
            [[260,40],[40,40],[40,260],[260,260]]
        ];
        for (const coords of faces) for (const opacity of [1,0.5]) {
            target.clear(new pdg.Color(0,0,0,1));
            const points = coords.map(([x,y]) => new pdg.Point(x,y));
            const ctx = {port:target, state:{globalAlpha:opacity,translateX:3,translateY:5},
                transformPoint:(x,y) => new pdg.Point(x+3,y+5)};
            renderer.renderPolygon(ctx, {screencoords:points, textures:[{_getPDGImage:()=>texture}]},
                {vertices:[0,1,2,3],texture:0}, null);
            const result = new pdg.Image(target, pdg.CopyPixels);
            for (let corner=0;corner<4;++corner) {
                const p=points[corner], previous=points[(corner+3)%4], next=points[(corner+1)%4];
                const x=Math.round(p.x*.8+previous.x*.1+next.x*.1+3);
                const y=Math.round(p.y*.8+previous.y*.1+next.y*.1+5);
                const actual=result.getPixel(x,y);
                ['red','green','blue'].forEach((channel,i) => {
                    if (Math.abs(actual[channel]-colors[corner][i]*opacity)>0.06)
                        throw Error('CanvasMark texture corner '+corner+' / opacity '+opacity+
                            ': '+channel+' at '+x+','+y+' was '+actual[channel]);
                });
                ++checked;
            }
        }
        renderer.renderPolygon({}, {}, {texture:null}, 'red');
        if (fallbacks!==1) throw Error('Untextured face did not retain the original renderer');
        return {cornerPixels:checked, untexturedFallbacks:fallbacks};
    } finally {
        ports.reverse().forEach(port => pdg.gfx.closeGraphicsPort(port));
    }
};
