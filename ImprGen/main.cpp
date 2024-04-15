#define _USE_MATH_DEFINES
#define WITHOUT_NUMPY

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <random>
#include "matplotlibcpp.h"

#define forI(i, c) for(size_t i = 0; i < c.size(); i++)

#define D 1.0
#define a 2.0
#define h 0.002
#define n 10000.0

// #define D 1.0
// #define a 0.1
// #define h 0.5
// #define n 70000.0

namespace plt = matplotlibcpp;

double getRandom(double t) {
    return (((double)std::rand() / (double)RAND_MAX) - 0.5) * 1;
}

double getRandom(double from, double to) {
    return (((double)std::rand() / (double)RAND_MAX) * (to - from) + from) * 1;
}

double correlationFunction(double t) {
    //return (1 / sqrt(2 * M_PI) * exp(-pow(t, 2) / 2));
    return D * exp(-a * t);
}


double f(double x, double t) {
    double s0 = h;
    double kf = sqrt((2 * D) / (a * s0));
    double tf = 1 / a;

    return -1 / tf * x + kf / tf * t;
}

double eulerMethod(double x0, double t0, double step, double endTime, std::vector<double>& xRes, std::vector<double>& res, std::vector<double> rnd) 
{
    double x = x0;
    double t = t0;
    
    int r = 0;

    while (t < endTime) {
        double dx = step * f(x, rnd[r]);
        r++;
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

        //k.push_back(sum / (x.size() / 10));
        k.push_back(sum / (x.size() + 1 - j));
    }

    
    double d = y[0] - k[0];
    forI(i, k) k[i] += 0.4;
    return k;
}

double factorial(double N) {
    double F = 1;
    for(double i = 1; i <= N; ++i) {
        F *= i;
    }
    return F;
}

double F(double x)
{
    double res = 0;
    double del = 1;
    for (int i = 0; i < 20; i++)
    {
        res += del * (pow(x, 2*i) / (pow(2, i) * (1 + 2*i) * factorial(i - 1))) * 3;
        del *= -1;

        //std::cout << res <<  std::endl;
    }
    return res * x / sqrt(2 * M_PI);
}


std::vector<double> applay(std::vector<double> vals, double (*fun)(double))
{
    std::vector<double> res;
    forI(i, vals) res.push_back(fun(vals[i]));
    return res;
}

void GetDensity(std::vector<double>& resultX,
    std::vector<double>& resultY,
    std::vector<double>& values,
    int co)
{
    double min = *std::min_element(begin(values), end(values));
    double max = *std::max_element(begin(values), end(values));
    double delta = (max - min) / co;

    for (double i = min; i <= max; i += delta)
    {
        resultX.push_back(i);

        int c = 0;
        for (size_t index = 0; index < values.size(); index++)
        {
            if (values[index] > i && values[index] <= i + delta)
                c++;
        }
        resultY.push_back(c);
    }
}

double getExpectedValue(std::vector<double> values, int co)
{
    std::vector<double> counts;
    std::vector<double> vals;

    GetDensity(vals, counts, values, co);

    double res = 0;
    for (size_t index = 0; index < vals.size(); index++)
        res += vals[index] * (((double)counts[index]) / (double)values.size());

    return res;
}

double reverse(double x)
{
    /*
        f(z) = 1 / (1 - sin(z)^2) [0, pi/4]
        F(z) = tan(z) = R

        x1 = arctan(r)

        left: 0
        right: 4

        x_i = arctan(e_i);
    */

    //return atan(x);
    return atan(x);
}


double colmagorivCheck(std::vector<double>& dataX,
    std::vector<double>& dataY,
    std::vector<double>& theoryDataX,
    std::vector<double>& theoryDataY,
    int from)
{
    double max = 0;
    for (size_t i = from; i < dataX.size(); i++)
    {
        double c = std::fabs(dataY[i] - theoryDataY[i]);
        if (c > max)
            max = c;
    }
    return max;
}

void getTheoryDistributionFunction(std::vector<double>& realX,
     std::vector<double>& x,
     std::vector<double>& y)
{
    for (auto _x : realX)
    {
        x.push_back(_x);
        y.push_back(atan(_x + 1.22));
    }
}

