#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "shell.h"
#include "util.h"
#include "history.h"

//check if err occured and print if it did -- returns bool of whether err occured
int check_err(int err, char * err_type){
  if(err == -1){
    char err_buff[BUFFER_SIZE];
    sprintf(err_buff, "%s: ", err_type);
    perror(err_buff);
    return -1;
  }
  return 0;
}

//remove ln from string
void stripln(char * string){
  char * new_line_pos;
  //remove \n
  while ( (new_line_pos = strchr(string, '\n')) ){
    *new_line_pos = 0;
  }
}

// Takes a string and returns a new string minus the character at index i
char * removeSpace(char * line, char * newLine, int index){
  int j = 0;
  for (int i = 0; i < strlen(line); i++){
    if (i != index){
      *(newLine + j) = *(line + i);
      j++;
    }
  }
  *(newLine + strlen(line) - 1) = 0;
  return newLine;
}

//fills input buffer char by char
void fill_input_buffer(char *input_buffer, struct termios *original) {
  int cursor = 0;

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
      disableRawMode(original);
      exit(0);
      //return 0;
    }
    else {
      printf("%c",c); fflush(stdout);
      input_buffer[cursor++] = c;
    }
  }
}