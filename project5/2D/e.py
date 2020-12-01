import numpy as np
from run import *
import matplotlib.pyplot as plt
from astropy import constants
plt.rcParams['font.size'] = 16
xy0 = 0
xy1 = 1
dxy = 0.01
dt = dxy**2/4
T_end = 0.02
xy = np.arange(xy0,xy1+dxy,dxy)
#compile_func()
run_func(T_end, dt, dxy)
data = np.loadtxt('data_2D.txt')

extent = [0,1,0,1]
plt.figure(figsize=(13,6))
ax1 = plt.subplot(1,2,1)
ax1.set_title('t = %g'% T_end)
im = plt.imshow(data, cmap='inferno', extent = extent)
plt.colorbar(im, ax = ax1,fraction=0.046, pad=0.04)

ax2 = plt.subplot(1,2,2,projection='3d')
ax2.set_title('Surface plot')
ax2 = plt.subplot(1,2,2,projection='3d')
X, Y = np.meshgrid(xy,xy)
ax2.plot_surface(X, Y, data, cmap='magma', rcount=200, ccount=200)
ax2.axis((1.1, -0.1, -0.1, 1.1));
ax2.set_xlabel("y")
ax2.set_ylabel("x")
ax2.set_zlabel("z")
plt.show()
