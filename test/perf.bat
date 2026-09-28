@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0perf.ps1" %*
exit /b %ERRORLEVEL%
