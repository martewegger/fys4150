import numpy as np
from run import *
import matplotlib.pyplot as plt

def calc_func():
    burn_in_no = np.load('burn_in_no_v1.npy')
    T0 = 2; T1 = 2.3
    dT = 0.05
    N = int(np.abs(T1-T0)//dT)
    T_arr = np.linspace(T0,T1,N+2)
    L_arr = np.array((40,60,80,100))
    E_mean = np.zeros((len(L_arr),len(T_arr)))
    M_mean = np.zeros((len(L_arr),len(T_arr)))
    E_mean_sqrd = np.zeros((len(L_arr),len(T_arr)))
    M_mean_sqrd = np.zeros((len(L_arr),len(T_arr)))

    for i, L in enumerate(L_arr):
        for j,T in enumerate(T_arr):
            print(i," ",j, end = "\r")
            run_func(temp = T_arr[j], len = L_arr[i], initial_state="ordered", MC_cycles = N_cycles, n = burn_in_no[i,j])
            E_mean[i,j], M_mean[i,j], E_mean_sqrd[i,j], M_mean_sqrd[i,j] = np.loadtxt('data.txt')
    np.save('E_M_E2_M2.npy', np.array((E_mean, M_mean, E_mean_sqrd, M_mean_sqrd)))

def plot_func():
    L_arr = np.array((40,60,80,100))
    E_mean, M_mean, E_mean_sqrd, M_mean_sqrd = np.load('E_M_E2_M2.npy')
    for i in range(len(L_arr)):
        plt.subplot(2,2,1)
        plt.title(r'Average energy, $\langle E \rangle $')
        plt.semilogy(T_arr, E_mean[i],label='L=%i' % L_arr[i])
        plt.ylabel(r'$\langle E \rangle\ [\texttt{J}]$')


        plt.subplot(2,2,2)
        plt.title(r'Average magnetisation, $\langle M \rangle$')
        plt.semilogy(T_arr, M_mean[i],label='L=%i' % L_arr[i])
        plt.ylabel(r'$\langle M \rangle$')

        plt.subplot(2,2,3)
        plt.title(r'Average squared energy, $\langle E^2 \rangle$')
        plt.semilogy(T_arr, E_mean_sqrd[i],label='L=%i' % L_arr[i])
        plt.ylabel(r'$\langle E^2 \rangle\ [\texttt{J^2}]$')
        plt.xlabel('Temperature')

        plt.subplot(2,2,4)
        plt.title(r'Average squared magnetisation, $\langle M^2 \rangle$')
        plt.semilogy(T_arr, M_mean_sqrd[i],label='L=%i' % L_arr[i])
        plt.ylabel(r'$\langle M^2 \rangle$')
        plt.xlabel('Temperature')
#compile_func()
calc_func()
#plot
