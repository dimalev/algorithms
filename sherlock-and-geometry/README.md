Problem
-------

[Sherlock and Geometry](https://www.hackerrank.com/challenges/sherlock-and-geometry)
from hackerrank.

Given a circle by it's center coordinates `x_c`, `y_c` and radius `R`, and triangle by coordinates
of it's vertices `x_i`, `y_i`, one should print `YES` if they intersect, and `NO` if they don't.

No triangles are degenerate (i.e. area is 0).

There are `T` test cases per one file.

Limits
------

`1 <= T <= 30000`
`1 <= R <= 2000`
`-2000 <= x_c, y_c <= 2000`
`-5000 <= x_i, y_i <= 5000`

Sample
------

Input:

```
2
0 0 10
10 0
15 0
15 5
0 0 10
0 0
5 0
5 5
```

Output:

```
YES
NO
```

Solution
--------

Basing on [simple geometry](http://dimalev.github.io/algorithms/algorithm/computational-geometry.html),
we can perform number of tests to see if there is an intersection.

First go through all the triangle vertices to see if any of them lie on the circle. If there are any -
output `YES`. Meanwhile we can test if all the verticies lie inside or outside the circle.

If all the vertices are inside - we can output `NO`. If there are some inside and some outside - we
output `YES`. If all the verticies are outside - we do some math to find out if there is a segment,
which intersects with the circle.

This can be done by first finding distance from center of the circle to the line containing segment.
This is done by finding cross product of segment, and circle center divided by segment length:

```
H = cross(AB, AC) / |AB|
```

, where `A` - is one side of segment, `B` - other one, and `C` - is circle radius. If this value is
greater then radius - we output `NO`.

Otherwise we try to find points of intersection of circle and segment. We don't need exect coordinates.
If we know how are are they from point `A` - that would be enough. For this we can find distance from
`A` to perpendicular falling from circle center onto line containing segment using dot product:

```
|AC'| = dot(AB, AC) / |AB|
```

, here `|AC'|` is not exectly right notation, because it will be signed. This means that it will have
negative value if `C'` is situated on opposite side from `A` then `B`, which for us will mean it's
outside of the segment.

Let `L` - be horizontal displacement of points of intersection from `C'`:

```
L^2 + H^2 = R^2
```

then, we can find distance of intersection points from `A` by:

```
I_1 = |AC'| + L
I_2 = |AC'| - L
```

In case if any of these values is in range `[0..|AB|]` - we output `YES`, otherwise `NO`.