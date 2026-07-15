# PDG Dependency Installation Script (Visual Studio Build Tools + ClangCL)
# PowerShell script to install all required dependencies for PDG development

param(
    [switch]$Force,
    [switch]$Help,
    [switch]$SkipInstall,
    [switch]$ConfigureOnly,
    [switch]$SkipInterfaceTools,
    [switch]$EnableInterfaceTools
)

# Function to display help
function Show-Help {
    Write-Host "PDG Dependency Installation Script (Visual Studio + ClangCL)" -ForegroundColor Cyan
    Write-Host "=============================================================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Usage: .\configure.ps1 [options]" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Options:" -ForegroundColor Yellow
    Write-Host "  -Force          Force reinstallation even if dependencies are already installed" -ForegroundColor White
    Write-Host "  -SkipInstall    Skip installation and only configure existing dependencies" -ForegroundColor White
    Write-Host "  -ConfigureOnly  Only run configuration steps, skip dependency detection/installation" -ForegroundColor White
    Write-Host "  -EnableInterfaceTools  Build bcpp and enable CAN_BUILD_INTERFACES (default: OFF)" -ForegroundColor White
    Write-Host "  -SkipInterfaceTools    Legacy flag; keeps interface tools disabled" -ForegroundColor White
    Write-Host "  -Help           Show this help message" -ForegroundColor White
    Write-Host ""
    Write-Host "This script will install and configure all dependencies required for PDG development:" -ForegroundColor White
    Write-Host "  - CMake (build system)" -ForegroundColor Gray
    Write-Host "  - Visual Studio Build Tools with ClangCL (C++ compiler)" -ForegroundColor Gray
    Write-Host "  - Python (for Node.js build)" -ForegroundColor Gray
    Write-Host "  - Windows SDK (for Windows development)" -ForegroundColor Gray
    Write-Host "  - NASM (assembly compiler for SIMD optimizations)" -ForegroundColor Gray
    Write-Host ""
    Write-Host "This configuration uses Visual Studio Build Tools with ClangCL for maximum" -ForegroundColor White
    Write-Host "compatibility with Node.js v24+ and Windows development." -ForegroundColor White
}

# Show help if requested
if ($Help) {
    Show-Help
    exit 0
}

# Function to write colored output
function Write-Status {
    param([string]$Message, [string]$Color = "White")
    Write-Host $Message -ForegroundColor $Color
}

function Write-Error-Status {
    param([string]$Message)
    Write-Host "ERROR: $Message" -ForegroundColor Red
}

function Write-Success-Status {
    param([string]$Message)
    Write-Host "SUCCESS: $Message" -ForegroundColor Green
}

function Write-Warning-Status {
    param([string]$Message)
    Write-Host "WARNING: $Message" -ForegroundColor Yellow
}

# Function to check if a command exists
function Test-Command {
    param([string]$Command)
    try {
        Get-Command $Command -ErrorAction Stop | Out-Null
        return $true
    }
    catch {
        return $false
    }
}

# Function to get version of a command
function Get-CommandVersion {
    param([string]$Command, [string]$VersionArg = "--version")
    try {
        $version = & $Command $VersionArg 2>$null | Select-Object -First 1
        return $version
    }
    catch {
        return $null
    }
}

# Function to refresh PATH environment variable
function Refresh-Path {
    param([switch]$Force = $false)
    
    # Check if we already have a manually configured environment
    $hasManualEnv = $env:CC -or $env:CXX -or $env:CMAKE_C_COMPILER -or $env:CMAKE_CXX_COMPILER
    
    if ($hasManualEnv -and -not $Force) {
        Write-Status "Skipping PATH refresh - manual environment detected" "Cyan"
        return
    }
    
    Write-Status "Refreshing PATH environment variable..." "Cyan"
    $machinePath = [System.Environment]::GetEnvironmentVariable("PATH", "Machine")
    $userPath = [System.Environment]::GetEnvironmentVariable("PATH", "User")
    $env:PATH = $machinePath + ";" + $userPath
    Write-Success-Status "PATH refreshed successfully"
}

# Function to wait for PATH updates and retry
function Wait-For-Path-Update {
    param([string]$Command, [int]$MaxRetries = 3, [int]$DelaySeconds = 2)
    
    for ($i = 1; $i -le $MaxRetries; $i++) {
        if (Test-Command $Command) {
            return $true
        }
        
        if ($i -lt $MaxRetries) {
            Write-Status "Waiting for $Command to become available (attempt $i/$MaxRetries)..." "Yellow"
            Start-Sleep -Seconds $DelaySeconds
            Refresh-Path -Force
        }
    }
    
    return $false
}

# Function to find dependency in common installation paths
function Find-DependencyInPaths {
    param([string]$Command, [string[]]$CommonPaths)
    
    foreach ($path in $CommonPaths) {
        if (Test-Path $path) {
            Write-Status "Found $Command at: $path" "Green"
            return $path
        }
    }
    return $null
}

# Function to install dependency via winget
function Install-Dependency {
    param(
        [string]$PackageId,
        [string]$PackageName,
        [string]$Command,
        [string]$VersionArg = "--version",
        [string[]]$CommonPaths = @(),
        [string]$PostInstallMessage = ""
    )
    
    Write-Status "Installing $PackageName via winget..." "Cyan"
    try {
        $installProcess = Start-Process -FilePath "winget" -ArgumentList @("install", $PackageId, "--accept-package-agreements", "--accept-source-agreements", "--silent") -Wait -PassThru -NoNewWindow
        
        if ($installProcess.ExitCode -eq 0) {
            Write-Success-Status "$PackageName installed successfully!"
            
            # Refresh PATH
            Refresh-Path -Force
            
            # Wait for command to become available
            if (Wait-For-Path-Update -Command $Command) {
                Write-Success-Status "$PackageName is now available in PATH!"
                if ($PostInstallMessage) {
                    Write-Status $PostInstallMessage "Cyan"
                }
                return $true
            }
            else {
                # Try to find in common paths
                $foundPath = Find-DependencyInPaths -Command $Command -CommonPaths $CommonPaths
                if ($foundPath) {
                    Write-Success-Status "$PackageName installed at: $foundPath"
                    return $foundPath
                }
                else {
                    Write-Warning-Status "$PackageName installed but not yet available in PATH"
                    Write-Host "You may need to restart your shell." -ForegroundColor Yellow
                    return $true
                }
            }
        }
        else {
            Write-Error-Status "Failed to install $PackageName via winget (exit code: $($installProcess.ExitCode))"
            return $false
        }
    }
    catch {
        Write-Error-Status "Error installing $PackageName`: $($_)"
        return $false
    }
}

