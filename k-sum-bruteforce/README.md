Problem
-------

Given `n` integers, find a subset of size `k` which will have sum of `sum`.

Algorithm must be brute-force. Analyse running time of algorithm.

Input
-----

First line contains `k`, second line - `sum`, all the rest - numbers from array.

Output
------

Any subset from given array of size `k` with sum of `sum`, in any order.

Solution
--------

Recursive function takes an array to operate on, number of elements to seek, target
sum, and limit in given array which must not be overlapped.

This allows to seek for each element on possition `i` by breaking array into two
parts - on the left from `i`th element we will seek for elements with higher index,
on the right - with lower index.

Such an approach allows us to iterate over all possible combinations of array
elements, and find required match.

Running time
------------

Because we go through all possible combinations of array elements - the running time
will be

```
              n!
C_n_k = -------------
         k! (n - k)!
```