Tools
=====

There are two main thing here:

* `algs4.jar` - library with classes which must be used instead of collections and other
standard java classes

* `check-all.sh` - script to run code quality checks. it takes a directory with code as
sole parameter. No exclusions. So, one will have to manualy omit warnings from third-party
code.

Code Quality Checks
===================

Runs few checks against code and compiled assets, and reports any found issues. Purpose is
to keep these reports clean.

Checkstyle
----------

Simple program to go through `*.java` files and detect code style violtions. Reports
into standard output.

`checkstyle-coursera.xml` - is a description of rules used by course.

`supressions.xml` - file from checkstyle source code, used in `checkstyle-coursera.xml`.

PMD
---

Popular tool to find common bed practice patterns. Reports into file `pmd.html` written
in the location where `check-all.sh` was executed (not in `tools/` folder, not in source
code folder).

Findbugs
--------

Another tool similar to PMD, but analyses `*.class` bytecode. Also reports into standard
output.

`findbugs-coursera.xml` - is a description of rules used by course.