#!/usr/bin/env node

'use strict';

const { spawn } = require('child_process');
const os = require('os');

function availableJobCount() {
  if (typeof os.availableParallelism === 'function') {
    return os.availableParallelism();
  }
  const cpus = os.cpus();
  return Array.isArray(cpus) && cpus.length > 0 ? cpus.length : 1;
}

function defaultJobCount() {
  const jobs = availableJobCount();
  return process.platform === 'win32' ? Math.min(jobs, 8) : jobs;
}

function parseJobCount(value) {
  if (!value) {
    return null;
  }
  if (value === 'max') {
    return availableJobCount();
  }
  const parsed = Number.parseInt(value, 10);
  return Number.isFinite(parsed) && parsed > 0 ? parsed : null;
}

function hasInheritedJobserver() {
  const makeFlags = process.env.MAKEFLAGS || '';
  return /(?:^|\s)--jobserver-(?:auth|fds)=/.test(makeFlags);
}

function inheritedJobCount() {
  const makeFlags = process.env.MAKEFLAGS || '';
  const shortForm = makeFlags.match(/(?:^|\s)-j(\d+)(?=\s|$)/);
  if (shortForm) return parseJobCount(shortForm[1]);
  const longForm = makeFlags.match(/(?:^|\s)--jobs(?:=(\d+)|\s+(\d+))(?=\s|$)/);
  return longForm ? parseJobCount(longForm[1] || longForm[2]) : null;
}

function withoutMakeJobserver(env) {
  const childEnv = { ...env };
  const makeFlags = (childEnv.MAKEFLAGS || '')
      .replace(/(?:^|\s)--jobserver-(?:auth|fds)=\S+/g, ' ')
      .replace(/(?:^|\s)-j\d*(?=\s|$)/g, ' ')
      .replace(/(?:^|\s)--jobs(?:=\d+|\s+\d+)?(?=\s|$)/g, ' ')
      .trim();
  if (makeFlags) childEnv.MAKEFLAGS = makeFlags;
  else delete childEnv.MAKEFLAGS;
  return childEnv;
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

const configuredJobs = parseJobCount(process.env.PDG_NODE_GYP_JOBS) ||
    parseJobCount(process.env.npm_config_jobs);
const makeJobs = inheritedJobCount();
const inheritedJobserver = process.platform !== 'win32' && hasInheritedJobserver();
const jobs = configuredJobs || makeJobs || defaultJobCount();
const nodeGyp = resolveNodeGypCommand();
const args = nodeGyp.args.concat(['rebuild', '--jobs', String(jobs)]);
if (process.env.PDG_NODE_BUILD_CONFIG === 'Release') args.push('--release');
else if (process.env.PDG_NODE_BUILD_CONFIG === 'Debug') args.push('--debug');

const parallelism = !configuredJobs && makeJobs ?
    `${jobs} parallel job(s) inherited from GNU make` : `${jobs} parallel job(s)`;
console.log(`[pdg] Building native module with node-gyp using ${parallelism}...`);
console.log(`[pdg] Working directory: ${process.cwd()}`);

const start = Date.now();
const child = spawn(nodeGyp.command, args, {
  stdio: 'inherit',
  env: inheritedJobserver ? withoutMakeJobserver(process.env) : process.env,
  shell: nodeGyp.useShell,
});

const heartbeat = setInterval(() => {
  const elapsedSeconds = Math.floor((Date.now() - start) / 1000);
  console.log(`[pdg] Native build still running after ${elapsedSeconds}s using ${parallelism}...`);
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
