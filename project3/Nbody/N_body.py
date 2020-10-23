import numpy as np
import matplotlib.pyplot as plt
from run_Nbody import *
plt.rcParams['font.size'] = 20

def Whole_system():
    T = 250
    filename = 'Nbody.txt'
    run_func(filename, T_end=T)

    data = np.transpose(np.loadtxt(filename))
    print(data.shape)
    os.system(" ".join(["rm", filename]))
    plt.figure(figsize=(9,18))
    name = ['Sun','Venus', 'Earth', 'Mars', 'Jupiter', 'Saturn', 'Uranus', 'Neptune', 'Pluto']
    plt.subplot(2,1,1);plt.title('Orbits of all major objects')
    for i in range(int(data.shape[0]/2)):
        x = data[int(2*i)]
        y = data[int(2*i+1)]
        plt.plot(x,y, label=name[i])
        plt.plot(x[-1],y[-1],'.')
    plt.ylabel('AU')
    plt.legend(loc='upper right')
    plt.subplot(2,1,2);plt.title('Orbits of the innermost objects')
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
#compile_func()
#vary_Mjup()

def Mercury_func():
    T = 100

    filename = 'Nbody.txt'
    run_func(filename, dt=3e-4, T_end=T)
    data = np.transpose(np.loadtxt(filename))
    print(data.shape)
    name = ['Sun', 'Mercury']
    os.system(" ".join(["rm", filename]))

    tol = 5e-5
    dist = 0.3075
    x,y = data[2:]

    r = np.sqrt(x**2+y**2)
    upper = dist+tol
    indx= np.array(np.where(r<upper))[0]


    indx_final = []
    for i in range(len(indx)-1):
        if np.abs(indx[i]-indx[i+1])>=2:
            indx_final.append(indx[i])
    indx_final = np.array((indx_final))

    x_p = x[indx_final]
    y_p = y[indx_final]

    theta_p = np.abs(np.arctan(y_p[-1]/x_p[-1]));
    print('theta_p = ', theta_p*(180/np.pi), 'degrees')#*3600)
    print('theta_p = ', theta_p*(180/np.pi)*3600, 'arcsecs')
    plt.figure(figsize = (12,18))
    plt.subplot(2,1,1)
    plt.title('Mercury´s first and last orbit \n over a 100 year period')
    plt.plot(x[indx_final[0]:indx_final[1]+3],y[indx_final[0]:indx_final[1]+3], label='First orbit')
    plt.plot(x[indx_final[-2]:indx_final[-1]+3], y[indx_final[-2]:indx_final[-1]+3], label='Last orbit')
    plt.xlabel('AU')
    plt.ylabel('AU')
    plt.legend()

    x0 = [0,x[0]]
    y0 = [0,y[0]]
    x1 = [0,x[indx_final[-1]]]
    y1 = [0,y[indx_final[-1]]]
    plt.subplot(2,1,2)
    plt.title('Precession of Mercury´s orbit')
    plt.plot(x0, y0, label='Original perihelion')
    plt.plot(x[indx_final[0]:indx_final[1]+3],y[indx_final[0]:indx_final[1]+3], label='First orbit')
    plt.plot(x[indx_final[-2]:indx_final[-1]+3], y[indx_final[-2]:indx_final[-1]+3], label='Last orbit')
    plt.plot(x1, y1, label='last perihelion')
    plt.xlabel('AU')
    plt.ylabel('AU')
    plt.legend()
    plt.xlim(0.28, 0.32)
    plt.ylim(-0.04, 0.04)
    plt.savefig('mercury.png')
    #plt.show()
compile_func()
Mercury_func()
