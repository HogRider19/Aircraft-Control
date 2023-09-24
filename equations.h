#include <map>
#include <string>
#include <cmath>


double get_al(std::map<std::string, double> v);
double get_q(std::map<std::string, double> v);

double dVdt(std::map<std::string, double> v);
double dTHdt(std::map<std::string, double> v);
double dw_zdt(std::map<std::string, double> v);
double dthdt(std::map<std::string, double> v);
double dydt(std::map<std::string, double> v);
double dxdt(std::map<std::string, double> v);
double dmdt(std::map<std::string, double> v);