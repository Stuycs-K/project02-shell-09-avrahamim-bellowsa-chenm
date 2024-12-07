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

static struct history_log * history_root;
static struct history_log * history_pointer;
char input_buffer[BUFFER_SIZE];

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

void history_handler(int signo){
  if(signo == SIGQUIT){ //ctrl + \ -> hist up 
      printf("%s\n", history_pointer->line);
      strcpy(input_buffer, history_pointer->line);
      history_pointer = history_pointer->next;
      if(history_pointer == NULL){
        history_pointer = history_root;
      }
  }
}

int main(){
  // history_root = new_history_log("");
  // history_pointer = history_root;

  printf("%s: hist\n", history_pointer->line);
  struct sigaction sa;
  struct sigaction old;
  sa.sa_handler = sighandler;
  sa.sa_flags = SA_RESTART;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGINT, &sa, &old);
  
  struct sigaction sa2;
  sa2.sa_handler = history_handler;
  sa2.sa_flags = SA_RESTART;
  sigemptyset(&sa2.sa_mask);
  sigaction(SIGQUIT, &sa2, &old);
  sigaction(SIGTSTP, &sa2, &old);
  

  
  prompt_print();


  while (fgets(input_buffer, BUFFER_SIZE, stdin)){

    char * lines_ary[TOKEN_SIZE];

    parse_lines(input_buffer, lines_ary);

    for(int i = 0; lines_ary[i]; i++){
      char * line = lines_ary[i];
      stripln(line);

      struct history_log * new_entry = new_history_log(line);
      history_root = history_log_add(history_root, new_entry);
      history_pointer = history_root;
      for (struct history_log * i = history_root; i; i=i->next){
        printf("%s\n", i->line);
      }

      char * chunks[MAXOPPS];

      char * myline = malloc(sizeof(char)*strlen(line));
      strcpy(myline, line);
      int size = 0;
      parse_opps(myline, chunks, &size);
      size--; //acount for ""


      flow_execution(chunks,0,size,old);
      free(myline);
      // for (int i = 0; i < size; i++){
      //   free(chunks[i]);
      // }
    }
    prompt_print();
  }
  return 0;
}
