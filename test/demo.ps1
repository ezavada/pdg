# Pass arguments unchanged, including --flags, to the shared runner.
$ErrorActionPreference = 'Stop'
$testRoot = Split-Path -Parent $PSScriptRoot
$testNode = $env:PDG_NODE
if (-not $testNode) {
    $testNode = Join-Path $testRoot 'tools/node.exe'
    if (-not (Test-Path $testNode)) { $testNode = Join-Path $testRoot 'tools/node' }
    if (-not (Test-Path $testNode)) { $testNode = 'node' }
}
& $testNode (Join-Path $PSScriptRoot 'lib/test_runner.js') 'demo' @args
exit $LASTEXITCODE
