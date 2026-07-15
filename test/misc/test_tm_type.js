#!/usr/bin/env node

// Test to check pdg.tm type information
const pdg = require('pdg');

console.log('=== PDG TimerManager Type Information ===');
console.log('pdg.tm type:', typeof pdg.tm);
console.log('pdg.tm constructor.name:', pdg.tm.constructor.name);
console.log('pdg.tm toString:', Object.prototype.toString.call(pdg.tm));
console.log('pdg.tm.toString():', pdg.tm.toString());
console.log('pdg.tm instanceof pdg.TimerManager:', pdg.tm instanceof pdg.TimerManager);

console.log('\n=== Other Manager Types ===');
console.log('pdg.fs toString:', Object.prototype.toString.call(pdg.fs));
console.log('pdg.evt toString:', Object.prototype.toString.call(pdg.evt));
console.log('pdg.res toString:', Object.prototype.toString.call(pdg.res));
console.log('pdg.cfg toString:', Object.prototype.toString.call(pdg.cfg));
console.log('pdg.lm toString:', Object.prototype.toString.call(pdg.lm));
if (pdg.hasGraphics) {
    console.log('pdg.gfx toString:', Object.prototype.toString.call(pdg.gfx));
}
if (pdg.hasSound) {
    console.log('pdg.snd toString:', Object.prototype.toString.call(pdg.snd));
}

console.log('\n=== Constructor Chain ===');
console.log('pdg.tm.constructor:', pdg.tm.constructor);
console.log('pdg.tm.constructor === pdg.TimerManager:', pdg.tm.constructor === pdg.TimerManager);
console.log('pdg.TimerManager.name:', pdg.TimerManager.name);
console.log('pdg.tm.constructor === pdg.tm.constructor:', pdg.tm.constructor === pdg.tm.constructor);
console.log('Are they the same function reference?', pdg.tm.constructor.toString() === pdg.TimerManager.toString());

console.log('\n=== Prototype Chain ===');
console.log('Object.getPrototypeOf(pdg.tm):', Object.getPrototypeOf(pdg.tm));
console.log('Object.getPrototypeOf(pdg.tm).constructor.name:', Object.getPrototypeOf(pdg.tm).constructor.name);
console.log('pdg.TimerManager.prototype:', pdg.TimerManager.prototype);
console.log('Prototype equality check:');
console.log('  Object.getPrototypeOf(pdg.tm) === pdg.TimerManager.prototype:', Object.getPrototypeOf(pdg.tm) === pdg.TimerManager.prototype);
console.log('  pdg.tm.__proto__ === pdg.TimerManager.prototype:', pdg.tm.__proto__ === pdg.TimerManager.prototype);
console.log('Constructor on prototype:');
console.log('  Object.getPrototypeOf(pdg.tm).constructor === pdg.TimerManager:', Object.getPrototypeOf(pdg.tm).constructor === pdg.TimerManager);

console.log('\n=== Methods Check ===');
console.log('pdg.tm.onTimeout type:', typeof pdg.tm.onTimeout);
console.log('pdg.tm.onInterval type:', typeof pdg.tm.onInterval);

console.log('\n=== Test New Instance ===');
try {
    const newTM = new pdg.TimerManager();
    console.log('new TimerManager() constructor.name:', newTM.constructor.name);
    console.log('new TimerManager() toString:', Object.prototype.toString.call(newTM));
    console.log('new TimerManager() has onTimeout:', typeof newTM.onTimeout);
} catch (e) {
    console.log('Cannot create new TimerManager:', e.message);
}

// Exit immediately to avoid hanging
setTimeout(() => {
    process.exit(0);
}, 100); 