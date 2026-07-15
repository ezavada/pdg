# PDG Dependency Installation Script
# PowerShell script to install all required dependencies for PDG development

param(
    [switch]$Force,
    [switch]$Help,
    [switch]$SkipInstall,
    [switch]$ConfigureOnly,
    [switch]$UseMSVC
)

# Function to display help
function Show-Help {
    Write-Host "PDG Dependency Installation Script" -ForegroundColor Cyan
    Write-Host "===================================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Usage: .\configure.ps1 [options]" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Options:" -ForegroundColor Yellow
    Write-Host "  -Force          Force reinstallation even if dependencies are already installed" -ForegroundColor White
    Write-Host "  -SkipInstall    Skip installation and only configure existing dependencies" -ForegroundColor White
    Write-Host "  -ConfigureOnly  Only run configuration steps, skip dependency detection/installation" -ForegroundColor White
    Write-Host "  -UseMSVC        Use Microsoft Visual C++ compiler instead of Clang" -ForegroundColor White
    Write-Host "  -Help           Show this help message" -ForegroundColor White
    Write-Host ""
    Write-Host "This script will install and configure all dependencies required for PDG development:" -ForegroundColor White
    Write-Host "  - CMake (build system)" -ForegroundColor Gray
    Write-Host "  - Visual Studio Build Tools or MinGW (C++ compiler)" -ForegroundColor Gray
    Write-Host "  - Clang/LLVM (alternative C++ compiler)" -ForegroundColor Gray
    Write-Host "  - Ninja (build system)" -ForegroundColor Gray
    Write-Host "  - Python (for Node.js build)" -ForegroundColor Gray
    Write-Host "  - Windows SDK (for Windows development)" -ForegroundColor Gray
    Write-Host ""
    Write-Host "After installation, it will configure all library dependencies and the main project." -ForegroundColor White
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

# Function to check and install Ninja
function Check-And-Install-Ninja {
    param([string]$LocalVarName = "NINJA_PATH")
    
    Write-Status "Checking for Ninja..." "Cyan"
    
    # Check if Ninja is in PATH
    if (Test-Command "ninja") {
        $version = Get-CommandVersion -Command "ninja"
        Write-Status "Found Ninja in PATH: $version" "Green"
        Set-Variable -Name $LocalVarName -Value "ninja" -Scope Script
        return $true
    }
    
    # Check common installation paths
    $ninjaPaths = @(
        "C:\Program Files\Ninja\ninja.exe",
        "C:\Program Files (x86)\Ninja\ninja.exe",
        "C:\ninja\ninja.exe"
    )
    
    $foundPath = Find-DependencyInPaths -Command "ninja" -CommonPaths $ninjaPaths
    if ($foundPath) {
        Set-Variable -Name $LocalVarName -Value $foundPath -Scope Script
        return $true
    }
    
    if ($SkipInstall) {
        Show-ManualInstallInstructions -PackageName "Ninja" -WingetCommand @("Ninja-build.Ninja") -ChocoCommand @("ninja") -DownloadUrl "https://ninja-build.org/"
        return $false
    }
    
    # Ask user if they want to install
    $install = Read-Host "Would you like to install Ninja automatically using winget? (y/n)"
    if ($install -eq "y" -or $install -eq "Y") {
        if (Install-Dependency -PackageId "Ninja-build.Ninja" -PackageName "Ninja" -Command "ninja" -CommonPaths $ninjaPaths) {
            Set-Variable -Name $LocalVarName -Value "ninja" -Scope Script
            return $true
        }
    }
    
    Show-ManualInstallInstructions -PackageName "Ninja" -WingetCommand @("Ninja-build.Ninja") -ChocoCommand @("ninja") -DownloadUrl "https://ninja-build.org/"
    return $false
}

# Function to check and install Python
function Check-And-Install-Python {
    param([string]$LocalVarName = "PYTHON_PATH")
    
    Write-Status "Checking for Python..." "Cyan"
    
    # Function to validate Python executable
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
            
            # Test if the executable actually works
            $version = Get-CommandVersion -Command $Command
            if ($version -and $version -notlike "*Microsoft Store*") {
                return $true
            }
            return $false
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
    
    # Check common installation paths
    $pythonPaths = @(
        "C:\Users\$env:USERNAME\AppData\Local\Programs\Python\Python313\python.exe",
        "C:\Users\$env:USERNAME\AppData\Local\Programs\Python\Python312\python.exe",
        "C:\Users\$env:USERNAME\AppData\Local\Programs\Python\Python311\python.exe",
        "C:\Python313\python.exe",
        "C:\Python312\python.exe",
        "C:\Python311\python.exe",
        "C:\Program Files\Python313\python.exe",
        "C:\Program Files\Python312\python.exe",
        "C:\Program Files\Python311\python.exe"
    )
    
    foreach ($pythonPath in $pythonPaths) {
        if (Test-Path $pythonPath) {
            # Test if this Python installation actually works
            try {
                $version = & $pythonPath --version 2>$null
                if ($version -and $version -notlike "*Microsoft Store*") {
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
        Show-ManualInstallInstructions -PackageName "Python" -WingetCommand @("Python.Python.3.13", "Python.Python.3.12", "Python.Python.3.11") -ChocoCommand @("python") -DownloadUrl "https://www.python.org/downloads/"
        return $false
    }
    
    # Ask user if they want to install
    $install = Read-Host "Would you like to install Python automatically using winget? (y/n)"
    if ($install -eq "y" -or $install -eq "Y") {
        if (Install-Dependency -PackageId "Python.Python.3.13" -PackageName "Python" -Command "python" -CommonPaths $pythonPaths) {
            Set-Variable -Name $LocalVarName -Value "python" -Scope Script
            return $true
        }
    }
    
    Show-ManualInstallInstructions -PackageName "Python" -WingetCommand @("Python.Python.3.13", "Python.Python.3.12", "Python.Python.3.11") -ChocoCommand @("python") -DownloadUrl "https://www.python.org/downloads/"
    return $false
}

# Function to check and install MinGW
function Check-And-Install-MinGW {
    param([string]$LocalVarName = "MINGW_PATH")
    
    Write-Status "Checking for MinGW..." "Cyan"
    
    # Check if gcc is in PATH
    $gccCommands = @("gcc", "x86_64-w64-mingw32-gcc")
    foreach ($cmd in $gccCommands) {
        if (Test-Command $cmd) {
            $version = Get-CommandVersion -Command $cmd
            # Get the full path to the gcc executable
            $fullPath = (Get-Command $cmd).Source
            Write-Status "Found MinGW in PATH ($cmd): $version" "Green"
            Set-Variable -Name $LocalVarName -Value $fullPath -Scope Script
            return $true
        }
    }
    
    # Check common installation paths
    $mingwPaths = @(
        "C:\msys64\ucrt64\bin\gcc.exe",  # WinLibs UCRT installation
        "C:\msys64\mingw64\bin\gcc.exe",
        "C:\msys64\clang64\bin\gcc.exe",
        "C:\Program Files\mingw-w64\x86_64-*\bin\gcc.exe",
        "C:\mingw64\bin\gcc.exe",
        "C:\Program Files\LLVM-MinGW\bin\gcc.exe",
        "C:\Program Files (x86)\LLVM-MinGW\bin\gcc.exe",
        "C:\tools\mingw64\bin\gcc.exe",
        "C:\Program Files\mingw-w64\bin\gcc.exe",
        "C:\Program Files (x86)\mingw-w64\bin\gcc.exe",
        "C:\mingw\bin\gcc.exe",
        "C:\mingw64\bin\gcc.exe",
        "C:\Program Files\mingw64\bin\gcc.exe",
        "C:\Program Files (x86)\mingw64\bin\gcc.exe"
    )
    
    $foundPath = Find-DependencyInPaths -Command "gcc" -CommonPaths $mingwPaths
    if ($foundPath) {
        Write-Status "Found MinGW at: $foundPath" "Green"
        Set-Variable -Name $LocalVarName -Value $foundPath -Scope Script
        return $true
    }
    
    if ($SkipInstall) {
        Show-ManualInstallInstructions -PackageName "MinGW" -WingetCommand @("MartinStorsjo.LLVM-MinGW.UCRT") -ChocoCommand @("mingw") -DownloadUrl "https://github.com/mstorsjo/llvm-mingw/releases"
        return $false
    }
    
    # Ask user if they want to install
    $install = Read-Host "Would you like to install MinGW automatically using winget? (y/n)"
    if ($install -eq "y" -or $install -eq "Y") {
        Write-Status "Installing MinGW-w64 via winget..." "Yellow"
        
        # Try installing WinLibs MinGW-w64 (UCRT runtime)
        try {
            $result = winget install "BrechtSanders.WinLibs.POSIX.UCRT" --accept-package-agreements --accept-source-agreements --silent
            if ($LASTEXITCODE -eq 0) {
                Refresh-Path
                # Check if gcc is now in PATH
                if (Test-Command "gcc") {
                    $gccPath = (Get-Command "gcc").Source
                    Write-Success-Status "WinLibs MinGW-w64 installed successfully"
                    Set-Variable -Name $LocalVarName -Value $gccPath -Scope Script
                    return $true
                }
                else {
                    # If not in PATH, try to find it in common locations
                    $foundPath = Find-DependencyInPaths -Command "gcc" -CommonPaths $mingwPaths
                    if ($foundPath) {
                        Write-Success-Status "WinLibs MinGW-w64 installed successfully (found at: $foundPath)"
                        Set-Variable -Name $LocalVarName -Value $foundPath -Scope Script
                        return $true
                    }
                }
            }
        }
        catch {
            Write-Warning-Status "WinLibs MinGW-w64 installation failed: $($_)"
        }
        
        # Fallback: Try installing via chocolatey if available
        if (Get-Command "choco" -ErrorAction SilentlyContinue) {
            Write-Status "Trying Chocolatey installation..." "Yellow"
            try {
                choco install mingw -y
                if ($LASTEXITCODE -eq 0) {
                    Refresh-Path
                    if (Test-Command "gcc") {
                        $gccPath = (Get-Command "gcc").Source
                        Write-Success-Status "MinGW installed via Chocolatey"
                        Set-Variable -Name $LocalVarName -Value $gccPath -Scope Script
                        return $true
                    }
                }
            }
            catch {
                Write-Warning-Status "Chocolatey installation failed: $($_)"
            }
        }
        
        Write-Error-Status "Automatic MinGW installation failed"
    }
    
    Show-ManualInstallInstructions -PackageName "MinGW" -WingetCommand @("BrechtSanders.WinLibs.POSIX.UCRT") -ChocoCommand @("mingw") -DownloadUrl "https://winlibs.com/" -AdditionalInstructions "Or install MSYS2 from https://www.msys2.org/ and run: pacman -S mingw-w64-x86_64-gcc"
    return $false
}

# Function to check and install Clang/LLVM
function Check-And-Install-Clang {
    param([string]$LocalVarName = "CLANG_PATH")
    
    Write-Status "Checking for Clang/LLVM..." "Cyan"
    
    # Check if Clang is in PATH
    $clangCommands = @("clang", "clang-cl")
    foreach ($cmd in $clangCommands) {
        if (Test-Command $cmd) {
            $version = Get-CommandVersion -Command $cmd
            Write-Status "Found Clang in PATH ($cmd): $version" "Green"
            Set-Variable -Name $LocalVarName -Value $cmd -Scope Script
            return $true
        }
    }
    
    # Check common installation paths
    $clangPaths = @(
        "C:\Program Files\LLVM\bin\clang.exe",
        "C:\Program Files (x86)\LLVM\bin\clang.exe",
        "C:\msys64\mingw64\bin\clang.exe",
        "C:\msys64\clang64\bin\clang.exe"
    )
    
    $foundPath = Find-DependencyInPaths -Command "clang" -CommonPaths $clangPaths
    if ($foundPath) {
        Set-Variable -Name $LocalVarName -Value $foundPath -Scope Script
        return $true
    }
    
    if ($SkipInstall) {
        Show-ManualInstallInstructions -PackageName "Clang/LLVM" -WingetCommand @("LLVM.LLVM") -ChocoCommand @("llvm") -DownloadUrl "https://releases.llvm.org/download.html" -AdditionalInstructions "3. Visual Studio Installer: Install 'MSVC v143 - VS 2022 C++ Clang Compiler Toolset'"
        return $false
    }
    
    # Ask user if they want to install
    $install = Read-Host "Would you like to install Clang/LLVM automatically using winget? (y/n)"
    if ($install -eq "y" -or $install -eq "Y") {
        if (Install-Dependency -PackageId "LLVM.LLVM" -PackageName "Clang/LLVM" -Command "clang" -CommonPaths $clangPaths) {
            Set-Variable -Name $LocalVarName -Value "clang" -Scope Script
            return $true
        }
    }
    
    Show-ManualInstallInstructions -PackageName "Clang/LLVM" -WingetCommand @("LLVM.LLVM") -ChocoCommand @("llvm") -DownloadUrl "https://releases.llvm.org/download.html" -AdditionalInstructions "3. Visual Studio Installer: Install 'MSVC v143 - VS 2022 C++ Clang Compiler Toolset'"
    return $false
}

# Function to check and install Visual Studio Build Tools
function Check-And-Install-VisualStudio {
    param([string]$LocalVarName = "MSBUILD_PATH")
    
    Write-Status "Checking for Visual Studio Build Tools..." "Cyan"
    
    # Check for Visual Studio compiler using vswhere
    $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vsWhere) {
        try {
            # Look for Visual Studio with C++ tools
            $vsInstall = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
            if ($vsInstall) {
                Write-Status "Found Visual Studio with C++ tools at: $vsInstall" "Green"
                $vcvarsPath = Join-Path $vsInstall "VC\Auxiliary\Build\vcvars64.bat"
                if (Test-Path $vcvarsPath) {
                    Set-Variable -Name $LocalVarName -Value $vcvarsPath -Scope Script
                    return $true
                }
            }
            
            # Look for Build Tools
            $buildToolsInstall = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Workload.VCTools -property installationPath
            if ($buildToolsInstall) {
                Write-Status "Found Visual Studio Build Tools at: $buildToolsInstall" "Green"
                $vcvarsPath = Join-Path $buildToolsInstall "VC\Auxiliary\Build\vcvars64.bat"
                if (Test-Path $vcvarsPath) {
                    Set-Variable -Name $LocalVarName -Value $vcvarsPath -Scope Script
                    return $true
                }
            }
        }
        catch {
            Write-Warning-Status "Error checking Visual Studio installations: $($_)"
        }
    }
    
    if ($SkipInstall) {
        Show-ManualInstallInstructions -PackageName "Visual Studio Build Tools" -WingetCommand @("Microsoft.VisualStudio.2022.BuildTools") -DownloadUrl "https://visualstudio.microsoft.com/downloads/" -AdditionalInstructions "Make sure to install the 'C++ build tools' workload during installation."
        return $false
    }
    
    # Ask user if they want to install
    $install = Read-Host "Would you like to install Visual Studio Build Tools automatically using winget? (y/n)"
    if ($install -eq "y" -or $install -eq "Y") {
        Write-Status "Installing Visual Studio Build Tools with C++ workload..." "Cyan"
        try {
            $installProcess = Start-Process -FilePath "winget" -ArgumentList @("install", "Microsoft.VisualStudio.2022.BuildTools", "--override", "--add", "Microsoft.VisualStudio.Workload.VCTools", "--accept-package-agreements", "--accept-source-agreements") -Wait -PassThru -NoNewWindow
            
            if ($installProcess.ExitCode -eq 0) {
                Write-Success-Status "Visual Studio Build Tools with C++ workload installed!"
                Start-Sleep -Seconds 5
                Refresh-Path -Force
                
                # Try to find the installation
                if (Test-Path $vsWhere) {
                    $buildToolsInstall = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Workload.VCTools -property installationPath
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
                Write-Error-Status "Failed to install Visual Studio Build Tools via winget (exit code: $($installProcess.ExitCode))"
            }
        }
        catch {
            Write-Error-Status "Error installing Visual Studio Build Tools: $($_)"
        }
    }
    
    Show-ManualInstallInstructions -PackageName "Visual Studio Build Tools" -WingetCommand @("Microsoft.VisualStudio.2022.BuildTools") -DownloadUrl "https://visualstudio.microsoft.com/downloads/" -AdditionalInstructions "Make sure to install the 'C++ build tools' workload during installation."
    return $false
}

# Function to check for Visual Studio with ClangCL support (required for Node.js v24+)
function Check-VisualStudio-ClangCL {
    param([string]$LocalVarName = "VS_CLANGCL_AVAILABLE")
    
    Write-Status "Checking for Visual Studio with ClangCL support..." "Cyan"
    
    # Check for Visual Studio compiler using vswhere
    $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vsWhere) {
        try {
            # Look for Visual Studio with ClangCL components
            $vsInstall = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Llvm.Clang -property installationPath
            if ($vsInstall) {
                # Check if ClangCL is actually available
                $clangPath = Join-Path $vsInstall "VC\Tools\Llvm\x64\bin\clang.exe"
                if (Test-Path $clangPath) {
                    Write-Status "Found Visual Studio with ClangCL at: $vsInstall" "Green"
                    Set-Variable -Name $LocalVarName -Value $true -Scope Script
                    return $true
                }
            }
            
            # Also check Build Tools
            $buildToolsInstall = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Llvm.Clang -property installationPath
            if ($buildToolsInstall) {
                $clangPath = Join-Path $buildToolsInstall "VC\Tools\Llvm\x64\bin\clang.exe"
                if (Test-Path $clangPath) {
                    Write-Status "Found Visual Studio Build Tools with ClangCL at: $buildToolsInstall" "Green"
                    Set-Variable -Name $LocalVarName -Value $true -Scope Script
                    return $true
                }
            }
        }
        catch {
            Write-Warning-Status "Error checking Visual Studio ClangCL installations: $($_)"
        }
    }
    
    Write-Warning-Status "Visual Studio with ClangCL not found"
    Write-Host ""
    Write-Host "Node.js v24+ requires Visual Studio with ClangCL support." -ForegroundColor Yellow
    Write-Host "Please install the following components:" -ForegroundColor White
    Write-Host "1. Visual Studio 2022 (17.6 or newer) with 'Desktop development with C++' workload" -ForegroundColor Gray
    Write-Host "   OR Visual Studio Build Tools with 'C++ build tools' workload" -ForegroundColor Gray
    Write-Host "2. Additional required components:" -ForegroundColor White
    Write-Host "   - C++ Clang Compiler for Windows (Microsoft.VisualStudio.Component.VC.Llvm.Clang)" -ForegroundColor Gray
    Write-Host "   - MSBuild support for LLVM toolset (Microsoft.VisualStudio.Component.VC.Llvm.ClangToolset)" -ForegroundColor Gray
    Write-Host ""
    Write-Host "You can install these via:" -ForegroundColor White
    Write-Host "  winget install Microsoft.VisualStudio.2022.BuildTools --override --add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.VC.Llvm.Clang --add Microsoft.VisualStudio.Component.VC.Llvm.ClangToolset" -ForegroundColor Gray
    Write-Host ""
    
    Set-Variable -Name $LocalVarName -Value $false -Scope Script
    return $false
}

# Function to check Windows SDK
function Check-WindowsSDK {
    param([string]$LocalVarName = "WINDOWS_SDK_AVAILABLE")
    
    Write-Status "Checking for Windows SDK..." "Cyan"
    
    # Check for Windows SDK in common locations
    $sdkPaths = @(
        "C:\Program Files (x86)\Windows Kits\10\Lib",
        "C:\Program Files (x86)\Microsoft SDKs\Windows\v10.0A\Lib",
        "C:\Program Files\Microsoft SDKs\Windows\v10.0A\Lib"
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
        Show-ManualInstallInstructions -PackageName "Windows SDK" -WingetCommand @("Microsoft.WindowsSDK.10.0.17134") -DownloadUrl "https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/" -AdditionalInstructions "3. Visual Studio Installer: Install 'Windows 10/11 SDK' component"
        return $false
    }
    
    $install = Read-Host "Would you like to install Windows SDK automatically using winget? (y/n)"
    if ($install -eq "y" -or $install -eq "Y") {
        Write-Status "Installing Windows SDK via winget..." "Cyan"
        try {
            $installProcess = Start-Process -FilePath "winget" -ArgumentList @("install", "Microsoft.WindowsSDK.10.0.17134", "--accept-package-agreements", "--accept-source-agreements") -Wait -PassThru -NoNewWindow
            if ($installProcess.ExitCode -eq 0) {
                Write-Success-Status "Windows SDK installed successfully!"
                Write-Host "Please restart your PowerShell session and run this script again." -ForegroundColor Yellow
                return $true
            }
            else {
                Write-Error-Status "Failed to install Windows SDK via winget (exit code: $($installProcess.ExitCode))"
            }
        }
        catch {
            Write-Error-Status "Error installing Windows SDK: $($_)"
        }
    }
    
    Show-ManualInstallInstructions -PackageName "Windows SDK" -WingetCommand @("Microsoft.WindowsSDK.10.0.17134") -DownloadUrl "https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/" -AdditionalInstructions "3. Visual Studio Installer: Install 'Windows 10/11 SDK' component"
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

# Function to get resource compiler path for Clang
function Get-ClangResourceCompiler {
    param([string]$ClangPath)
    
    # Try llvm-rc.exe first (preferred)
    $rcPath = $ClangPath -replace "clang\.exe$", "llvm-rc.exe"
    if (Test-Path $rcPath) {
        return $rcPath
    }
    
    # Fallback to windres.exe
    $rcPath = $ClangPath -replace "clang\.exe$", "windres.exe"
    if (Test-Path $rcPath) {
        return $rcPath
    }
    
    # Final fallback to clang itself
    return $ClangPath
}

# Function to convert Windows path to CMake-compatible path
function Convert-ToCMakePath {
    param([string]$Path)
    return $Path -replace "\\", "/"
}

# Function to find MinGW library path
function Get-MinGW-LibraryPath {
    param([string]$GccPath)
    
    # Extract the base directory from gcc path
    $baseDir = Split-Path (Split-Path $GccPath -Parent) -Parent
    $libPath = Join-Path $baseDir "lib"
    
    if (Test-Path $libPath) {
        return Convert-ToCMakePath -Path $libPath
    }
    
    # Fallback to common MinGW lib paths
    $commonLibPaths = @(
        "C:\msys64\mingw64\lib",
        "C:\msys64\clang64\lib",
        "C:\mingw64\lib"
    )
    
    foreach ($path in $commonLibPaths) {
        if (Test-Path $path) {
            return Convert-ToCMakePath -Path $path
        }
    }
    
    return ""
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

# Main script execution
Write-Host ""
Write-Host "PDG Dependency Installation Script" -ForegroundColor Cyan
Write-Host "===================================" -ForegroundColor Cyan
Write-Host ""

# Initialize dependency paths
$CMAKE_PATH = ""
$NINJA_PATH = ""
$PYTHON_PATH = ""
$CLANG_PATH = ""
$MSBUILD_PATH = ""
$WINDOWS_SDK_AVAILABLE = $false
$VS_CLANGCL_AVAILABLE = $false

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
    
    # Check Ninja
    if (-not (Check-And-Install-Ninja)) {
        Write-Error-Status "Cannot proceed without Ninja. Exiting."
        exit 1
    }
    
    # Check Python
    if (-not (Check-And-Install-Python)) {
        Write-Error-Status "Cannot proceed without Python. Exiting."
        exit 1
    }
    
    # Check compiler based on user preference
    if ($UseMSVC) {
        Write-Status "User requested Microsoft Visual C++ compiler" "Cyan"
        $clangAvailable = $false
        if (-not (Check-And-Install-VisualStudio)) {
            Write-Error-Status "Cannot proceed without Visual Studio Build Tools. Exiting."
            exit 1
        }
    }
    else {
        # Check MinGW (required for Clang on Windows)
        $mingwAvailable = Check-And-Install-MinGW
        if (-not $mingwAvailable) {
            Write-Error-Status "MinGW not available. Required for Clang on Windows. Exiting."
            exit 1
        }
        
        # Check Clang/LLVM (preferred)
        $clangAvailable = Check-And-Install-Clang
        
        # Only check Visual Studio if Clang is not available
        if (-not $clangAvailable) {
            Write-Error-Status "Clang/LLVM not available. Please install Clang/LLVM or use -UseMSVC flag for Visual Studio Build Tools."
            exit 1
        }
    }
    
    # Check Windows SDK
    if (-not (Check-WindowsSDK)) {
        if ($clangAvailable) {
            if (-not (Install-WindowsSDK)) {
                Write-Error-Status "Cannot proceed without Windows SDK for Clang. Exiting."
                exit 1
            }
        }
    }
    
    # Check Visual Studio with ClangCL (required for Node.js v24+)
    Check-VisualStudio-ClangCL
}

Write-Host ""
Write-Status "Configuring PDG Project and Dependencies" "Cyan"
Write-Host "=========================================" -ForegroundColor Cyan
Write-Host ""

# Configure main project
try {
    if ($UseMSVC -or (-not $CLANG_PATH)) {
        # Use Visual Studio generator with MSVC
        Write-Status "Using Microsoft Visual C++ compiler with Visual Studio generator" "Cyan"
        $vsGenerators = @("Visual Studio 17 2022", "Visual Studio 16 2019", "Visual Studio 15 2017")
        $configured = $false
        foreach ($vsGen in $vsGenerators) {
            try {
                Write-Status "Trying Visual Studio generator: $vsGen" "Cyan"
                Invoke-CMakeConfigure -SourcePath ".." -BuildPath "msvc" -Generator $vsGen -Arguments @("-DCAN_BUILD_INTERFACES=OFF")
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
    elseif ($CLANG_PATH -and $WINDOWS_SDK_AVAILABLE) {
        # Use Ninja with Clang
        Write-Status "Using Clang compiler with Ninja generator" "Cyan"
        try {
            # Determine C++ compiler path (clang++ or clang-cl)
            $clangCxxPath = $CLANG_PATH
            if ($CLANG_PATH -like "*clang.exe") {
                $clangCxxPath = $CLANG_PATH -replace "clang\.exe$", "clang++.exe"
                if (-not (Test-Path $clangCxxPath)) {
                    $clangCxxPath = $CLANG_PATH  # Fallback to clang if clang++ not found
                }
            }
            # Get resource compiler path and convert to CMake format
            $rcPath = Get-ClangResourceCompiler -ClangPath $CLANG_PATH
            $cmakeClangPath = Convert-ToCMakePath -Path $CLANG_PATH
            $cmakeClangCxxPath = Convert-ToCMakePath -Path $clangCxxPath
            $cmakeRcPath = Convert-ToCMakePath -Path $rcPath
            
            # Get MinGW library path
            if (-not $MINGW_PATH) {
                Write-Error-Status "MinGW path not found. Cannot configure Clang without MinGW libraries."
                exit 1
            }
            $mingwLibPath = Get-MinGW-LibraryPath -GccPath $MINGW_PATH
            
            # Configure Clang to use MSVC-style linking with Windows SDK
            $cmakeArgs = @(
                "-DCAN_BUILD_INTERFACES=OFF",
                "-DCMAKE_C_COMPILER=`"$cmakeClangPath`"",
                "-DCMAKE_CXX_COMPILER=`"$cmakeClangCxxPath`"",
                "-DCMAKE_RC_COMPILER=`"$cmakeRcPath`"",
                "-DCMAKE_SYSTEM_NAME=Windows",
                "-DCMAKE_C_FLAGS=`"-target x86_64-pc-windows-gnu`"",
                "-DCMAKE_CXX_FLAGS=`"-target x86_64-pc-windows-gnu`"",
                "-DCMAKE_EXE_LINKER_FLAGS=`"-fuse-ld=lld -target x86_64-pc-windows-gnu`"",
                "-DCMAKE_SHARED_LINKER_FLAGS=`"-fuse-ld=lld -target x86_64-pc-windows-gnu`""
            )
            
            # Add MinGW library path (required for MinGW-style linking)
            if ($MINGW_PATH) {
                $mingwLibPath = Get-MinGW-LibraryPath -GccPath $MINGW_PATH
                if ($mingwLibPath) {
                    $cmakeArgs += @("-DCMAKE_LIBRARY_PATH=`"$mingwLibPath`"")
                }
            }
            
            # Add Windows SDK library path (optional)
            if ($WINDOWS_SDK_AVAILABLE) {
                # Find the actual Windows SDK path and version
                $sdkPaths = @(
                    "C:\Program Files (x86)\Windows Kits\10\Lib",
                    "C:\Program Files\Microsoft SDKs\Windows\v10.0A\Lib"
                )
                
                foreach ($sdkPath in $sdkPaths) {
                    if (Test-Path $sdkPath) {
                        # Find the latest version
                        $versions = Get-ChildItem $sdkPath -Directory | Where-Object { $_.Name -match '^\d+\.\d+\.\d+\.\d+$' } | Sort-Object Name -Descending
                        if ($versions.Count -gt 0) {
                            $latestVersion = $versions[0].Name
                            $sdkLibPath = Convert-ToCMakePath -Path "$sdkPath\$latestVersion\ucrt\x64"
                            $cmakeArgs += @("-DCMAKE_LIBRARY_PATH=`"$sdkLibPath`"")
                            break
                        }
                    }
                }
            }
            Invoke-CMakeConfigure -SourcePath ".." -BuildPath "msvc" -Generator "Ninja" -Arguments $cmakeArgs
        }
        catch {
            Write-Error-Status "Clang configuration failed: $($_)"
            Write-Host ""
            Write-Host "Clang configuration failed. You have the following options:" -ForegroundColor Yellow
            Write-Host "1. Fix the Clang installation and try again" -ForegroundColor White
            Write-Host "2. Use Visual Studio Build Tools instead (requires -UseMSVC flag)" -ForegroundColor White
            Write-Host "3. Install a different C++ compiler" -ForegroundColor White
            Write-Host ""
            Write-Host "To use Visual Studio Build Tools, run:" -ForegroundColor Cyan
            Write-Host "  .\configure.ps1 -UseMSVC" -ForegroundColor Gray
            Write-Host ""
            throw "Cannot proceed without a working C++ compiler"
        }
    }
    else {
        Write-Error-Status "No C++ compiler available. Please install Clang/LLVM or use -UseMSVC flag for Visual Studio Build Tools."
        exit 1
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
    if ($UseMSVC -or (-not $CLANG_PATH)) {
        # Use Visual Studio generator for dependencies
        $vsGen = "Visual Studio 17 2022"
        Invoke-CMakeConfigure -SourcePath "..\..\..\deps\glfw" -BuildPath "build\win32\glfw" -Generator $vsGen -Arguments @("-DGLFW_BUILD_EXAMPLES=OFF", "-DGLFW_BUILD_TESTS=OFF")
    }
    else {
        # Use Ninja with Clang for dependencies
        $clangCxxPath = $CLANG_PATH
        if ($CLANG_PATH -like "*clang.exe") {
            $clangCxxPath = $CLANG_PATH -replace "clang\.exe$", "clang++.exe"
            if (-not (Test-Path $clangCxxPath)) {
                $clangCxxPath = $CLANG_PATH  # Fallback to clang if clang++ not found
            }
        }
        # Get resource compiler path and convert to CMake format
        $rcPath = Get-ClangResourceCompiler -ClangPath $CLANG_PATH
        $cmakeClangPath = Convert-ToCMakePath -Path $CLANG_PATH
        $cmakeClangCxxPath = Convert-ToCMakePath -Path $clangCxxPath
        $cmakeRcPath = Convert-ToCMakePath -Path $rcPath
        
        # Get MinGW library path
        if (-not $MINGW_PATH) {
            Write-Error-Status "MinGW path not found. Cannot configure GLFW without MinGW libraries."
            exit 1
        }
        $mingwLibPath = Get-MinGW-LibraryPath -GccPath $MINGW_PATH
        
        # Configure GLFW with MinGW-style linking
        $glfwArgs = @(
            "-DGLFW_BUILD_EXAMPLES=OFF",
            "-DGLFW_BUILD_TESTS=OFF",
            "-DCMAKE_C_COMPILER=`"$cmakeClangPath`"",
            "-DCMAKE_CXX_COMPILER=`"$cmakeClangCxxPath`"",
            "-DCMAKE_RC_COMPILER=`"$cmakeRcPath`"",
            "-DCMAKE_SYSTEM_NAME=Windows",
            "-DCMAKE_C_FLAGS=`"-target x86_64-pc-windows-gnu`"",
            "-DCMAKE_CXX_FLAGS=`"-target x86_64-pc-windows-gnu`"",
            "-DCMAKE_EXE_LINKER_FLAGS=`"-fuse-ld=lld -target x86_64-pc-windows-gnu`"",
            "-DCMAKE_SHARED_LINKER_FLAGS=`"-fuse-ld=lld -target x86_64-pc-windows-gnu`""
        )
        
        # Add MinGW library path if found
        if ($mingwLibPath) {
            $glfwArgs += @("-DCMAKE_LIBRARY_PATH=`"$mingwLibPath`"")
        }
        Invoke-CMakeConfigure -SourcePath "..\..\..\deps\glfw" -BuildPath "build\win32\glfw" -Generator "Ninja" -Arguments $glfwArgs
    }
}
catch {
    Write-Error-Status "GLFW configuration failed: $($_)"
    exit 1
}

# Configure Chipmunk
Write-Status "Configuring Chipmunk Library..." "Yellow"
try {
    if ($UseMSVC -or (-not $CLANG_PATH)) {
        # Use Visual Studio generator for dependencies
        $vsGen = "Visual Studio 17 2022"
        Invoke-CMakeConfigure -SourcePath "..\..\..\deps\chipmunk" -BuildPath "build\win32\chipmunk" -Generator $vsGen -Arguments @("-DBUILD_DEMOS=OFF", "-DBUILD_SHARED=OFF")
    }
    else {
        # Use Ninja with Clang for dependencies
        $clangCxxPath = $CLANG_PATH
        if ($CLANG_PATH -like "*clang.exe") {
            $clangCxxPath = $CLANG_PATH -replace "clang\.exe$", "clang++.exe"
            if (-not (Test-Path $clangCxxPath)) {
                $clangCxxPath = $CLANG_PATH  # Fallback to clang if clang++ not found
            }
        }
        # Get resource compiler path and convert to CMake format
        $rcPath = Get-ClangResourceCompiler -ClangPath $CLANG_PATH
        $cmakeClangPath = Convert-ToCMakePath -Path $CLANG_PATH
        $cmakeClangCxxPath = Convert-ToCMakePath -Path $clangCxxPath
        $cmakeRcPath = Convert-ToCMakePath -Path $rcPath
        
        # Get MinGW library path
        if (-not $MINGW_PATH) {
            Write-Error-Status "MinGW path not found. Cannot configure Chipmunk without MinGW libraries."
            exit 1
        }
        $mingwLibPath = Get-MinGW-LibraryPath -GccPath $MINGW_PATH
        
        # Configure Chipmunk with MinGW-style linking
        $chipmunkArgs = @(
            "-DBUILD_DEMOS=OFF",
            "-DBUILD_SHARED=OFF",
            "-DCMAKE_C_COMPILER=`"$cmakeClangPath`"",
            "-DCMAKE_CXX_COMPILER=`"$cmakeClangCxxPath`"",
            "-DCMAKE_RC_COMPILER=`"$cmakeRcPath`"",
            "-DCMAKE_SYSTEM_NAME=Windows",
            "-DCMAKE_C_FLAGS=`"-target x86_64-pc-windows-gnu`"",
            "-DCMAKE_CXX_FLAGS=`"-target x86_64-pc-windows-gnu`"",
            "-DCMAKE_EXE_LINKER_FLAGS=`"-fuse-ld=lld -target x86_64-pc-windows-gnu`"",
            "-DCMAKE_SHARED_LINKER_FLAGS=`"-fuse-ld=lld -target x86_64-pc-windows-gnu`""
        )
        
        # Add MinGW library path if found
        if ($mingwLibPath) {
            $chipmunkArgs += @("-DCMAKE_LIBRARY_PATH=`"$mingwLibPath`"")
        }
        Invoke-CMakeConfigure -SourcePath "..\..\..\deps\chipmunk" -BuildPath "build\win32\chipmunk" -Generator "Ninja" -Arguments $chipmunkArgs
    }
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
    if ($UseMSVC -or (-not $CLANG_PATH)) {
        # Use Visual Studio generator for dependencies
        $vsGen = "Visual Studio 17 2022"
        Invoke-CMakeConfigure -SourcePath "..\..\..\deps\libjpeg-turbo" -BuildPath "build\win32\libjpeg-turbo" -Generator $vsGen -Arguments @("-DWITH_SIMD=ON")
    }
    else {
        # Use Ninja with Clang for dependencies
        $clangCxxPath = $CLANG_PATH
        if ($CLANG_PATH -like "*clang.exe") {
            $clangCxxPath = $CLANG_PATH -replace "clang\.exe$", "clang++.exe"
            if (-not (Test-Path $clangCxxPath)) {
                $clangCxxPath = $CLANG_PATH  # Fallback to clang if clang++ not found
            }
        }
        # Get resource compiler path and convert to CMake format
        $rcPath = Get-ClangResourceCompiler -ClangPath $CLANG_PATH
        $cmakeClangPath = Convert-ToCMakePath -Path $CLANG_PATH
        $cmakeClangCxxPath = Convert-ToCMakePath -Path $clangCxxPath
        $cmakeRcPath = Convert-ToCMakePath -Path $rcPath
        
        # Get MinGW library path
        if (-not $MINGW_PATH) {
            Write-Error-Status "MinGW path not found. Cannot configure libjpeg-turbo without MinGW libraries."
            exit 1
        }
        $mingwLibPath = Get-MinGW-LibraryPath -GccPath $MINGW_PATH
        
        # Configure libjpeg-turbo with MinGW-style linking
        $libjpegArgs = @(
            "-DWITH_SIMD=ON",
            "-DCMAKE_C_COMPILER=`"$cmakeClangPath`"",
            "-DCMAKE_CXX_COMPILER=`"$cmakeClangCxxPath`"",
            "-DCMAKE_RC_COMPILER=`"$cmakeRcPath`"",
            "-DCMAKE_SYSTEM_NAME=Windows",
            "-DCMAKE_C_FLAGS=`"-target x86_64-pc-windows-gnu`"",
            "-DCMAKE_CXX_FLAGS=`"-target x86_64-pc-windows-gnu`"",
            "-DCMAKE_EXE_LINKER_FLAGS=`"-fuse-ld=lld -target x86_64-pc-windows-gnu`"",
            "-DCMAKE_SHARED_LINKER_FLAGS=`"-fuse-ld=lld -target x86_64-pc-windows-gnu`""
        )
        
        # Add MinGW library path if found
        if ($mingwLibPath) {
            $libjpegArgs += @("-DCMAKE_LIBRARY_PATH=`"$mingwLibPath`"")
        }
        Invoke-CMakeConfigure -SourcePath "..\..\..\deps\libjpeg-turbo" -BuildPath "build\win32\libjpeg-turbo" -Generator "Ninja" -Arguments $libjpegArgs
    }
}
catch {
    Write-Error-Status "libjpeg-turbo configuration failed: $($_)"
    exit 1
}

# Configure Node.js
Write-Status "Configuring Node.js Library..." "Yellow"

# Check if Visual Studio with ClangCL is available (required for Node.js v24+)
if (-not $VS_CLANGCL_AVAILABLE) {
    Write-Error-Status "Node.js v24+ requires Visual Studio with ClangCL support."
    Write-Host ""
    Write-Host "Please install Visual Studio 2022 with the following components:" -ForegroundColor Yellow
    Write-Host "1. 'Desktop development with C++' workload" -ForegroundColor White
    Write-Host "2. C++ Clang Compiler for Windows (Microsoft.VisualStudio.Component.VC.Llvm.Clang)" -ForegroundColor White
    Write-Host "3. MSBuild support for LLVM toolset (Microsoft.VisualStudio.Component.VC.Llvm.ClangToolset)" -ForegroundColor White
    Write-Host ""
    Write-Host "You can install these via:" -ForegroundColor Cyan
    Write-Host "  winget install Microsoft.VisualStudio.2022.BuildTools --override --add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.VC.Llvm.Clang --add Microsoft.VisualStudio.Component.VC.Llvm.ClangToolset" -ForegroundColor Gray
    Write-Host ""
    Write-Host "After installing, restart your PowerShell session and run this script again." -ForegroundColor Yellow
    Write-Error-Status "Node.js configuration is required. Exiting."
    exit 1
}

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
        
        # Run vcbuild with proper environment (using openssl-no-asm to avoid NASM requirement)
        Write-Status "Running Node.js vcbuild.bat..." "Cyan"
        $process = Start-Process -FilePath "cmd" -ArgumentList @("/c", "vcbuild.bat", "nobuild", "nosign", "openssl-no-asm") -Wait -PassThru -NoNewWindow
        
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
if (Test-Path "tools\make_bat") {
    Copy-Item "tools\make_bat" "make.bat" -Force
    Write-Host ""
    Write-Success-Status "Configuration completed successfully!"
    Write-Host "Type 'make' to build the project." -ForegroundColor Yellow
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

Write-Host ""
Write-Status "Dependency Installation and Configuration script finished." "Green"
