#include "parse.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void prompt_print(){
  //print prompt
    printf("\n>> ");
    fflush(stdout);
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
  
  while (1){

    
    prompt_print();
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
        sigaction(SIGINT, &old, NULL);
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
