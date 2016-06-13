start: main.o
	./main.o < input-1.txt > output.txt && \
  echo -e "\nInput:" && cat input-1.txt && \
  echo -e "\nOutput:" && cat output.txt && \
  echo -e "\nDiff:" && diff -w output.txt output-1.txt && echo -e "\nTest OK"

main.o: main.cpp
	g++ -O2 -fno-stack-limit -x c++ -std=c++11 main.cpp -o main.o
