param(
    [ValidateSet("Debug", "Release")]
    [string]$Config = "Release"
)

$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$targetDir = Join-Path $repoRoot "build\node-pdg"
$installDir = Join-Path $repoRoot "build\node-pdg-install"
$npmCacheDir = Join-Path $repoRoot "build\npm-cache"
$version = (Get-Content -Raw (Join-Path $repoRoot "VERSION")).Trim()
$packageArchive = Join-Path $targetDir "pdg-$version.tgz"

function Resolve-NodeExecutable {
    param([string]$BuildConfig)

    $candidates = @(
        (Join-Path $repoRoot "tools\node.exe"),
        (Join-Path $repoRoot "deps\node\out\$BuildConfig\node.exe"),
        (Join-Path $repoRoot "deps\node\Release\node.exe")
    )

    foreach ($candidate in $candidates) {
        if (Test-Path $candidate) {
            return $candidate
        }
    }

    throw "Could not find a usable Node.js executable. Build the 'node' target first."
}

function Resolve-NpmCli {
    $candidates = @(
        (Join-Path $repoRoot "tools\npm\bin\npm-cli.js"),
        (Join-Path $repoRoot "node_modules\npm\bin\npm-cli.js")
    )

    foreach ($candidate in $candidates) {
        if (Test-Path $candidate) {
            return $candidate
        }
    }

    throw "Could not find npm-cli.js under tools\\npm or node_modules\\npm."
}

function Resolve-VsDevCmd {
    $candidates = @(
        "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat",
        "C:\Program Files\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat",
        "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\Tools\VsDevCmd.bat"
    )

    foreach ($candidate in $candidates) {
        if (Test-Path $candidate) {
            return $candidate
        }
    }

    throw "Could not find a Visual Studio developer command script."
}

function Resolve-WindowsSdkVersion {
    $sdkRoot = "C:\Program Files (x86)\Windows Kits\10\Lib"
    if (-not (Test-Path $sdkRoot)) {
        return $null
    }

    $sdkDirectory = Get-ChildItem -LiteralPath $sdkRoot -Directory |
        Sort-Object { [version]$_.Name } -Descending |
        Select-Object -First 1
    if ($sdkDirectory) {
        return $sdkDirectory.Name
    }

    return $null
}

function Set-TemporaryEnvironment {
    param([hashtable]$Values)

    $previousValues = @{}
    foreach ($name in $Values.Keys) {
        $previousValues[$name] = [System.Environment]::GetEnvironmentVariable($name, "Process")
        [System.Environment]::SetEnvironmentVariable($name, $Values[$name], "Process")
    }
    return $previousValues
}

function Restore-TemporaryEnvironment {
    param([hashtable]$PreviousValues)

    foreach ($name in $PreviousValues.Keys) {
        [System.Environment]::SetEnvironmentVariable($name, $PreviousValues[$name], "Process")
    }
}

function Initialize-InstallWorkspace {
    param([string]$Path)

    if (Test-Path $Path) {
        Remove-Item -LiteralPath $Path -Recurse -Force
    }

    New-Item -ItemType Directory -Path $Path -Force | Out-Null

    $installPackageJson = @'
{
  "name": "pdg-node-install",
  "private": true
}
'@
    Set-Content -LiteralPath (Join-Path $Path "package.json") -Value $installPackageJson
}

function Invoke-Npm {
    param(
        [string]$WorkingDirectory,
        [string[]]$Arguments,
        [hashtable]$Environment = @{},
        [switch]$UseVsDevCmd
    )

    Push-Location $WorkingDirectory
    $previousValues = Set-TemporaryEnvironment $Environment
    try {
        if ($UseVsDevCmd) {
            $quotedArgs = $Arguments | ForEach-Object { '"' + $_ + '"' }
            $commandParts = @(
                'call "' + $script:vsDevCmd + '" -arch=amd64 -host_arch=amd64 >nul'
            )
            if ($script:windowsSdkVersion) {
                $commandParts += 'set "WindowsTargetPlatformVersion=' + $script:windowsSdkVersion + '"'
            }
            $commandParts += 'set "PATH=' + $script:nodeDir + ';%PATH%"'
            $commandParts += '"' + $script:nodeExe + '" "' + $script:npmCli + '" ' + ($quotedArgs -join ' ')
            $process = Start-Process -FilePath "cmd.exe" -ArgumentList @("/d", "/s", "/c", ($commandParts -join " && ")) -PassThru -NoNewWindow -Wait
            if ($process.ExitCode -ne 0) {
                throw "npm exited with code $($process.ExitCode) while running: $($Arguments -join ' ')"
            }
        }
        else {
            & $script:nodeExe $script:npmCli @Arguments
            if ($LASTEXITCODE -ne 0) {
                throw "npm exited with code $LASTEXITCODE while running: $($Arguments -join ' ')"
            }
        }
    }
    finally {
        Restore-TemporaryEnvironment $previousValues
        Pop-Location
    }
}

