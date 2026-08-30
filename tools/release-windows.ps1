param(
    [string]$Tag,
    [switch]$Configure,
    [string]$OutputDirectory
)

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$pdgRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
if ([string]::IsNullOrWhiteSpace($OutputDirectory)) {
    $OutputDirectory = Join-Path $pdgRoot "artifacts\release"
}

Push-Location $pdgRoot
try {
    if ([string]::IsNullOrWhiteSpace($Tag)) {
        $Tag = (& git describe --tags --exact-match HEAD 2>$null)
        if ($LASTEXITCODE -ne 0 -or [string]::IsNullOrWhiteSpace($Tag)) {
            throw "HEAD is not tagged. Pass -Tag vMAJOR.MINOR.PATCH when validating a prospective release locally."
        }
    }

    & cmake "-DPDG_SOURCE_DIR=$pdgRoot" "-DRELEASE_TAG=$Tag" -P "cmake\ValidateReleaseVersion.cmake"
    if ($LASTEXITCODE -ne 0) { throw "Release version validation failed." }

    $version = (Get-Content "VERSION" -Raw).Trim()
    $buildCache = Join-Path $pdgRoot "msvc\CMakeCache.txt"
    if ($Configure -or -not (Test-Path $buildCache)) {
        & powershell -NoProfile -ExecutionPolicy Bypass -File ".\configure.ps1" -SkipInstall
        if ($LASTEXITCODE -ne 0) { throw "Windows configuration failed." }
    }

    $cmakeArguments = @(
        "-S", ".",
        "-B", "msvc",
        "-DBUILD_TESTING=ON",
        "-DCAN_BUILD_INTERFACES=OFF",
        "-DPDG_HEADLESS=OFF"
    )
    & cmake @cmakeArguments
    if ($LASTEXITCODE -ne 0) { throw "CMake release configuration failed." }

    if (-not (Test-Path ".\make.ps1")) {
        Copy-Item ".\tools\make_ps1" ".\make.ps1"
    }
    & powershell -NoProfile -ExecutionPolicy Bypass -File ".\make.ps1" -Target pdg -Config Release
    if ($LASTEXITCODE -ne 0) { throw "Windows release build failed." }

    & cmake --build msvc --config Release --target pdg-app-view-utils-tests pdg-app-framework-tests --parallel
    if ($LASTEXITCODE -ne 0) { throw "Windows native test build failed." }

    & ctest --test-dir msvc --build-config Release --output-on-failure
    if ($LASTEXITCODE -ne 0) { throw "Native tests failed." }
    if (-not (Test-Path ".\node_modules\jasmine-node\package.json")) {
        $nodeExe = Join-Path $pdgRoot "tools\node.exe"
        if (-not (Test-Path $nodeExe)) {
            $nodeExe = Join-Path $pdgRoot "deps\node\out\Release\node.exe"
        }
        $npmCli = Join-Path $pdgRoot "deps\node\deps\npm\bin\npm-cli.js"
        if (-not (Test-Path $nodeExe) -or -not (Test-Path $npmCli)) {
            throw "The locally built Node.js and its npm CLI are required to install the JavaScript test runner."
        }
        & $nodeExe $npmCli install --no-save --package-lock=false jasmine-node@1.16.0
        if ($LASTEXITCODE -ne 0) { throw "JavaScript test dependency installation failed." }
    }
    # The npm/native Node plugin is released separately by the pdg-node target.
    & cmd /c ".\test\client.bat"
    if ($LASTEXITCODE -ne 0) { throw "Client JavaScript tests failed." }

    # The symbol/debug package uses RelWithDebInfo so it can reuse the Release-built
    # third-party libraries, including Node. It still compiles PDG with DEBUG=1.
    $releaseDependencyLibraries = @(
        "build\win32\glfw\src\Release\glfw3.lib",
        "build\win32\glfw\src\glfw3.lib",
        "build\win32\chipmunk\src\Release\chipmunk.lib",
        "build\win32\chipmunk\src\chipmunk.lib",
        "build\win32\libjpeg-turbo\Release\jpeg.lib",
        "build\win32\libjpeg-turbo\jpeg.lib"
    )
    foreach ($library in $releaseDependencyLibraries) {
        if (-not (Test-Path $library)) {
            throw "Expected Windows release dependency library was not produced: $library"
        }
    }

    # Build a distinct executable with DEBUG logging and PDB symbols.
    & cmake --build msvc --config RelWithDebInfo --target pdg --parallel
    if ($LASTEXITCODE -ne 0) { throw "Windows debug build failed." }

    $sourceExe = Join-Path $pdgRoot "msvc\src\Release\pdg.exe"
    $sourceDebugExe = Join-Path $pdgRoot "msvc\src\RelWithDebInfo\pdg-debug.exe"
    $sourceDebugPdb = Join-Path $pdgRoot "msvc\src\RelWithDebInfo\pdg-debug.pdb"
    foreach ($requiredFile in @($sourceExe, $sourceDebugExe, $sourceDebugPdb)) {
        if (-not (Test-Path $requiredFile)) {
            throw "Expected release file was not produced: $requiredFile"
        }
    }

    $assetBaseName = "pdg-v$version-windows-x64"
    $debugAssetBaseName = "pdg-debug-v$version-windows-x64"
    $stageDirectory = Join-Path $OutputDirectory "stage\$assetBaseName"
    $debugStageDirectory = Join-Path $OutputDirectory "stage\$debugAssetBaseName"
    $assetPath = Join-Path $OutputDirectory "$assetBaseName.zip"
    $debugAssetPath = Join-Path $OutputDirectory "$debugAssetBaseName.zip"
    $checksumPath = "$assetPath.sha256"
    $debugChecksumPath = "$debugAssetPath.sha256"

    if (Test-Path $stageDirectory) { Remove-Item $stageDirectory -Recurse -Force }
    if (Test-Path $debugStageDirectory) { Remove-Item $debugStageDirectory -Recurse -Force }
    New-Item -ItemType Directory -Path $stageDirectory -Force | Out-Null
    New-Item -ItemType Directory -Path $debugStageDirectory -Force | Out-Null
    Copy-Item $sourceExe (Join-Path $stageDirectory "pdg.exe")
    Copy-Item $sourceDebugExe (Join-Path $debugStageDirectory "pdg-debug.exe")
    Copy-Item $sourceDebugPdb (Join-Path $debugStageDirectory "pdg-debug.pdb")
    Copy-Item "LICENSE", "README.md", "VERSION" $stageDirectory
    Copy-Item "LICENSE", "README.md", "VERSION" $debugStageDirectory
    $thirdPartyLicenses = [ordered]@{
        "chipmunk.txt" = "deps\chipmunk\LICENSE.txt"
        "glfw.txt" = "deps\glfw\LICENSE.md"
        "glm.txt" = "deps\glm\copying.txt"
        "libjpeg-turbo.txt" = "deps\libjpeg-turbo\LICENSE.md"
        "libjpeg-turbo-IJG.txt" = "deps\libjpeg-turbo\README.ijg"
        "libtess2.txt" = "deps\libtess2\LICENSE.txt"
        "minizip.txt" = "deps\minizip\LICENSE"
        "node.txt" = "deps\node\LICENSE"
        "libpng.txt" = "deps\png\LICENSE"
        "SpriterPlusPlus.txt" = "deps\SpriterPlusPlus\LICENSE"
        "tinyxml2.txt" = "deps\SpriterPlusPlus\tinyxml2\license.txt"
    }
    foreach ($packageDirectory in @($stageDirectory, $debugStageDirectory)) {
        $noticesDirectory = Join-Path $packageDirectory "THIRD_PARTY_LICENSES"
        New-Item -ItemType Directory -Path $noticesDirectory -Force | Out-Null
        foreach ($notice in $thirdPartyLicenses.GetEnumerator()) {
            Copy-Item $notice.Value (Join-Path $noticesDirectory $notice.Key)
        }
    }

    # Smoke-test both staged executables rather than their build-tree copies.
    & (Join-Path $stageDirectory "pdg.exe") ".\test\misc\test_exit.js"
    if ($LASTEXITCODE -ne 0) { throw "Packaged release executable smoke test failed." }
    & (Join-Path $debugStageDirectory "pdg-debug.exe") ".\test\misc\test_exit.js"
    if ($LASTEXITCODE -ne 0) { throw "Packaged debug executable smoke test failed." }

    New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
    if (Test-Path $assetPath) { Remove-Item $assetPath -Force }
    if (Test-Path $checksumPath) { Remove-Item $checksumPath -Force }
    if (Test-Path $debugAssetPath) { Remove-Item $debugAssetPath -Force }
    if (Test-Path $debugChecksumPath) { Remove-Item $debugChecksumPath -Force }
    Compress-Archive -Path (Join-Path $stageDirectory "*") -DestinationPath $assetPath -CompressionLevel Optimal
    Compress-Archive -Path (Join-Path $debugStageDirectory "*") -DestinationPath $debugAssetPath -CompressionLevel Optimal

    $hash = (Get-FileHash -Algorithm SHA256 $assetPath).Hash.ToLowerInvariant()
    "$hash  $([System.IO.Path]::GetFileName($assetPath))" | Set-Content -Path $checksumPath -Encoding ascii
    $debugHash = (Get-FileHash -Algorithm SHA256 $debugAssetPath).Hash.ToLowerInvariant()
    "$debugHash  $([System.IO.Path]::GetFileName($debugAssetPath))" | Set-Content -Path $debugChecksumPath -Encoding ascii

    Write-Host "Created $assetPath"
    Write-Host "Created $checksumPath"
    Write-Host "Created $debugAssetPath"
    Write-Host "Created $debugChecksumPath"
}
finally {
    Pop-Location
}
