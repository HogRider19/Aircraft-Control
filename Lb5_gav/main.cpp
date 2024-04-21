#define forI(i, p) for(size_t i = 0; i < p.size(); i++)
#define pr(m) std::cout << m <<std::endl
#define _USE_MATH_DEFINES
#define WITHOUT_NUMPY

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <random>
#include "matplotlibcpp.h"

#define D 1.0
#define a 0.1
#define h 0.05

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
    return t / 2 - t * t / 16;
}

double reverse(double x)
{
    /*
        f(z) = 1 / 2 - z / 8 [0, 4]
        F(z) = -(z - 8)*z / 16 = R

        x1 = 4 + 4*sqrt(1 - R) Хуйня!
        x2 = 4 - 4*sqrt(1 - R)

        left: 0
        right: 4

        x_i = 4 - 4*sqrt(1 - e_i)
    */
    if (x >= 1) return 4;
    return 4 - 4*sqrt(1 - x);
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

double colmagorivCheck(std::vector<double>& sig)
{
    std::vector<double> resX; 
    std::vector<double> resY; 

    std::vector<double> sortedV = {sig.begin(), sig.end()};
    std::sort(sortedV.begin(), sortedV.end());

    for(int i = 0; i < sortedV.size(); i++)
    {
        double val = sortedV[i];
        int count = 0;
        for(int j = 0; j < sortedV.size(); j++)
        {
            if(sortedV[j] <= val)
            {
                count++;
            }
        }
        resX.push_back(val);
        resY.push_back(count / static_cast<double>(sortedV.size()));
    }

    std::vector<double> th;
    for (int i = 0; i < resX.size(); i++)
        th.push_back(distributionFunction(resX[i]));

    double max = 0;
    for (size_t i = 0; i < resY.size(); i++)
    {
        double c = std::fabs(resY[i] - th[i]);

        if (c > max)
            max = c;
    }
    return max;
}

int main() 
{
    // 6 (9)
    srand(0);

    double endt = 3 / a + 2000;

    int rndCount = endt / h + 300;
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

    pr(rnd.size());

    step_num = 1;
    plotSignal(getRow(rnd.size()), rnd);
    plotDensity(rnd);
    plotDistribution(rnd);
    plt::show();

    std::vector<double> step_2_x; 
    std::vector<double> step_2_y;
    formFilter(0, 0, h, endt, step_2_x, step_2_y, rnd);

    step_num = 2;
    plotSignal(step_2_x, step_2_y);
    plotDensity(step_2_y);
    plotDistribution(step_2_y);
    plotCore(step_2_x, step_2_y, 3 / a, true);
    plt::show();

    std::vector<double> step_3_x = step_2_x; 
    std::vector<double> step_3_y = applay(step_2_y, F);

    step_num = 3;
    plotSignal(step_3_x, step_3_y);
    plotDensity(step_3_y);
    plotDistribution(step_3_y);
    plotCore(step_3_x, step_3_y);
    plt::show();

    std::vector<double> step_4_x = step_3_x; 
    std::vector<double> step_4_y = applay(step_3_y, reverse);

    double c = colmagorivCheck(step_4_y);
    std::cout << "Index: " << c <<  std::endl;
    if (c < 0.162) pr("Passed"); else pr("Failed");

    step_num = 4;
    plotSignal(step_4_x, step_4_y);
    plotDensity(step_4_y);
    plotDistribution(step_4_y, true);
    plotCore(step_4_x, step_4_y);
    plt::show();

    return 0;
}