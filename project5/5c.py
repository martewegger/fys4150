import numpy as np
from run import *
import matplotlib.pyplot as plt
from astropy import constants
plt.rcParams['font.size'] = 18

dx = 0.1
dt = dx**2/3
T_end = 0.02
method = "ForwardEuler"
#compile_func()
run_func(T_end, dt, dx, method)
x = np.arange(0,1+dx,dx)
data = np.transpose(np.loadtxt("data_1D.txt"))
print(x.shape, data.shape)

plt.figure(figsize = (8,8))
plt.plot(x, data[:,-1])
plt.show()
