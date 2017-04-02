#!/usr/bin/python3

from sys import argv
from numpy import random

# generate test with huge number in output

def print_input():
    print("5000 2047")
    output = [(i * 100, random.randint(100, 1000000)) for i in range(100, 5100)]
    print("\n".join(["{} {}".format(x, w) for (x, w) in output]))

def print_output():
    throw("I don't know :(")

def print_use():
    print("pass 'in' to generate input, or 'out' to generate output")

if argv[1] == "in":
    print_input()
elif argv[1] == "out":
    print_output()
else:
    print_use()
