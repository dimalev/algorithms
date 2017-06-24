tools=../../tools
stdlib=${tools}/algs4.jar
checkAll=${tools}/check-all.sh

javaOpts=-cp ${stdlib}:.

.PHONY: bench gen-tests check-all all

all: check-all gen-tests bench
	echo "Done"

check-all: *.class
	${checkAll} .

gen-tests: GenRandomTest.class
	java ${javaOpts} GenRandomTest 100000 900 100 true tests/input-1.txt tests/output-1.txt && \
  java ${javaOpts} GenRandomTest 10000000 10000 1000 true tests/input-2.txt tests/output-2.txt

bench: Benchmark.class UF.class QuickFind.class QuickUnion.class QuickUnionImproved.class
	java ${javaOpts} Benchmark

%.class: %.java
	javac ${javaOpts} $<

clean:
	rm *.class
