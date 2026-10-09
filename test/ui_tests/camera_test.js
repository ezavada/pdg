// Run: test/ui camera --page luma-fade (or --page whip-left, --web camera).
(function() {
    'use strict';
    var session = pdg.visualTestSession;
    var capturing = typeof window !== 'undefined' && new URLSearchParams(window.location.search).has('capture');
    var port = pdg.gfx.createWindowPort(new pdg.Rect(960, 640), 'PDG Camera Transitions');
    if (!port) throw Error('Could not create the camera test window');
    var layers = [], cameras = [], movers = [];
    // A full-range cloud mask avoids frozen silhouettes and flat-color plateaus.
    var lumaMask = new pdg.Image('./data/camera-luma-mask.png');
    var duration = 2.4, whipDuration = .325, hold = 1.2, active = 0, transitioning = false, finished = false, handoffs = 0;
    var matchApproachSeconds = 1.2, matchSettleSeconds = .8, matchHoldSeconds = 4, settlingUntil = 0;
    var matchCases = [
        {mode:pdg.matchSource, label:'matchSource'},
        {mode:pdg.matchSourceAndSize, label:'matchSourceAndSize'},
        {mode:pdg.matchSource, label:'matchSource', cameraMotion:true},
        {mode:pdg.matchSourceAndSize, label:'matchSourceAndSize', cameraMotion:true},
        {mode:pdg.matchTarget, label:'matchTarget'},
        {mode:pdg.matchTargetAndSize, label:'matchTargetAndSize'}
    ];
    var matchCaseIndex = 0, matchLeg = 1;
    var now = session ? session.now : function() { return pdg.tm.getMilliseconds(); };
    var styles = [
        ['Crossfade',pdg.camera_Crossfade],
        ['Wipe Left',pdg.camera_WipeLeft],
        ['Wipe Right',pdg.camera_WipeRight],
        ['Wipe Up',pdg.camera_WipeUp],
        ['Wipe Down',pdg.camera_WipeDown],
        ['Luma Fade',pdg.camera_LumaFade],
        ['Whip Left',pdg.camera_WhipLeft],
        ['Whip Right',pdg.camera_WhipRight],
        ['Whip Up',pdg.camera_WhipUp],
        ['Whip Down',pdg.camera_WhipDown],
        ['Cut',null],
        ['Match Cut','match'],
        ['Match Cut Return','match-return'],
        ['Match Fade','match-fade'],
        ['Match Fade Return','match-fade-return']
    ];
    var styleIndex = session ? session.page : 0;
    var started = now();
    var automated = !session && process.argv.indexOf('--wait') < 0;
    var automatedStyles = [0,2,6,5,10,11,12,13,14], automatedStyleIndex = 0;
    var matchFadeSeconds = .6, matchingFade = false;
    if (automated) matchHoldSeconds = .2;
    function fill(color) {
        return new pdg.Attributes().fillColor(color).lineStyle(pdg.lineStyle_None);
    }
    function layer(camera) {
        var result = pdg.createSpriteLayer(port);
        result.setCamera(camera); layers.push(result); return result;
    }
    function sprite(target, drawing, x, y) {
        var result = target.createSprite();
        result.createPart('art').setDrawing(drawing); result.setLocation(x, y); return result;
    }
    function scene(index) {
        var camera = new pdg.Camera().setViewport(port.getDrawingArea()).setLocation(480, 320);
        cameras.push(camera);
        var background = layer(camera), foreground = layer(camera), drawing = pdg.createDrawing();
        drawing.addRect(new pdg.Rect(-2000, -2000, 4000, 4000), fill(index ? '#15375e' : '#8b3f46'));
        drawing.addRect(new pdg.Rect(-2000, 420, 4000, 4000), fill(index ? '#10253e' : '#542b36'));
        drawing.addEllipse(new pdg.Point(720, 190), 80, 80, fill(index ? '#a9e8ff' : '#ffc477'));
        if (index) {
            for (var i = 0; i < 28; ++i)
                drawing.addEllipse(new pdg.Point(40 + (i * 137) % 880, 110 + (i * 61) % 230), 2, 2, fill('#d2efff'));
        } else {
            for (var j = 0; j < 12; ++j)
                drawing.addRect(new pdg.Rect(j * 85, 340 - (j % 3) * 30, j * 85 + 60, 445), fill('#6c303c'));
        }
        sprite(background, drawing, 0, 0);
        var art = pdg.createDrawing();
        art.addEllipse(new pdg.Point(0, 0), 105, 105, fill(index ? '#27769c' : '#bc6370'));
        art.addRect(new pdg.Rect(-65, -65, 65, 65), fill(index ? '#60d9e8' : '#ffd19b'));
        art.addEllipse(new pdg.Point(0, 0), 38, 38, fill(index ? '#d6fbff' : '#fff0dc'));
        var subject=sprite(foreground, art, 360, 360);subject.setSize(210,210);
        movers.push(subject);
        if (index) camera.hide();
    }
    scene(0); scene(1);
    if (capturing && new URLSearchParams(window.location.search).get('capture') === 'reverse') {
        active=1;cameras[0].hide();cameras[1].show();
    }
    port.setCameraDrawingEnabled(false); // HUD remains above both complete camera images.
    if (session) session.onPause.push(function(paused) {
        cameras.forEach(function(camera) { if (paused) camera.pauseSchedule(); else camera.resumeSchedule(); });
    });
    function later(callback, seconds) {
        if (session) session.setTimeout(callback, seconds * 1000);
        else setTimeout(callback, seconds * 1000);
    }
    function boundNextShot(seconds) {
        // Retained match framing can drift over successive handoffs. Reframe
        // during the hold only when another full oscillation would cross an edge.
        cameras[1-active].cancelSchedule();cameras[active].cancelSchedule();
        var subject=movers[active],camera=cameras[active],area=port.getDrawingArea();
        var bounds=subject.getLayer().layerToPortQuad(new pdg.Quad(subject.getRotatedBounds())).getBounds();
        var center=bounds.centerPoint(),zoom=camera.getZoom();
        var margin=Math.min(area.width()/2,bounds.width()/2+90*zoom+48);
        var x=Math.max(area.left+margin,Math.min(area.right-margin,center.x));
        if (Math.abs(x-center.x)>.01) {
            var focus=camera.getLocation();
            camera.moveTo(focus.x+(center.x-x)/zoom,focus.y,seconds,pdg.easeInOutQuad);
        }
    }
    function transition() {
        if (finished) return;
        transitioning = true;
        var style=styles[styleIndex][1];
        if (styleIndex>=11) {
            // Interactive pages show both shots; automation needs one handoff.
            var legs=automated ? 1 : 2;
            matchCaseIndex = Math.floor(handoffs / legs) % matchCases.length;
            matchLeg = handoffs % legs + 1;
            var matchCase = matchCases[matchCaseIndex];
            var area = port.getDrawingArea();
            // Completed semantic schedules still record subsequent edits. Clear
            // them before preparing fresh shots or starting the next pan.
            cameras[active].cancelSchedule();cameras[1-active].cancelSchedule();
            // Each new destination is a fresh shot. Reusing its retained settling
            // pose would feed the previous cut's zoom and travel into this match.
            cameras[1-active].setLocation(area.width() / 2, area.height() / 2).setZoom(1);
            movers[0].setScale(1,1);movers[1].setScale(1.2,1.2);
            if (matchCase.cameraMotion) {
                var subject = movers[active];
                var screenPosition = subject.getLayer().layerToPortPoint(
                    new pdg.Quad(subject.getRotatedBounds()).centerPoint());
                var distanceLeft = screenPosition.x - area.left;
                var distanceRight = area.right - screenPosition.x;
                // Move the subject toward the farther screen edge. Camera
                // translation moves the scene in the opposite direction.
                var cameraDirection = distanceRight > distanceLeft ? -1 : 1;
                // Native linear motion runs alongside matching and continues
                // past the handoff while hidden. Matching moves the incoming
                // camera, so its inherited motion and settling remain visible.
                var motionSeconds = matchApproachSeconds + matchSettleSeconds + (style.indexOf('fade')>=0 ? matchFadeSeconds : 0);
                var projectedBounds=subject.getLayer().layerToPortQuad(new pdg.Quad(subject.getRotatedBounds())).getBounds();
                // Reserve space for the entire subject, its full oscillation
                // and inherited settling travel before choosing the pan speed.
                var zoom=cameras[active].getZoom();
                var room=Math.max(distanceLeft,distanceRight)-projectedBounds.width()/2-90*zoom-24;
                var panSpeed=Math.min(80,Math.max(0,room)/(zoom*(motionSeconds+matchSettleSeconds)));
                cameras[active].moveBy(cameraDirection * panSpeed * motionSeconds, 0,
                    motionSeconds, pdg.linearTween);
            }
            // The selected shot is the reference: source matching aligns the
            // hidden incoming shot; target matching moves the outgoing shot.
            var operation=style.indexOf('fade')>=0 ? 'matchFadeTo' : 'matchCutTo';
            matchingFade=operation==='matchFadeTo';
            // Accelerating all the way to the fade would carry a large matching
            // pan/zoom rate through the blend. Arrive smoothly at the target shot.
            cameras[active][operation](cameras[1-active],{matchSource:movers[active],matchTarget:movers[1-active],mode:matchCase.mode,approachSeconds:matchApproachSeconds,fadeSeconds:matchFadeSeconds,settleSeconds:matchSettleSeconds,settleReturnsCamera:style.indexOf('return')>=0,approachEasing:style.indexOf('fade')>=0 ? pdg.easeInOutQuad : pdg.easeInQuad});
        }
        else if (style===null) cameras[active].wait(duration).cutTo(cameras[1-active]);
        else if (style>=pdg.camera_WhipLeft) cameras[active].whipPanTo(cameras[1-active],whipDuration,style,.7,pdg.easeInOutQuad);
        else if (style===pdg.camera_LumaFade) cameras[active].lumaFadeTo(cameras[1-active],duration,lumaMask,.2,false,pdg.linearTween);
        else cameras[active].transitionTo(cameras[1-active],duration,style,pdg.linearTween);
    }
    if (!capturing) later(transition, styleIndex >= 11 ? matchHoldSeconds : hold);
    pdg.on(pdg.eventType_PortDraw, function(event) {
        if (event.port !== port) return false;
        if (!capturing && transitioning && cameras[active].isHidden()) {
            settlingUntil = styleIndex >= 11 ? now() + matchSettleSeconds * 1000 : 0;
            var nextDelay = styleIndex >= 11 ? matchSettleSeconds + matchHoldSeconds : hold;
            active = 1 - active; transitioning = false; ++handoffs;
            var next = transition;
            if (automated && handoffs >= (styleIndex >= 11 ? matchCases.length : 1)) {
                handoffs = 0; ++automatedStyleIndex;
                if (automatedStyleIndex === automatedStyles.length) next = finish;
                else styleIndex = automatedStyles[automatedStyleIndex];
            }
            // Hold the view after settling; automated runs use a short hold.
            if (matchingFade) later(function() {
                boundNextShot(Math.min(.4,matchHoldSeconds));later(next,matchHoldSeconds);
            },matchSettleSeconds);
            else later(next, nextDelay);
        }
        var area = port.getDrawingArea(), elapsed = (now() - started) / 1000;
        cameras.forEach(function(camera) {
            var viewport=camera.getViewport();
            if (viewport.left!==area.left || viewport.top!==area.top || viewport.right!==area.right || viewport.bottom!==area.bottom) camera.setViewport(area);
            if (styleIndex<11) camera.setLocation(area.width() / 2, area.height() / 2);
        });
        // Update both scenes, including the hidden scene, from the same clock.
        movers.forEach(function(item, index) {
            if (styleIndex >= 11) {
                // Separate moving subjects make camera travel legible.
                // Fixed rotation avoids changing projected bounds as they spin,
                // which would otherwise introduce extra zoom-rate matching.
                item.setLocation(area.width() * (index ? .6 : .4)
                    + Math.sin(elapsed * 1.2 + index * Math.PI) * 45, area.height() * .57);
                item.setRotation(0);
                return;
            }
            item.setLocation(area.width() * .4 + Math.sin(elapsed * (index ? 1.3 : .9)) * 130,
                area.height() * .57 + Math.cos(elapsed * (index ? .8 : 1.2)) * 35);
            item.setRotation(elapsed * (index ? -.7 : .5));
        });
        if (automated && matchingFade) movers.forEach(function(item,index) {
            if (cameras[index].isHidden()) return;
            var bounds=item.getLayer().layerToPortQuad(new pdg.Quad(item.getRotatedBounds())).getBounds();
            if (!Number.isFinite(bounds.left+bounds.right+bounds.top+bounds.bottom) || bounds.left<area.left || bounds.right>area.right || bounds.top<88 || bounds.bottom>area.bottom-100)
                throw Error('Matched-fade subject left the visible scene: '+matchCases[matchCaseIndex].label+' '+JSON.stringify(bounds));
        });
        return false; // Let SpriteManager render the scene layers.
    });
    layers[layers.length - 1].onDrawPortComplete(function() {
        var area = port.getDrawingArea();
        port.drawRect(new pdg.Rect(0, 0, area.right, 88), fill('#111b2d'));
        port.drawText('Live camera transitions: ' + styles[styleIndex][0], new pdg.Point(24, 34), fill('#ffffff').textSize(25));
        var matchCase = matchCases[matchCaseIndex];
        port.drawText(styleIndex >= 11
            ? 'Options ' + (matchCaseIndex + 1) + '/' + matchCases.length
                + ' | mode: ' + matchCase.label
                + ' | handoff ' + matchLeg + (automated ? '/1 | ' : '/2 | ')
                + (matchCase.cameraMotion ? 'Source pans up to 80 units/s within the frame'
                    : ((matchCase.mode === pdg.matchSource || matchCase.mode === pdg.matchSourceAndSize) ? 'Incoming camera aligns while hidden' : 'Outgoing camera approaches'))
            : 'Warm city and cool night keep moving.',
            new pdg.Point(24, 65), fill('#bdcddd').textSize(16));
        var label = transitioning ? (active ? 'Night → City' : 'City → Night') + ' — ' + styles[styleIndex][0].toLowerCase()
            : (active ? 'Night' : 'City') + (now() < settlingUntil ? ' — settling' : ' — holding');
        port.drawRect(new pdg.Rect(20, area.bottom - 100, 540, area.bottom - 46), fill('#111b2d'));
        port.drawText(label, new pdg.Point(34, area.bottom - 66), fill('#ffffff').textSize(19));
        if (session) session.draw(port);
        return false;
    });
    function finish() {
        finished = true;
        cameras.forEach(function(camera) { camera.cancelSchedule(); });
        layers.forEach(function(item) { pdg.cleanupLayer(item); });
        pdg.gfx.closeGraphicsPort(port); pdg.quit();
    }
    pdg.onKeyPress(function(event) {
        if (!session && event.unicode === pdg.key_Escape) { finish(); return true; }
        return false;
    });
    if (capturing) {
        var sampledProgress=-1;
        window.pdgCameraVisualTest={setProgress:function(progress) {
            if(sampledProgress<0) {
                cameras[active].lumaFadeTo(cameras[1-active],duration,lumaMask,.2,false,pdg.linearTween);
                cameras[active].animate(0);cameras[active].pauseSchedule();transitioning=true;styleIndex=5;
                sampledProgress=0;
            }
            if(!Number.isFinite(progress) || progress<sampledProgress || progress>1)throw Error('Capture progress must increase in [0,1]');
            cameras[active].resumeSchedule().animate((progress-sampledProgress)*duration);cameras[active].pauseSchedule();sampledProgress=progress;
        }};
    }
    pdg.run();
})();
