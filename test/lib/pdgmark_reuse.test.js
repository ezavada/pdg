'use strict';
// Exercise the actual benchmark objects, recording geometry at the draw boundary.
// Check visible motion as well as allocation counts and native ownership.
const assert = require('assert');
const fs = require('fs');
const path = require('path');
const vm = require('vm');
const source = fs.readFileSync(path.join(__dirname, '../perf_tests/pdgmark/pdgmark.js'), 'utf8');
const identity = [1,0,0,0,1,0,0,0,1];
function multiply(a,b) {
    return identity.map((_,i) => {
        const row=i%3, col=Math.floor(i/3);
        return a[row]*b[col*3]+a[row+3]*b[col*3+1]+a[row+6]*b[col*3+2];
    });
}
function near(actual,expected) {
    assert(Math.abs(actual-expected)<1e-7, `${actual} != ${expected}`);
}
function transformed(p,m) { return {x:m[0]*p.x+m[3]*p.y+m[6],y:m[1]*p.x+m[4]*p.y+m[7]}; }
function benchmark(quickMode=true) {
    const allocated=[], draws=[], counts={};
    function count(kind) {counts[kind]=(counts[kind]||0)+1;}
    class Point { constructor(x=0,y=0) {count('Point');this.x=x;this.y=y;} }
    class Rect {
        constructor(a,b,c,d) {count('Rect');Object.assign(this, c===undefined?
            {left:0,top:0,right:a,bottom:b}:{left:a,top:b,right:c,bottom:d});}
        width(){return this.right-this.left;} height(){return this.bottom-this.top;}
    }
    class Color {constructor(...values){count('Color');this.values=values;}}
    class Native {
        constructor(){count(this.constructor.name);allocated.push(this);this.deleted=false;}
        delete(){assert(!this.deleted,'native object deleted twice');this.deleted=true;}
    }
    class Attributes extends Native {
        constructor(){super();this.matrix=identity.slice();this.style={};}
        setTransform(m){this.matrix=Array.from(m);return this;}
        rotation(angle,center={x:0,y:0}) {
            const c=Math.cos(angle),s=Math.sin(angle),x=center.x,y=center.y;
            this.matrix=multiply(this.matrix,[c,s,0,-s,c,0,x-c*x+s*y,y-s*x-c*y,1]);return this;
        }
        scale(x,y){this.matrix=multiply(this.matrix,[x,0,0,0,y,0,0,0,1]);return this;}
        fillGradient(start,color1,end,color2) {
            this.style.gradient={start:{...start},end:{...end},color1,color2};return this;
        }
    }
    for(const name of ['fillColor','fillOpacity','blendMode','lineColor','lineThickness','textSize','textStyle'])
        Attributes.prototype[name]=function(value){this.style[name]=value;return this;};
    class AnimatedAttributes extends Attributes {
        setCenterOffset(center){this.center={...center};return this;}
        setLocation(p){this.location={...p};return this;}
        setScale(x,y){this.sx=x;this.sy=y;return this;}
        setRotation(angle){
            const c=Math.cos(angle),s=Math.sin(angle),p=this.center||{x:0,y:0},l=this.location||{x:0,y:0};
            const sx=this.sx??1,sy=this.sy??1;
            this.matrix=[c*sx,s*sx,0,-s*sy,c*sy,0,l.x+p.x-c*sx*p.x+s*sy*p.y,l.y+p.y-s*sx*p.x-c*sy*p.y,1];
            return this;
        }
    }
    class Polygon extends Native {
        constructor(){super();this.points=[];this.edits=0;}
        addPoint(p){this.points.push({...p});this.edits++;}
        setPoint(i,p){this.points[i]={...p};this.edits++;}
    }
    class Spline extends Polygon {}
    class Image extends Native {getWidth(){count('widthReads');return 26;} getHeight(){count('heightReads');return 37;}}
    const bounds=new Rect(1000,800), events={};
    const port={getDrawingArea:()=>bounds};
    for(const method of ['drawPolygon','drawSpline','drawImage','drawLine','drawArc','drawEllipse','drawRect','drawText'])
        port[method]=(...args)=>{
            const attrs=args[args.length-1];assert(!attrs.deleted);
            for(const arg of args) if(arg instanceof Native) assert(!arg.deleted);
            draws.push({method,args,matrix:attrs.matrix.slice(),style:structuredClone(attrs.style),
                points:args[0].points && args[0].points.map(p=>transformed(p,attrs.matrix)),
                values:args.map(arg=>arg instanceof Point?{x:arg.x,y:arg.y}:arg)});
        };
    const pdg={Point,Offset:Point,Rect,Color,Attributes,AnimatedAttributes,Polygon,Spline,Image,
        gfx:{createWindowPort:()=>port,closeGraphicsPort(){}},
        eventType_PortDraw:'draw',eventType_KeyPress:'key',key_Escape:27,
        textStyle_Plain:0,textStyle_Bold:1,textStyle_Italic:2,
        on:(e,cb)=>{events[e]=cb;},quit(){context.quit=true;}};
    const quick={requireRelease(){},uncap(){},options:()=>({quick:quickMode}),
        baseline:()=>({tests:Object.fromEntries(['bitmap','drawing','alpha','polygon','text'].map(n=>[n,{objectsAt60FPS:3}]))}),
        load:()=>3,dispose:o=>{if(o&&o.delete)o.delete();},write(){},
        Sampler:class {constructor(){this.frames=[];}reset(){}tick(){return false;}}};
    let random=0.4;
    const math=Object.create(Math);math.random=()=>random;
    const context=vm.createContext({console:{log(){}},Date,Math:math,setTimeout(){},global:{},
        process:{argv:[],exit(code){context.exitCode=code;}},
        require:name=>name==='pdg'?pdg:name==='../quick'?quick:{writeFileSync(){}}});
    vm.runInContext(source.slice(0,source.indexOf('// Setup and run')),context);
    return {context,pdg,port,bounds,draws,allocated,counts,random:value=>{random=value;}};
}

