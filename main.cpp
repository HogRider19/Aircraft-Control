#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include "solver.h"
#include "src/Include/matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main() {
    int seconds = 33;

    std::array<std::vector<double>, 8> simulationsResults;

    for (int i = 0; i < seconds * 2; i++)
    {
        std::vector<double> initialValues = { V_0, TH_0, w_z_0, th_0, y_0, x_0, m_0 };
        std::vector<double> results;

        SolverFunctionPtr solver = getEnviconmentSolver();
        solver(0, double(i) / 2, 0.01, initialValues, results);

        for (int k = 0; k < 7; k++)
            (simulationsResults[k]).push_back(results[k]);
        simulationsResults[7].push_back(results[3] - results[1]);
    }

    std::vector<std::string> titles = {"V", "TH", "w_z", "th", "y", "x", "m", "a"};
    for (int i = 0; i < 8; i++)
    {
        plt::subplot(3, 3, i + 1);
        plt::plot(simulationsResults[i]);
        plt::title(titles[i]);
    }
    plt::show();

    return 0;
}