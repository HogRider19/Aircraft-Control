import matplotlib.pyplot as plt
import numpy as np
from scipy.integrate import odeint
from system import system

from consts import *


# Начальные условия
y0 = [V_0, TH_0, w_z_0, th_0, y_0, x_0, m_0]

# Временной интервал
t = np.linspace(0, 33, 10000)

# Решение системы дифференциальных уравнений
sol = odeint(system, y0, t)

labels = ["V", "TH", "w_z", "th", "y", "x", "m"]

for i in range(4):
    plt.subplot(3, 3, i + 1)
    plt.plot(t, sol[:, i], label=labels[i])
    plt.title(labels[i])
    plt.grid(True)

plt.subplot(3, 3, 5)
plt.plot(sol[:, 5], sol[:, 4])
plt.title("y(x)")
plt.grid(True)

plt.show()