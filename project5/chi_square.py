import numpy as np
import matplotlib.pyplot as plt

def chi_square_func(calc, ana_func, ts, dt, plot=False):
    n_t, n_x = calc.shape
    x = np.linspace(0,1,n_x)
    ana = ana_func(x, ts)
    time = np.linspace(0,(n_t-1)*dt,n_t)
    xs = np.zeros((len(ts),n_x))

    for i,t in enumerate(ts):
        xs[i] = calc[np.argmin(np.abs(time - t))]

    var = (np.std(xs,axis=1)**2)[:,np.newaxis]
    chi_squared = np.sum(((ana - xs)**2/var**2),axis=1)

    if plot == True:
        plt.figure()
        for i,(y,t,a) in enumerate(zip(xs,ts,ana)):
            plt.plot(x, y,label=r"calculated, t = %g, $\chi^2=%.3f$" % (t,chi_squared[i]))
            plt.plot(x, a,"--",label="analytic, t = %g" % t)
        plt.xlabel("x")
        plt.legend()
        plt.savefig("comparison.png")
        plt.close()

    return chi_squared

def analytic_sol_func(x,t):
    k = np.arange(1,10001,1)
    
    t = t[:,np.newaxis, np.newaxis]
    x = x[np.newaxis,:,np.newaxis]
    k = k[np.newaxis,np.newaxis,:]

    u = np.sum(2*(-1)**k*np.sin(x*k*np.pi)*np.exp(-t*(k*np.pi)**2)/(k*np.pi), axis=2)[:,:,np.newaxis] + x
    return u[:,:,0]

if __name__ == "__main__":
    t_array = np.array((0.02,0.05,0.1))
    dt = 0.01/2
    calc = np.loadtxt("data_1D.txt")
    print(chi_square_func(calc, analytic_sol_func, t_array, dt, plot=True))
