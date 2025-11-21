@echo off
REM Build script for bank-management-system (Windows)
REM Usage: double-click or run from PowerShell/cmd: build.bat

REM Change to script directory and into src
pushd "%~dp0src"

REM Compile all sources into main.exe with include path
gcc *.c -I../include -o main.exe
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Build failed with exit code %ERRORLEVEL%.
    popd
    exit /b %ERRORLEVEL%
)

echo Build succeeded: %CD%\main.exe
popd
exit /b 0