# Function to show manual installation instructions
function Show-ManualInstallInstructions {
    param(
        [string]$PackageName,
        [string[]]$WingetCommand,
        [string[]]$ChocoCommand,
        [string]$DownloadUrl,
        [string]$AdditionalInstructions = ""
    )
    
    Write-Host ""
    Write-Host "==========================================" -ForegroundColor Cyan
    Write-Host "$PackageName Installation Required" -ForegroundColor Cyan
    Write-Host "==========================================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Please install $PackageName using one of these methods:" -ForegroundColor White
    Write-Host ""
    
    if ($WingetCommand) {
        Write-Host "1. Windows Package Manager (Recommended):" -ForegroundColor Green
        foreach ($cmd in $WingetCommand) {
            Write-Host "   winget install $cmd" -ForegroundColor Gray
        }
        Write-Host ""
    }
    
    if ($ChocoCommand) {
        Write-Host "2. Chocolatey:" -ForegroundColor Green
        foreach ($cmd in $ChocoCommand) {
            Write-Host "   choco install $cmd" -ForegroundColor Gray
        }
        Write-Host ""
    }
    
    if ($DownloadUrl) {
        Write-Host "3. Direct Download:" -ForegroundColor Green
        Write-Host "   $DownloadUrl" -ForegroundColor Gray
        Write-Host ""
    }
    
    if ($AdditionalInstructions) {
        Write-Host "Additional Instructions:" -ForegroundColor Yellow
        Write-Host $AdditionalInstructions -ForegroundColor White
        Write-Host ""
    }
    
    Write-Host "After installing $PackageName, restart your PowerShell session" -ForegroundColor Yellow
    Write-Host "and run this script again." -ForegroundColor Yellow
    Write-Host ""
    Write-Host "==========================================" -ForegroundColor Cyan
}

# Function to check and install CMake
function Check-And-Install-CMake {
    param([string]$LocalVarName = "CMAKE_PATH")
    
    Write-Status "Checking for CMake..." "Cyan"
    
    # Check if CMake is in PATH
    if (Test-Command "cmake") {
        $version = Get-CommandVersion -Command "cmake"
        Write-Status "Found CMake in PATH: $version" "Green"
        Set-Variable -Name $LocalVarName -Value "cmake" -Scope Script
        return $true
    }
    
    # Check common installation paths
    $cmakePaths = @(
        "C:\Program Files\CMake\bin\cmake.exe",
        "C:\Program Files (x86)\CMake\bin\cmake.exe",
        "C:\cmake\bin\cmake.exe"
    )
    
    $foundPath = Find-DependencyInPaths -Command "cmake" -CommonPaths $cmakePaths
    if ($foundPath) {
        Set-Variable -Name $LocalVarName -Value $foundPath -Scope Script
        return $true
    }
    
    if ($SkipInstall) {
        Show-ManualInstallInstructions -PackageName "CMake" -WingetCommand @("Kitware.CMake") -ChocoCommand @("cmake") -DownloadUrl "https://cmake.org/download/"
        return $false
    }
    
    # Ask user if they want to install
    $install = Read-Host "Would you like to install CMake automatically using winget? (y/n)"
    if ($install -eq "y" -or $install -eq "Y") {
        if (Install-Dependency -PackageId "Kitware.CMake" -PackageName "CMake" -Command "cmake" -CommonPaths $cmakePaths) {
            Set-Variable -Name $LocalVarName -Value "cmake" -Scope Script
            return $true
        }
    }
    
    Show-ManualInstallInstructions -PackageName "CMake" -WingetCommand @("Kitware.CMake") -ChocoCommand @("cmake") -DownloadUrl "https://cmake.org/download/"
    return $false
}

# Function to check and install NASM
function Check-And-Install-NASM {
    param([string]$LocalVarName = "NASM_PATH")
    
    Write-Status "Checking for NASM..." "Cyan"
    
    # Check if NASM is in PATH
    if (Test-Command "nasm") {
        $version = Get-CommandVersion -Command "nasm" -VersionArg "-v"
        Write-Status "Found NASM in PATH: $version" "Green"
        Set-Variable -Name $LocalVarName -Value "nasm" -Scope Script
        return $true
    }
    
    # Check common installation paths
    $nasmPaths = @(
        "C:\Users\$env:USERNAME\AppData\Local\bin\NASM\nasm.exe",
        "C:\Program Files\NASM\nasm.exe",
        "C:\Program Files (x86)\NASM\nasm.exe",
        "C:\nasm\nasm.exe"
    )
    
    $foundPath = Find-DependencyInPaths -Command "nasm" -CommonPaths $nasmPaths
    if ($foundPath) {
        Set-Variable -Name $LocalVarName -Value $foundPath -Scope Script
        return $true
    }
    
    if ($SkipInstall) {
        Show-ManualInstallInstructions -PackageName "NASM" -WingetCommand @("NASM.NASM") -ChocoCommand @("nasm") -DownloadUrl "https://www.nasm.us/"
        return $false
    }
    
    # Ask user if they want to install
    $install = Read-Host "Would you like to install NASM automatically using winget? (y/n)"
    if ($install -eq "y" -or $install -eq "Y") {
        if (Install-Dependency -PackageId "NASM.NASM" -PackageName "NASM" -Command "nasm" -CommonPaths $nasmPaths -VersionArg "-v") {
            Set-Variable -Name $LocalVarName -Value "nasm" -Scope Script
            return $true
        }
    }
    
    Show-ManualInstallInstructions -PackageName "NASM" -WingetCommand @("NASM.NASM") -ChocoCommand @("nasm") -DownloadUrl "https://www.nasm.us/"
    return $false
}

