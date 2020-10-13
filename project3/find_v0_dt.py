import os
import sys
import matplotlib.pyplot as plt
import numpy as np
plt.rcParams['font.size'] = 16

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

    plt.figure(figsize = (7,7))
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


compile()
find_dt()
