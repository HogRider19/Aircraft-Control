#include "equations.h"


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
    return P_val*cos(al) / v["m"] - (v["c_xa0"] + A_val * pow(al, 2)) * q * S_val / v["m"] - g_val * sin(v["TH"]);
}

double dTHdt(std::map<std::string, double> v){

    #ifdef PARALLEL_APPROACH
        return 0;
    #endif

    double al = get_al(v);
    double q = get_q(v);
    return P_val*sin(al) / (v["m"] * v["V"]) + v["c_ya_al"]*q*S_val*al / (v["m"] * v["V"]) - g_val * cos(v["TH"]) / v["V"];
}

double dw_zdt(std::map<std::string, double> v){
    double al = get_al(v);
    double q = get_q(v);
    return (m_z_al*al + m_z_wz * L_val/ v["V"] *  v["w_z"] + m_z_delb*(del_b * 3.14 / 180.0))*q*S_val*L_val/I_z;
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

double drdt(std::map<std::string, double> v){
    return v["V_c"] * cos(v["e_c"] - v["TH_c"]) - v["V"] * cos(v["f_c"] - v["TH_c"]);
}

double de_cdt(std::map<std::string, double> v){
    return (-v["V_c"] * cos(v["e_c"] - v["TH_c"]) - v["V"] * sin(v["f_c"] - v["TH_c"])) / v["r"];
} 