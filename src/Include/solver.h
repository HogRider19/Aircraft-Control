#pragma once

#define EULER

#include <vector>
#include "equations.h"
#include "consts.h"

typedef void (*SolverFunctionPtr)(double, double, double, const std::vector<double>&, std::vector<std::vector<double>>&, std::vector<double>&, double, double);

void systemOfEquations(double t, const std::vector<double>& y, std::vector<double>& results, double, double);
SolverFunctionPtr getEnviconmentSolver();

void rungeKuttaSystem(double t0, double t1, double step, const std::vector<double>& y0, std::vector<double>& y1, std::vector<double>& x, double, double);
void eulerSystem(double t0, double t1, double step, const std::vector<double>& y0, std::vector<std::vector<double>>& y1, std::vector<double>& x, double, double);