@echo off
set NODE_DEBUG=

REM Ensure we run from repo root (parent of test\) so PDG_ROOT and paths are correct
cd /d "%~dp0"
cd ..
REM Set up environment variables like the bash script
set PDG_ROOT=%CD%
set PDG_NPM=%PDG_ROOT%\tools\npm
set PDG_NODE_GYP=%PDG_ROOT%\tools\node-gyp
set PDG_JASMINE_NODE=%PDG_ROOT%\tools\jasmine-node
set PDG_REPL=%PDG_ROOT%\tools\repl
set PDG_TEST_MODE=client
set PDG_TEST_PLATFORM=win32
set PDG_TEST_ARTIFACTS_DIR=%PDG_ROOT%\artifacts\test-results\%PDG_TEST_PLATFORM%\%PDG_TEST_MODE%
set PDG_TEST_LOG_DIR=%PDG_TEST_ARTIFACTS_DIR%\logs
set PDG_TEST_REPORT_DIR=%PDG_TEST_ARTIFACTS_DIR%\reports
set PDG_TEST_TEMP_DIR=%PDG_TEST_ARTIFACTS_DIR%\tmp

if not exist "%PDG_TEST_LOG_DIR%" mkdir "%PDG_TEST_LOG_DIR%"
if not exist "%PDG_TEST_REPORT_DIR%" mkdir "%PDG_TEST_REPORT_DIR%"
if not exist "%PDG_TEST_TEMP_DIR%" mkdir "%PDG_TEST_TEMP_DIR%"

echo PDG_ROOT = %PDG_ROOT%
echo PDG_TEST_ARTIFACTS_DIR = %PDG_TEST_ARTIFACTS_DIR%

REM Check if jasmine-node is available, if not install it
if not exist node_modules\jasmine-node\package.json (
    echo Installing jasmine-node and dependencies...
    echo Running PowerShell installation script...
    powershell -ExecutionPolicy Bypass -File test\install-dependencies.ps1
    if errorlevel 1 (
        echo ERROR: Failed to install dependencies.
        goto Error
    )
    echo Installation completed.
)

REM Check if jasmine-node is now available
if not exist node_modules\jasmine-node\package.json (
    echo ERROR: Failed to install jasmine-node.
    echo Please run the configure script first or install dependencies manually.
    goto Error
)

echo Starting echo server ...
for /F %%i in ('powershell -NoProfile -ExecutionPolicy Bypass -Command "$p = Start-Process -FilePath \"$env:PDG_ROOT\\tools\\node.exe\" -ArgumentList \"$env:PDG_ROOT\\tools\\echo_tcp.js\" -WorkingDirectory \"$env:PDG_ROOT\" -PassThru -WindowStyle Hidden; $p.Id"') do set ECHOSERVER_PID=%%i
if not defined ECHOSERVER_PID (
    echo ERROR: Failed to start echo server.
    goto Error
)

echo Running Tests ...
cd test
REM run the tests, some of which use the echo server
set PDG_CLIENT_EXE=pdg-run.exe
set PDG_SOURCE_EXE=
if exist ..\msvc\src\Release\pdg.exe set PDG_SOURCE_EXE=..\msvc\src\Release\pdg.exe
if not defined PDG_SOURCE_EXE if exist ..\pdg.exe set PDG_SOURCE_EXE=..\pdg.exe
if not defined PDG_SOURCE_EXE (
    echo ERROR: No Windows PDG executable found. Build with .\make.ps1 -Target pdg first.
    goto Error
)
del /F /Q pdg_crash.log >nul 2>nul
del /F /Q "%PDG_CLIENT_EXE%" >nul 2>nul
copy /Y "%PDG_SOURCE_EXE%" "%PDG_CLIENT_EXE%" >nul
if errorlevel 1 (
    echo ERROR: Failed to stage %PDG_SOURCE_EXE% as %CD%\%PDG_CLIENT_EXE%.
    goto Error
)
echo Using PDG client executable: %CD%\%PDG_CLIENT_EXE% ^(from %PDG_SOURCE_EXE%^)
@echo on
%PDG_CLIENT_EXE% client_test.js %*
@echo off
set BUILD_STATUS=%ERRORLEVEL%

REM cleanup after the tests (kill echo server; "SUCCESS...terminated" is from taskkill, not pdg.exe)
cd ..
if defined ECHOSERVER_PID taskkill /PID %ECHOSERVER_PID% /T /F >nul 2>nul

if not %BUILD_STATUS%==0 goto Error

goto Success

:Error
echo Tests Failed
exit /b 1

:Success
echo All Tests Succeeded
exit /b 0
