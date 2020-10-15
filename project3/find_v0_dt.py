import os
import sys
import matplotlib.pyplot as plt
import numpy as np
from run import *
from scipy.ndimage.filters import gaussian_filter
from scipy.signal import savgol_filter
plt.rcParams['font.size'] = 14

def compile():
    cpp_codes = "main.cpp class_code.cpp"
    compiler_flags = "-larmadillo -O2"
    executeable = "main.out"

    os.system("echo compiling...")
    os.system(" ".join(["c++", "-o", executeable, cpp_codes, compiler_flags]))

def find_v0():
    n = 100
    v0_array = np.linspace(6.2,6.4,n)# AU/yr
    rel_err =np.zeros(n)
    compile_func()
    for i in range(len(v0_array)):
        filename = "orbit.txt"
        print('Running for x0, y0 = (1,0), vy0 = %f' % v0_array[i])
        run_func(filename, v0_array[i], vx0=0, dt=1e-3, T_end=1.1, method = "ForwardEuler", compile=False)
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
    plt.savefig('optimal_v0.png')
    np.save('optimal_v0.npy', v0_array[optimal_indx])
#compile()
#find_v0()

def find_dt():
    compile()
    n = 1001
    dt_array= np.linspace(1e-2,5e-4,n)
    rel_err =np.zeros(n)
    method1 = "ForwardEuler"
    filename = "orbit.txt"
    for i in range(len(dt_array)):
        print('Running for x0, y0 = (1,0), dt = %f' % dt_array[i])
        run_func(filename, np.load("optimal_v0.npy"), vx0=0, dt=dt_array[i], T_end=1.1, method =method1, compile=False)
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
    plt.savefig('optimal_dt_%s.png' % method1)
    np.save('optimal_dt_%s.npy' % method1, dt_array[optimal_indx])
    plt.show()
find_dt()
