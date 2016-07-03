.PHONY: output-*

start: main.o output-*

main.o: main.cpp
	g++ -O2 -fno-stack-limit -x c++ -std=c++11 main.cpp -o main.o

output-*: $(subst output,input,$@)
	./main.o < $(subst output,input,$@) > output.txt && \
  echo -e "\nInput:" && cat $(subst output,input,$@) && \
  echo -e "\nOutput:" && cat $@ && \
  echo -e "\nDiff:" && diff -w output.txt $@ && echo -e "\nTest OK"

