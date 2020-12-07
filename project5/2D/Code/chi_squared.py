import numpy as np

def chi_squared_func(computed, analytic):
    return np.sum((computed[1:-1,1:-1]-analytic[1:-1,1:-1])**2/analytic[1:-1,1:-1])
