echo Compiling...
@echo off
set winexe=wintest
gcc %1 -o wintest

if %errorlevel% equ 0 (
    echo off
) else (
    echo on
    echo Failed to compile. 
)

.\wintest.exe
del wintest.exe