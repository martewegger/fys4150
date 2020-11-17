import numpy as np
from run import *
import matplotlib.pyplot as plt
from probability import *

burn_in_no = np.loadtxt('burn_in_no_2e+06.txt')
T_arr = np.arange(2,2.3+0.05,0.05)
L_arr = np.array((40,60,80,100))
N_cycles = 1e6
L = 40; T = 2
L2 = len(T_arr)*len(L_arr)
'''
for i, L in enumerate(L_arr):
    for j,T in enumerate(T_arr):
        print((i+1)*(j+1),"/", L2, end = "\r")
        run_func(temp = T_arr[j], len = L_arr[i], initial_state="random", MC_cycles = N_cycles, n = burn_in_no[i,j])
        E, M, E2, M2 = np.loadtxt('data.txt')
        print(M2)'''
#compile_func()
'''
print(burn_in_no[0,0])

run_func(temp = T_arr[0], len =L_arr[0], initial_state="random", MC_cycles = N_cycles, n =burn_in_no[0,0])
#E, M, E2, M2 = np.loadtxt('data.txt')
M = np.loadtxt('magnetisation.txt')
#E = np.loadtxt('Energy.txt')
M_mean = expectation_func(M)
probability_func(M, in_label='magnetisation')
plt.show()'''

#E_mean = expectation_func(E)
#M_mean = expectation_func(M)
#E_mean_2 = expectation_func(E, squared=True)
#M_mean_2 = expectation_func(M, squared=True)
#print(E_mean, M_mean, E_mean_2, M_mean_2)
#plt.plot(np.arange(N_cycles), M)
#plt.show()
'''plt.plot(np.arange(N_cycles), E)
plt.show()'''
#probability_func(M, in_label='magnetisation')
E_mean = np.load('E_M_E2_M2.npy')[0]
a = E_mean*T_arr[np.newaxis]
print(a.shape)
