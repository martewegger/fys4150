import os
import sys
import matplotlib.pyplot as plt
import numpy as np
from run import *
from scipy.ndimage.filters import gaussian_filter
from scipy.signal import savgol_filter
plt.rcParams['font.size'] = 20
Euler = "ForwardEuler"
Verlet = "Verlet"

def find_v0():
    #compile_func()
    n = 100
    v0_array = np.linspace(6.2,6.4,n)# AU/yr
    rel_err =np.zeros(n)
    for i in range(len(v0_array)):
        filename = "orbit.txt"
        print('Running for x0, y0 = (1,0), vy0 = %f' % v0_array[i])
        run_func(filename, v0_array[i], vx0=0, dt=1e-3, T_end=1.1, method = Euler, compile=False)
        x, y = np.transpose(np.loadtxt(filename))
        rel_err[i] = (np.abs(np.sum(np.sqrt(x**2+y**2) - 1)))/1
        print('Relative error = %.3f' % rel_err[i])
    os.system(" ".join(["rm", filename]))


    optimal_indx = np.argmin(rel_err)
    print('Optimal vy0 = %f' % (v0_array[optimal_indx]))

    plt.figure(figsize = (8,8))
    plt.title('Accumulative relative error for orbit')
    plt.plot(v0_array, rel_err)
    plt.plot(v0_array[optimal_indx], rel_err[optimal_indx], 'ro', label='$V_{y0}$=%f' % v0_array[optimal_indx])
    plt.xlabel('$V_{y0}$')
    plt.ylabel('Relative error')
    plt.legend()
    #plt.savefig('optimal_v0.png')
    np.save('optimal_v0.npy', v0_array[optimal_indx])

#find_v0()

def find_dt(solver_method):
    n = 1001
    dt_array= np.linspace(1e-2,5e-4,n)
    rel_err =np.zeros(n)

    filename = "orbit.txt"
    for i in range(len(dt_array)):
        print('Running for x0, y0 = (1,0), dt = %f' % dt_array[i])
        run_func(filename, np.load("optimal_v0.npy"), vx0=0, dt=dt_array[i], T_end=1.1, method=solver_method, compile=False)
        x, y = np.transpose(np.loadtxt(filename))
        rel_err[i] = (np.abs(np.sum(np.sqrt(x**2+y**2) - 1)))/1
        print('Relative error = %.6f' % rel_err[i])
    os.system(" ".join(["rm", filename]))
    optimal_indx = np.argmin(rel_err)

    print('Optimal dt = %f' % (dt_array[optimal_indx]))
    plt.figure(figsize = (8,8))
    plt.title('Accumulative relative error for orbit')
    #plt.plot(dt_array, savgol_filter(rel_err, 51,6))
    plt.plot(dt_array, rel_err)
    plt.plot(dt_array[optimal_indx], rel_err[optimal_indx], 'ro', label=r'$\Delta t$ = %f' % dt_array[optimal_indx])
    plt.xlabel(r'$\Delta t$')
    plt.ylabel('Relative error')
    plt.legend()
    #plt.savefig('optimal_dt_%s.png' % solver_method)
    np.save('optimal_dt_%s.npy' % solver_method, dt_array[optimal_indx])
    plt.show()


#find_dt(Euler)
#find_dt(Verlet)

def time_func():
    #compile_func()
    N = 1e5
    T = 1.1
    h = T/(N-1)
    filename = "outfile.txt"
    run_func(filename, np.load("optimal_v0.npy"), vx0=0, dt=h, T_end=T, method=Euler, compile=False)
    Euler_time = np.loadtxt('timing.txt')
    run_func(filename, np.load("optimal_v0.npy"), vx0=0, dt=h, T_end=1.1, method=Verlet, compile=False)
    Verlet_time = np.loadtxt('timing.txt')
    print('Euler t = %s' % Euler_time)
    print('Verlet t = %s' % Verlet_time)

#time_func()


def vary_beta():

    beta_array = np.linspace(2,3,3)
    filename = 'outfile.txt'
    plt.figure(figsize=(8,8))
    plt.title(r'Earth orbit for varying $\beta$')
    print(np.load("optimal_v0.npy"))
    for i in range(len(beta_array)):
        run_func(filename, 5, vx0=0, dt=np.load('optimal_dt_Verlet.npy'), T_end=1.2, method=Verlet, beta = beta_array[i], compile=False)
        x,y = np.transpose(np.loadtxt(filename))
        plt.plot(x,y, label=r'$\beta = %.2f$' % beta_array[i])
    plt.xlabel('AU')
    plt.ylabel('AU')
    plt.legend()
    #plt.savefig('vary_beta.png')
    plt.show()
#compile_func()
#vary_beta()

def run_and_plot():
    filename = 'outfile.txt'
    run_func(filename, np.load("optimal_v0.npy"), vx0=0, dt=np.load('optimal_dt_Verlet.npy'), T_end=12, method=Verlet, beta=2, compile=False)
    x,y = np.transpose(np.loadtxt(filename))
    plt.figure(figsize=(8,8))
    plt.title('Earth´s orbit ')
    plt.plot(x,y, label='Earth')
    plt.plot(0,0,'.', label='Sun')
    plt.xlabel('AU')
    plt.ylabel('AU')
    plt.legend(loc='upper right')
    #plt.savefig('basic_orbit.png')
    #plt.show()
#compile_func()
#run_and_plot()
