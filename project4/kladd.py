import numpy as np
from run import *
import matplotlib.pyplot as plt
from probability import *
N_cycles = 1e6
MC_array = np.arange(N_cycles)

T0 = 2.1; T1 = 2.4
dT = 0.005
N = int(np.abs(T1-T0)//dT)
T_arr = np.linspace(T0,T1,N+2)


init_state='random'
T=2.4;L=20
run_func(temp = T, len = L, initial_state=init_state, MC_cycles = N_cycles)
L2 = L**2
M = np.transpose(np.loadtxt('magnetisation.txt'))
M_mean = np.cumsum(M)/(MC_array+1)
N_cycles = np.arange(len(M))
plt.plot(N_cycles, M_mean/L2)
plt.plot(N_cycles, M/L2)
plt.show()
#Energy
'''
print('T = ', T)
run_func(temp = T, len = L, initial_state=init_state, MC_cycles = N_cycles)
E = np.transpose(np.loadtxt("Energy.txt"))
median1 = np.median(E)
sigma=np.std(E[np.where(E<=median1)[0][0]:])
indx1 = np.where(E<=median1+sigma)[0][0]
print(indx1)
print('#burn in cycles needed= ',indx1+1)
MC_short = np.arange(N_cycles-indx1)
E_mean = np.cumsum(E)/(MC_array+1)
print(E[indx1:].shape, MC_array[indx1:].shape)

print('total Std = ', np.std(E))
print('actual Std = ', np.std(E[indx1:]))

print('\n')

print(E_mean[int(1e5)],E_mean[int(5e5)])

plt.figure(figsize=(10,10))
plt.title(r'Energy evolution for $T=%g$ with %s initiation' % (T, init_state))
plt.axvline(MC_array[indx1],c='k',ls = 'dashed')
plt.plot(MC_array, E, label='E')
plt.plot(MC_array, E_mean, label=r'$\langle E\rangle$')
plt.axhline(median1, c='r', ls = 'dashed',label='$E_{eq} = %i$' % median1)
plt.ylabel('Energy $[J]$')
plt.xlabel('# of Monte Carlo cycles')
plt.legend(loc='upper right')
'''

'''
#run_func(temp = T, len = L, initial_state=init_state, MC_cycles = N_cycles)
M = np.abs(np.transpose(np.loadtxt("magnetisation.txt")))
M_mean = np.cumsum(M[indx1:])/(MC_array[indx1:]+1)

plt.figure(figsize=(10,10))
plt.title(r'Magnetisation for $T=%g$ with %s initiation' % (T, init_state))

plt.plot(MC_array, M, label=r'$|M|$')
plt.plot(MC_array[indx1:], M_mean, label=r'$\langle |M|\rangle$')
plt.ylabel('Magnetisation $[J]$')
plt.xlabel('# of Monte Carlo cycles')
plt.legend(loc='upper right')'''
plt.show()
