compile: parse.o shell.o prompt.o util.o redirect.o
	@gcc -g -o shell parse.o shell.o prompt.o util.o redirect.o

parse.o: parse.h parse.c
	@gcc -c parse.c -Wall

util.o: util.h shell.h util.c
	@gcc -c util.c -Wall

prompt.o: colors.h prompt.c
	@gcc -c prompt.c -Wall

redirect.o: redirect.c 
	@gcc -c redirect.c -Wall

shell.o: parse.h shell.h prompt.h util.h redirect.h shell.c
	@gcc -c shell.c -Wall

clean:
	rm -f *.o shell
