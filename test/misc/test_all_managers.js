#!/usr/bin/env node

// Test to verify all managers work correctly after our fixes
const pdg = require('pdg');

console.log('=== Testing All Manager Instances ===');

const managers = [
    { name: 'FileManager', instance: pdg.fs, constructor: pdg.FileManager },
    { name: 'TimerManager', instance: pdg.tm, constructor: pdg.TimerManager },
    { name: 'EventManager', instance: pdg.evt, constructor: pdg.EventManager },
    { name: 'ResourceManager', instance: pdg.res, constructor: pdg.ResourceManager },
    { name: 'ConfigManager', instance: pdg.cfg, constructor: pdg.ConfigManager },
    { name: 'LogManager', instance: pdg.lm, constructor: pdg.LogManager },
];

if (pdg.hasGraphics) {
    managers.push({ name: 'GraphicsManager', instance: pdg.gfx, constructor: pdg.GraphicsManager });
}
if (pdg.hasSound) {
    managers.push({ name: 'SoundManager', instance: pdg.snd, constructor: pdg.SoundManager });
}

managers.forEach(({ name, instance, constructor }) => {
    console.log(`\n--- ${name} ---`);
    console.log(`  toString: ${Object.prototype.toString.call(instance)}`);
    console.log(`  instanceof: ${instance instanceof constructor}`);
    console.log(`  constructor ===: ${instance.constructor === constructor}`);
    console.log(`  prototype ===: ${Object.getPrototypeOf(instance) === constructor.prototype}`);
    
    // Test new instance creation
    try {
        const newInstance = new constructor();
        console.log(`  new instance toString: ${Object.prototype.toString.call(newInstance)}`);
        console.log(`  new instance instanceof: ${newInstance instanceof constructor}`);
    } catch (e) {
        console.log(`  new instance: Cannot create (${e.message})`);
    }
});

console.log('\n=== All Tests Complete ===');

// Exit immediately to avoid hanging
setTimeout(() => {
    process.exit(0);
}, 100); 