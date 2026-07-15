// Test script that disables PDG auto-exit feature
// This script will hang (as before) unless manually terminated

console.log('Test script with auto-exit disabled...');

// Disable auto-exit
global._pdgNoAutoExit = true;

// Simple computation
let sum = 0;
for (let i = 1; i <= 50; i++) {
    sum += i;
}

console.log(`Computed sum: ${sum}`);
console.log('Script execution complete, but auto-exit is disabled.');
console.log('This script will hang indefinitely. Press Ctrl+C to exit.');

// This script will NOT auto-exit because we disabled it
// Demonstrates the opt-out mechanism 