
@echo off

g++ main.cpp solver.cpp equations.cpp consts.h -o main.exe
main.exe
del main.exe
pause