param(
    [Parameter(Mandatory = $true)]
    [string]$TargetDir
)

$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
. (Join-Path $PSScriptRoot "submodules.ps1")

if (-not (Ensure-RepoSubmodule -RepoRoot $repoRoot -SubmodulePath "deps/node" -SentinelRelativePath "deps\node\src\node_version.h" -DisplayName "Node.js source checkout")) {
    throw "Node.js source checkout is required."
}

if ([System.IO.Path]::IsPathRooted($TargetDir)) {
    $resolvedTargetDir = [System.IO.Path]::GetFullPath($TargetDir)
}
else {
    $resolvedTargetDir = [System.IO.Path]::GetFullPath((Join-Path $repoRoot $TargetDir))
}

if ($resolvedTargetDir -eq $repoRoot) {
    throw "Refusing to overwrite the repository root."
}

function New-CleanDirectory {
    param([string]$Path)

    if (Test-Path $Path) {
        Remove-Item -LiteralPath $Path -Recurse -Force
    }
    New-Item -ItemType Directory -Path $Path -Force | Out-Null
}

function Copy-DirectoryContents {
    param(
        [string]$Source,
        [string]$Destination
    )

    New-Item -ItemType Directory -Path $Destination -Force | Out-Null
    Get-ChildItem -LiteralPath $Source -Force | Copy-Item -Destination $Destination -Recurse -Force
}

