Problem
-------

From Hackerrank [Digital Camera Autodetect: Day or Night](https://www.hackerrank.com/challenges/digital-camera-day-or-night).

Determine if image shows daytime or nighttime.

Input
-----

Grid of pixel data. Each channel (Red, Green, Blue) seperated by comma, each pixel in single row is seperated
by space, each row is seperated by new line.

Sample
------

```
0,0,200 0,0,10 10,0,0
90,90,50 90,90,10 255,255,255
100,100,88 80,80,80 15,75,255
```

Solution
--------

This task is a good place to try mathematical libraries available in any language.

`convert.py` takes single argument - image path, and outputs it's contents according to the input format.
See `images/` for sample images, and `image-data/` for converted counterparts. For example:

```
./convert.py images/day-1.jpg >> image-data/day-1.txt
```

To run algorithm:

```
cat image-data/day-1.txt | python3 main.py
```

Solution is based on converting RGB data into grayscale (just avarage of all three channels), and taking mean
value of colors. If it's over some threshold - image is a day, otherwise - night.

