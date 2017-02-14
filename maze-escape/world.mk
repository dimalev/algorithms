.PHONY: clean-world run-world-units

clean-world:
	rm -f world

world: world.cpp
	g++ -x c++ -std=c++11 -O2 world.cpp -o world

world-units: world.cpp
	g++ -DUNITS -x c++ -std=c++11 world.cpp -o world-units

run-world-units: world-units
	./world-units < world-fixtures.txt > output.txt 2> log.txt && \
  echo -e "\nInput:" && cat world-fixtures.txt && \
  echo -e "\nOutput:" && cat output.txt && \
  echo -e "\n\nLog:\n" && cat log.txt && \
  echo -e "\nDiff:" && diff -w output.txt world-units-output.txt && echo -e "\nUnit Tests OK"
