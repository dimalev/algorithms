# task

given N numbers Ai, and K, find A(i + 1) <= K which will have GCD > 1 with other Ai.

# sample

input:

```
3 5
2 6 4
```

output:

```
4
```

# solution

seek all unique dividers of first number, and filter ones that do not divide any of
the rest of the numbers. go through each of found numbers and check biggest number
not bigger then K which is divided by each divider. one of the numbers - is result.

**Note** seek dividers of first number up to ```sqrt(first)```, otherwise you may get
time out.