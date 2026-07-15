#!/usr/bin/env node
// -----------------------------------------------
// run_lanes.js
//
// Shared CLI for platform test lane definitions.
// Writes per-lane result snapshots into artifacts/test-results.
// -----------------------------------------------

var childProcess = require('child_process');
var fs = require('fs');
var path = require('path');

var repoRoot = path.resolve(__dirname, '..');
var manifestPath = path.join(__dirname, 'lanes.json');
var resultsIndexPath = path.join(repoRoot, 'artifacts', 'test-results', 'lanes', 'latest-results.json');

function ensureDir(dirPath) {
    if (!fs.existsSync(dirPath)) {
        fs.mkdirSync(dirPath, { recursive: true });
    }
}

function sanitizeSegment(value, fallbackValue) {
    var text = String(value || fallbackValue || '');
    text = text.toLowerCase().replace(/[^a-z0-9._-]+/g, '-').replace(/^-+|-+$/g, '');
    return text || fallbackValue || 'unknown';
}

function loadManifest() {
    return JSON.parse(fs.readFileSync(manifestPath, 'utf8'));
}

function readIndex() {
    if (!fs.existsSync(resultsIndexPath)) {
        return { lanes: {} };
    }
    try {
        return JSON.parse(fs.readFileSync(resultsIndexPath, 'utf8'));
    } catch (e) {
        return { lanes: {} };
    }
}

function writeIndex(indexData) {
    var manifest = loadManifest();
    var allowedLaneIds = {};
    manifest.lanes.forEach(function(lane) {
        allowedLaneIds[lane.id] = true;
    });

    Object.keys(indexData.lanes || {}).forEach(function(laneId) {
        if (!allowedLaneIds[laneId]) {
            delete indexData.lanes[laneId];
        }
    });

    ensureDir(path.dirname(resultsIndexPath));
    fs.writeFileSync(resultsIndexPath, JSON.stringify(indexData, null, 2) + '\n', 'utf8');
}

function findLane(manifest, laneId) {
    for (var i = 0; i < manifest.lanes.length; i++) {
        if (manifest.lanes[i].id === laneId) {
            return manifest.lanes[i];
        }
    }
    return null;
}

function platformLabel(platformName) {
    if (platformName === 'win32') {
        return 'Windows';
    }
    if (platformName === 'linux') {
        return 'Linux';
    }
    if (platformName === 'darwin') {
        return 'macOS';
    }
    return platformName;
}

function toWslPath(winPath) {
    var normalized = path.resolve(winPath).replace(/\\/g, '/');
    var driveMatch = /^([A-Za-z]):(.*)$/.exec(normalized);
    if (!driveMatch) {
        return normalized;
    }
    return '/mnt/' + driveMatch[1].toLowerCase() + driveMatch[2];
}

function createMismatchHint(lane) {
    if (process.platform === 'win32' && lane.targetPlatform === 'linux') {
        return 'Run inside WSL: cd ' + toWslPath(repoRoot) + ' && ./test/lanes run ' + lane.id;
    }
    if (process.platform === 'win32' && lane.targetPlatform === 'darwin') {
        return 'Run on the Mac checkout: ./test/lanes run ' + lane.id;
    }
    return 'Run this lane on a ' + platformLabel(lane.targetPlatform) + ' host.';
}

function laneArtifactsDir(lane) {
    return path.join(repoRoot, 'artifacts', 'test-results', lane.targetPlatform, 'lanes', sanitizeSegment(lane.id, 'lane'));
}

function createBaseResult(lane, status) {
    return {
        laneId: lane.id,
        laneName: lane.name,
        category: lane.category,
        targetPlatform: lane.targetPlatform,
        hostPlatform: process.platform,
        automation: lane.automation,
        status: status,
        startedAt: new Date().toISOString(),
        notes: lane.notes || [],
        checklist: lane.checklist || [],
        warnings: [],
        steps: []
    };
}

function resolveRepoPath(targetPath) {
    if (!targetPath) {
        return repoRoot;
    }
    if (path.isAbsolute(targetPath)) {
        return targetPath;
    }
    return path.resolve(repoRoot, targetPath);
}

