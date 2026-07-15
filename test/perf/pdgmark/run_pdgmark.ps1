# Convenience script to run PDGMark from any directory

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$PdgRoot = (Get-Item $ScriptDir).Parent.Parent.Parent.FullName

Set-Location $PdgRoot

Write-Host "Running PDGMark from $PdgRoot"
Write-Host ""

$exitCode = 0
& ./pdg test/perf/pdgmark/pdgmark.js
$exitCode = $LASTEXITCODE

if ($exitCode -eq 0) {
    Write-Host ""
    Write-Host "=========================================="
    Write-Host "PDGMark Complete!"
    Write-Host "=========================================="

    $ResultsPath = Join-Path $PdgRoot "test\perf\pdgmark\pdgmark_results.json"
    if (Test-Path $ResultsPath) {
        Write-Host ""
        Write-Host "Results saved to: test/perf/pdgmark/pdgmark_results.json"
        try {
            $json = Get-Content $ResultsPath -Raw | ConvertFrom-Json
            if ($null -ne $json.compositeScore) {
                Write-Host "Composite Score: $($json.compositeScore)"
            }
        } catch { }
        Write-Host ""
        Write-Host "To save as baseline:"
        Write-Host "  Copy-Item test\perf\pdgmark\pdgmark_results.json \"
        Write-Host "    test\perf\pdgmark\pdgmark_baseline.json"
        Write-Host ""
        Write-Host "To compare with baseline:"
        Write-Host "  node test/perf/pdgmark/compare_results.js"
        Write-Host ""
    }
} else {
    Write-Host ""
    Write-Host "PDGMark failed. Check error messages above."
    exit 1
}
