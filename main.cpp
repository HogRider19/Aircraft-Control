#include <iostream>
#include <cmath>

// Определяем функцию, для которой нужно решить дифференциальное уравнение
double f(double x, double y) {
    return y - pow(x, 2); 
}

// Метод Эйлера
double eulerMethod(double x0, double y0, double h, double x, double (*func)(double x, double y)) {
    double y = y0;
    while (x0 < x) {
        y += h * f(x0, y); // Вычисляем новое значение y
        x0 += h; // Увеличиваем x на шаг h
    }
    return y;
}

int main() {
    double x0 = 0; // Начальное значение x
    double y0 = 1; // Начальное значение y
    double h = 0.001; // Шаг
    double x = 1; // Значение x, для которого нужно найти решение уравнения

    std::cout << eulerMethod(x0, y0, h, x, f) << std::endl;

    return 0;
}