#include "parse.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void sighandler(int signo){
  if(signo==SIGINT){

  }
}

int main(){
  signal(SIGINT, sighandler);
  while (1){

    //print prompt
    printf(">> ");
    fflush(stdout);

    //get cmd
    char line[256];
    if(fgets(line, 256, stdin)){
      line[strlen(line) - 1] = 0;
      char * arg_ary[256];
      parse_args(line, arg_ary);

      // if it was exit stop the program
      if(!strcmp(arg_ary[0], "exit")){
        exit(0);
      }

      // fork
      if(!fork()){
        execvp(arg_ary[0], arg_ary);
      }
      else{
        int status;
        int kidid = wait(&status); //wait for child
      }
    }
    else{ //if EOF exit
      exit(0);
    }
  }
}
