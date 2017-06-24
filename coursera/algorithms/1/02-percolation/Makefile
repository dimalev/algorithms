tools=../../tools
stdlib=${tools}/algs4.jar
checkAll=${tools}/check-all.sh

javaOpts=-cp ${stdlib}:.

.PHONY: check-all

check-all: *.class
	${checkAll} .

visualize: Percolation.class PercolationVisualizer.class
	java ${javaOpts} PercolationVisualizer tests/${TEST}

stats: PercolationStats.class
	java ${javaOpts} PercolationStats ${N} ${T}

%.class: %.java
	javac ${javaOpts} $<

clean:
	rm *.class
