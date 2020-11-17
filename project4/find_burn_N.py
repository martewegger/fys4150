from run import *
import numpy as np
import matplotlib.pyplot as plt
plt.rcParams['font.size'] = 14

def find_burn_N_func(N_cycles):
    T_arr = np.arange(2,2.3+0.05,0.05)
    L_arr = np.array((40,60,80,100))
    results = np.zeros((len(L_arr), len(T_arr)))
    file = open('burn_in_no_%.e.txt'% N_cycles, 'w')
    a=0
    for i, L in enumerate(L_arr):
        for j, T in enumerate(T_arr):
            a+=1
            print(a,"/",len(T_arr)*len(L_arr), end = "\r")
            run_func(temp = T, len = L, initial_state="random", MC_cycles= N_cycles)
            energies = np.transpose(np.loadtxt("Energy.txt"))
            median = np.median(energies)
            indx = np.where(energies==median)[0][0]
            results[i,j] = indx+1
            file.write('%10s' % results[i,j])
            file.write("   ")
        file.write('\n')
    print(results)
    file.close()
N_list = [5e5,8e5,9e5,1e6,2e6,3e6,5e6,1e7]
#compile_func()
#find_burn_N_func(N_cycles= 5e6)


def plot_burn_in_no():
    T_arr = np.arange(2,2.3+0.05,0.05)
    L_arr = np.array((40,60,80,100))
    N_arr = [5e5,8e5,9e5,1e6,2e6,3e6,5e6,1e7]
    data = np.zeros((len(N_arr), len(L_arr), len(T_arr)))
    for i in range(len(N_arr)):
        data[i] = np.loadtxt('burn_in_no_%.e.txt'% N_arr[i])
    plt.figure(figsize=(10,10))
    for j in range(len(L_arr)):
        for k in range(len(T_arr)):
            plt.plot(N_arr,data[:,j,k]/N_arr, label='L=%i, T=%.2f' % (L_arr[j], T_arr[k]))
    plt.xlabel('# of Monte Carlo cycles')
    plt.ylabel('Relative # of burn cycles needed, #/N')
    plt.legend()
    plt.savefig('burn_in.png')
    plt.show()

plot_burn_in_no()
