import numpy as np
from run import *
import matplotlib.pyplot as plt
from astropy import constants
from analytic_2D import analytic_func
from chi_squared import chi_squared_func
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

plt.figure(figsize=(9,9))
plt.title('Computed diffusion model')
im1 = plt.imshow(data, cmap='inferno', extent = extent)
plt.colorbar(im1,fraction=0.046, pad=0.04)
plt.xlabel('x')
plt.ylabel('y')
plt.savefig('computed_2D.png')

plt.figure(figsize=(9,9))
ax2 = plt.subplot(1,1,1,projection='3d')
ax2.set_title('Surface plot of numerical solution')
X, Y = np.meshgrid(xy,xy)
ax2.plot_surface(X, Y, data, cmap='magma', rcount=200, ccount=200)
ax2.axis((1.1, -0.1, -0.1, 1.1));
ax2.set_xlabel("y")
ax2.set_ylabel("x")
ax2.set_zlabel("z")
plt.savefig('computed_3D.png')


analytic = analytic_func(X,Y,T_end)
plt.figure(figsize=(9,9))
plt.title('Analytic solution in 2D')
im3 = plt.imshow(analytic, cmap='inferno', extent = extent)
plt.colorbar(im3,fraction=0.046, pad=0.04)
plt.xlabel('x')
plt.ylabel('y')
plt.savefig('analytic_2D.png')

chi_ij = (data[1:-1,1:-1]-analytic[1:-1,1:-1])**2/analytic[1:-1,1:-1]
plt.figure(figsize=(9,9))
plt.title(r'$\chi^2_{i,j}$')
im4 = plt.imshow(chi_ij, cmap='inferno', extent = extent)
plt.colorbar(im4,fraction=0.046, pad=0.04)
plt.xlabel('x')
plt.ylabel('y')
plt.savefig('chi_sqrd.png')

plt.show()
'''
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
plt.show()'''
