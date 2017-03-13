#!/bin/python3

[n, t] = list(map(int, input().strip().split()))

i = 1
total = 0
current = n
for c in map(int, input().strip().split()):
    if i < t:
        current -= c
        if current < 5:
            total += (n - current)
            current = n
    i += 1

print(total)
