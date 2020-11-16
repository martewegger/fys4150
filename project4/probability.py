import numpy as np
import matplotlib.pyplot as plt
def Frequency_func(energies, in_label):
    max_ = np.max(energies)
    min_ = np.min(energies)
    values = np.arange(min_,max_+1,4)
    freq = np.zeros(len(values))
    for i,value in enumerate(values):
        freq[i] = len(np.where(energies==value)[0])
    prob = freq/len(energies)
    expected = np.sum(values*prob)

    plt.rcParams.update({'font.size': 14})
    plt.title("Probability Distribution $P(E)$", fontsize=20)
    plt.grid(axis="y",ls="--",zorder=0)
    plt.bar(values, prob, width=2.5, zorder=2, label=in_label)
    plt.axvline(expected,c="r",ls="--", label="Expectation value")
    plt.legend(fontsize=16)
    plt.xlabel("Energies", fontsize=16)

    return values, prob
