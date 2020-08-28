import numpy as np

def u_func(x):
    return 1-(1-np.exp(-10))*x-np.exp(-10*x)


x=np.linspace(0,1,10)
y=u_func(x)

print(y)
