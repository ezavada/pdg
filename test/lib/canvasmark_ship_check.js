'use strict';

// Independently decoded palette/tRNS samples from the original CanvasMark PNGs.
// Cover the first, middle and last 64px frames of both tall ship sprite sheets.
module.exports = function checkCanvasMarkShips(pdg, capture, assetBase) {
    const references = require('./canvasmark_ship_pixels');
    const base = assetBase || (typeof window !== 'undefined' && window.document ? '/test/' : 'test/');
    const port = pdg.gfx.createOffscreenPort(new pdg.Rect(192,128));
    const background = new pdg.Color(0.125,0.25,0.5,1);
    const channels = ['red','green','blue','alpha'];
    const images = {};
    let decodedPixels = 0, renderedPixels = 0;
    try {
        port.clear(background);
        references.forEach((ref,index) => {
            let image = images[ref.asset];
            if (!image) {
                image = images[ref.asset] = new pdg.Image(base+'perf_tests/canvasmark2013/images/'+ref.asset);
                image.retainData(); // The test inspects CPU pixels after rendering too.
                if (image.getWidth()!==64 || image.getHeight()!==5760) throw Error('Missing ship sprite sheet');
            }
            ref.samples.forEach(([x,y,...rgba]) => {
                const pixel = image.getPixel(x, ref.frame*64+y);
                channels.forEach((channel,i) => {
                    if (Math.abs(pixel[channel]-rgba[i]/255)>1/255)
                        throw Error(ref.asset+' frame '+ref.frame+': corrupt decoded '+channel+' at '+x+','+y);
                });
                ++decodedPixels;
            });
            const crop = image.getSubsection(new pdg.Rect(0,ref.frame*64,64,(ref.frame+1)*64));
            const x = index%3*64, y = Math.floor(index/3)*64;
            port.drawImage(crop,new pdg.Rect(x,y,x+64,y+64),new pdg.Attributes().fitType(pdg.fit_Fill));
        });
        const result = new pdg.Image(port,pdg.CopyPixels);
        references.forEach((ref,index) => ref.samples.forEach(([x,y,r,g,b,a]) => {
            const pixel = result.getPixel(index%3*64+x,Math.floor(index/3)*64+y);
            [r,g,b].forEach((value,i) => {
                const expected = value/255*a/255 + background[channels[i]]*(1-a/255);
                if (Math.abs(pixel[channels[i]]-expected)>0.025)
                    throw Error(ref.asset+' frame '+ref.frame+': corrupt rendered '+channels[i]+' at '+x+','+y);
            });
            ++renderedPixels;
        }));
        if (capture) capture(result,192,128);
        return {decodedPixels,renderedPixels};
    } finally {
        pdg.gfx.closeGraphicsPort(port);
    }
};
