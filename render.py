import sys
from functools import reduce
from collections import defaultdict
import matplotlib.pyplot as plt
import numpy as np

def average(lst):
    return reduce(lambda x, y: x + y, lst) / float(len(lst))

header = input().split(' ')

numbers = np.array([[float(num) for num in line.split(' ')] for line in sys.stdin])

time_by_thread = defaultdict(list)

for i in range(numbers.shape[0]):
    time_by_thread[numbers[i][0]].append([numbers[i][1], numbers[i][2]])

for threads in time_by_thread.keys():
    runtimes = np.array(time_by_thread[threads])
    plt.plot(runtimes[:, 0], runtimes[:, 1], label=str(threads))

plt.yscale('log')
plt.xscale('log')
plt.legend()
plt.savefig("stats.png")
