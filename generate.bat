@echo off

set /p POST_BUILD_COPY_PATH="Enter the path to copy the DLL to after building: "
echo Generating project files...
call tools\premake5 --postbuildcopy="%POST_BUILD_COPY_PATH%" vs2022