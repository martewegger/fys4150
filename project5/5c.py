import numpy as np
from run import *
from chi_square import *
import matplotlib.pyplot as plt
from astropy import constants
plt.rcParams['font.size'] = 16

dx = 0.01            # Endre her til 0.01
r=2
dt = dx**2/r
T_end1 = 0.02
T_end2 = 0.1
# method = "ForwardEuler"
#compile_func()
run_func(T_end1, dt, dx, method = "ForwardEuler")
F_Euler = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
run_func(T_end1, dt, dx, method = "Crank_Nicolsen")
CN = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
run_func(T_end1, dt, dx, method = "BackwardEuler")
B_Euler = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]

x = np.arange(0,1+dx,dx)
analytic = analytic_sol_func(x,np.array((T_end1,T_end2)))

plt.figure()
plt.title(r'$t=%g$, $\Delta t = (\Delta x)^2/%g$, $\Delta x = %g$' % (T_end1, r, dx))
plt.plot(x, F_Euler, label='ForwardEuler')
plt.plot(x, CN, label='Crank-Nicolson')
plt.plot(x, B_Euler, label='BackwardEuler')
plt.plot(x, analytic[0],"r--", label="Analytic")
plt.xlabel('x')
plt.ylabel(r'$u(x,t)$')
plt.legend()
plt.savefig("task_c_t1.png")
plt.close()

run_func(T_end2, dt, dx, method = "ForwardEuler")
chi_square_func(np.loadtxt("data_1D.txt"), analytic_sol_func, np.array((T_end1,T_end2)), dt, method="FE", plot=True)
F_Euler = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
run_func(T_end2, dt, dx, method = "Crank_Nicolsen")
chi_square_func(np.loadtxt("data_1D.txt"), analytic_sol_func, np.array((T_end1,T_end2)), dt, method="CN", plot=True)
CN = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]
run_func(T_end2, dt, dx, method = "BackwardEuler")
chi_square_func(np.loadtxt("data_1D.txt"), analytic_sol_func, np.array((T_end1,T_end2)), dt, method="BE", plot=True)
B_Euler = np.transpose(np.loadtxt("data_1D.txt"))[:,-1]

plt.figure()
plt.title(r'$t=%g$, $\Delta t = (\Delta x^2)/%g$, $\Delta x = %g$' % (T_end2, r, dx))
plt.plot(x, F_Euler, label='ForwardEuler')
plt.plot(x, CN, label='Crank-Nicolson')
plt.plot(x, B_Euler, label='BackwardEuler')
plt.plot(x, analytic[1],"r--", label="Analytic")
plt.xlabel('x')
plt.ylabel(r'$u(x,t)$')
plt.legend()
plt.savefig('task_c_t2.png')
plt.close()
