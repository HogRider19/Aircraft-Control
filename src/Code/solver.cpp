#include "equations.h"
#include "solver.h"

#include <iostream>


int stepCount = 0;

void systemOfEquations(double t, const std::vector<double>& y, std::vector<double>& results)
{
    std::map<std::string, double> values = std::map<std::string, double>();
    
    values["V"] = y[0];
    values["TH"] = y[1];
    values["w_z"] = y[2];
    values["th"] = y[3];
    values["y"] = y[4];
    values["x"] = y[5];
    values["m"] = y[6];

    // std::cout << "Step: " << ++stepCount << std::endl;
    // std::cout << "dVdt: " << y[0] << std::endl;
    // std::cout << "dVdt: " << y[0] << std::endl;
    // std::cout << "dTHdt: " << y[1] << std::endl;
    // std::cout << "dw_zdt: " << y[2] << std::endl;
    // std::cout << "dthdt: " << y[3] << std::endl;
    // std::cout << "dydt: " << y[4] << std::endl;
    // std::cout << "dxdt: " << y[5] << std::endl;
    // std::cout << "dmdt: " << y[6] << std::endl;
    // std::cout << std::endl << std::endl;

    results[0] = dVdt(values);
    results[1] = dTHdt(values);
    results[2] = dw_zdt(values);
    results[3] = dthdt(values);
    results[4] = dydt(values);
    results[5] = dxdt(values);
    results[6] = dmdt(values);

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

    // Создаем вспомогательные векторы
    std::vector<double> k1(n), k2(n), k3(n), k4(n);

    // Инициализируем вектор y1 начальными значениями
    y1.push_back(y0);
    x.push_back(t0);    

    // Итерационный процесс метода Рунге-Кутты
    for (double t = t0; t < t1; t += step)
    {
        x.push_back(t);
        systemOfEquations(t, y1.back(), k1);

        // Вычисляем значения k2
        std::vector<double> y2(n);
        for (int i = 0; i < n; ++i)
        {
            y2[i] = y1.back()[i] + 0.5 * step * k1[i];
        }
        systemOfEquations(t + 0.5 * step, y2, k2);

        // Вычисляем значения k3
        std::vector<double> y3(n);
        for (int i = 0; i < n; ++i)
        {
            y3[i] = y1.back()[i] + 0.5 * step * k2[i];
        }
        systemOfEquations(t + 0.5 * step, y3, k3);

        // Вычисляем значения k4
        std::vector<double> y4(n);
        for (int i = 0; i < n; ++i)
        {
            y4[i] = y1.back()[i] + step * k3[i];
        }
        systemOfEquations(t + step, y4, k4);

        // Обновляем значения y1
        std::vector<double> temp(n);
        for (int i = 0; i < n; ++i)
        {
            temp.push_back((step / 6) * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]));
        }
        y1.push_back(temp);
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
    int n = y0.size(); // количество неизвестных функций

    // Инициализируем вектор y1 начальными значениями
    y1.push_back(y0);
    x.push_back(t0);

    double perPersent = 0;

    // Итерационный процесс метода Эйлера
    for (double t = t0; t < t1; t += step)
    {
        // Создаем вектор для хранения временных значений y
        x.push_back(t);
        std::vector<double> yTemp(n);

        std::vector<double> paramsTemp(n);
        systemOfEquations(t, y1.back(), paramsTemp);

        if (t * 100 / t1 - perPersent > 1)
        {
            std::cout << int(t * 100 / t1) << "%" << std::endl; 
            perPersent = t * 100 / t1;
        }

        // Вычисляем новые значения y1
        for (int i = 0; i < n; i++)
            yTemp[i] = y1.back()[i] + step * paramsTemp[i];

        if (yTemp[0] > V_max)
            yTemp[0] = V_max;
        else if (yTemp[0] < 0)
            yTemp[0] = -V_max;

        // Обновляем значения y1
        y1.push_back(yTemp);
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