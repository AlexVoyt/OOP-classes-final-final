@echo off
clear
mkdir ..\build
pushd ..\build
echo Compiling...
cl /Zi /Od /EHsc ..\code\main.cpp
IF %ERRORLEVEL% == 0 (
    echo SUCCSESS
    REM main.exe
) ELSE (
    echo ERROR DURING COMPILING
)
popd
