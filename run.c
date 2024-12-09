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
 
  //take a parsed cmd chunk and ecexute the required files making the changes to stdin and stdout
  void flow_execution(char ** chunks, int index, int size, struct sigaction old){

    
    if(size <= 2){
      run_cmd(chunks[index], old);
    }
    //A a B b C

    // char * A = chunks[index];
    // char * a = chunks[index+1];
    // char * B = chunks[index+2];
    // char * b = chunks[index+3];
    // char * C = chunks[index+4];

    int old_stdin = fileno(stdin);
    int old_stdout = fileno(stdout);

    if(!strcmp(chunks[index+1], ">")){
      old_stdout = redirect_stdout_create_file(chunks[index+2]);
      run_cmd(chunks[index], old);
      reset_stdout(old_stdout);
    }

    if (!strcmp(chunks[index+1], "|")){
      old_stdout = redirect_stdout_create_file("temp");
      run_cmd(chunks[index], old);
      reset_stdout(old_stdout);


      old_stdin = redirect_stdin_create_file("temp");

      if (size > index + 3){
        old_stdout = redirect_stdout_create_file(chunks[index+4]);
      }
      run_cmd(chunks[index+2], old);
      reset_stdout(old_stdout);
      reset_stdin(old_stdin);

    }

    fflush(stdout);
    if(!strcmp(chunks[index+1], "<")){
      old_stdin = redirect_stdin_create_file(chunks[index + 2]);
      if (size > index + 3){
        if (!strcmp(chunks[index+3], "|")){
          old_stdout = redirect_stdout_create_file("temp");
        }
        if (!strcmp(chunks[index+3], ">")){
          old_stdout = redirect_stdout_create_file(chunks[index + 4]);
        }
      }
      run_cmd(chunks[index], old);
      reset_stdin(old_stdin);
      reset_stdout(old_stdout);
      if (size > index + 3){
        if (!strcmp(chunks[index+3], "|")){
          old_stdin = redirect_stdin_create_file("temp");

          if (size > index + 5){
            old_stdout = redirect_stdout_create_file(chunks[index+6]);
          }
          run_cmd(chunks[index+4], old);
          reset_stdout(old_stdout);
          reset_stdin(old_stdin);
        }
      }
    }

    for (int i = 0; i<size; i++){
      free(chunks[i]);
    }
  }

  //run a cmd_block including reset signal handling
  int run_cmd(char * cmd_block, struct sigaction old){

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
        
      }
      else{
        int status;
        wait(&status); //wait for child
      }
    }
    return 0;
  }
