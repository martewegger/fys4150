import numpy as np
from run import *
import matplotlib.pyplot as plt
from astropy import constants

dx = 0.1
r=2
dt = dx**2/r
T_end = 0.1
method = "ForwardEuler"
#compile_func()
run_func(T_end, dt, dx, method = "ForwardEuler")
F_Euler = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
run_func(T_end, dt, dx, method = "Crank_Nicolsen")
CN = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
run_func(T_end, dt, dx, method = "BackwardEuler")
B_Euler = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]

x = np.arange(0,1+dx,dx)

plt.figure(figsize = (12,6))
plt.title(r'Time $=%g$, $\Delta t = \frac{(\Delta x)^2}{%g}$, $\Delta x = %g$' % (T_end, r, dx))
plt.plot(x, F_Euler, label='ForwardEuler')
plt.plot(x, CN, label='Crank Nicolsen')
plt.plot(x, B_Euler, label='BackwardEuler')
plt.xlabel('x')
plt.ylabel(r'$u(x,t)$')
plt.legend()
plt.show()
