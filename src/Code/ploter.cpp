#include "ploter.h"
#include <iostream>

namespace plt = matplotlibcpp;

void plotParameters(
    std::vector<double> x,
    std::vector<std::vector<double>> y)
{
    std::vector<std::string> titles = {"x1", "x2", "x3", "x4", "x5"};
    for (int i = 0; i < 5; i++)
    {
        plt::figure(i + 1);
        plt::plot(x, y[i]);
        plt::title(titles[i]);
        plt::grid(true);
    }

    plt::show();
}

std::vector<std::vector<double>> transformResults(std::vector<std::vector<double>> results)
{
    std::vector<std::vector<double>> resultsTransform;
    for (int k = 0; k < 7; k++)
    {
        std::vector<double> temp;
        for (int i = 0; i < results.size(); i++)
        {
            temp.push_back(results[i][k]);
        }
        resultsTransform.push_back(temp);
    }
    return resultsTransform;
}