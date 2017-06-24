Percolation
===========

Given NxN grid, where each cell can be open or closed, with top side as a source of liquid,
it is required to find out:

# which cells are filled with liquid? if two cells are open, and share one side, and one of
them is filled (connected to top side, or connected to another open filled cell) - it is
filled.

# if grid percolates, i.e. there is at least one filled cell in the bottom row?

Having such a percolation class, it is required to find out how many cells must be open,
before grid start percolate. Few statistics must be run against this class.

Files
=====

Solutions:

* `Percolation.java` - simulates percolation, using `WeightedQuickUnionUF` from `algs4.jar`
library. Use `PercolationVisualizer.java` to see how it works. Single parameter - is the
name of file with test.

* `PercolationStats.java` - runs statistical tests against percolation simulation.

* `PercolationVisualizer.java` - tool to debug Percolation solution.

* `InteractivePercolationVisualizer.java` - another tool, which i did not use...

Tests:

* `tests/input*.txt` - files which can be used as inputs for `PercolationVisualizer.java`

* `tests/input*.png` - proper visualization results.

Makefile Targets
================

* `check-all` to run tests of the code. Ignore `PercolationVisualizer.java` errors - it's
third party code.

* `visualize TEST=input1.txt` runs single visualization with `TEST` file from `tests/`
folder as input.

* `stats N=200 T=100` runs statistics against `NxN` grid, `T` times. Outputs results into
standard output.
