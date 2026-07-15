// Test script for PDG auto-exit feature
// This script should exit automatically without requiring process.exit()

console.log('PDG auto-exit test script starting...');

// Simple computation that doesn't create any lasting handles
let sum = 0;
for (let i = 1; i <= 100; i++) {
    sum += i;
}

console.log(`Computed sum: ${sum}`);
console.log('Script execution complete. Should auto-exit soon...');

// This script intentionally does NOT call process.exit()
// The PDG auto-exit feature should detect completion and exit gracefully 