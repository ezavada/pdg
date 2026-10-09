// Server-side test bootstrap only; excluded from browser artifacts.
'use strict';
function opensslExecutable(cp,fs,path){
    if(process.env.OPENSSL)return process.env.OPENSSL;
    if(process.platform==='win32'){
        const git=cp.spawnSync('git',['--exec-path'],{encoding:'utf8'});
        if(!git.error && git.status===0){
            const root=path.resolve(git.stdout.trim(),'../../..');
            for(const relative of ['usr/bin/openssl.exe','ucrt64/bin/openssl.exe','mingw64/bin/openssl.exe']){
                const candidate=path.join(root,relative);
                if(fs.existsSync(candidate))return candidate;
            }
        }
    }
    return 'openssl';
}
exports.create=function(){
    const fs=require('fs'),os=require('os'),path=require('path'),cp=require('child_process'),crypto=require('crypto');
    const directory=fs.mkdtempSync(path.join(process.env.PDG_TEST_TEMP_DIR || os.tmpdir(),'pdg-webtransport-'));
    const certFile=path.join(directory,'cert.pem'),keyFile=path.join(directory,'key.pem');
    cp.execFileSync(opensslExecutable(cp,fs,path),['req','-x509','-newkey','ec','-pkeyopt','ec_paramgen_curve:P-256','-nodes','-keyout',keyFile,'-out',certFile,'-days','14','-subj','/CN=localhost','-addext','subjectAltName=DNS:localhost,IP:127.0.0.1'],{stdio:'ignore'});
    const digest=Array.from(crypto.createHash('sha256').update(new crypto.X509Certificate(fs.readFileSync(certFile)).raw).digest());
    return {tls:{certFile,keyFile},digest,remove:()=>fs.rmSync(directory,{recursive:true,force:true})};
};
