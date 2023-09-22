#include <vector>


typedef double (*SoleveResultFunctionPtr)(double, double);
typedef std::vector<SoleveResultFunctionPtr> (*SolverFunctionPtr)(SoleveResultFunctionPtr, double, double, std::vector<double>);

std::vector<SoleveResultFunctionPtr> eulerSystem(
    SoleveResultFunctionPtr funcs,
    double t0,
    double t1,
    std::vector<double> initialValues)
{
    return std::vector<SoleveResultFunctionPtr>();
}

std::vector<SoleveResultFunctionPtr> rungeKuttaSystem(
    SoleveResultFunctionPtr funcs,
    double t0,
    double t1,
    std::vector<double> initialValues)
{
    return std::vector<SoleveResultFunctionPtr>();
}

SolverFunctionPtr getSolver(bool isEuler)
{
    if (isEuler)
    {
        return eulerSystem;
    }
    return rungeKuttaSystem;
}