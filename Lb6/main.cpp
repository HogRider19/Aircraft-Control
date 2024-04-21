#define forI(i, p) for(size_t i = 0; i < p.size(); i++)
#define pr(m) std::cout << m <<std::endl
#define _USE_MATH_DEFINES
#define WITHOUT_NUMPY

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <random>
#include "matplotlibcpp.h"

#define D 0.5
#define a 2.0
#define h 0.002

namespace plt = matplotlibcpp;

int step_num = 1;

double getRandom(double from = 0, double to = 1) {
    return (((double)std::rand() / (double)RAND_MAX) * (to - from) + from) * 1;
}

std::vector<double> getRow(int count){
    std::vector<double> r;
    for(int i = 0; i < count; i++)
        r.push_back(i);
    return r;
}

double correlationFunction(double t) {
    //return D * exp(-a * t);
    return 1 * exp(-a * t);
}

double distributionFunction(double t) {
    return tan(t);
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
    return atan(x);
}


std::vector<double> applay(std::vector<double> vals, double (*fun)(double))
{
    std::vector<double> res;
    forI(i, vals) res.push_back(fun(vals[i]));
    return res;
}

void plotDensity(const std::vector<double>& y, int count = 100) {
    if (y.size() < count) count = y.size();

    double min_y = *std::min_element(y.begin(), y.end());
    double max_y = *std::max_element(y.begin(), y.end());

    std::vector<double> resY;
    std::vector<double> resX;
    resY.push_back(0);
    resX.push_back((*std::min_element(y.begin(), y.end())));
    for (int i = 0; i < count; i++)
    {
        double step = (max_y - min_y) / count;
        double ll = min_y + (double)i * step;
        double hh = ll + step;

        double c = 0;
        forI(k, y) if (y[k] >= ll && y[k] < hh) c++;

        resX.push_back(ll);
        resY.push_back(c);
    }
    resY.push_back(0);
    resX.push_back((*std::max_element(y.begin(), y.end())));

    plt::figure(1);
    plt::title("pl* " + std::to_string(step_num));
    plt::plot(resX, resY);
    plt::grid(true);
}

void plotDistribution(const std::vector<double>& v, bool th = false)
{
    std::vector<double> resX; 
    std::vector<double> resY; 

    // int b = v.size() < 3000 ? v.size() : 30000;

    // std::vector<double> sortedV = {v.begin(), v.begin() + b};
    // std::sort(sortedV.begin(), sortedV.end());

    std::vector<double> sortedV = {v.begin(), v.end()};
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

    std::vector<double> resY_th = applay(resX, distributionFunction);

    plt::figure(2);
    plt::title("Распределение " + std::to_string(step_num));
    plt::plot(resX, resY);
    if (th) plt::plot(resX, resY_th);
    plt::grid(true);
}

void plotSignal(const std::vector<double>& x, const std::vector<double>& y)
{
    plt::figure(3);
    plt::title("Сигнал " + std::to_string(step_num));
    plt::plot(x, y);
    plt::grid(true);
}

void plotCore(std::vector<double> x, std::vector<double> y, double border = 3 / a, bool th = false) {
    // Mx = 1 / n * sum(Xi)
    // Dx = 1 / (n - 1) * sum(Xi - Mx)^2
    // K(t) = 1 / (n + 1 - j) * sum ((Xi - Mx) (Xi+j - Mx))

    double n = x.size();
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

        k.push_back(sum / (x.size() + 1 - j));
    }

    std::vector<double> xx = x;

    int borderIndex = xx.size() - 1;
    forI(i, xx) if (xx[i] > border) { borderIndex = i; break; }
    xx = {xx.begin(), xx.begin() + borderIndex};
    k = {k.begin(), k.begin() + borderIndex};

    std::vector<double> k_th;
    k_th = applay(xx, correlationFunction);

    plt::figure(4);
    plt::title("Кореляционная функция " + std::to_string(step_num));
    plt::plot(xx, k);
    if (th) plt::plot(xx, k_th);
    plt::grid(true);
}

double f(double x, double rnd) {
    double aa = a;
    double DD = 1;
    double hh = h;

    double s0 = hh * DD;
    double kf = sqrt((2 * DD) / (aa * s0));
    double tf = 1 / aa;

    return -1 / tf * x + kf / tf * rnd;
}

double formFilter(double x0, double t0, double step, double endTime,
 std::vector<double>& xRes, std::vector<double>& res, std::vector<double> rnd) 
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

int findX(double val, std::vector<double>& x, std::vector<double>& y)
{
    int index = 0;
    double delta = 10000;
    for(int i = 0; i < x.size(); i++)
    {
        if (std::fabs(x[i] - val) < delta)
        {
            delta = std::fabs(x[i] - val);
            index = i;
        }
    }

    return index;
}



