.PHONY: clean-player

clean-player:
	rm -f player

player: player.cpp
	g++ --std=c++14 -O2 player.cpp -o player
