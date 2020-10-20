import numpy as np
import matplotlib.pyplot as plt
from run_Nbody import *

def test_func():
    T = 12
    dt = np.load('optimal_dt_Verlet.npy')
    filename = 'Nbody.txt'
    run_func(filename, dt, T_end=T)
    #sun_x, sun_y, earth_x, earth_y = np.transpose(np.loadtxt(filename))
    sun_x, sun_y, earth_x, earth_y, jupiter_x, jupiter_y = np.transpose(np.loadtxt(filename))
    plt.figure()
    plt.title('Test run of 3-body problem')
    plt.plot(sun_x, sun_y, label='Sun')
    plt.plot(sun_x[0], sun_y[0],'.', label='start')


    plt.plot(earth_x, earth_y, label='Earth')
    plt.plot(earth_x[0], earth_y[0],'.', label='start')
    plt.plot(jupiter_x, jupiter_y, label='Jupiter')
    plt.plot(jupiter_x[0], jupiter_y[0],'.', label='start')
    plt.legend()
    plt.savefig('3body.png')
    plt.show()

#compile_func()
test_func()
