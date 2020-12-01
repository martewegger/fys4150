import numpy as np
from run import *
import matplotlib.pyplot as plt
from astropy import constants
plt.rcParams['font.size'] = 16

dx = 0.1
r=2
dt = dx**2/r
T_end = 0.03
method = "ForwardEuler"
#compile_func()
run_func(T_end, dt, dx, method = "ForwardEuler")
F_Euler = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
run_func(T_end, dt, dx, method = "Crank_Nicolsen")
CN = np.transpose(np.loadtxt("data_1D.txt"))
print(F_Euler.shape, CN.shape)
x = np.arange(0,1+dx,dx)

fig, ax = plt.subplots(1,2,figsize = (12,6))
ax[0].set_title(r'Time $=%g$, $\Delta t = \frac{(\Delta x)^2}{%g}$, $\Delta x = %g$' % (T_end, r, dx))
ax[0].plot(x, F_Euler, label='ForwardEuler')
#ax[0].plot(x, CN, label='Crank Nicolsen')
ax[0].set_xlabel('x')
ax[0].set_ylabel(r'$u(x,t)$')
ax[0].legend()
'''
T_end = 0.1
method = "ForwardEuler"
#compile_func()
run_func(T_end, dt, dx, method = "ForwardEuler")
F_Euler = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
run_func(T_end, dt, dx, method = "Crank_Nicolsen")
CN = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
x = np.arange(0,1+dx,dx)

ax[1].set_title(r'Time $=%g$, $\Delta t = \frac{(\Delta)x^2}{%g}$, $\Delta x = %g$' % (T_end, r, dx))'''
#ax[1].plot(x, F_Euler, label='ForwardEuler')
ax[1].set_title('Crank Nicolsen with same parameters')
ax[1].plot(x, CN, label='Crank Nicolsen')
ax[1].set_xlabel('x')
#ax[1].legend()
plt.savefig('CN_fail.png')

plt.show()
