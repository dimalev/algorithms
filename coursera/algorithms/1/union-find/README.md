Union Find
----------

Allows connecting pairs of nodes, and test if there exists a path for two given nodes. See `UF.java` interface.

To run benchmark use:

```
make gen-tests bench
```

This will generate medium and big tests, and run implementations on these.

Files
-----

Implementations:

* `UF.java` - main interface for different algorithm implementations,
* `QuickFind.java` - simplest implementation with fastest connectivity check, but slow union.
* `QuickUnion.java` - improved union, but slover find.
* `QuickUnionImproved.java` - more improvements on union.

Testing:

* `Benchmark.java` - run basic algorithms benchmark
* `GenRandomTest.java` - generate random connectivity test
* `tests/` - tests to run for algorithms