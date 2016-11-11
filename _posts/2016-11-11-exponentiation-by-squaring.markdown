---
layout: algorithm
title:  "Exponentiation by squaring"
date:   2016-11-11 22:37:00 +0300
categories: ["algorithm"]
algorithm: ["binary"]
implementations: ["cpp"]
---

When we need to find `N`th power of some number `M`, we may choose to do this by incrementing power by 1.
This means to have some `R` initialized to 1, and multiply it by `M` for `N` times. This yeilds `O(N)`
time.

We can observe that for some `R` which is `M^k`, we can get `M^(2 * k)` by simply multiply `R` with itself.
This means, we can manipulate power of `R` in two ways - multiply it by two, or add one.

So, if we represent `N` in binary format - we can multiply `R` with itself `log(N)` times, and multiply by
`M` when we have `1` in binary representation.

For example, to find `M = 3` and `N = 10`, we can have:

```
N = 1010

R0 = 1
R1 = R0 * R0 * M = 3
R2 = R2 * R2 = 9
R3 = R3 * R3 * M = 243
R4 = R4 * R4 = 59049
```

See [Antipalindromic Strings][antipalindromic-strings] task for example.

There are other patterns with reuse of already available results to ease computations.

[antipalindromic-strings]: {{ site.data.global.algo-github }}/tree/master/antipalindromic-strings/main.cpp
