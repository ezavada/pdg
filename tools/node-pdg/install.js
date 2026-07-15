#!/usr/bin/env node

'use strict';

const { spawn } = require('child_process');
const os = require('os');

function defaultJobCount() {
  if (typeof os.availableParallelism === 'function') {
    return os.availableParallelism();
  }
  const cpus = os.cpus();
  return Array.isArray(cpus) && cpus.length > 0 ? cpus.length : 1;
}

function parseJobCount(value) {
  if (!value) {
    return null;
  }
  if (value === 'max') {
    return defaultJobCount();
  }
  const parsed = Number.parseInt(value, 10);
  return Number.isFinite(parsed) && parsed > 0 ? parsed : null;
}

function resolveNodeGypCommand() {
  const configuredNodeGyp = process.env.npm_config_node_gyp;
  if (configuredNodeGyp && /\.(?:[cm]?js)$/i.test(configuredNodeGyp)) {
    return {
      command: process.execPath,
      args: [configuredNodeGyp],
      useShell: false,
    };
  }
  if (configuredNodeGyp) {
    return {
      command: configuredNodeGyp,
      args: [],
      useShell: process.platform === 'win32' && /\.(cmd|bat)$/i.test(configuredNodeGyp),
    };
  }
  return {
    command: process.platform === 'win32' ? 'node-gyp.cmd' : 'node-gyp',
    args: [],
    useShell: process.platform === 'win32',
  };
}

const jobs = parseJobCount(process.env.PDG_NODE_GYP_JOBS) ||
    parseJobCount(process.env.npm_config_jobs) ||
    defaultJobCount();
const nodeGyp = resolveNodeGypCommand();
const args = nodeGyp.args.concat(['rebuild', '--jobs', String(jobs)]);

console.log(`[pdg] Building native module with node-gyp using ${jobs} parallel job(s)...`);
console.log(`[pdg] Working directory: ${process.cwd()}`);

const start = Date.now();
const child = spawn(nodeGyp.command, args, {
  stdio: 'inherit',
  env: process.env,
  shell: nodeGyp.useShell,
});

const heartbeat = setInterval(() => {
  const elapsedSeconds = Math.floor((Date.now() - start) / 1000);
  console.log(`[pdg] Native build still running after ${elapsedSeconds}s with ${jobs} job(s)...`);
}, 30000);

child.on('error', (error) => {
  clearInterval(heartbeat);
  console.error(`[pdg] Failed to launch node-gyp: ${error.message}`);
  process.exit(1);
});

child.on('exit', (code, signal) => {
  clearInterval(heartbeat);
  if (signal) {
    console.error(`[pdg] node-gyp exited from signal ${signal}.`);
    process.exit(1);
  }
  process.exit(code === null ? 1 : code);
});