# Function to check and install Python
# Node.js build requires Python 3.9 or newer and does not support Python 3.14+
function Check-And-Install-Python {
    param([string]$LocalVarName = "PYTHON_PATH")
    
    Write-Status "Checking for Python (3.9 to 3.13 required; 3.14+ not supported by Node.js)..." "Cyan"
    
    # Returns $true if version is Python 3.9 through 3.13 (rejects < 3.9 and >= 3.14)
    function Test-PythonVersionSupported {
        param([string]$VersionOutput)
        if (-not $VersionOutput -or $VersionOutput -like "*Microsoft Store*") { return $false }
        if ($VersionOutput -match "Python\s+(\d+)\.(\d+)") {
            $major = [int]$Matches[1]
            $minor = [int]$Matches[2]
            if ($major -lt 3) { return $false }
            if ($major -eq 3) {
                if ($minor -lt 9) { return $false }   # 3.9 minimum
                if ($minor -ge 14) { return $false }  # 3.14+ not supported
            }
            return $true
        }
        return $false
    }
    
    # Function to validate Python executable (works and version is 3.9-3.13)
    function Test-PythonExecutable {
        param([string]$Command)
        try {
            # Get the full path to the command
            $fullPath = (Get-Command $Command -ErrorAction Stop).Source
            
            # Skip Windows Store app aliases
            if ($fullPath -like "*WindowsApps*") {
                Write-Status "Skipping Windows Store Python alias: $fullPath" "Yellow"
                return $false
            }
            
            $version = Get-CommandVersion -Command $Command
            if (-not $version) { return $false }
            if (-not (Test-PythonVersionSupported -VersionOutput $version)) {
                if ($version -match "Python\s+3\.(\d+)") {
                    $minor = [int]$Matches[1]
                    if ($minor -lt 9) {
                        Write-Status "Python $version is too old. Node.js requires Python 3.9 or newer." "Yellow"
                    } else {
                        Write-Status "Python $version is not supported by Node.js. Please install Python 3.9-3.13." "Yellow"
                    }
                }
                return $false
            }
            return $true
        }
        catch {
            return $false
        }
    }
    
    # Check if Python is in PATH
    $pythonCommands = @("python", "python3", "py")
    foreach ($cmd in $pythonCommands) {
        if (Test-Command $cmd) {
            if (Test-PythonExecutable $cmd) {
                $version = Get-CommandVersion -Command $cmd
                Write-Status "Found Python in PATH ($cmd): $version" "Green"
                Set-Variable -Name $LocalVarName -Value $cmd -Scope Script
                return $true
            }
        }
    }
    
    # Check common installation paths (3.9-3.13 supported)
    $pythonPaths = @(
        "C:\Users\$env:USERNAME\AppData\Local\Programs\Python\Python313\python.exe",
        "C:\Users\$env:USERNAME\AppData\Local\Programs\Python\Python312\python.exe",
        "C:\Users\$env:USERNAME\AppData\Local\Programs\Python\Python311\python.exe",
        "C:\Users\$env:USERNAME\AppData\Local\Programs\Python\Python310\python.exe",
        "C:\Users\$env:USERNAME\AppData\Local\Programs\Python\Python39\python.exe",
        "C:\Python313\python.exe",
        "C:\Python312\python.exe",
        "C:\Python311\python.exe",
        "C:\Python310\python.exe",
        "C:\Python39\python.exe",
        "C:\Program Files\Python313\python.exe",
        "C:\Program Files\Python312\python.exe",
        "C:\Program Files\Python311\python.exe",
        "C:\Program Files\Python310\python.exe",
        "C:\Program Files\Python39\python.exe"
    )
    
    foreach ($pythonPath in $pythonPaths) {
        if (Test-Path $pythonPath) {
            try {
                $version = & $pythonPath --version 2>$null
                if ($version -and $version -notlike "*Microsoft Store*" -and (Test-PythonVersionSupported -VersionOutput $version)) {
                    Write-Status "Found Python at: $pythonPath ($version)" "Green"
                    Set-Variable -Name $LocalVarName -Value $pythonPath -Scope Script
                    return $true
                }
            }
            catch {
                # Continue to next path
            }
        }
    }
    
    if ($SkipInstall) {
        Show-ManualInstallInstructions -PackageName "Python 3.9-3.13 (Node.js requires 3.9+, does not support 3.14+)" -WingetCommand @("Python.Python.3.13", "Python.Python.3.12", "Python.Python.3.11") -ChocoCommand @("python") -DownloadUrl "https://www.python.org/downloads/" -AdditionalInstructions "Node.js requires Python 3.9 or newer and does not support Python 3.14+. If you have Python 3.14+ or an older Python (< 3.9), install Python 3.9-3.13 and ensure it appears first in PATH."
        return $false
    }
    
    # Ask user if they want to install
    Write-Status "Node.js build requires Python 3.9-3.13 (3.14+ not supported)." "Gray"
    $install = Read-Host "Would you like to install Python 3.13 automatically using winget? (y/n)"
    if ($install -eq "y" -or $install -eq "Y") {
        if (Install-Dependency -PackageId "Python.Python.3.13" -PackageName "Python 3.13" -Command "python" -CommonPaths $pythonPaths) {
            Set-Variable -Name $LocalVarName -Value "python" -Scope Script
            return $true
        }
    }
    
    Show-ManualInstallInstructions -PackageName "Python 3.9-3.13 (Node.js requires 3.9+, does not support 3.14+)" -WingetCommand @("Python.Python.3.13", "Python.Python.3.12", "Python.Python.3.11") -ChocoCommand @("python") -DownloadUrl "https://www.python.org/downloads/" -AdditionalInstructions "Node.js requires Python 3.9 or newer and does not support Python 3.14+. If you have Python 3.14+ or an older Python (< 3.9), install Python 3.9-3.13 and ensure it appears first in PATH."
    return $false
}


# Function to download Visual Studio Build Tools installer
function Download-VisualStudioInstaller {
    param([string]$InstallerPath = ".\vs_BuildTools.exe")
    
    if (Test-Path $InstallerPath) {
        Write-Status "Visual Studio Build Tools installer already exists" "Green"
                    return $true
    }
    
    Write-Status "Downloading Visual Studio Build Tools installer..." "Cyan"
    try {
        $downloadUrl = "https://aka.ms/vs/17/release/vs_BuildTools.exe"
        Invoke-WebRequest -Uri $downloadUrl -OutFile $InstallerPath -UseBasicParsing
        Write-Success-Status "Downloaded Visual Studio Build Tools installer"
                        return $true
            }
            catch {
        Write-Error-Status "Failed to download Visual Studio Build Tools installer: $($_)"
    return $false
    }
}

