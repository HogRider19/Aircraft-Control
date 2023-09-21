#include "mathUtils.h"

double rungeKuttaMethod(double x0, double y0, double h, double xn, double (*func)(double x, double y)) {
    double y = y0;
    double x = x0;

    while (x < xn) {
        double k1 = func(x, y);
        double k2 = func(x + h / 2, y + k1 * h / 2);
        double k3 = func(x + h / 2, y + k2 * h / 2);
        double k4 = func(x + h, y + k3 * h);

        y = y + (k1 + 2 * k2 + 2 * k3 + k4) * h / 6;
        x = x + h;
    }
    return y;
}

double eulerMethod(double x0, double y0, double h, double x, double (*func)(double x, double y)) {
    double y = y0;
    while (x0 < x) {
        y += h * func(x0, y); 
        x0 += h; 
    }
    return y;
}