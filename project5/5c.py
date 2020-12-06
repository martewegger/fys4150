import numpy as np
from run import *
from chi_square import *
import matplotlib.pyplot as plt
from astropy import constants
plt.rcParams['font.size'] = 16

dx = 0.1
r=2
dt = dx**2/r
T_end = 0.02
method = "ForwardEuler"
#compile_func()
run_func(T_end, dt, dx, method = "ForwardEuler")
F_Euler = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
run_func(T_end, dt, dx, method = "Crank_Nicolsen")
CN = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
run_func(T_end, dt, dx, method = "BackwardEuler")
B_Euler = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]

x = np.arange(0,1+dx,dx)

fig, ax = plt.subplots(1,2,figsize = (12,6))
ax[0].set_title(r'Time $=%g$, $\Delta t = \frac{(\Delta x)^2}{%g}$, $\Delta x = %g$' % (T_end, r, dx))
ax[0].plot(x, F_Euler, label='ForwardEuler')
ax[0].plot(x, CN, label='Crank Nicolsen')
ax[0].plot(x, B_Euler, label='BackwardEuler')
ax[0].set_xlabel('x')
ax[0].set_ylabel(r'$u(x,t)$')
ax[0].legend()

T_end = 0.1
run_func(T_end, dt, dx, method = "ForwardEuler")
chi_square_func(np.loadtxt("data_1D.txt"), analytic_sol_func, np.array((0.02,0.1)), dt, method="FE", plot=True)
F_Euler = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
run_func(T_end, dt, dx, method = "Crank_Nicolsen")
chi_square_func(np.loadtxt("data_1D.txt"), analytic_sol_func, np.array((0.02,0.1)), dt, method="CN", plot=True)
CN = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
run_func(T_end, dt, dx, method = "BackwardEuler")
chi_square_func(np.loadtxt("data_1D.txt"), analytic_sol_func, np.array((0.02,0.1)), dt, method="BE", plot=True)
B_Euler = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
x = np.arange(0,1+dx,dx)

ax[1].set_title(r'Time $=%g$, $\Delta t = \frac{(\Delta)x^2}{%g}$, $\Delta x = %g$' % (T_end, r, dx))

ax[1].plot(x, F_Euler, label='ForwardEuler')
ax[1].plot(x, CN, label='Crank Nicolsen')
ax[1].plot(x, B_Euler, label='BackwardEuler')
ax[1].set_xlabel('x')
ax[1].legend()
plt.savefig('task_c.png')

plt.show()
