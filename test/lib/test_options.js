// Selection is shared by all three entry points. Keep this module runtime-free.
'use strict';
const catalog = require('./ui_test_catalog');

function parse(kind, args) {
    if (!['unit', 'ui', 'demo'].includes(kind)) throw Error('Expected unit, ui, or demo.');
    const options = {kind, target: 'native', suites: [], page: null};
    for (let i = 0; i < args.length; ++i) {
        const arg = args[i];
        if (['--web', '--emscripten', '--ios', '--node'].includes(arg)) {
            const target = arg === '--emscripten' ? 'web' : arg.slice(2);
            if (options.target !== 'native' && options.target !== target)
                throw Error('Choose only one of --web, --ios, and --node.');
            options.target = target;
        } else if (arg === '--page' || arg.startsWith('--page=')) {
            options.page = arg === '--page' ? args[++i] : arg.slice(7);
            if (!options.page || options.page.startsWith('-')) throw Error('--page requires a page number or name.');
        } else if (['--list', '--verbose', '--no-build', '--automated', '--iphone', '--ipad'].includes(arg)) {
            options[arg.slice(2)] = true;
        } else if (['--help', '-h', '/?'].includes(arg)) options.help = true;
        else if (arg === '--wait') {} // Compatibility: visual sessions are interactive by default.
        else if (arg.startsWith('-')) throw Error('Unknown option: ' + arg);
        else options.suites.push(arg.replace(/^(?:spec[/\\]|js:)/, '').replace(/\.spec\.js$/, ''));
    }
    if (kind === 'unit' && options.page !== null) throw Error('--page applies to ui and demo.');
    if (options.iphone && options.ipad) throw Error('Choose --iphone or --ipad.');
    if ((options.iphone || options.ipad) && options.target !== 'ios') throw Error('--iphone/--ipad require --ios.');
    if (options.automated && options.page !== null) throw Error('--automated runs complete suites; omit --page.');
    return options;
}

function visualPages(options) {
    const suites = catalog.filter(entry => entry.kind === options.kind);
    const requested = options.suites.map(name => name === 'shape' ? 'shape-fill' : name === 'control-gallery' ? 'mvc' : name);
    requested.forEach(name => {
        if (!suites.some(entry => entry.id === name))
            throw Error('Unknown ' + options.kind + ' suite: ' + name + '. Use --list.');
    });
    const pages = [];
    suites.filter(entry => !requested.length || requested.includes(entry.id)).forEach(entry => {
        entry.pages.forEach((name, index) => pages.push({suite: entry.id, name,
            id: entry.id + '/' + name, localPage: index, entry}));
    });
    return pages;
}

function pageIndex(pages, requested) {
    if (requested === null) return 0;
    if (/^[1-9][0-9]*$/.test(requested)) {
        const index = Number(requested) - 1;
        if (index < pages.length) return index;
    } else {
        const matches = pages.map((p, i) => p.id === requested || p.name === requested ? i : -1).filter(i => i >= 0);
        if (matches.length === 1) return matches[0];
        if (matches.length > 1) throw Error('Ambiguous page: ' + requested + '. Use suite/page.');
    }
    throw Error('Unknown page: ' + requested + '. Use --list to see page numbers and names.');
}

exports.parse = parse;
exports.visualPages = visualPages;
exports.pageIndex = pageIndex;
