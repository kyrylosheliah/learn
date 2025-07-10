from sympy import *

def formula_plot(string_formula = "x**2 + 3*x - 1/2", x_num = 4.0):
    x = symbols('x')
    expr = sympify(string_formula)
    return expr.subs(x, x_num).evalf()

def formula_surface(string_formula = "x**2 + 3*y - 1/2", x_num = 4.0, y_num = 8.0):
    x, y = symbols('x y')
    expr = sympify(string_formula)
    return expr.subs(x, x_num).subs(y, y_num).evalf()

# print(formula_plot())
# print(formula_plot("x^2", 4))
# print(formula_surface())
# print(formula_surface("x^2 + y^2", 1, 2))

from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from matplotlib import cm
import matplotlib.pyplot as plt
import tkinter as tk

win = tk.Tk()
win.title("python_lab11_12")
win.geometry("300x100")
str1 = tk.Entry(win)
str1.grid(row = 0, column = 0)
str2 = tk.Entry(win)
str2.grid(row = 1, column = 0)

import re

def update_plot():
    f_str1 = str(str1.get())
    # f_str1 = re.sub(r'[^0-9()+\-*/^x]', "", f_str1)
    # str1.delete(0,"end")
    # str1.insert(0, f_str1)
    plot_x = np.linspace(0, 6*np.pi, 100)
    plot_y = np.copy(plot_x)
    for i in range(len(plot_y)):
        plot_y[i] = formula_plot(f_str1, plot_y[i])
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.plot(plot_x, plot_y, 'r-')
    plt.show()

def create_surface():
    f_str2 = str(str2.get())
    # f_str2 = re.sub(r'[^0-9()+\-*/^xy]', "", f_str2)
    # str2.delete(0,"end")
    # str2.insert(0, f_str2)
    x_plot = np.linspace(-100, 100, 50)
    y_plot = np.linspace(-100, 100, 50)
    x, y = np.meshgrid(x_plot, y_plot)
    z = np.copy(x)
    for i in range(len(z)):
        for j in range(len(z[i])):
            z[i][j] = formula_surface(f_str2, x[i][j], y[i][j])
    fig = plt.figure(figsize = (6,6))
    Axes3D = fig.add_subplot(projection = '3d')
    Axes3D.set_xlabel('X')
    Axes3D.set_ylabel('Y')
    Axes3D.set_zlabel('Z')
    surf = Axes3D.plot_surface(x, y, z, rstride=5, cstride=5, cmap=cm.viridis)
    plt.draw()
    plt.show()

button = tk.Button(win, text = "График", command = update_plot)
button.grid(row = 0, column = 1)
button = tk.Button(win, text = "Поверхность", command = create_surface)
button.grid(row = 1, column = 1)
win.mainloop()