function Copy-TreeFiltered {
    param(
        [string]$Source,
        [string]$Destination,
        [scriptblock]$ShouldExclude
    )

    $sourceRoot = (Resolve-Path -LiteralPath $Source).Path
    New-Item -ItemType Directory -Path $Destination -Force | Out-Null

    foreach ($item in Get-ChildItem -LiteralPath $sourceRoot -Recurse -Force) {
        $relativePath = $item.FullName.Substring($sourceRoot.Length).TrimStart('\')
        if (& $ShouldExclude $relativePath $item) {
            continue
        }

        $destinationPath = Join-Path $Destination $relativePath
        if ($item.PSIsContainer) {
            New-Item -ItemType Directory -Path $destinationPath -Force | Out-Null
            continue
        }

        $destinationParent = Split-Path -Parent $destinationPath
        New-Item -ItemType Directory -Path $destinationParent -Force | Out-Null
        Copy-Item -LiteralPath $item.FullName -Destination $destinationPath -Force
    }
}

function Get-RepoPath {
    param([string]$RelativePath)
    return Join-Path $repoRoot $RelativePath
}

Write-Host "Collecting all the files for the module" -ForegroundColor Cyan

New-CleanDirectory $resolvedTargetDir

Write-Host " * src/bindings/common ==> $resolvedTargetDir\src\bindings\common"
Copy-DirectoryContents (Get-RepoPath "src\bindings\common") (Join-Path $resolvedTargetDir "src\bindings\common")

Write-Host " * src/bindings/javascript/v8 ==> $resolvedTargetDir\src\bindings\javascript\v8"
Copy-DirectoryContents (Get-RepoPath "src\bindings\javascript\v8") (Join-Path $resolvedTargetDir "src\bindings\javascript\v8")

Write-Host " * src/bindings/generated ==> $resolvedTargetDir\src\bindings\generated"
Copy-DirectoryContents (Get-RepoPath "src\bindings\generated") (Join-Path $resolvedTargetDir "src\bindings\generated")

Write-Host " * src/bindings/javascript/memblock.* ==> $resolvedTargetDir\src\bindings\javascript"
New-Item -ItemType Directory -Path (Join-Path $resolvedTargetDir "src\bindings\javascript") -Force | Out-Null
Get-ChildItem -LiteralPath (Get-RepoPath "src\bindings\javascript") -Filter "memblock.*" -File | Copy-Item -Destination (Join-Path $resolvedTargetDir "src\bindings\javascript") -Force

Write-Host " * src/bindings/node ==> $resolvedTargetDir\src\bindings\node"
Copy-DirectoryContents (Get-RepoPath "src\bindings\node") (Join-Path $resolvedTargetDir "src\bindings\node")

Write-Host " * src/bindings/javascript/pdg.js ==> $resolvedTargetDir\lib\pdg.js"
New-Item -ItemType Directory -Path (Join-Path $resolvedTargetDir "lib") -Force | Out-Null
Copy-Item -LiteralPath (Get-RepoPath "src\bindings\javascript\pdg.js") -Destination (Join-Path $resolvedTargetDir "lib\pdg.js") -Force

Write-Host " * src/js ==> $resolvedTargetDir\lib"
Copy-DirectoryContents (Get-RepoPath "src\js") (Join-Path $resolvedTargetDir "lib")

Write-Host " * src/inc ==> $resolvedTargetDir\src\inc"
Copy-TreeFiltered (Get-RepoPath "src\inc") (Join-Path $resolvedTargetDir "src\inc") {
    param($relativePath, $item)
    $normalizedPath = $relativePath -replace '/', '\'
    return $normalizedPath -eq "pdg\app" -or $normalizedPath.StartsWith("pdg\app\")
}

Write-Host " * src/sys ==> $resolvedTargetDir\src\sys"
Copy-TreeFiltered (Get-RepoPath "src\sys") (Join-Path $resolvedTargetDir "src\sys") {
    param($relativePath, $item)
    $segments = ($relativePath -replace '/', '\').Split('\', [System.StringSplitOptions]::RemoveEmptyEntries)
    return ($segments -contains "gles") -or ($segments -contains "ios") -or ($segments -contains "ipad")
}

Copy-Item -LiteralPath (Get-RepoPath "src\sys\macosx\platform-image-macosx.mm") -Destination (Join-Path $resolvedTargetDir "src\sys\macosx\platform-image-macosx-objc.cxx") -Force

Write-Host " * tools/node-pdg/* ==> $resolvedTargetDir"
Get-ChildItem -LiteralPath (Get-RepoPath "tools\node-pdg") -File | Copy-Item -Destination $resolvedTargetDir -Force
if (Test-Path (Join-Path $resolvedTargetDir "npm_ignore")) {
    Move-Item -LiteralPath (Join-Path $resolvedTargetDir "npm_ignore") -Destination (Join-Path $resolvedTargetDir ".npmignore") -Force
}

Write-Host " * deps/chipmunk/include ==> $resolvedTargetDir\deps\chipmunk\include"
Copy-DirectoryContents (Get-RepoPath "deps\chipmunk\include") (Join-Path $resolvedTargetDir "deps\chipmunk\include")

Write-Host " * deps/chipmunk/src ==> $resolvedTargetDir\deps\chipmunk\src"
Copy-DirectoryContents (Get-RepoPath "deps\chipmunk\src") (Join-Path $resolvedTargetDir "deps\chipmunk\src")

Write-Host " * deps/chipmunk/LICENSE.txt ==> $resolvedTargetDir\deps\chipmunk\LICENSE.txt"
Copy-Item -LiteralPath (Get-RepoPath "deps\chipmunk\LICENSE.txt") -Destination (Join-Path $resolvedTargetDir "deps\chipmunk\LICENSE.txt") -Force

Write-Host " * deps/glfw/include ==> $resolvedTargetDir\deps\glfw\include"
Copy-DirectoryContents (Get-RepoPath "deps\glfw\include") (Join-Path $resolvedTargetDir "deps\glfw\include")

Write-Host " * deps/glfw/src ==> $resolvedTargetDir\deps\glfw\src"
Copy-DirectoryContents (Get-RepoPath "deps\glfw\src") (Join-Path $resolvedTargetDir "deps\glfw\src")

Write-Host " * deps/glm ==> $resolvedTargetDir\deps\glm"
Copy-DirectoryContents (Get-RepoPath "deps\glm") (Join-Path $resolvedTargetDir "deps\glm")

Write-Host " * deps/SpriterPlusPlus ==> $resolvedTargetDir\deps\SpriterPlusPlus"
Copy-DirectoryContents (Get-RepoPath "deps\SpriterPlusPlus") (Join-Path $resolvedTargetDir "deps\SpriterPlusPlus")

Write-Host " * deps/node/deps/zlib ==> $resolvedTargetDir\deps\zlib"
Copy-DirectoryContents (Get-RepoPath "deps\node\deps\zlib") (Join-Path $resolvedTargetDir "deps\zlib")

Write-Host " * deps/minizip ==> $resolvedTargetDir\deps\minizip"
Copy-DirectoryContents (Get-RepoPath "deps\minizip") (Join-Path $resolvedTargetDir "deps\minizip")

Write-Host " * deps/png ==> $resolvedTargetDir\deps\png"
Copy-DirectoryContents (Get-RepoPath "deps\png") (Join-Path $resolvedTargetDir "deps\png")
Remove-Item -LiteralPath (Join-Path $resolvedTargetDir "deps\png\.gitignore") -Force -ErrorAction SilentlyContinue

Write-Host " * docs/javascript/man/* ==> $resolvedTargetDir\man"
Copy-DirectoryContents (Get-RepoPath "docs\javascript\man") (Join-Path $resolvedTargetDir "man")

Write-Host " * VERSION ==> $resolvedTargetDir"
Copy-Item -LiteralPath (Get-RepoPath "VERSION") -Destination (Join-Path $resolvedTargetDir "VERSION") -Force

Write-Host "Copied all source files to $resolvedTargetDir." -ForegroundColor Green
