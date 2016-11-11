Problem
-------

[Anti-Palindromic Strings](https://www.hackerrank.com/challenges/antipalindromic-strings)
from hackerrank.

You are given alphabet containing `M` letters. The task is to count
how many strings of length `N` are there which do not havepalindromic
substrings longer then one letter in length.

The answer must be reported modulo `10^9 + 7`.

Limitations
-----------

Number of test cases per test file `1 <= T <= 10^5`.

`1 <= N, M <= 10^9`

Solution
--------

We must not have two same letters coming one after another (e.g. `EE`
or `AA`) and we must not have same letters surrounding any other
letter (`AZA` or `WCW`). Fulfilling these two constraints is enough
to be eligible for count string.

This effectively means, that we can have any letter on first place
(which is `M` variants), on the second place - we can have any letter,
but not the same as on first place (`M - 1` variants), and on any other
place, we can have any letter, which is not equal to first and second
letter preceding current one (`M - 2` variants). Which yeilds:

```
Answer = M * (M - 1) * (M - 2) ^ (N - 2)
```

for `N > 1`, and

```
Answer = M
```

for `N = 1`.

The most interesting part of this task - is calculate `(M - 2) ^ (N - 2)`
efficiantly, and not exceed numeric limits.
