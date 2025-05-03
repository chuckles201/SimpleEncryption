echo Compiling...
@echo off
set winexe=wintest
g++ tests.c -o wintest

if %errorlevel% equ 0 (
    echo off
) else (
    echo on
    echo Failed to compile.
)

.\wintest.exe
del wintest.exe