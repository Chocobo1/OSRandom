@echo off

if not defined CL_EXIST (
	call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
	set CL_EXIST=1
)

cl /O2 /EHsc /W4 test.cpp /Fe: run_tests.exe
