#define forI(i, p) for(size_t i = 0; i < p.size(); i++)
#define pr(m) std::cout << m <<std::endl
#define _USE_MATH_DEFINES
#define WITHOUT_NUMPY

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <random>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

#define y 15.0
#define h 20.0
#define T 100.0
#define a_d 3.0
#define e_treb 0.01
// p

double getRandom(double from = 0, double to = 1) {
    return (((double)std::rand() / (double)RAND_MAX) * (to - from) + from) * 1;
}

void process(int& N, int& M, double time)
{
    double t = 0;
    while (t < time)
    {
        double dt_st = -1 / y * log(1 - getRandom());
        double dt_en = -1 / h * log(1 - getRandom());

        t += dt_st;
        N += 1;

        if (dt_st >= dt_en)
            M++;
    }
}

int main() 
{
    #pragma region 123
    double N_end = 23493;
    srand(2);
    #pragma endregion

    double t = -1 / y * log(1 - getRandom());
    int N = 1; int M = 1;
    process(N, M, T);

    double p_pr = (double)M / (double)N;
    double e_pr = a_d * sqrt((p_pr * (1 - p_pr)) / N);

    pr("First Step");
    pr("N = " << N);
    pr("M = " << M);
    pr("P = " << p_pr);
    pr("Accuracy = " << e_pr);
    pr("");

    if (e_pr > e_treb)
    {
        double N_treb = (a_d * a_d * p_pr * (1 - p_pr)) / (e_treb * e_treb);
        double add_T = N_treb / y - T + 200;

        process(N, M, add_T);
        p_pr = (double)M / (double)N;
        e_pr = a_d * sqrt((p_pr * (1 - p_pr)) / N);

        pr("Additional step");
        pr("Additional N = " << N_treb);
        pr("Additional T = " << add_T);
        pr("");
    }

    pr("Final Step");
    pr("N = " << N_end);
    pr("M = " << M);
    pr("P = " << p_pr);
    pr("Accuracy = " << e_pr);

    pr("Theory P: " << h / (y + h));
    // plt::figure(1);
    // plt::title("Распределение");
    // plt::plot(res);
    // plt::grid(true);
    // plt::show();

    return 0;
}