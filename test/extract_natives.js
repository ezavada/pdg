#!/usr/bin/env node

const fs = require('fs');

// Extract the pdg_main_v24_native array data from the natives header file
function extractNativeArray() {
    const nativesContent = fs.readFileSync('src/bindings/node/pdg_natives.h', 'utf8');
    
    // Find the pdg_main_v24_native array
    const startMarker = 'const PDG_JS_CHAR pdg_main_v24_native[] = {';
    const endMarker = '};';
    
    const startIndex = nativesContent.indexOf(startMarker);
    if (startIndex === -1) {
        console.error('Could not find pdg_main_v24_native array');
        return null;
    }
    
    const arrayStart = startIndex + startMarker.length;
    const arrayEnd = nativesContent.indexOf(endMarker, arrayStart);
    if (arrayEnd === -1) {
        console.error('Could not find end of pdg_main_v24_native array');
        return null;
    }
    
    const arrayData = nativesContent.substring(arrayStart, arrayEnd);
    return arrayData;
}

// Convert the array data back to a string
function arrayToString(arrayData) {
    // Split by commas and convert each number to a character
    const numbers = arrayData.split(',').map(s => parseInt(s.trim()));
    
    // Remove the null terminator (last character with value 0)
    if (numbers.length > 0 && numbers[numbers.length - 1] === 0) {
        numbers.pop();
    }
    
    return String.fromCharCode(...numbers);
}

// Main execution
try {
    console.log('Extracting pdg_main_v24_native array...');
    const arrayData = extractNativeArray();
    
    if (!arrayData) {
        process.exit(1);
    }
    
    console.log('Converting array data to string...');
    const reconstructedContent = arrayToString(arrayData);
    
    // Write the reconstructed content to a temporary file
    fs.writeFileSync('pdg_main_v24_reconstructed.js', reconstructedContent);
    console.log('Reconstructed file written to pdg_main_v24_reconstructed.js');
    
    // Read the original file
    const originalContent = fs.readFileSync('src/bindings/node/pdg_main_v24.js', 'utf8');
    
    // Compare the files
    if (originalContent === reconstructedContent) {
        console.log('✅ Files are identical!');
        console.log(`Both files are ${originalContent.length} characters long`);
    } else {
        console.log('❌ Files are different!');
        console.log(`Original file size: ${originalContent.length} characters`);
        console.log(`Reconstructed file size: ${reconstructedContent.length} characters`);
        
        // Find where they differ
        const minLength = Math.min(originalContent.length, reconstructedContent.length);
        for (let i = 0; i < minLength; i++) {
            if (originalContent[i] !== reconstructedContent[i]) {
                console.log(`First difference at position ${i}:`);
                console.log(`Original: "${originalContent.substring(i, i + 50)}"`);
                console.log(`Reconstructed: "${reconstructedContent.substring(i, i + 50)}"`);
                break;
            }
        }
        
        if (reconstructedContent.length < originalContent.length) {
            console.log(`Reconstructed file is truncated by ${originalContent.length - reconstructedContent.length} characters`);
        } else if (reconstructedContent.length > originalContent.length) {
            console.log(`Reconstructed file is longer by ${reconstructedContent.length - originalContent.length} characters`);
        }
    }
    
    // Also check if the reconstructed file is valid JavaScript
    try {
        require('vm').runInNewContext(reconstructedContent, {}, { filename: 'reconstructed.js' });
        console.log('✅ Reconstructed file is valid JavaScript');
    } catch (error) {
        console.log('❌ Reconstructed file has JavaScript syntax errors:');
        console.log(error.message);
    }
    
} catch (error) {
    console.error('Error:', error.message);
    process.exit(1);
} 