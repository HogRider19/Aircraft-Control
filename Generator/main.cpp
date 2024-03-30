#define _USE_MATH_DEFINES
#define WITHOUT_NUMPY

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <random>
#include "matplotlibcpp.h"

#define forI(i, c) for(size_t i = 0; i < c.size(); i++)

// #define D 0.5
// #define a 2.0
// #define h 0.002
// #define n 10000.0

#define D 1.0
#define a 0.1
#define h 0.5
#define n 70000.0

namespace plt = matplotlibcpp;

double getRandom(double t) {
    return (((double)std::rand() / (double)RAND_MAX) - 0.5) * 1;
}

double correlationFunction(double t) {
    return D * exp(-a * t);
}


double f(double x, double t) {
    double s0 = h / 12;
    double kf = sqrt((2 * D) / (a * s0));
    double tf = 1 / a;

    return -1 / tf * x + kf / tf * getRandom(t);
}

double eulerMethod(double x0, double t0, double step, double endTime, std::vector<double>& xRes, std::vector<double>& res) {
    double x = x0;
    double t = t0;
    
    while (t < endTime) {
        double dx = step * f(x, t);
        x += dx;
        t += step;
        xRes.push_back(t);
        res.push_back(x);
    }
    
    return x;
}

std::vector<double> getCore(std::vector<double> x, std::vector<double> y) {
    // Mx = 1 / n * sum(Xi)
    // Dx = 1 / (n - 1) * sum(Xi - Mx)^2
    // K(t) = 1 / (n + 1 - j) * sum ((Xi - Mx) (Xi+j - Mx))

    double Mx = 0;
    forI(i, y) Mx += y[i];
    Mx = (Mx / ((double)x.size()));

    double Dx = 0;
    forI(i, y) Dx += pow((y[i] - Mx), 2);
    Dx = (Dx / (n - 1));

    std::vector<double> k;
    double delta = x[1] - x[0];
    for (int j = 0; j < x.size(); j++)
    {
        double sum = 0;
        for(int i = 0; i < x.size() - j; i++)
            sum += (y[i] - Mx) * (y[i + j] - Mx);

        //std::cout << sum / (x.size() - (n + 1 - j)) << std::endl;

        k.push_back(sum / (x.size() / 10));
        //k.push_back(sum / (x.size() + 1 - j));
    }

    
    double d = y[0] - k[0];
    forI(i, k) k[i] += d;
    return k;
}


int main() {
    double t0 = 0; 
    double step = h; 
    double endTime = 3 / a;

    std::vector<double> Xt_x;
    std::vector<double> Xt_y;
    eulerMethod(correlationFunction(t0), t0, endTime / (double)n, endTime, Xt_x, Xt_y);
    
    std::vector<double> th_x;
    std::vector<double> th_y;
    forI(i, Xt_x)
    {
        double x = endTime / (double)Xt_x.size() * i;
        double y = correlationFunction(x);
        th_x.push_back(x);
        th_y.push_back(y);
    }

    std::vector<double> core_y = getCore(th_x, Xt_y);    
    std::vector<double> core_x {th_x.begin(), th_x.begin() + core_y.size()};
    
    std::vector<double> th_x_n {th_x.begin(), th_x.begin() + core_y.size()};
    std::vector<double> th_y_n {th_y.begin(), th_y.begin() + core_y.size()};

    double border = 20.0;
    int borderIndex = core_x.size() - 1;
    forI(i, core_x) if (core_x[i] > border) { borderIndex = i; break; }
    core_x = {core_x.begin(), core_x.begin() + borderIndex};
    core_y = {core_y.begin(), core_y.begin() + borderIndex};
    th_x_n = {th_x_n.begin(), th_x_n.begin() + borderIndex};
    th_y_n = {th_y_n.begin(), th_y_n.begin() + borderIndex};

    plt::figure(1);
    plt::plot(th_x_n, th_y_n);
    plt::plot(core_x, core_y);
    //plt::plot(Xt_x, Xt_y);
    plt::grid(true);
    plt::show();
    
    return 0;
}