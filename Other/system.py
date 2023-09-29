from consts import *
from math import sin, cos

def system(values, t):
    V, TH, w_z, th, y, x, m = values
    al = th - TH
    q = 0.5 * V ** 2 * 1.18 * 2.71 ** (-y / 10000)
    
    dVdt = P_val * cos(al) / m - (c_xa0 + A_val * al ** 2) * q * S_val / m - g_val * sin(TH)
    dTHdt = P_val * sin(al) / (m * V) + c_ya_al * q * S_val * al / (m * V) - g_val * cos(TH) / V
    dw_zdt = (m_z_al * al + m_z_wz * L_val / V * w_z + m_z_delb * (del_b * 3.14 / 180)) * q * S_val * L_val / I_z
    dthdt = w_z
    dydt = V * sin(TH)
    dxdt = V * cos(TH)
    dmdt = -m_c

    if V > V_max or V < -V_max:
        dVdt = 0

    return [dVdt, dTHdt, dw_zdt,
                dthdt, dydt, dxdt, dmdt]