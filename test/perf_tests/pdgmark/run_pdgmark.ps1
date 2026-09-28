# Convenience script to run PDGMark from any directory

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$PdgRoot = (Get-Item $ScriptDir).Parent.Parent.Parent.FullName

Set-Location $PdgRoot

$QuickMode = $args -contains '--quick'
$MarkName = if ($QuickMode) { "QuickPDGMark" } else { "PDGMark" }

Write-Host "Running $MarkName from $PdgRoot"
Write-Host ""

$exitCode = 0
$PerfNode = if ($env:PDG_NODE) { $env:PDG_NODE } else { Join-Path $PdgRoot "tools/node.exe" }
& $PerfNode test/lib/perf_build.js test/perf_tests/pdgmark/pdgmark.js @args
if ($QuickMode) { exit $LASTEXITCODE }
$exitCode = $LASTEXITCODE

if ($exitCode -eq 0) {
    Write-Host ""
    Write-Host "=========================================="
    Write-Host "PDGMark Complete!"
    Write-Host "=========================================="

    $ResultsPath = Join-Path $PdgRoot "test\perf_tests\pdgmark\pdgmark_results.json"
    if (Test-Path $ResultsPath) {
        Write-Host ""
        Write-Host "Results saved to: test/perf_tests/pdgmark/pdgmark_results.json"
        try {
            $json = Get-Content $ResultsPath -Raw | ConvertFrom-Json
            if ($null -ne $json.compositeScore) {
                Write-Host "Composite Score: $($json.compositeScore)"
            }
        } catch { }
        Write-Host ""
        Write-Host "To save as baseline:"
        Write-Host "  Copy-Item test\perf_tests\pdgmark\pdgmark_results.json \"
        Write-Host "    test\perf_tests\pdgmark\pdgmark_baseline.json"
        Write-Host ""
        Write-Host "To compare with baseline:"
        Write-Host "  node test/perf_tests/pdgmark/compare_results.js"
        Write-Host ""
    }
} else {
    Write-Host ""
    Write-Host "PDGMark failed. Check error messages above."
    exit 1
}
