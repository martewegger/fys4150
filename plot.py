import numpy as np
import matplotlib.pyplot as plt

def plot(filename):
    x,u,u_analytic=np.transpose(np.loadtxt(filename))
    plt.figure(figsize=(6,6));plt.title('Comparing numerical and analytic $u(x)$')
    plt.plot(x,u,c='k',ls='solid',lw=0.8,label='Numerical $u(x)$')
    plt.plot(x,u_analytic,c='k',ls='dashed',lw=0.8,label='Analytic $u(x)$')
    plt.legend()
    plt.xlabel('$x$');plt.ylabel('$u(x)$')
    plt.show()


plot("data.txt")
