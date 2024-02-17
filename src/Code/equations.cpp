#include "equations.h"

double sign(double val) {
    if (val > 0)
        return 1;
    else if(val == 0)
        return 0;
    
    return -1;
}

double getAltha_(std::map<std::string, double> v){
    double altha = v["x2"] - v["x1"];
    if(fabs(altha) <= Altha_max)
        return altha;
        
    return Altha_max * sign(altha);
}

double getTH(std::map<std::string, double> v){
    return (10000 - v["x5"]) / (b_val - V_val * v["t"]);
}

double dx1(std::map<std::string, double> v){
    return K_val * getAltha_(v);
}

double dx2(std::map<std::string, double> v){
    return v["x3"];
}

double dx3(std::map<std::string, double> v){
    return l_val * v["x1"] - l_val * v["x2"] - M_val * v["x3"] + n_val * v["x4"];
}

double dx4(std::map<std::string, double> v){
    return -k_t_val * v["x4"] - i_1_val * v["x2"] - i_2_val*v["x3"] + s_val * (getTH(v) - v["x1"]);
}

double dx5(std::map<std::string, double> v){
    return V_val * sin(v["x1"]);
}
