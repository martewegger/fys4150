import numpy as np
dx = 0.1
x0 = 0
x1 = 1
N = int((x1-x0)/dx+1)
x = np.linspace(x0,x1,N)
print(x)
