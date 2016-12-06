Problem
-------

[Alyona and Flowers][http://codeforces.com/problemset/problem/740/B] from codeforces.

Given array of `n` integers, and `m` subarrays, one must select some of subarrays, so
that summ of corresponding elements in array was maximum.

Limits
------

`1 <= n, m <= 100`

Solution
--------

We can calculate array of summs `S` from element `1` till `k` in source array `A`.
Then, we can calculate summ of elements for given subarray `[i..j]` by finding
difference  of `S[j]` and `S[i - 1]`.

For each subarray - we will account only those subarrays which have positive summ.