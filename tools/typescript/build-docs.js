#!/usr/bin/env node
'use strict';
const path = require('path');
const fs = require('fs');
const {execFileSync} = require('child_process');
const root = path.resolve(__dirname,'../..');
async function main() {
    require('./generate').run(true);
    execFileSync(process.execPath,[require.resolve('typescript/bin/tsc'),'-p',path.join(root,'src/typescript/mvc-app'),'--noEmit'],{stdio:'inherit'});
    const {Application} = await import('typedoc');
    const output = process.argv[2] ? path.resolve(process.argv[2]) : path.join(root,'docs/typescript/html');
    const app = await Application.bootstrapWithPlugins({
        name:'PDG TypeScript',
        entryPoints:[path.join(root,'types/index.d.ts'),path.join(root,'src/typescript/mvc-app/index.ts')],
        tsconfig:path.join(root,'src/typescript/mvc-app/tsconfig.json'),
        readme:path.join(root,'docs/typescript/README.md'),
        excludePrivate:true, excludeProtected:true, disableSources:true,
        includeVersion:false, sort:['source-order'],
        validation:{notExported:false,invalidLink:true,notDocumented:false},
        out:output
    });
    const project = await app.convert();
    if (!project) throw Error('TypeDoc conversion failed');
    app.validate(project);
    if (app.logger.hasErrors() || app.logger.hasWarnings()) throw Error('TypeDoc validation failed');
    // Recreate the generated reference so removed pages and copied assets cannot survive.
    fs.rmSync(output,{recursive:true,force:true});
    await app.generateDocs(project,output);
    if (!fs.existsSync(path.join(output,'index.html'))) throw Error('TypeDoc entry page is missing');
    fs.cpSync(path.join(root,'docs/typescript/examples'),path.join(output,'examples'),{recursive:true});
    console.log('TypeScript reference: '+path.join(output,'index.html'));
}
main().catch(error=>{console.error(error);process.exitCode=1;});