function relativeToRepo(targetPath) {
    var resolvedPath = resolveRepoPath(targetPath);
    var relativePath = path.relative(repoRoot, resolvedPath);
    return relativePath || '.';
}

function pathExists(targetPath) {
    try {
        return fs.existsSync(resolveRepoPath(targetPath));
    } catch (e) {
        return false;
    }
}

function latestEntryForPath(targetPath) {
    var resolvedPath = resolveRepoPath(targetPath);
    if (!fs.existsSync(resolvedPath)) {
        return null;
    }

    var stat = fs.statSync(resolvedPath);
    var latest = {
        path: resolvedPath,
        mtimeMs: stat.mtimeMs
    };

    if (!stat.isDirectory()) {
        return latest;
    }

    fs.readdirSync(resolvedPath).forEach(function(entryName) {
        var childLatest = latestEntryForPath(path.join(resolvedPath, entryName));
        if (childLatest && childLatest.mtimeMs > latest.mtimeMs) {
            latest = childLatest;
        }
    });

    return latest;
}

function collectLaneBuildChecks(lane) {
    var checks = lane.requiredBuilds || [];
    var missing = [];
    var stale = [];
    var warnings = [];

    checks.forEach(function(check) {
        var requiredPaths = (check.paths || []).map(resolveRepoPath);
        var missingPaths = requiredPaths.filter(function(requiredPath) {
            return !fs.existsSync(requiredPath);
        });

        if (missingPaths.length > 0) {
            missing.push({
                label: check.label || 'Required build',
                missingPaths: missingPaths.map(function(requiredPath) {
                    return path.relative(repoRoot, requiredPath) || requiredPath;
                }),
                buildCommands: check.buildCommands || []
            });
            return;
        }

        var freshnessTarget = check.freshnessPath || check.paths && check.paths[0];
        var staleInputs = check.staleInputs || [];
        if (!freshnessTarget || staleInputs.length === 0) {
            return;
        }

        var buildEntry = latestEntryForPath(freshnessTarget);
        if (!buildEntry) {
            return;
        }

        var newestInput = null;
        staleInputs.forEach(function(staleInput) {
            var inputEntry = latestEntryForPath(staleInput);
            if (inputEntry && (!newestInput || inputEntry.mtimeMs > newestInput.mtimeMs)) {
                newestInput = inputEntry;
            }
        });

        if (newestInput && newestInput.mtimeMs > buildEntry.mtimeMs) {
            var staleWarning = {
                label: check.label || 'Required build',
                message: (check.label || 'Required build') + ' may be out of date: ' + relativeToRepo(newestInput.path) + ' is newer than ' + relativeToRepo(buildEntry.path) + '.',
                buildCommands: check.buildCommands || []
            };
            stale.push(staleWarning);
            warnings.push(staleWarning.message);
        }
    });

    return {
        missing: missing,
        stale: stale,
        warnings: warnings
    };
}

function printMissingBuildHelp(lane, missingChecks) {
    var buildCommands = [];
    console.log('BLOCKED: ' + lane.id);
    console.log('  Missing required build artifacts.');
    missingChecks.forEach(function(check) {
        console.log('  ' + check.label + ': ' + check.missingPaths.join(', '));
        (check.buildCommands || []).forEach(function(buildCommand) {
            if (buildCommands.indexOf(buildCommand) === -1) {
                buildCommands.push(buildCommand);
            }
        });
    });
    if (buildCommands.length > 0) {
        console.log('  Build commands:');
        buildCommands.forEach(function(buildCommand) {
            console.log('    ' + buildCommand);
        });
    }
}

function printStaleBuildWarnings(staleChecks) {
    staleChecks.forEach(function(check) {
        console.log('  WARNING: ' + check.message);
        if (check.buildCommands && check.buildCommands.length > 0) {
            console.log('    Rebuild commands:');
            check.buildCommands.forEach(function(buildCommand) {
                console.log('      ' + buildCommand);
            });
        }
    });
}

