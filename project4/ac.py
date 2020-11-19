import numpy as np
import matplotlib.pyplot as plt
from run import run_func

def exact_2by2_func(T_arr):
    beta = 1/T_arr
    Z = 12 + 2*np.exp(8*beta) + 2*np.exp(-8*beta)
    M = (8*np.exp(8*beta) + 16)/Z
    E = 16/Z*(np.exp(-8*beta) - np.exp(8*beta))
    C_V = 256/(Z*T_arr**2)*(np.cosh(8*beta) - 4*np.sinh(8*beta)/Z)
    Chi = (32*np.exp(8*beta) + 32)/(Z*T_arr)
    return E, M, C_V, Chi

def numerical_2by2_func(T_arr):
    energies, magnetisation = ...
    E = np.mean(energies)
    E2 = np.mean(energies**2)
    M = np.mean(magnetisation)
    M2 = np.mean(magnetisation**2)
    C_V = (E2 - E**2)/T_arr
    Chi = (M2 - M**2)/T_arr
    return E, M, C_V, Chi

def plotter_2by2_func(T_arr):
    ex_E, ex_M, ex_C_V, ex_Chi = exact_2by2_func(T_arr)
    E, M, C_V, Chi = numerical_2by2_func(T_arr)

    plt.figure(figsize=(10,10))
    plt.subplot(2,2,1)
    plt.title(r"$\langle E \rangle$")
    plt.plot(T_arr,ex_E, label=r"Exact $\langle E\rangle$")
    plt.plot(T_arr,E, label=r"Numerical $\langle E\rangle$")
    plt.xlabel("E [J]")
    plt.legend()

    plt.subplot(2,2,2)
    plt.title(r"$\langle M \rangle$")
    plt.plot(T_arr,ex_M, label=r"Exact $\langle M\rangle$")
    plt.plot(T_arr,M, label=r"Numerical $\langle M\rangle$")
    plt.xlabel("Magnetisation")
    plt.legend()

    plt.subplot(2,2,3)
    plt.title(r"$C_V$")
    plt.plot(T_arr,ex_C_V, label=r"Exact $C_V$")
    plt.plot(T_arr,C_V, label=r"Numerical $C_V$")
    plt.xlabel("Heat capasity");plt.ylabel("Temperature [kT/J]")
    plt.legend()

    plt.subplot(2,2,4)
    plt.title(r"$\Chi$")
    plt.plot(T_arr,ex_Chi, label=r"Exact $\Chi$")
    plt.plot(T_arr,Chi, label=r"Numerical $\Chi$")
    plt.xlabel("Susceptebility");plt.ylabel("Temperature [kT/J]")
    plt.legend()
    plt.savefig("ac.png")
    plt.show()

if __name__ == "__main__":
    T_arr = np.linspace(2.1,2.4,7)
    plotter_2by2_func(T_arr)
