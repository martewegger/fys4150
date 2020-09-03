import numpy as np
import matplotlib.pyplot as plt

def plot(filename,n):
    x,gen,spec,u_analytic=np.transpose(np.loadtxt(filename))
    plt.figure(figsize=(6,6));plt.title('Special algo and analytic $u(x)$, n=%i'% n)
    plt.plot(x,spec,c='k',ls='solid',lw=0.8,label='Special $u(x)$')
    plt.plot(x,gen,c='k',ls='dotted',lw=0.8,label='General $u(x)$')
    plt.plot(x,u_analytic,c='k',ls='dashed',lw=0.8,label='Analytic $u(x)$')
    plt.legend()
    plt.xlabel('$x$');plt.ylabel('$u(x)$')
    plt.savefig('%i.png' % n)
    plt.show()

n=10
plot("data_%i.txt" % n, n)
