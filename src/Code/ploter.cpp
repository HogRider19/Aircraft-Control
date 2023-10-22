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


    plt::figure(1);
    plt::plot(x, y[1]);
    plt::title("TH");
    plt::grid(true);

    plt::figure(2);
    plt::plot(x, y[9]);
    plt::title("e_c");
    plt::grid(true);

    #ifndef SIM_DEBUG
        std::vector<double> f_c;
        for (int i = 0; i < y[1].size(); i++)
            f_c.push_back(y[9][i] - y[1][i]);

        plt::figure(3);
        plt::plot(x, f_c);
        plt::title("f_c");
        plt::grid(true);

        std::vector<double> e_c_f_c;
        for (int i = 0; i < y[1].size(); i++)
            e_c_f_c.push_back(y[9][i] - f_c[i]);

        plt::figure(4);
        plt::plot(x, e_c_f_c);
        plt::title("e_c - f_c");
        plt::grid(true);

        plt::figure(5);
        plt::plot(x, y[5], {{"label", "Aircraft"}});
        plt::plot(x, y[11], {{"label", "Target"}});
        plt::title("x");
        plt::grid(true);
        plt::legend();

        plt::figure(6);
        plt::plot(x, y[4], {{"label", "Aircraft"}});
        plt::plot(x, y[12], {{"label", "Target"}});
        plt::title("y");
        plt::grid(true);
        plt::legend();
    #endif

    plt::figure(7);
    plt::plot(y[5], y[4], {{"label", "Aircraft"}});
    plt::plot(y[11], y[12], {{"label", "Target"}});
    plt::title("y(x)");
    plt::grid(true);
    plt::legend();

    #ifdef SIM_DEBUG
        std::vector<double> r_real;
        for (int i = 0; i < y[5].size(); i++)
            r_real.push_back(
                sqrt(
                    pow(y[5][i] - y[11][i], 2) + pow(y[4][i] - y[12][i], 2)
                )
            );

        plt::figure(8);
        plt::plot(x, r_real);
        plt::title("r_real");
        plt::grid(true);
    #endif
    

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