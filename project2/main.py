import os
import sys
import matplotlib.pyplot as plt
import numpy as np


rho_max = np.linspace(3,6,10)
acum_rel_err = np.zeros(len(rho_max))
cpp_codes = "main.cpp class_code.cpp"
compiler_flags = "-larmadillo -O2"
executeable = "main.out"

def find_rho_max(run=False):
    n=350
    if run==True:
        os.system(" ".join(["c++", "-o", executeable, cpp_codes, compiler_flags]))
        run = "./main.out"

        for i in range(len(rho_max)):
            #filename = "max_rel_err_%s.txt" % i
            filename = "max_rel_err.txt"
            os.system(" ".join([run, str(rho_max[i]), str(filename), str(n)]))
            acum_rel_err[i] = np.loadtxt(filename)

    indx = np.argmin(acum_rel_err)
    plt.figure(); plt.title('Acumulative relative error for $\\rho_{max}$')
    plt.plot(rho_max, acum_rel_err, c='k', lw=0.8,ls='solid')
    plt.plot(rho_max[indx], acum_rel_err[indx], 'ro', label='(%.2f, %.2f)' % (rho_max[indx],acum_rel_err[indx]))
    plt.xlabel('$\\rho_{max}$')
    plt.ylabel('Relative error')
    plt.legend()
    plt.savefig('max_rel_err.png')
    #plt.show()
    os.system("rm max_rel_err.txt") # removing the txt file created.
    return np.min(acum_rel_err)

#find_rho_max(run=True)

def find_optimal_N(run = True):
    rho_max = 4.67  # calculated using the find_rho_max - function
    filename = "n_analysis.txt"
    if run==True:
        os.system(" ".join(["c++", "-o", executeable, cpp_codes, compiler_flags]))
        run = "./main.out"
    count = 2
    n = 350
    while count >1:
        filename = "n_analysis.txt"
        print('running for n= %d' % n)
        os.system(" ".join([run, str(rho_max), str(filename), str(n)]))
        count = np.loadtxt(filename)
        n += 10
        if n>=400:
            print(" No success, but break cause n too big..")
            break

    print("Possible success at n = %d" % (n-10))
    print("Fail count = %d" % count)

find_optimal_N(run=True)
