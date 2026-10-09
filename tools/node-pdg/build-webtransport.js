'use strict';
// Included in the npm source package; builds its pinned native backend first.
const fs=require('fs'),path=require('path'),cp=require('child_process');
exports.build=function(jobs){
    const root=process.cwd(),build=path.join(root,'webtransport-build');
    const configuration=process.env.PDG_NODE_BUILD_CONFIG==='Debug'?'Debug':'Release';
    const args=['-S',path.join(root,'src','sys','webtransport'),'-B',build,'-DCMAKE_BUILD_TYPE='+configuration];
    if(process.platform==='darwin')args.push(
        '-DCMAKE_OSX_ARCHITECTURES='+({x64:'x86_64',arm64:'arm64'}[process.arch] || process.arch),
        // Match Node 24's addon deployment target instead of the build host OS.
        '-DCMAKE_OSX_DEPLOYMENT_TARGET='+(process.env.MACOSX_DEPLOYMENT_TARGET || '13.5'));
    if(process.platform==='win32'){
        const arch={x64:'x64',ia32:'Win32',arm64:'ARM64'}[process.env.npm_config_arch || process.arch];
        if(!arch)throw Error('Unsupported Windows Node architecture');
        args.push('-G','Visual Studio 17 2022','-A',arch,'-DCMAKE_MSVC_RUNTIME_LIBRARY='+
            (configuration==='Debug'?'MultiThreadedDebug':'MultiThreaded'));
    }
    if(process.env.PDG_WEBTRANSPORT_SOURCES)for(const name of ['picoquic','picotls','mbedtls','cjson'])args.push('-DFETCHCONTENT_SOURCE_DIR_'+name.toUpperCase()+'='+path.join(process.env.PDG_WEBTRANSPORT_SOURCES,name));
    const cmake=process.env.CMAKE || 'cmake';
    for(const buildArguments of [args,['--build',build,'--config',configuration,'--target','pdg_webtransport_bundle','--parallel',String(jobs)]]){
        const result=cp.spawnSync(cmake,buildArguments,{stdio:'inherit'});
        if(result.error)throw result.error;
        if(result.status!==0)throw Error('Native WebTransport build failed ('+result.status+')');
    }
    const notices=path.join(root,'src','sys','webtransport','THIRD_PARTY_NOTICES.txt');
    fs.copyFileSync(notices,path.join(root,'WebTransport-Licenses.txt'));
};
