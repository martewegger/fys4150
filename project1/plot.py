import numpy as np
import matplotlib.pyplot as plt
filename =  'data_1000.txt'
x,gen,spec,LU,analytic=np.transpose(np.loadtxt(filename))
def plot(n):
    filename1 =  'data_10.txt'
    filename2 =  'data_100.txt'
    filename3 =  'data_1000.txt'
    x1,gen1,spec,LU,analytic1=np.transpose(np.loadtxt(filename1))
    gen1 = np.append(np.array((0)),gen1)
    gen1 = np.append(gen1,np.array((0)))
    x1 = np.append(np.array((0)),x1)
    x1 = np.append(x1,np.array((1)))

    x2,gen2,spec,LU,analytic2=np.transpose(np.loadtxt(filename2))
    x3,gen3,spec,LU,analytic3=np.transpose(np.loadtxt(filename3))
    plt.figure(figsize=(15,6));
    #plt.title('General algorithm and analytic solutions, $u(x)$, n=%d'% n)
    plt.subplot(1,3,1);plt.title('n=10')
    #plt.plot(x,spec,c='k',ls='dotted',lw=0.8,label='Special $u(x)$')
    plt.plot(x1,gen1,c='red',ls='dashed',lw=0.9,label='General $u(x)$')
    plt.plot(x3,analytic3,c='k',ls='solid',lw=0.9,label='Analytic $u(x)$')
    plt.legend()
    plt.xlabel('$x$');plt.ylabel('$v(x)$')

    plt.subplot(1,3,2);plt.title('n=100')
    plt.plot(x2,gen2,c='red',ls='dashed',lw=0.9,label='General $u(x)$')
    plt.plot(x3,analytic3,c='k',ls='solid',lw=0.9,label='Analytic $u(x)$')
    plt.legend()
    plt.xlabel('$x$');plt.ylabel('$v(x)$')

    plt.subplot(1,3,3);plt.title('n=1000')
    plt.plot(x3,gen3,c='red',ls='dashed',lw=0.9,label='General $u(x)$')
    plt.plot(x3,analytic3,c='k',ls='solid',lw=0.9,label='Analytic $u(x)$')

    #plt.plot(x,LU,c='k',ls='dashdot',lw=0.8,label='LU $u(x)$')
    plt.legend()
    plt.xlabel('$x$');plt.ylabel('$v(x)$')
    plt.savefig('b.png')
    #plt.show()

N=1000
#plot(N)


def plot_rel_errors():
    filename="log_errors.txt"
    n,logh,log_errors = np.transpose(np.loadtxt(filename))
    plt.figure(figsize=(6,6));plt.title('Max relative error, $\\varepsilon$')
    errors=10**(log_errors)
    plt.plot(logh,log_errors,c='k',lw=0.8)
    plt.xlabel('$log_{10}(h)$');plt.ylabel('$log_{10}(\\varepsilon$)')
    plt.savefig('max_errors.png')
    plt.show()
#plot_rel_errors()

def error():
    rel_error=np.abs((LU-analytic)/analytic)
    plt.figure();#plt.title('')
    plt.plot(x,rel_error)
    plt.show()

#error()

def c():
    filename = 'CPU_times.txt'
    gen, spec, LU = np.transpose(np.loadtxt(filename))
    n = np.array((1,2,3,4,5,6))
    n = np.array((1e1,1e2,1e3,1e4,1e5,1e6))

    plt.figure(figsize=(6,6));
    plt.title('CPU times for the special, general and LU algorithms')
    plt.plot(n,spec, c = 'k', lw = 0.8, ls = 'solid', label = 'Special algo')
    plt.plot(n,gen, c = 'k', lw = 0.8, ls = 'dashed', label = 'General algo')
    plt.plot(n[:4],LU[:4], c = 'k', lw = 0.8, ls = 'dotted', label = 'LU algo')
    plt.xlabel('Number of steps')
    plt.ylabel('CPU time [ms]')
    plt.xscale('log')
    plt.yscale('log')
    plt.legend()

    plt.savefig('c.png')

c()
