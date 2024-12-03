compile: parse.o shell.o
	@gcc -g -o shell parse.o shell.o

parse.o: parse.h parse.c
	@gcc -g -c parse.c -Wall

shell.o: parse.h shell.c
	@gcc -g -c shell.c -Wall

clean:
	rm -f *.o shell
