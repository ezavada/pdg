require('./SpecHelper');
const mvcPath = process.ios ? '../src/js/mvc-app' : '../../src/js/mvc-app';
const modules = require(mvcPath + '/index');
const mvc = Object.fromEntries(Object.entries(modules).map(([name,value]) => [name, value && value[name] || value]));

mvc.MessageDialogView = modules.MessageDialog.MessageDialogView;
mvc.MessageDialogBorderView = modules.MessageDialog.MessageDialogBorderView;

function controller() {
    const c = Object.create(mvc.Controller.prototype);
    c.views = []; c.children = []; c.active = true; c.drawInactive = true;
    let clip = new pdg.Rect(0,0,800,600);
    c.port = { getClipRect: () => new pdg.Rect(clip), setClipRect: value => { clip = new pdg.Rect(value); } };
    c.getApplication = () => ({ getResourceManager: () => pdg.res, getTimerManager: () => pdg.tm, getEventManager: () => pdg.evt, getLogManager: () => pdg.lm });
    c.getTopController = () => c;
    c.getControlAttributes = () => new mvc.ControlAttributes();
    return c;
}
class ProbeView extends mvc.View {
    drawSelf() { this.drawnArea = this.getViewArea(); }
}

describe('MVC AnimatedAttributes views', function() {
    it('gives every visual control Animated behavior without a physics property', function() {
        for (const name of ['View','Button','Checkbox','RadioButton','PopupMenu',
            'ListBox','EditText','Scrollbar','ScrollingView','MessageView','MessageDialogView','MessageDialogBorderView']) {
            expect(mvc[name].prototype instanceof pdg.Animated).toBe(true);
            expect('physics' in mvc[name].prototype).toBe(false);
            for (const method of ['translation','rotation','scale']) expect(typeof mvc[name].prototype[method]).toBe('function');
        }
        const c = controller(), v = new ProbeView(c, new pdg.Rect(10,20,110,60));
        expect(v instanceof pdg.Animated).toBe(true);
        expect(v instanceof pdg.AnimatedAttributes).toBe(true);
        expect('physics' in v).toBe(false);
        expect(c instanceof pdg.Animated).toBe(false);
        expect(new mvc.ControlAttributes() instanceof pdg.Animated).toBe(false);
        expect(v.getLocation().x).toBe(60); expect(v.getLocation().y).toBe(40);
    });
    it('keeps drawing scale separate from view layout dimensions', function() {
        const v=new ProbeView(controller(),new pdg.Rect(10,20,110,60));
        v.setScale(2);v.scale(3);
        expect(v.getScale().x).toBe(6);expect(v.getWidth()).toBe(100);
        expect(v.getViewArea().width()).toBe(100);
        v.grow(2);
        expect(v.getViewArea().width()).toBe(200);expect(v.getScale().x).toBe(6);
    });
    it('steps view appearance with layout and supplies an Attributes drawing sample', function() {
        const c=controller(), v=new ProbeView(c,new pdg.Rect(10,20,110,60));
        v.fillColor(new pdg.Color(1,0,0));
        v.changeFillColor(new pdg.Color(0,0,1),1);
        v.changeFillOpacity(0,1);
        c.animateViews(.5);
        expect(v.getFillColor().blue).toBeCloseTo(.5,5);
        expect(v.getFillOpacity()).toBeCloseTo(.5,5);
        const drawing=pdg.createDrawing();
        const element=drawing.addRect(new pdg.Rect(-.5,-.5,.5,.5),v);
        const sample=element.getAttributes();
        expect(sample.getTransform()[0]).toBeCloseTo(100,5);
        expect(sample.getTransform()[6]).toBeCloseTo(60,5);
        expect(sample.getFillOpacity()).toBeCloseTo(.5,5);
        c.animateViews(.5);
        expect(v.getFillOpacity()).toBe(0);
        expect(element.getAttributes().getFillOpacity()).toBeCloseTo(.5,5);
    });
    it('keeps an empty Port clip fully clipped and restores a partial clip', function() {
        const c=controller(), v=new ProbeView(c,new pdg.Rect(10,20,110,60));
        c.port.setClipRect(new pdg.Rect());v.draw(c.port,1);
        expect(v.drawnArea).toBeUndefined();
        const partial=new pdg.Rect(20,30,70,50);c.port.setClipRect(partial);v.draw(c.port,2);
        expect(v.drawnArea.left).toBe(10);
        expect(c.port.getClipRect()).toEqual(partial);
    });
    it('moves the layout, drawing and clickable areas together in seconds', function() {
        const c=controller(), v=new ProbeView(c,new pdg.Rect(10,20,110,60));
        v.addClickablePart(new pdg.Rect(0,0,100,40),7);
        v.moveBy(100,40,.5,pdg.linearTween); c.animateViews(.25);
        expect(v.getViewArea().left).toBeCloseTo(60,5);
        expect(v.getViewArea().top).toBeCloseTo(40,5);
        expect(v.getPartClicked(new pdg.Point(65,45))).toBe(7);
        expect(v.pointInViewArea(new pdg.Point(15,25))).toBe(false);
        v.draw(c.port,1); expect(v.drawnArea.left).toBeCloseTo(60,5);
        c.animateViews(.25); expect(v.getViewArea().left).toBeCloseTo(110,5);
        v.setMovement(20,0); c.animateViews(.25);
        expect(v.getViewArea().left).toBeCloseTo(115,5);
        v.setSize(200,80);
        expect(v.getPartClicked(v.localToGlobal(new pdg.Point(180,70)))).toBe(7);
        const rect=v.getViewArea(); rect.left=-900;
        expect(v.getViewArea().left).toBeCloseTo(65,5);
    });
    it('updates button layout and preserves the center during growth', function() {
        const c=controller(), b=new mvc.Button(c,new pdg.Rect(20,30,120,70),9);
        b.grow(2,.5,pdg.linearTween); c.animateViews(.5);
        expect(b.getViewArea().left).toBeCloseTo(-30,5);
        expect(b.getViewArea().width()).toBeCloseTo(200,5);
        expect(b.getLocation().x).toBeCloseTo(70,5);
        expect(b.textBaselineCenterPoint.x).toBeCloseTo(100,5);
        expect(b.getPartClicked(new pdg.Point(150,80))).toBe(9);
    });
    it('keeps scrolling and port resize layout synchronized with Animated', function() {
        const c=controller(), v=new mvc.ScrollingView(c,new pdg.Rect(10,20,110,100));
        v.setAutoAdjust(mvc.ScrollingViewBindType.bind_None);
        v.moveView(15,25);
        expect(v.getLocation().x).toBeCloseTo(75,5);
        expect(v.getLocation().y).toBeCloseTo(85,5);
        v.scrollToTop(); expect(v.getViewArea().top).toBe(20);
        expect(v.getHeight()).toBe(80);
        v.scrollToRight(); expect(v.getViewArea().right).toBe(110);
        expect(v.getWidth()).toBe(100);
        const bound=new ProbeView(c,new pdg.Rect(10,20,110,60),mvc.ViewBinding.grow);
        bound.binding=mvc.ViewBinding.grow;
        bound.portResized(new pdg.Rect(0,0,200,100),new pdg.Rect(0,0,300,200));
        expect(bound.getWidth()).toBe(200); expect(bound.getHeight()).toBe(140);
        expect(bound.getLocation().x).toBe(110); expect(bound.getLocation().y).toBe(90);
    });
    it('steps children once, skips removed views and defers newly added views', function() {
        const c=controller(), child=controller(); c.children.push(child); child.parent=c;
        const first=new ProbeView(c,new pdg.Rect(10,10));
        const removed=new ProbeView(c,new pdg.Rect(10,10));
        const nested=new ProbeView(child,new pdg.Rect(10,10));
        removed.setMovement(100,0); nested.setMovement(100,0);
        child.addView(nested,42); // already registered by View's constructor
        let added;
        first.animate=function(seconds) {
            c.removeView(removed);
            added=new ProbeView(c,new pdg.Rect(10,10)); added.setMovement(100,0);
        };
        c.animateViews(.25);
        expect(removed.getLocation().x).toBe(5);
        expect(added.getLocation().x).toBe(5);
        expect(nested.getLocation().x).toBeCloseTo(30,5);
        c.active=false; c.drawInactive=false; c.animateViews(1);
        expect(nested.getLocation().x).toBeCloseTo(30,5);
        expect(()=>c.animateViews(-1)).toThrow();
    });
    it('passes the original View subclass to animation helpers', function() {
        const c=controller(), v=new ProbeView(c,new pdg.Rect(10,10));
        let target, seconds;
        const helper=new pdg.IAnimationHelper(function(what,dt) {
            target=what; seconds=dt; return true;
        });
        v.addAnimationHelper(helper); c.animateViews(.125); v.removeAnimationHelper(helper);
        expect(target).toBe(v); expect(target instanceof ProbeView).toBe(true);
        expect(seconds).toBe(.125);
    });
    it('moves and resizes a ListBox scrollbar along with its owner', function() {
        const c=controller(), list=new mvc.ListBox(c,new pdg.Rect(30,40,230,140),2,
            new pdg.Color(0,0,0,1),new pdg.Color(1,1,1,1));
        list.createScrollbar();
        try {
            list.moveBy(20,10,.5,pdg.linearTween); c.animateViews(.5);
            const area=list.getViewArea(), bar=list.scrollbar.getViewArea();
            expect(bar.right).toBeCloseTo(area.right,5);
            expect(bar.left).toBeCloseTo(area.right-16,5);
            expect(bar.top).toBeCloseTo(area.top,5);
            list.resizeTo(240,120,.25,pdg.linearTween); c.animateViews(.25);
            expect(list.scrollbar.getViewArea().height()).toBeCloseTo(120,5);
            expect(list.scrollbar.getPartClicked(new pdg.Point(
                list.scrollbar.getViewArea().left+2, list.scrollbar.getViewArea().top+2)))
                .not.toBe(mvc.ClickablePartsIDs.CLICKED_PART_NONE);
        } finally { list.destroy(); }
    });
    it('measures animated edit text for caret placement and selection geometry', function() {
        const c=controller(), edit=new mvc.EditText(c,new pdg.Rect(100,200,400,240));
        let selection;
        c.port.getTextWidth=(text,size)=>Array.from(text).reduce((width,ch)=>width+(ch==='W'?.9:.2)*size,0);
        c.port.drawRect=rect=>{selection=rect;};
        try {
            edit.setText('WWi');edit.textSize(10);
            expect(edit.getTextWidth('WWi')).toBeCloseTo(20,5);
            edit.changeTextSize(20,.5,pdg.linearTween);edit.animate(.5);
            expect(edit.getTextWidth('WWi')).toBeCloseTo(40,5);
            edit.setRotation(.4);edit.setFlipX(true);
            const click=edit.localToGlobal(new pdg.Point(24,15));
            expect(edit.getCaretPositionFromPoint(edit.globalToLocal(click))).toBe(1);
            edit.highlightStartCharIndex=1;edit.highlightEndCharIndex=2;
            edit.drawSelection();
            expect(selection.left).toBeCloseTo(121,5);
            expect(selection.right).toBeCloseTo(139,5);
            expect(selection.bottom).toBe(236);
        } finally { edit.destroy(); }
    });
    it('uses PortDraw once per frame and does not step another port', function() {
        const c=controller(); let calls=0,seconds;
        c.animateViews=dt=>{ calls++; seconds=dt; }; c.drawViews=()=>{};
        c.onPortDraw({port:c.port,frameNum:1});
        expect(calls).toBe(1); expect(seconds).toBe(0);
        c.onPortDraw({port:c.port,frameNum:1}); expect(calls).toBe(1);
        c._lastAnimationTime=pdg.tm.getMilliseconds()-250;
        c.onPortDraw({port:c.port,frameNum:2}); expect(calls).toBe(2);
        expect(seconds>=.25 && seconds<.35).toBe(true);
        c.onPortDraw({port:{},frameNum:3}); expect(calls).toBe(2);
        const child=controller(); child.parent=c;
        child.animateViews=()=>{ throw new Error('child stepped itself'); };
        expect(()=>child.onPortDraw({port:child.port,frameNum:1})).not.toThrow();
    });
});


