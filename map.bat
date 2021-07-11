@echo OFF
rem "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
mkdir build
cd build

cmake -G"Visual Studio 15 2017 Win64" ..

msbuild Map_Builder.sln
cd ..
