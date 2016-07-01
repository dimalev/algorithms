# task

there is a line of 0s and 1s. we must find minimal count of breaks to generate
lines of 0s, or, if line contains 1 - it must be the only one in it, and must
be in center:

```0001000```

# sample

```01001001000000001001001000```

with 7 breaks:

```010 (1) 010 (2) 010 (3) 00000 (4) 00100 (5) 1 (6) 00100 (7) 0```

# input

n and m ( 1 <= n <= m <= 10^9, n <= 10^6), where n - number of 1s, m - size of
line

n lines with indexes of 1s.

# output

minimal number of breaks

# solution remarks

for each 1 i count number of 0s after it before next 1. this number - is
maximum number of 0s which will surround it after break.

for each incoming new 1 - i generate numbers of white cells i can dedicate to
next 1, together with number of breaks i will need for this:

```{ min=3, max=5, count=4 }```

will mean that from 3 to 5 white cells can be generated with 4 breaks. with
this information from previous break - i can generate new information for next
one.

we start with tuples:

```
00100100

{ min=2, max=2, count=0 } # 2 zeros can be generated without introducing break

{ min=0, max=1, count=1 } # with one break we can generate one or no 0s
```

we must remember that we can reuse bigger breaks (if we can introduce 7 zeros
with 5 breaks, then 3 breaks we can introduce with 5 + 1 break, even if
iterative generation gives more breaks. this happens).

for last break we must remember that ```min=0``` does not require extra break,
so result must be ```count-1``` in that case.