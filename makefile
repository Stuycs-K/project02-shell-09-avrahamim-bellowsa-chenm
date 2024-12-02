compile: parse.o shell.o
	gcc -g -o shell parse.o shell.o

parse.o: parse.h parse.c
	gcc -c parse.c

shell.o: parse.h shell.c
	gcc -c shell.c

clean:
	rm *.o
	rm shell
