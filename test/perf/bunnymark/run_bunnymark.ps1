# Quick script to run Bunnymark from anywhere in the project

# Get the directory where this script lives
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path

# Get PDG root (three levels up: bunnymark -> perf -> test -> repo root)
$PdgRoot = (Get-Item $ScriptDir).Parent.Parent.Parent.FullName

# Change to PDG root
Set-Location $PdgRoot

# Run the benchmark
Write-Host "Running Bunnymark from $PdgRoot"
& ./pdg test/perf/bunnymark/bunnymark.js @args

# Show results if they exist
$ResultsPath = Join-Path $PdgRoot "test\perf\bunnymark_results.json"
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
