#include <consts.h>
#include <cmath>
double al = th - TH;

double dVdt(double TH, double V){
    return P*cos(al)/m - (c_xa0 + A*(al^2))*q*S/m - g*sin(TH);
}

double dTHdt(double V, double TH){
    return P*sin(al)/m*V + c_ya_al*q*S*al/(m*V) - g*cos(TH)/V;
}

double dw_zdt(double V, double w_z){
    return (m_z_al*al + m_z_wz * L/V * w_z +m_z_delb*del_b)*q*S*L/I_z;
}

double dthdt(double th, double w_z){
    return w_z;
}

double dydt(double V, double TH, double y){
    return V*sin(TH);
}

double dxdt(double V, double TH, double y){
    return V*cos(TH);
}

double dmdt(){
    return -m_c;
}