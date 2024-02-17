#define _USE_MATH_DEFINES
#define WITHOUT_NUMPY

#include <iostream>
#include "matplotlibcpp.h"
#include "consts.h"


void plotParameters(std::vector<double>, std::vector<std::vector<double>>);
void plotTargetParameters(std::vector<double>, std::vector<std::vector<double>>);


void plotB_X5(std::vector<double> x, std::vector<std::vector<double>> y_perf, std::vector<std::vector<double>> y);
void plotBParameters(std::vector<double> x,std::vector<std::vector<double>> y_perf, std::vector<std::vector<double>> y);


std::vector<std::vector<double>> transformResults(std::vector<std::vector<double>>);