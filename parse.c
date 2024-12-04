#define _GNU_SOURCE
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

void parse_opps(char * line, char ** opp_seperated_ary){
  //goal is to sep on <, >, |
  // a < b | c > d -> {a,<,b,|,c,>,d}


  char * greater_char = ">";
  char * less_char = "<";
  char * pipe_char = "|";

  char * symbolv[3];
  symbolv[0] = greater_char;
  symbolv[1] = less_char;
  symbolv[2] = pipe_char;

  unsigned int line_start = (unsigned int) line;

  unsigned int first_greater = ( unsigned int ) strchrnul(line,'>') - line_start;
  unsigned int first_less = ( unsigned int ) strchrnul(line, '<') - line_start;
  unsigned int first_pipe = ( unsigned int ) strchrnul(line, '|') - line_start;

  char * start = NULL;


  printf("%d,  >: %u, <: %u, |: %u\n", strlen(line), first_greater, first_less, first_pipe);

}

int main(){
  parse_opps("|  ", NULL);
}