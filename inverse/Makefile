start: main.o run

main.o: main.cpp
	g++ -O2 -fno-stack-limit -x c++ -std=c++11 main.cpp -o main.o

run: main.o
	./main.o

