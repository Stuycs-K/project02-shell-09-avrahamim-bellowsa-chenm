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
#include "history.h"

#define MAXOPPS 256

struct termios original;

//is the cmd a shell specific cmd?
int special_cmd(char ** arg_ary){
  if(!strcmp(arg_ary[0], "exit")) {
    disableRawMode(&original);
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

//handle the signal
void sighandler(int signo){
  if(signo==SIGINT){
    prompt_print();
  }
}

int main(){
  enableRawMode(&original);
  
  struct sigaction sa;
  struct sigaction old;
  sa.sa_handler = sighandler;
  sa.sa_flags = SA_RESTART;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGINT, &sa, &old);

  prompt_print();

  char input_buffer[BUFFER_SIZE];
  while (1){
    fill_input_buffer(input_buffer);
    
    //fprintf(stderr, "%s\n", input_buffer);
    //fprintf(stderr, "%d\n", strcmp(input_buffer, "exit"));

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
      size--;


      flow_execution(chunks,0,size,old);
      free(myline);
      // for (int i = 0; i < size; i++){
      //   free(chunks[i]);
      // }
    }
    prompt_print();
  }
  
  disableRawMode(&original);
  return 0;
}
