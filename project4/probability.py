import numpy as np
import matplotlib.pyplot as plt

def expectation_func(values_inn, squared=False):
    max_ = np.max(values_inn)
    min_ = np.min(values_inn)
    if type=='magnetisation':
        values = np.arange(min_,max_+1,2)
    else:
        values = np.arange(min_,max_+1,4)
    freq = np.zeros(len(values))
    for i,value in enumerate(values):
        freq[i] = len(np.where(values_inn==value)[0])
    prob = freq/len(values_inn)
    if squared==False:
        expected = np.sum(values*prob)
    else:
        expected = np.sum(values**2*prob)
    return expected

def probability_func(energies, in_label, plot=True):
    max_ = np.max(energies)
    min_ = np.min(energies)
    values = np.arange(min_,max_+1,4)
    freq = np.zeros(len(values))
    for i,value in enumerate(values):
        freq[i] = len(np.where(energies==value)[0])
    prob = freq/len(energies)
    expected = np.sum(values*prob)
    if plot==True:
        plt.rcParams.update({'font.size': 14})
        plt.title("Probability Distribution $P(E)$", fontsize=20)
        plt.grid(axis="y",ls="--",zorder=0)
        plt.bar(values, prob, width=2.5, zorder=2, label=in_label)
        plt.axvline(expected,c="r",ls="--", label=r'$\langle E\rangle$ = %.2f' % expected)
        plt.legend(fontsize=16)
        plt.xlabel("Energies", fontsize=16)
        #plt.show()


    return values, prob, expected