function finishResult(lane, result) {
    result.endedAt = new Date().toISOString();
    var laneDir = laneArtifactsDir(lane);
    ensureDir(laneDir);
    var latestPath = path.join(laneDir, 'latest.json');
    fs.writeFileSync(latestPath, JSON.stringify(result, null, 2) + '\n', 'utf8');

    var indexData = readIndex();
    indexData.generatedAt = result.endedAt;
    indexData.lanes[lane.id] = {
        laneId: lane.id,
        laneName: lane.name,
        targetPlatform: lane.targetPlatform,
        category: lane.category,
        automation: lane.automation,
        status: result.status,
        endedAt: result.endedAt,
        resultPath: latestPath
    };
    writeIndex(indexData);
    return latestPath;
}

function printHelp() {
    console.log('Usage: test/lanes <command> [options]\n');
    console.log('Commands:');
    console.log('  list');
    console.log('      Show the configured test lanes.');
    console.log('  run <lane-id>');
    console.log('      Run an automated lane or emit a checklist for a manual lane.');
    console.log('  record <lane-id> <passed|failed|blocked|manual> [note]');
    console.log('      Store a manual or external result for a lane.');
}

function printLaneList(manifest) {
    var indexData = readIndex();
    console.log('Configured PDG platform lanes:\n');
    manifest.lanes.forEach(function(lane) {
        var latest = indexData.lanes[lane.id];
        var currentPlatformMark = lane.targetPlatform === process.platform ? '*' : ' ';
        var latestStatus = latest ? latest.status : 'not-run';
        console.log(currentPlatformMark + ' ' + lane.id + ' [' + lane.category + ', ' + lane.automation + ', ' + platformLabel(lane.targetPlatform) + '] - ' + latestStatus);
        console.log('    ' + lane.name);
    });
    console.log('\n* matches the current host platform');
}

function writeStepLogs(stepDir, stepName, stdoutText, stderrText) {
    var stepSlug = sanitizeSegment(stepName, 'step');
    var stdoutPath = path.join(stepDir, stepSlug + '.stdout.log');
    var stderrPath = path.join(stepDir, stepSlug + '.stderr.log');
    fs.writeFileSync(stdoutPath, stdoutText || '', 'utf8');
    fs.writeFileSync(stderrPath, stderrText || '', 'utf8');
    return {
        stdoutPath: stdoutPath,
        stderrPath: stderrPath
    };
}

