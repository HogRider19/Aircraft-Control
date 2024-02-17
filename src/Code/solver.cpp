#include "equations.h"
#include "solver.h"
#include <iostream>

void systemOfEquations(
    double t,
    const std::vector<double>& y,
    std::vector<double>& results)
{
    std::map<std::string, double> values = std::map<std::string, double>();
    
    values["x1"] = y[0];
    values["x2"] = y[1];
    values["x3"] = y[2];
    values["x4"] = y[3];
    values["x5"] = y[4];

    results[0] = dx1(values);
    results[1] = dx2(values);
    results[2] = dx3(values);
    results[3] = dx4(values);
    results[4] = dx5(values);

    // std::cout << "dVdt: " << y[0] << std::endl;
    // std::cout << "dTHdt: " << y[1] << std::endl;
    // std::cout << "dw_zdt: " << y[2] << std::endl;
    // std::cout << "dthdt: " << y[3] << std::endl;
    // std::cout << "dydt: " << y[4] << std::endl;
    // std::cout << std::endl << std::endl;
}

void rungeKuttaSystem(
    double t0,
    double t1,
    double step,
    const std::vector<double>& y0,
    std::vector<std::vector<double>>& y1,
    std::vector<double>& x)
{
    // t0 - начальное время
    // t1 - конечное время
    // h - шаг интегрирования
    // y0 - вектор начальных значений неизвестных функций y
    // y1 - вектор, в который будут записаны результаты после интегрирования

    int n = y0.size(); // количество неизвестных функций
    x.clear();

    // Создаем вспомогательные векторы
    std::vector<double> k1(n), k2(n), k3(n), k4(n);

    // Инициализируем вектор y1 начальными значениями
    y1.push_back(y0);
    x.push_back(t0);    

    // Итерационный процесс метода Рунге-Кутты
    for (double t = t0; t < t1; t += step)
    {
        systemOfEquations(t, y1.back(), k1);

        // Вычисляем значения k2
        std::vector<double> y2(n);
        for (int i = 0; i < n; i++)
        {
            y2[i] = y1.back()[i] + 0.5 * step * k1[i];
        }
        systemOfEquations(t + 0.5 * step, y2, k2);

        // Вычисляем значения k3
        std::vector<double> y3(n);
        for (int i = 0; i < n; i++)
        {
            y3[i] = y1.back()[i] + 0.5 * step * k2[i];
        }
        systemOfEquations(t + 0.5 * step, y3, k3);

        // Вычисляем значения k4
        std::vector<double> y4(n);
        for (int i = 0; i < n; i++)
        {
            y4[i] = y1.back()[i] + step * k3[i];
        }
        systemOfEquations(t + step, y4, k4);

        // Обновляем значения y1
        std::vector<double> temp(n);
        for (int i = 0; i < n; i++)
        {
            temp.push_back((step / 6) * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]));
        }
        y1.push_back(temp);
        x.push_back(t);
    }
}

void eulerSystem(
    double t0,
    double t1,
    double step,
    const std::vector<double>& y0,
    std::vector<std::vector<double>>& y1,
    std::vector<double>& x)
{
    int n = y0.size();
    x.clear(); 

    y1.push_back(y0);
    x.push_back(t0);

    double pointIntegrateIntervalCount = (t1 - t0) / step;
    double pointInterval = (t1 - t0) / MAX_PLOT_POINTS_COUNT;
    double prevSavedT = t0;

    std::vector<double> yGlobTemp = y1.back();
    for (double t = t0; t < t1; t += step)
    {

        std::vector<double> yTemp(n);

        std::vector<double> paramsTemp(n);
        systemOfEquations(t, yGlobTemp, paramsTemp);

        for (int i = 0; i < n; i++)
            yTemp[i] = yGlobTemp[i] + step * paramsTemp[i];

        yGlobTemp = yTemp;
        if (pointIntegrateIntervalCount < MAX_PLOT_POINTS_COUNT || t - prevSavedT > pointInterval)
        {
            prevSavedT = t;
            x.push_back(t);
            y1.push_back(yTemp);
        }
    }
}

SolverFunctionPtr getEnviconmentSolver()
{
    #ifdef EULER
        return eulerSystem;
    #else
        return rungeKuttaSystem;
    #endif
}