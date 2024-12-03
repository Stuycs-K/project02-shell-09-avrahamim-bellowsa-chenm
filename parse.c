#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void parse_args( char * line, char ** arg_ary ){
  int argIndex = 0;
  while (line){
  	*(arg_ary + argIndex) = strsep(&line, " ");
  	argIndex++;
  }
  *(arg_ary + argIndex) = NULL;
}

void parse_lines(char * input, char ** line_ary){
  int i;
  for (i = 0; input; i++){
    line_ary[i] = strsep(&input,";");
  }
  line_ary[i] = NULL;
}
