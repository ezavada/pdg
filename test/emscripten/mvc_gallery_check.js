// Real pointer input through the MVC gallery's composed view transforms.
module.exports = async function({evaluate,pageCall,delay,url}) {
    const assert=require('assert'), fs=require('fs'), path=require('path');
    const target=new URL(url);
    target.search='?interactive=1&kind=demo&suites=mvc&page=1';
    await pageCall('Page.navigate',{url:target.href});
    const deadline=Date.now()+30000;
    while (!(await evaluate('!!window.pdgMvcGallery'))) {
        if (Date.now()>deadline) throw Error('MVC gallery did not initialize');
        await delay(100);
    }
    await delay(1400);
    async function point(expression) {
        const p=await evaluate(expression);
        const canvas=await evaluate('(function(){var r=document.getElementById("pdg-canvas").getBoundingClientRect(),a=pdg.gfx.getMainPort().getDrawingArea();return {x:r.x,y:r.y,sx:r.width/a.width(),sy:r.height/a.height()};})()');
        return {x:canvas.x+p.x*canvas.sx,y:canvas.y+p.y*canvas.sy};
    }
    async function click(expression) {
        const p=await point(expression);
        await pageCall('Input.dispatchMouseEvent',{type:'mouseMoved',...p});
        await pageCall('Input.dispatchMouseEvent',{type:'mousePressed',button:'left',clickCount:1,...p});
        await pageCall('Input.dispatchMouseEvent',{type:'mouseReleased',button:'left',clickCount:1,...p});
        await delay(150);
    }
    async function dragOut(expression) {
        const start=await point(expression), end=await point('({x:465,y:200})');
        await pageCall('Input.dispatchMouseEvent',{type:'mousePressed',button:'left',clickCount:1,...start});
        await pageCall('Input.dispatchMouseEvent',{type:'mouseMoved',buttons:1,...end});
        return async () => {
            await pageCall('Input.dispatchMouseEvent',{type:'mouseReleased',button:'left',clickCount:1,...end});
            await delay(150);
        };
    }
    for (const button of ['pdgMvcGallery.defaultButton','pdgMvcGallery.views.find(pair=>pair.first.getID()===103).first']) {
        const status=await evaluate('pdgMvcGallery.status');
        const release=await dragOut(button+'.localToGlobal(new pdg.Point(30,18))');
        assert.strictEqual(await evaluate(button+'.isPressed()'),false,'Button stayed pressed outside');
        await release();
        assert.strictEqual(await evaluate('pdgMvcGallery.status'),status,'Canceled press fired a click');
    }
    // Verify motion continues well after the old one-shot animation ended.
    const motionBefore=await evaluate('pdgMvcGallery.animatedButton.getRotation()');
    await delay(650);
    assert(Math.abs((await evaluate('pdgMvcGallery.animatedButton.getRotation()'))-motionBefore)>.01,
        'Animated button stopped moving');
    const disabledBefore=await evaluate('pdgMvcGallery.disabledRadio.getSelectedIndex()');
    await click('({x:175,y:370})');
    assert.strictEqual(await evaluate('pdgMvcGallery.disabledRadio.getSelectedIndex()'),disabledBefore,
        'Disabled radio accepted a pointer click');
    await click('({x:60,y:255})');
    await click('pdgMvcGallery.animatedButton.localToGlobal(new pdg.Point(25,18))');
    assert((await evaluate('pdgMvcGallery.status')).includes('106'),'Rotated button did not receive click');
    await click('pdgMvcGallery.reflectedButton.localToGlobal(new pdg.Point(25,18))');
    assert((await evaluate('pdgMvcGallery.status')).includes('107'),'Reflected button did not receive click');
    assert(!await evaluate('pdgVisualSession.paused'),'Control click paused the gallery');
    const before=await evaluate('pdgMvcGallery.list.scrollbar.getCurrentPosition()');
    await click('pdgMvcGallery.list.scrollbar.localToGlobal(new pdg.Point(8,pdgMvcGallery.list.scrollbar.getHeight()-8))');
    assert((await evaluate('pdgMvcGallery.list.scrollbar.getCurrentPosition()'))>before,'Composite scrollbar arrow did not scroll');
    await evaluate('pdgMvcGallery.list.scrollbar.setCurrentPosition(0)');
    const wheelPoint=await point('pdgMvcGallery.list.scrollbar.localToGlobal(new pdg.Point(8,60))');
    await pageCall('Input.dispatchMouseEvent',{type:'mouseMoved',...wheelPoint});
    await pageCall('Input.dispatchMouseEvent',{type:'mouseWheel',deltaX:0,deltaY:120,...wheelPoint});
    await delay(250);
    assert((await evaluate('pdgMvcGallery.list.scrollbar.getCurrentPosition()'))>0,'Vertical scrollbar ignored the wheel');
    // The owning list also forwards wheel input over its rows to its scrollbar.
    const listPoint=await point('pdgMvcGallery.list.localToGlobal(new pdg.Point(30,60))');
    await pageCall('Input.dispatchMouseEvent',{type:'mouseMoved',...listPoint});
    await pageCall('Input.dispatchMouseEvent',{type:'mouseWheel',deltaX:0,deltaY:-120,...listPoint});
    await delay(250);
    assert.strictEqual(await evaluate('pdgMvcGallery.list.scrollbar.getCurrentPosition()'),0,'List row wheel input did not scroll upward');
    await click('pdgMvcGallery.list.localToGlobal(new pdg.Point(20,12))');
    assert((await evaluate('pdgMvcGallery.list.selectedIndex'))>=0,'Resized list did not select a row');
    for (const x of [100,600]) {
        await click('({x:'+x+',y:465})');
        assert.strictEqual(await evaluate('pdgMvcGallery.children.length'),1,'Dialog did not open');
        const dialogFile=path.resolve(__dirname,'../../artifacts/test-results/web/mvc-dialog-'+x+'.png');
        fs.mkdirSync(path.dirname(dialogFile),{recursive:true});
        fs.writeFileSync(dialogFile,Buffer.from((await pageCall('Page.captureScreenshot',{format:'png'})).data,'base64'));
        const release=await dragOut('(function(){var r=pdgMvcGallery.children[0].getDialogRect();return {x:r.right-60,y:r.bottom-29};})()');
        await release();
        assert.strictEqual(await evaluate('pdgMvcGallery.children.length'),1,'Dragging out of Close closed the dialog');
        await click('(function(){var r=pdgMvcGallery.children[0].getDialogRect();return {x:r.right-60,y:r.bottom-29};})()');
        assert.strictEqual(await evaluate('pdgMvcGallery.children.length'),0,'Dialog did not close');
    }
    const result=await evaluate('document.getElementById("pdg-ui-result-json").textContent');
    assert(!result || JSON.parse(result).status!=='failed',result);
    const file=path.resolve(__dirname,'../../artifacts/test-results/web/mvc-gallery.png');
    fs.mkdirSync(path.dirname(file),{recursive:true});
    fs.writeFileSync(file,Buffer.from((await pageCall('Page.captureScreenshot',{format:'png'})).data,'base64'));
    return {status:'passed',checks:['button and dialog drag-out cancellation','repeating animation','disabled radio','wheel over scrollbar and list','rotated button','reflected button','composite scrollbar','resized list selection','default and themed dialogs','control input priority'],screenshot:file};
};
