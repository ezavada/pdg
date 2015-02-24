@echo off
set NODE_DEBUG=

echo SKIPPED - Starting echo server ...
REM start /B %PDG_ROOT%\tools\node.exe %PDG_ROOT%\tools\echo_tcp.js
REM for /F "TOKENS=1,2,*" %%a in ('tasklist /FI "IMAGENAME eq node.exe"') do set ECHOSERVER_PID=%%b

echo Running Tests ...
cd %PDG_ROOT%\test
REM run the tests, some of which use the echo server
copy /Y %PDG_ROOT%\pdg.exe %PDG_ROOT%\test\
pdg.exe client_test.js %*

REM cleanup after the tests
cd %PDG_ROOT%
taskkill /PID %ECHOSERVER_PID% /T /F
