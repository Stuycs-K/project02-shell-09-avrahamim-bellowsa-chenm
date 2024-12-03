#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "parse.h"
#include "colors.h"

#define BUFFER_SIZE 256
#define TOKEN_SIZE 256

int special_cmd(char ** arg_ary){
  if(!strcmp(arg_ary[0], "exit")) {
    exit(0);
  }
  //if it was cd change dir
  if (!strcmp(arg_ary[0], "cd")) {
    if (chdir(arg_ary[1])) perror("chdir error");
    
    return 1;
    
  }

  return 0;
}

//print prompt, includes pwd and $
void prompt_print(){
  //dynamically stores cwd in string
  char *cwd = getcwd(NULL, 0);
  if (cwd == NULL) perror("getcwd error");
  
  char * usr = getlogin();

  printf(GREEN"%s"COLOREND":"BLUE"%s"COLOREND"$", usr, cwd);
  
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
  
  char input_buffer[BUFFER_SIZE];
  while (fgets(input_buffer, BUFFER_SIZE, stdin)){

    char * lines_ary[TOKEN_SIZE];

    parse_lines(input_buffer, lines_ary);

    for(int i = 0; lines_ary[i]; i++){
      char * line = lines_ary[i];
      char * new_line_pos;
      while (new_line_pos = strchr(line, '\n')){
        *new_line_pos = 0;
      }
      char *arg_ary[TOKEN_SIZE];
      parse_args(line, arg_ary);

      //CHECK IF USER ENTERED A SPECIAL CMD
      if(!special_cmd(arg_ary)){

        //No special cmd -> fork
        if(!fork()){
          //child
          sigaction(SIGINT, &old, NULL);
          execvp(arg_ary[0], arg_ary);
        }
        else{
          int status;
          int kid_id = wait(&status); //wait for child
        }
      }
    }
    prompt_print();
  }
  return 0;
}