$nodeExe = Resolve-NodeExecutable -BuildConfig $Config
$npmCli = Resolve-NpmCli
$nodeDir = Split-Path -Parent $nodeExe
$vsDevCmd = Resolve-VsDevCmd
$windowsSdkVersion = Resolve-WindowsSdkVersion
New-Item -ItemType Directory -Path $npmCacheDir -Force | Out-Null
$npmEnvironment = @{
    "npm_config_loglevel" = "error"
    "npm_config_nodedir" = (Join-Path $repoRoot "deps\node")
    "npm_config_cache" = $npmCacheDir
    "npm_config_msvs_version" = "2022"
    "GYP_MSVS_VERSION" = "2022"
    "PATH" = "$nodeDir;$env:PATH"
}
$bundledNodeGyp = Join-Path $repoRoot "tools\npm\node_modules\node-gyp\bin\node-gyp.js"
if (Test-Path $bundledNodeGyp) {
    $npmEnvironment["npm_config_node_gyp"] = $bundledNodeGyp
}
if ($Config -eq "Debug") {
    $npmEnvironment["npm_config_debug"] = "true"
}

Write-Host "Packaging the PDG Node.js module..." -ForegroundColor Cyan
& (Join-Path $PSScriptRoot "copy-node-module-source.ps1") $targetDir

Invoke-Npm -WorkingDirectory $targetDir -Arguments @("pack") -Environment $npmEnvironment

if (-not (Test-Path $packageArchive)) {
    throw "Expected package archive was not produced: $packageArchive"
}

Write-Host "Installing the packaged module into node_modules..." -ForegroundColor Cyan
Initialize-InstallWorkspace -Path $installDir
Invoke-Npm -WorkingDirectory $installDir -Arguments @("install", "--no-save", $packageArchive) -Environment $npmEnvironment -UseVsDevCmd

$builtModuleDir = Join-Path $installDir "node_modules\pdg"
$builtModulePath = if ($Config -eq "Debug") {
    Join-Path $builtModuleDir "build\Debug\pdg.node"
}
else {
    Join-Path $builtModuleDir "build\Release\pdg.node"
}

if (-not (Test-Path $builtModulePath)) {
    throw "Expected native module was not produced: $builtModulePath"
}

Write-Host "Syncing the installed module into the repo node_modules..." -ForegroundColor Cyan
$repoNodeModulesDir = Join-Path $repoRoot "node_modules"
$repoBuiltModuleDir = Join-Path $repoNodeModulesDir "pdg"
New-Item -ItemType Directory -Path $repoNodeModulesDir -Force | Out-Null
Remove-Item -LiteralPath $repoBuiltModuleDir -Recurse -Force -ErrorAction SilentlyContinue
Copy-Item -LiteralPath $builtModuleDir -Destination $repoNodeModulesDir -Recurse -Force
$builtModuleDir = $repoBuiltModuleDir
$builtModulePath = if ($Config -eq "Debug") {
    Join-Path $builtModuleDir "build\Debug\pdg.node"
}
else {
    Join-Path $builtModuleDir "build\Release\pdg.node"
}

Write-Host "Testing the installed module..." -ForegroundColor Cyan
Invoke-Npm -WorkingDirectory $builtModuleDir -Arguments @("test") -Environment $npmEnvironment

Write-Host ""
Write-Host "Done with PDG Node.js Module" -ForegroundColor Green
Write-Host $packageArchive
Write-Host $builtModulePath
