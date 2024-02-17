#include "solver.h"
#include "ploter.h"


int main() {
    std::vector<double> initialValues = { x1_0, x2_0, x3_0, x4_0, x5_0 };
    std::vector<std::vector<double>> results;
    std::vector<double> resultsX;

    std::cout << "000000000" << std::endl;

    SolverFunctionPtr solver = getEnviconmentSolver();
    solver(T_0, T_1, h_val, initialValues, results, resultsX);

    std::cout << "11111111111111" << std::endl;

    plotParameters(resultsX, transformResults(results));

    std::cout << "2222222222" << std::endl;
    return 0;
}