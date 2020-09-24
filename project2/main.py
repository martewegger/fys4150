import os
import sys
import matplotlib.pyplot as plt
import numpy as np


rho_max = np.linspace(3,10,10)
acum_rel_err = np.zeros(len(rho_max))
cpp_codes = "main.cpp class_code.cpp"
compiler_flags = "-larmadillo -O2"
executeable = "main.out"

def find_rho_max():
    os.system(" ".join(["c++", "-o", executeable, cpp_codes, compiler_flags]))
    run = "./main.out"

    for i in range(len(rho_max)):
        filename = "max_rel_err_%s" % i
        os.system(" ".join([run, str(rho_max[i]), str(filename)]))

    for i in range(len(rho_max)):
        filename = "max_rel_err_%s" % i
        acum_rel_err[i] = np.loadtxt(filename)
    plt.figure(); plt.title('Tittel')
    plt.plot(rho_max, acum_rel_err)
    #plt.show()
