Queues
======

Files
-----

* `Deque.java` - implements deque with few restrictions.

* `Permutation.java` - given words in stdin, and one command line parameter - limit, outputs
uniformly random no more then limit number words given in stdin without repeat.

* `RandomizedQueue.java` - implements queue with random elements retrieval.

* `tests/` - tests for RandomizedQueue from course.

Makefile
--------

* `test-deque` - runs deque unit tests

* `test-permutation N=10 TEST=tale.txt` - runs permutation test with `N` as a limit, and
`tests/${TEST}` for input file

* `test-queue` - runs randomized queue tests
