import numpy as np
import os

def compile_func():
    cpp_codes = "main_2D.cpp PDE_2D.cpp"
    compiler_flags = "-larmadillo -O2"
    #compiler_flags= None
    executeable = "main_2D.out"
    os.system("echo compiling...")
    os.system(" ".join(["c++", "-o", executeable, cpp_codes]))

def run_func(T_end=0.1, dt=(0.1**2)/2, dxy=0.1,method="ForwardEuler", compile=False):
    if compile==True:
        compile_func()
    run = "./main_2D.out"
    os.system(" ".join([run, str(T_end), str(dt), str(dxy), method]))
if __name__ == '__main__':
    #compile_func()
    run_func(compile = True)