for(const gradient of [false,true]) for(let sides=3;sides<=7;sides++) {
    const run=benchmark();
    // Pick the side count, then switch the random stream at the gradient flag.
    let index=0;
    run.context.Math.random=()=>++index===3?(sides-3+0.1)/5:index===7?(gradient?0.8:0.2):0.4;
    const obj=new run.context.PolygonObject(run.bounds);
    const before={...run.counts};
    let polygon,attrs;
    for(let frame=0;frame<120;frame++) {
        obj.update();obj.draw(run.port);
        const draw=run.draws.at(-1);
        if(frame===0) {polygon=draw.args[0];attrs=draw.args[1];}
        assert.strictEqual(draw.args[0],polygon,'retain the polygon across draws');
        assert.strictEqual(draw.args[1],attrs,'retain styled attributes');
        assert.strictEqual(polygon.edits,sides,'rotation must not invalidate tessellation');
        draw.points.forEach((p,i)=>{
            const angle=obj.rotation+i/sides*Math.PI*2;
            near(p.x,obj.centerX+Math.cos(angle)*obj.radius);
            near(p.y,obj.centerY+Math.sin(angle)*obj.radius);
        });
        if(gradient) {
            near(draw.style.gradient.start.x,obj.centerX-obj.radius);
            near(draw.style.gradient.end.x,obj.centerX+obj.radius);
            near(draw.style.gradient.start.y,obj.centerY);
            near(draw.style.gradient.end.y,obj.centerY);
        }
    }
    assert.deepStrictEqual(run.counts,before,'polygon drawing must not allocate arguments');
    run.context.testObjects=[obj];run.context.cleanupTestObjects();
    assert(polygon.deleted&&attrs.deleted);
    run.context.cleanupTestObjects(); // Safe after the stage has already ended.
}

for(const quickMode of [false,true]) for(const completion of ['next','finish','escape']) {
    const run=benchmark(quickMode),ctx=run.context;
    ctx.port=run.port;ctx.testImage=new run.pdg.Image();
    const obj=new ctx.PolygonObject(run.bounds);
    obj.draw(run.port);
    const [polygon,attrs]=run.draws.at(-1).args;
    ctx.testObjects=[obj];ctx.currentTestIndex=completion==='next'?4:5;
    if(completion==='escape')ctx.onKeyPress({unicode:27});else ctx.startNextTest();
    assert(polygon.deleted&&attrs.deleted,`${completion} must release retained native objects`);
    if(completion!=='next') {
        const count=run.draws.length;ctx.onDraw({port:run.port});
        assert.strictEqual(run.draws.length,count,'draw after completion must do nothing');
    }
}
console.log('PASS: PDGMark polygons retain geometry, rotation, gradients and ownership');

