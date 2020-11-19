from run import *
import numpy as np
import matplotlib.pyplot as plt
from probability import *
plt.rcParams['font.size'] = 14


def d_func(T=1, N_cycles = 1e5):
    print('T = ', T)
    MC_array = np.arange(N_cycles)

    run_func(temp = T, len = 40, initial_state="random", MC_cycles = N_cycles)
    energies_disordered = np.transpose(np.loadtxt("Energy.txt"))
    #print('Variance = ', np.var(energies_disordered))
    #print('RMS = ', np.std(energies_disordered))
    median = np.median(energies_disordered)
    indx1 = np.where(energies_disordered==median)[0][0]

    run_func(temp = T, len = 40, initial_state="ordered", MC_cycles = N_cycles)
    energies_ordered = np.transpose(np.loadtxt("Energy.txt"))
    #print('Variance = ', np.var(energies_ordered))
    #print('RMS = ', np.std(energies_ordered))
    median = np.median(energies_ordered)
    indx2 = np.array((np.where(energies_ordered==median)))[0,0]

    plt.figure(figsize=(15,7))
    plt.subplot(1,2,1)
    plt.title(r'Energy evolution for $T=%g$ kT/$J$' % T)
    plt.plot(MC_array, energies_disordered, label='Initially disordered')
    plt.axhline(median, c='r', ls = 'dashed',label='$E_{eq} = %i$' % median)
    plt.ylabel('Energy $[J]$(coupling constant)')
    plt.xlabel('# of Monte Carlo cycles')
    plt.xlim(0, 4*np.max([indx1, indx2]))
    plt.legend(loc='upper right')


    plt.subplot(1,2,2)
    plt.title(r'Energy evolution for $T=%g$ kT/$J$' % T)
    plt.plot(MC_array, energies_ordered, label='Initially ordered')
    plt.axhline(median, c='r', ls = 'dashed',label='$E_{eq} = %i$' % median)
    plt.xlabel('# of Monte Carlo cycles')
    plt.xlim(0, 4*np.max([indx1, indx2]))
    plt.legend()
    plt.savefig('energies_T_%i' % T)
    #plt.show()

    plt.figure(figsize = (15,7))
    plt.subplot(1,2,1)
    probability_func(energies_disordered[indx1:], 'Disordered, T=%g' % T)
    print('Equilibrium situation reached after %i MC cycles with disordered initial state' % MC_array[indx1])
    print('RMS = ', np.std(energies_disordered))
    print('RMS = ', np.std(energies_disordered[indx1:]), 'Cut disordered')

    plt.subplot(1,2,2)
    probability_func(energies_ordered[indx2:], 'Ordered, T=%g' % T)
    plt.savefig('prob_T_%i' % T)
    print('Equilibrium situation reached after %i MC cycles with ordered initial state' % MC_array[indx2])
    print('RMS = ', np.std(energies_ordered))
    print('RMS = ', np.std(energies_ordered[indx2:]), 'cut ordered')
    #plt.show()





#compile_func()
#d_func(T=1, N_cycles=5e5)
#d_func(T=2.4, N_cycles=5e5)
d_func(T=2.4, N_cycles=5e5)
'''
T_arr = np.linspace(2,2.3,7)
for i in range(len(T_arr)):
    d_func(T=T_arr[i], N_cycles=5e5)'''
