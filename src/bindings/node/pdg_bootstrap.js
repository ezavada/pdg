// pdg_bootstrap.js
//
// Bootstrapper for PDG embedded Node.js
// This is the ONLY entry point for node::LoadEnvironment().
// It sets up PDG bindings and loads the real main script from disk or resources.

// Set up debug logging
_debug_log = function() {};
if (process.env.NODE_DEBUG && /pdg/.test(process.env.NODE_DEBUG)) {
  _debug_log = function(x) {
    console.error(x);
  };
}

_debug_log('[PDG] pdg_bootstrap.js: Module loaded');

// Save the original require function for linked bindings to use
global._originalRequire = require;

// Create a proper require function that can access Node.js built-in modules
// This follows the Node.js embedder's guide approach
const publicRequire = require('module').createRequire(process.cwd() + '/');

// Save the public require function for C++ fallback
global._publicRequire = publicRequire;

// Load the main PDG JavaScript system using _linkedBinding for the first load
_debug_log('[PDG] pdg_bootstrap.js: Loading pdg.js system...');
const pdgSystem = process._linkedBinding('pdg');

global.pdg = pdgSystem;
_debug_log('[PDG] pdg_bootstrap.js: process.pdg has ' + Object.keys(process.pdg).length + ' properties');
_debug_log('[PDG] pdg_bootstrap.js: pdgSystem has ' + Object.keys(pdgSystem).length + ' properties');

// Register the embedded singleton for ordinary CommonJS modules as well as
// the entry script's linked-binding require. Node resolves a filename BEFORE
// consulting Module._cache: a bare 'pdg' cache key alone is not sufficient.
// Without this alias, nested imports load an unrelated npm copy (or fail when
// no package is installed). Only the exact public module name is intercepted;
// relative paths, built-ins, and all other packages keep Node's normal lookup.
const Module = require('module');
const pdgModule = new Module('pdg');
pdgModule.filename = 'pdg';
pdgModule.loaded = true;
pdgModule.exports = pdgSystem;
Module._cache.pdg = pdgModule;
const resolveFilename = Module._resolveFilename;
Module._resolveFilename = function(request, parent, isMain, options) {
    if (request === 'pdg') return 'pdg';
    return resolveFilename.apply(this, arguments);
};
_debug_log('[PDG] pdg_bootstrap.js: Embedded PDG registered for CommonJS imports');

_debug_log('[PDG] pdg_bootstrap.js: PDG system loaded, scheduled further execution into event loop');

// Load PDG main asynchronously to ensure proper initialization order
setImmediate(() => {
    _debug_log('[PDG] pdg_bootstrap.js: Loading PDG main...');
    const pdgMain = process._linkedBinding('pdg_main_v24');
    _debug_log('[PDG] pdg_bootstrap.js: Complete - PDG application initialized');
});
