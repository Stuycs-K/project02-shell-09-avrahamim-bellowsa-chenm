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
  int cursor = 0;
  while (1){
    cursor = 0;

    memset(input_buffer, 0, MAX_COMMAND_LENGTH);
    while (1) {
      char c;
      if (read(STDIN_FILENO, &c, 1) == -1) continue;

      if (c == '\n') {
        printf("\n");
        if (cursor > 0) {
          add_to_history(input_buffer);
          history_index = history_count;
        }
        break;
      }
      else if (c == 127) {//backspace
        if (cursor > 0) {
          input_buffer[--cursor] = '\0';
          printf("\b \b"); fflush(stdout);
        }
      }
      else if (c == '\033') {//escape sequence
        char seq[2];
        if (read(STDIN_FILENO, &seq[0], 1) == -1) continue;
        if (read(STDIN_FILENO, &seq[1], 1) == -1) continue;

        if (seq[0] == '[') {
          if (seq[1] == 'A') {//up arrow
            handle_up_arrow(input_buffer, &cursor);
          }
          else if (seq[1] == 'B') {//down arrow
            handle_down_arrow(input_buffer, &cursor);
          }
        }
      }
      else if (c == 4) {//Ctrl+D EOF
        //printf("\nExiting shell...\n");
        disableRawMode(&original);
        exit(0);
        //return 0;
      }
      else {
        printf("%c",c); fflush(stdout);
        input_buffer[cursor++] = c;
      }
    }
    
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
