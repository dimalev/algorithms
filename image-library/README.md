Problem
-------

Implement Image manipulation library.

How to run
----------

Just run `make` in the root. This will build `tester` program out of `main.cpp` file
and run it.

Architecture
------------

All `Image`s are represented as `std::vector`s of `Col`s, which in turn are
`std::vector`s of `Cell` implemented as `std::array`. These containers are used for
ease of understanding, and to reuse there copy and move capabilities (Not Implmemented).

`Col` class has specialization for single dimention. To refer to it's cell - member
type `cel_t` can be used.

Input and output is gathered inside `image_io.hpp` file. It is based on `std::string`
manipulation.

Image processing functions implmemented in `image_manip.hpp` file. It can take advantage
of `image_part.hpp` and `col_part.hpp` tool classes which represent rectangular view of
some piece of source `Image`. `*Avarage` family (small family) of calls is used in
`Scale` function. Also, it is planed to put multiplication of `ImagePart` with given
two dimentional array of weights - to be used for convolve operation. Also, `*Avarage`
can be implemented by forging special case of multiplication.

Testing and Usage
-----------------

Sample usage, as well as testing is presented in `main.cpp` file.

`test_harness.cpp` contains some special functions and macroses for testing.

Issues
------

`Scale` function requires non-`const` input parameter.