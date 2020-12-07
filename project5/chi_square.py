import numpy as np
import matplotlib.pyplot as plt

def chi_square_func(calc, ana_func, ts, dt, method, plot=False):
    n_t, n_x = calc.shape
    x = np.linspace(0,1,n_x)
    ana = ana_func(x, ts)
    time = np.linspace(0,(n_t-1)*dt,n_t)
    xs = np.zeros((len(ts),n_x))
    dx = 1/(n_x-1)

    for i,t in enumerate(ts):
        xs[i] = calc[np.argmin(np.abs(time - t))]

    var = (np.std(xs,axis=1)**2)[:,np.newaxis]
    chi_squared = np.sum(((ana[:,1:] - xs[:,1:])**2/ana[:,1:]**2),axis=1)/n_x

    if plot == True:
        plt.rcParams.update({'font.size': 14})
        plt.figure()
        plt.title(r"%s dx $=%g$" % (method, dx), fontsize=20)
        for i,(y,t,a) in enumerate(zip(xs,ts,ana)):
            plt.plot(x, y,label=r"$u^{num}(x,%g)$, $\chi^2=%gf$" % (t,chi_squared[i]))
            plt.plot(x, a,"--",label=r"$u^{ana}(x,%g)$" % t)
        plt.xlabel("x");plt.ylabel("u(x)")
        plt.legend(fontsize=12)
        plt.savefig("comparison%s.png" % method)
        plt.close()

    return chi_squared

def analytic_sol_func(x,t):
    k = np.arange(1,10001,1)

    t = t[:,np.newaxis, np.newaxis]
    x = x[np.newaxis,:,np.newaxis]
    k = k[np.newaxis,np.newaxis,:]

    u = np.sum(2*(-1)**k*np.sin(x*k*np.pi)*np.exp(-t*(k*np.pi)**2)/(k*np.pi), axis=2)[:,:,np.newaxis] + x
    return u[:,:,0]
