'use strict';
const assert = require('assert');
const EventEmitter = require('events');
const createOutput = require('./unit_output');

function stream(tty) {
    const result = new EventEmitter();
    Object.assign(result, {isTTY:tty, rows:24, columns:80, text:''});
    result.write = text => { result.text += text; };
    return result;
}
const green = '\x1b[32m.\x1b[0m';
const summary = '\nFinished in 0.2 seconds\n2 tests, 3 assertions, 1 failure, 0 skipped\n';
const terminal = stream(true);
const output = createOutput(terminal, {TERM:'xterm-256color'});
output.start();
terminal.write('Application log\n');
output.progress(green);
output.print(green);
assert(terminal.text.includes(green), 'progress is visible before completion');
assert(terminal.text.includes('\x1b[1;17r'), 'application logs use the upper scroll region');
output.progress('\x1b[31mF\x1b[0m');
output.print('\x1b[31mF\x1b[0m\nFailures:\n  expected true\n');
output.print(summary);
assert(!terminal.text.includes('Failures:'), 'diagnostics stay out of the live pane');
terminal.columns = 30;
terminal.rows = 12;
terminal.emit('resize');
assert(terminal.text.includes('\x1b[1;7r'), 'pane follows terminal resize');
output.finish();
assert(terminal.text.indexOf('Application log') < terminal.text.indexOf('Failures:'));
assert(terminal.text.endsWith(summary));
assert(terminal.text.includes('\x1b[r\x1b8'), 'restore cursor after resetting the scroll region');
assert.strictEqual(terminal.listenerCount('resize'), 0);
const complete = terminal.text;
output.finish();
assert.strictEqual(terminal.text, complete, 'exit cleanup does not duplicate output');

for (const [tty, env] of [[false, {}], [true, {TERM:'dumb'}]]) {
    const redirected = stream(tty);
    const buffered = createOutput(redirected, env);
    buffered.start();
    buffered.progress(green);
    buffered.print(green);
    redirected.write('Application log\n');
    assert.strictEqual(redirected.text, 'Application log\n');
    buffered.print(summary);
    buffered.finish();
    assert(redirected.text.endsWith(green + summary));
    assert(!redirected.text.includes('\x1b[r'), 'no cursor controls in redirected output');
}

// Resizing below the minimum height restores ordinary scrolling immediately.
const tiny = stream(true);
const resized = createOutput(tiny, {});
resized.start();
tiny.rows = 5;
tiny.emit('resize');
assert(tiny.text.includes('\x1b[r'));
tiny.rows = 24;
tiny.emit('resize');
const restoredPane = tiny.text.length;
resized.progress(green);
assert(tiny.text.slice(restoredPane).includes(green), 'live progress resumes when the terminal grows');
resized.finish();
assert.strictEqual(tiny.listenerCount('resize'), 0);

const narrow = stream(true);
narrow.columns = 10;
const rolling = createOutput(narrow, {});
rolling.start();
rolling.progress('\x1b[31mF\x1b[0m');
for (let i = 1; i < 54; ++i) rolling.progress(green);
const fullPane = narrow.text.length;
rolling.progress(green);
const repaint = narrow.text.slice(fullPane);
assert(repaint.includes('\x1b[J'), 'a full pane rolls by a whole row');
assert(!repaint.includes('\x1b[31mF'), 'oldest row leaves the live pane');
rolling.finish();
console.log('PASS: live unit progress, resize, cleanup, failures and redirected output');
