Problem
-------

[Sorted Subsegments](https://www.hackerrank.com/contests/101hack38/challenges/sorted-subsegments)
from hackerrank.

Given an array `A` of elements `[a_0, a_1, .., a_(n-1)]` and `q` queries to sort elements in range
`[s_i .. e_i]`, `0 <= i < q`, find value of an element which will appear on `k`th position.

Limitations
-----------

`1 <= n, q <= 75000`
`0 <= k < n`
`-10^9 <= a_i <= 10^9`
`0 <= s_i <= e_i < n`

Solution
--------

First observation is that even having each value eligible to be in range `-10^9 .. 10^9`, there
are at most 75000 values in total. So, first of all - we rename our values into serial number.
For example, if we have sequence of values `20, -78, 302, -78, 12`, we will create a vocabulary
`-78, 12, 20, 302`, and transform sequence into `2, 0, 3, 0, 1`.

We will find out if our answer is less or equal given number. This will allow us to find answer
using binary search by vocabulary. To do this - we will sort another array of elements which is
built of results of predicate funtion `p(a_i) = a_i >= a_k`, where `a_k` is a value we test our
result against. In this case, sorting segment `[s_i .. e_i]` is performed by counting number of
`1`s and `0`s, and then putting them in proper order.

We can store data about `0`s and `1`s in tree structure - segment tree. Each node in this tree
represents some segment of an array (`s` and `e`), and number of `0`s and `1`s in it. If
segment is sorted - it's a leaf of a tree. In such a tree we can very efficiantly perform
storting. For this, we find out how many `0`s and `1`s fall into our segment, remove and alter
segments which intersects with our new segement, and then, add it to the tree as a leaf.