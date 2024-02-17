#include "solver.h"
#include "ploter.h"

double getError(std::vector<double> y_perf, std::vector<double> y) {
    std::vector<double> B;
    for (size_t k = 0; k < y.size(); k++) {
        B.push_back(fabs((y_perf[k] - y[k]) / y[k]) * 100);
    }

    int shift = (int)(y.size() * 0.1);

    double max = 0.0;
    for (size_t i = shift; i < y.size(); i++) {
        if (B[i] > max)
            max = B[i];
    }

    return max;
}


int main() {
    std::vector<double> initialValues = { x1_0, x2_0, x3_0, x4_0, x5_0 };

    SolverFunctionPtr solver = getEnviconmentSolver();

    std::vector<double> resultsX;
    std::vector<std::vector<double>> resultsPerfect;
    solver(T_0, T_1, h_per_val, initialValues, resultsPerfect, resultsX);

    double hResult = h_per_val;
    double prevError = 0;
    for (double h = h_per_val * 2; h < h_max_val; h = h * 2) {
        std::vector<std::vector<double>> results;
        solver(T_0, T_1, h, initialValues, results, resultsX);

        double error = getError(transformResults(resultsPerfect)[4], transformResults(results)[4]);

        if (error > 1.0) {
            std::cout << "Max Error: " << prevError << std::endl;
            std::cout << "Selected step: " << hResult << std::endl;
            break;
        }

        prevError = error;
        hResult = h;
    }


    std::vector<double> resultsXNew;
    std::vector<std::vector<double>> results;

    solver(T_0, T_1, hResult, initialValues, results, resultsXNew);
    plotParameters(resultsXNew, transformResults(results));

    return 0;
}