# Function to check Visual Studio components
function Test-VisualStudioComponents {
    param([string]$InstallPath)
    
    $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path $vsWhere)) { return $false }
    
    try {
        # Check if the installation has the required components by checking the installation path directly
        # First, verify the installation exists and has the basic structure
        if (-not (Test-Path $InstallPath)) { return $false }
        
        # Check for the presence of Clang in the expected location
        $clangPath = Join-Path $InstallPath "VC\Tools\Llvm\bin\clang.exe"
        if (-not (Test-Path $clangPath)) { return $false }
        
        # Check for vcvars64.bat which indicates VC tools are installed
        $vcvarsPath = Join-Path $InstallPath "VC\Auxiliary\Build\vcvars64.bat"
        if (-not (Test-Path $vcvarsPath)) { return $false }
        
        # If we get here, the essential components are present
        return $true
    }
    catch {
        return $false
    }
}

# Function to check and install Visual Studio Build Tools with ClangCL
function Check-And-Install-VisualStudio {
    param([string]$LocalVarName = "MSBUILD_PATH")
    
    Write-Status "Checking for Visual Studio Build Tools with ClangCL..." "Cyan"
    
    # Check for Visual Studio compiler using vswhere
    $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vsWhere) {
        try {
            # Look for Visual Studio with C++ tools and ClangCL
            $vsInstall = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -requires Microsoft.VisualStudio.Component.VC.Llvm.Clang -property installationPath
            if ($vsInstall) {
                Write-Status "Found Visual Studio with C++ tools and ClangCL at: $vsInstall" "Green"
                $vcvarsPath = Join-Path $vsInstall "VC\Auxiliary\Build\vcvars64.bat"
                if (Test-Path $vcvarsPath) {
                    Set-Variable -Name $LocalVarName -Value $vcvarsPath -Scope Script
                    return $true
                }
            }
            
            # Look for Build Tools with ClangCL
            $buildToolsInstall = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Workload.VCTools -requires Microsoft.VisualStudio.Component.VC.Llvm.Clang -property installationPath
            if ($buildToolsInstall) {
                # Check if all required components are present
                if (Test-VisualStudioComponents -InstallPath $buildToolsInstall) {
                    Write-Status "Found Visual Studio Build Tools with all required ClangCL components at: $buildToolsInstall" "Green"
                    $vcvarsPath = Join-Path $buildToolsInstall "VC\Auxiliary\Build\vcvars64.bat"
                    if (Test-Path $vcvarsPath) {
                        Set-Variable -Name $LocalVarName -Value $vcvarsPath -Scope Script
                        return $true
                    }
                } else {
                    Write-Status "Found Visual Studio Build Tools but missing some ClangCL components" "Yellow"
                    # Ask if user wants to add missing components
                    if (-not $SkipInstall) {
                        $addComponents = Read-Host "Would you like to add the missing ClangCL components? (y/n)"
                        if ($addComponents -eq "y" -or $addComponents -eq "Y") {
                            return Install-VisualStudioComponents -InstallPath $buildToolsInstall -LocalVarName $LocalVarName
                        } else {
                            # User declined to add components, show manual instructions
                            Show-ManualInstallInstructions -PackageName "Visual Studio Build Tools with ClangCL" -WingetCommand @("Download vs_BuildTools.exe from https://aka.ms/vs/17/release/vs_BuildTools.exe") -DownloadUrl "https://visualstudio.microsoft.com/downloads/" -AdditionalInstructions "Run: vs_BuildTools.exe --quiet --wait --norestart --nocache --add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.VC.Llvm.Clang --add Microsoft.VisualStudio.Component.VC.Llvm.ClangToolset"
                            return $false
                        }
                    } else {
                        # Skip install mode, show manual instructions
                        Show-ManualInstallInstructions -PackageName "Visual Studio Build Tools with ClangCL" -WingetCommand @("Download vs_BuildTools.exe from https://aka.ms/vs/17/release/vs_BuildTools.exe") -DownloadUrl "https://visualstudio.microsoft.com/downloads/" -AdditionalInstructions "Run: vs_BuildTools.exe --quiet --wait --norestart --nocache --add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.VC.Llvm.Clang --add Microsoft.VisualStudio.Component.VC.Llvm.ClangToolset"
                        return $false
                    }
                }
            }
        }
        catch {
            Write-Warning-Status "Error checking Visual Studio installations: $($_)"
        }
    }
    
    # No Visual Studio found, need to install
    if ($SkipInstall) {
        Show-ManualInstallInstructions -PackageName "Visual Studio Build Tools with ClangCL" -WingetCommand @("Download vs_BuildTools.exe from https://aka.ms/vs/17/release/vs_BuildTools.exe") -DownloadUrl "https://visualstudio.microsoft.com/downloads/" -AdditionalInstructions "Run: vs_BuildTools.exe --quiet --wait --norestart --nocache --add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.VC.Llvm.Clang --add Microsoft.VisualStudio.Component.VC.Llvm.ClangToolset"
        return $false
    }
    
    # Ask user if they want to install
    $install = Read-Host "Would you like to install Visual Studio Build Tools with ClangCL automatically? (y/n)"
    if ($install -eq "y" -or $install -eq "Y") {
        return Install-VisualStudioBuildTools -LocalVarName $LocalVarName
    }
    
    Show-ManualInstallInstructions -PackageName "Visual Studio Build Tools with ClangCL" -WingetCommand @("Download vs_BuildTools.exe from https://aka.ms/vs/17/release/vs_BuildTools.exe") -DownloadUrl "https://visualstudio.microsoft.com/downloads/" -AdditionalInstructions "Run: vs_BuildTools.exe --quiet --wait --norestart --nocache --add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.VC.Llvm.Clang --add Microsoft.VisualStudio.Component.VC.Llvm.ClangToolset"
    return $false
}

