#!/usr/bin/python3

from sys import argv

# generate test with huge number in output

def print_input():
    print("5000 1")
    for i in range(4999):
        print("{} 1000000".format(1000000 - i))
    print("4999 1")

def print_output():
    bottom = 1000000 - 4999
    sum = 0
    for i in range(4999):
        sum += 1000000 * (bottom - i)
    print(sum)

def print_use():
    print("pass 'in' to generate input, or 'out' to generate output")

if argv[1] == "in":
    print_input()
elif argv[1] == "out":
    print_output()
else:
    print_use()
