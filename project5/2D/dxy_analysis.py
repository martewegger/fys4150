import numpy as np
from run import *
import matplotlib.pyplot as plt
from astropy import constants
from analytic_2D import analytic_func
from chi_squared import chi_squared_func
plt.rcParams['font.size'] = 16

xy0 = 0
xy1 = 1
N = 50
dxy = np.linspace(0.005,0.2, N)
chi_arr = np.zeros((N))
T_end = 0.02
r = 4
dt = dxy[0]**2/r

a=0
for i in range(N):
    a+=1
    print('computed = ',a,'/',N, end = "\r")
    #dt = dxy[i]**2/r
    run_func(T_end, dt, dxy[i])
    data = np.loadtxt('data_2D.txt')
    xy = np.linspace(xy0,xy1,data.shape[0])
    X, Y = np.meshgrid(xy,xy)
    chi_arr[i] = chi_squared_func(data, analytic_func(X, Y, T_end))

m, b = np. polyfit(dxy, chi_arr, 1)
plt.figure(figsize=(9,9))
plt.title('Stability analysis')
plt.plot(dxy, chi_arr, 'o')
plt.plot(dxy, m*dxy + b, label='Linear fit')
plt.xlabel(r'$\Delta (x,y)$')
plt.ylabel(r'$\chi^2$')
plt.legend()
plt.savefig('dxy_stability.png')
plt.show()
