.PHONY: say-*

bench: Benchmark.class QuickFind.class UF.class
	java Benchmark

%.class: %.java
	javac $<

clean:
	rm *.class
