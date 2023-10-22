#include "solver.h"
#include "ploter.h"


int main() {
    double r_0 = sqrt(pow(x_0 - x_c_0, 2) + pow(y_0 - y_c_0, 2));
    double e_c_0 = atan2(y_c_0 - y_0, x_c_0 - x_0);

    std::vector<double> initialValues = { V_0, TH_0, w_z_0, th_0, y_0, x_0, m_0, V_c_0, TH_c_0, e_c_0, r_0, x_c_0, y_c_0};
    std::vector<std::vector<double>> results;
    std::vector<double> resultsX;

    SolverFunctionPtr solver = getEnviconmentSolver();
    solver(T_0, T_val, h_val, initialValues, results, resultsX, c_ya_al_1, c_xa0_1);

    plotTargetParameters(resultsX, transformResults(results));
    return 0;
}