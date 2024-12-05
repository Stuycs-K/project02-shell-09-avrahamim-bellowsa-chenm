cmd: ls
STD: 1
STD: 1
README.md
a.out
colors.h
makefile
parse.c
parse.h
parse.o
prompt.c
prompt.h
prompt.o
redirect.c
redirect.h
redirect.o
run.c
run.h
run.o
shell
shell.c
shell.h
shell.o
t
temp
util.c
util.h
util.o

[32mabellows50[0m:[34m~/systems/project02-shell-09-avrahamim-bellowsa-chenm[0m$ cat t

cmd: cat t
STD: 1
STD: 1

[32mabellows50[0m:[34m~/systems/project02-shell-09-avrahamim-bellowsa-chenm[0m$ cat shell.c

cmd: cat shell.c
STD: 1
STD: 1
// #define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <pwd.h>
#include <string.h>


#include "parse.h"
#include "colors.h"
#include "shell.h"
#include "prompt.h"
#include "util.h"
#include "redirect.h"
#include "run.h"

#define MAXOPPS 256

int special_cmd(char ** arg_ary){
  if(!strcmp(arg_ary[0], "exit")) {
    exit(0);
  }
  //if it was cd change dir
  if (!strcmp(arg_ary[0], "cd")) {
    check_err(chdir(arg_ary[1]), "chdir error");
    return 1;
  }

  if(!strcmp(arg_ary[0], "")){
    return 1;
  }
  return 0;
}

void sighandler(int signo){
  if(signo==SIGINT){
    prompt_print();
  }
}

int main(){
  struct sigaction sa;
  struct sigaction old;
  sa.sa_handler = sighandler;
  sa.sa_flags = SA_RESTART;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGINT, &sa, &old);

  prompt_print();

  char input_buffer[BUFFER_SIZE];
  while (fgets(input_buffer, BUFFER_SIZE, stdin)){

    char * lines_ary[TOKEN_SIZE];

    parse_lines(input_buffer, lines_ary);

    for(int i = 0; lines_ary[i]; i++){
      char * line = lines_ary[i];
      stripln(line);
      
      char * chunks[MAXOPPS];
      char * myline = malloc(sizeof(char)*strlen(line));
      strcpy(myline, line);
      int size = 0;
      parse_opps(myline, chunks, &size);
   

      flow_execution(chunks,0,size,old);
      // run_cmd(line, old);
    }
    prompt_print();
  }
  return 0;
}

[32mabellows50[0m:[34m~/systems/project02-shell-09-avrahamim-bellowsa-chenm[0m$ cat shell.c
>
te

redirecting stdout to ... > te