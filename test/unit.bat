@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0unit.ps1" %*
exit /b %ERRORLEVEL%
