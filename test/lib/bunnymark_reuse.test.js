'use strict';
// Execute the real benchmark with a deterministic window and image. Verify that
// resource reuse preserves motion, resizing and both completion paths.
const assert = require('assert');
const fs = require('fs');
const path = require('path');
const vm = require('vm');
const source = fs.readFileSync(path.join(__dirname, '../perf_tests/bunnymark/bunnymark.js'), 'utf8');

function benchmark(quickMode) {
    const events = {}, draws = [], attributes = [];
    const bounds = {width:() => width, height:() => height};
    let width = 800, height = 600, finishSampling = false, quit = false;
    const port = {getDrawingArea:() => bounds, drawRect(){}, drawText(){},
        drawImage(image, position, attrs) {
            assert(!attrs.deleted, 'draw arguments must remain alive throughout sampling');
            draws.push({x:position.x, y:position.y, position, attrs});
        }};
    class Attributes {
        constructor(){this.deleted=false;attributes.push(this);}
        fillColor(){return this;} textSize(){return this;} textStyle(){return this;}
        delete(){assert(!this.deleted, 'release native ownership once');this.deleted=true;}
    }
    let imageWidth = 26, imageHeight = 37, widthReads = 0, heightReads = 0;
    const pdg = {
        Attributes, Point:class {constructor(x,y){this.x=x;this.y=y;}},
        Rect:class {}, Color:class {},
        Image:class {getWidth(){++widthReads;return imageWidth;} getHeight(){++heightReads;return imageHeight;}},
        gfx:{createWindowPort:() => port,closeGraphicsPort(){}},
        eventType_PortDraw:'draw',eventType_KeyPress:'key',key_Escape:27,
        on:(event,callback) => {events[event]=callback;}, run(){},quit(){quit=true;}
    };
    const quick = {
        requireRelease(){},uncap(){},options:() => ({quick:quickMode,factor:1}),
        baseline:() => ({bunnymarkScore:2}),dispose:object => {if(object)object.delete();},write(){},
        Sampler:class {constructor(){this.frames=[];} tick(){return finishSampling;} result(){return {score:2};}}
    };
    const randoms = [0.25,0.3,0.1,0.8, 0.9,0.8,0.6,0.2];let randomIndex=0;
    const math=Object.create(Math);math.random=() => randoms[randomIndex++ % randoms.length];
    const context=vm.createContext({console:{log(){}},Date,Math:math,
        process:{argv:['pdg','bunnymark.js','--manual','--batch','2'],exit(){throw Error('unexpected exit');}},
        require:name => name==='pdg'?pdg:name==='../quick'?quick:{writeFileSync(){}},global:{}});
    vm.runInContext('(function(){\n'+source+'\n})();',context);
    return {draws,attributes,port,
        frame(){events.draw({port});},resize(w,h){width=w;height=h;},
        resizeImage(w,h){imageWidth=w;imageHeight=h;},
        imageReads:() => [widthReads,heightReads],
        finish(){if(quickMode){finishSampling=true;events.draw({port});}else events.key({unicode:27});},
        hasQuit:() => quit};
}

for(const quickMode of [false,true]) {
    const run=benchmark(quickMode);
    const drawFrame=() => {
        const reads=run.imageReads();
        run.frame();
        assert.deepStrictEqual(run.imageReads(),reads.map(count=>count+1),
            'read each native image dimension once per frame, regardless of bunny count');
    };
    drawFrame();
    assert.deepStrictEqual(run.draws.map(({x,y})=>[x,y]),[[196,178.5],[721,472.5]]);
    const args=run.draws[0];
    run.resize(80,90);
    drawFrame();
    assert.deepStrictEqual(run.draws.slice(2).map(({x,y})=>[x,y]),[[54,53],[54,53]],
        'resizing the window must update both bounce limits');
    run.resizeImage(32,40);
    run.resize(40,45);
    drawFrame();
    assert.deepStrictEqual(run.draws.slice(4).map(({x,y})=>[x,y]),[[8,5],[8,5]],
        'frame-level dimensions must reflect image and window changes');
    for(const draw of run.draws) {
        assert.strictEqual(draw.position,args.position,'draws reuse the scratch Point');
        assert.strictEqual(draw.attrs,args.attrs,'draws reuse native Attributes');
    }
    assert(!args.attrs.deleted);
    run.finish();assert(run.hasQuit());assert(args.attrs.deleted);
    const count=run.draws.length;run.frame();assert.strictEqual(run.draws.length,count);
    assert(run.attributes.every(attrs=>attrs.deleted),'all native Attributes are released');
}
console.log('PASS: BunnyMark resource reuse preserves motion, resizing and completion');
