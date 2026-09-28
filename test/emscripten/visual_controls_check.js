// Exercise real browser input, page reloads and paused framebuffers.
module.exports = async function({evaluate, pageCall, delay, url}) {
    const assert = require('assert');
    async function ready(expected) {
        const deadline = Date.now() + 30000;
        while (Date.now() < deadline) {
            if (await evaluate('!!window.pdgVisualSession && window.pdgVisualSession.title.includes(' + JSON.stringify(expected) + ')')) {
                await delay(150); return;
            }
            const error = await evaluate('document.getElementById("pdg-ui-result-json").textContent');
            if (error) throw Error(error);
            await delay(100);
        }
        throw Error('Visual page did not initialize: ' + expected);
    }
    async function key(name, code, virtualKey) {
        await pageCall('Input.dispatchKeyEvent', {type: 'keyDown', key: name, code, windowsVirtualKeyCode: virtualKey,
            text: name === ' ' ? ' ' : undefined});
        await pageCall('Input.dispatchKeyEvent', {type: 'keyUp', key: name, code, windowsVirtualKeyCode: virtualKey});
        await delay(100);
    }
    async function click(x, y) {
        const bounds = await evaluate('(function(){var r=document.getElementById("pdg-canvas").getBoundingClientRect();return {x:r.left,y:r.top};})()');
        await pageCall('Input.dispatchMouseEvent', {type:'mousePressed', x:bounds.x+x, y:bounds.y+y, button:'left', clickCount:1});
        await pageCall('Input.dispatchMouseEvent', {type:'mouseReleased', x:bounds.x+x, y:bounds.y+y, button:'left', clickCount:1});
        await delay(100);
    }
    await ready('shape-fill/pentagram');
    await key(' ', 'Space', 32);
    assert(await evaluate('pdgVisualSession.paused'), 'Space must pause');
    const before = await evaluate('pdg.tm.getMilliseconds()');
    const shot = await pageCall('Page.captureScreenshot', {format:'png'});
    await delay(300);
    assert.strictEqual(await evaluate('pdg.tm.getMilliseconds()'), before, 'Clock advances while paused');
    const after = await pageCall('Page.captureScreenshot', {format:'png'});
    assert(after.data === shot.data, 'Drawing changes while paused');
    await click(15, 100);
    assert(!await evaluate('pdgVisualSession.paused'), 'Background click must resume');
    await delay(150);
    assert(await evaluate('pdg.tm.getMilliseconds()') > before, 'Clock did not resume');
    await key('ArrowRight', 'ArrowRight', 39);
    await ready('shape-fill/complex');
    await key('ArrowLeft', 'ArrowLeft', 37);
    await ready('shape-fill/pentagram');
    // Toolbar navigation is available without a keyboard (iOS/touch).
    const size = await evaluate('(function(){var r=pdg.gfx.getMainPort().getDrawingArea();return {w:r.width(),h:r.height()};})()');
    await click(size.w - 25, size.h - 15);
    await ready('shape-fill/complex');
    const physicsURL = new URL(url);
    physicsURL.search = '?interactive=1&kind=demo&suites=particles&page=1';
    await pageCall('Page.navigate', {url:physicsURL.href});
    await ready('particles/particles');
    await delay(300);
    await key(' ', 'Space', 32);
    assert(await evaluate('pdgVisualSession.paused'));
    const particleFrame = await pageCall('Page.captureScreenshot', {format:'png'});
    await delay(300);
    const pausedParticles = await pageCall('Page.captureScreenshot', {format:'png'});
    assert(particleFrame.data === pausedParticles.data, 'Particle physics advances while paused');
    await key(' ', 'Space', 32);
    assert(!await evaluate('pdgVisualSession.paused'));
    await delay(300);
    assert.notStrictEqual((await pageCall('Page.captureScreenshot', {format:'png'})).data, pausedParticles.data, 'Particles did not resume');
    physicsURL.search = '?interactive=1&kind=demo&suites=animation-physics&page=1';
    await pageCall('Page.navigate', {url:physicsURL.href});
    await ready('animation-physics/animation-physics');
    await click(900, 140); // Show capsules, a real demo control.
    assert(await evaluate('pdgAnimationPhysicsDemo.getCapsules().visible'), 'Demo button did not receive its click');
    assert(!await evaluate('pdgVisualSession.paused'), 'A demo button also paused the session');
    await key(' ', 'Space', 32);
    const pose = await evaluate('JSON.stringify(pdgAnimationPhysicsDemo.getCapsules().bodies)');
    await delay(250);
    assert.strictEqual(await evaluate('JSON.stringify(pdgAnimationPhysicsDemo.getCapsules().bodies)'), pose, 'Rig moves while paused');
    physicsURL.search = '?interactive=1&kind=demo&suites=mvc&page=1';
    await pageCall('Page.navigate', {url:physicsURL.href});
    await ready('mvc/mvc');
    await click(150, 260); // Checkbox controller registers after Application calls pdg.run().
    assert(!await evaluate('pdgVisualSession.paused'), 'MVC control click was intercepted by the session');
    await key(' ', 'Space', 32);
    assert(await evaluate('pdgVisualSession.paused'), 'MVC session did not pause');
    return {status:'passed', checks:['page selection', 'Space pause', 'frozen clock', 'frozen drawing',
        'background click resume', 'next/previous keys', 'touch toolbar', 'particle physics pause/resume',
        'demo button priority', 'rig physics pause', 'MVC input priority']};
};
