tools=../../tools
stdlib=${tools}/algs4.jar
checkAll=${tools}/check-all.sh

javaOpts=-cp ${stdlib}:.

.PHONY: check-all

check-all: *.class
	${checkAll} .

board: Board.class
	java -ea ${javaOpts} Board

solver: Solver.class Board.class
	java -ea ${javaOpts} Solver ${TEST}

puzzle-checker: PuzzleChecker.class Solver.class Board.class
	java -ea ${javaOpts} PuzzleChecker tests/puzzle*.txt

%.class: %.java
	javac ${javaOpts} $<

clean:
	rm *.class
