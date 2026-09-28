# Convenience script to run CanvasMark 2013 from anywhere in the project

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$PdgRoot = (Get-Item $ScriptDir).Parent.Parent.Parent.FullName

Set-Location $PdgRoot

$QuickMode = $args -contains '--quick'
$MarkName = if ($QuickMode) { "QuickCanvasMark" } else { "CanvasMark" }

Write-Host "Running $MarkName from $PdgRoot"
if (-not $QuickMode) { Write-Host "Press SPACE or click to start tests. Press ESC to quit." }
Write-Host ""

$PerfNode = if ($env:PDG_NODE) { $env:PDG_NODE } else { Join-Path $PdgRoot "tools/node.exe" }
& $PerfNode test/lib/perf_build.js test/perf_tests/canvasmark2013/canvasmark.js @args
exit $LASTEXITCODE