double colmagorivCheck(std::vector<double>& dataX,
    std::vector<double>& dataY,
    std::vector<double>& theoryDataX,
    std::vector<double>& theoryDataY)
{
    double x_1 = std::max(dataX[0], theoryDataX[0]);
    double x_2 = std::min(*(dataX.end() - 1), *(theoryDataX.end() - 1));

    double max = 0;
    for (double x = x_1; x < x_2; x += (x_2 - x_1) / 100)
    {
        int index_x_1 = findX(x, dataX, dataY);
        int index_x_2 = findX(x, theoryDataX, theoryDataY);
        double c = std::fabs(dataY[index_x_1] - theoryDataY[index_x_2]);
        if (c > max)
            max = c;
    }
    return max;
}

double factorial(double N) {
    double F = 1;
    for(double i = 1; i <= N; ++i) {
        F *= i;
    }
    return F;
}

double erf(double x)
{
    double res = 0;
    double step = x / 100;
    for (double _x = 0; _x < fabs(x); _x += fabs(step))
        res += exp(-_x * _x) * step;

    return 2 / sqrt(M_PI) * res;
}

double F(double x)
{
    // double res = 0;
    // double del = 1;
    // for (int i = 0; i < 30; i++)
    // {
    //     res += del * (pow(x, 2*i) / (pow(2, i) * (1 + 2*i) * factorial(i - 1))) * 3;
    //     del *= -1;
    // }

    // return (res * x / sqrt(2 * M_PI) + 1) / 2;
    return (erf(x / sqrt(2)) + 1) * 0.5;
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

void GenerateSignal(int count, int seed, std::vector<double>& res)
{
    srand(seed);

    double endt = h * count;
    int rndCount = count;
    std::vector<double> rnd(rndCount);

    for (int i = 0; i < rndCount; i += 2) 
    {
        L1:
        double e1 = getRandom(0, 1);
        double e2 = getRandom(0, 1);

        double v1 = 2 * e1 - 1;
        double v2 = 2 * e2 - 1;
        double s = v1 * v1 + v2 * v2;
        if (s >= 1) goto L1;

        double r = sqrt(-2 * log(s) / s);
        rnd[i] = v1 * r;
        rnd[i + 1] = v2 * r;
    }

    std::vector<double> step_2_x; 
    std::vector<double> step_2_y;
    formFilter(0, 0, h, endt, step_2_x, step_2_y, rnd);

    std::vector<double> step_3_x = step_2_x; 
    std::vector<double> step_3_y = applay(step_2_y, F);

    std::vector<double> step_4_x = step_3_x; 
    res = applay(step_3_y, reverse);
}

int main() 
{
    std::vector<double> v1;
    std::vector<double> v2;
    std::vector<double> v3;

    for (int i = 0; i < 150; i++)
    {
        std::vector<double> signal;
        GenerateSignal(100, i, signal);

        v1.push_back(signal[90]);
        v2.push_back(signal[95]);
    }

    GenerateSignal(30000, 1, v3);

    std::vector<double> distr_v1_x;
    std::vector<double> distr_v1_y;
    getDistributionFunction(v1, distr_v1_x, distr_v1_y);

    std::vector<double> distr_v2_x;
    std::vector<double> distr_v2_y;
    getDistributionFunction(v2, distr_v2_x, distr_v2_y);

    std::vector<double> distr_v3_x;
    std::vector<double> distr_v3_y;
    getDistributionFunction(v3, distr_v3_x, distr_v3_y);

    double cIndex1 = colmagorivCheck(distr_v1_x, distr_v1_y, distr_v2_x, distr_v2_y);
    std::cout << "Colmagorov Index [1]: " << cIndex1 << std::endl;

    if (cIndex1 < 0.162)
        std::cout << "colmagorivCheck [1]: Passed" << std::endl;
    else
        std::cout << "colmagorivCheck [1]: Failed" << std::endl;


    double cIndex2 = colmagorivCheck(distr_v1_x, distr_v1_y, distr_v3_x, distr_v3_y);
    std::cout << "Colmagorov Index [2]: " << cIndex2 << std::endl;

    if (cIndex2 < 0.162)
        std::cout << "colmagorivCheck [2]: Passed" << std::endl;
    else
        std::cout << "colmagorivCheck [2]: Failed" << std::endl;

    plt::figure(1);
    plt::title("Распределение");
    plt::plot(distr_v1_x, distr_v1_y);
    plt::plot(distr_v2_x, distr_v2_y);
    plt::grid(true);
    plt::show();

    return 0;
}