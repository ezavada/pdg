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

// Make PDG module available through normal require() calls
// This allows scripts to use require('pdg') instead of process._linkedBinding('pdg')
_debug_log('[PDG] pdg_bootstrap.js: Registering PDG module in require cache...');
try {
    const Module = require('module');
    if (Module._cache) {
        Module._cache['pdg'] = {
            id: 'pdg',
            filename: 'pdg',
            loaded: true,
            children: [],
            parent: null,
            paths: [],
            exports: pdgSystem
        };
        _debug_log('[PDG] pdg_bootstrap.js: PDG module registered in Module._cache');
    } else if (publicRequire.cache) {
        publicRequire.cache['pdg'] = {
            id: 'pdg',
            filename: 'pdg',
            loaded: true,
            children: [],
            parent: null,
            paths: [],
            exports: pdgSystem
        };
        _debug_log('[PDG] pdg_bootstrap.js: PDG module registered in publicRequire.cache');
    } else {
        console.log('[PDG] pdg_bootstrap.js: Warning: Could not register PDG module in require cache');
    }
} catch (err) {
    console.error('[PDG] pdg_bootstrap.js: Error registering PDG module in cache:', err.message);
}

_debug_log('[PDG] pdg_bootstrap.js: PDG system loaded, scheduled further execution into event loop');

// Load PDG main asynchronously to ensure proper initialization order
setImmediate(() => {
    _debug_log('[PDG] pdg_bootstrap.js: Loading PDG main...');
    const pdgMain = process._linkedBinding('pdg_main_v24');
    _debug_log('[PDG] pdg_bootstrap.js: Complete - PDG application initialized');
});