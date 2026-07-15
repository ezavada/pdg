# Quick script to run CanvasMark 2013 from anywhere in the project

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$PdgRoot = (Get-Item $ScriptDir).Parent.Parent.Parent.FullName

Set-Location $PdgRoot

Write-Host "Running CanvasMark 2013 from $PdgRoot"
Write-Host "Press SPACE or click to start tests. Press ESC to quit."
Write-Host ""

& ./pdg test/perf/canvasmark2013/canvasmark.js @args
