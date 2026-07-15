// Simple test to debug delayTimerUntil issue
var pdg = require('pdg');

console.log('Testing delayTimerUntil...');

var delayUntilCount = 0;
var originalFireTime = 0;
var delayedFireTime = 0;
var targetFireTime = 0;

var t = pdg.tm.onInterval(function(evt) {
    delayUntilCount++;
    console.log('Timer fired #' + delayUntilCount + ' at time ' + pdg.tm.getMilliseconds());
    
    if (delayUntilCount === 1) {
        originalFireTime = pdg.tm.getMilliseconds();
        targetFireTime = pdg.tm.getMilliseconds() + 100;
        console.log('Setting delayUntil to ' + targetFireTime);
        pdg.tm.delayTimerUntil(evt.id, targetFireTime);
    } else if (delayUntilCount === 2) {
        delayedFireTime = pdg.tm.getMilliseconds();
        console.log('Second fire at time ' + delayedFireTime);
        console.log('Target was ' + targetFireTime);
        console.log('Difference: ' + (delayedFireTime - targetFireTime));
        
        if (delayedFireTime >= targetFireTime) {
            console.log('SUCCESS: Timer fired at or after target time');
        } else {
            console.log('FAILURE: Timer fired before target time');
        }
        
        // Cancel the timer
        pdg.tm.cancelTimer(evt.id);
    }
}, 20);

// Start the pdg event loop
pdg.run();

// Let it run for a few seconds
setTimeout(function() {
    console.log('Test completed');
    pdg.quit();
}, 5000);
