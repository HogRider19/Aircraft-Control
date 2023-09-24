#define _USE_MATH_DEFINES

#include <iostream>
#include "src/Include/solver.h"
#include "src/Include/matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main() {
    // std::vector<double> initialValues = { V_0, TH_0, w_z_0, th_0, y_0, x_0, m_0 };
    // std::vector<double> results;

    // SolverFunctionPtr solver = getEnviconmentSolver();
    // solver(T_0, T, h, initialValues, results);

    // std::cout << "Results for t="<< T << std::endl;
    // std::cout << "V: " << results[0] << std::endl;
    // std::cout << "TH: " << results[1] << std::endl;
    // std::cout << "w_z: " << results[2] << std::endl;
    // std::cout << "th: " << results[3] << std::endl;
    // std::cout << "y: " << results[4] << std::endl;
    // std::cout << "x: " << results[5] << std::endl;
    // std::cout << "m: " << results[6] << std::endl;

    int seconds = 33;

    std::vector<float> V_res;
    std::vector<float> TH_res;
    std::vector<float> w_z_res;
    std::vector<float> th_res;
    std::vector<float> y_res;
    std::vector<float> x_res;
    std::vector<float> m_res;

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

    // std::vector<std::string> titles = {"V", "TH", "w_z", "th", "y", "x", "m"};
    // for (int i = 0; i < 7; i++)
    // {
    //     plt::subplot(3, 3, i + 1);
    //     plt::plot(V_res);
    //     plt::title(titles[i]);
    // }

    plt::subplot(3, 3, 1);
    plt::plot(V_res);
    plt::title("V");

    plt::show();

    return 0;
}