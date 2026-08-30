if (typeof(pdg) == 'undefined') {
	console.log("SpecHelper.js requiring pdg");
	pdg = require('pdg');
}
pdg.run();

(function (original) {
    console.enableLogging = function () {
        console.log = original;
    };
    console.disableLogging = function () {
        console.log = function () {};
    };
})(console.log);

if ((typeof(process) != 'undefined') && process.env.PDG_DEBUG && process.env.PDG_DEBUG.indexOf('VERBOSE') != -1) {

	console.log('Found PDG_DEBUG=VERBOSE in environment. Logging tests.');

    verbose = true;
} else {
	console.log('Quiet Mode. Set PDG_DEBUG=VERBOSE in environment for verbose mode.');

	beforeEach(console.disableLogging);

	afterEach(console.enableLogging);
	
	verbose = false;
}

if (typeof(fs) == 'undefined') {
    fs = null;
    try {
        fs = require('fs');
    } catch(e) {
        if (typeof(FS) != "undefined") {
            // running in a browser, use emscripten's file system
            fs = FS;
            fs.readdirSync = fs.readdir;
            fs.readFileSync = fs.readFile;
            fs.unlinkSync = fs.unlink;
	}
}

// The native V8 client retains the legacy `method(null)` signature
// introspection protocol. JSC and browser bindings treat null as an invalid
// required argument instead.
expectNullArgumentError = function(callback) {
	var supportsNullIntrospection =
		(typeof process != 'undefined') && !process.ios;
	if (supportsNullIntrospection) {
		expect(callback).not.toThrow();
	} else {
		expect(callback).toThrow();
	}
};
}
