import numpy as np
import matplotlib.pyplot as plt

def chi_square_func(calc, ana_func, t_1, t_2, dt):
    n_t, n_x = calc.shape
    x = np.linspace(0,1,nx)
    ana = ana_func(x, np.array((t_1,t_2)))
    time = np.linspace(0,(n_t-1)*dt,n_t)
    xs = np.array((calc[np.argmin(np.abs(time - t_1))],calc[np.argmin(np.abs(time - t_2))]))
    var = np.std(xs,axis=1)**2
    chi_squared = np.sum(((ana - calc)**2/var**2),axis=1)
    return chi_squared

def analytic_sol_func(x,t):
    k = np.arange(1,1001,1)
    t = t[:,np.newaxis, np.newaxis]
    x = x[np.newaxis,:,np.newaxis]
    k = k[np.newaxis,np.newaxis,:]
    u = np.sum(2*(-1)**k*np.sin(x*k*np.pi)*np.exp(-t*(k*np.pi)**2), axis=2)[:,:,np.newaxis] + x
    print(u[:,:,0])
    return u[:,:,0]

analytic_sol_func(np.linspace(0,1,100),np.array((0.1,0.2)))
