.PHONY: run

run: tester
	./tester

tester: main.cpp image.hpp col.hpp image_part.hpp col_part.hpp image_io.hpp image_manip.hpp
	g++ --std=c++14 -o tester main.cpp image.hpp col.hpp image_part.hpp col_part.hpp image_manip.hpp image_io.hpp
