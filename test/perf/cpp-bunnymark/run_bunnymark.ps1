# Quick script to run C++ Bunnymark from anywhere in the project

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$PdgRoot = (Get-Item $ScriptDir).Parent.Parent.Parent.FullName

Set-Location $PdgRoot

# On Windows we must use bunnymark.exe (the "bunnymark" file here is a launcher path, not the binary)
$testDir = Join-Path $PdgRoot "test\perf\cpp-bunnymark"
$buildDir = Join-Path $PdgRoot "msvc\src\Release"
$Exe = $null
if (Test-Path (Join-Path $testDir "bunnymark.exe")) { $Exe = Join-Path $testDir "bunnymark.exe" }
elseif (Test-Path (Join-Path $buildDir "bunnymark.exe")) { $Exe = Join-Path $buildDir "bunnymark.exe" }
elseif ($env:OS -notmatch 'Windows' -and (Test-Path (Join-Path $testDir "bunnymark"))) { $Exe = Join-Path $testDir "bunnymark" }
if (-not $Exe) {
    Write-Host "Bunnymark executable not found. Build with: .\tools\make_ps1 -Target pdg-tests"
    exit 1
}

Write-Host "Running C++ Bunnymark from $PdgRoot"
Write-Host "SPACE = add bunnies, ESC = quit and show results"
Write-Host ""

& $Exe @args

$ResultsPath = Join-Path $PdgRoot "test\perf\cpp-bunnymark\bunnymark_results.json"
if (Test-Path $ResultsPath) {
    Write-Host ""
    Write-Host "Results saved. Key metrics:"
    try {
        $json = Get-Content $ResultsPath -Raw | ConvertFrom-Json
        if ($json.performance) {
            $json.performance.PSObject.Properties | Where-Object { $_.Name -match 'maxBunniesAt60FPS|averageFPS' } | ForEach-Object {
                Write-Host "  $($_.Name): $($_.Value)"
            }
        }
    } catch { }
}
