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
delta = 0.002
#dxy = np.linspace(0.005,0.1, N+1)
dxy = np.arange(0.005,0.1+delta, delta)
N = len(dxy)
chi_arr = np.zeros((N))
Nxy = np.zeros((N))
T_end = 0.02
r = 4
dt = dxy[0]**2/r

a=0
for i in range(len(dxy)):
    a+=1
    print('computed = ',a,'/',len(dxy)+1, end = "\r")
    #dt = dxy[i]**2/r
    run_func(T_end, dt, dxy[i])
    data = np.loadtxt('data_2D.txt')
    xy = np.linspace(xy0,xy1,data.shape[0])
    X, Y = np.meshgrid(xy,xy)
    Nxy[i] = len(xy)**2
    chi_arr[i] = chi_squared_func(data, analytic_func(X, Y, T_end))

m, b = np. polyfit(dxy, chi_arr/Nxy, 1)
plt.figure(figsize=(11,11))
plt.title('Stability analysis')
plt.plot(dxy, chi_arr/Nxy, 'o')
plt.plot(dxy, m*dxy + b, label='Linear fit, $y = %.4f\cdot h %.6f$' % (m, b))
plt.xlabel(r'$h$')
plt.ylabel(r'$\chi^2/$pixel')
plt.legend()
plt.savefig('dxy_stability.png')
plt.show()
