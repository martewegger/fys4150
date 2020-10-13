import os
import sys
import matplotlib.pyplot as plt
import numpy as np
plt.rcParams['font.size'] = 14

def compile():
    cpp_codes = "main.cpp class_code.cpp"
    compiler_flags = "-larmadillo -O2"
    executeable = "main.out"

    os.system("echo compiling...")
    os.system(" ".join(["c++", "-o", executeable, cpp_codes, compiler_flags]))


def find_v0():

    n = 20
    v0_array = np.linspace(6.2,6.4,n)# AU/yr

    N =1e5
    rel_err =np.zeros(n)
    run = "./main.out"
    for i in range(len(v0_array)):
        filename = "orbit.txt"
        print('Running for x0, y0 = (1,0), vy0 = %f' % v0_array[i])
        os.system(" ".join([run, str(N), str(filename),str(v0_array[i])]))
        x, y = np.transpose(np.loadtxt(filename))
        rel_err[i] = (np.abs(np.sum(np.sqrt(x**2+y**2) - 1)))/1
        print('Relative error = %3.f' % rel_err[i])
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
    v0 = np.load("optimal_v0.npy")
    T_end = 1.1
    n = 1001
    dt_array= np.linspace(1e-2,5e-4,n)
    N_array = T_end/dt_array+1
    #N_array = np.linspace(1e4,1e6, 101)
    #dt_array = T_end/(N_array-1)

    N =1e5
    rel_err =np.zeros(n)
    run = "./main.out"

    for i in range(len(dt_array)):
        filename = "orbit.txt"
        print('Running for x0, y0 = (1,0), dt = %f' % dt_array[i])
        print('N = %.3e' % N_array[i])
        os.system(" ".join([run, str(N_array[i]), str(filename),str(v0)]))
        x, y = np.transpose(np.loadtxt(filename))
        rel_err[i] = (np.abs(np.sum(np.sqrt(x**2+y**2) - 1)))/1
        print('Relative error = %.6f' % rel_err[i])
        os.system(" ".join(["rm", filename]))
    optimal_indx = np.argmin(rel_err)
    print('Optimal dt = %f' % (dt_array[optimal_indx]))

    plt.figure(figsize = (8,8))
    plt.title('Accumulative relative error for orbit')
    plt.plot(dt_array, rel_err)
    plt.plot(dt_array[optimal_indx], rel_err[optimal_indx], 'ro', label=r'$\Delta t$ = %f' % dt_array[optimal_indx])
    plt.xlabel(r'$\Delta t$')
    plt.ylabel('Relative error')
    plt.legend()
    plt.savefig('optimal_dt.png')
    np.save('optimal_dt.npy', dt_array[optimal_indx])
    plt.show()



compile()
find_dt()
