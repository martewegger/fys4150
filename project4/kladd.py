from run import *
import numpy as np
import matplotlib.pyplot as plt
plt.rcParams['font.size'] = 14


def d_func():
    T = 1 # kT/J
    N_cycles = 2e5
    T = 2.4
    run_func(temp = T, len = 20, initial_state="random", MC_cycles = N_cycles)
    energies_disordered = np.transpose(np.loadtxt("Energy.txt"))
    plt.figure(figsize=(15,7))
    plt.subplot(1,2,1)
    plt.title(r'Energy as a function of MonteCarlo cycles for $T=1 $kT/J')
    plt.plot(np.arange(N_cycles), energies_disordered, label='Initially disordered')
    plt.axhline(np.median(energies_disordered), c='r',label='$E_{eq} = %i$' % np.median(energies_disordered))
    plt.legend(loc='upper right')

    run_func(temp = T, len = 20, initial_state="ordered", MC_cycles = N_cycles)
    energies_ordered = np.transpose(np.loadtxt("Energy.txt"))
    plt.subplot(1,2,2)
    plt.title(r'Energy as a function of MonteCarlo cycles for $T=1 $kT/J')
    plt.plot(np.arange(N_cycles), energies_ordered, label='Initially ordered')
    plt.axhline(np.median(energies_ordered), c='r',label='$E_{eq} = %i$' % np.median(energies_ordered))
    plt.legend(loc='lower right')
    plt.show()
#compile_func()
d_func()
