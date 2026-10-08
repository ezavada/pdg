'use strict';

// A terminal scroll region also separates logs written directly by native code.
// Only Jasmine output is buffered; application stdout/stderr stay untouched.
module.exports = function createUnitOutput(stream, env) {
    var chunks = [], dots = [], active = false, finished = false;
    var live = !!(stream.isTTY && env.TERM !== 'dumb' && stream.rows >= 8 && stream.columns >= 10);
    var bottom, width, dotRows;

    function layout() {
        width = Math.max(1, stream.columns - 1);
        dotRows = Math.max(1, Math.min(6, Math.floor(stream.rows / 3)));
        bottom = stream.rows - dotRows - 1;
    }

    function render() {
        if (!active) return;
        var first = Math.max(0, Math.ceil(dots.length / width) - dotRows) * width;
        var visible = dots.slice(first);
        var output = '\x1b7\x1b[' + (bottom + 1) + ';1H\x1b[J' + '-'.repeat(width);
        for (var i = 0; i < visible.length; i += width) {
            output += '\x1b[' + (bottom + 2 + Math.floor(i / width)) + ';1H' + visible.slice(i, i + width).join('');
        }
        stream.write(output + '\x1b8');
    }

    function resize() {
        if (finished) return;
        // Release the old pane before rebuilding it at the new terminal size.
        if (active) stream.write('\x1b[r\x1b[' + (bottom + 1) + ';1H\x1b[J');
        if (stream.rows < 8 || stream.columns < 10) {
            active = false;
            return;
        }
        layout();
        stream.write('\x1b[1;' + bottom + 'r\x1b[' + bottom + ';1H');
        active = true;
        render();
    }

    return {
        start: function() {
            if (!live || active || finished) return;
            layout();
            // Make space below any startup logs before reserving the pane.
            stream.write('\n'.repeat(dotRows + 1) + '\x1b[1;' + bottom + 'r\x1b[' + bottom + ';1H');
            active = true;
            stream.on('resize', resize);
            render();
        },
        progress: function(dot) {
            if (finished) return;
            dots.push(dot);
            if (!active) return;
            var index = dots.length - 1;
            if (index >= width * dotRows && index % width === 0) {
                render();
            } else {
                var row = bottom + 2 + Math.min(Math.floor(index / width), dotRows - 1);
                stream.write('\x1b7\x1b[' + row + ';' + (index % width + 1) + 'H' + dot + '\x1b8');
            }
        },
        print: function(text) {
            if (!finished) chunks.push(String(text));
        },
        finish: function() {
            if (finished) return;
            finished = true;
            if (live) stream.removeListener('resize', resize);
            if (active) {
                // Keep the log cursor, clear the pane, and restore normal scrolling.
                stream.write('\x1b7\x1b[' + (bottom + 1) + ';1H\x1b[J\x1b[r\x1b8');
                active = false;
            }
            stream.write('\n' + '-'.repeat(Math.max(1, Math.min(stream.columns || 80, 80) - 1)) + '\n' + chunks.join(''));
        }
    };
};
