#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <pwd.h>

#include "parse.h"
#include "colors.h"


#define BUFFER_SIZE 256
#define TOKEN_SIZE 256

int check_err(int err, char * err_type){
  if(err == -1){
    char err_buff[BUFFER_SIZE];
    sprintf(err_buff, "%s: %s", err_type, strerror(errno));
    perror(err_buff);
    return -1;
  }
  return 0;
}

int special_cmd(char ** arg_ary){
  if(!strcmp(arg_ary[0], "exit")) {
    exit(0);
  }
  //if it was cd change dir
  if (!strcmp(arg_ary[0], "cd")) {
    check_err(chdir(arg_ary[1]), "chdir error");
    return 1;
  }

  if(!strcmp(arg_ary[0], "")){
    return 1;
  }
  return 0;
}

//print prompt, includes pwd and $
void prompt_print(){
  //dynamically stores cwd in string
  char *cwd = getcwd(NULL, 0);
  if (cwd == NULL){
    perror("getcwd error");
  }

  char * home;
  char * newCWD;
  char tilda[256];
  tilda[0] = '~';
  tilda[1] = '\0';
  if ((home = getenv("HOME"))){
    //printf("Home: %s\n",home);
    if ((newCWD = strstr(cwd, home))){
      newCWD += strlen(home);
      strcat(tilda, newCWD);
      strcpy(cwd, tilda);
      //printf("%s\n", cwd);
    }
  }

  //get username with struct passwd
  uid_t usr = geteuid();
  struct passwd * pas = getpwuid(usr);


  printf("\n");
  printf(GREEN"%s"COLOREND":"BLUE"%s"COLOREND"$", pas->pw_name, cwd);
  fflush(stdout);

  free(cwd);
}

void sighandler(int signo){
  if(signo==SIGINT){
    prompt_print();
  }
}

int main(){
  struct sigaction sa;
  struct sigaction old;
  sa.sa_handler = sighandler;
  sa.sa_flags = SA_RESTART;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGINT, &sa, &old);

  prompt_print();

  char input_buffer[BUFFER_SIZE];
  while (fgets(input_buffer, BUFFER_SIZE, stdin)){

    char * lines_ary[TOKEN_SIZE];

    parse_lines(input_buffer, lines_ary);

    for(int i = 0; lines_ary[i]; i++){
      char * line = lines_ary[i];
      char * new_line_pos;
      while (new_line_pos = strchr(line, '\n')){
        *new_line_pos = 0;
      }
      char *arg_ary[TOKEN_SIZE];
      parse_args(line, arg_ary);

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
    prompt_print();
  }
  return 0;
}