describe('MVC appearance composition and transformed input', function() {
    it('inherits unset theme channels and respects explicit default values', function() {
        const c=controller(), v=new ProbeView(c,new pdg.Rect(100,40));
        const theme=new pdg.Attributes().fillColor('red').lineColor('blue').lineThickness(7).roundedCorners(12).textSize(24);
        let merged=v.getDrawingAttributes(theme);
        expect(merged.getFillColor().red).toBe(1); expect(merged.getLineThickness()).toBe(7);
        expect(merged.getTextSize()).toBe(24);
        v.lineThickness(1).roundedCorners(0).textSize(12).fillColor('green');
        merged=v.getDrawingAttributes(theme);
        expect(merged.getLineThickness()).toBe(1); expect(merged.getRoundedCornerRadius()).toBe(0);
        expect(merged.getTextSize()).toBe(12); expect(merged.getFillColor().green).toBeCloseTo(128/255,5);
        expect(theme.getLineThickness()).toBe(7);
        const label=v.getDrawingAttributes(new pdg.Attributes().fillColor('white'),true);
        expect(label.getFillColor().red).toBe(1); expect(label.getFillColor().blue).toBe(1);
        v.changeFillColor('blue',1,pdg.linearTween);v.animate(.5);
        expect(v.getDrawingAttributes(theme).getFillColor().blue).toBeCloseTo(.5,5);
    });
    it('composes state fallback and custom draw samples without mutating the theme', function() {
        const v=new ProbeView(controller(),new pdg.Rect(100,40));v.fillOpacity(.3);
        let sample;
        const theme=new mvc.ControlAttributes().stateDrawRoutine(mvc.ControlState.Normal,(p,r,s)=>{sample=s.drawing;});
        theme.draw({},new pdg.Rect(100,40),mvc.ControlState.Hovered,v);
        expect(sample.getFillOpacity()).toBeCloseTo(.3,5);
        expect(theme.state(mvc.ControlState.Normal).hasDrawing).toBe(false);
    });
    it('uses inverse rotation and reflection for regions and rejects a collapsed view', function() {
        const v=new ProbeView(controller(),new pdg.Rect(40,50,160,90));
        v.addClickablePart(new pdg.Rect(0,0,25,40),7);v.setRotation(Math.PI/3);v.setFlipX(true);
        const world=v.localToGlobal(new pdg.Point(10,20)), back=v.globalToLocal(world);
        expect(back.x).toBeCloseTo(10,4);expect(back.y).toBeCloseTo(20,4);
        expect(v.getPartClicked(world)).toBe(7);expect(v.pointInViewVisibleArea(world)).toBe(true);
        expect(v.pointInViewVisibleArea(new pdg.Point(42,52))).toBe(false);
        v.setScale(0);expect(v.pointInViewVisibleArea(world)).toBe(false);
    });
    it('keeps a visual child clipped, transformed, laid out and drawn only once', function() {
        const c=controller(), parent=new ProbeView(c,new pdg.Rect(20,20,180,100));
        const child=new ProbeView(c,new pdg.Rect(30,30,80,60));child.setParentView(parent);
        expect(()=>parent.setParentView(child)).toThrow();
        parent.moveBy(10,15);expect(child.getViewArea().left).toBe(40);expect(child.getViewArea().top).toBe(45);
        let draws=0;child.drawSelf=()=>{draws++;};c.drawViews(c.port,1);expect(draws).toBe(1);
        parent.setRotation(.4);child.setFlipY(true);
        const p=child.localToGlobal(new pdg.Point(10,10));expect(child.globalToLocal(p).x).toBeCloseTo(10,4);
        expect(child.pointInViewVisibleArea(p)).toBe(true);
        parent.hide();expect(child.isVisible()).toBe(false);
        child.destroy();expect(parent.childViews.length).toBe(0);
    });
});

