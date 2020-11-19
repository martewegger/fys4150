from run import *
import numpy as np
import matplotlib.pyplot as plt
plt.rcParams['font.size'] = 14

def find_burn_N_func():
    N_list = [1e5, 2e5, 3e5,4e5,5e5]
    N_list=np.linspace(5e5,2e6,5)
    T=2.4
    L = 100
    results = np.zeros((len(N_list)))
    #file = open('burn_in_no_final.txt', 'w')
    file = open('burn_in_no_final.txt', 'w')
    a=0
    for i,N in enumerate(N_list):
        a+=1
        print(a,"/", len(N_list), end = "\r")
        run_func(temp = T, len = L, initial_state="random", MC_cycles= N)
        energies = np.transpose(np.loadtxt("Energy.txt"))
        median = np.median(energies)
        sigma=np.std(energies[np.where(energies<=median)[0][0]:])
        indx = np.where(energies<=median+sigma)[0][0]
        results[i] = indx+1
        file.write('%10s \n' % results[i])
    print(results)
    file.close()
N_list = [1e5, 3e5, 5e5, 8e5,1e6,1.5e6]

#compile_func()
#find_burn_N_func()


def plot_burn_in_no():
    T = 2.4
    L = 100
    N_arr = [1e5, 3e5, 5e5, 8e5,1e6,1.5e6]
    N_arr = [1e5, 2e5, 3e5,4e5,5e5]
    N_arr=np.linspace(5e5,2e6,5)
    data = np.loadtxt('burn_in_no_final.txt')
    plt.figure(figsize=(10,10))
    plt.plot(N_arr,data, label='L=%i, T=%.2f' % (L, T))
    plt.xlabel('# of Monte Carlo cycles')
    plt.ylabel('Relative # of burn cycles needed, #/N')
    plt.legend()
    plt.savefig('burn_in.png')
    plt.show()

plot_burn_in_no()
