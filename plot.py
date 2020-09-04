import numpy as np
import matplotlib.pyplot as plt
filename =  'data_10.txt'
x,gen,spec,LU,analytic=np.transpose(np.loadtxt(filename))
def plot(n):
    plt.figure(figsize=(6,6));plt.title('Special algo and analytic $u(x)$, n=%d'% n)
    #plt.plot(x,spec,c='k',ls='solid',lw=0.8,label='Special $u(x)$')
    plt.plot(x,gen,c='k',ls='dotted',lw=0.8,label='General $u(x)$')
    #plt.plot(x,analytic,c='k',ls='dashed',lw=0.8,label='Analytic $u(x)$')
    #plt.plot(x,LU,c='k',ls='dashdot',lw=0.8,label='LU $u(x)$')
    plt.legend()
    plt.xlabel('$x$');plt.ylabel('$u(x)$')
    plt.savefig('%d.png' % n)
    plt.show()

N=10
#plot(N)


def plot_rel_errors():
    filename="log_errors.txt"
    n,logh,log_errors = np.transpose(np.loadtxt(filename))
    plt.figure(figsize=(6,6));plt.title('Max relative error')
    errors=10**(log_errors)
    plt.plot(n,errors)
    plt.show()
plot_rel_errors()
