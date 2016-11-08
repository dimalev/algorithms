Problem
-------

[Longest Palindromic Subsequence](https://www.hackerrank.com/contests/hourrank-13/challenges/longest-palindromic-subsequence) original from Hacker Rank.

For short: given a string `S`, and a delta `k` (integer) - you should count how many distinct chars can be
insterted to make longest palindromic subsequence of `S` at least `k` symbols longer?

Limitations: at most 10 queries per test file. Length of string `N` is at most 3000, and `0 <= k <= 50`.

Sample
------

Input:

```
3
1 1
a
3 2
aab
3 0
aba
```

Output:

```
2
1
104
```

For first test case - we can add `a` before first (and alone) char, or after this - length will be one
symbol longer.

For second - the only way to make sequence longer - is to add `b` in the beggining. Sequence will become
4 symbols long (`baab`) wich is 2 symbols longer then it was (`aa`).

For third - we can add any symbols in beginning, end, and in between any symbol.

Tip
---

Sequence must not be consecutive.

Solution
--------

First of all, if `k > 2` - the answer is always zero.

Solution is about taking each space where char can be inserted, and going through all the chars which it will
make pair with. Separate case is when the inserted char will happen to take place in the middle of new
sequence.

For each such a new case - the length of the longest palindromic sequence can be calculated in `O(1)` time,
if we have values for functions wich calculate:

1. Longest common sequence for "wings" of `S`: `[1..i]` and `[j..N]`, 
2. Longest palidromic subsequence of `S` in `[i..j]` substring.

These two function happen to be recursive, and thier values can be stored in matrices of `NxN` size. Values
for these matrices can be calculated in `O(N^2)`.