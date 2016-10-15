.PHONY: all zero one two three clean

all: one zero two three
	echo "DONE!"

zero: zero.o
	./zero.o

one: one.o
	./one.o

two: two.o
	./two.o

three: three.o
	./three.o

zero.o: zero.cpp
	g++ --std=c++14 -o zero.o zero.cpp

one.o: one.cpp
	g++ --std=c++14 -o one.o one.cpp

two.o: two.cpp
	g++ --std=c++14 -o two.o two.cpp

three.o: three.cpp
	g++ --std=c++14 -o three.o three.cpp

clean:
	rm one.o zero.o two.o three.o
