---
layout: post
title:  "Building Solutions"
date:   2016-09-27 14:17:25 +0300
categories: environment
---

Main purpose of environment is allow me to write code, and all the other things happen by means of simple magic.

Under magic, I understand:

1. Compile Code with required options and capabilities.
2. Run Code against available tests according to specified limitations and report results.
3. Generate big, or compuationally complicated tests for stress testing.
4. Allow debugging of tests to find issues.
5. Test separate pieces of code.

To mitigate these requirements, I implemented [Makefile][test-cpp-makefile] (c++ in this example) and added emacs
support for running targets with shortcuts. For example `M+f5` runs compilation and tests, failing on first bad one.

Some parts of functionality is independent across languages, in which solution is implemented, like tests. Others - are
language dependant.

To start working on new solution, I:

1. Create new folder under the name of task,
2. Copy Makefiles from [test/][test-folder] which correspond to languages i wish to use,
3. Create test inputs/outputs,
4. Start wrting The Code in The Emacs!

### Managing Problem Limitations

All the algorithms have limitations - in memory, running time, and maybe others (like number of available threads,
maybe). This is *NOT* currently supported.

If solutions runs into infinite loop - make process just hangs up. I use `killall ./main.o`.

### Tests

Currently, I support only plain input and output. Tests are run when `output-xx.txt` exists. In this case, compiled
executable is run with corresponding `input-xx.txt` as input. Here `xx` MUST match.

If any test fails - make fails, with corresponding cerr displayed to debug solution. See language section for details on
how to add debugging to your solution. Only `cout` content is compared with given output.

*Note:* whitespaces metter. I use plain `diff`, to check if solution is ok, and to display differences.

### Test separate pieces of code

Not supported. One of the problems - is that solution MUST be bundled in single file, and i cannot easily spread it in
different files. This will make submission step more complicated.

One of ideas to support some `vial-xx.cpp` with `vial-xx-input-xx.cpp` and `vial-xx-output-xx.cpp` convention, and force
developers to manualy copy/paste required code into main solution.

Also it is maybe makes sense to create subdirectories with subprograms as separate problems... but still force to
copy/paste code which we need.

## Supported Languages

### C++

Solution is supposed to reside in single `main.cpp` file.

[Makefile][test-cpp-makefile] is supposed to do all the job.

During compilation, `ALGO_DEBUG` is defined. It can be used for debugging:

{% highlight cpp %}
#include <iostream>

int main() {
  int a, b;
  std::cin >> a >> b;
#ifdef ALGO_DEBUG
  std::cerr << "Read numbers: " << a << " " << b << std::endl;
#endif
  std::cout << (a + b) << std::endl;
  return 0;
}
{% endhighlight %}

In this scenario, I will dump read numbers into `cerr`, which is not used for comparision in tests. Also, testing
websites will not define `ALGO_DEBUG`, and output will never be shown up during real tests.

I should add assertions, to omit `#ifdef` wrapping.

### Java

Solution is supposed to reside in single `Solution.java` file.

[Makefile.java][test-java-makefile] is supposed to do all the job.

Debugging is not supported yet :(

### Erlang

There some solutions here and there, but no complete routine to work on such problems.

[solution-source]: {{ site.data.global.algo-github }}/tree/master/playlist-in-future/main.cpp
[test-cpp-makefile]: {{ site.data.global.algo-github }}/tree/master/test/Makefile
[test-java-makefile]: {{ site.data.global.algo-github }}/tree/master/test/Makefile.java
