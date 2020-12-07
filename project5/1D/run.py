import numpy as np
import os

def compile_func():
    cpp_codes = "main.cpp PDE.cpp"
    compiler_flags = "-larmadillo -O2"
    #compiler_flags= None
    executeable = "main.out"
    os.system("echo compiling...")
    os.system(" ".join(["c++", "-o", executeable, cpp_codes]))

def run_func(T_end=10, dt=(0.1**2)/2, dx=0.1,method="ForwardEuler", compile=False):
    if compile==True:
        compile_func()
    run = "./main.out"
    os.system(" ".join([run, str(T_end), str(dt), str(dx), method]))
if __name__ == '__main__':
    #compile_func()
    run_func(compile = True)
