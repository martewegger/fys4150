import numpy as np
from run import *
import matplotlib.pyplot as plt
from astropy import constants
from analytic_2D import analytic_func
plt.rcParams['font.size'] = 16
xy0 = 0
xy1 = 1
dxy = 0.01
dt = dxy**2/4
T_end = 0.02
T_end = 0.1
xy = np.arange(xy0,xy1+dxy,dxy)
#compile_func()
run_func(T_end, dt, dxy)
data = np.loadtxt('data_2D.txt')


extent = [0,1,0,1]
plt.figure(figsize=(12,12))
ax1 = plt.subplot(2,2,1)
ax1.set_title('t = %g'% T_end)
im = ax1.imshow(data, cmap='inferno', extent = extent)
plt.colorbar(im, ax = ax1,fraction=0.046, pad=0.04)

ax2 = plt.subplot(2,2,2,projection='3d')
ax2.set_title('Surface plot')
X, Y = np.meshgrid(xy,xy)
ax2.plot_surface(X, Y, data, cmap='magma', rcount=200, ccount=200)
ax2.axis((1.1, -0.1, -0.1, 1.1));
ax2.set_xlabel("y")
ax2.set_ylabel("x")
ax2.set_zlabel("z")


analytic = analytic_func(X,Y,T_end)
ax3 = plt.subplot(2,2,3)
ax3.set_title('t = %g'% T_end)
im = ax3.imshow(analytic, cmap='inferno', extent = extent)
plt.colorbar(im, ax = ax3,fraction=0.046, pad=0.04)

rel_err = np.abs(analytic[1:-1,1:-1]-data[1:-1,1:-1])/analytic[1:-1,1:-1]
ax4 = plt.subplot(2,2,4)
ax4.set_title('t = %g'% T_end)
im = ax4.imshow(rel_err, cmap='inferno', extent = extent)
plt.colorbar(im, ax = ax4,fraction=0.046, pad=0.04)


plt.savefig('computed_2D.png')


fig, ax = plt.subplots(1,2,figsize=(12,6))
slice_data = data[data.shape[0]//2,:]
slice_ana = analytic[data.shape[0]//2,:]

ax[0].set_title('Alice along the y-axis')
ax[0].plot(xy, slice_data, c = 'red',ls ='solid', label='Computed')
ax[0].plot(xy, slice_ana, c = 'blue', ls='dashed', label='Analytic')
ax[0].legend()

ax[1].set_title('Relative error')
slice_rel_err = np.abs(slice_ana[1:-1]-slice_data[1:-1])/slice_ana[1:-1]
ax[1].plot(xy[1:-1], slice_rel_err)
plt.show()
