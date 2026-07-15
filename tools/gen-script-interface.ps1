#Requires -Version 5.1
<#
.SYNOPSIS
  PowerShell port of gen-script-interface.sh - preprocess bindings and run bcpp.

  Environment:
    BCPP_EXE - optional full path to bcpp.exe (otherwise bcpp on PATH).
    PDG_GEN_SCRIPT_VERBOSE=1 - print which preprocessor runs and command lines (also use -GenVerbose).
    PDG_GEN_SCRIPT_KEEP_TEMPS=1 - copy workDir (tmp.1, tmp.5, bcpp output) under build\win32\gen-script-last-<id>\

  MSBuild: run from a shell with $env:PDG_GEN_SCRIPT_VERBOSE='1' so child processes inherit it.
#>
param(
    [Parameter(Mandatory = $true)][string]$BindingDir,
    [Parameter(Mandatory = $true)][string]$PdgSrc,
    [string]$PdgTargetDir = "",
    [string]$PdgBuildDir = "",
    [string]$PdgOutFilename = "",
    [switch]$GenVerbose,
    [switch]$KeepTemps
)

$ErrorActionPreference = "Stop"

$script:GenScriptVerbose = $GenVerbose -or ($env:PDG_GEN_SCRIPT_VERBOSE -eq '1')
$script:GenScriptKeepTemps = $KeepTemps -or ($env:PDG_GEN_SCRIPT_KEEP_TEMPS -eq '1')

function Write-GenScriptLog {
    param([string]$Message)
    if ($script:GenScriptVerbose) {
        Write-Host "[gen-script-interface] $Message" -ForegroundColor Cyan
    }
}

function Get-PdgRoot {
    $tools = $PSScriptRoot
    return (Resolve-Path (Join-Path $tools "..")).Path
}

function Get-VsDevCmdBat {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path $vswhere)) { return $null }
    $install = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath 2>$null
    if (-not $install) { return $null }
    $bat = Join-Path $install "Common7\Tools\VsDevCmd.bat"
    if (Test-Path $bat) { return $bat }
    return $null
}

function Get-VsInstallRoot {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path $vswhere)) { return $null }
    return & $vswhere -latest -products * -property installationPath 2>$null | Select-Object -First 1
}

# Clang-cl uses the same preprocessor behavior as gcc/clang (needed for CR -> @ -> newlines). MSVC cl /EP does not.
function Get-VsLlvmClangClExe {
    $root = Get-VsInstallRoot
    if (-not $root) { return $null }
    foreach ($rel in @("VC\Tools\Llvm\x64\bin\clang-cl.exe", "VC\Tools\Llvm\bin\clang-cl.exe")) {
        $p = Join-Path $root $rel
        if (Test-Path $p) { return $p }
    }
    return $null
}

function Get-CppPreprocessorCommand {
    if (Get-Command clang -ErrorAction SilentlyContinue) {
        return @{ Exe = "clang"; ArgsPrefix = @("-E", "-x", "c++", "-std=c++20") }
    }
    if (Get-Command gcc -ErrorAction SilentlyContinue) {
        return @{ Exe = "gcc"; ArgsPrefix = @("-E", "-x", "c++", "-std=c++20") }
    }
    if (Get-Command clang++ -ErrorAction SilentlyContinue) {
        return @{ Exe = "clang++"; ArgsPrefix = @("-E", "-x", "c++", "-std=c++20") }
    }
    return $null
}

