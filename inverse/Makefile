start: main.o t1 t2

main.o: main.cpp
	g++ -O2 -fno-stack-limit -x c++ -std=c++11 main.cpp -o main.o

t1: input-1.txt output-1.txt main.o
	./main.o < input-1.txt > output.txt && \
  echo -e "\nInput:" && cat input-1.txt && \
  echo -e "\nOutput:" && cat output.txt && \
  echo -e "\nDiff:" && diff -w output.txt output-1.txt && echo -e "\nTest OK"

t2: input-2.txt output-2.txt main.o
	./main.o < input-2.txt > output.txt && \
  echo -e "\nInput:" && cat input-2.txt && \
  echo -e "\nOutput:" && cat output.txt && \
  echo -e "\nDiff:" && diff -w output.txt output-2.txt && echo -e "\nTest OK"