for(let type=0;type<4;type++) {
    const run=benchmark();let index=0;
    run.context.Math.random=()=>++index===1?(type+0.1)/4:0.4;
    const obj=new run.context.DrawingObject(run.bounds),before={...run.counts};
    let attrs,spline;
    for(let frame=0;frame<120;frame++) {
        obj.update();obj.draw(run.port);
        const draw=run.draws.at(-1);
        if(frame===0){attrs=draw.args.at(-1);spline=draw.args[0];}
        assert.strictEqual(draw.args.at(-1),attrs);
        near(draw.style.lineThickness,obj.thickness);
        assert.deepStrictEqual(draw.style.lineColor.values,obj.color.values);
        if(type===0) {
            for(let i=0;i<2;i++) {
                const sign=i===0?1:-1,p=draw.values[i];
                near(p.x,obj.x+sign*Math.cos(obj.angle)*obj.size);
                near(p.y,obj.y+sign*Math.sin(obj.angle)*obj.size);
            }
        } else if(type===2) {
            assert.strictEqual(draw.args[0],spline);
            assert.strictEqual(spline.edits,4+2*(frame+1));
            const expected=[{x:obj.x,y:obj.y},
                {x:obj.x+obj.size*Math.cos(obj.angle),y:obj.y+obj.size*Math.sin(obj.angle)},
                {x:obj.x+obj.size*Math.cos(obj.angle+1),y:obj.y+obj.size*Math.sin(obj.angle+1)},
                {x:obj.x,y:obj.y+obj.size}];
            draw.points.forEach((p,i)=>{near(p.x,expected[i].x);near(p.y,expected[i].y);});
        } else {
            near(draw.values[0].x,obj.x);near(draw.values[0].y,obj.y);
            near(draw.values[1],type===1?obj.size:obj.size/2);
            near(draw.values[2],type===1?obj.size:obj.size/2);
            if(type===1){near(draw.values[3],obj.angle);near(draw.values[4],obj.angle+Math.PI*1.5);}
        }
    }
    assert.deepStrictEqual(run.counts,before,'line/arc/spline/ellipse draws must reuse arguments');
    run.context.testObjects=[obj];run.context.cleanupTestObjects();
    assert(run.allocated.every(o=>o.deleted),'release drawing Attributes and Spline');
}
console.log('PASS: PDGMark drawing reuse preserves all four primitive animations');

for(const random of [0,0.2,0.5,0.9]) {
    const run=benchmark();run.random(random);
    run.context.testImage=new run.pdg.Image();
    run.context.addBitmapObjects(4,run.bounds);
    assert.strictEqual(run.counts.widthReads,1);assert.strictEqual(run.counts.heightReads,1);
    const before={...run.counts},identities=[];
    for(let frame=0;frame<120;frame++) for(const [i,obj] of run.context.testObjects.entries()) {
        obj.update();obj.draw(run.port);
        const draw=run.draws.at(-1);
        if(frame===0) identities[i]=draw.args;
        draw.args.forEach((arg,j)=>assert.strictEqual(arg,identities[i][j]));
        // Original code rotates about the unscaled center AFTER origin scaling.
        const cx=obj.x+13,cy=obj.y+18.5,c=Math.cos(obj.rotation),s=Math.sin(obj.rotation);
        for(const [dx,dy] of [[0,0],[26,0],[26,37],[0,37]]) {
            const p={x:obj.x+dx,y:obj.y+dy},actual=transformed(p,draw.matrix);
            const x=p.x*obj.scale-cx,y=p.y*obj.scale-cy;
            near(actual.x,cx+c*x-s*y);near(actual.y,cy+s*x+c*y);
        }
    }
    assert.deepStrictEqual(run.counts,before,'bitmap draws must not allocate or read image dimensions');
    run.context.cleanupTestObjects();
    assert(run.allocated.filter(o=>o!==run.context.testImage).every(o=>o.deleted));
}
console.log('PASS: PDGMark bitmap reuse preserves scale/rotation and hoists image getters');

for(let type=0;type<2;type++) for(let blend=0;blend<6;blend++) {
    const run=benchmark();let index=0;
    run.context.Math.random=()=>++index===1?(type+0.1)/2:index===10?(blend+0.1)/6:0.4;
    const obj=new run.context.AlphaObject(run.bounds),before={...run.counts};
    let geometry,attrs;
    for(let frame=0;frame<120;frame++) {
        obj.update();obj.draw(run.port);
        const draw=run.draws.at(-1);
        if(frame===0){geometry=draw.args[0];attrs=draw.args.at(-1);}
        assert.strictEqual(draw.args[0],geometry);assert.strictEqual(draw.args.at(-1),attrs);
        near(draw.style.fillOpacity,obj.opacity);assert.strictEqual(draw.style.blendMode,blend);
        assert.deepStrictEqual(draw.style.fillColor.values,obj.color.values);
        if(type===0) {
            near(geometry.left,obj.x);near(geometry.top,obj.y);
            near(geometry.right,obj.x+obj.width);near(geometry.bottom,obj.y+obj.height);
        } else {
            near(geometry.x,obj.x+obj.width/2);near(geometry.y,obj.y+obj.height/2);
            near(draw.args[1],obj.width/2);near(draw.args[2],obj.height/2);
        }
        const cx=obj.x+obj.width/2,cy=obj.y+obj.height/2;
        for(const [dx,dy] of [[0,0],[obj.width,0],[obj.width,obj.height],[0,obj.height]]) {
            const p=transformed({x:obj.x+dx,y:obj.y+dy},draw.matrix);
            const x=dx-obj.width/2,y=dy-obj.height/2,c=Math.cos(obj.rotation),s=Math.sin(obj.rotation);
            near(p.x,cx+c*x-s*y);near(p.y,cy+s*x+c*y);
        }
    }
    assert.deepStrictEqual(run.counts,before,'alpha draws must reuse geometry and style');
    run.context.testObjects=[obj];run.context.cleanupTestObjects();
    assert(run.allocated.every(o=>o.deleted));
}
console.log('PASS: PDGMark alpha reuse preserves both shapes, rotation and all blend modes');

