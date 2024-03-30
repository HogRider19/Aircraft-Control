#include <stdio.h>
#include <iostream>
#include <cmath>
#include <random>

double _f(double t)
{
    return ((double)std::rand() / (double)RAND_MAX - 0.5) * 0.005;
}

#define getRandom _f