tools=../../tools
stdlib=${tools}/algs4.jar
checkAll=${tools}/check-all.sh

javaOpts=-cp ${stdlib}:.

.PHONY: check-all

check-all: *.class
	${checkAll} .

point-set: PointSET.class
	java -ea ${javaOpts} PointSET

kd-tree: KdTreeVisualizer.class KdTree.class
	java -ea ${javaOpts} KdTree

visual: KdTreeVisualizer.class KdTree.class
	java ${javaOpts} KdTreeVisualizer

search: RangeSearchVisualizer.class KdTree.class
	java ${javaOpts} RangeSearchVisualizer ${TEST}

near: NearestNeighborVisualizer.class KdTree.class
	java ${javaOpts} NearestNeighborVisualizer ${TEST}

%.class: %.java
	javac ${javaOpts} $<

clean:
	rm *.class