function runLane(lane) {
    var result;
    var latestPath;
    if (lane.targetPlatform !== process.platform) {
        result = createBaseResult(lane, 'blocked');
        result.blockedReason = 'Lane target platform does not match the current host.';
        result.runHint = createMismatchHint(lane);
        latestPath = finishResult(lane, result);
        console.log('BLOCKED: ' + lane.id);
        console.log('  ' + result.blockedReason);
        console.log('  ' + result.runHint);
        console.log('  Result: ' + latestPath);
        return 1;
    }

    var buildChecks = collectLaneBuildChecks(lane);
    if (buildChecks.missing.length > 0) {
        result = createBaseResult(lane, 'blocked');
        result.blockedReason = 'Missing required build artifacts.';
        result.missingBuilds = buildChecks.missing;
        result.buildCommands = [];
        buildChecks.missing.forEach(function(check) {
            (check.buildCommands || []).forEach(function(buildCommand) {
                if (result.buildCommands.indexOf(buildCommand) === -1) {
                    result.buildCommands.push(buildCommand);
                }
            });
        });
        latestPath = finishResult(lane, result);
        printMissingBuildHelp(lane, buildChecks.missing);
        console.log('  Result: ' + latestPath);
        return 1;
    }

    if (lane.automation !== 'automated') {
        result = createBaseResult(lane, 'manual');
        result.warnings = buildChecks.warnings.slice();
        result.staleBuilds = buildChecks.stale.slice();
        result.runHint = 'Use the checklist below, then record the outcome with: test/lanes record ' + lane.id + ' passed "notes"';
        latestPath = finishResult(lane, result);
        console.log('MANUAL: ' + lane.id);
        printStaleBuildWarnings(buildChecks.stale);
        lane.checklist.forEach(function(item, index) {
            console.log('  ' + (index + 1) + '. ' + item);
        });
        console.log('  ' + result.runHint);
        console.log('  Result: ' + latestPath);
        return 0;
    }

    result = createBaseResult(lane, 'passed');
    result.warnings = buildChecks.warnings.slice();
    result.staleBuilds = buildChecks.stale.slice();
    var laneDir = laneArtifactsDir(lane);
    var stepDir = path.join(laneDir, 'steps');
    ensureDir(stepDir);

    console.log('Running lane: ' + lane.id);
    printStaleBuildWarnings(buildChecks.stale);
    lane.steps.forEach(function(step, index) {
        if (result.status === 'failed' && lane.stopOnFailure !== false) {
            return;
        }

        console.log('  [' + (index + 1) + '/' + lane.steps.length + '] ' + step.name);
        var startedAt = new Date().toISOString();
        var execResult = childProcess.spawnSync(step.command, {
            cwd: repoRoot,
            shell: true,
            encoding: 'utf8',
            stdio: ['ignore', 'pipe', 'pipe']
        });

        var stdoutText = execResult.stdout || '';
        var stderrText = execResult.stderr || '';
        var logPaths = writeStepLogs(stepDir, String(index + 1) + '-' + step.name, stdoutText, stderrText);
        var exitCode = typeof execResult.status === 'number' ? execResult.status : 1;
        var stepStatus = exitCode === 0 && !execResult.error ? 'passed' : 'failed';

        result.steps.push({
            name: step.name,
            command: step.command,
            startedAt: startedAt,
            endedAt: new Date().toISOString(),
            status: stepStatus,
            exitCode: exitCode,
            stdoutLog: logPaths.stdoutPath,
            stderrLog: logPaths.stderrPath,
            error: execResult.error ? String(execResult.error.message || execResult.error) : null
        });

        if (stdoutText) {
            process.stdout.write(stdoutText);
        }
        if (stderrText) {
            process.stderr.write(stderrText);
        }

        if (stepStatus !== 'passed') {
            result.status = 'failed';
        }
    });

    latestPath = finishResult(lane, result);
    console.log((result.status === 'passed' ? 'PASS' : 'FAIL') + ': ' + lane.id);
    console.log('  Result: ' + latestPath);
    return result.status === 'passed' ? 0 : 1;
}

function recordLane(lane, status, note) {
    var validStatuses = {
        passed: true,
        failed: true,
        blocked: true,
        manual: true
    };
    if (!validStatuses[status]) {
        console.error('Invalid status: ' + status);
        return 1;
    }

    var result = createBaseResult(lane, status);
    result.recorded = true;
    result.recordedNote = note || '';
    result.runHint = lane.targetPlatform !== process.platform ? createMismatchHint(lane) : '';
    var latestPath = finishResult(lane, result);
    console.log('Recorded ' + status + ' for ' + lane.id);
    console.log('  Result: ' + latestPath);
    return 0;
}

function main() {
    var manifest = loadManifest();
    var args = process.argv.slice(2);
    var command = args.shift() || 'list';

    if (command === 'list') {
        printLaneList(manifest);
        return 0;
    }

    if (command === 'run') {
        var laneId = args.shift();
        if (!laneId) {
            printHelp();
            return 1;
        }
        var lane = findLane(manifest, laneId);
        if (!lane) {
            console.error('Unknown lane: ' + laneId);
            return 1;
        }
        return runLane(lane);
    }

    if (command === 'record') {
        var recordLaneId = args.shift();
        var status = args.shift();
        if (!recordLaneId || !status) {
            printHelp();
            return 1;
        }
        var recordLaneDef = findLane(manifest, recordLaneId);
        if (!recordLaneDef) {
            console.error('Unknown lane: ' + recordLaneId);
            return 1;
        }
        return recordLane(recordLaneDef, status, args.join(' '));
    }

    printHelp();
    return 1;
}

process.exit(main());
