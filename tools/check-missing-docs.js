#!/usr/bin/env node

/**
 * check-missing-docs.js
 * 
 * Tool to analyze the JavaScript API from pdg-js.json and compare it against
 * existing dox files to identify missing documentation.
 * 
 * Usage: node check-missing-docs.js [options]
 *   --classes    Check for missing class documentation
 *   --methods    Check for missing method documentation for a specific class
 *   --class NAME Check methods for specific class (use with --methods)
 *   --all        Check both classes and all methods
 */

const fs = require('fs');
const path = require('path');

// Configuration
const PDG_JS_JSON = path.join(__dirname, '..', 'docs', 'javascript', 'pdg-js.json');
const DOX_DIR = path.join(__dirname, '..', 'docs', 'javascript', 'dox');

/**
 * Load and parse the pdg-js.json file
 */
function loadPDGInterface() {
    if (!fs.existsSync(PDG_JS_JSON)) {
        console.error(`Error: ${PDG_JS_JSON} not found`);
        process.exit(1);
    }
    
    const content = fs.readFileSync(PDG_JS_JSON, 'utf8');
    return JSON.parse(content);
}

/**
 * Get all existing dox files
 */
function getExistingDoxFiles() {
    if (!fs.existsSync(DOX_DIR)) {
        console.error(`Error: ${DOX_DIR} not found`);
        process.exit(1);
    }
    
    const files = fs.readdirSync(DOX_DIR);
    return files.filter(file => file.endsWith('.dox'));
}

/**
 * Convert a class name to the expected dox filename format
 */
function classToDoxFilename(className) {
    // Convert to lowercase and insert underscores before capital letters (except the first)
    let result = '';
    for (let i = 0; i < className.length; i++) {
        const char = className[i];
        if (i > 0 && char >= 'A' && char <= 'Z') {
            result += '_';
        }
        result += char.toLowerCase();
    }
    
    return `classpdg_1_1_${result}.dox`;
}

/**
 * Convert a method name to the expected dox filename format
 * Based on funcPrototypeToMangledName() from Markdown.DoxyEditor.js
 */
function methodToDoxFilename(className, methodName, params = []) {
    // Convert class name to lowercase with underscores
    let classNormalized = '';
    for (let i = 0; i < className.length; i++) {
        const char = className[i];
        if (i > 0 && char >= 'A' && char <= 'Z') {
            classNormalized += '_';
        }
        classNormalized += char.toLowerCase();
    }
    
    const methodNormalized = methodName.toLowerCase();
    
    // Handle overloaded methods - params can be an array of parameter arrays
    if (params && params.length > 0 && Array.isArray(params[0])) {
        // This is an overloaded method with multiple parameter signatures
        return params.map(overloadParams => {
            const paramSig = createParameterSignature(overloadParams);
            return `classpdg_1_1_${classNormalized}-${methodNormalized}${paramSig}.dox`;
        });
    } else {
        // Single method signature
        const paramSig = createParameterSignature(params);
        return `classpdg_1_1_${classNormalized}-${methodNormalized}${paramSig}.dox`;
    }
}

/**
 * Create parameter signature for a single method overload
 */
