
@echo off

g++ main.cpp src/Code/solver.cpp src/Code/equations.cpp src/Code/ploter.cpp src/Include/consts.h -o main.exe -I C:\Users\79143\AppData\Local\Programs\Python\Python38\include -I src/Include -I C:\Users\79143\AppData\Local\Programs\Python\Python38\Lib\site-packages\numpy\core\include -L C:\Users\79143\AppData\Local\Programs\Python\Python38\libs -lpython38
main.exe
del main.exe
pause