# Function to install Visual Studio components to existing installation
function Install-VisualStudioComponents {
    param([string]$InstallPath, [string]$LocalVarName = "MSBUILD_PATH")
    
    Write-Status "Adding missing ClangCL components to existing Visual Studio installation..." "Cyan"
    
    $vsInstallerPath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vs_installer.exe"
    if (-not (Test-Path $vsInstallerPath)) {
        Write-Error-Status "Visual Studio Installer not found"
        return $false
    }
    
    $modifyArgs = @(
        "modify",
        "--installPath", $InstallPath,
        "--quiet",
        "--norestart",
        "--add", "Microsoft.VisualStudio.Workload.VCTools",
        "--add", "Microsoft.VisualStudio.Component.VC.Llvm.Clang",
        "--add", "Microsoft.VisualStudio.Component.VC.Llvm.ClangToolset",
        "--add", "Microsoft.VisualStudio.Component.VC.Tools.x86.x64" # MSVC v143 - VS 2022 C++ x64/x86 build tools
    )
    
    try {
        $modifyProcess = Start-Process -FilePath $vsInstallerPath -ArgumentList $modifyArgs -Wait -PassThru -NoNewWindow
             
        if ($modifyProcess.ExitCode -eq 0) {
            Write-Success-Status "Successfully added ClangCL components!"
            Start-Sleep -Seconds 3
            Refresh-Path -Force
            
            # Verify installation
            $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
            if (Test-Path $vsWhere) {
                $buildToolsInstall = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Workload.VCTools -requires Microsoft.VisualStudio.Component.VC.Llvm.Clang -property installationPath
                if ($buildToolsInstall) {
                    $vcvarsPath = Join-Path $buildToolsInstall "VC\Auxiliary\Build\vcvars64.bat"
                    if (Test-Path $vcvarsPath) {
                        Set-Variable -Name $LocalVarName -Value $vcvarsPath -Scope Script
                        return $true
                    }
                }
            }
            return $true
        }
        else {
            Write-Error-Status "Failed to add components (exit code: $($modifyProcess.ExitCode))"
            return $false
        }
    }
    catch {
        Write-Error-Status "Error adding components: $($_)"
        return $false
    }
}

# Function to install Visual Studio Build Tools from scratch
function Install-VisualStudioBuildTools {
    param([string]$LocalVarName = "MSBUILD_PATH")
    
    Write-Status "Installing Visual Studio Build Tools with C++ workload and ClangCL..." "Cyan"
    
    # Download installer
    if (-not (Download-VisualStudioInstaller)) {
        Write-Error-Status "Failed to download Visual Studio Build Tools installer"
        return $false
    }
    
    # Use direct command-line installation (more reliable than config file)
    $installArgs = @(
        "--passive",
        "--wait", 
        "--norestart",
        "--nocache",
        "--add", "Microsoft.VisualStudio.Workload.VCTools",
        "--add", "Microsoft.VisualStudio.Component.VC.Llvm.Clang",
        "--add", "Microsoft.VisualStudio.Component.VC.Llvm.ClangToolset",
        "--add", "Microsoft.VisualStudio.Component.VC.Tools.x86.x64"
    )
    
    try {
        $installProcess = Start-Process -FilePath ".\vs_BuildTools.exe" -ArgumentList $installArgs -Wait -PassThru -NoNewWindow
               
        if ($installProcess.ExitCode -eq 0) {
            Write-Success-Status "Visual Studio Build Tools with ClangCL installed!"
            Start-Sleep -Seconds 5
            Refresh-Path -Force
            
            # Clean up installer files
            if (Test-Path ".\vs_BuildTools.exe") { Remove-Item ".\vs_BuildTools.exe" -Force }
            
            # Try to find the installation
            $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
            if (Test-Path $vsWhere) {
                $buildToolsInstall = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Workload.VCTools -requires Microsoft.VisualStudio.Component.VC.Llvm.Clang -property installationPath
                if ($buildToolsInstall) {
                    $vcvarsPath = Join-Path $buildToolsInstall "VC\Auxiliary\Build\vcvars64.bat"
                    if (Test-Path $vcvarsPath) {
                        Set-Variable -Name $LocalVarName -Value $vcvarsPath -Scope Script
                        return $true
                    }
                }
            }
            return $true
        }
        else {
            Write-Error-Status "Installation failed (exit code: $($installProcess.ExitCode))"
            Show-ManualInstallInstructions -PackageName "Visual Studio Build Tools with ClangCL" -WingetCommand @("Download vs_BuildTools.exe from https://aka.ms/vs/17/release/vs_BuildTools.exe") -DownloadUrl "https://visualstudio.microsoft.com/downloads/" -AdditionalInstructions "Run: vs_BuildTools.exe --quiet --wait --norestart --nocache --add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.VC.Llvm.Clang --add Microsoft.VisualStudio.Component.VC.Llvm.ClangToolset"
            return $false
        }
    }
    catch {
        Write-Error-Status "Error installing Visual Studio Build Tools: $($_)"
        Show-ManualInstallInstructions -PackageName "Visual Studio Build Tools with ClangCL" -WingetCommand @("Download vs_BuildTools.exe from https://aka.ms/vs/17/release/vs_BuildTools.exe") -DownloadUrl "https://visualstudio.microsoft.com/downloads/" -AdditionalInstructions "Run: vs_BuildTools.exe --quiet --wait --norestart --nocache --add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.VC.Llvm.Clang --add Microsoft.VisualStudio.Component.VC.Llvm.ClangToolset"
        return $false
    }
}

# Function to check Windows SDK
function Check-WindowsSDK {
    param([string]$LocalVarName = "WINDOWS_SDK_AVAILABLE")
    
    Write-Status "Checking for Windows SDK..." "Cyan"
    
    # Check for Windows SDK in common locations, prioritizing newer versions
    # only check for the versions we need to build Node.js v24
    $sdkPaths = @(
        "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0",
        "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0", 
        "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0"
    )
    
    foreach ($path in $sdkPaths) {
        if (Test-Path $path) {
            # Check if it has actual library files, not just metadata
            $libFiles = Get-ChildItem $path -Recurse -Filter "*.lib" -ErrorAction SilentlyContinue
            if ($libFiles.Count -gt 0) {
                Write-Status "Found Windows SDK libraries at: $path" "Green"
                Set-Variable -Name $LocalVarName -Value $true -Scope Script
                return $true
            }
        }
    }
    
    Write-Warning-Status "Windows SDK not found or incomplete"
    Set-Variable -Name $LocalVarName -Value $false -Scope Script
    return $false
}

