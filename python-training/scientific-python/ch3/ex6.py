#!/usr/bin/python3

def my_symmetric_difference(A, B):
    return (A - B).union(B - A)

def test_diff(A, B):
    my_diff = my_symmetric_difference(A, B)
    built_diff = A.symmetric_difference(B)
    print("my:\t{}\nbuitin:\t{}".format(my_diff, built_diff))

tests = [
    [{1,2,3}, {4,5,6}],
    [{2,3,4}, {2,3,4}],
    [{1,2,3}, {2,3,4}]
    ]

for [A, B] in tests:
    test_diff(A, B)
    print("\n")
