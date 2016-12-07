Problem
-------

[Building a List][https://www.hackerrank.com/challenges/building-a-list] from hackerrank.

Given sets of letters, one must produce in alphabetical order all the combinations of these letters.

Limits
------

`1 <= T <= 50` - number of tests
`1 <= N <= 16` - number of letters

Solution
--------

Just generating all the combinations using binary representation, and then sorting is enough.

There can be up to `2 ^ 16 = 65536` combinations.

In my solution I've used recursive generation of combinations, basing on prefix.