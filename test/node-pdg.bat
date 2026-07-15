@echo off
set NODE_DEBUG=
if "%PDG_ROOT%"=="" (
    cd /d "%~dp0"
    cd ..
    set PDG_ROOT=%CD%
)
set NODE_BIN=%PDG_ROOT%\tools\node.exe
set PDG_TEST_MODE=node
set PDG_TEST_PLATFORM=win32
set PDG_TEST_ARTIFACTS_DIR=%PDG_ROOT%\artifacts\test-results\%PDG_TEST_PLATFORM%\%PDG_TEST_MODE%
set PDG_TEST_LOG_DIR=%PDG_TEST_ARTIFACTS_DIR%\logs
set PDG_TEST_REPORT_DIR=%PDG_TEST_ARTIFACTS_DIR%\reports
set PDG_TEST_TEMP_DIR=%PDG_TEST_ARTIFACTS_DIR%\tmp

if not exist "%PDG_TEST_LOG_DIR%" mkdir "%PDG_TEST_LOG_DIR%"
if not exist "%PDG_TEST_REPORT_DIR%" mkdir "%PDG_TEST_REPORT_DIR%"
if not exist "%PDG_TEST_TEMP_DIR%" mkdir "%PDG_TEST_TEMP_DIR%"

cd /d "%PDG_ROOT%"

if not exist node_modules\jasmine-node\package.json (
    echo Installing jasmine-node and dependencies...
    powershell -ExecutionPolicy Bypass -File test\install-dependencies.ps1
    if errorlevel 1 exit /b 1
)

echo Starting echo server ...
for /F %%i in ('powershell -NoProfile -ExecutionPolicy Bypass -Command "$p = Start-Process -FilePath \"$env:PDG_ROOT\\tools\\node.exe\" -ArgumentList \"$env:PDG_ROOT\\tools\\echo_tcp.js\" -WorkingDirectory \"$env:PDG_ROOT\" -PassThru -WindowStyle Hidden; $p.Id"') do set ECHOSERVER_PID=%%i
if not defined ECHOSERVER_PID exit /b 1

echo Running Tests ...
if exist "%NODE_BIN%" (
    "%NODE_BIN%" "%PDG_ROOT%\test\node_test.js" %*
) else (
    node "%PDG_ROOT%\test\node_test.js" %*
)
set BUILD_STATUS=%ERRORLEVEL%

REM cleanup after the tests
taskkill /PID %ECHOSERVER_PID% /T /F >nul 2>nul
exit /b %BUILD_STATUS%
