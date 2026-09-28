// Shared spring-driven head/hand controller, with optional bone-bound sword artwork.
// All controller times, transition durations and spring steps are seconds.
module.exports = function(pdg, sprite, layer, worldScale, options) {
    var HEAD = options.head, SHOULDER = options.shoulder, ELBOW = options.elbow, HAND = options.hand;
    var arm = [SHOULDER, ELBOW, HAND];
    var grip, bladeStart, bladeTip;
    function angle(value) { return Math.atan2(Math.sin(value), Math.cos(value)); }
    function clamp(value, low, high) { return Math.max(low, Math.min(high, value)); }
    function point(transform, local) {
        var x = local.x * transform.scaleX, y = local.y * transform.scaleY;
        return new pdg.Point(transform.x + x * Math.cos(transform.rotation) - y * Math.sin(transform.rotation),
            transform.y + x * Math.sin(transform.rotation) + y * Math.cos(transform.rotation));
    }
    function segmentDistance(p, a, b) {
        var dx = b.x - a.x, dy = b.y - a.y;
        var t = clamp(((p.x - a.x) * dx + (p.y - a.y) * dy) / Math.max(1e-12, dx * dx + dy * dy), 0, 1);
        return Math.hypot(p.x - a.x - t * dx, p.y - a.y - t * dy);
    }
    if (!sprite.isAnimationPoseEnabled() && !sprite.enableAnimationPose(options.reference))
        throw new Error(options.label + ' pose: ' + sprite.getAnimationRigError());
    if (options.clips) sprite.startAnimation(options.reference);
    var initialHand = sprite.getAnimationBoneTransform(HAND, pdg.animationSpace_World);
    // Drawing geometry is specified in display-sized rig units. Compensate for
    // the imported hand's nonuniform bone scale, especially on Grey Guy.
    var localScaleX = worldScale / Math.abs(initialHand.scaleX);
    var localScaleY = worldScale / Math.abs(initialHand.scaleY);
    function local(x, y) { return new pdg.Point(x * localScaleX, y * localScaleY); }
    grip = local(options.grip.x, options.grip.y);
    bladeStart = local(options.grip.x, options.grip.y - (options.sword ? 9 : 0));
    bladeTip = local(options.grip.x, options.grip.y - (options.sword ? 64 : 0));
    var initialTip = point(initialHand, bladeTip);
    var spring = new pdg.AnimationSpringTarget(1, 85, 11);
    spring.setState({x: initialTip.x, y: initialTip.y, velocityX: 0, velocityY: 0});
    var state = {
        sprite: sprite, spring: spring, clip: options.reference, cycleStartSeconds: null,
        label: options.label, facing: sprite.isFlippedX() ? -1 : 1,
        intervalSeconds: 4.0, blendSeconds: 0.65, transitionCount: 0,
        lastSeconds: null, aimWeight: 0, tracking: false, aim: initialTip,
        mouse: null, hitCount: 0, hitArmed: true, flashUntilSeconds: 0,
        baseArm: [], bladeStart: bladeStart, bladeTip: bladeTip, grip: grip
    };

    // Save each freshly sampled arm before IK; blend back to that exact sample
    // when tracking fades out. Head and arm edits never accumulate across frames.
    state.preModifier = sprite.addAnimationModifier(function(view) {
        state.baseArm = arm.map(function(name) { return view.getLocalTransform(name); });
        if (!state.aimWeight) return;
        var head = view.getTransform(HEAD, pdg.animationSpace_World);
        var parent = view.getTransform(options.headParent, pdg.animationSpace_World);
        var desired = Math.atan2(state.aim.y - head.y, state.aim.x - head.x);
        // The head bone's x-axis runs up the skull; its forward axis is +pi/2.
        var turn = clamp(angle(desired - head.rotation - Math.PI / 2), -0.65, 0.65);
        view.rotateLocal(HEAD, turn * state.aimWeight * (parent.scaleX * parent.scaleY < 0 ? -1 : 1));
    }, pdg.animationStage_PreConstraint);
    function addIK(hand) {
        return sprite.addAnimationIK({root: SHOULDER, middle: ELBOW, tip: HAND,
            targetX: hand.x, targetY: hand.y, space: pdg.animationSpace_World,
            bendDirection: -state.facing, stretch: pdg.animationIK_NoStretch});
    }
    state.ik = addIK(initialHand);
    state.postModifier = sprite.addAnimationModifier(function(view) {
        var hand = view.getTransform(HAND, pdg.animationSpace_World);
        var parent = view.getTransform(ELBOW, pdg.animationSpace_World);
        var dx = state.aim.x - hand.x, dy = state.aim.y - hand.y;
        // Compensate for the grip's sideways offset from the wrist. The sword's
        // negative local y-axis then points from the grip toward the target.
        var heading = options.sword ? Math.atan2(dy, dx) +
            Math.acos(clamp(grip.x * hand.scaleX / Math.max(1e-9, Math.hypot(dx, dy)), -1, 1)) :
            (state.handAngle === undefined ? hand.rotation : state.handAngle);
        view.rotateLocal(HAND, angle(heading - hand.rotation) * (parent.scaleX * parent.scaleY < 0 ? -1 : 1));
        arm.forEach(function(name, i) {
            var solved = view.getLocalTransform(name), base = state.baseArm[i];
            solved.rotation = base.rotation + angle(solved.rotation - base.rotation) * state.aimWeight;
            view.setLocalTransform(name, solved);
        });
    }, pdg.animationStage_PostConstraint);

    var bladeElement;
    function bladeInk(hit) { return new pdg.Attributes().fillColor(hit ? 'orange' : 'silver').lineColor('white').lineThickness(1); }
    if (options.sword) {
        var sword = pdg.createDrawing(), blade = new pdg.Polygon();
        var gx = options.grip.x, gy = options.grip.y;
        [[-3,-9],[-3,-54],[0,-64],[3,-54],[3,-9]].forEach(function(p) {
            blade.addPoint(local(gx + p[0], gy + p[1]));
        });
        bladeElement = sword.addPolygon(blade, bladeInk(false));
        sword.addLine(local(gx,gy-10), local(gx,gy-59), new pdg.Attributes().lineColor('white').lineThickness(1));
        function rect(x0,y0,x1,y1,color) {
            sword.addRect(new pdg.Rect((gx+x0)*localScaleX,(gy+y0)*localScaleY,
                (gx+x1)*localScaleX,(gy+y1)*localScaleY),new pdg.Attributes().fillColor(color).lineColor('black'));
        }
        rect(-2,-6,2,9,'brown'); rect(-10,-10,10,-6,'gold'); rect(-3,8,3,12,'gold');
        state.drawing = sword;
        state.drawable = sprite.addAnimationDrawable(sword, {bone: HAND,
            placement: pdg.animationDraw_BeforeSlot, slot: options.handSlot,
            bounds: {left:(gx-11)*localScaleX,top:(gy-65)*localScaleY,
                right:(gx+11)*localScaleX,bottom:(gy+13)*localScaleY}});
    }
    var flashing = false;
    state.start = function(seconds) {
        if (state.cycleStartSeconds === null) state.cycleStartSeconds = seconds;
    };
    state.update = function(seconds, mousePort, portBounds) {
        if(state.physicsPaused){state.lastSeconds=seconds;return;}
        var dt = state.lastSeconds === null ? 0 : clamp(seconds - state.lastSeconds, 0, 0.05);
        state.lastSeconds = seconds;
        if (options.clips && state.cycleStartSeconds !== null) {
            var cycle = Math.floor((seconds - state.cycleStartSeconds) / state.intervalSeconds);
            var clip = options.clips[cycle % options.clips.length];
            if (options.flipWithCycle) sprite.setFlipX(Math.floor(cycle / options.clips.length) % 2 === 1);
            if (clip !== state.clip) {
                sprite.transitionToAnimation(clip, 0.0, state.blendSeconds);
                state.clip = clip; ++state.transitionCount;
            }
        }
        var facing = sprite.isFlippedX() ? -1 : 1;
        if (facing !== state.facing) {
            state.facing = facing; state.aimWeight = 0;
            sprite.removeAnimationModifier(state.ik);
            var resetHand = sprite.getAnimationBoneTransform(HAND, pdg.animationSpace_World);
            var resetTip = point(resetHand, bladeTip);
            spring.setState({x:resetTip.x,y:resetTip.y,velocityX:0,velocityY:0});
            state.aim = resetTip; state.ik = addIK(resetHand);
        }
        var screenRoot = layer.layerToPortPoint(sprite.getLocation());
        state.tracking = !!mousePort && (mousePort.x - screenRoot.x) * state.facing > 0 &&
            mousePort.x >= portBounds.left && mousePort.x < portBounds.right &&
            mousePort.y >= portBounds.top && mousePort.y < portBounds.bottom;
        state.mouse = mousePort;
        state.aimWeight += ((state.tracking ? 1 : 0) - state.aimWeight) * (1 - Math.exp(-dt / 0.15));
        if (state.aimWeight < 0.001 && !state.tracking) state.aimWeight = 0;
        var hand = sprite.getAnimationBoneTransform(HAND, pdg.animationSpace_World);
        var destination = state.tracking ? layer.portToLayerPoint(mousePort) : point(hand, bladeTip);
        state.aim = spring.update(destination.x, destination.y, dt);
        var shoulder = sprite.getAnimationBoneTransform(SHOULDER, pdg.animationSpace_World);
        var direction = Math.atan2(state.aim.y - shoulder.y, state.aim.x - shoulder.x);
        var rotation = options.sword ? direction + Math.PI / 2 : direction + 0.58 * state.facing;
        state.handAngle = rotation;
        var offsetX = bladeTip.x * hand.scaleX * Math.cos(rotation) - bladeTip.y * hand.scaleY * Math.sin(rotation);
        var offsetY = bladeTip.x * hand.scaleX * Math.sin(rotation) + bladeTip.y * hand.scaleY * Math.cos(rotation);
        sprite.setAnimationIKTarget(state.ik, state.aim.x - offsetX, state.aim.y - offsetY, pdg.animationSpace_World);
        hand = sprite.getAnimationBoneTransform(HAND, pdg.animationSpace_World);
        state.swordStart = layer.layerToPortPoint(point(hand, bladeStart));
        state.swordTip = layer.layerToPortPoint(point(hand, bladeTip));
        var distance = mousePort ? segmentDistance(mousePort, state.swordStart, state.swordTip) : Infinity;
        if (distance > 14 && seconds >= state.flashUntilSeconds + 0.25) state.hitArmed = true;
        if (options.sword && state.tracking && state.aimWeight > 0.8 && state.hitArmed && distance < 7) {
            var dx = state.swordTip.x - state.swordStart.x, dy = state.swordTip.y - state.swordStart.y;
            var length = Math.max(1, Math.hypot(dx, dy));
            // Recoil the spring target, not the OS cursor. One impulse per
            // contact, rearmed only after separation, prevents overlap chatter.
            spring.applyImpulse((-dx / length - .35 * dy / length) * 120 * worldScale,
                (-dy / length + .35 * dx / length) * 120 * worldScale);
            state.hitArmed = false; ++state.hitCount;
            state.flashUntilSeconds = seconds + 0.18;
            state.hitPoint = new pdg.Point(mousePort.x, mousePort.y);
        }
        var hit = seconds < state.flashUntilSeconds;
        if (hit !== flashing) { flashing = hit; if (bladeElement) bladeElement.setAttributes(bladeInk(hit)); }
    };
    state.drawOverlay = function(port) {
        if (flashing && state.hitPoint) {
            var ink = new pdg.Attributes().lineColor('yellow').lineThickness(2);
            for (var i = 0; i < 6; ++i) {
                var a = i * Math.PI / 3;
                port.drawLine(new pdg.Point(state.hitPoint.x + 5 * Math.cos(a), state.hitPoint.y + 5 * Math.sin(a)),
                    new pdg.Point(state.hitPoint.x + 12 * Math.cos(a), state.hitPoint.y + 12 * Math.sin(a)), ink);
            }
        }
    };
    return state;
};
