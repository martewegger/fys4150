from run import *
import numpy as np
import matplotlib.pyplot as plt
plt.rcParams['font.size'] = 18
init = 'random'
T = 2.4
L = 100
L2 = L*L
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

print('total Std = ', np.std(E))
print('actual Std = ', np.std(E[indx1:]))


plt.figure(figsize=(10,10))
plt.title(r'Energy evolution for $T=%g$ with %s initiation' % (T, init_state))
plt.axvline(MC_array[indx1],c='k',ls = 'dashed', label='Burn in period')
plt.plot(MC_array, E/L2, label='E')
plt.plot(MC_array, E_mean/L2, label=r'$\langle E\rangle$')
plt.axhline(median1/L2, c='r', ls = 'dashed',label='$E_{eq} = %.3f$' % (median1/L2))
plt.ylabel(r'Energy$/L^2 $')
plt.xlabel('# of Monte Carlo cycles')
plt.legend(loc='upper right')
plt.savefig('burn_illu.png')
plt.show()
