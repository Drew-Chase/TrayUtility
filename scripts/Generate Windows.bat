@echo off
@title Generate Visual Studio Files
@echo Generating Visual Studio Files...
cd ../
premake5 vs2022
@echo Done!
@pause