# Function to install Windows SDK
function Install-WindowsSDK {
    if ($SkipInstall) {
        Show-ManualInstallInstructions -PackageName "Windows SDK" -WingetCommand @("Microsoft.WindowsSDK.10.0.22621", "Microsoft.WindowsSDK.10.0.22000") -DownloadUrl "https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/" -AdditionalInstructions "3. Visual Studio Installer: Install 'Windows 10/11 SDK' component"
        return $false
    }
    
    $install = Read-Host "Would you like to install Windows SDK automatically using winget? (y/n)"
    if ($install -eq "y" -or $install -eq "Y") {
        Write-Status "Installing Windows SDK via winget..." "Cyan"
        try {
            # Try the latest Windows SDK versions first (22621 for Windows 11 22H2, 22000 for Windows 11)
            $sdkVersions = @("Microsoft.WindowsSDK.10.0.22621", "Microsoft.WindowsSDK.10.0.22000", "Microsoft.WindowsSDK.10.0.19041")
            $installed = $false
            
            foreach ($sdkVersion in $sdkVersions) {
                Write-Status "Attempting to install $sdkVersion..." "Cyan"
                $installProcess = Start-Process -FilePath "winget" -ArgumentList @("install", $sdkVersion, "--accept-package-agreements", "--accept-source-agreements", "--silent") -Wait -PassThru -NoNewWindow
                if ($installProcess.ExitCode -eq 0) {
                    Write-Success-Status "Windows SDK ($sdkVersion) installed successfully!"
                    Write-Host "Please restart your PowerShell session and run this script again." -ForegroundColor Yellow
                    $installed = $true
                    break
                }
                else {
                    Write-Warning-Status "Failed to install $sdkVersion (exit code: $($installProcess.ExitCode)), trying next version..."
                }
            }
            
            if (-not $installed) {
                Write-Error-Status "Failed to install any Windows SDK version via winget"
                return $false
            }
            return $true
        }
        catch {
            Write-Error-Status "Error installing Windows SDK: $($_)"
            return $false
        }
    }
    
    Show-ManualInstallInstructions -PackageName "Windows SDK" -WingetCommand @("Microsoft.WindowsSDK.10.0.22621", "Microsoft.WindowsSDK.10.0.22000") -DownloadUrl "https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/" -AdditionalInstructions "3. Visual Studio Installer: Install 'Windows 10/11 SDK' component"
    return $false
}

