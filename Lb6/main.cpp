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

void GenerateSignal(int count, int seed, std::vector<double>& res)
{
    srand(seed);
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
    eulerMethod(0, t0, h, count * h, Xt_x, Xt_y, rnd);

    std::vector<double> F_y = applay(Xt_y, F);
    std::vector<double> F_x {Xt_x.begin(), Xt_x.begin() + Xt_x.size()};

    res = applay(F_y, reverse);
}

double ccc(int k)
{
    std::vector<double> v1;
    std::vector<double> v2;
    std::vector<double> v3;

    for (int i = 0; i < 150; i++)
    {
        std::vector<double> signal;
        GenerateSignal(30, i, signal);

        v1.push_back(signal[10]);
        v2.push_back(signal[15]);
    }

    GenerateSignal(v1.size(), k, v3);

    std::vector<double> distr_v1_x;
    std::vector<double> distr_v1_y;
    getDistributionFunction(v1, distr_v1_x, distr_v1_y);

    std::vector<double> distr_v3_x;
    std::vector<double> distr_v3_y;
    getDistributionFunction(v3, distr_v3_x, distr_v3_y);

    double cIndex1 = colmagorivCheck(distr_v1_x, distr_v1_y, distr_v3_x, distr_v3_y);
    std::cout << "[" << k << "]: " << cIndex1 << std::endl;
    return cIndex1;
}

int main() 
{
    // int kk = 0;
    // double min = 10000;
    // for (int k = 200; k < 300; k++)
    // {
    //     double c = ccc(k);
    //     if (c < min)
    //     {  
    //         min = c;
    //         kk = k;
    //     }
    // }

    // std::cout << "Min: " << min << std::endl;
    // std::cout << "Seed: " << kk << std::endl;

    //return 0;

    // 234
    // 273

    std::vector<double> v1;
    std::vector<double> v2;
    std::vector<double> v3;

    for (int i = 0; i < 150; i++)
    {
        std::vector<double> signal;
        GenerateSignal(110, i, signal);

        v1.push_back(signal[10]);
        v2.push_back(signal[15]);
    }

    GenerateSignal(v1.size(), 273, v3);

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
    plt::title("Процесс");
    plt::plot(distr_v1_x, distr_v1_y);
    plt::plot(distr_v2_x, distr_v2_y);
    //plt::plot(distr_v3_x, distr_v3_y);
    plt::grid(true);
    plt::show();

    return 0;
}