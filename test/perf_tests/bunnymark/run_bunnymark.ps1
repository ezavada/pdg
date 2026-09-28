# Convenience script to run Bunnymark from anywhere in the project

# Get the directory where this script lives
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path

# Get PDG root (three levels up: bunnymark -> perf_tests -> test -> repo root)
$PdgRoot = (Get-Item $ScriptDir).Parent.Parent.Parent.FullName

# Change to PDG root
Set-Location $PdgRoot

$QuickMode = $args -contains '--quick'
$MarkName = if ($QuickMode) { "QuickBunnyMark" } else { "BunnyMark" }

# Run the benchmark
Write-Host "Running $MarkName from $PdgRoot"
$PerfNode = if ($env:PDG_NODE) { $env:PDG_NODE } else { Join-Path $PdgRoot "tools/node.exe" }
& $PerfNode test/lib/perf_build.js test/perf_tests/bunnymark/bunnymark.js @args
if ($QuickMode -or $LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

# Show results if they exist
$ResultsPath = Join-Path $PdgRoot "test\perf_tests\bunnymark\bunnymark_results.json"
if (Test-Path $ResultsPath) {
    Write-Host ""
    Write-Host "Results saved. Key metrics:"
    $json = Get-Content $ResultsPath -Raw | ConvertFrom-Json
    if ($json.performance) {
        $json.performance.PSObject.Properties | Where-Object { $_.Name -match 'maxBunniesAt60FPS|averageFPS' } | ForEach-Object {
            Write-Host "  $($_.Name): $($_.Value)"
        }
    }
}