# Function to run CMake configuration
function Invoke-CMakeConfigure {
    param(
        [string]$SourcePath,
        [string]$BuildPath,
        [string]$Generator = "",
        [string[]]$Arguments = @(),
        [switch]$CleanFirst = $false
    )
    
    # Create build directory if it doesn't exist
    if (-not (Test-Path $BuildPath)) {
        New-Item -ItemType Directory -Path $BuildPath -Force | Out-Null
    }
    
    # Clean build directory if requested or if there are cache conflicts
    if ($CleanFirst -or (Test-Path "$BuildPath\CMakeCache.txt")) {
        Write-Status "Cleaning build directory: $BuildPath" "Yellow"
        Remove-Item "$BuildPath\*" -Recurse -Force -ErrorAction SilentlyContinue
    }
    
    # Change to build directory
    Push-Location $BuildPath
    
    try {
        # Build CMake command
        $cmakeArgs = @()
        if ($Generator) {
            $cmakeArgs += "-G", "`"$Generator`""
        }
        $cmakeArgs += $Arguments
        $cmakeArgs += $SourcePath
        
        Write-Status "Running: $CMAKE_PATH $($cmakeArgs -join ' ')" "Gray"
        
        # Execute CMake
        $process = Start-Process -FilePath $CMAKE_PATH -ArgumentList $cmakeArgs -Wait -PassThru -NoNewWindow
        
        if ($process.ExitCode -ne 0) {
            # If it failed due to generator mismatch, try cleaning and retrying
            if ($process.ExitCode -eq 1 -and (Test-Path "CMakeCache.txt")) {
                Write-Warning-Status "Generator mismatch detected, cleaning and retrying..."
                Remove-Item "CMakeCache.txt" -Force -ErrorAction SilentlyContinue
                Remove-Item "CMakeFiles" -Recurse -Force -ErrorAction SilentlyContinue
                
                # Retry the configuration
                $process = Start-Process -FilePath $CMAKE_PATH -ArgumentList $cmakeArgs -Wait -PassThru -NoNewWindow
                
                if ($process.ExitCode -ne 0) {
                    throw "CMake configuration failed with exit code $($process.ExitCode) after retry"
                }
            }
            else {
                throw "CMake configuration failed with exit code $($process.ExitCode)"
            }
        }
        
        Write-Success-Status "CMake configuration completed"
    }
    finally {
        Pop-Location
    }
}

# Function to copy file if source exists
function Copy-File-If-Exists {
    param(
        [string]$Source,
        [string]$Destination
    )
    
    if (Test-Path $Source) {
        Copy-Item $Source $Destination -Force
        Write-Status "Copied $Source to $Destination" "Gray"
        return $true
    }
    else {
        Write-Warning-Status "Source file not found: $Source"
        return $false
    }
}

function Build-BcppIfNeeded {
    param(
        [string]$RepoRoot,
        [string]$VsGenerator
    )
    if ([string]::IsNullOrEmpty($CMAKE_PATH)) {
        Write-Warning-Status "CMake path not set; skipping bcpp build."
        return $false
    }
    $zip = Join-Path $RepoRoot "tools\bcpp.tar.zip"
    if (-not (Test-Path $zip)) {
        Write-Warning-Status "tools/bcpp.tar.zip not found; skipping bcpp build."
        return $false
    }
    $extractRoot = Join-Path $RepoRoot "build\win32\bcpp-src"
    $innerTar = Join-Path $extractRoot "bcpp.tar"
    $srcDir = Join-Path $extractRoot "bcpp-20120318\code"
    if (-not (Test-Path $srcDir)) {
        Write-Status "Extracting bcpp source from tools/bcpp.tar.zip..." "Cyan"
        if (-not (Test-Path $extractRoot)) {
            New-Item -ItemType Directory -Force -Path $extractRoot | Out-Null
        }
        Expand-Archive -LiteralPath $zip -DestinationPath $extractRoot -Force
        if (-not (Test-Path $innerTar)) {
            Write-Warning-Status "bcpp.tar missing inside tools/bcpp.tar.zip"
            return $false
        }
        $tar = Start-Process -FilePath "tar" -ArgumentList @("-xf", $innerTar, "-C", $extractRoot) -Wait -PassThru -NoNewWindow
        if ($tar.ExitCode -ne 0) {
            Write-Warning-Status "tar extract of bcpp.tar failed with exit $($tar.ExitCode)"
            return $false
        }
    }
    $cmakeLists = Join-Path $RepoRoot "tools\bcpp\CMakeLists.txt"
    if (-not (Test-Path $cmakeLists)) {
        Write-Warning-Status "tools/bcpp/CMakeLists.txt not found; skipping bcpp build."
        return $false
    }
    $bcppBuildDir = Join-Path $RepoRoot "build\win32\bcpp"
    $bcppExe = Join-Path $bcppBuildDir "Release\bcpp.exe"
    if (Test-Path $bcppExe) {
        Write-Status "bcpp already present: $bcppExe" "Gray"
        return $true
    }
    Write-Status "Building bcpp (used to regenerate JavaScript binding sources)..." "Cyan"
    if (-not (Test-Path $bcppBuildDir)) {
        New-Item -ItemType Directory -Force -Path $bcppBuildDir | Out-Null
    }
    Push-Location $bcppBuildDir
    try {
        $srcNorm = $srcDir.Replace('\', '/')
        $toolchainSrc = Join-Path $RepoRoot "tools\bcpp"
        $cfg = Start-Process -FilePath $CMAKE_PATH -ArgumentList @(
            "-G", $VsGenerator,
            "-A", "x64",
            "-DBCPP_SOURCE_DIR=$srcNorm",
            $toolchainSrc
        ) -Wait -PassThru -NoNewWindow
        if ($cfg.ExitCode -ne 0) {
            Write-Warning-Status "CMake configure for bcpp failed with exit $($cfg.ExitCode)"
            return $false
        }
        $bd = Start-Process -FilePath $CMAKE_PATH -ArgumentList @("--build", ".", "--config", "Release") -Wait -PassThru -NoNewWindow
        if ($bd.ExitCode -ne 0) {
            Write-Warning-Status "CMake build for bcpp failed with exit $($bd.ExitCode)"
            return $false
        }
    }
    finally {
        Pop-Location
    }
    if (-not (Test-Path $bcppExe)) {
        Write-Warning-Status "bcpp.exe not found after build (expected $bcppExe)"
        return $false
    }
    Write-Success-Status "bcpp built successfully"
    return $true
}

# Main script execution
Write-Host ""
Write-Host "PDG Dependency Installation Script (Visual Studio + ClangCL)" -ForegroundColor Cyan
Write-Host "=============================================================" -ForegroundColor Cyan
Write-Host ""

# Initialize dependency paths
$CMAKE_PATH = ""
$PYTHON_PATH = ""
$MSBUILD_PATH = ""
$NASM_PATH = ""
$WINDOWS_SDK_AVAILABLE = $false

# Refresh PATH to pick up any recently installed tools
Refresh-Path

# Check if winget is available
if (-not (Test-Command "winget")) {
    Write-Error-Status "winget is not available. Please install Windows Package Manager first."
    Write-Host "Download from: https://github.com/microsoft/winget-cli/releases" -ForegroundColor Gray
    exit 1
}

if (-not $ConfigureOnly) {
    # Check and install dependencies
    Write-Host ""
    Write-Status "Checking and Installing Dependencies" "Cyan"
    Write-Host "=====================================" -ForegroundColor Cyan
    Write-Host ""
    
    # Check CMake
    if (-not (Check-And-Install-CMake)) {
        Write-Error-Status "Cannot proceed without CMake. Exiting."
        exit 1
    }
    
    # Check NASM
    if (-not (Check-And-Install-NASM)) {
        Write-Error-Status "Cannot proceed without NASM. Exiting."
        exit 1
    }
    
    # Check Python
    if (-not (Check-And-Install-Python)) {
        Write-Error-Status "Cannot proceed without Python. Exiting."
        exit 1
    }
    
    # Check Visual Studio Build Tools with ClangCL
        if (-not (Check-And-Install-VisualStudio)) {
        Write-Error-Status "Cannot proceed without Visual Studio Build Tools with ClangCL. Exiting."
            exit 1
    }
    
    # Check Windows SDK
    if (-not (Check-WindowsSDK)) {
            if (-not (Install-WindowsSDK)) {
            Write-Error-Status "Cannot proceed without Windows SDK. Exiting."
                exit 1
        }
    }
}

Write-Host ""
Write-Status "Configuring PDG Project and Dependencies" "Cyan"
Write-Host "=========================================" -ForegroundColor Cyan
Write-Host ""

if ([string]::IsNullOrEmpty($CMAKE_PATH) -and (Test-Command "cmake")) {
    $CMAKE_PATH = "cmake"
}

$shouldBuildInterfaceTools = $EnableInterfaceTools -and (-not $SkipInterfaceTools)
if ($EnableInterfaceTools -and $SkipInterfaceTools) {
    Write-Warning-Status "Both -EnableInterfaceTools and -SkipInterfaceTools were provided; interface tools will remain disabled."
}

$pdgCmakeInterfaceArgs = @("-DCAN_BUILD_INTERFACES=OFF")
if ($shouldBuildInterfaceTools) {
    if (Build-BcppIfNeeded -RepoRoot $PSScriptRoot -VsGenerator "Visual Studio 17 2022") {
        $bcppExePath = Join-Path $PSScriptRoot "build\win32\bcpp\Release\bcpp.exe"
        $pdgCmakeInterfaceArgs = @("-DCAN_BUILD_INTERFACES=ON", "-DBCPP_EXECUTABLE=$bcppExePath")
    }
    else {
        Write-Warning-Status "Could not build bcpp; JavaScript interface regeneration disabled (CAN_BUILD_INTERFACES=OFF)."
    }
}

# Configure main project using Visual Studio generator with ClangCL
try {
    Write-Status "Using Visual Studio generator (MSVC)" "Cyan"
        $vsGenerators = @("Visual Studio 17 2022", "Visual Studio 16 2019", "Visual Studio 15 2017")
        $configured = $false
        foreach ($vsGen in $vsGenerators) {
            try {
                Write-Status "Trying Visual Studio generator: $vsGen" "Cyan"
            Invoke-CMakeConfigure -SourcePath ".." -BuildPath "msvc" -Generator $vsGen -Arguments ($pdgCmakeInterfaceArgs + @("-DCMAKE_CXX_STANDARD=20"))
            Write-Success-Status "Successfully configured with Visual Studio generator"
                $configured = $true
                break
            }
            catch {
                Write-Warning-Status "Visual Studio generator $vsGen failed: $($_)"
                continue
            }
        }
        if (-not $configured) {
            throw "All Visual Studio generators failed"
    }
}
catch {
    Write-Error-Status "Main project configuration failed: $($_)"
    exit 1
}

Write-Host ""
Write-Status "Configuring Dependencies" "Cyan"
Write-Host "=======================" -ForegroundColor Cyan

# Configure GLFW
Write-Status "Configuring GLFW Library..." "Yellow"
try {
        $vsGen = "Visual Studio 17 2022"
    Invoke-CMakeConfigure -SourcePath "..\..\..\deps\glfw" -BuildPath "build\win32\glfw" -Generator $vsGen -Arguments @("-DGLFW_BUILD_EXAMPLES=OFF", "-DGLFW_BUILD_TESTS=OFF")
}
catch {
    Write-Error-Status "GLFW configuration failed: $($_)"
    exit 1
}

# Configure Chipmunk
Write-Status "Configuring Chipmunk Library..." "Yellow"
try {
        $vsGen = "Visual Studio 17 2022"
    Invoke-CMakeConfigure -SourcePath "..\..\..\deps\chipmunk" -BuildPath "build\win32\chipmunk" -Generator $vsGen -Arguments @("-DBUILD_DEMOS=OFF", "-DBUILD_SHARED=OFF")
}
catch {
    Write-Error-Status "Chipmunk configuration failed: $($_)"
    exit 1
}

# Configure PNG
Write-Status "Configuring PNG Library..." "Yellow"
$pngConfigCopied = Copy-File-If-Exists "deps\png\scripts\pnglibconf.h.prebuilt" "deps\png\pnglibconf.h"
if (-not $pngConfigCopied) {
    Write-Warning-Status "PNG library may not configure properly without pnglibconf.h"
}

# Configure JPEG Turbo
Write-Status "Configuring JPEG Turbo Library..." "Yellow"
$jpegConfigCopied = Copy-File-If-Exists "src\sys\libjpeg-turbo\jconfig-win32.h" "deps\libjpeg-turbo\src\jconfig.h"
if (-not $jpegConfigCopied) {
    Write-Warning-Status "libjpeg-turbo may not configure properly without jconfig.h"
}

try {
        $vsGen = "Visual Studio 17 2022"
    Invoke-CMakeConfigure -SourcePath "..\..\..\deps\libjpeg-turbo" -BuildPath "build\win32\libjpeg-turbo" -Generator $vsGen -Arguments @("-DWITH_SIMD=ON")
}
catch {
    Write-Error-Status "libjpeg-turbo configuration failed: $($_)"
    exit 1
}

# Configure Node.js
Write-Status "Configuring Node.js Library..." "Yellow"
if (Test-Path "deps\node\vcbuild.bat") {
    try {
        Push-Location "deps\node"
        
        # Set up Python environment for Node.js build
        if ($PYTHON_PATH -and $PYTHON_PATH -ne "python" -and $PYTHON_PATH -ne "python3" -and $PYTHON_PATH -ne "py") {
            # Add Python directory to PATH for this process
            $pythonDir = Split-Path $PYTHON_PATH -Parent
            $env:PATH = "$pythonDir;$env:PATH"
            Write-Status "Added Python directory to PATH: $pythonDir" "Cyan"
        }
        
        # Create output directories
        if (-not (Test-Path "out\Debug")) { New-Item -ItemType Directory -Path "out\Debug" -Force | Out-Null }
        if (-not (Test-Path "out\Release")) { New-Item -ItemType Directory -Path "out\Release" -Force | Out-Null }
        
        # Set Windows SDK version for Node.js build
        # Try to find the latest available Windows SDK version that includes what we need to build Node.js v24
        $latestSdkVersion = $null
        $sdkVersions = @("10.0.22621.0", "10.0.22000.0", "10.0.19041.0")
        foreach ($version in $sdkVersions) {
            $sdkPath = "C:\Program Files (x86)\Windows Kits\10\Lib\$version"
            if (Test-Path $sdkPath) {
                $latestSdkVersion = $version
                Write-Status "Using Windows SDK version: $latestSdkVersion" "Green"
                break
            }
        }
        
        if ($latestSdkVersion) {
            $env:WindowsTargetPlatformVersion = $latestSdkVersion
            Write-Status "Set WindowsTargetPlatformVersion to: $latestSdkVersion" "Cyan"
        } else {
            Write-Warning-Status "Could not find a suitable Windows SDK version, using default"
        }
        
        # Run vcbuild with proper environment (using openssl-no-asm to avoid NASM requirement)
        Write-Status "Running Node.js vcbuild.bat..." "Cyan"
        $process = Start-Process -FilePath "cmd" -ArgumentList @("/c", "vcbuild.bat", "nobuild") -Wait -PassThru -NoNewWindow
        
        if ($process.ExitCode -ne 0) {
            throw "Node.js configuration failed with exit code $($process.ExitCode)"
        }
        
        Write-Success-Status "Node.js configuration completed"
    }
    catch {
        Write-Error-Status "Node.js configuration failed: $($_)"
        Write-Error-Status "Node.js configuration is required. Exiting."
        exit 1
    }
    finally {
        Pop-Location
    }
}
else {
    Write-Error-Status "Node.js vcbuild.bat not found"
    Write-Error-Status "Node.js configuration is required. Exiting."
    exit 1
}

# Copy make.bat if it exists
if (Test-Path "tools\make_ps1") {
    Copy-Item "tools\make_ps1" "make.ps1" -Force
    Write-Host ""
    Write-Success-Status "Configuration completed successfully!"
    Write-Host "Type '.\make.ps1' to build the project." -ForegroundColor Yellow
}
else {
    Write-Host ""
    Write-Success-Status "Configuration completed successfully!"
    Write-Host "Use your preferred build system to compile the project." -ForegroundColor Yellow
}

Write-Host ""
Write-Status "Build Summary:" "Cyan"
Write-Host "- Main project: msvc\ directory" -ForegroundColor White
Write-Host "- GLFW: build\win32\glfw\ directory" -ForegroundColor White
Write-Host "- Chipmunk: build\win32\chipmunk\ directory" -ForegroundColor White
Write-Host "- libjpeg-turbo: build\win32\libjpeg-turbo\ directory" -ForegroundColor White
Write-Host "- Node.js: deps\node\ directory" -ForegroundColor White
if ($shouldBuildInterfaceTools -and (Test-Path (Join-Path $PSScriptRoot "build\win32\bcpp\Release\bcpp.exe"))) {
    Write-Host "- bcpp (binding generator): build\win32\bcpp\Release\bcpp.exe" -ForegroundColor White
}

Write-Host ""
Write-Status "Dependency Installation and Configuration script finished." "Green"
