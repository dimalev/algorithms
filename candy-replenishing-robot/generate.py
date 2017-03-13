#!/usr/bin/python3

import time
import random

test_index = 2
n = 100
t = 100

random.seed(time.time())

with open("input-{}.txt".format(test_index), "w") as input_file:
    with open("output-{}.txt".format(test_index), "w") as output_file:
        input_file.write("{} {}\n".format(n, t))
        current = n
        total = 0
        takes = []
        for i in range(0, t):
            c = random.randint(1, current)
            current -= c
            if current < 5:
                total += (n - current)
                current = n
            takes.append(c)
        input_file.write(" ".join(map(str, takes)) + "\n")
        output_file.write(str(total) + "\n")
