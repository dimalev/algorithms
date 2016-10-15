.PHONY: all zero one two three four five six clean

all: one zero two three four five
	echo "DONE!"

zero: zero.o
	./zero.o

one: one.o
	./one.o

two: two.o
	./two.o

three: three.o
	./three.o

four: four.o
	./four.o

five: five.o
	./five.o

six: six.o
	./six.o

zero.o: zero.cpp
	g++ --std=c++14 -o zero.o zero.cpp

one.o: one.cpp
	g++ --std=c++14 -o one.o one.cpp
two.o: two.cpp
	g++ --std=c++14 -o two.o two.cpp

three.o: three.cpp
	g++ --std=c++14 -o three.o three.cpp

four.o: four.cpp
	g++ --std=c++14 -o four.o four.cpp

five.o: five.cpp
	g++ --std=c++14 -o five.o five.cpp

six.o: six.cpp
	g++ --std=c++14 -o six.o six.cpp

clean:
	rm *.o
