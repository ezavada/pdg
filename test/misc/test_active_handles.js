// Test script with active handles - should NOT auto-exit
// This script has a timer, so auto-exit should detect it and keep running

console.log('Test script with active timer handle...');

let counter = 0;

// This timer keeps the event loop alive
const interval = setInterval(() => {
    counter++;
    console.log(`Timer tick ${counter}`);
    
    if (counter >= 5) {
        console.log('Clearing timer and exiting...');
        clearInterval(interval);
        
        // After clearing the timer, the script should auto-exit
        console.log('Timer cleared. Should auto-exit in a moment...');
    }
}, 1000);

console.log('Script setup complete. Timer will run 5 times then auto-exit should trigger.');

// This script should:
// 1. Initially detect the active timer handle and continue running
// 2. After clearing the timer, detect no active handles and auto-exit 