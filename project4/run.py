import numpy as np
import os

def compile_func():
    cpp_codes = "main.cpp Ising2D.cpp"
    #compiler_flags = "-larmadillo -O2"
    compiler_flags= None
    executeable = "main.out"
    os.system("echo compiling...")
    os.system(" ".join(["c++", "-o", executeable, cpp_codes]))

def run_func(temp=1, len=20, initial_state="random",MC_cycles=1e2, compile=False):
    if compile==True:
        compile_func()
    run = "./main.out"
    os.system(" ".join([run, str(temp), str(len), str(initial_state), str(MC_cycles)]))

if __name__ == '__main__':
    #compile_func()
    run_func(compile = True)
