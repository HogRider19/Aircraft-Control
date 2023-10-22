#include "solver.h"
#include "ploter.h"


int main() {
    std::vector<double> initialValues = { V_0, TH_0, w_z_0, th_0, y_0, x_0, m_0 };
    std::vector<std::vector<double>> results1, results2, results3;
    std::vector<double> resultsX;

    SolverFunctionPtr solver = getEnviconmentSolver();
    solver(T_0, T_val, h_val, initialValues, results1, resultsX, c_ya_al_1, c_xa0_1);
    solver(T_0, T_val, h_val, initialValues, results2, resultsX, c_ya_al_2, c_xa0_2);
    solver(T_0, T_val, h_val, initialValues, results3, resultsX, c_ya_al_3, c_xa0_3);

    plotParameters(resultsX, transformResults(results1),
            transformResults(results2), transformResults(results3));
    return 0;
}