#include <iostream>
#include "solver.h"


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
    for (int i = 0; i < seconds * 2; i++)
    {
        std::vector<double> initialValues = { V_0, TH_0, w_z_0, th_0, y_0, x_0, m_0 };
        std::vector<double> results;

        SolverFunctionPtr solver = getEnviconmentSolver();
        solver(0, double(i) / 2, 0.01, initialValues, results);

        std::cout << results[0] << ",";
    }


    return 0;
}