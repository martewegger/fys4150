from run import *
import numpy as np


def find_burn_N_func():
    T_arr = np.arange(2,2.3+0.05,0.05)

    L_arr = np.array((40,60,80,100))
    results = np.zeros((len(L_arr), len(T_arr)))
    for i, L in enumerate(L_arr):

        for j, T in enumerate(T_arr):
            print(i," ",j, end = "\r")
            run_func(temp = T, len = L, initial_state="random", MC_cycles= 5e5)
            energies = np.transpose(np.loadtxt("Energy.txt"))
            median = np.median(energies)
            indx = np.where(energies==median)[0][0]
            results[i,j] = indx+1
    print(results)
    np.save('burn_in_no_v2.npy', results)
find_burn_N_func()
