import numpy as np
from run import *
import matplotlib.pyplot as plt
from probability import *
N_cycles = 1e6
MC_array = np.arange(N_cycles)
def calc_plot(L=20, init_state='random'):
    print(init_state)
    L2 = L*L
    T=2.4
    #Energy
    print('T = ', T)
    run_func(temp = T, len = L, initial_state=init_state, MC_cycles = N_cycles)
    E = np.transpose(np.loadtxt("Energy.txt"))
    median1 = np.median(E)
    if init_state=='random':
        indx1 = np.where(E<=median1)[0][0]
    else:
        indx1 = np.where(E>=median1)[0][0]
    E_mean = np.cumsum(E)/(MC_array+1)

    print('total Std = ', np.std(E))
    print('actual Std = ', np.std(E[indx1:]))
    print('\n')

    plt.figure(figsize=(10,10))
    plt.title(r'Energy evolution for $T=%g$ with %s initiation' % (T, init_state))
    #plt.axvline(MC_array[indx1],c='k',ls = 'dashed')
    plt.plot(MC_array, E/L2, label='E')
    plt.plot(MC_array, E_mean/L2, label=r'$\langle E\rangle$')
    plt.axhline(median1/L2, c='r', ls = 'dashed',label='$E_{eq} = %i$' % median1)
    plt.ylabel('Energy $[J]$')
    plt.xlabel('# of Monte Carlo cycles')
    plt.legend(loc='upper right')
    plt.savefig('E_%i_%s.png' % (T,init_state))


    #Magnetisation
    run_func(temp = T, len = L, initial_state=init_state, MC_cycles = N_cycles)
    M = np.transpose(np.loadtxt("magnetisation.txt"))
    M_mean = np.cumsum(M)/(MC_array+1)

    plt.figure(figsize=(10,10))
    plt.title(r'Magnetisation for $T=%g$ with %s initiation' % (T, init_state))

    plt.plot(MC_array, M/L2, label=r'$|M|$')
    plt.plot(MC_array, M_mean/L2, label=r'$\langle |M|\rangle$')
    plt.ylabel('Magnetisation $[J]$')
    plt.xlabel('# of Monte Carlo cycles')
    plt.legend(loc='upper right')
    plt.savefig('M_%i_%s.png' % (T,init_state))

    #probability distribution
    plt.figure(figsize=(10,10))
    probability_func(E[indx1:], '%s initial state, T=%g' % (init_state,T))
    print('Equilibrium situation reached after %i MC cycles with %s initial state' % (MC_array[indx1], init_state))
    plt.savefig('energies_%i_%s.png' % (T,init_state))


    T = 1
    print('T = ', T)
    #Energy
    run_func(temp = T, len = L, initial_state=init_state, MC_cycles = N_cycles)
    E2 = np.transpose(np.loadtxt("Energy.txt"))
    median2 = np.median(E2)
    if init_state=='random':
        indx2 = np.where(E2<=median2)[0][0]
    else:
        indx2 = np.where(E2>=median2)[0][0]
    E2_mean= np.cumsum(E2)/(MC_array+1)

    print('total Std = ', np.std(E2))
    print('actual Std = ', np.std(E2[indx2:]))
    print('\n')

    plt.figure(figsize=(10,10))
    plt.title(r'Energy evolution for $T=%g$ with %s initiation' % (T,init_state))
    #plt.axvline(MC_array[indx2],c='k',ls = 'dashed')
    plt.plot(MC_array, E2/L2, label='E')
    plt.plot(MC_array, E2_mean/L2, label=r'$\langle E\rangle$')
    plt.axhline(median2/L2, c='r', ls = 'dashed',label='$E_{eq} = %i$' % median2)
    plt.ylabel('Energy $[J]$')
    plt.xlabel('# of Monte Carlo cycles')
    plt.legend(loc='upper right')
    plt.savefig('E_%i_%s.png' % (T,init_state))


    #Magnetisation
    run_func(temp = T, len = L, initial_state=init_state, MC_cycles = N_cycles)
    M2 = np.abs(np.transpose(np.loadtxt("magnetisation.txt")))
    M2_mean = np.cumsum(M2)/(MC_array+1)

    plt.figure(figsize=(10,10))
    plt.title(r'Magnetisation for $T=%g$ with %s initiation' % (T,init_state))

    plt.plot(MC_array, M2/L2, label=r'$|M|$')
    plt.plot(MC_array, M2_mean/L2, label=r'$\langle |M|\rangle$')
    plt.ylabel('Magnetisation $[J]$')
    plt.xlabel('# of Monte Carlo cycles')
    plt.legend(loc='upper right')
    plt.savefig('M_%i_%s.png' % (T,init_state))

    #Probability distribution
    plt.figure(figsize=(10,10))
    probability_func(E2[indx2:], '%s initial state, T=%g' % (init_state,T))
    print('Equilibrium situation reached after %i MC cycles with %s initial state' % (MC_array[indx2], init_state))
    plt.savefig('energies_%i_%s.png' % (T,init_state))
#compile_func()
calc_plot(init_state="random")
calc_plot(init_state='ordered')