function createParameterSignature(params) {
    if (!params || params.length === 0) {
        return '-x';  // No parameters
    }
    
    // Build parameter string like the original function does
    let paramString = params.map(p => {
        if (p.type && p.type.includes('object')) {
            // Extract class name from "object ClassName"
            const match = p.type.match(/object\s+(\w+)/);
            if (match) {
                const typeName = match[1].toLowerCase();
                // Map known types to their abbreviations (from funcPrototypeToMangledName)
                if (typeName === 'rect') return ' rect ';
                if (typeName === 'point') return ' point ';
                if (typeName === 'vector') return ' vector ';
                if (typeName === 'quad') return ' quad ';
                if (typeName === 'color') return ' color ';
                if (typeName === 'offset') return ' offset ';
                if (typeName === 'image') return ' image ';
                if (typeName === 'spline') return ' spline ';
                if (typeName === 'polygon') return ' polygon ';
                if (typeName === 'attributes') return ' attributes ';
                if (typeName === 'font') return ' font ';
                if (typeName === 'sprite') return ' sprite ';
                if (typeName === 'spritelayer') return ' spritelayer ';
                if (typeName === 'serializer') return ' serializer ';
                if (typeName === 'deserializer') return ' deserializer ';
                if (typeName === 'ieventhandler') return ' ieventhandler ';
                if (typeName === 'ianimationhelper') return ' ianimationhelper ';
                // For unknown object types, wrap in underscores
                return ` ${typeName} `;
            }
        }
        if (p.type === 'number') return ' number ';
        if (p.type === 'number int') return ' int ';
        if (p.type === 'number uint') return ' uint ';
        if (p.type === 'number float') return ' number ';
        if (p.type === 'string') return ' string ';
        if (p.type === 'boolean') return ' boolean ';
        if (p.type === 'function') return ' function ';
        if (p.type === 'string Binary') return ' binarystring ';
        if (p.type === 'object MemBlock') return ' memblock ';
        if (p.type === 'object') return ' object ';
        if (p.type === 'undefined') return ' undefined ';
        return ' undefined ';
    }).join('');
    
    // Apply the same transformations as funcPrototypeToMangledName
    paramString = paramString.replace(/ boolean /g, ' b ');
    paramString = paramString.replace(/ color /g, ' c ');
    paramString = paramString.replace(/ offset /g, ' d ');
    paramString = paramString.replace(/ function /g, ' f ');
    paramString = paramString.replace(/ int /g, ' i ');
    paramString = paramString.replace(/ number /g, ' n ');
    paramString = paramString.replace(/ object /g, ' o ');
    paramString = paramString.replace(/ point /g, ' p ');
    paramString = paramString.replace(/ quad /g, ' q ');
    paramString = paramString.replace(/ rect /g, ' r ');
    paramString = paramString.replace(/ string /g, ' s ');
    paramString = paramString.replace(/ uint /g, ' u ');
    paramString = paramString.replace(/ vector /g, ' v ');
    paramString = paramString.replace(/ binarystring /g, ' 1 ');
    paramString = paramString.replace(/ memblock /g, ' m ');
    paramString = paramString.replace(/ buffer /g, ' 8 ');
    paramString = paramString.replace(/ (\S\S+) /g, ' _$1_ '); // Wrap unknown types in underscores
    paramString = paramString.replace(/ /g, ''); // Remove all spaces
    
    return '-' + paramString;
}

/**
 * Check for missing class documentation
 */
function checkMissingClasses(interface, existingDoxFiles, createMode = false) {
    console.log('=== MISSING CLASS DOCUMENTATION ===\n');
    
    const classes = interface.interface.filter(item => item.type === 'class');
    const missing = [];
    
    // Use pdg-js.json as the authority - check all classes defined in the interface
    for (const cls of classes) {
        const expectedDoxFile = classToDoxFilename(cls.name);
        const hasDox = existingDoxFiles.includes(expectedDoxFile);
        
        
        if (!hasDox) {
            missing.push({
                className: cls.name,
                expectedDoxFile: expectedDoxFile
            });
            
            if (createMode) {
                const filePath = `${__dirname}/../docs/javascript/dox/${expectedDoxFile}`;
                createDoxFile(filePath, cls.name, null, null, null);
            }
        }
    }
    
    if (missing.length === 0) {
        console.log('✅ All exposed classes have documentation files');
    } else {
        console.log(`❌ ${missing.length} exposed classes missing documentation:\n`);
        missing.forEach(item => {
            console.log(`Class: ${item.className}`);
            console.log(`Missing: ${item.expectedDoxFile}\n`);
        });
    }
    
    return missing;
}

/**
 * Check for missing method documentation for a specific class
 */
function checkMissingMethods(className, interface, existingDoxFiles, createMode = false) {
    console.log(`=== MISSING METHOD DOCUMENTATION FOR ${className} ===\n`);
    
    const cls = interface.interface.find(item => 
        item.type === 'class' && item.name === className
    );
    
    if (!cls) {
        console.error(`❌ Class ${className} not found in interface`);
        return [];
    }
    
    const methods = cls.interface.filter(item => 
        item.type === 'function' && !item.inherited_from
    );
    const missing = [];
    
    for (const method of methods) {
        const expectedDoxFiles = methodToDoxFilename(className, method.name, method.params);
        
        // Handle both single filename and array of filenames (for overloaded methods)
        const doxFiles = Array.isArray(expectedDoxFiles) ? expectedDoxFiles : [expectedDoxFiles];
        
        for (let i = 0; i < doxFiles.length; i++) {
            const expectedDoxFile = doxFiles[i];
            const hasDox = existingDoxFiles.includes(expectedDoxFile);
            
            if (!hasDox) {
                // For overloaded methods, get the specific parameter set for this overload
                let methodParams = method.params || [];
                if (Array.isArray(methodParams) && methodParams.length > 0 && Array.isArray(methodParams[0])) {
                    methodParams = methodParams[i] || [];
                }
                
                missing.push({
                    className: className,
                    methodName: method.name,
                    expectedDoxFile: expectedDoxFile,
                    returns: method.returns || 'void',
                    params: methodParams,
                    overloadIndex: doxFiles.length > 1 ? i : undefined
                });
                
                if (createMode) {
                    const filePath = `${__dirname}/../docs/javascript/dox/${expectedDoxFile}`;
                    createDoxFile(filePath, className, method.name, method, methodParams);
                }
            }
        }
    }
    
    if (missing.length === 0) {
        console.log(`✅ All methods for ${className} have documentation files`);
    } else {
        console.log(`❌ ${missing.length} methods missing documentation for ${className}:\n`);
        missing.forEach(item => {
            const overloadInfo = item.overloadIndex !== undefined ? ` (overload ${item.overloadIndex + 1})` : '';
            console.log(`Method: ${item.className}.${item.methodName}${overloadInfo}`);
            console.log(`Returns: ${item.returns}`);
            if (item.params.length > 0) {
                console.log(`Params: ${item.params.map(p => `${p.name}: ${p.type}`).join(', ')}`);
            }
            console.log(`Missing: ${item.expectedDoxFile}\n`);
        });
    }
    
    return missing;
}

