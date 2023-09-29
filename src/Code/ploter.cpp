#include "ploter.h"
#include <iostream>

namespace plt = matplotlibcpp;

void plotParameters(
    std::vector<double> x,
    std::vector<std::vector<double>> y1,
    std::vector<std::vector<double>> y2,
    std::vector<std::vector<double>> y3)
{
    // "V", "TH", "w_z", "th", "y", "x", "m", "y(x)"

    std::cout << x.size() << std::endl;

    std::vector<std::string> titles = {"V", "TH", "w_z", "th", "y", "x", "m", "y(x)"};
    for (int i = 0; i < 7; i++)
    {
        plt::subplot(3, 3, i + 1); 
        plt::plot(x, y1[i]);
        plt::title(titles[i]);
        plt::grid(true);
    }

    plt::subplot(3, 3, 8); 
    plt::plot(y1[5], y1[4]);
    plt::title("y(x)");
    plt::grid(true);

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