#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "util.h"

//parse the args for execvp
int parse_args( char * line, char ** arg_ary ){
  int argIndex = 0;
  while (line){
  	*(arg_ary + argIndex) = strsep(&line, " ");
  	argIndex++;
  }
  *(arg_ary + argIndex) = NULL;
  return argIndex;
}

//parses set of semicolon seperated lines into ary
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

//finds the first example of < | or > in line and passes it into sep_on
// Takes line and looks for the first instance of < | or >, then puts that in sep_on
void sep_on_first_char(char * line, char * sep_on){ //sep_on must be malloced!!
  //goal is to sep on <, >, |
  // a < b | c > d -> {a,<,b,|,c,>,d}

  char * symbolv[3];
  symbolv[0] = ">";
  symbolv[1] = "<";
  symbolv[2] = "|";

  int lengths[3];
  for(int i = 0; i<3; i++){
    char * ptr = strstr(line, symbolv[i]);
    if (ptr == 0){
      lengths[i] = 255;//placeholder to not be minimum
    }
    else {
      lengths[i] = ptr - line;
    }
  }

  if(lengths[0] == lengths[1] && lengths[1] == lengths[2]){ // no sep occured
    strcpy(sep_on,"");
    return;
  }

  int min_length = min(lengths,3);

  strcpy(sep_on,symbolv[min_length]);
}

//parse a cmd sequence with redirects into a ary
void parse_opps(char * line, char ** opp_seperated_ary, int* size){
  int s = *size;
  char * sep_on = malloc(4);

  sep_on_first_char(line, sep_on);

  char * token = strsep(&line, sep_on);
  if (*(token) == ' '){
    char temptoken[strlen(token) - 1];
    removeSpace(token, temptoken, 0);
    strcpy(token, temptoken);
  }
  if (*(token + strlen(token) - 1) == ' '){
    char temptoken[strlen(token) - 1];
    removeSpace(token, temptoken, strlen(token) - 1);
    strcpy(token, temptoken);
  }

  opp_seperated_ary[s] = malloc(sizeof(char)*strlen(token));
  strcpy(opp_seperated_ary[s], token);
  s++;
  opp_seperated_ary[s] = sep_on;
  s++;

  *size = s;
  if(line && strcmp(line, "")){
    parse_opps(line, opp_seperated_ary,size);
  }
  //free(sep_on);
}
