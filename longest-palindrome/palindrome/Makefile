.PHONY: output-*

start: main.o output-*

main.o: main.cpp
	g++ -DALGO_DEBUG -O2 -fno-stack-limit -x c++ -std=c++11 main.cpp -o main.o

output-*: $(subst output,input,$@)
	./main.o < $(subst output,input,$@) > output.txt 2> log.txt && \
  echo -e "\nInput:" && cat $(subst output,input,$@) && \
  echo -e "\nOutput:" && cat output.txt && \
  echo -e "\n\nLog:\n" && cat log.txt && \
  echo -e "\nDiff:" && diff -w output.txt $@ && echo -e "\nTest OK"


brute.o: brute-force.cpp
	g++ -DALGO_DEBUG -O2 -fno-stack-limit -x c++ -std=c++11 brute-force.cpp -o brute.o
