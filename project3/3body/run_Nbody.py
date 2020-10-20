import numpy as np
import os

def compile_func():
    cpp_codes = "main.cpp class_code.cpp"
    compiler_flags = "-larmadillo -O2"
    executeable = "main.out"
    os.system("echo compiling...")
    os.system(" ".join(["c++", "-o", executeable, cpp_codes, compiler_flags]))

def run_func(filename="outfile.txt", dt=np.load("optimal_dt_Verlet.npy"), T_end=1.1, beta=2, compile=False):
    if compile==True:
        compile_func()
    run = "./main.out"
    os.system(" ".join([run, filename, str(dt), str(T_end), str(beta)]))
