import os
import sys
import matplotlib.pyplot as plt
import numpy as np
plt.rcParams['font.size'] = 16


rho_max = np.linspace(3,6,10)
acum_rel_err = np.zeros(len(rho_max))
lambda1 = np.zeros(len(rho_max))
lambda2 = np.zeros(len(rho_max))
lambda3 = np.zeros(len(rho_max))
lambda4 = np.zeros(len(rho_max))
cpp_codes = "main.cpp class_code.cpp"
compiler_flags = "-larmadillo -O2"
executeable = "main.out"
run = "./main.out"
lambda_list = np.array((3,7,11,15))

def find_rho_max(run=False):
    n=350
    if run==True:
        os.system("echo compiling...")
        os.system(" ".join(["c++", "-o", executeable, cpp_codes, compiler_flags]))
        for i in range(len(rho_max)):
            filename = "max_rel_err.txt"
            print('Running for rho_max= %f' % rho_max[i])
            os.system(" ".join([run, str(rho_max[i]), str(filename), str(n)]))

            data = np.array((np.loadtxt(filename)))
            lambda1[i] = data[0]
            lambda2[i] = data[1]
            lambda3[i] = data[2]
            lambda4[i] = data[3]
            acum_rel_err[i] = data[4]

    indx = np.argmin(acum_rel_err)
    plt.figure(); plt.title('Acumulative relative error as a function of $\\rho_{max}$')
    plt.plot(rho_max, acum_rel_err, c='k', lw=0.8,ls='solid')
    plt.plot(rho_max[indx], acum_rel_err[indx], 'ro', label='(%.2f, %.2f)' % (rho_max[indx],acum_rel_err[indx]))
    plt.xlabel('$\\rho_{max}$')
    plt.ylabel('Relative error')
    plt.legend(fontsize=16)
    plt.savefig('max_rel_err.png')
    #plt.show()

    plt.figure();plt.title('Relative error as a function of $\\rho_{max}$')

    indx1 = np.argmin(lambda1)
    plt.plot(rho_max,lambda1, 'r', label='$\\lambda_1 = 3$')
    plt.plot(rho_max[indx1], lambda1[indx1], 'ro', label='(%.2f, %.1e)' % (rho_max[indx1],lambda1[indx1]))

    indx2 = np.argmin(lambda2)
    plt.plot(rho_max,lambda2,'b', label='$\\lambda_2 = 5$')
    plt.plot(rho_max[indx2], lambda2[indx2], 'bo', label='(%.2f, %.1e)' % (rho_max[indx2],lambda2[indx2]))

    indx3 = np.argmin(lambda3)
    plt.plot(rho_max,lambda3,'g', label='$\\lambda_3 = 11$')
    plt.plot(rho_max[indx3], lambda3[indx3], 'go', label='(%.2f, %.1e)' % (rho_max[indx3],lambda3[indx3]))

    indx4 = np.argmin(lambda4)
    plt.plot(rho_max,lambda4, 'm',label='$\\lambda_4 = 15$')
    plt.plot(rho_max[indx4], lambda4[indx4], 'mo', label='(%.2f, %.1e)' % (rho_max[indx4],lambda4[indx4]))
    plt.xlabel('$\\rho_{max}$')
    plt.ylabel('Relative error')
    plt.legend()
    plt.savefig('rel_err_lmbda.png')

    os.system("rm max_rel_err.txt") # removing the txt file created.
    final = np.array((rho_max[indx1], rho_max[indx2], rho_max[indx3], rho_max[indx4], rho_max[indx])) #index tilsvarer rhomax for acc, de andre tilsvarer rhomax for lam1, lam2 osv.
    np.save('rho_values.npy', final)
#find_rho_max(run=True) #hash ut denne

def find_optimal_N(run_cpp = False): #finne optal n for hver lam.
    omega_r = 0
    plt.figure();plt.title('Relative error as a function of matrix size, $N$')
    rho_vals = np.load('rho_values.npy') #dette er rhomax verdiier for ulike lam og acc
    filename = "n_analysis.txt"
    if run_cpp==True:
        os.system("echo compiling...")
        os.system(" ".join(["c++", "-o", executeable, cpp_codes, compiler_flags]))

    #err_list = []
    err = 1
    tol = 1e-4
    n_max = 0
    for i in range(len(rho_vals)-1):  # sjekker ikke for gjennomsnitts verdien
        print("\n")
        print("--------------------------------------------------------")
        n_list = []
        err_list = []
        n_min = 450
        n = n_min #teste for disse
        err = 1
        rho_max = rho_vals[i] #finne optimal n for hver rhomax
        #n_list[i] (_rhomax1) = [] #lage en liste for hver rho-max
        os.system("echo evaluating rho_max= %f for lambda%d" % (rho_max, i+1))
        while err >tol:
            n_list.append(n)
            os.system("echo running for n= %d" % n)
            os.system(" ".join([run, str(rho_max), str(filename), str(n), str(i), str(omega_r)]))
            err = 0

            err = np.loadtxt(filename) #cpp leser error for gitt/hver n. den skal være under 1e-4. ta var på for å plotte? må appende. lage en liste, for å lagre disse verdiene i.!
            err_list.append(err)
            print("error= ", err)
            #må lagre n-verdier.
            #liste.append(n) #en liste jeg lager)
            n += 10
            if n>=650:
                print(" No success, but break cause n too big..")
                break
            if n > n_max:
                n_max = n
        print("Possible success at n = %d" % (n-10))
        print("relative error= %g" %  err)

        plt.plot(n_list,err_list, '.', label='$\\lambda_%d$' % (i+1))
    plt.plot([n_min,n_max], [1e-4,1e-4], c='k', label='tolerance')
    plt.xlabel('$N$')
    plt.ylabel('Relative error')
    plt.legend(fontsize=16)
    plt.savefig('n_analysis.png')

    os.system(" ".join(["rm", str(filename)]))


#find_optimal_N(run_cpp=True)


def vary_w_r():
    n=350
    colors = np.array(('r', 'b', 'g', 'orange'))
    plt.figure(figsize=(10,10));plt.title('Relative error for different $\\omega_r$')
    w_r = np.array((0.01, 0.5, 1, 5))
    os.system("echo compiling...")
    os.system(" ".join(["c++", "-o", executeable, cpp_codes, compiler_flags]))
    filename = 'omega_test.txt'
    rho_vals = np.load('rho_values.npy')
    os.system("echo running omega_r analysis")
    for i in range(len(lambda_list)):
        rho_max = rho_vals[i]
        err_list = []
        for j in range(len(w_r)):
            os.system(" ".join([run, str(rho_max), str(filename), str(n), str(i), str(w_r[j])]))
            err_list.append(np.loadtxt(filename))
        plt.plot(w_r,err_list, c = colors[i], label='$\\lambda_%d$' % (i+1))
        plt.plot(w_r,err_list, c = colors[i])
    plt.xlabel('$\\omega_r$')
    plt.ylabel('Relative error')
    plt.legend(fontsize=16)
    plt.savefig('test_w_r.png')
    #os.system(" ".join(["rm", str(filename)]))
vary_w_r()
