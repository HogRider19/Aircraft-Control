g++ main.cpp \
    src/Code/solver.cpp \
    src/Code/equations.cpp \
    src/Code/ploter.cpp \
    \
    -o main \
    -O3 \
    \
    -I src/Include \
    -I /usr/include/python3.10 \
    -lpython3.10

./main

rm ./main