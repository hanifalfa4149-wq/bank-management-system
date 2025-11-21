@echo off
REM Clean script for bank-management-system (Windows)

pushd "%~dp0src"
if exist main.exe del /Q main.exe
popd

echo Clean complete.
exit /b 0
