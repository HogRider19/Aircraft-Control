#include <iostream>
#include <vector>
#include <cmath>

double colmagorivCheck(std::vector<double>& dataX,
    std::vector<double>& dataY,
    std::vector<double>& theoryDataX,
    std::vector<double>& theoryDataY)
{
    double max = 0;
    for (size_t i = 0; i < dataX.size(); i++)
    {
        double c = std::fabs(dataY[i] - theoryDataY[i]);
        if (c > max)
            max = c;
    }
    return max;
}

double getRandom() {
    return (((double)std::rand() / (double)RAND_MAX) - 0.5) * 1;
}

int main() 
{
    std::vector<double> v1;
    std::vector<double> v2;

    for (int i = 0; i < 1000; i++)
    {
        double rnd = getRandom();
        if (i = 5)
        {
            v1.push_back(rnd);
        }
    }

    return 0;
}