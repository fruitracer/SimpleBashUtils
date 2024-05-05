SHELL := /bin/bash
GCC=gcc
CFLAGC= -Wall -Werror -Wextra -std=c11
LEAKS=valgrind --tool=memcheck --leak-check=yes
FILE=test_grep/test.txt
FILE2=test_grep/t1.txt    
PATTERN_FILE=test_grep/patterns.reg

all: clean grep 

grep: 
	$(GCC) $(CFLAGC) grep.c -o grep

test:
	rm -f *o
	rm -f grep
	$(GCC) $(CFLAGC) grep.c -o grep
	./test_grep/test.sh

clean:
	rm -f *o
	rm -f grep
