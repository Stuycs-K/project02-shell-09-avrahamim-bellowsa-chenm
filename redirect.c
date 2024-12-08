#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#include "redirect.h"
#include "util.h"

//redirect stdout to fd
int redirect_stdout(int fd){
  int stdfileno = fileno(stdout);
  fflush(stdout);
  int old_stdout = dup(stdfileno);
  check_err(dup2(fd, stdfileno), "dup2 err");
  return old_stdout;
}

//open file and then redirect stdout to it
int redirect_stdout_create_file(char * name){
    int fd = open(name,  O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if(check_err(fd, "file creat err")){
        return -1;
    }
    return redirect_stdout(fd);
}

//redirect stdin to fd
int redirect_stdin(int fd){
    int stdfileno = fileno(stdin);
    int old_stdin = dup(stdfileno);
    check_err(dup2(fd, stdfileno), "dup2 err");
    return old_stdin;
}

//open file and then redirect stdin to it
int redirect_stdin_create_file(char * name){
    int fd = open(name, O_RDONLY, 0);
    return redirect_stdin(fd);
}

//reset stdin to old_stdin
void reset_stdin(int old_stdin){
    int stdinno = fileno(stdin);
    dup2(old_stdin, stdinno);

}

//reset stdout to old_stdout
void reset_stdout(int old_stdout){
  int stdoutno = fileno(stdout);
  dup2(old_stdout, stdoutno);
}
