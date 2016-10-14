.PHONY: all zero one clean

all: one zero
	echo "DONE!"

zero: zero.o
	./zero.o

one: one.o
	./one.o

zero.o: zero.cpp
	g++ --std=c++14 -o zero.o zero.cpp

one.o: one.cpp
	g++ --std=c++14 -o one.o one.cpp

clean:
	rm one.o zero.o
