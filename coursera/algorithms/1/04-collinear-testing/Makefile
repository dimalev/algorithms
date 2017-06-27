tools=../../tools
stdlib=${tools}/algs4.jar
checkAll=${tools}/check-all.sh

javaOpts=-cp ${stdlib}:.

.PHONY: check-all

check-all: *.class
	${checkAll} .

test-deque: Deque.class
	java ${javaOpts} Deque

test-queue: RandomizedQueue.class
	java ${javaOpts} RandomizedQueue

test-permutation: Permutation.class RandomizedQueue.class
	java ${javaOpts} Permutation ${N} < tests/${TEST}

%.class: %.java
	javac ${javaOpts} $<

clean:
	rm *.class
