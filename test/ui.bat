@echo off
setlocal
set NODE_DEBUG=

cd /d "%~dp0"
cd ..
set PDG_ROOT=%CD%
set PDG_TEST_MODE=ui
set PDG_TEST_PLATFORM=win32

set NODE_BIN=%PDG_ROOT%\tools\node.exe
if exist "%NODE_BIN%" (
    "%NODE_BIN%" "%PDG_ROOT%\test\lib\ui_runner.js" %*
) else (
    node "%PDG_ROOT%\test\lib\ui_runner.js" %*
)

endlocal
