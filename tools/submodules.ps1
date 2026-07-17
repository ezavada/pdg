function Ensure-RepoSubmodule {
    param(
        [Parameter(Mandatory = $true)]
        [string]$RepoRoot,
        [Parameter(Mandatory = $true)]
        [string]$SubmodulePath,
        [Parameter(Mandatory = $true)]
        [string]$SentinelRelativePath,
        [string]$DisplayName = $SubmodulePath
    )

    $sentinelPath = Join-Path $RepoRoot $SentinelRelativePath
    if (Test-Path $sentinelPath) {
        return $true
    }

    Write-Host "WARNING: $DisplayName is not checked out at $SubmodulePath" -ForegroundColor Yellow

    $gitCommand = Get-Command git -ErrorAction SilentlyContinue
    if (-not $gitCommand) {
        Write-Host "ERROR: git is required to populate $SubmodulePath." -ForegroundColor Red
        Write-Host "Run: git submodule update --init --recursive $SubmodulePath" -ForegroundColor Yellow
        return $false
    }

    Write-Host "Initializing $DisplayName from git submodule $SubmodulePath..." -ForegroundColor Cyan

    Push-Location $RepoRoot
    try {
        & $gitCommand.Source submodule update --init --checkout --recursive -- $SubmodulePath
        if ($LASTEXITCODE -ne 0) {
            Write-Host "ERROR: unable to populate $SubmodulePath via git submodule update." -ForegroundColor Red
            return $false
        }
    }
    finally {
        Pop-Location
    }

    if (-not (Test-Path $sentinelPath)) {
        Write-Host "ERROR: $DisplayName is still missing after submodule initialization." -ForegroundColor Red
        return $false
    }

    return $true
}
