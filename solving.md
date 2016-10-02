---
layout: page
title:  "Solving"
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

For C++ first two steps can be executed by running `./new-problem.sh ${PROBLEM_NAME}`. It also contains special
prototype file `prototype.cpp` which includes `debug.cpp` with definitions of assertions. More on this later.

### Managing Problem Limitations

All the algorithms have limitations - in memory, running time, and maybe others (like number of available threads,
maybe). This is *NOT* currently supported.

If solutions runs into infinite loop - make process just hangs up. I use `killall ./main.o`.

### Tests

Currently, I support only plain input and output. Tests are run when `output-xx.txt` exists. In this case, compiled
executable is run with corresponding `input-xx.txt` as input. Here `xx` MUST match.

If any test fails - make fails, with corresponding cerr displayed to debug solution. See language section for details on
how to add debugging to your solution. Only `cout` content is compared with given output.

*Note:* whitespaces metter. Specially - new line in the end. I use plain `diff`, to check if solution is ok,
and to display differences. So, if output seems to be the same - check if there are extra new lines in output
file, or if you did not miss new line in your own output.

### Test separate pieces of code

Not supported. One of the problems - is that solution MUST be bundled in single file, and i cannot easily spread it in
different files. This will make submission step more complicated.

One of ideas to support some `vial-xx.cpp` with `vial-xx-input-xx.cpp` and `vial-xx-output-xx.cpp` convention, and force
developers to manualy copy/paste required code into main solution.

Also it is maybe makes sense to create subdirectories with subprograms as separate problems... but still force to
copy/paste code which we need. On the other hand - it allows to create separate bundle with tests and macroses
wich allow debug (specialized `TRACE` statements).

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

In this scenario, I will dump read numbers into `std::cerr`, which is not used for comparision in tests. Also, testing
websites will not define `ALGO_DEBUG`, and output will never be shown up during real tests.

Some traces are available as well. Former code could be rewritten like this:

{% highlight cpp linenos %}
#include <iostream>

#ifdef ALGO_DEBUG
#include "../test/debug.cpp"
#else
#define TRACE(message)
#define TRACE_LINE(message)
#define ASSERT(expr)
#endif

int main() {
  int a, b;
  std::cin >> a >> b;
  TRACE_LINE("Read numbers: " << a << " " << b);
  std::cout << (a + b) << std::endl;
  return 0;
}
{% endhighlight %}

Header with multiple macro definitions first includes main debug functionality. If you put your solution in
sub-dirrectory - don't forget to change `debug.cpp` include location. `#else` part will be executed during
real solution testing, and evaluate to nothing therefor.

`TRACE` will output into `std::cerr` whatever you pass into it, so use `<<`. `TRACE_LINE` from example is same
as `TRACE` but adds `<< std::endl` to the end.

`ASSERT` statement is simplest testing tool used in many applications. It takes input and tests it using
`if(...)` statement. If parameters evaluate to `false` - it's formula is reported into `std::cerr` with line
where check if executed:

{% highlight cpp linenos %}
TRACE_LINE("Start");
int a = 100;
ASSERT(a == 12);
TRACE_LINE("End");
{% endhighlight %}

<pre>
Start
(AE)
(AE)	a == 12 FAILED!
(AE)	line: 3
(AE)
End
</pre>

`(AE)` prefix is added for easier handling in other software (who knows, maybe it will be good some day). It
supposed to mean `A`ssertion `E`rror. Assertion definition is inspired by "Game Engine Architecture" book.

*Remember!* never to put any logic inside traces or assertions - for they are not executed during real
solution testing. This is common rule, so make sure you remember it!

In case if more functions will be added (arrays output, matrix dump, other), they MUST be added to `#else` part to be substituted during real testing to empty statements.

### Java

Solution is supposed to reside in single `Solution.java` file.

[Makefile.java][test-java-makefile] is supposed to do all the job.

Debugging is not supported yet :(

### Erlang

There some solutions here and there, but no complete routine to work on such problems.

[solution-source]: {{ site.data.global.algo-github }}/tree/master/playlist-in-future/main.cpp
[test-cpp-makefile]: {{ site.data.global.algo-github }}/tree/master/test/Makefile
[test-java-makefile]: {{ site.data.global.algo-github }}/tree/master/test/Makefile.java
