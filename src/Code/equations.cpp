#include "equations.h"


double get_al(std::map<std::string, double> v)
{
    return v["th"] - v["TH"];
}

double get_q(std::map<std::string, double> v)
{
    return 0.5 * pow(v["V"], 2) * 1.18 * exp(-v["y"] / 10000);
}

double get_f_c(std::map<std::string, double> v){
    return v["e_c"] - v["TH"];
}

/*   
    Equations for the aircraft
*/

double dVdt(std::map<std::string, double> v){
    double al = get_al(v);
    double q = get_q(v);
    return P_val*cos(al) / v["m"] - (v["c_xa0"] + A_val * pow(al, 2)) * q * S_val / v["m"] - g_val * sin(v["TH"]);
}

double dTHdt(std::map<std::string, double> v){
    double al = get_al(v);
    double q = get_q(v);
    return P_val*sin(al) / (v["m"] * v["V"]) + v["c_ya_al"]*q*S_val*al / (v["m"] * v["V"]) - g_val * cos(v["TH"]) / v["V"];
}

double dTHdt_approach(std::map<std::string, double> v){
    return dVdt(v) / v["V"] * tan(v["e_c"] - v["TH"]);
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

/*   
    Equations for the target
*/

double dV_cdt(std::map<std::string, double> v){
    return 0;
};

double dTH_cdt(std::map<std::string, double> v){
    return 0;
};

double dx_cdt(std::map<std::string, double> v){
    return v["V_c"]*cos(v["TH_c"]);
};

double dy_cdt(std::map<std::string, double> v){
    return v["V_c"]*sin(v["TH_c"]);
};

double drdt(std::map<std::string, double> v){

    // #ifdef PARALLEL_APPROACH
    //     return sqrt(pow(v["x"] - v["x_c"], 2) + pow(v["y"] - v["y_c"], 2));
    // #endif

    double f_c = get_f_c(v);
    return v["V_c"] * cos(v["e_c"] - v["TH_c"]) - v["V"] * cos(v["e_c"] - v["TH"]);
};

double de_cdt(std::map<std::string, double> v){
    double f_c = get_f_c(v); 
    return (-v["V_c"] * sin(v["e_c"] - v["TH_c"]) + v["V"] * sin(v["e_c"] - v["TH"])) / v["r"];
};

double de_cdt_approach(std::map<std::string, double> v){
    return 0;
};