
@echo off

g++ main.cpp src/Code/solver.cpp src/Code/equations.cpp src/Include/consts.h -o main.exe -I C:\Users\79143\AppData\Local\Programs\Python\Python38\include -I src/Include -I C:\Users\79143\AppData\Local\Programs\Python\Python38\Lib\site-packages\numpy\core\include -L C:\Users\79143\AppData\Local\Programs\Python\Python38\libs -lpython38
@REM main.exe
@REM del main.exe
pause