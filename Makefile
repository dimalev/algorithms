PHONY: clean

clean:
	find . -iname main.o -or -iname log.txt -or -iname output.txt -or -iname Solution.class \
  | xargs rm
