#include "parse.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
  while (1){
    char line[256];
    fgets(line, 256, stdin);
    line[strlen(line) - 1] = 0;

    printf("%s\n", line);


    char * arg_ary[256];
    parse_args(line, arg_ary);


    if(!strcmp(arg_ary[0], "exit")){
      exit(0);
    }

    if(!fork()){
      execvp(arg_ary[0], arg_ary);
    }
  }
}
