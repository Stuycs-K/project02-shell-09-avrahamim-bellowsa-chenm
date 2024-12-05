#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <pwd.h>

#include "run.h"
#include "parse.h"
#include "util.h"
#include "shell.h"
#include "redirect.h"

#define MAXOPPS 100
// void flow_execution(char * in_line){
//     char * chunks[MAXOPPS];
//     char * line = malloc(sizeof(char)*strlen(line));
//     strcpy(line, in_line);
//     int size = 0;

//     parse_opps(line, chunks, &size);



// }

void flow_execution(char ** chunks, int index, int size, struct sigaction old){
  for(int i = 0; i<size; i++){
    printf("%s\n", chunks[i]);
  }
  if(size <= 2){
    run_cmd(chunks[index], old);
  }
  //A a B b C

  // char * A = chunks[index];
  // char * a = chunks[index+1];
  // char * B = chunks[index+2];
  // char * b = chunks[index+3];
  // char * C = chunks[index+4];

  if(index != 0){
    if(!strcmp(chunks[index-1], "|")){ //if this block is coming out of a pipe, set stdin to temp
      printf("Prev was | -> stdin=temp\n");
      redirect_stdin_create_file("temp");
    }
  }
  if(!strcmp(chunks[index+1], ">")){
    int old_stdout = redirect_stdout_create_file(chunks[index+2]);
    run_cmd(chunks[index], old);
    reset_fds(fileno(stdin), old_stdout);
  }

  if(!strcmp(chunks[index+1], "<")){
    printf("redirecting stdin to... > %s\n", chunks[index+2]);
    redirect_stdin_create_file(chunks[index+2]);

    if(!strcmp(chunks[index+3], "|")){
      printf("redirecting stdout to... > %s\n", "temp");
      redirect_stdout_create_file("temp");
      run_cmd(chunks[index], old);
      flow_execution(chunks, index+4, size-4, old);
    }

    if(!strcmp(chunks[index+3], ">")){
      printf("redirecting stdout to... > %s\n", chunks[index+4]);
      redirect_stdout_create_file(chunks[index+4]);
      run_cmd(chunks[index], old);
    }




  }
}

int run_cmd(char * cmd_block, struct sigaction old){

  printf("cmd: %s\n", cmd_block);
  char *arg_ary[TOKEN_SIZE];

  parse_args(cmd_block, arg_ary);

  //CHECK IF USER ENTERED A SPECIAL CMD
  if(!special_cmd(arg_ary)){

    //No special cmd -> fork
    int fork_result = fork();
    check_err(fork_result, "fork error");
    if(!fork_result){
      //child
      sigaction(SIGINT, &old, NULL);
      int exec_vp_result = execvp(arg_ary[0], arg_ary);
      if(check_err(exec_vp_result, "execvp err")){
        exit(0);
      }
    }
    else{
      int status;
      int kid_id = wait(&status); //wait for child
    }
  }
}
