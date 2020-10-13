import os
import sys
import matplotlib.pyplot as plt
import numpy as np
plt.rcParams['font.size'] = 16
def circle():

    theta =  linspace(0,2*np.pi, N)
    return np.sin(theta)**2 + np.cos(theta)**2

pos = circle()



n = 10
v0_array = np.linspace(6.3,6.7,n)# AU/yr
cpp_codes = "main.cpp class_code.cpp"
compiler_flags = "-larmadillo -O2"
executeable = "main.out"
run = "./main.out"

os.system("echo compiling...")
os.system(" ".join(["c++", "-o", executeable, cpp_codes, compiler_flags]))
N =1e5
rel_err =np.zeros(n)
for i in range(len(v0_array)):
    filename = "orbit.txt"
    print('Running for x0, y0 = (1,0), vy0 = %f' % v0_array[i])
    os.system(" ".join([run, str(N) str(v0_array[i]), str(filename)])
    data = np.array((np.loadtxt(filename)))
    x, y = data
    rel_err[i] = np.sum((x**2+y**2) - r)

plt.figure(figsize = (7,7))
plt.title('Acumulative relative error for orbit')
plt.plot(v0_array, rel_err)
plt.savefig('find_v0')
