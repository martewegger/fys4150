import numpy as np
import matplotlib.pyplot as plt
from run_Nbody import *
plt.rcParams['font.size'] = 20

def Whole_system():
    T = 250
    dt = np.load('optimal_dt_Verlet.npy')
    filename = 'Nbody.txt'
    run_func(filename, dt, T_end=T)

    data = np.transpose(np.loadtxt(filename))
    print(data.shape)
    os.system(" ".join(["rm", filename]))
    plt.figure(figsize=(18,9))
    name = ['Sun','Venus', 'Earth', 'Mars', 'Jupiter', 'Saturn', 'Uranus', 'Neptune', 'Pluto']
    plt.subplot(1,2,1);plt.title('Orbits of all major objects')
    for i in range(int(data.shape[0]/2)):
        x = data[int(2*i)]
        y = data[int(2*i+1)]
        plt.plot(x,y, label=name[i])
        plt.plot(x[-1],y[-1],'.')
    plt.xlabel('AU')
    plt.ylabel('AU')
    plt.legend(loc='upper right')
    plt.subplot(1,2,2);plt.title('Orbits of the innermost objects')
    for i in range(5):
        x = data[int(2*i)]
        y = data[int(2*i+1)]
        plt.plot(x,y, label=name[i])
        plt.plot(x[-1],y[-1],'.')
    plt.xlabel('AU')
    plt.ylabel('AU')
    plt.legend(loc='upper right')
    plt.savefig('orbits.png')
    plt.show()
#compile_func()
#Whole_system()

def vary_Mjup():
    T = 15
    dt = np.load('optimal_dt_Verlet.npy')
    filename = 'Nbody.txt'
    run_func(filename, dt, T_end=T)
    data = np.transpose(np.loadtxt(filename))
    name = ['Sun', 'Earth', 'Jupiter']
    os.system(" ".join(["rm", filename]))
    plt.figure(figsize=(9,9))
    plt.title('Jupiters mass$ = 1M_{Jup}$')
    for i in range(int(data.shape[0]/2)):
        x = data[int(2*i)]
        y = data[int(2*i+1)]
        plt.plot(x,y, label=name[i])
        plt.plot(x[-1],y[-1],'.')
    plt.xlabel('AU')
    plt.ylabel('AU')
    plt.legend(loc='upper right')
    plt.savefig('1mjup.png')
compile_func()
vary_Mjup()
