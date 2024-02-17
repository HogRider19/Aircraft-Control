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

void plotB_X5(
    std::vector<double> x,
    std::vector<std::vector<double>> y_perf,
    std::vector<std::vector<double>> y)
{
    // std::cout << "X: " << x.size() << std::endl;
    // std::cout << "Y: " << y[4].size() << std::endl;
    // std::cout << "Y_perf: " << y_perf[4].size() << std::endl;
    // std::cout << " "  << std::endl;

    std::vector<double> B;
    for (size_t k = 0; k < x.size(); k++) {
        B.push_back(fabs((y_perf[4][k] - y[4][k]) / y[4][k]) * 100);
    }

    plt::figure(1);
    plt::plot(x, B);
    plt::title("X5 B");
    plt::grid(true);

    plt::show();    

}

void plotBParameters(
    std::vector<double> x,
    std::vector<std::vector<double>> y_perf,
    std::vector<std::vector<double>> y)
{
        std::vector<std::string> titles = {"x1", "x2", "x3", "x4", "x5"};
    for (int i = 0; i < 5; i++)
    {
        plt::figure(i + 1);
        plt::plot(x, y_perf[i], {{"label", "perf"}});
        plt::plot(x, y[i], {{"label", "siple"}});
        plt::title(titles[i]);
        plt::grid(true);
        plt::legend();
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