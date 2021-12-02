call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
cmake --version

mkdir build
cd build
cmake -A x64 -DCMAKE_GENERATOR_TOOLSET=v142 ..

pause