#define _USE_MATH_DEFINES
#define WITHOUT_NUMPY

#include "matplotlibcpp.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

namespace plt = matplotlibcpp;


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

    return 4 - 4*sqrt(1 - x);
}

void getTheoryDistributionFunction(std::vector<double>& x,
     std::vector<double>& y,
     std::vector<double>& realX)
{
    for (int i = 0; i < realX.size(); i++)
    {
        x.push_back(realX[i]);
        y.push_back(-(realX[i] - 8.0) * realX[i] * 16.0 / 256.0);
    }
}

double colmagorivCheck(std::vector<double>& dataX,
    std::vector<double>& dataY,
    std::vector<double>& theoryDataX,
    std::vector<double>& theoryDataY)
{
    double max = 0;
    for (size_t i = 0; i < dataX.size(); i++)
    {
        double c = std::fabs(dataY[i] - theoryDataY[i]);
        if (c > max)
            max = c;
    }
    return max;
}

void GetDensity(std::vector<double>& resultX,
    std::vector<int>& resultY,
    std::vector<double>& values,
    int n)
{
    double min = *std::min_element(begin(values), end(values));
    double max = *std::max_element(begin(values), end(values));
    double delta = (max - min) / n;

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

double getExpectedValue(std::vector<double> values, int n)
{
    std::vector<int> counts;
    std::vector<double> vals;

    GetDensity(vals, counts, values, n);

    double res = 0;
    for (size_t index = 0; index < vals.size(); index++)
        res += vals[index] * (((double)counts[index]) / (double)values.size());

    return res;
}


void plotVector(std::vector<double> valuesX, std::vector<double> valuesY, std::string title)
{
    plt::figure(1);
    plt::plot(valuesX, valuesY);
    plt::title(title);
    plt::grid(true);
    plt::show();
}

void plotDensity(std::vector<double>& values, std::string title, int n = 100)
{
    std::vector<int> counts;
    std::vector<double> vals;

    GetDensity(vals, counts, values, n);

    std::vector<double> doublecounts(counts.begin(), counts.end());
    plotVector(vals, doublecounts, title);
}

void getDistributionFunction(std::vector<double>& x, std::vector<double>& y, std::vector<double>& values)
{
    for (size_t i = 0; i < values.size(); i++)
    {
        x.push_back(values[i]);
        y.push_back((double)i / (double)values.size());
    }
}

void plotDistributionFunction(std::vector<double>& values, std::string title)
{
    std::vector<double> x;
    std::vector<double> y;
    getDistributionFunction(x, y, values);
    plotVector(x, y, title);
}


int main() 
{
    std::vector<double> randomValues;
    std::vector<double> newRandomValues;

    for (int i = 0; i < 10000; i++)
    {
        double val = ((double)std::rand()) / RAND_MAX;
        randomValues.push_back(val);
        newRandomValues.push_back(reverse(val));
    }

    std::sort(randomValues.begin(), randomValues.end());
    std::sort(newRandomValues.begin(), newRandomValues.end());

    std::cout << "ExpectedValue: 1.33" << std::endl;
    std::cout << "RealExpectedValue: " << getExpectedValue(newRandomValues, 1000) << std::endl;

    std::vector<double> realX;
    std::vector<double> realY;
    getDistributionFunction(realX, realY, newRandomValues);


    std::vector<double> theoryX;
    std::vector<double> theoryY;
    getTheoryDistributionFunction(theoryX, theoryY, realX);


    double c = colmagorivCheck(realX, realY, theoryX, theoryY);
    std::cout << "colmagorivCheck Index: " << c <<  std::endl;

    if (c < 0.112)
        std::cout << "colmagorivCheck: Passed" << std::endl;
    else
        std::cout << "colmagorivCheck: Failed" << std::endl;


    plotDistributionFunction(newRandomValues, "DistributionFunction");
    plotDensity(newRandomValues, "Density");
}