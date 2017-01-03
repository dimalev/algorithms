Problem
-------

You are develpoing navigator voice alerts. You must inform driver about approaching to a turn.
You want to inform his as close to the corner as possible. There are `N` prerecorded distances
`d_i` available. Each is played `t_i` time. For each of these phrases - navigator must add
words "after" and "meters turn right" with the constant time duration `T`. You must find
minimal distance to the turn where you can start playing the alert. If there are several 
alerts possible to play on the same minimal distance - the one with the minimal index must be
selected. The speed of the driver is `V`. Numeration of prerecorded distances starts from one.

Limitaions
----------

All values are not more then `1000`, and all floats are given with 3 digits after decimal
point. Output must have 5 precision digits.

Input
-----

```
L T
N
d_1 t_1
...
d_N t_N
```

Sample
------

Input:

```
30 5.000
2
200 0.400
178 3.111
```

Output:

```
362.00000 1
```

Options:

For first option we must start playing it at minimum before 200 meters, to play alert - we will need
5.4 seconds, driver will make 162m. So we must start from 362m.

For second option - we must start before 178m, playing will take 8.111s, hence - 421.33000 meters.

So, we pick first option.

Solution
--------

Just go through all the values and calculate `d_i + V * (T + t_i)`, and select first minimal.