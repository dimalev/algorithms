---
layout: algorithm
title:  "Computational Geometry"
date:   2016-11-25 17:13:00 +0300
categories: ["algorithm"]
algorithm: ["geometry"]
implementations: ["cpp"]
---

Main concept we use in Computational Geometry is **vector**. Lets describe it by it's coordinates in
space `v = (v_x, v_y, v_z, ... )`. Usually we will work with two dimentinal vectors, rarely - with
three diemntional ones. But four-dimentional vectors can also be useful, and
[widely used in gaming][gamasutra-quaterions] for rotation and general object transformation.
These are [quaternions][quaternion-wolfram].

Many concepts are implemented in my [raytracer study][raytracer-github].

## Main operations

**Dot product** (or inner product) of vectors `v1` and `v2`:

```
dot(v1, v2) = v1_x * v2_x + v1_y + v2_y = |v1| * |v2| * cos(theta)
```

, where `theta` - is angle between `v1` and `v2`.

If one of vectors is unit vector (with length of `1`), then dot product is length of projection of other
vector onto unit one.

Hence, if it's value is equal to zero - then two vectors are perpendicular. On the other hand, if it's
value is equal to multiplication of both vectors sizes (`cos(theta) = 1`) then these vectors are collinear
(parallel).

**Cross product** works with tree-dimentional vectors, and in result it has a pseudo-vector, which is
perpendicular to the plain containing input vectors, and it's size equal to `|v1| * |v2| * sin(theta)`.
We explore it's third value for two-diemntional vectors:

```
cross(v1, v2) = v1_y * v2_x - v1_x * v2_y = |v1| * |v2| * sin(theta)
```

Because it has `sin(theta)` in it's value, we can use this formula to find out if `v2` is in clockwise (CW)
of conter-clockwise (CCW) direction from first vector `v1`.

Quick hack to know which sign is CW, I use simple example with two vectors `v1 = (1, 0)` and `v2 = (0, 1)`.
It is easy to see that first one - is horizontal, and second is vertical, and it is CCW from first one.

## Segment intersection search

Uses sweep-line (horizontal or vertical) to go through given set of line segments. When crossing some
segments, it stores them in ordered tree by coordinate (`x` for horizontal, and  `y` for vertical sweep-line).
This concept can be used in many algorithms. See [segment intersection][segment-intersection] for details
of algorithm and implementation.

## Convex hull

For a given bunch of points in space, one must find smallest possible convex hull to host all the points.

## Closest pair of points

For a given bunch of points in space, one must find two most close points.


[gamasutra-quaterions]: http://www.gamasutra.com/view/feature/131686/rotating_objects_using_quaternions.php
[quaternion-wolfram]: http://mathworld.wolfram.com/Quaternion.html
[raytracer-github]: {{ site.data.global.raytracer-github }}
[segment-intersection]: {{ site.data.global.algo-github }}/tree/master/segment-intersactions