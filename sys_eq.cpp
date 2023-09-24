#include <consts.h>
#include <cmath>
#include <map>
#include <string>


double get_al(std::map<std::string, double> v)
{
    return v["th"] - v["TH"];
}

double get_q(std::map<std::string, double> v)
{
    return 0.5 * pow(v["V"], 2) * 1.18 * exp(-v["y"] / 10000);
}

////

double dVdt(std::map<std::string, double> v){
    double al = get_al(v);
    double q = get_q(v);
    return P*cos(al) / v["m"] - (c_xa0 + A * (pow(al, 2))) * q * S / v["m"] - g * sin(v["TH"]);
}

double dTHdt(std::map<std::string, double> v){
    double al = get_al(v);
    double q = get_q(v);
    return P*sin(al) / v["m"] * v["V"] + c_ya_al*q*S*al / (v["m"] * v["V"]) - g * cos(v["TH"]) / v["V"];
}

double dw_zdt(std::map<std::string, double> v){
    double al = get_al(v);
    double q = get_q(v);
    return (m_z_al*al + m_z_wz * L/ v["V"] *  v["w_z"] + m_z_delb*del_b)*q*S*L/I_z;
}

double dthdt(std::map<std::string, double> v){
    return v["w_z"];
}

double dydt(std::map<std::string, double> v){
    return v["V"]*sin(v["TH"]);
}

double dxdt(std::map<std::string, double> v){
    return v["V"]*cos(v["TH"]);
}

double dmdt(std::map<std::string, double> v){
    return -m_c;
}