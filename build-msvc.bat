@echo off
setlocal enabledelayedexpansion

set SCRIPT_DIR=%~dp0
if "%SCRIPT_DIR:~-1%"=="\" set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%

if "%BUILD_DIR%"=="" set BUILD_DIR=%SCRIPT_DIR%\build-msvc
if "%CONFIG%"=="" set CONFIG=Release
if "%EMBREE_DIR%"=="" set EMBREE_DIR=C:\embree-4.4.0\lib\cmake\embree-4.4.0
if "%TBB_DIR%"=="" set TBB_DIR=C:\oneapi-tbb-2021.11.0\lib\cmake\tbb

set TARGETS=%*
if "%TARGETS%"=="" set TARGETS=all

pushd "%SCRIPT_DIR%"

nmake /f Makefile.msvc BUILD_DIR="%BUILD_DIR%" CONFIG=%CONFIG% EMBREE_DIR="%EMBREE_DIR%" TBB_DIR="%TBB_DIR%" %TARGETS%
if errorlevel 1 goto :error

echo.
echo Binaries have been built in %BUILD_DIR%
popd
exit /b 0

:error
popd
exit /b 1
