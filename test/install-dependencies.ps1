# PowerShell script to install Node.js dependencies for PDG tests
# Uses npm to properly install packages with all their dependencies

Write-Host "Installing Node.js dependencies for PDG tests..." -ForegroundColor Green

$PDG_ROOT = Get-Location
$nodeModulesPath = Join-Path $PDG_ROOT "node_modules"
$toolsPath = Join-Path $PDG_ROOT "tools"

# Create node_modules directory if it doesn't exist
if (!(Test-Path $nodeModulesPath)) {
    New-Item -ItemType Directory -Path $nodeModulesPath | Out-Null
    Write-Host "Created node_modules directory" -ForegroundColor Yellow
}

# Check if jasmine-node is already installed
$jasmineNodePath = Join-Path $nodeModulesPath "jasmine-node"
if (Test-Path (Join-Path $jasmineNodePath "package.json")) {
    Write-Host "jasmine-node is already installed" -ForegroundColor Green
    exit 0
}

# Check if npm exists in tools, if not install it
$npmPath = Join-Path $toolsPath "npm"
if (!(Test-Path $npmPath)) {
    Write-Host "npm not found in tools, installing npm..." -ForegroundColor Yellow
    
    # Create tools directory if it doesn't exist
    if (!(Test-Path $toolsPath)) {
        New-Item -ItemType Directory -Path $toolsPath -Force | Out-Null
    }
    
    # Download npm
    $npmUrl = "https://registry.npmjs.org/npm/-/npm-11.5.0.tgz"
    $npmTgz = "npm-11.5.0.tgz"
    
    try {
        Invoke-WebRequest -Uri $npmUrl -OutFile $npmTgz
        Write-Host "Downloaded npm package" -ForegroundColor Green
        
        # Extract npm
        $npmTempDir = "npm-temp"
        if (Test-Path $npmTempDir) {
            Remove-Item -Recurse -Force $npmTempDir
        }
        New-Item -ItemType Directory -Path $npmTempDir | Out-Null
        
        # Extract using 7-Zip or tar
        $sevenZipPath = "C:\Program Files\7-Zip\7z.exe"
        if (Test-Path $sevenZipPath) {
            & $sevenZipPath x $npmTgz -o$npmTempDir
        } else {
            $tarPath = "tar.exe"
            if (Get-Command $tarPath -ErrorAction SilentlyContinue) {
                & $tarPath -xzf $npmTgz -C $npmTempDir
            } else {
                Write-Host "No suitable extraction tool found. Please install 7-Zip or use Windows 10+" -ForegroundColor Red
                exit 1
            }
        }
        
        # Copy npm to deps/node
        $extractedNpm = Get-ChildItem $npmTempDir -Directory | Select-Object -First 1
        if ($extractedNpm) {
            Copy-Item -Path $extractedNpm.FullName -Destination $npmPath -Recurse
            Write-Host "Installed npm to deps/node" -ForegroundColor Green
        }
        
        # Clean up
        Remove-Item -Recurse -Force $npmTempDir -ErrorAction SilentlyContinue
        Remove-Item $npmTgz -ErrorAction SilentlyContinue
        
    } catch {
        Write-Host "Failed to install npm: $($_.Exception.Message)" -ForegroundColor Red
        exit 1
    }
}

# Set up npm executable path
$npmExe = Join-Path $npmPath "bin\npm-cli.js"
$nodeExe = Join-Path $toolsPath "node.exe"

Write-Host "Installing jasmine-node@1.16.0 and dependencies using npm..." -ForegroundColor Yellow

# Temporarily rename package.json to avoid installing pdg dependency
$originalPackageJsonPath = Join-Path $PDG_ROOT "package.json"
$backupPackageJsonPath = Join-Path $PDG_ROOT "package.json.backup"

try {
    # Backup original package.json
    if (Test-Path $originalPackageJsonPath) {
        Move-Item $originalPackageJsonPath $backupPackageJsonPath -Force
    }
    
    # Run npm install directly for jasmine-node without package.json
    $npmArgs = @($npmExe, "install", "jasmine-node@1.16.0", "--no-save")
    $process = Start-Process -FilePath $nodeExe -ArgumentList $npmArgs -WorkingDirectory $PDG_ROOT -Wait -PassThru -NoNewWindow
    
    if ($process.ExitCode -eq 0) {
        Write-Host "Successfully installed jasmine-node and dependencies using npm" -ForegroundColor Green
    } else {
        Write-Host "npm install failed with exit code: $($process.ExitCode)" -ForegroundColor Red
        exit 1
    }
} catch {
    Write-Host "Failed to run npm install: $($_.Exception.Message)" -ForegroundColor Red
    exit 1
} finally {
    # Restore original package.json
    if (Test-Path $backupPackageJsonPath) {
        Move-Item $backupPackageJsonPath $originalPackageJsonPath -Force
    }
}

