@echo off
REM Run script for bank-management-system (Windows)
REM Builds if main.exe is missing, then runs it.

REM Change to script directory and into src
pushd "%~dp0src"

REM If executable doesn't exist, build it
if not exist main.exe (
    echo main.exe not found, building...
    call "%~dp0build.bat"
    if %ERRORLEVEL% NEQ 0 (
        echo Build failed. Aborting run.
        popd
        exit /b %ERRORLEVEL%
    )
)

REM Run the program
.\main.exe

popd
exit /b 0
