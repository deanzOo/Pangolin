@echo off
pushd ..\
call lib\bin\premake\premake5.exe vs2019
popd
PAUSE