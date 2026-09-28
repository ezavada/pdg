@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0rigs.ps1" %*
exit /b %ERRORLEVEL%
