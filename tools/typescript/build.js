#!/usr/bin/env node
'use strict';
const fs = require('fs');
const path = require('path');
const {execFileSync} = require('child_process');
const root = path.resolve(__dirname, '../..');
const output = path.join(root, 'build/typescript');
const packageDir = path.join(output, 'package');
require('./generate').run();
fs.rmSync(path.join(output, 'mvc-app'), {recursive:true, force:true});
execFileSync(process.execPath, [require.resolve('typescript/bin/tsc'), '-p', path.join(root, 'src/typescript/mvc-app')], {stdio:'inherit'});
// This directory is owned entirely by this build. Recreate it to remove stale modules.
fs.rmSync(packageDir, {recursive:true, force:true});
fs.mkdirSync(path.join(packageDir, 'mvc-app'), {recursive:true});
for (const name of ['index.d.ts', 'coverage.json']) fs.copyFileSync(path.join(root, 'types', name), path.join(packageDir, name));
for (const name of fs.readdirSync(path.join(output, 'mvc-app'))) {
    if (!/\.(js|d\.ts)$/.test(name)) continue;
    const source = fs.readFileSync(path.join(output, 'mvc-app', name), 'utf8');
    // Relocate the one engine declaration dependency into the distribution.
    // Runtime code contains no import of this type-only dependency.
    const relocated = name.endsWith('.d.ts')
        ? source.replace(/(['"])\.\.\/\.\.\/\.\.\/types\1/g, '"../index"')
        : source.replace(/^\/\/# sourceMappingURL=.*$/gm, '');
    fs.writeFileSync(path.join(packageDir, 'mvc-app', name), relocated);
}
const coverage = JSON.parse(fs.readFileSync(path.join(root,'types/coverage.json'),'utf8'));
const tooling = require('./package.json');
const dependencies = Object.fromEntries(coverage.typePackages.map(name => {
    const dependency = '@types/' + name;
    if (!tooling.devDependencies[dependency]) throw Error('Unpinned type dependency: ' + dependency);
    return [dependency,tooling.devDependencies[dependency]];
}));
fs.writeFileSync(path.join(packageDir, 'package.json'), JSON.stringify({
    name:'pdg-typescript', version:fs.readFileSync(path.join(root,'VERSION'),'utf8').trim(),
    private:true, description:'PDG opt-in engine declarations and separate TypeScript MVC implementation',
    types:'index.d.ts', license:'MIT', dependencies
}, null, 2) + '\n');
for (const [source, target] of [['LICENSE','LICENSE'],['docs/typescript/README.md','README.md']]) {
    fs.copyFileSync(path.join(root,source), path.join(packageDir,target));
}
console.log('Built TypeScript distribution: ' + packageDir);
