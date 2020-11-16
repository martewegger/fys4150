import numpy as np
import matplotlib.pyplot as plt
def Frequency_func(energies):
    import numpy as np
    import matplotlib.pyplot as plt

    max = np.max(abs(energies))
    min = -max
    values = np.arange(min,max+1,4)
    freq = np.zeros(len(values))
    for i,value in enumerate(values):
        freq[i] = len(np.where(energies==value)[0])
    prob = freq/len(energies)

    plt.figure(figsize=(8,6))
    plt.rcParams.update({'font.size': 14})
    plt.title("Probability Distribution $P(E)$", fontsize=20)
    plt.grid(axis="y",ls="--",zorder=0)
    plt.bar(values, prob, tick_label=values, width=2.5, zorder=2)
    plt.xlabel("Energies", fontsize=16)
    # plt.savefig("Probability.png")

    return values, prob

a = np.array((-24,-20,-12,-4,-4,-4,0,0,4,4,4,4,8,12,16,20,24))
b = Frequency_func(a)

plt.show()