for(let style=0;style<3;style++) {
    const run=benchmark();let index=0;
    run.context.Math.random=()=>++index===10?(style+0.1)/3:0.4;
    const obj=new run.context.TextObject(run.bounds),before={...run.counts};
    let position,attrs;
    for(let frame=0;frame<120;frame++) {
        obj.update();obj.draw(run.port);
        const draw=run.draws.at(-1);
        if(frame===0){position=draw.args[1];attrs=draw.args[2];}
        assert.strictEqual(draw.args[0],obj.text);assert.strictEqual(draw.args[1],position);
        assert.strictEqual(draw.args[2],attrs);near(position.x,obj.x);near(position.y,obj.y);
        assert.strictEqual(draw.style.textStyle,style);near(draw.style.textSize,obj.size);
        assert.deepStrictEqual(draw.style.fillColor.values,obj.color.values);
        const origin=transformed(position,draw.matrix),p=transformed({x:obj.x+15,y:obj.y-7},draw.matrix);
        near(origin.x,obj.x);near(origin.y,obj.y);
        near(p.x,obj.x+15*Math.cos(obj.rotation)+7*Math.sin(obj.rotation));
        near(p.y,obj.y+15*Math.sin(obj.rotation)-7*Math.cos(obj.rotation));
    }
    assert.deepStrictEqual(run.counts,before,'text draws must reuse position and style');
    run.context.testObjects=[obj];run.context.cleanupTestObjects();
    assert(run.allocated.every(o=>o.deleted));
}
console.log('PASS: PDGMark text reuse preserves content, styling, rotation and ownership');

for(const quickMode of [false,true]) {
    const run=benchmark(quickMode),ctx=run.context;
    ctx.calculateAutoAddDelay=()=>Infinity;
    ctx.setup();
    const background=ctx.backgroundAttrs,overlay=ctx.overlayAttrs,positions=ctx.overlayPositions;
    for(let stage=0;stage<5;stage++) {
        const before={...run.counts};
        for(let frame=0;frame<3;frame++) {
            const first=run.draws.length,capacity=ctx.objectsAt60FPS;
            run.bounds.right=frame===0?1000:720;run.bounds.bottom=frame===0?800:400;
            ctx.onDraw({port:run.port});
            const bg=run.draws[first],hud=run.draws.slice(-8);
            assert.strictEqual(bg.args[1],background);
            near(bg.args[0].width(),run.bounds.width());near(bg.args[0].height(),run.bounds.height());
            hud.forEach((draw,i)=>{
                assert.strictEqual(draw.method,'drawText');assert.strictEqual(draw.args[2],overlay);
                assert.strictEqual(draw.args[1],positions[i]);near(draw.values[1].x,10);
                near(draw.values[1].y,[20,50,70,90,110,130,160,180][i]);
            });
            assert.strictEqual(hud[1].args[0],`Test ${stage+1}/5: ${ctx.tests[stage].title}`);
            assert.strictEqual(hud[2].args[0],'Objects: '+ctx.testObjects.length);
            assert.strictEqual(hud[5].args[0],'Objects @ 60 FPS: '+capacity);
            assert.strictEqual(hud[6].args[0],quickMode?'Fixed load (quick)':'Adding objects...');
        }
        assert.deepStrictEqual(run.counts,before,'whole frames reuse object and HUD drawing arguments');
        ctx.currentTestIndex++;ctx.startNextTest();
    }
    assert(ctx.quit);assert(run.allocated.every(o=>o.deleted),'completion releases objects, HUD and image');
    const count=run.draws.length;ctx.onDraw({port:run.port});assert.strictEqual(run.draws.length,count);
}
for(const quickMode of [false,true]) {
    const run=benchmark(quickMode),ctx=run.context;ctx.setup();
    ctx.onKeyPress({unicode:27});
    assert(run.allocated.every(o=>o.deleted),'Escape releases all retained resources');
    const before={...run.counts};
    ctx.currentTestIndex=2;ctx.startNextTest(); // Simulate a queued stabilization timer after Escape.
    ctx.onKeyPress({unicode:27});ctx.onDraw({port:run.port});
    assert.deepStrictEqual(run.counts,before,'late timers and events must not restart a finished benchmark');
}
console.log('PASS: PDGMark HUD reuse preserves layout, resizing, stages and complete cleanup');
