@echo off
mkdir msvc
cd msvc
set MODE=0
reg query "HKEY_CLASSES_ROOT\VisualStudio.DTE.10.0" >> nul 2>&1
if "%ERRORLEVEL%" NEQ "1" (set MODE=10)
reg query "HKEY_LOCAL_MACHINE\Software\Microsoft\VisualStudio\10.0" >> nul 2>&1
if "%ERRORLEVEL%" NEQ "1" (set MODE=10)
reg query "HKEY_CLASSES_ROOT\VisualStudio.DTE.11.0" >> nul 2>&1
if "%ERRORLEVEL%" NEQ "1" (set MODE=12)
reg query "HKEY_LOCAL_MACHINE\Software\Microsoft\VisualStudio\12.0" >> nul 2>&1
if "%ERRORLEVEL%" NEQ "1" (set MODE=12)
reg query "HKEY_CLASSES_ROOT\VisualStudio.DTE.15.0" >> nul 2>&1
if "%ERRORLEVEL%" NEQ "1" (set MODE=15)
reg query "HKEY_LOCAL_MACHINE\Software\Microsoft\VisualStudio\15.0" >> nul 2>&1
if "%MODE%" NEQ "0" ( 
  if "%MODE%" == "15" ( 
    echo Creating Project Files for Visual Studio 15...
    cmake -G "Visual Studio 15" .. -DCAN_BUILD_INTERFACES=OFF
  ) else if "%MODE%" == "12" ( 
    echo Creating Project Files for Visual Studio 12...
    cmake -G "Visual Studio 12" .. -DCAN_BUILD_INTERFACES=OFF
  ) else ( 
    echo Creating Project Files for Visual Studio 10...
    cmake -G "Visual Studio 10" .. -DCAN_BUILD_INTERFACES=OFF
  ) 
) else (
  echo Visual Studio not installed! 
  goto end
) 
cd ..

echo Configuring GLFW Library...
mkdir build\win32\glfw
cd build\win32\glfw
cmake -D GLFW_BUILD_EXAMPLES=OFF -D GLFW_BUILD_TESTS=OFF ..\..\..\deps\glfw
cd ..\..\..\

echo Configuring Chipmunk Library...
mkdir build\win32\chipmunk
cd build\win32\chipmunk
cmake -D BUILD_DEMOS=OFF ..\..\..\deps\chipmunk
cd ..\..\..\

echo Configuring PNG Library...
echo -- Copying deps\png\scripts\pnglibconf.h.prebuilt to deps\png\pnglibconf.h
copy deps\png\scripts\pnglibconf.h.prebuilt deps\png\pnglibconf.h

echo Configuring JPEG Turbo Library...
mkdir build\win32\libjpeg-turbo
cd build\win32\libjpeg-turbo
cmake ..\..\..\deps\libjpeg-turbo
cd ..\..\..\

echo Configuring Node.js Library...
cd deps\node
mkdir out\Debug
mkdir out\Release
call vcbuild.bat nobuild nosign
cd ..\..

copy tools\make_bat make.bat
echo Done. Type 'make' to build.

:end
