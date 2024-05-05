GCC=gcc
CFLAGC= -Wall -Werror -Wextra -std=c11

all: clean cat

cat: 
	$(GCC) $(CFLAGC) cat.c -o cat

test:
	rm -f *o
	rm -f cat
	$(GCC) $(CFLAGC) cat.c -o cat
	./test_cat/test.sh


clean:
	rm -f *o
	rm -f cat
	clear
