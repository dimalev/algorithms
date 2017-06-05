.PHONY: output-* units start release

# add units here, in case if you would like to run unit tests as part of usual routine
start: main-debug.o output-*

release: main.o

units: main-units.o
	./main-units.o < fixtures.txt > output.txt 2> log.txt && \
  echo -e "\nInput:" && cat fixtures.txt && \
  echo -e "\nOutput:" && cat output.txt && \
  echo -e "\n\nLog:\n" && cat log.txt && \
  echo -e "\nDiff:" && diff -w output.txt units-output.txt && echo -e "\nUnit Tests OK"

main-debug.o: main.cpp
	g++ -DALGO_DEBUG -O0 -g -fno-stack-limit -x c++ -std=c++11 main.cpp -o main-debug.o

main-units.o: main.cpp
	g++ -DALGO_DEBUG -DUNITS -O2 -fno-stack-limit -x c++ -std=c++11 main.cpp -o main-units.o

main.o: main.cpp
	g++ -O2 -fno-stack-limit -x c++ -std=c++11 main.cpp -o main.o

output-*: $(subst output,input,$@)
	./main-debug.o < $(subst output,input,$@) > output.txt 2> log.txt && \
  echo -e "\nInput:" && cat $(subst output,input,$@) && \
  echo -e "\nOutput:" && cat output.txt && \
  echo -e "\n\nLog:\n" && cat log.txt && \
  echo -e "\nDiff:" && diff -w output.txt $@ && echo -e "\nTest OK"
