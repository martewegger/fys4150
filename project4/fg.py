import numpy as np
from run import *
import matplotlib.pyplot as plt
from probability import *
from astropy import constants
plt.rcParams['font.size'] = 18


def Cv_func(E_mean, E_mean_sqrd, T):
    return 1/(T**2)*(E_mean_sqrd-E_mean**2)

def chi_func(M_mean, M_mean_sqrd, T):
    return 1/(T)*(M_mean_sqrd-M_mean**2)

def calc_func():
    #burn_in_no = np.loadtxt('burn_in_no_1e+07.txt')

    T0 = 2.1; T1 = 2.4
    dT = 0.005
    N = int(np.abs(T1-T0)//dT)
    T_arr = np.linspace(T0,T1,N+2)

    L_arr = np.array((40,60,80,100))
    burn_in_no = np.ones((len(L_arr),len(T_arr)))*1#2e5
    E_mean = np.zeros((len(L_arr),len(T_arr)))
    M_mean = np.zeros((len(L_arr),len(T_arr)))
    E_mean_sqrd = np.zeros((len(L_arr),len(T_arr)))
    M_mean_sqrd = np.zeros((len(L_arr),len(T_arr)))
    M_mean_abs = np.zeros((len(L_arr),len(T_arr)))
    N_cycles = 1e3
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
            E_mean[i,j] = np.mean(E)#expectation_func(E)
            M_mean[i,j] = np.mean(M)
            M_mean_abs = np.mean(np.abs(M))
            E_mean_sqrd[i,j] = np.mean(E**2)#expectation_func(E,squared=True)
            M_mean_sqrd[i,j] = np.mean(M**2)#expectation_func(M, squared=True, type='magnetisation')
    np.save('E_M_E2_M2_test.npy'% N_cycles, np.array((E_mean, M_mean,M_mean_abs,E_mean_sqrd, M_mean_sqrd)))


def plot_func():
    N_cycles = 5e5
    T0 = 2.1; T1 = 2.4
    dT = 0.005
    N = int(np.abs(T1-T0)//dT)
    T_arr = np.linspace(T0,T1,N+2)
    L_arr = np.array((40,60,80,100))
    E_mean, M_mean,M_mean_abs,E_mean_sqrd, M_mean_sqrd = np.load('E_M_E2_M2_test.npy')
    ylen, xlen = E_mean.shape

    Cv = Cv_func(E_mean, E_mean_sqrd, T_arr[np.newaxis])
    chi = chi_func(M_mean, M_mean_sqrd, T_arr[np.newaxis])

    L2 = L_arr*L_arr

    color = ['blue','orange','green','red']
    plt.figure(figsize=(10,10))
    plt.title(r'Energy, $\langle E \rangle$')
    for i in range(len(L_arr)):
        plt.plot(T_arr,E_mean[i]/L2[i],c=color[i], label='L=%i' % L_arr[i])
    plt.ylabel(r'$\langle E \rangle/L^2$')
    plt.xlabel('Temperature')
    plt.legend()
    #plt.savefig('energy.png')

    tol = 1e1  # Choose a tolerance
    M_indx = np.zeros((ylen))

    plt.figure(figsize=(10,10))
    plt.title(r'Magnetisation, $\langle |M| \rangle$')
    for i in range(len(L_arr)):
        plt.plot(T_arr,M_mean[i]/L2[i],c=color[i], label='L=%i' % L_arr[i])
    plt.ylabel(r'$\langle |M| \rangle/L^2$')
    plt.xlabel('Temperature')
    plt.legend()
    #plt.savefig('magnetisation.png')

    Cv_indx = np.zeros((ylen))
    Tc = np.zeros((ylen))
    plt.figure(figsize=(10,10))
    plt.title(r'Specific heat capacity, $C_v$')
    #Tc = np.ones((ylen))*2.3
    for i in range(len(L_arr)):
        Tc_indx = np.argmax(Cv[i])
        Tc[i] = T_arr[Tc_indx]
        plt.plot(T_arr,Cv[i]/L2[i],c=color[i], label='L=%i' % L_arr[i])
        plt.plot(Tc[i], Cv[i,Tc_indx]/L2[i], '.',c=color[i], label=r'$T_c = %.2f$ ' % Tc[i])
    plt.ylabel(r'$C_v/L^2$')
    plt.xlabel('Temperature')
    plt.legend()
    #plt.savefig('heat_capacity.png')

    chi_indx = np.zeros((ylen))
    plt.figure(figsize=(10,10))
    plt.title(r'Susceptibility, $\chi$')
    for i in range(len(L_arr)):
        plt.plot(T_arr,chi[i]/L2[i], c=color[i],label='L=%i' % L_arr[i])
    plt.ylabel(r'$\chi/L^2$')
    plt.xlabel('Temperature')
    plt.legend()

    #plt.savefig('susceptibility.png')
    #plt.show()

    Tc_file = open('Tc.txt', 'w')
    for i in range(len(Tc)):
        Tc_file.write('%10s \n' % Tc[i])
    Tc_file.close()
    #np.save('Tc.npy', np.array((M_Tc, Cv_Tc, chi_Tc)))

    plt.figure(figsize=(10,10))
    plt.title(r'$T_c$ comparison')
    Tc_L_infty = Tc-1/L_arr
    plt.plot(L_arr, Tc_L_infty,'x',c='r')
    plt.plot(L_arr, Tc_L_infty,c='blue')
    plt.axhline(2.269,c='green', label=r'Expected, $T_c= 2.269[k_B T/J]$')
    plt.xlabel('L')
    plt.ylabel('Temperature')
    plt.legend()
    #plt.savefig('Tc.png')
    plt.show()






#compile_func()
#calc_func()
plot_func()
