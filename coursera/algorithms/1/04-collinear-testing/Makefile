tools=../../tools
stdlib=${tools}/algs4.jar
checkAll=${tools}/check-all.sh

javaOpts=-cp ${stdlib}:.

.PHONY: check-all

check-all: *.class
	${checkAll} .

point: Point.class
	java ${javaOpts} Point

brute: BruteCollinearPoints.class LineSegment.class Point.class
	java ${javaOpts} BruteCollinearPoints ${TEST}

fast: FastCollinearPoints.class LineSegment.class Point.class
	java ${javaOpts} FastCollinearPoints ${TEST}

old-fast: OldFastCollinearPoints.class LineSegment.class Point.class
	java ${javaOpts} OldFastCollinearPoints ${TEST}

%.class: %.java
	javac ${javaOpts} $<

clean:
	rm *.class
