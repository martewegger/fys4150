import numpy as np
import matplotlib.pyplot as plt

def chi_square_func(calc, ana, t_1, t_2, dt):
    n_t, n_x = calc.shape
    time = np.linspace(0,(n_t-1)*dt,n_t)
    xs = np.array((calc[np.argmin(np.abs(time - t_1)],calc[np.argmin(np.abs(time - t_2)]))
    var = np.std(xs,axis=1)**2
    chi_squared = np.sum((ana - calc)**2/var**2),axis=1)
    return chi_squared
