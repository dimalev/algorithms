.PHONY: clean-world

clean-world:
	rm -f world

world: world.cpp
	g++ --std=c++14 -O2 world.cpp -o world
