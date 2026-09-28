'use strict';
(async () => {
    const $ = id => document.getElementById(id);
    const controls = [...document.querySelectorAll('button,input,select')];
    controls.forEach(control => { control.disabled = true; });
    const embedded = $('recordings');
    let payload = embedded.textContent;
    if (embedded.dataset.encoding === 'gzip-base64') {
        if (typeof DecompressionStream === 'undefined') {
            throw new Error('Please open this viewer in a current version of Chrome, Firefox, Safari or Edge.');
        }
        const bytes = Uint8Array.from(atob(payload), c => c.charCodeAt(0));
        const decoded = new Blob([bytes]).stream().pipeThrough(new DecompressionStream('gzip'));
        payload = await new Response(decoded).text();
    }
    const data = JSON.parse(payload);
    // Expose the decoded data to offline inspection and release verification.
    embedded.type = 'application/json';
    embedded.textContent = payload;
    embedded.dataset.encoding = 'json';
    const records = data.recordings;
    let pair, time = 0, playing = false, previous = null, duration = 0;
    const cameras = {stack: [-8, -22, 8, 3], pile: [-10, -23, 10, 3],
        chain: [-22, -3, 23, 23]};
    const descriptions = {
        stack: 'Watch the gaps, compression and motion as the boxes settle.',
        pile: 'Watch the boxes settle against one another and the bin walls.',
        chain: 'The links pivot from a fixed anchor. Red marks show separation between joint anchors.',
        contacts: 'Rows rotate the opposing forces from inward to vertical; force increases across columns. Arrows vanish on separation, then the circles coast.',
        approach: 'Rows increase the vertical offset from head-on to a miss. Columns speed up left to right. Times mark first contact (or closest pass for misses).'
    };
    const available = (scene, owner) => ['basic', 'chipmunk'].every(solver =>
        records.some(r => r.scene === scene && r.owner === owner && r.solver === solver && !r.sleepAfter));
    for (const option of [...$('owner').options]) {
        if (!records.some(r => r.owner === option.value && r.solver === 'chipmunk')) option.remove();
    }
    function frameAt(record, seconds) {
        let lo = 0, hi = record.frames.length - 1;
        while (lo < hi) {
            const mid = Math.ceil((lo + hi) / 2);
            if (record.frames[mid][0] <= seconds + 1e-8) lo = mid;
            else hi = mid - 1;
        }
        return record.frames[lo];
    }
    function endpoint(frame, index, localX) {
        if (index < 0) return [0, 0];
        const start = 1 + index * 4, angle = frame[start + 2];
        return [frame[start] + Math.cos(angle) * localX, frame[start + 1] + Math.sin(angle) * localX];
    }
    function drawCirclePairs(record, context, width, height) {
        const touching = record.scene === 'contacts';
        const frame = frameAt(record, time), initial = record.frames[0];
        const columns = 1 + Math.max(...record.pairs.map(p => p[1]));
        const rows = 1 + Math.max(...record.pairs.map(p => p[2]));
        const left = 56, top = 47, cw = (width - left - 10) / columns, ch = (height - top - 12) / rows;
        const scale = Math.min((cw - 10) / 10, (ch - 8) / 7);
        context.font = '11px system-ui'; context.textAlign = 'center'; context.fillStyle = '#aebccd';
        context.fillText(touching ? 'Force on each circle →' : 'Contact / closest pass time →', left + (width - left) / 2, 15);
        context.textAlign = 'left'; context.fillText(touching ? 'Angle' : 'Offset', 6, top - 15);
        context.textAlign = 'center';
        for (const [first, column, row, offset, contactSeconds, magnitude, release] of record.pairs) {
            const x = left + column * cw, y = top + row * ch, cx = x + cw / 2, cy = y + ch / 2;
            context.fillStyle = '#c8d5e5';
            if (!row) context.fillText(touching ? `${magnitude}` : `${contactSeconds.toFixed(2).replace(/\.?0+$/, '')} s`, cx, top - 10);
            if (!column) {
                context.fillText(touching ? `${Math.round(offset * 180 / Math.PI)}°` : `${(offset / 2).toFixed(2)}D`, 26, cy - 2);
                context.fillStyle = '#8798ae';
                context.fillText(touching ? (offset === 0 ? 'inward' : offset > 1.57 ? 'vertical' : '') : (offset === 0 ? 'head-on' : offset > 2 ? 'miss' : ''), 26, cy + 13);
            }
            context.strokeStyle = '#304154'; context.lineWidth = 1;
            context.strokeRect(x, y, cw, ch);
            context.save(); context.beginPath(); context.rect(x + 1, y + 1, cw - 2, ch - 2); context.clip();
            context.translate(cx, cy); context.scale(scale, scale);
            // Dashed paths and start markers make each pair's approach visible.
            context.lineWidth = 1 / scale; context.strokeStyle = '#465b70'; context.setLineDash([2 / scale, 3 / scale]);
            for (let side = 0; side < 2; ++side) {
                const i = 1 + (first + side) * 4;
                context.beginPath(); context.moveTo(-5, initial[i + 1]); context.lineTo(5, initial[i + 1]); context.stroke();
                context.beginPath(); context.arc(initial[i], initial[i + 1], 1, 0, Math.PI * 2); context.stroke();
            }
            context.setLineDash([]);
            for (let side = 0; side < 2; ++side) {
                const i = 1 + (first + side) * 4;
                const color = side ? '#ffbb69' : '#70dcf5';
                context.strokeStyle = color; context.fillStyle = side ? '#d89046' : '#368ca4';
                context.lineWidth = 1.5 / scale;
                context.beginPath(); context.arc(frame[i], frame[i + 1], 1, 0, Math.PI * 2);
                context.fill(); context.stroke();
                // Recent trajectory displays deflection without replaying physics in JS.
                context.beginPath();
                for (let sample = 0; sample <= 8; ++sample) {
                    const f = frameAt(record, Math.max(0, time - .8 + sample * .1));
                    if (sample) context.lineTo(f[i], f[i + 1]); else context.moveTo(f[i], f[i + 1]);
                }
                context.stroke();
                if (touching && (release < 0 || time < release)) {
                    const sign = side ? -1 : 1, dx = sign * Math.cos(offset), dy = -sign * Math.sin(offset);
                    const length = .8 + .25 * Math.sqrt(magnitude);
                    const x0 = frame[i], y0 = frame[i + 1], x1 = x0 + dx * length, y1 = y0 + dy * length;
                    context.strokeStyle = '#f9ec99'; context.beginPath();
                    context.moveTo(x0, y0); context.lineTo(x1, y1);
                    context.moveTo(x1 - dx * .35 - dy * .2, y1 - dy * .35 + dx * .2);
                    context.lineTo(x1, y1); context.lineTo(x1 - dx * .35 + dy * .2, y1 - dy * .35 - dx * .2);
                    context.stroke();
                }
            }
            context.restore();
            if (touching) {
                context.fillStyle = release >= 0 && time >= release ? '#8dd5b4' : '#d2c591';
                context.font = '10px system-ui';
                context.fillText(release >= 0 && time >= release ? 'coasting' : 'force on', cx, y + ch - 6);
                context.font = '11px system-ui';
            }
        }
        $(record.solver + '-metric').textContent = `${record.pairs.length} pairs shown · ${touching ? 'arrows = active forces' : 'D = circle diameter'} · bodies can leave their cells`;
    }
    function draw(record) {
        const canvas = $(record.solver), context = canvas.getContext('2d');
        const rect = canvas.getBoundingClientRect(), ratio = window.devicePixelRatio || 1;
        const w = Math.round(rect.width * ratio), h = Math.round(rect.height * ratio);
        if (canvas.width !== w || canvas.height !== h) { canvas.width = w; canvas.height = h; }
        context.setTransform(ratio, 0, 0, ratio, 0, 0);
        context.clearRect(0, 0, rect.width, rect.height);
        if (record.scene === 'approach' || record.scene === 'contacts') {
            drawCirclePairs(record, context, rect.width, rect.height);
            return;
        }
        const [left, top, right, bottom] = cameras[record.scene];
        const scale = Math.min((rect.width - 30) / (right - left), (rect.height - 30) / (bottom - top));
        context.translate((rect.width - (right - left) * scale) / 2 - left * scale,
            (rect.height - (bottom - top) * scale) / 2 - top * scale);
        context.scale(scale, scale);
        context.lineWidth = 1 / scale;
        context.strokeStyle = '#203045';
        for (let x = Math.ceil(left); x <= right; x += 2) {
            context.beginPath(); context.moveTo(x, top); context.lineTo(x, bottom); context.stroke();
        }
        for (let y = Math.ceil(top); y <= bottom; y += 2) {
            context.beginPath(); context.moveTo(left, y); context.lineTo(right, y); context.stroke();
        }
        for (const [x, y, hx, hy] of record.scenery) {
            context.fillStyle = '#46566b'; context.strokeStyle = '#a1b1c6';
            context.fillRect(x - hx, y - hy, hx * 2, hy * 2);
            context.strokeRect(x - hx, y - hy, hx * 2, hy * 2);
        }
        const frame = frameAt(record, time);
        let sleeping = 0, maxError = 0;
        for (let i = 0; i < record.bodies.length; ++i) {
            const [id, hx, hy] = record.bodies[i], start = 1 + i * 4;
            const asleep = frame[start + 3] === 1;
            sleeping += asleep ? 1 : 0;
            context.save(); context.translate(frame[start], frame[start + 1]); context.rotate(frame[start + 2]);
            context.fillStyle = asleep ? '#748595aa' : `hsl(${(id * 47 + 175) % 360} 65% 60% / .62)`;
            context.strokeStyle = asleep ? '#bbc7d1' : `hsl(${(id * 47 + 175) % 360} 85% 83%)`;
            context.lineWidth = 1.5 / scale;
            context.beginPath();
            if (hy) context.rect(-hx, -hy, hx * 2, hy * 2);
            else context.arc(0, 0, hx, 0, Math.PI * 2);
            context.fill(); context.stroke();
            context.strokeStyle = '#102030'; context.beginPath(); context.moveTo(0, 0); context.lineTo(hx * .65, 0); context.stroke();
            context.restore();
        }
        if (record.scene === 'chain') {
            for (let i = 0; i < record.bodies.length; ++i) {
                const a = endpoint(frame, i - 1, 1), b = endpoint(frame, i, -1);
                const error = Math.hypot(a[0] - b[0], a[1] - b[1]);
                maxError = Math.max(maxError, error);
                context.strokeStyle = '#ff736c'; context.lineWidth = 2 / scale;
                context.beginPath(); context.moveTo(...a); context.lineTo(...b); context.stroke();
                context.fillStyle = i ? '#eff4fc' : '#ffdb8a';
                context.beginPath(); context.arc(...a, 2.7 / scale, 0, Math.PI * 2); context.fill();
            }
        }
        $(record.solver + '-metric').textContent = record.scene === 'chain'
            ? `Visible joint separation: ${maxError.toFixed(6)} units`
            : `Showing ${record.bodies.length} bodies · ${sleeping} sleeping`;
    }
    function render() {
        if (!pair) return;
        pair.forEach(draw);
        $('time').value = time;
        $('clock').textContent = `${time.toFixed(2)} / ${duration.toFixed(2)} s`;
        $('play').textContent = playing ? 'Pause' : 'Play';
        $('play').setAttribute('aria-pressed', String(playing));
    }
    function choose(resetTime = true) {
        for (const option of $('scene').options) option.disabled = !available(option.value, $('owner').value);
        if (!available($('scene').value, $('owner').value)) {
            const first = [...$('scene').options].find(o => !o.disabled);
            if (!first) throw new Error('This recording needs both solvers for at least one scene.');
            $('scene').value = first.value;
        }
        const scene = $('scene').value, owner = $('owner').value;
        const find = (solver, sleep) => records.find(r => r.scene === scene && r.owner === owner &&
            r.solver === solver && Boolean(r.sleepAfter) === sleep);
        $('sleep').disabled = !find('chipmunk', true);
        const sleep = $('sleep').checked && !$('sleep').disabled;
        pair = [find('basic', false), find('chipmunk', sleep)];
        duration = Math.min(...pair.map(r => r.frames.at(-1)[0]));
        time = resetTime ? 0 : Math.min(time, duration);
        previous = null;
        $('time').max = duration;
        $('chip-settings').textContent = sleep ? `Sleep after ${pair[1].sleepAfter} s` : 'Sleeping disabled';
        $('caption').textContent = `${pair[0].simulationBodies.toLocaleString()} bodies simulated per solver; ` +
            `${pair[0].bodies.length} shown from ${scene === 'approach' || scene === 'contacts' ? 'rows spanning the full range' : 'the first group'}. ` + descriptions[scene];
        render();
    }
    function seek(seconds) { time = Math.max(0, Math.min(duration, seconds)); previous = null; render(); }
    function toggle() { if (time >= duration) time = 0; playing = !playing; previous = null; render(); }
    function step(delta) { playing = false; seek(time + delta); }
    $('scene').addEventListener('change', () => choose());
    $('owner').addEventListener('change', () => choose());
    $('sleep').addEventListener('change', () => choose(false));
    $('play').addEventListener('click', toggle);
    $('restart').addEventListener('click', () => seek(0));
    $('step').addEventListener('click', () => step(.02));
    $('time').addEventListener('input', () => { playing = false; seek(Number($('time').value)); });
    window.addEventListener('resize', render);
    window.addEventListener('keydown', event => {
        if (event.target.closest('input,select,button')) return;
        if (event.code === 'Space') { event.preventDefault(); toggle(); }
        if (event.code === 'ArrowRight') { event.preventDefault(); step(.02); }
        if (event.code === 'ArrowLeft') { event.preventDefault(); step(-.02); }
    });
    function tick(now) {
        if (playing && previous !== null) {
            time += Math.min((now - previous) / 1000, .1) * Number($('speed').value);
            if (time > duration) {
                if ($('loop').checked) time %= duration;
                else { time = duration; playing = false; }
            }
            render();
        }
        previous = now;
        requestAnimationFrame(tick);
    }
    controls.forEach(control => { control.disabled = false; });
    choose();
    $('loading').hidden = true;
    window.pdgPhysicsViewer = {
        seek,
        get state() { return {time, playing, duration, scene: $('scene').value, owner: $('owner').value,
            frameTimes: pair.map(r => frameAt(r, time)[0]), shown: pair.map(r => r.bodies.length)}; }
    };
    requestAnimationFrame(tick);
})().catch(error => {
    document.getElementById('loading').hidden = true;
    document.getElementById('error').textContent = `Unable to load the recorded comparison. ${error.message}`;
});
