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

int check_err(int err, char * err_type){
  if(err == -1){
    char err_buff[BUFFER_SIZE];
    sprintf(err_buff, "%s: ", err_type);
    perror(err_buff);
    return -1;
  }
  return 0;
}

// Takes a string and returns a new string minus the character at index i
char * removeSpace(char * line, char * newLine, int index){
  int j = 0;
  for (int i = 0; i < strlen(line); i++){
    if (i != index){
      printf("i: %d %c, j: %d %c\n", i, *(line + i), j, *(newLine + j));
      *(newLine + j) = *(line + i);
      j++;
    }
  }
  *(newLine + strlen(line) - 1) = 0;
  // for (int i = 0; i < strlen(newLine); i++){
  //   printf("New: %c\n", *(newLine + i));
  // }
  // for (int i = 0; i < strlen(line); i++){
  //   printf("Old: %c\n", *(line + i));
  // }
  return newLine;
}