/**
 * Check for missing method documentation for all classes
 */
function checkAllMissingMethods(interface, existingDoxFiles, createMode = false) {
    console.log('=== MISSING METHOD DOCUMENTATION FOR ALL CLASSES ===\n');
    
    const classes = interface.interface.filter(item => item.type === 'class');
    const allMissing = [];
    
    for (const cls of classes) {
        const missing = checkMissingMethods(cls.name, interface, existingDoxFiles, createMode);
        allMissing.push(...missing);
        
        if (missing.length > 0) {
            console.log('---\n');
        }
    }
    
    if (allMissing.length === 0) {
        console.log('✅ All methods for all classes have documentation files');
    } else {
        console.log(`\n📊 SUMMARY: ${allMissing.length} total methods missing documentation`);
    }
    
    return allMissing;
}

/**
 * Create a dox file with the specified template
 */
function createDoxFile(filePath, className, methodName, method, params) {
    const fs = require('fs');
    
    let template;
    if (method) {
        // Method template
        const paramList = params.map(p => {
            // Extract the last word from the type (e.g., "number int" -> "int", "object Color" -> "Color")
            // Special case for "string Binary" -> "BinaryString"
            let typeName;
            if (p.type === 'string Binary') {
                typeName = 'BinaryString';
            } else {
                const typeWords = p.type.split(' ');
                typeName = typeWords[typeWords.length - 1];
            }
            return `${typeName} ${p.name}`;
        }).join(', ');
        const brief = method.brief || 'TODO: Add brief description';
        
        template = `namespace pdg { /**

\\fn pdg::${className}::${methodName}(${paramList})

\\brief ${brief}

**/ }`;
    } else {
        // Class template
        template = `namespace pdg { /**

\\class pdg::${className}

\\brief TODO: Add brief description for ${className} class

**/ }`;
    }
    
    try {
        fs.writeFileSync(filePath, template);
        console.log(`✅ Created: ${filePath}`);
        return true;
    } catch (error) {
        console.error(`❌ Failed to create ${filePath}: ${error.message}`);
        return false;
    }
}

/**
 * Main function
 */
function main() {
    const args = process.argv.slice(2);
    
    if (args.length === 0) {
        console.log('Usage: node check-missing-docs.js [options]');
        console.log('  --classes           Check for missing class documentation');
        console.log('  --methods           Check for missing method documentation');
        console.log('  --class NAME        Check methods for specific class (use with --methods)');
        console.log('  --all               Check both classes and all methods');
        console.log('  --create            Create missing dox files with templates');
        console.log('');
        console.log('Examples:');
        console.log('  node check-missing-docs.js --classes');
        console.log('  node check-missing-docs.js --methods --class Port');
        console.log('  node check-missing-docs.js --all');
        console.log('  node check-missing-docs.js --methods --class Port --create');
        return;
    }
    
    console.log('Loading PDG JavaScript interface...');
    const interface = loadPDGInterface();
    
    console.log('Scanning existing dox files...');
    const existingDoxFiles = getExistingDoxFiles();
    
    console.log(`Found ${interface.interface.filter(i => i.type === 'class').length} classes in interface`);
    console.log(`Found ${existingDoxFiles.length} existing dox files\n`);
    
    const checkClasses = args.includes('--classes') || args.includes('--all');
    const checkMethods = args.includes('--methods') || args.includes('--all');
    const createMode = args.includes('--create');
    const specificClass = args.includes('--class') ? args[args.indexOf('--class') + 1] : null;
    
    if (checkClasses) {
        checkMissingClasses(interface, existingDoxFiles, createMode);
        console.log('');
    }
    
    if (checkMethods) {
        if (specificClass) {
            checkMissingMethods(specificClass, interface, existingDoxFiles, createMode);
        } else {
            checkAllMissingMethods(interface, existingDoxFiles, createMode);
        }
    }
}

if (require.main === module) {
    main();
}

module.exports = {
    loadPDGInterface,
    getExistingDoxFiles,
    classToDoxFilename,
    methodToDoxFilename,
    createDoxFile,
    checkMissingClasses,
    checkMissingMethods,
    checkAllMissingMethods
};
