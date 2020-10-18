import matplotlib.pyplot as plt
import numpy as np
import os
plt.rcParams['font.size'] = 14

def compile():
    cpp_codes = "main.cpp class_code.cpp"
    compiler_flags = "-larmadillo -O2"
    executeable = "main.out"

    os.system("echo compiling...")
    os.system(" ".join(["c++", "-o", executeable, cpp_codes, compiler_flags]))


def run_func(v0, N):
    filename = "Tellus.txt"
    run = "./main.out"
    print('Running for x0, y0 = (1,0), vy0 = %f' % v0)
    os.system(" ".join([run, str(N), str(filename),str(v0)]))

#compile()
#run_func(v0=6.294737, N=1e5)
run_func(v0=8.8, N=1e5)

data1 = np.loadtxt("Tellus.txt") #read the positions from file

# The positions of the planets
earth_x     = data[:,0];    earth_y     = data[:,1]
"""
mercury_x   = data[:,2];    mercury_y   = data[:,3]
venus_x     = data[:,4];    venus_y     = data[:,5]
mars_x      = data[:,6];    mars_y      = data[:,7]
jupiter_x   = data[:,8];    jupiter_y   = data[:,9]
saturn_x    = data[:,10];   saturn_y    = data[:,11]
uranus_x    = data[:,12];   uranus_y    = data[:,13]
neptune_x   = data[:,14];   neptune_y   = data[:,15]
pluto_x     = data[:,16];   pluto_y     = data[:,17]
"""
sun_x       = 0;            sun_y       = 0

# Plot:
plt.figure(figsize=(6,6))
plt.plot(earth_x, earth_y, label="Earth orbit")
plt.plot(earth_x[-1], earth_y[-1], "o", label="Earth")
plt.plot(earth_x[0], earth_y[0], "o", label="Earth start")
"""
plt.plot(mercury_x, mercury_y, label="Mercury")
plt.plot(venus_x, venus_y, label="Venus")
plt.plot(mars_x, mars_y, label="Mars")
plt.plot(jupiter_x, jupiter_y, label="Jupiter")
plt.plot(saturn_x, saturn_y, label="Saturn")
plt.plot(uranus_x, uranus_y, label="Uranus")
plt.plot(neptune_x, neptune_y, label="Neptune")
plt.plot(pluto_x, pluto_y, label="Pluto")
"""
plt.plot(sun_x, sun_y, "o", c="yellow", label="Sun")
#plt.axis("equal")
#plt.xlim(-1.5,1.5)
#plt.ylim(-1.5,1.5)
plt.xlabel('X')
plt.ylabel('Y')
plt.legend(fontsize=16)
plt.title("Position of planets")
plt.show()
