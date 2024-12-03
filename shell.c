#include "parse.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256
#define TOKEN_SIZE 256

//print prompt, includes pwd and $
void prompt_print(){
  //dynamically stores cwd in string
  char *cwd = getcwd(NULL, 0);
  if (cwd == NULL) perror("getcwd error");
  
  printf("%s $", cwd);
  
  free(cwd);
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
  
  prompt_print();
  
  char line[BUFFER_SIZE];
  while (fgets(line, BUFFER_SIZE, stdin)){

    line[strlen(line) - 1] = 0;//delete newline
    char *arg_ary[TOKEN_SIZE];
    parse_args(line, arg_ary);

    // if it was exit stop the program
    if(!strcmp(arg_ary[0], "exit")) {
      exit(0);
    }
    else if (!strcmp(arg_ary[0], "cd")) {
      if (chdir(arg_ary[1])) perror("chdir error");
      else {
        prompt_print();
        continue;
      }
    }

    //cmd isn't cd or exit
    // fork
    if(!fork()){
      sigaction(SIGINT, &old, NULL);
      execvp(arg_ary[0], arg_ary);
    }
    else{
      int status;
      int kid_id = wait(&status); //wait for child
    }
    prompt_print();
  }
  
  return 0;
}
