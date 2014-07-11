if (typeof(pdg) == 'undefined') {
	console.log("SpecHelper.js requiring pdg");
	pdg = require('pdg');
	pdg.run();
}

(function (original) {
    console.enableLogging = function () {
        console.log = original;
    };
    console.disableLogging = function () {
        console.log = function () {};
    };
})(console.log);

if (process.env.PDG_DEBUG && process.env.PDG_DEBUG.indexOf('VERBOSE') != -1) {

	console.log('Found PDG_DEBUG=VERBOSE in environment. Logging tests.');

} else {
	console.log('Quiet Mode. Set PDG_DEBUG=VERBOSE in environment for verbose mode.');

	beforeEach(console.disableLogging);

	afterEach(console.enableLogging);
}
