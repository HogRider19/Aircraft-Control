#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include "solver.h"
#include "src/Include/matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main() {
    int seconds = 33;

    std::vector<double> V_res;
    std::vector<double> TH_res;
    std::vector<double> w_z_res;
    std::vector<double> th_res;
    std::vector<double> y_res;
    std::vector<double> x_res;
    std::vector<double> m_res;

    for (int i = 0; i < seconds * 2; i++)
    {
        std::vector<double> initialValues = { V_0, TH_0, w_z_0, th_0, y_0, x_0, m_0 };
        std::vector<double> results;

        SolverFunctionPtr solver = getEnviconmentSolver();
        solver(0, double(i) / 2, 0.01, initialValues, results);

        V_res.push_back(results[0]);
        TH_res.push_back(results[1]);
        w_z_res.push_back(results[2]);
        th_res.push_back(results[3]);
        y_res.push_back(results[4]);
        x_res.push_back(results[5]);
        m_res.push_back(results[6]);
    }

    std::vector<std::string> titles = {"V", "TH", "w_z", "th", "y", "x", "m"};
    for (int i = 0; i < 7; i++)
    {
        plt::subplot(3, 3, i + 1);
        plt::plot(V_res);
        plt::title(titles[i]);
    }
    plt::show();

    return 0;
}