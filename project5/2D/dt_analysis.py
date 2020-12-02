import numpy as np
from run import *
import matplotlib.pyplot as plt
from astropy import constants
from analytic_2D import analytic_func
from chi_squared import chi_squared_func
plt.rcParams['font.size'] = 16

xy0 = 0
xy1 = 1
#N = 20
dxy = 0.01
#r = np.linspace(4, 6, N)
dr = 0.005
#r = np.arange(4,30+dr,dr)
#r = np.arange(35,41+dr,dr)
r = np.arange(3.8,4.1+dr,dr)
dt = dxy**2/r
N = int(r.shape[0])
print('N = ', N, 'dt = ', dxy**2/r[N-1])
T_end = 0.02
#compile_func()
chi = np.zeros((N))
def compute():
    a=0
    for i in range(N):
        a+=1
        print('computed = ',a,'/',N, end = "\r")
        run_func(T_end, dt[i], dxy)
        data = np.loadtxt('data_2D.txt')
        xy = np.linspace(xy0,xy1,data.shape[0])
        X, Y = np.meshgrid(xy,xy)
        chi[i] = chi_squared_func(data, analytic_func(X, Y, T_end))
        np.save('dt_chi.npy', chi)
#compute()
chi = np.load('dt_chi.npy')
indx = np.where(chi<1e-4)[0][0]


plt.figure(figsize=(9,9))
plt.title('Stability analysis')
plt.plot(r, chi, 'o')
plt.vlines(r[indx],ymin=0, ymax=np.max(chi), ls='dashed', colors ='red', label='$r = %.3f$' % r[indx])
plt.yscale('log')
plt.xlabel(r'$r=\frac{\left(\Delta (x,y)\right)^2}{\Delta t}$')
plt.ylabel(r'$\chi^2$')
plt.legend()
plt.savefig('dt_stability.png')
plt.show()
