#include "ploter.h"
#include <iostream>

namespace plt = matplotlibcpp;

void plotParameters(
    std::vector<double> x,
    std::vector<std::vector<double>> y1,
    std::vector<std::vector<double>> y2,
    std::vector<std::vector<double>> y3)
{
    std::vector<std::string> titles = {"V", "TH", "w_z", "th", "y", "x", "m"};
    for (int i = 0; i < 4; i++)
    {
        plt::figure(i + 1);
        plt::plot(x, y1[i], {{"label", "c_ya_al_1"}});
        plt::plot(x, y2[i], {{"label", "c_ya_al_1+20%"}});
        plt::plot(x, y3[i], {{"label", "c_ya_al_1-20%"}});
        plt::title(titles[i]);
        plt::grid(true);
        plt::legend();
    }

    plt::figure(5);
    plt::plot(y1[5], y1[4], {{"label", "c_ya_al_1"}});
    plt::plot(y2[5], y2[4], {{"label", "c_ya_al_1+20%"}});
    plt::plot(y3[5], y3[4], {{"label", "c_ya_al_1-20%"}});
    plt::title("y(x)");
    plt::grid(true);
    plt::legend();

    plt::show();
}

void plotTargetParameters(std::vector<double> x, std::vector<std::vector<double>> y)
{
    std::vector<std::string> titles = {
        "V", "TH", "w_z",
        "th", "y", "x", "m",

        "V_c", "TH_c", "e_c",
        "r", "x_c", "y_c"
    };

    // for (int i = 0; i < 4; i++)
    // {
    //     plt::figure(i + 1);
    //     plt::plot(x, y[i]);
    //     plt::title(titles[i]);
    //     plt::grid(true);
    // }

    for (int i = 9; i < 11; i++)
    {
         plt::figure(i + 1);
         plt::plot(x, y[i]);
         plt::title(titles[i]);
         plt::grid(true);
    }

    plt::figure(5);
    plt::plot(y[5], y[4], {{"label", "Aircraft"}});
    plt::plot(y[11], y[12], {{"label", "Target"}});

    plt::title("y(x)");
    plt::grid(true);
    plt::legend();

    //
    std::vector<double> r_real;
    for (int i = 0; i < y[5].size(); i++)
        r_real.push_back(
            sqrt(
                pow(y[5][i] - y[11][i], 2) + pow(y[4][i] - y[12][i], 2)
            )
        );

    plt::figure(6);
    plt::plot(x, r_real, {{"label", "Aircraft"}});

    plt::title("r_real");
    plt::grid(true);
    //

    plt::show();
}

std::vector<std::vector<double>> transformResults(std::vector<std::vector<double>> results)
{
    std::vector<std::vector<double>> resultsTransform;
    for (int k = 0; k < 13; k++)
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