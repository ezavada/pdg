// Realistic PDG script test - should auto-exit when complete
console.log('Starting realistic PDG script...');

// Simulate typical PDG usage
if (typeof pdg !== 'undefined') {
    console.log('PDG version:', process.versions.pdg);
    
    // Some typical computations
    let total = 0;
    for (let i = 0; i < 1000; i++) {
        total += Math.sin(i) * Math.cos(i);
    }
    
    console.log('Computed total:', total.toFixed(4));
    console.log('Script completed successfully');
} else {
    console.log('PDG not available');
}

// This script should auto-exit without requiring process.exit() 