if (pdg.hasGraphics) describe('MVC rendering and scrolling clips', function() {
    let port,c,views;
    beforeEach(function() { port=pdg.gfx.createOffscreenPort(new pdg.Rect(160,160));c=controller();c.port=port;views=[]; });
    afterEach(function() { views.forEach(v=>v.destroy());pdg.gfx.closeGraphicsPort(port); });
    function alpha(x,y) { return new pdg.Image(port,pdg.CopyPixels).getPixel(x,y).alpha; }
    class Overflow extends mvc.ScrollingView {
        drawSelf(p) { p.drawRect(new pdg.Rect(-200,-200,400,400),new pdg.Attributes().fillColor('red')); }
    }
    function make(frame) { const v=new Overflow(c,frame);views.push(v);return v; }
    it('clips a partly offscreen viewport and restores the caller clip, including exceptions', function() {
        const v=make(new pdg.Rect(-10,10,80,60)), clip=new pdg.Rect(5,0,120,120);
        port.setClipRect(clip);v.draw(port,1);
        const pixels=[alpha(6,15),alpha(2,15),alpha(85,15),alpha(6,65)];
        expect(pixels).toEqual([1,0,0,0]);
        expect(port.getClipRect()).toEqual(clip);
        v.drawSelf=()=>{throw Error('draw failed');};expect(()=>v.draw(port,2)).toThrow();
        expect(port.getClipRect()).toEqual(clip);
    });
    it('clips to the actual rotated viewport rather than its bounding box', function() {
        const v=make(new pdg.Rect(40,60,120,100));v.setRotation(Math.PI/4);
        v.draw(port,1);
        expect(alpha(80,80)).toBe(1);expect(alpha(40,42)).toBe(0);expect(alpha(55,55)).toBe(1);
        expect(v.pointInViewVisibleArea(new pdg.Point(40,42))).toBe(false);
        expect(v.pointInViewVisibleArea(new pdg.Point(55,55))).toBe(true);
        const source=v._renderPort;port.clear();v.draw(port,2);expect(v._renderPort).toBe(source);
        v.setViewFrame(new pdg.Rect(50,60,110,100));port.clear();v.draw(port,3);
        expect(v._renderPort===source).toBe(false);
    });
    it('reflects rendered asymmetric content with its hit region and clears old pixels', function() {
        const v=new ProbeView(c,new pdg.Rect(40,60,120,100));views.push(v);
        v.drawSelf=p=>p.drawRect(v.localToGlobalRect(new pdg.Rect(0,0,20,40)),new pdg.Attributes().fillColor('blue'));
        v.setFlipX(true);v.addClickablePart(new pdg.Rect(0,0,20,40),4);v.draw(port,1);
        expect(alpha(110,80)).toBe(1);expect(alpha(50,80)).toBe(0);
        expect(v.getPartClicked(new pdg.Point(110,80))).toBe(4);
        v.drawSelf=()=>{};port.clear();v.draw(port,2);expect(alpha(110,80)).toBe(0);
    });
    it('supports passing the View itself as unit-coordinate drawing attributes', function() {
        const v=new ProbeView(c,new pdg.Rect(40,60,120,100));views.push(v);
        v.fillColor('red').setRotation(Math.PI/4);
        v.drawSelf=p=>p.drawRect(new pdg.Rect(-.5,-.5,.5,.5),v);
        const matrix=v.getTransform();v.draw(port,1);
        expect(alpha(55,55)).toBe(1);expect(alpha(40,42)).toBe(0);
        expect(v.getTransform()).toEqual(matrix);
    });
    it('restores state after failure in a transformed child draw', function() {
        const v=make(new pdg.Rect(40,60,120,100));v.setRotation(.4);
        v.drawSelf=()=>{throw Error('draw failed');};const clip=port.getClipRect();
        expect(()=>v.draw(port,1)).toThrow();expect(v.getPort()).toBe(port);expect(port.getClipRect()).toEqual(clip);
        v.drawSelf=()=>{};expect(()=>v.draw(port,2)).not.toThrow();
    });
});
