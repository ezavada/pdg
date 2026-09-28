// Give bundled Jasmine 1.x the same done-callback contract as jasmine-node.
// Both browser and JavaScriptCore runners must wait before releasing fixtures.
module.exports = function installAsyncCompatibility(globals) {
    function adapt(callback, timeout) {
        if (typeof callback !== 'function' || callback.length === 0) return callback;
        return function() {
            var spec = globals.jasmine.getEnv().currentSpec;
            var completed = false;
            function done(error) {
                if (completed) { spec.fail(new Error('done called more than once')); return; }
                if (error) spec.fail(error);
                completed = true;
            }
            done.fail = function(error) { done(error || new Error('async callback failed')); };
            globals.runs(function() {
                try { callback.call(spec, done); }
                catch (error) { done(error); }
            });
            globals.waitsFor(function() { return completed; }, 'asynchronous callback completion', timeout || 5000);
        };
    }
    var nativeIt = globals.it;
    globals.it = function(description, callback, timeout) {
        return nativeIt(description, adapt(callback, timeout));
    };
    ['beforeEach', 'afterEach'].forEach(function(name) {
        var original = globals[name];
        globals[name] = function(callback, timeout) { return original(adapt(callback, timeout)); };
    });
};
