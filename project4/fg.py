import numpy as np
from run import *
import matplotlib.pyplot as plt
from probability import *
from astropy import constants
plt.rcParams['font.size'] = 14


def Cv_func(E_mean, E_mean_sqrd, T):
    return 1/(constants.k_B*T**2)*(E_mean_sqrd-E_mean**2)

def chi_func(M_mean, M_mean_sqrd, T):
    return 1/(constants.k_B*T)*(M_mean_sqrd-M_mean**2)

def calc_func():
    burn_in_no = np.loadtxt('burn_in_no_1e+07.txt')
    T0 = 2; T1 = 2.3
    dT = 0.05
    N = int(np.abs(T1-T0)//dT)
    T_arr = np.linspace(T0,T1,N+2)
    L_arr = np.array((40,60,80,100))
    E_mean = np.zeros((len(L_arr),len(T_arr)))
    M_mean = np.zeros((len(L_arr),len(T_arr)))
    E_mean_sqrd = np.zeros((len(L_arr),len(T_arr)))
    M_mean_sqrd = np.zeros((len(L_arr),len(T_arr)))
    N_cycles = 1e7
    ylen, xlen = E_mean.shape
    L2 = xlen*ylen
    a=0
    for i, L in enumerate(L_arr):
        for j,T in enumerate(T_arr):
            a+=1
            print(a,"/", L2, end = "\r")
            run_func(temp = T_arr[j], len = L_arr[i], initial_state="random", MC_cycles = N_cycles, n = burn_in_no[i,j])
            E = np.loadtxt('Energy.txt')
            M = np.loadtxt('magnetisation.txt')
            E_mean[i,j] = expectation_func(E)
            M_mean[i,j] = expectation_func(np.abs(M),type='magnetisation')
            E_mean_sqrd[i,j] = expectation_func(E,squared=True)
            M_mean_sqrd[i,j] = expectation_func(M, squared=True, type='magnetisation')
    np.save('E_M_E2_M2.npy', np.array((E_mean, M_mean, E_mean_sqrd, M_mean_sqrd)))



def plot_func():
    T0 = 2; T1 = 2.3
    L_arr = np.array((40,60,80,100))
    T_arr = np.linspace(T0,T1,7)
    E_mean, M_mean, E_mean_sqrd, M_mean_sqrd = np.load('E_M_E2_M2.npy')
    ylen, xlen = E_mean.shape
    Cv = Cv_func(E_mean, E_mean_sqrd, T_arr[np.newaxis])
    chi = chi_func(M_mean, M_mean_sqrd, T_arr[np.newaxis])
    plt.figure(figsize=(12,12))

    plt.subplot(2,2,1)
    plt.title(r'Energy, $\langle E \rangle$')
    for i in range(len(L_arr)):
        plt.plot(T_arr,E_mean[i], label='L=%i' % L_arr[i])
    plt.ylabel(r'$\langle E \rangle$')
    plt.legend()

    tol = 1e1  # Choose a tolerance
    M_indx = np.zeros((ylen))
    M_Tc = np.zeros((ylen))
    plt.subplot(2,2,2)
    plt.title(r'Magnetisation, $\langle |M| \rangle$')
    for i in range(len(L_arr)):
        #M_indx[i] = np.where(M_mean<=tol)[0][0]
        #M_Tc[i] = T_arr[M_indx[i]]
        plt.plot(T_arr,M_mean[i], label='L=%i' % L_arr[i])
        #plt.plot(M_Tc[i], M_mean[M_indx[i]], '.', label=r'$T_c = %.2f$ ' % M_Tc[i])

    plt.ylabel(r'$\langle |M| \rangle$')
    plt.legend()

    Cv_indx = np.zeros((ylen))
    plt.subplot(2,2,3)
    plt.title(r'Specific heat capacity, $C_v$')
    for i in range(len(L_arr)):
        #Cv_indx[i] = np.argmax(np.abs(np.gradient(Cv,T_arr,axis=1)))
        #Cv_Tc[i] = T_arr[Cv_indx[i]]
        plt.plot(T_arr,Cv[i], label='L=%i' % L_arr[i])
        #plt.plot(Cv_Tc[i], Cv_mean[Cv_indx[i]], '.', label=r'$T_c = %.2f$ ' % Cv_Tc[i])
    plt.ylabel(r'$C_v$')
    plt.xlabel('Temperature')
    plt.legend()

    chi_indx = np.zeros((ylen))
    plt.subplot(2,2,4)
    plt.title(r'Susceptibility, $\chi$')
    for i in range(len(L_arr)):
        #chi_indx[i] = np.argmax(np.abs(np.gradient(chi,T_arr,axis=1)))
        #chi_Tc[i] = T_arr[chi_indx[i]]
        plt.plot(T_arr,chi[i], label='L=%i' % L_arr[i])
        #plt.plot(chi_Tc[i], chi[chi_indx[i]], '.', label=r'$T_c = %.2f$ ' % chi_Tc[i])
    plt.ylabel(r'$\chi$')
    plt.xlabel('Temperature')
    plt.legend()

    plt.savefig('g.png')
    plt.show()
    #np.save('Tc.npy', np.array((M_Tc, Cv_Tc, chi_Tc)))




#compile_func()
#calc_func()
plot_func()
