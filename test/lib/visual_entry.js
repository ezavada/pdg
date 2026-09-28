// Native and Node entry point; iOS uses launch() after preparing bundle paths.
exports.launch = function(id, page, title, navigate) {
    var pdg = require('pdg');
    if (!pdg.hasGraphics) throw Error('Visual pages require a graphics build. Use --web or --ios.');
    var catalog = require('./ui_test_catalog');
    var entry = catalog.filter(function(item) { return item.id === id; })[0];
    if (!entry || !entry.pages[page]) throw Error('Unknown visual page: ' + id + '/' + page);
    var session = require('./visual_session').install(pdg, {page: page, title: title, navigate: navigate});
    process.argv = [process.execPath, entry.scriptPath, '--wait'];
    var script = entry.workingDir === 'repo' ? '../../' + entry.scriptPath : '../' + entry.scriptPath;
    if (process.ios) script = '../' + entry.scriptPath.replace(/^test\//, '');
    require(script);
    session.ready();
    return session;
};
if (typeof process !== 'undefined' && /(?:^|[/\\])visual_entry\.js$/.test(process.argv[1] || '')) {
    // PDG runtime argv contains the executable and entry script, as Node does.
    exports.launch(process.argv[2], Number(process.argv[3]), process.argv[4], function(action) {
        process.exit(action === 'next' ? 90 : action === 'previous' ? 91 : 0);
    });
}
