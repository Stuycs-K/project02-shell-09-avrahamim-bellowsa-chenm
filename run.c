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