.PHONY: output-*

start: Solution.class output-*

Solution.class: Solution.java
	javac Solution.java

output-*: $(subst output,input,$@)
	java Solution < $(subst output,input,$@) > output.txt 2> log.txt && \
  echo -e "\nInput:" && cat $(subst output,input,$@) && \
  echo -e "\nOutput:" && cat output.txt && \
  echo -e "\n\nLog:\n" && cat log.txt && \
  echo -e "\nDiff:" && diff -w output.txt $@ && echo -e "\nTest OK"

