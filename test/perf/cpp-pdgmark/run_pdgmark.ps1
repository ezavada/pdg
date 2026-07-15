# Quick script to run C++ PDGMark from anywhere in the project

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$PdgRoot = (Get-Item $ScriptDir).Parent.Parent.Parent.FullName

Set-Location $PdgRoot

$ExePath = Join-Path $PdgRoot "test\perf\cpp-pdgmark\pdgmark"
if (-not (Test-Path $ExePath) -and -not (Test-Path "$ExePath.exe")) {
    Write-Host "PDGMark executable not found. Build with: make pdg-tests (or your build command)"
    exit 1
}
$Exe = if (Test-Path "$ExePath.exe") { "$ExePath.exe" } else { $ExePath }

Write-Host "Running C++ PDGMark from $PdgRoot"
Write-Host "ESC = quit and show results at any time"
Write-Host ""

& $Exe @args

$ResultsPath = Join-Path $PdgRoot "test\perf\cpp-pdgmark\pdgmark_results.json"
if (Test-Path $ResultsPath) {
    Write-Host ""
    Write-Host "Results saved to: test\perf\cpp-pdgmark\pdgmark_results.json"
    try {
        $json = Get-Content $ResultsPath -Raw | ConvertFrom-Json
        if ($null -ne $json.compositeScore) {
            Write-Host "Composite Score: $($json.compositeScore)"
        }
    } catch { }
}