void getDistributionFunction(
    const std::vector<double>& v,
    std::vector<double>& resX,
    std::vector<double>& resY)
{
    std::vector<double> sortedV = v;
    std::sort(sortedV.begin(), sortedV.end());

    int s = sortedV.size();
    for(int i = 0; i < s; i++)
    {
        double val = sortedV[i];
        int count = 0;
        for(int j = 0; j < s; j++)
        {
            if(sortedV[j] <= val)
            {
                count++;
            }
        }
        resX.push_back(val);
        resY.push_back(count / static_cast<double>(s));
    }
}


int main() {

    // 4
    srand(4);
    int rndCount = 100000;
    std::vector<double> rnd(rndCount);

    for (auto& item : rnd) 
    {
        double sum = 0;
        for(int i = 0; i < 12; i++) sum += getRandom(0, 1);
        item = sum - 6;
    }

    double t0 = 0; 
    double step = h; 
    double endTime = 3 / a;

    std::vector<double> Xt_x;
    std::vector<double> Xt_y;
    eulerMethod(0, t0, h, endTime, Xt_x, Xt_y, rnd);

    std::vector<double> th_x;
    std::vector<double> th_y;
    forI(i, Xt_x)
    {
        double x = endTime / (double)Xt_x.size() * i;
        double y = correlationFunction(x);
        th_x.push_back(x);
        th_y.push_back(y);
    }

    std::vector<double> core_y = getCore(Xt_x, Xt_y);    
    std::vector<double> core_x {th_x.begin(), th_x.begin() + core_y.size()};

    std::vector<double> F_y = applay(Xt_y, F);
    std::vector<double> F_x {Xt_x.begin(), Xt_x.begin() + Xt_x.size()};

    std::cout << "Expected value before: " << getExpectedValue(F_y, 1000) << std::endl;

    std::vector<double> new_F_y = applay(F_y, reverse);
    std::vector<double> new_F_x {th_x.begin(), th_x.begin() + core_y.size()};

    std::cout << "Expected value after: " << getExpectedValue(new_F_y, 1000) << std::endl;

    //
    std::vector<double> realTheoryX;
    std::vector<double> realTheoryY;
    getDistributionFunction(new_F_y, realTheoryX, realTheoryY);

    std::vector<double> theoryX;
    std::vector<double> theoryY;
    getTheoryDistributionFunction(realTheoryX, theoryX, theoryY);
    //

    double c = colmagorivCheck(realTheoryX, realTheoryY, theoryX, theoryY, 0);
    std::cout << "colmagorivCheck Index: " << c <<  std::endl;

    if (c < 0.162)
        std::cout << "colmagorivCheck: Passed" << std::endl;
    else
        std::cout << "colmagorivCheck: Failed" << std::endl;

    double border = 0.8;
    int nn = 0;
    int borderIndex = core_x.size() - 1;
    forI(i, core_x) if (core_x[i] > border) { borderIndex = i; break; }
    core_x = {core_x.begin(), core_x.begin() + borderIndex};
    core_y = {core_y.begin(), core_y.begin() + borderIndex};
    th_x = {th_x.begin(), th_x.begin() + borderIndex};
    th_y = {th_y.begin(), th_y.begin() + borderIndex};
    new_F_x = {new_F_x.begin() + nn, new_F_x.begin() + borderIndex};
    new_F_y = {new_F_y.begin() + nn, new_F_y.begin() + borderIndex};
    F_x = {F_x.begin(), F_x.begin() + borderIndex};
    F_y = {F_y.begin(), F_y.begin() + borderIndex};
    Xt_x = {Xt_x.begin(), Xt_x.begin() + borderIndex};
    Xt_y = {Xt_y.begin(), Xt_y.begin() + borderIndex};

    plt::figure(1);
    plt::title("Кореляционная функция");
    plt::plot(th_x, th_y);
    plt::plot(core_x, core_y);
    plt::grid(true);

    theoryX = {theoryX.begin(), theoryX.begin() + 723};
    theoryY = {theoryY.begin(), theoryY.begin() + 723};

    plt::figure(2);
    plt::title("Функция распределения");
    plt::plot(theoryX, theoryY);
    plt::plot(realTheoryX, realTheoryY);
    plt::grid(true);

    plt::figure(3);
    plt::title("Процесс");
    plt::plot(new_F_x, new_F_y);
    plt::grid(true);
    plt::show();

    return 0;
}