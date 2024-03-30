
@echo off

g++ main.cpp -o main.exe -I /. -I C:\Users\79143\AppData\Local\Programs\Python\Python38\include -I C:\Users\79143\AppData\Local\Programs\Python\Python38\Lib\site-packages\numpy\core\include -L C:\Users\79143\AppData\Local\Programs\Python\Python38\libs -lpython38
main.exe

pause