import numpy as np
import matplotlib.pyplot as plt
filename =  'data_1000.txt'
x,gen,spec,LU,analytic=np.transpose(np.loadtxt(filename))
def plot(n):
    plt.figure(figsize=(6,6));plt.title('Numerical and analytic $u(x)$, n=%d'% n)
    plt.plot(x,spec,c='k',ls='solid',lw=0.8,label='Special $u(x)$')
    plt.plot(x,gen,c='k',ls='dotted',lw=0.8,label='General $u(x)$')
    plt.plot(x,analytic,c='k',ls='dashed',lw=0.8,label='Analytic $u(x)$')
    plt.plot(x,LU,c='k',ls='dashdot',lw=0.8,label='LU $u(x)$')
    plt.legend()
    plt.xlabel('$x$');plt.ylabel('$u(x)$')
    plt.savefig('comparison.png')
    plt.show()

N=1000
plot(N)


def plot_rel_errors():
    filename="log_errors.txt"
    n,logh,log_errors = np.transpose(np.loadtxt(filename))
    plt.figure(figsize=(6,6));plt.title('Max relative error, $\\varepsilon$')
    errors=10**(log_errors)
    plt.plot(logh,log_errors,c='k',lw=0.8)
    plt.xlabel('$log_{10}(h)$');plt.ylabel('$log_{10}(\\varepsilon$)')
    plt.savefig('max_errors.png')
    plt.show()
plot_rel_errors()

def error():
    rel_error=np.abs((LU-analytic)/analytic)
    plt.figure();#plt.title('')
    plt.plot(x,rel_error)
    plt.show()

#error()