# Create symlink in tools directory (fallback to copy if symlink fails)
$toolsJasmineNode = Join-Path $toolsPath "jasmine-node"
$jasmineNodeBin = Join-Path $jasmineNodePath "bin\jasmine-node"

if (Test-Path $toolsJasmineNode) {
    Remove-Item $toolsJasmineNode -Force
}

if (Test-Path $jasmineNodeBin) {
    try {
        # Try to create symbolic link first
        New-Item -ItemType SymbolicLink -Path $toolsJasmineNode -Target $jasmineNodeBin -ErrorAction Stop | Out-Null
        Write-Host "Created symlink for jasmine-node" -ForegroundColor Green
    } catch {
        # If symlink fails (no admin privileges), copy the file instead
        Write-Host "Symlink creation failed (admin privileges required), copying file instead..." -ForegroundColor Yellow
        Copy-Item -Path $jasmineNodeBin -Destination $toolsJasmineNode -Force
        Write-Host "Copied jasmine-node to tools directory" -ForegroundColor Green
    }
}

# Install other required packages using npm
Write-Host "Installing net-repl@0.1.2 using npm..." -ForegroundColor Yellow
try {
    # Run npm install for net-repl using PDG's node executable
    $npmArgs = @($npmExe, "install", "net-repl@0.1.2", "--no-save")
    $process = Start-Process -FilePath $nodeExe -ArgumentList $npmArgs -WorkingDirectory $PDG_ROOT -Wait -PassThru -NoNewWindow
    
    if ($process.ExitCode -eq 0) {
        Write-Host "Successfully installed net-repl using npm" -ForegroundColor Green
        
        # Create symlink (fallback to copy if symlink fails)
        $netReplPath = Join-Path $nodeModulesPath "net-repl"
        $toolsRepl = Join-Path $PDG_ROOT "tools\repl"
        $netReplBin = Join-Path $netReplPath "bin\repl.js"
        
        if (Test-Path $toolsRepl) {
            Remove-Item $toolsRepl -Force
        }
        
        if (Test-Path $netReplBin) {
            try {
                # Try to create symbolic link first
                New-Item -ItemType SymbolicLink -Path $toolsRepl -Target $netReplBin -ErrorAction Stop | Out-Null
                Write-Host "Created symlink for net-repl" -ForegroundColor Green
            } catch {
                # If symlink fails (no admin privileges), copy the file instead
                Write-Host "Symlink creation failed (admin privileges required), copying file instead..." -ForegroundColor Yellow
                Copy-Item -Path $netReplBin -Destination $toolsRepl -Force
                Write-Host "Copied net-repl to tools directory" -ForegroundColor Green
            }
        }
    } else {
        Write-Host "npm install for net-repl failed with exit code: $($process.ExitCode)" -ForegroundColor Yellow
    }
} catch {
    Write-Host "Failed to install net-repl with npm: $($_.Exception.Message)" -ForegroundColor Yellow
}

# Clean up any temporary files (npm handles its own cleanup)
try {
    if (Test-Path "npm-temp") {
        Remove-Item -Recurse -Force "npm-temp" -ErrorAction SilentlyContinue
    }
    if (Test-Path "npm-11.5.0.tgz") {
        Remove-Item "npm-11.5.0.tgz" -ErrorAction SilentlyContinue
    }
} catch {
    Write-Host "Warning: Could not clean up temporary files: $($_.Exception.Message)" -ForegroundColor Yellow
}

# Verify installation
$success = $true
if (!(Test-Path (Join-Path $jasmineNodePath "package.json"))) {
    Write-Host "ERROR: jasmine-node installation failed" -ForegroundColor Red
    $success = $false
}

if (!(Test-Path (Join-Path $nodeModulesPath "net-repl\package.json"))) {
    Write-Host "WARNING: net-repl installation failed or skipped" -ForegroundColor Yellow
}

if ($success) {
    Write-Host "Dependencies installation completed successfully!" -ForegroundColor Green
} else {
    Write-Host "Dependencies installation completed with errors!" -ForegroundColor Red
    exit 1
}
