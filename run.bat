@echo off

:parse
IF "%~1"=="" GOTO help
IF "%~1"=="run" GOTO run
IF "%~1"=="test" GOTO test

:help
echo help
exit

:run
g++ -o main .\main.cpp
.\main.exe
exit

:test
echo compiling tests
g++ -o tests tests\test_optimize_single.cpp
echo running tests
.\tests.exe