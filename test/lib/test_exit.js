console.log("Testing explicit exit...");

const pdg = require('pdg');
console.log("PDG available:", !!pdg);

console.log("Exiting with code 0");
process.exit(0); 