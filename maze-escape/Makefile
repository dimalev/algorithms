.PHONY: test units run

test: units run

overlord: overlord.cpp
	g++ --std=c++14 -o overlord overlord.cpp

heraclius: heraclius.cpp
	g++ --std=c++14 -o heraclius heraclius.cpp

heraclius-units.o: heraclius.cpp
	g++ -DALGO_DEBUG -DUNITS -O2 -fno-stack-limit -x c++ -std=c++11 heraclius.cpp -o heraclius-units.o

run: overlord heraclius
	./overlord ./heraclius maze.txt

units: heraclius-units.o
	./heraclius-units.o < fixtures.txt > output.txt 2> log.txt && \
  echo -e "\nInput:" && cat fixtures.txt && \
  echo -e "\nOutput:" && cat output.txt && \
  echo -e "\n\nLog:\n" && cat log.txt && \
  echo -e "\nDiff:" && diff -w output.txt units-output.txt && echo -e "\nUnit Tests OK"
