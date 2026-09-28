// Pixel oracles for Port clipping, per-operation overflow and live Drawing replay.
module.exports = function(pdg, port, gl, canvas) {
    var saved=port.getClipRect(), area=port.getDrawingArea();
    var width=320, height=320, checks=0;
    var black=new pdg.Color(0,0,0), white=new pdg.Color(1,1,1);
    var rect=new pdg.Rect(80,80,220,220), center=new pdg.Point(150,150);
    var texture=new pdg.Image('data/yinyang.png');
    var strip=new pdg.ImageStrip('data/yinyang.png'); strip.setNumFrames(2);
    var polygon=new pdg.Polygon();
    [[80,80],[220,80],[190,150],[220,220],[80,220]].forEach(function(p){polygon.addPoint(new pdg.Point(p[0],p[1]));});
    var spline=new pdg.Spline();
    spline.addSegment(new pdg.Point(80,80),new pdg.Point(220,80),new pdg.Point(80,220),new pdg.Point(220,220));
    var drawing=pdg.createDrawing(); drawing.addRect(rect,new pdg.Attributes().fillColor(white));
    function attrs() {return new pdg.Attributes().fillColor(white).lineColor(white).lineThickness(3).lineStyle(pdg.lineStyle_Solid);}
    function clear() {
        port.resetClipRect(); port.drawRect(area,new pdg.Attributes().fillColor(black));
        gl.clear(gl.DEPTH_BUFFER_BIT);
    }
    function capture() {
        var pixels=new Uint8Array(width*height*4);
        gl.readPixels(0,canvas.height-height,width,height,gl.RGBA,gl.UNSIGNED_BYTE,pixels);
        return pixels;
    }
    function color(p,x,y) {var i=((height-1-y)*width+x)*4; return [p[i],p[i+1],p[i+2]];}
    function brightness(c) {return c[0]+c[1]+c[2];}
    function compare(name, before, after, bounds, needPixels) {
        var bad=0, visible=0;
        for(var y=1;y<height-1;y++) for(var x=1;x<width-1;x++) {
            var inside=bounds && x+.5>=bounds.left && x+.5<bounds.right && y+.5>=bounds.top && y+.5<bounds.bottom;
            var expected=inside?color(before,x,y):[0,0,0], actual=color(after,x,y);
            if(inside && brightness(expected)>30) visible++;
            if(Math.max.apply(Math,expected.map(function(c,i){return Math.abs(c-actual[i]);}))>3) bad++;
        }
        checks++;
        if(bad || (needPixels && !visible)) throw new Error(name+': '+bad+' incorrect pixels, '+visible+' inside pixels');
    }
    var operations=[
        ['line',function(a){port.drawLine(new pdg.Point(80,90),new pdg.Point(220,210),a);}],
        ['spline',function(a){port.drawSpline(spline,a);}],
        ['arc',function(a){port.drawArc(center,70,70,0,Math.PI*2,a);}],
        ['rect',function(a){port.drawRect(rect,a);}],
        ['rounded rect',function(a){port.drawRect(rect,a.roundedCorners(20));}],
        ['quad',function(a){port.drawQuad(new pdg.Quad(rect),a);}],
        ['polygon',function(a){port.drawPolygon(polygon,a);}],
        ['ellipse',function(a){port.drawEllipse(center,70,60,a);}],
        ['image',function(a){port.drawImage(texture,rect,a.fillColor(new pdg.Color(0,0,0,0)).lineStyle(pdg.lineStyle_None));}],
        ['strip',function(a){port.drawImage(strip,rect,a.frame(1).fillColor(new pdg.Color(0,0,0,0)).lineStyle(pdg.lineStyle_None));}],
        ['drawing',function(a){port.drawDrawing(drawing,new pdg.Point(0,0),a);}],
        ['text point',function(a){port.drawText('Clipping boundary',new pdg.Point(80,150),a.textSize(24));}],
        ['transformed text',function(a){port.drawText('Clipping boundary',new pdg.Point(80,150),a.textSize(24).rotation(.12,center));}],
        ['text rect',function(a){port.drawText('Clipping boundary',rect,a.textSize(24));}],
        ['sphere',function(a){port.drawSphere(center,65,a);}]
    ];
    try {
        operations.forEach(function(op) {
            clear();op[1](attrs());var baseline=capture();
            // Single clip replaces its predecessor. Empty and disjoint clips stay empty.
            [new pdg.Rect(100,100,210,210),new pdg.Rect(),new pdg.Rect(-40,-40,-10,-10),new pdg.Rect(110.25,100.75,205.75,209.25)].forEach(function(clip,i){
                clear();port.setClipRect(clip);op[1](attrs().clipOverflow(false));
                compare(op[0]+' Port '+i,baseline,capture(),clip,i===0);
            });
            clear();port.setClipRect(new pdg.Rect());port.setClipRect(new pdg.Rect(100,100,210,210));op[1](attrs());
            compare(op[0]+' replacement',baseline,capture(),new pdg.Rect(100,100,210,210),true);
            clear();port.setClipRect(new pdg.Rect(100,100,210,210));op[1](attrs().clipOverflow(true));
            compare(op[0]+' overflow respects Port',baseline,capture(),new pdg.Rect(100,100,210,210),true);
        });
        var narrow=new pdg.Rect(110,80,170,220), narrowPoly=new pdg.Polygon();
        [[110,80],[170,80],[170,220],[110,220]].forEach(function(p){narrowPoly.addPoint(new pdg.Point(p[0],p[1]));});
        var overflow=[
            ['rect',function(a){port.drawRect(narrow,a);}],
            ['rounded rect',function(a){port.drawRect(narrow,a.roundedCorners(12));}],
            ['polygon',function(a){port.drawPolygon(narrowPoly,a);}],
            ['ellipse',function(a){port.drawEllipse(new pdg.Point(140,150),30,70,a);}],
            ['image',function(a){port.drawImage(texture,narrow,a);}],
            ['strip',function(a){port.drawImage(strip,narrow,a.frame(1));}]
        ];
        overflow.forEach(function(op){
            [pdg.fit_Overflow,pdg.fit_Height].forEach(function(fit){
                function a(clip){return new pdg.Attributes().texture(texture).fitType(fit).clipOverflow(clip).lineStyle(pdg.lineStyle_None);}
                clear();op[1](a(false));var baseline=capture();
                clear();op[1](a(true));compare(op[0]+' overflow '+fit,baseline,capture(),narrow,true);
                var explicit=new pdg.Rect(130,110,200,240);
                clear();port.setClipRect(explicit);op[1](a(true));
                compare(op[0]+' intersection '+fit,baseline,capture(),narrow.intersection(explicit),true);
                var restored=port.getClipRect();
                if(restored.left!==explicit.left || restored.right!==explicit.right) throw new Error('clip leaked from '+op[0]);
            });
        });
        // Rotated and reflected overflow uses transformed bounds for primitives.
        overflow.slice(0,4).forEach(function(op){
            [-1,1].forEach(function(sign){
                function a(clip){return new pdg.Attributes().texture(texture).fitType(pdg.fit_Overflow)
                    .clipOverflow(clip).rotation(.4,center).scale(sign,1,center).lineStyle(pdg.lineStyle_None);}
                var matrix=a(true).getTransform(), corners=[[110,80],[170,80],[170,220],[110,220]];
                var points=corners.map(function(p){return [matrix[0]*p[0]+matrix[3]*p[1]+matrix[6],matrix[1]*p[0]+matrix[4]*p[1]+matrix[7]];});
                var box=new pdg.Rect(Math.min.apply(Math,points.map(function(p){return p[0];})),Math.min.apply(Math,points.map(function(p){return p[1];})),
                    Math.max.apply(Math,points.map(function(p){return p[0];})),Math.max.apply(Math,points.map(function(p){return p[1];})));
                clear();op[1](a(false));var before=capture();
                clear();op[1](a(true));compare(op[0]+' transformed overflow '+sign,before,capture(),box,true);
            });
        });
        // Original line coordinates are outside the Port; its transformed pixels are visible.
        clear();port.drawLine(new pdg.Point(-100,120),new pdg.Point(-60,160),attrs().translation(new pdg.Offset(220,0)));
        var line=capture();
        if(brightness(color(line,140,140))<100) throw new Error('transformed line was culled using local coordinates');
        checks++;
        // Live retained replay changes without setAttributes, and does not tick the source.
        var live=new pdg.AnimatedAttributes().fillColor(white), retained=pdg.createDrawing();
        var element=retained.addRect(new pdg.Rect(70,70,110,110),new pdg.Attributes());
        element.setLiveAttributes(live);live.moveTo(80,0,1,pdg.linearTween);live.animate(.5);
        clear();port.drawDrawing(retained,new pdg.Point(0,0),new pdg.Attributes());
        var pixels=capture();
        if(brightness(color(pixels,125,90))<700 || brightness(color(pixels,80,90))>0 || live.getLocation().x!==40) throw new Error('live replay did not follow the external animation sample');
        checks++;
        element.clearLiveAttributes();live.animate(.5);
        clear();port.drawDrawing(retained,new pdg.Point(0,0),new pdg.Attributes());
        compare('frozen live replay',pixels,capture(),area,true);
    } finally {port.setClipRect(saved);}
    return checks;
};
