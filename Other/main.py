import numpy as np
import matplotlib.pyplot as plt
include "matplotlibcpp.h"

# Заданные параметры
D = 1  # Дисперсия
a = 1  # Параметр a
T = 3 * a  # Интервал

# Функция для генерации белого шума
def generate_white_noise(n):
    return np.random.normal(loc=0, scale=1, size=n)

# Функция для расчета корреляционной функции
def correlation_function(t):
    return D * np.exp(-a * np.abs(t))

# Функция для применения фильтра
def apply_filter(white_noise):
    filtered_process = np.zeros_like(white_noise)
    for i in range(len(white_noise)):
        filtered_process[i] = np.sum(white_noise[:i+1] * np.exp(-a * np.arange(i, -1, -1)))
    return filtered_process

# Генерация белого шума
n_samples = 1000
white_noise = generate_white_noise(n_samples)

# Применение фильтра
filtered_process = apply_filter(white_noise)

# Расчет корреляционной функции для полученного процесса
correlation_values = np.zeros_like(filtered_process)
for i in range(len(filtered_process)):
    correlation_values[i] = np.sum(filtered_process[:i+1] * filtered_process[::-1][:i+1])

# Нормализация корреляционной функции
correlation_values /= np.max(correlation_values)

# Расчет значений времени для построения графика
time_values = np.linspace(0, T, n_samples)

# Построение графиков
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.plot(time_values, correlation_function(time_values), label='Заданная корреляционная функция')
plt.xlabel('Время')
plt.ylabel('Корреляционная функция')
plt.title('Заданная корреляционная функция')
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(time_values, correlation_values, label='Полученная корреляционная функция')
plt.xlabel('Время')
plt.ylabel('Корреляционная функция')
plt.title('Полученная корреляционная функция')
plt.legend()

plt.tight_layout()
plt.show()