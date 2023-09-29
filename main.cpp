#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include "solver.h"
#include "src/Include/matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main() {
    int seconds = 33;

    std::vector<double> initialValues = { V_0, TH_0, w_z_0, th_0, y_0, x_0, m_0 };
    std::vector<std::vector<double>> results;
    std::vector<double> resultsX;

    SolverFunctionPtr solver = getEnviconmentSolver();
    solver(0, T_val, 0.00001, initialValues, results, resultsX);

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

    std::vector<std::string> titles = {"V", "TH", "w_z", "th", "y", "x", "m"};
    for (int i = 0; i < 7; i++)
    {
        plt::subplot(3, 3, i + 1); 
        plt::plot(resultsX, resultsTransform[i]);
        plt::title(titles[i]);
        plt::grid(true);
    }

    plt::show();

    return 0;
}