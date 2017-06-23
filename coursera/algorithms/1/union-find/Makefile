.PHONY: bench gen-tests

gen-tests: GenRandomTest.class
	java GenRandomTest 100000 900 100 true tests/input-1.txt tests/output-1.txt && \
  java GenRandomTest 10000000 10000 1000 true tests/input-2.txt tests/output-2.txt

bench: Benchmark.class UF.class QuickFind.class QuickUnion.class QuickUnionImproved.class
	java Benchmark

%.class: %.java
	javac $<

clean:
	rm *.class
