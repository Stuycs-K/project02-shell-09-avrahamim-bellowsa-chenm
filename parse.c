#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void parse_args( char * line, char ** arg_ary ){
  int argIndex = 0;
  while (line){
  	*(arg_ary + argIndex) = strsep(&line, " ");
  	argIndex++;
  }
  *(arg_ary + argIndex) = NULL;
}
