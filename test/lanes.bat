@echo off
setlocal

cd /d "%~dp0"
cd ..
set PDG_ROOT=%CD%

set NODE_BIN=%PDG_ROOT%\tools\node.exe
if exist "%NODE_BIN%" (
    "%NODE_BIN%" "%PDG_ROOT%\test\run_lanes.js" %*
) else (
    node "%PDG_ROOT%\test\run_lanes.js" %*
)

endlocal
