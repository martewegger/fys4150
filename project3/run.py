import numpy as np
import os

def compile_func():
    cpp_codes = "main.cpp class_code.cpp"
    compiler_flags = "-larmadillo -O2"
    executeable = "main.out"
    os.system("echo compiling...")
    os.system(" ".join(["c++", "-o", executeable, cpp_codes, compiler_flags]))

def run_func(filename="outfile.txt", vy0=np.load("optimal_v0.npy"),vx0=0, dt=np.load("optimal_dt_ForwardEuler.npy"), T_end=1.1, method = "ForwardEuler", beta=2, compile=False):
    if compile==True:
        compile_func()
    run = "./main.out"
    os.system(" ".join([run, filename, str(vx0), str(vy0), str(dt), str(T_end), method, str(beta)]))

if __name__ == '__main__':
    compile_func()
    #run_func(compile = True)