function Invoke-CppPreprocessToFile {
    param(
        [string]$SourceFile,
        [string]$OutFile,
        [string[]]$IncludeDirs,
        [string[]]$Defines
    )
    $inc = ($IncludeDirs | ForEach-Object { "/I`"$_`"" }) -join " "
    $def = ($Defines | ForEach-Object { "/D$_" }) -join " "
    $quotedSrc = "`"$SourceFile`""
    $quotedOut = "`"$OutFile`""
    $devCmd = Get-VsDevCmdBat

    # 1) VS LLVM clang-cl (preferred on Windows: gcc-like preprocessor, preserves @ from PDG_SCRIPT CR macro)
    $clangCl = Get-VsLlvmClangClExe
    if ($devCmd -and $clangCl) {
        Write-GenScriptLog "preprocessor: VS LLVM clang-cl"
        Write-GenScriptLog "  clang-cl: $clangCl"
        Write-GenScriptLog "  VsDevCmd: $devCmd"
        $inner = "`"$clangCl`" /nologo /EP /TP $def $inc $quotedSrc > $quotedOut 2>&1"
        $cmd = "`"$devCmd`" -arch=amd64 -no_logo && $inner"
        Write-GenScriptLog "  cmd /c: $cmd"
        cmd /c $cmd
        if ($LASTEXITCODE -ne 0) { throw "clang-cl /EP preprocessor failed with exit $LASTEXITCODE" }
        return
    }

    Write-GenScriptLog "VS LLVM clang-cl not found (install 'C++ Clang Compiler for Windows' workload), trying PATH compilers..."

    # 2) clang/gcc on PATH (e.g. MSYS2 / standalone LLVM)
    $tool = Get-CppPreprocessorCommand
    if ($tool) {
        Write-GenScriptLog "preprocessor: $($tool.Exe) on PATH (gnu-style -E)"
        $args = @()
        if ($tool.ArgsPrefix) { $args = $tool.ArgsPrefix + $args }
        foreach ($d in $Defines) { $args += "-D$d" }
        foreach ($i in $IncludeDirs) { $args += "-I$i" }
        $args += $SourceFile, "-o", $OutFile
        Write-GenScriptLog "  args: $($args -join ' ')"
        & $tool.Exe @args
        if ($LASTEXITCODE -ne 0) { throw "Preprocessor $($tool.Exe) failed with exit $LASTEXITCODE" }
        return
    }

    # 3) MSVC cl - conforming preprocessor; /utf-8 keeps PowerShell sed pipeline stable
    if (-not $devCmd) {
        throw "No C++ preprocessor found: install the VS C++ LLVM component (clang-cl), MinGW/LLVM clang/gcc on PATH, or MSVC Build Tools (VsDevCmd)."
    }

    Write-GenScriptLog "preprocessor: MSVC cl /EP (/Zc:preprocessor matches gcc-like macro expansion for CR -> @)"
    Write-GenScriptLog "  VsDevCmd: $devCmd"
    # /std:c++20 aligns with project; /Zc:preprocessor is required for #define CR @ to behave like gcc -E
    $inner = "cl /nologo /EP /TP /std:c++20 /Zc:preprocessor /utf-8 $def $inc $quotedSrc > $quotedOut 2>&1"
    $cmd = "`"$devCmd`" -arch=amd64 -no_logo && $inner"
    Write-GenScriptLog "  cmd /c: $cmd"
    cmd /c $cmd
    if ($LASTEXITCODE -ne 0) { throw "cl /EP preprocessor failed with exit $LASTEXITCODE" }
}

function Read-AllTextWithRetry {
    param(
        [string]$Path,
        [int]$MaxAttempts = 50,
        [int]$DelayMs = 20
    )
    # Second $false: do not throw on invalid UTF-8 bytes (cl /utf-8 output is usually clean; be tolerant)
    $enc = New-Object System.Text.UTF8Encoding $false, $false
    for ($a = 0; $a -lt $MaxAttempts; $a++) {
        try {
            return [System.IO.File]::ReadAllText($Path, $enc)
        }
        catch [System.IO.IOException] {
            if ($a -ge $MaxAttempts - 1) { throw }
            Start-Sleep -Milliseconds $DelayMs
        }
    }
}

function Apply-SedPipeline {
    param([string]$InPath, [string]$OutPath)
    # Canonical pre-bcpp text: clang/gcc vs cl can differ in line endings and token spacing; normalize here so
    # bcpp.exe always sees the same tmp.5 (same Mac/Win output without post-processing bcpp).
    $utf8 = New-Object System.Text.UTF8Encoding $false, $false
    $t = Read-AllTextWithRetry -Path $InPath
    $t = $t -replace "`r`n", "`n"
    $t = $t -replace "`r", "`n"
    $t = $t.Replace("@", "`n")
    $t = $t.Replace("%#", "#")
    $t = $t -replace '(?m)# .*$', ''
    $t = $t.Replace("__line__", "__LINE__")
    # args[n-m] / ARGV[n-m]: MSVC often omits the space gcc keeps (see pdg_script_macros.h ARGV[n-1]).
    $t = [regex]::Replace($t, '(?i)\bARGV\[(\d+)-(\d+)\]', 'args[$1 -$2]')
    $t = [regex]::Replace($t, '\bargs\[(\d+)-(\d+)\]', 'args[$1 -$2]')
    # EOL " ) ;" can appear in some -E output; same pattern is also reintroduced by bcpp on Windows—normalize here first.
    $t = [regex]::Replace($t, '(?m)\)\s+;\s*$', ');')
    $t = [regex]::Replace($t, '(?m)\}\s+;\s*$', '};')
    [System.IO.File]::WriteAllText($OutPath, $t, $utf8)
}

$utf8NoBom = New-Object System.Text.UTF8Encoding $false
function Write-Utf8NoBom {
    param([string]$Path, [string]$Text)
    [System.IO.File]::WriteAllText($Path, $Text, $utf8NoBom)
}
function Add-Utf8NoBom {
    param([string]$Path, [string]$Text)
    [System.IO.File]::AppendAllText($Path, $Text, $utf8NoBom)
}

$PDG_ROOT = Get-PdgRoot
if (-not (Test-Path $PdgSrc)) {
    throw "Source file not found: $PdgSrc"
}
$PdgSrc = (Resolve-Path $PdgSrc).Path

$PdgSrcDir = Split-Path -Parent $PdgSrc
$PdgRelSrcDir = $PdgSrcDir
if ($PdgSrcDir.StartsWith($PDG_ROOT, [StringComparison]::OrdinalIgnoreCase)) {
    $PdgRelSrcDir = $PdgSrcDir.Substring($PDG_ROOT.Length).TrimStart("\", "/")
}
$PdgSrcFilename = Split-Path -Leaf $PdgSrc
$PdgRelSrc = (Join-Path $PdgRelSrcDir $PdgSrcFilename) -replace '\\', '/'

if ([string]::IsNullOrEmpty($PdgTargetDir)) {
    $PdgTargetDir = Join-Path $PDG_ROOT "src\bindings"
} elseif (-not [System.IO.Path]::IsPathRooted($PdgTargetDir)) {
    $PdgTargetDir = Join-Path $PDG_ROOT $PdgTargetDir
}
if (-not (Test-Path $PdgTargetDir)) {
    New-Item -ItemType Directory -Path $PdgTargetDir -Force | Out-Null
}
$PdgTargetDir = (Resolve-Path $PdgTargetDir).Path

if ([string]::IsNullOrEmpty($PdgBuildDir)) {
    $PdgBuildDir = Join-Path $PDG_ROOT "build"
} elseif ($PdgBuildDir -eq "." -or $PdgBuildDir -eq "./") {
    $PdgBuildDir = (Get-Location).Path
} elseif (-not [System.IO.Path]::IsPathRooted($PdgBuildDir)) {
    $PdgBuildDir = Join-Path (Get-Location).Path $PdgBuildDir
}
if (-not (Test-Path $PdgBuildDir)) {
    New-Item -ItemType Directory -Path $PdgBuildDir -Force | Out-Null
}
$PdgBuildDir = (Resolve-Path $PdgBuildDir).Path

if ([string]::IsNullOrEmpty($PdgOutFilename)) {
    $PdgOutFilename = $PdgSrcFilename
}

$PdgTarget = Join-Path $PdgTargetDir $PdgOutFilename

$BcppExe = $env:BCPP_EXE
if ([string]::IsNullOrEmpty($BcppExe)) {
    $defaultBcpp = Join-Path $PDG_ROOT "build\win32\bcpp\Release\bcpp.exe"
    if (Test-Path $defaultBcpp) { $BcppExe = $defaultBcpp }
}
if ([string]::IsNullOrEmpty($BcppExe)) {
    throw "bcpp not found. Set BCPP_EXE or build with configure.ps1 (build\win32\bcpp\Release\bcpp.exe)."
}
$BcppExe = (Resolve-Path $BcppExe).Path

# Build header with an explicit trailing newline so LICENSE never runs into the final "//" (avoids "//// Permission").
$hdrLines = @(
    '// -----------------------------------------------',
    '// This file automatically generated from:',
    '//',
    "//    `$PDG_ROOT/$PdgRelSrc",
    "//    `$PDG_ROOT/src/bindings/$BindingDir/pdg_script_macros.h",
    '//'
)
$hdr = ($hdrLines -join "`r`n") + "`r`n"
Write-Utf8NoBom -Path $PdgTarget -Text $hdr

$lic = Join-Path $PDG_ROOT "src\bindings\$BindingDir\LICENSE"
Add-Utf8NoBom -Path $PdgTarget -Text ([System.IO.File]::ReadAllText($lic))
# gen-script-interface.sh: echo "" twice after LICENSE. LICENSE has no trailing blank line, so three CRLFs => three blank lines before bcpp body (matches committed pdg_interfaces.cpp).
Add-Utf8NoBom -Path $PdgTarget -Text "`r`n`r`n`r`n"

$incTarget = $PdgTargetDir
$incBinding = Join-Path $PDG_ROOT "src\bindings\$BindingDir"
$incJs = Join-Path $PDG_ROOT "src\bindings\javascript"
$includeDirs = @($incTarget, $incBinding, $incJs)
$defines = @("PDG_BUILDING_INTERFACE_FILES")

# Isolated work dir: MSBuild runs many custom commands in parallel; shared tmp.1.txt caused races.
$workDir = Join-Path $PdgBuildDir ("gis-" + [guid]::NewGuid().ToString("n"))
New-Item -ItemType Directory -Path $workDir -Force | Out-Null
$tmp1 = Join-Path $workDir "tmp.1.txt"
$tmp5 = Join-Path $workDir "tmp.5.txt"

Write-GenScriptLog "source: $PdgSrc"
Write-GenScriptLog "target: $PdgTarget"
Write-GenScriptLog "workDir: $workDir"
Write-GenScriptLog "bcpp: $BcppExe"

try {
    Invoke-CppPreprocessToFile -SourceFile $PdgSrc -OutFile $tmp1 -IncludeDirs $includeDirs -Defines $defines
    if ($script:GenScriptVerbose -and (Test-Path -LiteralPath $tmp1)) {
        $pre = [System.IO.File]::ReadAllText($tmp1, (New-Object System.Text.UTF8Encoding $false, $false))
        $at = ([regex]::Matches($pre, '@')).Count
        $nlCount = ([regex]::Matches($pre, '\r?\n')).Count
        $previewLen = [Math]::Min(200, $pre.Length)
        Write-GenScriptLog ('after preprocess (tmp.1.txt): length={0}, at-sign count={1}, line-break sequences={2}, preview: {3}' -f $pre.Length, $at, $nlCount, $pre.Substring(0, $previewLen))
    }

    Apply-SedPipeline -InPath $tmp1 -OutPath $tmp5

    if ($script:GenScriptVerbose -and (Test-Path -LiteralPath $tmp5)) {
        $t5 = [System.IO.File]::ReadAllText($tmp5, (New-Object System.Text.UTF8Encoding $false, $false))
        $t5nl = ([regex]::Matches($t5, '\r?\n')).Count
        $t5at = ([regex]::Matches($t5, '@')).Count
        Write-GenScriptLog ('after sed pipeline (tmp.5.txt): length={0}, at-sign count={1}, line-break sequences={2}' -f $t5.Length, $t5at, $t5nl)
    }

    # Write bcpp stdout to a file. Assigning native exe output to a PowerShell string can collapse or alter newlines.
    $tmp6 = Join-Path $workDir "tmp.6.bcpp-out.txt"
    Push-Location $workDir
    try {
        cmd /c "`"$BcppExe`" `"tmp.5.txt`" 2>nul > `"$tmp6`""
    }
    finally {
        Pop-Location
    }

    $bcppText = $null
    if (Test-Path -LiteralPath $tmp6) {
        # bcpp emits OEM/ANSI on Windows; Default matches legacy C tools
        $bcppText = [System.IO.File]::ReadAllText($tmp6, [System.Text.Encoding]::Default)
    }
    if ([string]::IsNullOrEmpty($bcppText)) {
        throw "bcpp produced no output (see tmp.6.bcpp-out.txt under build\win32\gen-script-last-* when PDG_GEN_SCRIPT_KEEP_TEMPS=1)."
    }
    # bcpp may echo the input basename before the formatted body (.h tmp names or .cpp source names)
    while ($true) {
        $m = [regex]::Match($bcppText, '^\s*(\S+\.(?:h|cpp|c|cc|cxx))\s*\r?\n')
        if (-not $m.Success) { break }
        $bcppText = $bcppText.Substring($m.Length)
    }
    # Catch " ) ;" if bcpp added it after a clean tmp.5 (grep tmp.5.txt when PDG_GEN_SCRIPT_KEEP_TEMPS=1 to see which).
    #$bcppText = [regex]::Replace($bcppText, '(?m)\)\s+;\s*$', ');')
    [System.IO.File]::AppendAllText($PdgTarget, $bcppText, $utf8NoBom)
}
finally {
    if ($script:GenScriptKeepTemps) {
        $base = Join-Path $PDG_ROOT "build\win32"
        if (-not (Test-Path $base)) { New-Item -ItemType Directory -Path $base -Force | Out-Null }
        $leaf = (Split-Path -Leaf $workDir)
        $dest = Join-Path $base "gen-script-last-$leaf"
        if (Test-Path -LiteralPath $dest) {
            Remove-Item -LiteralPath $dest -Recurse -Force -ErrorAction SilentlyContinue
        }
        Copy-Item -LiteralPath $workDir -Destination $dest -Recurse -Force
        Write-Host "[gen-script-interface] intermediates saved: $dest (tmp.1, tmp.5, tmp.6.bcpp-out.txt)" -ForegroundColor Green
        Write-GenScriptLog "intermediates: tmp.1=preprocess, tmp.5=after sed, tmp.6=bcpp stdout"
    }
    if (-not $script:GenScriptKeepTemps) {
        Remove-Item -LiteralPath $workDir -Recurse -Force -ErrorAction SilentlyContinue
    }
}
