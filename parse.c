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


int min(int * intv, int s){
  int min_index = 0;
  for(int i = 1; i<s; i++){
    if(intv[i]<intv[min_index]){
      min_index = i;
    }
  }
  return min_index;
}

void sep_on_first_char(char * line, char * sep_on){ //sep_on must be malloced!!
  //goal is to sep on <, >, |
  // a < b | c > d -> {a,<,b,|,c,>,d}

  char * symbolv[3];
  symbolv[0] = ">";
  symbolv[1] = "<";
  symbolv[2] = "|";

  int lengths[3];
  for(int i = 0; i<3; i++){
    char * mv_line = malloc(strlen(line)*sizeof(char));
    strcpy(mv_line, line);
    char * token = strsep(&mv_line, symbolv[i]);
    lengths[i] = strlen(token);
    free(token);
  }

  if(lengths[0] == lengths[1] && lengths[1] == lengths[2]){ // no sep occured
    return;
  }

  int min_length = min(lengths,3);

  strcpy(sep_on,symbolv[min_length]);
}

void parse_opps(char * line, char ** opp_seperated_ary, int* size){
  int s = *size;
  char * sep_on = malloc(sizeof(char));

  sep_on_first_char(line, sep_on);

  char * token = strsep(&line, sep_on);

  opp_seperated_ary[s] = token;
  s++;
  opp_seperated_ary[s] = malloc(sizeof(char));
  strcpy(opp_seperated_ary[s], sep_on);
  s++;

  *size = s;
  if(line){
    printf("LINE: %s\n", line);
    parse_opps(line, opp_seperated_ary,size);
  }
}

int main(){
  char * test[256];
  char * line = malloc(sizeof(char)*256);
  strcpy(line, "a c rbicus<b|c>d");
  int s = 0;
  
  parse_opps(line, test, &s);

  for (int i = 0; i<s; i++){
    if(test[i]){
      printf("%s\n", test[i]);
    }
  }
  // parse_opps("gar<d|<|> ", test, 0);
}