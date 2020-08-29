import numpy as np
import matplotlib.pyplot as plt

def plot(filename):
    data=np.loadtxt(filename)
    plt.plot(data[:,0], data[:,1])
    print("x = ", data[:,0])
    print("u = ", data[:,1])
    plt.show()


plot("data.txt")
