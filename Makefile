all: abc.c
	gcc -g -Wall -lm -o abc abc.c

clean:
	$(RM) abc.o
