compile: parse.o shell.o prompt.o util.o redirect.o run.o
	@gcc -g -o shell parse.o shell.o prompt.o util.o redirect.o run.o

parse.o: parse.h parse.c
	@gcc -g -c parse.c -Wall

util.o: util.h shell.h util.c
	@gcc -c -g util.c -Wall

prompt.o: colors.h prompt.c
	@gcc -c -g prompt.c -Wall

redirect.o: redirect.c 
	@gcc -c -g redirect.c -Wall

shell.o: parse.h shell.h prompt.h util.h redirect.h shell.c
	@gcc -c -g shell.c -Wall

run.o: run.c shell.h util.h parse.h
	@gcc -c -g run.c -Wall

clean:
	rm -f *.o shell
