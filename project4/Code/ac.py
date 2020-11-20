import numpy as np
import matplotlib.pyplot as plt
from run import run_func

def exact_2by2_func(T_arr):
    beta = 1/T_arr
    Z = 12 + 2*np.exp(8*beta) + 2*np.exp(-8*beta)
    M = (8*np.exp(8*beta) + 16)/Z
    E = 16/Z*(np.exp(-8*beta) - np.exp(8*beta))
    C_V = 256/(Z*T_arr**2)*(np.cosh(8*beta) - 4*np.sinh(8*beta)**2/Z)
    Chi = (32*np.exp(8*beta) + 32)/(Z*T_arr)
    return E, M, C_V, Chi

def numerical_2by2_func(T):
    L=2
    N_cycles = 1e5
    init_state = 'random'
    # run_func(temp = T, len = L, initial_state=init_state, MC_cycles = N_cycles)
    energies = np.transpose(np.loadtxt('energy.txt'))
    magnetisation = np.transpose(np.loadtxt('magnetisation.txt'))
    E = np.mean(energies)
    E2 = np.mean(energies**2)
    M = np.mean(np.abs(magnetisation))
    M2 = np.mean(magnetisation**2)
    C_V = (E2 - E**2)/T**2
    Chi = (M2 - np.mean(magnetisation)**2)/T
    return E, M, C_V, Chi

if __name__ == "__main__":
    print(exact_2by2_func(1))
    print(numerical_2by2_func(1))
